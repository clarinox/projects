#ifndef __GAP_BLE_CENTRAL_API_h__
#define __GAP_BLE_CENTRAL_API_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gap.Ble.Central.Api.h
* Description         Declares API Functions and Definitions For GapBle Central 
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026

*******************************************************************************/

#include "Gap.Ble.DirectionFinding.Api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
Refer to #clxGapBleEnableExtendedScan function.
*/
#define CLX_GAP_BLE_ENABLE_EXTENDED_SCAN_COMPLETE                                           0x6900

/**
Refer to #clxGapBleDisableExtendedScan function.
*/
#define CLX_GAP_BLE_DISABLE_EXTENDED_SCAN_COMPLETE                                          0x6901

/**
Refer to #clxGapBleDisconnectPhysicalLink function.
*/
#define CLX_GAP_BLE_DISCONNECT_PHYSICAL_LINK_COMPLETE                                       0x6902

/**
Refer to #clxGapBlePeriodicAdvertisingSyncTransfer function.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_TRANSFER_COMPLETE                             0x6903


/**
Refer to #clxGapBlePeriodicAdvertisingStartSynchronizing function.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_START_SYNCHRONIZING_COMPLETE                       0x6904

/**
Refer to #clxGapBlePeriodicAdvertisingCancelSynchronizing function.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_CANCEL_SYNCHRONIZING_COMPLETE                      0x6905

/**
Refer to #clxGapBlePeriodicAdvertisingStopSynchronizing function.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_STOP_SYNCHRONIZING_COMPLETE                        0x6906
/**
Refer to #clxGapBleEncrypt function.
*/
#define CLX_GAP_BLE_ENCRYPT_COMPLETE                                                        0x6907

/**
Refer to #clxGapBleExtendedConnectToPeripheral function.
*/
#define CLX_GAP_BLE_EXTENDED_CONNECT_TO_PERIPHERAL_COMPLETE                                 0x6908

/**
Refer to #clxGapBleAddRemoveDeviceInPeriodicAdvertiserList function.
*/
#define CLX_GAP_BLE_ADD_REMOVE_DEVICE_IN_PERIODIC_ADVERTISER_LIST_COMPLETE                  0x6909

/**
Refer to #clxGapBleClearAllDevicesFromPeriodicAdvertiserList function.
*/
#define CLX_GAP_BLE_CLEAR_ALL_DEVICES_FROM_PERIODIC_ADVERTISER_LIST_COMPLETE                0x690a

/**
Refer to #clxGapBleReadPeriodicAdvertiserListSize function.
*/
#define CLX_GAP_BLE_READ_PERIODIC_ADVERTISER_LIST_SIZE_COMPLETE                             0x690b

/**
Received when the first periodic advertising packet is received from the advertiser. Only after this,
the periodic advertising synchronization with the periodic advertising train from an advertiser is considered completed.
The parameter of this indication is of type #ClxGapBlePeriodicAdvertisingSyncEstablishedIndication.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_INDICATION                        0xa900


/**
Received when the periodic advertising sync is lost from the advertiser. Periodic advertising reports will no longer be received
unless the sync with the remote advertiser is established again.
The parameter of this indication is of type #ClxGapBlePeriodicAdvertisingSyncLostIndication.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_LOST_INDICATION                               0xa901


/**
This indication is received when the periodic advertising packet is received from the advertiser.
Periodic advertising synchronization with the periodic advertising train from an advertiser has to be established in order to receive this indication.
The parameter of this indication is of type #ClxGapBlePeriodicAdvertisingReportIndication.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_REPORT_INDICATION                                  0xa902

/**
This indication is received when the controller receives the periodic advertising synchronization information
from the device whose connection handle is returned as part of indication parameters.

The status indicates if the controller has successfully synchronized to the device or synchronization failed.
The parameter of this indication is of type #ClxGapBlePeriodicAdvertisingSyncTransferReceivedIndication.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_INDICATION                  0xa903

/**
This event shall be generated when a response to a PAwR train is received.
The parameter of this indication is of type #ClxGapBlePeriodicAdvertisingResponseReportIndication.
*/
#define CLX_GAP_BLE_PERIODIC_ADVERTISING_RESPONSE_REPORT_INDICATION                         0xa904

/**
Specifies the established connection type
*/
typedef enum ClxBleConnectionTypeEnum
{
    ClxBleConnectionType_Legacy     = 0x00,        /*!< Legacy connection */
    ClxBleConnectionType_Enhanced   = 0x01         /*!< Enhanced connection */
} ClxBleConnectionType;

typedef enum ClxExtendedScanFilterDuplicateEnum
{
    ClxExtendedScanFilterDuplicate_Disabled      = 0x00,    /*!< Duplicate filtering disabled */
    ClxExtendedScanFilterDuplicate_Enabled       = 0x01,    /*!< Duplicate filtering enabled */
    ClxExtendedScanFilterDuplicate_Enabled_Reset = 0x02     /*!< Duplicate filtering enabled, reset for each scan period*/
} ClxExtendedScanFilterDuplicate;

/**
Determines the scanning type
*/
typedef enum BleScanTypeEnum
{
    BleScanType_Passive = 0x00,
    BleScanType_Active  = 0x01
} BleScanType;


typedef enum ClxExtendedScanFilterPolicyEnum
{
    ClxExtendedScanFilterPolicy_All                              = 0x00,       /*!< Accept all advertising and scan response PDUs except directed advertising PDUs not addressed to this device */
    ClxExtendedScanFilterPolicy_WhiteList                        = 0x01,       /*!< Accept only advertising and scan response PDUs from devices where the advertiser's address is in the White List.
                                                                                    Directed advertising PDUs which are not addressed to this device shall be ignored. */
    ClxExtendedScanFilterPolicy_InitiatedByLocalDevice           = 0x02,       /*!< Accept all advertising and scan response PDUs except directed advertising PDUs where the initiator's identity address does not address this device.
                                                                                    Note: Directed advertising PDUs where the initiator's address is a resolvable private address that cannot be resolved are also accepted.*/
    ClxExtendedScanFilterPolicy_WhiteList_InitiatedByLocalDevice = 0x03,       /*!< Accept all advertising and scan response PDUs except:
                                                                                    advertising and scan response PDUs where the advertiser's identity address is not in the White List; and
                                                                                    directed advertising PDUs where the initiator's identity address does not address this device
                                                                                    Note: Directed advertising PDUs where the initiator's address is a resolvable private address that cannot be resolved are also accepted. */
} ClxExtendedScanFilterPolicy;


/* Parameters for extended scan on a primary channel (Bluetooth 5.0 or later): */
typedef struct ClxGapBleExtendedScanParametersStruct
{
    BleScanType           scanType;
    u4                    scanInterval;
    u4                    scanWindow;
} ClxGapBleExtendedScanParameters;


/**
Details of the Periodic Advertiser to whom the local device shall sync with.
*/
typedef struct ClxBlePeriodicAdvertiserDetailsStruct
{
    u1               advertisingSID;       /*!< The SID value (advertising Set ID) subfield set in the ADI filed of Advertising PDU */
    ClxBleBdAddress  advertiserAddress;    /*!< Specifies the address of the periodic advertiser */
} ClxBlePeriodicAdvertiserDetails;

/* Parameters for extended connect (Bluetooth 5.0 or later): */
typedef struct ClxGapBleExtendedConnectParametersStruct
{
    u2          scanInterval;               /*!< Value to define how frequently the controller should scan. The value range starts from 0x0004 to 0xFFFF */
    u2          scanWindow;                 /*!< Value to define how long the controller should scan. The value range starts from 0x0004 to 0xFFFF.
                                                 The value of scan window should not be greater than the value of scan interval.
                                                 If both are set to the same value, then the scanning should happen continuously */
    u2          connectIntervalMin;         /*!< Minimum interval value for the connection. The value range starts from 0x0006 to 0x0C80 */
    u2          connectIntervalMax;         /*!< Maximum interval value for the connection. The value range starts from 0x0006 to 0x0C80 */
    u2          connectionLatency;          /*!< Value to define the slave latency for the connection. The value range starts from 0x0000 to 0x01F3 */
    u2          supervisionTimeout;         /*!< Value to define the link supervision timeout for the connection (multiples of 10 milliseconds).
                                                 The value range starts from 0x000A to 0x0C80 */
    u2          minCElength;                /*!< Minimum length of connection event. The value range starts from 0x0000 to 0xFFFF */
    u2          maxCElength;                /*!< Maximum length of connection event. The value range starts from 0x0000 to 0xFFFF */
} ClxGapBleExtendedConnectParameters;

typedef struct ClxBleConnectionDetailsStruct
{
    ClxBleConnectionType    type;                           /*!< Connection type */
    ClxBleBdAddress         remoteDeviceAddr;               /*!< The identity address or the current physical address of the remote device */
    ClxBleConnectionHandle  connectionHandle;               /*!< The handle of the connection to the remote device. This handle will not change until the connection is terminated */
    u2                      connectionInterval;             /*!< The connection interval */
    u2                      connectionLatency;              /*!< The connection latency */
    u2                      supervisionTimeout;             /*!< The connection supervision timeout */
    u1                      localPrivateAddress[6];         /*!< Local reolvable private address. This is valid for the connection type #ClxBleConnectionType_Enhanced */
    u1                      remotePrivateAddress[6];        /*!< Remote reolvable private address. This is valid for the connection type #ClxBleConnectionType_Enhanced */
    u1                      advertisingHandle;              /*!< Identifies the advertising set */
    u2                      syncHandle;                     /*!< Identifies the periodic advertising train */
} ClxBleConnectionDetails;


/**
Data Structure for the indication #CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_INDICATION
*/
typedef struct ClxGapBlePeriodicAdvertisingSyncEstablishedIndicationStruct
{
    ClxResult                        status;                         /*!< Status of the event returned from the controller */
    u2                               syncHandle;                     /*!< Handle identifying the periodic advertising train */
    ClxBlePeriodicAdvertiserDetails  advertiserDetails;              /*!< Specifies the address and SID details of the periodic advertiser */
    ClxBlePhyType                    advertiserPhy;                  /*!< PHY used for periodic advertisement */
    u2                               periodicAdvertisingInterval;    /*!< Interval between the periodic advertising events */
    u1                               advertiserClockAccuracy;        /*!< Accuracy of the periodic advertiser's clock */
    u1                               noOfSubEvents;                  /*!< Number of sub events */
    u1                               subEventInterval;               /*!< Sub event interval */
    u1                               responseSlotDelay;              /*!< Response slot delay */
    u1                               responseSlotSpacing;            /*!< Response slot spacing */
} ClxGapBlePeriodicAdvertisingSyncEstablishedIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_LOST_INDICATION
*/
typedef struct ClxGapBlePeriodicAdvertisingSyncLostIndicationStruct
{
    u2  syncHandle;    /*!< Handle identifying the periodic advertising train */
} ClxGapBlePeriodicAdvertisingSyncLostIndication;


/**
Data Structure for the indication #CLX_GAP_BLE_PERIODIC_ADVERTISING_REPORT_INDICATION
*/
typedef struct ClxGapBlePeriodicAdvertisingReportIndicationStruct
{
    u2                                   syncHandle;                /*!< Handle identifying the periodic advertising train */
    u1                                   txPower;                   /*!< TX Power as received from remote device */
    s1                                   rssi;                      /*!< RSSI value for the packet, excluding any Constant Tone Extension. */
    ClxBleCteType                        cteType;                   /*!< Specifies the type CTE (Constant Tone Extension) */
    u2                                   periodicEventCounter;      /*!< The value of event counter for the reported periodic advertising packet */
    u1                                   subEvent;                  /*!< Sub event number */
    ClxBlePeriodicAdvertisingDataStatus  dataStatus;                /*!< Indicates if the data is completely or partially received from the periodic advertiser */
    u1                                   dataSize;                  /*!< Size of the Periodic advertising data received from remote periodic advertiser */
    u1*                                  data;                      /*!< Periodic advertising data received from remote periodic advertiser */
} ClxGapBlePeriodicAdvertisingReportIndication;


/**
Data Structure for the indication #CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_INDICATION
*/
typedef struct ClxGapBlePeriodicAdvertisingSyncTransferReceivedIndicationStruct
{
    u1                               status;                         /*!< 0x00 if synchronization is successful otherwise the error code indicates the reason */
    u2                               connectionHandle;               /*!< Connection Handle that corresponds to the reported information */
    u2                               serviceData;                    /*!< Information provided by the remote device */
    u2                               syncHandle;                     /*!< Handle identifying the periodic advertising train */
    ClxBlePeriodicAdvertiserDetails  advertiserDetails;              /*!< Specifies the address and SID details of the periodic advertiser */
    ClxBlePhyType                    advertiserPhy;                  /*!< PHY used for periodic advertisement */
    u2                               periodicAdvertisingInterval;    /*!< Interval between the periodic advertising events */
    u1                               advertiserClockAccuracy;        /*!< Accuracy of the periodic advertiser's clock */
    u1                               noOfSubEvents;                  /*!< Number of sub events */
    u1                               subEventInterval;               /*!< Subevent interval */
    u1                               responseSlotDelay;              /*!< Response slot delay */
    u1                               responseSlotSpacing;            /*!< Response slot spacing */
} ClxGapBlePeriodicAdvertisingSyncTransferReceivedIndication;


/**
Data Structure for the indication #CLX_GAP_BLE_PERIODIC_ADVERTISING_RESPONSE_REPORT_INDICATION
*/
typedef struct ClxGapBlePeriodicAdvertisingResponseReportIndicationStruct
{
    u1              advertisingHandle;                               /*!< Handle to indentify periodic advertising train */
    u1              subEvent;                                        /*!< Subevent number */
    u1              txStatus;                                        /*!< Sync subevent data transmitted or not */
    u1              txPower;                                         /*!< Tx power detail */
    u1              rssi;                                            /*!< RSSI */
    ClxBleCteType   cteType;                                         /*!< Constant Tone Extension type */
    u1              responseSlot;                                    /*!< Received data response slot */
    u1              dataStatus;                                      /*!< Status about whether the data is completed or not */
    u1              dataLength;                                      /*!< Length of data */
    u1*             data;                                            /*!< Periodic advertising response data */
} ClxGapBlePeriodicAdvertisingResponseReportIndication;

/**
Enables extended scan.

NOTE : This API requires Bluetooth V5.0 or later.

Note : If the duration argument is zero or both the duration argument and the period argument are non-zero, the Bluetooth controller continues scanning until scanning
       is disabled by a call to #clxGapBleDisableExtendedScan .The period argument will be ignored when the duration argument is zero.

Note : If the duration argument is non-zero and the period argument is zero, The Bluetooth controller will continue scanning until the duration has expired.

Note : If both the duration argument and the period argument are non-zero, the period must be greater than the duration.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_ENABLE_EXTENDED_SCAN_COMPLETE.
                This indication has no parameters.

\param[  in   ] stack                           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] localAddressType                Own address type: local device's address type.
\param[  in   ] filterPolicy                    The filtering policy to be used during scan.
\param[  in   ] scanParameter_Le1M_PHY          The scan parameters used when the primary channels are being scanned using LE 1M PHY.
                                                If set to NULL, LE 1M PHY will not be used for scanning.
\param[  in   ] scanParameter_LeCoded_PHY       The scan parameters used when the primary channels are being scanned using LE Coded PHY.
                                                If set to NULL, LE Coded PHY will not be used for scanning.
\param[  in   ] filterDuplicates                Filtering policy used for duplicate advertising packets.
\param[  in   ] duration                        Scan duration in one scan period, in units of 10 ms. It ranges from 0x0001 (10 ms) to 0xFFFF (655.34 s).
                                                A value of zero indicates that the Bluetooth controller must scan continuously until explicitly disabled.
\param[  in   ] period                          Time interval from when the Bluetooth controller started its last scan duration
                                                until it begins the subsequent scan duration, in units of 1.28 seconds.
                                                It ranges from 0x0001 (1.28 s) to 0xFFFF (83,884 s).
                                                A value of zero indicates that the Bluetooth controller must scan continuously.

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
ClxResult clxGapBleEnableExtendedScan(_in_ ClxStack                                         stack,
                                      _in_ ClxBleOwnAddressMode                             localAddressType,
                                      _in_ ClxExtendedScanFilterPolicy                      filterPolicy,
                                      _user_in_ const ClxGapBleExtendedScanParameters*      scanParameter_Le1M_PHY,
                                      _user_in_ const ClxGapBleExtendedScanParameters*      scanParameter_LeCoded_PHY,
                                      _in_ ClxExtendedScanFilterDuplicate                   filterDuplicates,
                                      _in_ u2                                               duration,
                                      _in_ u2                                               period,
                                      _in_ boolean                                          block);

/**
Disables extended scan.

NOTE : This API requires Bluetooth V5.0 or later.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_DISABLE_EXTENDED_SCAN_COMPLETE.
                   This indication has no parameters.

\param[  in   ] stack              Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] block              Type of the operation.
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
ClxResult clxGapBleDisableExtendedScan(_in_ ClxStack    stack,
                                       _in_ boolean     block);

/**
Disconnects from the remote connection.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_DISCONNECT_PHYSICAL_LINK_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                       BLE stack handle.
\param[  in   ] connectionHandle            The handle of the physical connection to be disconnected.
\param[  in   ] disconnectionTimeoutValue   Timeout value (in milliseconds) for disconnection attempt.
\param[  in   ] block                       Type of the operation.
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

        - #CLX_ERROR_CONNECTION_NOT_EXIST: There is no active Bluetooth LowEnergy physical link to the remote device
        - #CLX_ERROR_TIMEOUT_OCCURRED: Fail to receive disconnect complete event due to no response from remote device
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleDisconnectPhysicalLink(_in_ ClxStack                stack,
                                          _in_ ClxBleConnectionHandle  connectionHandle,
                                          _in_ u4                      disconnectionTimeoutValue,
                                          _in_ boolean                 block);

/**
Transfers the periodic advertising sync details to broacast sink or scan delegator. The synchronization should have been started before using the API #clxGapBlePeriodicAdvertisingStartSynchronizing.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_TRANSFER_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack               Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle    ACL connection handle  which is established using the API #clxGapBleExtendedConnectToPeripheral.
\param[  in   ] serviceData         Application provided data between broadcast assistant and sink device.
\param[  in   ] syncHandle          Handle identifying the periodic advertising train.
\param[  in   ] block               Type of the operation. 
                            -           TRUE:  API will be blocked until this command is completed (successfully or failed). 
                            -           FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBlePeriodicAdvertisingSyncTransfer(_in_ ClxStack  stack,
                                                   _in_ u2        connectionHandle,
                                                   _in_ u2        serviceData,
                                                   _in_ u2        syncHandle,
                                                   _in_ boolean   block);


/**
Synchronizes with periodic advertising train from advertiser and starts receiving periodic advertising packets.

NOTE: Synchronization happens only when scanning is enabled and if the value matches with the
Advertising SID subfield in the ADI field of the received advertisement packet.

NOTE: This command is considered complete only when indication #CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_INDICATION is received. API #clxGapBlePeriodicAdvertisingCancelSynchronizing can be used to cancel the command anytime before the indication #CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_INDICATION is received.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_PERIODIC_ADVERTISING_START_SYNCHRONIZING_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                 Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] useAdvertiserList     TRUE to listen to advertisers from advertiser list (Advertiser details given to this API is ignored. Can be passed as NULL).
                                      FALSE to listen to advertiser whose details are passed as arguments to this API
\param[  in   ] enableReporting       TRUE to enable receiving advertising reports initially. FALSE to disable initial receiving of reports.
\param[  in   ] advertiserDetails     Specifies the address details of the periodic advertiser. NULL if \a useAdvertiserList is TRUE
\param[  in   ] numberOfEventsToSkip  The maximum number of periodic advertising events that can be skipped after a successful receive. Range - 0 to 499
\param[  in   ] syncTimeout           The maximum permitted time between successful receives. If this time is exceeded, synchronization is lost. Range - 100 ms to 163.84 s
\param[  in   ] syncCteType           Sync types of CTE in periodic advertising to synchronize to, as a OR-ed combination of values defined in #ClxBleSyncCteType.
\param[  in   ] block                 Type of the operation.
                                      - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                      - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBlePeriodicAdvertisingStartSynchronizing(_in_ ClxStack                                     stack,
                                                         _in_ boolean                                      useAdvertiserList,
                                                         _in_ boolean                                      enableReporting,
                                                         _user_in_ const ClxBlePeriodicAdvertiserDetails*  advertiserDetails,
                                                         _in_ u2                                           numberOfEventsToSkip,
                                                         _in_ u2                                           syncTimeout,
                                                         _in_ u1                                           syncCteType,
                                                         _in_ boolean                                      block);

/**
Cancel the synchronization command that is currently in progress. The synchronization should have been started before using the API #clxGapBlePeriodicAdvertisingStartSynchronizing.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_PERIODIC_ADVERTISING_CANCEL_SYNCHRONIZING_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack  Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] block  Type of the operation.
                       - TRUE:  API will be blocked until this command is completed (successfully or failed).
                       - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBlePeriodicAdvertisingCancelSynchronizing(_in_ ClxStack  stack,
                                                          _in_ boolean   block);

/**
Stops reception of the periodic advertising train identified by the given sync handle. The synchronization should have been started before using the API #clxGapBlePeriodicAdvertisingStartSynchronizing.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_PERIODIC_ADVERTISING_STOP_SYNCHRONIZING_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack       Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] syncHandle  Handle identifying the periodic advertising train.
\param[  in   ] block       Type of the operation.
                            - TRUE:  API will be blocked until this command is completed (successfully or failed).
                            - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBlePeriodicAdvertisingStopSynchronizing(_in_ ClxStack  stack,
                                                        _in_ u2        syncHandle,
                                                        _in_ boolean   block);

/**
Encrypts the connection for already paired or bonded devices. This API shall be used by Central role only.

If a key with enough strength is available in both the local machine and remote machine, the encryption procedure will carry on.
If this is not the case, the behavior of this function will be based on the local device role:

- Local device is a central : The command is complete with an error. The application may call #clxGapBleStartBondingProcedure() to perform bonding with the remote device.
- Local device is a peripheral : The pairing will be automatically initiated by the remote central.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_ENCRYPT_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack              Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle   The handle of the physical connection to be encrypted.
\param[  in   ] bondingProperties  Configuring the bonding properties, refer to #ClxBleSmpSecureBondingProperty..
                                    - TRUE:  If previously bonded, start encryption. Otherwise return an error to indicate bonding with the remote device required CLX_ERROR_BLE_SMP_AUTHENTICATION_REQUIREMENTS.
                                    - FALSE: Turn encryption off
\param[  in   ] block              Type of the operation.
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
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid.
        - #CLX_ERROR_GAP_PAIRED_DEVICES_COUNT_MAX_LIMIT_REACHED: When the configured maximum no of paired devices count (Ble.MaxNoOfPairedDevices) reached.
        - #CLX_ERROR_COMMAND_NOT_SUPPORTED: The API shall be used only by Central role.
        - #CLX_ERROR_BLE_SMP_PASSKEY_ENTRY_FAILED: The user input of passkey failed, for example, the user cancelled the operation.
        - #CLX_ERROR_BLE_SMP_OOB_NOT_AVAILABLE: The OOB data is not available.
        - #CLX_ERROR_BLE_SMP_AUTHENTICATION_REQUIREMENTS: The pairing procedure cannot be performed as authentication requirements cannot be met due to IO capabilities of one or both devices.
        - #CLX_ERROR_BLE_SMP_CONFIRM_VALUE_FAILED: The confirm value does not match the calculated compare value.
        - #CLX_ERROR_BLE_SMP_PAIRING_NOT_SUPPORTED: Pairing is not supported by the device.
        - #CLX_ERROR_BLE_SMP_ENCRYPTION_KEY_SIZE: The resultant encryption key size is insufficient for the security requirements of this device.
        - #CLX_ERROR_BLE_SMP_COMMAND_NOT_SUPPORTED: The SMP command received is not supported on this device.
        - #CLX_ERROR_BLE_SMP_UNSPECIFIED_REASON: Pairing failed due to an unspecified reason.
        - #CLX_ERROR_BLE_SMP_REPEATED_ATTEMPTS: Pairing or authentication procedure is disallowed because too little time has elapsed since last pairing request or security request.
        - #CLX_ERROR_BLE_SMP_INVALID_PARAMETERS: The Invalid Parameters error code indicates the command length is invalid a parameter is outside of the specified range.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.

\remarks
Bonding information will be deleted when the API returns the below error codes
                - CLX_ERROR_HCI_AUTHENTICATION_FAILURE
                - CLX_ERROR_HCI_PIN_OR_KEY_MISSING
*/
ClxResult clxGapBleEncrypt(_in_ ClxStack                stack,
                           _in_ ClxBleConnectionHandle  connectionHandle,
                           _in_ u1                      bondingProperties,
                           _in_ boolean                 block);

/**
Establish an instance of a extended connection to remote device.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_EXTENDED_CONNECT_TO_PERIPHERAL_COMPLETE.
                   The parameter of this indication is of type #ClxGapBleConnectToPeripheralComplete.

\param[  in   ] stack                         Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] advertisingHandle             Periodic advertising train handle.
\param[  in   ] subEvent                      Subevent where the connection request is being sent.
\param[  in   ] localAddressType              Own address type: local device's address type.
\param[  in   ] peerAddress                   Address to directly connect to (set to NULL if not using directed connection). The address type shall be one of the following:
                                              #ClxBleAddressType_Public : The address is the public address of the remote device. Directly use this address for connection.
                                              #ClxBleAddressType_Random : The address is the random address of the remote device. Directly use this address for connection.
                                              #ClxBleAddressType_PublicIdentity : The address is the public address of the remote device.
                                              Connect using the latest resolvable private address of the remote device. If no such an address exists, the command completes with the error CLX_ERROR_INVALID_REQUEST.
                                              #ClxBleAddressType_StaticIdentity : The address is the static address of the remote device.
                                              Connect using the latest resolvable private address of the remote device. If no such an address exists, the command completes with the error CLX_ERROR_INVALID_REQUEST.


\param[  in   ] connectParameter_Le1M_PHY     The parameters for 1M Phy to establish the ACL connection.
\param[  in   ] connectParameter_Le2M_PHY     The parameters for 2M Phy to establish the ACL connection.
\param[  in   ] connectParameter_Le_Coded     The parameters for LE coded Phy to establish the ACL connection.
\param[  out  ] connectionDetails             Connection details
\param[  in   ] connectionTimeoutValue        Timeout value (in milliseconds) for the connection attempt. If a link cannot be created to the remote device
                                              before the connection timer expires, the connection request will be cancelled and this function will complete with an error.
\param[  in   ] block                         Type of the operation.
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

        - #CLX_ERROR_TIMEOUT_OCCURRED: Connection procedure has been cancelled as the connection timer expired.
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid.
        - #CLX_ERROR_BLE_SMP_IR_PARAMETER_NOT_CONFIGURED: BSP Configuration parameter Ble.Smp.IR is not configured.
                                                          (Applicable only if 'localAddressType' parameter is ClxBleOwnAddressMode_PrivateResolvable)
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleExtendedConnectToPeripheral(_in_ ClxStack                                    stack,
                                               _in_ u1                                          advertisingHandle,
                                               _in_ u1                                          subEvent,
                                               _in_ ClxBleOwnAddressMode                        localAddressType,
                                               _user_in_ const ClxBleBdAddress*                 peerAddress,
                                               _user_in_ ClxGapBleExtendedConnectParameters*    connectParameter_Le1M_PHY,
                                               _user_in_ ClxGapBleExtendedConnectParameters*    connectParameter_Le2M_PHY,
                                               _user_in_ ClxGapBleExtendedConnectParameters*    connectParameter_Le_Coded,
                                               _user_out_ ClxBleConnectionDetails*              connectionDetails,
                                               _in_ u4                                          connectionTimeoutValue,
                                               _in_ boolean                                     block);

/**
Used to search for the availability of custom data in the given extended advertising data.

\param[  in   ] data            extended advertising data
\param[  in   ] dataLength      Length of the extended advertising data in bytes
\param[  in   ] type            Data type as described above or refer to assigned numbers in the Generic Access Profile
\param[  out  ] payloadLength   The length of the custom data payload

\return         If the given custom data type is available in the source extended advertising data, returns the starting reference of the custom data.
                If the API returns NULL, the specified custom data type is not initialized in the extended advertising data buffer.
*/
const u1* clxBleFindExtendedAdvDataField(const u1* data, u1 dataLength, u1 type, u1* payloadLength);

/**
Used to search for the availability of custom data in the given extended advertising data using service UUID.

\param[  in   ] data              extended advertising data
\param[  in   ] dataLength        Length of the extended advertising data in bytes
\param[  in   ] uuid              Service UUID type and UUID value used to find the data.
\param[  out  ] payloadLength     The length of the custom data payload

\return         If the given custom data type is available in the source extended advertising data, returns the starting reference of the custom data.
                If the API returns NULL, the specified custom data type is not initialized in the extended advertising data buffer.
*/
const u1* clxBleFindExtendedAdvDataByUUID(const u1* data, u1 dataLength, ClxGattUuid* uuid, u1* payloadLength);

/**
Adds/Removes the given device to/from the Periodic Advertiser list in Controller.

NOTE: Already added/removed device shall not be added/removed again.

NOTE: New device shall not be added/removed if the command #clxGapBlePeriodicAdvertisingStartSynchronizing execution is still pending.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_ADD_REMOVE_DEVICE_IN_PERIODIC_ADVERTISER_LIST_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack              Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] isRemove           TRUE to remove the adverser entry from controller's list. FALSE to add the advertiser entry to controller's list.
\param[  in   ] advertiserDetails  Device details of the advertiser that has to be added to the Controller list
\param[  in   ] block              Type of the operation.
                                   - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleAddRemoveDeviceInPeriodicAdvertiserList(_in_ ClxStack                                     stack,
                                                           _in_ boolean                                      isRemove,
                                                           _user_in_ const ClxBlePeriodicAdvertiserDetails*  advertiserDetails,
                                                           _in_ boolean                                      block);

/**
Removes all the device entries in the Periodic Advertiser list of Controller.

NOTE: Device entries shall not be removed if the command #clxGapBlePeriodicAdvertisingStartSynchronizing execution is still pending.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_CLEAR_ALL_DEVICES_FROM_PERIODIC_ADVERTISER_LIST_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack  Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] block  Type of the operation.
                       - TRUE:  API will be blocked until this command is completed (successfully or failed).
                       - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleClearAllDevicesFromPeriodicAdvertiserList(_in_ ClxStack  stack,
                                                             _in_ boolean   block);

/**
Reads the size of controller's Periodic Advertiser list.

NOTE: The size of the list is not fixed and the controller can change it anytime.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_READ_PERIODIC_ADVERTISER_LIST_SIZE_COMPLETE.
                   The parameter of this indication is of type #ClxGapBleReadPeriodicAdvertiserListSizeComplete.

\param[  in   ] stack               Local device stack handle. A stack object must be created before a GAP API used.
\param[  out  ] advertiserListSize  Maximum size of the controller's Periodic Advertiser List.
\param[  in   ] block               Type of the operation.
                                    - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleReadPeriodicAdvertiserListSize(_in_ ClxStack   stack,
                                                  _user_out_ u1*  advertiserListSize,
                                                  _in_ boolean    block);


#ifdef __cplusplus
}
#endif

#endif  // __GAP_BLE_CENTRAL_API_h__
