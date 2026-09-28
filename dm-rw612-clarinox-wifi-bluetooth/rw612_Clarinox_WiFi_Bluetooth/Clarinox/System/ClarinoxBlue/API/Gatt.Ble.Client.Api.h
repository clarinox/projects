#ifndef __Gatt_Ble_Client_Api_h__
#define __Gatt_Ble_Client_Api_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gatt.Ble.Client.Api.h
* Description         Declares API Functions and Definitions For GattBleClient
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
Passed to #clxGattClientConfigureCharacteristic to enable Notifications for a characteristic.
*/
#define CLX_GATT_CLENT_CONFIGURATION_BIT_NOTIFY                                             0x01

/**
Passed to #clxGattClientConfigureCharacteristic to enable Indications for a characteristic.
*/
#define CLX_GATT_CLENT_CONFIGURATION_BIT_INDICATE                                           0x02


/**
Used Internally.
*/
#define CLX_GATT_CREATE_CLIENT_COMPLETE                                                     0x5f3f


/**
Refer to #clxGattClientBind function.
*/
#define CLX_GATT_CLIENT_BIND_COMPLETE                                                       0x5f00

/**
Refer to #clxGattClientGetListOfServices function.
*/
#define CLX_GATT_CLIENT_GET_LIST_OF_SERVICES_COMPLETE                                       0x5f01

/**
Refer to #clxGattClientDiscoverCharacteristics function.
*/
#define CLX_GATT_CLIENT_DISCOVER_CHARACTERISTICS_COMPLETE                                   0x5f02

/**
Refer to #clxGattClientDiscoverCharacteristicDescriptors function.
*/
#define CLX_GATT_CLIENT_DISCOVER_CHARACTERISTIC_DESCRIPTORS_COMPLETE                        0x5f03

/**
Refer to #clxGattClientRead function.
*/
#define CLX_GATT_CLIENT_READ_COMPLETE                                                       0x5f04

/**
Refer to #clxGattClientReadMultipleCharacteristicsValue function.
*/
#define CLX_GATT_CLIENT_READ_MULTIPLE_CHARACTERISTICS_VALUE_COMPLETE                        0x5f05

/**
Refer to #clxGattClientWrite function.
*/
#define CLX_GATT_CLIENT_WRITE_COMPLETE                                                      0x5f06

/**
Refer to #clxGattGetPendingEvent function.
*/
#define CLX_GATT_GET_PENDING_EVENT_COMPLETE                                                 0x5f07

/**
Refer to #clxGattClientConfigureCharacteristic function.
*/
#define CLX_GATT_CLIENT_CONFIGURE_CHARACTERISTIC_COMPLETE                                   0x5f09

/**
Refer to #clxGattClientGetValueHandle function.
*/
#define CLX_GATT_CLIENT_GET_VALUE_HANDLE_COMPLETE                                           0x5f0a


/**
This indication is received by the application when a GATT Notification or GATT Indications has been received from the remote GATT server to inform the
local client of the modification in a characteristic value. This indication is received only if GATT Notifications or GATT Indications have been previously enabled for the characteristic.
The application shall call #clxGattGetPendingEvent() in order to get the details of the event.
This indication has no arguments.
*/
#define CLX_GATT_CLIENT_EVENT_RECEIVED_INDICATION                                           0x9f00

/**
The GATT write procedure to be used for a write operation
*/
typedef enum ClxGattWriteProcedureEnum
{
    ClxGattWriteProcedure_WriteWithResponse         = 0x00,    /*!< A response to the write request shall be sent by the remote GATT server. The response will determine whether or not
                                                                    the operation has been successful.
                                                                    NOTE: This procedure is used only if the length of data to write is less than or equal to (MTU - 3). Otherwise, the 'Reliable Write'
                                                                    procedure will be used instead. */
    ClxGattWriteProcedure_WriteWithNoResponse       = 0x01,    /*!< No response to the write request will be sent by the remote GATT server. So, there is no way to know whether or not the operation
                                                                    has been successful.
                                                                    This procedure shall be used only if verification of the success of the write operation is not required.
                                                                    NOTE: If the target attribute is a characteristic value, the characteristic shall have a 'Write With No Response' permission.
                                                                    Otherwise, the procedure will be silently ignored by the remote GATT server.
                                                                    NOTE: This procedure is used only if the length of data to write is less than or equal to (MTU - 3). Otherwise, the 'Reliable Write'
                                                                    procedure will be used instead. */
    ClxGattWriteProcedure_ReliableWrite             = 0x02,    /*!< A response to the write request shall be sent by the remote GATT server. The response will determine whether or not
                                                                    the operation has been successful. Furthermore, the integrity of the data written in the remote GATT server will be verified. */
    ClxGattWriteProcedure_SignedWriteWithNoResponse = 0x03     /*!< No response to the signed write request shall be sent by the remote GATT server. So, there is no way to know whether or not the operation
                                                                    has been successful. */
} ClxGattWriteProcedure;

/**
The type of an event received from the remote GATT server
*/
typedef enum ClxGattEventTypeEnum
{
    ClxGattEventType_Notification   = 0x01,    /*!< A notification informs the local client of a modification in a remote characteristic value.
                                                    No confirmation of reception of this event is sent back to the remote server. */
    ClxGattEventType_Indication     = 0x02,    /*!< An indication informs the local client of a modification in a remote characteristic value.
                                                    When the event is delivered to the application, and confirmation message is automatically sent back to the remote server. */
    ClxGattEventType_SignedData     = 0x03     /*!< An indication informs the local client of a signed data from remote server. */
} ClxGattEventType;

/**
Contains the details of a GATT event received from the remote GATT server.
*/
typedef struct ClxGattEventStruct
{
    u2                characteristicValueHandle;    /*!< The handle of the value of a characteristic for which the event has been issued. */
    ClxGattEventType  eventType;                    /*!< Type of the received event. */
    u1*               data;                         /*!< An application-provided buffer containing the new value of the characteristic for which this event has been issued.
                                                         If the value of the characteristic is longer than (MTU - 3), then only the first (MTU - 3) of the value will be returned.
                                                         NOTE: This buffer is never allocated by the stack. */
    u4                dataLength;                   /*!< Length of the data, in bytes. */
} ClxGattEvent;

/**
Contains the details of a GATT service.
*/
typedef struct ClxGattServiceDetailStruct
{
    u2                  firstHandle;    /*!< The handle of the first attribute belonging to this service */
    u2                  lastHandle;     /*!< The handle of the last attribute belonging to this service */
    ClxGattUuid         uuid;           /*!< The UUID of this service */
    ClxGattServiceType  type;           /*!< Type of this service */
} ClxGattServiceDetail;

/**
Contains the details of a GATT characteristic descriptor.
*/
typedef struct ClxGattCharacteristicDescriptorDetailStruct
{
    u2           handle;    /*!< The handle of the descriptor */
    ClxGattUuid  uuid;      /*!< The UUID of the descriptor */
} ClxGattCharacteristicDescriptorDetail;

/**
Contains the details of a GATT characteristic.
*/
typedef struct ClxGattCharacteristicDetailStruct
{
    u2           valueHandle;          /*!< The handle of the ATT attribute containing the value of this characteristic */
    u2           declarationHandle;    /*!< The handle of the ATT attribute containing the declaration of this characteristic */
    u1           properties;           /*!< The properties of this characteristic */
    u2           endHandle;            /*!< The handle of the ATT attribute belonging to this characteristic */
    ClxGattUuid  uuid;                 /*!< The UUID of this characteristic */
} ClxGattCharacteristicDetail;

/**
Contains a buffer into which the value of a GATT characteristic is stored.
*/
typedef struct ClxGattCharacteristicValueStruct
{
    u2   valueHandle;     /*!< The handle of the ATT attribute containing the value of the characteristic */
    u1*  buffer;          /*!< The buffer to store the value of the characteristic */
    u2   bufferLength;    /*!< The length of the buffer */
} ClxGattCharacteristicValue;

/**
Creates an instance of GATT client on the local device. A GATT client may communicate with a single remote GATT server at any given time.

NOTE: If simultaneous access to two or more remote GATT servers is required, a new instance of GATT client must be created per remote GATT server.

NOTE: Before an instance of local GATT client can be used, it shall be bound to a remote GATT server, using #clxGattClientBind.

\param[  in   ] stack         Bluetooth stack handle. A stack object must be created before any other profiles are created.
\param[  in   ] callbackFunc  A pointer to the call-back function which will be called upon reception of indication events related to this handle.

\return Handle to the instance of GATT client. NULL if the creation has failed.
*/
ClxHandle clxGattCreateClient(_in_ ClxStack                    stack,
                              _in_ ClxApplicationCallbackFunc  callbackFunc);

/**
Configures a characteristic for this GATT client. This function may be used to enable/disable Notifications and/or Indications for a characteristic.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CLIENT_CONFIGURE_CHARACTERISTIC_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt                               The handle of the local GATT client.
\param[  in   ] descriptorDetail                   The details of descriptors discovered for the target characteristic. The descriptor details must have been discovered by a previous call to #clxGattClientDiscoverCharacteristicDescriptors.
\param[  in   ] flag                               The bits to write into the Characteristic Client Configuration attribute. If a  bit is set, the corresponding feature will be enabled.Similarly, if a bit is not set, the corresponding feature will be disabled.
\param[  in   ] block                              Indicates mode of operation:
                                                     TRUE: Blocking mode
                                                     FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_GATT_CLIENT_NOT_BOUND: The GATT client is not bound to a remote GATT server
        - #CLX_ERROR_BLE_GATT_WRONG_STATE: Another operation is pending completion on this local GATT client
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_REQUEST_NOT_SUPPORTED: Attribute server does not support the request received from the client.
        - #CLX_ERROR_BLE_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH: The attribute value length is invalid for the operation
*/
ClxResult clxGattClientConfigureCharacteristic(_in_ ClxHandle                                          gatt,
                                               _user_in_ const ClxGattCharacteristicDescriptorDetail*  descriptorDetail,
                                               _in_ u2                                                 flag,
                                               _in_ boolean                                            block);

/**
Data Structure for the indication #CLX_GATT_CLIENT_BIND_COMPLETE
*/
typedef struct ClxGattClientBindCompleteStruct
{
    _user_out_ u2*  negotiatedMtu;    /*!< If the binding has been successful, this argument will contain the actual MTU which has been negotiated with the remote GATT server.
                                           This MTU will be used for both incoming and outgoing ATT packets. The negotiated value may be equal or less than the requested MTU. But, it cannot be less than 23 bytes.
                                           If the binding has not been successful, this argument shall be ignored. */
} ClxGattClientBindComplete;

/**
Binds a local GATT client to a remote GATT server on a connected remote device. If bound successfully, all subsequent inquiries will be made to the bound remote GATT server.
A physical link must already have been established to the remote device. The GAP API #clxGapBleConnectToPeripheral() shall be used to establish a physical link to a remote device in peripheral role.

NOTE: A local GATT client may only communicate with a single remote GATT server at any given time. If simultaneous communications with more than one remote GATT service is required,
one instance of local GATT client is required per each remote GATT server.
NOTE: If the binding has been successful, the local GATT client cannot be unbound, until the physical link to the remote device is disconnected. In such a case, the GATT client is automatically unbound
from the disconnected server, and it may subsequently be bound to the same or different GATT server (as long as there is a physical link to the desired remote device).
NOTE: Two or more local GATT clients cannot be bound to the same remote GATT server.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CLIENT_BIND_COMPLETE.
                   The parameter of this indication is of type #ClxGattClientBindComplete.

\param[  in   ] gatt              The handle of the local GATT client
\param[  in   ] connectionHandle  The handle of the connection to the remote device.
\param[  in   ] requestedMtu      The proposed MTU for the communication with the remote GATT server for both outgoing and incoming packets, in bytes.
                                  The minimum value is 23 bytes.
\param[  out  ] negotiatedMtu     If the binding has been successful, this argument will contain the actual MTU which has been negotiated with the remote GATT server.
                                  This MTU will be used for both incoming and outgoing ATT packets. The negotiated value may be equal or less than the requested MTU. But, it cannot be less than 23 bytes.
                                  If the binding has not been successful, this argument shall be ignored.
\param[  in   ] block             Indicates mode of operation:
                                  TRUE: Blocking mode
                                  FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_CONNECTION_NOT_EXIST: There is no Bluetooth LowEnergy physical link to the remote peripheral
        - #CLX_ERROR_BLE_GATT_DEVICE_ALREADY_BOUND: The remote peripheral is already bound to another local GATT client
        - #CLX_ERROR_BLE_GATT_CLIENT_ALREADY_BOUND: This GATT client is already bound to the remote GATT server
        - #CLX_ERROR_BLE_GATT_NOT_SUPPORTED_BY_LOCAL_ROLE: This operation is not supported by GATT Server role
        - #CLX_ERROR_TIMEOUT_OCCURRED: When there is no response from remote device
*/
ClxResult clxGattClientBind(_in_ ClxHandle               gatt,
                            _in_ ClxBleConnectionHandle  connectionHandle,
                            _in_ u2                      requestedMtu,
                            _user_out_ u2*               negotiatedMtu,
                            _in_ boolean                 block);

/**
Data Structure for the indication #CLX_GATT_CLIENT_GET_LIST_OF_SERVICES_COMPLETE
*/
typedef struct ClxGattClientGetListOfServicesCompleteStruct
{
    _user_out_ ClxGattServiceDetail*  list;                /*!< A application-provided list of objects of type #ClxGattServiceDetail which, on a successful completion, will contain the details of retrieved services.
                                                                If the number of discovered services is more than the size of the list (teh argument listSize), only the first listSize services will be returned.
                                                                The argument numberOfServices will be set to the number of valid entries in the list. */
    _user_out_ u2*                    numberOfServices;    /*!< Number of elements in the list which, on a successful completion, will contain valid service details. */
} ClxGattClientGetListOfServicesComplete;

/**
Retrieves the list of all GATT services existing in the remote GATT server. The local GATT client shall already have been bound to a remote GATT server.
Optionally, the list of services with a specific UUID may be retrieved.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CLIENT_GET_LIST_OF_SERVICES_COMPLETE.
                   The parameter of this indication is of type #ClxGattClientGetListOfServicesComplete.

\param[  in   ] gatt              The handle of the GATT client.
\param[  in   ] uuid              The UUID of services to be retrieved. If set to NULL, all services of the remote GATT server will be retrieved.
\param[  in   ] listSize          The maximum number of services which details can be stored in the user-defined service list. This member cannot be 0.
\param[  out  ] list              A application-provided list of objects of type #ClxGattServiceDetail which, on a successful completion, will contain the details of retrieved services.
                                  If the number of discovered services is more than the size of the list (teh argument listSize), only the first listSize services will be returned.
                                  The argument numberOfServices will be set to the number of valid entries in the list.
\param[  out  ] numberOfServices  Number of elements in the list which, on a successful completion, will contain valid service details.
\param[  in   ] block             Indicates mode of operation: TRUE: Blocking mode. FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_GATT_CLIENT_NOT_BOUND: The GATT client is not bound to a remote GATT server
        - #CLX_ERROR_BLE_GATT_WRONG_STATE: Another operation is pending completion on this local GATT client
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid
        - #CLX_ERROR_BLE_ATT_UNEXPECTED_RESPONSE: When invalid response received from remote device
        - #CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_FOUND: No attribute found within the given attribute handle range.
*/
ClxResult clxGattClientGetListOfServices(_in_ ClxHandle                    gatt,
                                         _user_in_ const ClxGattUuid*      uuid,
                                         _in_ u2                           listSize,
                                         _user_out_ ClxGattServiceDetail*  list,
                                         _user_out_ u2*                    numberOfServices,
                                         _in_ boolean                      block);

/**
Data Structure for the indication #CLX_GATT_CLIENT_DISCOVER_CHARACTERISTICS_COMPLETE
*/
typedef struct ClxGattClientDiscoverCharacteristicsCompleteStruct
{
    _user_out_ ClxGattCharacteristicDetail*  list;                       /*!< A application-provided list of objects of type #ClxGattCharacteristicDetail which, on a successful completion, will contain the details of retrieved characteristics.
                                                                              If the number of discovered characteristics is more than the size of the list (the argument listSize), only the first listSize characteristics will be returned.
                                                                              The argument numberOfCharacteristics will be to the number of valid entries in the list. */
    _user_out_ u2*                           numberOfCharacteristics;    /*!< Number of elements in the list which, on a successful completion, will contain valid characteristic details */
} ClxGattClientDiscoverCharacteristicsComplete;

/**
Retrieves the list of all characteristics of a remote GATT service. The local GATT client shall already have been bound to a remote GATT server.
Optionally, the list of characteristics with a specific UUID may be retrieved.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CLIENT_DISCOVER_CHARACTERISTICS_COMPLETE.
                   The parameter of this indication is of type #ClxGattClientDiscoverCharacteristicsComplete.

\param[  in   ] gatt                     The handle of the GATT client
\param[  in   ] uuid                     The UUID of characteristics to be retrieved. If set to NULL, all characteristics of the remote GATT service will be retrieved.
\param[  in   ] service                  The details of the remote GATT service for which the characteristics are to be discovered.
\param[  in   ] listSize                 The maximum number of characteristics which details can be stored in the user-defined characteristic list. This member cannot be 0.
\param[  out  ] list                     A application-provided list of objects of type #ClxGattCharacteristicDetail which, on a successful completion, will contain the details of retrieved characteristics.
                                         If the number of discovered characteristics is more than the size of the list (the argument listSize), only the first listSize characteristics will be returned.
                                         The argument numberOfCharacteristics will be to the number of valid entries in the list.
\param[  out  ] numberOfCharacteristics  Number of elements in the list which, on a successful completion, will contain valid characteristic details
\param[  in   ] block                    Indicates mode of operation:. TRUE: Blocking mode. FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_GATT_CLIENT_NOT_BOUND: The GATT client is not bound to a remote GATT server
        - #CLX_ERROR_BLE_GATT_WRONG_STATE: Another operation is pending completion on this local GATT client
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid
        - #CLX_ERROR_BLE_GATT_INVALID_CHARACTERISTIC: When firstHandle value of parameter service, is greater than lastHandle.
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_FOUND: No attribute found within the given attribute handle range.
        - #CLX_ERROR_BLE_ATT_UNEXPECTED_RESPONSE: When invalid response received from remote device
*/
ClxResult clxGattClientDiscoverCharacteristics(_in_ ClxHandle                           gatt,
                                               _user_in_ const ClxGattUuid*             uuid,
                                               _user_in_ const ClxGattServiceDetail*    service,
                                               _in_ u2                                  listSize,
                                               _user_out_ ClxGattCharacteristicDetail*  list,
                                               _user_out_ u2*                           numberOfCharacteristics,
                                               _in_ boolean                             block);

/**
Data Structure for the indication #CLX_GATT_CLIENT_DISCOVER_CHARACTERISTIC_DESCRIPTORS_COMPLETE
*/
typedef struct ClxGattClientDiscoverCharacteristicDescriptorsCompleteStruct
{
    _user_out_ ClxGattCharacteristicDescriptorDetail*  list;                                 /*!< A application-provided list of objects of type #ClxGattCharacteristicDescriptorDetail which, on a successful completion, will contain the details of retrieved descriptors.
                                                                                                  If the number of discovered descriptors is more than the size of the list (the argument listSize), only the first listSize descriptors will be returned.
                                                                                                  The argument numberOfCharacteristicDescriptors will be set to the number of valid entries in the list. */
    _user_out_ u2*                                     numberOfCharacteristicDescriptors;    /*!< Number of elements in the list which, on a successful completion, will contain valid descriptor details. */
} ClxGattClientDiscoverCharacteristicDescriptorsComplete;

/**
Retrieves the list of all descriptors of a remote GATT characteristic. The local GATT client shall already have been bound to a remote GATT server.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CLIENT_DISCOVER_CHARACTERISTIC_DESCRIPTORS_COMPLETE.
                   The parameter of this indication is of type #ClxGattClientDiscoverCharacteristicDescriptorsComplete.

\param[  in   ] gatt                               The handle of the GATT client
\param[  in   ] characteristic                     The characteristic for which the list descriptors are to be retrieved.
\param[  in   ] listSize                           The maximum number of descriptors which details can be stored in the user-defined descriptor list.This member cannot be 0.
\param[  out  ] list                               A application-provided list of objects of type #ClxGattCharacteristicDescriptorDetail which, on a successful completion, will contain the details of retrieved descriptors.
                                                   If the number of discovered descriptors is more than the size of the list (the argument listSize), only the first listSize descriptors will be returned.
                                                   The argument numberOfCharacteristicDescriptors will be set to the number of valid entries in the list.
\param[  out  ] numberOfCharacteristicDescriptors  Number of elements in the list which, on a successful completion, will contain valid descriptor details.
\param[  in   ] block                              Indicates mode of operation: TRUE: Blocking mode. FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_GATT_CLIENT_NOT_BOUND: The GATT client is not bound to a remote GATT server
        - #CLX_ERROR_BLE_GATT_WRONG_STATE: Another operation is pending completion on this local GATT client
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid
        - #CLX_ERROR_BLE_GATT_INVALID_CHARACTERISTIC: When valueHandle value of parameter characteristic, is greater than endHandle.
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_FOUND: No attribute found within the given attribute handle range.
        - #CLX_ERROR_BLE_ATT_UNEXPECTED_RESPONSE: When invalid response received from remote device
*/
ClxResult clxGattClientDiscoverCharacteristicDescriptors(_in_ ClxHandle                                     gatt,
                                                         _user_in_ const ClxGattCharacteristicDetail*       characteristic,
                                                         _in_ u2                                            listSize,
                                                         _user_out_ ClxGattCharacteristicDescriptorDetail*  list,
                                                         _user_out_ u2*                                     numberOfCharacteristicDescriptors,
                                                         _in_ boolean                                       block);

/**
Data Structure for the indication #CLX_GATT_CLIENT_READ_COMPLETE
*/
typedef struct ClxGattClientReadCompleteStruct
{
    _user_out_ u1*  buffer;        /*!< A caller-provided buffer which, on a successful completion, will contain the value of the attribute.
                                        The buffer shall be not modified or deleted until this command is complete. */
    _user_out_ u4*  readLength;    /*!< A call-provided variable which, on a successful completion, will contain the actual length of data read. This may be less than or equal to
                                        the buffer size. */
} ClxGattClientReadComplete;

/**
Reads the value of an attribute from the remote GATT server. The handle of the attribute must be known.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CLIENT_READ_COMPLETE.
                   The parameter of this indication is of type #ClxGattClientReadComplete.

\param[  in   ] gatt        The handle of the GATT client.
\param[  in   ] handle      The handle of the attribute to be read
\param[  out  ] buffer      A caller-provided buffer which, on a successful completion, will contain the value of the attribute.
                            The buffer shall be not modified or deleted until this command is complete.
\param[  in   ] bufferSize  The size of the caller-provided buffer, in bytes.
\param[  in   ] offset      The zero-based offset of the first byte of the attribute value to be read.
                            If the offset does not exist in the attribute value, an error will be returned.
                            NOTE: Reading the value of an attribute from a non-zero offset may not be supported for all attributes.
                            Generally, reading from a non-zero offset is only used to read the rest of the value of a characteristic with a long value.
\param[  out  ] readLength  A call-provided variable which, on a successful completion, will contain the actual length of data read. This may be less than or equal to
                            the buffer size.
\param[  in   ] block       Indicates mode of operation:
                            TRUE: Blocking mode
                            FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_GATT_CLIENT_NOT_BOUND: The GATT client is not bound to a remote GATT server
        - #CLX_ERROR_BLE_GATT_WRONG_STATE: Another operation is pending completion on this local GATT client
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_FOUND: No attribute found within the given attribute handle range.
        - #CLX_ERROR_BLE_ATT_READ_NOT_PERMITTED: The attribute cannot be read.
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_ENCRYPTION: The attribute requires encryption before it can be read.
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_AUTHENTICATION: The attribute requires authentication before it can be read
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_AUTHORIZATION: The attribute requires authorization before it can be read
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE: The Encryption Key Size used for encrypting this link is insufficient
        - #CLX_ERROR_BLE_ATT_INVALID_OFFSET: Offset specified was past the end of the attribute.
        - #CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_LONG: The attribute cannot be read using the offset
        - #CLX_ERROR_BLE_ATT_UNEXPECTED_RESPONSE: When invalid response received from remote device
*/
ClxResult clxGattClientRead(_in_ ClxHandle  gatt,
                            _in_ u2         handle,
                            _user_out_ u1*  buffer,
                            _in_ u4         bufferSize,
                            _in_ u4         offset,
                            _user_out_ u4*  readLength,
                            _in_ boolean    block);

/**
Data Structure for the indication #CLX_GATT_CLIENT_READ_MULTIPLE_CHARACTERISTICS_VALUE_COMPLETE
*/
typedef struct ClxGattClientReadMultipleCharacteristicsValueCompleteStruct
{
    _user_out_ u1*  buffer;        /*!< A caller-provided buffer which, on a successful completion, will contain the values of the characteristics concatenated together.
                                        The buffer shall not be modified or deleted until this command is complete. */
    _user_out_ u4*  readLength;    /*!< A call-provided variable which, on a successful completion, will contain the actual length of data read. This may be less than or equal to
                                        the buffer size. However, it cannot be more than (MTU - 1). */
} ClxGattClientReadMultipleCharacteristicsValueComplete;

/**
Reads the value of multiple characteristics from the remote GATT server. The values will be concatenated and received in one single buffer.
It is assumed that the application knows the size of each characteristic value. The values in the returned buffers will be in the same order as
the input characteristics.

NOTE : This API command may be used to read fixed-length characteristic values. If the length of each characteristic value is not known, the API command
#clxGattClientRead shall be used instead.

NOTE: A maximum of (MTU - 1) bytes of total values may be returned by this command (where MTU is the negotiated MTU returned by #clxGattClientBind() command).
If the concatenation of characteristic values results in a size more than (MTU - 1), then only the first (MTU - 1) bytes will be returned.

NOTE: If the value of any of the characteristic cannot be read for any reason (e.g. No read-able permission, ...), the entire operation will fail.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CLIENT_READ_MULTIPLE_CHARACTERISTICS_VALUE_COMPLETE.
                   The parameter of this indication is of type #ClxGattClientReadMultipleCharacteristicsValueComplete.

\param[  in   ] gatt                     The handle of the GATT client
\param[  in   ] numberOfCharacteristics  Number of elements in the list which, on a successful completion, will contain valid characteristic details
\param[  in   ] list                     The list of the characteristics which values are to be retrieved. The argument numberOfCharacteristics shall be set to the number of characteristics.
                                         The order of characteristics in the list determines the order of values in the returned buffer.
                                         NOTE: The number of characteristics in this operation is limited to a maximum of (MTU - 1)/2 where MTU is the negotiated MTU as returned by #clxGattClientBind.
                                         If there are more characteristics in the list than this limit, then the list will be truncated.
                                         (Example: If MTU is 23 bytes, then values of a maximum of 11 descriptors may be retrieved).

\param[  in   ] bufferSize               The size of the caller-provided buffer, in bytes.
                                         NOTE: If the buffer is larger than (MTU - 1) bytes, only the first (MTU - 1) bytes of the buffer will be used for the operation.
\param[  out  ] buffer                   A caller-provided buffer which, on a successful completion, will contain the values of the characteristics concatenated together.     
                                         The buffer shall not be modified or deleted until this command is complete.
\param[  out  ] readLength               A call-provided variable which, on a successful completion, will contain the actual length of data read. This may be less than or equal to the buffer size. However, it cannot be more than (MTU - 1).
\param[  in   ] block                    Indicates mode of operation: TRUE: Blocking mode. FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_GATT_CLIENT_NOT_BOUND: The GATT client is not bound to a remote GATT server
        - #CLX_ERROR_BLE_GATT_WRONG_STATE: Another operation is pending completion on this local GATT client
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_FOUND: No attribute found within the given attribute handle range.
        - #CLX_ERROR_BLE_ATT_READ_NOT_PERMITTED: The attribute cannot be read.
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_ENCRYPTION: The attribute requires encryption before it can be read.
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_AUTHENTICATION: The attribute requires authentication before it can be read
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_AUTHORIZATION: The attribute requires authorization before it can be read
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE: The Encryption Key Size used for encrypting this link is insufficient
        - #CLX_ERROR_BLE_ATT_UNEXPECTED_RESPONSE: When invalid response received from remote device
*/
ClxResult clxGattClientReadMultipleCharacteristicsValue(_in_ ClxHandle                                gatt,
                                                        _in_ u2                                       numberOfCharacteristics,
                                                        _user_in_ const ClxGattCharacteristicDetail*  list,
                                                        _in_ u4                                       bufferSize,
                                                        _user_out_ u1*                                buffer,
                                                        _user_out_ u4*                                readLength,
                                                        _in_ boolean                                  block);

/**
Writes a new value for an attribute in the remote GATT server. The handle of the attribute must be known.

For the purpose of write operations, an attribute has either a variable-length value or a fixed-length variable. This information
is assumed to be known by the application.

If the target attribute has a variable-length value, the following rules apply:
- If the value to write is longer than the maximum length of the attribute value, the write operation will fail.
- If the value to write is shorter than the maximum length of the attribute value, the current value of the attribute in the GATT server will
be replaced by the be value. Therefore, if the length of new value is 0, the current value of the attribute will be completely removed.

If the target attribute has a fixed-length value, the following rules apply:
- If the value to write is longer than the length of the attribute value, the write operation will fail.
- If the value to write is shorter than the length of the attribute value, The first part of the value (up to the length of the data to be written) will
be replaced. The rest of the value will remain unchanged.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CLIENT_WRITE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt        The handle of the GATT client
\param[  in   ] handle      The handle of the attribute to write
\param[  in   ] procedure   The Procedure to use for the write operation.
                            NOTE: This argument is ignored if the length of the data to write is not suitable for this procedure.
                            Please refer to #ClxGattWriteProcedure documentation for more details.
\param[  in   ] data        A caller-provided buffer which contains the new value of the attribute. This argument may be NULL only if no data needs to be written.
                            The buffer shall not be modified or deleted until this command is complete.
\param[  in   ] dataLength  Length of the new value. It may be 0 only if data is NULL.
\param[  in   ] block       Indicates mode of operation:
                            TRUE: Blocking mode
                            FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_GATT_CLIENT_NOT_BOUND: The GATT client is not bound to a remote GATT server
        - #CLX_ERROR_BLE_GATT_WRONG_STATE: Another operation is pending completion on this local GATT client
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_FOUND: No attribute found within the given attribute handle range.
        - #CLX_ERROR_BLE_ATT_WRITE_NOT_PERMITTED: The attribute cannot be written.
        - #CLX_ERROR_BLE_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH: The attribute value length is invalid for the operation
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_ENCRYPTION: The attribute requires encryption before it can be read.
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_AUTHENTICATION: The attribute requires authentication before it can be read
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_AUTHORIZATION: The attribute requires authorization before it can be read
        - #CLX_ERROR_BLE_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE: The Encryption Key Size used for encrypting this link is insufficient
        - #CLX_ERROR_BLE_ATT_INVALID_OFFSET: Offset specified was past the end of the attribute.
        - #CLX_ERROR_BLE_ATT_UNEXPECTED_RESPONSE: When invalid response received from remote device
*/
ClxResult clxGattClientWrite(_in_ ClxHandle              gatt,
                             _in_ u2                     handle,
                             _in_ ClxGattWriteProcedure  procedure,
                             _user_in_ const u1*         data,
                             _in_ u4                     dataLength,
                             _in_ boolean                block);

/**
Data Structure for the indication #CLX_GATT_GET_PENDING_EVENT_COMPLETE
*/
typedef struct ClxGattGetPendingEventCompleteStruct
{
    _user_out_ ClxGattEvent*  event;     /*!< A caller-provided object of type ClxGattEvent which, on a successful completion, will contain the details of the received event.
                                              This argument cannot be NULL. */
    _user_out_ u1*            buffer;    /*!< A caller-provided buffer which, on a successful completion, will contain the new value of the characteristic for which this event has been issued.
                                              NOTE: A maximum (MTU - 3) bytes of the characteristic value may be returned, where MTU is the negotiated MTU returned by #clxGattClientBind. */
} ClxGattGetPendingEventComplete;

/**
Pulls a notification, which has been received from the remote GATT server, out of the queue and returns its details to the application.

NOTE: This command shall be issued for each #CLX_GATT_CLIENT_EVENT_RECEIVED_INDICATION indication which has been received. The application should
issue this command as soon as possible. Otherwise, the incoming notification queue may become full and new notifications may be dropped.

NOTE: If the physical link to the remote GATT server device is lost, all pending events in the queue will be automatically removed.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_GET_PENDING_EVENT_COMPLETE.
                   The parameter of this indication is of type #ClxGattGetPendingEventComplete.

\param[  in   ] gatt        The handle of the GATT client.
\param[  out  ] event       A caller-provided object of type ClxGattEvent which, on a successful completion, will contain the details of the received event.
                            This argument cannot be NULL.
\param[  out  ] buffer      A caller-provided buffer which, on a successful completion, will contain the new value of the characteristic for which this event has been issued.
                            NOTE: A maximum (MTU - 3) bytes of the characteristic value may be returned, where MTU is the negotiated MTU returned by #clxGattClientBind.
\param[  in   ] bufferSize  Size of the buffer.
\param[  in   ] block       Indicates mode of operation:
                            TRUE: Blocking mode
                            FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_GATT_NO_EVENT_PENDING: There is no event pending
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid
*/
ClxResult clxGattGetPendingEvent(_in_ ClxHandle            gatt,
                                 _user_out_ ClxGattEvent*  event,
                                 _user_out_ u1*            buffer,
                                 _in_ u4                   bufferSize,
                                 _in_ boolean              block);

/**
Data Structure for the indication #CLX_GATT_CLIENT_GET_VALUE_HANDLE_COMPLETE
*/
typedef struct ClxGattClientGetValueHandleCompleteStruct
{
    _user_out_ u2*              valueHandle;
} ClxGattClientGetValueHandleComplete;

/**
Retrieves the characteristic value handle from remote GATT server. The local GATT client shall already have been bound to a remote GATT server.

\param[  in   ] gatt                GATT client handle.
\param[  in   ] serviceUuid         Service UUID.
\param[  in   ] characteristicUuid  Characteristic UUID.
\param[  in   ] valueHandle         A caller provided variable to retrieve the characteristic value handle.
\param[  in   ] block               Indicates mode of operation:
                                        TRUE: Blocking mode
                                        FALSE: Non-blocking mode

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CLIENT_GET_VALUE_HANDLE_COMPLETE.
                   The parameter of this indication is of type #ClxGattGetPendingEventComplete.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
        - #CLX_ERROR_BLE_GATT_CLIENT_NOT_BOUND: The GATT client is not bound to a remote GATT server
        - #CLX_ERROR_BLE_GATT_WRONG_STATE: Another operation is pending completion on this local GATT client
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid
        - #CLX_ERROR_BLE_ATT_UNEXPECTED_RESPONSE: When invalid response received from remote device
        - #CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_FOUND: No attribute found within the given attribute handle range.
        - #CLX_ERROR_BLE_GATT_INVALID_CHARACTERISTIC: When firstHandle value of parameter service, is greater than lastHandle.
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
*/
ClxResult clxGattClientGetValueHandle(_in_ ClxHandle                gatt,
                                      _user_in_ const ClxGattUuid*  serviceUuid,
                                      _user_in_ const ClxGattUuid*  characteristicUuid,
                                      _user_out_ u2*                valueHandle,
                                      _in_ boolean                  block);

#ifdef __cplusplus
}
#endif

#endif // __Gatt_Ble_Client_Api_h__

