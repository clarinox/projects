#ifndef __Gap_Ble_4_2_Api_h__
#define __Gap_Ble_4_2_Api_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gap.Ble.4.2.Api.h
* Description         Declares API Functions and Definitions For Gap Ble 4.2
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/
#include "Gap.Ble.Central.Api.h"
#include "Gap.Ble.Peripheral.Api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
Refer to #clxGapBleStartScan function.
*/
#define CLX_GAP_BLE_START_SCAN_COMPLETE                                                     0x5501

/**
Refer to #clxGapBleStopScan function.
*/
#define CLX_GAP_BLE_STOP_SCAN_COMPLETE                                                      0x5502

/**
Refer to #clxGapBleConnectToPeripheral function.
*/
#define CLX_GAP_BLE_CONNECT_TO_PERIPHERAL_COMPLETE                                          0x5504

/**
Refer to #clxGapBleStartAdvertising function.
*/
#define CLX_GAP_BLE_START_ADVERTISING_COMPLETE                                              0x5506

/**
Refer to #clxGapBleStopAdvertising function.
*/
#define CLX_GAP_BLE_STOP_ADVERTISING_COMPLETE                                               0x5507

/**
This indication is received when there is a physical-layer (ACL) connection established 
from a remote device (Central Role).
The parameter of this indication is of type #ClxGapBleConnectionEstablishedByRemoteCentralIndication.
*/
#define CLX_GAP_BLE_CONNECTION_ESTABLISHED_BY_REMOTE_CENTRAL_INDICATION                     0x9500

/**
This indication is received during scanning procedure, which indicates 
a device has been discovered in the vicinity. This object will be valid until the next #clxGapBleStartScan 
API function call.
The parameter of this indication is of type #ClxGapBleDeviceAdvertisingIndication.
*/
#define CLX_GAP_BLE_DEVICE_ADVERTISING_INDICATION                                           0x9502

/**
Data Structure for the indication #CLX_GAP_BLE_CONNECTION_ESTABLISHED_BY_REMOTE_CENTRAL_INDICATION
*/
typedef struct ClxGapBleConnectionEstablishedByRemoteCentralIndicationStruct
{
    ClxBleConnectionDetails  connectionDetails;
} ClxGapBleConnectionEstablishedByRemoteCentralIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_DEVICE_ADVERTISING_INDICATION
*/
typedef struct ClxGapBleDeviceAdvertisingIndicationStruct
{
    ClxBleAdvertisingType  advertisingType;
    ClxBleBdAddress        deviceAddr;
    ClxBleAdvertisingData  advertisingData;
    s1                     rssi;
} ClxGapBleDeviceAdvertisingIndication;

typedef struct ClxBleAddAdvertisingDataFieldCompleteStruct
{
    _user_out_ ClxBleAdvertisingData*  obj;    /*!< User buffer for advertising the local device's custom data */
} ClxBleAddAdvertisingDataFieldComplete;

/**
Used for initializing the custom advertising data field. For the details of latest version of the fields see assigned numbers Generic Access Profile; 
https://www.bluetooth.com/specifications/assigned-numbers/Generic-Access-Profile  Below list shows the type values and descriptions;  
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
- 0x3D  3D Information Data 
- 0xFF  Manufacturer Specific Data

\param[  out  ] obj            User buffer for advertising the local device's custom data
\param[  in   ] type           Advertising data type as described above
\param[  in   ] payload        The data being advertised
\param[  in   ] payloadLength  The length of custom data

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
*/
boolean clxBleAddAdvertisingDataField(_user_out_ ClxBleAdvertisingData*  obj,
                                        _in_ u1                            type,
                                        _user_in_ const u1*                payload,
                                        _in_ u1                            payloadLength);

typedef struct ClxBleFindAdvertisingDataFieldCompleteStruct
{
    _user_out_ u1*  payloadLength;    /*!< The length of custom data */
} ClxBleFindAdvertisingDataFieldComplete;

/**
Used for searching the availability of custom data.

\param[  in   ] obj            User buffer for advertising the local device's custom data
\param[  in   ] type           Advertising data type as described above
\param[  out  ] payloadLength  The length of custom data

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
*/
const u1* clxBleFindAdvertisingDataField(_user_in_ const ClxBleAdvertisingData*  obj,
                                         _in_ u1                                 type,
                                         _user_out_ u1*                          payloadLength);

/**
Starts scanning from the local device. If any Bluetooth devices in the vicinity are found, then 
#CLX_GAP_BLE_DEVICE_ADVERTISING_INDICATION message will be received via the callback function. A name 
request will be performed for each new discovered device which is not already in the pairing list.

Optionally, a filter may be used to limit the discovered devices to a specific device class (or a combination of device classes).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_START_SCAN_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack             Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] localAddressType  Own address type: local device's address type.
\param[  in   ] leScanType        0x00 Passive scan, 0x01 Active Scan. 
                                  Passive scan: The Peripheral advertising data only received. 
                                  Active scan: The Peripheral advertising data and scan response data will be received.
\param[  in   ] leScanInterval    Time interval between scans. Range: 0x0004 to 0x4000. Equivalent time Range: 2.5 ms to 10.24 seconds.
\param[  in   ] leScanWindow      Duration of scan, less than or equal to scan interval. Range: 0x0004 to 0x4000. Equivalent time Range: 2.5 ms to 10.24 seconds.
\param[  in   ] useWhitelist      Whether or not to use whitelist (FALSE = don't use, TRUE = use)
\param[  in   ] filterDuplicate   whether or not to enable scan filter duplicates (FALSE = disable, TRUE = enabled)
\param[  in   ] block             Type of the operation. 
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

        - CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleStartScan(_in_ ClxStack              stack,
                             _in_ ClxBleOwnAddressMode  localAddressType,
                             _in_ BleScanType           leScanType,
                             _in_ u4                    leScanInterval,
                             _in_ u4                    leScanWindow,
                             _in_ boolean               useWhitelist,
                             _in_ boolean               filterDuplicate,
                             _in_ boolean               block);

/**
Stop scanning from the local device. This operation will stop any on-going scanning operation, as has been initiated by #clxGapBleStartScan

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_STOP_SCAN_COMPLETE.
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

        - CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleStopScan(_in_ ClxStack  stack,
                            _in_ boolean   block);

/**
Data Structure for the indication #CLX_GAP_BLE_CONNECT_TO_PERIPHERAL_COMPLETE
*/
typedef struct ClxGapBleConnectToPeripheralCompleteStruct
{
    _user_out_ ClxBleConnectionDetails*  connectionDetails;    /*!< Connection details */
} ClxGapBleConnectToPeripheralComplete;

/**
Establish an instance of a connection to remote device.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_CONNECT_TO_PERIPHERAL_COMPLETE.
                   The parameter of this indication is of type #ClxGapBleConnectToPeripheralComplete.

\param[  in   ] stack                         Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] performScan                   If TRUE, The stack will perform a scan to discover the peer device and turn-on the duplicate filter to avoid redundant packets. If found, the connection procedure will go ahead.
                                              Otherwise the parameter is FALSE, The connection procedure is started directly.
                                              If this argument is TRUE, peerAddress CANNOT be NULL. The same timeout value (connectionTimeoutValue) which applies to the connection procedure also applies to the scan procedure. If the timer expires and
                                              the peer device has not been found, this command will complete with the error #CLX_ERROR_TIMEOUT_OCCURRED. However, if the peer device is found, the timer will restarted before the connection procedure is started.
                                              NOTE : Set this argument to TRUE only if you are trying to connect to a peer device using its identity address while the peer is currently using a resolvable private address.
                                              The scan procedure will make sure that the current private address of the peer device will be discovered. In other cases, This scan procedure does not serve any purpose.
\param[  in   ] scanInterval                  Value to define how frequently the controller should scan. The value range starts from 0x0004 to 0x4000.
\param[  in   ] scanWindow                    Value to define how long the controller should scan. The value range starts from 0x0004 to 0x4000. The value of scan window should not be greater than the value of scan interval. 
                                              If both are set to the same value, lthe scanning should happen continuously.
\param[  in   ] peerAddress                   Address to directly connect to (set to NULL if not using directed connection). The address type shall be one of the following:
                                              #ClxBleAddressType_Public : The address is the public address of the remote device. Directly use this address for connection.
                                              #ClxBleAddressType_Random : The address is the random address of the remote device. Directly use this address for connection.
                                              #ClxBleAddressType_PublicIdentity : The address is the public address of the remote device.
                                              Connect using the latest resolvable private address of the remote device. If no such an address exists, the command completes with the error CLX_ERROR_INVALID_REQUEST.
                                              #ClxBleAddressType_StaticIdentity : The address is the static address of the remote device.
                                              Connect using the latest resolvable private address of the remote device. If no such an address exists, the command completes with the error CLX_ERROR_INVALID_REQUEST.
\param[  in   ] localAddressType              Own address type: local device's address type.
\param[  in   ] minimumConnectionInterval     Minimum interval value for the connection. The value range starts from 0x0006 to 0x0c80.
\param[  in   ] maximumConnectionInterval     Maximum interval value for the connection. The value range starts from 0x0006 to 0x0c80. The maximum connection interval value should not be less than minimal value.
\param[  in   ] connectionLatency             Value to define the slave latency for the connection. The value range starts from 0x0000 to 0x01F3
\param[  in   ] supervisionTimeout            Value to define the link supervision timeout for the connection (multiples of 10 milliseconds). The value range starts from 0x000a to 0x0c80.
\param[  in   ] minimumConnectionEventLength  Minimum length of connection event. The value range starts from 0x0000 to 0xffff.
\param[  in   ] maximumConnectionEventLength  Maximum length of connection event. The value range starts from 0x0000 to 0xffff. This value should not be less than minimum connection event length.
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
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_ERROR_TIMEOUT_OCCURRED: Connection procedure has been cancelled as the connection timer expired.
        - CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid.
        - CLX_ERROR_BLE_SMP_IR_PARAMETER_NOT_CONFIGURED: BSP Configuration parameter Ble.Smp.IR is not configured.
                                                          (Applicable only if 'localAddressType' parameter is ClxBleOwnAddressMode_PrivateResolvable)
        - CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleConnectToPeripheral(_in_ ClxStack                        stack,
                                       _in_ boolean                         performScan,
                                       _in_ u2                              scanInterval,
                                       _in_ u2                              scanWindow,
                                       _user_in_ const ClxBleBdAddress*     peerAddress,
                                       _in_ ClxBleOwnAddressMode            localAddressType,
                                       _in_ u2                              minimumConnectionInterval,
                                       _in_ u2                              maximumConnectionInterval,
                                       _in_ u2                              connectionLatency,
                                       _in_ u2                              supervisionTimeout,
                                       _in_ u2                              minimumConnectionEventLength,
                                       _in_ u2                              maximumConnectionEventLength,
                                       _user_out_ ClxBleConnectionDetails*  connectionDetails,
                                       _in_ u4                              connectionTimeoutValue,
                                       _in_ boolean                         block);

/**
Start advertising is used to make local device discoverable/connectable. Advertising settings are applied during enabling advertising.
When the Peripheral starts the advertising, the controller periodically sends advertising packets. The size of advertising packet has 31 data bytes available to use.
The Central device may listen on advertising channels and receive these packets.

advertisingIntervalMin and advertisingIntervalMax parameters are ignored if the advertisingType is directed advertising (ClxBleAdvertisingType_ConnectableDirected).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_START_ADVERTISING_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                     Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] advertisingIntervalMin    0x0020 to 0x4000, interval = advertising_interval_min * 0.625msec.
                                          For non-directed advertising this value should be less than or equal to advertisingIntervalMax.
                                          The minimum for this value is 160 for  ClxBleAdvertisingType_ScannableUndirected, for other undirected scan types minimum value can be 32.
                                          The maximum value for all cases can be 16384
\param[  in   ] advertisingIntervalMax    0x0020 to 0x4000, interval = advertising_interval_max * 0.625msec. For non-directed advertising. This value should be more than or equal to advertisingIntervalMin.
\param[  in   ] advertisingType           0 - connectable undirected advertising, 0x01- connectable directed, 0x02 - scannable undirected advertising, 0x03 - non-connectable undirected advertising
\param[  in   ] localAddressType          Own address type: local device's address type.
\param[  in   ] peerAddress               Address to directly advertise to (set to 0 if not using directed advertising)
\param[  in   ] advertisingChannelsToUse  Selects the advertising channel to be used when transmitting the advertising packets. May be a OR-ed combination of the following values:
                                            #CLX_BLE_ADVERTISING_CHANNEL_37,
                                            #CLX_BLE_ADVERTISING_CHANNEL_38,
                                            #CLX_BLE_ADVERTISING_CHANNEL_39,
                                          Set to #CLX_BLE_ALL_ADVERTISING_CHANNELS to select all channels.
\param[  in   ] advertisingFilterPolicy   Filter policy applied to remote devices;
                                          0x00: Allow scan and connection request from anyone,
                                          0x01: Allow scan from whitelist only, allow connection request from any,
                                          0x02: Allow scan request from any device, allow connection request from white list devices only,
                                          0x03: Allow scan request and connection request from white list only
\param[  in   ] advertisingData           Data to be sent in advertising packets
\param[  in   ] block                     Type of the operation. 
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

        - CLX_ERROR_BLE_REMOTE_DEVICE_NOT_FOUND_BY_IDENTITY_ADDRESS: If the given peer address cannot be found in paired device details list.
                                                                      (Applicable only if 'advertisingType' is ClxBleAdvertisingType_ConnectableDirected and localAddressType is ClxBleOwnAddressMode_PrivateResolvable)
        - CLX_ERROR_INVALID_COMMAND_PARAMETER: One or more of provided arguments are invalid.
        - CLX_ERROR_BLE_SMP_IR_PARAMETER_NOT_CONFIGURED: BSP Configuration parameter Ble.Smp.IR is not configured.
                                                          (Applicable only if 'localAddressType' parameter is ClxBleOwnAddressMode_PrivateResolvable)
        - CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleStartAdvertising(_in_ ClxStack                           stack,
                                    _in_ u4                                 advertisingIntervalMin,
                                    _in_ u4                                 advertisingIntervalMax,
                                    _in_ ClxBleAdvertisingType              advertisingType,
                                    _in_ ClxBleOwnAddressMode               localAddressType,
                                    _user_in_ const ClxBleBdAddress*        peerAddress,
                                    _in_ u1                                 advertisingChannelsToUse,
                                    _in_ ClxBleAdvertisingFilterPolicy      advertisingFilterPolicy,
                                    _user_in_ const ClxBleAdvertisingData*  advertisingData,
                                    _in_ boolean                            block);

/**
Stop advertising is used to make device non-discoverable and non-connectable

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_STOP_ADVERTISING_COMPLETE.
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

        - CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleStopAdvertising(_in_ ClxStack  stack,
                                   _in_ boolean   block);


#ifdef __cplusplus
}
#endif



#endif // __Gap_Ble_4_2_Api_h__
