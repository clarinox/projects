/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.audiostream_control.cpp
* Description         Implements the codec functions for the GATT service Audio Stream Control
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
#include "Ble.Bap.Api.h"

#include "org.bluetooth.service.audiostream_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for Clx Bluetooth Characteristic Sink ASE or Source ASE:
*/
u4 clxEncodeOrgBluetoothCharacteristicSourceOrSinkAse (_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    const ClxBapAudioStreamEndpoint* sinkEndpoint = reinterpret_cast<const ClxBapAudioStreamEndpoint*>(input);

    *result = clxBapEncodeSinkAse ( sinkEndpoint, buffer, bufferSize, &inputSize );

    return inputSize;
}

/*
Decoder for Clx Bluetooth Characteristic Sink ASE or Source ASE:
*/
u4 clxDecodeOrgBluetoothCharacteristicSourceOrSinkAse(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)outputSize;

    ClxSize filledLength = 0;
    ClxBapAudioStreamEndpoint* sinkEndpoint = reinterpret_cast<ClxBapAudioStreamEndpoint*>(output);

    *result = clxBapDecodeSinkAse ( data, dataLength, sinkEndpoint, &filledLength );

    return filledLength;
}


/*
Encoder for ClxOrgBluetoothCharacteristicAseControlPointFields :
*/
u4 clxEncodeOrgBluetoothCharacteristicAseControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    const ClxBapAseOpCode* aseControlPoint = reinterpret_cast<const ClxBapAseOpCode*>(input);

    *result = clxBapEncodeAseOpCodeData ( aseControlPoint, buffer, bufferSize, &inputSize );

    return inputSize;
}


/*
Decoder for ClxOrgBluetoothCharacteristicAseControlPointFields :
*/
u4 clxDecodeOrgBluetoothCharacteristicAseControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)outputSize;

    ClxSize filledLength = 0;

    ClxBapAseOpCode* aseControlPoint = reinterpret_cast<ClxBapAseOpCode*>(output);

    *result = clxBapDecodeExtendedLevelAseOpCodeData ( data, dataLength, aseControlPoint, &filledLength );

    return filledLength;
}


#ifdef __cplusplus
}
#endif

#endif /* CLX_BLE_ISOCHRONOUS */

