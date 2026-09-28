#ifndef __Gap_Ble_Api_h__
#define __Gap_Ble_Api_h__

/********************************************************************************
*
* Project             ClarinoxBlue
* File                Gap.Ble.Api.h
* Description         Declares API Functions and Definitions For GapBle
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#define CLX_BLE_GAP_ADDRESS_VALUE_LENGTH                               6   /* Bytes */

#define CLX_BLE_AD_FIELD_HEADER_LENGTH                                 2   /* Bytes */

#define CLX_BLE_EXTENDED_ADVERTISING_DATA_MAX_SIZE                     ( 0xFF - CLX_BLE_AD_FIELD_HEADER_LENGTH )  /* 255 Bytes */

#define CLX_BLE_INVALID_CONNECTION_HANDLE                              0xFF00

/**
Service Data - 16-bit UUID. 
*/
#define CLX_BLE_GAP_AD_TYPE_16_BIT_SERVICE_DATA                        0x16

/**
Service Data - 32-bit UUID. 
*/
#define CLX_BLE_GAP_AD_TYPE_32_BIT_SERVICE_DATA                        0x20

/**
Service Data - 128-bit UUID. 
*/
#define CLX_BLE_GAP_AD_TYPE_128_BIT_SERVICE_DATA                       0x21


/**
LE Security Mode 1:
 - Level 1: No security (no authentication, no encryption)
 - Level 2: Unauthenticated pairing with encryption (no MITM protection)
 - Level 3: Authenticated pairing with encryption (MITM protection)

LE Security Mode 2:
 - Level 1: Unauthenticated pairing with data signing (MITM protection)
 - Level 2: Authenticated pairing with data signing (MITM protection)

 Mixed LE security modes requirements:
 If security mode 1 and mode 2 level 2 are required, security mode 1 level 3 is used
 If security mode 1 level 3 and mode 2 are required, security mode 1 level 3 is used
 If security mode 1 level 2 and mode 2 level 1 is required, mode 1 level 2 is used


 The security mode is defined by CLX_BLE_GAP_SECURITY_MODE 
 The security level is defined by CLX_BLE_GAP_SECURITY_LEVEL 
*/

#define CLX_BLE_GAP_SECURITY_MODE                                                       1

#define CLX_BLE_GAP_SECURITY_LEVEL                                                      1

/**
LE Privacy:
 Peripheral:
  Privacy features are set by CLX_BLE_GAP_PRIVACY_FLAG and CLX_BLE_GAP_RECCONECTION_ADDRESS

    CLX_BLE_GAP_PERIPHERAL_PRIVACY_FLAG :           1 - Privacy enabled
                                                    0 - Privacy Disabled
    CLX_BLE_GAP_PERPHERAL_RECCONECTION_ADDRESS:     1 - Use reconnection address
                                                    0 - Use resolvable address

    CLX_BLE_GAP_PERIPHERAL_PRIVACY_FLAG            CLX_BLE_GAP_PERPHERAL_RECCONECTION_ADDRESS         Privacy Support
    0                                               x                                                   None
    1                                               0                                                   Privacy only in undirected connectable mode
    1                                               1                                                   Privacy in directed connectable mode and undirected connectable mode                                                    
*/

#define CLX_BLE_GAP_PERIPHERAL_PRIVACY_FLAG                                                 1

#define CLX_BLE_GAP_PERPHERAL_RECCONECTION_ADDRESS                                          1

#define CLX_BLE_GAP_CENTRAL_PRIVACY_ENABLE                                                  1


#define CLX_BLE_AD_FLAG_LIMITED_DISCOVERABLE_MODE                                           0x01
#define CLX_BLE_AD_FLAG_GENERAL_DISCOVERABLE_MODE                                           0x02
#define CLX_BLE_AD_FLAG_BR_EDR_NOT_SUPPORTED                                                0x04
#define CLX_BLE_AD_FLAG_SIMULTANEOUS_LE_BR_EDR_CONTROLLER_SUPPORTED                         0x08
#define CLX_BLE_AD_FLAG_SIMULTANEOUS_LE_BR_EDR_HOST_SUPPORTED                               0x10


/**
Used Internally.
*/
#define CLX_GAP_BLE_CREATE_COMPLETE                                                         0x553F

/**
Refer to #clxGapBleManageWhiteList function.
*/
#define CLX_GAP_BLE_MANAGE_WHITE_LIST_COMPLETE                                              0x5500

/**
Refer to #clxGapBleGetConnectionParameters function.
*/
#define CLX_GAP_BLE_GET_CONNECTION_PARAMETERS_COMPLETE                                      0x5503

/**
Refer to #clxGapBleChangeConnectionParameter function.
*/
#define CLX_GAP_BLE_CHANGE_CONNECTION_PARAMETER_COMPLETE                                    0x5505

/**
Refer to #clxGapBleConnectionParameterChangeResponse function.
*/
#define CLX_GAP_BLE_CONNECTION_PARAMETER_CHANGE_RESPONSE_COMPLETE                           0x5508

/**
Refer to #clxBleSendTestCommand function.
*/
#define CLX_BLE_SEND_TEST_COMMAND                                                           0x5509


/**
This indication is received when the physical (ACL) link to a remote device has failed.
The parameter for this indication is of type #ClxGapBleLinkDisconnectionIndication.
*/
#define CLX_GAP_BLE_LINK_DISCONNECTION_INDICATION                                           0x9501

/**
This indication is received when the current encryption procedure has been complete. This indication
is received only if the encryption procedure has been initiated by the remote device.

The parameter for this indication is of type #ClxGapBleEncryptionCompletedIndication
*/
#define CLX_GAP_BLE_ENCRYPTION_COMPLETED_INDICATION                                         0x9503

/**
This indication is received when the controller updated the connection parameter.

The status indicates if the controller has successfully updated the connection parameters or failed.
The parameter of this indication is of type #ClxGapBleConnectionParameterUpdatedIndication.
*/
#define CLX_GAP_BLE_CONNECTION_PARAMETER_UPDATED_INDICATION                                 0x9504

/**
This indication is received when the controller changed the payload length or transmission time of a packet.
The parameter of this indication is of type #ClxGapBleDataLengthChangedIndication.

NOTE : This INDICATION requires Bluetooth V4.2 or later.
*/
#define CLX_GAP_BLE_DATA_LENGTH_CHANGED_INDICATION                                          0x9505

/**
This indication is received when the controller changed the transmitter PHY or receiver PHY or both.

The status indicates if the controller has successfully updated the PHY or failed.
The parameter of this indication is of type #ClxGapBlePhyUpdatedIndication.

NOTE : This INDICATION requires Bluetooth V5.0 or later.
*/
#define CLX_GAP_BLE_PHY_UPDATED_INDICATION                                                  0x9506

/**
This indication is received when the remote device requests to change the active connection parameters.
The parameter of this indication is of type #ClxGapBleConnectionParameterChangeRequestIndication.
*/
#define CLX_GAP_BLE_CONNECTION_PARAMETER_CHANGE_REQUEST_INDICATION                          0x9507


/**
Determines the address type of a remote BLE device.
*/
typedef enum ClxBleAddressTypeEnum
{
    ClxBleAddressType_Public           = 0x00,    /*!< The universally unique Bluetooth address of the device */
    ClxBleAddressType_Random           = 0x01,    /*!< A randomly generated address. A static, resolvable or non-resolvable address */
    ClxBleAddressType_PublicIdentity   = 0x02,    /*!< The universally unique Bluetooth address of the device, which has been resolved */
    ClxBleAddressType_StaticIdentity   = 0x03     /*!< A static (random) address which has been resolved as the unique identifier of the device */
} ClxBleAddressType;

/**
Determines the addressing mode of a local BLE device.
*/
typedef enum ClxBleOwnAddressModeEnum
{
    ClxBleOwnAddressMode_Identity                                      = 0x00,     /*!< The identity address of the local device will be used. 
                                                                                        If ClarinoxBlue has been configured to use a random static address, that address will 
                                                                                        be used. Otherwise, the Bluetooth address of the controller will be used. */
    ClxBleOwnAddressMode_PrivateResolvable                             = 0x01,     /*!< A random resolvable address will be generated and used (The parameter "Ble.Smp.IR" 
                                                                                        shall have been configured during the initialization of ClarinoxBlue). */
    ClxBleOwnAddressMode_PrivateNonResolvable                          = 0x02      /*!< A random non-resolvable address will be generated and used. */
} ClxBleOwnAddressMode;

/**
Determines the operations on a white list
*/
typedef enum ClxBleWhiteListOperationEnum
{
    ClxBleWhiteListOperation_Add      = 0x00,    /*!< Add a device into the white list */
    ClxBleWhiteListOperation_Remove   = 0x01,    /*!< Remove a device from the white list */
    ClxBleWhiteListOperation_Clear    = 0x02     /*!< Clear the current entries from the white list */
} ClxBleWhiteListOperation;

typedef u1 ClxBleExtendedAdvertisingHandle;

typedef u2 ClxBleConnectionHandle;

/**
Extended Advertising flags:
*/
typedef enum ClxBleExtendedAdvertisingFlagEnum
{
    ClxBleExtendedAdvertisingFlag_LegacyAdvertising                 = 0x10,     /*!< Use legacy advertising PDUs (The other flags will be ignored */
    ClxBleExtendedAdvertisingFlag_Anonymous                         = 0x20,     /*!< Omit advertiser's address from all PDUs (extended advertising mode only) */
    ClxBleExtendedAdvertisingFlag_InludeTxPower                     = 0x40      /*!< Include TxPower in the extended header of at least one advertising PDU */
} ClxBleExtendedAdvertisingFlag;

typedef enum ClxBleConnectionRoleEnum
{
    ClxBleConnectionRole_Master   = 0x00,    /*!< Master Role */
    ClxBleConnectionRole_Slave    = 0x01     /*!< Slave Role */
} ClxBleConnectionRole;

typedef enum ClxBlePhyPreferenceEnum
{
    ClxBlePhy_ControllerPreferredTx  = 0x01,            /*!< Controller preferred Tx PHY */
    ClxBlePhy_ControllerPreferredRx  = 0x02,            /*!< Controller preferred Rx PHY */
    ClxBlePhy_HostPreferredTx        = 0x04,            /*!< Host preferred Tx PHY */
    ClxBlePhy_HostPreferredRx        = 0x08             /*!< Host preferred Rx PHY */
} ClxBlePhyPreference;

typedef enum ClxBlePhyTypeEnum
{
    ClxBlePhyType_1M        = 0x01,             /*!< LE 1M PHY */
    ClxBlePhyType_2M        = 0x02,             /*!< LE 2M PHY */
    ClxBlePhyType_Coded     = 0x03              /*!< LE Coded PHY */
} ClxBlePhyType;


typedef enum ClxBleLECodedPhyEnum
{
    ClxBleLECodedPhy_NoPreference,              /*!< LE coded PHY with no preference */
    ClxBleLECodedPhy_SymbolRate_2,              /*!< LE coded PHY with 2 symbols */
    ClxBleLECodedPhy_SymbolRate_8               /*!< LE coded PHY with 8 symbols */
} ClxBleLECodedPhy;

typedef enum ClxBleParameterChangeFilterEnum
{
    ClxBleParameterChangeFilter_ConnectionUpdate    = 0x01,     /*!< Filter to enable connection parameter update. It requires the valid values for minimum/maximum connection interval,
                                                                     connection latency, supervision timeout and minimum/maximum connection event length of the API #clxGapBleChangeConnectionParameter */
    ClxBleParameterChangeFilter_DataLengthChange    = 0x02,     /*!< Filter to enable data length extension. It requires Bluetooth V4.2 or later. Also, needs the valid values for
                                                                     single packet length and single packet transmit time of the API #clxGapBleChangeConnectionParameter */
    ClxBleParameterChangeFilter_PhyUpdate           = 0x04      /*!< Filter to enable PHY update. It requires Bluetooth V5.0 or later. Also, needs the valid values for PHY force apply,
                                                                     Tx PHY, Rx PHY and LE coded options of the API #clxGapBleChangeConnectionParameter */
} ClxBleParameterChangeFilter;

typedef enum ClxBleTestCommandEnum
{
    ClxBleCommand_ReceiverTest,                                 /*!< Filter to send receiver test command */
    ClxBleCommand_TransmitterTest,                              /*!< Filter to send transmitter test command */
    ClxBleCommand_EndTest                                       /*!< Filter to send the test end command */
} ClxBleTestCommand;

/* BLE Audio roles */
typedef enum ClxBleAudioRoleEnum
{
    ClxBleAudioRole_CallGateway                     = 0x01,     /*!< Call Gateway (CG) */
    ClxBleAudioRole_CallTerminal                    = 0x02,     /*!< Call Terminal (CT) */
    ClxBleAudioRole_UnicastMediaSender              = 0x04,     /*!< Unicast Media Sender (UMS) */
    ClxBleAudioRole_UnicastMediaReceiver            = 0x08,     /*!< Unicast Media Receiver (UMR) */
    ClxBleAudioRole_BroadcastMediaSender            = 0x10,     /*!< Broadcast Media Sender (BMS) */
    ClxBleAudioRole_BroadcastMediaReceiver          = 0x20      /*!< Broadcast Media Receiver (BMR) */
    /* Others RFU */
} ClxBleAudioRole;


/**
Specifies the type of periodic advertiser address
*/
typedef enum ClxBleAdvertiserAddressTypeEnum
{
    ClxBleAdvertiserAddressType_Public = 0x00,    /*!< The universally unique Bluetooth address of the device */
    ClxBleAdvertiserAddressType_Random = 0x01     /*!< A randomly generated address. A static, resolvable or non-resolvable address */
} ClxBleAdvertiserAddressType;


/**
Specifies the completeness of the received periodic advertising data
*/
typedef enum ClxBlePeriodicAdvertisingDataStatusEnum
{
    ClxBlePeriodicAdvertisingDataStatus_Complete  = 0x00,    /*!< All data completely received */
    ClxBlePeriodicAdvertisingDataStatus_Continue  = 0x01,    /*!< Incomplete data received. More to come */
    ClxBlePeriodicAdvertisingDataStatus_Truncated = 0x02     /*!< Incomplete data received. Truncated */
} ClxBlePeriodicAdvertisingDataStatus;

typedef struct ClxBlePhyTypeFlagBitsStruct
{
    boolean phy_1M:1;
    boolean phy_2M:1;
    boolean phy_Coded:1;
} ClxBlePhyTypeFlagBits;

/**
Determines the type of the received advertising PDU in an extended advertising report.
This structure defines both legacy and non-legacy (extended) advertising PDUs. A separate flag bit determines if the received advertising PDU has been of legacy
or a non-legacy variety. Refer to the documentation of #ClxGapBleDeviceExtendedAdvertisingIndication for more information.

In case of a legacy PDU, the following list provides the mapping between #ClxBleAdvertisingType and #ClxBleExtendedAdvertisingReportTypeFlags :

- #ClxBleAdvertisingType_ConnectableUndirected       :   connectable and scannable are set
- #ClxBleAdvertisingType_ConnectableDirected         :   connectable and directed are set
- #ClxBleAdvertisingType_ScannableUndirected         :   scannable is set
- #ClxBleAdvertisingType_NonConnectableUndirected    :   All fields are reset
- #ClxBleAdvertisingType_ScanResponse                :   scanResponse and scannable are set, connectable could be either set or reset
*/
typedef struct ClxBleExtendedAdvertisingReportTypeFlagsStruct
{
    boolean connectable:1;
    boolean scannable:1;
    boolean directed:1;
    boolean scanResponse:1;
} ClxBleExtendedAdvertisingReportTypeFlags;

typedef struct ClxBleBdAddressStruct
{
    u1                 value[6];       /*!< The universally unique Bluetooth address of the device */
    ClxBleAddressType  addressType;
} ClxBleBdAddress;

typedef struct ClxConfigBleBdAddressStruct
{
    ClxConfigParam   paramInfo;    /*!< Not to be modified manually. Call #clxConfigInitBleBdAddressParam instead. */
    ClxBleBdAddress  addr;         /*!< The value of this configuration parameter, as an object of type #ClxBleBdAddress */
} ClxConfigBleBdAddress;

CLX_DEFINE_CONFIG_TYPE(ClxConfigBleBdAddress);

typedef struct ClxBleDeviceDetailAndNumericValueStruct
{
    ClxBleBdAddress  deviceAddr;
    u4               value;
} ClxBleDeviceDetailAndNumericValue;

/**
Data Structure for the indication #CLX_GAP_BLE_LINK_DISCONNECTION_INDICATION
*/
typedef struct ClxGapBleLinkDisconnectionIndicationStruct
{
    ClxBleConnectionHandle  connectionHandle;    /*!< The handle of the connection to the remote device */
    ClxResult               reason;
} ClxGapBleLinkDisconnectionIndication;


/**
Data Structure for the indication #CLX_GAP_BLE_ENCRYPTION_COMPLETED_INDICATION
*/
typedef struct ClxGapBleEncryptionCompletedIndicationStruct
{
    ClxBleConnectionHandle  connectionHandle;
    ClxError                reason;
} ClxGapBleEncryptionCompletedIndication;


/**
Data Structure for the indication #CLX_GAP_BLE_CONNECTION_PARAMETER_UPDATED_INDICATION
*/
typedef struct ClxGapBleConnectionParameterUpdatedIndicationStruct
{
    u1  status;                                                      /*!< 0x00 if connection parameter update is successful otherwise the error code indicates the reason */
    u2  connectionHandle;                                            /*!< The connection handle */
    u2  connectionInterval;                                          /*!< The connection interval */
    u2  connectionLatency;                                           /*!< The connection latency */
    u2  supervisionTimeout;                                          /*!< The connection supervision timeout */
} ClxGapBleConnectionParameterUpdatedIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_DATA_LENGTH_CHANGED_INDICATION
*/
typedef struct ClxGapBleDataLengthChangedIndicationStruct
{
    u2  connectionHandle;                                            /*!< The connection handle */
    u2  txPacketLength;                                              /*!< Tx packet length */
    u2  txTransmitTime;                                              /*!< Tx packet transmission time */
    u2  rxPacketLength;                                              /*!< Rx packet length */
    u2  rxReceiveTime;                                               /*!< Rx packet receiving time */
} ClxGapBleDataLengthChangedIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_PHY_UPDATED_INDICATION
*/
typedef struct ClxGapBlePhyUpdatedIndicationStruct
{
    u1  status;                                                      /*!< 0x00 if PHY update is successful otherwise the error code indicates the reason */
    u2  connectionHandle;                                            /*!< The connection handle */
    u1  txPhy;                                                       /*!< Transmitter PHY */
    u1  rxPhy;                                                       /*!< Receiver PHY */
} ClxGapBlePhyUpdatedIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_CONNECTION_PARAMETER_CHANGE_REQUEST_INDICATION
*/
typedef struct ClxGapBleConnectionParameterChangeRequestIndicationStruct
{
    u2 connectionHandle;                                             /*!< The connection handle */
    u2 minimumInterval;                                              /*!< Minimum connection interval */
    u2 maximumInterval;                                              /*!< Maximum connection interval */
    u2 latency;                                                      /*!< Connection latency */
    u2 supervisionTimeout;                                           /*!< Supervision timeout */
} ClxGapBleConnectionParameterChangeRequestIndication;


/**
Data Structure for the indication #CLX_GAP_BLE_GET_CONNECTION_PARAMETERS_COMPLETE
*/
typedef struct ClxGapBleGetConnectionParametersCompleteStruct
{
    _user_out_ ClxConfigList* parameters;    /*!< Parameters associated with the given connection handle. */
} ClxGapBleGetConnectionParametersComplete;

/**
Data Structure for the indication #CLX_BLE_SEND_TEST_COMMAND
*/
typedef struct ClxBleSendTestCommandCompleteStruct
{
    _user_out_ u2* packetCount;    /*!< Application allocated buffer to store the number of received packets count */
} ClxBleSendTestCommandComplete;


/**
Initializes the memory to retrieve the current established connection details like the physical address of
local device, physical address of remote device and identity address of remote device.

\param[  out  ] object      User buffer to retrieve the address
\param[  in   ] paramName   The name of the parameter like "LocalCurrentAddress", "RemoteCurrentAddress" and "RemoteIdentityAddress"
\param[  in   ] paramValue  Assigning the value of given parameters
\param[  in   ] parentList  The parent configuration list
*/
void clxConfigInitBleBdAddressParam(ClxConfigBleBdAddress*  object,
                                    const s1*               paramName,
                                    const ClxBleBdAddress*  paramValue,
                                    ClxConfigList*          parentList);

/**
Manage white list supports the below operations.

    Add     - Adding a remote device to white list by giving input address
    Delete  - Removing a single entry from white list by giving input address
    Clear   - Removing all white list entries

This API should be called after #clxGapBleConnectToPeripheral in Central role and after getting the connection establishment indication
#CLX_GAP_BLE_CONNECTION_ESTABLISHED_BY_REMOTE_CENTRAL_INDICATION in Peripheral role.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_MANAGE_WHITE_LIST_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack       Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] operation   Type of the white list operation.
\param[  in   ] deviceAddr  Device that needs to be added or deleted to the white list. Please ignore this parameter when using the white list clear operation.
\param[  in   ] block       Type of the operation. 
                            - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                            - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_COMMAND_PARAMETER: If deviceAddr parameter is NULL.(Applicable only for operation value ClxBleWhiteListOperation_Add and ClxBleWhiteListOperation_Remove).
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.

\remarks
Please find the usage of white list with respect to BLE roles

Central     - If the local device adds the remote device as white list, then during white list scanning it allows only white listed device's
              advertising packets and rejects  all other packets.
Peripheral  - If the local device adds the remote device as white list, then the peripheral device can send the advertising packets to a specified
              device based on the filtering policies through the API #clxGapBleStartAdvertising.
*/
ClxResult clxGapBleManageWhiteList(_in_ ClxStack                     stack,
                                   _in_ ClxBleWhiteListOperation     operation,
                                   _user_in_ const ClxBleBdAddress*  deviceAddr,
                                   _in_ boolean                      block);


/**
API returns the connection parameters associated with the given connection handle.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_GET_CONNECTION_PARAMETERS_COMPLETE.
                   The parameter of this indication is of type #ClxGapBleGetConnectionParametersComplete.

\param[  in   ] stack             Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle  The handle of the established physical connection.
\param[  out  ] parameters        Parameters associated with the given connection handle.
\param[  in   ] block             Type of the operation. 
                                    - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_CONNECTION_NOT_EXIST: There is no active Bluetooth LowEnergy connection to the remote device.
*/
ClxResult clxGapBleGetConnectionParameters(_in_ ClxStack                stack,
                                           _in_ ClxBleConnectionHandle  connectionHandle,
                                           _user_out_ ClxConfigList*    parameters,
                                           _in_ boolean                 block);
/**
This API is used to update the connection parameter, tx/rx PHY and extending the packet length.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_CHANGE_CONNECTION_PARAMETER_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle                The handle of the established physical connection.
\param[  in   ] filter                          Filter to enable connection update, data length extension and set phy of type #ClxBleParameterChangeFilter. 
                                                 enum values are a bitfield and can be ORed.
\param[  in   ] minimumConnectionInterval       Minimum interval value for the connection. The value range starts from 0x0006 to 0x0c80.
\param[  in   ] maximumConnectionInterval       Maximum interval value for the connection. The value range starts from 0x0006 to 0x0c80. The maximum connection interval value should not be less than minimal value.
\param[  in   ] connectionLatency               Value to define the slave latency for the connection. The value range starts from 0x0000 to 0x01F3.
\param[  in   ] supervisionTimeout              Value to define the link supervision timeout for the connection (multiples of 10 milliseconds). The value range starts from 0x000a to 0x0c80.
\param[  in   ] minimumConnectionEventLength    Minimum length of connection event. The value range starts from 0x0000 to 0xffff.
\param[  in   ] maximumConnectionEventLength    Maximum length of connection event. The value range starts from 0x0000 to 0xffff. This value should not be less than minimum connection event length.
\param[  in   ] singlePacketLength              Data packet length. The minimum length is 27(0x001B) bytes and the maximum length is 251(0x00FB) bytes.
\param[  in   ] singlePacketTransmitTime        Time to transmit the single packet. The value range starts from 0x0148 to 0x4290.
\param[  in   ] phyPreference                   PHY preference of type #ClxBlePhyPreference.
\param[  in   ] txPhy                           Transmitter PHY of type #ClxBlePhyType.
\param[  in   ] rxPhy                           Receiver PHY of type #ClxBlePhyType.
\param[  in   ] leCodedOptions                  LE coded PHY options of type #ClxBleLECodedPhy.
\param[  in   ] block                           Type of the operation. 
                                                    - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

NOTE:
- The parameters \a minimumConnectionInterval \a maximumConnectionInterval \a connectionLatency \a supervisionTimeout \a minimumConnectionEventLength and \a maximumConnectionEventLength are applicable to the parameter \a filter sets as #ClxBleParameterChangeFilter_ConnectionUpdate.

- The parameters \a singlePacketLength and \a singlePacketTransmitTime are applicable to the parameter \a filter sets as #ClxBleParameterChangeFilter_DataLengthChange.

- The parameters \a phyPreference \a txPhy \a rxPhy and \a leCodedOptions are applicable to the parameter \a filter sets as #ClxBleParameterChangeFilter_PhyUpdate.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_COMMAND_NOT_SUPPORTED: When Bluetooth library does not support to V5.0 or later
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleChangeConnectionParameter(_in_ ClxStack              stack,
                                             _in_ u2                    connectionHandle,
                                             _in_ u1                    filter,
                                             _in_ u2                    minimumConnectionInterval,
                                             _in_ u2                    maximumConnectionInterval,
                                             _in_ u2                    connectionLatency,
                                             _in_ u2                    supervisionTimeout,
                                             _in_ u2                    minimumConnectionEventLength,
                                             _in_ u2                    maximumConnectionEventLength,
                                             _in_ u2                    singlePacketLength,
                                             _in_ u2                    singlePacketTransmitTime,
                                             _in_ u1                    phyPreference,
                                             _in_ ClxBlePhyType         txPhy,
                                             _in_ ClxBlePhyType         rxPhy,
                                             _in_ ClxBleLECodedPhy      leCodedOptions,
                                             _in_ boolean               block);

/**
This API is used to response the remote device's connection parameter change request. Please note that this API shall be called after receiving
the indication #CLX_GAP_BLE_CONNECTION_PARAMETER_CHANGE_REQUEST_INDICATION.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_CONNECTION_PARAMETER_CHANGE_RESPONSE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle                The handle of the established physical connection.
\param[  in   ] accept                          Flag to accept or reject the request.
\param[  in   ] minimumConnectionInterval       Agreed minimum connection interval value with remote device. The value range starts from 0x0006 to 0x0c80.
\param[  in   ] maximumConnectionInterval       Agreed maximum connection interval value with remote device. The value range starts from 0x0006 to 0x0c80. The maximum connection interval value should not be less than minimal value.
\param[  in   ] connectionLatency               Agreed connection latency value with remote device.The value range starts from 0x0000 to 0x01F3.
\param[  in   ] supervisionTimeout              Agreed link supervision timeout value with remote device. The value range starts from 0x000a to 0x0c80.
\param[  in   ] minimumConnectionEventLength    Minimum length of connection event. The value range starts from 0x0000 to 0xffff.
\param[  in   ] maximumConnectionEventLength    Maximum length of connection event. The value range starts from 0x0000 to 0xffff. This value should not be less than minimum connection event length.
\param[  in   ] block                           Type of the operation. 
                                                    - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleConnectionParameterChangeResponse(_in_ ClxStack  stack,
                                                     _in_ u2        connectionHandle,
                                                     _in_ boolean   accept,
                                                     _in_ u2        minimumConnectionInterval,
                                                     _in_ u2        maximumConnectionInterval,
                                                     _in_ u2        connectionLatency,
                                                     _in_ u2        supervisionTimeout,
                                                     _in_ u2        minimumConnectionEventLength,
                                                     _in_ u2        maximumConnectionEventLength,
                                                     _in_ boolean   block);


/**
Allows the local device controller to send the BLE test commands.

NOTE: If any test command is executed either #ClxBleCommand_ReceiverTest or #ClxBleCommand_TransmitterTest then the end test command #ClxBleCommand_EndTest must be executed.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_BLE_SEND_TEST_COMMAND.
                   This indication does not have any parameters.

\param[  in   ] stack           Local device stack handle. A stack object must be created before the API used.
\param[  in   ] command         Filter to send the test command of type #ClxBleTestCommand.
\param[  in   ] TxRxChannel     Tx/Rx channel frequency. The value range starts from 0x00 to 0x027.
\param[  in   ] txDataLength    Tx test data length. This parameter is only applicable to #ClxBleCommand_TransmitterTest. The value range starts from 0x00 to 0xFF.
\param[  in   ] txPayloadType   Tx packet payload transmission order. This parameter is only applicable to #ClxBleCommand_TransmitterTest. The packet payload transmission type range starts from 0x00 to 0x07.
\param[  out  ] packetCount     Number of packets received. This parameter is only applicable to #ClxBleCommand_EndTest. The packets count should be 0x0000 for #ClxBleCommand_TransmitterTest.
\param[  in   ] block           Type of the operation. 
                                    - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_COMMAND_PARAMETER: One or more of provided parameters are invalid.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxBleSendTestCommand(_in_ ClxStack           stack,
                                _in_ ClxBleTestCommand  command,
                                _in_ u1                 TxRxChannel,
                                _in_ u1                 txDataLength,
                                _in_ u1                 txPayloadType,
                                _user_out_ u2*          packetCount,
                                _in_ boolean            block);

/**
Finds the remote device's audio role.

This API shall be supported from the core spec version 5.3 or ClarinoxBlue version 13.0.0

\param[  in   ] payload         Extended advertising data 
\param[  in   ] payloadLength   Length of the extended advertising data
\param[  out  ] role            Retrieves the audio role of type #ClxBleAudioRole supported by remote devcie

\return         #CLX_SUCCESS    if the audio role is available in the extended advertising data
                #CLX_ERROR      when the audio role is not available
*/
ClxResult clxGapBleFindAudioRole(_user_in_  const u1*  payload,
                                 _in_       const u1   payloadLength,
                                 _user_out_ u2*        role);


#include "Gap.Ble.4.2.Api.h"

#ifdef __cplusplus
}
#endif

#endif  // __Gap_Ble_Api_h__
