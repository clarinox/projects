#ifndef WLAN_CONFIG_H
#define WLAN_CONFIG_H

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                Wlan.Config.h
* Description         Contains WLAN configuration parameters
*
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


#define CLX_WLAN_INVALID_CHANNEL_NUMBER                 0


/**
ClxFreuencyBand enumerates different types of WLAN frequency bands.
*/
typedef enum ClxWlanFrequencyBandEnum
{
    ClxWlanFreqBandInvalid = 0,  
    ClxWlanFreqBand2_4GHz = 1,
    ClxWlanFreqBand5GHz = 2,
    ClxWlanFreqBand4_9GHz = 3,
    ClxWlanFreqBand6GHz = 4
} ClxWlanFrequencyBand;


/**
ClxWlanChannelBandwidth enumerates different channel widths.
*/
typedef enum ClxWlanChannelBandwidthEnum
{
    ClxWlanChannelBandwidth_Invalid = 0,     /*!< Invalid value for the channel type. MUST NOT be used by the application */
    ClxWlanChannelBandwidth_20 = 1,          /*!< A IEEE802.11a/b/g/n/ac channel with the channel bandwidth of 20MHz */
    ClxWlanChannelBandwidth_40_Below = 2,    /*!< A IEEE802.11n channel with the channel bandwidth of 20MHz+20MHz (Secondary channel is below primary channel) */
    ClxWlanChannelBandwidth_40_Above = 3,    /*!< A IEEE802.11n channel with the channel bandwidth of 20MHz+20MHz (Secondary channel is above primary channel) */
    ClxWlanChannelBandwidth_80 = 4,          /*!< A IEEE802.11ac channel with the channel bandwidth of 80 MHz */
    ClxWlanChannelBandwidth_160 = 5,         /*!< A IEEE802.11ac channel with the Contiguous channel bandwidth of 160 MHz */
    ClxWlanChannelBandwidth_80_80 = 6        /*!< A IEEE802.11ac channel with the non-contiguous channel bandwidth of 80+80 MHz */
} ClxWlanChannelBandwidth;


/**
ClxWlanStandard enumerates the different WLAN standards. More than one value may be Bit-wise combined, 
if a relevant configuration parameter allows this.
*/
typedef enum ClxWlanStandard
{
    ClxWlanStandardB    = 0x01,
    ClxWlanStandardAG   = 0x02,                                  /*!<  Both IEEE802.11g and IEEE802.11a (The only difference is the frequency band in which they operate) */
    ClxWlanStandardN    = 0x04,
    ClxWlanStandardAC   = 0x08,
    ClxWlanStandardAX   = 0x10
} ClxWlanStandard;


/**
WLAN regulatory domain regions
*/
typedef enum ClxWlanRegulatoryRegion 
{      
	ClxWlanRegulatoryRegion_None	= 0,                        /*!< Not defined by the country */
	ClxWlanRegulatoryRegion_FCC		= 1,                        /*!< FCC (US Federal Communications Commission) */
	ClxWlanRegulatoryRegion_ETSI	= 2,                        /*!< ETSI (The European Telecommunications Standards Institute) */
	ClxWlanRegulatoryRegion_JP		= 3,                        /*!< Japan */
    ClxWlanRegulatoryRegion_Max     = ClxWlanRegulatoryRegion_JP
} ClxWlanRegulatoryRegion;


/**
ClxWlanStandard enumerates the different scan options. More than one value may be Bit-wise combined, 
if a relevant configuration parameter allows this. The value ClxWlanNoScan shall not be combined with
the other values.
*/
typedef enum ClxWlanScanType
{
    ClxWlanNoScan = 0x0,
    ClxWlanPassiveScan = 0x1,
    ClxWlanActiveScan = 0x2,
    ClxWlanDfsScan = 0x04                               /*!< Passive scan until activity on the channel is detected. Then active scan is permitted.
                                                             (As per current IEEE802.11h regulatory domain requirement) */     
} ClxWlanScanType CLX_CTYPE;



/**
General capabilities of a WLAN station. Can be bit-wise-combined into a single variable: 
*/
#define CLX_WLAN_CAPABILITY_SHORT_PREAMBLE_SUPPORTED                        0x00000001
#define CLX_WLAN_CAPABILITY_QOS_SUPPORTED                                   0x00000002
#define CLX_WLAN_CAPABILITY_SHORT_SLOT_TIME_SUPPORTED                       0x00000004

/* WIFI Alliance standard capabilities: */
#define CLX_WLAN_CAPABILITY_WPS_SUPPORTED                                   0x00000080    /*!< The station supports WiFi Protected Setup */
#define CLX_WLAN_CAPABILITY_WMM_SUPPORTED                                   0x00000100    /*!< The station supports WiFi MultiMedia (based on IEEE802.11 QOS features) */
#define CLX_WLAN_CAPABILITY_WIFI_DIRECT_SUPPORTED                           0x00000200    /*!< The station supports WiFi Direct - also known as P2P (Point to Point) mode */

/* IEEE802.11 standard capabilities: */
#define CLX_WLAN_CAPABILITY_HT_SUPPORTED                                    0x00000400    /*!< The station supports IEEE802.11n, technically known as HT (High Throughput)  */
#define CLX_WLAN_CAPABILITY_VHT_SUPPORTED                                   0x00000800    /*!< The station supports IEEE802.11ac, technically known as VHT (Very High Throughput)  */

#define CLX_WLAN_CAPABILITY_RADIO_MEASUREMENT_SUPPORTED                     0x00001000    /*!< Radio Measurement is supported  */
#define CLX_WLAN_CAPABILITY_APSD_SUPPORTED                                  0x00002000    /*!< Automatic Power Save Delivery (APSD) is supported by the QOS-enabled device */

#define CLX_WLAN_CAPABILITY_HE_SUPPORTED                                    0x00004000    /*!< The station supports IEEE802.11ax, technically known as HE (High Efficiency)  */

#define CLX_WLAN_CAPABILITY_WPA_SUPPORTED                                   0x00008000    /*!< The legacy WPA is supported */

#define CLX_WLAN_CAPABILITY_CLARINOX_MESH_SUPPORTED                         0x00010000    /*!< Clarinox (Proprietary) MESH technology is supported */

#define CLX_WLAN_CAPABILITY_BTM_SUPPORTED                                   0x00020000    /*!< The station supports BSS Transition Management, a feature \
                                                                                               of IEEE802.11v technically known as WNM (Wireless Network Management) */

/**
ClxWlanStandard enumerates non-HT (IEE802.11a, IEEE802.11g, and IEEE802.11b) data rates.
*/
enum ClxWlanNonHTRate
{
    ClxWlanNonHTRate_NULL       = 0,                 /*!< Indicates that the relevant parameter is not a non-HT data rate */
    ClxWlanNonHTRate_1Mbps      = 2,                 /*!< Mandatory in all standards */
    ClxWlanNonHTRate_2Mbps      = 4,                 /*!< Mandatory in all standards */
    ClxWlanNonHTRate_5_5Mbps    = 11,                /*!< 5.5Mpbs - Mandatory in IEEE802.11b standard */
    ClxWlanNonHTRate_6Mbps      = 12,                /*!< Mandatory in IEEE802.11ag standard */
    ClxWlanNonHTRate_9Mbps      = 18,                /*!< IEEE802.11ag standard */
    ClxWlanNonHTRate_11Mbps     = 22,                /*!< Mandatory in IEEE802.11b standard */
    ClxWlanNonHTRate_12Mbps     = 24,                /*!< Mandatory in IEEE802.11ag standard */
    ClxWlanNonHTRate_18Mbps     = 36,                /*!< IEEE802.11ag standard */
    ClxWlanNonHTRate_22Mbps     = 44,                /*!< Deprecated */
    ClxWlanNonHTRate_24Mbps     = 48,                /*!< IEEE802.11ag standard */
    ClxWlanNonHTRate_33Mbps     = 66,                /*!< Deprecated */
    ClxWlanNonHTRate_36Mbps     = 72,                /*!< IEEE802.11ag standard */
    ClxWlanNonHTRate_48Mbps     = 96,                /*!< IEEE802.11ag standard */
    ClxWlanNonHTRate_54Mbps     = 108                /*!< IEEE802.11ag standard */
};


/**
Bit-Wise definition of Non-HT rates. Used when a value contains a combination of rates. 
*/
#define CLX_WLAN_NON_HT_RATE_BIT_1MBPS                                      0x0001    
#define CLX_WLAN_NON_HT_RATE_BIT_2MBPS                                      0x0002        
#define CLX_WLAN_NON_HT_RATE_BIT_5_5MBPS                                    0x0004    
#define CLX_WLAN_NON_HT_RATE_BIT_6MBPS                                      0x0008        
#define CLX_WLAN_NON_HT_RATE_BIT_9MBPS                                      0x0010        
#define CLX_WLAN_NON_HT_RATE_BIT_11MBPS                                     0x0020    
#define CLX_WLAN_NON_HT_RATE_BIT_12MBPS                                     0x0040    
#define CLX_WLAN_NON_HT_RATE_BIT_18MBPS                                     0x0080
#define CLX_WLAN_NON_HT_RATE_BIT_22MBPS                                     0x0100
#define CLX_WLAN_NON_HT_RATE_BIT_24MBPS                                     0x0200
#define CLX_WLAN_NON_HT_RATE_BIT_33MBPS                                     0x0400
#define CLX_WLAN_NON_HT_RATE_BIT_36MBPS                                     0x0800
#define CLX_WLAN_NON_HT_RATE_BIT_48MBPS                                     0x1000
#define CLX_WLAN_NON_HT_RATE_BIT_54MBPS                                     0x2000

#define CLX_WLAN_HT_MAX_NUMBER_OF_SPATIAL_STREAMS				            4

#define CLX_WLAN_HT_RX_SUPPORTED_MCS_BITMASK_SIZE					        10			/*!< Bytes */
#define CLX_WLAN_HT_CAPABILITY_MAX_MCS_INDEX						        76			/*!< IEEE802.11n supports MC0 through MCS76 */

/* 
IEEE802.11n HT (High Throughput) capabilities. A bitwise combination may be stored in the ClxWlanHTInfo.capabilities member : 
*/
#define CLX_WLAN_HT_CAP_BIT_40MHZ_CHANNEL_WIDTH_SUPPORTED                   0x0001    /*!< The station supports 40MHz channel width to double the data throughput */
#define CLX_WLAN_HT_CAP_BIT_SGI_FOR_20MHZ_SUPPORTED                         0x0002    /*!< Short Guard Interval (400ns) is supported in 20MHz channels */
#define CLX_WLAN_HT_CAP_BIT_SGI_FOR_40MHZ_SUPPORTED                         0x0004    /*!< Short Guard Interval (400ns) is supported in 40MHz channels */
#define CLX_WLAN_HT_CAP_BIT_GREENFIELD_MODE_SUPPORTED                       0x0008    /*!< Greenfield mode (fast mode but disruptive to IEEE802.11abg stations in the area) is supported */
#define CLX_WLAN_HT_CAP_BIT_40MHZ_INTOLERANT                                0x0010    /*!< The station is not able to operate in an environment where 40MHz channels are in use */
#define CLX_WLAN_HT_CAP_BIT_STATIC_POWER_SAVING_MODE_SUPPORTED              0x0020    /*!< The static power saving mode is supported (mutually exclusive with dynamic mode) */
#define CLX_WLAN_HT_CAP_BIT_DYNAMIC_POWER_SAVING_MODE_SUPPORTED             0x0040    /*!< The dynamic power saving mode is supported (mutually exclusive with static mode) */
#define CLX_WLAN_HT_CAP_BIT_DELAYED_BLOCK_ACK_SUPPORTED                     0x0080    /*!< Delayed Block ACK is supported */
#define CLX_WLAN_HT_CAP_BIT_TX_STBC_SUPPORTED                               0x0100    /*!< The device supports transmission of STBC (Space Time Block Code) coded frames */
#define CLX_WLAN_HT_CAP_BIT_LONG_A_MSDU_SUPPORTED                           0x0200    /*!< Long A-MSDU (7935 bytes) is supported. If not set, then only short A-MSDU (3839 bytes) is supported */



/**
Determines whether or not a IEEE802.11n (HT) RX MCS (Modulation and Coding Scheme) is supported by a device.

MCS0 through MCS32 use Equal Modulation (EQM). With EQM, the same modulation scheme is used in all spacial streams.

Index  NSS   Modulation   CodingRate
------------------------------------
MCS0	1	   BPSK	         1/2
MCS1	1	   QPSK	         1/2
MCS2	1	   QPSK	         3/4
MCS3	1	   16-QAM	     1/2
MCS4	1	   16-QAM	     3/4
MCS5	1	   64-QAM	     2/3
MCS6	1	   64-QAM	     3/4
MCS7	1	   64-QAM	     5/6
MCS8	2	   BPSK	         1/2
MCS9	2	   QPSK	         1/2
MCS10	2	   QPSK	         3/4
MCS11	2	   16-QAM	     1/2
MCS12	2	   16-QAM	     3/4
MCS13	2	   64-QAM	     2/3
MCS14	2	   64-QAM	     3/4
MCS15	2	   64-QAM	     5/6
MCS16	3	   BPSK	         1/2
MCS17	3	   QPSK	         1/2
MCS18	3	   QPSK	         3/4
MCS19	3	   16-QAM	     1/2
MCS20	3	   16-QAM	     3/4
MCS21	3	   64-QAM	     2/3
MCS22	3	   64-QAM	     3/4
MCS23	3	   64-QAM	     5/6
MCS24	4	   BPSK	         1/2
MCS25	4	   QPSK	         1/2
MCS26	4	   QPSK	         3/4
MCS27	4	   16-QAM	     1/2
MCS28	4	   16-QAM	     3/4
MCS29	4	   64-QAM	     2/3
MCS30	4	   64-QAM	     3/4
MCS31	4	   64-QAM	     5/6
MCS32	1	   BPSK          1/4

MCS33 through MCS76 use UnEqual Modulation (UEQM). With UEQM, a different modulation scheme is used in each spacial stream. 

\param[ in ] wlanHTInfo  An object of type ClxWlanHTInfo which contains information on the device.
\param[ in ] mcs         The MCS index to be checked. The valid values are 0 through #CLX_WLAN_HT_CAPABILITY_MAX_MCS_INDEX. 

\return If the provided MCS is supported by the device in the RX path, a non-zero value is returned. Otherwise, 0 is returned.
*/
#define CLX_WLAN_HT_RX_MCS_BIT(wlanHTInfo, mcs)                          ( ((u1)(mcs) <= CLX_WLAN_HT_CAPABILITY_MAX_MCS_INDEX) ?                                              \
                                                                           ( (wlanHTInfo).rxMcsSet[((u1)(mcs) & 0x78) >> 3] & CLX_SET_BIT(((u1)(mcs) & 0x07)) ) : 0 )


typedef enum ClxWlanHTSupportedTxNSSEnum
{
    ClxWlanHtSupportedTxNSS_One = 0,                /*!< One spacial stream is supported */
    ClxWlanHtSupportedTxNSS_Two = 1,                /*!< Two spacial streams are supported */
    ClxWlanHtSupportedTxNSS_Three = 2,              /*!< Three spacial streams are supported */
    ClxWlanHtSupportedTxNSS_Four = 3,               /*!< Four spacial streams are supported */
    ClxWlanHtSupportedTxNSS_SameAsRX = 5            /*!< The same number of spacial streams that are supported in the RX path (as determined by the RX MCS set) */
} ClxWlanHTSupportedTxNSS;


typedef enum ClxWlanHTSupportedRxSTBCEnum
{
    ClxWlanHTSupportedRxSTBC_NotSupported = 0,      /*!< STBC (Space Time Block Code) for reception (RX path) is not supported  */
    ClxWlanHTSupportedRxSTBC_OneStream = 1,         /*!< STBC is supported in RX path for one spatial stream */
    ClxWlanHTSupportedRxSTBC_TwoStreams = 2,        /*!< STBC is supported in RX path for one and two spatial streams */
    ClxWlanHTSupportedRxSTBC_ThreeStreams = 3      /*!< STBC is supported in RX path for one, two and three spatial streams */
} ClxWlanHTSupportedRxSTBC;


/**
Provides information on a local or remote IEEE802.11n device, also known as a HT (High Throughput) device.
*/
typedef struct ClxWlanHTInfoStruct
{
    u2                           capabilities;                                                /*!< A bitwise combination of CLX_WLAN_HT_CAP_BIT_ definitions */

    u1                           rxMcsSet[CLX_WLAN_HT_RX_SUPPORTED_MCS_BITMASK_SIZE];         /*!< Set of IEEE802.11n RX MCSs. Use the macro #CLX_WLAN_HT_RX_MCS_BIT to test for presence of a particular IEEE802.11n MCS bit */
    ClxWlanHTSupportedTxNSS      supportedTxNSS;                                              /*!< Determines the Number of Spacial Streams (NSS) which are supported by the device in the TX path */
    ClxWlanHTSupportedRxSTBC     supportedRxSTBC;                                             /*!< Determines the Number of Spacial Streams for which the device supports reception of STBC (Space Time Block Code) coded frames */  

    struct HT_BSS
    {
        u2                       primaryChannel;                                              /*!< The 20 MHz primary channel on which the BSS is operating.
                                                                                                   For 20 MHz channels, indicates the center channel number of the operating channel.
                                                                                                   For 40 MHz channels, indicates the center channel number of the primary channel */ 
        ClxWlanChannelBandwidth  channelBW;                                                   /*!< The bandwidth of the channel on which the BSS is operating. The allowed values are 
                                                                                                       #ClxWlanChannelBandwidth_20    
                                                                                                       #ClxWlanChannelBandwidth_40_Below
                                                                                                       #ClxWlanChannelBandwidth_40_Above */
    } bss;                                                                                    /*!< Information on the BSS for which the HT device is the Access Point role.
                                                                                                   MUST be ignored if this object does NOT describe a device in Access Point role */
} ClxWlanHTInfo;



/**
Enumerates the IEEE802.11ac (VHT) MCSs (Modulation and Coding Schemes) supported for a specific NSS (Number of Spacial Streams).

Index    Modulation   CodingRate
--------------------------------
MCS0       BPSK	         1/2
MCS1       QPSK	         1/2
MCS2       QPSK	         3/4
MCS3       16-QAM	     1/2
MCS4       16-QAM	     3/4
MCS5       64-QAM	     2/3
MCS6       64-QAM	     3/4
MCS7       64-QAM	     5/6
MCS8       256-QAM	     3/4
MCS9       256-QAM	     5/6
*/
typedef enum ClxWlanVHTSupportedMCSEnum
{
    ClxWlanVHTSupportedMCS_0_7 = 0,			            /* MCS 0 to 7 are supported for a specific NSS */
    ClxWlanVHTSupportedMCS_0_8 = 1,			            /* MCS 0 to 8 are supported for a specific NSS */
    ClxWlanVHTSupportedMCS_0_9 = 2,			            /* MCS 0 to 9 are supported for a specific NSS */
    ClxWlanVHTSupportedMCS_None = 3			            /* Set for a NSS which is not supported by the device */
} ClxWlanVHTSupportedMCS;


/**
Enumerates the IEEE802.11ac (VHT) channel bandwidths supported by a device.
*/
typedef enum ClxWlanVHTSupportedBandwidthEnum
{
    ClxWlanVHTSupportedBandwidth_80 = 0,                /* Supports 20, 40, and 80 MHz channels (Mandatory for all VHT devices) */
    ClxWlanVHTSupportedBandwidth_160 = 1,               /* In addition to VHTSupportedBandwidth_80, it also supports contiguous 160 MHz channels */
    ClxWlanVHTSupportedBandwidth_80_80 = 2              /* In addition to VHTSupportedBandwidth_160, it also supports non-contiguous 80+80 MHz channels */
} ClxWlanVHTSupportedBandwidth;


/**
Enumerates the IEEE802.11ax (HE) channel bandwidths supported by a device.
*/
typedef enum ClxWlanHESupportedBandwidthEnum
{
    ClxWlanHESupportedBandwidth_40_2_4G = 0,            /* Supports 20 MHz and 40 MHz channels in 2.4 GHz band */
    ClxWlanHESupportedBandwidth_80 = 1,                 /* Supports 20, 40, and 80 MHz channels in 5 GHz / 6 GHz bands */
    ClxWlanHESupportedBandwidth_160 = 2,                /* In addition to HESupportedBandwidth_80, supports contiguous 160 MHz channels */
    ClxWlanHESupportedBandwidth_80_80 = 3               /* In addition to HESupportedBandwidth_160, supports non-contiguous 80+80 MHz channels */
} ClxWlanHESupportedBandwidth;


#define CLX_WLAN_VHT_MAX_NUMBER_OF_SPATIAL_STREAMS				            8

#define _CLX_WLAN_GET_VHT_SUPPORTED_MCS_PER_NSS_(map, nss)                  ( (((u1)(nss) > 0) && ((u1)(nss) <= CLX_WLAN_VHT_MAX_NUMBER_OF_SPATIAL_STREAMS)) ?                               \
                                                                              (ClxWlanVHTSupportedMCS)(((map) >> (((u1)(nss) - 1) << 1)) & 0x03) : ClxWlanVHTSupportedMCS_None )

#define _CLX_WLAN_SET_VHT_SUPPORTED_MCS_PER_NSS_(map, nss, value)           map |= ( (((u1)(nss) > 0) && ((u1)(nss) <= CLX_WLAN_VHT_MAX_NUMBER_OF_SPATIAL_STREAMS)) ?                        \
                                                                                     (((u2)(value) & 0x03) << (((u1)(nss) - 1) << 1)) : 0 )


/**
Extracts (from a ClxWlanVHTInfo object) the IEEE802.11ac (VHT) RX MCSs (Modulation and Coding Schemes) supported by a device for a specific NSS (Number of Spacial Streams).

\param[ in ] wlanVHTInfo An object of type ClxWlanVHTInfo which contains information on the device.
\param[ in ] nss         The NSS for which the supported RX MSCs is to be extracted. The value must be 1 through 8. If an invalid mss is provided, the value #ClxWlanVHTSupportedMCS_None will be returned.

\return The supported RX MCSs for the provided NSS, as a value of type #ClxWlanVHTSupportedMCS
*/
#define CLX_WLAN_GET_VHT_SUPPORTED_RX_MCS_PER_NSS(wlanVHTInfo, nss)                 _CLX_WLAN_GET_VHT_SUPPORTED_MCS_PER_NSS_((wlanVHTInfo).rxMcsSet, nss)

/**
Extracts (from a ClxWlanVHTInfo object) the IEEE802.11ac (VHT) TX MCSs (Modulation and Coding Schemes) supported by a device for a specific NSS (Number of Spacial Streams).

\param[ in ] wlanVHTInfo An object of type ClxWlanVHTInfo which contains information on the device.
\param[ in ] nss         The NSS for which the supported TX MSCs is to be extracted. The value must be 1 through 8. If an invalid mss is provided, the value #ClxWlanVHTSupportedMCS_None will be returned.

\return The supported TX MCSs for the provided NSS, as a value of type #ClxWlanVHTSupportedMCS
*/
#define CLX_WLAN_GET_VHT_SUPPORTED_TX_MCS_PER_NSS(wlanVHTInfo, nss)                 _CLX_WLAN_GET_VHT_SUPPORTED_MCS_PER_NSS_((wlanVHTInfo).txMcsSet, nss)

/**
Sets (in a ClxWlanVHTInfo object) the IEEE802.11ac (VHT) RX MCSs (Modulation and Coding Schemes) supported by a device for a specific NSS (Number of Spacial Streams).

\param[ in ] wlanVHTInfo An object of type ClxWlanVHTInfo which contains information on the device.
\param[ in ] nss         The NSS for which the supported RX MSCs is to be set. The value must be 1 through 8.
\param[ in ] value       The supported MCSs for the specified NSS, as a value of type #ClxWlanVHTSupportedMCS.
*/
#define CLX_WLAN_SET_VHT_SUPPORTED_RX_MCS_PER_NSS(wlanVHTInfo, nss, value)         _CLX_WLAN_SET_VHT_SUPPORTED_MCS_PER_NSS_((wlanVHTInfo).rxMcsSet, nss)

/**
Sets (in a ClxWlanVHTInfo object) the IEEE802.11ac (VHT) TX MCSs (Modulation and Coding Schemes) supported by a device for a specific NSS (Number of Spacial Streams).

\param[ in ] wlanVHTInfo An object of type ClxWlanVHTInfo which contains information on the device.
\param[ in ] nss         The NSS for which the supported TX MSCs is to be set. The value must be 1 through 8.
\param[ in ] value       The supported MCSs for the specified NSS, as a value of type #ClxWlanVHTSupportedMCS.
*/
#define CLX_WLAN_SET_VHT_SUPPORTED_TX_MCS_PER_NSS(wlanVHTInfo, nss, value)         _CLX_WLAN_SET_VHT_SUPPORTED_MCS_PER_NSS_((wlanVHTInfo).txMcsSet, nss)



/**
Provides information on a local or remote IEEE802.11ac device, also known as a VHT (Very High Throughput) device.
*/
typedef struct ClxWlanVHTInfoStruct
{
    u2                             capabilities;        /*!< Reserved for future use. Set to 0 */
                                   
    u2                             rxMcsSet;            /*!< Set of IEEE802.11ac RX MCSs supported by the device. Use the macro #CLX_WLAN_GET_VHT_SUPPORTED_RX_MCS_PER_NSS to extract supported MCSs per a NSS */
    u2                             txMcsSet;            /*!< Set of IEEE802.11ac TX MCSs supported by the device. Use the macro #CLX_WLAN_GET_VHT_SUPPORTED_TX_MCS_PER_NSS to extract supported MCSs per a NSS */          
                                   
    ClxWlanVHTSupportedBandwidth   supportedBW;         /*!< The channel bandwidths supported by the device.
                                                             NOTE : A limited set of supported TX/RX MCSs  and NSS may be allowed to be used with some channel bandwidths */
    struct VHT_BSS                     
    {                              
        u2                         channel0;            /*!< For 20 MHz, 40 MHz, 80 MHz and contiguous 160 MHz channels, indicates the center channel number of the operating channel.
                                                             For 80+80 MHZ channels, indicates the center channel number of the primary 80 MHz channel */
        u2                         channel1;            /*!< For 80+80 MHZ channels, indicates the center channel number of the secondary 80 MHz channel. 
                                                             For other types of channels, it is set to #CLX_WLAN_INVALID_CHANNEL_NUMBER */
        ClxWlanChannelBandwidth    channelBW;           /*!< The bandwidth of the channel on which the BSS is operating */
    } bss;                                              /*!< Information on the BSS for which the VHT device is the AP (Access Point).
                                                             MUST be ignored if this object does NOT describe a device in access point role */
} ClxWlanVHTInfo;


/**
Provides information on a local or remote IEEE802.11ax device, also known as a HE (High Efficiency) device.
*/
typedef struct ClxWlanHEInfoStruct
{
    u2                             capabilities;        /*!< Combined HE MAC and PHY capabilities info bitmask */
    ClxWlanHESupportedBandwidth    supportedBW;         /*!< The channel bandwidths supported by the device. */
} ClxWlanHEInfo;


/**
IEEE802.11-2020 specification - Section 9.4.2.167
Indicates the duration of a burst instance of an FTM session.
*/
typedef enum ClxWlanRTTBurstDurationEnum
{
    ClxWlanRTTBurstDuration_250us = 2,
    ClxWlanRTTBurstDuration_500us = 3,
    ClxWlanRTTBurstDuration_1ms = 4,
    ClxWlanRTTBurstDuration_2ms = 5,
    ClxWlanRTTBurstDuration_4ms = 6,
    ClxWlanRTTBurstDuration_8ms = 7,
    ClxWlanRTTBurstDuration_16ms = 8,
    ClxWlanRTTBurstDuration_32ms = 9,
    ClxWlanRTTBurstDuration_64ms = 10,
    ClxWlanRTTBurstDuration_128ms = 11,
    ClxWlanRTTBurstDuration_NoPreference = 15   /* Maybe used in STA role. CANNOT be used in AccessPoint role */
} ClxWlanRTTBurstDuration;


/**
IEEE802.11-2020 specification - Section 9.4.2.167
Indicates the requested or allocated PPDU format and bandwidth that can be used by Fine Timing Measurement frames in an FTM session.
*/
typedef enum ClxWlanRTTFormatAndBandwidthEnum
{
    ClxWlanRTTFormatAndBandwidth_NoPreference = 0,  /* Maybe used in STA role. CANNOT be used in AccessPoint role */
    ClxWlanRTTFormatAndBandwidth_NontHT5 = 4,
    ClxWlanRTTFormatAndBandwidth_NontHT10 = 6,
    ClxWlanRTTFormatAndBandwidth_NontHT20 = 8,
    ClxWlanRTTFormatAndBandwidth_HT20 = 9,
    ClxWlanRTTFormatAndBandwidth_VHT20 = 10,
    ClxWlanRTTFormatAndBandwidth_HT40 = 11,
    ClxWlanRTTFormatAndBandwidth_VHT40 = 12,
    ClxWlanRTTFormatAndBandwidth_VHT80 = 13,
    ClxWlanRTTFormatAndBandwidth_VHT80_80 = 14,
    ClxWlanRTTFormatAndBandwidth_VHT160_TwoLOs = 15,
    ClxWlanRTTFormatAndBandwidth_VHT160_SingleLO = 16   
} ClxWlanRTTFormatAndBandwidth;



/**
ClxWlanConfigRate defines a single TX/RX rate as defined by IEEE802.11 standard. An object of type #ClxWlanConfigRate may refer
to a non-HT rate (as defined IEEE802.11a, IEEE802.11b or IEEE802.11g standard), or a HT (High Throughput) rate as defined by
IEEE802.11n standard. A non-HT rate is defined by the actual over-the-air data rate (in Mbps). A HT rate is defined by a MCS
(Modulation and Coding Scheme) index which is mapped to the actual over-the-air data rate.

paramInfo : provides information of the parameter. This is to be set by a call to clxConfigInitRateParam(). 
This SHALL not be set manually.

nonHTValue : The data rate value, only if this is a non-HT rate. The value shall be selected from #ClxWlanNonHTRate enumerator.
If this object defines a HT rate, this member SHALL be set to ClxWlanNonHTRate_NULL.
mcsIndex : The MCS value of this rate, only if this a HT rate. This member is ignored if "nonHTValue" of type #ClxWlanNonHTRate is not set to ClxWlanNonHTRate_NULL.
Refer to IEEE802.11n (2009) specification for more information on MCS rates and their meaning.
basicRate : This value only applies when the local interface is set to AccessPoint or AD-HOC mode. In these modes, setting this member to TRUE indicates
that this object specifies a Basic Rate. A basic rate is a rate which must be supported by all clients in a BSS/IBSS. If a client does not support one or 
more of basic rates, it will not be able to join the WLAN network. Basic rates are used to send multicast/broadcast packets in the network.
In Station mode, this member has no effect and is ignored by ClarinoxWLAN.
*/
typedef struct ClxWlanConfigRateStruct
{
    ClxConfigParam                paramInfo;
    enum ClxWlanNonHTRate         nonHTValue;
    u4                            mcsIndex;
    boolean                       basicRate;
} ClxWlanConfigRate;


CLX_DEFINE_CONFIG_TYPE(ClxWlanConfigRate);


/**
Initializes a member of parentList with the given object of type #ClxWlanConfigRate.
*/
extern void clxConfigInitRateParam (ClxWlanConfigRate* object, 
                                    const s1* paramName, 
                                    enum ClxWlanNonHTRate nonHTValue,
                                    u4 mcsIndex,
                                    boolean    basicRate,
                                    ClxConfigList* parentList);


/**
ClxWlanConfigChannel defines relevant information of a given WLAN channel. The structure also includes regulatory
domain-related information on a channel basis. The API user shall make sure these parameters are set appropriately
according to the regulatory rules of the domain/country in which the product is used. ClarinoxWLAN will NOT examine these
values for consistency with the regulatory rules.

paramInfo : provides information of the parameter. This is to be set by a call to clxConfigInitChannelParam(). 
This SHALL not be set manually.

channelNumber : An unsigned number allocated to every WLAN channel.
frequencyBand : The frequency band in which the channel is located. This parameter is of type #ClxWlanFrequencyBand.
allowedScanType : The type of scanning which is permitted in the current regulatory domain for this channel. The parameter
shall contain an OR-ed combination of values of type #ClxWlanScanType. If scanning is not permitted on this channel, this
parameter shall be set to ClxWlanNoScan.
maxAllowedTxPower : The maximum TX power (in dBm) allowed on this channel according to the regulatory rules.
*/
typedef struct ClxWlanConfigChannelStruct
{
    ClxConfigParam                paramInfo;
    u2                            channelNumber;
    ClxWlanFrequencyBand          frequencyBand;
    u4                            allowedScanType;
    u4                            maxAllowedTxPower;
} ClxWlanConfigChannel;


CLX_DEFINE_CONFIG_TYPE(ClxWlanConfigChannel);


/**
Initializes a member of parentList with the given object of type #ClxWlanConfigChannel.
*/
extern void clxConfigInitChannelParam    (ClxWlanConfigChannel* object, 
                                           const s1* paramName, 
                                           u2 channelNumber, 
                                           ClxWlanFrequencyBand frequencyBand,
                                           u4 allowedScanType,
                                           u4 maxAllowedTxPower,
                                           ClxConfigList* parentList);


#ifdef __cplusplus
}
#endif


#endif // WLAN_CONFIG_H

/******************************************************************************/
/* 1. MISRA C 2004 RULE VIOLATION:                                            */
/* Message       : Identifiers (internal and external) shall not rely on the  */
/*                 significance of more than 31 characters.                   */
/* Rule          : MISRA-C:2004 Rule 5.1                                      */
/* Justification : Improves clarity of macro definitions. The compiler used   */
/*                 supports symbols longer than 31 characters, hence no risks.*/
/******************************************************************************/


/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused type declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.3                                      */ 
/* Justification : Unused type declarations are to be used in user 		      */
/* 				   applications.      										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/
