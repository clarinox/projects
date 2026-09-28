#ifndef ClxIperfServer_h
#define ClxIperfServer_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxIperfServer.h
* Description         Declares IPerf server API
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#define IPERF_SERVER_PORT   5001
#define IPERF_CLIENT_PORT   5001
#define IPERF_INTERVAL      2000


#ifdef __cplusplus
extern "C" {
#endif
   

extern ClxResult clxUdpIperfServerInit(u2 interval, const ClxSocketAddressContainer* serverAddress);
extern void clxUdpIperfServerDestroy();

extern ClxResult clxTcpIperfServerInit(u2 interval, const ClxSocketAddressContainer* serverAddress);
extern void clxTcpIperfServerDestroy();


#ifdef __cplusplus
}
#endif

#endif // ClxIperfServer_h

