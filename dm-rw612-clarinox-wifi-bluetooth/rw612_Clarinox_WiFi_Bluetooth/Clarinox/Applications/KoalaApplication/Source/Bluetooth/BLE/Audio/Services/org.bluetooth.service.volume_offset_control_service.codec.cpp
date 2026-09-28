/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.volume_offset_control_service.cpp
* Description         Implements the codec functions for the GATT service Volume Offset Control Service
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
#include "org.bluetooth.service.volume_offset_control_service.h"


#ifdef __cplusplus
extern "C" {
#endif


/*
Encoder for ClxOrgBluetoothCharacteristicVolumeOffsetStateFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicVolumeOffsetState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_2(input_->volumeOffset, (u2*)(buffer + index));
    index += 2;
    buffer[index++] = input_->changeCounter;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicVolumeOffsetStateFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicVolumeOffsetState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicVolumeOffsetStateFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->volumeOffset = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;

    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->changeCounter = (u1)data[index++];

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicAudioLocationFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAudioLocation(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    (void)bufferSize;

    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioLocationFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicAudioLocationFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicAudioLocationFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_2(input_->audioLocation, (u2*)(buffer + index));

    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicAudioLocationFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAudioLocation(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;

    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioLocationFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicAudioLocationFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicAudioLocationFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    output_->audioLocation = (u2)READ_FROM_LITTLEENDIAN_4((u4*)(data + index));

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicVolumeOffsetControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->opcode;
    buffer[index++] = input_->changeCounter;

    WRITE_TO_LITTLEENDIAN_2(input_->volumeOffset, (u2*)(buffer + index));
    index += 2;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicVolumeOffsetControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicVolumeOffsetControlPointFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->opcode = (u1)data[index++];

    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->changeCounter = (u1)data[index++];

    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->volumeOffset = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAudioOutputDescription(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->audioOutput, input_->audioOutput_Length);
    index += input_->audioOutput_Length;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAudioOutputDescription(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicAudioOutputDescriptionFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    output_->audioOutput_Length = dataLength - index;

    memcpy((void*)output_->audioOutput, (const void*)(data + index), output_->audioOutput_Length);
    index += output_->audioOutput_Length;
    
    return index;
}

#ifdef __cplusplus
}
#endif
