/*********************************************************************************
*
* Project             Clarinox WLAN App
* File                DriverMLAN.c
* Description         MLAN Driver App Wrapper
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2020 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#include "Driver.h"

#include "WiFiApp.h"
#include "WlanScan.h"
#include "Wlan.Marvel.Config.h"


#ifdef CLX_NXP_POWER_TABLE_MANAGEMENT_SUPPORT_ENABLE
/*NXP W9098 JAPAN POWER TABLE*/
const u1 mlanCustomPowerTable[634] = {
    0x0d, 0x0a, 0x72, 0x65, 0x67, 0x69, 0x6f, 0x6e, 0x5f, 0x70, 0x77, 0x72, 0x5f, 0x63, 0x66, 0x67, 
    0x20, 0x3d, 0x20, 0x7b, 0x20, 0x0d, 0x0a, 0x34, 0x39, 0x20, 0x30, 0x32, 0x20, 0x63, 0x32, 0x20, 
    0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 
    0x31, 0x20, 0x30, 0x30, 0x20, 0x65, 0x65, 0x20, 0x30, 0x31, 0x20, 0x30, 0x36, 0x20, 0x30, 0x30, 
    0x20, 0x34, 0x61, 0x20, 0x35, 0x30, 0x20, 0x0d, 0x0a, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 
    0x30, 0x20, 0x30, 0x33, 0x20, 0x30, 0x36, 0x20, 0x30, 0x32, 0x20, 0x61, 0x61, 0x20, 0x30, 0x30, 
    0x20, 0x38, 0x38, 0x20, 0x38, 0x38, 0x20, 0x30, 0x33, 0x20, 0x30, 0x31, 0x20, 0x30, 0x61, 0x20, 
    0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x0d, 0x0a, 0x30, 0x30, 0x20, 0x30, 0x30, 
    0x20, 0x34, 0x61, 0x20, 0x35, 0x30, 0x20, 0x30, 0x30, 0x20, 0x30, 0x30, 0x20, 0x38, 0x33, 0x20, 
    0x30, 0x39, 0x20, 0x30, 0x31, 0x20, 0x30, 0x30, 0x20, 0x30, 0x38, 0x20, 0x30, 0x36, 0x20, 0x61, 
    0x30, 0x20, 0x30, 0x30, 0x20, 0x32, 0x30, 0x20, 0x65, 0x30, 0x20, 0x0d, 0x0a, 0x36, 0x38, 0x20, 
    0x30, 0x32, 0x20, 0x30, 0x37, 0x20, 0x30, 0x35, 0x20, 0x38, 0x33, 0x20, 0x63, 0x31, 0x20, 0x61, 
    0x30, 0x20, 0x39, 0x30, 0x20, 0x36, 0x30, 0x20, 0x35, 0x34, 0x20, 0x32, 0x32, 0x20, 0x31, 0x62, 
    0x20, 0x30, 0x63, 0x20, 0x38, 0x37, 0x20, 0x34, 0x34, 0x20, 0x36, 0x32, 0x20, 0x0d, 0x0a, 0x31, 
    0x31, 0x20, 0x33, 0x30, 0x20, 0x30, 0x63, 0x20, 0x33, 0x65, 0x20, 0x32, 0x62, 0x20, 0x31, 0x32, 
    0x20, 0x38, 0x62, 0x20, 0x63, 0x35, 0x20, 0x32, 0x32, 0x20, 0x63, 0x30, 0x20, 0x39, 0x30, 0x20, 
    0x35, 0x38, 0x20, 0x31, 0x63, 0x20, 0x30, 0x34, 0x20, 0x30, 0x30, 0x20, 0x31, 0x63, 0x20, 0x0d, 
    0x0a, 0x63, 0x36, 0x20, 0x65, 0x33, 0x20, 0x62, 0x31, 0x20, 0x66, 0x39, 0x20, 0x30, 0x38, 0x20, 
    0x31, 0x63, 0x20, 0x31, 0x30, 0x20, 0x30, 0x36, 0x20, 0x38, 0x36, 0x20, 0x34, 0x39, 0x20, 0x61, 
    0x35, 0x20, 0x31, 0x31, 0x20, 0x35, 0x39, 0x20, 0x35, 0x30, 0x20, 0x30, 0x30, 0x20, 0x31, 0x65, 
    0x20, 0x0d, 0x0a, 0x30, 0x61, 0x20, 0x39, 0x36, 0x20, 0x63, 0x62, 0x20, 0x32, 0x34, 0x20, 0x66, 
    0x32, 0x20, 0x39, 0x39, 0x20, 0x39, 0x38, 0x20, 0x33, 0x63, 0x20, 0x30, 0x36, 0x20, 0x30, 0x31, 
    0x20, 0x30, 0x30, 0x20, 0x34, 0x31, 0x20, 0x34, 0x30, 0x20, 0x38, 0x30, 0x20, 0x33, 0x30, 0x20, 
    0x37, 0x61, 0x20, 0x0d, 0x0a, 0x30, 0x30, 0x20, 0x32, 0x38, 0x20, 0x30, 0x30, 0x20, 0x31, 0x33, 
    0x20, 0x38, 0x33, 0x20, 0x34, 0x32, 0x20, 0x36, 0x30, 0x20, 0x30, 0x30, 0x20, 0x61, 0x35, 0x20, 
    0x30, 0x61, 0x20, 0x38, 0x39, 0x20, 0x34, 0x36, 0x20, 0x30, 0x61, 0x20, 0x30, 0x32, 0x20, 0x32, 
    0x38, 0x20, 0x37, 0x34, 0x20, 0x0d, 0x0a, 0x39, 0x61, 0x20, 0x35, 0x64, 0x20, 0x32, 0x61, 0x20, 
    0x38, 0x38, 0x20, 0x30, 0x38, 0x20, 0x30, 0x38, 0x20, 0x63, 0x37, 0x20, 0x61, 0x39, 0x20, 0x66, 
    0x35, 0x20, 0x31, 0x38, 0x20, 0x66, 0x64, 0x20, 0x32, 0x36, 0x20, 0x61, 0x39, 0x20, 0x34, 0x66, 
    0x20, 0x61, 0x36, 0x20, 0x64, 0x36, 0x20, 0x0d, 0x0a, 0x36, 0x61, 0x20, 0x37, 0x35, 0x20, 0x32, 
    0x61, 0x20, 0x62, 0x35, 0x20, 0x37, 0x32, 0x20, 0x61, 0x31, 0x20, 0x35, 0x65, 0x20, 0x61, 0x36, 
    0x20, 0x64, 0x35, 0x20, 0x63, 0x32, 0x20, 0x39, 0x33, 0x20, 0x63, 0x30, 0x20, 0x31, 0x30, 0x20, 
    0x31, 0x32, 0x20, 0x38, 0x39, 0x20, 0x36, 0x34, 0x20, 0x0d, 0x0a, 0x62, 0x33, 0x20, 0x35, 0x38, 
    0x20, 0x63, 0x31, 0x20, 0x66, 0x36, 0x20, 0x35, 0x62, 0x20, 0x33, 0x64, 0x20, 0x61, 0x65, 0x20, 
    0x64, 0x33, 0x20, 0x34, 0x65, 0x20, 0x61, 0x65, 0x20, 0x64, 0x35, 0x20, 0x36, 0x64, 0x20, 0x31, 
    0x36, 0x20, 0x64, 0x62, 0x20, 0x36, 0x35, 0x20, 0x61, 0x61, 0x20, 0x0d, 0x0a, 0x65, 0x62, 0x20, 
    0x37, 0x33, 0x20, 0x30, 0x61, 0x20, 0x30, 0x32, 0x20, 0x36, 0x39, 0x20, 0x37, 0x37, 0x20, 0x61, 
    0x61, 0x20, 0x64, 0x64, 0x20, 0x63, 0x61, 0x20, 0x64, 0x64, 0x20, 0x34, 0x34, 0x20, 0x62, 0x65, 
    0x20, 0x35, 0x65, 0x20, 0x36, 0x63, 0x20, 0x33, 0x35, 0x20, 0x63, 0x62, 0x20, 0x0d, 0x0a, 0x39, 
    0x38, 0x20, 0x65, 0x63, 0x20, 0x0d, 0x0a, 0x7d, 0x0d, 0x0a
};
#endif

static void setScanChannelInfo(ClxMlanOID_UserScanChannel* obj,
                               u1 chanbelNumber,
                               enum ClxWlanFrequencyBandEnum freqband,
                               boolean activeScan,
                               u4 scanTimeDuration)
{
    obj->chan_number = chanbelNumber;
    
    /* 'B/G' Band = 0, 'A' Band = 1  */
    switch(freqband)
    {
    case ClxWlanFreqBand2_4GHz:
      {
        obj->radio_type = 0U;
        break;
      }
    case ClxWlanFreqBand5GHz:
      {
        obj->radio_type = 1U;
        break; 
      }
    default:
      {
        BLACKBOX;
        break;
      }
    }

    obj->scan_type = (activeScan ? 1U : 2U);  /* Active = 1, Passive = 2 */
    obj->scan_time = scanTimeDuration; /* ms */
}

ClxResult configureScanParameters_MLAN(ClxHandle interfaceHandle, 
                                       const u1* channelList_2_4GHz, 
                                       u4 numOfChannels_2_4GHz,
                                       const u1* channelList_5GHz,
                                       u4 numOfChannels_5GHz,
                                       u4 numOfProbesPerChannel,
                                       u4 scanDurationPerChannel, 
                                       ClxWlanScanType scanType)
{
    typedef struct Config_
    {
        ClxConfigList            parentList;
        ClxMlanOID_UserScan      userScanOID;
        ClxMlanOidConfigParam    userScanOID_ConfigParam;
    }Config;

    static Config config;

    clxConfigInitParamsList(&config.parentList, NULL, NULL);

    u4 index = 0;

    (void)memset(&config.userScanOID, 0, sizeof(config.userScanOID));

    config.userScanOID.keep_previous_scan = 1u;
    config.userScanOID.bss_mode = ClxBSSType_Infrastructure;
    config.userScanOID.num_probes = numOfProbesPerChannel;

    config.userScanOID.scan_chan_gap = 0u;
    config.userScanOID.proberesp_only = 0u;

    for (u4 i = 0; i < numOfChannels_2_4GHz; i++)
    {
        setScanChannelInfo(&config.userScanOID.chan_list[index++], 
            channelList_2_4GHz[i],
            ClxWlanFreqBand2_4GHz,
            (scanType == ClxWlanActiveScan) ? TRUE : FALSE,
            scanDurationPerChannel);
    }

    for (u4 i = 0; i < numOfChannels_5GHz; i++)
    {
        setScanChannelInfo(&config.userScanOID.chan_list[index++],
            channelList_5GHz[i],
            ClxWlanFreqBand5GHz,
            (scanType == ClxWlanActiveScan) ? TRUE : FALSE,
            scanDurationPerChannel);
    }

    BLACKBOX_IF(index > CLX_MLAN_USER_SCAN_CHAN_MAX);

    clxMlanIniOidConfigParam(&config.userScanOID_ConfigParam,
        &config.userScanOID,
        CLX_CONFIG_TYPE(ClxMlanOID_UserScan),
        ClxMlanOidAction_SET,
        &config.parentList);

    ClxResult ret = clxWlanSetParametersValue(interfaceHandle, &config.parentList, TRUE);

    if ( (ret != CLX_SUCCESS) ||
         (!config.userScanOID_ConfigParam.paramInfo.processed) )
    {
        clxConsoleUIEngineText("MLAN : Setting scan channels failed with error %s\n", 
            clxGetWlanErrorCodeText(ret));
    }

    return ret;
}

ClxResult configureBgScanParameters_MLAN(ClxHandle interfaceHandle,
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
    u4 numberOfSsids)
{
    typedef struct Config_
    {
        ClxConfigList            parentList;
        ClxMlanOID_BgScanConfig  bgScanOID;
        ClxMlanOidConfigParam    bgScanOID_ConfigParam;
    }Config;

    static Config config;

    clxConfigInitParamsList(&config.parentList, NULL, NULL);

    u4 index = 0;

    u4 reportCondition = ((rssiThreshold != 0) ? CLX_MLAN_BG_SCAN_SSID_RSSI_MATCH : 0) |
        ((snrThreshold != 0) ? CLX_MLAN_BG_SCAN_SSID_SNR_MATCH : 0);

    if (reportCondition == 0)
    {
        reportCondition = CLX_MLAN_BG_SCAN_SSID_MATCH;
    }

    reportCondition |= CLX_MLAN_BG_SCAN_CONDITION_WAIT_ALL_CHAN_DONE;

    (void)memset(&config.bgScanOID, 0, sizeof(config.bgScanOID));

    config.bgScanOID.config_type = ClxMlanOID_BgScanConfigType_Normal;
    config.bgScanOID.bss_type = ClxBSSType_Infrastructure;
    config.bgScanOID.num_probes = numOfProbesPerChannel;
    config.bgScanOID.chan_per_scan = channelsPerScanInstance;
    config.bgScanOID.scan_interval = scanInterval;
    config.bgScanOID.report_condition = reportCondition;
    config.bgScanOID.rssi_threshold = rssiThreshold;
    config.bgScanOID.snr_threshold = snrThreshold;
    config.bgScanOID.repeat_count = repeatCount;
    config.bgScanOID.start_later = 0;

    for (u4 i = 0; i < MIN(numberOfSsids, CLX_MLAN_MRVDRV_MAX_SSID_LIST_LENGTH); i++)
    {
        memcpy(&config.bgScanOID.ssid_list[i], ssids + i, sizeof(ClxSSID));
    }

    for (u4 i = 0; i < numOfChannels_2_4GHz; i++)
    {
        setScanChannelInfo(&config.bgScanOID.chan_list[index++],
            channelList_2_4GHz[i],
            ClxWlanFreqBand2_4GHz,
            (scanType == ClxWlanActiveScan) ? TRUE : FALSE,
            scanDurationPerChannel);
    }

    for (u4 i = 0; i < numOfChannels_5GHz; i++)
    {
        setScanChannelInfo(&config.bgScanOID.chan_list[index++],
            channelList_5GHz[i],
            ClxWlanFreqBand5GHz,
            (scanType == ClxWlanActiveScan) ? TRUE : FALSE,
            scanDurationPerChannel);
    }

    BLACKBOX_IF(index > CLX_MLAN_USER_SCAN_CHAN_MAX);

    clxMlanIniOidConfigParam(&config.bgScanOID_ConfigParam,
        &config.bgScanOID,
        CLX_CONFIG_TYPE(ClxMlanOID_BgScanConfig),
        ClxMlanOidAction_SET,
        &config.parentList);

    ClxResult ret = clxWlanSetParametersValue(interfaceHandle, &config.parentList, TRUE);

    if ((ret != CLX_SUCCESS) ||
        (!config.bgScanOID_ConfigParam.paramInfo.processed))
    {
        clxConsoleUIEngineText("MLAN : Enabling backgrournd scan failed with error %s\n",
            clxGetWlanErrorCodeText(ret));
    }

    return ret;
}

ClxResult configureParameters_MLAN(ClxHandle interfaceHandle)
{
    typedef struct Config_
    {
        ClxConfigList            parentList;

        ClxMlanOID_CountryCode   countryCodeOID;

#if defined(CONFIG_BEAMFORMING)
        ClxMlanOID_BfGlobalCfg	 beamformingGlobalOID;
#endif

#ifdef CLX_NXP_POWER_TABLE_MANAGEMENT_SUPPORT_ENABLE
        ClxMlanOID_HostCmd       powerTableDataOID;
#endif

        ClxMlanOidConfigParam    countryCodeOID_ConfigParam;

#if defined(CONFIG_BEAMFORMING)
        ClxMlanOidConfigParam    beamformingGlobalOID_ConfigParam;
#endif

#ifdef CLX_NXP_POWER_TABLE_MANAGEMENT_SUPPORT_ENABLE
        ClxMlanOidConfigParam    powerTableData_ConfigParam;
#endif
    }Config;

    static Config config;

    clxConfigInitParamsList(&config.parentList, NULL, NULL);

    /* Set your country code for regulatory domain restrictions to take effect: */
    (void)memcpy(config.countryCodeOID.country_code, "AU", 3);

#if defined(CONFIG_BEAMFORMING)
    config.beamformingGlobalOID.bf_enbl = 0;
    config.beamformingGlobalOID.sounding_enbl = 0;
    config.beamformingGlobalOID.fb_type = 0;
    config.beamformingGlobalOID.snr_threshold = 0;
    config.beamformingGlobalOID.sounding_interval = 0;
    config.beamformingGlobalOID.bf_mode = 0;
#endif

#ifdef CLX_NXP_POWER_TABLE_MANAGEMENT_SUPPORT_ENABLE
    config.powerTableDataOID.data = mlanCustomPowerTable;
    config.powerTableDataOID.dataLength = sizeof(mlanCustomPowerTable);
#endif

    clxMlanIniOidConfigParam(&config.countryCodeOID_ConfigParam,
        &config.countryCodeOID,
        CLX_CONFIG_TYPE(ClxMlanOID_CountryCode),
        ClxMlanOidAction_SET,
        &config.parentList);

#if defined(CONFIG_BEAMFORMING)
    clxMlanIniOidConfigParam(&config.beamformingGlobalOID_ConfigParam,
        &config.beamformingGlobalOID,
        CLX_CONFIG_TYPE(ClxMlanOID_BfGlobalCfg),
        ClxMlanOidAction_SET,
        &config.parentList);
#endif

#ifdef CLX_NXP_POWER_TABLE_MANAGEMENT_SUPPORT_ENABLE
    clxMlanIniOidConfigParam(&config.powerTableData_ConfigParam,
        &config.powerTableDataOID,
        CLX_CONFIG_TYPE(ClxMlanOID_HostCmd),
        ClxMlanOidAction_SET,
        &config.parentList);
#endif

    ClxResult ret = clxWlanSetParametersValue(interfaceHandle, &config.parentList, TRUE);

    if (ret == CLX_SUCCESS)
    {
        if (!config.countryCodeOID_ConfigParam.paramInfo.processed)
        {
            clxConsoleUIEngineText("NXP: Setting country code failed\n");
        }

#if defined(CONFIG_BEAMFORMING)
        if (!config.beamformingGlobalOID_ConfigParam.paramInfo.processed)
        {
            clxConsoleUIEngineText("NXP: Setting Beamforming parameters failed\n");
        }
#endif

#ifdef CLX_NXP_POWER_TABLE_MANAGEMENT_SUPPORT_ENABLE
        if (!config.powerTableData_ConfigParam.paramInfo.processed)
        {
            clxConsoleUIEngineText("Marvell : Setting Custom power table failed\n");
        }
#endif
    }

    return ret;
}

ClxResult getConnectionTempSensorInfo_MLAN(ClxHandle interfaceHandle)
{
    struct TempConfig
    {
        ClxConfigList                       parentList;
        
        ClxMlanOID_TempSensor               getTempSensorOID;
        ClxMlanOidConfigParam               getTempSensorOID_ConfigParam;
    };
    
    struct TempConfig tempConfig;
    
    clxConfigInitParamsList(&tempConfig.parentList, NULL, NULL);

    memset(&tempConfig.getTempSensorOID, 0, sizeof(tempConfig.getTempSensorOID));
    
    clxMlanIniOidConfigParam(&tempConfig.getTempSensorOID_ConfigParam,
                             &tempConfig.getTempSensorOID_ConfigParam,
                             CLX_CONFIG_TYPE(ClxMlanOID_TempSensor),
                             ClxMlanOidAction_GET,
                             &tempConfig.parentList);
    
    ClxResult ret = clxWlanGetParametersValue(interfaceHandle, &tempConfig.parentList, TRUE);
    
    if ((ret != CLX_SUCCESS) || (tempConfig.getTempSensorOID_ConfigParam.paramInfo.processed == FALSE))
    {
        clxConsoleUIEngineText("Retrieving the Signal information failed\n");
        return CLX_FAIL;
    }
    else
    {
        clxConsoleUIEngineText("WLAN module temperature : %d\n", tempConfig.getTempSensorOID.temperature);
    }

    return CLX_SUCCESS;
}

s2 getConnectionAverageMgmtRSSI_MLAN(ClxHandle interfaceHandle)
{
    struct Config
    {
        ClxConfigList                       parentList;

        ClxMlanOID_Signal                   getSignalOID;
        ClxMlanOidConfigParam               getSignalOID_ConfigParam;
    };

    struct Config config;

    clxConfigInitParamsList(&config.parentList, NULL, NULL);

    memset(&config.getSignalOID, 0, sizeof(config.getSignalOID));

    clxMlanIniOidConfigParam(&config.getSignalOID_ConfigParam,
                             &config.getSignalOID,
                             (void*)CLX_CONFIG_TYPE(ClxMlanOID_Signal),
                             ClxMlanOidAction_GET,
                             &config.parentList);

    ClxResult ret = clxWlanGetParametersValue(interfaceHandle, &config.parentList, TRUE);
    s2 avgRSSI = 0;

    if ((ret != CLX_SUCCESS) || (config.getSignalOID_ConfigParam.paramInfo.processed == FALSE)) {
        clxConsoleUIEngineText("Retriving the Signal information failed\n");
    } else if (config.getSignalOID.selector & CLX_MLAN_BCN_RSSI_AVG_MASK) {
        avgRSSI = config.getSignalOID.bcn_rssi_avg;
        clxConsoleUIEngineText("Average Beacon RSSI : %d dBm\n", avgRSSI);
    }

    return avgRSSI;
}

ClxResult getConnectionSignalInfo_MLAN(ClxHandle interfaceHandle)
{
    struct Config
    {
        ClxConfigList                       parentList;

        ClxMlanOID_Signal                   getSignalOID;
        ClxMlanOidConfigParam               getSignalOID_ConfigParam;
    };

    struct Config config;

    clxConfigInitParamsList(&config.parentList, NULL, NULL);

    memset(&config.getSignalOID, 0, sizeof(config.getSignalOID));

    clxMlanIniOidConfigParam(&config.getSignalOID_ConfigParam,
                             &config.getSignalOID_ConfigParam,
                             CLX_CONFIG_TYPE(ClxMlanOID_Signal),
                             ClxMlanOidAction_GET,
                             &config.parentList);

    ClxResult ret = clxWlanGetParametersValue(interfaceHandle, &config.parentList, TRUE);

    if ((ret != CLX_SUCCESS) || (config.getSignalOID_ConfigParam.paramInfo.processed == FALSE))
    {
        clxConsoleUIEngineText("Retriving the Signal information failed\n");
        return CLX_FAIL;
    }

    if (config.getSignalOID.selector & CLX_MLAN_BCN_RSSI_LAST_MASK)
    {
        clxConsoleUIEngineText("Last Beacon RSSI : %d dBm\n", config.getSignalOID.bcn_rssi_last);
    }

    if (config.getSignalOID.selector & CLX_MLAN_BCN_RSSI_AVG_MASK)
    {
        clxConsoleUIEngineText("Average Beacon RSSI : %d dBm\n", config.getSignalOID.bcn_rssi_avg);
    }

    if (config.getSignalOID.selector & CLX_MLAN_DATA_RSSI_LAST_MASK)
    {
        clxConsoleUIEngineText("Last Data RSSI : %d dBm\n", config.getSignalOID.data_rssi_last);
    }

    if (config.getSignalOID.selector & CLX_MLAN_DATA_RSSI_AVG_MASK)
    {
        clxConsoleUIEngineText("Average Data RSSI : %d dBm\n", config.getSignalOID.data_rssi_avg);
    }

	return CLX_SUCCESS;
}

ClxResult getConnectionStatInfo_MLAN(ClxHandle interfaceHandle)
{
    struct Config
    {
        ClxConfigList                       parentList;

        ClxMlanOID_Stats                    getStatOID;
        ClxMlanOidConfigParam               getStatOID_ConfigParam;
    };

    struct Config config2;

    clxConfigInitParamsList(&config2.parentList, NULL, NULL);

    memset(&config2.getStatOID, 0, sizeof(config2.getStatOID));

    clxMlanIniOidConfigParam(&config2.getStatOID_ConfigParam,
                             &config2.getStatOID_ConfigParam,
                             CLX_CONFIG_TYPE(ClxMlanOID_Stats),
                             ClxMlanOidAction_GET,
                             &config2.parentList);

    ClxResult ret = clxWlanGetParametersValue(interfaceHandle, &config2.parentList, TRUE);

    if ((ret != CLX_SUCCESS) || (config2.getStatOID_ConfigParam.paramInfo.processed == FALSE))
    {
        clxConsoleUIEngineText("Retrieving the statistics information failed\n");
        return CLX_FAIL;
    }

        clxConsoleUIEngineText("Multicast transmitted frame count  : %d \n", config2.getStatOID.mcast_tx_frame);
        clxConsoleUIEngineText("Multicast received frame count  : %d\n", config2.getStatOID.mcast_rx_frame);

    return CLX_SUCCESS;
}

void setConfigFtmSession_MLAN(ClxHandle staHandle)
{
    static s1 inputBuf[32];

    struct Config
    {
        ClxConfigList               parentList;

        ClxMlanOID_RTTConfigParams  rttConfigParamsOID;
        ClxMlanOidConfigParam       rttConfigParamsOID_ConfigParam;
    };

    struct Config config;

    clxConfigInitParamsList(&config.parentList, NULL, NULL);

    clxMemSet(&config.rttConfigParamsOID, 0, sizeof(config.rttConfigParamsOID));

    clxConsoleUIEngineInputBox("Burst Exponent: ", inputBuf, sizeof(inputBuf));
    config.rttConfigParamsOID.burst_exponent = clxAsciiToInteger(inputBuf);

    clxConsoleUIEngineInputBox("Burst Duration: ", inputBuf, sizeof(inputBuf));
    config.rttConfigParamsOID.burst_duration = (ClxWlanRTTBurstDuration)clxAsciiToInteger(inputBuf);

    clxConsoleUIEngineInputBox("Min Delta FTM: ", inputBuf, sizeof(inputBuf));
    config.rttConfigParamsOID.min_delta_ftm = clxAsciiToInteger(inputBuf);

    clxConsoleUIEngineInputBox("FTMs per Burst: ", inputBuf, sizeof(inputBuf));
    config.rttConfigParamsOID.ftms_per_burst = clxAsciiToInteger(inputBuf);

    clxConsoleUIEngineInputBox("Channel Spacing: ", inputBuf, sizeof(inputBuf));
    config.rttConfigParamsOID.chan_spacing = (ClxWlanRTTFormatAndBandwidth)clxAsciiToInteger(inputBuf);

    clxConsoleUIEngineInputBox("Burst Period (in 100 milliseconds): ", inputBuf, sizeof(inputBuf));
    config.rttConfigParamsOID.burst_period = clxAsciiToInteger(inputBuf);

    config.rttConfigParamsOID.asap = 1;
    config.rttConfigParamsOID.civic_req = 0;
#if defined(CLX_FLOATING_POINT_SUPPORTED)
    config.rttConfigParamsOID.lci_req = 0;
#endif

    clxMlanIniOidConfigParam(&config.rttConfigParamsOID_ConfigParam,
        &config.rttConfigParamsOID,
        CLX_CONFIG_TYPE(ClxMlanOID_RTTConfigParams),
        ClxMlanOidAction_SET,
        &config.parentList);

    ClxResult ret = clxWlanSetParametersValue(staHandle, &config.parentList, TRUE);
    if ((ret != CLX_SUCCESS) || (config.rttConfigParamsOID_ConfigParam.paramInfo.processed == FALSE))
    {
        clxConsoleUIEngineText("clxWlanSetParametersValue() failed with error %s", clxGetWlanErrorCodeText(ret));
    }
}

void startStopFtmSession_MLAN(ClxHandle staHandle, boolean start)
{
    struct Config
    {
        ClxConfigList                       parentList;

        ClxMlanOID_RTTSessionControl        rttSessionControlOID;
        ClxMlanOidConfigParam               rttSessionControlOID_ConfigParam;
    };

    struct Config config;

    ClxDiscoveredBss* bss = NULL;

    clxConfigInitParamsList(&config.parentList, NULL, NULL);

    clxMemSet(&config.rttSessionControlOID, 0, sizeof(config.rttSessionControlOID));

    s4 bssIndex = clxWlanScanSelectDiscoveredBSS(staHandle);

    if (bssIndex >= 0)
    {
        bss = clxWlanScanGetDiscoveredBSSByIndex((u4)bssIndex);
        CLX_ASSERT(bss);
        clxMemCpy(config.rttSessionControlOID.peer_addr, bss->base.macAddress, sizeof(bss->base.macAddress));
        config.rttSessionControlOID.channel = (u1)bss->primaryChannel;
    }

    clxMlanIniOidConfigParam(&config.rttSessionControlOID_ConfigParam,
        &config.rttSessionControlOID,
        start ? CLX_CONFIG_TYPE(ClxMlanOID_StartRTTSession) : CLX_CONFIG_TYPE(ClxMlanOID_StopRTTSession),
        ClxMlanOidAction_SET,
        &config.parentList);

    ClxResult ret = clxWlanSetParametersValue(staHandle, &config.parentList, TRUE);
    if ((ret != CLX_SUCCESS) || (config.rttSessionControlOID_ConfigParam.paramInfo.processed == FALSE))
    {
        clxConsoleUIEngineText("clxWlanSetParametersValue() failed with error %s", clxGetWlanErrorCodeText(ret));
    }
}

void driverSpecificReport_MLAN(ClxWlanDriverSpecificIndication* arg)
{
    if (arg->type == CLX_CONFIG_TYPE(ClxMlanOID_RTTCompleteIndication))
    {
        ClxMlanOID_RTTCompleteIndication* rttCompleteIndication = (ClxMlanOID_RTTCompleteIndication*)arg;

        clxConsoleUIEngineText("\nFTM Complete Event:\n");

        clxConsoleUIEngineText("\n    Mac Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
            rttCompleteIndication->peer_addr[0],
            rttCompleteIndication->peer_addr[1],
            rttCompleteIndication->peer_addr[2],
            rttCompleteIndication->peer_addr[3],
            rttCompleteIndication->peer_addr[4],
            rttCompleteIndication->peer_addr[5]);

        clxConsoleUIEngineText("    Average RTT: %u\n", rttCompleteIndication->avg_rtt);
        clxConsoleUIEngineText("    Average Clock Offset: %u ps\n", rttCompleteIndication->avg_clk_offset);
        clxConsoleUIEngineText("    Measurement Start Timestamp (TSF): %u\n", rttCompleteIndication->meas_start_tsf);
    
        /* 
        clock offset is in pico seconds, distance should be in meters.
        (Half of the value is the single-way time offset, and assuming the speed of wave propagation is 3x(10^8) m/s):
        */
        clxConsoleUIEngineText("    Distance: %.01f m\n\n", rttCompleteIndication->avg_clk_offset / 2 * 0.0003);
    }
}

// Define the driver operations for MLAN
const DriverOps mlanOps = {
    .configureScanParameters = configureScanParameters_MLAN,
    .configureParameters = configureParameters_MLAN,
    .getConnectionTempSensorInfo = getConnectionTempSensorInfo_MLAN,
    .getConnectionAverageMgmtRSSI = getConnectionAverageMgmtRSSI_MLAN,
    .getConnectionStatInfo = getConnectionStatInfo_MLAN,
    .getConnectionSignalInfo = getConnectionSignalInfo_MLAN,
    .configureBgScanParameters = configureBgScanParameters_MLAN,
    .setConfigFtmSession = setConfigFtmSession_MLAN,
    .startStopFtmSession = startStopFtmSession_MLAN,
    .driverSpecificReport = driverSpecificReport_MLAN
};

const DriverOps* GetDriverOps(void) {
    return &mlanOps;
}
