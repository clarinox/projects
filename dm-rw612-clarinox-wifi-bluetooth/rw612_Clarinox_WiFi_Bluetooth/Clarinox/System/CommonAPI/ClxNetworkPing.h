#ifndef ClxNetworkPing_h
#define ClxNetworkPing_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxNetworkPing.h
* Description         Declares Network PING request for Embedded Systems
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#include "NetworkAccessInterface.Bsp.h"


#define CLX_NETWORK_PING_DEFAULT_PAYLOAD_SIZE           32   /* Bytes */
#define CLX_NETWORK_PING_DEFAULT_INTERVAL               100  /* in units of 10ms (1 second) */


#ifdef __cplusplus
extern "C" {
#endif


    struct ClxNetworkPing;
    typedef struct ClxNetworkPing* ClxNetworkPingHandle;


    extern ClxResult clxNetworkPingStart(_in_ ClxAsyncNetworkSocket socket,
                                         _in_ ClxSocketIpv4Address localIP,
                                         _in_ ClxSocketIpv4Address remoteIP,
                                         _in_ u2 payloadSize,
                                         _in_ u1 interval,
                                         _in_ ClxStdOutput notify,
                                         _out_ ClxNetworkPingHandle* handle);

    extern ClxResult clxNetworkPingStop(_in_ ClxNetworkPingHandle handle);


#ifdef __cplusplus
}
#endif

#endif // ClxNetworkPing_h