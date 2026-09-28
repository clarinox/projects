/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                UnicastReceiver.cpp
* Description         This main application file provides the GATT operations
*                     and main menu.
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
#include "GattServer.h"
#include "GattApp.h"
#include "BleLc3Common.h"
#include "BleIso.h"
#include "UnicastCommon.h"
#include "Gap.Ble.Bonding.Api.h"
#include "GapBleApp.h"

/* Menu options used to invoke UnicastReceiver main menu */
typedef enum BleUnicastReceiverMenuItemEnum
{
    UnicastReceiverMenuItem_StartAdvertising              = 1,
    UnicastReceiverMenuItem_StopAdvertising,
    UnicastReceiverMenuItem_ConfigureStreamControl,
    UnicastReceiverMenuItem_DeleteAllPairedDevices,
    UnicastReceiverMenuItem_ReturnToPreviousMenu,
    UnicastReceiverMenuItem_TotalItems
}UnicastReceiverMenuItem;

ClxBleExtendedAdvertisingData   extendedAdvObj          = { };
extern s1                       inputValue[MAX_INPUT_SIZE];

void bleAudioUnicastReceiverFillAdvInfo ( ClxBleExtendedAdvertisingData* extAdvertisingObj )
{
    u1 flagAdvData      = CLX_BLE_AD_FLAG_GENERAL_DISCOVERABLE_MODE;
    u2 aseServiceUUID   = CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID;
    u2 appearance       = 0x0940;   // Generic wearable audio device
    u2 role = ClxBleAudioRole_UnicastMediaReceiver | ClxBleAudioRole_BroadcastMediaReceiver;

    if ( NULL == extAdvertisingObj )
    {
        return;
    }

    clxBleGapInitExtAdvertisingBuffer (extAdvertisingObj);

    /* AD flag */
    clxBleAddExtendedAdvertisingDataField(extAdvertisingObj,
                                          CLX_BLE_GAP_AD_TYPE_FLAG,
                                          (u1*)&flagAdvData,
                                          sizeof(flagAdvData));

    /* Appearance */
    clxBleAddExtendedAdvertisingDataField(extAdvertisingObj,
                                          CLX_BLE_GAP_AD_TYPE_APPEARANCE,
                                          (u1*)&appearance,
                                          sizeof(appearance));

    /* Audio Stream Control Service */
    clxBleAddExtendedAdvertisingDataField(extAdvertisingObj,
                                          CLX_BLE_GAP_AD_TYPE_16_BIT_SERVICE_DATA,
                                          (u1*)&aseServiceUUID,
                                          (u1)sizeof(aseServiceUUID));

    /* TMAP role */
    clxGapBleSetAudioRole(role, extAdvertisingObj);

    /* Local device name */
    clxBleAddExtendedAdvertisingDataField(extAdvertisingObj,
                                          CLX_BLE_GAP_AD_TYPE_COMPLETE_LOCAL_DEVICE_NAME,
                                          (u1*)clxGetBTLocalDeviceName(),
                                          (u1)strlen(clxGetBTLocalDeviceName()));
}

void clxBleUnicastFillASEInfo ( u1 opCode, ClxBapAudioStreamEndpoint* aseRecord )
{
    if ( NULL == aseRecord )
    {
        return;
    }

    switch( opCode )
    {
        case ClxBapAEStates_Idle:
        {
            /* ASE State */
            aseRecord->aseState = ClxBapAEStates_Idle;
            break;
        }

        case ClxBapAEStates_CodecConfigured:
        {
            /* ASE State */
            aseRecord->aseState = ClxBapAEStates_CodecConfigured;

            /* Codec parameters */
            ClxBapAseServerCodecConfig*  codec = &aseRecord->codec;

            codec->framing                         = BleAudioPduFraming_UnframedIsoalNotSupported;
            codec->preferredPhy                    = BleAudioTargetPhy_LE_2M;
            codec->preferredRetransmissionNum      = 0x01;
            codec->maxTransportLatency             = CLX_BLE_ISO_MAX_TRANSPORT_LATENCY;
            codec->presentationDelayMin            = 0x060402;
            codec->presentationDelayMax            = 0x332211;
            codec->preferredPresentationDelayMin   = 0x151005;
            codec->preferredPresentationDelayMax   = 0x161106;

            codec->codecId.format            = CLX_BLE_AUDIO_CODEC_FORMAT;
            codec->codecId.companyID         = CLX_BLE_AUDIO_CODEC_COMPANY_ID;
            codec->codecId.vendorSpecificID  = CLX_BLE_AUDIO_CODEC_VENDOR_SPECIFIC_ID;

            /* Codec specific configuration */
            {
                ClxBapCodecConfig* codecInfo = &codec->aseCodecSpecificConfig;

                /* Sampling Frequency */
                {
                    codecInfo->samplingFrequency    = CLX_BLE_AUDIO_CONFIG_SAMPLING_FREQUENCIES;         // 48000 Hz
                }

                /* Frame duration */
                {
                    codecInfo->frameDuration        = CLX_BLE_AUDIO_CONFIG_FRAME_DURATIONS;      // 10 ms
                }

                /* Channels */
                {
                    codecInfo->channelAllocation    = CLX_BLE_AUDIO_CONFIG_AUDIO_CHANNEL_ALLOCATION;  // Mono
                }

                /* Max codec frames per SDU */
                {
                    codecInfo->framesPerSdu         = 0x03;        // TODO - need to test
                }
            }

            break;
        }

        case ClxBapAEStates_QoSConfigured:
        {
            /* ASE State */
            aseRecord->aseState = ClxBapAEStates_QoSConfigured;

            ClxBapAseServerQosConfiguration*  qosConfig = &aseRecord->qosConfig;

            qosConfig->cigId                     = CLX_BLE_ISO_CIG_ID;
            qosConfig->cisId                     = aseRecord->aseId;
            qosConfig->sduInterval               = CLX_BLE_ISO_SDU_INTERVAL;
            qosConfig->framing                   = BleAudioPduFraming_UnframedIsoalNotSupported;
            qosConfig->phy                       = BleAudioTargetPhy_LE_2M;
            qosConfig->retransmissionNum         = CLX_BLE_ISO_RETRANSMISSION;
            qosConfig->presentationDelay         = CLX_BLE_ISO_PRESENTATION_DELAY;
            qosConfig->maxSdu                    = CLX_BLE_ISO_MAX_SDU_SIZE;
            qosConfig->maxTransportLatency       = CLX_BLE_ISO_MAX_TRANSPORT_LATENCY;

            break;
        }

        case ClxBapAEStates_Enabling:
        case ClxBapAEStates_Streaming:
        case ClxBapAEStates_Disabling:
        {
            /* ASE State */
            aseRecord->aseState = ClxBapAEStates_Enabling;

            ClxBapAseServerOtherConfig*  aseAddStates = &aseRecord->aseOthersStates;

            aseAddStates->cigId             = CLX_BLE_ISO_CIG_ID;
            aseAddStates->cisId             = aseRecord->aseId;
            /* TO DO : Need to fill the Metadata */

            break;
        }
        
        default:
        {
            return;
        }
    }
}

void resetAseList(void)
{
    ClxResult ret = CLX_ERROR;

    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    u1 aseID = 0x01;
    u1 loop = 0;

    bleAudioConfig->currentSinkAseCount = 0;
    bleAudioConfig->currentSourceAseCount = 0;
    
    for (loop = 0; loop < CLX_BLE_UNICAST_SUPPORTED_SINK_ASE_COUNT; ++loop)
    {
        ClxBapAudioStreamEndpoint*sinkAseInfo = clxBleAppGetSinkAseRecord(loop);

        if ( NULL == sinkAseInfo )
        {
            break;
        }

        clxMemSet(sinkAseInfo, 0x00, sizeof(ClxBapAudioStreamEndpoint));

        sinkAseInfo->aseId    = aseID;                     // ASE Id
        sinkAseInfo->aseState = ClxBapAEStates_Idle;       // ASE state

        ++bleAudioConfig->currentSinkAseCount;

        ret = clxBleUnicastSetAudioStreamEndPoint( sinkAseInfo->aseId,sinkAseInfo );
        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nSet Sink ASE status FAIL - %s\n", clxGetErrorCodeText(ret));
            break;
        }
        /* To increase the ASE ID as odd numbers */
        aseID += 1;
    }
    
    for (loop = 0; loop < CLX_BLE_UNICAST_SUPPORTED_SOURCE_ASE_COUNT; ++loop)
    {
        ClxBapAudioStreamEndpoint*sourceAseInfo = clxBleAppGetSourceAseRecord(loop);

        if ( NULL == sourceAseInfo )
        {
            break;
        }

        clxMemSet(sourceAseInfo, 0x00, sizeof(ClxBapAudioStreamEndpoint));

        sourceAseInfo->aseId    = aseID;                     // ASE Id
        sourceAseInfo->aseState = ClxBapAEStates_Idle;       // ASE state

        ++bleAudioConfig->currentSourceAseCount;

        ret = clxBleUnicastSetAudioStreamEndPoint( sourceAseInfo->aseId, sourceAseInfo );
        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nSet Source ASE status FAIL - %s\n", clxGetErrorCodeText(ret));
            break;
        }

        /* To increase the ASE ID as even numbers */
        aseID += 1;
    }

}

u2 clxBleGetServerAseLocalValueHandle ( ClxBleRoleType aseRole, u1 aseIndex )
{
    if ( ClxBleRoleType_SINK == aseRole )
    {
        s4 sinkAseHandleIndex = CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_HANDLE_INDEX;

        /* This condition applies only when there are multiple Sink ASEs with the same UUID */
        if ( 0 != aseIndex )
        {
            sinkAseHandleIndex += (3*aseIndex);
        }

        return clxBleGetServerLocalValueHandle(GattService_AudioStreamControlIndex, sinkAseHandleIndex);
    }
    else if ( ClxBleRoleType_SOURCE == aseRole )
    {
        s4 sourceAseHandleIndex = CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_HANDLE_INDEX;

        /* This condition applies only when there are multiple Source ASEs with the same UUID */
        if ( 0 != aseIndex )
        {
            sourceAseHandleIndex += (3*aseIndex);
        }

        return clxBleGetServerLocalValueHandle(GattService_AudioStreamControlIndex, sourceAseHandleIndex);
    }
    else
    {
        clxConsoleUIEngineText("Invlaid ASE Role Type\n");
        return 0;
    }
}

ClxBleRoleType getAseRoleAndIndexFromList(u1 aseId, u1* index)
{
    u1 loop = 0;

    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    if ( NULL == index )
    {
        return ClxBleRoleType_INVALID;
    }

    *index = CLX_BAP_INVALID_FIELD_U8;

    for (loop = 0; loop < bleAudioConfig->currentSinkAseCount; ++loop)
    {
        ClxBapAudioStreamEndpoint*sinkAseInfo = clxBleAppGetSinkAseRecord(loop);

        if ( NULL == sinkAseInfo )
        {
            break;
        }

        if (aseId == sinkAseInfo->aseId)
        {
            *index = loop;
            return ClxBleRoleType_SINK;
        }
    }

    for (loop = 0; loop < bleAudioConfig->currentSourceAseCount; ++loop)
    {
        ClxBapAudioStreamEndpoint*sourceAseInfo = clxBleAppGetSourceAseRecord(loop);

        if ( NULL == sourceAseInfo )
        {
            break;
        }

        if (aseId == sourceAseInfo->aseId)
        {
            *index = loop;
            return ClxBleRoleType_SOURCE;
        }
    }

    return ClxBleRoleType_INVALID;
}

/*****************************************************************************************************************************************
*                                        clxBleUnicastSetAudioStreamEndPoint
*
* Configure the audio Stream End point
*
* \param aseID         ASE ID
* \param opCode        OpCode to set into Audio stream endpoint
*
****************************************************************************************************************************************/
ClxResult clxBleUnicastSetAudioStreamEndPoint (u1 aseID, ClxBapAudioStreamEndpoint* inputAseInfo )
{
    /* Need to hanlde as check and write only the ASE Control point */
    ClxResult errCode  = CLX_ERROR;
    u1 aseIndex = CLX_BAP_INVALID_FIELD_U8;

    ClxBleRoleType aseRole = ClxBleRoleType_INVALID;

    ClxBapAudioStreamEndpoint* unicastReceiverAse = NULL;

    ClxSize filledLength = 0;

    u2 aseServerHandleIndex = 0;

    if ( NULL == getGattServerHandle() )
    {
        clxConsoleUIEngineText("\nInvalid GATT server handle\n" );
        return errCode;
    }

    if ( NULL == inputAseInfo )
    {
        return errCode;
    }

    aseRole = getAseRoleAndIndexFromList(aseID, &aseIndex);

    if (CLX_BAP_INVALID_FIELD_U8 == aseIndex)
    {
        clxConsoleUIEngineText("\nInvalid ASE Id[0x%X]\n",aseID);
        return errCode;
    }

    if ( ClxBleRoleType_SINK == aseRole )
    {
        unicastReceiverAse = clxBleAppGetSinkAseRecord( aseIndex );
    }
    else if ( ClxBleRoleType_SOURCE == aseRole )
    {
        unicastReceiverAse = clxBleAppGetSourceAseRecord( aseIndex );
    }

    if ( NULL == unicastReceiverAse )
    {
        clxConsoleUIEngineText("\nInvalid ASE Record\n" );
        return errCode;
    }

    switch( inputAseInfo->aseState )
    {
        case ClxBapAEStates_Idle:
        {
            /* ASE State */
            unicastReceiverAse->aseState = ClxBapAEStates_Idle;
            break;
        }

        case ClxBapAEStates_CodecConfigured:
        {
            /* ASE State */
            unicastReceiverAse->aseState = ClxBapAEStates_CodecConfigured;

            memcpy(&unicastReceiverAse->codec, &inputAseInfo->codec, sizeof(ClxBapAseServerCodecConfig));

            break;
        }

        case ClxBapAEStates_QoSConfigured:
        {
            /* ASE State */
            unicastReceiverAse->aseState = ClxBapAEStates_QoSConfigured;

            memcpy(&unicastReceiverAse->qosConfig, &inputAseInfo->qosConfig, sizeof(ClxBapAseServerQosConfiguration));

            break;
        }

        case ClxBapAEStates_Enabling:
        case ClxBapAEStates_Streaming:
        case ClxBapAEStates_Disabling:
        {
            /* ASE State */
            unicastReceiverAse->aseState = ClxBapAEStates_Enabling;

            ClxBapAseServerOtherConfig*  aseAddStates = &unicastReceiverAse->aseOthersStates;

            aseAddStates->cigId             = inputAseInfo->aseOthersStates.cigId;
            aseAddStates->cisId             = inputAseInfo->aseOthersStates.cisId;

            /* TODO (Temporary): Currently setting metadata to a fixed length of CLX_GATT_MAX_LTV_RECORD_LENGTH. 
               If we later change it to support dynamic length, the handling below must be updated accordingly. */
            if ( aseAddStates->metadata && inputAseInfo->aseOthersStates.metadata )
            {
                memcpy(aseAddStates->metadata, inputAseInfo->aseOthersStates.metadata, sizeof(ClxBapAudioMetadataLtv));
            }

            break;
        }
        
        default:
        {
            errCode = CLX_ERROR_INVALID_COMMAND_ARGUMENT;
            return errCode;
        }
    }

    /* In some cases, there are multiple Sink ASEs with the same UUID, 
       so we retrieve the handle index using an API instead of accessing it directly */
    aseServerHandleIndex = clxBleGetServerAseLocalValueHandle(aseRole, aseIndex);

    if ( ClxBleRoleType_SINK == aseRole )
    {
        errCode = clxBapEncodeSinkAse( unicastReceiverAse,
                                       (u1*)inputValue,
                                       MAX_INPUT_SIZE,
                                       &filledLength );

        if ( CLX_SUCCESS != errCode )
        {
            return errCode;
        }

        errCode = clxBapSetSinkAse ( getGattServerHandle(),
                                     aseServerHandleIndex,
                                     (u1*)inputValue,
                                     filledLength,
                                     TRUE );

        if (CLX_SUCCESS != errCode)
        {
            printBufferHexAndChar ( (u1*)inputValue, filledLength );
            clxConsoleUIEngineText("\nSet Sink ASE Fail with the result %s\n", clxGetErrorCodeText(errCode));
            return errCode;
        }

        clxConsoleUIEngineText("\nSet Sink ASE: status - %s\n", clxGetErrorCodeText(errCode));
        return errCode;
    }
    else if ( ClxBleRoleType_SOURCE == aseRole )
    {
        errCode = clxBapEncodeSourceAse( unicastReceiverAse,
                                         (u1*)inputValue,
                                         MAX_INPUT_SIZE,
                                         &filledLength );

        if ( CLX_SUCCESS != errCode )
        {
            return errCode;
        }

        errCode = clxBapSetSourceAse ( getGattServerHandle(),
                                       aseServerHandleIndex,
                                       (u1*)inputValue,
                                       filledLength,
                                       TRUE );

        if (CLX_SUCCESS != errCode)
        {
            printBufferHexAndChar ( (u1*)inputValue, filledLength );
            clxConsoleUIEngineText("\nSet Source ASE Fail with the result %s\n", clxGetErrorCodeText(errCode));
            return errCode;
        }

        clxConsoleUIEngineText("\nSet Source ASE: status - %s\n", clxGetErrorCodeText(errCode));
        return errCode;
    }
    else
    {
        clxConsoleUIEngineText("\nInvalid ASE Id\n");
        return errCode;
    }
}

void clxBleUnicastSetPacInfo( ClxBleRoleType role )
{
    ClxResult ret = CLX_SUCCESS;

    u1  codeCabLocLength  = 0;
    u1  pacIndex          = 0;
    ClxSize filledLength = 0;

    u2 frequency [] = { 0x0020 /* 32000 Hz */, 0x0080 /* 48000 Hz */ };
    u4 octect[]     = { 0x0050003c /* 32000 Hz */, 0x009b004b /* 48000 Hz*/ };

    ClxBapPacRecords  pacInfo = {};

    pacInfo.numberOfPacRecords = CLX_GATT_MAX_PAC_RECORD_SUPPORTED;

    if ( pacInfo.numberOfPacRecords )
    {
        pacInfo.pacRecords = (ClxBapSinglePacRecord*)clxAppAllocZero(pacInfo.numberOfPacRecords * sizeof(ClxBapSinglePacRecord));

        if ( NULL == pacInfo.pacRecords )
        {
            return;
        }
    }

    for ( pacIndex = 0; pacIndex < pacInfo.numberOfPacRecords && pacInfo.pacRecords; ++pacIndex )
    {
        codeCabLocLength  = 0;

        ClxBapCodecCapabilities *codecCabInfo = &pacInfo.pacRecords[pacIndex].capabilities;
        ClxBapAudioMetadataLtv *metadataInfo  = &pacInfo.pacRecords[pacIndex].metadata;

        clxBapInitStructureByConfigType ( codecCabInfo, ClxBapConfigType_CodecCapability);
        clxBapInitStructureByConfigType ( metadataInfo, ClxBapConfigType_MetaData);

        /* Codec ID */
        pacInfo.pacRecords[pacIndex].codecId.format            = CLX_BLE_AUDIO_CODEC_FORMAT;

        pacInfo.pacRecords[pacIndex].codecId.companyID         = 0x00;
        pacInfo.pacRecords[pacIndex].codecId.vendorSpecificID  = 0x00;

        /* Set Codec Specific Capabilities data */

        /* Sampling Frequency */
        {
           codecCabInfo->supportedSamplingFrequencies       = frequency[pacIndex];        // 48000 Hz
        }

        /* Frame duration */
        {
           codecCabInfo->supportedFrameDurations            = 0x02;            // 10 ms
        }

        /* Audio channel */
        {
           codecCabInfo->supportedChannelAllocations        = 0x01;           // Mono
        }

        /* Octect per Frame */
        {
           codecCabInfo->supportedFrameLengthRange          = octect[pacIndex];
        }

        /* No.of codec frmae per SDU */
        {
           codecCabInfo->supportedSduIntervals              = 0x01;
        }

        /* 2 LTV structures for Subgroup[0], defining: as below */
        /* << Set MetaData Configurations >> */
        if ( metadataInfo )
        {
            /* MetaData LTV 1: Streaming Audio Contexts: */
            /* Preferred_Audio_Contexts LTV structure Value as MEDIA */
            metadataInfo->preferredAudioContexts = 0x01;
        }
    }

    ret = clxBapEncodePacRecord( static_cast<const ClxBapPacRecords*>(&pacInfo),
                                 (u1*)inputValue,
                                 MAX_INPUT_SIZE,
                                 &filledLength );

    if ( CLX_SUCCESS != ret )
    {
        clxConsoleUIEngineText("\nEncode Sink PAC: status - %s\n", clxGetErrorCodeText(ret));
        return;
    }

    if( ClxBleRoleType_SINK == role )
    {
        ret = clxBapSetSinkPac( getGattServerHandle(),
                                clxBleGetServerLocalValueHandle(GattService_PublishedAudioCapabilitiesIndex,
                                                                CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_HANDLE_INDEX),
                                (u1*)inputValue,
                                filledLength,
                                TRUE );

        clxConsoleUIEngineText("\nSet Sink PAC: status - %s\n", clxGetErrorCodeText(ret));
    }
    else if( ClxBleRoleType_SOURCE == role )
    {
        ret = clxBapSetSourcePac( getGattServerHandle(),
                                clxBleGetServerLocalValueHandle(GattService_PublishedAudioCapabilitiesIndex,
                                                                CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_HANDLE_INDEX),
                                (u1*)inputValue,
                                filledLength,
                                TRUE );

        clxConsoleUIEngineText("\nSet Source PAC: status - %s\n", clxGetErrorCodeText(ret));
    }

    for (pacIndex = 0; pacIndex < pacInfo.numberOfPacRecords; ++pacIndex)
    {
        clxConsoleUIEngineText("\n[#%d] Format[%s] Sampling Freq[%u Hz] Frame duration[%s] Audio channel[%X]", pacIndex,
            getCodingFormatFromBitValue((u1)pacInfo.pacRecords[pacIndex].codecId.format),
            getCapSamplingFrequencyFromBitValue(pacInfo.pacRecords[pacIndex].capabilities.supportedSamplingFrequencies),
            getCapFrameDurationFromBitValue(pacInfo.pacRecords[pacIndex].capabilities.supportedFrameDurations),
            pacInfo.pacRecords[pacIndex].capabilities.supportedChannelAllocations);
    }

    if ( pacInfo.pacRecords )
    {
        clxPoolsetFree( pacInfo.pacRecords );
    }
}

void clxBleUnicastSetAudioLocations( ClxBleRoleType role, u4 audioLocations )
{
    ClxResult ret = CLX_SUCCESS;
    ClxBapPacAudioLocations audioLoc = {};
    audioLoc.pacAudioLocations = audioLocations;

    if( ClxBleRoleType_SINK == role )
    {
        ret = clxBapSetSinkAudioLocation ( getGattServerHandle(),
                                           clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                                            CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_HANDLE_INDEX ),
                                           audioLoc,
                                           TRUE );
        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nSet Sink Audio Location: FAIL status - %s\n", clxGetErrorCodeText(ret));
        }
        else
        {
            clxConsoleUIEngineText("\nSet Sink Audio Location:[%X]\n", audioLocations);
        }
    }
    else if( ClxBleRoleType_SOURCE == role )
    {
        ret = clxBapSetSourceAudioLocation ( getGattServerHandle(),
                                           clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                                            CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_HANDLE_INDEX ),
                                           audioLoc,
                                           TRUE );
        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nSet Source Audio Location: FAIL status - %s\n", clxGetErrorCodeText(ret));
        }
        else
        {
            clxConsoleUIEngineText("\nSet Source Audio Location:[%X]\n", audioLocations);
        }
    }
}

/*****************************************************************************************************************************************
*                                        setPublicAudioCapabilities
*
* Configure the audio capabilities in Source/Sink PAC characteristic
*
****************************************************************************************************************************************/
void setPublicAudioCapabilities(void)
{
    clxBleUnicastSetPacInfo ( ClxBleRoleType_SINK );
    clxBleUnicastSetPacInfo ( ClxBleRoleType_SOURCE );

    clxBleUnicastSetAudioLocations ( ClxBleRoleType_SINK, 0x00000003 );
    clxBleUnicastSetAudioLocations ( ClxBleRoleType_SOURCE, 0x00000001 );

    configureAvailableAudioContexts( );
    configureSupportedAudioContext( );
}

/***************************************************************************************************************************************
*                                                Unicast Receiver Menu
*
* Menu to display Low Energy unicast Receiver role related menu options
*
****************************************************************************************************************************************/
void bluetoothLowEnergyUnicastReceiverMenu ( ClxStack stack )
{
    initAdvertisingData(clxGetBTLocalDeviceName());

    bleResetIsoStreamHandleIntoAudioSendThrdCxt ( );

    resetAseList();
    setPublicAudioCapabilities();

    while (TRUE)
    {
        const s1* unicastReceiver = "Advertise Local Device Data\0"
                                    "Stop Advertising\0"
                                    "Configure Stream Control\0"
                                    "Delete All Paired Devices\0"
                                    "Return to previous menu\0";

        u4 unicastReceiverIndex = clxConsoleUIEngineShowMenu("Please select how to proceed:",
                                                             unicastReceiver,
                                                             UnicastReceiverMenuItem_TotalItems - 1);

        switch (unicastReceiverIndex)
        {
            case UnicastReceiverMenuItem_StartAdvertising:
            {
                ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();
                
                bleAudioConfig->bisOrCisStream.streamType    = ClxBleIsoStreamType_CIS;
                bleAudioUnicastReceiverFillAdvInfo ( &extendedAdvObj );
                bleStartExtendedAdvertising ( stack, &extendedAdvObj, FALSE);
            }
            break;

            case UnicastReceiverMenuItem_StopAdvertising:
            {
                bleStopExtendedAdvertising ( stack, &extendedAdvObj );
                clxBleGapDestroyExtAdvertisingBuffer ( &extendedAdvObj );
            }
            break;

            case UnicastReceiverMenuItem_ConfigureStreamControl:
            {
                u4 option = 0;
                u1 loop = 0;

                ClxBapAudioStreamEndpoint inputAse = {};
                ClxBapAudioMetadataLtv    metadata = {};
                inputAse.aseOthersStates.metadata = &metadata;

                clxConsoleUIEngineInputBox ("Enter {0: Idle, 1: Codec configure, 2: Qos configure, 3: Enable, 4: Streaming, 5: Disable }\n", inputValue, MAX_INPUT_SIZE );
                option = (ClxBapAudioEndpointStates) atoi(inputValue);

                for (loop = 0; loop < CLX_BLE_UNICAST_SUPPORTED_ASE_COUNT; loop++)
                {
                    clxBleUnicastFillASEInfo( (u1) option, &inputAse );

                    /* For Temporary: set the ASEId as 1,2,3... (Sink ASE Id's are odd and Source ASE Id's are even numbers) */
                    clxBleUnicastSetAudioStreamEndPoint( loop + 1, &inputAse );
                }
            }
            break;

            case UnicastReceiverMenuItem_DeleteAllPairedDevices:
            { 
                ClxError err = clxGapBleDeleteAllPairedDevicesInfo(stack, TRUE);
                clxConsoleUIEngineText("\nDeleting All Paired info completed with %s\n", clxGetErrorCodeText(err));
            }
            break;

            case UnicastReceiverMenuItem_ReturnToPreviousMenu:
            {
                bleResetIsoStreamHandleIntoAudioSendThrdCxt ( );
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

