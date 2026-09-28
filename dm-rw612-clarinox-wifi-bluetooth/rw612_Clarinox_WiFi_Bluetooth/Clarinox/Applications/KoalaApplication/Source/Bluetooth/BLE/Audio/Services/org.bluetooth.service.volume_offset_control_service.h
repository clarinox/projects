#ifndef __org_bluetooth_service_volume_offset_control_service_h__
#define __org_bluetooth_service_volume_offset_control_service_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.volume_offset_control_service.h
* Description         Declares definitions for the GATT service Volume Offset Control Service
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
Volume Offset Control Service GATT Service:
VOCS is instantiated to expose the offset level and location of an audio output such as a speaker.
*/
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_NAME    "Volume Offset Control Service"
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_UUID    0x1845

/**
Offset State Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicVolumeOffsetStateFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE                 "Offset State"
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_HANDLE_INDEX    12
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_STRUCT          struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_VALUE_TYPE      ClxOrgBluetoothCharacteristicVolumeOffsetStateFields_Type
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_SIZE            ClxOrgBluetoothCharacteristicVolumeOffsetStateFields_Size
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_UUID            0x2B80


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicVolumeOffsetState.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicVolumeOffsetState.
*/
struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields
{
    /**
    Field : Volume_Offset
    Format : uint16
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u2 volumeOffset;
    
    /**
    Field : Change_Counter
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 changeCounter;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicVolumeOffsetStateFields
*/
#define ClxOrgBluetoothCharacteristicVolumeOffsetStateFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicVolumeOffsetStateFields
*/
#define ClxOrgBluetoothCharacteristicVolumeOffsetStateFields_Size    (2 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeOffsetStateFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeOffsetStateFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicVolumeOffsetState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeOffsetStateFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeOffsetStateFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicVolumeOffsetState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Audio Location Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAudioLocationFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION                 "Audio Location"
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_HANDLE_INDEX    15
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_STRUCT          struct ClxOrgBluetoothCharacteristicAudioLocationFields
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_VALUE_TYPE      ClxOrgBluetoothCharacteristicAudioLocationFields_Type
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_SIZE            ClxOrgBluetoothCharacteristicAudioLocationFields_Size
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_UUID            0x2B81


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicAudioLocation.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicAudioLocation.
*/
struct ClxOrgBluetoothCharacteristicAudioLocationFields
{
    /**
    Field : audio_Location
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 audioLocation;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAudioLocationFields
*/
#define ClxOrgBluetoothCharacteristicAudioLocationFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicAudioLocationFields
*/
#define ClxOrgBluetoothCharacteristicAudioLocationFields_Size    (4)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAudioLocationFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAudioLocationFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioLocationFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAudioLocation(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAudioLocationFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAudioLocationFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioLocationFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAudioLocation(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Volume Offset Control Point Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT                 "Volume Offset Control Point"
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_HANDLE_INDEX    18
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE)
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_STRUCT          struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_VALUE_TYPE      ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields_Type
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_SIZE            ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields_Size
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_UUID            0x2B82


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicVolumeOffsetControlPoint.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicVolumeOffsetControlPoint.
*/
struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields
{
    /**
    Field : opcode
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 opcode;
    
    /**
    Field : change_Counter
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 changeCounter;
    
    /**
    Field : volume_Offset
    Format : uint16
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u2 volumeOffset;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields
*/
#define ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields
*/
#define ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields_Size    (1 + 1 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicVolumeOffsetControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicVolumeOffsetControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Audio Output Description Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION                 "Audio Output Description"
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_HANDLE_INDEX    20
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_STRUCT          struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_VALUE_TYPE      ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields_Type
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_SIZE            ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields_Size
#define CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_UUID            0x2B83


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicAudioOutputDescription.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicAudioOutputDescription.
*/
struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields
{
    /**
    Field : audio_Output
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 audioOutput_Length;
    s1 audioOutput[100];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields
*/
#define ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields
*/
#define ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields_Size    (100 + 4)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAudioOutputDescription(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAudioOutputDescription(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Volume Offset Control Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Volume Offset Control Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetVolumeOffsetControlServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __org_bluetooth_service_volume_offset_control_service_h__

