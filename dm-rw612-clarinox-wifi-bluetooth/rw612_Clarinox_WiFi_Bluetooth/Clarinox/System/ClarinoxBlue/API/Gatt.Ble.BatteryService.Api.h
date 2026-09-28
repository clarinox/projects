#ifndef __Gatt_Ble_BatteryService_Api_h__
#define __Gatt_Ble_BatteryService_Api_h__

/********************************************************************************
*
* Project             GattBleBatteryService
* File                Gatt.Ble.BatteryService.Api.h
* Description         Declares API Functions and Definitions For GattBleBatteryService
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
Refer to #clxBleGattGetBatteryLevel function.
*/
#define CLX_BLE_GATT_GET_BATTERY_LEVEL_COMPLETE                                             0x7101

/**
Refer to #clxBleGattSetBatteryLevel function.
*/
#define CLX_BLE_GATT_SET_BATTERY_LEVEL_COMPLETE                                             0x7102

/**
Data Structure for the indication #CLX_BLE_GATT_GET_BATTERY_LEVEL_COMPLETE
*/
typedef struct ClxBleGattGetBatteryLevelCompleteStruct
{
    _user_out_ u1*  buffer;    /*!< A caller-provided buffer, which should be 1 byte, will contain the value of the attribute upon successful completion.
                                    The buffer shall not be modified or deleted until this command is complete. */
} ClxBleGattGetBatteryLevelComplete;

/**
This API retrieves the battery level from GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BLE_GATT_GET_BATTERY_LEVEL_COMPLETE.
                   The parameter of this indication is of type #ClxBleGattGetBatteryLevelComplete.

\param[  in   ] gatt    The handle of the GATT client or server.
\param[  in   ] handle  The value handle of the Battery Level characteristic. If the local device operates as a GATT client, the value handle of
                        the Battery level characteristic can be obtained using the #clxGattClientGetValueHandle API.If the local device functions as a GATT server, 
                        the handle value should be derived from the base handle plus the handle index of the Battery level characteristic.
\param[  out  ] buffer  A caller-provided buffer, which should be 1 byte, will contain the value of the attribute upon successful completion.
                        The buffer shall not be modified or deleted until this command is complete.
\param[  in   ] block   Indicates mode of operation:
                        TRUE: Blocking mode
                        FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_SUCCESS: The operation has been successful
*/
ClxResult clxBleGattGetBatteryLevel(_in_ ClxHandle  gatt,
                                    _in_ u2         handle,
                                    _user_out_ u1*  buffer,
                                    _in_ boolean    block);

/**
This API sets the battery level into GATT database. It can be used by GATT Server (Peripheral) only.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BLE_GATT_SET_BATTERY_LEVEL_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt          The handle of the GATT server.
\param[  in   ] handle        The value handle of the Battery Level characteristic. the handle value should be derived
                              from the base handle plus the handle index of the Battery level characteristic.
\param[  in   ] batteryLevel  Input the battery level (which should be 1 byte) to write to the Battery Level characteristic.
\param[  in   ] block         Type of the operation.
                              - TRUE:  API will be blocked until this command is completed (successfully or failed).
                              - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_SUCCESS: Operation is successful
        - #CLX_ERROR_COMMAND_NOT_SUPPORTED: If GATT Server/BAS is not supported by/enabled in stack
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The attribute handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_WRITE_NOT_PERMITTED: The attribute cannot be written
        - #CLX_ERROR_TIMEOUT_OCCURRED: Set battery level done, but timeout occurred for sending notification/indication due to no response from remote device
*/
ClxResult clxBleGattSetBatteryLevel(_in_ ClxHandle  gatt,
                                    _in_ u2         handle,
                                    _in_ u1         batteryLevel,
                                    _in_ boolean    block);


#ifdef __cplusplus
}
#endif



#endif // __Gatt_Ble_BatteryService_Api_h__
