/*******************************************************************************
*
* Project             ClarinoxBlue Low Energy
* File                org.bluetooth.characteristic.gap.resolvable_private_address_only.codec.cpp
* Description         Implements the codec functions for Reference Characteristic ""
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
Encoder for ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->resolvableprivateaddress;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->resolvableprivateaddress = (u1)data[index++];
    
    return index;
}

#ifdef __cplusplus
}
#endif

