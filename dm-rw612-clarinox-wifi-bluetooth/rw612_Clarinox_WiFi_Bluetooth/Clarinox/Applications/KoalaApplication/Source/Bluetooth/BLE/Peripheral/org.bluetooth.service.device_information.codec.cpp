/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.device_information.cpp
* Description         Implements the codec functions for the GATT
*                     Device Information service
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/


#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"



#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxOrgBluetoothCharacteristicManufacturerNameStringFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicManufacturerNameString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->manufacturerName, 16);
    index += 16;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicManufacturerNameStringFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicManufacturerNameString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;
    
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicManufacturerNameStringFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)output_->manufacturerName, (const void*)(data + index), 16);
    index += 16;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicModelNumberStringFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicModelNumberString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicModelNumberStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicModelNumberStringFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicModelNumberStringFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->modelNumber, 16);
    index += 16;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicModelNumberStringFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicModelNumberString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;
    
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicModelNumberStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicModelNumberStringFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicModelNumberStringFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)output_->modelNumber, (const void*)(data + index), 16);
    index += 16;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicSerialNumberStringFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicSerialNumberString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicSerialNumberStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicSerialNumberStringFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicSerialNumberStringFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->serialNumber, 16);
    index += 16;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicSerialNumberStringFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicSerialNumberString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;
    
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicSerialNumberStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicSerialNumberStringFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicSerialNumberStringFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)output_->serialNumber, (const void*)(data + index), 16);
    index += 16;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicHardwareRevisionStringFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicHardwareRevisionString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->hardwareRevision, 16);
    index += 16;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicHardwareRevisionStringFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicHardwareRevisionString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;
    
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicHardwareRevisionStringFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)output_->hardwareRevision, (const void*)(data + index), 16);
    index += 16;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicFirmwareRevisionString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->firmwareRevision, 16);
    index += 16;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicFirmwareRevisionString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;
    
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicFirmwareRevisionStringFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)output_->firmwareRevision, (const void*)(data + index), 16);
    index += 16;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicSoftwareRevisionString(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)(buffer + index), (const void*)input_->softwareRevision, 16);
    index += 16;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicSoftwareRevisionString(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;
    
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicSoftwareRevisionStringFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    memcpy((void*)output_->softwareRevision, (const void*)(data + index), 16);
    index += 16;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicSystemIdFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicSystemId(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicSystemIdFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicSystemIdFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicSystemIdFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    WRITE_TO_LITTLEENDIAN_5(input_->manufacturerIdentifier, (buffer + index));
    index += 5;
    WRITE_TO_LITTLEENDIAN_3(input_->organizationallyUniqueIdentifier, (buffer + index));
    index += 3;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicSystemIdFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicSystemId(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;
    
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicSystemIdFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicSystemIdFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicSystemIdFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 5) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    READ_FROM_LITTLEENDIAN_5(output_->manufacturerIdentifier, u4, (data + index));
    index += 5;
    if (dataLength - index < 3) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->organizationallyUniqueIdentifier = (u4)READ_FROM_LITTLEENDIAN_3((data + index));
    index += 3;
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataList(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }
    u4 index = 0;

    if (buffer == NULL || input == NULL)
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }
    
    *result = CLX_SUCCESS;
    // Add encoder logic for data
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataList(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;
    
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataListFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }
    
    u4 index = 0;
    
    if (data == NULL || output == NULL)
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    *result = CLX_SUCCESS;
    // Add decoder logic for data
    
    return index;
}

/*
Encoder for ClxOrgBluetoothCharacteristicPnpIdFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicPnpId(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    if (inputSize != sizeof(struct ClxOrgBluetoothCharacteristicPnpIdFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    const struct ClxOrgBluetoothCharacteristicPnpIdFields* input_ = reinterpret_cast<const struct ClxOrgBluetoothCharacteristicPnpIdFields*>(input);

    u4 index = 0;

    *result = CLX_SUCCESS;
    buffer[index++] = input_->vendorIdSource;
    WRITE_TO_LITTLEENDIAN_2(input_->vendorId, (u2*)(buffer + index));
    index += 2;
    WRITE_TO_LITTLEENDIAN_2(input_->productId, (u2*)(buffer + index));
    index += 2;
    WRITE_TO_LITTLEENDIAN_2(input_->productVersion, (u2*)(buffer + index));
    index += 2;
    
    BLACKBOX_IF(index >bufferSize);
    return index;
}

/*
Decoder for ClxOrgBluetoothCharacteristicPnpIdFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicPnpId(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)dataLength;
    
    if (outputSize != sizeof(struct ClxOrgBluetoothCharacteristicPnpIdFields))
    {
        *result =  CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        return 0;
    }

    struct ClxOrgBluetoothCharacteristicPnpIdFields* output_ = reinterpret_cast<struct ClxOrgBluetoothCharacteristicPnpIdFields*>(output);

    u4 index = 0;

    *result = CLX_SUCCESS;
    if (dataLength - index < 1) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->vendorIdSource = (u1)data[index++];
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->vendorId = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->productId = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    if (dataLength - index < 2) { *result = CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH; return 0; }
    output_->productVersion = (u2)READ_FROM_LITTLEENDIAN_2((u2*)(data + index));
    index += 2;
    
    return index;
}

#ifdef __cplusplus
}
#endif

