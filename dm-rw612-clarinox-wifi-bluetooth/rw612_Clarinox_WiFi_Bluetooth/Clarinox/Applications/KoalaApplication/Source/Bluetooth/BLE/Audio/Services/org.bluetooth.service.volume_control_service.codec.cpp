/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.volume_control_service.cpp
* Description         Implements the codec functions for the GATT service Volume Control Service
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
#include "org.bluetooth.service.volume_control_service.h"



#ifdef __cplusplus
extern "C" {
#endif
/*
Encoder for ClxOrgBluetoothCharacteristicVolumeStateFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicVolumeState(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicVolumeStateFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicVolumeStateFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->volumeSetting;
    buffer[index++] = input_->mute;
    buffer[index++] = input_->changeCounter;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicVolumeStateFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicVolumeState(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeStateFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicVolumeStateFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicVolumeStateFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->volumeSetting = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->mute = (u1)data[index++];
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->changeCounter = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicVolumeControlPointFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicVolumeControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicVolumeControlPointFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicVolumeControlPointFields*>(input);

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
Decoder for ClxOrgBluetoothCharacteristicVolumeControlPointFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicVolumeControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeControlPointFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicVolumeControlPointFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicVolumeControlPointFields*>(output);

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
Encoder for ClxOrgBluetoothCharacteristicVolumeFlagsFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicVolumeFlags(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeFlagsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicVolumeFlagsFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicVolumeFlagsFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->volumeFlags;

    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicVolumeFlagsFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicVolumeFlags(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicVolumeFlagsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicVolumeFlagsFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicVolumeFlagsFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:

    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->volumeFlags = (u1)data[index++];
    
    return index;
}

#ifdef __cplusplus
}
#endif
