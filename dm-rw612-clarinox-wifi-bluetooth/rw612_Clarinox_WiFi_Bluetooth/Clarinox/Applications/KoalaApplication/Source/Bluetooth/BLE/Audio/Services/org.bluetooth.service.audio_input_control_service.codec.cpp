/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.audio_input_control_service.cpp
* Description         Implements the codec functions for the GATT service Audio Input Control Service
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
#include "org.bluetooth.service.audio_input_control_service.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxOrgBluetoothCharacteristicAudioInputStateFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAudioInputState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicAudioInputStateFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicAudioInputStateFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->gainSetting;
    buffer[index++] = input_->mute;
    buffer[index++] = input_->gainMode;
    buffer[index++] = input_->changeCounter;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicAudioInputStateFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAudioInputState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicAudioInputStateFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicAudioInputStateFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->gainSetting = (s1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->mute = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->gainMode = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->changeCounter = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicGainSettingsFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGainSettings(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGainSettingsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGainSettingsFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGainSettingsFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->units;
    buffer[index++] = input_->min;
    buffer[index++] = input_->max;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGainSettingsFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGainSettings(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGainSettingsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGainSettingsFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGainSettingsFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->units = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->min = (s1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->max = (s1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicAudioInputTypeFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAudioInputType(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputTypeFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicAudioInputTypeFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicAudioInputTypeFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->inputType;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicAudioInputTypeFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAudioInputType(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputTypeFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicAudioInputTypeFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicAudioInputTypeFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->inputType = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicAudioInputStatusFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAudioInputStatus(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputStatusFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicAudioInputStatusFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicAudioInputStatusFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->inputStatus;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicAudioInputStatusFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAudioInputStatus(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputStatusFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicAudioInputStatusFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicAudioInputStatusFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->inputStatus = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicAudioInputControlPointFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAudioInputControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->opcode;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicAudioInputControlPointFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAudioInputControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicAudioInputControlPointFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->opcode = (u1)data[index++];

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicAudioInputDescriptionFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAudioInputDescription(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->audioInput, input_->audioInput_Length);
    index += input_->audioInput_Length;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicAudioInputDescriptionFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAudioInputDescription(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicAudioInputDescriptionFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    output_->audioInput_Length = dataLength - index;
    memcpy((void*)output_->audioInput, (const void*)(data + index), output_->audioInput_Length);
    index += output_->audioInput_Length;
    
    return index;
}
#ifdef __cplusplus
}

#endif
