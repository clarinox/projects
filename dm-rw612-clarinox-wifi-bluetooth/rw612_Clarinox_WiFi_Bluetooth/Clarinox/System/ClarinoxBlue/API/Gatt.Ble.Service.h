#ifndef __Gatt_Ble_Service_h__
#define __Gatt_Ble_Service_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gatt.Ble.Service.h
* Description         Declares Common API Functions and Definitions For GATT Services
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


/**
How to manually prepare a GATT service for ClarinoxBlue:

Application-specific GATT services need to be registered with the ClarinoxBlue GATT server handle. This is done by using clxGattRegisterLocalService API function.

A GATT service contains the following elements:

- All the attributes belonging to the service (e.g. Primary Service, Characteristic Declarations, Characteristic Values and so on).

- A buffer for each characteristic value. This buffer is used to store the value of the characteristic value. A unique buffer needs to be associated
to each characteristic value attribute.

- A BLE database object of type ClxBleGattDatabase. This object simply holds an array of all attribute objects belonging to the service, and the total number of  
attributes. The database array holds the list of pointers to the attribute objects (and attribute objects themselves).

Typically, the entire service is implemented as a C structure or a C++ class, where the members are the attributes, buffers and the database object.

Service Interface:

When the service structure or class has been implemented, A "Service Interface" needs to be implemented. The service is passed to #clxGattRegisterLocalService API function
for the registration procedure.

A Service Interface is of type #ClxBleGattServiceInterface, which contains pointers to the functions:

- initInstance: This function is called by the stack during the registration procedure. The implementation of the function must allocate an instance of the service structure or
class. This function initiates each attribute object, sets the list of attribute objects in the database object, and returns the database object. If there has been any issue during the initialization
of the service, any allocated object/buffer so far must be deleted and this function must return NULL.

NOTE: In case of an error, the stack will NOT call destroyInstance() to clean up the service objects.

- destroyInstance: This function is called by the stack when the GATT server handle is being destroyed. This is only called if the service has previously registered to the stack successfully.

IMPORTANT: Both of these functions must be implemented.


Attribute Objects:
All attribute objects belonging to a service are C structures. The very first member of the attribute is an object of type ClxBleAttribute.

IMPORTANT: An attribute object must NOT be initialized manually. For each attribute type, a function exists which shall be called to initialize an instance of
the attribute objects. The following attribute types are defined:

-#ClxBlePrimaryServiceAttribute                           : Use the function #clxInitBlePrimaryServiceAttribute to initialize the object.
-#ClxBleCharacteristicDeclarationAttribute                : Use the function #clxInitBleCharacteristicDeclarationAttribute to initialize the object.
-#ClxBleCharacteristicClientConfigurationAttribute        : Use the function #clxInitBleCharacteristicClientConfigurationAttribute to initialize the object.
-#ClxBleCharacteristicValueAttribute                      : Use the function #clxInitBleCharacteristicValueAttribute to initialize the object.


Format of the Attribute Handles used by Clarinox GATT server:

A two-byte handle is assigned to each attribute in a service. This is conducted by the stack. ClarinoxBlue generates handles with the following structure:

MSB                                            LSB
-------------------------------------------------
| Service Handle Base | Service Attribute Index |
-------------------------------------------------
      6 bits                    10 bits

Service Handle Base specifies what service the handle belongs to. 
Up to 64 GATT services (with handle bases 0b000000 to 0b111111) can be registered into the GATT server at the same time.

Service Attribute Index is the of the handle within the service database and starts from zero.

Upon successful registration of a service, the API function #clxGattRegisterLocalService returns the Service Handle Base assigned to the service
by the stack. In order to calculate the handle for an arbitrary attribute inside the service, simply add the service handle base with the
zero-based index of the attribute in the service database list. This value is obtained from the return value of the initInstance in the interface object of this service.


Service Structure:

A service contains at least one attribute: Primary Service. A primary service attribute must be an instance of the structure #ClxBlePrimaryServiceAttribute.
In addition, It must be the very first entry in the database object array.

A service may contain zero or more characteristics. A characteristic is made up of a minimum of two attributes:

- Characteristic Declaration: An object of type #ClxBleCharacteristicDeclarationAttribute. This object must be the first attribute in the collection of attributes
related to a characteristic. This object must be immediately followed by the Characteristic Value attribute.

- Characteristic Value: An object of type ClxBleCharacteristicValueAttribute (the value type has 2 options as defined in #ClxBleAttributeValueTypeEnum):
    + Fixed type (#ClxBleAttributeValueType_FixedLength) for characteristics which have a fixed-size value which cannot be changed by 
    either the local device or any remote client.
    + Variable type (#ClxBleAttributeValueType_VariableLength) for characteristics which have a maximum size but the current value may have a size less than the maximum size. 
    Both the local device and remote clients may change the size of the value by writing a value with size less than the maximum size.

Optionally, a characteristic may have a client configuration descriptor attribute of type #ClxBleCharacteristicClientConfigurationAttribute. This characteristic must be in the database if the characteristic value
attribute has #CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE and/or #CLX_GATT_ATTRIBUTE_PERMISSION_INDICATABLE permissions.

If this attribute exists for a characteristic, it must immediately follow the characteristic value attribute.

Characteristic Value Buffers:
When the function #clxInitBleCharacteristicValueAttribute is called to initialize a Characteristic Value attribute,
the buffer which stores the value of this characteristic must be provided by the user. 
The buffer is typically a member of the service structure or class.

IMPORTANT: The value buffers for all characteristics must be 32-bit aligned. In order to make sure this is the case, the buffer can be defined as of type u4, instead of u1. The size of
the buffer array is then divided by 4. For instance, assume we need a buffer of size n:

\code
u4 buf[(n + 3)/4];

buf is guaranteed to be 32-bit aligned, with the size of at least n bytes. Alternatively, the macro CLX_ALIGNED_BUFFER_4 (defined in ClxCommon.h) may be used:

CLX_ALIGNED_BUFFER_4(buf, n);
\endcode

*/


#define CLX_GATT_MAX_NUMBER_OF_CONNECTIONS                              20
#define CLX_GATT_MAX_NUMBER_OF_PRESENTATION_FORMAT_DECLARATIONS         20

/*GATT UUIDs*/
#define CLX_GATT_PRIMARY_SERVICE_UUID                                   0x2800 
#define CLX_GATT_SECONDARY_SERVICE_UUID                                 0x2801 
#define CLX_GATT_INCLUDE_DEFINITION_UUID                                0x2802
#define CLX_GATT_CHARACTERISTIC_DECLARATION_UUID                        0x2803 

#define CLX_GATT_CHARACTERISTIC_EXTENDED_PROPERTIES_DESCRIPTOR_UUID     0x2900
#define CLX_GATT_CHARACTERISTIC_USER_DESCRIPTION_UUID                   0x2901
#define CLX_GATT_CHARACTERISTIC_CLIENT_CONFIG_DESCRIPTOR_UUID           0x2902
#define CLX_GATT_CHARACTERISTIC_SERVER_CONFIG_DESCRIPTOR_UUID           0x2903
#define CLX_GATT_CHARACTERISTIC_PRESENTATION_FORMAT_DESCRIPTOR_UUID     0x2904
#define CLX_GATT_CHARACTERISTIC_AGGREGATE_FORMAT_UUID                   0x2905
#define CLX_GATT_CHARACTERISTIC_VALID_RANGE_DESCRIPTOR_UUID             0x2906
#define CLX_GATT_CHARACTERISTIC_ER_REFERENCE_DESCRIPTOR_UUID            0x2907
#define CLX_GATT_CHARACTERISTIC_REPORT_REFERENCE_DESCRIPTOR_UUID        0x2908
#define CLX_GATT_CHARACTERISTIC_NUMBER_OF_DIGITALS_DESCRIPTOR_UUID      0x2909
#define CLX_GATT_CHARACTERISTIC_VALUE_TRIGGER_SETTING_DESCRIPTOR_UUID   0x290A
#define CLX_GATT_CHARACTERISTIC_ES_CONFIGURATION_DESCRIPTOR_UUID        0x290B
#define CLX_GATT_CHARACTERISTIC_ES_MEASUREMENT_DESCRIPTOR_UUID          0x290C
#define CLX_GATT_CHARACTERISTIC_ES_TRIGGER_SETTING_DESCRIPTOR_UUID      0x290D
#define CLX_GATT_CHARACTERISTIC_TIME_TRIGGER_SETTING_DESCRIPTOR_UUID    0x290E

#define CLX_GATT_GAP_PRIMARY_SERVICE_VALUE_UUID                         0x1800       
#define CLX_GATT_GATT_PRIMARY_SERVICE_VALUE_UUID                        0x1801

#define CLX_GATT_CHARACTERISTIC_SERVICE_CHANGED_UUID                    0x2A05
#define CLX_GATT_CHARACTERISTIC_SERVICE_CHANGED_SIZE                    (2 + 2)

#define CLX_GATT_GAP_DEVICE_NAME_UUID                                   0x2A00
#define CLX_GATT_GAP_DEVICE_NAME_MAX_SIZE                               (CLX_GATT_MAX_DEVICE_NAME + 1)    /* 1 byte for NULL termination */

#define CLX_GATT_GAP_APPEARANCE_UUID                                    0x2A01
#define CLX_GATT_GAP_APPEARANCE_SIZE                                    2 // bytes

/* Generic Permissions (applicable to all attributes): */
#define CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE                          0x0001
#define CLX_GATT_ATTRIBUTE_PERMISSION_READABLE                          0x0002
#define CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED               0x0004
#define CLX_GATT_ATTRIBUTE_PERMISSION_AUTHENTICATION_REQUIRED           0x0008
#define CLX_GATT_ATTRIBUTE_PERMISSION_AUTHERIZATION_REQUIRED            0x0010

/* 
Permissions applicable to characteristic value attributes only:
*/
#define CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE         0x0020
#define CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE                        0x0040
#define CLX_GATT_ATTRIBUTE_PERMISSION_INDICATABLE                       0x0080
#define CLX_GATT_ATTRIBUTE_PERMISSION_BROADCASTABLE                     0x0100
#define CLX_GATT_ATTRIBUTE_PERMISSION_AUTHENTICATED_SIGNED_WRITABLE     0x0200
#define CLX_GATT_ATTRIBUTE_PERMISSION_EXTENDABLE                        0x0400

#define CLX_GATT_INVALID_GROUP_END_HANDLE                               0xFFFFFFFF

#define CLX_GATT_SERVICE_ELEMENTS_REQUIRED_ALIGNMENT                    4            /* bytes (Fixed. SHALL not be modified) */

#define CLX_BLE_GATT_SERVICE_HANDLE_BASE_FILTER                         0xFC00      /* 6 MSB bits of the handle */
#define CLX_BLE_GATT_SERVICE_ATTR_INDEX_FILTER                          0x03FF      /* 10 LSB bits of the handle */


/*Return value of characteristic with CharactersiticValueIndex under the service ServiceHandleBase*/
#define clxGattGetCharacteristicValueHandle(ServiceHandleBase, CharactersiticValueIndex)   ((ServiceHandleBase & CLX_BLE_GATT_SERVICE_HANDLE_BASE_FILTER) | (CharactersiticValueIndex & CLX_BLE_GATT_SERVICE_ATTR_INDEX_FILTER))

/*Return Service handle from attribute handle*/
#define clxBleGetServiceHandleBaseFromHandle(attrHandle)          ((u2)attrHandle & CLX_BLE_GATT_SERVICE_HANDLE_BASE_FILTER)


/* Returns the zero-based service attribute index within the parent service database for the specified attribute handle: */
#define clxBleGetServiceAttributeIndexFromHandle(attrHandle)     ((u2)attrHandle & CLX_BLE_GATT_SERVICE_ATTR_INDEX_FILTER)


/************************************
ClxBleErrorCode:
************************************/
typedef enum ClxBleErrorCodeEnum
{
    ClxBleErrorCode_InvalidHandle                                       = 0x01,
    ClxBleErrorCode_ReadNotPermitted                                    = 0x02,
    ClxBleErrorCode_WriteNotPermitted                                   = 0x03,
    ClxBleErrorCode_InvalidPDU                                          = 0x04,
    ClxBleErrorCode_InsufficientAuthentication                          = 0x05,
    ClxBleErrorCode_RequestNotSupported                                 = 0x06,
    ClxBleErrorCode_InvalidOffset                                       = 0x07,
    ClxBleErrorCode_InsufficientAuthorization                           = 0x08,
    ClxBleErrorCode_PrepareQueueFull                                    = 0x09,
    ClxBleErrorCode_AttributeNotFound                                   = 0x0A,
    ClxBleErrorCode_AttributeNotLong                                    = 0x0B,
    ClxBleErrorCode_InsufficientEncryptionKeySize                       = 0x0C,
    ClxBleErrorCode_InvalidAttributeValueLength                         = 0x0D,
    ClxBleErrorCode_UnlikelyError                                       = 0x0E,
    ClxBleErrorCode_InsufficientEncryption                              = 0x0F,
    ClxBleErrorCode_UnsupportedGroupType                                = 0x10,
    ClxBleErrorCode_InsufficientResources                               = 0x11
} ClxBleErrorCode;

/************************************
ClxBlePresentationFormatType
************************************/
typedef enum ClxBlePresentationFormatTypeEnum
{
    ClxBlePresentationFormatType_Boolean = 0x01,
    ClxBlePresentationFormatType_Twobit  = 0x02,
    ClxBlePresentationFormatType_Nibble = 0x03,
    ClxBlePresentationFormatType_UInt8 = 0x04,
    ClxBlePresentationFormatType_UInt12 = 0x05,
    ClxBlePresentationFormatType_UInt16 = 0x06,
    ClxBlePresentationFormatType_UInt24 = 0x07,
    ClxBlePresentationFormatType_UInt32 = 0x08,
    ClxBlePresentationFormatType_UInt48 = 0x09,
    ClxBlePresentationFormatType_UInt64 = 0x0A,
    ClxBlePresentationFormatType_UInt128 = 0x0B,
    ClxBlePresentationFormatType_SInt8 = 0x0C,
    ClxBlePresentationFormatType_SInt12 = 0x0D,
    ClxBlePresentationFormatType_SInt16 = 0x0E,
    ClxBlePresentationFormatType_SInt24 = 0x0F,
    ClxBlePresentationFormatType_SInt32 = 0x10,
    ClxBlePresentationFormatType_SInt48 = 0x11,
    ClxBlePresentationFormatType_SInt64 = 0x12,
    ClxBlePresentationFormatType_SInt128 = 0x13,
    ClxBlePresentationFormatType_Float32 = 0x14,
    ClxBlePresentationFormatType_Float64 = 0x15,
    ClxBlePresentationFormatType_SFLOAT = 0x16,
    ClxBlePresentationFormatType_FLOAT = 0x17,
    ClxBlePresentationFormatType_DUInt16 = 0x18,
    ClxBlePresentationFormatType_UTF8s = 0x19,
    ClxBlePresentationFormatType_UTF16s = 0x1A,
    ClxBlePresentationFormatType_Struct = 0x1B
} ClxBlePresentationFormatType;

/********************************
ClxBleEsMesaturementSamplingType
********************************/
typedef enum ClxBleEsMesaturementSamplingTypeEnum
{
    ClxBleEsMesaturementSamplingType_Unspecified    = 0x00,
    ClxBleEsMesaturementSamplingType_Instantaneous  = 0x01,
    ClxBleEsMesaturementSamplingType_ArithmeticMean = 0x02,
    ClxBleEsMesaturementSamplingType_Rms            = 0x03,
    ClxBleEsMesaturementSamplingType_Maximum        = 0x04,
    ClxBleEsMesaturementSamplingType_Minimum        = 0x05,
    ClxBleEsMesaturementSamplingType_Accumulated    = 0x06,
    ClxBleEsMesaturementSamplingType_Count          = 0x07
    /* 0x08 - 0xff Reserved for future use */
} ClxBleEsMesaturementSamplingType;

/*********************************
ClxBleEsMeasurementApplicationType
*********************************/
typedef enum ClxBleEsMeasurementApplicationTypeEnum
{
    ClxBleEsMeasurementApplicationType_Unspecified                  = 0x00,
    ClxBleEsMeasurementApplicationType_Air                          = 0x01,
    ClxBleEsMeasurementApplicationType_Water                        = 0x02,
    ClxBleEsMeasurementApplicationType_Barometric                   = 0x03,
    ClxBleEsMeasurementApplicationType_Soil                         = 0x04,
    ClxBleEsMeasurementApplicationType_Infrared                     = 0x05,
    ClxBleEsMeasurementApplicationType_MapDatabase                  = 0x06,
    ClxBleEsMeasurementApplicationType_BarometicElevation           = 0x07,
    ClxBleEsMeasurementApplicationType_GpsOnlyEvelevation           = 0x08,
    ClxBleEsMeasurementApplicationType_GpsAndMapDatabaseElevation   = 0x09,
    ClxBleEsMeasurementApplicationType_VerticalDatumElevation       = 0x0A,
    ClxBleEsMeasurementApplicationType_Onshore                      = 0x0B,
    ClxBleEsMeasurementApplicationType_OnboardVessel                = 0x0C,
    ClxBleEsMeasurementApplicationType_Front                        = 0x0D,
    ClxBleEsMeasurementApplicationType_BackAndRear                  = 0x0E,
    ClxBleEsMeasurementApplicationType_Upper                        = 0x0F,
    ClxBleEsMeasurementApplicationType_Lower                        = 0x10,
    ClxBleEsMeasurementApplicationType_Primary                      = 0x11,
    ClxBleEsMeasurementApplicationType_Secondary                    = 0x12,
    ClxBleEsMeasurementApplicationType_Outdoor                      = 0x13,
    ClxBleEsMeasurementApplicationType_Indoor                       = 0x14,
    ClxBleEsMeasurementApplicationType_Top                          = 0x15,
    ClxBleEsMeasurementApplicationType_Bottom                       = 0x16,
    ClxBleEsMeasurementApplicationType_Main                         = 0x17,
    ClxBleEsMeasurementApplicationType_Backup                       = 0x18,
    ClxBleEsMeasurementApplicationType_Auxiliary                    = 0x19,
    ClxBleEsMeasurementApplicationType_Supplementary                = 0x1A,
    ClxBleEsMeasurementApplicationType_Inside                       = 0x1B,
    ClxBleEsMeasurementApplicationType_Outside                      = 0x1C,
    ClxBleEsMeasurementApplicationType_Left                         = 0x1D,
    ClxBleEsMeasurementApplicationType_Right                        = 0x1E,
    ClxBleEsMeasurementApplicationType_Internal                     = 0x1F,
    ClxBleEsMeasurementApplicationType_External                     = 0x20,
    ClxBleEsMeasurementApplicationType_Solar                        = 0x21
    /* 0x22 - 0xff Reserved for future use */
} ClxBleEsMeasurementApplicationType;

typedef enum ClxBleEsConfigurationTriggerLogicTypeEnum
{
    ClxBleEsConfigurationTriggerLogicType_BooleanAnd    = 0x00,
    ClxBleEsConfigurationTriggerLogicType_BooleanOr     = 0x01
    /* 0x02 - 0xff Reserved for future use */
} ClxBleEsConfigurationTriggerLogicType;

typedef enum ClxBleEsTriggerSettingConditionEnum
{
    ClxBleEsTriggerSettingCondition_TriggerInactive         = 0x00,
    ClxBleEsTriggerSettingCondition_FixedTimeInterval       = 0x01,
    ClxBleEsTriggerSettingCondition_NoLessThanSpecifiedTime = 0x02,
    ClxBleEsTriggerSettingCondition_CompareToPreviousValue  = 0x03,
    ClxBleEsTriggerSettingCondition_LessThanValue           = 0x04,
    ClxBleEsTriggerSettingCondition_LessThanEqualValue      = 0x05,
    ClxBleEsTriggerSettingCondition_GreaterThanValue        = 0x06,
    ClxBleEsTriggerSettingCondition_GreaterThanEqualValue   = 0x07,
    ClxBleEsTriggerSettingCondition_EqualValue              = 0x08,
    ClxBleEsTriggerSettingCondition_NotEqualValue           = 0x09
    /* 0x0a - 0xff Reserved for future use */
} ClxBleEsTriggerSettingCondition;

/************************************
ClxBleAttributeValueType:
************************************/
typedef enum ClxBleAttributeValueTypeEnum
{
    ClxBleAttributeValueType_FixedLength                                = 0,
    ClxBleAttributeValueType_VariableLength                             = 1
} ClxBleAttributeValueType;


/************************************
ClxBleRttiObject:
************************************/
typedef struct ClxBleRttiObjectStruct
{
    const void* rtti;                                                                                                   /* Contains Runtime Type Information. */
} ClxBleRttiObject;


/************************************
ClxBleAttribute:
************************************/
typedef struct ClxBleAttributeStruct
{
    ClxBleRttiObject             base;                                                                                /* Based object. SHALL NOT be set or modified by the application. */

    u2                           handle;                                                                              /* Set by the GATT server. SHALL NOT BE MODIFIED BY THE APPLICATION */ 
    u4                           permissions;   
    ClxGattUuid                  uuid;
    ClxBleAttributeValueType     valueType;                                                                           /* Specifies the type of the value of this attribute (e.g. Fixed Length value, Variable Length value or user defined value type) */
    u4                           groupEndHandle;                                                                      /* Shall be set if this is the first attribute in an attribute group. Otherwise, SHALL be set to CLX_GATT_INVALID_GROUP_END_HANDLE which
                                                                                                                         indicates that this is not an attribute in the beginning of the group. 
                                                                                                                         NOTE : The other attributes in a group (apart from the beginning attribute) SHALL also set this to CLX_GATT_INVALID_GROUP_END_HANDLE. */
    
    void (*initAttribute) (const struct ClxBleAttributeStruct* attr,
                           u2 serviceHandleBase);                                                                    /* Called when the parent service (the service to which this attribute belongs) has been successfully registered in the stack and a service handle
                                                                                                                         base has been assigned to the service. If the attribute value contains any handle value, the implementation of this function must set the handle(s)
                                                                                                                         to the correct value based on the provided service handle base. Optional if no initialization is required (in this case it shall be set to NULL). */
    
    ClxSize (*getCurrentValueLength) (const struct ClxBleAttributeStruct* attr,
                                      u1 remoteDeviceIndex);                                                         /* SHALL be implemented for all attributes. The return value is the length of the current value of the attribute in the encoded format. */

    boolean (*compare) (const struct ClxBleAttributeStruct* attr,
                        u1 remoteDeviceIndex,
                        const u1* data);

    u1      (*readValue) (const struct ClxBleAttributeStruct* attr,
                          u1 remoteDeviceIndex,
                          u1* buf,
                          ClxSize offset, 
                          ClxSize lengthToRead);                                                                      /* SHALL be implemented for all attributes. 
                                                                                                                         The return value is the BLE error code.        
                                                                                                                         NOTE : An implementation does not need to support reading from any arbitrary offset. If the passed offset is not good,
                                                                                                                         the implementation SHALL return ClxBleErrorCodeEnum_InvalidOffset. However, support for reading from offset 0 is mandatory.
                                                                                                                         NOTE : An implementation does not need to check the permissions against this request. This will be done by the ATT layer. */
    u1      (*writeValue) (struct ClxBleAttributeStruct* base,
                           u1 remoteDeviceIndex,
                           const u1* data, 
                           ClxSize offset,
                           ClxSize dataLen);                                                                          /* SHALL be implemented for all attributes. The return value is the BLE error code.
                                                                                                                         NOTE : An implementation does not need to check the permissions against this request. This will be done by the ATT layer. */
} ClxBleAttribute;


/************************************
ClxBlePrimaryServiceAttribute:
************************************/
typedef struct ClxBlePrimaryServiceAttributeStruct
{
    ClxBleAttribute               base;

    ClxGattUuid                   value;
} ClxBlePrimaryServiceAttribute;

/************************************
ClxBleSecondaryServiceAttribute:
************************************/
typedef struct ClxBleSecondaryServiceAttributeStruct
{
    ClxBleAttribute               base;

    ClxGattUuid                   value;
} ClxBleSecondaryServiceAttribute;



struct ClxBleCharacteristicValueAttributeStruct;


/*********************************************************************
ClxBleCharacteristicValue_Encode and ClxBleCharacteristicValue_Decode:
**********************************************************************/
typedef u4 (*ClxBleCharacteristicValue_Encode) (_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);
typedef u4 (*ClxBleCharacteristicValue_Decode) (_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);


/************************************
ClxBleCharacteristicValueAttribute:
************************************/
struct ClxBleCharacteristicValueAttributeStruct
{
    ClxBleAttribute                     base;

    u1* Clx32bitAligned_                buffer;
    ClxSize                             currentDataLength;     /* Used only in case of a variable length characteristic value */ 
    ClxSize                             bufferSize;

    ClxBleCharacteristicValue_Encode    encode;
    ClxBleCharacteristicValue_Decode    decode;
};


typedef struct ClxBleCharacteristicValueAttributeStruct ClxBleCharacteristicValueAttribute;


/****************************************
ClxBleCharacteristicDeclarationAttribute:
*****************************************/
typedef struct ClxBleCharacteristicDeclarationAttributeStruct
{
    ClxBleAttribute                     base;

    u4                                  flag;           /* Set by the GATT server. SHALL NOT be modified by the application */

    ClxGattUuid                         valueUUID;
    u1                                  properties;
} ClxBleCharacteristicDeclarationAttribute;


/************************************************
ClxBleCharacteristicClientConfigurationAttribute:
*************************************************/
typedef struct ClxBleCharacteristicClientConfigurationAttributeStruct
{
    ClxBleAttribute      base;

    u2                   configurationBitsForClient[CLX_GATT_MAX_NUMBER_OF_CONNECTIONS];
} ClxBleCharacteristicClientConfigurationAttribute;

/************************************************
ClxBleCharacteristicServerConfigurationAttribute:
*************************************************/
typedef struct ClxBleCharacteristicServerConfigurationAttributeStruct
{
    ClxBleAttribute     base;

    u2                  configurationBitsForServer;
} ClxBleCharacteristicServerConfigurationAttribute;


/*********************************************
ClxBleCharacteristicPresentationFormatDescriptorAttribute:
**********************************************/
typedef struct ClxBleCharacteristicPresentationFormatDescriptorAttributeStruct
{
    ClxBleAttribute     base;

     u1                 format;
     u1                 exponent;
     u2                 unit;
     u1                 nameSpace;
     u2                 description;
} ClxBleCharacteristicPresentationFormatDescriptorAttribute;


/*********************************************
ClxBleCharacteristicAggregateFormatAttribute:
**********************************************/
typedef struct ClxBleCharacteristicAggregateFormatAttributeStruct
{
    ClxBleAttribute     base;

     ClxBleCharacteristicPresentationFormatDescriptorAttribute*    formatDescriptorList[CLX_GATT_MAX_NUMBER_OF_PRESENTATION_FORMAT_DECLARATIONS];
     u2                 numOfFormatDescriptors;
} ClxBleCharacteristicAggregateFormatAttribute;

/*********************************************
ClxBleCharacteristicIncludeDefinitionAttribute:
**********************************************/
typedef struct ClxBleCharacteristicIncludeDefinitionAttributeStruct
{
    ClxBleAttribute     base;

    u2                  startHandle;
    u2                  endHandle;
    u2                  serviceUUID;
} ClxBleCharacteristicIncludeDefinitionAttribute;

/*********************************************
ClxBleCharacteristicExtendedPropertiesAttribute:
**********************************************/
typedef struct ClxBleCharacteristicExtendedPropertiesAttributeStruct
{
    ClxBleAttribute      base;

     u2                  characteristicExtendedPropertiesBitField;
} ClxBleCharacteristicExtendedPropertiesAttribute;

/*********************************************
ClxBleCharacteristicUserDescriptionAttribute:
**********************************************/
typedef struct ClxBleCharacteristicUserDescriptionAttributeStruct
{
    ClxBleAttribute      base;

     u1*                 userDescription;
     u2                  userDescriptionSize;
} ClxBleCharacteristicUserDescriptionAttribute;

/*******************************************
ClxBleCharacteristicEsMeasurementAttribute:
*******************************************/
typedef struct ClxBleCharacteristicEsMeasurementAttributeStruct
{
    ClxBleAttribute base;

    u2              flags;
    u1              sampling;
    u1              measurementPeriod[3];
    u1              updateInterval[3];
    u1              application;
    u1              measurement;
} ClxBleCharacteristicEsMeasurementAttribute;

/*********************************************
ClxBleCharacteristicEsConfigurationAttribute:
*********************************************/
typedef struct ClxBleCharacteristicEsConfigurationAttributeStruct
{
    ClxBleAttribute base;

    u1              triggerLogic;
} ClxBleCharacteristicEsConfigurationAttribute;

/***************************************
ClxBleCharacteristicValidRangeAttribute:
***************************************/
typedef struct ClxBleCharacteristicValidRangeAttributeSturct
{
    ClxBleAttribute base;

    u2              boundValues;
} ClxBleCharacteristicValidRangeAttribute;

/****************************************************
ClxBleCharacteristicExternalReportReferenceAttribute:
****************************************************/
typedef struct ClxBleCharacteristicExternalReportReferenceAttributeStruct
{
    ClxBleAttribute base;
    ClxGattUuid     externalRefUUID;
} ClxBleCharacteristicExternalReportReferenceAttribute;

/********************************************
ClxBleCharacteristicReportReferenceAttribute:
********************************************/
typedef struct ClxBleCharacteristicReportReferenceAttributeStruct
{
    ClxBleAttribute base;
    u1              reportId;
    u1              reportType;
}ClxBleCharacteristicReportReferenceAttribute;

/*********************************************
ClxBleCharacteristicNumberOfDigitalsAttribute:
*********************************************/
typedef struct ClxBleCharacteristicNumberOfDigitalsAttributeStruct
{
    ClxBleAttribute base;
    u1              noOfDigitals;
}ClxBleCharacteristicNumberOfDigitalsAttribute;

/***************************************************************************************
ClxBleCharacteristicTriggerSetting_Encode and ClxBleCharacteristicTriggerSetting_Decode:
***************************************************************************************/
typedef u4 (*ClxBleCharacteristicTriggerSetting_Encode) (_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);
typedef u4 (*ClxBleCharacteristicTriggerSetting_Decode) (_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);

/*******************************************
ClxBleCharacteristicTriggerSettingAttribute:
*******************************************/
typedef struct ClxBleCharacteristicTriggerSettingAttributeStruct
{
    ClxBleAttribute                             base;

    u1* Clx32bitAligned_                        buffer;
    ClxSize                                     currentDataLength;     /* Used only in case of a variable length characteristic value */ 
    ClxSize                                     bufferSize;

    ClxBleCharacteristicTriggerSetting_Encode   encode;
    ClxBleCharacteristicTriggerSetting_Decode   decode;
}ClxBleCharacteristicTriggerSettingAttribute;

/**
Holds the Gatt database for an application. The database is statically defined at compile time and would not change during the life cycle of the application
*/
typedef struct ClxBleGattDatabaseStruct
{
    ClxBleAttribute**   attrList;
    ClxSize             numberOfAttributes;
} ClxBleGattDatabase;

/**
Provides the interface for the Gatt service
*/
typedef struct ClxBleGattServiceInterfaceStruct
{
    ClxBleGattDatabase* (*initInstance) (const ClxConfigList* configList);
    void (*destroyInstance) (ClxBleGattDatabase* database);
    void (*baseHandleUpdated) (u2 baseHandle);
} ClxBleGattServiceInterface;

/**
Holds the  Gatt service database.
*/
typedef struct ClxBleGattServiceInfoStruct
{
    u2                                  handleBase;
    const s1*                           name;
    const ClxBleGattServiceInterface*   (*gettGattServiceInterface) ();
    const s1*                           (*getGattServiceCharacteristicName) (u2 handleIndex);
} ClxBleGattServiceInfo;


/**
Return a ClxGattUuid object with the specified 2 byte uuid.
*/
extern void clxInitGattUuid2(ClxGattUuid* obj, 
                             u2 uuid);

/*
Initializes a ClxGattUuid object with the specified 16 byte uuid stored in a buffer, in Big Endian byte order:

uuid[0] is MSB
...
uuid[15] is LSB

NOTE : UUIDs are transferred over the air in Little Endian order. Do NOT use this function to initialize ClxGattUuid object with a received UUID (e.g. in received advertising data).
Use the function #clxDecodeGattUuid() for that purpose.
*/
extern void clxInitGattUuid16(ClxGattUuid* obj, 
                              const u1* uuid);

/**
Returns a ClxGattUuid object with the specified 16 byte string uuid
*/
extern boolean clxInitGattUuid16FromAscii(ClxGattUuid* obj,
                                          const s1* str);

/**
Returns TRUE if UUID arg1 is the same as UUID arg2. Otherwise, returns FALSE. 
obj1 and obj2 CANNOT be NULL.

NOTE : A 128bit UUID may be compared to a 16bit UUID only if it belongs to Bluetooth SIG 
(All 16bit UUIDs are assumed to belong to Bluetooth SIG).
*/
extern boolean clxIsGattUuidsEqual(const ClxGattUuid* obj1, 
                                   const ClxGattUuid* obj2);

/**
Encodes an object of type ClxGattUuid into a buffer in the over-the-air (Little Endian) byte order.
Use this function to add a UUID in the advertising data.

The length of the output depends on the type of input UUID:

- if uuid->type is ClxGattUuidType_Uuid2, the output will be 2 bytes.
- if uuid->type is ClxGattUuidType_Uuid16, the output will be 16 bytes.

The output buffer shall be large enough to accommodate the UUID in binary encoded form.
*/
extern void clxEncodeGattUuid(const ClxGattUuid* uuid, u1* output);

/**
Decodes a UUID encoded in over-the-air (Little Endian) byte order into an object of type ClxGattUuid.
Use this function to read a UUID from received advertising data.

inputSize SHALL be either 2 or 16.

The type of the output object (uuid->type) depends on inputSize:

- if inputSize is 2, uuid->type will be ClxGattUuidType_Uuid2.
- if inputSize is 16, uuid->type will be ClxGattUuidType_Uuid16.

\return TRUE if the operation has been successful.
FALSE if inputSize is neither 2 or 16.
*/
extern boolean clxDecodeGattUuid(ClxGattUuid* uuid, const u1* input, u4 inputSize);


/**
Must be used to initialise a primary service attribute, with UUID serviceUUID. 
The final attribute corresponding to this service or a characteristic in this service is at groupEndHandle
*/
extern void clxInitBlePrimaryServiceAttribute(ClxBlePrimaryServiceAttribute* base, 
                                              const ClxGattUuid* serviceUUID,
                                              u2 groupEndHandle);

/**
Must be used to initialise a secondary service attribute, with UUID serviceUUID. 
The final attribute corresponding to this service or a characteristic in this service is at groupEndHandle
*/
extern void clxInitBleSecondaryServiceAttribute(ClxBleSecondaryServiceAttribute* base, 
                                                const ClxGattUuid* serviceUUID,
                                                u2 groupEndHandle);

/**
Must be used to initialise a Characteristic Declaration attribute with corresponding characteristic properties, 
corresponding characteristic value attribute handle and corresponding characteristic UUID specified in valueUUID
*/
extern void clxInitBleCharacteristicDeclarationAttribute(ClxBleCharacteristicDeclarationAttribute* base,
                                                         const ClxGattUuid* valueUUID);


/**
Must be used to initialise a Characteristic Client Configuration Attribute
*/
extern void clxInitBleCharacteristicClientConfigurationAttribute(ClxBleCharacteristicClientConfigurationAttribute* base);

/**
Must be used to initialise a Characteristic Client Configuration Attribute with specified configuration bits
*/
extern void clxInitBleCharacteristicServerConfigurationAttribute(ClxBleCharacteristicServerConfigurationAttribute* base, 
                                                                 u2 characteristicConfigurationBits);

/**
Must be used to initialise a Characteristic Aggregate format Attribute, with a list of characteristic presentation format handles 
and the number of characteristic presentation format handles defined in that list
*/
extern void clxInitBleCharacteristicAggregateFormatAttribute(ClxBleCharacteristicAggregateFormatAttribute* base, 
                                                             ClxBleCharacteristicPresentationFormatDescriptorAttribute** formatDescriptorList, 
                                                             u2 numOfFormatDescriptors);

/**
Must be used to initialise a characteristic extended properties attribute with specified properties
*/
extern void clxInitBleCharacteristicExtendedPropertiesAttribute(ClxBleCharacteristicExtendedPropertiesAttribute* base, 
                                                                u2 characteristicExtendedPropertiesBitField);

/*
Must be used to initialise a characteristic user description attribute to explain attribute. 
userDecsription is a char array of ascii characters of specified size
*/
extern void clxInitBleCharacteristicUserDescriptionAttribute(ClxBleCharacteristicUserDescriptionAttribute* base, 
                                                             u1* userDescription, 
                                                             u2 userDescriptionSize,
                                                             u4 permissions);

/**
Must be used to initialise a characteristic include definition to point to secondary services to a primary service from start handle to end handle
*/
extern void clxInitBleCharacteristicIncludeDefinitionAttribute(ClxBleCharacteristicIncludeDefinitionAttribute* base, 
                                                               u2 startHandle,  
                                                               u2 endHandle,  
                                                               u2 serviceUUID);

/**
Must be used to initialise a characteristic format descriptor. 
If more than one is required, a characteristic aggregate format declaration is required
*/
extern void clxInitBleCharacteristicPresentationFormatDescriptorAttribute(ClxBleCharacteristicPresentationFormatDescriptorAttribute* base, 
                                                                          u2 description, 
                                                                          u1 format, 
                                                                          u1 exponent, 
                                                                          u1 namesSpace, 
                                                                          u2 unit);

/**
Used for defining values of characteristics with fixed length values.
*/
extern void clxInitBleCharacteristicValueAttribute(ClxBleCharacteristicValueAttribute* attr,
                                                   const ClxGattUuid* valueUUID,
                                                   ClxBleAttributeValueType valueType,
                                                   u1* Clx32bitAligned_ dataBuffer,
                                                   ClxSize dataBufferSize,
                                                   u4 permissions,
                                                   ClxBleCharacteristicValue_Encode encoder,
                                                   ClxBleCharacteristicValue_Decode decoder);

/**
Must be used to initialise a characteristic Environmental Sensing Measurement descriptor.
*/
extern void clxInitBleCharacteristicEsMeasurementDescriptorAttribute(ClxBleCharacteristicEsMeasurementAttribute* base,
                                                                     u2  flags,
                                                                     u1  sampling,
                                                                     u1* measurementPeriod,
                                                                     u1* updateInterval,
                                                                     u1  application,
                                                                     u1  measurement);

/**
Must be used to initialise a characteristic Environmental Sensing Configuration descriptor.
*/
extern void clxInitBleCharacteristicEsConfigurationDescriptorAttribute(ClxBleCharacteristicEsConfigurationAttribute* base,
                                                                       u1 triggerLogic);

/**
Must be used to initialise a characteristic Valid Range descriptor.
*/
extern void clxInitBleCharacteristicValidRangeDescriptorAttribute(ClxBleCharacteristicValidRangeAttribute* base, u2 boundValues);

/**
Must be used to initialise a characteristic External Report Reference descriptor.
*/
extern void clxInitBleCharacteristicExternalReportReferenceDescriptorAttribute(ClxBleCharacteristicExternalReportReferenceAttribute* base,
                                                                               const ClxGattUuid* externalRefUUID);

/**
Must be used to initialise a characteristic Report Reference descriptor.
*/
extern void clxInitBleCharacteristicReportReferenceDescriptorAttribute(ClxBleCharacteristicReportReferenceAttribute* base,
                                                                       u1 reportId,
                                                                       u1 reportType);

/**
Must be used to initialise a characteristic Number of Digitals descriptor.
*/
extern void clxInitBleCharacteristicNumberOfDigitalsDescriptorAttribute(ClxBleCharacteristicNumberOfDigitalsAttribute* base,
                                                                        u1 noOfDigitals);

/**
Must be used to initialise the following descriptors
    1) Environmental Trigger Setting descriptor
    2) Value Trigger Setting descriptor
    3) Time Trigger Setting descriptor

The application should pass the corresponding uuid on the parameter 'descriptorUUID'.
*/
extern void clxInitBleCharacteristicTriggerSettingDescriptorAttribute(ClxBleCharacteristicTriggerSettingAttribute* base,
                                                                      const ClxGattUuid* descriptorUUID,
                                                                      u1* Clx32bitAligned_ dataBuffer,
                                                                      ClxSize dataBufferSize,
                                                                      ClxBleCharacteristicTriggerSetting_Encode encoder,
                                                                      ClxBleCharacteristicTriggerSetting_Decode decoder);

#ifdef __cplusplus
}
#endif


#endif  // __Gatt_Ble_Service_h__

