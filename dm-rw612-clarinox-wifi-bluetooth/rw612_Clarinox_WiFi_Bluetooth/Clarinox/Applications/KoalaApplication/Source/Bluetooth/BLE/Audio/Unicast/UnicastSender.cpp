/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                UnicastSender.cpp
* Description         This application file provides the BLE audio unicast sender
*                     operations menu.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#include "BleAudioCommon.h"
#include "Iso.Ble.Client.Api.h"

#include "BleAudio.Unicast.Client.Api.h"
#include "Ble.Bap.Api.h"
#include "GattApp.h"
#include "GattClient.h"
#include "UnicastCommon.h"
#include "BleLc3Common.h"
#include "BleIso.h"
#include "Gap.Ble.Bonding.Api.h"

/* Menu options used to invoke UnicastSender main menu */
typedef enum UnicastSenderMenuItemEnum
{
    UnicastSenderMenuItem_StartScan                = 1,
    UnicastSenderMenuItem_StopScan,
    UnicastSenderMenuItem_ConnectToDiscoveredDevice,
    UnicastSenderMenuItem_Play,
    UnicastSenderMenuItem_Pause,
    UnicastSenderMenuItem_Next,
    UnicastSenderMenuItem_Previous,
    UnicastSenderMenuItem_DisconnectFromDevice,
    UnicastSenderMenuItem_ReturnToPreviousMenu,
    UnicastSenderMenuItem_TotalItems
}UnicastSenderMenuItem;

extern s1 inputValue[MAX_INPUT_SIZE];

s1* getAseStateFromValue(u1 value)
{
    if (ClxBapAEStates_Idle == value)
    {
        return ((s1*)"Idle");
    }
    else if (ClxBapAEStates_CodecConfigured == value)
    {
        return ((s1*)"Codec Configured");
    }
    else if (ClxBapAEStates_QoSConfigured == value)
    {
        return ((s1*)"QoS Configured");
    }
    else if (ClxBapAEStates_Enabling == value)
    {
        return ((s1*)"Enabling");
    }
    else if (ClxBapAEStates_Streaming == value)
    {
        return ((s1*)"Streaming");
    }
    else if (ClxBapAEStates_Disabling == value)
    {
        return ((s1*)"Disabling");
    }
    else if (ClxBapAEStates_Releasing == value)
    {
        return ((s1*)"Releasing");
    }
    else
    {
        clxConsoleUIEngineText("Invalid state %u:\n", value);
    }

    return NULL;
}

s1* getAseName(u2 uuid)
{
    if (CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID == uuid)
    {
        return ((s1*) "Sink Ase");
    }
    else if (CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_UUID == uuid)
    {
        return ((s1*) "Source Ase");
    }

    return NULL;
}

ClxBleRoleType getRoleByAseUuid (u2 uuid)
{
    if (CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID == uuid)
    {
        return ClxBleRoleType_SINK;
    }
    else if (CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_UUID == uuid)
    {
        return ClxBleRoleType_SOURCE;
    }
    return ClxBleRoleType_INVALID;
}

/**
Discover Sink ASE Id and its state
*/
ClxResult  bleAudioUnicastDiscoverAseIdAndState(ClxHandle gattClientHandle, ClxGattUuid* uuid)
{
    ClxGattServiceDetail sd     = { };
    ClxResult            ret    = CLX_ERROR;

    ClxBleRoleType sourceOrSink = ClxBleRoleType_INVALID;

    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    if ( 0    == gattClientHandle )
    {
        return CLX_ERROR_INVALID_HANDLE;
    }

    GattClient *gattClient = getGattClientHandleInfo();

    memset(&sd, 0, sizeof(sd));

    /* Disovering of Audio Streaming Control Service (ASCS) */
    ClxGattUuid serviceUuid = { };
    clxInitGattUuid2 ( &serviceUuid, (u2)CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID );

    ret = bleCentralDiscoverAllPrimaryServices ( &serviceUuid, FALSE);

    if ( CLX_SUCCESS != ret )
    {
        clxConsoleUIEngineText("\nbleCentralDiscoverAllPrimaryServices completed with the result %s\n", clxGetErrorCodeText(ret));
        return ret;
    }

    u1 serviceIndex = 0;

    /**
    First handle shall be the handle from which the services of those would be discovered
    */
    sd.firstHandle = gattClient->serviceList[serviceIndex].firstHandle;

    /**
    Last handle shall be the handle till which the services of those would be discovered
    */
    sd.lastHandle = gattClient->serviceList[serviceIndex].lastHandle;

    /**
    Maximum size of characteristics details that can be stored in the user defined buffer.
    */
    u2 listSize = sizeof(gattClient->characteristicList) / sizeof(ClxGattCharacteristicDetail);

    /**
    Variable returning the retrieved characteristics count from server upon successful completion of 
    clxGattClientDiscoverCharacteristics(.)
    */
    u2 noOfCharacteristics = 0;

    /**
    Discovers all characteristics of a service in the server and get the list of attribute handle - value 
    pairs corresponding to the characteristics in the service definition.
    */
    ret = clxGattClientDiscoverCharacteristics(getGattClientHandle(),
                                               uuid,
                                               &sd,
                                               listSize,
                                               gattClient->characteristicList,
                                               &gattClient->noOfCharacteristics,
                                               TRUE);

    if ( CLX_SUCCESS != ret )
    {
        clxConsoleUIEngineText("\nclxGattClientDiscoverCharacteristics completed with the result %s\n", clxGetErrorCodeText(ret));
        return ret;
    }

    noOfCharacteristics = gattClient->noOfCharacteristics;

    sourceOrSink = getRoleByAseUuid((u2)uuid->value[0]);

    if ( ClxBleRoleType_SINK   != sourceOrSink &&\
         ClxBleRoleType_SOURCE != sourceOrSink )
    {
        return CLX_ERROR;
    }

    if ( ClxBleRoleType_SINK == sourceOrSink )
    {
        bleAudioConfig->currentSinkAseCount   = 0;
        memset(bleAudioConfig->sinkAseRecords, 0x00, sizeof(bleAudioConfig->sinkAseRecords));
    }
    else
    {
        bleAudioConfig->currentSourceAseCount   = 0;
        memset(bleAudioConfig->sourceAseRecords, 0x00, sizeof(bleAudioConfig->sourceAseRecords));
    }

    for (u4 i = 0; i < noOfCharacteristics; i++)
    {
        u4 valueReadLength = 0;

        if ( ClxBleRoleType_SINK == sourceOrSink )
        {
             ret = clxBapGetSinkAse( gattClientHandle,
                                    gattClient->characteristicList[i].valueHandle,
                                    (u1*)inputValue,
                                    MAX_INPUT_SIZE,
                                    &valueReadLength,
                                    TRUE );
        }
        else
        {
            ret = clxBapGetSourceAse( gattClientHandle,
                                      gattClient->characteristicList[i].valueHandle,
                                      (u1*)inputValue,
                                      MAX_INPUT_SIZE,
                                      &valueReadLength,
                                      TRUE );
        }

        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nGet ASE record completed with the result %s\n", clxGetErrorCodeText(ret));
            return CLX_ERROR;
        }

        if ( CLX_BLE_UNICAST_SUPPORTED_SINK_ASE_COUNT == bleAudioConfig->currentSinkAseCount && ClxBleRoleType_SINK == sourceOrSink )
        {
            clxConsoleUIEngineText("BLE Audio Sink ASE Count reached the MAX count[%d]\n", bleAudioConfig->currentSinkAseCount);
            continue;
        }
        else if ( CLX_BLE_UNICAST_SUPPORTED_SOURCE_ASE_COUNT == bleAudioConfig->currentSourceAseCount && ClxBleRoleType_SINK == sourceOrSink )
        {
            clxConsoleUIEngineText("BLE Audio Source ASE Count reached the MAX count[%d]\n", bleAudioConfig->currentSourceAseCount);
            continue;
        }

        ClxBapAudioStreamEndpoint* locASEInfo = NULL;

        if ( ClxBleRoleType_SINK == sourceOrSink )
        {
            locASEInfo = clxBleAppGetSinkAseRecord(bleAudioConfig->currentSinkAseCount);
        }
        else
        {
            locASEInfo = clxBleAppGetSourceAseRecord(bleAudioConfig->currentSourceAseCount);
        }

        /* Decode the ASE buffer */
        clxDecodeOrgBluetoothCharacteristicSourceOrSinkAse ( (u1*)inputValue,
                                                             valueReadLength,
                                                             locASEInfo,
                                                             sizeof(ClxBapAudioStreamEndpoint),
                                                             &ret );

        if ( CLX_SUCCESS != ret )
        {
            printBufferHexAndChar ( (u1*)inputValue, valueReadLength );

            clxConsoleUIEngineText("\nDecode %s ASE completed with the result %s\n",
                                        ( ClxBleRoleType_SINK == sourceOrSink ) ? "Sink" : "Source",
                                        clxGetErrorCodeText(ret));
            return CLX_ERROR;
        }

        clxConsoleUIEngineText("\nAse ID:% 02x, State: %s, Type: %s", 
                                        locASEInfo->aseId,
                                        getAseStateFromValue(locASEInfo->aseState),
                                        getAseName((u2)gattClient->characteristicList[i].uuid.value[0]));

        if ( ClxBleRoleType_SINK == sourceOrSink )
        {
            ++bleAudioConfig->currentSinkAseCount;
        }
        else
        {
            ++bleAudioConfig->currentSourceAseCount;
        }
    }

    return ret;
}

/**
Audio stream endpoint config codec control point operations
*/
ClxResult aseConfigCodecOperation(ClxHandle clientHandle)
{
    ClxResult ret = CLX_FAIL;
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    u2  aseValueHandle = 0;
    u2  returnLength   = 0;
    u1  buffer [ CLX_GATT_MAX_LTV_RECORD_LENGTH ] = { },
        i = 0;

    ClxBapAseOpCode* aseCodecControlPoint = clxBleGetAseControlPoint();

    aseCodecControlPoint->opcode          = ClxBapAseOpCodeType_ConfigCodecOperation;
    aseCodecControlPoint->numberOfAses    = 0x01;

    /* Fill the ASE operation info as based on the numberOfAses */
    for ( i = 0; i < aseCodecControlPoint->numberOfAses && aseCodecControlPoint->opCodeInfo; ++i )
    {
        aseCodecControlPoint->opCodeInfo[ i ].configCodec.aseId                     = 0x01;
        aseCodecControlPoint->opCodeInfo[ i ].configCodec.targetLatency             = BleAudioTargetLatency_Balanced;
        aseCodecControlPoint->opCodeInfo[ i ].configCodec.targetPhy                 = BleAudioTargetPhy_LE_1M;
        aseCodecControlPoint->opCodeInfo[ i ].configCodec.codecId.format            = CLX_BLE_AUDIO_CODEC_FORMAT;
        aseCodecControlPoint->opCodeInfo[ i ].configCodec.codecId.companyID         = 0x0000;
        aseCodecControlPoint->opCodeInfo[ i ].configCodec.codecId.vendorSpecificID  = 0x0000;

        if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.samplingFrequency )
        {
            aseCodecControlPoint->opCodeInfo[ i ].configCodec.codecSpecificConfig.samplingFrequency = bleAudioConfig->codecInfo.samplingFrequency;
        }

        if ( CLX_BAP_INVALID_FIELD_U8 != bleAudioConfig->codecInfo.frameDuration )
        {
            aseCodecControlPoint->opCodeInfo[ i ].configCodec.codecSpecificConfig.frameDuration     = bleAudioConfig->codecInfo.frameDuration;
        }

        if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.channelAllocation )
        {
            aseCodecControlPoint->opCodeInfo[ i ].configCodec.codecSpecificConfig.channelAllocation = bleAudioConfig->codecInfo.channelAllocation;
        }

        if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.frameLength )
        {
            aseCodecControlPoint->opCodeInfo[ i ].configCodec.codecSpecificConfig.frameLength       = bleAudioConfig->codecInfo.frameLength;
        }

        if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.framesPerSdu )
        {
            aseCodecControlPoint->opCodeInfo[ i ].configCodec.codecSpecificConfig.framesPerSdu      = bleAudioConfig->codecInfo.framesPerSdu;
        }

        clxConsoleUIEngineText("\n\n#%d {Config Codec} BAP Set ASE OP Code: ASEID [%X]",
                                    i,
                                    aseCodecControlPoint->opCodeInfo[ i ].configCodec.aseId );

        clxBleAudioPrintDataBasedOnSpecFormat ( (void*)&aseCodecControlPoint->opCodeInfo[ i ].configCodec.codecSpecificConfig,
                                                ClxBleAudioSpecStructure_CodecConfig );

    }

    aseValueHandle = GetValueHandle(clientHandle, CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);

    returnLength = (u2)clxEncodeOrgBluetoothCharacteristicAseControlPoint ( buffer,
                                                                            CLX_GATT_MAX_LTV_RECORD_LENGTH,
                                                                            aseCodecControlPoint,
                                                                            sizeof(ClxBapAseOpCode),
                                                                            &ret );

    clxConsoleUIEngineText("\nCodec Configure Data: \n");
    for (u4 loop = 0; loop < returnLength; loop++)
    {
        clxConsoleUIEngineText("%02x ", buffer[loop]);
    }

    if ( 0 != aseValueHandle && \
         ( CLX_SUCCESS == ret && returnLength ) )
    {
        ret = clxBapSetAseOpCode( clientHandle,
                                  aseValueHandle,
                                  buffer,
                                  returnLength,
                                  TRUE );

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\n{Config Codec} BAP Set ASE OP Code completed with the result %s\n",clxGetErrorCodeText(ret));
        }
    }

    return ret;
}

/**
ASE control point QoS operations
*/
ClxResult aseQosConfiguration(ClxHandle clientHandle)
{
    ClxResult ret = CLX_FAIL;
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    u2  aseValueHandle = 0,
        returnLength   = 0;
    ClxBapAseOpCode* qosConfiguration = clxBleGetAseControlPoint();

    u1  buffer [ CLX_GATT_MAX_LTV_RECORD_LENGTH ] = { },
        i   = 0;

    qosConfiguration->opcode       = ClxBapAseOpCodeType_ConfigQosOperation;
    qosConfiguration->numberOfAses = 0x01;

    /* Fill the ASE operation info as based on the numberOfAses */
    for ( i = 0; i < qosConfiguration->numberOfAses && qosConfiguration->opCodeInfo; ++i )
    {
        qosConfiguration->opCodeInfo[ i ].configQos.aseId                = 0x01;
        qosConfiguration->opCodeInfo[ i ].configQos.cigId                = CLX_BLE_ISO_CIG_ID;
        qosConfiguration->opCodeInfo[ i ].configQos.cisId                = CLX_BLE_ISO_CIG_ID;
        qosConfiguration->opCodeInfo[ i ].configQos.sduInterval          = CLX_BLE_ISO_SDU_INTERVAL;
        qosConfiguration->opCodeInfo[ i ].configQos.framing              = BleAudioPduFraming_UnframedIsoalSupported;
        qosConfiguration->opCodeInfo[ i ].configQos.phy                  = BleAudioTargetPhy_LE_1M;
        qosConfiguration->opCodeInfo[ i ].configQos.maxSdu               = CLX_BLE_ISO_MAX_SDU_SIZE;
        qosConfiguration->opCodeInfo[ i ].configQos.retransmissionNum    = CLX_BLE_ISO_RETRANSMISSION;
        qosConfiguration->opCodeInfo[ i ].configQos.maxTransportLatency  = CLX_BLE_ISO_MAX_TRANSPORT_LATENCY;
        qosConfiguration->opCodeInfo[ i ].configQos.presentationDelay    = bleAudioConfig->presentationDelay;

        clxConsoleUIEngineText("\n#%d {Config QoS} BAP Set ASE OP Code: ASEID [%X]\n",
                                    i,
                                    qosConfiguration->opCodeInfo[ i ].configQos.aseId );
    }

    aseValueHandle = GetValueHandle(clientHandle, CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);

    returnLength = (u2)clxEncodeOrgBluetoothCharacteristicAseControlPoint ( buffer,
                                                                            CLX_GATT_MAX_LTV_RECORD_LENGTH,
                                                                            qosConfiguration,
                                                                            sizeof(ClxBapAseOpCode),
                                                                            &ret );

    clxConsoleUIEngineText("\nQos Configure Data: \n");
    for (u4 loop = 0; loop < returnLength; loop++)
    {
        clxConsoleUIEngineText("%02x ", buffer[loop]);
    }

    if ( 0 != aseValueHandle && \
       ( CLX_SUCCESS == ret && returnLength ) )
    {
        ret = clxBapSetAseOpCode( clientHandle,
                                  aseValueHandle,
                                  buffer,
                                  returnLength,
                                  TRUE );

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\n{Config QoS} BAP Set ASE OP Code failed with the error %s\n",clxGetErrorCodeText(ret));
        }
    }

    return ret;
}

/**
ASE control point enable operation
*/
ClxResult aseEnableOperation(ClxHandle clientHandle)
{
    ClxResult ret = CLX_FAIL;
    ClxBapAseOpCode* enableAse = clxBleGetAseControlPoint();

    u2  aseValueHandle = 0,
        returnLength   = 0;

    u1  buffer [ CLX_GATT_MAX_LTV_RECORD_LENGTH ] = { },
        i = 0;

    enableAse->opcode       = ClxBapAseOpCodeType_EnableOperation;
    enableAse->numberOfAses = 0x01;

    /* Fill the ASE operation info as based on the numberOfAses */
    for ( i = 0; i < enableAse->numberOfAses && enableAse->opCodeInfo; ++i )
    {
        enableAse->opCodeInfo[ i ].enable.aseId          = 0x01;

        clxConsoleUIEngineText("\n#%d {Enable} BAP Set ASE OP Code: ASEID [%X]\n",
                                    i,
                                    enableAse->opCodeInfo[ i ].enable.aseId );
    }

    aseValueHandle = GetValueHandle(clientHandle, CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);

    returnLength = (u2)clxEncodeOrgBluetoothCharacteristicAseControlPoint ( buffer,
                                                                            CLX_GATT_MAX_LTV_RECORD_LENGTH,
                                                                            enableAse,
                                                                            sizeof(ClxBapAseOpCode),
                                                                            &ret );

    clxConsoleUIEngineText("\nEnable Data: \n");
    for (u4 loop = 0; loop < returnLength; loop++)
    {
        clxConsoleUIEngineText("%02x ", buffer[loop]);
    }

    if ( 0 != aseValueHandle && \
         ( CLX_SUCCESS == ret && returnLength ) )
    {
        ret = clxBapSetAseOpCode( clientHandle,
                                  aseValueHandle,
                                  buffer,
                                  returnLength,
                                  TRUE );

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\n{Enable} BAP Set ASE OP Code failed with the error %s\n",clxGetErrorCodeText(ret));
        }
    }

    return ret;
}

/**
ASE control point Receiver Start Ready operation
*/
ClxResult aseReceiverStartReadyOperation(ClxHandle gattClientHandle )
{
    ClxResult ret = CLX_FAIL;
    ClxBapAseOpCode* receiverStartReadyAse = clxBleGetAseControlPoint();
    u2  aseValueHandle = 0,
        returnLength   = 0;

    u1  buffer [ CLX_GATT_MAX_LTV_RECORD_LENGTH ] = { },
        i = 0;

    receiverStartReadyAse->opcode       = ClxBapAseOpCodeType_ReceiverStartReadyOperation;
    receiverStartReadyAse->numberOfAses = 0x01;

    /* Fill the ASE operation info as based on the numberOfAses */
    for ( i = 0; i < receiverStartReadyAse->numberOfAses && receiverStartReadyAse->opCodeInfo; ++i )
    {
        receiverStartReadyAse->opCodeInfo[ i ].receiverReady.aseId          = 0x01;

        clxConsoleUIEngineText("\n#%d {Receiver Start Ready} BAP Set ASE OP Code: ASEID [%X]\n",
                                    i,
                                    receiverStartReadyAse->opCodeInfo[ i ].configCodec.aseId );
    }

    aseValueHandle = GetValueHandle(gattClientHandle, CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);

    returnLength = (u2)clxEncodeOrgBluetoothCharacteristicAseControlPoint ( buffer,
                                                                            CLX_GATT_MAX_LTV_RECORD_LENGTH,
                                                                            receiverStartReadyAse,
                                                                            sizeof(ClxBapAseOpCode),
                                                                            &ret );
    
    clxConsoleUIEngineText("\nStart Ready Data: \n");
    for (u4 loop = 0; loop < returnLength; loop++)
    {
        clxConsoleUIEngineText("%02x ", buffer[loop]);
    }
    
    if ( 0 != aseValueHandle && \
         ( CLX_SUCCESS == ret && returnLength ) )
    {
        ret = clxBapSetAseOpCode( gattClientHandle,
                                  aseValueHandle,
                                  buffer,
                                  returnLength,
                                  TRUE );

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\n{Receiver Start Ready} BAP Set ASE OP Code failed with the error %s\n",clxGetErrorCodeText(ret));
        }
    }

    return ret;
}

/**
ASE control point Disable operation
*/
ClxResult aseDisableOperation(ClxHandle gattClientHandle )
{
    ClxResult ret = CLX_FAIL;
    ClxBapAseOpCode* aseDisable = clxBleGetAseControlPoint();
    u2  aseValueHandle = 0,
        returnLength   = 0;

    u1  buffer [ CLX_GATT_MAX_LTV_RECORD_LENGTH ] = { },
        i = 0;

    aseDisable->opcode       = ClxBapAseOpCodeType_DisableOperation;
    aseDisable->numberOfAses = 0x01;

    /* Fill the ASE operation info as based on the numberOfAses */
    for ( i = 0; i < aseDisable->numberOfAses && aseDisable->opCodeInfo; ++i )
    {
        aseDisable->opCodeInfo[ i ].stateDisable.aseId          = 0x01;

        clxConsoleUIEngineText("\n#%d {Disable} BAP Set ASE OP Code: ASEID [%X]\n",
                                    i,
                                    aseDisable->opCodeInfo[ i ].stateDisable.aseId );
    }

    aseValueHandle = GetValueHandle(gattClientHandle, CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);

    returnLength = (u2)clxEncodeOrgBluetoothCharacteristicAseControlPoint ( buffer,
                                                                            CLX_GATT_MAX_LTV_RECORD_LENGTH,
                                                                            aseDisable,
                                                                            sizeof(ClxBapAseOpCode),
                                                                            &ret );

    clxConsoleUIEngineText("\nDisable Data: \n");
    for (u4 loop = 0; loop < returnLength; loop++)
    {
        clxConsoleUIEngineText("%02x ", buffer[loop]);
    }

    if ( 0 != aseValueHandle && \
         ( CLX_SUCCESS == ret && returnLength ) )
    {
        ret = clxBapSetAseOpCode( gattClientHandle,
                                  aseValueHandle,
                                  buffer,
                                  returnLength,
                                  TRUE );

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\n{Disable} BAP Set ASE OP Code failed with the error %s\n",clxGetErrorCodeText(ret));
        }
    }

    return ret;
}

/**
ASE control point Receiver Stop Ready operation
*/
ClxResult aseReceiverStopReadyOperation(ClxHandle gattClientHandle )
{
    ClxResult ret = CLX_FAIL;

    ClxBapAseOpCode* receiverStopReady = clxBleGetAseControlPoint();
    u2  aseValueHandle = 0,
        returnLength   = 0;

    u1  buffer [ CLX_GATT_MAX_LTV_RECORD_LENGTH ] = { },
        i = 0;

    receiverStopReady->opcode       = ClxBapAseOpCodeType_ReceiverStopReadyOperation;
    receiverStopReady->numberOfAses = 0x01;

    /* Fill the ASE operation info as based on the numberOfAses */
    for ( i = 0; i < receiverStopReady->numberOfAses && receiverStopReady->opCodeInfo; ++i )
    {
        receiverStopReady->opCodeInfo[ i ].receiverStop.aseId          = 0x01;

        clxConsoleUIEngineText("\n#%d {Receiver Stop Ready} BAP Set ASE OP Code: ASEID [%X]\n",
                                    i,
                                    receiverStopReady->opCodeInfo[ i ].receiverStop.aseId );
    }

    aseValueHandle = GetValueHandle(gattClientHandle, CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);

    returnLength = (u2)clxEncodeOrgBluetoothCharacteristicAseControlPoint ( buffer,
                                                                            CLX_GATT_MAX_LTV_RECORD_LENGTH,
                                                                            receiverStopReady,
                                                                            sizeof(ClxBapAseOpCode),
                                                                            &ret );
    
    clxConsoleUIEngineText("\nStop Ready Data: \n");
    for (u4 loop = 0; loop < returnLength; loop++)
    {
        clxConsoleUIEngineText("%02x ", buffer[loop]);
    }
    
    if ( 0 != aseValueHandle && \
         ( CLX_SUCCESS == ret && returnLength ) )
    {
        ret = clxBapSetAseOpCode( gattClientHandle,
                                  aseValueHandle,
                                  buffer,
                                  returnLength,
                                  TRUE );

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\n{Receiver Stop Ready} BAP Set ASE OP Code failed with the error %s\n",clxGetErrorCodeText(ret));
        }
    }

    return ret;
}

/**
ASE control point Update Metadata operation
*/
ClxResult aseUpdateMetadataOperation(ClxHandle gattClientHandle )
{
    ClxResult ret = CLX_FAIL;
    ClxBapAseOpCode* updateAseMetadata = clxBleGetAseControlPoint();
    u2  aseValueHandle = 0,
        returnLength   = 0;

    u1  buffer [ CLX_GATT_MAX_LTV_RECORD_LENGTH ] = { },
        i = 0;

    updateAseMetadata->opcode       = ClxBapAseOpCodeType_UpdateMetadataOperation;
    updateAseMetadata->numberOfAses = 0x01;

    /* Fill the ASE operation info as based on the numberOfAses */
    for ( i = 0; i < updateAseMetadata->numberOfAses && updateAseMetadata->opCodeInfo; ++i )
    {
        updateAseMetadata->opCodeInfo[ i ].updateMetadata.aseId             = 0x01;

        clxConsoleUIEngineText("\n#%d {Update ASE Metadata} BAP Set ASE OP Code: ASEID [%X]\n",
                                    i,
                                    updateAseMetadata->opCodeInfo[ i ].updateMetadata.aseId );

        /* LTV structures*/
        ClxBapAudioMetadataLtv *metadataInfo = &updateAseMetadata->opCodeInfo[ i ].updateMetadata.metadata;

        /* << Set MetaData Configurations >> */
        if ( metadataInfo )
        {
            /* MetaData LTV 1: Streaming Audio Contexts: */
            /* Preferred_Audio_Contexts LTV structure Value as MEDIA */
            metadataInfo->preferredAudioContexts = 0x00;
        }
    }

    returnLength = (u2)clxEncodeOrgBluetoothCharacteristicAseControlPoint ( buffer,
                                                                            CLX_GATT_MAX_LTV_RECORD_LENGTH,
                                                                            updateAseMetadata,
                                                                            sizeof(ClxBapAseOpCode),
                                                                            &ret );

    clxConsoleUIEngineText("\nMetadata update Data: \n");
    for (u4 loop = 0; loop < returnLength; loop++)
    {
        clxConsoleUIEngineText("%02x ", buffer[loop]);
    }

    aseValueHandle = GetValueHandle(gattClientHandle, CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);

    if ( 0 != aseValueHandle && \
         ( CLX_SUCCESS == ret && returnLength ) )
    {
        ret = clxBapSetAseOpCode( gattClientHandle,
                                  aseValueHandle,
                                  buffer,
                                  returnLength,
                                  TRUE );

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\n{Update Metadata} BAP Set ASE OP Code failed with the error %s\n",clxGetErrorCodeText(ret));
        }
    }

    return ret;
}

/**
ASE control point Release operation
*/
ClxResult aseReleaseOperation(ClxHandle gattClientHandle )
{
    ClxResult ret = CLX_FAIL;
    ClxBapAseOpCode* release = clxBleGetAseControlPoint();
    u2  aseValueHandle = 0,
        returnLength   = 0;

    u1  buffer [ CLX_GATT_MAX_LTV_RECORD_LENGTH ] = { },
        i = 0;

    release->opcode       = ClxBapAseOpCodeType_ReleaseOperation;
    release->numberOfAses = 0x01;

    /* Fill the ASE operation info as based on the numberOfAses */
    for ( i = 0; i < release->numberOfAses && release->opCodeInfo; ++i )
    {
        release->opCodeInfo[ i ].releaseOperation.aseId          = 0x01;

        clxConsoleUIEngineText("\n#%d {Release} BAP Set ASE OP Code: ASEID [%X]\n",
                                    i,
                                    release->opCodeInfo[ i ].releaseOperation.aseId );
    }

    aseValueHandle = GetValueHandle(gattClientHandle, 
                                    CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                    CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);

    returnLength = (u2)clxEncodeOrgBluetoothCharacteristicAseControlPoint ( buffer,
                                                                            CLX_GATT_MAX_LTV_RECORD_LENGTH,
                                                                            release,
                                                                            sizeof(ClxBapAseOpCode),
                                                                            &ret );

    clxConsoleUIEngineText("\nRelease Data: \n");
    for (u4 loop = 0; loop < returnLength; loop++)
    {
        clxConsoleUIEngineText("%02x ", buffer[loop]);
    }

    if ( 0 != aseValueHandle && \
         ( CLX_SUCCESS == ret && returnLength ) )
    {
        ret = clxBapSetAseOpCode( gattClientHandle,
                                  aseValueHandle,
                                  buffer,
                                  returnLength,
                                  TRUE );

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\n{Release} BAP Set ASE OP Code failed with the error %s\n",clxGetErrorCodeText(ret));
        }
    }

    return ret;
}

ClxResult bleCreateCIS(void)
{
    ClxResult ret = CLX_FAIL;

    ClxBLEAudioConfiguration*   bleAudioConfig       = clxGetBLEAudioConfigurationInfo();

    /**
    Object to store a local gatt client instance handle for GATT API commands
    */
    static ClxCentralInstanceInfo *gattClientInfo = getGattClientInstanceInfo();

    if ( bleAudioConfig->cisActiveStatus )
    {
        clxConsoleUIEngineText("\nCIS Already created");
        return CLX_SUCCESS;
    }

    bleResetIsoStreamHandleIntoAudioSendThrdCxt();

    if ( bleAudioConfig->numOfCIS > MAX_SUPPORT_CIS_COUNT || bleAudioConfig->numOfCIS == 0 )
    {
        clxConsoleUIEngineText("CIS Count[%d] is grater than MAX support CIS Count[%d]\n",
                                        bleAudioConfig->numOfCIS,
                                        MAX_SUPPORT_CIS_COUNT );

        bleAudioConfig->numOfCIS = MAX_SUPPORT_CIS_COUNT;
    }

    ClxBleCisEstablishmentResult result[ MAX_SUPPORT_CIS_COUNT ];
    ClxBleCigParameters cigParams = { };

    cigParams.cigID.value                       = CLX_BLE_ISO_CIG_ID;
    cigParams.masterToSlaveSduInterval          = 10000;
    cigParams.slaveToMasterSduInterval          = 10000;
    cigParams.framing                           = ClxBleCigFraming_Unframed;
    cigParams.slavesClockAccuracy               = (u1)0;
    cigParams.maxMasterToSlaveTransportLatency  = 300;
    cigParams.maxSlaveToMasterTransportLatency  = 300;
    cigParams.packing                           = ClxBleCigPacking_Sequential;

    ClxBleCisParameters cisParams[ MAX_SUPPORT_CIS_COUNT ];

    for (u4 i = 0; i < bleAudioConfig->numOfCIS; i++)
    {
        cisParams[i].cisID.value                = (u1)i + 1;

        cisParams[i].masterToSlavePHY.phy_1M    = TRUE;
        cisParams[i].masterToSlavePHY.phy_2M    = FALSE;
        cisParams[i].masterToSlavePHY.phy_Coded = FALSE;

        cisParams[i].slaveToMasterPHY.phy_1M    = TRUE;
        cisParams[i].slaveToMasterPHY.phy_2M    = FALSE;
        cisParams[i].slaveToMasterPHY.phy_Coded = FALSE;

        cisParams[i].maxMasterToSlaveRetransmissions = 0x01;
        cisParams[i].maxSlaveToMasterRetransmissions = 0x00;

        cisParams[i].maxMasterToSlaveSduLength = 0x50;
        cisParams[i].maxSlaveToMasterSduLength = 0x00;

        result[i].cis.streamType      = ClxBleIsoStreamType_CIS;
        result[i].cis.groupID.value   = CLX_BLE_ISO_CIG_ID;
        result[i].cis.streamID.value  = (u1) i + 1;

        result[i].aclConnectionHandle = gattClientInfo->gattClient[ 0 ].connectionHandle;
    }

    ret = clxBleIsoClientSetCigParams(getIsoClientHandle(), &cigParams, bleAudioConfig->numOfCIS, cisParams, TRUE);
    clxConsoleUIEngineText("\nclxBleIsoClientSetCigParams: result - %s\n", clxGetErrorCodeText(ret));

    ret = clxBleIsoClientEstablishCis(getIsoClientHandle(), bleAudioConfig->numOfCIS, result, TRUE);
    clxConsoleUIEngineText("\nclxBleIsoClientEstablishCis: result - %s\n", clxGetErrorCodeText(ret));

    if (ret == CLX_SUCCESS)
    {
        for (u4 i = 0; i < bleAudioConfig->numOfCIS; i++)
        {
            clxConsoleUIEngineText("\nCIS: Stream type %u, Group id %u, Stream id %u, Result %s\n",
                                                result[i].cis.streamType, 
                                                result[i].cis.groupID.value,
                                                result[i].cis.streamID.value,
                                                clxGetErrorCodeText(result[i].result));
        }
    }

    bleAudioConfig->cisActiveStatus = TRUE;

    return ret;
}

ClxResult bleDestroyCIS ( void )
{
    ClxResult ret = CLX_FAIL;

    ClxBLEAudioConfiguration*   bleAudioConfig       = clxGetBLEAudioConfigurationInfo();

    if ( FALSE == bleAudioConfig->cisActiveStatus )
    {
        clxConsoleUIEngineText("\nCIS Not yet created !!");
        return CLX_SUCCESS;
    }

    if ( 0 == bleAudioConfig->numOfCIS )
    {
        clxConsoleUIEngineText("\nCIS not created  yet!\n");
        return ret;
    }

    for (u4 i = 0; i < bleAudioConfig->numOfCIS; i++)
    {
        ClxBleIsoStream  cis = { };

        cis.streamType      = ClxBleIsoStreamType_CIS;
        cis.groupID.value   = CLX_BLE_ISO_CIG_ID;
        cis.streamID.value  = (u1)(i + 1);

        ret = clxBleIsoDisconnectCis( getIsoClientHandle(), cis, TRUE );
        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\n clxBleIsoDisconnectCis failed with error %s", clxGetErrorCodeText(ret));
            return ret;
        }

        clxConsoleUIEngineText("\nCIS: Stream type %u, Group id %u, Stream id %u",
                                            cis.streamType, 
                                            cis.groupID.value,
                                            cis.streamID.value );
    }

    bleAudioConfig->numOfCIS = 0;

    bleResetIsoStreamHandleIntoAudioSendThrdCxt();

    bleAudioConfig->cisActiveStatus = FALSE;

    return ret;
}

/* this api only for clinet role */
ClxGattCharacteristicDetail* clxBapUnicastSenderGetValueHandleByAseId (_in_       ClxHandle  gatt,
                                                                       _in_       u1         aseId,
                                                                       _user_out_ ClxResult* ret )
{
    ClxGattServiceDetail sd     = {};

    ClxBapAudioStreamEndpoint aseInfo = {};

    ClxBapAudioMetadataLtv    metadata = {};
    aseInfo.aseOthersStates.metadata = &metadata;
    clxBapInitStructureByConfigType ( aseInfo.aseOthersStates.metadata, ClxBapConfigType_MetaData);

    ClxGattUuid characteristicUuid = {};
    u1 serviceIndex = 0;
    int charIndex = 0;

    if ( 0 == gatt || NULL == ret )
    {
        return NULL;
    }

    *ret = CLX_FAIL;

    GattClient *gattClient = getGattClientHandleInfo();

    /* Disovering of Audio Streaming Control Service (ASCS) */
    ClxGattUuid serviceUuid = { };
    clxInitGattUuid2 ( &serviceUuid, (u2)CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID );

    *ret = bleCentralDiscoverAllPrimaryServices ( &serviceUuid, FALSE);

    if ( CLX_SUCCESS != *ret )
    {
        clxConsoleUIEngineText("\nbleCentralDiscoverAllPrimaryServices completed with the result %s\n", clxGetErrorCodeText(*ret));
        return NULL;
    }

    /**
    First handle shall be the handle from which the services of those would be discovered
    */
    sd.firstHandle = gattClient->serviceList[serviceIndex].firstHandle;

    /**
    Last handle shall be the handle till which the services of those would be discovered
    */
    sd.lastHandle = gattClient->serviceList[serviceIndex].lastHandle;

    /**
    Maximum size of characteristics details that can be stored in the user defined buffer.
    */
    u2 listSize = sizeof(gattClient->characteristicList) / sizeof(ClxGattCharacteristicDetail);

    /**
    Discovers all characteristics of a service in the server and get the list of attribute handle - value 
    pairs corresponding to the characteristics in the service definition.
    */

    for ( charIndex = 0; charIndex < 2; ++charIndex )
    {
        if ( 0 == charIndex )
        {
            clxInitGattUuid2 ( &characteristicUuid, (u2)CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID);
        }
        else
        {
            clxInitGattUuid2 ( &characteristicUuid, (u2)CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_UUID);
        }

        gattClient->noOfCharacteristics = 0;
        memset ( gattClient->characteristicList, 0x00, sizeof(gattClient->characteristicList) );

        *ret = clxGattClientDiscoverCharacteristics(getGattClientHandle(),
                                                    &characteristicUuid,
                                                    &sd,
                                                    listSize,
                                                    gattClient->characteristicList,
                                                    &gattClient->noOfCharacteristics,
                                                    TRUE);

        if ( CLX_SUCCESS != *ret )
        {
            clxConsoleUIEngineText("\nclxGattClientDiscoverCharacteristics completed with the result %s\n", clxGetErrorCodeText(*ret));
            return NULL;
        }

        for (u4 i = 0; i < gattClient->noOfCharacteristics; i++)
        {
            u4 valueReadLength = 0;
            if ( 0 == charIndex )
            {
                *ret = clxBapGetSinkAse( gatt,
                                        gattClient->characteristicList[i].valueHandle,
                                        (u1*)inputValue,
                                        MAX_INPUT_SIZE,
                                        &valueReadLength,
                                        TRUE );
            }
            else
            {
                *ret = clxBapGetSourceAse( gatt,
                                           gattClient->characteristicList[i].valueHandle,
                                           (u1*)inputValue,
                                           MAX_INPUT_SIZE,
                                           &valueReadLength,
                                           TRUE );
            }

            if ( CLX_SUCCESS != *ret )
            {
                clxConsoleUIEngineText("\nclxBapGetSinkAse completed with the result %s\n", clxGetErrorCodeText(*ret));
                return NULL;
            }

            /* Decode the ASE buffer */
            clxDecodeOrgBluetoothCharacteristicSourceOrSinkAse ( (u1*)inputValue,
                                                                 valueReadLength,
                                                                 &aseInfo,
                                                                 sizeof(ClxBapAudioStreamEndpoint),
                                                                 ret );

            if ( CLX_SUCCESS != *ret )
            {
                clxConsoleUIEngineText("\nDecode Sink/Source ASE completed with the result %s\n", clxGetErrorCodeText(*ret));
                return NULL;
            }

            if ( aseId == aseInfo.aseId )
            {
                clxConsoleUIEngineText("\nAse ID:% 02x, State: %s, Type: %s", 
                                                aseInfo.aseId,
                                                getAseStateFromValue(aseInfo.aseState),
                                                getAseName((u2)gattClient->characteristicList[i].uuid.value[0]));

                *ret = CLX_SUCCESS;
                return &gattClient->characteristicList[i];
            }
        }
    }

    return NULL;
}

/***************************************************************************************************************************************
*                                                Unicast Sender Menu
*
* Menu to display Low Energy unicast sender role related menu options
*
****************************************************************************************************************************************/
void bluetoothLowEnergyUnicastSenderMenu ( ClxStack stack )
{
    ClxResult ret = CLX_ERROR;

    if ( NULL == getGattClientHandle() )
    {
        clxConsoleUIEngineText("\nINVALID Gatt Client Handle");
        return;
    }

    /**
    Object to store a local gatt client instance handle for GATT API commands
    */
    static ClxCentralInstanceInfo *gattClientInfo = getGattClientInstanceInfo();

    if ( NULL == gattClientInfo )
    {
        clxConsoleUIEngineText("\nINVALID Gatt Client Instance Info");
        return;
    }

    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    /* Unicast Sender application configured as Audio source role */
    bleAudioConfig->currentRole = ClxBleRoleType_SOURCE;

    while (TRUE)
    {
        const s1* UnicastSenderMenu =    "Scan for Receiver Devices\0"
                                         "Stop Scan\0"
                                         "Connect to Discovered Device\0"
                                         "Play\0"
                                         "Pause\0"
                                         "Next\0"
                                         "Previous\0"
                                         "Disconnect from remote device\0"
                                         "Return to previous menu\0";

        u4 UnicastSenderIndex = clxConsoleUIEngineShowMenu("Please select how to proceed:",
                                                            UnicastSenderMenu,
                                                            UnicastSenderMenuItem_TotalItems - 1);

        switch (UnicastSenderIndex)
        {

            case UnicastSenderMenuItem_StartScan:
            {
                resetRemoteDeviceList();
                startExtendedScan(stack, FALSE);
                bleAudioConfig->bisOrCisStream.streamType    = ClxBleIsoStreamType_CIS;

                break;
            }

            case UnicastSenderMenuItem_StopScan:
            {
                ret = clxGapBleDisableExtendedScan(stack, TRUE);
                clxConsoleUIEngineText("\nclxGapBleDisableExtendedScan: status - %s\n", clxGetErrorCodeText(ret));

                break;
            }

            case UnicastSenderMenuItem_ConnectToDiscoveredDevice:
            {
                ClxBapAseOpCode* aseCntlPoint = clxBleGetAseControlPoint();

                /* In case the scanning is still ongoing: */
                clxGapBleStopScan(stack, TRUE);

                RemoteDeviceInfo* device = showRemoteDeviceList();

                if (device)
                {
                    ClxBleConnectionDetails connectionDetails;
                    ClxGapBleExtendedConnectParameters    connectParameter_Le1M_PHY = { };
                    ClxGattUuid characteristcUuid = { };
                    u2 negotiatedMTU = 0;

                    connectParameter_Le1M_PHY.scanInterval       = 140;
                    connectParameter_Le1M_PHY.scanWindow         = 100;
                    connectParameter_Le1M_PHY.connectIntervalMin = 50;
                    connectParameter_Le1M_PHY.connectIntervalMax = 70;
                    connectParameter_Le1M_PHY.connectionLatency  = 0;
                    connectParameter_Le1M_PHY.supervisionTimeout = 2000;
                    connectParameter_Le1M_PHY.minCElength        = 0x01;
                    connectParameter_Le1M_PHY.maxCElength        = 0x0C00;

                    ret = clxGapBleExtendedConnectToPeripheral( stack,
                                                                0x00,
                                                                0x00,
                                                                ClxBleOwnAddressMode_Identity,
                                                                &device->address,
                                                                &connectParameter_Le1M_PHY,
                                                                NULL,
                                                                NULL,
                                                                &connectionDetails,
                                                                CONNECTION_TIMEOUT,
                                                                TRUE );

                    if (CLX_SUCCESS != ret)
                    {
                        clxConsoleUIEngineText("\nPhysical Connection attempt to the device %s failed with error %s\n", device->name, clxGetErrorCodeText(ret));
                        break;
                    }

                    /* Caching the remote device connection handle, address type and its address for further processing */
                    gattClientInfo->gattClient[ 0 ].connectionHandle = connectionDetails.connectionHandle;
                    gattClientInfo->gattClient[ 0 ].peerDeviceAddress.addressType = connectionDetails.remoteDeviceAddr.addressType;

                    memcpy( gattClientInfo->gattClient[ 0 ].peerDeviceAddress.value,
                            connectionDetails.remoteDeviceAddr.value,
                            CLX_BLE_GAP_ADDRESS_VALUE_LENGTH);

                    ret = clxGapBleStartBondingProcedure(stack,
                                          gattClientInfo->gattClient[ 0 ].connectionHandle,
                                          ClxBleSmpBondingType_Bonding,
                                          getBondingProperty ( TRUE, FALSE, FALSE ),
                                          16,
                                          (u1)ClxBleSmpKeyDistribution_EncryptionKey | (u1)ClxBleSmpKeyDistribution_IdentityKey,
                                          (u1)ClxBleSmpKeyDistribution_EncryptionKey | (u1)ClxBleSmpKeyDistribution_IdentityKey,
                                          TRUE);

                    if (CLX_SUCCESS != ret)
                    {
                        clxConsoleUIEngineText("\nPairing attempt to the device %s failed with error %s\n", device->name, clxGetErrorCodeText(ret));
                        break;
                    }

                    /* Stores the paired device name */
                    ret = clxGapBleSetPairedDeviceName(stack, connectionDetails.connectionHandle, device->name, (u1)strlen(device->name), TRUE);

                    if (CLX_SUCCESS != ret)
                    {
                        clxConsoleUIEngineText("\nclxGapBleSetPairedDeviceName failed with error %s\n", clxGetErrorCodeText(ret));
                        break;
                    }

                    ret = clxGattClientBind(getGattClientHandle(), connectionDetails.connectionHandle, 500, &negotiatedMTU, TRUE);

                    if (CLX_SUCCESS != ret)
                    {
                        clxConsoleUIEngineText("\nBinding attempt to the device %s failed with error %s\n", device->name, clxGetErrorCodeText(ret));
                        break;
                    }

                    if( NULL == aseCntlPoint->opCodeInfo )
                    {
                        aseCntlPoint->opCodeInfo = (ClxAseOpCodeInfo*)clxAppAllocZero(4 * sizeof(ClxAseOpCodeInfo));
                        if ( NULL == aseCntlPoint->opCodeInfo )
                        {
                            clxConsoleUIEngineText("\nclxAppAllocZero Faill Error\n");
                        }
                        clxBleInitAseOpCodeInfo ( aseCntlPoint );
                    }

                    clxConsoleUIEngineText("\nPlease wait to establish the Unicast audio streaming procedure\n");

                    /* Enable notification to the characteristics in ASCS and PACS */
                    bleCentralEnableNotificationForAllCharacteristics(CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID);
                    bleCentralEnableNotificationForAllCharacteristics(CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID);

                    /* Discover the audio capabilities */
                    discoverAudioCapability(CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_UUID);

                    /* Discover ASE Id */
                    clxInitGattUuid2 ( &characteristcUuid, (u2)CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID );
                    bleAudioUnicastDiscoverAseIdAndState (getGattClientHandle(), &characteristcUuid);

                    clxInitGattUuid2 ( &characteristcUuid, (u2)CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_UUID );
                    bleAudioUnicastDiscoverAseIdAndState (getGattClientHandle(), &characteristcUuid);

                    /* Discover the audio contexts */
                    discoverAudioContext();

                    /* Codec configure */
                    aseConfigCodecOperation(getGattClientHandle());

                    /* Qos configure */
                    aseQosConfiguration(getGattClientHandle());

                    /* Enable */
                    aseEnableOperation(getGattClientHandle());

                    /* create CIS */
                    bleCreateCIS();

                    if (bleAudioConfig->cisActiveStatus)
                    {
                        for (u1 index  = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
                        {
                            /* Call init function to create the Audio Send thread */
                            bleInitAudioSendThread ( index );
                        }

                        clxBleSetupISODataPath ( getIsoClientHandle(),
                                                 ClxBleIsoDataPathDirection_Input,
                                                 ClxBleIsoStreamType_CIS,
                                                 bleAudioConfig->numOfCIS,
                                                 CLX_BLE_ISO_CIG_ID,
                                                 TRUE );
                    }
                }

                break;
            }

            case UnicastSenderMenuItem_Play:
            {
                u1 index = 0;

                for ( index  = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
                {
                    bleStartAudioSendProcess ( index );
                }
            }
            break;

            case UnicastSenderMenuItem_Pause:
            {
                u1 index = 0;

                for ( index  = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
                {
                    clxConsoleUIEngineText( "\nBLE Audio Send Pause #%d {Status Changed[%u -> %u]}\n",
                                            index,
                                            bleGetAudioSendThreadState ( index ),
                                            ClxBleAudioPlayState_PAUSE );

                    bleSetAudioSendThreadState ( ClxBleAudioPlayState_PAUSE, index );
                }
            }
            break;

            case UnicastSenderMenuItem_Next:
            {
                u1 index = 0;

#if ( 1 < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT )
                {
                    clxConsoleUIEngineInputBox ("Enter the BLE Audio Send thread Context Index:", inputValue, sizeof(inputValue));
                    index = (u1)atoi(inputValue); 
                }
#endif /* ( 1 < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT ) */

                clxConsoleUIEngineText( "\nBLE Audio Go to Next Audio file\n" );

                bleSetAudioSendThreadState ( ClxBleAudioPlayState_GoNext, index );
            }
            break;

            case UnicastSenderMenuItem_Previous:
            {
                u1 index = 0;

#if ( 1 < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT )
                {
                    clxConsoleUIEngineInputBox ("Enter the BLE Audio Send thread Context Index:", inputValue, sizeof(inputValue));
                    index = (u1)atoi(inputValue); 
                }
#endif /* ( 1 < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT ) */

                clxConsoleUIEngineText( "\nBLE Audio Go to Previous Audio file\n" );

                bleSetAudioSendThreadState ( ClxBleAudioPlayState_GoPrevious, index );
            }
            break;

            case UnicastSenderMenuItem_DisconnectFromDevice:
            {
                ClxBapAseOpCode* aseCntlPoint = clxBleGetAseControlPoint();

                /* Removing the ISO path */
                if (bleAudioConfig->cisActiveStatus)
                {
                    u1 index  = 0;

                    bleSetAudioSendThreadState ( ClxBleAudioPlayState_STOP, index );

                    ret = clxBleRemoveISODataPath ( getIsoClientHandle(),
                                                    ClxBleIsoDataPathDirection_Input,
                                                    ClxBleIsoStreamType_CIS,
                                                    bleAudioConfig->numOfCIS,
                                                    CLX_BLE_ISO_CIG_ID );

                    if ( CLX_SUCCESS != ret )
                    {
                        clxConsoleUIEngineText ( "BLE Remove ISO Data Path Fail- %s\n", clxGetErrorCodeText(ret));
                    }

                    for ( index  = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
                    {
                        bleDestroyAudioSendThread( index );
                    }
                }

                /* Destroy CIS */
                bleDestroyCIS ( );

                clxPoolsetFree(aseCntlPoint->opCodeInfo);
                aseCntlPoint->opCodeInfo = NULL;

                ret = clxGapBleDisconnectPhysicalLink ( stack,
                                                        gattClientInfo->gattClient[ 0 ].connectionHandle,
                                                        DISCONNECTION_TIMEOUT,
                                                        TRUE );

                clxConsoleUIEngineText("\nDisconnection completed with the result %s\n", clxGetErrorCodeText(ret));
                break;
            }

            case UnicastSenderMenuItem_ReturnToPreviousMenu:
            {
                return;
            }

            default:
            {
                clxConsoleUIEngineText("\nPlease select the valid menu options...\n");
                break;
            }
        }
    }
}

#endif /* defined(CLX_BLE_ISOCHRONOUS) */

