#ifndef __Org_Bluetooth_Service_Published_Audiocapabilities_h__
#define __Org_Bluetooth_Service_Published_Audiocapabilities_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.published_audiocapabilities.h
* Description         Declares definitions for the GATT service Published Audio Capabilities
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#include "BleAudioCommon.h"
#include "Gatt.Ble.Includes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
Published Audio Capabilities GATT Service:
PACS can be instantiated on devices that are able to accept the establishment of audio streams. Examples of such devices are speakers, headsets, hearing aids, and microphones.
*/
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_NAME    "Published Audio Capabilities"

/**
Sink PAC Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_UUID.

The value of this characteristic is of type #ClxBapPacRecords.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC                 "Sink PAC"
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_STRUCT          ClxBapPacRecords
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_VALUE_TYPE      ClxOrgBluetoothCharacteristicSinkPacFields_Type
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_SIZE            CLX_GATT_MAX_LTV_RECORD_LENGTH
/**
Defines the value type of the structure #ClxBapPacRecords
*/
#define ClxOrgBluetoothCharacteristicSinkPacFields_Type    ClxBleAttributeValueType_VariableLength

/**
Encodes the fields of an object of type #ClxBapPacRecords into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxBapPacRecords which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(ClxBapPacRecords).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSinkOrSourcePac(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxBapPacRecords.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxBapPacRecords which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(ClxBapPacRecords). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSinkOrSourcePac(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);

/**
Sink Audio Location Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_UUID.

The value of this characteristic is of type #ClxBapPacAudioLocations.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION                 "Sink Audio Location"
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_HANDLE_INDEX    5
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_STRUCT          ClxBapPacAudioLocations
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_VALUE_TYPE      ClxBapPacAudioLocations_Type
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_SIZE            ClxBapPacAudioLocations_Size

/**
Defines the value type of the structure #ClxBapPacAudioLocations
*/
#define ClxBapPacAudioLocations_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxBapPacAudioLocations
*/
#define ClxBapPacAudioLocations_Size    (4 + 2)

/**
Encodes the fields of an object of type #ClxBapPacAudioLocations into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxBapPacAudioLocations which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(ClxBapPacAudioLocations).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSinkAudioLocation(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxBapPacAudioLocations.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxBapPacAudioLocations which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(ClxBapPacAudioLocations). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSinkAudioLocation(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Source PAC Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSourcePacFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC                 "Source PAC"
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_HANDLE_INDEX    8
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_STRUCT          ClxBapPacRecords
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_VALUE_TYPE      ClxOrgBluetoothCharacteristicSourcePacFields_Type
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_SIZE            CLX_GATT_MAX_LTV_RECORD_LENGTH

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSourcePacFields
*/
#define ClxOrgBluetoothCharacteristicSourcePacFields_Type    ClxBleAttributeValueType_VariableLength

/**
Source Audio Location Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_UUID.

The value of this characteristic is of type #ClxBapPacAudioLocations.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION                 "Source Audio Location"
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_HANDLE_INDEX    11
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_STRUCT          ClxBapPacAudioLocations
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_VALUE_TYPE      ClxBapPacAudioLocations_Type
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_SIZE            ClxBapPacAudioLocations_Size

/**
Defines the value type of the structure #ClxBapPacAudioLocations
*/
#define ClxBapPacAudioLocations_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxBapPacAudioLocations
*/
#define ClxBapPacAudioLocations_Size    (4 + 2)

/**
Encodes the fields of an object of type #ClxBapPacAudioLocations into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxBapPacAudioLocations which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(ClxBapPacAudioLocations).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSourceAudioLocation(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxBapPacAudioLocations.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxBapPacAudioLocations which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(ClxBapPacAudioLocations). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSourceAudioLocation(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Available Audio Contexts Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAvailableAudioContextsFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS                 "Available Audio Contexts"
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_HANDLE_INDEX    14
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_STRUCT          ClxBapPacAvailableAudioContext
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_VALUE_TYPE      ClxOrgBluetoothCharacteristicAvailableAudioContextsFields_Type

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAvailableAudioContextsFields
*/
#define ClxOrgBluetoothCharacteristicAvailableAudioContextsFields_Type    ClxBleAttributeValueType_VariableLength

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAvailableAudioContextsFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAvailableAudioContextsFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(ClxBapPacAvailableAudioContext).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAvailableAudioContexts(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAvailableAudioContextsFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAvailableAudioContextsFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(ClxBapPacAvailableAudioContext). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAvailableAudioContexts(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Supported Audio Contexts Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSupportedAudioContextsFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS                 "Supported Audio Contexts"
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_HANDLE_INDEX    17
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_STRUCT          ClxBapPacSupportedAudioContext
#define CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_VALUE_TYPE      ClxOrgBluetoothCharacteristicSupportedAudioContextsFields_Type
  
/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSupportedAudioContextsFields
*/
#define ClxOrgBluetoothCharacteristicSupportedAudioContextsFields_Type    ClxBleAttributeValueType_VariableLength
 

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSupportedAudioContextsFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicSupportedAudioContextsFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(ClxBapPacSupportedAudioContext).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSupportedAudioContexts(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSupportedAudioContextsFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicSupportedAudioContextsFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(ClxBapPacSupportedAudioContext). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSupportedAudioContexts(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Published Audio Capabilities GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Published Audio Capabilities GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetPublishedAudioCapabilitiesGattServiceInterface();

const ClxBleGattServiceInterface* clxGetPublishedAudioCapabilitiesGattServiceInterface( void );

const s1* clxGetPublishedAudioCapabilitiesGattServiceCharacteristicName(u2 handleIndex);

#ifdef __cplusplus
}
#endif

#endif /* CLX_BLE_ISOCHRONOUS */

#endif /* __Org_Bluetooth_Service_Published_Audiocapabilities_h__ */

