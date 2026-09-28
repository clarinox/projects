/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.alert_notification.cpp
* Description         Implements the codec functions for the GATT 
*                     Alert Notification Service
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
Encoder for ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicSupportedNewAlertCategory(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->categoryIdBitMask0;
    buffer[index++] = input_->categoryIdBitMask1;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicSupportedNewAlertCategory(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->categoryIdBitMask0 = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->categoryIdBitMask1 = (u1)data[index++];

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicNewAlertFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicNewAlert(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicNewAlertFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicNewAlertFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicNewAlertFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->categoryId;
    buffer[index++] = input_->numberOfNewAlert;
    memcpy((void*)(buffer + index), (const void*)input_->textStringInformation, 16);
    index += 16;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicNewAlertFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicNewAlert(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicNewAlertFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicNewAlertFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicNewAlertFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->categoryId = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->numberOfNewAlert = (u1)data[index++];
    memcpy((void*)output_->textStringInformation, (const void*)(data + index), 16);
    index += 16;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicSupportedUnreadAlertCategory(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->categoryIdBitMask0;
    buffer[index++] = input_->categoryIdBitMask1;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicSupportedUnreadAlertCategory(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->categoryIdBitMask0 = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->categoryIdBitMask1 = (u1)data[index++];

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicUnreadAlertStatusFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicUnreadAlertStatus(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->categoryId;
    buffer[index++] = input_->unreadCount;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicUnreadAlertStatusFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicUnreadAlertStatus(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->categoryId = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->unreadCount = (u1)data[index++];
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAlertNotificationControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->commandId;
    buffer[index++] = input_->categoryId;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAlertNotificationControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->commandId = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->categoryId = (u1)data[index++];

    return index;
}

#ifdef __cplusplus
}
#endif

