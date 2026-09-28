#ifndef __C_Bleservicegenerator_Xml_Custom_OrgBluetoothServiceHearingAccessService__
#define __C_Bleservicegenerator_Xml_Custom_OrgBluetoothServiceHearingAccessService__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.hearing_access_service.h
* Description         Declares definitions for the GATT service Hearing Access Service
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
Hearing Access Service GATT Service:
The Hearing Access Service is used to identify a hearing aid and optionally to control hearing aid presets
*/
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_NAME    "Hearing Access Service"
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_UUID    0x1854

/**
Hearing Aid Features Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicHearingAidFeaturesFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES                 "Hearing Aid Features"
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_STRUCT          struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_VALUE_TYPE      ClxOrgBluetoothCharacteristicHearingAidFeaturesFields_Type
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_SIZE            ClxOrgBluetoothCharacteristicHearingAidFeaturesFields_Size
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_UUID            0x2BDA


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicHearingAidFeatures.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicHearingAidFeatures.
*/
struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields
{
    /**
    Field : aidFeatures
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 aidfeatures;
    
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
Defines the value type of the structure #ClxOrgBluetoothCharacteristicHearingAidFeaturesFields
*/
#define ClxOrgBluetoothCharacteristicHearingAidFeaturesFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicHearingAidFeaturesFields
*/
#define ClxOrgBluetoothCharacteristicHearingAidFeaturesFields_Size    (1 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicHearingAidFeaturesFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicHearingAidFeaturesFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicHearingAidFeatures(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicHearingAidFeaturesFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicHearingAidFeaturesFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicHearingAidFeatures(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Hearing Aid Preset Control Point Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT                 "Hearing Aid Preset Control Point"
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_HANDLE_INDEX    5
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_STRUCT          struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_VALUE_TYPE      ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields_Type
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_SIZE            ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields_Size
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_UUID            0x2BDB


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicHearingAidPresetControlPoint.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicHearingAidPresetControlPoint.
*/
struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields
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
    Field : index
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 index;
    
    /**
    Field : name
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 name_Length;
    s1 name[40];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields
*/
#define ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields
*/
#define ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields_Size    (1 + 1 + 40)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicHearingAidPresetControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicHearingAidPresetControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Active Preset Index Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicActivePresetIndexFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX                 "Active Preset Index"
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_HANDLE_INDEX    7
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_STRUCT          struct ClxOrgBluetoothCharacteristicActivePresetIndexFields
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_VALUE_TYPE      ClxOrgBluetoothCharacteristicActivePresetIndexFields_Type
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_SIZE            ClxOrgBluetoothCharacteristicActivePresetIndexFields_Size
#define CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_UUID            0x2BDC


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicActivePresetIndex.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicActivePresetIndex.
*/
struct ClxOrgBluetoothCharacteristicActivePresetIndexFields
{
    /**
    Field : activePresetIndex
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 activepresetindex;
    
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
Defines the value type of the structure #ClxOrgBluetoothCharacteristicActivePresetIndexFields
*/
#define ClxOrgBluetoothCharacteristicActivePresetIndexFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicActivePresetIndexFields
*/
#define ClxOrgBluetoothCharacteristicActivePresetIndexFields_Size    (1 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicActivePresetIndexFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicActivePresetIndexFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicActivePresetIndexFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicActivePresetIndex(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicActivePresetIndexFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicActivePresetIndexFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicActivePresetIndexFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicActivePresetIndex(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Hearing Access Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Hearing Access Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetHearingAccessServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __C_Bleservicegenerator_Xml_Custom_OrgBluetoothServiceHearingAccessService__

