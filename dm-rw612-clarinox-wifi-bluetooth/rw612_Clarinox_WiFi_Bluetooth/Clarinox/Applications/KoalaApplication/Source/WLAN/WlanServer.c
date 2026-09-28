/*********************************************************************************
*
* Project             Wlan Sample Application
* File                WlanServer.c
* Description         Wlan AP role application file
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include "ConsoleUIEngine.h"
#include "ClarinoxWlan.h"
#include "Wlan.Api.h"
#include "Wlan.Config.h"
#include "WlanErrors.h"
#include "WiFiApp.h"
#if defined(CLX_MARVELL)
#include "Wlan.Marvel.Config.h"
#endif

#ifdef CLX_WPA_SUPPLICANT
#   include "Wlan.WpaSupplicant.Api.h"
#endif

extern void clxCheckMemoryUsage();

#if defined(CLX_WIFI_OVER_LAN)
static const u1 userMacAddress[CLX_MAC_ADDR_LEN] = WIFI_OVER_LAN_LOCAL_AP_MAC_ADDR;
#elif defined(USER_DEFINED_ACCESSPOINT_MAC_ADDRESS)    
static const u1 userMacAddress[CLX_MAC_ADDR_LEN] = CLX_WLAN_AP_MAC_ADDRESS;
#else
static const u1* userMacAddress = NULL;
#endif

#if defined(CLX_IEEE802_11_R_SUPPORTED)
//#define FRMD_AP_1 0
static const s1 mobility_domain[] = "a3b4";
//#if (FRMD_AP_1)
//static const s1 nas_identifier_1[] = "CLX-AP-1";
//static const s1 r1_key_holder_1[] = "C095DA016235";
//static const s1 r0kh_self_1[] = "C0:95:DA:01:62:35 CLX-AP-1 11223344556677889900aabbccddeeff";
//static const s1 r0kh_peer_1[] = "C0:95:DA:01:6E:B1 CLX-AP-2 11223344556677889900aabbccddeeff";
//static const s1 r1kh_self_1[] = "C0:95:DA:01:62:35 C0:95:DA:01:62:35 11223344556677889900aabbccddeeff";
//static const s1 r1kh_peer_1[] = "C0:95:DA:01:6E:B1 C0:95:DA:01:6E:B1 11223344556677889900aabbccddeeff";
////#else
//static const s1 nas_identifier_2[] = "CLX-AP-2";
//static const s1 r1_key_holder_2[]  = "C095DA016EB1";
//static const s1 r0kh_self_2[] = "C0:95:DA:01:6E:B1 CLX-AP-2 11223344556677889900aabbccddeeff";
//static const s1 r0kh_peer_2[] = "C0:95:DA:01:62:35 CLX-AP-1 11223344556677889900aabbccddeeff";
//static const s1 r1kh_self_2[] = "C0:95:DA:01:6E:B1 C0:95:DA:01:6E:B1 11223344556677889900aabbccddeeff";
//static const s1 r1kh_peer_2[] = "C0:95:DA:01:62:35 C0:95:DA:01:62:35 11223344556677889900aabbccddeeff";

static const s1 nas_identifier_1[] = "CLX-AP-1";
static const s1 r1_key_holder_1[] = "C095DA016235";
static const s1 r0kh_self_1[] = "C0:95:DA:01:62:35 CLX-AP-1 11223344556677889900aabbccddeeff";
static const s1 r0kh_peer_1[] = "58:E8:76:E3:00:03 CLX-AP-2 11223344556677889900aabbccddeeff";
static const s1 r0kh_peer_12[] = "58:E8:76:E3:00:04 CLX-AP-3 11223344556677889900aabbccddeeff";
static const s1 r1kh_self_1[] = "C0:95:DA:01:62:35 C0:95:DA:01:62:35 11223344556677889900aabbccddeeff";
static const s1 r1kh_peer_1[] = "58:E8:76:E3:00:03 58:E8:76:E3:00:03 11223344556677889900aabbccddeeff";
static const s1 r1kh_peer_12[] = "58:E8:76:E3:00:04 58:E8:76:E3:00:04 11223344556677889900aabbccddeeff";
//#else
static const s1 nas_identifier_2[] = "CLX-AP-1";
static const s1 r1_key_holder_2[]  = "C095DA016235";
static const s1 r0kh_self_2[] = "C0:95:DA:01:62:35 CLX-AP-1 11223344556677889900aabbccddeeff";
static const s1 r0kh_peer_2[] = "58:E8:76:E3:00:04 CLX-AP-2 11223344556677889900aabbccddeeff";
static const s1 r1kh_self_2[] = "C0:95:DA:01:62:35 C0:95:DA:01:62:35 11223344556677889900aabbccddeeff";
static const s1 r1kh_peer_2[] = "58:E8:76:E3:00:04 58:E8:76:E3:00:04 11223344556677889900aabbccddeeff";
//#endif
#endif

#define MIN_PASSKEY_LENGTH				8 /* Bytes */

const char *cmdBTM_Template_1 = "%02X:%02X:%02X:%02X:%02X:%02X "
                        "pref=1 "
                        "abridged=1 "
                        "disassoc_imminent=1 "
                        "disassoc_timer=200 "
                        "valid_int=30 "
                        "neighbor=58:E8:76:E3:00:03,0x00003F77,81,1,7,0301ff";

const char *cmdBTM_Template_2 = "%02X:%02X:%02X:%02X:%02X:%02X "
						"pref=1 "
						"abridged=1 "
						"disassoc_imminent=1 "
						"disassoc_timer=200 "
						"valid_int=30 "
						"neighbor=58:E8:76:E3:00:04,0x00003F77,115,36,7,0301ff";

char cmdBTM_1[256];
char cmdBTM_2[256];


typedef struct AccessPointConfigParamsStructs
{
	ClxBSSInfo     bssInfo;

	const s1*	   passKey;
	u1			   maxTxPower;
	u4			   clientInactivityTimeout;
	u1			   maxNumberOfStations;
	boolean		   hiddenSSID;
	const s1*	   country;
} AccessPointConfigParams;


#ifdef CLX_WPA_SUPPLICANT
/* 
Check out https://web.mit.edu/freebsd/head/contrib/wpa/hostapd/hostapd.conf for more information: 
*/
static ClxResult clxWlanAddAccessPointInterfaceBss(ClxService* apService,
	const AccessPointConfigParams* configParams)
{
	struct HostApConfig
	{
		ClxConfigList       parentList;

		ClxConfigWsSymbol	hwMode;
		ClxConfigInteger	channel;
		/*ClxConfigWsSymbol   countryCode; */
		ClxConfigInteger    ieee802n;
		ClxConfigInteger    ieee802ac;
		ClxConfigInteger    ieee80211w;
		ClxConfigInteger	sae_pwe;
		ClxConfigInteger    wmmEnabled;

		ClxConfigInteger	authAlgorithm;
		ClxConfigInteger    wpa;
		ClxConfigWsSymbol	keyMgmtSuites;
		ClxConfigWsSymbol   rsnPairwise;
		ClxConfigWsSymbol   passPhrase;

		ClxConfigInteger    bssTransitionEnabled;
#ifdef CLX_IEEE802_11_R_SUPPORTED
		//802.11r releated parameters
		ClxConfigInteger    ftOverDs;
		ClxConfigInteger    ftPskGenerateLocal;
		//ClxConfigInteger	ftR0KeyLifetime;
		//ClxConfigInteger	r1MaxKeyLifetime;
		//ClxConfigInteger	reassociationDeadline;
		//ClxConfigInteger	pmkR1Push;

		ClxConfigWsSymbol		mobilityDomain;
		ClxConfigWsSymbol       nasIdentifier;
		ClxConfigWsSymbol		r1KeyHolder;
		ClxConfigWsSymbol		r0kh_self;
		ClxConfigWsSymbol		r0kh_peer;
		ClxConfigWsSymbol		r1kh_self;
		ClxConfigWsSymbol		r1kh_peer;
#endif
	};

	struct HostApConfig hostApConfig;

	clxConfigInitParamsList(&hostApConfig.parentList, NULL, NULL);

	{
		const s1* hwMode;
		hwMode = (configParams->bssInfo.band == ClxWlanFreqBand2_4GHz) ? "g" : "a";

		clxConfigInitWsSymbolParam(&hostApConfig.hwMode, "hw_mode", hwMode, &hostApConfig.parentList);
	}

	clxConfigInitIntegerParam(&hostApConfig.channel, "channel", configParams->bssInfo.channel, &hostApConfig.parentList);

	/*
	if (configParams->country)
	{
		clxConfigInitWsSymbolParam(&hostApConfig.countryCode, "country_code", configParams->country, &hostApConfig.parentList);
	}
	*/

	clxConfigInitIntegerParam(&hostApConfig.ieee802n,
		"ieee80211n",
		(configParams->bssInfo.capabilities & CLX_WLAN_CAPABILITY_HT_SUPPORTED) ? 1 : 0,
		&hostApConfig.parentList);

	clxConfigInitIntegerParam(&hostApConfig.ieee802ac,
		"ieee80211ac",
		(configParams->bssInfo.capabilities & CLX_WLAN_CAPABILITY_VHT_SUPPORTED) ? 1 : 0,
		&hostApConfig.parentList);

	clxConfigInitIntegerParam(&hostApConfig.wmmEnabled,
		"wmm_enabled",
		(configParams->bssInfo.capabilities & CLX_WLAN_CAPABILITY_WMM_SUPPORTED) ? 1 : 0,
		&hostApConfig.parentList);

	clxConfigInitIntegerParam(&hostApConfig.bssTransitionEnabled,
		"bss_transition",
		1,
		&hostApConfig.parentList);

	/* 1=wpa, 2=wep, 3=both */
	clxConfigInitIntegerParam(&hostApConfig.authAlgorithm,
		"auth_algs",
		1,
		&hostApConfig.parentList);

	/* 1=wpa only, 2=wpa2 only, 3=wpa/wpa2 */
	clxConfigInitIntegerParam(&hostApConfig.wpa,
		"wpa",
		(configParams->bssInfo.capabilities & CLX_WLAN_CAPABILITY_WPA_SUPPORTED) ? 3 : 2,
		&hostApConfig.parentList);

	{
		static s1 wpaKeyMgmt[128];
		wpaKeyMgmt[0] = '\0';

		if (configParams->bssInfo.authType & ClxAuthTypePresharedKey)
		{
			clxStrCat(wpaKeyMgmt, "WPA-PSK ");
		}

		if (configParams->bssInfo.authType & ClxAuthTypeSAE)
		{
			clxStrCat(wpaKeyMgmt, "SAE ");
		}

		if (configParams->bssInfo.authType & ClxAuthTypeOWE)
		{
			clxStrCat(wpaKeyMgmt, "OWE ");
		}

		if (configParams->bssInfo.authType & ClxAuthTypePSK_SHA256)
		{
			clxStrCat(wpaKeyMgmt, "WPA-PSK-SHA256 ");
		}

        if (configParams->bssInfo.authType & ClxAuthTypePSK_FT)
        {
            clxStrCat(wpaKeyMgmt, "FT-PSK ");
        }

        if (configParams->bssInfo.authType & ClxAuthTypeSAE_FT)
        {
            clxStrCat(wpaKeyMgmt, "FT-SAE ");
        }

		CLX_ASSERT(clxStrLen(wpaKeyMgmt) < sizeof(wpaKeyMgmt));

		clxConfigInitWsSymbolParam(&hostApConfig.keyMgmtSuites, "wpa_key_mgmt", wpaKeyMgmt, &hostApConfig.parentList);
	}

#ifdef CLX_IEEE802_11_R_SUPPORTED
    if (configParams->bssInfo.authType & (ClxAuthTypePSK_FT | ClxAuthTypeSAE_FT))
    {
        clxConfigInitIntegerParam(&hostApConfig.ftOverDs, "ft_over_ds", 0,
                &hostApConfig.parentList);

        clxConfigInitIntegerParam(&hostApConfig.ftPskGenerateLocal,
                "ft_psk_generate_local", 1, &hostApConfig.parentList);

        clxConfigInitWsSymbolParam(&hostApConfig.mobilityDomain,
                "mobility_domain", mobility_domain, &hostApConfig.parentList);

        const s1* boardSelect = "FRDM Board 1(C095DA016235)\0"
            "FRDM Board 2(C095DA016EB1)";

        s1 s = clxConsoleUIEngineShowMenu("Select the Board type:", boardSelect, 2);

        if(1 == s)
        {
            clxConfigInitWsSymbolParam(&hostApConfig.nasIdentifier,
                    "nas_identifier", nas_identifier_1, &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r1KeyHolder, "r1_key_holder",
                    r1_key_holder_1, &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r0kh_self, "r0kh", r0kh_self_1,
                    &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r0kh_peer, "r0kh", r0kh_peer_1,
                    &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r0kh_peer, "r0kh", r0kh_peer_12,
                    &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r1kh_self, "r1kh", r1kh_self_1,
                    &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r1kh_peer, "r1kh", r1kh_peer_1,
                    &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r1kh_peer, "r1kh", r1kh_peer_12,
                    &hostApConfig.parentList);
        }
        else
        {
            clxConfigInitWsSymbolParam(&hostApConfig.nasIdentifier,
                    "nas_identifier", nas_identifier_2, &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r1KeyHolder, "r1_key_holder",
                    r1_key_holder_2, &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r0kh_self, "r0kh", r0kh_self_2,
                    &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r0kh_peer, "r0kh", r0kh_peer_2,
                    &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r1kh_self, "r1kh", r1kh_self_2,
                    &hostApConfig.parentList);

            clxConfigInitWsSymbolParam(&hostApConfig.r1kh_peer, "r1kh", r1kh_peer_2,
                    &hostApConfig.parentList);
        }
	}
#endif

	{
		u1 ieee80211w = 0; /* disabled  */

		if (configParams->bssInfo.authType == ClxAuthTypeSAE)
		{
			ieee80211w = 2; /* required */
		}
		else if (configParams->bssInfo.authType & ClxAuthTypeSAE)
		{
			ieee80211w = 1; /* optional */
		}

		clxConfigInitIntegerParam(&hostApConfig.ieee80211w,
			"ieee80211w",
			ieee80211w,
			&hostApConfig.parentList);

	}

//    clxConfigInitIntegerParam(&hostApConfig.sae_pwe,
//        "sae_pwe",
//        2,
//        &hostApConfig.parentList);

	{
		static s1 rsnPairwise[64];
		rsnPairwise[0] = '\0';

		if (configParams->bssInfo.encProtocol & ClxEncProtoTKIP)
		{
			clxStrCat(rsnPairwise, "TKIP ");
		}

		if (configParams->bssInfo.encProtocol & ClxEncProtoAES_CCMP)
		{
			clxStrCat(rsnPairwise, "CCMP ");
		}

		if (configParams->bssInfo.encProtocol & ClxEncProto_CCMP_256)
		{
			clxStrCat(rsnPairwise, "CCMP-256 ");
		}

		CLX_ASSERT(clxStrLen(rsnPairwise) < sizeof(rsnPairwise));

		clxConfigInitWsSymbolParam(&hostApConfig.rsnPairwise, "rsn_pairwise", rsnPairwise, &hostApConfig.parentList);
	}

	if (configParams->passKey)
	{
		clxConfigInitWsSymbolParam(&hostApConfig.passPhrase, "wpa_passphrase", configParams->passKey, &hostApConfig.parentList);
	}

	return clxWpaSupplicant_AddHostApInterface(apService, "CLX-AP", ClxIfTypeAP, &configParams->bssInfo.ssid, &hostApConfig.parentList, TRUE);
}
#endif // CLX_WPA_SUPPLICANT

ClxResult clxWlanStartAccessPointInterface(ClxHandle apHandle, 
										   AccessPointConfigParams* configParams,
										   ClxConfigList*  extraConfigParameters)
{
	ClxResult  ret = CLX_SUCCESS;

#ifdef CLX_WPA_SUPPLICANT
	ClxService apService;
#endif

	/*
	Define a structure to contain all the initial configuration parameters to be
	passed to clxWlanStartInterface() for the local station (AccessPoint role).

	All objects SHALL be initialized using the initialization functions provided for each configuration type.
	*/
	struct ApConfig
	{
		ClxConfigList     parentList;

		struct
		{
			ClxWlanConfigRate  rates[MAX_NUMBER_OF_RATES];
			ClxConfigArray     ratesArray;
		}
		supportedRates;

		ClxConfigData     ssid;
		ClxConfigString   freqBand;
		ClxConfigInteger  channel;
		ClxConfigInteger  hiddenSSID;
		ClxConfigInteger  maxTxPower;
		ClxConfigString   channelType;
		ClxConfigInteger  beaconInterval;
		ClxConfigInteger  dtimPeriod;
		ClxConfigInteger  maxNumStations;
		ClxConfigInteger  wifiSupportedStandards;
		ClxConfigInteger  cipherSuites;
		ClxConfigInteger  clientInactivityTimeout;
		ClxConfigString   passPhrase;
		ClxConfigData     encKey;
		ClxConfigData     bssid;

#if defined(CLX_WL18XX)  
		ClxConfigInteger rxBaPolicyBitmap;
#endif
	};

	struct ApConfig apConfig;

#ifdef CLX_WPA_SUPPLICANT
	clxInitLocalServiceObject(apHandle, &apService);
#endif

	/*
	Initialize the parent list object (apConfig.parentList) which is to hold all other configuration objects (SHALL be initialized first):
	*/
	clxConfigInitParamsList(&apConfig.parentList, NULL, NULL);

	/* Maximum TX Power to be used by WL18xx hardware, in dBm */
	clxConfigInitIntegerParam(&apConfig.maxTxPower, "MaxTxPower", configParams->maxTxPower, &apConfig.parentList);

	clxWlanInitRates(apConfig.supportedRates.rates, &apConfig.supportedRates.ratesArray, &apConfig.parentList);

	const s1* freqBand;

	configParams->bssInfo.channel = (configParams->bssInfo.channel == 0) ? DEFAULT_AP_CHANNEL_NO : configParams->bssInfo.channel;

	switch(configParams->bssInfo.band)
	{
	case ClxWlanFreqBand2_4GHz:
		freqBand = "2.4GHZ";
		break;

	case ClxWlanFreqBand5GHz:
		freqBand = "5GHZ";
		break;
		
	default:
		BLACKBOX;
	}

	/* 
	SSID of the network to be established. It is NOT null-terminated. The length of the SSID is given as the forth argument: 
	*/
	clxConfigInitDataParam    (&apConfig.ssid,					 "SSID",					(u1*)configParams->bssInfo.ssid.value,		configParams->bssInfo.ssid.len, &apConfig.parentList);
	clxConfigInitStringParam  (&apConfig.freqBand,				 "FreqBand",				freqBand,									&apConfig.parentList);           /* The frequency band in which the BSS will operate                             */
	clxConfigInitIntegerParam (&apConfig.channel,				 "Channel",					configParams->bssInfo.channel,				&apConfig.parentList);           /* The channel on which the BSS will operate (2.4GHZ or 5GHZ)                   */
	clxConfigInitIntegerParam (&apConfig.hiddenSSID,			 "HiddenSSID",				configParams->hiddenSSID,					&apConfig.parentList);           /* The SSID will be hidden (if value 1) or will be transparent (if value is 0)  */
	clxConfigInitStringParam  (&apConfig.channelType,			 "ChannelType",				"NO_HT",									&apConfig.parentList);           /* The frequency channel type (NO_HT for traditional 20MHz channels)            */
	clxConfigInitIntegerParam (&apConfig.beaconInterval,		 "BeaconInterval",			configParams->bssInfo.beaconInterval,		&apConfig.parentList);           /* Beacon Interval in milliseconds                                              */
	clxConfigInitIntegerParam (&apConfig.dtimPeriod,			 "DtimPeriod",				configParams->bssInfo.dtimPeriod,			&apConfig.parentList);           /* DTIM period in units of BeaconInterval                                     */
	clxConfigInitIntegerParam (&apConfig.maxNumStations,		 "Ap.MaxNumberOfStations",	configParams->maxNumberOfStations,			&apConfig.parentList);           /* Max number of clients which can join the BSS at the same time                */

	u4 wifiSupportedStandards = 0;
	if (configParams->bssInfo.capabilities & CLX_WLAN_CAPABILITY_WPA_SUPPORTED)
	{
		wifiSupportedStandards |= ClxWifiSupportedStandard_WPA;
	}
	if (configParams->bssInfo.authType & ClxAuthTypePresharedKey)
	{
		wifiSupportedStandards |= ClxWifiSupportedStandard_WPA2;
	}
	if (configParams->bssInfo.authType & (ClxAuthTypeSAE & ClxAuthTypeOWE))
	{
		wifiSupportedStandards |= ClxWifiSupportedStandard_WPA3;
	}

	clxConfigInitIntegerParam(&apConfig.wifiSupportedStandards, "WifiSupportedStandards",	wifiSupportedStandards,						&apConfig.parentList);			 /* Wi-Fi standards supported by the AccessPoint */

	if (configParams->passKey)
	{
		/*
		You may also use the parameter "Ap.EncryptionKey" of type ClxConfigData in order to give the 32byte key directly to the stack.
		In this case, Ap.EncryptionPasskey is not required and will be ignored:
		*/
		clxConfigInitStringParam(&apConfig.passPhrase,	 "Ap.EncryptionPasskey",	configParams->passKey, &apConfig.parentList);           /* The encryption passkey used to generate the master key                       */
	}

	clxConfigInitIntegerParam(&apConfig.cipherSuites,	 "Ap.EncryptionProtocol",	configParams->bssInfo.encProtocol, &apConfig.parentList);           /* The encryption protocol(s) supported by the BSS (values can be ORes)         */

	static const s1 zeroMacAddress[] = { 0, 0, 0, 0, 0, 0 };

	if (clxMemCmp(configParams->bssInfo.bssid, zeroMacAddress, CLX_MAC_ADDRESS_LENGTH) != 0)
	{
		clxConfigInitDataParam(&apConfig.bssid,			 "InterfaceMacAddress",		configParams->bssInfo.bssid, CLX_MAC_ADDRESS_LENGTH, &apConfig.parentList);
	}

	/* The maximum time, in seconds, for an associated client to be inactive before it is de-associated and removed from the BSS: */
	clxConfigInitIntegerParam(&apConfig.clientInactivityTimeout, "ClientInactivityTimeout", configParams->clientInactivityTimeout /* Seconds */, &apConfig.parentList);


#if defined(CLX_WL18XX)  
	clxConfigInitIntegerParam(&apConfig.rxBaPolicyBitmap, "Wl18xx.RxBaPolicyBitmap", 0x00FF, &apConfig.parentList);
#endif

	if (extraConfigParameters)
	{
		apConfig.parentList.last->next = extraConfigParameters->first;
		apConfig.parentList.last =	     extraConfigParameters->last;
	}


	ret = clxWlanStartInterface(apHandle, &apConfig.parentList, TRUE);

	if (ret != CLX_SUCCESS)
	{
		clxConsoleUIEngineText("Starting the WLAN virtual AccessPoint failed with error %s\n", clxGetWlanErrorCodeText(ret));
		goto Failure_StartInterface;
	}

	clxWlanInterfaceGetMacAddr(apHandle, configParams->bssInfo.bssid, TRUE);

	clxConsoleUIEngineText("WLAN virtual interface started with MAC address %02X:%02X:%02X:%02X:%02X:%02X\n",
		configParams->bssInfo.bssid[0],
		configParams->bssInfo.bssid[1],
		configParams->bssInfo.bssid[2],
		configParams->bssInfo.bssid[3],
		configParams->bssInfo.bssid[4],
		configParams->bssInfo.bssid[5]);

#ifdef CLX_WPA_SUPPLICANT
	/* We add the interface to wpa_supplicant: */
	ret = clxWlanAddAccessPointInterfaceBss(&apService, configParams);
	if (ret != CLX_SUCCESS)
	{
		clxConsoleUIEngineText("\nAdding the AP interface BSS configuration parameters to WPA Supplicant failed with error %s\n", clxGetWlanErrorCodeText(ret));

		goto Failure_AddInterface;
	}
#endif

	return CLX_SUCCESS;

#ifdef CLX_WPA_SUPPLICANT
Failure_AddInterface :
    clxWpaSupplicant_RemoveInterface(&apService, TRUE);
	clxWlanStopInterface(apHandle, TRUE);
#endif

Failure_StartInterface:
	return ret;
}

AccessPointConfigParams configParams;

ClxResult clxWlanStartAccessPointInterfaceUsingParams(ClxHandle apHandle, ClxBSSInfo *desiredAPConf, s1 *desiredPass, ClxConfigList* extraConfigParameters)
{
	s1 passKey[CLX_WLAN_MAX_PMK_LEN + 1];

	clxMemSet(&configParams, 0 , sizeof(configParams));

	if (userMacAddress)
	{
		clxMemCpy(configParams.bssInfo.bssid, userMacAddress, CLX_MAC_ADDRESS_LENGTH);
	}

	configParams.maxTxPower =				DEFAULT_AP_MAX_TX_POWER;
	configParams.bssInfo.beaconInterval =	DEFAULT_AP_BEACON_INTERVAL;
	configParams.bssInfo.dtimPeriod =		DEFAULT_AP_DTIM_PERIOD;
	configParams.clientInactivityTimeout =	DEFAULT_CLIENT_INACTIVITY_TIMEOUT;
	configParams.maxNumberOfStations =		DEFAULT_MAX_NUMBER_OF_AP_CLIENTS;
	configParams.hiddenSSID =				FALSE;
	configParams.country =					"AU";
	configParams.passKey =					passKey;

#if defined(CLX_IEEE802_11_N_SUPPORTED)
	configParams.bssInfo.capabilities = CLX_WLAN_CAPABILITY_HT_SUPPORTED | CLX_WLAN_CAPABILITY_WMM_SUPPORTED;
#endif

	if (desiredAPConf == NULL)
	{
		do
		{
			clxConsoleUIEngineInputBox("Enter the SSID: ", clxUiInputBuffer, sizeof(clxUiInputBuffer));
			//clxStrCpy(clxUiInputBuffer, "clxTest");

			configParams.bssInfo.ssid.len = MIN((sizeof(configParams.bssInfo.ssid.value) - 1), clxStrLen(clxUiInputBuffer));
			clxMemCpy(configParams.bssInfo.ssid.value, clxUiInputBuffer, configParams.bssInfo.ssid.len);
			configParams.bssInfo.ssid.value[configParams.bssInfo.ssid.len] = '\0';
		} while (configParams.bssInfo.ssid.len == 0);

		do
		{
			const s1* menu = "Open system authentication\0"
				"WPA+WPA2\0"
				"WPA2\0"
				"WPA2+WPA3\0"
				"WPA3\0"
			    "WPA2+FT-PSK\0"
			    "WPA2+FT-SAE\0"
			    "WPA3+FT-SAE\0"
				"Return to main menu";

			s1 s = clxConsoleUIEngineShowMenu("Select the Authentication type:", menu, 9);
			//s1 s = 3;

			switch (s)
			{
			case 1:
				configParams.bssInfo.authType = (u4)ClxAuthTypeOpenSystem;
				configParams.bssInfo.encProtocol = (u4)ClxEncProtoNONE;
				break;
			case 2:
				configParams.bssInfo.authType = (u4)ClxAuthTypePresharedKey;
				configParams.bssInfo.capabilities |= CLX_WLAN_CAPABILITY_WPA_SUPPORTED;
				configParams.bssInfo.encProtocol = (u4)ClxEncProtoTKIP | (u4)ClxEncProtoAES_CCMP;
				break;
			case 3:
				configParams.bssInfo.authType = (u4)ClxAuthTypePresharedKey;
				configParams.bssInfo.encProtocol = (u4)ClxEncProtoAES_CCMP;
				break;
			case 4:
				configParams.bssInfo.authType = (u4)ClxAuthTypePresharedKey | (u4)ClxAuthTypeSAE;
				configParams.bssInfo.encProtocol = (u4)ClxEncProtoAES_CCMP | (u4)ClxEncProto_BIP_CMAC_128;
				break;
			case 5:
				configParams.bssInfo.authType = (u4)ClxAuthTypeSAE;
				configParams.bssInfo.encProtocol = (u4)ClxEncProtoAES_CCMP | (u4)ClxEncProto_BIP_CMAC_128;
				break;
            case 6:
                configParams.bssInfo.authType = (u4)ClxAuthTypePresharedKey | (u4)ClxAuthTypePSK_FT;
                configParams.bssInfo.encProtocol = (u4)ClxEncProtoAES_CCMP;
                break;
            case 7:
                configParams.bssInfo.authType = (u4)ClxAuthTypePresharedKey | (u4)ClxAuthTypeSAE_FT;
                configParams.bssInfo.encProtocol = (u4)ClxEncProtoAES_CCMP;
                break;
            case 8:
                configParams.bssInfo.authType = (u4)ClxAuthTypeSAE | (u4)ClxAuthTypeSAE_FT;
                configParams.bssInfo.encProtocol = (u4)ClxEncProtoAES_CCMP | (u4)ClxEncProto_BIP_CMAC_128;
                break;
			default:
				break;
			}
		} while (configParams.bssInfo.encProtocol == 0xFFFFFFFF);

		do
		{
			clxConsoleUIEngineInputBox("Channel Number: ", clxUiInputBuffer, sizeof(clxUiInputBuffer));
			//clxStrCpy(clxUiInputBuffer, "1");

			configParams.bssInfo.channel = atoi(clxUiInputBuffer);
		} while (configParams.bssInfo.channel == 0);
	}
	else
	{
		clxMemCpy(&configParams.bssInfo.ssid, &desiredAPConf->ssid, sizeof(configParams.bssInfo.ssid));
		configParams.bssInfo.authType = desiredAPConf->authType;
		configParams.bssInfo.capabilities = desiredAPConf->capabilities;
		configParams.bssInfo.encProtocol = desiredAPConf->encProtocol;
		configParams.bssInfo.channel = desiredAPConf->channel;
	}


	if (configParams.bssInfo.encProtocol != (u4)ClxEncProtoNONE)
	{
		if (desiredPass == NULL)
		{
			do
			{
				clxConsoleUIEngineInputBox("Enter the Passkey: ", clxUiInputBuffer, sizeof(clxUiInputBuffer));
				//clxStrCpy(clxUiInputBuffer, "50505050");

				u4 passKeyLength = clxStrLen(clxUiInputBuffer);

				if (passKeyLength < MIN_PASSKEY_LENGTH)
				{
					clxConsoleUIEngineText("Passkey must be at least %u bytes long\n", MIN_PASSKEY_LENGTH);
					passKey[0] = '\0';
				}
				else
				{
					passKeyLength = MIN((sizeof(passKey) - 1), passKeyLength);
					clxMemCpy(passKey, clxUiInputBuffer, passKeyLength);
					passKey[passKeyLength] = '\0';
				}
			} while (passKey[0] == '\0');
		}
		else
		{
			u4 passKeyLength = MIN((sizeof(passKey) - 1), clxStrLen(desiredPass));
			clxMemCpy(passKey, desiredPass, passKeyLength);
			passKey[passKeyLength] = '\0';
		}

	}

	if (configParams.bssInfo.channel <= CLX_WLAN_NO_OF_2_4GHZ_CHANNELS)
	{
		configParams.bssInfo.band = ClxWlanFreqBand2_4GHz;
	}
	else
	{
		configParams.bssInfo.band = ClxWlanFreqBand5GHz;
	}

	return clxWlanStartAccessPointInterface(apHandle,
		&configParams,
		extraConfigParameters);
}

void showAccessPointMenu(ClxStack stack)
{    
	static ClxHandle wlanApHandle = NULL;

    ClxError ret;
                	
    while (1)
    {  
        const s1* menu = "Start Interface as an AccessPoint\0"
            "Enable the device\0"
            "Disable the device\0"
            "Get Max rate for a joined client\0"
            "Memory statistics\0"
            "Set Bandwidth Limit\0"
        	"Set Bandwidth Limit Exception Ports\0"
            "Get current Bandwidth usage\0"
            "Stop Interface\0"
        	"BSS Transition Test for AP 1\0"
        	"BSS Transition Test for AP 2\0"
            "Return to previous menu";

        u4 s = clxConsoleUIEngineShowMenu("WLAN AP Menu", menu, 12);

        if (s == 1)
        {              
	        if (wlanApHandle == NULL)
	        {
				ClxConfigList extraList;
				clxConfigInitParamsList(&extraList, NULL, NULL);

		        /* 
		        Create a single virtual interface and get a handle to it. 
		        The handle will to start, stop and control the virtual interface: 
		        */
			    ret = clxWlanCreateInterface(stack,        /* The WLAN stack object, as returned by clxInitClarinoxWlan()                 */
					WLAN_INTERFACE_NAME_AP,                /* Name of WL18xx virtual interface (fixed)                                    */
					ClxIfTypeAP,
				    createNetworkAccessInterface(),
				    &wlanApHandle);                        /* On a successful return, will contain a handle to the virtual interface      */

			    if (ret != CLX_SUCCESS)
			    {
				    clxConsoleUIEngineText("Creation of WLAN virtual interface failed with error %d\n", ret);
				    return;
			    }
          
				ret = clxWlanStartAccessPointInterfaceUsingParams(wlanApHandle, NULL, NULL, &extraList);
				if (ret != CLX_SUCCESS)
				{
					clxConsoleUIEngineText("Starting the WLAN virtual interface failed with error %d\n", ret);
					clxCloseHandle(wlanApHandle);
					wlanApHandle = NULL;
				}
	        }
	        else
	        {
		        clxConsoleUIEngineText("\nWiFi AP interface has already started.\n");     
	        }          
        }
	    else if (s == 2)
        {
	        if (wlanApHandle)
	        {           
		        ret = clxWlanStartRole(wlanApHandle, TRUE);
            
		        clxConsoleUIEngineText("Enabling the WLAN virtual AccessPoint complete with result %s\n", clxGetWlanErrorCodeText(ret));
	        }
	        else
	        {
		        clxConsoleUIEngineText("\nPlease start interface as an access point.\n"); 
	        }
        }
        else if (s == 3)
        {
	        if (wlanApHandle)
	        {
		        ret = clxWlanStopRole(wlanApHandle, TRUE);

		        clxConsoleUIEngineText("Disabling the WLAN virtual AccessPoint complete with result %s\n", clxGetWlanErrorCodeText(ret));  
	        }
	        else
	        {
		        clxConsoleUIEngineText("\nPlease start interface as an access point.\n");
	        }          
        }
        else if (s == 4)
        {
	        if (wlanApHandle)
	        {
				/* Structure to hold some information to be retrieved from the WLAN stack for a specific client (The client is identified by its MAC address): */
		        struct ClientConfig
		        {
			        ClxConfigList     parentList;
			        ClxConfigData     clientMacAddr;
			        u1                clientMacAddrBuffer[6];
			        ClxWlanConfigRate MaxRate;
			        ClxConfigInteger  capabilities;
		        };

		        struct ClientConfig clientConfig;

		        s1 requestedChannel[32];
		        clxConsoleUIEngineInputBox("\nEnter the client MAC address : ", requestedChannel, sizeof(requestedChannel));
                      
		        if (!clxWlanParseMacAddressString(requestedChannel, clientConfig.clientMacAddrBuffer))
		        {
			        clxConsoleUIEngineText("\nPlease enter a MAC address in the format XX:XX:XX:XX:XX:XX\n");
			        continue;
		        }

		        /* The parent list is initialized first: */
		        clxConfigInitParamsList(&clientConfig.parentList, "ClientDetails", NULL);

		                    /* Assign clientConfig.clientMacAddrBuffer to clientConfig.clientMacAddr. This is the MAC address of the client for which the other parameters are to be retrieved */
		        clxConfigInitDataParam(&clientConfig.clientMacAddr, "MacAddress", clientConfig.clientMacAddrBuffer, sizeof(clientConfig.clientMacAddrBuffer), &clientConfig.parentList);
            
		        /* Initialize clientConfig.MaxRate. The initial value is not important: */
		        clxConfigInitRateParam(&clientConfig.MaxRate, "MaxLinkTxRate", ClxWlanNonHTRate_NULL, 0, FALSE, &clientConfig.parentList);
            
		        /* Initialize clientConfig.capabilities. The initial value is not important: */
		        clxConfigInitIntegerParam(&clientConfig.capabilities, "Capabilities", 0, &clientConfig.parentList);
            
		        /* Retrieve the value of the parameters defined above: */
		        clxWlanGetParametersValue(wlanApHandle,                           /* Handle to the virtual interface as returned by clxWlanCreateInterface                                            */
			        &clientConfig.parentList,             /* A pointer to parent list object containing the parameters to be retrieved                                        */ 
			        TRUE);                                /* Blocking mode                                                                                                    */

			                    /* if clientConfig.clientMacAddr has been processed by the WLAN stack, then it means a client with this MAC address has been found. Otherwise, there is no such a client: */
		        if (clientConfig.clientMacAddr.paramInfo.processed == FALSE)
		        {
			        clxConsoleUIEngineText("\nA client with the specified MAC address was not found\n");
			        continue;
		        }

		                    /*  If clientConfig.MaxRate has been processed by the WLAN stack, it has a valid value: */
		        if (clientConfig.MaxRate.paramInfo.processed)
		        {
			        if (clientConfig.MaxRate.nonHTValue == ClxWlanNonHTRate_NULL)
			        {
				        clxConsoleUIEngineText("Max Rate = MCS %u\n", (u4)clientConfig.MaxRate.mcsIndex);
			        }
			        else
			        {
				        clxConsoleUIEngineText("Max Rate = %u Mbps\n", (u4)clientConfig.MaxRate.nonHTValue / 2);
			        }
		        }

		                    /*  If clientConfig.capabilities has been processed by the WLAN stack, it has a valid value: */
		        if (clientConfig.capabilities.paramInfo.processed)
		        {
					clxWlanPrintCapabilities(clientConfig.capabilities.paramValue);
		        }
		        else
		        {
			        clxConsoleUIEngineText("\nMax Rate has not been negotiated for the specified client, as yet\n");
		        }
	        }
	        else
	        {
		        clxConsoleUIEngineText("\nPlease start interface as an access point.\n");    
	        }
        }
        else if (s == 5)
        {
#if defined (CLX_DEBUG)
        	clxConsoleUIEngineText("\nThis option is not available in Debug version. \n To view memory statistics, use the memory monitor in ClariFi.\n");
#else
        	clxCheckMemoryUsage();
#endif
        }
        else if (s == 6)
        {
#ifdef CLX_BANDWIDTH_LIMIT_SUPPORTED
        	clxWlanSetBwLimit(wlanApHandle);
#else
            clxConsoleUIEngineText("\nFeature not supported\n");
#endif
        }
        else if (s == 7)
        {
#ifdef CLX_BANDWIDTH_LIMIT_SUPPORTED
        	clxWlanSetBwLimitExceptPors(wlanApHandle);
#else
            clxConsoleUIEngineText("\nFeature not supported\n");
#endif
        }
        else if (s == 8)
        {
#ifdef CLX_BANDWIDTH_LIMIT_SUPPORTED
        	clxWlanGetBwUsage(wlanApHandle);
#else
            clxConsoleUIEngineText("\nFeature not supported\n");
#endif
        }
        else if (s == 9)
        {
	        if (wlanApHandle)
	        {
#ifdef CLX_WPA_SUPPLICANT
                ClxService apService;
                clxInitLocalServiceObject(wlanApHandle, &apService);
#endif

			    ret = clxWlanStopRole(wlanApHandle, TRUE);

			    if (ret != CLX_WLAN_ERROR_ROLE_NOT_STARTED)
			    {
					clxConsoleUIEngineText("Disabling the WLAN virtual AccessPoint complete with result %s\n", clxGetWlanErrorCodeText(ret));
			    }

#ifdef CLX_WPA_SUPPLICANT
                ret = clxWpaSupplicant_RemoveInterface(&apService, TRUE);
                clxConsoleUIEngineText("\nRemoving interface from WPA Supplicant is complete with result %s", clxGetWlanErrorCodeText(ret));
#endif

				/* Stop the virtual interface: */
			    ret = clxWlanStopInterface(wlanApHandle, TRUE);
			    clxConsoleUIEngineText("\nStopping interface is complete with result %s", clxGetWlanErrorCodeText(ret));
            
				if (ret == CLX_SUCCESS)
				{
					ret = clxCloseHandle(wlanApHandle);
					clxConsoleUIEngineText("\nClosing Station handle is complete with result %s", clxGetWlanErrorCodeText(ret));

					wlanApHandle = NULL;

					clxConsoleUIEngineText("\nPlease disable WiFi stack\n");
				}
	        }
	        else
	        {
		        clxConsoleUIEngineText("\nPlease start interface as an access point.\n");     
	        }             
        }
        else if (s == 10)
        {
			if (wlanApHandle)
			{
				ClxService apService;
				clxInitLocalServiceObject(wlanApHandle, &apService);


				ret = clxWpaSupplicant_SendBssTransitionReq(&apService, "CLX-AP", ClxIfTypeAP, cmdBTM_1, TRUE);
				clxConsoleUIEngineText("\nSending BSS Transition test is complete with result %s", clxGetWlanErrorCodeText(ret));
			}
			else
			{
				clxConsoleUIEngineText("\nPlease start interface as an access point.\n");
			}
        }
        else if (s == 11)
        {
			if (wlanApHandle)
			{
				ClxService apService;
				clxInitLocalServiceObject(wlanApHandle, &apService);


				ret = clxWpaSupplicant_SendBssTransitionReq(&apService, "CLX-AP", ClxIfTypeAP, cmdBTM_2, TRUE);
				clxConsoleUIEngineText("\nSending BSS Transition test is complete with result %s", clxGetWlanErrorCodeText(ret));
			}
			else
			{
				clxConsoleUIEngineText("\nPlease start interface as an access point.\n");
			}
        }
        else if (s == 12)
        {
            return;
        }
    }
}

boolean clxWlanAccessPointIndicationHandler(ClxStack stack, ClxHandle handle, u4 messageID, const void* params, ClxError errorCode)
{
	switch (messageID)
	{
	case CLX_WLAN_STATION_JOINED_INDICATION:
		{
			struct ClientDetails
			{
				ClxConfigList     parentList;
				u1                addrBuf[6];
				ClxConfigData     macAddress;
				ClxWlanConfigRate maxRate;
			};

			ClxWlanStationJoinedIndication* arg = (ClxWlanStationJoinedIndication*)params;
			clxConsoleUIEngineText("\nStation Joined...");

			clxConsoleUIEngineText("\nMac Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
				arg->macAddress[0],
				arg->macAddress[1],
				arg->macAddress[2],
				arg->macAddress[3],
				arg->macAddress[4],
				arg->macAddress[5]);

			snprintf(cmdBTM_1, sizeof(cmdBTM_1), cmdBTM_Template_1,
					arg->macAddress[0], arg->macAddress[1], arg->macAddress[2],
					arg->macAddress[3], arg->macAddress[4], arg->macAddress[5]);

			snprintf(cmdBTM_2, sizeof(cmdBTM_2), cmdBTM_Template_2,
					arg->macAddress[0], arg->macAddress[1], arg->macAddress[2],
					arg->macAddress[3], arg->macAddress[4], arg->macAddress[5]);

			clxConsoleUIEngineText("\nbssID: %02X:%02X:%02X:%02X:%02X:%02X\n",
				arg->bssID[0],
				arg->bssID[1],
				arg->bssID[2],
				arg->bssID[3],
				arg->bssID[4],
				arg->bssID[5]);

			break;
		}

	case CLX_WLAN_STATION_DISCONNECTED_INDICATION:
		{
			ClxWlanStationDisconnectedIndication* arg = (ClxWlanStationDisconnectedIndication*)params;
			clxConsoleUIEngineText("\nStation Disconnected from...");

			clxConsoleUIEngineText("\nMac Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
				arg->macAddress[0],
				arg->macAddress[1],
				arg->macAddress[2],
				arg->macAddress[3],
				arg->macAddress[4],
				arg->macAddress[5]);

			clxConsoleUIEngineText("\nbssID: %02X:%02X:%02X:%02X:%02X:%02X\n",
				arg->bssID[0],
				arg->bssID[1],
				arg->bssID[2],
				arg->bssID[3],
				arg->bssID[4],
				arg->bssID[5]);

			clxConsoleUIEngineText("\nReason for disconnection: %s\n", clxGetWlanErrorCodeText(arg->reason));
			clxConsoleUIEngineText("\n");

			break;
		}

	case CLX_WLAN_STATION_AUTHENTICATION_INITIATED_INDICATION:
		{
			ClxWlanStationAuthenticationInitiatedIndication* arg = (ClxWlanStationAuthenticationInitiatedIndication*)params;
			clxConsoleUIEngineText("\nStation initiated the authentication");

			clxConsoleUIEngineText("\nMac Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
				arg->macAddress[0],
				arg->macAddress[1],
				arg->macAddress[2],
				arg->macAddress[3],
				arg->macAddress[4],
				arg->macAddress[5]);

			break;
		}

	case CLX_WLAN_STATION_ASSOCIATION_INITIATED_INDICATION:
		{
			ClxWlanStationAuthenticationInitiatedIndication* arg = (ClxWlanStationAuthenticationInitiatedIndication*)params;
			clxConsoleUIEngineText("\nStation initiated the association.");

			clxConsoleUIEngineText("\nMac Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
				arg->macAddress[0],
				arg->macAddress[1],
				arg->macAddress[2],
				arg->macAddress[3],
				arg->macAddress[4],
				arg->macAddress[5]);

			break;
		}

	case CLX_WLAN_STATION_AUTHENTICATION_COMPLETED_INDICATION:
		{
			ClxWlanStationAuthAssociationCompleted* arg = (ClxWlanStationAuthAssociationCompleted*)params;
			clxConsoleUIEngineText("\nStation completed the authentication with the result: %s", clxGetWlanErrorCodeText(arg->statusCode));

			clxConsoleUIEngineText("\nMac Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
				arg->macAddress[0],
				arg->macAddress[1],
				arg->macAddress[2],
				arg->macAddress[3],
				arg->macAddress[4],
				arg->macAddress[5]);

			break;
		}

	case CLX_WLAN_STATION_ASSOCIATION_COMPLETED_INDICATION:
		{
			ClxWlanStationAuthAssociationCompleted* arg = (ClxWlanStationAuthAssociationCompleted*)params;
			clxConsoleUIEngineText("\nStation completed the association with the result: %s", clxGetWlanErrorCodeText(arg->statusCode));

			clxConsoleUIEngineText("\nMac Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
				arg->macAddress[0],
				arg->macAddress[1],
				arg->macAddress[2],
				arg->macAddress[3],
				arg->macAddress[4],
				arg->macAddress[5]);

			break;
		}

	default:
		return FALSE;
	}

	return TRUE;
}
