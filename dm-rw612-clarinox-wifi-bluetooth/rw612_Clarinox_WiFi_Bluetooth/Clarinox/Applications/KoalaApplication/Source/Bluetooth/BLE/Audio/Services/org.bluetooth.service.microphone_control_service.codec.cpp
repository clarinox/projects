/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.microphone_control_service.cpp
* Description         Implements the codec functions for the GATT service Microphone Control Service
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
#include "org.bluetooth.service.microphone_control_service.h"



#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxOrgBluetoothCharacteristicMuteFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicMute(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicMuteFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicMuteFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicMuteFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
	*/

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->audioState;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicMuteFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicMute(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicMuteFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicMuteFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicMuteFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
	*/

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->audioState = (u1)data[index++];
    
    return index;
}

#ifdef __cplusplus
}
#endif
