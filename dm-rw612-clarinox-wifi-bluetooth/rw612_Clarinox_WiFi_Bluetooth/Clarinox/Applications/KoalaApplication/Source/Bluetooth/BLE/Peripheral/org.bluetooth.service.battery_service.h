#ifndef __org_bluetooth_service_battery_service_h__
#define __org_bluetooth_service_battery_service_h__

/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.battery_service.h
* Description         Declares definitions for the GATT Battery Service
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/**
Battery Service GATT Service:
The Battery Service exposes the state of a battery within a device.
*/
#define CLX_GATT_SERVICE_BATTERY_SERVICE_NAME    "Battery Service"
#define CLX_GATT_SERVICE_BATTERY_SERVICE_UUID    0x180F

/**
Battery Level Characteristic:
The Battery Level characteristic is read using the GATT Read Characteristic Value sub-procedure and returns the current battery level as a percentage from 0% to 100%;
0% represents a battery that is fully discharged, 100% represents a battery that is fully charged.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicBatteryLevelFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL                 "Battery Level"
#define CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_STRUCT          struct ClxOrgBluetoothCharacteristicBatteryLevelFields
#define CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_VALUE_TYPE      ClxOrgBluetoothCharacteristicBatteryLevelFields_Type
#define CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_SIZE            ClxOrgBluetoothCharacteristicBatteryLevelFields_Size
#define CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_UUID            0x2A19


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicBatteryLevel.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicBatteryLevel.
*/
struct ClxOrgBluetoothCharacteristicBatteryLevelFields
{
    /**
    Field : Level
    Format : uint8
    Unit : org.bluetooth.unit.percentage
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 100
    */
    u1 level;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicBatteryLevelFields
*/
#define ClxOrgBluetoothCharacteristicBatteryLevelFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicBatteryLevelFields
*/
#define ClxOrgBluetoothCharacteristicBatteryLevelFields_Size    1

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicBatteryLevelFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicBatteryLevelFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBatteryLevelFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicBatteryLevel(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicBatteryLevelFields.

\param[ in  ] data A caller-provided buffer containing the data in encoded format.
\param[ in  ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicBatteryLevelFields which, on a successful return, will contain the data in decoded format.
\param[ in  ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicBatteryLevelFields). 

\param[ in  ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicBatteryLevel(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Battery Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Battery Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetBatteryServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __org_bluetooth_service_battery_service_h__

