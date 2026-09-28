#ifndef __org_bluetooth_service_human_interface_device_h__
#define __org_bluetooth_service_human_interface_device_h__

/********************************************************************************
*
* Project             BLE GATT Combined SIG Application
* File                org.bluetooth.service.human_interface_device.h
* Description         Declares definitions for the GATT Human Interface Device
*                     Service.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/**
Human Interface Device GATT Service:
This service exposes the HID reports and other HID data intended for HID Hosts and HID Devices.
*/
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_NAME    "Human Interface Device"
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_UUID    0x1812

/**
Protocol Mode Characteristic:
The Protocol Mode characteristic is used to expose the current protocol mode of the HID Service with which it is associated, or to set the desired protocol mode of the HID Service
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicProtocolModeFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE                 "Protocol Mode"
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE)
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_STRUCT          struct ClxOrgBluetoothCharacteristicProtocolModeFields
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_VALUE_TYPE      ClxOrgBluetoothCharacteristicProtocolModeFields_Type
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_SIZE            ClxOrgBluetoothCharacteristicProtocolModeFields_Size
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_UUID            0x2A4E


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicProtocolMode.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicProtocolMode.
*/
struct ClxOrgBluetoothCharacteristicProtocolModeFields
{
    /**
    Field : Protocol Mode Value
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Value Enumerations :
    {
        0 : Boot Protocol Mode
        1 : Report Protocol Mode
    }
    */
    u1 protocolModeValue;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicProtocolModeFields
*/
#define ClxOrgBluetoothCharacteristicProtocolModeFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicProtocolModeFields
*/
#define ClxOrgBluetoothCharacteristicProtocolModeFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicProtocolModeFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicProtocolModeFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicProtocolModeFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicProtocolMode(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicProtocolModeFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicProtocolModeFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicProtocolModeFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicProtocolMode(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Report Characteristic:
The Report characteristic is used to exchange data between a HID Device and a HID Host.
Note: Mandatory to support at least one Report Type (Input Report, Output Report, or Feature Report) if the Report characteristic is supported.
The Report Reference characteristic descriptor is used to provide the Report ID and Report Type for the Report characteristic value.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicReportFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT                 "Report"
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_HANDLE_INDEX    4
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_STRUCT          struct ClxOrgBluetoothCharacteristicReportFields
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_VALUE_TYPE      ClxOrgBluetoothCharacteristicReportFields_Type
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_SIZE            ClxOrgBluetoothCharacteristicReportFields_Size
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_UUID            0x2A4D


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicReport.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicReport.
*/
struct ClxOrgBluetoothCharacteristicReportFields
{
    /**
    Field : Report Value
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 reportValue;
    
    /**
    Field : Report ID
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 255
    */
    u1 reportId;
    
    /**
    Field : Report Type
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 1
    Maximum : 3
    Value Enumerations :
    {
        1 : Input Report
        2 : Output report
        3 : Feature Report
    }
    */
    u1 reportType;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicReportFields
*/
#define ClxOrgBluetoothCharacteristicReportFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicReportFields
*/
#define ClxOrgBluetoothCharacteristicReportFields_Size    (512)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicReportFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicReportFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicReportFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicReport(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicReportFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicReportFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicReportFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicReport(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Report Map Characteristic:
The Report Map characteristic value contains formatting and other information for Input Report, Output Report and Feature Report data transferred between a HID Device and HID Host.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicReportMapFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP                 "Report Map"
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_HANDLE_INDEX    7
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_STRUCT          struct ClxOrgBluetoothCharacteristicReportMapFields
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_VALUE_TYPE      ClxOrgBluetoothCharacteristicReportMapFields_Type
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_SIZE            ClxOrgBluetoothCharacteristicReportMapFields_Size
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_UUID            0x2A4B


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicReportMap.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicReportMap.
*/
struct ClxOrgBluetoothCharacteristicReportMapFields
{
    /**
    Field : Report Map Value
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 reportMapValue;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicReportMapFields
*/
#define ClxOrgBluetoothCharacteristicReportMapFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicReportMapFields
*/
#define ClxOrgBluetoothCharacteristicReportMapFields_Size    (512)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicReportMapFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicReportMapFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicReportMapFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicReportMap(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicReportMapFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicReportMapFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicReportMapFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicReportMap(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Boot Keyboard Input Report Characteristic:
The Boot Report Reference characteristic is used to provide HID Hosts operating in Boot Protocol Mode with a simplified method of discovering certain HID Service characteristics. Only a single instance of this characteristic exists as part of the HID Service.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT                 "Boot Keyboard Input Report"
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_HANDLE_INDEX    9
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_STRUCT          struct ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_VALUE_TYPE      ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields_Type
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_SIZE            ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields_Size
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_UUID            0x2A22


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicBootKeyboardInputReport.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicBootKeyboardInputReport.
*/
struct ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields
{
    /**
    Field : Boot Keyboard Input Report Value
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 bootKeyboardInputReportValue;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields
*/
#define ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields
*/
#define ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields_Size    (512)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBootKeyboardInputReport(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBootKeyboardInputReportFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBootKeyboardInputReport(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Boot Keyboard Output Report Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT                 "Boot Keyboard Output Report"
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_HANDLE_INDEX    12
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE)
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_STRUCT          struct ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_VALUE_TYPE      ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields_Type
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_SIZE            ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields_Size
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_UUID            0x2A32


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicBootKeyboardOutputReport.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicBootKeyboardOutputReport.
*/
struct ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields
{
    /**
    Field : Boot Keyboard Output Report Value
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 bootKeyboardOutputReportValue;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields
*/
#define ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields
*/
#define ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields_Size    (512)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBootKeyboardOutputReport(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBootKeyboardOutputReportFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBootKeyboardOutputReport(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
HID Information Characteristic:
The HID Information characteristic is used to hold a set of values known as the HID Device?s HID Attributes
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicHidInformationFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION                 "HID Information"
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_HANDLE_INDEX    14
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_STRUCT          struct ClxOrgBluetoothCharacteristicHidInformationFields
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_VALUE_TYPE      ClxOrgBluetoothCharacteristicHidInformationFields_Type
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_SIZE            ClxOrgBluetoothCharacteristicHidInformationFields_Size
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_UUID            0x2A4A


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicHidInformation.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicHidInformation.
*/
struct ClxOrgBluetoothCharacteristicHidInformationFields
{
    /**
    Field : bcdHID
    Format : uint16
    Unit : Not Available
    Description : 16-bit unsigned integer representing version number of base USB HID Specification implemented by HID Device
    Requirement : Mandatory
    */
    u2 bcdhid;
    
    /**
    Field : bCountryCode
    Format : 8bit
    Unit : Not Available
    Description : Identifies which country the hardware is localized for. Most hardware is not localized and thus this value would be zero (0).
    Requirement : Mandatory
    */
    u1 bcountrycode;
    
    /**
    Field : Flags
    Format : 8bit
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Value BitField :
    {
        Index 0 : RemoteWake
        {
            0 : The device is not designed to be capable of providing wake-up signal to a HID host
            1 : The device is designed to be capable of providing wake-up signal to a HID host
        }
        Index 1 : NormallyConnectable
        {
            0 : The device is not normally connectable
            1 : The device is normally connectable
        }
    }
    */
    u1 flags;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicHidInformationFields
*/
#define ClxOrgBluetoothCharacteristicHidInformationFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicHidInformationFields
*/
#define ClxOrgBluetoothCharacteristicHidInformationFields_Size    (2 + 1 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicHidInformationFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicHidInformationFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHidInformationFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicHidInformation(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicHidInformationFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicHidInformationFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHidInformationFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicHidInformation(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
HID Control Point Characteristic:
The HID Control Point characteristic is a control-point attribute that defines the HID Commands like Suspend and Exit Suspend.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicHidControlPointFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT                 "HID Control Point"
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_HANDLE_INDEX    16
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE)
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_STRUCT          struct ClxOrgBluetoothCharacteristicHidControlPointFields
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_VALUE_TYPE      ClxOrgBluetoothCharacteristicHidControlPointFields_Type
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_SIZE            ClxOrgBluetoothCharacteristicHidControlPointFields_Size
#define CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_UUID            0x2A4C


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicHidControlPoint.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicHidControlPoint.
*/
struct ClxOrgBluetoothCharacteristicHidControlPointFields
{
    /**
    Field : HID Control Point Command
    Format : uint8
    Unit : Not Available
    Description : There are no response codes defined for the Suspend and Exit Suspend commands.
    Requirement : Mandatory
    Value Enumerations :
    {
        0 : Suspend
        1 : Exit Suspend
    }
    */
    u1 hidControlPointCommand;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicHidControlPointFields
*/
#define ClxOrgBluetoothCharacteristicHidControlPointFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicHidControlPointFields
*/
#define ClxOrgBluetoothCharacteristicHidControlPointFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicHidControlPointFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicHidControlPointFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHidControlPointFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicHidControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicHidControlPointFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicHidControlPointFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicHidControlPointFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicHidControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Human Interface Device GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Human Interface Device GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetHumanInterfaceDeviceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __org_bluetooth_service_human_interface_device_h__

