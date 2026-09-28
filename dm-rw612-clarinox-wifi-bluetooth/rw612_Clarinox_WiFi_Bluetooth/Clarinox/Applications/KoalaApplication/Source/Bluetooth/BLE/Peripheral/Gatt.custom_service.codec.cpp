/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                Gatt.custom_service.codec.cpp
* Description         Implements the codec functions for the GATT  
*                     Custom Service.
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
Encoder for ClxGattCustomCharacteristicRxdataFields :
*/
u4 clxEncodeGattCustomCharacteristicRxdata(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxGattCustomCharacteristicRxdataFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxGattCustomCharacteristicRxdataFields* input_ = reinterpret_cast<const struct ClxGattCustomCharacteristicRxdataFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->rxdatasize;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxGattCustomCharacteristicRxdataFields :
*/
u4 clxDecodeGattCustomCharacteristicRxdata(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxGattCustomCharacteristicRxdataFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxGattCustomCharacteristicRxdataFields* output_ = reinterpret_cast<struct ClxGattCustomCharacteristicRxdataFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->rxdatasize = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxGattCustomCharacteristicTxdataFields :
*/
u4 clxEncodeGattCustomCharacteristicTxdata(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxGattCustomCharacteristicTxdataFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxGattCustomCharacteristicTxdataFields* input_ = reinterpret_cast<const struct ClxGattCustomCharacteristicTxdataFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->txdatasize;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxGattCustomCharacteristicTxdataFields :
*/
u4 clxDecodeGattCustomCharacteristicTxdata(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxGattCustomCharacteristicTxdataFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxGattCustomCharacteristicTxdataFields* output_ = reinterpret_cast<struct ClxGattCustomCharacteristicTxdataFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->txdatasize = (u1)data[index++];
    
    return index;
}

#ifdef __cplusplus
}
#endif

