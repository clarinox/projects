/*********************************************************************************
*
* Project             Wlan Sample Application
* File                WlanClient.cpp
* Description         Wlan Station role application file
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
#include "Driver/Driver.h"
#include "WlanScan.h"

#ifdef CLX_WPA_SUPPLICANT
#   include "Wlan.WpaSupplicant.Api.h"
#endif

#ifdef CLX_WLAN_ROAMING_ENABLE
#include "WlanRoaming.h"
static ClxWlanRomingModule *roamingModule = NULL;
#endif

#ifdef CLX_WIFI_MESH_AUTO
#include "WlanMeshAuto.h"
#endif

extern void clxCheckMemoryUsage(void);


#if defined(CLX_WIFI_OVER_LAN)
    static const u1 userMacAddress[CLX_MAC_ADDRESS_LENGTH] = WIFI_OVER_LAN_LOCAL_STA_MAC_ADDR;
#elif defined(USER_DEFINED_STATION_MAC_ADDRESS)
    static const u1 userMacAddress[CLX_MAC_ADDRESS_LENGTH] = CLX_WLAN_STATION_MAC_ADDRESS;
#else
    static const u1* userMacAddress = NULL;
#endif

s2 clxWlanAppGetConnectionAverageRSSI(ClxHandle interfaceHandle)
{
    const DriverOps* drv = GetDriverOps();
    if (drv == NULL) {
        return 0;
    }

    return drv->getConnectionAverageMgmtRSSI(interfaceHandle);
}

#ifdef CLX_WPA_SUPPLICANT
static ClxResult clxAddWpaSupplicantNetwork(ClxHandle staHandle, ClxWlanConnectionProfile* connProfile)
{
    ClxService stationService;

    struct NetworkCredentials
    {
        ClxConfigList      parent;

        ClxConfigValue     pairwiseCipher;
        ClxConfigValue     groupwiseCipher;
        ClxConfigValue     groupMgmtCipher;

        ClxConfigValue     key_mgmt;

        ClxConfigInteger   ieee80211w;

        ClxConfigData      key;
        ClxConfigString    passwdPhrase;

        ClxConfigValue     eap;

        ClxConfigString    phase1;
        ClxConfigString    phase2Auth;

        ClxConfigString    ca_cert;
        ClxConfigString    client_cert;
        ClxConfigString    identity;
        ClxConfigString    private_key;
        ClxConfigString    anonymous_identity;
        ClxConfigString    password;
    };

    const s1* keyMgmt = NULL;

    struct NetworkCredentials securityCredentials;

    const s1* pairwise = NULL;
    const s1* groupwise = NULL;
    const s1* groupMgmt = NULL;

    u4 ieee80211w = 0;

    clxInitLocalServiceObject(staHandle, &stationService);

    clxConfigInitParamsList(&securityCredentials.parent, NULL, NULL);

    switch (connProfile->authTypeToUse)
    {
    case ClxAuthTypeOpenSystem:
    case ClxAuthTypePresharedKey:
    case ClxAuthTypeSAE:
    case ClxAuthTypeOWE:
#if defined(CLX_IEEE802_11_R_SUPPORTED)
    case ClxAuthTypePSK_FT:
    case ClxAuthTypeSAE_FT:
#endif
    {
        switch (connProfile->authTypeToUse)
        {
        case ClxAuthTypeOpenSystem:
            keyMgmt = "NONE";
            break;
        case ClxAuthTypePresharedKey:
            keyMgmt = "WPA-PSK";
            break;
        case ClxAuthTypeSAE:
            /* With SAE and OWE, MFP is mandatory */
            keyMgmt = "SAE";
            ieee80211w = 2;
            break;
        case ClxAuthTypeOWE:
            keyMgmt = "OWE";
            ieee80211w = 2;
            break;
#if defined(CLX_IEEE802_11_R_SUPPORTED)
        case ClxAuthTypePSK_FT:
            keyMgmt = "FT-PSK";
            ieee80211w = 1;
            break;
        case ClxAuthTypeSAE_FT:
            /* With SAE and OWE, MFP is mandatory */
            keyMgmt = "FT-SAE";
            ieee80211w = 2;
            break;
#endif
        default:
            BLACKBOX;
            return CLX_FAIL;
        }

        clxConfigInitValueParam(&securityCredentials.key_mgmt, "key_mgmt", (void*)keyMgmt, 0, &securityCredentials.parent);

        if (connProfile->authTypeToUse != ClxAuthTypeOpenSystem)
        {
            if (connProfile->securityCredential.keyLen == 32)
            {
                clxConfigInitDataParam(&securityCredentials.key, "psk", connProfile->securityCredential.key, 32, &securityCredentials.parent);
            }
            else if (connProfile->securityCredential.passwdPhrase)
            {
                clxConfigInitStringParam(&securityCredentials.passwdPhrase, "psk", connProfile->securityCredential.passwdPhrase, &securityCredentials.parent);
            }
            else
            {
                return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
            }

            clxConfigInitIntegerParam(&securityCredentials.ieee80211w, "ieee80211w", ieee80211w, &securityCredentials.parent);
        }
    }
    break;

    case ClxAuthTypeIEEE802_1x:
    case ClxAuthTypeIEEE802_1x_SHA256:
    case ClxAuthTypeIEEE802_1x_SUITE_B:
    case ClxAuthTypeIEEE802_1x_SUITE_B_192:
#if defined(CLX_IEEE802_11_R_SUPPORTED)
    case ClxAuthTypeIEEE802_1x_FT:
    case ClxAuthTypeIEEE802_1x_FT_SHA384:
#endif
    {
        switch (connProfile->authTypeToUse)
        {
        case ClxAuthTypeIEEE802_1x:
            keyMgmt = "WPA-EAP";
            break;
        case ClxAuthTypeIEEE802_1x_SHA256:
            keyMgmt = "WPA-EAP-SHA256";
            ieee80211w = 2;
            break;
        case ClxAuthTypeIEEE802_1x_SUITE_B:
            keyMgmt = "WPA-EAP-SUITE-B";
            ieee80211w = 2;
            break;
        case ClxAuthTypeIEEE802_1x_SUITE_B_192:
            keyMgmt = "WPA-EAP-SUITE-B-192";
            ieee80211w = 2;
            break;
#if defined(CLX_IEEE802_11_R_SUPPORTED)
        case ClxAuthTypeIEEE802_1x_FT:
            keyMgmt = "FT-EAP";
            break;
        case ClxAuthTypeIEEE802_1x_FT_SHA384:
            keyMgmt = "FT-EAP-SHA384";
            ieee80211w = 2;
            break;
#endif
        default:
            BLACKBOX;
        }

        clxConfigInitValueParam(&securityCredentials.key_mgmt, "key_mgmt", (void*)keyMgmt, 0, &securityCredentials.parent);

        const s1* menu =
            "EAP-TTLS-MSCHAPv2\0"
            "EAP-PEAP-MSCHAPv2\0"
            "EAP_TLS\0"
            "Return to main menu";

        u4 eapMethod = clxConsoleUIEngineShowMenu("EAP Method", menu, 4);

        if (eapMethod == 4)
        {
            return 0;
        }

        static s1 ca_cert[64];

        clxConsoleUIEngineInputBox("\nCA Certificate File Path: ", ca_cert, sizeof(ca_cert));
        clxConfigInitStringParam(&securityCredentials.ca_cert, "ca_cert", ca_cert, &securityCredentials.parent);

        static s1 identity[64];

        clxConsoleUIEngineInputBox("Identity: ", identity, sizeof(identity));
        clxConfigInitStringParam(&securityCredentials.identity, "identity", identity, &securityCredentials.parent);

        static s1 password[64];

        if ((eapMethod == 1) || (eapMethod == 2))
        {
            static s1 anonymous_identity[64];

            clxConsoleUIEngineInputBox("Anonymous Identity: ", anonymous_identity, sizeof(anonymous_identity));
            clxConfigInitStringParam(&securityCredentials.anonymous_identity, "anonymous_identity", anonymous_identity, &securityCredentials.parent);

            clxConsoleUIEngineInputBox("Password: ", password, sizeof(password));
            clxConfigInitStringParam(&securityCredentials.password, "password", password, &securityCredentials.parent);
        }
        else if (eapMethod == 3)
        {
            static s1 client_cert[64];

            clxConsoleUIEngineInputBox("\nClient Certificate File Path: ", client_cert, sizeof(client_cert));
            clxConfigInitStringParam(&securityCredentials.client_cert, "client_cert", client_cert, &securityCredentials.parent);

            static s1 private_key[64];
            clxConsoleUIEngineInputBox("\nClient Private Key File Path: ", private_key, sizeof(private_key));
            clxConfigInitStringParam(&securityCredentials.private_key, "private_key", private_key, &securityCredentials.parent);

            clxConsoleUIEngineInputBox("\nClient Private Key Password: ", password, sizeof(password));
            clxConfigInitStringParam(&securityCredentials.password, "private_key_passwd", password, &securityCredentials.parent);
        }

        if (eapMethod == 1)
        {
            clxConfigInitValueParam(&securityCredentials.eap, "eap", (void*)"TTLS", 0, &securityCredentials.parent);
        }
        else if (eapMethod == 2)
        {
            clxConfigInitValueParam(&securityCredentials.eap, "eap", (void*)"PEAP", 0, &securityCredentials.parent);
        }
        else if (eapMethod == 3)
        {
            clxConfigInitValueParam(&securityCredentials.eap, "eap", (void*)"TLS", 0, &securityCredentials.parent);
        }

        /* Disable TLS time check (comment this out if the local OS has local time support such as Windows and Linux : */
        clxConfigInitStringParam(&securityCredentials.phase1, "phase1", "tls_disable_time_checks=1", &securityCredentials.parent);

        clxConfigInitStringParam(&securityCredentials.phase2Auth, "phase2", "auth=MSCHAPV2", &securityCredentials.parent);
    }
    break;
    default:
        return 0;
    }

    switch (connProfile->cipherSuite)
    {
    case 0:		/* OpenSystem */
        break;
    case CLX_IEEE80211_TKIP_OUI:
        pairwise = "TKIP";
        groupwise = "TKIP";
        break;
    case CLX_IEEE80211_CCMP_OUI:
        pairwise = "CCMP";
        groupwise = "TKIP CCMP";
        break;
    case CLX_IEEE80211_CCMP_256_OUI:
        pairwise = "CCMP-256 GCMP GCMP-256";
        groupwise = pairwise;
        groupMgmt = "BIP-CMAC-256 ";
        break;
    case CLX_IEEE80211_GCMP_256_OUI:
        pairwise = "GCMP-256";
        groupwise = "GCMP-256";
        break;
    default:
        BLACKBOX;
    }

    if (pairwise)
    {
        clxConfigInitValueParam(&securityCredentials.pairwiseCipher, "pairwise", (void*)pairwise, 0, &securityCredentials.parent);
    }

    if (groupwise)
    {
        clxConfigInitValueParam(&securityCredentials.groupwiseCipher, "group", (void*)groupwise, 0, &securityCredentials.parent);
    }

    if (groupMgmt)
    {
        clxConfigInitValueParam(&securityCredentials.groupMgmtCipher, "group_mgmt", (void*)groupMgmt, 0, &securityCredentials.parent);
    }

    clxConfigInitIntegerParam(&securityCredentials.ieee80211w, "ieee80211w", ieee80211w, &securityCredentials.parent);

#ifdef WPA_SUPPLICANT_2_9
    u1* bssid = NULL;

    if (connProfile->bssid[0] != 0xFF)
    {
        bssid = connProfile->bssid;
    }
    
    return clxWpaSupplicant_AddWirelessNetwork(&stationService, &connProfile->ssid, bssid, &securityCredentials.parent, TRUE);
#else /* WPA_SUPPLICANT_2_10 */
    return clxWpaSupplicant_AddWirelessNetwork(&stationService, &connProfile->ssid, &securityCredentials.parent, TRUE);
#endif
}
#endif

ClxResult clxWlanAppFindUserConnectionDetailsByDiscoveredBss(ClxWlanConnectionProfile* connProfile, const ClxDiscoveredBss* bss)
{
    clxStrCpy(connProfile->ssid.value, bss->ssid.value);
    connProfile->ssid.len = bss->ssid.len;

    clxMemCpy(connProfile->bssid, bss->base.macAddress, CLX_MAC_ADDRESS_LENGTH);

#if defined(CLX_WPA_SUPPLICANT)
    if (bss->authTypes & (u4)ClxAuthTypeIEEE802_1x)
    {
        connProfile->authTypeToUse = ClxAuthTypeIEEE802_1x;
    }
    else
#endif
        if (bss->authTypes & (u4)ClxAuthTypeSAE)
        {
            connProfile->authTypeToUse = ClxAuthTypeSAE;
        }
        else if (bss->authTypes & (u4)ClxAuthTypeOWE)
        {
            connProfile->authTypeToUse = ClxAuthTypeOWE;
        }
        else if (bss->authTypes & (u4)ClxAuthTypePresharedKey)
        {
            connProfile->authTypeToUse = ClxAuthTypePresharedKey;
        }
        else if (bss->authTypes & (u4)ClxAuthTypeOpenSystem)
        {
            connProfile->authTypeToUse = ClxAuthTypeOpenSystem;
        }
        else
        {
            return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        }

    if (bss->supportedEncProtocols & ClxEncProtoAES_CCMP)
    {
        connProfile->cipherSuite = CLX_IEEE80211_CCMP_OUI;
    }
    else if (bss->supportedEncProtocols & ClxEncProtoTKIP)
    {
        connProfile->cipherSuite = CLX_IEEE80211_TKIP_OUI;
    }
    else if (bss->supportedEncProtocols & ClxEncProtoNONE)
    {
        connProfile->cipherSuite = 0;
    }
    else
    {
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
    }

    return CLX_SUCCESS;
}

static ClxResult getUserConnectionDetails(ClxWlanConnectionProfile* connProfile, const ClxDiscoveredBss* bss)
{
    s1 ssid[33];

    if (bss)
    {
        clxStrCpy(connProfile->ssid.value, bss->ssid.value);
        connProfile->ssid.len = bss->ssid.len;

        clxMemCpy(connProfile->bssid, bss->base.macAddress, CLX_MAC_ADDRESS_LENGTH);
    }
    else
    {
        clxConsoleUIEngineInputBox("Enter SSID to connect to: ", ssid, sizeof(ssid));

        clxStrCpy(connProfile->ssid.value, ssid);

        connProfile->ssid.len = (u1)clxStrLen(ssid);
        connProfile->ssid.value[connProfile->ssid.len] = 0;

        memset(connProfile->bssid, 0xff, CLX_MAC_ADDRESS_LENGTH);
    }

    const s1* menu = "Open System\0"
        "WPA2 Personal (CCMP)\0"                         /* SHA1 */
#if defined(CLX_WPA_SUPPLICANT)
        "WPA3 Personal (CCMP)\0"                         /* SAE */
        "WPA2 Enterprise (CCMP)\0"                       /* SHA1 */
        "WPA3 Enterprise (CCMP)\0"                       /* SHA256 */
        "WPA3 Enterprise (GCMP-256)\0"                   /* SHA256 */
        "WPA3 Enterprise Suite B 192Bit (GCMP-256)\0"    /* SHA384 */
#   if defined(CLX_IEEE802_11_R_SUPPORTED)
        "FT Over IEEE802.11x\0"
        "FT Over IEEE802.11x SHA384\0"
        "FT Over PSK\0"
        "FT Over SAE\0"
#   endif
#endif
        "Return to main menu";

    u4 numOfItems = 3;

#ifdef CLX_WPA_SUPPLICANT
    numOfItems += 5;
#   if defined(CLX_IEEE802_11_R_SUPPORTED)
    numOfItems += 4;
#   endif
#endif

    u4 auth = clxConsoleUIEngineShowMenu("Authentication Type", menu, numOfItems);

    connProfile->cipherSuite = CLX_IEEE80211_CCMP_OUI;

    switch (auth)
    {
    case 1:
        connProfile->authTypeToUse = ClxAuthTypeOpenSystem;
        connProfile->cipherSuite = 0;
        break;
    case 2:
        connProfile->authTypeToUse = ClxAuthTypePresharedKey;
        break;
#if defined(CLX_WPA_SUPPLICANT)
    case 3:
        connProfile->authTypeToUse = ClxAuthTypeSAE;
        break;
    case 4:
        connProfile->authTypeToUse = ClxAuthTypeIEEE802_1x;
        break;
    case 5:
        connProfile->authTypeToUse = ClxAuthTypeIEEE802_1x_SHA256;
        break;
    case 6:
        connProfile->authTypeToUse = ClxAuthTypeIEEE802_1x_SHA256;
        connProfile->cipherSuite = CLX_IEEE80211_GCMP_256_OUI;
        break;
    case 7:
        connProfile->authTypeToUse = ClxAuthTypeIEEE802_1x_SUITE_B_192;
        connProfile->cipherSuite = CLX_IEEE80211_GCMP_256_OUI;
        break;
#   if defined(CLX_IEEE802_11_R_SUPPORTED)
    case 8:
        connProfile->authTypeToUse = ClxAuthTypeIEEE802_1x_FT;
        break;
    case 9:
        connProfile->authTypeToUse = ClxAuthTypeIEEE802_1x_FT_SHA384;
        break;
    case 10:
        connProfile->authTypeToUse = ClxAuthTypePSK_FT;
        break;
    case 11:
        connProfile->authTypeToUse = ClxAuthTypeSAE_FT;
        break;
#   endif
#endif
    default:
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
    }

    return CLX_SUCCESS;
}


/*********************
Public APIs:
*********************/

ClxResult clxWlanStartStationInterface(ClxHandle staHandle,
                                       u2 maxTxPower,
                                       u2 macLayerMTU,
                                       u2 rtsThreshold,
                                       ClxConfigList* extraConfigParameters)
{
    ClxResult  ret = CLX_SUCCESS;
    const DriverOps* drv = GetDriverOps();
    if (!drv) {
        return CLX_FAIL;
    }

#ifdef CLX_WPA_SUPPLICANT
    ClxService stationService;
#endif

    /*
    Define a structure to contain all the initial configuration parameters to be
    passed to clxWlanStartInterface() for the local station (Station role).

    All objects SHALL be initialized using the initialization functions provided for each configuration type.
    */
    struct StationConfig
    {
        ClxConfigList     parentList;
        struct
        {
            ClxWlanConfigRate rates[MAX_NUMBER_OF_RATES];
            ClxConfigArray    ratesArray;
        }
        supportedRates;
#if defined(CLX_WL12XX) || defined(CLX_MARVELL)
        ClxConfigInteger  maxTxPower;
#endif
        ClxConfigInteger  rtsThreshold;
        ClxConfigInteger  macLayerMTU;
        ClxConfigData     interfaceMacAddress;
        ClxConfigInteger  connectionBssInfoMaxAge;
    };

    struct StationConfig stationConfig;

#ifdef CLX_WPA_SUPPLICANT
    clxInitLocalServiceObject(staHandle, &stationService);
#endif

    /*
    Initialize the parent list object (stationConfig.parentList) which is to hold all other configuration objects (SHALL be initialized first):
    */
    clxConfigInitParamsList(&stationConfig.parentList, NULL, NULL);

    /*
    These values are recommended by the driver:
    */
#if defined(CLX_WL12XX) || defined(CLX_MARVELL)
    clxConfigInitIntegerParam(&stationConfig.maxTxPower,   "MaxTxPower", maxTxPower, &stationConfig.parentList);            /* Maximum TX Power to be used by WL12xx hardware, in dBm */
#endif
    clxConfigInitIntegerParam(&stationConfig.macLayerMTU,  "MacLayerMTU", macLayerMTU, &stationConfig.parentList);            /* Maximum size of MAC frames which can be sent without fragmentation */
    clxConfigInitIntegerParam(&stationConfig.rtsThreshold, "RTSThreshold", rtsThreshold, &stationConfig.parentList);            /* RTS/CTS Threshold */

    clxConfigInitIntegerParam(&stationConfig.connectionBssInfoMaxAge, "ConnectionBssInfoMaxAge", 60, &stationConfig.parentList);            /* RTS/CTS Threshold */

    if (userMacAddress)
    {
        /*
        If 'InterfaceMacAddress' parameter is not set, the physical MAC address of WiLink controller will be used for this interface.
        NOTE : In case of Multi role, each interface MUST have a different MAC address.
        */
        clxConfigInitDataParam(&stationConfig.interfaceMacAddress, "InterfaceMacAddress", userMacAddress, CLX_MAC_ADDRESS_LENGTH, &stationConfig.parentList);
    }

    clxWlanInitRates(stationConfig.supportedRates.rates, &stationConfig.supportedRates.ratesArray, &stationConfig.parentList);

    if (extraConfigParameters)
    {
        stationConfig.parentList.last->next = extraConfigParameters->first;
        stationConfig.parentList.last = extraConfigParameters->last;
    }

    /*
    Start the interface as a station. Since this is the only interface we start in this application, the driver will perform many operations as follows:

    - The Bus driver (e.g. SDIO) is initialized and prepared for communication with the WLAN controller.
    - The controller is booted.
    - The firmware is loaded into the controller.
    - Initial configuration parameters are set.
    - The requested role is enabled in the controller.
    */
    ret = clxWlanStartInterface(staHandle,                  /* Handle to the virtual interface as returned by clxWlanCreateInterface                                            */
        &stationConfig.parentList,                          /* A pointer to parent list object containing all the initial configuration parameters                              */
        TRUE);                                              /* Blocking mode. Do no return until the interface starting procedure is complete either with success or in error   */

    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("Starting the WLAN virtual interface failed with error %s\n", clxGetWlanErrorCodeText(ret));
        goto Failure_StartInterface;
    }

#ifdef CLX_WPA_SUPPLICANT
    /* We add the interface to WPA Supplicant: */
#ifdef WPA_SUPPLICANT_2_9
    /* We add the interface to WPA Supplicant: */
    ret = clxWpaSupplicant_AddInterface(&stationService, "CLX-STA", WPA_SUPPLICANT_CONFIG_FILE, TRUE);
#else /* WPA_SUPPLICANT_2_10 */
    /* We add the interface to WPA Supplicant: */
    ret = clxWpaSupplicant_AddInterface(&stationService, "CLX-STA", ClxIfTypeSTA, WPA_SUPPLICANT_CONFIG_FILE, TRUE);
#endif
    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nAdding the interface to WPA Supplicant failed with error %s\n", clxGetWlanErrorCodeText(ret));

        goto Failure_AddInterface;
    }
#endif
    u1 macAddr[CLX_MAC_ADDRESS_LENGTH];

    /* Get the MAC address of this virtual interface (This is only available after the interface is successfully started): */
    clxWlanInterfaceGetMacAddr(staHandle, macAddr, TRUE);
    clxConsoleUIEngineText("WLAN virtual interface started with MAC address %02X:%02X:%02X:%02X:%02X:%02X\n",
        macAddr[0],
        macAddr[1],
        macAddr[2],
        macAddr[3],
        macAddr[4],
        macAddr[5]);

    /*
    Structure containing the configuration parameter used to obtain the Firmware version of the WL1xx controller.
    NOTE : A parent list object of type ClxConfigList is always required to pass any configuration parameters to the WLAN stack/driver
    even if there is only one parameter being passed:
    */
    struct FwVersion
    {
        ClxConfigList       parentList;
        ClxConfigData       fwVersion;
        u1                  fwVersionBuf[32];
    };

    struct FwVersion fwVersion;

    /* The parent list to be passed to clxConfigInitParamsList. SHALL be initialized first: */
    clxConfigInitParamsList(&fwVersion.parentList, NULL, NULL);

    /*
    The buffer fwVersion.fwVersionBuf is assigned to the object of type ClxConfigData.
    When clxWlanGetParametersValue returns, fwVersion.fwVersionBuf will hold the Firmware version, in ASCII format:
    */
    clxConfigInitDataBufferParam(&fwVersion.fwVersion, WLAN_FIRMWARE_VERSION_CONFIG_NAME, fwVersion.fwVersionBuf, sizeof(fwVersion.fwVersionBuf), &fwVersion.parentList);

    /* Retrieve the requested parameters from the Wlan driver: */

    ret = clxWlanGetParametersValue(staHandle,            /* Handle to the virtual interface as returned by clxWlanCreateInterface    */
        &fwVersion.parentList,                                      /* A pointer to parent list object containing the parameter (fwVersion.fwVersion)                     */
        TRUE);                                                      /* Blocking mode. Do no return until the parameter is read from the driver                            */

    if (ret == CLX_SUCCESS)
    {
#if defined(CLX_WILINK)
        clxConsoleUIEngineText("Firmware Version : %s\n", fwVersion.fwVersionBuf);
#else
        clxConsoleUIEngineText("Firmware Version : %d.%d.%d.p%d\n", fwVersion.fwVersionBuf[2],
            fwVersion.fwVersionBuf[1],
            fwVersion.fwVersionBuf[0],
            fwVersion.fwVersionBuf[3]);
#endif
    }

    ret = drv->configureParameters(staHandle);
    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nSetting configuration parameters failed with error %s\n", clxGetWlanErrorCodeText(ret));
        goto Failure_Config;
    }

#ifdef CLX_WLAN_ROAMING_ENABLE
    roamingModule = clxWlanCreateRoamingModule(staHandle);
#endif

    return CLX_SUCCESS;

Failure_Config:
#ifdef CLX_WPA_SUPPLICANT
    clxWpaSupplicant_RemoveInterface(&stationService, TRUE);
#endif

#ifdef CLX_WPA_SUPPLICANT
    Failure_AddInterface :
    clxWlanStopInterface(staHandle, TRUE);
#endif

Failure_StartInterface:
    return ret;
}

ClxResult clxStopStationInterface(ClxHandle staHandle)
{
    ClxResult ret = CLX_SUCCESS;

#ifdef CLX_WPA_SUPPLICANT
    ClxService stationService;

    clxInitLocalServiceObject(staHandle, &stationService);
#endif

    /*
    Disconnect from the network. This will peacefully disconnect the local machine from the network by sending De-Authentication and De-Association
    frames to the AccessPoint:
    */
    ret = clxWlanDisconnect(staHandle, NULL, TRUE);

    if (ret != CLX_ERROR_CONNECTION_NOT_EXIST)
    {
        clxConsoleUIEngineText("\nDisconnection is complete with result %d %s", ret, clxGetWlanErrorCodeText(ret));
    }

#ifdef CLX_WLAN_ROAMING_ENABLE
    clxWlanDestroyRoamingModule(roamingModule);
#endif

#ifdef CLX_WPA_SUPPLICANT
    ret = clxWpaSupplicant_RemoveInterface(&stationService, TRUE);
    clxConsoleUIEngineText("\nRemoving interface from WPA Supplicant is complete with result %s", clxGetWlanErrorCodeText(ret));
#endif
    /* Stop the virtual interface: */
    ret = clxWlanStopInterface(staHandle, TRUE);
    clxConsoleUIEngineText("\nStopping interface is complete with result %s", clxGetWlanErrorCodeText(ret));

    return ret;
}

ClxResult clxWlanAppGetConnectionInfo(ClxHandle staHandle, ClxConnInfo*connInfo)
{
        /* Initialize the parent list first: */
        clxConfigInitParamsList(&connInfo->parentList, NULL, NULL);

        /*
        The values to which we set the values are not important. They will be set by the stack.
        Only connInfo.channel.channelNumber and connInfo.channel.frequencyBand will be set by the stack:
        */
        clxConfigInitChannelParam(&connInfo->channel,
            "CurrentChannel",
            0,
            ClxWlanFreqBand2_4GHz,
            0,
            0,
            &connInfo->parentList);

        /* Assign connInfo.bssidBuf to connInfo.bssid object: */
        clxConfigInitDataBufferParam(&connInfo->bssid,
            "CurrentBSSID",
            connInfo->bssidBuf,
            sizeof(connInfo->bssidBuf),
            &connInfo->parentList);

        ClxResult ret = clxWlanGetParametersValue(staHandle,   /* Handle to the virtual interface as returned by clxWlanCreateInterface                                                */
            &connInfo->parentList,                             /* A pointer to the parent list object containing the CurrentChannel and CurrentBSSID parameter objects                 */
            TRUE);                                             /* Blocking mode                                                                                                        */

        if (ret == CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nConnection at channel %u. BSSID = %02X:%02X:%02X:%02X:%02X:%02X\n",
                connInfo->channel.channelNumber,
                connInfo->bssidBuf[0],
                connInfo->bssidBuf[1],
                connInfo->bssidBuf[2],
                connInfo->bssidBuf[3],
                connInfo->bssidBuf[4],
                connInfo->bssidBuf[5]);
        }
        return ret;
}

ClxResult clxWlanConnectStationInterface(ClxHandle staHandle)
{
    ClxResult ret = CLX_SUCCESS;
    ClxDiscoveredBss* bss = NULL;
    ClxWlanConnectionProfile connProfile;
    const DriverOps* drv = GetDriverOps();
    if (!drv) {
        return CLX_FAIL;
    }

    s4 bssIndex = clxWlanScanSelectDiscoveredBSS(staHandle);

    if (bssIndex >= 0)
    {
        bss = clxWlanScanGetDiscoveredBSSByIndex((u4)bssIndex);
        CLX_ASSERT(bss);
    }

    ret = getUserConnectionDetails(&connProfile, bss);
    if (ret != CLX_SUCCESS)
    {
        return ret;
    }

    /* Initialize the encryption-related parameters with zero: */
    connProfile.securityCredential.keyLen = 0;
    memset(connProfile.securityCredential.passwdPhrase, 0, sizeof(connProfile.securityCredential.passwdPhrase));
    memset(connProfile.securityCredential.key, 0, sizeof(connProfile.securityCredential.key));

    switch (connProfile.authTypeToUse)
    {
    case ClxAuthTypePresharedKey:
    case ClxAuthTypeSAE:
#if defined(CLX_IEEE802_11_R_SUPPORTED)
    case ClxAuthTypePSK_FT:
    case ClxAuthTypeSAE_FT:
    case ClxAuthTypePSK_FT_SHA384:
#endif
        {
            /* define a larger array in case user enters more than 64 character */
            s1 pwd[70];
            clxConsoleUIEngineText("\nPasskey should be between 8-63, if 64 characters are entered they need to be hex numbers.");
            clxConsoleUIEngineInputBox("\nEnter Encryption Passkey (Max 63 characters) or Master Key (64 hex): ", pwd, sizeof(pwd));
            u4 passLength = strlen(pwd);

            if ((passLength > 64) || (passLength < 8))
            {
                clxConsoleUIEngineText("\nInvalid Password, it's longer than 64.");
                return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
            }
            else if (passLength == 64)
            {
                /* keyLen shall be set to 32 for HEX key */
                connProfile.securityCredential.keyLen = 32;
                if (clxAsciiToBinary(connProfile.securityCredential.key, (u1*)pwd, 64) != CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("\nEnter only hex values(0-9 or a-f)");
                    return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
                }
            }
            else
            {
                strcpy(connProfile.securityCredential.passwdPhrase, pwd);
            }
        }
        break;

    default:
        break;
    }

#ifdef CLX_WPA_SUPPLICANT
    ret = clxAddWpaSupplicantNetwork(staHandle, &connProfile);

    if (ret != CLX_SUCCESS)
    {
        return ret;
    }
#endif /* #ifdef CLX_WPA_SUPPLICANT */

    ret = clxWlanScanConfigure(staHandle, bss, ClxWlanActiveScan);
    if (ret != CLX_SUCCESS)
    {
        return ret;
    }

    /* Connect to the network identified by the information given in connProfile: */
    ret = clxWlanConnect(staHandle, &connProfile, TRUE);

    /*
    Show the connection details
    */
    clxConsoleUIEngineText("\nConnection to %s is complete with result %d %s",
        connProfile.ssid.value,
        ret,
        clxGetWlanErrorCodeText(ret));

    if (ret == CLX_SUCCESS)
    {
        ClxConnInfo connInfo;
        clxWlanAppGetConnectionInfo(staHandle, &connInfo);
#ifdef CLX_WLAN_ROAMING_ENABLE
        clxWlanRoamingModule_QueueConnectionEvent(roamingModule, connProfile.ssid.value);
#endif
    }

    return ret;
}

/*******************************************************************************************************************************
*                                                       showStationMenu
*
* Provide the Station Role UI menu.
*
*******************************************************************************************************************************/
void showStationMenu(ClxStack stack)
{
    ClxError error;
    static ClxHandle wlanStationHandle = NULL;
    const DriverOps* drv = GetDriverOps();
    if (!drv) {
        return;
    }

    while (1)
    {
        const s1* menu = "Start Interface as Station\0"
            "Scan\0"
            "Scan for a specific SSID\0"
            "Connect to wireless network\0"
            "Disconnect from wireless network\0"
            "Probe the AccessPoint\0"
            "Memory statistics\0"
            "Stop Interface\0"
            "Get Signal Strength Information\0"
            "Get Statistics Information\0"
            "Get WLAN module temperature\0"
            "Start Background Scan\0"
            "Stop Background Scan\0"
            "Get List of Wpa_Supplicant network entries\0"
            "Set FTM (IEEE802.11mc) configuration\0"
            "Start FTM (IEEE802.11mc) session\0"
            "Stop FTM (IEEE802.11mc) session\0"
        	"Set Bandwidth Limit\0"
            "Set Bandwidth Limit Exception Ports\0"
        	"Get current Bandwidth usage\0"
#if defined(CLX_MLAN_RF_TEST_MODE)
            "RF Test Mode\0"
#endif
            "Return to previous menu";

#if defined(CLX_MLAN_RF_TEST_MODE)
        u4 s = clxConsoleUIEngineShowMenu("WLAN STA Menu", menu, 22);
#else
        u4 s = clxConsoleUIEngineShowMenu("WLAN STA Menu", menu, 21);
#endif
        if (s == 1)
        {
            ClxConfigList extraList;
            clxConfigInitParamsList(&extraList, NULL, NULL);
            ClxResult ret;

            if (!wlanStationHandle)
            {
                /*
                Create a single virtual interface and get a handle to it.
                The handle will to start, stop and control the virtual interface:
                */
                ret = clxWlanCreateInterface(stack, /* The WLAN stack object, as returned by clxInitClarinoxWlan()                 */
                    WLAN_INTERFACE_NAME_STA,                  /* Name of WL18xx virtual interface (fixed)                                    */
                    ClxIfTypeSTA,
                    createNetworkAccessInterface(),
                    &wlanStationHandle);                      /* On a successful return, will contain a handle to the virtual interface      */

                if (ret != CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("Creation of WLAN virtual interface failed with error %d\n", ret);
                    return;
                }

                if (clxWlanStartStationInterface(wlanStationHandle,
                        DEFAULT_STA_MAX_TX_POWER,
                        DEFAULT_MAC_LAYER_MTU,
                        DEFAULT_RTS_THRESHOLD,
                        &extraList) != CLX_SUCCESS)
                {
                    clxCloseHandle(wlanStationHandle);
                    wlanStationHandle = NULL;
                }
            }
            else
            {
                clxConsoleUIEngineText("\nWiFi Station interface has already started.\n");
            }

            ret = clxWlanScanInit(TRUE);
            if (ret != CLX_SUCCESS)
            {
                clxConsoleUIEngineText("Cannot create WLAN App Scan features! %d\n", ret);
                return;
            }
        }
        else if (s == 2)
        {
            if (wlanStationHandle)
            {
                clxWlanScanStationInterface(wlanStationHandle);
            }
            else
            {
                clxConsoleUIEngineText("\nPlease start the interface as a WiFi station first.\n");
            }
        }
        else if (s == 3)
        {
            if (wlanStationHandle)
            {
                ClxSSID ssid;

                clxConsoleUIEngineInputBox("Enter SSID to scan for: ", ssid.value, sizeof(ssid.value) - 1);
                ssid.len = (u1)strlen(ssid.value);

                clxWlanScanSpecificSsid(wlanStationHandle, &ssid);
            }
            else
            {
                clxConsoleUIEngineText("\nPlease start the interface as a WiFi station first.\n");
            }
        }
        else if (s == 4)
        {
            if (wlanStationHandle)
            {
                clxWlanConnectStationInterface(wlanStationHandle);
            }
            else
            {
                clxConsoleUIEngineText("\nPlease start the interface as a WiFi station first.\n");
            }
        }
        else if (s == 5)
        {
            if (wlanStationHandle)
            {
                /*
                Disconnect from the network. This will peacefully disconnect the local machine from the network by sending De-Authentication and De-Association
                frames to the AccessPoint:
                */
#ifdef CLX_WLAN_ROAMING_ENABLE
                clxWlanRoamingModule_QueueDisconnectionEvent(roamingModule, 0);
#endif
                error = clxWlanDisconnect(wlanStationHandle, NULL, TRUE);

                clxConsoleUIEngineText("\nDisconnection is complete with result %d %s", error, clxGetWlanErrorCodeText(error));
            }
            else
            {
                clxConsoleUIEngineText("\nPlease start the interface as a WiFi station first.\n");
            }
        }
        else if (s == 6)
        {
#if defined(CLX_WILINK)
            if (wlanStationHandle)
            {

                u1 dest[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
                ClxBSSInfo bssInfo;

                /* Send probe requests to the air: */
                error = clxWlanProbe(wlanStationHandle,            /* Handle to the virtual interface as returned by clxWlanCreateInterface                                                        */
                    dest,                                           /* The destination of probe requests. dest has been set to FF:FF:FF:FF:FF:FF which is the broadcast address                     */
                    5,                                              /* The maximum number of probe requests to be sent if no probe response is received                                             */
                    1,                                              /* The time interval between consecutive probe requests, in the unit of BeaconInterval                                          */
                    &bssInfo,                                       /* The caller-provided object which on a successful return will hold information of the BSS which has responded to the probe    */
                    TRUE);                                          /* Blocking mode                                                                                                                */

                if (error == CLX_SUCCESS)
                {
                    clxWlanPrintDetailedBssInfo(&bssInfo, 0);
                }
                else
                {
                    clxConsoleUIEngineText("\nProbe failed with result %d %s", error, clxGetWlanErrorCodeText(error));
                }
            }
            else
            {
                clxConsoleUIEngineText("\nPlease start the interface as a WiFi station first.\n");
            }
#else
            clxConsoleUIEngineText("\nFeature not supported\n");
#endif
        }
        else if (s == 7)
        {
#if defined (CLX_DEBUG)
            clxConsoleUIEngineText("\nThis option is not available in Debug version. \n To view memory statistics, use the memory analyzer in Clarinox debugger.\n");
#else
            clxCheckMemoryUsage();
#endif
        }
        else if (s == 8)
        {
            if (wlanStationHandle)
            {
                error = clxStopStationInterface(wlanStationHandle);

                if (error == CLX_SUCCESS)
                {
                    error = clxCloseHandle(wlanStationHandle);

                    clxConsoleUIEngineText("\nClosing Station handle is complete with result %s", clxGetWlanErrorCodeText(error));

                    wlanStationHandle = NULL;

                    clxConsoleUIEngineText("\nPlease disable WiFi stack\n");

                    return;
                }
            }
            else
            {
                clxConsoleUIEngineText("\nPlease start the interface as a WiFi station first.\n");
            }
        }
        else if (s == 9)
        {
            for(u1 i1 = 0; i1 < 10; i1++)
            {
                clxSleep(500);
                drv->getConnectionSignalInfo(wlanStationHandle);
            }
        }
        else if( s == 10)
        {
            for(u1 i1 = 0; i1 < 5; i1++)
            {
                clxSleep(1000);
                drv->getConnectionStatInfo(wlanStationHandle);
            }
        }
        else if(s == 11)
        {
            for(u1 i1 = 0; i1 < 5; i1++)
            {
                clxSleep(1000);
                drv->getConnectionTempSensorInfo(wlanStationHandle);
            }
        }
        else if (s == 12)
        {
            clxWlanStartBGScanWithUserParams(wlanStationHandle);
        }
        else if (s == 13)
        {
#if defined(CLX_WILINK)
            clxConsoleUIEngineText("\nFeature not supported\n");
#elif defined (CLX_MARVELL)
            error = clxWlanStopBgScan(wlanStationHandle, TRUE);
            if (error != CLX_SUCCESS)
            {
                clxConsoleUIEngineText("\nclxWlanStopBgScan() failed with error %s\n", clxGetWlanErrorCodeText(error));
            }
#endif
        }
        else if (s == 14)
        {
#ifdef CLX_WPA_SUPPLICANT
            //getListOfWpaSupplicantNetworkEntries(wlanStationHandle);
#else
            clxConsoleUIEngineText("\nFeature not supported\n");
#endif
        }
        else if (s == 15)
        {
            drv->setConfigFtmSession(wlanStationHandle);
        }
        else if (s == 16)
        {
            drv->startStopFtmSession(wlanStationHandle, TRUE);
        }
        else if (s == 17)
        {
            drv->startStopFtmSession(wlanStationHandle, FALSE);
        }
        else if (s == 18)
        {
#ifdef CLX_BANDWIDTH_LIMIT_SUPPORTED
        	clxWlanSetBwLimit(wlanStationHandle);
#else
            clxConsoleUIEngineText("\nFeature not supported\n");
#endif
        }
        else if (s == 19)
        {
#ifdef CLX_BANDWIDTH_LIMIT_SUPPORTED
        	clxWlanSetBwLimitExceptPors(wlanStationHandle);
#else
            clxConsoleUIEngineText("\nFeature not supported\n");
#endif
        }
        else if (s == 20)
        {
#ifdef CLX_BANDWIDTH_LIMIT_SUPPORTED
        	clxWlanGetBwUsage(wlanStationHandle);
#else
            clxConsoleUIEngineText("\nFeature not supported\n");
#endif
        }
#if defined(CLX_MLAN_RF_TEST_MODE)
        else if (s == 21)
        {
            static s1 cmd[512];
            clxConsoleUIEngineInputBox("MLAN RF test mode > ", cmd, sizeof(cmd));
            error = clxMlanRunRfTestModeCommand(wlanStationHandle, cmd);

            if (error != CLX_SUCCESS)
            {
                clxConsoleUIEngineText("\nclxMlanRunRfTestModeCommand() failed with error %s\n", clxGetWlanErrorCodeText(error));
            }
        }
        else if (s == 22)
        {
            return;
        }
#else
        else if (s == 21)
        {
            return;
        }
#endif
    }
}

boolean clxWlanStationIndicationHandler(ClxStack stack, ClxHandle handle, u4 messageID, const void* params, ClxError errorCode)
{
    switch (messageID)
    {
    case CLX_WLAN_SCAN_COMPLETE:
        clxConsoleUIEngineText("\nScan is complete with the result : %s\n", clxGetWlanErrorCodeText(errorCode));
        break;

    case CLX_WLAN_BSS_DISCOVERED_INDICATION:
        {
            ClxWlanBssDiscoveredIndication* arg = (ClxWlanBssDiscoveredIndication*)params;
            clxWlanScanBSSDiscovered(&arg->details);

            break;
        }

    case CLX_WLAN_LINK_LOST_INDICATION:
        clxConsoleUIEngineText("\nBeacons have been lost\n");
        break;

    case CLX_WLAN_AP_DISCONNECTED_INDICATION:
        {
            ClxWlanApDisconnectedIndication* arg = (ClxWlanApDisconnectedIndication*)params;
            clxConsoleUIEngineText("\nAp disconnected with the reason: %s\n", clxGetWlanErrorCodeText(arg->reason));

            clxConsoleUIEngineText("\nMac Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                arg->macAddress[0],
                arg->macAddress[1],
                arg->macAddress[2],
                arg->macAddress[3],
                arg->macAddress[4],
                arg->macAddress[5]);

#ifdef CLX_WIFI_MESH_AUTO
            clxWlanMeshAutoQueueDisconnectionEvent(NULL, arg->reason);
#endif

            break;
        }

    case CLX_WLAN_DRIVER_SPECIFIC_INDICATION:
        {
            ClxWlanDriverSpecificIndication* arg = (ClxWlanDriverSpecificIndication*)params;
            const DriverOps* drv = GetDriverOps();
            if (drv) {
                drv->driverSpecificReport(arg);
            }
        }
        break;

    default:
        break;
    }

    return FALSE;
}
