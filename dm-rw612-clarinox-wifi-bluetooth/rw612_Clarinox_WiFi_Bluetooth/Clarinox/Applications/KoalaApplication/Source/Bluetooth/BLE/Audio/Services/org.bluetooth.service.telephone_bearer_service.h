#ifndef __org_bluetooth_service_telephone_bearer_service_h__
#define __org_bluetooth_service_telephone_bearer_service_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.telephone_bearer_service.h
* Description         Declares definitions for the GATT service Telephone Bearer Service
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
Telephone Bearer Service GATT Service:
TBS is instantiated on devices that can make and/or receive phone calls. These devices include cell
phones; tablets; personal computers (PCs); laptops; wearable devices such as smart watches and smart
speakers/displays; and conference room equipment
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_NAME    "Telephone Bearer Service"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_UUID    0x184B

/**
Bearer Provider Name Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicBearerProviderNameFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME                 "Bearer Provider Name"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_STRUCT          struct ClxOrgBluetoothCharacteristicBearerProviderNameFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_VALUE_TYPE      ClxOrgBluetoothCharacteristicBearerProviderNameFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_SIZE            ClxOrgBluetoothCharacteristicBearerProviderNameFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_UUID            0x2BB3


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicBearerProviderName.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicBearerProviderName.
*/
struct ClxOrgBluetoothCharacteristicBearerProviderNameFields
{
    /**
    Field : provider_Name
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 providerName_Length;
    s1 providerName[32];
    
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
Defines the value type of the structure #ClxOrgBluetoothCharacteristicBearerProviderNameFields
*/
#define ClxOrgBluetoothCharacteristicBearerProviderNameFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicBearerProviderNameFields
*/
#define ClxOrgBluetoothCharacteristicBearerProviderNameFields_Size    (32 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicBearerProviderNameFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicBearerProviderNameFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerProviderNameFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBearerProviderName(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicBearerProviderNameFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicBearerProviderNameFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerProviderNameFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBearerProviderName(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Bearer UCI Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI                 "Bearer UCI"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_HANDLE_INDEX    5
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_STRUCT          struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_VALUE_TYPE      ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_SIZE            ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_UUID            0x2BB4


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicBearerUniformCallerIdentifier.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicBearerUniformCallerIdentifier.
*/
struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields
{
    /**
    Field : bearer_Uci
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 bearerUci_Length;
    s1 bearerUci[32];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields
*/
#define ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields
*/
#define ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields_Size    (32)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBearerUniformCallerIdentifier(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBearerUniformCallerIdentifier(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Bearer Technology Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicBearerTechnologyFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY                 "Bearer Technology"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_HANDLE_INDEX    7
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_STRUCT          struct ClxOrgBluetoothCharacteristicBearerTechnologyFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_VALUE_TYPE      ClxOrgBluetoothCharacteristicBearerTechnologyFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_SIZE            ClxOrgBluetoothCharacteristicBearerTechnologyFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_UUID            0x2BB5


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicBearerTechnology.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicBearerTechnology.
*/
struct ClxOrgBluetoothCharacteristicBearerTechnologyFields
{
    /**
    Field : provider_Name
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 providerName;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicBearerTechnologyFields
*/
#define ClxOrgBluetoothCharacteristicBearerTechnologyFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicBearerTechnologyFields
*/
#define ClxOrgBluetoothCharacteristicBearerTechnologyFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicBearerTechnologyFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicBearerTechnologyFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerTechnologyFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBearerTechnology(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicBearerTechnologyFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicBearerTechnologyFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerTechnologyFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBearerTechnology(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Bearer URI Schemes Supported List Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST                 "Bearer URI Schemes Supported List"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_HANDLE_INDEX    10
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_STRUCT          struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_VALUE_TYPE      ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_SIZE            ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_UUID            0x2BB6


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicBearerUriSchemesSupportedList.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicBearerUriSchemesSupportedList.
*/
struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields
{
    /**
    Field : supported_Scheme
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 supportedScheme_Length;
    s1 supportedScheme[32];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields
*/
#define ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields
*/
#define ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields_Size    (32)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBearerUriSchemesSupportedList(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBearerUriSchemesSupportedList(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Bearer List Current Calls Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS                 "Bearer List Current Calls"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_HANDLE_INDEX    12
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_STRUCT          struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_VALUE_TYPE      ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_SIZE            ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_UUID            0x2BB8


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicBearerListCurrentCalls.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicBearerListCurrentCalls.
*/
struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields
{
    /**
    Field : list_Item_Length
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 listItemLength;
    
    /**
    Field : call_Index
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 callIndex;
    
    /**
    Field : call_State
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 callState;
    
    /**
    Field : call_Flags
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 callFlags;
    
    /**
    Field : call_Uri
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 callUri_Length;
    s1 callUri[32];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields
*/
#define ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields
*/
#define ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields_Size    (1 + 1 + 1 + 1 + 32)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBearerListCurrentCalls(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBearerListCurrentCalls(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Content Control ID Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicContentControlIdFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID                 "Content Control ID"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_HANDLE_INDEX    15
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_STRUCT          struct ClxOrgBluetoothCharacteristicContentControlIdFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_VALUE_TYPE      ClxOrgBluetoothCharacteristicContentControlIdFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_SIZE            ClxOrgBluetoothCharacteristicContentControlIdFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID            0x2BBA


/**
Status Flags Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicStatusFlagsFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS                 "Status Flags"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_HANDLE_INDEX    17
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_STRUCT          struct ClxOrgBluetoothCharacteristicStatusFlagsFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_VALUE_TYPE      ClxOrgBluetoothCharacteristicStatusFlagsFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_SIZE            ClxOrgBluetoothCharacteristicStatusFlagsFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_UUID            0x2BBB


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicStatusFlags.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicStatusFlags.
*/
struct ClxOrgBluetoothCharacteristicStatusFlagsFields
{
    /**
    Field : status_Flags
    Format : uint16
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u2 statusFlags;
    
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
Defines the value type of the structure #ClxOrgBluetoothCharacteristicStatusFlagsFields
*/
#define ClxOrgBluetoothCharacteristicStatusFlagsFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicStatusFlagsFields
*/
#define ClxOrgBluetoothCharacteristicStatusFlagsFields_Size    (2 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicStatusFlagsFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicStatusFlagsFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicStatusFlagsFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicStatusFlags(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicStatusFlagsFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicStatusFlagsFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicStatusFlagsFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicStatusFlags(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Call State Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicCallStateFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE                 "Call State"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_HANDLE_INDEX    20
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_STRUCT          struct ClxOrgBluetoothCharacteristicCallStateFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_VALUE_TYPE      ClxOrgBluetoothCharacteristicCallStateFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_SIZE            ClxOrgBluetoothCharacteristicCallStateFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_UUID            0x2BBD


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicCallState.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicCallState.
*/
struct ClxOrgBluetoothCharacteristicCallStateFields
{
    /**
    Field : call_Index
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 callIndex;
    
    /**
    Field : state
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 state;
    
    /**
    Field : call_Flags
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 callFlags;
    
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
Defines the value type of the structure #ClxOrgBluetoothCharacteristicCallStateFields
*/
#define ClxOrgBluetoothCharacteristicCallStateFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicCallStateFields
*/
#define ClxOrgBluetoothCharacteristicCallStateFields_Size    (1 + 1 + 1 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicCallStateFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicCallStateFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicCallStateFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicCallState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicCallStateFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicCallStateFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicCallStateFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicCallState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Call Control Point Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicCallControlPointFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT                 "Call Control Point"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_HANDLE_INDEX    23
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_STRUCT          struct ClxOrgBluetoothCharacteristicCallControlPointFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_VALUE_TYPE      ClxOrgBluetoothCharacteristicCallControlPointFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_SIZE            ClxOrgBluetoothCharacteristicCallControlPointFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_UUID            0x2BBE


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicCallControlPoint.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicCallControlPoint.
*/
struct ClxOrgBluetoothCharacteristicCallControlPointFields
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
Defines the value type of the structure #ClxOrgBluetoothCharacteristicCallControlPointFields
*/
#define ClxOrgBluetoothCharacteristicCallControlPointFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicCallControlPointFields
*/
#define ClxOrgBluetoothCharacteristicCallControlPointFields_Size    (1 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicCallControlPointFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicCallControlPointFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicCallControlPointFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicCallControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicCallControlPointFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicCallControlPointFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicCallControlPointFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicCallControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Call Control Point Optional Opcode Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE                 "Call Control Point Optional Opcode"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_HANDLE_INDEX    26
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_STRUCT          struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_VALUE_TYPE      ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_SIZE            ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_UUID            0x2BBF


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicCallControlPointOptionalOpcode.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicCallControlPointOptionalOpcode.
*/
struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields
{
    /**
    Field : optional_Opcode
    Format : uint16
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u2 optionalOpcode;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields
*/
#define ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields
*/
#define ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields_Size    (2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicCallControlPointOptionalOpcode(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicCallControlPointOptionalOpcode(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Termination Reason Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicTerminationReasonFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON                 "Termination Reason"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_HANDLE_INDEX    28
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_STRUCT          struct ClxOrgBluetoothCharacteristicTerminationReasonFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_VALUE_TYPE      ClxOrgBluetoothCharacteristicTerminationReasonFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_SIZE            ClxOrgBluetoothCharacteristicTerminationReasonFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_UUID            0x2BC0


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicTerminationReason.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicTerminationReason.
*/
struct ClxOrgBluetoothCharacteristicTerminationReasonFields
{
    /**
    Field : reason_Code
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 reasonCode;
    
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
Defines the value type of the structure #ClxOrgBluetoothCharacteristicTerminationReasonFields
*/
#define ClxOrgBluetoothCharacteristicTerminationReasonFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicTerminationReasonFields
*/
#define ClxOrgBluetoothCharacteristicTerminationReasonFields_Size    (1 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicTerminationReasonFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicTerminationReasonFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTerminationReasonFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicTerminationReason(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicTerminationReasonFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicTerminationReasonFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicTerminationReasonFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicTerminationReason(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Incoming Call Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicIncomingCallFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL                 "Incoming Call"
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_HANDLE_INDEX    31
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_STRUCT          struct ClxOrgBluetoothCharacteristicIncomingCallFields
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_VALUE_TYPE      ClxOrgBluetoothCharacteristicIncomingCallFields_Type
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_SIZE            ClxOrgBluetoothCharacteristicIncomingCallFields_Size
#define CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_UUID            0x2BC1


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicIncomingCall.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicIncomingCall.
*/
struct ClxOrgBluetoothCharacteristicIncomingCallFields
{
    /**
    Field : reason_Code
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 reasonCode;
    
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
Defines the value type of the structure #ClxOrgBluetoothCharacteristicIncomingCallFields
*/
#define ClxOrgBluetoothCharacteristicIncomingCallFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicIncomingCallFields
*/
#define ClxOrgBluetoothCharacteristicIncomingCallFields_Size    (1 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicIncomingCallFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicIncomingCallFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicIncomingCallFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicIncomingCall(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicIncomingCallFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicIncomingCallFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicIncomingCallFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicIncomingCall(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Telephone Bearer Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Telephone Bearer Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetTelephoneBearerServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __org_bluetooth_service_telephone_bearer_service_h__

