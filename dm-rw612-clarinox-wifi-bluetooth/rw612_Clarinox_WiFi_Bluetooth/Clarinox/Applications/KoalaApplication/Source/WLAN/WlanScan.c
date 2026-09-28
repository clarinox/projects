

/*********************************************************************************
*
* Project             Wlan Sample Application Scan Wrapper
* File                WlanScan.c
* Description         Wlan application Scan Wrapper + Discovery Module
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#include "WlanScan.h"
#include "Driver/Driver.h"
#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
#include "Wlan.ClxMesh.Api.h"
#endif

const DriverOps* drv = NULL;

const u1 scanChannels_2_4GHz[] = { 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u };                        /* All 2.4GHz channels except for channel 14 */
const u1 scanChannels_5GHz[] =   { 36u, 40u, 44u, 48u, 60u, 64u, 102u, 108u, 112u, 116u, 149u, 153u, 157u, 161u, 165u };      /* 5 GHz channels commonly used by AccessPoints */

#define NUMBER_OF_2_4_CHANNELS   (sizeof(scanChannels_2_4GHz)/sizeof(u1))
#define NUMBER_OF_5_CHANNELS     (sizeof(scanChannels_5GHz)/sizeof(u1))

#define SCAN_TIME_PER_CHANNEL                          25u /* ms */
#define SCAN_TIME_PER_SPECIFIC_CHANNEL                 100u/* ms */

#define NUM_OF_SCAN_PROBE_REQUESTS_PER_CHANNEL         2u

static ClxWlanStationListHandle discoveredBssContainer = NULL;

static boolean gFancyDiscoveredBSSResults = TRUE;
static boolean gInitialized = FALSE;

static boolean addBssToDiscoveredBssContainer(ClxWlanStationListHandle this_, ClxBSSInfo* bss, u4* index)
{
    struct ClxWlanStationListItemInfo info = clxWlanStationListAdd(this_, bss->bssid);

    if ((info.station) && (info.stationExists == FALSE))
    {
        ClxDiscoveredBss* entry = (ClxDiscoveredBss*)info.station;

        clxMemCpy(&entry->ssid, &bss->ssid, sizeof(entry->ssid));

        entry->authTypes =             bss->authType;
        entry->supportedEncProtocols = bss->encProtocol;
        entry->band =                  bss->band;
        entry->primaryChannel =        bss->channel;
        entry->rssi =                  bss->rssi;
#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
        entry->isMeshNode = FALSE;
        entry->hopsToRoot = 0;
        ClxWlanMeshNodeInfo meshNodeInfo;
        if (bss->meshBssIE && clxWlanMeshDecodeMeshBssIE(bss->meshBssIE, &meshNodeInfo))
        {
            entry->isMeshNode = TRUE;
            memset(entry->nodeAddress, 0, sizeof(entry->nodeAddress));
            if (meshNodeInfo.alMacAddress.base.initialized)
            {
                clxMemCpy(entry->nodeAddress, meshNodeInfo.alMacAddress.field, CLX_MAC_ADDRESS_LENGTH);
            }
            memset(entry->rootAddress, 0, sizeof(entry->rootAddress));
            if (meshNodeInfo.uplinkConnectionInfo.base.initialized)
            {
                entry->hopsToRoot = meshNodeInfo.uplinkConnectionInfo.hopsToRoot;
                clxMemCpy(entry->rootAddress, meshNodeInfo.uplinkConnectionInfo.rootALMacAddress, CLX_MAC_ADDRESS_LENGTH);
            }
            entry->meshID.len = 0;
            if (meshNodeInfo.meshID.base.initialized)
            {
                clxMemCpy(&entry->meshID, &meshNodeInfo.meshID.field, sizeof(ClxSSID));
            }
            /* TODO: Move mesh specific declarations into a header and use it common. */
            entry->maxClients = 8;
            entry->currentClients = 0;
            if (meshNodeInfo.downlinkInfo.base.initialized)
            {
                entry->maxClients = meshNodeInfo.downlinkInfo.maxNumberOfClients;
                entry->currentClients = meshNodeInfo.downlinkInfo.currentNumberOfClients;
            }
        }
#endif
        *index = clxWlanStationListGetNumber(this_);
        return TRUE;
    }

    return FALSE;
}

ClxDiscoveredBss* clxWlanScanGetDiscoveredBSSByBSSID(u1* bssid)
{
    if (discoveredBssContainer == NULL) {
        return NULL;
    }
    return (ClxDiscoveredBss*)clxWlanStationListFindByMacAddress(discoveredBssContainer, bssid);
}

u4 clxWlanScanGetDiscoveredBSSCount()
{
    return clxWlanStationListGetNumber(discoveredBssContainer);
}

ClxDiscoveredBss* clxWlanScanGetDiscoveredBSSByIndex(u4 index)
{
    ClxDiscoveredBss* bss = NULL;
    u4 count = clxWlanStationListGetNumber(discoveredBssContainer);

    if (count != 0 && index < count)
    {
        bss = (ClxDiscoveredBss*)clxWlanStationListGetByIndex(discoveredBssContainer, index);
    }
    
    return bss;
}

ClxResult clxWlanScanInit(boolean fancyResults)
{
    if (gInitialized) {
        return CLX_SUCCESS;
    }

    drv = GetDriverOps();
    if (!drv) {
        return CLX_FAIL;
    }

    discoveredBssContainer = clxWlanStationListCreate(MAX_NO_OF_AP_IN_VICINITY, sizeof(ClxDiscoveredBss));
    if (discoveredBssContainer == NULL) {
        return CLX_FAIL;
    }

    gFancyDiscoveredBSSResults = fancyResults;
    gInitialized = TRUE;

    return CLX_SUCCESS;
}


void clxWlanScanBSSDiscovered(ClxBSSInfo* bss)
{
    u4 index = 0;

    bss->rssi = (bss->rssi-0xFF)/2;

    if (addBssToDiscoveredBssContainer(discoveredBssContainer, bss, &index))
    {
        clxConsoleUIEngineText("\nSSID=%s, BSSID=%02X:%02X:%02X:%02X:%02X:%02X, RSSI=%d dBm\n",
            (s1*)bss->ssid.value,
            bss->bssid[0],
            bss->bssid[1],
            bss->bssid[2],
            bss->bssid[3],
            bss->bssid[4],
            bss->bssid[5],
            (s4)bss->rssi);

        if (gFancyDiscoveredBSSResults) {
            clxWlanPrintDetailedBssInfo(bss, index);
        }
    }
}


s4 clxWlanScanSelectDiscoveredBSS(ClxHandle staHandle)
{
    u4 count = clxWlanStationListGetNumber(discoveredBssContainer);

    if (count == 0)
    {
        return -1;
    }

    u4 index = 0;

    while (index < count)
    {
        ClxDiscoveredBss* bss = (ClxDiscoveredBss*)clxWlanStationListGetByIndex(discoveredBssContainer, index);
        CLX_ASSERT(bss);

        clxConsoleUIEngineText("%u. (%02X:%02X:%02X:%02X:%02X:%02X) %s\n", ++index,
            bss->base.macAddress[0],
            bss->base.macAddress[1],
            bss->base.macAddress[2],
            bss->base.macAddress[3],
            bss->base.macAddress[4],
            bss->base.macAddress[5],
            bss->ssid.len ? bss->ssid.value : "<Wildcard SSID>");
    }

    clxConsoleUIEngineText("%u. Let me enter BSS details manually\n", ++index);

    u4 selection = 0;

    while ((selection < 1) || (selection > index))
    {
        clxConsoleUIEngineInputBox("\nSelect an item : ", clxUiInputBuffer, sizeof(clxUiInputBuffer));

        selection = atoi(clxUiInputBuffer);
    }

    return (selection == index) ? -1 : (s4)(selection - 1);
}

ClxResult clxWlanScanStationInterface(ClxHandle staHandle)
{
    ClxResult ret = CLX_SUCCESS;
    const DriverOps* drv = GetDriverOps();
    if (!drv) {
        return CLX_FAIL;
    }

    clxWlanStationListClear(discoveredBssContainer);
    
    ret = drv->configureScanParameters(staHandle, 
        scanChannels_2_4GHz,
        NUMBER_OF_2_4_CHANNELS,
        scanChannels_5GHz,
        NUMBER_OF_5_CHANNELS,
        NUM_OF_SCAN_PROBE_REQUESTS_PER_CHANNEL,
        SCAN_TIME_PER_CHANNEL,
        ClxWlanPassiveScan);

    if (ret != CLX_SUCCESS)
    {
        return ret;
    }

    /*
    Scan NO_OF_SCAN_REPETITION times to find all the APs
    */
    for (u4 k = 0; k < NO_OF_SCAN_REPETITION; k++)
    {
        ret = clxWlanScan(staHandle,                /* Handle to the virtual interface as returned by clxWlanCreateInterface                                                */
            NULL,                                   /* Do not filter based on AP's MAC address   */
            NULL,                                   /* Do not scan for a specific SSID. Scan for all available networks in the area (Operating on the provided channels)    */
            TRUE);                                  /* Blocking mode. Do not return until the scan procedure is complete                                                    */

        /* Sleep a little bit so the details of discovered devices can be fully printed: */
        clxSleep(20);

        if (ret != CLX_SUCCESS)
        {
            break;
        }

        if (clxWlanStationListGetNumber(discoveredBssContainer) == MAX_NO_OF_AP_IN_VICINITY)
        {
            /* The list is full. So, no point in keeping scanning: */
            break;
        }
    }

    clxConsoleUIEngineText("\nScan is complete with the result: %s - No of BSSs found: %u\n",
        clxGetWlanErrorCodeText(ret),
        clxWlanStationListGetNumber(discoveredBssContainer));

    return ret;
}

/* TODO: Refactor to cover all scan functions with a parameter struct */
ClxResult clxWlanScanStationInterfaceForSpecificBSS(ClxHandle staHandle, 
    ClxDiscoveredBss *bss, ClxWlanScanType scanType, u2 scanTime, u1 repeatCount)
{
    ClxResult ret = CLX_SUCCESS;
    const DriverOps* drv = GetDriverOps();
    if (!drv) {
        return CLX_FAIL;
    }

    clxWlanStationListClear(discoveredBssContainer);

    if (bss->band == ClxWlanFreqBand5GHz)
    {
        ret = drv->configureScanParameters(staHandle, NULL, 0, (u1 *)&bss->primaryChannel, 1,
            NUM_OF_SCAN_PROBE_REQUESTS_PER_CHANNEL,
            scanTime,
            scanType);
    }
    else
    {
        ret = drv->configureScanParameters(staHandle, (u1*)&bss->primaryChannel, 1, NULL, 0,
            NUM_OF_SCAN_PROBE_REQUESTS_PER_CHANNEL,
            scanTime,
            scanType);
    }

    if (ret != CLX_SUCCESS)
    {
        return ret;
    }

    for (u4 k = 0; k < repeatCount; k++)
    {
        ret = clxWlanScan(staHandle,                /* Handle to the virtual interface as returned by clxWlanCreateInterface */
            NULL,                                   /* Do not filter based on AP's MAC address   */
            &bss->ssid,
            TRUE);                                  /* Blocking mode. */

        /* Sleep a little bit so the details of discovered devices can be fully printed: */
        clxSleep(20);

        if (ret != CLX_SUCCESS)
        {
            break;
        }

        if (clxWlanStationListGetNumber(discoveredBssContainer) == MAX_NO_OF_AP_IN_VICINITY)
        {
            /* The list is full. So, no point in keeping scanning: */
            break;
        }
    }

    clxConsoleUIEngineText("\nScan is complete with the result: %d - No of BSSs found: %u\n",
        ret, clxWlanStationListGetNumber(discoveredBssContainer));

    return ret;
}

ClxResult clxWlanScanSpecificSsid(ClxHandle staHandle,
                                  const ClxSSID* ssid)
{
    ClxResult ret = CLX_SUCCESS;
    u4 numOfDiscoveredBss = 0;
    const DriverOps* drv = GetDriverOps();
    if (!drv) {
        return CLX_FAIL;
    }

    clxWlanStationListClear(discoveredBssContainer);

    ret = drv->configureScanParameters(staHandle,
        scanChannels_2_4GHz,
        NUMBER_OF_2_4_CHANNELS,
        scanChannels_5GHz,
        NUMBER_OF_5_CHANNELS,
        NUM_OF_SCAN_PROBE_REQUESTS_PER_CHANNEL,
        SCAN_TIME_PER_CHANNEL,
        ClxWlanActiveScan);

    if (ret != CLX_SUCCESS)
    {
        return ret;
    }

    /*
    Scan NO_OF_SCAN_REPETITION times to find all the APs
    */
    for (u4 k = 0; k < NO_OF_SCAN_REPETITION; k++)
    {
        ret = clxWlanScan(staHandle,                /* Handle to the virtual interface as returned by clxWlanCreateInterface                                                */
            NULL,                                   /* Do not filter based on AP's MAC address   */
            ssid,                                   
            TRUE);                                  /* Blocking mode. Do not return until the scan procedure is complete                                                    */

        /* Sleep a little bit so the details of discovered devices can be fully printed: */
        clxSleep(20);

        if (ret != CLX_SUCCESS)
        {
            break;
        }

        /* If we already have the BSS on the list, we will break: */
        numOfDiscoveredBss = clxWlanStationListGetNumber(discoveredBssContainer);

        for (u4 i = 0; i < numOfDiscoveredBss; i++)
        {
            ClxDiscoveredBss* bss = (ClxDiscoveredBss*)clxWlanStationListGetByIndex(discoveredBssContainer, i);
            CLX_ASSERT(bss);

            if (clxMemCmp(&bss->ssid, ssid, sizeof(ClxSSID)) == 0)
            {
                break;
            }
        }
    }

    clxConsoleUIEngineText("\nScan is complete with the result: %s - No of BSSs found: %u\n",
        clxGetWlanErrorCodeText(ret),
        numOfDiscoveredBss);

    return ret;
}

ClxResult clxWlanScanConfigure(ClxHandle staHandle,
                               ClxDiscoveredBss *bss,
                               ClxWlanScanType scanType)
{
    ClxResult ret = CLX_FAIL;
    if (bss)
    {
        u1 channel = (u1)bss->primaryChannel;

        if (bss->band == ClxWlanFreqBand5GHz)
        {
            ret = drv->configureScanParameters(staHandle, NULL, 0, &channel, 1,
                NUM_OF_SCAN_PROBE_REQUESTS_PER_CHANNEL,
                SCAN_TIME_PER_CHANNEL,
                ClxWlanActiveScan);
        }
        else
        {
            ret = drv->configureScanParameters(staHandle, &channel, 1, NULL, 0,
                NUM_OF_SCAN_PROBE_REQUESTS_PER_CHANNEL,
                SCAN_TIME_PER_CHANNEL,
                ClxWlanActiveScan);
        }
    }
    else
    {
        ret = clxWlanScanConfigureBlind(staHandle, scanType);
    }

    return ret;
}

ClxResult clxWlanScanConfigureBlind(ClxHandle staHandle, ClxWlanScanType scanType)
{
    return drv->configureScanParameters(staHandle,
        scanChannels_2_4GHz,
        NUMBER_OF_2_4_CHANNELS,
        scanChannels_5GHz,
        NUMBER_OF_5_CHANNELS,
        NUM_OF_SCAN_PROBE_REQUESTS_PER_CHANNEL,
        SCAN_TIME_PER_CHANNEL,
        scanType);
}



ClxResult clxWlanStartBGScanWithUserParams(ClxHandle staHandle)
{
    ClxResult ret = CLX_SUCCESS;
    static s1 inputBuf[32];
    ClxSSID ssid[4];
    u4 numberOfSsids = 0;
    u1 channelsPerScanInstance;
    u4 scanInterval;
    s4 rssiThreshold;
    s4 snrThreshold;
    u4 repeatCount = 0;
    const DriverOps* drv = GetDriverOps();
    if (!drv) {
        return CLX_FAIL;
    }

    while ((numberOfSsids == 0) || (numberOfSsids > (sizeof(ssid) / sizeof(ClxSSID))))
    {
        clxConsoleUIEngineInputBox("Number of SSIDs to scan for (1 to 4): ", inputBuf, sizeof(inputBuf));
        numberOfSsids = clxAsciiToInteger(inputBuf);
    }

    for (u4 i = 0; i < numberOfSsids; i++)
    {
        clxConsoleUIEngineText("SSID %u : ", i + 1);
        clxConsoleUIEngineInputBox("", ssid[i].value, sizeof(ssid[i].value) - 1);
        ssid[i].len = (u1)strlen(ssid[i].value);
    }

    clxConsoleUIEngineInputBox("Number of channels per scan instance: ", inputBuf, sizeof(inputBuf));
    channelsPerScanInstance = clxAsciiToInteger(inputBuf);

    clxConsoleUIEngineInputBox("Number of scan repeats (0=scan until stopped): ", inputBuf, sizeof(inputBuf));
    repeatCount = clxAsciiToInteger(inputBuf);

    clxConsoleUIEngineInputBox("Interval between scan instances: ", inputBuf, sizeof(inputBuf));
    scanInterval = clxAsciiToInteger(inputBuf);

    while (1)
    {
        clxConsoleUIEngineInputBox("Report RSSI Threshold in dBm (0 to disable): ", inputBuf, sizeof(inputBuf));
        rssiThreshold = clxAsciiToInteger(inputBuf);

        if (rssiThreshold > 0)
        {
            clxConsoleUIEngineText("\nRSSI Threshold must be a negative value\n");
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        clxConsoleUIEngineInputBox("Report SNR Threshold in dB (0 to disable): ", inputBuf, sizeof(inputBuf));
        snrThreshold = clxAsciiToInteger(inputBuf);

        if (snrThreshold < 0)
        {
            clxConsoleUIEngineText("\nSNR Threshold must be a non-negative value\n");
        }
        else
        {
            break;
        }
    }

    ret = drv->configureBgScanParameters(staHandle,
        scanChannels_2_4GHz,
        sizeof(scanChannels_2_4GHz),
        scanChannels_5GHz,
        sizeof(scanChannels_5GHz),
        NUM_OF_SCAN_PROBE_REQUESTS_PER_CHANNEL,
        SCAN_TIME_PER_CHANNEL,
        ClxWlanActiveScan,
        channelsPerScanInstance,
        repeatCount,
        scanInterval,
        (u1)(-1 * rssiThreshold),
        (u1)snrThreshold,
        ssid,
        numberOfSsids);

    if (ret == CLX_SUCCESS)
    {
        ret = clxWlanStartBgScan(staHandle,
            repeatCount ? FALSE : TRUE,
            TRUE);

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxWlanStartBgScan() failed with error %s\n", clxGetWlanErrorCodeText(ret));
        }
    }

    return ret;
}
