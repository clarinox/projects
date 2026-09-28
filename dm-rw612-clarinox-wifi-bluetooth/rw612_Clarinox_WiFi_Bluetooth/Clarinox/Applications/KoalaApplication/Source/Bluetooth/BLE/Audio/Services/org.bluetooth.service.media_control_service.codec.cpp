/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.media_control_service.cpp
* Description         Implements the codec functions for the GATT service Media Control Service
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
#include "org.bluetooth.service.media_control_service.h"



#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxOrgBluetoothCharacteristicMediaPlayerNameFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicMediaPlayerName(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->playerName, input_->playerName_Length);
    index += input_->playerName_Length;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicMediaPlayerNameFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicMediaPlayerName(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    output_->playerName_Length = dataLength - index;
    memcpy((void*)output_->playerName, (const void*)(data + index), output_->playerName_Length);
    index += output_->playerName_Length;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicTrackChangedFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicTrackChanged(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicTrackChangedFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicTrackChangedFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicTrackChangedFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;

    BLACKBOX_IF(index >bufferSize);
    return index;

}

/*
Decoder for ClxOrgBluetoothCharacteristicTrackChangedFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicTrackChanged(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicTrackChangedFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicTrackChangedFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicTrackChangedFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;

    return index;

}

/*
Encoder for ClxOrgBluetoothCharacteristicTrackTitleFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicTrackTitle(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicTrackTitleFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicTrackTitleFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicTrackTitleFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->playerName, input_->playerName_Length);
    index += input_->playerName_Length;

    BLACKBOX_IF(index >bufferSize);
    return index;

}

/*
Decoder for ClxOrgBluetoothCharacteristicTrackTitleFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicTrackTitle(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicTrackTitleFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicTrackTitleFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicTrackTitleFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    output_->playerName_Length = dataLength - index;
    memcpy((void*)output_->playerName, (const void*)(data + index), output_->playerName_Length);
    index += output_->playerName_Length;

    return index;

}

/*
Encoder for ClxOrgBluetoothCharacteristicTrackDurationFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicTrackDuration(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicTrackDurationFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicTrackDurationFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicTrackDurationFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_4(*((u4*)&input_->trackDuration), (u4*)(buffer + index));
    index += 4;

    BLACKBOX_IF(index >bufferSize);
    return index;

}

/*
Decoder for ClxOrgBluetoothCharacteristicTrackDurationFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicTrackDuration(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicTrackDurationFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicTrackDurationFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicTrackDurationFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 4) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->trackDuration = (s4)READ_FROM_LITTLEENDIAN_4((u4*)(data + index));
    index += 4;

    return index;

}

/*
Encoder for ClxOrgBluetoothCharacteristicTrackPositionFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicTrackPosition(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicTrackPositionFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicTrackPositionFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicTrackPositionFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_4(*((u4*)&input_->trackPosition), (u4*)(buffer + index));
    index += 4;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicTrackPositionFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicTrackPosition(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicTrackPositionFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicTrackPositionFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicTrackPositionFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 4) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->trackPosition = (s4)READ_FROM_LITTLEENDIAN_4((u4*)(data + index));
    index += 4;

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicMediaStateFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicMediaState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicMediaStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicMediaStateFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicMediaStateFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->mediaState;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicMediaStateFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicMediaState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicMediaStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicMediaStateFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicMediaStateFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->mediaState = (u1)data[index++];
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;

    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicContentControlIdFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicContentControlId(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicContentControlIdFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicContentControlIdFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicContentControlIdFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->contentControlId;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicContentControlIdFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicContentControlId(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicContentControlIdFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicContentControlIdFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicContentControlIdFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->contentControlId = (u1)data[index++];

    return index;
}

#ifdef __cplusplus
}
#endif
