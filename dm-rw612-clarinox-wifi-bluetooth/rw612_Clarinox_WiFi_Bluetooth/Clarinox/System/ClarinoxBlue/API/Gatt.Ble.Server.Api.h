#ifndef __Gatt_Ble_Server_Api_h__
#define __Gatt_Ble_Server_Api_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gatt.Ble.Server.Api.h
* Description         Declares API Functions and Definitions For GattBleServer
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
Used Internally.
*/
#define CLX_GATT_CREATE_SERVER_COMPLETE                                                     0x603F

/** 
Indicates completion of #clxGattRegisterLocalService function execution 
*/
#define CLX_GATT_REGISTER_LOCAL_SERVICE_COMPLETE                                            0x6000

/** 
Indicates completion of #clxGattWriteLocal function execution 
*/
#define CLX_GATT_WRITE_LOCAL_COMPLETE                                                       0x6001

/** 
Indicates completion of #clxGattReadLocal function execution 
*/
#define CLX_GATT_READ_LOCAL_COMPLETE                                                        0x6002

/**
Refer to #clxGattEncodeLocalCharacteristicValue function.
*/
#define CLX_GATT_ENCODE_LOCAL_CHARACTERISTIC_VALUE_COMPLETE                                 0x6003

/**
Refer to #clxGattDecodeLocalCharacteristicValue function.
*/
#define CLX_GATT_DECODE_LOCAL_CHARACTERISTIC_VALUE_COMPLETE                                 0x6004

/**
Refer to #clxGattUnregisterLocalService function.
*/
#define CLX_GATT_UNREGISTER_LOCAL_SERVICE_COMPLETE                                          0x6005

/**
This indication is received when a client used #clxGattWriteLocal for updating the remote 
characteristic value. The parameter of this indication will be of type #ClxGattValueUpdatedIndicationStruct. 
It is only applicable to server role. The user can read the data by using a #clxGattReadLocal function
*/
#define CLX_GATT_VALUE_UPDATED_INDICATION                                                   0xA002

/**
This indication is received when a client negotiates MTU with server
The parameter of this indication is of type #ClxGattMtuValueUpdatedIndication.
*/
#define CLX_GATT_MTU_VALUE_UPDATED_INDICATION                                               0xA003

/**
This indication is received when a client makes a request to read the value of a characteristics from server
The parameter of this indication is of type #ClxGattValueReadIndication.
*/
#define CLX_GATT_VALUE_READ_INDICATION                                                      0xA004

/** Data Structure for the indication #CLX_GATT_VALUE_UPDATED_INDICATION */
typedef struct ClxGattValueUpdatedIndicationStruct
{
    ClxBleBdAddress       remoteDevice;
    u2                    characteristicHandle;
    u2                    valueLength;
    const u1*             characteristicValueBuffer;
} ClxGattValueUpdatedIndication;

/**
Data Structure for the indication #CLX_GATT_MTU_VALUE_UPDATED_INDICATION
*/
typedef struct ClxGattMtuValueUpdatedIndicationStruct
{
    ClxBleBdAddress  remoteDevice;
    u2               negotiatedMtu;
} ClxGattMtuValueUpdatedIndication;

/**
Data Structure for the indication #CLX_GATT_VALUE_READ_INDICATION
*/
typedef struct ClxGattValueReadIndicationStruct
{
    ClxBleBdAddress  remoteDevice;
    u2               characteristicHandle;
    u2               valueLength;
    u2               offset;
} ClxGattValueReadIndication;

/** Data Structure for the indication #CLX_GATT_REGISTER_LOCAL_SERVICE_COMPLETE */
typedef struct ClxGattRegisterLocalServiceCompleteStruct 
{
    _user_out_ u2*     serviceHandleBase;
} ClxGattRegisterLocalServiceComplete;



/**
Creates a handle to an instance of Gatt generic attribute profile on the server device. Only a single instance of Gatt server
is allowed. Gatt server instance is capable of providing multiple services to multiple clients simultaneously.

\param[  in   ] stack             Bluetooth stack handle. A stack object must be created before any other profiles are created.
\param[  in   ] callbackFunc      A pointer to the call-back function which will be called upon reception of indication events related to this handle.
\return ClxHandle Gatt profile handle. This handle must be used for any further operations on this server.
*/
ClxHandle clxGattCreateServer(_in_ ClxStack                     stack,
                              _in_ ClxApplicationCallbackFunc   callbackFunc);

/**
Registers a local service for a given Bluetooth Low Energy Gatt server. Before registering a service, Gatt server must have been created.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_REGISTER_LOCAL_SERVICE_COMPLETE.
                   The parameter of this indication is of type #ClxGattRegisterLocalServiceComplete.

\param[  in   ] gatt               Gatt server handle.
\param[  in   ] serviceInterface   Service interface for the local Gatt service.
\param[  in   ] configList         Any configuration parameters that are to be passed to services.
\param[  out  ] serviceHandleBase  Service handle base index.
\param[  in   ] block              Type of the operation.
                                   - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to Gatt was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_REQUEST: If GATT Server is not supported by/enabled in stack.
*/
ClxResult clxGattRegisterLocalService(_in_ ClxHandle                                  gatt,
                                      _user_in_ const ClxBleGattServiceInterface*     serviceInterface,
                                      _user_in_ const ClxConfigList*                  configList,
                                      _user_out_ u2*                                  serviceHandleBase,
                                      _in_ boolean                                    block);

/**
Write into a local characteristics value. If the client notification/indication feature is set, then this value will be automatically available to the clients of this service.
If the characteristics has notify or indicate attribute set then attribute value change will be notified/indicated to the registered client.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_WRITE_LOCAL_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt                       Gatt server handle.
\param[  in   ] characteristicHandle       Handle for the characteristic to read.
\param[  in   ] characteristicValue        Buffer to write to the characteristic value
\param[  in   ] characteristicValueLength  Length of the buffer to write to the characteristic value.
\param[  in   ] writeTimeoutValue          Timeout value (in milliseconds) to write the characteristic value and sending updated value to central when notification/indication configured.
\param[  in   ] block                      Type of the operation.
                                            - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                            - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to Gatt was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_REQUEST: If GATT Server is not supported by/enabled in stack
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH: The attribute value length is invalid for the operation
        - #CLX_ERROR_BLE_ATT_WRITE_NOT_PERMITTED: The attribute cannot be written
        - #CLX_ERROR_TIMEOUT_OCCURRED: Characteristic write done, but timeout occurred for sending notification/indication due to no response from remote device
*/
ClxResult clxGattWriteLocal(_in_ ClxHandle          gatt,
                            _in_ u2                 characteristicHandle,  
                            _user_in_ const u1*     characteristicValue,
                            _in_ ClxSize            characteristicValueLength,
                            _in_ u4                 writeTimeoutValue,
                            _in_ boolean            block);

/**
Data Structure for the indication #CLX_GATT_READ_LOCAL_COMPLETE
*/
typedef struct ClxGattReadLocalCompleteStruct
{
    _user_out_ u1*       characteristicValueBuffer;        /*!< Buffer reading the characteristic value */
    _user_out_ ClxSize*  readCharacteristicValueLength;    /*!< Length of the read characteristic value. If the characteristic value length is fixed then this pointer is meaningless. */
} ClxGattReadLocalComplete;

/**
Read from a local characteristics value. Characteristics values with writable attribute should be read by the user application by using the clxGattReadLocal.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_READ_LOCAL_COMPLETE.
                   The parameter of this indication is of type #ClxGattReadLocalComplete.

\param[  in   ] gatt                           Gatt server handle.
\param[  in   ] characteristicHandle           Handle for the characteristic to read.
\param[  out  ] characteristicValueBuffer      Buffer reading the characteristic value
\param[  in   ] characteristicValueBufferSize  Size of the buffer to read the characteristic value.
\param[  out  ] readCharacteristicValueLength  Length of the read characteristic value. If the characteristic value length is fixed then this pointer is meaningless.
\param[  in   ] block                          Type of the operation.
                                                - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to Gatt was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_REQUEST: If GATT Server is not supported by/enabled in stack
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_LONG: The attribute cannot be read using the offset
*/
ClxResult clxGattReadLocal(_in_ ClxHandle          gatt,
                           _in_ u2                 characteristicHandle,  
                           _user_out_ u1*          characteristicValueBuffer,
                           _in_ ClxSize            characteristicValueBufferSize,
                           _user_out_ ClxSize*     readCharacteristicValueLength,
                           _in_ boolean            block);

/**
Encodes the input structure into the binary format and stores it as the value of the characteristic.
An encoder function shall have already been registered for the characteristic indicated by the provided handle.

IMPORTANT : A characteristic value is of a specific type which is indicated in the documentations. The provided data as input to this
function shall match this type. Otherwise, a corruption may occur. Refer to the documentations for the data type associated to the desired characteristic.

NOTE : If the encoding procedure has been successful, and any client has registered to receive indications/notifications when the value of this characteristic is modified locally,
indications/notifications will be sent to these client before this command is complete.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_ENCODE_LOCAL_CHARACTERISTIC_VALUE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt                  Gatt server handle.
\param[  in   ] characteristicHandle  Handle of the characteristic. The handle shall belong to a characteristic
\param[  in   ] data                  Pointer to the caller-provided data which is to be encoded into the desired characteristic value.
                                      The actual type of the data (as a C structure) depends on the desired characteristic, as indicated in the relevant documentations.
\param[  in   ] dataSize              Size of data. Assume data is of type DATA_STRUCT (which is a C structure),
                                      then this argument shall be set to sizeof(DATA_STRUCT). This argument is used for a simple sanity check.
                                      NOTE : If this value is not the size of expected data structure, implementation of encoders shall return the error CLX_ERROR_INVALID_COMMAND_ARGUMENT.
\param[  in   ] block                 Indicates mode of operation:
                                      - TRUE : Blocking mode
                                      - FALSE : Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: An attribute with the provided handle does not exist
        - #CLX_ERROR_BLE_NOT_CHARACTERISTIC_VALUE_ATTRIBUTE: The provided handle does not belong to a characteristic value
        - #CLX_ERROR_BLE_CODEC_NOT_IMPLEMENTED: An encoder for the desired characteristic has not been implemented
        - #CLX_ERROR_INVALID_REQUEST: If GATT Server is not supported by/enabled in stack
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
*/
ClxResult clxGattEncodeLocalCharacteristicValue(_in_ ClxHandle           gatt,
                                                _in_ u2                  characteristicHandle,
                                                _user_in_ const void*    data,
                                                _in_ u4                  dataSize,
                                                _in_ boolean             block);

/**
Data Structure for the indication #CLX_GATT_DECODE_LOCAL_CHARACTERISTIC_VALUE_COMPLETE
*/
typedef struct ClxGattDecodeLocalCharacteristicValueCompleteStruct 
{
    _user_out_ void*    buffer;        /*!< Pointer to the caller-provided data structure into which the the desired characteristic value is to be decoded.
                                            The actual type of the data structure (as a C structure) depends on the desired characteristic, as indicated in the relevant documentations. */
} ClxGattDecodeLocalCharacteristicValueComplete;

/**
Decodes the value of a characteristic into a C-style data structure.
An decoder function shall have already been registered for the characteristic indicated by the provided handle.

IMPORTANT : A characteristic value is of a specific type which is indicated in the documentations. The provided data structure as output to this
function shall match this type. Otherwise, a corruption may occur. Refer to the documentations for the data type associated to the desired characteristic.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DECODE_LOCAL_CHARACTERISTIC_VALUE_COMPLETE.
                   The parameter of this indication is of type #ClxGattDecodeLocalCharacteristicValueComplete.

\param[  in   ] gatt                  Gatt server handle.
\param[  in   ] characteristicHandle  Handle of the characteristic. The handle shall belong to a characteristic.
\param[  out  ] buffer                Pointer to the caller-provided data structure into which the the desired characteristic value is to be decoded.
                                      The actual type of the data structure (as a C structure) depends on the desired characteristic, as indicated in the relevant documentations.
\param[  in   ] bufferSize            Size of buffer. Assume buffer is of type DATA_STRUCT (which is a C structure),
                                      then this argument shall be set to sizeof(DATA_STRUCT). This argument is used for a simple sanity check.
                                      NOTE : If this value is not the size of expected data structure, implementation of decoders shall return the error CLX_ERROR_INVALID_COMMAND_ARGUMENT.
\param[  in   ] block                 Indicates mode of operation:
                                      - TRUE : Blocking mode
                                      - FALSE : Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_NOT_CHARACTERISTIC_VALUE_ATTRIBUTE: The provided handle does not belong to a characteristic value
        - #CLX_ERROR_BLE_CODEC_NOT_IMPLEMENTED: An encoder for the desired characteristic has not been implemented
        - #CLX_ERROR_INVALID_REQUEST: If GATT Server is not supported by/enabled in stack
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
*/
ClxResult clxGattDecodeLocalCharacteristicValue(_in_ ClxHandle      gatt,
                                                _in_ u2             characteristicHandle,
                                                _user_out_ void*    buffer,
                                                _in_ u4             bufferSize,
                                                _in_ boolean        block);

/**
De-registers a local service which is already registered.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_UNREGISTER_LOCAL_SERVICE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt                Gatt server handle.
\param[  in   ] serviceBaseHandle   Service base handle which is retrieved through the API #clxGattRegisterLocalService.
\param[  in   ] block               Type of the operation.
                                    - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to Gatt was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_REQUEST: If GATT Server is not supported by/enabled in stack
        - #CLX_ERROR_BLE_ATT_INVALID_BASE_HANDLE: The service base handle is invalid
        - #CLX_ERROR_BLE_ATT_REQUEST_NOT_ALLOWED: Service de-registration is not allowed during an active connection
*/
ClxResult clxGattUnregisterLocalService(_in_ ClxHandle      gatt,
                                        _in_ u2             serviceBaseHandle,
                                        _in_ boolean        block);

#ifdef __cplusplus
}
#endif

#endif  // __Gatt_Ble_Server_Api_h__

