/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.telephone_bearer_service.cpp
* Description         Implements the codec functions for the GATT service Telephone Bearer Service
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
#include "org.bluetooth.service.telephone_bearer_service.h"



#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxOrgBluetoothCharacteristicBearerProviderNameFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicBearerProviderName(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerProviderNameFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicBearerProviderNameFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicBearerProviderNameFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->providerName, input_->providerName_Length);
    index += input_->providerName_Length;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicBearerProviderNameFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicBearerProviderName(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerProviderNameFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicBearerProviderNameFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicBearerProviderNameFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    output_->providerName_Length = dataLength - index;
    memcpy((void*)output_->providerName, (const void*)(data + index), output_->providerName_Length);
    index += output_->providerName_Length;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicBearerUniformCallerIdentifier(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->bearerUci, input_->bearerUci_Length);
    index += input_->bearerUci_Length;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicBearerUniformCallerIdentifier(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicBearerUniformCallerIdentifierFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    output_->bearerUci_Length = dataLength - index;
    memcpy((void*)output_->bearerUci, (const void*)(data + index), output_->bearerUci_Length);
    index += output_->bearerUci_Length;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicBearerTechnologyFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicBearerTechnology(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerTechnologyFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicBearerTechnologyFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicBearerTechnologyFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->providerName;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicBearerTechnologyFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicBearerTechnology(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerTechnologyFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicBearerTechnologyFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicBearerTechnologyFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->providerName = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicBearerUriSchemesSupportedList(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->supportedScheme, input_->supportedScheme_Length);
    index += input_->supportedScheme_Length;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicBearerUriSchemesSupportedList(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicBearerUriSchemesSupportedListFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    output_->supportedScheme_Length = dataLength - index;
    memcpy((void*)output_->supportedScheme, (const void*)(data + index), output_->supportedScheme_Length);
    index += output_->supportedScheme_Length;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicBearerListCurrentCalls(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->listItemLength;
    buffer[index++] = input_->callIndex;
    buffer[index++] = input_->callState;
    buffer[index++] = input_->callFlags;
    memcpy((void*)(buffer + index), (const void*)input_->callUri, input_->callUri_Length);
    index += input_->callUri_Length;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicBearerListCurrentCalls(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicBearerListCurrentCallsFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->listItemLength = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->callIndex = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->callState = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->callFlags = (u1)data[index++];
    output_->callUri_Length = dataLength - index;
    memcpy((void*)output_->callUri, (const void*)(data + index), output_->callUri_Length);
    index += output_->callUri_Length;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicStatusFlagsFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicStatusFlags(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicStatusFlagsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicStatusFlagsFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicStatusFlagsFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_2(input_->statusFlags, (u2*)(buffer + index));
    index += 2;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicStatusFlagsFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicStatusFlags(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicStatusFlagsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicStatusFlagsFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicStatusFlagsFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->statusFlags = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicCallStateFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicCallState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicCallStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicCallStateFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicCallStateFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->callIndex;
    buffer[index++] = input_->state;
    buffer[index++] = input_->callFlags;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicCallStateFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicCallState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicCallStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicCallStateFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicCallStateFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->callIndex = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->state = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->callFlags = (u1)data[index++];
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicCallControlPointFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicCallControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicCallControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicCallControlPointFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicCallControlPointFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->opcode;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicCallControlPointFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicCallControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicCallControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicCallControlPointFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicCallControlPointFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->opcode = (u1)data[index++];
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicCallControlPointOptionalOpcode(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_2(input_->optionalOpcode, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicCallControlPointOptionalOpcode(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicCallControlPointOptionalOpcodeFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->optionalOpcode = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicTerminationReasonFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicTerminationReason(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicTerminationReasonFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicTerminationReasonFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicTerminationReasonFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->reasonCode;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicTerminationReasonFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicTerminationReason(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicTerminationReasonFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicTerminationReasonFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicTerminationReasonFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->reasonCode = (u1)data[index++];
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicIncomingCallFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicIncomingCall(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicIncomingCallFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicIncomingCallFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicIncomingCallFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->reasonCode;
    WRITE_TO_LITTLEENDIAN_2(input_->properties, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicIncomingCallFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicIncomingCall(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicIncomingCallFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicIncomingCallFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicIncomingCallFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->reasonCode = (u1)data[index++];
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->properties = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

#ifdef __cplusplus
}
#endif
