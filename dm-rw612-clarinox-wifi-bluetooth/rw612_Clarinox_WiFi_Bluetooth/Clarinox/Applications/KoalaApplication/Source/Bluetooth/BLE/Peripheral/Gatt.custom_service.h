#ifndef __gatt_custom_service_h__
#define __gatt_custom_service_h__

/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                Gatt.custom_service.h
* Description         Declares definitions for the GATT Custom Service.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/**
Custom Service GATT Service:
Defining GATT custom service.
*/
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_NAME    "GATT Custom Service"
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_UUID    "65f2c16489ab523865f2c16489ab5238"

/**
Rx Data Characteristic:
Rx data buffer
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_UUID.

The value of this characteristic is of type #ClxGattCustomCharacteristicRxdataFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA                 "Rx Data"
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_STRUCT          struct ClxGattCustomCharacteristicRxdataFields
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_VALUE_TYPE      ClxGattCustomCharacteristicRxdataFields_Type
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_SIZE            ClxGattCustomCharacteristicRxdataFields_Size
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_UUID            "65f2c16489ab523965f2c16489ab5239"


/**
Encoder function for this structure is #clxEncodeGattCustomCharacteristicRxdata.
Decoder function for this structure is #clxDecodeGattCustomCharacteristicRxdata.
*/
struct ClxGattCustomCharacteristicRxdataFields
{
    /**
    Field : RxDataSize
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 rxdatasize;
};

/**
Defines the value type of the structure #ClxGattCustomCharacteristicRxdataFields
*/
#define ClxGattCustomCharacteristicRxdataFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxGattCustomCharacteristicRxdataFields
*/
#define ClxGattCustomCharacteristicRxdataFields_Size    (50)

/**
Encodes the fields of an object of type #ClxGattCustomCharacteristicRxdataFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxGattCustomCharacteristicRxdataFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxGattCustomCharacteristicRxdataFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeGattCustomCharacteristicRxdata(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxGattCustomCharacteristicRxdataFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxGattCustomCharacteristicRxdataFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxGattCustomCharacteristicRxdataFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeGattCustomCharacteristicRxdata(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Tx Data Characteristic:
Tx data buffer
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_UUID.

The value of this characteristic is of type #ClxGattCustomCharacteristicTxdataFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA                 "Tx Data"
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_HANDLE_INDEX    5
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_STRUCT          struct ClxGattCustomCharacteristicTxdataFields
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_VALUE_TYPE      ClxGattCustomCharacteristicTxdataFields_Type
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_SIZE            ClxGattCustomCharacteristicTxdataFields_Size
#define CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_UUID            "65f2c16489ab523765f2c16489ab5237"


/**
Encoder function for this structure is #clxEncodeGattCustomCharacteristicTxdata.
Decoder function for this structure is #clxDecodeGattCustomCharacteristicTxdata.
*/
struct ClxGattCustomCharacteristicTxdataFields
{
    /**
    Field : TxDataSize
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 txdatasize;
};

/**
Defines the value type of the structure #ClxGattCustomCharacteristicTxdataFields
*/
#define ClxGattCustomCharacteristicTxdataFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxGattCustomCharacteristicTxdataFields
*/
#define ClxGattCustomCharacteristicTxdataFields_Size    (50)

/**
Encodes the fields of an object of type #ClxGattCustomCharacteristicTxdataFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxGattCustomCharacteristicTxdataFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxGattCustomCharacteristicTxdataFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeGattCustomCharacteristicTxdata(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxGattCustomCharacteristicTxdataFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxGattCustomCharacteristicTxdataFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxGattCustomCharacteristicTxdataFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeGattCustomCharacteristicTxdata(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Custom Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Custom Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetCustomServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __gatt_custom_service_h__

