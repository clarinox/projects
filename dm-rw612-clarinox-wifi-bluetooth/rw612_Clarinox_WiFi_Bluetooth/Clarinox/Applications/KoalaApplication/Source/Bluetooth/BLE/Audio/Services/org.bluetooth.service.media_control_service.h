#ifndef __org_bluetooth_service_media_control_service_h__
#define __org_bluetooth_service_media_control_service_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.media_control_service.h
* Description         Declares definitions for the GATT service Media Control Service
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
Media Control Service GATT Service:
This specification describes two services: Media Control Service (MCS) and Generic Media Control
Service (GMCS).
*/
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_NAME    "Media Control Service"
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_UUID    0x1848

/**
Media Player Name Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicMediaPlayerNameFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME                 "Media Player Name"
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_STRUCT          struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_VALUE_TYPE      ClxOrgBluetoothCharacteristicMediaPlayerNameFields_Type
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_SIZE            ClxOrgBluetoothCharacteristicMediaPlayerNameFields_Size
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_UUID            0x2B93


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicMediaPlayerName.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicMediaPlayerName.
*/
struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields
{
    /**
    Field : player_Name
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 playerName_Length;
    s1 playerName[32];
    
    /**
    Field : Properties
    Format : 16bit
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 3
    Value BitField :
    {
        Index 0 : 
        {
            0 : Notifications disabled            
            1 : Notifications enabled            
        }
        Index 1 : 
        {
            0 : Indications disabled            
            1 : Indications enabled            
        }
    }
    */
    u2 properties;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicMediaPlayerNameFields
*/
#define ClxOrgBluetoothCharacteristicMediaPlayerNameFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicMediaPlayerNameFields
*/
#define ClxOrgBluetoothCharacteristicMediaPlayerNameFields_Size    (32 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicMediaPlayerNameFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicMediaPlayerNameFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicMediaPlayerName(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicMediaPlayerNameFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicMediaPlayerNameFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicMediaPlayerName(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Track Changed Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicTrackChangedFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED                 "Track Changed"
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_HANDLE_INDEX    4
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_STRUCT          struct ClxOrgBluetoothCharacteristicTrackChangedFields
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_VALUE_TYPE      ClxOrgBluetoothCharacteristicTrackChangedFields_Type
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_SIZE            ClxOrgBluetoothCharacteristicTrackChangedFields_Size
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_UUID            0x2B96


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicTrackChanged.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicTrackChanged.
*/
struct ClxOrgBluetoothCharacteristicTrackChangedFields
{
    /**
    Field : Properties
    Format : 16bit
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 3
    Value BitField :
    {
        Index 0 : 
        {
            0 : Notifications disabled            
            1 : Notifications enabled            
        }
        Index 1 : 
        {
            0 : Indications disabled            
            1 : Indications enabled            
        }
    }
    */
    u2 properties;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicTrackChangedFields
*/
#define ClxOrgBluetoothCharacteristicTrackChangedFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicTrackChangedFields
*/
#define ClxOrgBluetoothCharacteristicTrackChangedFields_Size    (2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicTrackChangedFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicTrackChangedFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTrackChangedFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicTrackChanged(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicTrackChangedFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicTrackChangedFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTrackChangedFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicTrackChanged(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Track Title Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicTrackTitleFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE                 "Track Title"
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_HANDLE_INDEX    7
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_STRUCT          struct ClxOrgBluetoothCharacteristicTrackTitleFields
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_VALUE_TYPE      ClxOrgBluetoothCharacteristicTrackTitleFields_Type
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_SIZE            ClxOrgBluetoothCharacteristicTrackTitleFields_Size
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_UUID            0x2B97


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicTrackTitle.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicTrackTitle.
*/
struct ClxOrgBluetoothCharacteristicTrackTitleFields
{
    /**
    Field : player_Name
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 playerName_Length;
    s1 playerName[32];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicTrackTitleFields
*/
#define ClxOrgBluetoothCharacteristicTrackTitleFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicTrackTitleFields
*/
#define ClxOrgBluetoothCharacteristicTrackTitleFields_Size    (32)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicTrackTitleFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicTrackTitleFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTrackTitleFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicTrackTitle(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicTrackTitleFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicTrackTitleFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTrackTitleFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicTrackTitle(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Track Duration Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicTrackDurationFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION                 "Track Duration"
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_HANDLE_INDEX    9
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_STRUCT          struct ClxOrgBluetoothCharacteristicTrackDurationFields
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_VALUE_TYPE      ClxOrgBluetoothCharacteristicTrackDurationFields_Type
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_SIZE            ClxOrgBluetoothCharacteristicTrackDurationFields_Size
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_UUID            0x2B98


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicTrackDuration.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicTrackDuration.
*/
struct ClxOrgBluetoothCharacteristicTrackDurationFields
{
    /**
    Field : track_Duration
    Format : sint32
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s4 trackDuration;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicTrackDurationFields
*/
#define ClxOrgBluetoothCharacteristicTrackDurationFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicTrackDurationFields
*/
#define ClxOrgBluetoothCharacteristicTrackDurationFields_Size    (4)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicTrackDurationFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicTrackDurationFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTrackDurationFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicTrackDuration(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicTrackDurationFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicTrackDurationFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTrackDurationFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicTrackDuration(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Track Position Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicTrackPositionFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION                 "Track Position"
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_HANDLE_INDEX    11
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_STRUCT          struct ClxOrgBluetoothCharacteristicTrackPositionFields
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_VALUE_TYPE      ClxOrgBluetoothCharacteristicTrackPositionFields_Type
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_SIZE            ClxOrgBluetoothCharacteristicTrackPositionFields_Size
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_UUID            0x2B99


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicTrackPosition.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicTrackPosition.
*/
struct ClxOrgBluetoothCharacteristicTrackPositionFields
{
    /**
    Field : track_Position
    Format : sint32
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s4 trackPosition;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicTrackPositionFields
*/
#define ClxOrgBluetoothCharacteristicTrackPositionFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicTrackPositionFields
*/
#define ClxOrgBluetoothCharacteristicTrackPositionFields_Size    (4)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicTrackPositionFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicTrackPositionFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTrackPositionFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicTrackPosition(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicTrackPositionFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicTrackPositionFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTrackPositionFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicTrackPosition(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Media State Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicMediaStateFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE                 "Media State"
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_HANDLE_INDEX    13
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_STRUCT          struct ClxOrgBluetoothCharacteristicMediaStateFields
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_VALUE_TYPE      ClxOrgBluetoothCharacteristicMediaStateFields_Type
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_SIZE            ClxOrgBluetoothCharacteristicMediaStateFields_Size
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_UUID            0x2BA3


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicMediaState.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicMediaState.
*/
struct ClxOrgBluetoothCharacteristicMediaStateFields
{
    /**
    Field : media_State
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 mediaState;
    
    /**
    Field : Properties
    Format : 16bit
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 3
    Value BitField :
    {
        Index 0 : 
        {
            0 : Notifications disabled            
            1 : Notifications enabled            
        }
        Index 1 : 
        {
            0 : Indications disabled            
            1 : Indications enabled            
        }
    }
    */
    u2 properties;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicMediaStateFields
*/
#define ClxOrgBluetoothCharacteristicMediaStateFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicMediaStateFields
*/
#define ClxOrgBluetoothCharacteristicMediaStateFields_Size    (1 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicMediaStateFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicMediaStateFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicMediaStateFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicMediaState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicMediaStateFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicMediaStateFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicMediaStateFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicMediaState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Content Control ID Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicContentControlIdFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID                 "Content Control ID"
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_HANDLE_INDEX    16
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_STRUCT          struct ClxOrgBluetoothCharacteristicContentControlIdFields
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_VALUE_TYPE      ClxOrgBluetoothCharacteristicContentControlIdFields_Type
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_SIZE            ClxOrgBluetoothCharacteristicContentControlIdFields_Size
#define CLX_GATT_SERVICE_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID            0x2BBA


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicContentControlId.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicContentControlId.
*/
struct ClxOrgBluetoothCharacteristicContentControlIdFields
{
    /**
    Field : content_Control_Id
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 contentControlId;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicContentControlIdFields
*/
#define ClxOrgBluetoothCharacteristicContentControlIdFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicContentControlIdFields
*/
#define ClxOrgBluetoothCharacteristicContentControlIdFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicContentControlIdFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicContentControlIdFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicContentControlIdFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicContentControlId(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicContentControlIdFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicContentControlIdFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicContentControlIdFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicContentControlId(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Media Control Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Media Control Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetMediaControlServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __org_bluetooth_service_media_control_service_h__

