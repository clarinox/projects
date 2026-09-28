/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.coordinated_set_identification_service.cpp
* Description         Implements the codec functions for the GATT service Coordinated Set Identification Service
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2024 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"
#include "org.bluetooth.service.coordinated_set_identification_service.h"



#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicSetIdentityResolvingKey(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->type;
    memcpy ( buffer + index + 1, &input_->value[0], 16 );
    index += 16;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicSetIdentityResolvingKey(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->type = (u1)data[index++];
    if (dataLength - index < 16) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }

    memcpy ( &output_->value[0], data + index + 1, 16);
    index += 16;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicCoordinatedSetSize(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->coordinatedSetSize;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicCoordinatedSetSize(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->coordinatedSetSize = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicSetMemberLockFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicSetMemberLock(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicSetMemberLockFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicSetMemberLockFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicSetMemberLockFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->setMemberLock;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicSetMemberLockFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicSetMemberLock(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicSetMemberLockFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicSetMemberLockFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicSetMemberLockFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->setMemberLock = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicSetMemberRankFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicSetMemberRank(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicSetMemberRankFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicSetMemberRankFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicSetMemberRankFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->setMemberRank;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicSetMemberRankFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicSetMemberRank(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicSetMemberRankFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicSetMemberRankFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicSetMemberRankFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->setMemberRank = (u1)data[index++];
    
    return index;
}

#ifdef __cplusplus
}
#endif

