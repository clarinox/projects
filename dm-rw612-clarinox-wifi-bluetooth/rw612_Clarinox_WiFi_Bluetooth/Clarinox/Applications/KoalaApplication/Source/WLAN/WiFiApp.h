#ifndef WiFiApp_H
#define WiFiApp_H

/*********************************************************************************
*
* Project             Wlan Sample Application
* File                WiFiApp.h
* Description         Wlan application variable are declared here
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/




#include "ClxBspConfig.h"


#if !defined(DEFAULT_MAC_LAYER_MTU)
#   define DEFAULT_MAC_LAYER_MTU                2352
#endif

#if !defined(DEFAULT_RTS_THRESHOLD)
#   define DEFAULT_RTS_THRESHOLD                2353
#endif

#if !defined(DEFAULT_AP_CHANNEL_NO)
#   define DEFAULT_AP_CHANNEL_NO			    6
#endif

#if !defined(DEFAULT_STA_MAX_TX_POWER)
#   define DEFAULT_STA_MAX_TX_POWER			    18
#endif

#if !defined(DEFAULT_AP_MAX_TX_POWER)
#   define DEFAULT_AP_MAX_TX_POWER			    18
#endif

#if !defined(MAX_TX_POWER_SUPPORTED_BY_WLAN)
#   define MAX_TX_POWER_SUPPORTED_BY_WLAN       25
#endif

#if !defined(DEFAULT_AP_BEACON_INTERVAL)
#   define DEFAULT_AP_BEACON_INTERVAL			100
#endif

#if !defined(DEFAULT_AP_DTIM_PERIOD)
#   define DEFAULT_AP_DTIM_PERIOD			    2
#endif

#if !defined(DEFAULT_CLIENT_INACTIVITY_TIMEOUT)
#   define DEFAULT_CLIENT_INACTIVITY_TIMEOUT	10     /* seconds */
#endif

#if !defined(DEFAULT_MAX_NUMBER_OF_AP_CLIENTS)
#   define DEFAULT_MAX_NUMBER_OF_AP_CLIENTS	    8
#endif


#if defined(CLX_IEEE802_11_N_SUPPORTED)
#	if defined (SUPPORT_TWO_SPATIAL_STREAMS)
#       define MAX_NUMBER_OF_RATES              29
#	else
#       define MAX_NUMBER_OF_RATES              21
#   endif
#else
#       define MAX_NUMBER_OF_RATES              13
#endif


#define MAX_CHANNEL_NO_IN_2_4_BAND		        14

#define MAX_VENDOR_SPECIFIC_IE_LEN              256

#define MIN_PSWD_PHRASE_LEN                     8

#define PASSWD_LEN_MAX          (64)
#define PASSWD_LEN_MIN          (8)


#ifdef __cplusplus
extern "C" {
#endif


#if !defined(CLX_WILINK) && !defined(CLX_MARVELL) &&!defined(CLX_WIFI_OVER_LAN)
    #error "Define CLX_WILINK, CLX_MARVELL or CLX_WIFI_OVER_LAN for WLAN"
#endif

#if defined(CLX_WILINK)
    #if defined(CLX_MARVELL)
        #error "Define only one of CLX_WILINK or CLX_MARVELL"
    #endif
    #if !defined(CLX_WL12XX) && !defined(CLX_WL18XX)
        #error "Define the chip family (CLX_WL12XX or CLX_WL18XX)"
    #endif
    #if defined(CLX_WL12XX) && defined(CLX_WL18XX)
        #error "Define only one of CLX_WL12XX or CLX_WL18XX"
    #endif
#include "Wl18xx.Config.h"
#endif

#if defined(CLX_MARVELL)
    #if defined(CLX_WILINK)
        #error "Define only one of CLX_WILINK or CLX_MARVELL"
    #endif
#endif

/**
The information of joint ST
*/
typedef struct ClxDiscoveredBssStruct
{
    struct ClxWlanStationListItem base;

    ClxSSID                 ssid;

    u4                      supportedEncProtocols;
    u4                      authTypes;

    ClxWlanFrequencyBand    band;
    u2                      primaryChannel;
    s2                      rssi;
#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
    boolean                 isMeshNode;
    ClxSSID                 meshID;
    u1                      rootAddress[CLX_MAC_ADDRESS_LENGTH];
    u1                      nodeAddress[CLX_MAC_ADDRESS_LENGTH];
    u1                      hopsToRoot;
    u1                      maxClients;
    u1                      currentClients;
#endif
} ClxDiscoveredBss;


typedef struct ClxConnInfo
{
    ClxConfigList         parentList;
    ClxWlanConfigChannel  channel;        /* The channel on which the network is currently operating */
    ClxConfigData         bssid;          /* The 6-byte unique ID of the BSS, which is the MAC address of the AccessPoint */
    u1                    bssidBuf[6];    /* A buffer to store the BSSID (bssid does not have a buffer on its own) */
} ClxConnInfo;

#if defined(CLX_WILINK)
#   if defined(CLX_WL12XX)
        extern ClxWlanDriverEntry Wl12xx_DriverEntry;
#       define Wlan_DriverEntry Wl12xx_DriverEntry
#   elif defined(CLX_WL18XX)
        extern ClxWlanDriverEntry Wl18xx_DriverEntry;
#       define Wlan_DriverEntry Wl18xx_DriverEntry
#   else
#       error "Driver entry struct needs to be declared here; it is defined by the driver library"
    #endif
#elif defined(CLX_MARVELL)
    extern ClxWlanDriverEntry Mlan_DriverEntry;
#   define Wlan_DriverEntry Mlan_DriverEntry
#elif defined(CLX_WIFI_OVER_LAN)
    extern ClxWlanDriverEntry wifiOverLAN_DriverEntry;
#   define Wlan_DriverEntry wifiOverLAN_DriverEntry
#else
#   error "Driver entry struct needs to be declared here; it is defined by the driver library"
#endif


#if defined(CLX_WILINK)
#	if defined(CLX_WL12XX)
#       define WLAN_INTERFACE_NAME_STA                  "TI-Wl12xx"
#       define WLAN_INTERFACE_NAME_AP                   "TI-Wl12xx"
#       define WLAN_FIRMWARE_VERSION_CONFIG_NAME        "Wl12xx.FirmwareVersion"
#	elif defined(CLX_WL18XX)
#       define WLAN_INTERFACE_NAME_STA                  "TI-Wl18xx"
#       define WLAN_INTERFACE_NAME_AP                   "TI-Wl18xx"
#       define WLAN_FIRMWARE_VERSION_CONFIG_NAME        "Wl18xx.FirmwareVersion"
#	else
#error "Define virtualInterfaceName here"
#	endif
#elif defined(CLX_MARVELL)
#       define WLAN_INTERFACE_NAME_STA                  "Mlan"
#       define WLAN_INTERFACE_NAME_AP                   "Mlan"
#       define WLAN_FIRMWARE_VERSION_CONFIG_NAME        "Mlan.FirmwareVersion"
#elif defined(CLX_WIFI_OVER_LAN)
#       define WLAN_INTERFACE_NAME_STA                  "WiFiOverLAN_Station"
#       define WLAN_INTERFACE_NAME_AP                   "WiFiOverLAN_AccessPoint"
#       define WLAN_FIRMWARE_VERSION_CONFIG_NAME        "WiFiOverLAN.FirmwareVersion"
#else
#   error "Define Chipset here"
#endif


extern s1           clxUiInputBuffer[MAX_UI_INPUT_SIZE + 1];

extern void         clxInitBsp(void);

extern void         clxWlanInitRates(ClxWlanConfigRate rates[MAX_NUMBER_OF_RATES],
                                     ClxConfigArray* ratesArray,
                                     ClxConfigList* parentList);

ClxResult clxWlanStartAccessPointInterfaceUsingParams(ClxHandle apHandle, ClxBSSInfo* desiredAPConf, s1* desiredPass, ClxConfigList* extraConfigParameters);

extern ClxResult    clxWlanStartStationInterface(ClxHandle staHandle,
                                                 u2 maxTxPower,
                                                 u2 macLayerMTU,
                                                 u2 rtsThreshold,
                                                 ClxConfigList* extraConfigParameters);

extern              ClxResult clxStopStationInterface(ClxHandle staHandle);
extern              ClxResult clxWlanConnectStationInterface(ClxHandle staHandle);

extern void         clxWlanPrintCapabilities(u4 capabilities);

extern void         clxWlanPrintDetailedBssInfo(ClxBSSInfo* bss, u4 index);

extern void         showStationMenu(ClxStack stack);
extern void         showAccessPointMenu(ClxStack stack);
extern void         showMeshMenu(ClxStack stack);

extern boolean      clxWlanStationIndicationHandler(ClxStack stack, ClxHandle handle, u4 messageID, const void* params, ClxError errorCode);
extern boolean      clxWlanAccessPointIndicationHandler(ClxStack stack, ClxHandle handle, u4 messageID, const void* params, ClxError errorCode);

extern ClxResult    clxTcpIpModule_Init(void);
extern void         clxTcpIpModule_Deinit(void);

#if defined(CLX_NETWORK_INTERFACE_LWIP)
extern void         issueLwipCommand(const s1 * command);
#endif

#if defined(CLX_SOCKETS_SUPPORT)
extern boolean      clxStartIPerf(s1* command);
#endif

extern struct ClxNetworkAccessInterface* createNetworkAccessInterface(void);

#if defined CLX_BANDWIDTH_LIMIT_SUPPORTED
extern void clxWlanSetBwLimit(ClxHandle staHandle);
extern void clxWlanSetBwLimitExceptPors(ClxHandle handle);
extern void clxWlanGetBwUsage(ClxHandle staHandle);
#endif

#ifdef __cplusplus
}
#endif


#endif /* WiFiApp_H */
