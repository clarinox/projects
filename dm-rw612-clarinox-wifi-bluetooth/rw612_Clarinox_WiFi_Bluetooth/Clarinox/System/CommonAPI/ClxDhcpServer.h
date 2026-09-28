#ifndef ClxDhcpServer_h
#define ClxDhcpServer_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxDhcpServer.h
* Description         Declares DCHP Server API
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#include "NetworkAccessInterface.Bsp.h"
#include "NetworkStackServiceInterface.Bsp.h"


#define CLX_DHCPV4_DEFAULT_SERVER_PORT                      67U      /* Standard No 67 */
#define CLX_DHCPV4_SERVER_DEFAULT_LEASE_TIME                86400U   /* 1 day */  
#define CLX_DHCPV4_SERVER_DEFAULT_INTERFACE_MTU             1500     /* Bytes */ 

#define CLX_DHCPV4_DOMAIN_LENGTH_MAX_LENGTH                 64U      /* Bytes */  

#define CLX_DHCPV4_SERVER_DEFAULT_MAX_NUM_OF_CLIENTS        10U     


#ifdef __cplusplus
extern "C" {
#endif
  

struct ClxDhcpv4Server;
typedef struct ClxDhcpv4Server* ClxDhcpv4ServerHandle;


typedef struct ClxDhcpv4ServerConfigConfigStuct
{
    ClxSocketIpv4Address   localIP;                                                 /*!< Cannot be 0 */
    u2                     localPort;                                               /*!< If 0, CLX_DHCPV4_DEFAULT_SERVER_PORT will used */
                           
    u1                     maxNumOfClients;                                         /*!< If 0, CLX_DHCPV4_SERVER_DEFAULT_MAX_NUM_OF_CLIENTS will be used */
                           
    ClxSocketIpv4Address   subnetMask;                                              /*!< Cannot be 0 */                         
    ClxSocketIpv4Address   broadcastIP;                                             /*!< If 0, CLX_LIMITED_BROADCAST_IP will be used */

    ClxSocketIpv4Address   clientStartIP;                                           /*!< Cannot be 0. MUST be in the same sub network as the local IP.
                                                                                         The IPs available to the clients will be clientStartIP through (clientStartIP + maxNumOfClients - 1).
                                                                                         This range MUST NOT include any static IPs (including the local IP). */
    ClxSocketIpv4Address   gatewayIP;                                               /*!< Cannot be 0. MUST be in the same sub network as the local IP */
    ClxSocketIpv4Address   routerIP;                                                /*!< If 0, the same value as gatewayIP will be used */

    ClxSocketIpv4Address   dnsIP1;                                                  /*!< Cannot be 0. Preferred DNS */ 
    ClxSocketIpv4Address   dnsIP2;                                                  /*!< May be 0 */
    ClxSocketIpv4Address   dnsIP3;                                                  /*!< May be 0 */
                           
    u4                     leaseTime;                                               /*!< If 0, CLX_DHCPV4_SERVER_DEFAULT_LEASE_TIME will used */  
    u2                     interfaceMTU;                                            /*!< If 0, CLX_DHCPV4_SERVER_DEFAULT_INTERFACE_MTU will used */  

    s1                     domainName[CLX_DHCPV4_DOMAIN_LENGTH_MAX_LENGTH + 1];     /*!< May be empty */
                           
    ClxStdOutput           notify;                                                  /*!< May be NULL */
} ClxDhcpv4ServerConfig;



extern ClxResult clxDhcpv4ServerInit(_in_ const ClxDhcpv4ServerConfig* config, 
                                     _in_ ClxAsyncNetworkSocket socket,
                                     _out_ ClxDhcpv4ServerHandle* handle);

extern ClxResult clxDhcpv4ServerDestroy(_in_ ClxDhcpv4ServerHandle handle);


#ifdef __cplusplus
}
#endif

#endif // ClxDhcpServer_h

