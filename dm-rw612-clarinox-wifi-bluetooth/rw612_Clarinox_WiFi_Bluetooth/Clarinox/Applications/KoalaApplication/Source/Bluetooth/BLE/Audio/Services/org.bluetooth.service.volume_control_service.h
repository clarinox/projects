#ifndef __org_bluetooth_service_volume_control_service_h__
#define __org_bluetooth_service_volume_control_service_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.volume_control_service.h
* Description         Declares definitions for the GATT service Volume Control Service
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
Volume Control Service GATT Service:
VCS is instantiated to expose the controls and state of a device that can control the volume of an audio
output such as one or more speakers.
*/
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_NAME    "Volume Control Service"
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_UUID    0x1844

/**
Volume State Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicVolumeStateFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE                 "Volume State"
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_STRUCT          struct ClxOrgBluetoothCharacteristicVolumeStateFields
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_VALUE_TYPE      ClxOrgBluetoothCharacteristicVolumeStateFields_Type
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_SIZE            ClxOrgBluetoothCharacteristicVolumeStateFields_Size
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_UUID            0x2B7D


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicVolumeState.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicVolumeState.
*/
typedef struct ClxOrgBluetoothCharacteristicVolumeStateFields
{
    /**
    Field : volume_Setting
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 volumeSetting;
    
    /**
    Field : mute
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 mute;
    
    /**
    Field : change_Counter
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 changeCounter;
}ClxVolumeState;

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicVolumeStateFields
*/
#define ClxOrgBluetoothCharacteristicVolumeStateFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicVolumeStateFields
*/
#define ClxOrgBluetoothCharacteristicVolumeStateFields_Size    (1 + 1 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeStateFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeStateFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeStateFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicVolumeState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeStateFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeStateFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeStateFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicVolumeState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Volume Control Point Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicVolumeControlPointFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT                 "Volume Control Point"
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_HANDLE_INDEX    5
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_STRUCT          struct ClxOrgBluetoothCharacteristicVolumeControlPointFields
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_VALUE_TYPE      ClxOrgBluetoothCharacteristicVolumeControlPointFields_Type
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_SIZE            ClxOrgBluetoothCharacteristicVolumeControlPointFields_Size
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_UUID            0x2B7E


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicVolumeControlPoint.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicVolumeControlPoint.
*/
struct ClxOrgBluetoothCharacteristicVolumeControlPointFields
{
    /**
    Field : Opcode
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 opcode;

    /**
    Field : change counter
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 change_counter;

    /**
    Field : volume settings
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 volume_settings;
};

typedef enum ClxOrgBluetoothCharacteristicVolumeControlPointOpcodeEnum
{
    VCS_Controlpoint_RelativeVolumeDown,
    VCS_Controlpoint_RelativeVolumeUp,
    VCS_Controlpoint_UnmuteRelativeVolumeDown,
    VCS_Controlpoint_UnmuteRelativeVolumeUp,
    VCS_Controlpoint_SetAbsoluteVolume,
    VCS_Controlpoint_Unmute,
    VCS_Controlpoint_Mute
} ClxOrgBluetoothCharacteristicVolumeControlPointOpcode;

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicVolumeControlPointFields
*/
#define ClxOrgBluetoothCharacteristicVolumeControlPointFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicVolumeControlPointFields
*/
#define ClxOrgBluetoothCharacteristicVolumeControlPointFields_Size    (1 + 1 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeControlPointFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeControlPointFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeControlPointFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicVolumeControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeControlPointFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeControlPointFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeControlPointFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicVolumeControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Volume Flags Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicVolumeFlagsFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS                 "Volume Flags"
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_HANDLE_INDEX    7
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_STRUCT          struct ClxOrgBluetoothCharacteristicVolumeFlagsFields
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_VALUE_TYPE      ClxOrgBluetoothCharacteristicVolumeFlagsFields_Type
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_SIZE            ClxOrgBluetoothCharacteristicVolumeFlagsFields_Size
#define CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_UUID            0x2B7F


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicVolumeFlags.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicVolumeFlags.
*/
typedef struct ClxOrgBluetoothCharacteristicVolumeFlagsFields
{
    /**
    Field : volume_Flags
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 volumeFlags;
}ClxVolumeFlag;

typedef enum ClxOrgBluetoothCharacteristicVolumeFlagEnum
{
    VCS_VolumeFlag_Reset,
    VCS_VolumeFlag_Userset
} ClxOrgBluetoothCharacteristicVolumeFlag;

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicVolumeFlagsFields
*/
#define ClxOrgBluetoothCharacteristicVolumeFlagsFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicVolumeFlagsFields
*/
#define ClxOrgBluetoothCharacteristicVolumeFlagsFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeFlagsFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeFlagsFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeFlagsFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicVolumeFlags(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicVolumeFlagsFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicVolumeFlagsFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicVolumeFlagsFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicVolumeFlags(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);

/**
Returns the interface to Volume Control Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Volume Control Service GATT service. The interface SHALL NOT be modified or removed
*/
const ClxBleGattServiceInterface* clxGetVolumeControlServiceGattServiceInterface();

/**
Returns the Characteristic Name of the Volume Control Service based on the handle index from the local GATT server

\param[ in ] handleIndex  Characteristic handle index

\return The Characteristic Name for the given Characteristic handle index
*/
const s1* clxGetVolumeControlServiceGattServiceCharacteristicName(u2 handleIndex);

#ifdef __cplusplus
}
#endif

#endif /* __org_bluetooth_service_volume_control_service_h__ */

