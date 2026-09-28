#ifndef __GAP_BLE_PERIPHERAL_API_h__
#define __GAP_BLE_PERIPHERAL_API_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gap.Ble.Peripheral.Api.h
* Description         Declares API Functions and Definitions For Gap Ble Peripheral
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#define CLX_BLE_ADVERTISING_DATA_MAX_SIZE                                                   31  /* Bytes */

#define CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE                                         0xF0


#define CLX_BLE_ADVERTISING_CHANNEL_37                                                      0x01
#define CLX_BLE_ADVERTISING_CHANNEL_38                                                      0x02
#define CLX_BLE_ADVERTISING_CHANNEL_39                                                      0x04
#define CLX_BLE_ALL_ADVERTISING_CHANNELS                                                    (CLX_BLE_ADVERTISING_CHANNEL_37 | CLX_BLE_ADVERTISING_CHANNEL_38 | CLX_BLE_ADVERTISING_CHANNEL_39)

#define CLX_BLE_INVALID_ADVERTISING_SID_VALUE                                               0xFF
#define CLX_BLE_INVALID_ADVERTISING_TX_POWER_VALUE                                          0x7F
#define CLX_BLE_INVALID_ADVERTISING_RSSI_VALUE                                              0x7F

/**
Refer to #clxGapBleSetScanResponseData function.
*/
#define CLX_GAP_BLE_SET_SCAN_RESPONSE_DATA_COMPLETE                                         0x7000

/**
Refer to #clxGapBleSetExtendedAdvertisingParameters function.
*/
#define CLX_GAP_BLE_SET_EXTENDED_ADVERTISING_PARAMETERS_COMPLETE                            0x7001

/**
Refer to #clxGapBleSetExtendedAdvertisingData function.
*/
#define CLX_GAP_BLE_SET_EXTENDED_ADVERTISING_DATA_COMPLETE                                  0x7002

/**
Refer to #clxGapBleEnableDisableExtendedAdvertising function.
*/
#define CLX_GAP_BLE_ENABLE_DISABLE_EXTENDED_ADVERTISING_COMPLETE                            0x7003

/**
Refer to #clxGapBleEnablePeriodicAdvertisingMode function.
*/
#define CLX_GAP_BLE_ENABLE_PERIODIC_ADVERTISING_MODE_COMPLETE                               0x7004

/**
Refer to #clxGapBleDisablePeriodicAdvertisingMode.
*/
#define CLX_GAP_BLE_DISABLE_PERIODIC_ADVERTISING_MODE_COMPLETE                              0x7005

/**
refer to #clxGapBleGetExtendedAdvertisingCapabilities function.
*/
#define CLX_GAP_BLE_GET_EXTENDED_ADVERTISING_CAPABILITIES_COMPLETE                          0x7006

/**
Refer to #clxGapBleRemoveExtendedAdvertisingSet function.
*/
#define CLX_GAP_BLE_REMOVE_EXTENDED_ADVERTISING_SET_COMPLETE                                0x7007

/**
Refer to #clxGapBleClearExtendedAdvertisingSets function.
*/
#define CLX_GAP_BLE_CLEAR_EXTENDED_ADVERTISING_SETS_COMPLETE                                0x7008

/**
Refer to #clxGapBlePollAdvertisingReport function.
*/
#define CLX_GAP_BLE_POLL_ADVERTISING_REPORT_COMPLETE                                        0x7009


/**
This indication may be received if a scan request is received for an ongoing extended advertising session.
The parameter for this indication is of type #ClxGapBleScanRequestReceivedIndication.
*/
#define CLX_GAP_BLE_SCAN_REQUEST_RECEIVED_INDICATION                                        0xb000

/**
This event shall be generated when a scanner/synchronizer device requests PAwR subevent data (a Response Slot) during a Periodic Advertising with Responses (PAwR) train.
The parameter of this indication is of type #ClxGapBlePeriodicAdvertisingSubEventDataRequestIndication.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_INDICATION                   0xb001

/**
This indication is received during extended scanning procedure (refer to #clxGapBleEnablePeriodicAdvertisingMode), which indicates
a device has been discovered in the vicinity.

NOTE : This INDICATION requires Bluetooth V5.0 or later.

The parameter for this indication is of type #ClxGapBleDeviceExtendedAdvertisingIndication.
*/
#define CLX_GAP_BLE_DEVICE_EXTENDED_ADVERTISING_INDICATION                                  0xb002

/* Phy options when transmitting LE Coded PHY */
typedef enum ClxBlePhyOptionsEnum
{
    ClxBlePhyOptions_NoPreference   = 0x00,     /*!< The Host has no preferred or required coding when transmitting on the LE Coded PHY */
    ClxBlePhyOptions_HostPrefersS2  = 0x01,     /*!< The Host prefers that S=2 coding be used when transmitting on the LE Coded PHY */
    ClxBlePhyOptions_HostPrefersS8  = 0x02,     /*!< The Host prefers that S=8 coding be used when transmitting on the LE Coded PHY */
    ClxBlePhyOptions_HostRequiresS2 = 0x03,     /*!< The Host requires that S=2 coding be used when transmitting on the LE Coded PHY */
    ClxBlePhyOptions_HostRequiresS8 = 0x04      /*!< The Host requires that S=8 coding be used when transmitting on the LE Coded PHY */
} ClxBlePhyOptions;

/**
Periodic Advertising flags:
*/
typedef enum ClxBlePeriodicAdvertisingFlagEnum
{
    ClxBlePeriodicAdvertisingFlagInludeTxPower = 0x40      /*!< Include TxPower in the advertising PDU */
} ClxBlePeriodicAdvertisingFlag;

/**
Determines the advertising type (applicable to connection only)
*/
typedef enum ClxBleAdvertisingTypeEnum
{
    ClxBleAdvertisingType_ConnectableUndirected            = 0x00,     /*!< connectable by anyone */
    ClxBleAdvertisingType_ConnectableDirected              = 0x01,     /*!< connectable by directed address (high duty cycle)  */
    ClxBleAdvertisingType_ScannableUndirected              = 0x02,     /*!< scannable by anyone */
    ClxBleAdvertisingType_NonConnectableUndirected         = 0x03,     /*!< non-connectable */
    ClxBleAdvertisingType_ConnectableDirected_LowDutyCycle = 0x04,     /*!< connectable by directed address (low duty cycle). Available in Bluetooth 4.1 and above */

    ClxBleAdvertisingType_ScanResponse                     = 0x10      /*!< Scan Response (Only in CLX_GAP_BLE_DEVICE_ADVERTISING_INDICATION indication) */
} ClxBleAdvertisingType;

/**
Determines the operations of advertising filter (applicable to discovery only)
*/
typedef enum ClxBleAdvertisingFilterPolicyEnum
{
    ClxBleAdvertisingFilterPolicy_ScanConnectionAnyone             = 0x00,    /*!< Scan and advertise connectable by anyone */
    ClxBleAdvertisingFilterPolicy_ScanWhitelistConnectionAnyone    = 0x01,    /*!< Scan by whitelist devices, advertise connectable by anyone */
    ClxBleAdvertisingFilterPolicy_ScanAnyoneConnectionWhitelist    = 0x02,    /*!< Scan by anyone, connectable to only whitelist devices */
    ClxBleAdvertisingFilterPolicy_ScanWhitelistConnectionWhitelist = 0x03     /*!< Scan by whitelist devices and connectable by whitelist devices only */
} ClxBleAdvertisingFilterPolicy;

typedef enum ClxBleAdvertisingDataTypeEnum
{
    ClxBleAdvertisingDataType_Advertising         = 0x00,       /*!< Advertising data */
    ClxBleAdvertisingDataType_ScanResponse        = 0x01,       /*!< Scan response data */
    ClxBleAdvertisingDataType_PeriodicAdvertising = 0x02        /*!< Periodic advertising data */
} ClxBleAdvertisingDataType;

/**
Extended advertising fragmentation preference as passed to #clxGapBleSetExtendedAdvertisingData.
*/
typedef enum ClxBleAdvertisingFragmentPreferenceEnum
{
    ClxBleAdvertisingFragmentPreference_Fragment      = 0x00,      /*!< The Controller may fragment all Host advertising data */
    ClxBleAdvertisingFragmentPreference_DoNotFragment = 0x01       /*!< The Controller should not fragment or should minimize fragmentation of Host advertising data */
} ClxBleAdvertisingFragmentPreference;


typedef enum ClxBleExtendedAdvertisingDataStatusEnum
{
    ClxBleExtendedAdvertisingDataStatus_Complete   = 0x00,          /*!< Data is complete */
    ClxBleExtendedAdvertisingDataStatus_Incomplete = 0x01,          /*!< Data is incomplete, more data to come */
    ClxBleExtendedAdvertisingDataStatus_Truncated  = 0x02           /*!< Data is truncated, NO more data to come */
} ClxBleExtendedAdvertisingDataStatus;

/**
Data Structure for the indication #CLX_GAP_BLE_GET_EXTENDED_ADVERTISING_CAPABILITIES_COMPLETE
*/
typedef struct ClxGapBleGetExtendedAdvertisingCapabilitiesCompleteStruct
{
    _user_out_ u2* maxDataLengthPerAdvertisingSet;          /*!< Upon successful completion of the command, contains the maximum length of data which can be set for a ordinary extended advertising, periodic advertising, or scan response associated to an
                                                                                                    extended advertising set. The Bluetooth controller may need to fragment the data into two or more packets. */
    _user_out_ u1* maxNumberOfSupportedAdvertisingSets;     /*!< Upon successful completion of the command, contains the maximum number of advertising sets supported by the Bluetooth controller.
                                                                                                    Actual number of extended advertising set that can be used at the same time is also limited by the amount of memory and resources available to the Bluetooth controller at any time,
                                                                                                    and may be less than this value. */
} ClxGapBleGetExtendedAdvertisingCapabilitiesComplete;

typedef struct ClxBleAdvertisingDataStruct
{
    u1  data[CLX_BLE_ADVERTISING_DATA_MAX_SIZE];
    u1  dataLength;                                 /*!< Maximum value shall be CLX_BLE_ADVERTISING_DATA_MAX_SIZE Bytes.
                                                         Shall be set to 0 if no advertising data or scan response data is required. */
} ClxBleAdvertisingData;

/**
Determines the type of the advertising PDUs to be used for an extended advertising set.
This structure defines both legacy and non-legacy (extended) advertising PDUs. A separate flag bit determines if the received advertising PDU has been of legacy
or a non-legacy variety. Refer to the documentation of #clxGapBleSetExtendedAdvertisingParameters for more information.

In case of a non-legacy (extended) PDUs, the following restrictions apply:

- connectable and scannable MUST NOT be set simultaneously.
- highDuty MUST NOT be set (High Duty Cycle PDUs are not used with extended advertising).

In case of using legacy PDUs, the following list provides the mapping between #ClxBleAdvertisingType and #ClxBleExtendedAdvertisingSetTypeFlags :

- #ClxBleAdvertisingType_ConnectableUndirected                  :   connectable and scannable are set
- #ClxBleAdvertisingType_ConnectableDirected                    :   connectable, highDuty, and directed are set
- #ClxBleAdvertisingType_ScannableUndirected                    :   scannable is set
- #ClxBleAdvertisingType_NonConnectableUndirected               :   All fields are reset
- #ClxBleAdvertisingType_ConnectableDirected_LowDutyCycle       :   connectable and directed are set
*/
typedef struct ClxBleExtendedAdvertisingSetTypeFlagsStruct
{
    boolean connectable : 1;
    boolean scannable   : 1;
    boolean directed    : 1;
    boolean highDuty    : 1;
} ClxBleExtendedAdvertisingSetTypeFlags;

typedef struct ClxBleAdvertisingSetInfoStruct
{
    ClxBleExtendedAdvertisingHandle     handle;
    u2                                  duration;
    u1                                  maxAdvertisingEvents;
} ClxBleAdvertisingSetInfo;


/**
Data Structure for the indication #CLX_GAP_BLE_READ_PERIODIC_ADVERTISER_LIST_SIZE_COMPLETE
*/
typedef struct ClxGapBleReadPeriodicAdvertiserListSizeCompleteStruct
{
    _user_out_ u1* advertiserListSize;    /*!< Maximum size of the controller's Periodic Advertiser List. */
} ClxGapBleReadPeriodicAdvertiserListSizeComplete;

/**
Data Structure for the indication #CLX_GAP_BLE_SET_EXTENDED_ADVERTISING_PARAMETERS_COMPLETE
*/
typedef struct ClxGapBleSetExtendedAdvertisingParametersCompleteStruct
{
    _user_out_ ClxBleExtendedAdvertisingHandle* advertisingHandle;  /*!< Upon a successful completion of this command, this argument will contain the handle to the created extended advertising set. If the command has been used
                                                                             to update an existing advertising set, this argument will be the same as existingAdvertisingHandle. This argument may be NULL. */
    _user_out_ s1*                              selectedTxPower;    /*!< Upon a successful completion of this command, this argument will contain the TX power selected by the Bluetooth controller to send advertising packets for this set. */
} ClxGapBleSetExtendedAdvertisingParametersComplete;

/* Data Structure for the indication #CLX_GAP_BLE_SCAN_REQUEST_RECEIVED_INDICATION */
typedef struct ClxGapBleScanRequestReceivedIndicationStruct
{
    ClxBleExtendedAdvertisingHandle     handle;
    ClxBleBdAddress                     scannerAddress;
} ClxGapBleScanRequestReceivedIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_INDICATION
*/
typedef struct ClxGapBlePeriodicAdvertisingSubEventDataRequestIndicationStruct
{
    u1          advertisingHandle;                                   /*!< Handle to indentify periodic advertising train */
    u1          subEventStart;                                       /*!< First sub event that data is requested */
    u1          subEventDataCount;                                   /*!< The number fo subevents that data is requested */
} ClxGapBlePeriodicAdvertisingSubEventDataRequestIndication;

/**
Data structure for extended advertising indications (BLuetooth 5.0 or later).
*/
typedef struct ClxBleExtendedAdvertisingDataStruct
{
    u1*                                     data;               /*!< Dynamically allocated by ClarinoxBlue stack. It will be valid only inside the indication call-back function. Deleted as soon as the indication call-back function returns */
    u1                                      actualDataLength;   /*!< Actual length of the Dynamically allocated data */
    u1                                      dataLength;         /*!< Length of the data */
    ClxBleExtendedAdvertisingDataStatus     dataStatus;         /*!< Status of the data */
} ClxBleExtendedAdvertisingData;


/**
Data Structure for the indication #CLX_GAP_BLE_DEVICE_EXTENDED_ADVERTISING_INDICATION
*/
typedef struct ClxGapBleDeviceExtendedAdvertisingIndicationStruct
{
    u4                                          flags;                                  /*!< Flag bits providing more information about this structure, as an OR-ed combination of values defined in #ClxBleExtendedAdvertisingFlag. */
    ClxBleExtendedAdvertisingReportTypeFlags    advertisingType;                        /*!< The type of the advertising PDU received. This value is relevant for both legacy and non-legacy PDUs.
                                                                                             This specifies a legacy PDU if the bit #ClxBleExtendedAdvertisingFlag_LegacyAdvertising is set in #flags.
                                                                                             Refer to the documentation of #ClxBleExtendedAdvertisingReportTypeFlags for more information */
    ClxBleBdAddress                             remoteAddr;                             /*!< The address of the advertiser. This is a valid address only if the flag bit #ClxBleExtendedAdvertisingFlag_Anonymous has NOT been set in the member #flags */
    ClxBleBdAddress                             directAddr;                             /*!< The address of the target device when the advertising is of a directed type (e.g. when the bit ClxBleExtendedAdvertisingReportTypeFlags.directed is set in the member #advertisingType),
                                                                                             Otherwise, this value must be ignored */
    ClxBlePhyType                               primaryPHY;                             /*!< The PHY used to receive this advertising packet on primary advertising channels */
    ClxBlePhyType                               secondaryPHY;                           /*!< The PHY used to receive this advertising packet on secondary advertising channels */
    u1                                          advertisingSID;                         /*!< The SID value (advertising Set ID) of the advertising packet. A value of CLX_BLE_INVALID_ADVERTISING_SID_VALUE indicates that the packet does not include the SID value */
    s1                                          txPower;                                /*!< The TX power used by the advertiser to send this packet. A value of CLX_BLE_INVALID_ADVERTISING_TX_POWER_VALUE indicates that the packet does not include the TX Power value */
    s1                                          rssi;                                   /*!< The RSSI of the received packet. A value of CLX_BLE_INVALID_ADVERTISING_RSSI_VALUE indicates that RSSI is not available for this packet */
    u2                                          periodicAdvertisingInterval;            /*!< Periodic advertising interval, in units of 1.25 ms. It ranges from 0x0006 (7.5 ms) to 0xFFFF (81,918 s). A value of 0 indicates that the packet does not belong to a periodic advertising set */
    ClxBleExtendedAdvertisingData               advertisingData;                        /*!< Advertising data */
} ClxGapBleDeviceExtendedAdvertisingIndication;


/**
Initializes the memory to advertise the local device's custom data like UUID, device name, device class, device id and etc.

\param[  out  ] obj  user buffer for advertising the local device's custom data
*/
void clxBleInitAdvertisingData(_user_out_ ClxBleAdvertisingData* obj);

/**
The size of advertisement packet has 31 data bytes available to use. If the Peripheral device wants to advertise more than 31 bytes the it uses the scan response data. It allows to send additional 31 bytes as advertising packets.
The Central device has to probe by an active scan to receive this data through the indication #CLX_GAP_BLE_DEVICE_ADVERTISING_INDICATION

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_SET_SCAN_RESPONSE_DATA_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack             Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] scanResponseData  Data to be sent in scan response packets
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

        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: If length of scanResponseData buffer is greater than CLX_BLE_ADVERTISING_DATA_MAX_SIZE.
        - #CLX_ERROR_INVALID_COMMAND_PARAMETER: If scanResponseData parameter is NULL.
        - #CLX_ERROR_TIMEOUT_OCCURRED: Timeout occurred before the response to the HCI command is received.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleSetScanResponseData(_in_ ClxStack                           stack,
                                       _user_in_ const ClxBleAdvertisingData*  scanResponseData,
                                       _in_ boolean                            block);

/**
Creates a new extended advertising set with the provided parameters, or update the parameters of an existing extended advertising set.
If this command is used to update the parameters of an existing extended advertising set, the set must not have already been enabled (by a call to #clxGapBleEnableDisableExtendedAdvertising).
Otherwise, this command will fail with an error.

NOTE : This API requires Bluetooth V5.0 or later.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_SET_EXTENDED_ADVERTISING_PARAMETERS_COMPLETE.
                   This indication parameters are of the type #ClxGapBleSetExtendedAdvertisingParametersComplete.

\param[  in   ] stack                           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] existingAdvertisingHandle       The handle to an existing extended advertising set. If set to CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE, a new extended advertising set will be created.
\param[  in   ] advertisingIntervalMin          Minimum advertising interval for undirected and low duty cycle directed advertising, in the units of 0.625 ms.
                                                A valid value ranges from 0x000020 (20 ms) to 0xFFFFFF (10,485 s).

\param[  in   ] advertisingIntervalMax          Maximum advertising interval for undirected and low duty cycle directed advertising, in the units of 0.625 ms.
                                                A valid value ranges from 0x000020 (20 ms) to 0xFFFFFF (10,485 s).

\param[  in   ] advertisingFlags                Flag bits which provide more information about the extended advertising set. May be an OR-ed combination of values defined in #ClxBleExtendedAdvertisingFlag.

\param[  in   ] advertisingType                 The type of advertising PDU to use for this advertising set. This applies to both legacy and non-legacy (extended) advertising PDUs.
                                                Legacy PDUs will be used if the bit #ClxBleExtendedAdvertisingFlag_LegacyAdvertising is set in \a advertisingFlags
                                                Refer to the documentation of #ClxBleExtendedAdvertisingSetTypeFlags for more information.
\param[  in   ] localAddressType                Own address type: local device's address type.
\param[  in   ] peerAddress                     Address to directly advertise to (set to NULL if not using directed advertising)

\param[  in   ] primaryAdvertisingChannelsToUse        Selects the advertising channel to be used when transmitting the advertising packets. May be a OR-ed combination of the following values:
                                                    #CLX_BLE_ADVERTISING_CHANNEL_37
                                                    #CLX_BLE_ADVERTISING_CHANNEL_38
                                                    #CLX_BLE_ADVERTISING_CHANNEL_39
                                                Set to #CLX_BLE_ALL_ADVERTISING_CHANNELS to select all channels.

\param[  in   ] advertisingFilterPolicy         Filter policy applied to remote devices;
                                                0x00: Allow scan and connection request from anyone,
                                                0x01: Allow scan from whitelist only, allow connection request from any,
                                                0x02: Allow scan request from any device, allow connection request from white list devices only,
                                                0x03: Allow scan request and connection request from white list only

\param[  in   ] advertisingTxPower              Preferred TX power (in dBm) used to send the advertising packets. It ranges from -127 dBm to +20 dBm.
                                                A value of 0x7F indicates that the host has not preference.

\param[  in   ] primaryPhyType                  The PHY on which the advertising packets are transmitted on the primary advertising physical channel.
                                                If legacy advertising is being used (the flag ClxBleExtendedAdvertisingFlag_LegacyAdvertising is set in \a advertisingFlags argument),
                                                this argument is ignored and 1M PHY will be used.

\param[  in   ] secondaryAdvertisignMaxSkip     maximum number of advertising events that can be skipped before the first advertising packet is sent for this set.
                                                The value of 0 indicates that the first advertising packet shall be sent prior to the next advertising event.

\param[  in   ] secondaryPhyType                The PHY on which the advertising packets are transmitted on the secondary advertising physical channel.
                                                If legacy advertising is being used (the flag ClxBleExtendedAdvertisingFlag_LegacyAdvertising is set in \a advertisingFlags argument),
                                                this argument is ignored and 1M PHY will be used.

\param[  in   ] advertisingSID                  The SID value (advertising Set ID) for this advertising set. The value may be used by scanners to filter the advertising packets.
                                                If the advertising set only uses PDUs that do not contain an ADI field, Advertising_SID shall be ignored.

\param[  in   ] enableScanRequestNotification   If TRUE, CLX_GAP_BLE_SCAN_REQUEST_RECEIVED_INDICATION may be received for this advertising set. If FALSE, these indications will not be received for this set.

\param[  in   ] primaryPhyOptions               Primary advertising option for LE Coded PHY,.

\param[  in   ] secondaryPhyOptions             Secondary advertising option for LE Coded PHY,..

\param[  out  ] advertisingHandle               Upon a successful completion of this command, this argument will contain the handle to the created extended advertising set. If the command has been used
                                                to update an existing advertising set, this argument will be the same as existingAdvertisingHandle. This argument may be NULL.

\param[  out  ] selectedTxPower                 Upon a successful completion of this command, this argument will contain the TX power selected by the Bluetooth controller to send advertising packets for this set.

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
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleSetExtendedAdvertisingParameters(_in_ ClxStack                                   stack,
                                                    _in_ ClxBleExtendedAdvertisingHandle            existingAdvertisingHandle,
                                                    _in_ u4                                         advertisingIntervalMin,
                                                    _in_ u4                                         advertisingIntervalMax,
                                                    _in_ u4                                         advertisingFlags,
                                                    _in_ ClxBleExtendedAdvertisingSetTypeFlags      advertisingType,
                                                    _in_ ClxBleOwnAddressMode                       localAddressType,
                                                    _user_in_ const ClxBleBdAddress*                peerAddress,
                                                    _in_ u1                                         primaryAdvertisingChannelsToUse,
                                                    _in_ ClxBleAdvertisingFilterPolicy              advertisingFilterPolicy,
                                                    _in_ s1                                         advertisingTxPower,
                                                    _in_ ClxBlePhyType                              primaryPhyType,
                                                    _in_ u1                                         secondaryAdvertisignMaxSkip,
                                                    _in_ ClxBlePhyType                              secondaryPhyType,
                                                    _in_ u1                                         advertisingSID,
                                                    _in_ boolean                                    enableScanRequestNotification,
                                                    _in_ ClxBlePhyOptions                           primaryPhyOptions,
                                                    _in_ ClxBlePhyOptions                           secondaryPhyOptions,
                                                    _user_out_ ClxBleExtendedAdvertisingHandle*     advertisingHandle,
                                                    _user_out_ s1*                                  selectedTxPower,
                                                    _in_ boolean                                    block);

/**
Sets advertising data for an existing extended advertising set. The set must have been created by a previous call to #clxGapBleSetExtendedAdvertisingParameters.

NOTE : This API requires Bluetooth V5.0 or later.

This command may be used to set three different types of data for an advertising set, defined by the dataType argument. Each data type may be set independently from the others.

The maximum value for dataLength can be obtained from a call to #clxGapBleGetExtendedAdvertisingCapabilities. The Bluetooth controller may need to fragment the data into two or more advertising packets.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_SET_EXTENDED_ADVERTISING_DATA_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] advertisingHandle               The handle to an existing extended advertising set. This argument cannot be NULL.
\param[  in   ] dataType                        The type of the data to be set for the advertising set. Each data type may be set independently (without altering the other data types).
\param[  in   ] data                            The data (of the indicated type) to set for this advertising set. NULL to reset the advertising data associated with the given advertising handle.
\param[  in   ] dataLength                      The length of the data.
\param[  in   ] fragmentPreference              The fragmentation preference. This value could be ignored by the Bluetooth controller.
                                                If dataType is set to # ClxBleAdvertisingDataType_PeriodicAdvertising, this value will be ignored by the stack.

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
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleSetExtendedAdvertisingData(_in_ ClxStack                                         stack,
                                              _in_ ClxBleExtendedAdvertisingHandle                  advertisingHandle,
                                              _in_ ClxBleAdvertisingDataType                        dataType,
                                              _user_in_ const u1*                                   data,
                                              _in_ u4                                               dataLength,
                                              _in_ ClxBleAdvertisingFragmentPreference              fragmentPreference,
                                              _in_ boolean                                          block);

/**
Enables or disables one or more existing extended advertising sets.

NOTE : This API requires Bluetooth V5.0 or later.

Note : This command will succeed only if all extended advertising sets have been successfully enabled/disabled. Otherwise, the command will fail with an error.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_ENABLE_DISABLE_EXTENDED_ADVERTISING_COMPLETE.
                   This indication has no parameters.

\param[  in   ] stack                           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] adveretisingSets                A list of 1 or more advertising set information structures (of type #ClxBleAdvertisingSetInfo). This argument CANNOT be NULL.
                                                If the advertising set is to be enabled, all members of ClxBleAdvertisingSetInfo structure must be provided.
                                                If the advertising set is to be disabled, only the advertising handle (ClxBleAdvertisingSetInfo.handle) needs to be provided. The other members will be ignored.
\param[  in   ] numberOfAdvertisingSets         Number of advertising sets in the list (adveretisingSets). This argument CANNOT be 0.
\param[  in   ] enable                          If set to TRUE, the advertising sets will be enabled. If set to FALSE, the advertising set will be disabled.

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
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleEnableDisableExtendedAdvertising(_in_ ClxStack                                     stack,
                                                    _user_in_ const ClxBleAdvertisingSetInfo*         adveretisingSets,
                                                    _in_ u1                                           numberOfAdvertisingSets,
                                                    _in_ boolean                                      enable,
                                                    _in_ boolean                                      block);

/**
Enables periodic advertising mode for an existing extended advertising set.

NOTE : This API requires Bluetooth V5.0 or later.

Note : An advertising set cannot start periodic advertising if it has not been enabled (by a call to #clxGapBleEnableDisableExtendedAdvertising).
       This command may be called for an advertising set before OR after it has been enabled.
       If the advertising set is already enabled, periodic mode starts immediately.
       Otherwise, the periodic mode will be enabled but the periodic advertising will not start until #clxGapBleEnableDisableExtendedAdvertising is called for this advertising set.

Note : If the type of the advertising set (as passed to #clxGapBleSetExtendedAdvertisingParameters) allows the set to have data in its advertising packets,
       the data can be set by a call to #clxGapBleSetExtendedAdvertisingData, and setting the data type argument to #ClxBleAdvertisingDataType_PeriodicAdvertising.
       This data will be independent from other data types set for this advertising set, and will only be used in periodic advertising packets.

Note : Periodic advertising mode CANNOT be used for an anonymous advertising set (e.g. one with the flag #ClxBleExtendedAdvertisingFlag_Anonymous set for it).

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_ENABLE_PERIODIC_ADVERTISING_MODE_COMPLETE.
                   This indication has no parameters.

\param[  in   ] stack                           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] advertisingHandle               The handle to an existing extended advertising set. This argument cannot be NULL.
\param[  in   ] intervalMin                     Minimum advertising interval for periodic advertising, in the units of 1.25 ms.
                                                A valid value ranges from 0x0006 (7.5 ms) to 0xFFFF (81.9 s).
\param[  in   ] intervalMax                     Maximum advertising interval for periodic advertising, in the units of 1.25 ms.
                                                A valid value ranges from 0x0006 (7.5 ms) to 0xFFFF (81.9 s).
\param[  in   ] periodicFlags                   Flag bits which provide more information about the extended advertising set in periodic mode. May be an OR-ed combination of values defined in #ClxBlePeriodicAdvertisingFlag.
\param[  in   ] numSubEvents                    Number of sub events being transmitted for each periodic advertising event. Range: 0x00 to 0x80.
\param[  in   ] subEventInterval                Time between the subevents. Rangle: 0x06 to 0xFF.
\param[  in   ] responseSlotDelay               Time between the start of the advertising packet at the start of a subevent and the start of the first response slot. Range: 0x01 to 0xFE.
\param[  in   ] responseSlotSpacing             Time between the start of two consecutive response slots. Range: 0x02 to 0xFF.
\param[  in   ] numResponseSlots                Number of response slots in a subevent. Range: 0x01 to 0xFF.

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
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleEnablePeriodicAdvertisingMode(_in_ ClxStack                                     stack,
                                                 _in_ ClxBleExtendedAdvertisingHandle              advertisingHandle,
                                                 _in_ u4                                           intervalMin,
                                                 _in_ u4                                           intervalMax,
                                                 _in_ u2                                           periodicFlags,
                                                 _in_ u1                                           numSubEvents,
                                                 _in_ u1                                           subEventInterval,
                                                 _in_ u1                                           responseSlotDelay,
                                                 _in_ u1                                           responseSlotSpacing,
                                                 _in_ u1                                           numResponseSlots,
                                                 _in_ boolean                                      block);

/**
Disables periodic advertising mode for an existing extended advertising set.

NOTE : This API requires Bluetooth V5.0 or later.

Note : If an extended advertising set is disabled (by a call to #clxGapBleEnableDisableExtendedAdvertising) while it is already in periodic advertising mode,
       the advertising set will continue sending periodic advertising packets until is is disabled by a call to #clxGapBleDisablePeriodicAdvertisingMode.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_DISABLE_PERIODIC_ADVERTISING_MODE_COMPLETE.
                   This indication has no parameters.

\param[  in   ] stack                           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] advertisingHandle               The handle to an existing extended advertising set. This argument cannot be NULL.

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
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleDisablePeriodicAdvertisingMode(_in_ ClxStack                                     stack,
                                                  _in_ ClxBleExtendedAdvertisingHandle              advertisingHandle,
                                                  _in_ boolean                                      block);

/**
Retrieves extended advertising capabilities of the Bluetooth controller.

NOTE : This API requires Bluetooth V5.0 or later.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_GET_EXTENDED_ADVERTISING_CAPABILITIES_COMPLETE.
                   This indication parameters are of the type #ClxGapBleGetExtendedAdvertisingCapabilitiesComplete.

\param[  in   ] stack                               Local device stack handle. A stack object must be created before a GAP API used.
\param[  out  ] maxDataLengthPerAdvertisingSet      Upon successful completion of the command, contains the maximum length of data which can be set for a ordinary extended advertising, periodic advertising, or scan response associated to an
                                                    extended advertising set. The Bluetooth controller may need to fragment the data into two or more packets.

\param[  out  ] maxNumberOfSupportedAdvertisingSets Upon successful completion of the command, contains the maximum number of advertising sets supported by the Bluetooth controller.
                                                    Actual number of extended advertising set that can be used at the same time is also limited by the amount of memory and resources available to the Bluetooth controller at any time,
                                                    and may be less than this value.

\param[  in   ] block                               Type of the operation.
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

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
           any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleGetExtendedAdvertisingCapabilities(_in_ ClxStack     stack,
                                                      _user_out_ u2*    maxDataLengthPerAdvertisingSet,
                                                      _user_out_ u1*    maxNumberOfSupportedAdvertisingSets,
                                                      _in_ boolean      block);

/**
Removes an existing extended advertising set.

NOTE : This API requires Bluetooth V5.0 or later.

NOTE : When an extended advertising set is removed successfully, its handle becomes invalid. Using an invalid handle in any API will result in an error.

NOTE : An enabled advertising set (in non-periodic or periodic mode) cannot be removed.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_REMOVE_EXTENDED_ADVERTISING_SET_COMPLETE.
                   This indication has no parameters.

\param[  in   ] stack                               Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] advertisingHandle                   The handle to an existing extended advertising set. This argument cannot be NULL.

\param[  in   ] block                               Type of the operation.
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

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
           any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleRemoveExtendedAdvertisingSet(_in_ ClxStack                                   stack,
                                                _in_ ClxBleExtendedAdvertisingHandle            advertisingHandle,
                                                _in_ boolean                                    block);

/**
Removes all existing extended advertising sets.

NOTE : This API requires Bluetooth V5.0 or later.

NOTE : If this command succeeds, all Extended Advertising handles become invalid. Using an invalid handle in any API will result in an error.

NOTE : An enabled advertising set (in non-periodic or periodic mode) cannot be removed.

NOTE : The command is successful only if all provided advertising sets can be removed. Otherwise, the command will fail with an error.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_CLEAR_EXTENDED_ADVERTISING_SETS_COMPLETE.
                   This indication has no parameters.

\param[  in   ] stack                               Local device stack handle. A stack object must be created before a GAP API used.

\param[  in   ] block                               Type of the operation.
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

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
           any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleClearExtendedAdvertisingSets(_in_ ClxStack      stack,
                                                _in_ boolean       block);

/**
This API is used to poll the advertising reports from peripheral device. The available reports will be delivered to application through the indications
#CLX_GAP_BLE_DEVICE_ADVERTISING_INDICATION or #CLX_GAP_BLE_DEVICE_EXTENDED_ADVERTISING_INDICATION.

Please note that the single report shall be delivered to application for each API call.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_POLL_ADVERTISING_REPORT_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack   Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] block   Type of the operation.
                            - TRUE:  API will be blocked until this command is completed (successfully or failed).
                            - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_COMMAND_NOT_SUPPORTED: When Bluetooth library does not support for polling the advertising report
        - #CLX_ERROR_BLE_ADVERTISING_REPORT_QUEUE_EMPTY: No more advertising reports available
*/
ClxResult clxGapBlePollAdvertisingReport(_in_ ClxStack   stack,
                                         _in_ boolean    block);

/**
Used for initializing the custom extended advertising data field. For the details of latest version of the fields see assigned numbers Generic Access Profile;
https://www.bluetooth.com/specifications/assigned-numbers/Generic-Access-Profile

Note: Must ensure paylaod length is less than the obj data size.

Below list shows the "type" values and descriptions;
- 0x01  Flags
- 0x02  Incomplete List of 16-bit Service Class UUIDs
- 0x03  Complete List of 16-bit Service Class UUIDs
- 0x04  Incomplete List of 32-bit Service Class UUIDs
- 0x05  Complete List of 32-bit Service Class UUIDs
- 0x06  Incomplete List of 128-bit Service Class UUIDs
- 0x07  Complete List of 128-bit Service Class UUIDs
- 0x08  Shortened Local Name
- 0x09  Complete Local Name
- 0x0A  Tx Power Level
- 0x0D  Class of Device
- 0x0E  Simple Pairing Hash C
- 0x0E  Simple Pairing Hash C-192
- 0x0F  Simple Pairing Randomizer R
- 0x0F  Simple Pairing Randomizer R-192
- 0x10  Device ID
- 0x10  Security Manager TK Value
- 0x11  Security Manager Out of Band Flags
- 0x12  Slave Connection Interval Range
- 0x14  List of 16-bit Service Solicitation UUIDs
- 0x1F  List of 32-bit Service Solicitation UUIDs
- 0x15  List of 128-bit Service Solicitation UUIDs
- 0x16  Service Data
- 0x16  Service Data - 16-bit UUID
- 0x20  Service Data - 32-bit UUID
- 0x21  Service Data - 128-bit UUID
- 0x22  LE Secure Connections Confirmation Value
- 0x23  LE Secure Connections Random Value
- 0x24  URI
- 0x25  Indoor Positioning
- 0x26  Transport Discovery Data
- 0x17  Public Target Address
- 0x18  Random Target Address
- 0x19  Appearance
- 0x1A  Advertising Interval
- 0x1B  LE Bluetooth Device Address
- 0x1C  LE Role
- 0x1D  Simple Pairing Hash C-256
- 0x1E  Simple Pairing Randomizer R-256
- 0x2C  BIG Information
- 0x3D  3D Information Data
- 0xFF  Manufacturer Specific Data

\param[  out  ] obj            User buffer for extended advertising the local device's custom data
\param[  in   ] type           Extended advertising data type as described above
\param[  in   ] payload        The data being advertised
\param[  in   ] payloadLength  The length of custom data

\return TRUE if extended advertising data is added successfully, else FALSE when any of the arguments passed with invalid/incorrect values.
*/

boolean clxBleAddExtendedAdvertisingDataField(ClxBleExtendedAdvertisingData* obj,
                                              u1                             type,
                                              const u1*                      payload,
                                              u1                             payloadLength);

/**
Configures the local device's audio role.

This API shall be supported from the core spec version 5.3 or ClarinoxBlue version 13.0.0

\param[  in   ] role                    Audio role of type #ClxBleAudioRole supported by local device
\param[  out  ] extAdvDataObj           User buffer for extended advertising filled data

\return         #CLX_SUCCESS            if the audio role is added in extended advertising data
                #CLX_ERROR              when the audio role is not added
*/
ClxResult clxGapBleSetAudioRole(_in_       u2                              role,
                                _user_out_ ClxBleExtendedAdvertisingData*  extAdvDataObj);


#ifdef __cplusplus
}
#endif

#endif //__GAP_BLE_PERIPHERAL_API_h__
