/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.battery_service.cpp
* Description         Implements the codec functions for the GATT 
*                     Battery Service
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/


#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"



#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxOrgBluetoothCharacteristicBatteryLevelFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicBatteryLevel(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicBatteryLevelFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicBatteryLevelFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicBatteryLevelFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index] = input_->level;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicBatteryLevelFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicBatteryLevel(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicBatteryLevelFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicBatteryLevelFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicBatteryLevelFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->level = (u1)data[index];

    return index;
}

#ifdef __cplusplus
}
#endif

