/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.broadcast_audioscan.cpp
* Description         Implements the codec functions for the GATT service Broadcast Audio Scan
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
Encoder for ClxBapBroadcastScanOpCode :
*/
u4 clxEncodeOrgBluetoothCharacteristicBroadcastAudioscancontrolpoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    const ClxBapBroadcastScanOpCode* bscOpCodeInfo = reinterpret_cast<const ClxBapBroadcastScanOpCode*>(input);

    *result = clxBapEncodeBroadcastScanOpCodeData ( bscOpCodeInfo, buffer, bufferSize, &inputSize );

    return inputSize;
}

/*
Decoder for ClxBapBroadcastScanOpCode :
*/
u4 clxDecodeOrgBluetoothCharacteristicBroadcastAudioscancontrolpoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)outputSize;

    ClxSize filledLength = 0;

    ClxBapBroadcastScanOpCode* bscOpCodeInfo = reinterpret_cast<ClxBapBroadcastScanOpCode*>(output);

    *result = clxBapDecodeExtendedLevelBroadcastScanOpCodeData ( data, dataLength, bscOpCodeInfo, &filledLength );

    return filledLength;
}


/*
Encoder for ClxBapBroadcastReceiveState :
*/
u4 clxEncodeOrgBluetoothCharacteristicBroadcastReceivestate(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result)
{
    const ClxBapBroadcastReceiveState* receiveState = reinterpret_cast<const ClxBapBroadcastReceiveState*>(input);

    *result = clxBapEncodeBroadcastReceiveState ( receiveState, buffer, bufferSize, &inputSize );

    return inputSize;
}


/*
Decoder for ClxBapBroadcastReceiveState :
*/ 
u4 clxDecodeOrgBluetoothCharacteristicBroadcastReceivestate(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result)
{
    (void)outputSize;

    ClxSize filledLength = 0;

    ClxBapBroadcastReceiveState* receiveState = reinterpret_cast<ClxBapBroadcastReceiveState*>(output);

    *result = clxBapDecodeExtendedLevelBroadcastReceiveState ( data, dataLength, receiveState, &filledLength );

    return filledLength;
}


#ifdef __cplusplus
}
#endif

#endif /* CLX_BLE_ISOCHRONOUS */

