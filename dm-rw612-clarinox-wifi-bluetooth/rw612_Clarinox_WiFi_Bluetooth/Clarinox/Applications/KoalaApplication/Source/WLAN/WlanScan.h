#ifndef WiFiAppScan_H
#define WiFiAppScan_H

/*********************************************************************************
*
* Project             Wlan Sample Application Scan Wrapper
* File                WlanScan.h
* Description         Wlan application Scan Wrapper + Discovery Module
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#include <stdlib.h>

#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include "ConsoleUIEngine.h"
#include "ClarinoxWlan.h"
#include "Wlan.Api.h"
#include "Wlan.Config.h"
#include "WiFiApp.h"

ClxResult clxWlanScanInit(boolean fancyResults);
ClxResult clxWlanScanSpecificSsid(ClxHandle staHandle, const ClxSSID* ssid);
ClxResult clxWlanScanStationInterface(ClxHandle staHandle);
ClxResult clxWlanScanConfigureBlind(ClxHandle staHandle, ClxWlanScanType scanType);
ClxResult clxWlanScanConfigureMulti(ClxHandle staHandle,
                                    ClxDiscoveredBss *bss,
                                    ClxWlanScanType scanType,
                                    const u1* channelList, 
                                    u4 numOfChannels);
ClxResult clxWlanScanConfigure(ClxHandle staHandle,
                               ClxDiscoveredBss *bss,
                               ClxWlanScanType scanType);
ClxResult clxWlanScanStationInterfaceForSpecificBSS(ClxHandle staHandle,
    ClxDiscoveredBss *bss, ClxWlanScanType scanType, u2 scan_time, u1 repeat_cnt);
ClxDiscoveredBss* clxWlanScanGetDiscoveredBSSByBSSID(u1* bssid);
ClxDiscoveredBss* clxWlanScanGetDiscoveredBSSByIndex(u4 index);
s4 clxWlanScanSelectDiscoveredBSS(ClxHandle staHandle);
void clxWlanScanBSSDiscovered(ClxBSSInfo* bss);
u4 clxWlanScanGetDiscoveredBSSCount();
ClxResult clxWlanStartBGScanWithUserParams(ClxHandle staHandle);

#endif /* WiFiAppScan_H */