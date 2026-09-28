#ifndef __org_bluetooth_service_audio_input_control_service_h__
#define __org_bluetooth_service_audio_input_control_service_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.audio_input_control_service.h
* Description         Declares definitions for the GATT service Audio Input Control Service
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
Audio Input Control Service GATT Service:
The Audio Input Control Service is instantiated to expose the settings of an audio input such as a
Bluetooth audio stream, microphone, etc. Multiple audio inputs may be combined as part of the servers
audio mixing functionality.
*/
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_NAME    "Audio Input Control Service"
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_UUID    0x1843

/**
Audio Input State Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAudioInputStateFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE                 "Audio Input State"
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_HANDLE_INDEX    16
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_STRUCT          struct ClxOrgBluetoothCharacteristicAudioInputStateFields
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_VALUE_TYPE      ClxOrgBluetoothCharacteristicAudioInputStateFields_Type
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_SIZE            ClxOrgBluetoothCharacteristicAudioInputStateFields_Size
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_UUID            0x2B77


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicAudioInputState.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicAudioInputState.
*/
struct ClxOrgBluetoothCharacteristicAudioInputStateFields
{
    /**
    Field : gain_Setting
    Format : sint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s1 gainSetting;
    
    /**
    Field : mute
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 mute;
    
    /**
    Field : gain_Mode
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 gainMode;
    
    /**
    Field : change_Counter
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 changeCounter;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAudioInputStateFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputStateFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicAudioInputStateFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputStateFields_Size    (1 + 1 + 1 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputStateFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputStateFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputStateFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAudioInputState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputStateFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputStateFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputStateFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAudioInputState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Gain Settings Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGainSettingsFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS                 "Gain Settings"
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_HANDLE_INDEX    19
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_STRUCT          struct ClxOrgBluetoothCharacteristicGainSettingsFields
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_VALUE_TYPE      ClxOrgBluetoothCharacteristicGainSettingsFields_Type
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_SIZE            ClxOrgBluetoothCharacteristicGainSettingsFields_Size
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_UUID            0x2B78


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGainSettings.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGainSettings.
*/
struct ClxOrgBluetoothCharacteristicGainSettingsFields
{
    /**
    Field : units
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 units;
    
    /**
    Field : min
    Format : sint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s1 min;
    
    /**
    Field : max
    Format : sint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s1 max;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGainSettingsFields
*/
#define ClxOrgBluetoothCharacteristicGainSettingsFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGainSettingsFields
*/
#define ClxOrgBluetoothCharacteristicGainSettingsFields_Size    (1 + 1 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGainSettingsFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGainSettingsFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGainSettingsFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGainSettings(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGainSettingsFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGainSettingsFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGainSettingsFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGainSettings(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Audio Input Type Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAudioInputTypeFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE                 "Audio Input Type"
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_HANDLE_INDEX    21
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_STRUCT          struct ClxOrgBluetoothCharacteristicAudioInputTypeFields
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_VALUE_TYPE      ClxOrgBluetoothCharacteristicAudioInputTypeFields_Type
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_SIZE            ClxOrgBluetoothCharacteristicAudioInputTypeFields_Size
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_UUID            0x2B79


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicAudioInputType.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicAudioInputType.
*/
struct ClxOrgBluetoothCharacteristicAudioInputTypeFields
{
    /**
    Field : input_Type
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 inputType;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAudioInputTypeFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputTypeFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicAudioInputTypeFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputTypeFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputTypeFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputTypeFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputTypeFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAudioInputType(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputTypeFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputTypeFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputTypeFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAudioInputType(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Audio Input Status Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAudioInputStatusFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS                 "Audio Input Status"
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_HANDLE_INDEX    23
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_STRUCT          struct ClxOrgBluetoothCharacteristicAudioInputStatusFields
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_VALUE_TYPE      ClxOrgBluetoothCharacteristicAudioInputStatusFields_Type
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_SIZE            ClxOrgBluetoothCharacteristicAudioInputStatusFields_Size
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_UUID            0x2B7A


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicAudioInputStatus.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicAudioInputStatus.
*/
struct ClxOrgBluetoothCharacteristicAudioInputStatusFields
{
    /**
    Field : input_Status
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 inputStatus;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAudioInputStatusFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputStatusFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicAudioInputStatusFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputStatusFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputStatusFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputStatusFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputStatusFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAudioInputStatus(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputStatusFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputStatusFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputStatusFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAudioInputStatus(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Audio Input Control Point Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAudioInputControlPointFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT                 "Audio Input Control Point"
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_HANDLE_INDEX    26
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE)
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_STRUCT          struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_VALUE_TYPE      ClxOrgBluetoothCharacteristicAudioInputControlPointFields_Type
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_SIZE            ClxOrgBluetoothCharacteristicAudioInputControlPointFields_Size
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_UUID            0x2B7B


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicAudioInputControlPoint.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicAudioInputControlPoint.
*/
struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields
{
    /**
    Field : opcode
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 opcode;
    u1 changeCounter;
    u1 gainSetting;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAudioInputControlPointFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputControlPointFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicAudioInputControlPointFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputControlPointFields_Size    (1 + 1+ 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputControlPointFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputControlPointFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAudioInputControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputControlPointFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputControlPointFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAudioInputControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Audio Input Description Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAudioInputDescriptionFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION                 "Audio Input Description"
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_HANDLE_INDEX    28
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_STRUCT          struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_VALUE_TYPE      ClxOrgBluetoothCharacteristicAudioInputDescriptionFields_Type
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_SIZE            ClxOrgBluetoothCharacteristicAudioInputDescriptionFields_Size
#define CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_UUID            0x2B7C


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicAudioInputDescription.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicAudioInputDescription.
*/
struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields
{
    /**
    Field : audio_Input
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 audioInput_Length;
    s1 audioInput[50];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAudioInputDescriptionFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputDescriptionFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicAudioInputDescriptionFields
*/
#define ClxOrgBluetoothCharacteristicAudioInputDescriptionFields_Size    (54)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputDescriptionFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputDescriptionFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAudioInputDescription(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAudioInputDescriptionFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAudioInputDescriptionFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAudioInputDescription(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Audio Input Control Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Audio Input Control Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetAudioInputControlServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __Org_Bluetooth_Service_Audio_Input_Control_Service_h__

