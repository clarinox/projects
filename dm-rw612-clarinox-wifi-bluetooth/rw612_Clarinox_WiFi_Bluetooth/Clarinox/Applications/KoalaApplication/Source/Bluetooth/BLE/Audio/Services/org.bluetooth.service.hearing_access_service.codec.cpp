/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.hearing_access_service.cpp
* Description         Implements the codec functions for the GATT service Hearing Access Service
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
#include "org.bluetooth.service.hearing_access_service.h"



#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxOrgBluetoothCharacteristicHearingAidFeaturesFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicHearingAidFeatures(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->aidfeatures;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
    
}

/*
Decoder for ClxOrgBluetoothCharacteristicHearingAidFeaturesFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicHearingAidFeatures(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicHearingAidFeaturesFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->aidfeatures = (u1)data[index++];
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
    
}

/*
Encoder for ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicHearingAidPresetControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->opcode;
    buffer[index++] = input_->index;
    memcpy((void*)(buffer + index), (const void*)input_->name, input_->name_Length);
    index += input_->name_Length;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
    
}

/*
Decoder for ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicHearingAidPresetControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicHearingAidPresetControlPointFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->opcode = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->index = (u1)data[index++];
    output_->name_Length = dataLength - index;
    memcpy((void*)output_->name, (const void*)(data + index), output_->name_Length);
    index += output_->name_Length;
    
    return index;
    
}

/*
Encoder for ClxOrgBluetoothCharacteristicActivePresetIndexFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicActivePresetIndex(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicActivePresetIndexFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicActivePresetIndexFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicActivePresetIndexFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->activepresetindex;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
    
}

/*
Decoder for ClxOrgBluetoothCharacteristicActivePresetIndexFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicActivePresetIndex(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicActivePresetIndexFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicActivePresetIndexFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicActivePresetIndexFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->activepresetindex = (u1)data[index++];
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}


#ifdef __cplusplus
}
#endif
