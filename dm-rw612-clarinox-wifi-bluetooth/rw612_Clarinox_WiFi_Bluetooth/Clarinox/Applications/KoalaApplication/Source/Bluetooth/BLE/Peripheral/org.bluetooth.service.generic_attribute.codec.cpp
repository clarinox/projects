/*******************************************************************************
*
* Project             ClarinoxBlue Low Energy
* File                org.bluetooth.service.generic_attribute.cpp
* Description         Implements the codec functions for the GATT service Generic Attribute
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxOrgBluetoothCharacteristicGattServiceChangedFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGattServiceChanged(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGattServiceChangedFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGattServiceChangedFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGattServiceChangedFields*>(input);

    
    /*
    Sample implementation of the encoder logic.This may need to be modified as per the specification :*/

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_2(input_->startOfAffectedAttributeHandleRange, (u2*)(buffer + index));
    index += 2;
    WRITE_TO_LITTLEENDIAN_2(input_->endOfAffectedAttributeHandleRange, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
    
}

/*
Decoder for ClxOrgBluetoothCharacteristicGattServiceChangedFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGattServiceChanged(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGattServiceChangedFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGattServiceChangedFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGattServiceChangedFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->startOfAffectedAttributeHandleRange = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->endOfAffectedAttributeHandleRange = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
    
}

/*
Encoder for ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGattClientSupportedFeature(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->feature;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGattClientSupportedFeature(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGattClientSupportedFeatureFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->feature = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicGattDatabaseHashFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGattDatabaseHash(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_4(*((u4*)&input_->properties), (u4*)(buffer + index));
    index += 4;
    WRITE_TO_LITTLEENDIAN_4(*((u4*)&input_->flags), (u4*)(buffer + index));
    index += 4;
    WRITE_TO_LITTLEENDIAN_4(*((u4*)&input_->hashvalue), (u4*)(buffer + index));
    index += 4;
    WRITE_TO_LITTLEENDIAN_4(*((u4*)&input_->index), (u4*)(buffer + index));
    index += 4;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGattDatabaseHashFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGattDatabaseHash(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGattDatabaseHashFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 4) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u4)READ_FROM_LITTLEENDIAN_4((u4*)(data + index));
    index += 4;
    if (dataLength - index < 4) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->flags = (u4)READ_FROM_LITTLEENDIAN_4((u4*)(data + index));
    index += 4;
    if (dataLength - index < 4) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->hashvalue = (u4)READ_FROM_LITTLEENDIAN_4((u4*)(data + index));
    index += 4;
    if (dataLength - index < 4) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->index = (u4)READ_FROM_LITTLEENDIAN_4((u4*)(data + index));
    index += 4;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGattServerSupportedFeature(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->serversupportedfeature;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGattServerSupportedFeature(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGattServerSupportedFeatureFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->serversupportedfeature = (u1)data[index++];
    
    return index;
}

#ifdef __cplusplus
}
#endif

