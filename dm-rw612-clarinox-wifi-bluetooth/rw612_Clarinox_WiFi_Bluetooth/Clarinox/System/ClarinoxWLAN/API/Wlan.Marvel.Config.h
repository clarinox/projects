#ifndef Wlan_Marvel_Config_h
#define Wlan_Marvel_Config_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                Wlan.Marvel.Config.h
* Description         Declares Marvel WLAN controller configuration parameters
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

   

/**
Represents the base struct of a configuration parameter for the Marvel driver. 

Marvell driver supports taking three different actions on an OID parameter. However, all three actions may not be supported for all OID parameters :

- SET : Set a new value for an OID parameter in the driver/firmware.
        The object shall be passed to #clxWlanSetParametersValue().

- GET : Get the current value of the OID parameter from the driver/firmware.
        The object shall be passed to #clxWlanGetParametersValue(). Upon a successful completion, the object will contain the current value of OID.

- DELETE : Remove the current value of an OID parameter from the driver/firmware.
        The object shall be passed to #clxWlanSetParametersValue().

NOTE : configuration parameters of this type may not be passed to #clxWlanStartInterface().
*/
typedef ClxConfigValue ClxMlanOidConfigParam;



/** Mask of last beacon RSSI */
#define CLX_MLAN_BCN_RSSI_LAST_MASK              0x00000001
/** Mask of average beacon RSSI */
#define CLX_MLAN_BCN_RSSI_AVG_MASK               0x00000002
/** Mask of last data RSSI */
#define CLX_MLAN_DATA_RSSI_LAST_MASK             0x00000004
/** Mask of average data RSSI */
#define CLX_MLAN_DATA_RSSI_AVG_MASK              0x00000008
/** Mask of last beacon SNR */
#define CLX_MLAN_BCN_SNR_LAST_MASK               0x00000010
/** Mask of average beacon SNR */
#define CLX_MLAN_BCN_SNR_AVG_MASK                0x00000020
/** Mask of last data SNR */
#define CLX_MLAN_DATA_SNR_LAST_MASK              0x00000040
/** Mask of average data SNR */
#define CLX_MLAN_DATA_SNR_AVG_MASK               0x00000080
/** Mask of last beacon NF */
#define CLX_MLAN_BCN_NF_LAST_MASK                0x00000100
/** Mask of average beacon NF */
#define CLX_MLAN_BCN_NF_AVG_MASK                 0x00000200
/** Mask of last data NF */
#define CLX_MLAN_DATA_NF_LAST_MASK               0x00000400
/** Mask of average data NF */
#define CLX_MLAN_DATA_NF_AVG_MASK                0x00000800
/** Mask of all RSSI_INFO */
#define CLX_MLAN_ALL_RSSI_INFO_MASK              0x00000fff
#define CLX_MLAN_MAX_PATH_NUM                    3
/** path A */
#define CLX_MLAN_PATH_A                         0x01
/** path B */
#define CLX_MLAN_PATH_B                         0x02
/** path AB */
#define CLX_MLAN_PATH_AB                        0x03
/** ALL the path */
#define CLX_MLAN_PATH_ALL                       0


/** MLAN 802.11 MAC Address */
typedef u1 mlan80211_mac_addr[CLX_MAC_ADDRESS_LENGTH];

/** Macro for identifying automatic channel selection */

#define CLX_MLAN_ACS_CHANNEL   0U

/** 
Type definition of ClxMlanOID_Signal.
Supports GET action 
*/
typedef struct ClxMlanOID_SignalStruct 
{  
    /** Selector of get operation */
    /*
     * Bit0:  Last Beacon RSSI,  Bit1:  Average Beacon RSSI,
     * Bit2:  Last Data RSSI,    Bit3:  Average Data RSSI,
     * Bit4:  Last Beacon SNR,   Bit5:  Average Beacon SNR,
     * Bit6:  Last Data SNR,     Bit7:  Average Data SNR,
     * Bit8:  Last Beacon NF,    Bit9:  Average Beacon NF,
     * Bit10: Last Data NF,      Bit11: Average Data NF
     *
     * Bit0: PATH A
     * Bit1: PATH B
     */
    u2 selector;

    /** RSSI */
    /** RSSI of last beacon */
    s2 bcn_rssi_last;
    /** RSSI of beacon average */
    s2 bcn_rssi_avg;
    /** RSSI of last data packet */
    s2 data_rssi_last;
    /** RSSI of data packet average */
    s2 data_rssi_avg;

    /** SNR */
    /** SNR of last beacon */
    s2 bcn_snr_last;
    /** SNR of beacon average */
    s2 bcn_snr_avg;
    /** SNR of last data packet */
    s2 data_snr_last;
    /** SNR of data packet average */
    s2 data_snr_avg;

    /** NF */
    /** NF of last beacon */
    s2 bcn_nf_last;
    /** NF of beacon average */
    s2 bcn_nf_avg;
    /** NF of last data packet */
    s2 data_nf_last;
    /** NF of data packet average */
    s2 data_nf_avg;
} ClxMlanOID_Signal;


/**
Type definition of ClxMlanOID_Stats.
Supports GET action
*/
typedef struct ClxMlanOID_StatsStruct
{
    /** Statistics counter */
    /** Multicast transmitted frame count */
    u4 mcast_tx_frame;
    /** Failure count */
    u4 failed;
    /** Retry count */
    u4 retry;
    /** Multi entry count */
    u4 multi_retry;
    /** Duplicate frame count */
    u4 frame_dup;
    /** RTS success count */
    u4 rts_success;
    /** RTS failure count */
    u4 rts_failure;
    /** Ack failure count */
    u4 ack_failure;
    /** Rx fragmentation count */
    u4 rx_frag;
    /** Multicast Tx frame count */
    u4 mcast_rx_frame;
    /** FCS error count */
    u4 fcs_error;
    /** Tx frame count */
    u4 tx_frame;
    /** WEP ICV error count */
    u4 wep_icv_error;
    /* statistics when the local device is in STA role. Must be ignored in other roles */
    struct STA
    {
        /** beacon recv count */
        u4 bcn_rcv_cnt;
        /** beacon miss count */
        u4 bcn_miss_cnt;
    } sta;
} ClxMlanOID_Stats;


typedef enum ClxMlanChannelBandwidthEnum
{
    ClxMlanChannelBandwidth_20Mhz = 0x0,
    ClxMlanChannelBandwidth_40Mhz = 0x1,
    ClxMlanChannelBandwidth_80Mhz = 0x2,
    ClxMlanChannelBandwidth_160Mhz = 0x3
} ClxMlanChannelBandwidth;


typedef enum ClxMlanIEEE802_11nGuartIntervalEnum
{
    ClxMlanIEEE802_11nGuartInterval_Long = 0x0,
    ClxMlanIEEE802_11nGuartInterval_Short = 0x1
} ClxMlanIEEE802_11nGuartInterval;


typedef enum ClxMlanRateFormatEnum
{
    ClxMlanRateFormat_NonHT = 0x0,      /* Legacy (IEEE802.11abg) rate */
    ClxMlanRateFormat_HT = 0x1,         /* IEEE802.11n rate */
    ClxMlanRateFormat_VHT = 0x2         /* IEEE802.11ac rate */
} ClxMlanRateFormat;


typedef struct ClxMlanOID_DataRateStruct {
    /** Tx data rate multiplied by two (e.g. tx_data_rate = 130 means 65 Mbps) */
    u4 tx_data_rate;
    /** Rx data rate multiplied by two (e.g. rx_data_rate = 130 means 65 Mbps) */
    u4 rx_data_rate;
    /** Tx channel bandwidth */
    ClxMlanChannelBandwidth tx_ht_bw;
    /** Tx guard interval */
    ClxMlanIEEE802_11nGuartInterval tx_ht_gi;
    /** Rx channel bandwidth */
    ClxMlanChannelBandwidth rx_ht_bw;
    /** Rx guard interval */
    ClxMlanIEEE802_11nGuartInterval rx_ht_gi;
    /** TX MCS index */
    u4 tx_mcs_index;
    /** RX MCS index */
    u4 rx_mcs_index;
    /** Number of TX Spatial Streams for IEEE802.11ac */
    u4 tx_nss;
    /** Number of RX Spatial Streams for IEEE802.11ac */
    u4 rx_nss;
    /** TX Rate Format */
    ClxMlanRateFormat tx_rate_format;
    /** RX Rate Format */
    ClxMlanRateFormat rx_rate_format;
} ClxMlanOID_DataRate;


/**
Type definition of ClxMlanOID_TempSensor.
Supports GET action
*/
typedef struct ClxMlanOID_TempSensorStruct
{
    /** Temperature */
    s4 temperature;
} ClxMlanOID_TempSensor;

/**
Type definition of ClxMlanOID_FwInfo.
Supports GET action
*/
typedef struct ClxMlanOID_FwInfoStruct
{
    /** Firmware version */
    u4 fw_ver;
    /** HW Interface version number */
    u2 hw_if_version;
    /** HW version number */
    u2 hw_version;
    /** MAC address */
    mlan80211_mac_addr mac_addr;
    /** 802.11n device capabilities */
    u4 hw_dot_11n_dev_cap;
    /** Device support for MIMO abstraction of MCSs */
    u1 hw_dev_mcs_support;
    /** 802.11ac device capabilities */
    u4 hw_dot_11ac_dev_cap;
    /** 802.11ac device support for MIMO abstraction of MCSs */
    u4 hw_dot_11ac_mcs_support;
    /** Firmware capability information */
    u4 fw_cap_info;
    /** region code */
    u2 region_code;
    /** Number of Antennas */
    u2 number_of_antenna;
    /** End port number valid with current buffer setting for Multi-port enabled SDIO */
    u2  mp_end_port;
    /** Number of management IE buffers */
    u2  mgmt_buf_count;
    /** Max no of Multicast address  */
    u2 num_of_mcast_adr;
} ClxMlanOID_FwInfo;


/** Maximum number of channels that can be sent in user scan config */
#define CLX_MLAN_USER_SCAN_CHAN_MAX                  50

/** Maximum number of channels that can be sent in background scan config */
#define CLX_MLAN_BG_SCAN_CHAN_MAX                    41

/** Maximum length of SSID list */
#define CLX_MLAN_MRVDRV_MAX_SSID_LIST_LENGTH         10



/**
 *  @brief IOCTL channel sub-structure sent in ClxMlanConfig_UserScan
 *
 *  Multiple instances of this structure are included in the IOCTL command
 *   to configure a instance of a scan on the specific channel.
 */
typedef struct ClxMlanOID_UserScanChannelStruct 
{
    /** Channel Number to scan */
    u1 chan_number;
    /** Radio type: 'B/G' Band = 0, 'A' Band = 1 */
    u1 radio_type;
    /** Scan type: Active = 1, Passive = 2 */
    u1 scan_type;
    /** Scan duration in milliseconds; if 0 default used */
    u4 scan_time;
} ClxMlanOID_UserScanChannel;


/**
 *  Input structure to configure User Scan parameters
 *
 *  Specifies a number of parameters to be used in general for the scan
 *    as well as a channel list (ClxMlanConfig_UserScanChannel) for each scan period
 *    desired.
 *
 *  Supports SET, GET, and DELETE actions 
 */
typedef struct ClxMlanOID_UserScanStruct
{  
    /**
     *  Flag set to keep the previous scan table intact
     *
     *  If set, the scan results will accumulate, replacing any previous
     *   matched entries for a BSS with the new scan data
     */
    u1 keep_previous_scan;
    /**
     *  BSS mode to be sent in the firmware command
     *
     *  Field can be used to restrict the types of networks returned in the
     *    scan.  Valid settings are:
     *
     *   - ClxBSSType_Infrastructure  (infrastructure)
     *   - ClxBSSType_Independent (adhoc)
     *   - ClxBSSType_AnyType  (unrestricted, adhoc and infrastructure)
     */
    ClxBSSType bss_mode;
    /**
     *  Configure the number of probe requests for active chan scans
     */
    u1 num_probes;
    /**
     *  Variable number (fixed maximum) of channels to scan up
     */
    ClxMlanOID_UserScanChannel chan_list[CLX_MLAN_USER_SCAN_CHAN_MAX];
    /** scan channel gap */
    u2 scan_chan_gap;
    /** flag to filer only probe response */
    u1 proberesp_only;
} ClxMlanOID_UserScan;


/** Type definition of mlan_ds_misc_country_code
 *  for MLAN_OID_MISC_COUNTRY_CODE
 *
 *  Supports SET, and GET actions.
 */
typedef struct ClxMlanOID_CountryCodeStruct 
{ 
    /**
     * Country Code
     *
     *  Possible country code string values that can be assigned.
     *
     *  "US"    US FCC
     *  "CA"    IC Canada
     *  "SG"    Singapore
     *  "EU"    ETSI
     *  "AU"    Australia
     *  "KR"    Republic Of Korea
     *  "JP"    Japan
     *  "CN"    China
     *  "BR"    Brazil
     *  "RU"    Russia
     *  "IN"    India
     *  "MY"    Malaysia
     *
     *  For ETSI or EU region, the specific country codes can also be used, i.e.
     *  "AL", "AD", "AT", "AU", "BY", "BE", "BA", "BG", "HR", "CY", "CZ", "DK",
     *  "EE", "FI", "FR", "MK", "DE", "GR", "HU", "IS", "IE", "IT", "KR", "LV",
     *  "LI", "LT", "LU", "MT", "MD", "MC", "ME", "NL", "NO", "PL", "RO", "RU",
     *  "SM", "RS", "SI", "SK", "ES", "SE", "CH", "TR", "UA", "UK", "GB".
     */
    u1 country_code[CLX_WLAN_COUNTRY_CODE_LEN];
} ClxMlanOID_CountryCode;


#define CLX_MLAN_MAX_SUBBAND_802_11D        83

/** Data structure for subband set */
typedef struct ClxMlanSubbandsetStruct {
    /** First channel */
    u1 first_chan;
    /** Number of channels */
    u1 no_of_chan;
    /** Maximum Tx power in dBm */
    u1 max_tx_pwr;
} ClxMlanSubbandset;

/**
 *  Input structure to configure user defined channel frequency power table
 *
 *  Supports SET action.
 */
typedef struct ClxMlanOID_CfpTableStruct
{
    /** Country Code */
    u1 country_code[CLX_WLAN_COUNTRY_CODE_LEN];
    /** No. of subband in below */
    u1 no_of_sub_band;
    /** Subband data to send */
    ClxMlanSubbandset sub_band[CLX_MLAN_MAX_SUBBAND_802_11D];
} ClxMlanOID_CfpTable;


/**
 *  Input structure to configure host sleep mode
 *
 *  Supports SET action.
 */
typedef struct ClxMlanOID_HsCfgStruct
{
    /** Host sleep config condition */
    /** Bit0: broadcast data
     *  Bit1: unicast data
     *  Bit2: mac event
     *  Bit3: multicast data
     */
    u4 conditions;

    /** GPIO pin or 0xff for interface */
    u4 gpio;

    /** Gap in milliseconds or or 0xff for special
     *  setting when GPIO is used to wakeup host
     */
    u4 gap;

    /** Host sleep wake interval */
    u4 hs_wake_interval;

    /** Parameter type for indication gpio*/
    u1 param_type_ind;

    /** GPIO pin for indication wakeup source */
    u4 ind_gpio;

    /** Level on ind_gpio pin for indication normal wakeup source */
    u4 level;

    /** Parameter type for extend hscfg*/
    u1 param_type_ext;

    /** Events that will be forced ignore*/
    u4 event_force_ignore;

    /** Events that will use extend gap to inform host*/
    u4 event_use_ext_gap;

    /** Ext gap*/
    u1 ext_gap;

    /** GPIO wave level for extend hscfg*/
    u1 gpio_wave;
} ClxMlanOID_HsCfg;



/**
 *  Input structure to configure Beamforming
 *
 *  Supports SET action.
 */
typedef struct ClxMlanOID_BfGlobalCfgStruct 
{
    /** Global enable/disable bf */
    u1 bf_enbl;
    /** Global enable/disable sounding */
    u1 sounding_enbl;
    /** FB Type */
    u1 fb_type;
    /** SNR Threshold */
    u1 snr_threshold;
    /** Sounding interval in milliseconds */
    u2 sounding_interval;
    /** BF mode */
    u1 bf_mode;
} ClxMlanOID_BfGlobalCfg;




#define CLX_MLAN_BG_SCAN_SSID_MATCH                                 0x00000001      /** Background scan report condition flag : ssid match */
#define CLX_MLAN_BG_SCAN_SSID_SNR_MATCH                             0x00000002      /** Background scan report condition flag : ssid match and SNR exceeded */
#define CLX_MLAN_BG_SCAN_SSID_RSSI_MATCH                            0x00000004      /** Background scan report condition flag : ssid match and RSSI exceeded */
#define CLX_MLAN_BG_SCAN_CONDITION_WAIT_ALL_CHAN_DONE               0x80000000      /** Background scan report condition flag : wait for all channel scan to complete 
                                                                                        to report scan result */


/**
 *  Configuration type to set in the firmware for background scan.
 */
typedef enum ClxMlanOID_BgScanConfigTypeEnum
{
    ClxMlanOID_BgScanConfigType_Normal = 0x0001,            /** non U-APSD mode config */
    ClxMlanOID_BgScanConfigType_UAPSD = 0x0101,             /** U-APSD (Unscheduled Automatic Power Save Delivery) mode config */
    ClxMlanOID_BgScanConfigType_All = 0xff01                /** all configs */
} ClxMlanOID_BgScanConfigType;
        
        
/**
Input structure to configure background scan parameters.

Supports SET, GET, and DELETE actions

Background Scan Details:

Assume there is a total of T channels to scan in one scan session, as follows:

----------------------------------------------------------------------------------         -------------------------------------------
| Scan instance 1 (n channels) |   ScanInterval  | Scan instance 2 (n channels) |   ...    | Last scan instance (remaining channels) |
----------------------------------------------------------------------------------         -------------------------------------------
<---------------------------------------------------------- One scan session --------------------------------------------------------->

Within each scan instance, n channels are scanned (except for the last instance in the scan session in which fewer channels may be scanned). 

One scan session may be repeated N times, or forever (needs to be stopped explicitly by the application), or until an error occurs.

Before starting the BG scan, the BG scan configuration parameters must be passed to the NXP driver. The configuration parameter is of type ClxMlanOID_BgScanConfig (defined in Wlan.Marvel.Config.h). 
Initialize the entire ClxMlanOID_BgScanConfig  object with zero before assigning values to the members. The following members are defined:

    config_type :       Set it ClxMlanOID_BgScanConfigType_Normal.
    bss_type :          Set it to ClxBSSType_Infrastructure.
    chan_per_scan :     Number of channels scanned in each instance. This is the value 'n' in the diagram above.
    scan_interval :     Interval between consecutive scan instances in milliseconds. This is the value 'ScanInterval' in the diagram above.
    report_condition :  may be a logical combination of the following flag bit definitions (at least one bit must be set):

        CLX_MLAN_BG_SCAN_SSID_MATCH :                   ssid match bit
        CLX_MLAN_BG_SCAN_SSID_SNR_MATCH :               ssid match and SNR exceeded
        CLX_MLAN_BG_SCAN_SSID_RSSI_MATCH :              ssid match and RSSI exceeded

        In addition, the following flag bit may be also be set:

        CLX_MLAN_BG_SCAN_CONDITION_WAIT_ALL_CHAN_DONE : Wait for the scan session to complete to report scan results.
                                                        When present, the NXP firmware is requested to wait until the end of the current scan session to publish the list of matched BSSs (if any)

     num_probes :       Number of probes sent on each channel (in case of active scan).
     rssi_threshold :   The RSSI threshold. Applicable only if the condition  CLX_MLAN_BG_SCAN_SSID_RSSI_MATCH  has been set. This is an unsigned 1-byte value in dBm. The actual RSSI is simply the negative of the unsigned value passed. 
                        For example, for the RSSI threshold of -65 dBm, simply set the value of this member to 65 (do NOT do two's complement conversion).
     snr_threshold :    The SNR threshold. Applicable only if the condition  CLX_MLAN_BG_SCAN_SSID_SNR_MATCH  has been set. This is a positive 1-byte value in dB.
     repeat_count :     Number of times to repeat the scan session. This is the value 'N' mentioned above. A value of 0 means 'scan until stopped by the application or an error occurs'.
     start_later :      0 = start background scan immediately, 1 = start background scan after 'scan_interval' milliseconds
     ssid_list :        List of up to #CLX_MLAN_MRVDRV_MAX_SSID_LIST_LENGTH SSIDs to scan for.
     chan_list :        List of channels to scan in a single scan session. This is the value 'T' mentioned above. 
                        Up to #CLX_MLAN_BG_SCAN_CHAN_MAX channels may be defined. Each channel is described by an object of type ClxMlanOID_UserScanChannel.

NOTE: The list of channels are independent of the channels set for normal scan (e.g. via ClxMlanOID_UserScan configuration parameter).

BG scan is considered complete when one of the following occurs.

    - One or more BSSs are discovered which match one of the report conditions.
    - No BSS with a matched condition is found and 'repeat_count' number of scan sessions have been carried out  (only if repeat_count is not zero).
    - An error occurs.

BG scan may be started by a call to clxWlanStartBgScan(). It has the following argument:

    enableAutoRestart : If FALSE, when the BS scan is considered complete (based on the above criteria), an indication of type CLX_WLAN_BG_SCAN_TERMINATION_INDICATION is sent to the application.
                        If TRUE, when the BS scan is complete (except for the case when an error has occurred), the WLAN stack automatically restarts the BG scan with the very same configuration parameters.

Regardless of the value of "enableAutoRestart", the ongoing BG scan may be stopped at any time by a call to clxWlanStopBgScan().

NOTE : If there is a need to change the BG configuration parameters at any time, the ongoing BG scan must be stopped by a call to clxWlanStopBgScan() first before an attempt to pass a new set of configuration parameters to the driver. 
       Otherwise, the behaviour will be undefined.
NOTE : When there is an ongoing BG scan, normal scan cannot be performed. This means, a connection attempt is not possible when BG scan is ongoing (since the connection procedure involves a normal scan internally). 
       BG scan needs to be stopped before trying to connect to an AP. However, it is OK to disconnect from an AP when BG scan is ongoing.
*/
typedef struct ClxMlanOID_BgScanConfigStruct 
{
    /**
     * Type of Background scan configuration to set in the firmware.
     */
    ClxMlanOID_BgScanConfigType config_type;

    /**  BSS type:
     *   - ClxBSSType_Infrastructure  (infrastructure)
     *   - ClxBSSType_Independent     (adhoc)
     *   - ClxBSSType_AnyType         (unrestricted, adhoc and infrastructure)
     */
    ClxBSSType bss_type;
    /** number of channel scanned during each scan */
    u1 chan_per_scan;
    /** interval between consecutive scan in milliseconds */
    u4 scan_interval;
    /** CLX_MLAN_BG_SCAN_SSID_MATCH                     : ssid match bit 
     *  CLX_MLAN_BG_SCAN_SSID_SNR_MATCH                 : ssid match and SNR exceeded
     *  CLX_MLAN_BG_SCAN_SSID_RSSI_MATCH                : ssid match and RSSI exceeded
     *  CLX_MLAN_BG_SCAN_CONDITION_WAIT_ALL_CHAN_DONE   : wait for all channel scan to complete to report scan result
     */
    u4 report_condition;
    /*  Configure the number of probe requests for active chan scans */
    u1 num_probes;
    /** RSSI threshold */
    u1 rssi_threshold;
    /** SNR threshold */
    u1 snr_threshold;
    /** repeat count. Set to 0 for continuous background scan (until it is disabled) */
    u2 repeat_count;
    /** 0 = start background scan immediately, 1 = start background scan after 'scan_interval' milliseconds */
    u2 start_later;
    /** SSID filter list used in the to limit the scan results */
    ClxSSID ssid_list[CLX_MLAN_MRVDRV_MAX_SSID_LIST_LENGTH];
    /** Variable number (fixed maximum) of channels to scan up */
    ClxMlanOID_UserScanChannel chan_list[CLX_MLAN_BG_SCAN_CHAN_MAX];
} ClxMlanOID_BgScanConfig;


/**
Type definition of ClxMlanOID_HostCmd.
Supports SET action
*/
typedef struct ClxMlanOID_HostCmdStruct
{
    const u1* data;
    u4        dataLength;
} ClxMlanOID_HostCmd;


typedef struct ClxMlanOID_RTTCivicConfigStruct
{
    /**Civic location type*/
    u1 civic_location_type;
    /**Country code*/
    u2 country_code;
    /**Civic address type*/
    u1 civic_address_type;
    /**Civic address length*/
    u1 civic_address_length;
    /**Civic Address*/
    u1 civic_address[256];
} ClxMlanOID_RTTCivicConfig;

#if defined(CLX_FLOATING_POINT_SUPPORTED)
typedef struct ClxMlanOID_RTTLciConfigStruct
{
    /** known longitude*/
    r8 longitude;
    /** known Latitude*/
    r8 latitude;
    /** known altitude*/
    r8 altitude;
    /** known Latitude uncertainty*/
    u1 lat_unc;
    /** known Longitude uncertainty*/
    u1 long_unc;
    /** Known Altitude uncertainty*/
    u1 alt_unc;
    /** 1 word for additional Z information */
    u4 z_info;
} ClxMlanOID_RTTLciConfig;
#endif /* #if defined(CLX_FLOATING_POINT_SUPPORTED) */


/**
Type definition of ClxMlanOID_RTTConfigParams.
Supports SET action
*/
typedef struct ClxMlanOID_RTTConfigParamsStruct
{
    /** 
    Indicates how many burst instances are requested for the FTM session as (2 ^ burst_exponent). 
    The value 15 in an initial Fine Timing Measurement Request frame indicates no preference by the initiating STA and is valid (indicating 2^15 burst instances) when set by the responding STA.  
    */
    u1 burst_exponent;

    /**
    Burst Duration:
    */
    ClxWlanRTTBurstDuration burst_duration;

    /**
    Indicates minimum time between consecutive Fine Timing Measurement
    frames. It is specified in units of 100 micro seconds.
    */
    u1 min_delta_ftm;

    /**
    FALSE : No ASAP operation
    TRUE : ASAP operation
    */
    boolean asap;

    /**
    Number of FTMs per burst
    */
    u1 ftms_per_burst;

    /**
    # Channel spacing. Only the following values may be used:

    ClxWlanRTTFormatAndBandwidth_NoPreference (STA role only)
    ClxWlanRTTFormatAndBandwidth_NontHT20
    ClxWlanRTTFormatAndBandwidth_HT20
    ClxWlanRTTFormatAndBandwidth_VHT20
    ClxWlanRTTFormatAndBandwidth_HT40
    ClxWlanRTTFormatAndBandwidth_VHT40
    ClxWlanRTTFormatAndBandwidth_VHT80

    Other values MAY NOT be used.
    */
    ClxWlanRTTFormatAndBandwidth chan_spacing;

    /** Burst Period in units of 100 milliseconds */
    u2 burst_period;

    /** Indicates if civic location is required (in STA role) or available (in AccessPoint role) */
    u1 civic_req;

    /** Civic location details (only in AccessPoint role). In STA role, set all the members to 0 */
    ClxMlanOID_RTTCivicConfig civic_config;

#if defined(CLX_FLOATING_POINT_SUPPORTED)
    /** Indicates if LCI is required (in STA role) or available (in AccessPoint role) */
    u1 lci_req;

    /** LCI details (only in AccessPoint role) In STA role, set all the members to 0 */
    ClxMlanOID_RTTLciConfig lci_config;
#endif
} ClxMlanOID_RTTConfigParams;


/**
Type definition of ClxMlanOID_RTTSessionControl.
Supports SET action
*/
typedef struct ClxMlanOID_RTTSessionControlStruct
{
    u1 peer_addr[CLX_MAC_ADDRESS_LENGTH];
    u1 channel;
} ClxMlanOID_RTTSessionControl;


/**
Type definition of ClxMlanOID_UnassocRTTSession.
Supports SET action
*/
typedef struct ClxMlanOID_UnassocRTTSessionStruct
{
    boolean state; 
} ClxMlanOID_UnassocRTTSession;


typedef ClxMlanOID_RTTSessionControl ClxMlanOID_StartRTTSession;
typedef ClxMlanOID_RTTSessionControl ClxMlanOID_StopRTTSession;


/**
Type definition of ClxMlanOID_PSMode.
Supports SET action
*/
typedef struct ClxMlanOID_PSModeStruct
{
    boolean enable; 
} ClxMlanOID_PSMode;


/**
Type definition of ClxMlanOID_DeepSleepMode.
Supports SET action
*/
typedef struct ClxMlanOID_DeepSleepModeStruct
{
    boolean enable; 
} ClxMlanOID_DeepSleepMode;


/**
Type definition of ClxMlanOID_RTTCompleteIndication.
Received as an indication of type #CLX_WLAN_DRIVER_SPECIFIC_INDICATION.
*/
typedef struct ClxMlanOID_RTTCompleteIndicationStruct
{
    ClxWlanDriverSpecificIndication base;

    /** MAC address of the responder */
    u1 peer_addr[CLX_MAC_ADDRESS_LENGTH];
    /** Average RTT */
    u4 avg_rtt;
    /** Average Clock offset */
    u4 avg_clk_offset;
    /** Measure start timestamp */
    u4 meas_start_tsf;
} ClxMlanOID_RTTCompleteIndication;


/**
Type definition of ClxMlanOID_MlanFreeMemorySize.
Supports GET action
*/
typedef struct ClxMlanOID_MlanFreeMemorySize
{
    /** Free Memory in Bytes */
    u4 free_heap_size;
} ClxMlanOID_MlanFreeMemorySize;


CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_Signal);                            /*!<* Supports GET action */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_Stats);                             /*!<* Supports GET action */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_DataRate);                          /*!<* Supports GET action */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_TempSensor);                        /*!<* Supports GET action */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_FwInfo);                            /*!<* Supports GET action */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_UserScan);                          /*!<* Supports SET, GET, and DELETE actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_CountryCode);                       /*!<* Supports SET, and GET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_CfpTable);                          /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_HsCfg);                             /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_BfGlobalCfg);                       /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_HostCmd);                           /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_BgScanConfig);                      /*!<* Supports SET, GET, and DELETE actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_RTTConfigParams);                   /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_StartRTTSession);                   /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_StopRTTSession);                    /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_RTTCompleteIndication);             /*!<* Received as an indication of type #CLX_WLAN_DRIVER_SPECIFIC_INDICATION */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_UnassocRTTSession);                 /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_PSMode);                            /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_DeepSleepMode);                     /*!<* Supports SET actions */
CLX_DEFINE_CONFIG_TYPE(ClxMlanOID_MlanFreeMemorySize);                /*!<* Supports GET action  */


typedef enum ClxMlanOidActionEnum
{
    ClxMlanOidAction_GET = 0,
    ClxMlanOidAction_SET = 1,
    ClxMlanOidAction_DELETE = 2
} ClxMlanOidAction;


/**
Initializes an object of type #ClxMlanOidConfigParam, and adds it to the provided parent list (of type #parentList).
After initialization, the parameter object will contain a pointer to the OID (value) object and information on the action required.

The list may then be passed to either #clxWlanGetParametersValue() or #clxWlanSetParametersValue().

\param[ in ] param The parameter object of type #ClxMlanOidConfigParam.
\param[ in ] oid The OID value object which is to be attached to the parameter object. The type of this object is determined by the next argument (oidType).
\param[ in ] oidType Type of the OID structure. This value determines the requested configuration parameter. Only the OIDs defined in this file may be used.
                     This is basically the name of the OID object type passed to the macro CLX_CONFIG_TYPE (e.g. CLX_CONFIG_TYPE(ClxMlanOID_Signal), CLX_CONFIG_TYPE(ClxMlanOID_Stats) ...)
\param[ in ] action Action to take.The action shall be supported by the requested OID (as defined in this file). One of the following values may be provided:
                    - ClxMlanOidAction_GET :    The current value of the requested configuration parameter will be retrieved from the Marvel driver and will be
                                                stored in the provided OID object. This action may be used only if the parameter is passed to the API function #clxWlanGetParametersValue().
                                                Otherwise, the behaviour will be undefined.
                    - ClxMlanOidAction_SET :    The data provided in the provided OID object will replace the current value of the requested configuration parameter in the Marvel driver.
                                                This action may be used only if the parameter is passed to the API function #clxWlanSetParametersValue().
                                                Otherwise, the behaviour will be undefined.
                    - ClxMlanOidAction_DELETE : Deletes the current value of the requested configuration parameter. The configuration parameter will then hold the default value.
                                                This action may be used only if the parameter is passed to the API function #clxWlanSetParametersValue().
                                                Otherwise, the behaviour will be undefined.
\param[ in ] parentList Parent list to which this parameter is to be added.

\return TRUE if the object has been initialized successfully. FALSE if the oidType is invalid.
*/
boolean clxMlanIniOidConfigParam(ClxMlanOidConfigParam* param,
                                 void* oid,
                                 ClxConfigParamTypeID oidType,
                                 ClxMlanOidAction action,
                                 ClxConfigList* parentList);



/**
Runs a MLAN RF Test Mode command. This function will not return until the command is complete either successfully or in error.

NOTE : The command may print information on the command and/or response on the console output. If the BSP function pointer userPrintfFunction() has been set to a function, it will be called
       to print the information. Otherwise, the standard printf() function will be called.

\param[ in ]  interfaceHandle       The WLAN interface handle. A WLAN interface should be opened first with the clxWlanCreateInterface() function.
                                    The WLAN interface MUST be in STA role and MUST be already started by a previous call to clxWlanStartInterface() API.
\param[ in ]  command               The command is ASCII format. Please refer to NXP documentation on "RF Test Mode" for the details.

\return CLX_SUCCESS if the command has been passed to the NXP driver successfully. The command may print extra information on the console output.
        Any other value indicates an error (e.g. the command was not processed at all).
*/
ClxResult clxMlanRunRfTestModeCommand(ClxHandle interfaceHandle, const s1* command);


#ifdef __cplusplus
}
#endif



#endif // Wlan_Marvel_Config_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations.      */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user          */ 
/*                 applications.                                              */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations.    */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user        */ 
/*                 applications.                                              */
/******************************************************************************/
