#ifndef Wlan_Api_h
#define Wlan_Api_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                Wlan.Api.h
* Description         Declares API Functions and Definitions For ClarinoxWLAN
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
Max Length of an SSID
*/
#define CLX_MAX_SSID_LEN                                                                    32U

/**
Length of Pin Code
*/
#define CLX_WPS_PIN_CODE_LEN                                                                8U

    
/**
Length of Country Code
*/    
#define CLX_WLAN_COUNTRY_CODE_LEN                                                           3U


/**
The Pairwise Master Key (PMK) length
*/
#define CLX_WLAN_MAX_PMK_LEN                                                                32U


/**
Max Length of a Key in HEX format
*/
#define CLX_WLAN_MAX_KEY_LEN_IN_HEX                                                         (CLX_WLAN_MAX_PMK_LEN*2)


/**
Max Length of a password phrase
*/
#define CLX_WLAN_MAX_PSWD_PHRASE_LEN                                                        63U


/**
Total number of frequency channels in the 2.4 GHz band supported by IEEE802.11
*/
#define CLX_WLAN_NO_OF_2_4GHZ_CHANNELS                                                      14U


/**
Max Length of WPS short strings.
*/
#define CLX_WLAN_WPS_MAX_SHORT_STRING_LENGTH                                                32U

/**
Max Length of WPS device name.
*/
#define CLX_WLAN_WPS_MAX_DEVICE_NAME_LENGTH                                                 CLX_WLAN_WPS_MAX_SHORT_STRING_LENGTH

/**
Max Length of WPS model name.
*/
#define CLX_WLAN_WPS_MAX_MODEL_NAME_LENGTH                                                  CLX_WLAN_WPS_MAX_SHORT_STRING_LENGTH

/**
Max Length of WPS model number.
*/
#define CLX_WLAN_WPS_MAX_MODEL_NUMBER_LENGTH                                                CLX_WLAN_WPS_MAX_SHORT_STRING_LENGTH


/**
Max Length of WPS manufacturer name.
*/
#define CLX_WLAN_WPS_MAX_MANUFACTURER_NAME_LENGTH                                           64U


/**
Max Length of WPS serial number.
*/
#define CLX_WLAN_WPS_MAX_SERIAL_NUMBER_LENGTH                                               CLX_WLAN_WPS_MAX_SHORT_STRING_LENGTH


/**
Length of WPS UUID.
*/
#define CLX_WLAN_WPS_UUID_LENGTH                                                            16U


/**
Maximum number of clients that ClarinoxWLAN supports in the AP role. 
The actual maximum number may be limited by the driver/WLAN controller.
*/
#define CLX_WLAN_MAX_NUM_OF_AP_CLIENTS                                                      31U


/**
Used Internally.
*/
#define CLX_WLAN_CREATE_INTERFACE_COMPLETE                                                  0x783F


/**
Refer to #clxInitClarinoxWlan function.
*/
#define CLX_INIT_CLARINOX_WLAN_COMPLETE                                                     0x7800

/**
Refer to #clxTerminateClarinoxWlan function.
*/
#define CLX_TERMINATE_CLARINOX_WLAN_COMPLETE                                                0x7801


/**
Used Internally.
*/
#define CLX_DESTROY_CLARINOX_WLAN_COMPLETE                                                  0x7802


/**
Refer to #clxWlanInterfaceGetMacAddr function.
*/
#define CLX_WLAN_INTERFACE_GET_MAC_ADDR_COMPLETE                                            0x7804

/**
Refer to #clxWlanGetParametersValue function.
*/
#define CLX_WLAN_GET_PARAMETERS_VALUE_COMPLETE                                              0x7805

/**
Refer to #clxWlanSetParametersValue function.
*/
#define CLX_WLAN_SET_PARAMETERS_VALUE_COMPLETE                                              0x7806

/**
Refer to #clxWlanStartInterface function.
*/
#define CLX_WLAN_START_INTERFACE_COMPLETE                                                   0x7807

/**
Refer to #clxWlanStopInterface function.
*/
#define CLX_WLAN_STOP_INTERFACE_COMPLETE                                                    0x7808

/**
Refer to #clxWlanStartRole function.
*/
#define CLX_WLAN_START_ROLE_COMPLETE                                                        0x7809

/**
Refer to #clxWlanStopRole function.
*/
#define CLX_WLAN_STOP_ROLE_COMPLETE                                                         0x780a

/**
Refer to #clxWlanScan function.
*/
#define CLX_WLAN_SCAN_COMPLETE                                                              0x780b

/**
Refer to #clxWlanConnect function.
*/
#define CLX_WLAN_CONNECT_COMPLETE                                                           0x780d

/**
Refer to #clxWlanDisconnect function.
*/
#define CLX_WLAN_DISCONNECT_COMPLETE                                                        0x780e


/**
Refer to #clxWlanGetConnectionProfileWithWps function.
*/
#define CLX_WLAN_GET_CONNECTION_PROFILE_WITH_WPS_COMPLETE                                   0x780f


/**
Refer to #clxWlanActivateWpsRegistrar function.
*/
#define CLX_WLAN_ACTIVATE_WPS_REGISTRAR_COMPLETE                                            0x7810


/**
Refer to #clxWlanDeactivateWpsRegistrar function.
*/
#define CLX_WLAN_DEACTIVATE_WPS_REGISTRAR_COMPLETE                                          0x7811


/**
Refer to clxWlanSendTestCommand function.
*/
#define CLX_WLAN_SEND_TEST_COMMAND_COMPLETE                                                 0x7812


/**
Refer to #clxWlanStartBgScan function.
*/
#define CLX_WLAN_START_BG_SCAN_COMPLETE                                                     0x7813


/**
Refer to #clxWlanStopBgScan function.
*/
#define CLX_WLAN_STOP_BG_SCAN_COMPLETE                                                      0x7814


/**
Used Internally. 
The parameter of this indication is of type #ClxA2lDispCommandArgsComplete.
*/
#define CLX_WLAN_MANAGEMENT_COMMAND_ISSUE_COMPLETE                                          0x7815


/**
This indication is sent to the application when, during scan, a BSS (Access Point) is discovered.
The parameter of this indication is of type #ClxWlanBssDiscoveredIndication.
*/
#define CLX_WLAN_BSS_DISCOVERED_INDICATION                                                  0xb800

/**
This indication is sent to the application when a station has joined the local virtual AP.
The parameter of this indication is of type #ClxWlanStationJoinedIndication.
*/
#define CLX_WLAN_STATION_JOINED_INDICATION                                                  0xb801

/**
This indication is sent to the application when a station has disconnected from the local virtual AP.
The parameter of this indication is of type #ClxWlanStationDisconnectedIndication.
*/
#define CLX_WLAN_STATION_DISCONNECTED_INDICATION                                            0xb802

/**
This indication is sent to the application when authentication initiated by station.
The parameter of this indication is of type #ClxWlanStationAuthenticationInitiatedIndication.
*/
#define CLX_WLAN_STATION_AUTHENTICATION_INITIATED_INDICATION                                0xb803

/**
This indication is sent to the application when authentication completed by station.
The parameter of this indication is of type #ClxWlanStationAuthenticationCompletedIndication.
*/
#define CLX_WLAN_STATION_AUTHENTICATION_COMPLETED_INDICATION                                0xb804

/**
This indication is sent to the application when association initiated by station.
The parameter of this indication is of type #ClxWlanStationAssociationInitiatedIndication.
*/
#define CLX_WLAN_STATION_ASSOCIATION_INITIATED_INDICATION                                   0xb805

/**
This indication is sent to the application when association completed by station.
The parameter of this indication is of type #ClxWlanStationAssociationCompletedIndication.
*/
#define CLX_WLAN_STATION_ASSOCIATION_COMPLETED_INDICATION                                   0xb806

/**
The indication is sent to the application when a fatal hardware error has occurred and the application needs to start 
recovery procedure. This indication does not belong to a specific virtual interface, but to all initialized virtual 
interfaces present in the application. Therefore, the recovery procedure MUST be performed on all virtual interfaces. 
The actual reason of this indication is hardware-specific.

Upon reception of this indication, the application MUST stop all virtual interfaces which are open in the current 
session of the stack. In order to stop an interface, the function clxWlanStopInterface() must be called. Note that,
during recovery procedures, the function clxWlanStopInterface() will not try to gracefully terminate the links, and the 
ongoing tasks in the stack since the hardware is in a instable or failure state. In recovery mode, all links and tasks 
are forcefully terminated, without any further communication with the hardware.

IMPORTANT : After stopping all interfaces, the hardware must be power-cycled. This is done either automatically by the 
driver when the interfaces are re-started or must be done manually by the application. Refer to the documentation of the
driver being used for more information on how and when the power-cycling procedure can be carried out.

If this procedure for all virtual interfaces is successful, then these interfaces can be re-started by calling 
#clxWlanStartInterface. In this case, there is no need to destroy the entire stack and re-initialize it.

However, if the procedure mentioned above fails for any of the opened virtual interfaces, the stack instance MUST be 
terminated, and destroyed. Upon a successful termination and destroying, the stack may be re-initialized again.

IMPORTANT : Note that all open handles to virtual interfaces MUST be closed before the stack can be terminated.

During the recovery procedure, all established links to other wireless stations or networks will be lost, and any 
configuration parameters set by the application will be dropped. Therefore, the application must update its internal 
states accordingly. In recovery mode, the indications, which are normally sent by the stack to the application,
will not be sent.

Upon the reception of this indication, all non-blocking API function calls will return with an appropriate error code, 
and subsequent attempts to call any new API functions (except for clxWlanStopInterface() and clxCloseHandle() functions)
will fail. This is due to the fact that the stack has entered the recovery mode in order to prevent the application from
inflicting any further damage. This rule also applies to all BSP interfaces.

This indication has no arguments.
*/
#define CLX_WLAN_HARDWARE_ERROR_INDICATION                                                  0xb807

/**
This indication is sent to the application when AP disconnects from Station. This is indication is only sent when the 
local device is in station mode. This indication is only generated when the access point has initiates the disconnection
procedure. It will not be generated when the disconnection procedure has been initiated by the local device.

The parameter of this indication is of type #ClxWlanApDisconnectedIndication.
*/
#define CLX_WLAN_AP_DISCONNECTED_INDICATION                                                 0xb808

/**
This indication is sent to the application when the link to the remote machine seems to be lost (decided based on the 
recent beacon losses or data transmission failures). This is a hint that the AccessPoint might be out of range or 
(possibly) tuned off. Upon reception of this indication, the application may start Link Recovery procedures. The actual 
procedure used is application-specific. If the link cannot be recovered, the API function #clxWlanDisconnect() MUST be 
called.

If it is established that the local station needs to connect to a different access point in the same network 
(a.k.a Roaming), the API function #clxWlanConnect() can be called to re-associate to the new AP.

This indication is only received when the local machine is in a non-master role (e.g. Station role or P2P Client role),
and there is currently a connection to a wireless network.

NOTE : This indication might be not supported by some drivers/chips.

This indication has no arguments.
*/
#define CLX_WLAN_LINK_LOST_INDICATION                                                       0xb809


/**
This indication is sent to the application when the Clarinox WLAN evaluation license period has expired.
*/
#define CLX_WLAN_LICENSE_EXPIRED_INDICATION                                                 0xb80a


/**
This indication is sent to the application when a client station has been involved in a WPS session with the local device
as the WPS registrar. The parameter of the indication (of type #ClxWlanWpsSessionCompleteIndication) indicates whether or not the WPS session has been successful.

This indication may be sent only if the local interface is in AccessPoint or P2P GO role.

The parameter of this indication is of type #ClxWlanWpsSessionCompleteIndication.
*/
#define CLX_WLAN_WPS_SESSION_COMPLETE_INDICATION                                            0xb80b


/**
This indication is sent to the application when the WPS registrar (which had been previosuly activated by a call to #clxWlanActivateWpsRegistrar) has been deactivated 
due to one of the following reasons:

- The WPS registrar activity timer has expired. This is a 2-minute timer which starts when #clxWlanActivateWpsRegistrar is complete successfully.
- A client station has successfully been provisioned by the WPS registrar. 
- The role of local interface has been stopped by a call to #clxWlanStopRole.

This indication may be sent only if the local interface is in AccessPoint or P2P GO role.

NOTE : If the WPS registrar is deactivated by a call to #clxWlanDeactivateWpsRegistrar, this indication will NOT be sent to the application.

This indication has no arguments.
*/
#define CLX_WLAN_WPS_REGISTRAR_DEACTIVATED_INDICATION                                       0xb80c


/**
This indication is sent to the application when the ongoing background scan is terminated.
The parameter of this indication is of type #ClxWlanBgScanTerminatedIndication.
*/
#define CLX_WLAN_BG_SCAN_TERMINATION_INDICATION                                             0xb80d


/**
This indication is sent to the application when a driver-specific event occurs.
The parameter of this indication is of type (or an object deriving from) #ClxWlanDriverSpecificIndication
*/
#define CLX_WLAN_DRIVER_SPECIFIC_INDICATION                                                 0xb80e


/** 
\page ErrorCodes

- #CLX_WLAN_ERROR_DEAUTHENTICATED_STATION_LEFT_BSS: Station is leaving (or has left) IBSS or ESS 
- #CLX_WLAN_ERROR_STATION_INACTIVITY_TIMER_EXPIRED: Disassociated due to inactivity
- #CLX_WLAN_ERROR_INCORRECT_FRAME_TYPE_FROM_UNAUTHENTICATED_STA: Class 2 frame received from nonauthenticated station
- #CLX_WLAN_ERROR_INCORRECT_FRAME_TYPE_FROM_UNASSOCIATED_STA: Class 3 frame received from nonassociated station
- #CLX_WLAN_ERROR_DEASSOCIATED_STATION_LEFT_BSS: Disassociated because sending station is leaving (or has left) BSS
- #CLX_WLAN_ERROR_ASSOCIATION_REQUESTED_BEFORE_AUTHENTICATION: Station requesting (re)association is not authenticated with responding station
- #CLX_WLAN_ERROR_4WAY_KEY_HANDSHAKE_TIMEOUT: 4-Way Handshake timeout
- #CLX_WLAN_ERROR_GROUPWISE_KEY_HANDSHAKE_TIMEOUT: Group Key Handshake timeout
- #CLX_WLAN_ERROR_HANDSHAKE_INFO_MISMATCH: Information element in 4-Way Handshake different from (Re)Association Request/Probe Response/Beacon frame
- #CLX_WLAN_ERROR_INVALID_PAIRWISE_CIPHER: Invalid pairwise cipher
- #CLX_WLAN_ERROR_INVALID_AUTHENTICATION_PROTOCOL: Invalid AKMP
- #CLX_WLAN_ERROR_UNSUPPORTED_RSN_IE_VERSION: Unsupported RSN information element version
- #CLX_WLAN_ERROR_INVALID_CAPABILITIES_IN_RSN: Invalid RSN information element capabilities
- #CLX_WLAN_ERROR_REASSOCIATION_DENIED: Reassociation denied due to inability to confirm that association exists
- #CLX_WLAN_ERROR_ASSOCIATION_DENIED: Association denied due to reason outside the scope of this standard
- #CLX_WLAN_ERROR_PRE_ASSOC_AUTHENTICATION_CHALLENGE_FAILED: Authentication rejected because of challenge failure
- #CLX_WLAN_ERROR_PRE_ASSOC_AUTHENTICATION_TIMEOUT: Authentication rejected due to timeout waiting for next frame in sequence
- #CLX_WLAN_ERROR_ASSOCIATION_DENIED_IEEE802_11b_CONFIG_MISMATCH: Association denied due to requesting station not supporting the short preamble/PBCC modulation/Channel Agility option
- #CLX_WLAN_ERROR_ASSOCIATION_DENIED_IEEE802_11h_CONFIG_MISMATCH: Association request rejected because Spectrum Management capability is required/information in the Power Capability element is unacceptable/information in the Supported Channels element is unacceptable
- #CLX_WLAN_ERROR_ASSOCIATION_DENIED_IEEE802_11g_CONFIG_MISMATCH: Association denied due to requesting station not supporting the Short Slot Time option/the DSSS-OFDM option
- #CLX_WLAN_ERROR_INVALID_SECURITY_INFORMATION_ELEMENT: Invalid information element, i.e., an information element defined in this standard for which the content does not meet the specifications in Clause 7
*/


typedef u1 ClxWlanMacAddress[CLX_MAC_ADDRESS_LENGTH];


/**
The security credential of a wireless network, containing all security-related information required to connect to a BSS.

NOTE : This structure is only used with the ClarinoxWLAN internal authentication implementation. When an external 
       authentication module (e.g. WPA Supplicant) is used, security credentials are only passed to the external module 
       (via its own mechanism), and not to ClarinoxWLAN.

ClxWlanSecurityCredential has the following members which need detailed introduction:

- key : The key in binary format. The member keyLen must be set to the length of the key stored in this member.

- passwdPhrase : An ASCII(or UTF-8) null-terminated string which stores the passphrase.

The stack first checks "key" and "keyLen" members. If "keyLen" has been set to the expected key length, "key" will be 
used as the Pairwise Master Key (PMK) . In this case, "passwdPhrase" will be ignored.
NOTE : "keyLen" is supposed to be CLX_WLAN_MAX_PMK_LEN in case of WPA/WPA2/WPA3 Personal.

If "keyLen" is zero, or not the expected value, "passwdPhrase" will be used to generate the master key, internally.

Note that the PMK MUST be stored in BINARY format in "key". If the user interface takes the key in HEX format 
(64 characters), it must be converted to binary (32 bytes) before it is stored in "key".

The passphrase can be 8 to 63 bytes. Therefore, if the value entered by the user is shorter than 64 bytes, it must be 
taken as the passphrase. If the value entered is exactly 64 bytes, it must be taken as the PMK in HEX format.
The user must not be able to enter a value longer than 64 bytes.
*/
typedef struct ClxWlanSecurityCredentialStruct
{
    u1  keyIndex;                                       /*!< Deprecated. Must be always set to 0 */
    u2  keyLen;                                         /*!< The length of Pairwise Master Key (PMK). Must be set to 0 
                                                             if a pass-phrase is to be used to extract the master key instead */
    u1  key[CLX_WLAN_MAX_PMK_LEN];                          /*!< The Pairwise Master Key (PMK). Valid only if keyLen is set to CLX_WLAN_MAX_PMK_LEN. Otherwise, it will be ignored */
    s1  passwdPhrase[CLX_WLAN_MAX_PSWD_PHRASE_LEN+1];   /*!< WPA-PSK passphrase, as null terminated UTF-8 string. Used with WPA/WPA2/WPA3 Personal.
                                                             Used only if keyLen is 0. Otherwise it will be ignored */
} ClxWlanSecurityCredential;

/**
The Service Set Identifier(SSID) structure.
*/
typedef struct ClxSSIDStruct
{
    s1  value[CLX_MAX_SSID_LEN+1];    /*!< The buffer to hold the SSID, followed by a null character.
                                           In theory (as per the specifications), SSID may contain any arbitrary ASCII 
                                           characters. However, in practice, SSID is always a human-readable ASCII or 
                                           UTF-8 string.
                                           In either case, the null-termination character is not part of the SSID. */
    u1  len;                          /*!< The length of the SSID, excluding the null character */
} ClxSSID;

/**
The structure returned for indications #CLX_WLAN_STATION_AUTHENTICATION_COMPLETED_INDICATION
and #CLX_WLAN_STATION_ASSOCIATION_COMPLETED_INDICATION.
*/
typedef struct ClxWlanStationAuthAssociationCompletedStruct
{
    u1        macAddress[CLX_MAC_ADDRESS_LENGTH];    /*!< The MAC address of the station completed the authentication or 
                                                    association. */
    ClxError  statusCode;                      /*!< The status that AP returns to STA, in the response to the 
                                                    authentication or association request.
                                                    It can be printed with the clxGetWlanErrorCodeText() function. */
} ClxWlanStationAuthAssociationCompleted;


/**
Details of an WPS device. This structure is allocated by either the application (in order to provide the stack with the details of the local device),
or the stack (in order to provide the application with the details of a remote device).
When allocated by the application, members must not be modified or deleted until the parent object is removed.
When allocated by the stack, all members are deleted when the parent object is removed.
*/
typedef struct ClxWlanWpsDeviceDetailsStruct
{
    u4                      supportedMethods;                                       /*!< Supported WPS methods as an OR-ed combination of values defined in ClxWpsSupportedMethod */   
    const s1*               deviceName;                                             /*!< WPS-based device name of the device. Truncated if longer than #CLX_WLAN_WPS_MAX_DEVICE_NAME_LENGTH bytes.
                                                                                         Set to NULL if not available */
    const s1*               modelName;                                              /*!< WPS-based model name of the device. Truncated if longer than #CLX_WLAN_WPS_MAX_MODEL_NAME_LENGTH bytes.
                                                                                         Set to NULL if not available */
    const s1*               modelNumber;                                            /*!< WPS-based model number of the device. Truncated if longer than #CLX_WLAN_WPS_MAX_MODEL_NUMBER_LENGTH bytes.
                                                                                         Set to NULL if not available */
    const s1*               manufacturerName;                                       /*!< WPS-based manufacturer name of the device. Truncated if longer than #CLX_WLAN_WPS_MAX_MANUFACTURER_NAME_LENGTH bytes.
                                                                                         Set to NULL if not available */
    const s1*               serialNumber;                                           /*!< WPS-based serial number of the device. Truncated if longer than #CLX_WLAN_WPS_MAX_SERIAL_NUMBER_LENGTH bytes.
                                                                                         Set to NULL if not available */
    const u1*               uuid;                                                   /*!< WPS-based UUID of the device, of size CLX_WLAN_WPS_UUID_LENGTH bytes. Set to NULL if not available */
    ClxWpsDeviceType        primaryDeviceType;                                      /*!< Primary device type */
} ClxWlanWpsDeviceDetails;


/**
Information on the WPS-related capabilities and configuration of a BSS.
*/
typedef struct ClxWlanWpsApInformationStruct
{
    ClxWlanWpsDeviceDetails         device;                                     /*!< Details of the AP as an WPS device */

    boolean                         registrarActivated;                         /*!< TRUE if the Registrar has been activated on the AP (e.g. by a push button, via a browser, ...) */                                                                                   
    ClxWpsPasswordType              passwordType;                               /*!< Type of password to be used for the WPS authentication session. Set to ClxWpsPasswordType_Invalid if not available */
} ClxWlanWpsApInformation;




/**
Indicates the PMF (Protected Management Frame) policy required for a connection.
*/
typedef enum ClxWlanPmfPolicyEnum
{
    ClxWlanPmfPolicy_Disabled,
    ClxWlanPmfPolicy_Capable,
    ClxWlanPmfPolicy_Required
} ClxWlanPmfPolicy;



typedef struct ClxWlanMeshIE_Struct
{
    const u1* payload;
    u2        payloadLength;
} ClxWlanMeshIE;



/**
The information related to the Basic Service Set(BSS)
*/
typedef struct ClxBSSInfoStruct
{
    u1                          bssid[CLX_MAC_ADDRESS_LENGTH];              /*!< The BSSID (Basic Service Set ID) */
    u2                          channel;                                    /*!< The operating frequency channel. In case of IEEE802.11n/ac, this is
                                                                                 the primary 20MHz channel. */
    ClxWlanFrequencyBand        band;                                       /*!< The operating frequency band */
    ClxBSSType                  bssType;                                    /*!< Type of the BSS */
    s4                          rssi;                                       /*!< Signal power level in dBm */
    u4                          authType;                                   /*!< Authentication types supported by the BSS, as a bit-wise 
                                                                                 combination of values of type #ClxAuthType */
    u4                          encProtocol;                                /*!< Encryption protocols supported by the BSS, as a bit-wise 
                                                                                 combination of values of type #ClxEncryptionProtocolEnum */
    u4                          capabilities;                               /*!< Capabilities supported by the BSS, as an bit-wise combination of 
                                                                                values defined in Wlan.Config.h */
    u2                          supportedNonHTRates;                        /*!< The list of non-HT (IEEE802.11abg) rates supported by the BSS, as a bit-wise 
                                                                                 combination of rate bits defined in Wlan.Config.h */

    u2			                beaconInterval;                             /*!< The beacon interval */
    u2			                dtimPeriod;                                 /*!< The DTIM period in units of beaconInterval (and NOT in time units). A value of 1 indicates that DTIM will be present in each beacon. */

    ClxWlanHTInfo               htInfo;                                     /*!< Information on the IEEE802.11n (HT) capabilities and operation of the BSS.
                                                                                 Valid only if BSS capabilities (e.g. ClxBSSInfo.capabilities) include #CLX_WLAN_CAPABILITY_HT_SUPPORTED. Otherwise, MUST be ignored */

    ClxWlanVHTInfo              vhtInfo;                                    /*!< Information on the IEEE802.11ac (VHT) capabilities and operation of the BSS.
                                                                                 Valid only if BSS capabilities (e.g. ClxBSSInfo.capabilities) include #CLX_WLAN_CAPABILITY_VHT_SUPPORTED. Otherwise, MUST be ignored  */

    ClxWlanHEInfo               heInfo;                                    /*!< Information on the IEEE802.11ax (HE) capabilities and operation of the BSS.
                                                                                 Valid only if BSS capabilities (e.g. ClxBSSInfo.capabilities) include #CLX_WLAN_CAPABILITY_HE_SUPPORTED. Otherwise, MUST be ignored  */

    ClxSSID                     ssid;                                       /*!< The SSID (Service Set ID) */
    ClxWlanWpsApInformation     wpsInformation;                             /*!< Information on the WPS-related capabilities and configuration of the BSS. 
                                                                                 Provides valid information only if the flag bit #CLX_WLAN_CAPABILITY_WPS_SUPPORTED is set in capabilities. 
                                                                                 Otherwise, this member must be ignored. */ 
    ClxWlanPmfPolicy            pmf;                                        /*!< Indicates the PMF (Protected Management Frame) policy required by the BSS */

    ClxWlanMeshIE*              meshBssIE;                                  /*!< ClarinoxMesh IE in binary format. Set only if the BSS is a ClarinoxMesh BSS and the ClxBSSInfo object has been obtained
                                                                                 via a Mesh Node Uplink interface.
                                                                                 IMPORTANT: The receiver of the ClxBSSInfo object may own ClxWlanMeshIE the object by setting this member to NULL.  
                                                                                            In this case, the ClxWlanMeshIE object MUST be deleted by a call to clxReleaseWlanMeshBssIE().
                                                                                            If the member is not set to NULL, then it will be automatically deleted by the ClarinxoWLAN stack */
} ClxBSSInfo CLX_CTYPE;


CLX_DEFINE_CONFIG_TYPE(ClxBSSInfo);


/**
The connection profile struct, used with the API function clxWlanConnect().

The BSS to connect to is identified by ssid and optionally by bssid.

Depending on whether the connection is open or secure, as well as the method of authentication used
(internal or external, e.g. via WPA Supplicant), some of the fields may or may not be required.
*/
typedef struct ClxWlanConnectionProfileStruct
{
    ClxSSID                     ssid;                    /*!< BSSID (name) of the network to connect to */   
    u1                          bssid[CLX_MAC_ADDRESS_LENGTH]; /*!< The BSS's MAC address. If set to broadcast 
                                                              (FF:FF:FF:FF:FF:FF), the BSS with the strongest signal
                                                              will be selected. */
                                                              
    ClxAuthType                 authTypeToUse;           /*!< Authentication type of BSS.
                                                              If authTypeToUse is not set to ClxAuthTypeOpenSystem, 
                                                              security credentials (e.g. PSK, passkey, certificate, ...) 
                                                              for the selected authentication suite need to be passed to 
                                                              the authentication module.
                                                              NOTE : This value is ignored if an external authentication module (e.g. wpa_supplicant) is being used */
                                                              
    u4                          cipherSuite;             /*!< OUI (Organizationally unique identifier) of the cipher suite
                                                              to be used for the connection security.
                                                              If authTypeToUse is ClxAuthTypeOpenSystem, this value will 
                                                              be ignored.
                                                              NOTE : This value is ignored if an external authentication module (e.g. wpa_supplicant) is being used */
                                                              
    ClxWlanSecurityCredential   securityCredential;      /*!< The security credential for authentication. 
                                                              This is required only if the ClarinoxWLAN internal 
                                                              authentication is being used.
                                                              NOTE : This member is ignored if an external authentication module (e.g. wpa_supplicant) is being used */        
} ClxWlanConnectionProfile;



/**
The conenction profile as provided by a WPS registrar. The base structure may be directly
passed to #clxWlanConnect.
*/
typedef struct ClxWlanWpsConnectionProfileSruct
{
    ClxWlanConnectionProfile        base;                                       /*!< Base structure, as passed to #clxWlanConnect. */

    ClxWifiSupportedStandard        authenticationStandard;                     /*!< The authentication standard to use in order to connect to this BSS.
                                                                                     The value will be either #ClxWifiSupportedStandard_WPA, or ClxWifiSupportedStandard_WPA2.
                                                                                     NOTE : This is an informative field only. ClarinoxWLAN will select the best method automatically. */
    boolean                         networkKeyShareable;                        /*!< If TRUE, the key provided by WPS registrar may be shared among several clients.
                                                                                     If FALSE, the key may only be used by the local client */
} ClxWlanWpsConnectionProfile;


/**
Data Structure for the indication #CLX_WLAN_BSS_DISCOVERED_INDICATION
*/
typedef struct ClxWlanBssDiscoveredIndicationStruct
{
    ClxBSSInfo  details;    /*!< Details of the discovered BSS */
} ClxWlanBssDiscoveredIndication;

/**
Data Structure for the indication #CLX_WLAN_STATION_JOINED_INDICATION
*/
typedef struct ClxWlanStationJoinedIndicationStruct
{
    u1  macAddress[CLX_MAC_ADDRESS_LENGTH];    /*!< The MAC address of the station joined or disconnected */
    u1  bssID[CLX_MAC_ADDRESS_LENGTH];         /*!< The BSSID to which the station has joined, or from which the station has 
                                              disconnected */
} ClxWlanStationJoinedIndication;


/**
Data Structure for the indication #CLX_WLAN_WPS_SESSION_COMPLETE_INDICATION
*/
typedef struct ClxWlanWpsSessionCompleteIndicationStruct
{
    u1                          macAddress[CLX_MAC_ADDRESS_LENGTH];    /*!< The MAC address of the station which was involved in the WPS session */
    ClxResult                   result;                          /*!< Result of the WPS session. A value of CLX_SUCCESS indicates that the station has been successfully provisioned using WPS. 
                                                                      Any other value indicates that the session failed. In this case, the device details must be ignored. */
    ClxWlanWpsDeviceDetails     deviceDetails;                   /*!< The WPS-related details of the proviosioned station. Must be ignored if the result is not CLX_SUCCESS. */ 
} ClxWlanWpsSessionCompleteIndication;

/**
Data Structure for the indication #CLX_WLAN_STATION_DISCONNECTED_INDICATION
*/
typedef struct ClxWlanStationDisconnectedIndicationStruct
{
    u1        macAddress[CLX_MAC_ADDRESS_LENGTH];    /*!< The MAC address of the station joined or disconnected */
    u1        bssID[CLX_MAC_ADDRESS_LENGTH];         /*!< The BSSID to which the station has joined, or from which the station
                                                    has disconnected */
    ClxError  reason;
} ClxWlanStationDisconnectedIndication;

/**
Data Structure for the indication #CLX_WLAN_STATION_AUTHENTICATION_INITIATED_INDICATION
*/
typedef struct ClxWlanStationAuthenticationInitiatedIndicationStruct
{
    u1  macAddress[CLX_MAC_ADDRESS_LENGTH];    /*!< The MAC address of the station initiated the authentication */
} ClxWlanStationAuthenticationInitiatedIndication;

/**
Data Structure for the indication #CLX_WLAN_STATION_AUTHENTICATION_COMPLETED_INDICATION
*/
typedef struct ClxWlanStationAuthenticationCompletedIndicationStruct
{
    ClxWlanStationAuthAssociationCompleted detail; /*!< Details of the station which has completed the authentication */
} ClxWlanStationAuthenticationCompletedIndication;

/**
Data Structure for the indication #CLX_WLAN_STATION_ASSOCIATION_INITIATED_INDICATION
*/
typedef struct ClxWlanStationAssociationInitiatedIndicationStruct
{
    u1  macAddress[CLX_MAC_ADDRESS_LENGTH];    /*!< The MAC address of the station initiated the association */
} ClxWlanStationAssociationInitiatedIndication;

/**
Data Structure for the indication #CLX_WLAN_STATION_ASSOCIATION_COMPLETED_INDICATION
*/
typedef struct ClxWlanStationAssociationCompletedIndicationStruct
{
    ClxWlanStationAuthAssociationCompleted detail; /*!< Details of the station which has completed the association. */
} ClxWlanStationAssociationCompletedIndication;

/**
Data Structure for the indication #CLX_WLAN_AP_DISCONNECTED_INDICATION
*/
typedef struct ClxWlanApDisconnectedIndicationStruct
{
    u1        macAddress[CLX_MAC_ADDRESS_LENGTH];    /*!< The MAC address of the disconnected AP */
    ClxError  reason;                          /*!< The reason why the connection has been terminated */
} ClxWlanApDisconnectedIndication;



/**
Data Structure for the indication #CLX_WLAN_BG_SCAN_TERMINATION_INDICATION
*/
typedef struct ClxWlanBgScanTerminatedIndicationStruct
{
    ClxError  reason;                          /*!< The reason of the termination */
} ClxWlanBgScanTerminatedIndication;



/**
Data structure for the indication #CLX_WLAN_DRIVER_SPECIFIC_INDICATION.
The actual data structure may derive from ClxWlanDriverSpecificIndication in the following manner:

struct ActualDriverSpecificIndication
{
    ClxWlanDriverSpecificIndication base;  // MUST be the very first member in the structure

    // Rest of the indication data
};
*/
typedef struct ClxWlanDriverSpecificIndicationStruct
{   
    const struct ClxConfigParamType* type;                        /*!< The type of the driver-specific indication */
} ClxWlanDriverSpecificIndication;


/**
Creates a WLAN virtual Interface on the WLAN physical adaptor, and associates a handle to it.
The handle is passed to any subsequent API call. After successful creation of a new virtual interface, the interface 
MUST be started (by calling the #clxWlanStartInterface() function), before any other API functions, which take the 
handle of the interface as an input argument, may be called. Refer \ref creating_wlan_interface for more information.

\param[ in ] stack                          Wi-Fi stack handle. A stack object must be created before any other operation.
\param[ in ] interfaceName                  The name of the interface that will be opened. Must be a null-terminated 
                                            string with the maximum length of 32 bytes, including the null-termination.
\param[ in ] interfaceType                  Interface of type #ClxInterfaceType.
\param[ in ] networkTransportInterface      Implementation of the network stack as a caller-allocated 
                                            ClxNetworkAccessInterface object. This is the interface between ClarinoxWLAN
                                            stack and the external Network (e.g. TCP/IP) stack. This parameter CANNOT be
                                            NULL. The object is allocated by the caller, and CANNOT be deleted or 
                                            modified until the virtual interface is stopped by calling 
                                            clxWlanStopInterface() function (or clxWlanStartInterface() returns 
                                            an error).
\param[ out ] handle                        A handle for the created virtual interface. NULL if the creation fails.

\return One of the following values:

        #CLX_SUCCESS: The interface has been created successfully. #handle will contain the handle to the interface.
        #CLX_ERROR_INVALID_COMMAND_ARGUMENT: The argument #networkTransportInterface is NULL.
        #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_VIRTUAL_INTERFACE: The type of the interface (as indicated by the argument #interfaceType) is not supported in this build.
        #CLX_WLAN_ERROR_STACK_NOT_INITIALIZED: ClarinoxWLAN stack has not yet been initialized.
        #CLX_WLAN_ERROR_NOT_ENOUGH_RESOURCES: There are two many virtual interfaces created already (The maximum number of virtual interfaces may be limited by the driver implementation).
        #CLX_WLAN_ERROR_UNKNOWN_VIRTUAL_INTERFACE: A virtual interface by the provided name (as indicated by the argument #interfaceName) has not been implemented.
        #CLX_WLAN_ERROR_CHIPSET_NOT_SUPPORTED: The WLAN chipset/hardware is not supported by the current driver. This error may also occur if the Bus (e.g. SDIO) has not been configured correctly, so the driver is not able to access the controller internal registers.
        #CLX_WLAN_ERROR_BOOT_PROCESS_FAILED: The booting procedure for the WLAN controller has failed. Generally, the boot process includes resetting, loading the firmware, and configuring the controller.
        #CLX_WLAN_ERROR_NO_FIRMWARE_FOUND: The firmware file is not found or cannot be accessed by the driver.
        #CLX_WLAN_ERROR_BAD_FIRMWARE_FORMAT: The provided firmware is of invalid format, or an error occurred while reading the firmware file.
        
        Also, Bus-specific (e.g. SDIO-specific) error codes may also be returned if the initialization of the Bus fails.
*/
ClxError clxWlanCreateInterface(_in_ ClxStack                                 stack,
                                _in_ const s1*                                interfaceName,
                                _in_ ClxInterfaceType                         interfaceType,
                                _in_ struct ClxNetworkAccessInterface*        networkTransportInterface,
                                _user_out_ ClxHandle*                         handle);


/**
Data Structure for the indication #CLX_WLAN_INTERFACE_GET_MAC_ADDR_COMPLETE
*/
typedef struct ClxWlanInterfaceGetMacAddrCompleteStruct
{
    _user_out_ u1*  macAddrBuffer;    /*!< The buffer where the MAC address will be returned. The buffer must be pre-
                                           allocated by the user and must have enough space to hold the MAC address
                                           (which is an array of u1[CLX_MAC_ADDRESS_LENGTH]). */
} ClxWlanInterfaceGetMacAddrComplete;

/**
Gets the MAC address of the given interface on the local machine. This function MUST be called only if the interface is 
successfully started (by a call to the #clxWlanStartInterface() function).

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WLAN_INTERFACE_GET_MAC_ADDR_COMPLETE.
                   The parameter of this indication is of type #ClxWlanInterfaceGetMacAddrComplete.

\param[ in ] interfaceHandle    The WLAN interface handle. A WLAN interface should be opened first with the clxWlanCreateInterface() function.
\param[ out ] macAddrBuffer     The buffer where the MAC address will be returned. The buffer must be pre-allocated by 
                                the user and must have enough space to hold the MAC address (which is an array of u1[CLX_MAC_ADDRESS_LENGTH]).
\param[ in ] block              Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED: The virtual interface has not been started yet (by a call to #clxWlanStartInterface).
*/
ClxResult clxWlanInterfaceGetMacAddr(_in_ ClxHandle  interfaceHandle,
                                     _user_out_ u1*  macAddrBuffer,
                                     _in_ boolean    block);


/**
Retrieves the value of one or more driver parameters requested by the user.

The set of parameters that can be interrogated is driver-specific. Refer to the documentation of the driver used for the
list of parameters.

This function MUST be called only if the interface is successfully started (by a call to clxWlanStartInterface()).

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type 
                   #CLX_WLAN_GET_PARAMETERS_VALUE_COMPLETE.
                   This indication does not have any parameters.

\param[ in ]    interfaceHandle     The WLAN interface handle. A WLAN interface should be opened first with the clxWlanCreateInterface() function.
\param[ inout ] configList          The list of parameters to be interrogated, as a set of name/value pairs. The list object, and all its child objects, must not be modified or deleted until 
                                    this command is complete. These objects are all allocated by the caller.
\param[ in ]    block               Indicates mode of operation:
                                        TRUE: Blocking mode
                                        FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED: The virtual interface has not been started yet (by a call to #clxWlanStartInterface).
*/
ClxResult clxWlanGetParametersValue(_in_ ClxHandle          interfaceHandle,
                                    _inout_ ClxConfigList*  configList,
                                    _in_ boolean            block);


/**
Sets the value of one or more driver parameters requested by the user.
The set of parameters that can be configured is driver-specific. Refer to the documentation of the driver used for the 
list of parameters.

This function MUST be called only if the interface is successfully started (by a call to clxWlanStartInterface()).

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type 
                   #CLX_WLAN_SET_PARAMETERS_VALUE_COMPLETE.
                   This indication does not have any parameters.

\param[ in ]    interfaceHandle     The WLAN interface handle. A WLAN interface should be opened first with the clxWlanCreateInterface() function.
\param[ inout ] configList          The list of parameters to be configured, as a set of name/value pairs. The list object, and all its child objects, must not be modified or deleted until
                                    this command is complete. These objects are all allocated by the caller. The driver will only perform a READ-ONLY access on these parameters.
\param[ in ]    block               Indicates mode of operation:
                                        TRUE: Blocking mode
                                        FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED: The virtual interface has not been started yet (by a call to #clxWlanStartInterface).
        - #CLX_ERROR: One or more of the configuration parameters could not be set successfully.
*/
ClxResult clxWlanSetParametersValue(_in_ ClxHandle          interfaceHandle,
                                    _inout_ ClxConfigList*  configList,
                                    _in_ boolean            block);


/**
Starts the virtual interface operation which will provide service using the given WLAN Interface.
A valid ClxHandle (of the interface) must be provided and the interface should be of type #ClxIfTypeAP.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type 
                   #CLX_WLAN_START_INTERFACE_COMPLETE.
                   This indication does not have any parameters.

\param[ in  ]   interfaceHandle     The WLAN interface handle. A WLAN interface should be opened first with the clxWlanCreateInterface() function.
\param[ inout ] configList          List of the initial configuration parameters.
\param[ in  ]   block               Indicates mode of operation:
                                        TRUE: Blocking mode
                                        FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
        - #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED: Interface failed to start due to some reason
                                                (signal strength, not powered etc.)

        - #CLX_WLAN_ERROR_PRE_ASSOC_AUTHENTICATION_NOT_SUPPORTED: WEP40 and WEP104 encryption suites (as requested as a configuration parameter in configList as type #ClxConfigList) are not supported by ClarinoxWLAN as they are obsolete.
        - #CLX_WLAN_ERROR_TOO_MANY_REQUESTS_PENDING: The virtual-interface-start task is currently running.
        - #CLX_WLAN_ERROR_INTERFACE_IN_WRONG_STATE: The virtual interface is in a wrong state (e.g. Starting, Started, Stopping).
        - #CLX_WLAN_ERROR_NOT_IMPLEMENTED: The required role (as indicated by the third argument to #clxWlanCreateInterface) is not supported by the current driver.
        - #CLX_WLAN_ERROR_INVALID_PARAMETERS: One of the configuration parameters has a wrong value, or is missing in the configList parameters list.
        - #CLX_WLAN_ERROR_HW_COMMAND_COMPLETE_TIMEOUT: A command to the WLAN controller has timed out (e.g. the WLAN controller is not responsive).
        - #CLX_WLAN_FAILED: Sending a command to the WLAN controller has failed (e.g. the WLAN controller has returned an error as the response to the command).
        - #CLX_ERROR_BAD_STATE: The virtual interface is in a bad state (same as #CLX_WLAN_ERROR_INTERFACE_IN_WRONG_STATE).
        - #CLX_WLAN_ERROR_NOT_ENOUGH_RESOURCES: There is not enough memory or resources (e.g. WLAN controller internal resources) in order to start the interface.
                                                        
        Also, Network-Access-Interface-specific error codes may be returned if starting of the network access interface fails.
*/
ClxResult clxWlanStartInterface(_in_ ClxHandle          interfaceHandle,
                                _inout_ ClxConfigList*  configList,
                                _in_ boolean            block);

/**
Stops the virtual interface operation.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WLAN_STOP_INTERFACE_COMPLETE.
                   This indication does not have any parameters.

\param[ in ] interfaceHandle    The WLAN interface handle. A WLAN interface should be opened first with the clxWlanCreateInterface() function.
\param[ in ] block              Indicates mode of operation:
                                    TRUE: Blocking mode
                                    FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_WLAN_ERROR_TOO_MANY_REQUESTS_PENDING: The virtual-interface-stop task is currently running.
        - #CLX_WLAN_ERROR_INTERFACE_IN_WRONG_STATE: The virtual interface is in a wrong state (e.g. Starting, Stopping, Stopped).
        - #CLX_WLAN_ERROR_HW_COMMAND_COMPLETE_TIMEOUT: A command to the WLAN controller has timed out (e.g. the WLAN controller is not responsive).
        - #CLX_WLAN_FAILED: Sending a command to the WLAN controller has failed (e.g. the WLAN controller has returned an error as the response to the command).
*/
ClxResult clxWlanStopInterface(_in_ ClxHandle  interfaceHandle,
                               _in_ boolean    block);

/**
Starts the WLAN role which is associated to this interface. This function MUST be called only if the interface is 
successfully started (by a call to the clxWlanStartInterface() function).

This function can ONLY be used when the local interface has been configured as an AccessPoint. With Station and ADHOC 
mode, role start is automatically performed during the connection procedure.

Normally, This procedure involves the following steps:

- The chip RF transceiver is powered on. Thus, thus chip will be able to send and receive packets.
- The stack informs the network interface that the link is now up, and packets can be sent over the air.

The first step might not be implemented by all drivers. In this case, the RF transceiver is on as soon as 
clxWlanStartInterface() returns with success. However, the second step is always performed. Therefore, it is MANDATORY 
to call this function (in AccessPoint mode) after the successful start of the interface in order to make sure that
(at least) the network interface will operate properly.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the callback function will be called with an indication of type 
                   #CLX_WLAN_START_ROLE_COMPLETE.
                   This indication does not have any parameters.

\param[ in  ] interfaceHandle  The WLAN interface handle. A WLAN interface should be opened first with the
                                   clxWlanCreateInterface() function.
\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_VIRTUAL_INTERFACE: This API is not supported by the virtual interface.
        - #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED: The virtual interface has not been started yet (by a call to #clxWlanStartInterface).
        - #CLX_WLAN_ERROR_KEY_INSTALLATION_FAILED: Installation of required security key in the WLAN controller failed.
        - #CLX_WLAN_ERROR_ROLE_HAS_STARTED: The role is already started.
        - #CLX_ERROR_BAD_STATE: The virtual interface is in a bad state (same as #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED).
        - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_ROLE: This API is not supported in the current role of the virtual interface.
        - #CLX_WLAN_ERROR_NOT_ENOUGH_RESOURCES: There is not enough memory or resources (e.g. WLAN controller internal resources) in order to start the interface.
        - #CLX_WLAN_FAILED: An internal error has occurred, or sending a command to the WLAN controller has failed (e.g. the WLAN controller has returned an error as the response to the command).
        - #CLX_WLAN_ERROR_HW_COMMAND_COMPLETE_TIMEOUT: A command to the WLAN controller has timed out (e.g. the WLAN controller is not responsive).
*/
ClxResult clxWlanStartRole(_in_ ClxHandle  interfaceHandle,
                           _in_ boolean    block);

/**
Stops the WLAN role which is associated to this interface.

This function MUST be called only if the interface is successfully started (by a call to clxWlanStartInterface()).

This function can ONLY be used when the local interface has been configured as an AccessPoint. With Station and ADHOC 
mode, role start is automatically performed during the disconnection procedure.

Normally, This procedure involves the following steps:

- All client stations (station currently connected to the local AccessPoint, or about to be connected) are removed.
  If necessary, a deassociation or de-authentication frame is sent to the remote stations in order to inform them of the
  connection loss.
- The chip RF transceiver is powered off. Thus, thus chip will not be able to send and received packets.
- The stack informs the network interface that the link is now down.

The second step might not be implemented by all drivers. In this case, the RF transceiver is powered off only when the 
interface is stopped. However, the first and third steps are always performed.

NOTE : Although it is not mandatory to call this function before stopping the interface, it is recommended that this be 
       done since clxWlanStopRole() provides a peaceful termination of connections by sending appropriate disconnection 
       frames to the connected stations. clxWlanStopInterface() carries out the same steps (if not yet carried out), 
       except for peaceful termination of the connections.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WLAN_STOP_ROLE_COMPLETE.
                   This indication does not have any parameters.

\param[ in  ] interfaceHandle  The WLAN interface handle. A WLAN interface should be opened first with the 
                                   clxWlanCreateInterface() function.
\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_VIRTUAL_INTERFACE: This API is not supported by the virtual interface.
        - #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED: The virtual interface has not been started yet (by a call to #clxWlanStartInterface).
        - #CLX_WLAN_ERROR_TOO_MANY_REQUESTS_PENDING: The virtual-interface-stop-role task is currently running.
        - #CLX_WLAN_ERROR_ROLE_NOT_STARTED: The role is not yet started.
        - #CLX_ERROR_TIMEOUT_OCCURRED: Sending of an WLAN packet has timed out (e.g. the local device or the remote device is not responsive).
        - #CLX_WLAN_ERROR_HW_COMMAND_COMPLETE_TIMEOUT: A command to the WLAN controller has timed out (e.g. the WLAN controller is not responsive).
        - #CLX_WLAN_FAILED: Sending a command to the WLAN controller has failed (e.g. the WLAN controller has returned an error as the response to the command).
        - #CLX_ERROR_BAD_STATE: The virtual interface is in a bad state (same as #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED).
*/
ClxResult clxWlanStopRole(_in_ ClxHandle  interfaceHandle,
                          _in_ boolean    block);

/**
Performs A WLAN Scan. This scans for available BSSs (APs) in the vicinity.

This function MUST be called only if the interface is successfully started (by a call to clxWlanStartInterface()).

This command will not complete until the scan procedure is complete or an error occurs. If any BSS is discovered during 
this time, an indication of #CLX_WLAN_BSS_DISCOVERED_INDICATION will be sent to the application. 

NOTE : This operation may not have been implemented for some interface types or roles. Refer \ref subsec_scan_api_usage for more information on usage and configuration.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WLAN_SCAN_COMPLETE.
                   This indication does not have any parameters.

\param[ in  ] interfaceHandle  The WLAN interface handle. A WLAN interface should be opened first with the 
                                   clxWlanCreateInterface() function.

\param[ in  ] bssid        (Optional) BSSID of the AccessPoint to scan for. If set to NULL, the scan results will NOT be filtered by BSSID.

\param[ in  ] ssid         (Optional) SSID of the network to search for. If ssid is NULL than all the available BSSs will be searched.

\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

            - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode). The result of the scan will be available via the call-back function.
            - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode). The application logic needs wait until the current scan operation is finished.
            - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet. The application logic needs wait until the current scan operation is finished.
            - #CLX_ERROR_INVALID_HANDLE: Invalid handle is passed to the API.

            - #CLX_ERROR_TIMEOUT_OCCURRED: Timeout has occurred before the scan operation is completed. <b> This is a critical error the application needs to shut down and restart the Station interface to recover </b>.
            - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_VIRTUAL_INTERFACE: This API is not supported by the virtual interface.
            - #CLX_WLAN_ERROR_TOO_MANY_REQUESTS_PENDING: The virtual-interface-scan task is currently running. The application logic needs wait until the current scan operation is finished.
            - #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED: The virtual interface has not been started yet (by a call to #clxWlanStartInterface).
            - #CLX_WLAN_ERROR_SCAN_FAILED: The operation has failed. <b> This is a critical error the application needs to shut down and restart the Station interface to recover </b>.
            - #CLX_WLAN_FAILED: An internal error has occurred, or sending a command to the WLAN controller has failed (e.g. the WLAN controller has returned an error as the response to the command).<b> This is a critical error the application needs to shut down and restart the Station interface to recover </b>.
            - #CLX_WLAN_ERROR_HW_COMMAND_COMPLETE_TIMEOUT: A command to the WLAN controller has timed out (e.g. the WLAN controller is not responsive). <b> This is a critical error the application needs to shut down and restart the Station interface to recover </b>.
            - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_ROLE: This operation is not supported by this interface current role, E.g. scan API used with access point role.
            - #CLX_WLAN_ERROR_VENDOR_SPECIFIC_IE_NOT_SUPPORTED_BY_DRIVER: Decoding of Vendor Specific Information Elements is not supported by this driver. the argument vendorSpecificIeDecoder needs to be set to NULL.
*/
ClxResult clxWlanScan(_in_ ClxHandle                    interfaceHandle,
                      _user_in_ const u1*               bssid,
                      _user_in_ const ClxSSID*          ssid,
                      _in_ boolean                      block);


/**
Starts Background scan. As opposed to the normal scan (please refer to #clxWlanScan() documentation), the background scan is expected to have a less impact on the ongoing data traffic.

NOTE : This operation may not have been implemented for some WLAN drivers, interface types or roles.

This function MUST be called only if the interface is successfully started (by a call to clxWlanStartInterface()).

This command is complete when the background scan is started successfully or an error occurs.
When the background scan is successfully started, an indication of #CLX_WLAN_BSS_DISCOVERED_INDICATION will be sent to the application for each BSS discovered.

NOTE : Configuration parameters for the background scan are not directly passed to this command since these parameters are WLAN driver specific. Generally,
       the background scan configuration parameters are passed to the driver before issuing this command by a call to #clxWlanSetParametersValue(). Please refer to sample application provided,
       or contact Clarinox for more information on the background scan configuration details for each supported WLAN driver.

The background scan may be explicitly stopped by the user at any time by a call to clxWlanStopBgScan(). 
In addition, the background scan may be terminated by the driver for any reason. In this case, an indication of type #CLX_WLAN_BG_SCAN_TERMINATION_INDICATION will be sent to the application.

Blocking mode: This function will not return until the command is complete. The function return value indicates the
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WLAN_START_BG_SCAN_COMPLETE.
                   This indication does not have any parameters.

\param[ in  ] interfaceHandle  The WLAN interface handle. A WLAN interface should be opened first with the
                                   clxWlanCreateInterface() function.

\param[ in  ] enableAutoRestart If TRUE, WLAN stack attempts to automatically restart the background scan when the current background scan session is complete. This will continue until the background scan
                                is stopped by a call to clxWlanStopBgScan(), or an error occurs.
                                If FALSE, when the current background scan session is complete, an indication of type #CLX_WLAN_BG_SCAN_TERMINATION_INDICATION will be sent to the application.
                                NOTE : the WLAN driver specific configuration parameters define a background scan session, and when and how it is considered complete.  

\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode). The result of the scan will be available via the call-back function.
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode). The application logic needs wait until the current scan operation is finished.
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet. The application logic needs wait until the current scan operation is finished.
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle is passed to the API.

        - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_VIRTUAL_INTERFACE: This API is not supported by the virtual interface.
        - #CLX_WLAN_ERROR_NOT_IMPLEMENTED : This API has not been implemented by the WLAN driver.
        - #CLX_ERROR_BAD_STATE: The background scan is already running, or this API has been issued in a wrong state.
        Any other error codes indicate an error. 

*/
ClxResult clxWlanStartBgScan(_in_ ClxHandle     interfaceHandle, 
                             _in_ boolean       enableAutoRestart,
                             _in_ boolean       block);



/**
Stops the ongoing background scan. The background scan must already been started by a previous call to clxWlanStartBgScan().

NOTE : This operation may not have been implemented for some WLAN drivers, interface types or roles.

This function MUST be called only if the interface is successfully started (by a call to clxWlanStartInterface()).

This command is complete when on the following conditions occur: 

- The background scan is stopped immediately. In this case, the command will be complete with the result CLX_SUCCESS.
- The background scan is scheduled to be stopped as soon as possible. In this case, the command will be complete with the result CLX_WLAN_ERROR_BG_SCAN_TERMINATION_PENDING. 
  When the background scan is terminated, an indication of type #CLX_WLAN_BG_SCAN_TERMINATION_INDICATION will be sent to the application. In this case, the background scan is not considered stopped until the indication is received. 
- An error occurs. In this case, the command will be complete with an error code other than CLX_SUCCESS or CLX_WLAN_ERROR_BG_SCAN_TERMINATION_PENDING.

Blocking mode: This function will not return until the command is complete. The function return value indicates the
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WLAN_STOP_BG_SCAN_COMPLETE.
                   This indication does not have any parameters.

\param[ in  ] interfaceHandle  The WLAN interface handle. A WLAN interface should be opened first with the
                                   clxWlanCreateInterface() function.

\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode). The result of the scan will be available via the call-back function.
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode). The application logic needs wait until the current scan operation is finished.
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet. The application logic needs wait until the current scan operation is finished.
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle is passed to the API.

        - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_VIRTUAL_INTERFACE: This API is not supported by the virtual interface.
        - #CLX_WLAN_ERROR_BG_SCAN_TERMINATION_PENDING : The background scan is scheduled to be stopped as soon as possible.
                                                         In this case, when the background scan is terminated, an indication of type #CLX_WLAN_BG_SCAN_TERMINATION_INDICATION will be sent to the application.
        - #CLX_ERROR_BAD_STATE: The background scan is not currently running, or this API has been issued in a wrong state.
        Any other error codes indicate an error.
*/
ClxResult clxWlanStopBgScan(_in_ ClxHandle     interfaceHandle,
                            _in_ boolean       block);


/**
Makes a connection using the provided connection profile.
By this method the authentication and association operations are handled.

When there is no connection to a BSS, this API is called to connect the station to a BSS.
If there is already a connection to a BSS, this API may be called to re-associate to the same AP or a new AP in the 
same BSS (e.g. with the same BSSID).

The Authentication type of the BSS (ClxAuthTypeOpenSystem, ClxAuthTypePresharedKey, ClxAuthTypeIEEE802_1x, etc.) and the cipher suite to use (ClxEncProtoTKIP, ClxEncProtoAES_CCMP, etc.)
are required for establishing the connection to the access point and are provided to the API using the #ClxWlanConnectionProfile argument. These values of authentication type and cipher suite
can be found by first performing a selective scan for the access point of interest and retreaving the #ClxBSSInfoStruct which is provided along with the #CLX_WLAN_BSS_DISCOVERED_INDICATION.

This function MUST be called only if the interface is successfully started (by a call to clxWlanStartInterface()).


If this function returns #CLX_ERROR_CONNECTION_EXISTS or if the link cannot be recovered, the API function #clxWlanDisconnect() MUST be 
called before calling #clxWlanConnect.

NOTE : This operation is only implemented for STA roles.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WLAN_CONNECT_COMPLETE.
                   This indication does not have any parameters.

\param[ in  ] interfaceHandle  The WLAN interface handle. A WLAN interface should be opened first with the
                                   clxWlanCreateInterface() function.
\param[ in  ] connProfile      A user-allocated structure of type #ClxWlanConnectionProfile which contains the ssid and
                                   optionally the BssID to connect to, the authentication type, the encryption protocol and key 
                                   information. See #ClxWlanConnectionProfile for further details.
                                   NOTE : The object must not be deleted or modified until this command is complete.
\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
        
        - #CLX_ERROR_CONNECTION_EXISTS: There is already a connection, #clxWlanDisconnect() MUST be called before calling #clxWlanConnect
        - #CLX_WLAN_ERROR_INVALID_PARAMETERS: The argument connProfile is NULL.
        - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_ROLE: This operation is not supported by this interface current role.
        - #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED: The virtual interface has not been started yet (by a call to #clxWlanStartInterface).
        - #CLX_WLAN_ERROR_REQUESTED_AUTH_NOT_SUPPORTED_BY_DRIVER: The requested Authentication method is not supported by the current driver.
        - #CLX_WLAN_ERROR_REQUESTED_ENC_NOT_SUPPORTED_BY_BSS: The requested Encryption protocol is not supported by the remote AP.
        - #CLX_WLAN_ERROR_INVALID_GROUPWISE_CIPHER: The Groupwise Cipher Suite requested by the remote AP is not supported by ClarinoxWLAN in the current configuration. 
        - #CLX_WLAN_ERROR_BASIC_RATE_SET_NOT_SUPPORTED: The basic rates requested by the remote AP are not all supported  by ClarinoxWLAN in the current configuration.
        - #CLX_WLAN_ERROR_CONNECTION_ATTEMPT_TIMEOUT: Connection procedure has timed out.
        - #CLX_WLAN_ERROR_IEEE802_1X_AUTHENTICATION_FAILED: Authentication procedure has timed out.
        - #CLX_WLAN_ERROR_INTERFACE_IN_WRONG_STATE: The virtual interface is in a wrong state.
        - #CLX_WLAN_ERROR_BSS_INFO_NOT_AVAILABLE: The information on the requested BSS could not be obtained (e.g. The BSS does not exist or is not in the range, or the scanning procedure has failed).
        - #CLX_WLAN_FAILED: An internal error has occurred, or sending a command to the WLAN controller has failed (e.g. the WLAN controller has returned an error as the response to the command).
        - #CLX_WLAN_ERROR_HW_COMMAND_COMPLETE_TIMEOUT: A command to the WLAN controller has timed out (e.g. the WLAN controller is not responsive).     
        - #CLX_WLAN_ERROR_INVALID_PRE_ASSOC_AUTHENTICATION_ALGORITHM: The remote AP is trying to use legacy (WEP) Authentication method which is not supported by ClarinoxWLAN.
        - #CLX_WLAN_ERROR_UNEXPECTED_SEQUENCE_NUMBER: Invalid sequence number in Authentication frame.
        - #CLX_WLAN_ERROR_BSS_TYPE_DOES_NOT_MATCH_INTERFACE_TYPE: The remote BSS is an independent BSS (IBSS, also known as AdHoc), which is not supported by ClarinoxWLAN.
        - #CLX_WLAN_ERROR_TOO_MANY_REQUESTS_PENDING: The virtual-interface-connect task is currently running.
        - #CLX_ERROR_TIMEOUT_OCCURRED: Sending of an WLAN packet has timed out (e.g. the local device or the remote device is not responsive).
        - #CLX_ERROR_BAD_STATE: The virtual interface is in a bad state (same as #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED).

        Also, any standard IEEE802.11 status code may be returned if is has been received from the remote AP.
*/
ClxResult clxWlanConnect(_in_ ClxHandle                             interfaceHandle,
                         _user_in_ const ClxWlanConnectionProfile*  connProfile,
                         _in_ boolean                               block);

/**
Data Structure for the indication #CLX_WLAN_GET_CONNECTION_PROFILE_WITH_WPS_COMPLETE.
*/
typedef struct ClxWlanGetConnectionProfileWithWpsCompleteStruct
{
    _inout_ ClxWlanWpsConnectionProfile*   profile;   /*!< Holds the connection profile information for the authenticated Access Point.
                                                              The base structure (profile.base) The object may be passed to #clxWlanConnect() to initiate a connection to the Access Point.
                                                              If the command has not been successful, this argument shall be ignored. */
} ClxWlanGetConnectionProfileWithWpsComplete;


/**
Retrieves connection profile for a WPS-enabled Access Point using the WiFi Protected Setup (WPS) technology.

This API command scans for WPS-enabled Access Points for up to 2 minutes. If an Access Point in 'activated' WPS mode is discovered,
the local device will carry out the WPS authentication procedure with the Access Point. If the authentication procedure has been successful,
the retrieved connection profile (including the SSID, BSSID, Encryption Key, and other information) is returned. Then, the connection profile
may be used to connect to the Access Point by a call to #clxWlanConnect() function.

If no activated access point is discovered during the 2-minute window, the command will be complete with the error CLX_ERROR_TIMEOUT_OCCURRED.

The local device (called WPS Enrollee) is authenticated against a WPS registrar. The registrar may be the same as the Access Point, or
a separate server in the LAN. For the WPS authentication procedure to succeed, the registrar must be activated by the user. This could be achieved by pushing
a key, entering a PIN code into the registrar (only in case of the enrollee using a PIN code), or other mechanisms. Refer to the documentation of your
WPS Registrar/Access Point for more information.

Optionally, a PIN code may be provided to this command, which will be used during the authentication procedures. The PIN code may be fixed (e.g. printed on
a label attached to the local device), or generated randomly on the fly. In either case, the PIN code must be visible to the user as it needs to be supplied
to the registrar as well. If no PIN code is provided to this command, the authentication procedure will be performed using PBC (Push Button) method.

NOTE : This command will try to authenticate to at most one Access Point.. 

NOTE : This operation is only implemented for STA roles.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WLAN_CONNECT_COMPLETE.
                   This indication does not have any parameters.

\param[ in ]  interfaceHandle       The WLAN interface handle. A WLAN interface should be opened first with the clxWlanCreateInterface() function.
\param[ out ] profile               A user-provided object of type ClxWlanConnectionProfile which, on a successful completion, will hold the connection profile information
                                    for the authenticated Access Point. The object may be passed to #clxWlanConnect() to initiate a connection to the Access Point.
                                    If the command has not been successful, this argument shall be ignored.
\param[ in ]  localDeviceDetails    Details of an WPS device as defined in #ClxWlanWpsDeviceDetailsStruct
\param[ in ]  passwordType          Password type as defined in #ClxWpsPasswordTypeEnum
\param[ in ]  pinCode               A user-allocated buffer containing the PIN code to be used for authentication.
                                    In order to generate
                                    a correct PIN code, use #clxWlanGenerateRandomWpsPinCode() API function.
                                    If set to NULL, no PIN code will be required and used for authentication.
\param[ in ]  block                 Indicates mode of operation:
                                        TRUE: Blocking mode
                                        FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
                                        OR the command was explicitly cancelled by a call to clxWlanCancelWpsConnectionRequest() function.
        - #CLX_ERROR_TIMEOUT_OCCURRED: Timeout occurs.
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the arguments are invalid.
        - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_ROLE: This operation is not supported by this interface current role.
*/
ClxResult clxWlanGetConnectionProfileWithWps(_in_ ClxHandle                            interfaceHandle,
                                             _inout_ ClxWlanWpsConnectionProfile*      profile,
                                             _user_in_ const ClxWlanWpsDeviceDetails*  localDeviceDetails,
                                             _in_ ClxWpsPasswordType                   passwordType,
                                             _user_in_ const s1*                       pinCode,
                                             _in_ boolean                              block);

/**
Generates a 4-digit or a 8-digit numeric random PIN code to be used by the WPS Enrollee. The generated PIN code may be passed to #clxWlanGetConnectionProfileWithWps() function.

\param[ in ] buffer             A caller-allocated buffer which, on a successful return, will contain the generated PIN code as a NULL-terminated ASCII string. 
                                The buffer shall be large enough to accommodate the generated PIN code, and the NULL terminated character.
                                If pinCodeLength is 4, buffer shall be at least 5 bytes long.
                                If pinCodeLength is 8, buffer shall be at least 9 bytes long.

\param[ in ] pinCodeLength      Length of the PIN code to be generated. SHALL be either 4 or 8. If any other value is provided, this function will return an error.

\return CLX_SUCCESS if a PIN code was generated successfully.
CLX_ERROR_INVALID_COMMAND_ARGUMENT if the value of pinCodeLength was not either 4 or 8.
*/
ClxResult clxWlanGenerateRandomWpsPinCode(_in_ s1* buffer, 
                                              _in_ u4 pinCodeLength);

/**
Verifies that the provided WPS PIN code is valid. A valid WPS PIN code is a NULL-terminated string which must have the following characteristics:

- It is either 4 or 8 characters long.
- Each character is one of ASCII '0'-'9' digits. 
- In case of a 8-digit PIN code, the last digit must be a valid checksum value.

\param[ in ] pinCode The PIN code to be verified, as a NULL terminated string. This argument may be NULL.

\return CLX_SUCCESS if pinCode is a valid WPS PIN code, or if pinCode is NULL.
CLX_ERROR_INVALID_COMMAND_ARGUMENT is pinCode is not a valid WPS PIN code.
*/
ClxResult clxWlanValidateWpsPinCode(_in_ const s1* pinCode);


ClxResult clxWlanActivateWpsRegistrar(_in_ ClxHandle interfaceHandle,
                                      _in_ ClxWpsPasswordType devicePasswordID,
                                      _user_in_ const u1* remoteDeviceAddr,
                                      _user_in_ const s1* pinCode,
                                      _in_ boolean block);


ClxResult clxWlanDeactivateWpsRegistrar(_in_ ClxHandle interfaceHandle,
                                        _in_ boolean block);


/**
Disconnects an active connection. In Station role, this API is called to disconnect the local station from the BSS (wireless network).
In AP role, this API is called to disconnect an associated client from the local access point.

This function MUST be called only if the interface is successfully started (by a call to clxWlanStartInterface()).

NOTE : This operation may not have been implemented for some interface types or roles. Refer to the relevant driver 
       documentation for more information.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type 
                   #CLX_WLAN_DISCONNECT_COMPLETE.
                   This indication does not have any parameters.

\param[ in  ] interfaceHandle  The WLAN interface handle. A WLAN interface should be opened first with the
                                   clxWlanCreateInterface() function.
\param[ in  ] clientMacAddress In AP role, this is the MAC address of the associated client which needs to be disconnected from the local access point. In this role, this argument must not be NULL.
                                 In Station role, this argument must be set to NULL and will be ignored by the ClarinoxWLAN stack. 
\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED: The virtual interface has not been started yet (by a call to #clxWlanStartInterface).
        - #CLX_WLAN_ERROR_NOT_SUPPORTED_BY_ROLE: This operation is not supported by this interface current role.
        - #CLX_ERROR_CONNECTION_NOT_EXIST: There is no connection to the remote device.
        - #CLX_WLAN_FAILED: An internal error has occurred, or sending a command to the WLAN controller has failed (e.g. the WLAN controller has returned an error as the response to the command).
        - #CLX_WLAN_ERROR_HW_COMMAND_COMPLETE_TIMEOUT: A command to the WLAN controller has timed out (e.g. the WLAN controller is not responsive).
        - #CLX_ERROR_TIMEOUT_OCCURRED: Sending of an WLAN packet has timed out (e.g. the local device or the remote device is not responsive).
        - #CLX_ERROR_BAD_STATE: The virtual interface is in a bad state (same as #CLX_WLAN_ERROR_INTERFACE_NOT_STARTED).
*/
ClxResult clxWlanDisconnect(_in_ ClxHandle  interfaceHandle,
                            _in_ const u1*  clientMacAddress,
                            _in_ boolean    block);




typedef struct ClxWlanSendTestCommandCompleteStruct
{
    _user_out_ u1*                      responseBuffer;
    _user_out_ u4*                      responseLength;
} ClxWlanSendTestCommandComplete;


/**
Returns the ClarinoxWLan version.
\return A function-allocated buffer containing the version as a null-terminated string.
        The buffer must NOT be modified by the caller.
        Version is in the form of "[major_version].[minor_version].[revision].p[patch_no]"
*/
const s1* clxGetClarinoxWlanVersion(void);



#ifdef __cplusplus
}
#endif



#endif // Wlan_Api_h

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
