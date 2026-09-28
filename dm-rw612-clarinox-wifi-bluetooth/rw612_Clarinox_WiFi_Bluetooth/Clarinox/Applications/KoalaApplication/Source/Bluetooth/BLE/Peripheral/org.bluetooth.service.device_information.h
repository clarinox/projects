#ifndef __org_bluetooth_service_device_information_h__
#define __org_bluetooth_service_device_information_h__

/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.device_information.h
* Description         Declares definitions for the GATT Device Information
*                     service.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/**
Device Information GATT Service:
The Device Information Service exposes manufacturer and/or vendor information about a device.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_NAME    "Device Information"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_UUID    0x180A

/**
Manufacturer Name String Characteristic:
This characteristic represents the name of the manufacturer of the device.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicManufacturerNameStringFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING                 "Manufacturer Name String"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_STRUCT          struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_VALUE_TYPE      ClxOrgBluetoothCharacteristicManufacturerNameStringFields_Type
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_SIZE            ClxOrgBluetoothCharacteristicManufacturerNameStringFields_Size
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_UUID            0x2A29


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicManufacturerNameString.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicManufacturerNameString.
*/
struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields
{
    /**
    Field : Manufacturer Name
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s1 manufacturerName[16];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicManufacturerNameStringFields
*/
#define ClxOrgBluetoothCharacteristicManufacturerNameStringFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicManufacturerNameStringFields
*/
#define ClxOrgBluetoothCharacteristicManufacturerNameStringFields_Size    (16)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicManufacturerNameStringFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicManufacturerNameStringFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicManufacturerNameString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicManufacturerNameStringFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicManufacturerNameStringFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicManufacturerNameString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Model Number String Characteristic:
This characteristic represents the model number that is assigned by the device vendor.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicModelNumberStringFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING                 "Model Number String"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_HANDLE_INDEX    4
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_STRUCT          struct ClxOrgBluetoothCharacteristicModelNumberStringFields
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_VALUE_TYPE      ClxOrgBluetoothCharacteristicModelNumberStringFields_Type
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_SIZE            ClxOrgBluetoothCharacteristicModelNumberStringFields_Size
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_UUID            0x2A24


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicModelNumberString.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicModelNumberString.
*/
struct ClxOrgBluetoothCharacteristicModelNumberStringFields
{
    /**
    Field : Model Number
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s1 modelNumber[16];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicModelNumberStringFields
*/
#define ClxOrgBluetoothCharacteristicModelNumberStringFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicModelNumberStringFields
*/
#define ClxOrgBluetoothCharacteristicModelNumberStringFields_Size    (16)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicModelNumberStringFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicModelNumberStringFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicModelNumberStringFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicModelNumberString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicModelNumberStringFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicModelNumberStringFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicModelNumberStringFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicModelNumberString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Serial Number String Characteristic:
This characteristic represents the serial number for a particular instance of the device.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSerialNumberStringFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING                 "Serial Number String"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_HANDLE_INDEX    6
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_STRUCT          struct ClxOrgBluetoothCharacteristicSerialNumberStringFields
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_VALUE_TYPE      ClxOrgBluetoothCharacteristicSerialNumberStringFields_Type
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_SIZE            ClxOrgBluetoothCharacteristicSerialNumberStringFields_Size
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_UUID            0x2A25


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicSerialNumberString.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicSerialNumberString.
*/
struct ClxOrgBluetoothCharacteristicSerialNumberStringFields
{
    /**
    Field : Serial Number
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s1 serialNumber[16];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSerialNumberStringFields
*/
#define ClxOrgBluetoothCharacteristicSerialNumberStringFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicSerialNumberStringFields
*/
#define ClxOrgBluetoothCharacteristicSerialNumberStringFields_Size    (16)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSerialNumberStringFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicSerialNumberStringFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSerialNumberStringFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSerialNumberString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSerialNumberStringFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicSerialNumberStringFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSerialNumberStringFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSerialNumberString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Hardware Revision String Characteristic:
This characteristic represents the hardware revision for the hardware within the device.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicHardwareRevisionStringFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING                 "Hardware Revision String"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_HANDLE_INDEX    8
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_STRUCT          struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_VALUE_TYPE      ClxOrgBluetoothCharacteristicHardwareRevisionStringFields_Type
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_SIZE            ClxOrgBluetoothCharacteristicHardwareRevisionStringFields_Size
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_UUID            0x2A27


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicHardwareRevisionString.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicHardwareRevisionString.
*/
struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields
{
    /**
    Field : Hardware Revision
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s1 hardwareRevision[16];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicHardwareRevisionStringFields
*/
#define ClxOrgBluetoothCharacteristicHardwareRevisionStringFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicHardwareRevisionStringFields
*/
#define ClxOrgBluetoothCharacteristicHardwareRevisionStringFields_Size    (16)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicHardwareRevisionStringFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicHardwareRevisionStringFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicHardwareRevisionString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicHardwareRevisionStringFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicHardwareRevisionStringFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicHardwareRevisionString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Firmware Revision String Characteristic:
This characteristic represents the firmware revision for the firmware within the device.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING                 "Firmware Revision String"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_HANDLE_INDEX    10
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_STRUCT          struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_VALUE_TYPE      ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields_Type
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_SIZE            ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields_Size
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_UUID            0x2A26


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicFirmwareRevisionString.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicFirmwareRevisionString.
*/
struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields
{
    /**
    Field : Firmware Revision
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s1 firmwareRevision[16];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields
*/
#define ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields
*/
#define ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields_Size    (16)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicFirmwareRevisionString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicFirmwareRevisionString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Software Revision String Characteristic:
This characteristic represents the software revision for the software within the device.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING                 "Software Revision String"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_HANDLE_INDEX    12
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_STRUCT          struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_VALUE_TYPE      ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields_Type
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_SIZE            ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields_Size
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_UUID            0x2A28


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicSoftwareRevisionString.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicSoftwareRevisionString.
*/
struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields
{
    /**
    Field : Software Revision
    Format : utf8s
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    s1 softwareRevision[16];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields
*/
#define ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields
*/
#define ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields_Size    (16)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSoftwareRevisionString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields.

\param[ in  ] data A caller-provided buffer containing the data in encoded format.
\param[ in  ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields which, on a successful return, will contain the data in decoded format.
\param[ in  ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSoftwareRevisionString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
System ID Characteristic:
This characteristic represents a structure containing an Organizationally Unique Identifier (OUI) followed by a manufacturer-defined identifier and is unique for each individual instance of the product.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSystemIdFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID                 "System ID"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_HANDLE_INDEX    14
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_STRUCT          struct ClxOrgBluetoothCharacteristicSystemIdFields
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_VALUE_TYPE      ClxOrgBluetoothCharacteristicSystemIdFields_Type
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_SIZE            ClxOrgBluetoothCharacteristicSystemIdFields_Size
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_UUID            0x2A23


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicSystemId.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicSystemId.
*/
struct ClxOrgBluetoothCharacteristicSystemIdFields
{
    /**
    Field : Manufacturer Identifier
    Format : uint40
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 1099511627775
    */
    ClxUInteger64 manufacturerIdentifier;
    
    /**
    Field : Organizationally Unique Identifier
    Format : uint24
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 16777215
    */
    u4 organizationallyUniqueIdentifier;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSystemIdFields
*/
#define ClxOrgBluetoothCharacteristicSystemIdFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicSystemIdFields
*/
#define ClxOrgBluetoothCharacteristicSystemIdFields_Size    (5 + 3)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSystemIdFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicSystemIdFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSystemIdFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSystemId(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSystemIdFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicSystemIdFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSystemIdFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSystemId(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
IEEE 11073-20601 Regulatory Certification Data List Characteristic:
This characteristic represents regulatory and certification information for the product in a list defined in IEEE 11073-20601.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST                 "IEEE 11073-20601 Regulatory Certification Data List"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_HANDLE_INDEX    16
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_STRUCT          struct ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_VALUE_TYPE      ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields_Type
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_SIZE            ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields_Size
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_UUID            0x2A2A


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataList.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataList.
*/
struct ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields
{
    /**
    Field : Data
    Format : reg-cert-data-list
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 certificationData[16];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields
*/
#define ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields
*/
#define ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields_Size    (16)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataList(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataList(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
PnP ID Characteristic:
The PnP_ID characteristic is a set of values used to create a device ID value that is unique for this device.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicPnpIdFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID                 "PnP ID"
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_HANDLE_INDEX    18
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_STRUCT          struct ClxOrgBluetoothCharacteristicPnpIdFields
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_VALUE_TYPE      ClxOrgBluetoothCharacteristicPnpIdFields_Type
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_SIZE            ClxOrgBluetoothCharacteristicPnpIdFields_Size
#define CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_UUID            0x2A50


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicPnpId.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicPnpId.
*/
struct ClxOrgBluetoothCharacteristicPnpIdFields
{
    /**
    Field : Vendor ID Source
    Format : uint8
    Unit : Not Available
    Description : Identifies the source of the Vendor ID field
    Requirement : Mandatory
    Minimum : 1
    Maximum : 2
    Value Enumerations :
    {
        1 : Bluetooth SIG assigned Company Identifier value from the Assigned Numbers document        
        2 : USB Implementer?s Forum assigned Vendor ID value        
    }
    */
    u1 vendorIdSource;
    
    /**
    Field : Vendor ID
    Format : uint16
    Unit : Not Available
    Description : Identifies the product vendor from the namespace in the Vendor ID Source
    Requirement : Mandatory
    */
    u2 vendorId;
    
    /**
    Field : Product ID
    Format : uint16
    Unit : Not Available
    Description : Manufacturer managed identifier for this product
    Requirement : Mandatory
    */
    u2 productId;
    
    /**
    Field : Product Version
    Format : uint16
    Unit : Not Available
    Description : Manufacturer managed version for this product
    Requirement : Mandatory
    */
    u2 productVersion;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicPnpIdFields
*/
#define ClxOrgBluetoothCharacteristicPnpIdFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicPnpIdFields
*/
#define ClxOrgBluetoothCharacteristicPnpIdFields_Size    (1 + 2 + 2 + 2)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicPnpIdFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicPnpIdFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicPnpIdFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicPnpId(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicPnpIdFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicPnpIdFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicPnpIdFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicPnpId(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Device Information GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Device Information GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetDeviceInformationGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __org_bluetooth_service_device_information_h__

