#ifndef __C_Bleservicegenerator_Xml_Custom_OrgBluetoothServiceGenericAttribute__
#define __C_Bleservicegenerator_Xml_Custom_OrgBluetoothServiceGenericAttribute__

/*******************************************************************************
*
* Project             ClarinoxBlue Low Energy
* File                org.bluetooth.service.generic_attribute.h
* Description         Declares definitions for the GATT service Generic Attribute
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/**
Generic Attribute GATT Service:
*/
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_NAME    "Generic Attribute"
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_UUID    0x1801

/**
Service Changed Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGattServiceChangedFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED                 "Service Changed"
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_INDICATABLE)
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_STRUCT          struct ClxOrgBluetoothCharacteristicGattServiceChangedFields
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_VALUE_TYPE      ClxOrgBluetoothCharacteristicGattServiceChangedFields_Type
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_SIZE            ClxOrgBluetoothCharacteristicGattServiceChangedFields_Size
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_UUID            0x2A05


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGattServiceChanged.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGattServiceChanged.
*/
struct ClxOrgBluetoothCharacteristicGattServiceChangedFields
{
    /**
    Field : Start of Affected Attribute Handle Range
    Format : uint16
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 1
    Maximum : 65535
    */
    u2 startOfAffectedAttributeHandleRange;
    
    /**
    Field : End of Affected Attribute Handle Range
    Format : uint16
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 1
    Maximum : 65535
    */
    u2 endOfAffectedAttributeHandleRange;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGattServiceChangedFields
*/
#define ClxOrgBluetoothCharacteristicGattServiceChangedFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGattServiceChangedFields
*/
#define ClxOrgBluetoothCharacteristicGattServiceChangedFields_Size    (2 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGattServiceChangedFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGattServiceChangedFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGattServiceChangedFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGattServiceChanged(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGattServiceChangedFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGattServiceChangedFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGattServiceChangedFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGattServiceChanged(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Client Supported Feature Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE                 "Client Supported Feature"
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_HANDLE_INDEX    5
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE)
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_STRUCT          struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_VALUE_TYPE      ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields_Type
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_SIZE            ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields_Size
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_UUID            0x2B29


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGattClientSupportedFeature.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGattClientSupportedFeature.
*/
struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields
{
    /**
    Field : Feature
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 1
    Maximum : 65535
    */
    u1 feature;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields
*/
#define ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields
*/
#define ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGattClientSupportedFeature(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGattClientSupportedFeature(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Database Hash Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGattDatabaseHashFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH                 "Database Hash"
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_HANDLE_INDEX    7
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_STRUCT          struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_VALUE_TYPE      ClxOrgBluetoothCharacteristicGattDatabaseHashFields_Type
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_SIZE            ClxOrgBluetoothCharacteristicGattDatabaseHashFields_Size
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_UUID            0x2B2A


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGattDatabaseHash.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGattDatabaseHash.
*/
struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields
{
    /**
    Field : Properties
    Format : uint32
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 1
    Maximum : 65535
    */
    u4 properties;
    
    /**
    Field : Flags
    Format : uint32
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 1
    Maximum : 65535
    */
    u4 flags;
    
    /**
    Field : hashValue
    Format : uint32
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 1
    Maximum : 65535
    */
    u4 hashvalue;
    
    /**
    Field : index
    Format : uint32
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 1
    Maximum : 65535
    */
    u4 index;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGattDatabaseHashFields
*/
#define ClxOrgBluetoothCharacteristicGattDatabaseHashFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGattDatabaseHashFields
*/
#define ClxOrgBluetoothCharacteristicGattDatabaseHashFields_Size    (4 + 4 + 4 + 4)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGattDatabaseHashFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGattDatabaseHashFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGattDatabaseHash(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGattDatabaseHashFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGattDatabaseHashFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGattDatabaseHash(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Server Supported Feature Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE                 "Server Supported Feature"
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_HANDLE_INDEX    9
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_STRUCT          struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_VALUE_TYPE      ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields_Type
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_SIZE            ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields_Size
#define CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_UUID            0x2B3A


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGattServerSupportedFeature.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGattServerSupportedFeature.
*/
struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields
{
    /**
    Field : ServerSupportedFeature
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 1
    Maximum : 65535
    */
    u1 serversupportedfeature;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields
*/
#define ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields
*/
#define ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGattServerSupportedFeature(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGattServerSupportedFeature(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Generic Attribute GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Generic Attribute GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetGenericAttributeGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __C_Bleservicegenerator_Xml_Custom_OrgBluetoothServiceGenericAttribute__

