#ifndef WlanConst_h
#define WlanConst_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                ClarinoxWlanConst.h
* Description         Clarinox WLAN Protocol Stack constants and types
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#include "ClarinoxConst.h"

#ifdef __cplusplus
extern "C" {
#endif


#define CLX_WLAN_INDICATION_SCHEDULER_NAME              "ClarinoxWLAN.Indication"
#define CLX_WLAN_STACK_SCHEDULER_NAME                   "ClarinoxWLAN.Stack"
#define CLX_WPA_SUPPLICANT_SCHEDULER_NAME               "wpa_supplicant"


/**
Cipher suites, as defined by IEEE OUI (Organization Unique Identifier).
NOTE : Not all cipher suites may be supported by the WLAN hardware in the platform.
*/
#define CLX_IEEE80211_WEP_40_OUI                    0x000FAC01          /* OBSOLETE */
#define CLX_IEEE80211_TKIP_OUI                      0x000FAC02
#define CLX_IEEE80211_CCMP_OUI                      0x000FAC04          /* CCMP-128 */
#define CLX_IEEE80211_WEP_104_OUI                   0x000FAC05          /* OBSOLETE */
#define CLX_IEEE80211_BIP_CMAC_128_OUI              0x000FAC06          /* Only allowed for Protected Group Management Frames */
#define CLX_IEEE80211_GCMP_128_OUI                  0x000FAC08
#define CLX_IEEE80211_GCMP_256_OUI                  0x000FAC09
#define CLX_IEEE80211_CCMP_256_OUI                  0x000FAC0A
#define CLX_IEEE80211_BIP_GMAC_128_OUI              0x000FAC0B          /* Only allowed for Protected Group Management Frames */
#define CLX_IEEE80211_BIP_GMAC_256_OUI              0x000FAC0C          /* Only allowed for Protected Group Management Frames */
#define CLX_IEEE80211_BIP_CMAC_256_OUI              0x000FAC0D          /* Only allowed for Protected Group Management Frames */


/**
Wireless Protected Setup (WPS) authentication methods supported by the local or remote device.
*/
typedef enum ClxWpsSupportedMethodEnum
{
    ClxWpsSupportedMethod_Invalid               = 0x0000,               /*!< Invalid value */
    ClxWpsSupportedMethod_USBA                  = 0x0001,               /*!< (Flash Drive) Deprecated */
    ClxWpsSupportedMethod_Ethernet              = 0x0002,               /*!< Deprecated */
    ClxWpsSupportedMethod_Label                 = 0x0004,               /*!< 8 digit static PIN typically available on device */
    ClxWpsSupportedMethod_Display               = 0x0008,               /*!< A dynamic 4 or 8 digit PIN is available from a display. Version 2.0 devices must qualify
                                                                             the display as Virtual (0x2008) or Physical (0x4008) */
    ClxWpsSupportedMethod_ExternalNfcToken      = 0x0010,               /*!< A physical passive NFC token is used to transfer the configuration or device password */
    ClxWpsSupportedMethod_IntegratedNfcToken    = 0x0020,               /*!< The NFC passive token is integrated in the device */
    ClxWpsSupportedMethod_NfcInterface          = 0x0040,               /*!< The device contains an NFC interface */
    ClxWpsSupportedMethod_PushButton            = 0x0080,               /*!< The device contains either a physical or virtual pushbutton. Version 2.0 devices
                                                                              must qualify the pushbutton as Virtual (0x0280) or Physical (0x0480) */
    ClxWpsSupportedMethod_Keypad                = 0x0100,               /*!< Device is capable of entering a PIN */
    ClxWpsSupportedMethod_VirtualPushButton     = 0x0280,               /*!< Push button functionality is available through a software user interface */
    ClxWpsSupportedMethod_PhysicalPushButton    = 0x0480,               /*!< A physical push button is available on the device */
    ClxWpsSupportedMethod_VirtualDisplayPIN     = 0x2008,               /*!< The dynamic 4 or 8 digit PIN is displayed through a remote user interface. For
                                                                             example using the management html page of an AP to obtain the dynamic PIN */
    ClxWpsSupportedMethod_PhysicalDisplayPIN    = 0x4008                /*!< The dynamic 4 or 8 digit PIN is shown on a display/screen that is part of the device. For
                                                                             example obtaining the dynamic PIN from the LCD screen on a printer */
} ClxWpsSupportedMethod;


typedef enum ClxWpsPasswordTypeEnum
{
	ClxWpsPasswordType_PIN                      = 0x0000,              /*!< The Enrollee should use its PIN password (from the label or display) */
	ClxWpsPasswordType_UserSpecified            = 0x0001,              /*!< The user has overridden the password with a manually selected value */
	ClxWpsPasswordType_MachineSpecified         = 0x0002,              /*!< The original PIN password has been overridden by a strong, machine-generated device password value */
	ClxWpsPasswordType_Rekey                    = 0x0003,              /*!< Not supported by ClarinoxWLAN */
	ClxWpsPasswordType_PushButton               = 0x0004,              /*!< Push button should be used instead of a PIN */
	ClxWpsPasswordType_RegistrarSpecified       = 0x0005,              /*!< The PIN that has been obtained from the Registrar should be used */
	ClxWpsPasswordType_Invalid                  = 0xFFFF	           /*!< The password type is invalid or not available */
} ClxWpsPasswordType;


/*
Device types as defined by Wi-Fi Alliance for WPS.
*/
typedef enum ClxWpsDeviceTypeEnum
{
    ClxWps_Computer_PC                                          = 0x00010001,
    ClxWps_Computer_Server                                      = 0x00010002,
    ClxWps_Computer_MediaCenter                                 = 0x00010003,
    ClxWps_Computer_UltraMobile                                 = 0x00010004,
    ClxWps_Computer_Notebook                                    = 0x00010005,
    ClxWps_Computer_Desktop                                     = 0x00010006,
    ClxWps_Computer_MobileInternetDevice                        = 0x00010007,
    ClxWps_Computer_Netbook                                     = 0x00010008,
    ClxWps_Computer_Tablet                                      = 0x00010009,
    ClxWps_InputDevice_Keyboard                                 = 0x00020001,
    ClxWps_InputDevice_Mouse                                    = 0x00020002,
    ClxWps_InputDevice_Joystick                                 = 0x00020003,
    ClxWps_InputDevice_Trackball                                = 0x00020004,
    ClxWps_InputDevice_GamingController                         = 0x00020005,
    ClxWps_InputDevice_Remote                                   = 0x00020006,
    ClxWps_InputDevice_Touchscreen                              = 0x00020007,
    ClxWps_InputDevice_BiometricReader                          = 0x00020008,
    ClxWps_InputDevice_BarcodeReader                            = 0x00020009,
    ClxWps_Printer                                              = 0x00030001,
    ClxWps_Scanner                                              = 0x00030002,
    ClxWps_Fax                                                  = 0x00030003,
    ClxWps_Copier                                               = 0x00030004,
    ClxWps_Printer_Fax_Scanner_Copier                           = 0x00030005,       /* All-In-One Device */
    ClxWps_Camera_DigitalStillCamera                            = 0x00040001,
    ClxWps_Camera_VideoCamera                                   = 0x00040002,
    ClxWps_Camera_WebCamera                                     = 0x00040003,
    ClxWps_Camera_SecurityCamera                                = 0x00040004,
    ClxWps_Storage_NAS                                          = 0x00050001,
    ClxWps_Network_AP                                           = 0x00060001,
    ClxWps_Network_Router                                       = 0x00060002,
    ClxWps_Network_Switch                                       = 0x00060003,
    ClxWps_Network_Gateway                                      = 0x00060004,
    ClxWps_Network_Bridge                                       = 0x00060005,
    ClxWps_Display_Television                                   = 0x00070001,
    ClxWps_Display_ElectronicPictureFrame                       = 0x00070002,
    ClxWps_Display_Projector                                    = 0x00070003,
    ClxWps_Display_Monitor                                      = 0x00070004,
    ClxWps_MultimediaDevice_DAR                                 = 0x00080001,
    ClxWps_MultimediaDevice_PVR                                 = 0x00080002,
    ClxWps_MultimediaDevice_MCX                                 = 0x00080003,
    ClxWps_MultimediaDevice_SetTopBox                           = 0x00080004,
    ClxWps_MultimediaDevice_MediaClientServerAdapterExtender    = 0x00080005,
    ClxWps_MultimediaDevice_PortableVideoPlayer                 = 0x00080006,
    ClxWps_GamingDevices_Xbox                                   = 0x00090001,
    ClxWps_GamingDevices_Xbox360                                = 0x00090002,
    ClxWps_GamingDevices_Playstation                            = 0x00090003,
    ClxWps_GamingDevices_GameConsole_GameConsoleAdapter         = 0x00090004,
    ClxWps_GamingDevices_PortableGamingDevice                   = 0x00090005,
    ClxWps_Telephone_WindowsMobile                              = 0x000A0001,
    ClxWps_Telephone_PhoneSingleMode                            = 0x000A0002,
    ClxWps_Telephone_PhoneDualMode                              = 0x000A0003,
    ClxWps_Telephone_SmartphoneSingleMode                       = 0x000A0004,
    ClxWps_Telephone_SmartphoneDualMode                         = 0x000A0005,
    ClxWps_AudioDevice_AudioTunerReceiver                       = 0x000B0001,
    ClxWps_AudioDevice_Speakers                                 = 0x000B0002,
    ClxWps_AudioDevice_PortableMusicPlayer                      = 0x000B0003,
    ClxWps_AudioDevice_Headset                                  = 0x000B0004,
    ClxWps_AudioDevice_Headphone                                = 0x000B0005,
    ClxWps_AudioDevice_Microphone                               = 0x000B0006,
    ClxWps_AudioDevice_HomeTheaterSystem                        = 0x000B0007,
    ClxWps_VendorSpecificDeviceType                             = 0x0FFFFFFF        /*!< used only when a vendor-specific device type value is received from the remote device.
                                                                                         CANNOT be used when setting the device type of the local device */
} ClxWpsDeviceType;

/**
The type (role) of WLAN Interface. One or more interface types may be supported by a WLAN driver.
*/
typedef enum ClxInterfaceTypeEnum
{
    ClxIfTypeInvalid,                       /*!< Invalid Type (SHALL not be used by the application */
    ClxIfTypeAdhoc,                         /*!< Independent BSS member (OBSOLETE) */
    ClxIfTypeAP,                            /*!< Access Point */
    ClxIfTypeSTA,                           /*!< Station */
    ClxIfTypeP2P,                           /*!< A P2P interface. Upon successful conclusion of the P2P discovery phase, 
                                                 the interface will be in either P2P Client or P2P GO (Group Owner) role */ 
    ClxIfTypeP2P_GO,                        /*!< A P2P Group Owner. This will start the interface directly as a P2P Group Owner (GO) */
    ClxIfType_Monitor,                      /*!< A Monitor interface. This will be used to monitor WLAN frames in the air */
    ClxIfTypeVendorSpecific                 /*!< Vendor Specific interface */
} ClxInterfaceType;


/**
 * The Type of the encryption key
 */
typedef enum ClxWlanKeyTypeEnum
{
	ClxWlanKeyType_Pairwise = 1,
	ClxWlanKeyType_Groupwise = 2,
    ClxWlanKeyType_IGTK = 4,                /*!< Integrity Groupwise Temporal Key for broadcast/multicast protected management frames */ 
    ClxWlanKeyType_BIGTK = 5                /*!< Beacon Integrity Groupwise Temporal Key for protected beacon frames */
} ClxWlanKeyType;


/**
 * The Type of Authentication Mechanism. 
 * All authentication mechanisms may not be supported by the WLAN driver and/or the authentication module.
 */
typedef enum ClxAuthTypeEnum
{
    ClxAuthTypeInvalid              	= 0x0000,        /*!< Invalid value (MUST not be passed to ClarinoxWLAN). */  
    ClxAuthTypeOpenSystem           	= 0x0001,        /*!< Open System Authentication (only used for non-secure networks). */
    ClxAuthTypePresharedKey         	= 0x0004,        /*!< Authentication based on pre-shared master key or pass-phrase (Also known as WPA/WPA2 PSK or personal). Uses SHA1. */
    ClxAuthTypeIEEE802_1x           	= 0x0008,        /*!< IEEE802.1x Port-Based Authentication (Also known as WPA/WPA2 Enterprise). */  
    ClxAuthTypeSAE          	        = 0x0010,        /*!< Password-based Authentication via Simultaneous Authentication of Equals (SAE) algorithm (Also known as WPA3 Personal). */
    ClxAuthTypeOWE          	        = 0x0020,        /*!< Opportunistic (unauthenticated) Wireless Encryption (Also known as WiFi Enhanced Open) */
    ClxAuthTypePSK_SHA256   	        = 0x0040,        /*!< Authentication based on pre-shared master key or pass-phrase (Also known as WPA2 PSK or personal). Uses SHA256 */
    ClxAuthTypeIEEE802_1x_SHA256		= 0x0080,		 /*!< IEEE802.1x Port-Based Authentication (Also known as WPA3 Enterprise). Uses SHA256. */ 
    ClxAuthTypeIEEE802_1x_SUITE_B		= 0x0100,	     /*!< IEEE802.1x Port-Based Authentication (Also known as WPA3 Enterprise Suite B Compliant 128-bit). */ 
    ClxAuthTypeIEEE802_1x_SUITE_B_192	= 0x0200,	     /*!< IEEE802.1x Port-Based Authentication (Also known as WPA3 Enterprise Suite B 192-bit). */  
    ClxAuthTypeIEEE802_1x_FT            = 0x0400,        /*!< FT (Fast BSS Transmission) over IEEE802.1x Port-Based Authentication. */ 
    ClxAuthTypePSK_FT                   = 0x0800,        /*!< FT (Fast BSS Transmission) over pre-shared master key or pass-phrase. */ 
    ClxAuthTypeSAE_FT                   = 0x1000,        /*!< FT (Fast BSS Transmission) over Simultaneous Authentication of Equals (SAE). */ 
    ClxAuthTypeIEEE802_1x_FT_SHA384     = 0x2000,        /*!< FT (Fast BSS Transmission) over IEEE802.1x Port-Based Authentication. Uses SHA384. */ 
    ClxAuthTypePSK_FT_SHA384            = 0x4000         /*!< FT (Fast BSS Transmission) over pre-shared master key or pass-phrase. Uses SHA384. */ 
} ClxAuthType;


/**
 * The Type of Encryption Protocol (Cipher Suite). 
 * All cipher suites may not be supported by the WLAN driver.
 */
typedef enum ClxEncryptionProtocolEnum              /*! The encryption Protocols */
{
    ClxEncProtoNONE          = 0x0000,              /*!< No Encryption protocol to be used (only used with open system authentication) */
    ClxEncProtoWEP40         = 0x0001,              /*!< WEP40 (Deprecated) */
    ClxEncProtoWEP104        = 0x0002,              /*!< WEP104 (Deprecated) */
    ClxEncProtoTKIP          = 0x0004,              /*!< Temporal Key Integrity Protocol (Deprecated as of IEEE802.11n standard) */
    ClxEncProtoAES_CCMP      = 0x0008,              /*!< Advanced Encryption Standard (AES-128) Counter Cipher Mode 
                                                         with Block Chaining Message Authentication Code Protocol */
    ClxEncProto_Proprietary  = 0x0010,              /*!< Proprietary (non-standard) cipher suite */
    ClxEncProto_CCMP_256     = 0x0020,              /*!< Advanced Encryption Standard (AES-256) Counter Cipher Mode 
                                                          with Block Chaining Message Authentication Code Protocol */ 
    ClxEncProto_BIP_CMAC_128 = 0x0040,              /*!< 128-bit Broadcast/Multicast Integrity (BIP) cipher used with Protected Management Frames (802.11w) only (CMAC) */
    ClxEncProto_GCMP_128 =     0x0080,              /*!< 128-bit Galois/Counter Mode Protocol (GCMP) cipher used with IEEE802.11ac only  */
    ClxEncProto_GCMP_256 =     0x0100,              /*!< 256-bit Galois/Counter Mode Protocol (GCMP) cipher used with IEEE802.11ac only  */
    ClxEncProto_BIP_GMAC_128 = 0x0200,              /*!< 128-bit Broadcast/Multicast Integrity (BIP) cipher used with Protected Management Frames (802.11w) only (GMAC) */
    ClxEncProto_BIP_GMAC_256 = 0x0400,              /*!< 256-bit Broadcast/Multicast Integrity (BIP) cipher used with Protected Management Frames (802.11w) only (GMAC)  */
    ClxEncProto_BIP_CMAC_256 = 0x0800               /*!< 256-bit Broadcast/Multicast Integrity (BIP) cipher used with Protected Management Frames (802.11w) only (CMAC)  */
} ClxEncryptionProtocol CLX_CTYPE;


/**
The Type of Basic Service Set (BSS).
*/
typedef enum ClxBSSTypeEnum
{
    ClxBSSType_Unknown          = 0x00,             /*!< Invalid value */
    ClxBSSType_Infrastructure   = 0x01,             /*!< Infrastructure BSS */
    ClxBSSType_Independent      = 0x02,             /*!< Independent BSS */
    ClxBSSType_AnyType          = 0x03              /*!< Both Infrastructure and Independent BSS */
} ClxBSSType;

/**
The Wi-Fi Alliance standard(s) supported by a WLAN device (local or remote).

NOTE : The standards of a remote device are detected based on the information elements present in the management frames
       sent by that device. This does NOT imply a complete compliance with Wi-Fi Alliance certification programs.
*/
typedef enum ClxWifiSupportedStandardEnum
{
    ClxWifiSupportedStandard_None          = 0x00,    /*!< None of the following standards are supported */  
    ClxWifiSupportedStandard_WPA           = 0x01,    /*!< WPA Authentication
	                                                       (Usually used along with TKIP encryption protocol) */
    ClxWifiSupportedStandard_WPA2          = 0x02,    /*!< WPA2 Authentication
	                                                       (Usually used along with AES-CCMP encryption protocol) */
    ClxWifiSupportedStandard_WPS           = 0x10,    /*!< Wi-Fi Protected Setup */
    ClxWifiSupportedStandard_WMM           = 0x20,    /*!< Wi-Fi MultiMedia */
    ClxWifiSupportedStandard_WIFI_Direct   = 0x40,    /*!< Wi-Fi Direct (P2P) */
    ClxWifiSupportedStandard_WPA3          = 0x80    /*!< WPA3 Authentication */
} ClxWifiSupportedStandard CLX_CTYPE;


/**
A value of type ClxWlanRateIn100Kbps specifies a WLAN rate in the units of 100 Kbps. For instance, a value of 673 specifies a rate of 67,300 Kbps or 67.3 Mbps.
*/
typedef u4 ClxWlanRateIn100Kbps;


#define CLARINOX_WLAN_CLASS_ID                                    55
#define CLARINOX_WLAN_VIRTUAL_INTERFACE_CLASS_ID                  56


#ifdef __cplusplus
}
#endif

#endif // WlanConst_h

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
