#ifndef __Org_Bluetooth_Service_Broadcast_Audioscan_h__
#define __Org_Bluetooth_Service_Broadcast_Audioscan_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.broadcast_audioscan.h
* Description         Declares definitions for the GATT service Broadcast Audio Scan
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
Broadcast Audio Scan GATT Service:
This service is used by servers to solicit for clients to perform scanning for extended advertisements (EA) that carry information that
enables synchronization to periodic advertisements (PA) associated with broadcast isochronous streams (BIS) used to transport broadcast
Audio Streams on behalf of the server, and enables servers to report their synchronization status with the PA and with the associated BIS to clients.
*/
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_NAME    "Broadcast Audio Scan"
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID    0x184F

/**
Broadcast Audio Scan Control Point Characteristic:
A single Broadcast Audio Scan Control Point characteristic that can be used by clients to Inform the server that the client is performing,
or that a client is no longer performing, Remote Scanning on behalf of the server.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID.

The value of this characteristic is of type #ClxBapBroadcastScanOpCode.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT                 "Broadcast Audio Scan Control Point"
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_STRUCT          ClxBapBroadcastScanOpCode
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_VALUE_TYPE      ClxBapBroadcastScanOpCode_Type

/**
Defines the value type of the structure #ClxBapBroadcastScanOpCode
*/
#define ClxBapBroadcastScanOpCode_Type    ClxBleAttributeValueType_VariableLength

/**
Encodes the fields of an object of type #ClxBapBroadcastScanOpCode into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxBapBroadcastScanOpCode which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(ClxBapBroadcastScanOpCode).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBroadcastAudioscancontrolpoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxBapBroadcastScanOpCode.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxBapBroadcastScanOpCode which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(ClxBapBroadcastScanOpCode). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBroadcastAudioscancontrolpoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Broadcast Receive State Characteristic:
Broadcast Receive State characteristics that can be used by clients to determine whether the server is decrypting an encrypted broadcast Audio Stream,
and Determine whether the server requires a Broadcast Code in order to decrypt an encrypted broadcast Audio Stream.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_UUID.

The value of this characteristic is of type #ClxBapBroadcastReceiveState.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE                 "Broadcast Receive State"
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_HANDLE_INDEX    4
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_STRUCT          ClxBapBroadcastReceiveState
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_VALUE_TYPE      ClxBapBroadcastReceiveState_Type

/**
Defines the value type of the structure #ClxBapBroadcastReceiveState
*/
#define ClxBapBroadcastReceiveState_Type    ClxBleAttributeValueType_VariableLength

/**
Encodes the fields of an object of type #ClxBapBroadcastReceiveState into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxBapBroadcastReceiveState which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(ClxBapBroadcastReceiveState).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBroadcastReceivestate(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxBapBroadcastReceiveState.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxBapBroadcastReceiveState which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(ClxBapBroadcastReceiveState). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBroadcastReceivestate(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);

/**
Returns the interface to Broadcast Audio Scan GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Broadcast Audio Scan GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetBroadcastAudioScanGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif /* CLX_BLE_ISOCHRONOUS */

#endif /* __Org_Bluetooth_Service_Broadcast_Audioscan_h__ */

