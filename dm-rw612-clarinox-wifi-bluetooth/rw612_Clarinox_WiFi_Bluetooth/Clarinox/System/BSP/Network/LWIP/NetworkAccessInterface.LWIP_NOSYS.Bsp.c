/*******************************************************************************
*
* Project             Clarinox Network Architecture
* File                NetworkAccessInterface.LWIP_NOSYS.Bsp.c
* Description         NetworkAccessInterface implementation for LWIP stack NOSYS mode
*
* This file contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/


#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include "Thread.Bsp.h"
#include "ClxSocketWrapper.h"
#include "ClarinoxWLAN.h"
#include "ClxNetworkPing.h"
#if defined(USE_DHCP_SERVER)
#include "ClxDhcpServer.h"
#endif
#include "string.h"
#include "stdio.h"
#include "assert.h"

#if defined(CLX_WPA_SUPPLICANT) && (CLX_PACKAGE_A2L_RPC == 0)
#include "Wlan.WpaSupplicant.Bsp.h"
#endif
    
#include "lwip/opt.h"
#include "lwip/init.h"
#include "lwip/timeouts.h"
#include "lwip/dhcp.h"
#include "netif/etharp.h"
#include "netconfig.h"



#if !defined(NO_SYS) || (NO_SYS == 0)
#   define "Define NO_SYS as 1 in lwipopts.h"
#endif

#if !defined(SYS_LIGHTWEIGHT_PROT) || (SYS_LIGHTWEIGHT_PROT == 0)
#   define "Define SYS_LIGHTWEIGHT_PROT as 1 in lwipopts.h"
#endif

#if !defined(LWIP_TIMERS_CUSTOM) || (LWIP_TIMERS_CUSTOM == 0)
#   define "Define LWIP_TIMERS_CUSTOM as 1 in lwipopts.h"
#endif

#if (LWIP_NETIF_API == 1)
#   define "Define LWIP_NETIF_API as 0 in lwipopts.h"
#endif

#define INLINE static

#if !defined(LWIP_THREAD_STACK_SIZE)
#   define LWIP_THREAD_STACK_SIZE                       TCPIP_THREAD_STACK_SIZE
#endif

#if !defined(LWIP_THREAD_PRIORITY_LEVEL)
#   define LWIP_THREAD_PRIORITY_LEVEL                   ClxThreadPriority_Medium
#endif

#define LWIP_DATA_HANDLING_CONTEXT_PRIORITY             1
#define LWIP_INDICATION_HANDLING_CONTEXT_PRIORITY       3
#define NETIF_TIMER_PRIORITY                            3
#define LWIP_APP_REQUEST_HANDLING_CONTEXT_PRIORITY      3

#define LWIP_MAX_APP_REQUEST_LENGTH					    64 /* Bytes */


extern void sys_init(void);
extern void sys_deinit(void);


#if defined(USE_DHCP_SERVER)
extern ClxAsyncNetworkSocket clxCreateLwipAsyncUdpSocket();
#endif

extern ClxAsyncNetworkSocket clxLwipCreateLwipAsyncEchoRequestSocket();


void destroyLwipNetworkAccessInterface(struct ClxNetworkAccessInterface* interface);

static void lwipRxHandlingTaskProc 			(struct ClxSchedulerTask* task);
static void lwipIndicationHandlingTaskProc 	(struct ClxSchedulerTask* task);
static void lwipAppCommandHandler 			(struct ClxSchedulerMessageHandler* context,
											 struct ClxSchedulerMessage* message,
											 enum ClxSchedulerMessageHandlerAction action);


#if defined(USE_IPERF)
#   include "lwip/apps/lwiperf.h"
#endif

struct ClxLwipNetworkInterfaceStruct;

#if defined(CLX_64BIT_SUPPORT)
    typedef ull ClxStatValue;
#   define STAT_VALUE_FORMAT        "%llu"
#else
    typedef u4 ClxStatValue;
#   define STAT_VALUE_FORMAT        "%u"    
#endif


/***********************
LwipTaskState
************************/
typedef enum LwipTaskStateEnum
{
    LwipTaskState_Idle,
    LwipTaskState_Scheduled
} LwipTaskState;


/*************************
LwipTaskStruct
**************************/
typedef struct LwipTaskStruct
{
    struct ClxSchedulerTask     			base;   /* Must be the very first member */

    struct ClxLwipNetworkInterfaceStruct* 	netif;
    LwipTaskState                           state;
} LwipTask;


/*************************
LwipAppCommandStruct
**************************/
typedef struct LwipAppCommandStruct
{
    struct ClxSchedulerMessage     			base;   /* Must be the very first member */

    s1										args[LWIP_MAX_APP_REQUEST_LENGTH + 1];
} LwipAppCommand;


/***********************
LwipTimer
************************/
typedef struct LwipTimerStruct
{ 
    struct ClxSchedulerTimer base;
    struct lwip_cyclic_timer arg;
} LwipTimer;


/***********************
LwipNetworkInterface
************************/
typedef struct ClxLwipNetworkInterfaceStruct
{
    struct ClxCQueueable                queueable;              /* MUST be the first object in this struct */
    struct ClxNetworkAccessInterface    base;
 
    struct netif                        netif_;	
    struct ClxNetworkTransportHandle*   transportHandle;

    ClxNetworkDeviceRole                role;
        
    LwipTask*							rxHandlingTask;
    LwipTask*							indicationHandlingTask;

    u1                                  localAddr[6];
    
	boolean 			                linkUp; 

#if defined(USE_DHCP_SERVER)
    ClxDhcpv4ServerHandle               dhcpv4ServerHandle;
#endif

#if defined(CLX_NET_IF_STATS)
	ClxStatValue						totalTxBytesSent;
	ClxStatValue						totalTxBytesCompleted;
	ClxStatValue						totalTxPacketsSent;  
    ClxStatValue                        totalTxPacketsCompleted;
	ClxStatValue						totalRxBytesReceived;
	ClxStatValue						totalRxBytesHandled;
	ClxStatValue						totalRxPacketsReceived;
	ClxStatValue						totalRxPacketsHandled;    
	ClxStatValue						totalTxBytesDiscarded_NoBuf;
	ClxStatValue						totalRxBytesDiscarded_NoBuf;
	ClxStatValue						totalRxBytesDiscarded_Error;
	ClxStatValue						numberOfTimesRxTaskScheduled;
#endif
} LwipNetworkInterface;


#define GET_INTERFACE(arg)              ((LwipNetworkInterface*)(arg->userData))


/***********************
LwipModule
************************/
struct LwipModule
{  
    ClxThreadHandle                     threadHandle;
    ClxScheduler                        scheduler; 

    ClxCQueue  							interfaceQueue;          /* Queue of interfaces */

    ClxCQueue                           timersQueue;
    ClxNetworkBufferDescriptorChain     freeBufferDescriptors;

    struct ClxSchedulerMessageHandler* 	appRequestContext;

#if !defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
    ClxMutex                            mutex;
#endif

#ifdef USE_IPERF
    void*                               tcpIperfServerHandle;
#endif
};


/***********************
ClxLwipConfiguration
************************/
typedef struct ClxLwipConfigurationStruct
{
    ClxSocketIpv4Address    clientStaticIpv4;
    ClxSocketIpv4Address    clientIpv4Netmask;
    ClxSocketIpv4Address    clientIpv4Gateway;
    ClxSocketIpv4Address    routerStaticIpv4;
    ClxSocketIpv4Address    routerIpv4Netmask;
    ClxSocketIpv4Address    routerIpv4Gateway;
} ClxLwipConfiguration;


static struct LwipModule lwipModule;

static ClxLwipConfiguration predefinedLwipConfig;


ClxScheduler clxGetLwipScheduler()
{
    return lwipModule.scheduler;
}

#if defined(USE_IPERF)
static void lwiperf_report(void *arg, enum lwiperf_report_type report_type,
                           const ip_addr_t* local_addr, u16_t local_port, const ip_addr_t* remote_addr, u16_t remote_port,
                           u32_t bytes_transferred, u32_t ms_duration, u32_t bandwidth_kbitpsec)
{

    ClxStdOutput stdoutput = (ClxStdOutput)arg;

    u4 remoteAddr_HostOrder = CLX_NTOHL(remote_addr->addr);
    
    stdoutput("\n---------------------------------------------\n");
    stdoutput("Iperf TCP:\n");
    stdoutput("RemoteAddr : %u.%u.%u.%u:%u\n", 
                           CLX_IP4_ADDRESS_A(remoteAddr_HostOrder),
                           CLX_IP4_ADDRESS_B(remoteAddr_HostOrder),
                           CLX_IP4_ADDRESS_C(remoteAddr_HostOrder),
                           CLX_IP4_ADDRESS_D(remoteAddr_HostOrder),
                           CLX_NTOHS(remote_port));
    
    stdoutput("Data Transferred : %u Bytes\n", bytes_transferred);
    stdoutput("Duration : %u ms\n", ms_duration);    
    stdoutput("Bandwidth : %u kbps\n", bandwidth_kbitpsec);
    stdoutput("---------------------------------------------\n");    
}
#endif


/*****************************************
clxNetStackProcessSoftFrameConfigParams
*****************************************/
ClxResult clxNetStackProcessSoftFrameConfigParams(ClxGetSoftFrameIntegerParam getIntParam, ClxGetSoftFrameStringParam getStrParam)
{
    clxMemSet(&predefinedLwipConfig, 0, sizeof(predefinedLwipConfig));

    const s1* str = NULL;

    ClxNetworkServiceAddress ipv4;
    clxMemSet(&ipv4, 0, sizeof(ipv4));

#ifndef USE_DHCP_CLIENT
    str = getStrParam("NET_CLIENT_IPV4_ADDR");
    if (str)
    {
        if (clxNetStr2Addr(ClxNetworkServiceAddressType_IP4, str, &ipv4) != CLX_SUCCESS)
        {
            return CLX_FAIL;
        }

        predefinedLwipConfig.clientStaticIpv4 = ipv4.u.ip4.addr;
    }

    str = getStrParam("NET_CLIENT_IPV4_NETMASK");
    if (str)
    {
        if (clxNetStr2Addr(ClxNetworkServiceAddressType_IP4, str, &ipv4) != CLX_SUCCESS)
        {
            return CLX_FAIL;
        }

        predefinedLwipConfig.clientIpv4Netmask = ipv4.u.ip4.addr;
    }

    str = getStrParam("NET_CLIENT_IPV4_GATEWAY");
    if (str)
    {
        if (clxNetStr2Addr(ClxNetworkServiceAddressType_IP4, str, &ipv4) != CLX_SUCCESS)
        {
            return CLX_FAIL;
        }

        predefinedLwipConfig.clientIpv4Gateway = ipv4.u.ip4.addr;
    }
#endif

    str = getStrParam("NET_ROUTER_IPV4_ADDR");
    if (str)
    {
        if (clxNetStr2Addr(ClxNetworkServiceAddressType_IP4, str, &ipv4) != CLX_SUCCESS)
        {
            return CLX_FAIL;
        }

        predefinedLwipConfig.routerStaticIpv4 = ipv4.u.ip4.addr;
    }

    str = getStrParam("NET_ROUTER_IPV4_NETMASK");
    if (str)
    {
        if (clxNetStr2Addr(ClxNetworkServiceAddressType_IP4, str, &ipv4) != CLX_SUCCESS)
        {
            return CLX_FAIL;
        }

        predefinedLwipConfig.routerIpv4Netmask = ipv4.u.ip4.addr;
    }

    str = getStrParam("NET_ROUTER_IPV4_GATEWAY");
    if (str)
    {
        if (clxNetStr2Addr(ClxNetworkServiceAddressType_IP4, str, &ipv4) != CLX_SUCCESS)
        {
            return CLX_FAIL;
        }

        predefinedLwipConfig.routerIpv4Gateway = ipv4.u.ip4.addr;
    }

    return CLX_SUCCESS;
}


/***********************
LwipTask
************************/
static LwipTask* createLwipTask(LwipNetworkInterface* netif,
                                const s1* name,
                                ClxSchedulerTaskCallback callback,
                                u1 priority)
{
    LwipTask* ret = (LwipTask*)clxCreateSchedulerTask(lwipModule.scheduler,
                                                      name,
                                                      callback,
                                                      sizeof(LwipTask),
                                                      priority);

    CLX_ASSERT(ret);
    ret->netif = netif;
    ret->state = LwipTaskState_Idle;

    return ret;
}

static void destroyLwipTask(LwipTask* task)
{
    clxDeleteSchedulerTask(&task->base);
}




/***********************
LwipModule
************************/
INLINE void* lock()
{
#if defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
	return clxBspDisableOsScheduler();
#else
	clxAcquireMutex(lwipModule.mutex);
    return NULL;
#endif
}

INLINE void unlock(void* lockStatus)
{
#if defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
	clxBspEnableOsScheduler(lockStatus);
#else
	clxReleaseMutex(lwipModule.mutex);
#endif
}

#if defined(CLX_WLAN_PREFER_SPEED_OVER_LATENCY)
static void idleContextCallback (struct ClxSchedulerIdleContext* this_)
{
	ClxCQueueIterator lwifIter;

	clxCQueueFront(&lwipModule.interfaceQueue, &lwifIter);

	while (clxCQueueIteratorIsValid(&lwifIter))
	{
		LwipNetworkInterface* lwipif = (LwipNetworkInterface*)lwifIter.current;

        clxNetworkInterfaceFlushPendingTxPackets(lwipif->transportHandle);
        
		clxCQueueIteratorNext(&lwifIter);
	}
}
#endif

static ClxResult CLX_CALLBACK threadProc(void* data)
{
#if defined(CLX_WLAN_PREFER_SPEED_OVER_LATENCY)  
    struct ClxSchedulerIdleContext* idleContext = clxCreateSchedulerIdleContext(idleContextCallback, sizeof(struct ClxSchedulerIdleContext));
    CLX_DEBUG_ASSERT(idleContext);
    
    clxSetSchedulerIdleContext(lwipModule.scheduler, idleContext);
#endif
    
	clxRunSchedulerLoop(lwipModule.scheduler);

#if defined(CLX_WLAN_PREFER_SPEED_OVER_LATENCY)
    clxDeleteSchedulerIdleContext(idleContext);
#endif    
	return 0;
}

static ClxNetworkBufferDescriptor* getFreeDescriptor()
{
    void* lockStatus = lock();
    ClxNetworkBufferDescriptor* desc = clxNetworkBufferDescriptorChainPopFirst(&lwipModule.freeBufferDescriptors);
    unlock(lockStatus);

    if (!desc)
    {
        desc = clxNetworkInterfaceAllocateBufferDescriptor();
        assert(desc);
    }

    return desc;
}

ClxResult clxTcpIpModule_Init()
{
	sys_init();
    
#if !defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
    lwipModule.mutex = clxCreateMutex();
#endif

    clxCQueueInit(&lwipModule.interfaceQueue);

    lwipModule.scheduler = clxCreateScheduler();
    
    lwipModule.appRequestContext = clxCreateSchedulerMessageHandler(lwipModule.scheduler,
    		CLX_DEBUG_STR("LWIP Application Request"),
			lwipAppCommandHandler,
            sizeof(struct ClxSchedulerMessageHandler),
			LWIP_APP_REQUEST_HANDLING_CONTEXT_PRIORITY);

    lwipModule.threadHandle = clxBeginThread((ClxThreadFunction)threadProc,
                                        NULL,
                                        "LWIP Stack",
                                        LWIP_THREAD_STACK_SIZE,
                                        clarinoxWlanPlatformTaskPriorityTable,
                                        LWIP_THREAD_PRIORITY_LEVEL);

    if(lwipModule.threadHandle == NULL)
    {
        return CLX_FAIL;
    }
    
    clxCQueueInit(&lwipModule.timersQueue);
    
    clxNetworkBufferDescriptorChainInit(&lwipModule.freeBufferDescriptors);
    
    lwip_init();

#ifdef USE_IPERF
    lwipModule.tcpIperfServerHandle = lwiperf_start_tcp_server_default(lwiperf_report, clxConsoleUIEngineText);
#endif

    return CLX_SUCCESS;
}

void clxTcpIpModule_Deinit()
{
    clxTerminateScheduler(lwipModule.scheduler);
    
    clxDeleteThread(lwipModule.threadHandle, 0xFFFFFFFF);
    
    /* Delete all timers: */
    while(!clxCQueueIsEmpty(&lwipModule.timersQueue))
	{
		LwipTimer* timer = (LwipTimer*)clxCQueuePopFront(&lwipModule.timersQueue);

        clxStopSchedulerTimer(&timer->base);
        clxDeleteSchedulerTimer(&timer->base);
	}  

    clxDeleteSchedulerMessageHandler(lwipModule.appRequestContext);

    /* Now, we can delete the scheduler: */    
    clxDeleteScheduler(lwipModule.scheduler);
    
#if !defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
    clxDeleteMutex(lwipModule.mutex);
#endif

#ifdef USE_IPERF
    if (lwipModule.tcpIperfServerHandle)
    {
        lwiperf_abort(lwipModule.tcpIperfServerHandle);
    }
#endif      
      
	/* Free Network Buffer descriptors */
	while(1)
	{
		ClxNetworkBufferDescriptor* desc = clxNetworkBufferDescriptorChainPopFirst(&lwipModule.freeBufferDescriptors);
		
		if(!desc)
		{
			/* All descriptors are freed. */
			break;
		}
		else
		{
			clxNetworkInterfaceFreeBufferDescriptor(desc);
		}	
	}

    sys_deinit();
}



/***********************
lwip timers
************************/
static void lwipTimerCallback (struct ClxSchedulerTimer* timer)
{
    LwipTimer* timer_ = (LwipTimer*)timer;
    
    timer_->arg.handler();
    
    /* Restart the timer as all timers are cyclic: */
    clxStartSchedulerTimer(timer, timer_->arg.interval_ms);
}

void sys_timeouts_init(void)
{
    int i;

    for (i = 0; i < lwip_num_cyclic_timers; i++)
    {
        LwipTimer* timer = (LwipTimer*)clxCreateSchedulerTimer(lwipModule.scheduler,
#if LWIP_DEBUG_TIMERNAMES
                                                               lwip_cyclic_timers[i].handler_name,
#else
                                                               NULL,
#endif
                                                               lwipTimerCallback,
                                                               sizeof(LwipTimer),
                                                               NETIF_TIMER_PRIORITY);
        
        CLX_ASSERT(timer);
        clxMemCpy(&timer->arg, &lwip_cyclic_timers[i], sizeof(struct lwip_cyclic_timer));
        
        clxCQueuePushBack(&lwipModule.timersQueue, &timer->base.queueable);
        
        /* Start the timer: */
        clxStartSchedulerTimer(&timer->base, lwip_cyclic_timers[i].interval_ms);
    }
}

u32_t sys_now(void)
{
    return clxTickTime();
}


/***********************
other lwip stuff
************************/
static err_t sendNetFrame(struct netif *netif, struct pbuf *p)
{
    LwipNetworkInterface* lwipif = (LwipNetworkInterface*)(netif->state);
    
    if(lwipif->transportHandle == NULL)
    {
        return ERR_CONN;
    }
    
    boolean copyRequired = FALSE;

    u2 framelength = 0;

    ClxNetworkPacket packet;
    clxNetworkBufferDescriptorChainInit(&packet);
    
    for (struct pbuf* q = p; q != NULL; q = q->next) 
    {
        if (PBUF_NEEDS_COPY(q)) 
        {
            /* 
            This is an application buffer. We need to copy it to an internal buffer before passing
            to the network:
            */          
            copyRequired = TRUE;
            break;
        }
    }
    
    if (copyRequired)
    {
        /* We copy the entire packet into a new contiguous buffer: */ 
        struct pbuf* txbuf = pbuf_clone(PBUF_RAW_TX, PBUF_RAM, p);
        
        if (txbuf == NULL)
        {
            /* Not enough space to copy the TX packet: */
            LINK_STATS_INC(link.memerr);
            LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("sendNetFrame: could not queue a copy of PBUF_REF packet %p (out of memory)\n", (void *)p));      
            
#if defined(CLX_NET_IF_STATS)
            lwipif->totalTxBytesDiscarded_NoBuf += p->tot_len;
#endif
            return ERR_MEM;
        }
        
        /* We assume we have enough descriptors for buffers: */
        ClxNetworkBufferDescriptor* desc = getFreeDescriptor();

        desc->bufferAddr = (u1*)txbuf->payload;
        desc->data = desc->bufferAddr;
        desc->bufferSize = desc->dataLength = txbuf->tot_len;
        desc->userData = (void*)txbuf;     
          
        clxNetworkBufferDescriptorChainPushAll(&packet, desc);
                
        framelength = desc->dataLength;
    }
    else
    {
        for (struct pbuf* q = p; q != NULL; q = q->next) 
        {
          /* We assume we have enough descriptors for buffers: */
            ClxNetworkBufferDescriptor* desc = getFreeDescriptor();
            
            desc->fragmentType = CLX_NETWORK_PACKET_FRAGMENT_TYPE_CONTINUE;
            desc->bufferAddr = (u1*)q->payload;
            desc->data = desc->bufferAddr;
            desc->bufferSize = desc->dataLength = q->len;
            desc->userData = (void*)q;
            
            clxNetworkBufferDescriptorChainPushAll(&packet, desc);
                    
            framelength = framelength + q->len;
            pbuf_ref(q);
        } 
    }  
    
    if (packet.first == packet.current)
    {
        packet.first->fragmentType = CLX_NETWORK_PACKET_FRAGMENT_TYPE_COMPLETE;
    }
    else
    {
         packet.first->fragmentType = CLX_NETWORK_PACKET_FRAGMENT_TYPE_START;
         packet.current->fragmentType = CLX_NETWORK_PACKET_FRAGMENT_TYPE_END;  
    }
    
    packet.first->header.totalPacketLength = framelength;

#if defined(CLX_NET_IF_STATS)
	lwipif->totalTxBytesSent += packet.first->header.totalPacketLength;
    ++lwipif->totalTxPacketsSent;
#endif

    clxNetworkInterfaceQueueTxPacket(lwipif->transportHandle, &packet);

#if !defined(CLX_WLAN_PREFER_SPEED_OVER_LATENCY)
    clxNetworkInterfaceFlushPendingTxPackets(lwipif->transportHandle);
#endif
    
    return ERR_OK;
}

static err_t lwipInitNetIF(struct netif *netif)
{
#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = "clarinox";
#endif /* LWIP_NETIF_HOSTNAME */

    netif->name[0] = 'I';
    netif->name[1] = 'F';
    /* We directly use etharp_output() here to save a function call.
    * You can instead declare your own function an call etharp_output()
    * from it if you have to do some checks before sending (e.g. if link
    * is available...) */
    netif->output = etharp_output;
    netif->linkoutput = sendNetFrame;

    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    /* set MAC hardware address to 0.0.0.0 for now: */
    netif->hwaddr[0] =  0;
    netif->hwaddr[1] =  0;
    netif->hwaddr[2] =  0;
    netif->hwaddr[3] =  0;
    netif->hwaddr[4] =  0;
    netif->hwaddr[5] =  0;

    /* maximum transfer unit */
    netif->mtu = 1500;

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;  
    return ERR_OK;
}


/***********************
LwipNetworkInterface
************************/
#ifdef USE_DHCP_CLIENT
static void lwipNetworkAccessInterface_StartDHCP(LwipNetworkInterface* interface)
{
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;
 
    ipaddr.addr = 0;
    netmask.addr = 0;
    gw.addr = 0;
  
    netif_set_addr(&interface->netif_, &ipaddr , &netmask, &gw);
    
    dhcp_start(&interface->netif_);
}

static void lwipNetworkAccessInterface_StopDHCP(LwipNetworkInterface* interface)
{
    dhcp_stop(&interface->netif_);    
}
#endif

static void handleRxPacket(LwipNetworkInterface* lwipif, ClxNetworkBufferDescriptor* desc)
{
    struct pbuf* p = (struct pbuf*)desc->userData;

    switch(desc->fragmentType)
    {
    case CLX_NETWORK_PACKET_FRAGMENT_TYPE_COMPLETE:
        {
            CLX_DEBUG_ASSERT(desc->userData);
            CLX_DEBUG_ASSERT(p->next == NULL);

            p->len = p->tot_len = desc->header.totalPacketLength;

            err_t err = lwipif->netif_.input(p, &lwipif->netif_);

            if (err != ERR_OK)
            {
#if defined(CLX_NET_IF_STATS)
            	lwipif->totalRxBytesDiscarded_Error += desc->header.totalPacketLength;
#endif
                pbuf_free(p);
            }
#if defined(CLX_NET_IF_STATS)
            else
            {
            	lwipif->totalRxBytesHandled += desc->header.totalPacketLength;
                ++lwipif->totalRxPacketsHandled;
            }
#endif
            void* lockStatus = lock();
            clxNetworkBufferDescriptorChainPushSingle(&lwipModule.freeBufferDescriptors, desc);
            unlock(lockStatus);    
        }
        break;

    case CLX_NETWORK_PACKET_FRAGMENT_TYPE_NULL:
      {
          pbuf_free(p);

          void* lockStatus = lock();
          clxNetworkBufferDescriptorChainPushSingle(&lwipModule.freeBufferDescriptors, desc);
          unlock(lockStatus);    
      }
      break;

    default:
      BLACKBOX;
    }    
}


static void lwipNetworkAccessInterface_Init (_in_ struct ClxNetworkAccessInterface * thisObj)
{
    LwipNetworkInterface* lwipif = GET_INTERFACE(thisObj);

    clxCQueueInitItem(&lwipif->queueable);

    lwipif->transportHandle = NULL;
    
    lwipif->role = ClxNetworkDeviceRoleEnum_VendorSpecific;
    lwipif->linkUp = FALSE;
}

static ClxResult lwipNetworkAccessInterface_Start (_in_ struct ClxNetworkAccessInterface * thisObj,
                                                   _in_ struct ClxNetworkTransportHandle* transportHandle,
                                                   _in_ const ClxNetworkAddress* localPhysicalAddress,
                                                   _in_ ClxNetworkDeviceRole  localDeviceRole,
                                                   _in_ const ClxConfigList* configList)
{
    LwipNetworkInterface* lwipif = GET_INTERFACE(thisObj);

    clxNetworkAddressEncode(localPhysicalAddress, lwipif->localAddr);

    lwipif->transportHandle = transportHandle;
    	
    lwipif->role = localDeviceRole;
    
    /* We can create the tasks in the context of any thread. However, we can only delete them in the context they are used (which is the LWIP thread): */
	lwipif->rxHandlingTask = createLwipTask(lwipif, CLX_DEBUG_STR("LwipRxHandlingTask"), lwipRxHandlingTaskProc, LWIP_DATA_HANDLING_CONTEXT_PRIORITY);
	lwipif->indicationHandlingTask = createLwipTask(lwipif, CLX_DEBUG_STR("LwipIndicationHandlingTask"), lwipIndicationHandlingTaskProc, LWIP_INDICATION_HANDLING_CONTEXT_PRIORITY);

#if defined(CLX_NET_IF_STATS)
    lwipif->totalTxBytesSent = 0;
	lwipif->totalTxBytesCompleted = 0;
	lwipif->totalTxPacketsSent = 0; 
	lwipif->totalTxPacketsCompleted = 0;     
	lwipif->totalRxBytesReceived = 0;
	lwipif->totalRxBytesHandled = 0;
	lwipif->totalRxPacketsReceived = 0;
	lwipif->totalRxPacketsHandled = 0;    
	lwipif->totalTxBytesDiscarded_NoBuf = 0;
	lwipif->totalRxBytesDiscarded_NoBuf = 0;
	lwipif->totalRxBytesDiscarded_Error = 0;
	lwipif->numberOfTimesRxTaskScheduled = 0;
#endif

    /* The rest of the initialization will be done by the CLX_NETWORK_ACCESS_INTERFACE_INDICATION_STARTED indication: */
    return CLX_SUCCESS;
}

static void lwipNetworkAccessInterface_Stop(_in_ struct ClxNetworkAccessInterface * thisObj)
{
    LwipNetworkInterface* lwipif = GET_INTERFACE(thisObj);
       
    /* We should not return until CLX_NETWORK_ACCESS_INTERFACE_INDICATION_STOPPED indication has been handled: */
    void* lockStatus = lock();
    while (lwipif->transportHandle)
    {
    	unlock(lockStatus);
    	clxSleep(10);
    	lockStatus = lock();
    }
    unlock(lockStatus);

    /* The tasks must have been deleted: */
    CLX_ASSERT(lwipif->rxHandlingTask == NULL);
    CLX_ASSERT(lwipif->indicationHandlingTask == NULL);
}

static void* gLockStatus = NULL;

static void lwipNetworkAccessInterface_LockStatus (_in_ struct ClxNetworkAccessInterface * arg)
{
	gLockStatus = lock();
}

static void lwipNetworkAccessInterface_UnlockStatus (_in_ struct ClxNetworkAccessInterface * arg)
{
	unlock(gLockStatus);
}

static void lwipNetworkAccessInterface_LinkStatusUpdated (LwipNetworkInterface* lwipif,
                                                          ClxNetworkAccessInterfaceLinkStatus newStatus)
{
    switch(newStatus)
    {
    case ClxNetworkAccessInterfaceLinkStatus_Up:
    	{
			lwipif->linkUp = TRUE;
			netif_set_up(&lwipif->netif_);
    	}
#ifdef USE_DHCP_CLIENT
        if (lwipif->role == ClxNetworkDeviceRoleEnum_Client)
        {
            lwipNetworkAccessInterface_StartDHCP(lwipif);
        }
#endif
        break;

    case ClxNetworkAccessInterfaceLinkStatus_Down:
        lwipif->linkUp = FALSE;
#ifdef USE_DHCP_CLIENT
        if (lwipif->role == ClxNetworkDeviceRoleEnum_Client)
        {
            lwipNetworkAccessInterface_StopDHCP(lwipif);
        }
#endif        
        netif_set_down(&lwipif->netif_);
        break;
        
    default:
        CLX_DEBUG_ASSERT(0);
    }
}

static void lwipNetworkAccessInterface_HandleIndication (_in_ struct ClxNetworkAccessInterface * thisObj,
                                                         _in_ const ClxNetworkInterfaceIndication* indication)

{
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;

    LwipNetworkInterface* lwipif = GET_INTERFACE(thisObj);
    
    switch(indication->indicationID)
    {
    case CLX_NETWORK_ACCESS_INTERFACE_INDICATION_STARTED:
		{
			netif_add_noaddr(&lwipif->netif_, NULL, &lwipInitNetIF, &ethernet_input);

			lwipif->netif_.state = (void*)lwipif;

			lwipif->netif_.hwaddr_len = ETHARP_HWADDR_LEN;

			/* set MAC hardware address */
			lwipif->netif_.hwaddr[0] =  lwipif->localAddr[0];
			lwipif->netif_.hwaddr[1] =  lwipif->localAddr[1];
			lwipif->netif_.hwaddr[2] =  lwipif->localAddr[2];
			lwipif->netif_.hwaddr[3] =  lwipif->localAddr[3];
			lwipif->netif_.hwaddr[4] =  lwipif->localAddr[4];
			lwipif->netif_.hwaddr[5] =  lwipif->localAddr[5];

			clxCQueuePushBack(&lwipModule.interfaceQueue, &lwipif->queueable);

			switch (lwipif->role)
			{
			case ClxNetworkDeviceRoleEnum_Client:
			case ClxNetworkDeviceRoleEnum_VendorSpecific: /* Loopback interface */
				{
#ifndef USE_DHCP_CLIENT
					/* Static address used */
                    if (predefinedLwipConfig.clientStaticIpv4 != 0)
                    {
                        IP4_ADDR(&ipaddr, 
                            CLX_IP4_ADDRESS_A(predefinedLwipConfig.clientStaticIpv4),
                            CLX_IP4_ADDRESS_B(predefinedLwipConfig.clientStaticIpv4),
                            CLX_IP4_ADDRESS_C(predefinedLwipConfig.clientStaticIpv4),
                            CLX_IP4_ADDRESS_D(predefinedLwipConfig.clientStaticIpv4));
                    }
                    else
                    {
                        IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
                    }

                    if (predefinedLwipConfig.clientIpv4Netmask != 0)
                    {
                        IP4_ADDR(&netmask,
                            CLX_IP4_ADDRESS_A(predefinedLwipConfig.clientIpv4Netmask),
                            CLX_IP4_ADDRESS_B(predefinedLwipConfig.clientIpv4Netmask),
                            CLX_IP4_ADDRESS_C(predefinedLwipConfig.clientIpv4Netmask),
                            CLX_IP4_ADDRESS_D(predefinedLwipConfig.clientIpv4Netmask));
                    }
                    else
                    {
                        IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
                    }

                    if (predefinedLwipConfig.clientIpv4Gateway != 0)
                    {
                        IP4_ADDR(&gw,
                            CLX_IP4_ADDRESS_A(predefinedLwipConfig.clientIpv4Gateway),
                            CLX_IP4_ADDRESS_B(predefinedLwipConfig.clientIpv4Gateway),
                            CLX_IP4_ADDRESS_C(predefinedLwipConfig.clientIpv4Gateway),
                            CLX_IP4_ADDRESS_D(predefinedLwipConfig.clientIpv4Gateway));
                    }
                    else
                    {
                        IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
                    }

					netif_set_addr(&lwipif->netif_, &ipaddr , &netmask, &gw);
#endif
					netif_set_default(&lwipif->netif_);
				}
				break;

			case ClxNetworkDeviceRoleEnum_Router:
				{
                    /* Static address used */
                    if (predefinedLwipConfig.routerStaticIpv4 != 0)
                    {
                        IP4_ADDR(&ipaddr,
                            CLX_IP4_ADDRESS_A(predefinedLwipConfig.routerStaticIpv4),
                            CLX_IP4_ADDRESS_B(predefinedLwipConfig.routerStaticIpv4),
                            CLX_IP4_ADDRESS_C(predefinedLwipConfig.routerStaticIpv4),
                            CLX_IP4_ADDRESS_D(predefinedLwipConfig.routerStaticIpv4));
                    }
                    else
                    {
                        IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
                    }

                    if (predefinedLwipConfig.routerIpv4Netmask != 0)
                    {
                        IP4_ADDR(&netmask,
                            CLX_IP4_ADDRESS_A(predefinedLwipConfig.routerIpv4Netmask),
                            CLX_IP4_ADDRESS_B(predefinedLwipConfig.routerIpv4Netmask),
                            CLX_IP4_ADDRESS_C(predefinedLwipConfig.routerIpv4Netmask),
                            CLX_IP4_ADDRESS_D(predefinedLwipConfig.routerIpv4Netmask));
                    }
                    else
                    {
                        IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
                    }

                    if (predefinedLwipConfig.routerIpv4Gateway != 0)
                    {
                        IP4_ADDR(&gw,
                            CLX_IP4_ADDRESS_A(predefinedLwipConfig.routerIpv4Gateway),
                            CLX_IP4_ADDRESS_B(predefinedLwipConfig.routerIpv4Gateway),
                            CLX_IP4_ADDRESS_C(predefinedLwipConfig.routerIpv4Gateway),
                            CLX_IP4_ADDRESS_D(predefinedLwipConfig.routerIpv4Gateway));
                    }
                    else
                    {
                        IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
                    }

					netif_set_addr(&lwipif->netif_, &ipaddr , &netmask, &gw);

					netif_set_default(&lwipif->netif_);

#if defined(USE_DHCP_SERVER)
                    {
                        ClxDhcpv4ServerConfig cfg;
                        clxMemSet(&cfg, 0, sizeof(cfg));
                        cfg.localIP =       CLX_NTOHL(ipaddr.addr);
                        cfg.clientStartIP = CLX_NTOHL(ipaddr.addr) + 1;
                        cfg.gatewayIP =     CLX_NTOHL(gw.addr);
                        cfg.dnsIP1 =        CLX_NTOHL(gw.addr);
                        cfg.subnetMask =    CLX_NTOHL(netmask.addr);

                        if (clxDhcpv4ServerInit(&cfg, clxCreateLwipAsyncUdpSocket(), &lwipif->dhcpv4ServerHandle) != CLX_SUCCESS)
                        {
                            lwipif->dhcpv4ServerHandle = NULL;
                        }
                    }
#endif
				}
				break;

			default:
				assert(0);
			}
		}
    	break;

    case CLX_NETWORK_ACCESS_INTERFACE_INDICATION_STOPPED:
		{
			ClxNetworkPacket packet;

			/* Delete the tasks (this is safe since we are in the context of the LWIP thread): */
		    destroyLwipTask(lwipif->indicationHandlingTask);
		    destroyLwipTask(lwipif->rxHandlingTask);

		    lwipif->indicationHandlingTask = NULL;
		    lwipif->rxHandlingTask = NULL;

		    /* Simply discard any pending RX packet: */
		    while (clxNetworkInterfaceGetPendingRxPacket(lwipif->transportHandle, &packet))
		    {
		        packet.first->fragmentType = CLX_NETWORK_PACKET_FRAGMENT_TYPE_NULL;
		        handleRxPacket(lwipif, packet.first);
		    }

		    /*
		    TODO : Release pending TX buffers back to LWIP (This requires some work).
		    	   For now, throw a BLACKBOX so we know this is not currently implemented.
		    */
		   // BLACKBOX;

		    netif_remove(&lwipif->netif_);

#if defined(USE_DHCP_SERVER)
            if ((lwipif->role == ClxNetworkDeviceRoleEnum_Router) &&
                (lwipif->dhcpv4ServerHandle))
            {
                clxDhcpv4ServerDestroy(lwipif->dhcpv4ServerHandle);
            }
#endif

		    clxCQueueDetachItem(&lwipModule.interfaceQueue, &lwipif->queueable);

		    void* lockStatus = lock();
		    /* This makes the lwipNetworkAccessInterface_Stop() function wake up and return: */
		    lwipif->transportHandle = NULL;
		    unlock(lockStatus);
		}
    	break;

    case CLX_NETWORK_ACCESS_INTERFACE_INDICATION_NEW_LINK:    
    case CLX_NETWORK_ACCESS_INTERFACE_INDICATION_LINK_DISCONNECTED:
        break;

    case CLX_NETWORK_ACCESS_INTERFACE_INDICATION_LINK_STATUS_UPDATED:
        {
            ClxNetworkInterfaceIndication_LinkStatusUpdated* indication_ = (ClxNetworkInterfaceIndication_LinkStatusUpdated*)indication; 
                
            lwipNetworkAccessInterface_LinkStatusUpdated(lwipif, indication_->newStatus);
        }
        break;
      
    default: 
        break;
    }
}

static void lwipIndicationHandlingTaskProc (struct ClxSchedulerTask* task)
{
	LwipTask* 				     task_ = (LwipTask*)task;
    LwipNetworkInterface*        lwipif = task_->netif;

    void* lockStatus = lock();
    CLX_DEBUG_ASSERT(lwipif->indicationHandlingTask->state == LwipTaskState_Scheduled);

    while (clxNetworkInterfaceGetCurrentStatus(lwipif->transportHandle) & CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_MESSAGES)
    {
        unlock(lockStatus);
        clxNetworkInterfaceHandleIndication(lwipif->transportHandle, lwipNetworkAccessInterface_HandleIndication);
        lockStatus = lock();
        
        if (lwipif->transportHandle == NULL)
        {
            /* The interface has stopped: */
            unlock(lockStatus);
            return;
        }
    }

    lwipif->indicationHandlingTask->state = LwipTaskState_Idle;
    unlock(lockStatus);
}

static void lwipNetworkAccessInterface_IndicationPending (_in_ struct ClxNetworkAccessInterface * thisObj)
{
    LwipNetworkInterface* lwipif = GET_INTERFACE(thisObj); 
    boolean wakeupTask = FALSE;

    void* lockStatus = lock();
    if (lwipif->indicationHandlingTask->state == LwipTaskState_Idle)
    {
    	lwipif->indicationHandlingTask->state = LwipTaskState_Scheduled;
    	wakeupTask = TRUE;
    }
    unlock(lockStatus);
    
    if (wakeupTask)
    {
    	BLACKBOX_IF(clxWakeUpSchedulerTask(&lwipif->indicationHandlingTask->base) != CLX_SUCCESS);
    }
}

static void lwipNetworkAccessInterface_Destroy (_in_ struct ClxNetworkAccessInterface * thisObj)
{  
    destroyLwipNetworkAccessInterface(thisObj);
}

static void lwipNetworkAccessInterface_RxPacketsPending (_in_ struct ClxNetworkAccessInterface * thisObj)
{
    LwipNetworkInterface* lwipif = GET_INTERFACE(thisObj); 

    /*
    Since lwipRxHandlingTaskProc retrieves all pending RX packets in one go (using the clxNetworkInterfaceGetPendingRxPackets() API),
    there is no need for protection and state checking (as we do for the indication handling task).
    Remember that this function is called only if new RX packets are received while there is NO RX packets currently pending.
    So, when this function is called once, it won't be called again until clxNetworkInterfaceGetPendingRxPackets() is called in lwipRxHandlingTaskProc.
    */
    BLACKBOX_IF(clxWakeUpSchedulerTask(&lwipif->rxHandlingTask->base) != CLX_SUCCESS);

#if defined(CLX_NET_IF_STATS)
	++lwipif->numberOfTimesRxTaskScheduled;
#endif
}

static void lwipRxHandlingTaskProc (struct ClxSchedulerTask* task)
{
	LwipTask* 				     task_ = (LwipTask*)task;
    LwipNetworkInterface*        lwipif = task_->netif;
    ClxNetworkBufferDescriptor*  desc = NULL;

    /*
    When this function returns, the flag CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_RX_PACKETS has been reset,
    So, lwipNetworkAccessInterface_RxPacketsPending() may be called again:
    */
    desc = clxNetworkInterfaceGetPendingRxPackets(lwipif->transportHandle);
    
    while(desc)
    {
        ClxNetworkBufferDescriptor* next = desc->next;
        desc->next = NULL;

        handleRxPacket(lwipif, desc);
        
        desc = next;
    }
}

static ClxNetworkBufferDescriptor* lwipNetworkAccessInterface_GetFreeRxBuffer(_in_ struct ClxNetworkAccessInterface * thisObj, u2 length)
{ 
#if defined(CLX_NET_IF_STATS)  
    LwipNetworkInterface* lwipif = GET_INTERFACE(thisObj);
#endif
    
    struct pbuf* p = pbuf_alloc(PBUF_RAW, length, PBUF_POOL);
  
    if (p)
    {
        assert(p->next == NULL);
                        
        ClxNetworkBufferDescriptor* desc = getFreeDescriptor();
        
        desc->bufferAddr = (u1*)p->payload;
        desc->bufferSize = p->len;
        desc->userData = (void*)p;
        
#if defined(CLX_NET_IF_STATS)
        lwipif->totalRxBytesReceived += length;
        ++lwipif->totalRxPacketsReceived;
#endif

        return desc;
    }  

#if defined(CLX_NET_IF_STATS)
	lwipif->totalRxBytesDiscarded_NoBuf += length;
#endif

    return NULL;
}

static void lwipNetworkAccessInterface_TxBuffersComplete (_in_ struct ClxNetworkAccessInterface * thisObj)
{
    LwipNetworkInterface* lwipif = GET_INTERFACE(thisObj);
    
    ClxNetworkBufferDescriptor* current = clxNetworkInterfaceGetReleasedTxBuffers(lwipif->transportHandle);

    while (current)
    {
        ClxNetworkBufferDescriptor* next = current->next;
        current->next = NULL;
        struct pbuf* p = (struct pbuf*)current->userData;

#if defined(CLX_NET_IF_STATS)
        lwipif->totalTxBytesCompleted += current->dataLength;
        
        if ((current->fragmentType == CLX_NETWORK_PACKET_FRAGMENT_TYPE_START) ||
            (current->fragmentType == CLX_NETWORK_PACKET_FRAGMENT_TYPE_COMPLETE))
        {
            ++lwipif->totalTxPacketsCompleted;
        }
#endif

        pbuf_free(p);

        void* lockStatus = lock();
        clxNetworkBufferDescriptorChainPushAll(&lwipModule.freeBufferDescriptors, current);
        unlock(lockStatus);
        
        current = next;
    }
}

static void lwipAppCommand_Ifconfig (ClxStdOutput stdoutput)
{
	ClxCQueueIterator lwifIter;
	const s1* addr = NULL;
	u4 index = 0;

	clxCQueueFront(&lwipModule.interfaceQueue, &lwifIter);

	while (clxCQueueIteratorIsValid(&lwifIter))
	{
		LwipNetworkInterface* lwipif = (LwipNetworkInterface*)lwifIter.current;

        stdoutput("\nInterface %u (Type=%u) LINK %s\n", index, (u4)lwipif->role, lwipif->linkUp ? "UP" : "DOWN");

        stdoutput("    MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
	    		lwipif->localAddr[0],
				lwipif->localAddr[1],
				lwipif->localAddr[2],
				lwipif->localAddr[3],
				lwipif->localAddr[4],
				lwipif->localAddr[5]);

		addr = ip4addr_ntoa(&lwipif->netif_.ip_addr);
        stdoutput("    Ipv4 Address: %s\n", addr);

		addr = ip4addr_ntoa(&lwipif->netif_.netmask);
        stdoutput("    Subnet Mask: %s\n", addr);

		addr = ip4addr_ntoa(&lwipif->netif_.gw);
        stdoutput("    Default Gateway: %s\n", addr);

#if defined(CLX_NET_IF_STATS)
        stdoutput("    Statistics:\n");
        stdoutput("        TxBytesSent: " STAT_VALUE_FORMAT " Bytes (" STAT_VALUE_FORMAT " Packets)\n",         lwipif->totalTxBytesSent, lwipif->totalTxPacketsSent);
        stdoutput("        TxBytesCompleted: " STAT_VALUE_FORMAT " Bytes (" STAT_VALUE_FORMAT " Packets)\n", 	lwipif->totalTxBytesCompleted, lwipif->totalTxPacketsCompleted);      
        stdoutput("        TxBytesDiscarded (NoMem): " STAT_VALUE_FORMAT " Bytes\n", 	                        lwipif->totalTxBytesDiscarded_NoBuf);
        stdoutput("        RxBytesReceived: " STAT_VALUE_FORMAT " Bytes (" STAT_VALUE_FORMAT " Packets)\n",     lwipif->totalRxBytesReceived, lwipif->totalRxPacketsReceived);
        stdoutput("        RxBytesHandled: " STAT_VALUE_FORMAT " Bytes (" STAT_VALUE_FORMAT " Packets)\n", 	    lwipif->totalRxBytesHandled, lwipif->totalRxPacketsHandled);
        stdoutput("        RxBytesDiscarded (NoMem): " STAT_VALUE_FORMAT " Bytes\n", 	                        lwipif->totalRxBytesDiscarded_NoBuf);
        stdoutput("        RxBytesDiscarded (Errors): " STAT_VALUE_FORMAT " Bytes\n",                           lwipif->totalRxBytesDiscarded_Error);
        stdoutput("        TimesRxTaskScheduled: " STAT_VALUE_FORMAT " Times\n", 		                        lwipif->numberOfTimesRxTaskScheduled);
#endif // #if defined(CLX_NET_IF_STATS)

		clxCQueueIteratorNext(&lwifIter);
	}
}

#if defined(USE_IPERF)
static void lwipAppCommand_Iperf (struct ClxCommandLineArguments* args, ClxStdOutput stdoutput)
{
	const s1* arg = clxCommandLineArguments_parseNext(args);

	if (strcmp(arg, "-c") == 0)
	{
		ip4_addr_t serverAddr;

		/* Next argument must be the host address: */
		const s1* serverAddrStr = clxCommandLineArguments_parseNext(args);

		if ((serverAddrStr == NULL) ||
			(serverAddrStr[0] == '-'))
		{
            stdoutput("\n[IPerf] The argument -c must be followed by the server IP address\n");
			return;
		}

		if (!ip4addr_aton(serverAddrStr, &serverAddr))
		{
            stdoutput("\n[IPerf] Invalid Ipv4 address (%s)\n", serverAddrStr);
			return;
		}

		lwiperf_start_tcp_client_default(&serverAddr, lwiperf_report, stdoutput);

        stdoutput("\n[IPerf] TCP Client session to %s\n", serverAddrStr);
	}
	else if (strcmp(arg, "-s") == 0)
	{
		lwiperf_start_tcp_server_default(lwiperf_report, stdoutput);

        stdoutput("\n[IPerf] TCP Server session listening\n");
	}
}
#endif


static ClxNetworkPingHandle pingHandle = NULL;

static void lwipAppCommand_StartPing(struct ClxCommandLineArguments* args, ClxStdOutput stdoutput)
{
    ip4_addr_t  localAddr;
    ip4_addr_t  remoteAddr;
    u1          interval = 0;
    u2          payloadSize = 0;
    boolean     invalidArgs = FALSE;

    if (pingHandle)
    {
        stdoutput("\n[ping] Another session is ongoing\n");
        return;
    }

    localAddr.addr = 0;

    do
    {
        const s1* arg = clxCommandLineArguments_parseNext(args);

        if ((arg == NULL) || (ip4addr_aton(arg, &remoteAddr) == 0))
        {
            invalidArgs = TRUE;
            break;
        }

        while ((invalidArgs == FALSE) && ((arg = clxCommandLineArguments_parseNext(args)) != NULL))
        {
            if (strcmp(arg, "-w") == 0)
            {
                arg = clxCommandLineArguments_parseNext(args);

                if (arg)
                {
                    interval = (u1)clxAsciiToInteger(arg);
                }
                else
                {
                    invalidArgs = TRUE;
                    break;
                }
            }
            else if (strcmp(arg, "-l") == 0)
            {
                arg = clxCommandLineArguments_parseNext(args);

                if (arg)
                {
                    payloadSize = (u2)clxAsciiToInteger(arg);
                }
                else
                {
                    invalidArgs = TRUE;
                    break;
                }
            }
            else if (strcmp(arg, "-s") == 0)
            {
                arg = clxCommandLineArguments_parseNext(args);

                if ((arg == NULL) || (ip4addr_aton(arg, &localAddr) == 0))
                {
                    invalidArgs = TRUE;
                    break;
                }
            }
        }

        if (invalidArgs == FALSE)
        {
            ClxResult ret = clxNetworkPingStart(clxLwipCreateLwipAsyncEchoRequestSocket(),
                ntohl(localAddr.addr),
                ntohl(remoteAddr.addr),
                payloadSize,
                interval,
                stdoutput,
                &pingHandle);

            if ((ret != CLX_SUCCESS) && (ret != CLX_ERROR_COMPLETION_PENDING))
            {
                stdoutput("\n[ping] clxNetworkPingStart() failed with error %d\n", ret);
                pingHandle = NULL;
            }

            return;
        }
    } 
    while (0);

    stdoutput("\nping remote_ip [-w interval (in 10ms units)] [-l payload_length (bytes)] [-s local_address]\n");
}

static void lwipAppCommand_StopPing(ClxStdOutput stdoutput)
{
    if (pingHandle == NULL)
    {
        stdoutput("\n[ping] No session is running\n");
        return;
    }

    ClxResult ret = clxNetworkPingStop(pingHandle);

    if ((ret != CLX_SUCCESS) && (ret != CLX_ERROR_COMPLETION_PENDING))
    {
        stdoutput("\n[ping] clxNetworkPingStop() failed with error %d\n", ret);

    }

    pingHandle = NULL;
}

static void lwipAppCommandHandler (struct ClxSchedulerMessageHandler* context,
								   struct ClxSchedulerMessage* message,
								   enum ClxSchedulerMessageHandlerAction action)
{
	LwipAppCommand* command = (LwipAppCommand*)message;
	struct ClxCommandLineArguments args = { command->args };

	const s1* arg = clxCommandLineArguments_parseNext(&args);

#if defined(USE_IPERF)
	if (strcmp(arg, "iperf") == 0)
	{
		lwipAppCommand_Iperf(&args, clxConsoleUIEngineText);
		return;
	}
#endif
	if (strcmp(arg, "ifconfig") == 0)
	{
		lwipAppCommand_Ifconfig(clxConsoleUIEngineText);
		return;
	}
    if (strcmp(arg, "ping") == 0)
    {
        lwipAppCommand_StartPing(&args, clxConsoleUIEngineText);
        return;
    }
    if (strcmp(arg, "stop") == 0)
    {
        lwipAppCommand_StopPing(clxConsoleUIEngineText);
        return;
    }

	clxConsoleUIEngineText("\n[LWIP] Unknown command : \"%s\"\n", arg);
}

const struct ClxNetworkAccessInterface * createNetworkAccessInterface(void)
{
    LwipNetworkInterface* interface = (LwipNetworkInterface*)clxAppPoolsetAlloc(0, __LINE__, sizeof(LwipNetworkInterface));
    assert(interface);

    interface->base.userData = (void*)interface;
    
    interface->base.init = lwipNetworkAccessInterface_Init;
    interface->base.lockStatus = lwipNetworkAccessInterface_LockStatus;
    interface->base.unlockStatus = lwipNetworkAccessInterface_UnlockStatus;
    interface->base.start = lwipNetworkAccessInterface_Start;
    interface->base.stop = lwipNetworkAccessInterface_Stop;
    interface->base.indicationPending = lwipNetworkAccessInterface_IndicationPending;
    interface->base.destroy = lwipNetworkAccessInterface_Destroy;
    interface->base.rxPacketsPending = lwipNetworkAccessInterface_RxPacketsPending;
    interface->base.getFreeRxBuffer = lwipNetworkAccessInterface_GetFreeRxBuffer;
    interface->base.txBuffersComplete = lwipNetworkAccessInterface_TxBuffersComplete;
    
    return &interface->base;
}

void destroyLwipNetworkAccessInterface(struct ClxNetworkAccessInterface * interface)
{
    LwipNetworkInterface* lwipif = GET_INTERFACE(interface);
        
    clxPoolsetFree((void*)lwipif);
}

void issueLwipCommand(const s1* command)
{
	LwipAppCommand* msg = NULL;

	if (clxStrLen(command) > LWIP_MAX_APP_REQUEST_LENGTH)
	{
		clxConsoleUIEngineText("\nThe LWIP is too long !\n");
		return;
	}

	msg = (LwipAppCommand*)clxCreateSchedulerMessage(sizeof(LwipAppCommand));

	clxStrCpy(msg->args, command);

	clxQueueSchedulerMessage(lwipModule.appRequestContext, &msg->base);
}

/***********************
ClxNullNetworkInterface
************************/
struct ClxNullNetworkInterface
{
    struct ClxNetworkAccessInterface    base;
};

void nullNetInit (_in_ struct ClxNetworkAccessInterface * thisObj)
{
	(void)thisObj;
}

void nullNetLockStatus (_in_ struct ClxNetworkAccessInterface * thisObj)
{
	(void)thisObj;
}

void nullNetUnlockStatus (_in_ struct ClxNetworkAccessInterface * thisObj)
{
	(void)thisObj;
}

ClxResult nullNetUnlockStatusStart (_in_ struct ClxNetworkAccessInterface * thisObj,
									_in_ struct ClxNetworkTransportHandle* transportHandle,
									_in_ const ClxNetworkAddress* localPhysicalAddress,
									_in_ ClxNetworkDeviceRole  localDeviceRole,
									_in_ const ClxConfigList* configList)
{
	(void)thisObj;
	(void)transportHandle;
	(void)localPhysicalAddress;
	(void)localDeviceRole;
	(void)configList;

	return CLX_SUCCESS;
}

void nullNetUnlockStatusStop(_in_ struct ClxNetworkAccessInterface * thisObj)
{
	(void)thisObj;
}

void nullNetIndicationPending (_in_ struct ClxNetworkAccessInterface * thisObj)
{
	(void)thisObj;
}


void nullNetDestroy (_in_ struct ClxNetworkAccessInterface * thisObj)
{
    struct ClxNullNetworkInterface* interface_ = ((struct ClxNullNetworkInterface*)(thisObj->userData));

    clxPoolsetFree((void*)interface_);
}

void nullNetrRxPacketsPending (_in_ struct ClxNetworkAccessInterface * thisObj)
{
	(void)thisObj;
}

ClxNetworkBufferDescriptor* nullNetGetFreeRxBuffer(_in_ struct ClxNetworkAccessInterface * arg1, u2 arg2)
{
	(void)arg1;
	(void)arg2;
    return NULL;
}

void nullNetTxBuffersComplete (_in_ struct ClxNetworkAccessInterface * thisObj)
{
	(void)thisObj;
}

struct ClxNetworkAccessInterface* clxCreateNullNetworkAccessInterface(void)
{
    struct ClxNullNetworkInterface* interface = (struct ClxNullNetworkInterface*)clxAppPoolsetAlloc(0, __LINE__, sizeof(struct ClxNullNetworkInterface));
    CLX_ASSERT(interface);

    interface->base.userData = (void*)interface;

    interface->base.init = nullNetInit;
    interface->base.lockStatus = nullNetLockStatus;
    interface->base.unlockStatus = nullNetUnlockStatus;
    interface->base.start = nullNetUnlockStatusStart;
    interface->base.stop = nullNetUnlockStatusStop;
    interface->base.indicationPending = nullNetIndicationPending;
    interface->base.destroy = nullNetDestroy;
    interface->base.rxPacketsPending = nullNetrRxPacketsPending;
    interface->base.getFreeRxBuffer = nullNetGetFreeRxBuffer;
    interface->base.txBuffersComplete = nullNetTxBuffersComplete;

    return &interface->base;
}

ClxResult (*clxInitTcpIpStack) ()   = clxTcpIpModule_Init;
void      (*clxDeinitTcpIpStack) () = clxTcpIpModule_Deinit;

