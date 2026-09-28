#ifndef _Spp_h_
#define _Spp_h_

/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                Spp.h
* Description         Spp Application definitions
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2021 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#include "Spp.Api.h"


/* 
Creates the SPP profile with the server or client role. This will advertise the SPP functionality via the SDP server
*/
void createSppHandle(ClxStack stack, boolean server);

/* 
Deletes the SPP profile handle when there is no use for this profile.
*/
void deleteSppHandle(void);

/* 
Provides the SPP menu and initiate the connection
*/
void sppMenuFunction(ClxStack stack, ClxDeviceId id);

/*
This callback function is registered for the SPP profile, any events raised by SPP profile, causes this
callback function executed with the associated event and parameters. Executed from the stack thread context
*/
boolean sppIndicationHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);

#endif //_Spp_h_

