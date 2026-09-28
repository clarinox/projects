#ifndef __org_bluetooth_service_audiostream_control_h__
#define __org_bluetooth_service_audiostream_control_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.audiostream_control.h
* Description         Declares definitions for the GATT service Audio Stream Control
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#ifdef __cplusplus
extern "C" {
#endif

/**
Audio Stream Control GATT Service:
ASCS can be instantiated on devices that can accept the establishment of unicast Audio Streams. Examples of such devices are speakers, headsets, hearing aids, earbuds, and wireless microphones.
*/
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_NAME    "Audio Stream Control"

/**
Sink ASE Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSinkAseFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE                 "Sink ASE"
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_STRUCT          ClxBapAudioStreamEndpoint
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_VALUE_TYPE      ClxOrgBluetoothCharacteristicSinkAseFields_Type

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSinkAseFields
*/
#define ClxOrgBluetoothCharacteristicSinkAseFields_Type    ClxBleAttributeValueType_VariableLength

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSinkAseFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxBapAudioStreamEndpoint which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(ClxBapAudioStreamEndpoint).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSourceOrSinkAse(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSinkAseFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxBapAudioStreamEndpoint which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(ClxBapAudioStreamEndpoint). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSourceOrSinkAse(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);


/**
Source ASE Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSourceAseFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE                 "Source ASE"
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_HANDLE_INDEX    8
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_STRUCT          ClxBapAudioStreamEndpoint
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_VALUE_TYPE      ClxOrgBluetoothCharacteristicSourceAseFields_Type

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSourceAseFields
*/
#define ClxOrgBluetoothCharacteristicSourceAseFields_Type    ClxBleAttributeValueType_VariableLength

/**
ASE Control Point Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAseControlPointFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT                 "ASE Control Point"
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_HANDLE_INDEX    11
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_STRUCT          ClxBapAseOpCode
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_VALUE_TYPE      ClxOrgBluetoothCharacteristicAseControlPointFields_Type
#define CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_UUID            0x2BC6

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAseControlPointFields
*/
#define ClxOrgBluetoothCharacteristicAseControlPointFields_Type    ClxBleAttributeValueType_VariableLength


/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAseControlPointFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAseControlPointFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(ClxBapAseOpCode).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAseControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAseControlPointFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAseControlPointFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(ClxBapAseOpCode). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAseControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);

/**
Returns the interface to Audio Stream Control GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Audio Stream Control GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetAudioStreamControlGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif /* CLX_BLE_ISOCHRONOUS */

#endif /* __org_bluetooth_service_audiostream_control_h__ */

