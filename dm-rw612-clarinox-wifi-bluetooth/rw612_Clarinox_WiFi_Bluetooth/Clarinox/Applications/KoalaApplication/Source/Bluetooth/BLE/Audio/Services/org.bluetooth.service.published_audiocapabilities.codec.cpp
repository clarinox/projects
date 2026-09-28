/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.published_audiocapabilities.cpp
* Description         Implements the codec functions for the GATT service Published Audio Capabilities
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#include "BleAudioCommon.h"
#include "org.bluetooth.service.published_audiocapabilities.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Data Length Validity checking */
#define CLX_LENGTH_VALIDITY(length)  if (dataLength - index < length) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }

/*
Encoder for ClxBapPacRecords :
*/
u4 clxEncodeOrgBluetoothCharacteristicSinkOrSourcePac(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    const ClxBapPacRecords* pacRecord = reinterpret_cast<const ClxBapPacRecords*>(input);

    *result = clxBapEncodePacRecord ( pacRecord, buffer, bufferSize, &inputSize );

    return inputSize;
}

/*
Decoder for ClxBapPacRecords :
*/
u4 clxDecodeOrgBluetoothCharacteristicSinkOrSourcePac(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)outputSize;

    ClxSize filledLength = 0;

    ClxBapPacRecords* pacRecord = reinterpret_cast<ClxBapPacRecords*>(output);

    *result = clxBapDecodeExtendedLevelPacRecord ( data, dataLength, pacRecord, &filledLength );

    return filledLength;
}

/*
Encoder for ClxBapPacAudioLocations :
*/
u4 clxEncodeOrgBluetoothCharacteristicSinkAudioLocation(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    u4 index = 0;

    if (inputSize != sizeof(ClxBapPacAudioLocations))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const ClxBapPacAudioLocations* input_ = reinterpret_cast<const ClxBapPacAudioLocations*>(input);

    /* 
     Fill the Sink Audio Location info to the raw buffer based on spec mentioned structure
     */

    *result = CLX_SUCCESS;

    WRITE_TO_LITTLEENDIAN_4( input_->pacAudioLocations, (u4*)(buffer + index));
    index += 4;

    BLACKBOX_IF(index >bufferSize);
    return index;

}

/*
Decoder for ClxBapPacAudioLocations :
*/
u4 clxDecodeOrgBluetoothCharacteristicSinkAudioLocation(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    u4 index = 0;

    if (outputSize != sizeof(ClxBapPacAudioLocations))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    ClxBapPacAudioLocations* output_ = reinterpret_cast<ClxBapPacAudioLocations*>(output);

    *result = CLX_SUCCESS;

    /*
     Parse and get the Sink Audio Location info from the raw buffer based on spec mentioned structure
     */

    CLX_LENGTH_VALIDITY(4) output_->pacAudioLocations = (u4)READ_FROM_LITTLEENDIAN_4((u4*)(data + index));
    index += 4;

    return index;

}

/*
Encoder for ClxBapPacAudioLocations :
*/
u4 clxEncodeOrgBluetoothCharacteristicSourceAudioLocation(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    u4 index = 0;

    if (inputSize != sizeof(ClxBapPacAudioLocations))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const ClxBapPacAudioLocations* input_ = reinterpret_cast<const ClxBapPacAudioLocations*>(input);

    *result = CLX_SUCCESS;

    /* 
     Fill the Source Audio Location info to the raw buffer based on spec mentioned structure
     */

    WRITE_TO_LITTLEENDIAN_4( input_->pacAudioLocations, (u4*)(buffer + index));
    index += 4;

    BLACKBOX_IF(index >bufferSize);
    return index;

}

/*
Decoder for ClxBapPacAudioLocations :
*/
u4 clxDecodeOrgBluetoothCharacteristicSourceAudioLocation(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    u4 index = 0;

    if (outputSize != sizeof(ClxBapPacAudioLocations))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    ClxBapPacAudioLocations* output_ = reinterpret_cast<ClxBapPacAudioLocations*>(output);

    *result = CLX_SUCCESS;

    /*
     Parse and get the Source Audio Location info from the raw buffer based on spec mentioned structure
     */

    CLX_LENGTH_VALIDITY(4) output_->pacAudioLocations = (u4)READ_FROM_LITTLEENDIAN_4((u4*)(data + index));
    index += 4;

    return index;

}

/*
Encoder for ClxOrgBluetoothCharacteristicAvailableAudioContextsFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAvailableAudioContexts(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    u4 index = 0;

    if ( 0 == inputSize )
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const ClxBapPacAvailableAudioContext* input_ = reinterpret_cast<const ClxBapPacAvailableAudioContext*>(input);

    *result = CLX_SUCCESS;

    /* 
     Fill the PAC Available Audio Contexts info to the raw buffer based on spec mentioned structure
     */

    WRITE_TO_LITTLEENDIAN_2( input_->sinkContentAvailability, (u2*)(buffer + index));
    index += 2;

    WRITE_TO_LITTLEENDIAN_2( input_->sourceContentAvailability, (u2*)(buffer + index));
    index += 2;

    BLACKBOX_IF(index >bufferSize);
    return index;

}

/*
Decoder for ClxOrgBluetoothCharacteristicAvailableAudioContextsFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAvailableAudioContexts(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    u4 index = 0;

    if ( 0 == outputSize )
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    ClxBapPacAvailableAudioContext* output_ = reinterpret_cast<ClxBapPacAvailableAudioContext*>(output);

    *result = CLX_SUCCESS;

    /*
     Parse and get the Available Audio Contexts info from the raw buffer based on spec mentioned structure
     */

    CLX_LENGTH_VALIDITY(2) output_->sinkContentAvailability   = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;

    CLX_LENGTH_VALIDITY(2) output_->sourceContentAvailability = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;

    return index;

}

/*
Encoder for ClxOrgBluetoothCharacteristicSupportedAudioContextsFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicSupportedAudioContexts(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    u4 index = 0;

    if ( 0 == inputSize )
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const ClxBapPacSupportedAudioContext* input_ = reinterpret_cast<const ClxBapPacSupportedAudioContext*>(input);

    *result = CLX_SUCCESS;

    /* 
     Fill the PAC Supported Audio Contexts info to the raw buffer based on spec mentioned structure
     */

    WRITE_TO_LITTLEENDIAN_2( input_->supportedSinkContext, (u2*)(buffer + index));
    index += 2;

    WRITE_TO_LITTLEENDIAN_2( input_->supportedSourceContext, (u2*)(buffer + index));
    index += 2;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicSupportedAudioContextsFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicSupportedAudioContexts(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    u4 index = 0;

    if (outputSize != sizeof(ClxBapPacSupportedAudioContext))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    ClxBapPacSupportedAudioContext* output_ = reinterpret_cast<ClxBapPacSupportedAudioContext*>(output);

    *result = CLX_SUCCESS;

    /*
     Parse and get the Supported Audio Contexts info from the raw buffer based on spec mentioned structure
     */

    CLX_LENGTH_VALIDITY(2) output_->supportedSinkContext   = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;

    CLX_LENGTH_VALIDITY(2) output_->supportedSourceContext = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;

    return index;
}

#ifdef __cplusplus
}
#endif

#endif /* CLX_BLE_ISOCHRONOUS */

