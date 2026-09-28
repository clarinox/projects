#ifndef __C_Bleservicegenerator_Xml_Custom_OrgBluetoothServiceGenericAccess__
#define __C_Bleservicegenerator_Xml_Custom_OrgBluetoothServiceGenericAccess__

/*******************************************************************************
*
* Project             ClarinoxBlue Low Energy
* File                org.bluetooth.service.generic_access.h
* Description         Declares definitions for the GATT service Generic Access
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
Generic Access GATT Service:
The generic_access service contains generic information about the device. All available Characteristics are readonly.
*/
#define CLX_GATT_SERVICE_GENERIC_ACCESS_NAME    "Generic Access"
#define CLX_GATT_SERVICE_GENERIC_ACCESS_UUID    0x1800

/**
Device Name Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGapDeviceNameFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME                 "Device Name"
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_HANDLE_INDEX    3
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE)
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_STRUCT          struct ClxOrgBluetoothCharacteristicGapDeviceNameFields
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_VALUE_TYPE      ClxOrgBluetoothCharacteristicGapDeviceNameFields_Type
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_SIZE            ClxOrgBluetoothCharacteristicGapDeviceNameFields_Size
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_UUID            0x2A00


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGapDeviceName.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGapDeviceName.
*/
struct ClxOrgBluetoothCharacteristicGapDeviceNameFields
{
    /**
    Field : Name
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u4 name_Length;
    s1 name[248];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGapDeviceNameFields
*/
#define ClxOrgBluetoothCharacteristicGapDeviceNameFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGapDeviceNameFields
*/
#define ClxOrgBluetoothCharacteristicGapDeviceNameFields_Size    (248)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGapDeviceNameFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGapDeviceNameFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapDeviceNameFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGapDeviceName(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGapDeviceNameFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGapDeviceNameFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapDeviceNameFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGapDeviceName(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Appearance Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGapAppearanceFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE                 "Appearance"
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_HANDLE_INDEX    5
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_STRUCT          struct ClxOrgBluetoothCharacteristicGapAppearanceFields
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_VALUE_TYPE      ClxOrgBluetoothCharacteristicGapAppearanceFields_Type
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_SIZE            ClxOrgBluetoothCharacteristicGapAppearanceFields_Size
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_UUID            0x2A01


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGapAppearance.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGapAppearance.
*/
struct ClxOrgBluetoothCharacteristicGapAppearanceFields
{
    /**
    Field : Category
    Format : 16bit
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u2 category;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGapAppearanceFields
*/
#define ClxOrgBluetoothCharacteristicGapAppearanceFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGapAppearanceFields
*/
#define ClxOrgBluetoothCharacteristicGapAppearanceFields_Size    (2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGapAppearanceFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGapAppearanceFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapAppearanceFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGapAppearance(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGapAppearanceFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGapAppearanceFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapAppearanceFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGapAppearance(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Peripheral Preferred Connection Parameters Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS                 "Peripheral Preferred Connection Parameters"
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_HANDLE_INDEX    7
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_STRUCT          struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_VALUE_TYPE      ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields_Type
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_SIZE            ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields_Size
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_UUID            0x2A04


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParameters.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParameters.
*/
struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields
{
    /**
    Field : Minimum Connection Interval
    Format : uint16
    Unit : Not Available
    Description : connInterval_min = Minimum Connection Interval * 1.25 ms
    Requirement : Mandatory
    Minimum : 6
    Maximum : 3200
    */
    u2 minimumConnectionInterval;
    
    /**
    Field : Maximum Connection Interval
    Format : uint16
    Unit : Not Available
    Description : connInterval_max = Maximum Connection Interval * 1.25 ms. and is equal or greater than the Minimum Connection Interval
    Requirement : Mandatory
    Minimum : 6
    Maximum : 3200
    */
    u2 maximumConnectionInterval;
    
    /**
    Field : Slave Latency
    Format : uint16
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 1000
    */
    u2 slaveLatency;
    
    /**
    Field : Connection Supervision Timeout Multiplier
    Format : uint16
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 10
    Maximum : 3200
    */
    u2 connectionSupervisionTimeoutMultiplier;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields
*/
#define ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields
*/
#define ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields_Size    (2 + 2 + 2 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParameters(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParameters(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Central Address Resolution Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION                 "Central Address Resolution"
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_HANDLE_INDEX    9
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_STRUCT          struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_VALUE_TYPE      ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields_Type
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_SIZE            ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields_Size
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_UUID            0x2AA6


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGapCentralAddressResolutionSupport.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGapCentralAddressResolutionSupport.
*/
struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields
{
    /**
    Field : addressResolution
    Format : 8bit
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 addressresolution;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields
*/
#define ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields
*/
#define ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGapCentralAddressResolutionSupport(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGapCentralAddressResolutionSupport(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Resolvable Private Address Only Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY                 "Resolvable Private Address Only"
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_HANDLE_INDEX    11
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_STRUCT          struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_VALUE_TYPE      ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields_Type
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_SIZE            ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields_Size
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_UUID            0x2AC9

/**
Encrypted Data Key Material Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL                 "Encrypted Data Key Material"
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_HANDLE_INDEX    13
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_INDICATABLE)
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_STRUCT          struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_VALUE_TYPE      ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields_Type
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_SIZE            ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields_Size
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_UUID            0x2AC9

/**
LE GATT Security Levels Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS                 "LE GATT Security Levels"
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_HANDLE_INDEX    15
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_STRUCT          struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_VALUE_TYPE      ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields_Type
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_SIZE            ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields_Size
#define CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_UUID            0x2A03


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGapLeGattSecurityLevels.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGapLeGattSecurityLevels.
*/
struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields
{
    /**
    Field : gattSecurity
    Format : uint16
    Unit : Not Available
    Description : Not Available
    */
    u2 gattsecurity;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields
*/
#define ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields
*/
#define ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields_Size    (2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGapLeGattSecurityLevels(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGapLeGattSecurityLevels(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Generic Access GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Generic Access GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetGenericAccessGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __C_Bleservicegenerator_Xml_Custom_OrgBluetoothServiceGenericAccess__

