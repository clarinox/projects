/*********************************************************************************
*
* Project             Clarinox WLAN App
* File                Driver.h
* Description         Driver Wrapper to cover platform operations
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2020 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#ifndef CLX_APP_DRIVER_H
#define CLX_APP_DRIVER_H

#include <stdlib.h>

#include "ClxBsp.h"
#include "ClxBspConfig.h"

#include "ClarinoxWlan.h"
#include "Wlan.Api.h"
#include "Wlan.Config.h"

// Function prototypes for driver operations
typedef struct {
    ClxResult (*configureScanParameters)(ClxHandle interfaceHandle, 
                                        const u1* channelList_2_4GHz, 
                                        u4 numOfChannels_2_4GHz,
                                        const u1* channelList_5GHz,
                                        u4 numOfChannels_5GHz,
                                        u4 numOfProbesPerChannel,
                                        u4 scanDurationPerChannel, 
                                        ClxWlanScanType scanType);

    ClxResult (*configureParameters)(ClxHandle interfaceHandle);

    ClxResult (*getConnectionTempSensorInfo)(ClxHandle interfaceHandle);

    s2 (*getConnectionAverageMgmtRSSI)(ClxHandle interfaceHandle);

    ClxResult (*getConnectionSignalInfo)(ClxHandle interfaceHandle);

    ClxResult (*getConnectionStatInfo)(ClxHandle interfaceHandle);

    ClxResult (*configureBgScanParameters)(ClxHandle interfaceHandle,
                                        const u1* channelList_2_4GHz,
                                        u4 numOfChannels_2_4GHz,
                                        const u1* channelList_5GHz,
                                        u4 numOfChannels_5GHz,
                                        u4 numOfProbesPerChannel,
                                        u4 scanDurationPerChannel,
                                        ClxWlanScanType scanType,
                                        u1 channelsPerScanInstance,
                                        u4 repeatCount,
                                        u4 scanInterval,
                                        u1 rssiThreshold,
                                        u1 snrThreshold,
                                        const ClxSSID* ssids,
                                        u4 numberOfSsids);

    void (*setConfigFtmSession)(ClxHandle staHandle);
    
    void (*startStopFtmSession)(ClxHandle staHandle, boolean start);

    void (*driverSpecificReport)(ClxWlanDriverSpecificIndication* arg);

} DriverOps;

// Function to get the driver operations
const DriverOps* GetDriverOps(void);

#endif // CLX_APP_DRIVER_H
