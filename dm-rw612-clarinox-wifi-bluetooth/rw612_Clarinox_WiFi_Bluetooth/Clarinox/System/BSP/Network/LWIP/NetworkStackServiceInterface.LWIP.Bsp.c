/******************************************************************************
*
* Project             Wlan Sample Application
* File                NetworkStackServiceInterface.LWIP.Bsp.c
* Description         Implementation of Network Stack Service Interface for LWIP stack
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


#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/dns.h"
#include "lwip/raw.h"
#include "lwip/tcpip.h"
#include "errno.h"
#include <string.h>
#include <stdio.h>   
                               
                               
#define ASYNC_SOCKET_TASK_PRIORITY                                          1

#define IPV4_HEADER_LENGTH                                                  20 /* bytes */
#define IP_PROTOCOL_ICMP                                                    1

#if !defined(CLX_ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_IN_BITS)
#   error "Define CLX_ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_IN_BITS in ClxBspConfig.h"                                 
#endif

#define ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_MASK                            ((1 << CLX_ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_IN_BITS) - 1)


struct AsyncSocketStruct;

#if (NO_SYS)
extern ClxScheduler clxGetLwipScheduler();
#endif


#if LWIP_IPV4
#   define GET_IP_ADDR_PORT(addrContainer, ipv4addr, udpTcpPort)                                        \
        CLX_ASSERT(addrContainer->type == ClxNetworkServiceAddressType_IP4);                            \
        (ipv4addr).addr = htonl(addrContainer->u.ip4.addr);                                             \
        udpTcpPort = addrContainer->u.ip4.port

#   define SET_IP_ADDR_PORT(addrContainer, ipv4addr, udpTcpPort)                                        \
        addrContainer->type = ClxNetworkServiceAddressType_IP4;                                         \
        addrContainer->u.ip4.addr = ntohl((ipv4addr).addr);                                             \
        addrContainer->u.ip4.port = udpTcpPort
#else
#   error "Implement for IPv6"
#endif



/****************************
AsyncSocketDatagram
****************************/
typedef struct AsyncSocketDatagramStruct
{
    struct pbuf*   pbuf;
                  
    u2             currentIndex;   /* current index of the buffer in the pbuf object */
    u2             port;           /* Destination TCP/UDP of the packet */
    ip_addr_t      ipaddr;         /* Destination IP address of packet */
} AsyncSocketDatagram;


static void AsyncSocketDatagram_init(AsyncSocketDatagram* this_, struct pbuf* pbuf, u2 initialIndex, const ip_addr_t* ipaddr, u2 port)
{
    FAST_PATH_ASSERT(this_->pbuf == NULL);

    this_->pbuf = pbuf;
    this_->currentIndex = initialIndex;

#if LWIP_IPV4
    this_->ipaddr = *ipaddr;
#else
#   error "Implement for IPv6"
#endif

    this_->port = port;
}

static void AsyncSocketDatagram_destroy(AsyncSocketDatagram* this_)
{
    if (this_->pbuf)
    {
        pbuf_free(this_->pbuf);
        this_->pbuf = NULL;
    }
}

static ClxResult AsyncSocketDatagramQueue_decode(AsyncSocketDatagram* this_, ClxNetworkBufferDescriptor* desc, ClxNetworkServiceAddress* remoteAddr)
{
    ClxResult ret = CLX_ERROR_INTERNAL_ERROR;

    FAST_PATH_ASSERT(desc);
    FAST_PATH_ASSERT(remoteAddr);
    FAST_PATH_ASSERT(this_->pbuf);

    while (1)
    {
        struct pbuf* next = this_->pbuf->next;

        FAST_PATH_ASSERT(this_->currentIndex < this_->pbuf->len);

        u2 lenToCopy = MIN((desc->bufferSize - desc->dataLength), (this_->pbuf->len - this_->currentIndex));

        clxMemCpy(desc->data + desc->dataLength,
            (u1*)this_->pbuf->payload + this_->currentIndex,
            lenToCopy);

        desc->dataLength +=    lenToCopy;
        this_->currentIndex += lenToCopy;

        /* Either one or both of the following if conditions will be hit: */

        if (this_->currentIndex == this_->pbuf->len)
        {
            /* We are done with this buffer: */
            this_->currentIndex = 0;

            this_->pbuf->next = NULL;
            pbuf_free(this_->pbuf);
            this_->pbuf = next;

            if (this_->pbuf == NULL)
            {
                /* We are also done with this packet: */
                ret = CLX_SUCCESS;
                break;
            }
        }

        if (desc->dataLength == desc->bufferSize)
        {
            /* Service buffer is full: */
            ret = CLX_SYSTEM_ENOMEM;
            break;
        }
    }

    desc->fragmentType =             CLX_NETWORK_PACKET_FRAGMENT_TYPE_COMPLETE;
    desc->header.totalPacketLength = desc->dataLength;

    SET_IP_ADDR_PORT(remoteAddr, this_->ipaddr, this_->port);
    return ret;
}


/****************************
AsyncSocketDatagramQueue
****************************/
typedef struct AsyncSocketDatagramQueueStruct
{
    AsyncSocketDatagram  packets[ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_MASK + 1];
                         
    u4                   beginIndex;
    u4                   endIndex;
} AsyncSocketDatagramQueue;


static void AsyncSocketDatagramQueue_init(AsyncSocketDatagramQueue* this_)
{
    for (u4 i = 0; i < CLX_NUM_OF_ELEMENTS_IN_ARRAY(this_->packets); i++)
    {
        clxMemSet(&this_->packets[i], 0, sizeof(AsyncSocketDatagram));
    }

    this_->beginIndex = 0;
    this_->endIndex =   0;
}

static void AsyncSocketDatagramQueue_destroy(AsyncSocketDatagramQueue* this_)
{
    for (u4 i = 0; i < CLX_NUM_OF_ELEMENTS_IN_ARRAY(this_->packets); i++)
    {
        AsyncSocketDatagram_destroy(&this_->packets[i]);
    }
}

CLX_INLINE boolean AsyncSocketDatagramQueue_isEmpty(AsyncSocketDatagramQueue* this_)
{
    return ((this_->beginIndex != this_->endIndex) || 
            (this_->packets[this_->beginIndex].pbuf)) ? FALSE : TRUE;
}

static void AsyncSocketDatagramQueue_push(AsyncSocketDatagramQueue* this_, struct pbuf* pbuf, u2 initialIndex, const ip_addr_t* ipaddr, u2 port)
{
    FAST_PATH_ASSERT (pbuf);

    AsyncSocketDatagram* packet = &this_->packets[this_->endIndex];

    if ((this_->beginIndex == this_->endIndex) && (packet->pbuf))
    {

        /* Queue is full: */
        clxDebugError("AsyncSocketDatagramQueue_push: Discarding a datagram of size %u bytes since the queue is full", packet->pbuf->tot_len);
        AsyncSocketDatagram_destroy(packet);

        this_->beginIndex = (this_->beginIndex + 1) & ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_MASK;
        this_->endIndex = this_->beginIndex;
    }
    else
    {
        this_->endIndex = (this_->endIndex + 1) & ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_MASK;
    }

    AsyncSocketDatagram_init(packet, pbuf, initialIndex, ipaddr, port);
}

CLX_INLINE void AsyncSocketDatagramQueue_discard(AsyncSocketDatagramQueue* this_)
{
    AsyncSocketDatagram* packet = &this_->packets[this_->beginIndex];

    if (packet->pbuf)
    {
        AsyncSocketDatagram_destroy(packet);

        this_->beginIndex = (this_->beginIndex + 1) & ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_MASK;
    }
}

static ClxResult AsyncSocketDatagramQueue_pop(AsyncSocketDatagramQueue* this_, ClxNetworkBufferDescriptor* desc, ClxNetworkServiceAddress* remoteAddr)
{
    AsyncSocketDatagram* packet = &this_->packets[this_->beginIndex];
    ClxResult ret;

    if (packet->pbuf == NULL)
    {
        return CLX_SYSTEM_ENOENT;
    }

    ret = AsyncSocketDatagramQueue_decode(packet, desc, remoteAddr);

    if (ret == CLX_SUCCESS)
    {
        /* The packet is completely decoded into the service output: */
        this_->beginIndex = (this_->beginIndex + 1) & ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_MASK;
    }

    return ret;
}


/*************************
AsyncSocketTaskStruct
**************************/
typedef struct AsyncSocketTaskStruct
{
    struct ClxSchedulerTask     			base;   /* Must be the very first member */

    struct AsyncSocketStruct*               socket;
} AsyncSocketTask;


/*************************
AsyncSocketTimer
**************************/
typedef struct AsyncSocketTimerStruct
{
    struct ClxSchedulerTimer                base;   /* Must be the very first member */

    struct AsyncSocketStruct*               socket;
} AsyncSocketTimer;


/****************************
AsyncSocket
****************************/
typedef struct AsyncSocketStruct
{
    struct ClxAsyncNetworkSocketStruct  base;   /* This MUST be the very first member in the structure */

    struct ClxNetworkService*           service;
    const void*                         type;

    ClxNetworkBufferDescriptor*         pendingServiceRxDescriptor;

#if (NO_SYS)
    ClxScheduler                        scheduler;
    AsyncSocketTask*                    task;
    AsyncSocketTimer*                   rxTimer;
#endif
} AsyncSocket;

                      
static const void* AsyncSocket_type(_in_ ClxAsyncNetworkSocket this_)
{
    AsyncSocket* socket = (AsyncSocket*)this_;

    return socket->type;
}

static void AsyncSocket_scheduleTask (_in_ ClxAsyncNetworkSocket this_)
{
    AsyncSocket* socket = (AsyncSocket*)this_;

#if (NO_SYS)	//todo: check it!
    BLACKBOX_IF(clxWakeUpSchedulerTask(&socket->task->base) != CLX_SUCCESS);
#else
    tcpip_callback_with_block(socket->service->runSocketTask, socket->service, 1);
#endif
}

static void AsyncSocket_destroy(_in_ ClxAsyncNetworkSocket this_)
{
    AsyncSocket* socket = (AsyncSocket*)this_;

#if (NO_SYS)
    if (socket->task)
    {
        clxDeleteSchedulerTask(&socket->task->base);
        clxDeleteSchedulerTimer(&socket->rxTimer->base);
    }
#endif

    clxPoolsetFree(socket);
}

static void AsyncSocket_taskProc(struct ClxSchedulerTask* task)
{
    AsyncSocketTask* socketTask = (AsyncSocketTask*)task;

    socketTask->socket->service->runSocketTask(socketTask->socket->service, 
        &socketTask->socket->base);
}

static void AsyncSocket_rxTimerExpired (struct ClxSchedulerTimer* timer)
{
    AsyncSocketTimer* socketTimer = (AsyncSocketTimer*)timer;
    AsyncSocket* socket =           (AsyncSocket*)socketTimer->socket;

    ClxNetworkBufferDescriptor* desc = socket->pendingServiceRxDescriptor;
    BLACKBOX_IF(desc == NULL);

    socket->pendingServiceRxDescriptor = NULL;

    socketTimer->socket->service->socketRecvComplete(socketTimer->socket->service,
        &socketTimer->socket->base,
        desc,
        NULL,
        CLX_ERROR_TIMEOUT_OCCURRED);
}

static ClxResult AsyncSocket_new(AsyncSocket* this_, 
                                 u1 taskPriority,
                                 const void* type)
{ 
    this_->service = NULL;
    this_->type =    type;
    
    this_->pendingServiceRxDescriptor = NULL;

#if (NO_SYS)
    this_->scheduler = clxGetLwipScheduler();
    CLX_ASSERT(this_->scheduler);

    this_->task = (AsyncSocketTask*)clxCreateSchedulerTask(this_->scheduler,
        CLX_DEBUG_STR("LwipAsyncSocketTask"),
        AsyncSocket_taskProc,
        sizeof(AsyncSocketTask),
        taskPriority);

    this_->rxTimer = (AsyncSocketTimer*)clxCreateSchedulerTimer(this_->scheduler,
        CLX_DEBUG_STR("LwipAsyncSocketRxTimer"),
        AsyncSocket_rxTimerExpired,
        sizeof(AsyncSocketTimer),
        taskPriority);

    CLX_ASSERT(this_->task);
    CLX_ASSERT(this_->rxTimer);

    this_->task->socket =    this_;
    this_->rxTimer->socket = this_;
#endif

    this_->base.type =         AsyncSocket_type;
    this_->base.scheduleTask = AsyncSocket_scheduleTask;

    return CLX_SUCCESS;
}
    


/****************************
AsyncDatagramSocket
****************************/
typedef struct AsyncDatagramSocketStruct
{
    AsyncSocket                 base;


    void*                       pcb;
    pbuf_layer                  layer;

    u1                          protocol;       /* IP protocol (e.g. ICMP, UDP, ...). Applicable to Raw IP socket only */

    AsyncSocketDatagramQueue    rxQueue;

    void*                       (*new_pcb)      (u1 protocol);
    err_t                       (*bind)         (void* pcb, const ip_addr_t* ipaddr, u16_t port);
    err_t                       (*connect)      (void* pcb, const ip_addr_t* ipaddr, u16_t port);
    err_t                       (*send)         (void* pcb, struct pbuf* p);
    err_t                       (*sendto)       (void* pcb, struct pbuf* p, const ip_addr_t* dst_ip, u16_t dst_port);
    void                        (*recv)         (void* pcb, struct AsyncDatagramSocketStruct* socket);
    void                        (*remove_pcb)   (void* pcb);
} AsyncDatagramSocket;


#if LWIP_RAW

CLX_INLINE u1 recv_raw_callback(void* arg, struct raw_pcb* pcb, struct pbuf* p, const ip_addr_t* addr);

CLX_INLINE void* new_pcb_raw(u1 protocol)
{
    return (void*)raw_new(protocol);
}

CLX_INLINE err_t bind_raw(void* pcb, const ip_addr_t* ipaddr, u16_t port)
{
    return raw_bind((struct raw_pcb*)pcb, ipaddr);
}

CLX_INLINE err_t connect_raw(void* pcb, const ip_addr_t* ipaddr, u16_t port)
{
    return raw_connect((struct raw_pcb*)pcb, ipaddr);
}

CLX_INLINE err_t send_raw(void* pcb, struct pbuf* p)
{
    return raw_send((struct raw_pcb*)pcb, p);
}

CLX_INLINE err_t sendto_raw(void* pcb, struct pbuf* p, const ip_addr_t* dst_ip, u16_t dst_port)
{
    return raw_sendto((struct raw_pcb*)pcb, p, dst_ip);
}

CLX_INLINE void recv_raw(void* pcb, struct AsyncDatagramSocketStruct* socket)
{
    raw_recv((struct raw_pcb*)pcb, recv_raw_callback, socket);
}

CLX_INLINE void remove_pcb_raw(void* pcb)
{
    raw_remove((struct raw_pcb*)pcb);
}

#endif /* #if LWIP_RAW */

#if LWIP_UDP

CLX_INLINE void recv_udp_callback(void* arg, struct udp_pcb* pcb_lwip, struct pbuf* p, const ip_addr_t* addr, u2 port);

CLX_INLINE void* new_pcb_udp(u1 protocol)
{
    (void)protocol;
    return (void*)udp_new();
}

CLX_INLINE err_t bind_udp(void* pcb, const ip_addr_t* ipaddr, u16_t port)
{
    return udp_bind((struct udp_pcb*)pcb, ipaddr, port);
}

CLX_INLINE err_t connect_udp(void* pcb, const ip_addr_t* ipaddr, u16_t port)
{
    return udp_connect((struct udp_pcb*)pcb, ipaddr, port);
}

CLX_INLINE err_t send_udp(void* pcb, struct pbuf* p)
{
    return udp_send((struct udp_pcb*)pcb, p);
}

CLX_INLINE err_t sendto_udp(void* pcb, struct pbuf* p, const ip_addr_t* dst_ip, u16_t dst_port)
{
    return udp_sendto((struct udp_pcb*)pcb, p, dst_ip, dst_port);
}

CLX_INLINE void recv_udp(void* pcb, struct AsyncDatagramSocketStruct* socket)
{
    udp_recv((struct udp_pcb*)pcb, recv_udp_callback, socket);
}

CLX_INLINE void remove_pcb_udp(void* pcb)
{
    udp_remove((struct udp_pcb*)pcb);
}

#endif /* #if LWIP_UDP */


static ClxResult CLX_ASYNC AsyncDatagramSocket_init(_in_ ClxAsyncNetworkSocket this_,
                                                    _in_ struct ClxNetworkService* service,
                                                    _in_ const ClxNetworkServiceAddress* localAddress,
                                                    _in_ const ClxNetworkServiceAddress* remoteAddr,
                                                    _inout_ ClxConfigList* options)
{
    AsyncDatagramSocket* socket = (AsyncDatagramSocket*)this_;

    ip_addr_t  ipaddr;
    u2         port = 0;

    if ((service == NULL) && (localAddress == NULL))
    {
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
    }

    socket->pcb = socket->new_pcb(socket->protocol);

    if (socket->pcb == NULL)
    {
        return CLX_SYSTEM_ENOMEM;
    }

    GET_IP_ADDR_PORT(localAddress, ipaddr, port);

    err_t err = socket->bind(socket->pcb, &ipaddr, port);
    switch (err)
    {
    case ERR_OK:
        break;
    case ERR_USE:
        return CLX_SYSTEM_EADDRINUSE;
    default:
        clxDebugError("AsyncUdpSocket: udp_bind() failed with lwip error %d", (s4)err);
        return CLX_FAIL;
    }

    if (remoteAddr)
    {
        GET_IP_ADDR_PORT(remoteAddr, ipaddr, port);

        err = socket->connect(socket->pcb, &ipaddr, port);
        if (err != ERR_OK)
        {
            clxDebugError("AsyncUdpSocket: udp_connect() failed with lwip error %d", (s4)err);
            return CLX_FAIL;
        }
    }

    socket->base.service = service;

    socket->recv(socket->pcb, socket);

    return CLX_SUCCESS;
}

static ClxResult CLX_ASYNC AsyncDatagramSocket_send(_in_ ClxAsyncNetworkSocket this_,
                                                    _user_in_ ClxNetworkBufferDescriptor* desc,
                                                    _in_ const ClxNetworkServiceAddress* remoteAddr,
                                                    _in_ u4 timeout)
{
    AsyncDatagramSocket* socket = (AsyncDatagramSocket*)this_;

    err_t         err = ERR_OK;
    struct pbuf*  pbuf = NULL;
    ip_addr_t     ipaddr;
    u2            port = 0;

    if (desc == NULL)
    {
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
    }
    else if (socket->pcb == NULL)
    {
        return CLX_ERROR_BAD_STATE;
    }

    if (remoteAddr)
    {
        GET_IP_ADDR_PORT(remoteAddr, ipaddr, port);
    }

    pbuf = pbuf_alloc(socket->layer, desc->header.totalPacketLength, PBUF_RAM);

    if (pbuf == NULL)
    {
        return CLX_SYSTEM_ENOMEM;
    }

    pbuf->len = 0;

    while (desc)
    {
        clxMemCpy((u1*)pbuf->payload + pbuf->len, desc->data, desc->dataLength);

        pbuf->len += desc->dataLength;

        desc = desc->next;
    }

    FAST_PATH_ASSERT(pbuf->len == pbuf->tot_len);

    if (remoteAddr)
    {
        err = socket->sendto(socket->pcb, pbuf, &ipaddr, port);
    }
    else
    {
        err = socket->send(socket->pcb, pbuf);
    }

    pbuf_free(pbuf);

    switch (err)
    {
    case ERR_OK:
        return CLX_SUCCESS;
    case ERR_MEM:
        return CLX_SYSTEM_ENOBUFS;
    case ERR_RTE:
        return CLX_SYSTEM_ENETUNREACH;
    default:
        break;
    }

    clxDebugError("AsyncDatagramSocket: udp_send() failed with lwip error %d", (s4)err);
    return CLX_FAIL;
}

static ClxResult CLX_ASYNC AsyncDatagramSocket_recv(_in_ ClxAsyncNetworkSocket this_,
                                                    _user_in_ ClxNetworkBufferDescriptor* desc,
                                                    _out_ ClxNetworkServiceAddress* remoteAddr,
                                                    _in_ u4 timeout)
{
    AsyncDatagramSocket* socket = (AsyncDatagramSocket*)this_;
    ClxResult ret;

    if ((desc == NULL) || 
        (desc->bufferAddr == NULL) || 
        (desc->bufferSize == 0) ||
        (desc->next))
    {
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
    }
    else if (socket->pcb == NULL)
    {
        return CLX_SYSTEM_ENOTSOCK;
    }
    else if (socket->base.pendingServiceRxDescriptor)
    {
        clxDebugError("AsyncDatagramSocket_recv: Another recv() request is pending");
        return CLX_ERROR_BAD_STATE;
    }

    desc->data =        desc->bufferAddr;
    desc->dataLength =  0;

#if (NO_SYS)
    /* Stop the RX timer (in case it's running): */
    clxStopSchedulerTimer(&socket->base.rxTimer->base);
#endif

    /* First lets check if there is any packet pending: */
    ret = AsyncSocketDatagramQueue_pop(&socket->rxQueue, desc, remoteAddr);

    switch (ret)
    {
    case CLX_SUCCESS:
        break;

    case CLX_SYSTEM_ENOENT:
        if (timeout == 0)
        {
            ret = CLX_ERROR_TIMEOUT_OCCURRED;
        }
        else
        {
            /* We have to queue the descriptor and wait for reception of a new packet: */
            socket->base.pendingServiceRxDescriptor = desc;

            if (timeout != CLX_INFINITE)
            {
#if (NO_SYS)
                /* Start the timer: */
                clxStartSchedulerTimer(&socket->base.rxTimer->base, timeout);
#endif
            }

            ret = CLX_ERROR_COMPLETION_PENDING;
        }
        break;

    case CLX_SYSTEM_ENOMEM:
        /* Discard the rest of the packet data (to be consistent with BSD socket behaviour): */
        AsyncSocketDatagramQueue_discard(&socket->rxQueue);
        break;

    default:
        BLACKBOX;
        ret = CLX_ERROR_INTERNAL_ERROR;
        break;
    }

    return ret;
}

static ClxResult AsyncDatagramSocket_recv_callback(void* arg, struct pbuf* p, u2 initialIndex, const ip_addr_t* addr, u2 port)
{
    AsyncDatagramSocket* socket = (AsyncDatagramSocket*)arg;

    FAST_PATH_ASSERT(socket);

    if (AsyncSocketDatagramQueue_isEmpty(&socket->rxQueue) == FALSE)
    {
        /* If the RX queue is not empty, we cannot have a pending recv() operation: */
        FAST_PATH_ASSERT(socket->base.pendingServiceRxDescriptor == NULL);

        /* Push the packet to the RX queue: */
        AsyncSocketDatagramQueue_push(&socket->rxQueue, p, initialIndex, addr, port);
    }
    else if (socket->base.pendingServiceRxDescriptor)
    {
        ClxResult                    ret;
        ClxNetworkServiceAddress     remoteAddr;
        AsyncSocketDatagram          packet;
        ClxNetworkBufferDescriptor*  desc = socket->base.pendingServiceRxDescriptor;

#if (NO_SYS)
        /* Stop the RX timer (in case it's running): */
        clxStopSchedulerTimer(&socket->base.rxTimer->base);
#endif

        socket->base.pendingServiceRxDescriptor = NULL;

        clxMemSet(&packet, 0, sizeof(AsyncSocketDatagram));

        AsyncSocketDatagram_init(&packet, p, initialIndex, addr, port);
        
        ret = AsyncSocketDatagramQueue_decode(&packet, desc, &remoteAddr);

        switch (ret)
        {
        case CLX_SUCCESS:
        case CLX_SYSTEM_ENOMEM:
            break;

        default:
            BLACKBOX;
        }

        socket->base.service->socketRecvComplete(socket->base.service,
            &socket->base.base,
            desc,
            &remoteAddr,
            ret);

        return CLX_SUCCESS;
    }
    else
    {
        /* Push the packet to the RX queue: */
        AsyncSocketDatagramQueue_push(&socket->rxQueue, p, initialIndex, addr, port);
    }

    return CLX_ERROR_COMPLETION_PENDING;
}

#if LWIP_RAW
CLX_INLINE u1 recv_raw_callback(void* arg, struct raw_pcb* pcb, struct pbuf* p, const ip_addr_t* addr)
{
    if (p->len >= IPV4_HEADER_LENGTH)
    {
        /* 
        Before passing p to AsyncDatagramSocket_recv_callback, we increase the packet reference so it won't be freed 
        (we pass this back to LWIP for further processing): 
        */
        struct pbuf* pbuf = p;
        while (pbuf)
        {
            pbuf_ref(pbuf);
            pbuf = pbuf->next;
        }

        ClxResult ret = AsyncDatagramSocket_recv_callback(arg, p, IPV4_HEADER_LENGTH, addr, 0);
    }

    /* This will ask LWIP to pass it to other modules: */
    return 0;
}
#endif

#if LWIP_UDP 
CLX_INLINE void recv_udp_callback(void* arg, struct udp_pcb* pcb_lwip, struct pbuf* p, const ip_addr_t* addr, u2 port)
{
    ClxResult ret = AsyncDatagramSocket_recv_callback(arg, p, 0, addr, port);

    if (ret == CLX_SUCCESS)
    {
        pbuf_free(p);
    }
}
#endif

static ClxResult CLX_ASYNC AsyncDatagramSocket_terminate(_in_ ClxAsyncNetworkSocket this_)
{
    AsyncDatagramSocket* socket = (AsyncDatagramSocket*)this_;

    if (socket->pcb == NULL)
    {
        return CLX_ERROR_BAD_STATE;
    }

    socket->remove_pcb(socket->pcb);

    AsyncSocketDatagramQueue_destroy(&socket->rxQueue);

    return CLX_SUCCESS;
}

static void AsyncDatagramSocket_destroy(_in_ ClxAsyncNetworkSocket this_)
{
    AsyncDatagramSocket_terminate(this_);
    AsyncSocket_destroy(this_);
}

#if LWIP_RAW
static ClxAsyncNetworkSocket createLwipAsyncRawSocket(u1 protocol, const void* type)
{
    AsyncDatagramSocket* ret = (AsyncDatagramSocket*)clxAppAlloc(sizeof(AsyncDatagramSocket));

    AsyncSocket_new(&ret->base, ASYNC_SOCKET_TASK_PRIORITY, type);

    ret->pcb =      NULL;
    ret->layer =    PBUF_IP;
    ret->protocol = protocol;

    AsyncSocketDatagramQueue_init(&ret->rxQueue);

    ret->bind =                 bind_raw;
    ret->connect =              connect_raw;
    ret->new_pcb =              new_pcb_raw;
    ret->recv =                 recv_raw;
    ret->remove_pcb =           remove_pcb_raw;
    ret->send =                 send_raw;
    ret->sendto =               sendto_raw;

    ret->base.base.init =       AsyncDatagramSocket_init;
    ret->base.base.recv =       AsyncDatagramSocket_recv;
    ret->base.base.send =       AsyncDatagramSocket_send;
    ret->base.base.terminate =  AsyncDatagramSocket_terminate;
    ret->base.base.destroy =    AsyncDatagramSocket_destroy;

    return &ret->base.base;
}

ClxAsyncNetworkSocket clxLwipCreateLwipAsyncEchoRequestSocket()
{
    return createLwipAsyncRawSocket(IP_PROTOCOL_ICMP, CLX_C_STRUCTURE_TYPE(ClxAsyncNetworkEchoRequestSocket));
}

#endif /* #if LWIP_RAW */


#if LWIP_UDP 
ClxAsyncNetworkSocket clxCreateLwipAsyncUdpSocket()
{
    AsyncDatagramSocket* ret = (AsyncDatagramSocket*)clxAppAlloc(sizeof(AsyncDatagramSocket));

    AsyncSocket_new(&ret->base, ASYNC_SOCKET_TASK_PRIORITY, CLX_C_STRUCTURE_TYPE(ClxAsyncNetworkUdpSocket));
      
    ret->pcb =      NULL;
    ret->layer =    PBUF_TRANSPORT;
    ret->protocol = 0; /* not used with UDP sockets */

    AsyncSocketDatagramQueue_init(&ret->rxQueue);

    ret->bind =                 bind_udp;
    ret->connect =              connect_udp;
    ret->new_pcb =              new_pcb_udp;
    ret->recv =                 recv_udp;
    ret->remove_pcb =           remove_pcb_udp;
    ret->send =                 send_udp;
    ret->sendto =               sendto_udp;

    ret->base.base.init =       AsyncDatagramSocket_init;
    ret->base.base.recv =       AsyncDatagramSocket_recv;
    ret->base.base.send =       AsyncDatagramSocket_send;
    ret->base.base.terminate =  AsyncDatagramSocket_terminate;
    ret->base.base.destroy =    AsyncDatagramSocket_destroy;

    return &ret->base.base;    
}
#endif /* #if LWIP_UDP */
