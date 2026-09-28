#ifndef __org_bluetooth_service_microphone_control_service_h__
#define __org_bluetooth_service_microphone_control_service_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.microphone_control_service.h
* Description         Declares definitions for the GATT service Microphone Control Service
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2024 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/**
Microphone Control Service GATT Service:
There shall be no more than one instance of the Microphone Control Service (MICS) on a device. MICS is
declared on devices that can control the mute state of a microphones audio.
*/
#define CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_NAME    "Microphone Control Service"
#define CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_UUID    0x184D

/**
Mute Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicMuteFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE                 "Mute"
#define CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_STRUCT          struct ClxOrgBluetoothCharacteristicMuteFields
#define CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_VALUE_TYPE      ClxOrgBluetoothCharacteristicMuteFields_Type
#define CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_SIZE            ClxOrgBluetoothCharacteristicMuteFields_Size
#define CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_UUID            0x2BC3


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicMute.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicMute.
*/
struct ClxOrgBluetoothCharacteristicMuteFields
{
    /**
    Field : audioState
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 audioState;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicMuteFields
*/
#define ClxOrgBluetoothCharacteristicMuteFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicMuteFields
*/
#define ClxOrgBluetoothCharacteristicMuteFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicMuteFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicMuteFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicMuteFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicMute(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicMuteFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicMuteFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicMuteFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicMute(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Microphone Control Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Microphone Control Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetMicrophoneControlServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __org_bluetooth_service_microphone_control_service_h__

