/*******************************************************************************
*
* Project             ClarinoxBlue Low Energy
* File                org.bluetooth.service.generic_access.codec.cpp
* Description         Implements the codec functions for the GATT service Generic Access
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
Encoder for ClxOrgBluetoothCharacteristicGapDeviceNameFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGapDeviceName(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapDeviceNameFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGapDeviceNameFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGapDeviceNameFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->name, input_->name_Length);
    index += input_->name_Length;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGapDeviceNameFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGapDeviceName(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapDeviceNameFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGapDeviceNameFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGapDeviceNameFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    output_->name_Length = dataLength - index;
    memcpy((void*)output_->name, (const void*)(data + index), output_->name_Length);
    index += output_->name_Length;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicGapAppearanceFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGapAppearance(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapAppearanceFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGapAppearanceFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGapAppearanceFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_2(input_->category, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGapAppearanceFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGapAppearance(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapAppearanceFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGapAppearanceFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGapAppearanceFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->category = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParameters(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_2(input_->minimumConnectionInterval, (u2*)(buffer + index));
    index += 2;
    WRITE_TO_LITTLEENDIAN_2(input_->maximumConnectionInterval, (u2*)(buffer + index));
    index += 2;
    WRITE_TO_LITTLEENDIAN_2(input_->slaveLatency, (u2*)(buffer + index));
    index += 2;
    WRITE_TO_LITTLEENDIAN_2(input_->connectionSupervisionTimeoutMultiplier, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParameters(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParametersFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->minimumConnectionInterval = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->maximumConnectionInterval = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->slaveLatency = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->connectionSupervisionTimeoutMultiplier = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGapCentralAddressResolutionSupport(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->addressresolution;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGapCentralAddressResolutionSupport(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGapCentralAddressResolutionSupportFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->addressresolution = (u1)data[index++];
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicGapLeGattSecurityLevels(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields*>(input);

    /*
    Sample implementation of the encoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_2(input_->gattsecurity, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicGapLeGattSecurityLevels(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicGapLeGattSecurityLevelsFields*>(output);

    /*
    Sample implementation of the decoder logic. This may need to be modified as per the specification:
    */

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->gattsecurity = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

#ifdef __cplusplus
}
#endif

