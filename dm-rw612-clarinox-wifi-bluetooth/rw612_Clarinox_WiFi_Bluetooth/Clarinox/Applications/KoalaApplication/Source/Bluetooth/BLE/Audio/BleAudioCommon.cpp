/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                BleAudioCommon.cpp
* Description         This file BLE audio Common APIs
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
#include "GattClient.h"
#include "Iso.Ble.Client.Api.h"

#if defined(CLX_FLOATINGPOINT_LC3)
#include "FloatingpointLc3.h"
#endif /* defined(CLX_FLOATINGPOINT_LC3) */
#include "BleLc3Common.h"
#include "BleIso.h"

#include "BroadcastCommon.h"
#include "UnicastCommon.h"

ClxAppStreamChannelMode streamChannelMode = ClxAppStreamChannelMode_NotSet;

ClxBLEAudioConfiguration  bleAudioSetupConfig = { };

ClxBleAudioBISBasicAudioAnnouncement bisBasicAnnouncement = {};

u2 periodicSyncHandle = CLX_BLE_AUDIO_INVALID_HANDLE_VALUE;

static const s1* codecFormat[] =    {
                                          "uLaw"
                                        , "aLaw"
                                        , "CVSD"
                                        , "HCI"
                                        , "Linear PCM"
                                        , "mSBC"
                                        , "LC3"
                                        , "G 729A"
                                    };

/* ISO Server handle */
static ClxHandle    isoServerHandle    = NULL;

/* ISO Client handle */
static ClxHandle    isoClientHandle    = NULL;

/* CIS releated Variables */
ClxBapAseOpCode           aseCntlPt = {};

ClxBapBroadcastReceiveState bassReceiveState = { };

static u1 prefStreamId;
static u1 prefAudioCount;
static u2 prefStreamHandle;

extern s1  inputValue[MAX_INPUT_SIZE];

extern ClxBleBroadcastSelectorInfo gBroadcastSelectorInfo;

/* Menu options used to invoke BLE main menu */
typedef enum BleAudioItemEnum
{
    BleAudioMenuItem_DiscoverBleAudioDevices                    = 1,
    BleAudioMenuItem_StopDiscovering,
    BleAudioMenuItem_UnicastMediaSender,
    BleAudioMenuItem_UnicastMediaReceiver,
    BleAudioMenuItem_BroadcastMediaSender,
    BleAudioMenuItem_BroadcastMediaReceiver,
    BleAudioMenuItem_BroadcastSelector,
#if defined( CLX_LC3_PERFORMANCE_MEASUREMENT )
    BleAudioMenuItem_LC3CpuUtilisationTest,
#endif /* defined( CLX_LC3_PERFORMANCE_MEASUREMENT ) */
    BleAudioMenuItem_ReturnToPreviousMenu,
    BleAudioMenuItem_TotalItem

}BleAudioMenuItem;

/* Menu options used to invoke BLE BAP Profile menu */
typedef enum BleBapProfileEnum
{
    BleBapProfile_ASCS                    = 1,
    BleBapProfile_PACS,
    BleBapProfile_BASS,
    BleBapProfile_ReturnToPreviousMenu,
    BleBapProfile_TotalItem
}BleBapProfileItem;

/* Menu options used to invoke BLE BAP ASCS Profile menu */
typedef enum BleBapAscsProfileEnum
{
    BleBapAscs_GetSinkASE= 1,
    BleBapAscs_SetSinkASE,
    BleBapAscs_GetSourceASE,
    BleBapAscs_SetSourceASE,
    BleBapAscs_GetASEOpCode,
    BleBapAscs_SetASEOpCode,
    BleBapAscs_ReturnToPreviousMenu,
    BleBapAscs_TotalItem
}BleBapAscsProfileItem;

/* Menu options used to invoke BLE BAP PACS Profile menu */
typedef enum BleBapPacsProfileEnum
{
    BleBapPacs_GetSinkPAC= 1,
    BleBapPacs_SetSinkPAC,
    BleBapPacs_GetSinkAudioLocation,
    BleBapPacs_SetSinkAudioLocation,
    BleBapPacs_GetSourcePAC,
    BleBapPacs_SetSourcePAC,
    BleBapPacs_GetSourceAudioLocation,
    BleBapPacs_SetSourceAudioLocation,
    BleBapPacs_GetAvailableAudioContext,
    BleBapPacs_SetAvailableAudioContext,
    BleBapPacs_GetSupportedAudioContext,
    BleBapPacs_SetSupportedAudioContext,
    BleBapPacs_ReturnToPreviousMenu,
    BleBapPacs_TotalItem
}BleBapPacsProfileItem;

/* Menu options used to invoke BLE BAP BASS Profile menu */
typedef enum BleBapBassProfileEnum
{
    BleBapBass_GetBroadcastOpCode= 1,
    BleBapBass_SetBroadcastOpCode,
    BleBapBass_GetBroadcastReceiveState,
    BleBapBass_SetBroadcastReceiveState,
    BleBapBass_ReturnToPreviousMenu,
    BleBapBass_TotalItem
}BleBapBassProfileItem;

/* Callback function to accept or reject the BIS connection */
boolean bisRequestHandlerFunc (ClxHandle handle, ClxBleIsoStream bisOrCIS, u2 aclConnectionHandle)
{
    (void)handle;
    (void)aclConnectionHandle;

    clxConsoleUIEngineText("\nBIS(or)CIS ISO connection request received (Group-ID=%u, Stream-ID=%u)\n", bisOrCIS.groupID, bisOrCIS.streamID);

    setPreferredStreamId(bisOrCIS.streamID.value);

    return TRUE;
}

void bleCreateIsoServer ( ClxStack stack )
{
    if (isoServerHandle)
    {
        clxConsoleUIEngineText("\nISO Server is already created \n");
        return;
    }

    isoServerHandle = clxBleIsoServerCreate(stack, stackMessageHandler, bisRequestHandlerFunc);
}

void bleDeleteIsoServer ( void )
{
    if (!isoServerHandle)
    {
         clxConsoleUIEngineText("\nISO Server is not yet created \n");
        return;
    }

    clxCloseHandle(isoServerHandle);
    isoServerHandle = NULL;
}

ClxHandle  getIsoServerHandle ( void )
{
    return isoServerHandle;
}

/**
Handle Creation and deletion for ISO Client (CIS)
*/
void bleCreateIsoClient ( ClxStack stack )
{
    if (isoClientHandle)
    {
        clxConsoleUIEngineText("\nISO Client is already created \n");
        return;
    }

    isoClientHandle = clxBleIsoClientCreate ( stack, stackMessageHandler );
}

void bleDeleteIsoClient ( void )
{
    if (!isoClientHandle)
    {
         clxConsoleUIEngineText("\nISO Client is not yet created \n");
        return;
    }

    clxCloseHandle(isoClientHandle);
    isoClientHandle = NULL;
}

ClxHandle  getIsoClientHandle ( void )
{
    return isoClientHandle;
}

/***************************************************************************************************************************************
*                                        bluetoothLowEnergyAudioMenu
*
* Menu to display Bluetooth Low Energy Audio main menu options
*
* \param stack      - ClarinoxBlue stack
*
****************************************************************************************************************************************/
void bluetoothLowEnergyAudioMenu ( ClxStack stack )
{
    if (stack == NULL)
    {
        clxConsoleUIEngineText("\nClarinox Stack has to be initialized first\n");
        return;
    }

    while ( TRUE )
    {
        const s1* menu =    "Discover BLE Audio devices\0"
                            "Stop discovering\0"
                            "Unicast Media Sender (UMS)\0"
                            "Unicast Media Receiver (UMR)\0"
                            "Broadcast Media Sender (BMS)\0"
                            "Broadcast Media Receiver (BMR)\0"
                            "Broadcast Selector (BS)\0"
#if defined( CLX_LC3_PERFORMANCE_MEASUREMENT )
                            "LC3 CPU Utilisation Test\0"
#endif /* defined( CLX_LC3_PERFORMANCE_MEASUREMENT ) */
                            "Return to previous menu\0";

        u4 index = clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, BleAudioMenuItem_TotalItem - 1);

        switch ( index )
        {
            case BleAudioMenuItem_DiscoverBleAudioDevices:
            {
                resetRemoteDeviceList();
                startExtendedScan(stack, TRUE);
                break;
            }

            case BleAudioMenuItem_StopDiscovering:
            {
                ClxResult ret = clxGapBleDisableExtendedScan(stack, TRUE);

                if (CLX_SUCCESS != ret)
                {
                    clxConsoleUIEngineText("\nclxGapBleDisableExtendedScan: status - %s\n", clxGetErrorCodeText(ret));
                }
                break;
            }

            case BleAudioMenuItem_UnicastMediaSender:
            {
                bluetoothLowEnergyUnicastSenderMenu( stack );
            }
            break;

            case BleAudioMenuItem_UnicastMediaReceiver:
            {
                bluetoothLowEnergyUnicastReceiverMenu( stack );
            }
            break;

            case BleAudioMenuItem_BroadcastMediaSender:
            {
                bluetoothLowEnergyBroadcastSenderMenu( stack );
            }
            break;

            case BleAudioMenuItem_BroadcastMediaReceiver:
            {
                bluetoothLowEnergyBroadcastReceiverMenu( stack );
            }
            break;

            case BleAudioMenuItem_BroadcastSelector:
            {
                bluetoothLowEnergyBroadcastSelectorMenu(stack);
                break;
            }

#if defined( CLX_LC3_PERFORMANCE_MEASUREMENT )
            case BleAudioMenuItem_LC3CpuUtilisationTest:
            {
                extern void bluetoothLowEnergyAudioLc3TestMenu( ClxStack stack );
                bluetoothLowEnergyAudioLc3TestMenu( stack );
            }
            break;
#endif /* defined( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

            case BleAudioMenuItem_ReturnToPreviousMenu:
            {
                return;
            }

            default:
            {
                clxConsoleUIEngineText("\nPlease select a valid menu option..\n");
            }
            break;

        } /* switch ( index ) */

    } /* while ( TRUE ) */
}

/*******************************************************************************************************************************
*                                        clxBleAudioPrintDataBasedOnSpecFormat
*
* Print the Data Based On Spec mentioned Structure Format like Codec Specific Configuration, Capability and Metadata info's
*
*\param sourceBuffer       It contains data in the defined spec-based structure. and use the ClxBapConfigType enum to know config type.
*\param sourceBufferType   Structure Format type enum
*
*******************************************************************************************************************************/
void clxBleAudioPrintDataBasedOnSpecFormat ( void*                        sourceBuffer,
                                             ClxBleAudioSpecStructureType dataType )
{
    s1 outputMsg[ 0xFFF ] = { };
    boolean dataAvailable = FALSE;

    if ( NULL == sourceBuffer )
    {
        clxConsoleUIEngineText("\nInvalid Source Buffer{Print Failed}\n");
        return;
    }

    switch ( dataType )
    {
        case ClxBleAudioSpecStructure_CodecConfig :
        {
            ClxBapCodecConfig* codecConfig = (ClxBapCodecConfig*)sourceBuffer;

            clxConsoleUIEngineText("\n**** Codec_Specific_Configuration ****\n");

            if ( ClxBapCodecSamplingFreq_8000Hz <= codecConfig->samplingFrequency &&\
                 ClxBapCodecSamplingFreq_384000Hz >= codecConfig->samplingFrequency )
            {
                sprintf( outputMsg + strlen(outputMsg), "SamplingFrequency[%u Hz] ", getSamplingFrequencyFromValue ( codecConfig->samplingFrequency ));
                dataAvailable = TRUE;
            }

            if ( 0x00 == codecConfig->frameDuration ||\
                 0x01 == codecConfig->frameDuration )
            {
                sprintf( outputMsg + strlen(outputMsg), "FrameDuration[%s] ",
                            (0 == codecConfig->frameDuration) ? "7.5 ms" : "10 ms" );

                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != codecConfig->channelAllocation )
            {
                sprintf( outputMsg + strlen(outputMsg), "ChannelCount[%u] ", codecConfig->channelAllocation );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != codecConfig->frameLength  )
            {
                sprintf( outputMsg + strlen(outputMsg), "FrameLengthInBytes[%u] ", codecConfig->frameLength );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != codecConfig->framesPerSdu )
            {
                sprintf( outputMsg + strlen(outputMsg), "FrameBlocksPerSDU[%u] ", codecConfig->framesPerSdu );
                dataAvailable = TRUE;
            }

            if ( FALSE == dataAvailable )
            {
                clxConsoleUIEngineText("--No Data--", outputMsg );
            }
            else
            {
                clxConsoleUIEngineText("    { %s}", outputMsg );
            }

            clxConsoleUIEngineText("\n");
        }
        break;

        case ClxBleAudioSpecStructure_CodecCapability :
        {
            ClxBapCodecCapabilities *codecCabInfo = (ClxBapCodecCapabilities*)sourceBuffer;

            clxConsoleUIEngineText("\n**** Codec_Specific_Configuration ****\n");

            if ( CLX_BAP_NULL_BYTE != codecCabInfo->supportedSamplingFrequencies )
            {
                sprintf( outputMsg + strlen(outputMsg), "Supported Sampling Frequencies BitMask[0x%X] ",
                                        getCapSamplingFrequencyFromBitValue ( codecCabInfo->supportedSamplingFrequencies ));
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != codecCabInfo->supportedFrameDurations )
            {
                sprintf( outputMsg + strlen(outputMsg), "Supported Frame Durations[%s] ",
                            getCapFrameDurationFromBitValue ( codecCabInfo->supportedFrameDurations ));

                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != codecCabInfo->supportedChannelAllocations )
            {
                sprintf( outputMsg + strlen(outputMsg), "ChannelCount BitMask[0x%X] ", codecCabInfo->supportedChannelAllocations );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != codecCabInfo->supportedFrameLengthRange  )
            {
                sprintf( outputMsg + strlen(outputMsg), "Supported FrameLengthRange[%u] ", codecCabInfo->supportedFrameLengthRange );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != codecCabInfo->supportedSduIntervals )
            {
                sprintf( outputMsg + strlen(outputMsg), "Supported SDU Intervals[%u] ", codecCabInfo->supportedSduIntervals );
                dataAvailable = TRUE;
            }

            if ( FALSE == dataAvailable )
            {
                clxConsoleUIEngineText("--No Data--", outputMsg );
            }
            else
            {
                clxConsoleUIEngineText("    { %s}", outputMsg );
            }

            clxConsoleUIEngineText("\n");

        }
        break;

        case ClxBapConfigType_MetaData :
        {
            ClxBapAudioMetadataLtv*   metadata = (ClxBapAudioMetadataLtv*)sourceBuffer;

            clxConsoleUIEngineText("\n**** MetaData ****\n");

            if ( CLX_BAP_NULL_BYTE != metadata->preferredAudioContexts )
            {
                sprintf( outputMsg + strlen(outputMsg), "PreferredAudioContext[0x%04X] ", metadata->preferredAudioContexts );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->streamingAudioContexts )
            {
                sprintf( outputMsg + strlen(outputMsg), "StreamingAudioContext[0x%04X] ", metadata->streamingAudioContexts );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->languageCode[ 0 ] && \
                 CLX_BAP_NULL_BYTE != metadata->languageCode[ 1 ] && \
                 CLX_BAP_NULL_BYTE != metadata->languageCode[ 2 ] )
            {
                sprintf( outputMsg + strlen(outputMsg), "Language[%c%c%c] ",
                                    metadata->languageCode[ 2 ],
                                    metadata->languageCode[ 1 ],
                                    metadata->languageCode[ 0 ] );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_INVALID_FIELD_U8 != metadata->parentalRating )
            {
                sprintf( outputMsg + strlen(outputMsg), "ParentalRating[0x%02X] ", metadata->parentalRating );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_INVALID_FIELD_U8 != metadata->audioActivityState )
            {
                sprintf( outputMsg + strlen(outputMsg), "AudioActivityState[0x%02X] ", metadata->audioActivityState );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_INVALID_FIELD_U8 != metadata->broadcastAudioImmediateFlag )
            {
                sprintf( outputMsg + strlen(outputMsg), "BroadcastAudioImmRendFlag[%s] ",
                                            metadata->broadcastAudioImmediateFlag ? "Set" : "Not-Set");
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_INVALID_FIELD_U8 != metadata->assistedListeningType )
            {
                sprintf( outputMsg + strlen(outputMsg), "AssistedListeningStream[0x%02X] ", metadata->assistedListeningType);
                dataAvailable = TRUE;
            }

            if ( dataAvailable )
            {
                clxConsoleUIEngineText("    { %s}\n", outputMsg );
            }

            if ( CLX_BAP_NULL_BYTE != metadata->programTitle[0] )
            {
                clxConsoleUIEngineText("programTitle:");
                printBufferHexAndChar ( (const u1*)&metadata->programTitle[1], metadata->programTitle[0] );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->ccIDList[0] )
            {
                clxConsoleUIEngineText("CCIDList:");
                printBufferHexAndChar ( (const u1*)&metadata->ccIDList[1], metadata->ccIDList[0] );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->programInfoURI[0] )
            {
                clxConsoleUIEngineText("ProgramInfoURI:");
                printBufferHexAndChar ( (const u1*)&metadata->programInfoURI[1], metadata->programInfoURI[0] );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->broadcastName[0] )
            {
                clxConsoleUIEngineText("BroadcastName:");
                printBufferHexAndChar ( (const u1*)&metadata->broadcastName[1], metadata->broadcastName[0] );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->extendedMetadataLtv[0] )
            {
                clxConsoleUIEngineText("extendedMetadataLtv:");
                printBufferHexAndChar ( (const u1*)&metadata->extendedMetadataLtv[1], metadata->extendedMetadataLtv[0] );
                dataAvailable = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->vendorMetadataLtv[0] )
            {
                clxConsoleUIEngineText("vendorMetadataLtv:");
                printBufferHexAndChar ( (const u1*)&metadata->vendorMetadataLtv[1], metadata->vendorMetadataLtv[0] );
                dataAvailable = TRUE;
            }

            if ( FALSE == dataAvailable )
            {
                clxConsoleUIEngineText("--No Data--", outputMsg );
            }

            clxConsoleUIEngineText("\n");
        }
        break;

        case ClxBleAudioSpecStructure_BASSControlPoint:
        {
            ClxBapBroadcastScanOpCode* bassLocalCntlPt = (ClxBapBroadcastScanOpCode*)sourceBuffer;

            clxConsoleUIEngineText("\n**** Bass: Broadcast Audio Scan ControlPoint ****\n");

            clxConsoleUIEngineText("\nCurrent ControlPoint OPCode[%d]", bassLocalCntlPt->opcode );

            ClxBapBasAddSource* addSource = &bassLocalCntlPt->procedure.addSource;

            clxConsoleUIEngineText("\n\n\tControlPoint:- Add Source Operation");

            clxConsoleUIEngineText("\n{ Address[Type[%u](0x%02X%02X%02X%02X%02X%02X) AdvID[%u] BroadcastID[0x%X] PASyncState[%u] PAInterval[%u] No.OfSubGrp[%u] }",
                                    addSource->advertiserAddrType,
                                    addSource->advertiserAddr [5],
                                    addSource->advertiserAddr [4],
                                    addSource->advertiserAddr [3],
                                    addSource->advertiserAddr [2],
                                    addSource->advertiserAddr [1],
                                    addSource->advertiserAddr [0],
                                    addSource->advertisingSid,
                                    addSource->broadcastId,
                                    addSource->paSync,
                                    addSource->paInterval,
                                    addSource->numSubgroups);

            for ( int i = 0; 
                  i < addSource->numSubgroups &&\
                  addSource->bisSyncState &&\
                  addSource->metadata;
                  ++i )
            {
                clxConsoleUIEngineText("\n\t SubGrpIndex:#%d { BISSyncState[%u] }",
                                        i,
                                        addSource->bisSyncState[ i ]);

                clxBleAudioPrintDataBasedOnSpecFormat ( &addSource->metadata[ i ], ClxBleAudioSpecStructure_MetaData );
            }

            ClxBapBasModifySource* modifySource = &bassLocalCntlPt->procedure.modifySource;

            clxConsoleUIEngineText("\n\n\tControlPoint:- Modify Source Operation");

            clxConsoleUIEngineText("\n{ SourceID[%u] PASyncState[%u] PAInterval[%u] No.OfSubGrp[%u] }",
                                    modifySource->sourceId,
                                    modifySource->paSync,
                                    modifySource->paInterval,
                                    modifySource->numSubgroups);

            for ( int i = 0; 
                  i < modifySource->numSubgroups &&\
                  modifySource->bisSyncState &&\
                  modifySource->metadata;
                  ++i )
            {
                clxConsoleUIEngineText("\n\t SubGrpIndex:#%d { BISSyncState[%u] }",
                                        i,
                                        modifySource->bisSyncState[ i ]);

                clxBleAudioPrintDataBasedOnSpecFormat ( &modifySource->metadata[ i ], ClxBleAudioSpecStructure_MetaData );
            }

            ClxBapBasSetBroadcastCode* setBroadcastCode = &bassLocalCntlPt->procedure.setBroadcastCode;

            clxConsoleUIEngineText("\n\n\tControlPoint:- Set Broadcast Code Source Operation");

            clxConsoleUIEngineText("\n{ SourceID[%u] }\n\t BroadcastCode", setBroadcastCode->sourceId);

            clxConsoleUIEngineText("\n{ Broadcast Code }" );
            printBufferHexAndChar ( setBroadcastCode->broadcastCode, CLX_BAP_BASS_BROADCAST_CODE_LENGTH );

            ClxBapBasRemoveSource* removeSoure = &bassLocalCntlPt->procedure.removeSource;

            clxConsoleUIEngineText("\n\n\tControlPoint:- Remove Source Operation");

            clxConsoleUIEngineText("\n{ SourceID[%u] }\n", removeSoure->sourceId);
        }
        break;

        case ClxBleAudioSpecStructure_BASSReceiveState:
        {
            ClxBapBroadcastReceiveState* bassLocReceiveState = (ClxBapBroadcastReceiveState*)sourceBuffer;

            clxConsoleUIEngineText("\n**** Bass: Broadcast Receive State ****\n");

            clxConsoleUIEngineText("\n{ SourceID[%u] Address[Type[%u](0x%02X%02X%02X%02X%02X%02X) AdvID[%u] BroadcastID[0x%X] PASyncState[%u] No.OfSubGrp[%u] }",
                                    bassLocReceiveState->sourceId,
                                    bassLocReceiveState->sourceAddrType,
                                    bassLocReceiveState->sourceAddr [5],
                                    bassLocReceiveState->sourceAddr [4],
                                    bassLocReceiveState->sourceAddr [3],
                                    bassLocReceiveState->sourceAddr [2],
                                    bassLocReceiveState->sourceAddr [1],
                                    bassLocReceiveState->sourceAddr [0],
                                    bassLocReceiveState->sourceAdvSid,
                                    bassLocReceiveState->broadcastId,
                                    bassLocReceiveState->paSyncState,
                                    bassLocReceiveState->numSubgroups );

            clxConsoleUIEngineText("\n{ Big Encryption State[%u] }", bassLocReceiveState->bigEncryptionState );
            clxConsoleUIEngineText("\n{ BAD Code }");
            printBufferHexAndChar ( bassLocReceiveState->badCode, CLX_BAP_BASS_BAD_CODE_LENGTH );

            for ( int i = 0; 
                  i < bassLocReceiveState->numSubgroups &&\
                  bassLocReceiveState->bisSyncState &&\
                  bassLocReceiveState->metadata;
                  ++i )
            {
                clxConsoleUIEngineText("\n\t SubGrpIndex:#%d { BISSyncState[%u] }",
                                        i,
                                        bassLocReceiveState->bisSyncState[ i ]);

                clxBleAudioPrintDataBasedOnSpecFormat ( &bassLocReceiveState->metadata[ i ], ClxBleAudioSpecStructure_MetaData );
            }
        }
        break;

        default:
        {
            clxConsoleUIEngineText("\nUnknown Structure\n");
        }
    }
}

/*******************************************************************************************************************************
*                                        clxBleAudioPrintBISBasicAnnouncement
*
* Print the Basic Audio Announcement of BIS
*
* \param basicAnnouncement       Basic Audio Announcement Buffer
*
*******************************************************************************************************************************/
void clxBleAudioPrintBISBasicAnnouncement ( ClxBleAudioBISBasicAudioAnnouncement*   basicAnnouncement )
{
    int loopIndex = 0;

    if ( NULL == basicAnnouncement )
    {
        clxConsoleUIEngineText("\nInvalid BIS Basic Audio Announcement Handle\n");
        return;
    }

    clxConsoleUIEngineText("\nBroadcast Basic Audio Announcement details \nLevel#1 Info");
    clxConsoleUIEngineText("\n    UUID[0x%04X(%s)] NumberOfSubGroup[%d]\n",
                        basicAnnouncement->serviceUUID,
                        ( CLX_GATT_BASIC_AUDIO_ANNOUNCEMENT_UUID == basicAnnouncement->serviceUUID )? "Basic Audio Announcement Service" : "UNKNOWN Service",
                        basicAnnouncement->numberOfSubGrp );

    if ( CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED <  basicAnnouncement->numberOfSubGrp )
    {
        clxConsoleUIEngineText("\nError Supported Max SubGroup count[%d] is smaller than received count[%d]\n",
                              CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED,
                              basicAnnouncement->numberOfSubGrp );
    }

    for ( loopIndex = 0;
          loopIndex < CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED && NULL != basicAnnouncement->subGrp && loopIndex < basicAnnouncement->numberOfSubGrp;
          ++loopIndex )
    {

        clxConsoleUIEngineText("\n=================================\nLevel#2 [Group:#%d] \n", loopIndex + 1);

        ClxBleAudioBISSubGroup* locSubGrp = &basicAnnouncement->subGrp[ loopIndex ];

        clxConsoleUIEngineText("    NumberOfBIS[%d] {CodecFormat[0x%02X(%s)]\n",
                            locSubGrp->numberOfBIS,
                            locSubGrp->codecId.format,
                            getCodecFormat(locSubGrp->codecId.format) );

        clxBleAudioPrintDataBasedOnSpecFormat ( &locSubGrp->codecInfoForSubGrpSpecific, ClxBleAudioSpecStructure_CodecConfig );
        clxBleAudioPrintDataBasedOnSpecFormat ( &locSubGrp->metadata, ClxBleAudioSpecStructure_MetaData );

        for ( u1 bisIndex = 0;
              bisIndex < CLX_GATT_MAX_BIS_SUPPORTED && NULL != locSubGrp->bisSpecificInfo && bisIndex < locSubGrp->numberOfBIS;
              ++bisIndex )
        {
            ClxBleAudioBISSpecificCodecInfo* locBISInfo = &locSubGrp->bisSpecificInfo[ bisIndex ];

            clxConsoleUIEngineText("~~~~~~~~~~~~\nLevel#3 [BIS:#%d]\n", locBISInfo->bisIndex );

            clxBleAudioPrintDataBasedOnSpecFormat ( &locBISInfo->codecInfoForBISSpecific, ClxBleAudioSpecStructure_CodecConfig );
        }

      if ( CLX_GATT_MAX_BIS_SUPPORTED <  locSubGrp->numberOfBIS )
      {
          clxConsoleUIEngineText("\nError Supported Max BIS count[%d] is smaller than received count[%d]\n",
                                CLX_GATT_MAX_BIS_SUPPORTED,
                                locSubGrp->numberOfBIS );
      }

              clxConsoleUIEngineText("\n#################################\n");
    }
}

/*******************************************************************************************************************************
*                                        clxBleAudioCheckDataValidtyBasedOnSpecFormat
*
* Validate the Data Based On Spec mentioned Structure Format like Codec Specific Configuration, Capability, Metadata info's , etc...
*
*\param sourceBuffer       It contains data in the defined spec-based structure. and use the ClxBapConfigType enum to know config type.
*\param sourceBufferType   Structure Format type enum
*
*\return      TRUE  - Data is valid
*             FALSE - Invalid Data
*
*******************************************************************************************************************************/
boolean clxBleAudioCheckDataValidtyBasedOnSpecFormat ( void*                        sourceBuffer,
                                                       ClxBleAudioSpecStructureType dataType )
{
    boolean dataValid = TRUE;

    if ( NULL == sourceBuffer )
    {
        clxConsoleUIEngineText("\nInvalid Source Buffer{Print Failed}\n");
        return FALSE;
    }

    switch ( dataType )
    {
        case ClxBapConfigType_CodecConfig :
        {
            ClxBapCodecConfig* codecConfig = (ClxBapCodecConfig*)sourceBuffer;

            if ( !( ClxBapCodecSamplingFreq_8000Hz <= codecConfig->samplingFrequency &&\
                    ClxBapCodecSamplingFreq_384000Hz >= codecConfig->samplingFrequency ) )
            {
                return FALSE;
            }

            if ( !( 0x00 == codecConfig->frameDuration ||\
                    0x01 == codecConfig->frameDuration ) )
            {
                return FALSE;
            }

            if ( 0xFFFFFFFF < codecConfig->channelAllocation )
            {
                return FALSE;
            }

            if ( 0xFFFF < codecConfig->frameLength )
            {
                return FALSE;
            }

            if ( 0xFF < codecConfig->framesPerSdu )
            {
                return FALSE;
            }

            if ( FALSE == dataValid )
            {
                return FALSE;
            }
        }
        break;

        case ClxBapConfigType_CodecCapability :
        {
            ClxBapCodecCapabilities *codecCabInfo = (ClxBapCodecCapabilities*)sourceBuffer;

            if ( CLX_BAP_NULL_BYTE == codecCabInfo->supportedSamplingFrequencies)
            {
                return FALSE;
            }

            if ( CLX_BAP_NULL_BYTE == codecCabInfo->supportedFrameDurations)
            {
                return FALSE;
            }

            if ( CLX_BAP_NULL_BYTE == codecCabInfo->supportedChannelAllocations )
            {
                return FALSE;
            }

            if ( CLX_BAP_NULL_BYTE == codecCabInfo->supportedFrameLengthRange )
            {
                return FALSE;
            }

            if ( CLX_BAP_NULL_BYTE == codecCabInfo->supportedSduIntervals )
            {
                return FALSE;
            }

            if ( FALSE == dataValid )
            {
                return FALSE;
            }
        }
        break;

        case ClxBapConfigType_MetaData :
        {
            ClxBapAudioMetadataLtv*   metadata = (ClxBapAudioMetadataLtv*)sourceBuffer;

            if ( 0xBFFF < metadata->preferredAudioContexts ||
                 CLX_BAP_NULL_BYTE >= metadata->preferredAudioContexts )
            {
                return FALSE;
            }
            else
            {
                dataValid = TRUE;
            }

            if ( 0xBFFF < metadata->streamingAudioContexts ||
                 CLX_BAP_NULL_BYTE >= metadata->streamingAudioContexts )
            {
                return FALSE;
            }
            else
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->programTitle[0] )
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->languageCode[0] &&\
                 CLX_BAP_NULL_BYTE != metadata->languageCode[1] &&\
                 CLX_BAP_NULL_BYTE != metadata->languageCode[2] )
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->ccIDList[0] )
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_INVALID_FIELD_U8 != metadata->parentalRating )
            {
               dataValid = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->programInfoURI[0] )
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->broadcastName[0] )
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->extendedMetadataLtv[0] )
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_NULL_BYTE != metadata->vendorMetadataLtv[0] )
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_INVALID_FIELD_U8 != metadata->audioActivityState )
            {
                return FALSE;
            }
            else
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_INVALID_FIELD_U8 != metadata->broadcastAudioImmediateFlag )
            {
                dataValid = TRUE;
            }

            if ( CLX_BAP_INVALID_FIELD_U8 != metadata->assistedListeningType )
            {
                dataValid = TRUE;
            }

            if ( FALSE == dataValid )
            {
                return FALSE;
            }
        }
        break;

        default:
        {
            clxConsoleUIEngineText("\nUnknown Structure\n");

            return FALSE;
        }
    }
    return TRUE;
}

/*****************************************************************************************************************************************
*                                        getSamplingFrequencyFromValue
*
* Get the actual Sampling Frequency value from the specification value.
*
* \param[  in   ] value      Spec mentioned Sampling Frequency value.
*
* \return                    Actual Sampling Frequency.
*
******************************************************************************************************************************************/
s4  getSamplingFrequencyFromValue ( u1 value )
{
    switch ( value )
    {
        case ClxBapCodecSamplingFreq_8000Hz:    return 8000;
        case ClxBapCodecSamplingFreq_11025Hz:   return 11025;
        case ClxBapCodecSamplingFreq_16000Hz:   return 16000;
        case ClxBapCodecSamplingFreq_22050Hz:   return 22050;
        case ClxBapCodecSamplingFreq_24000Hz:   return 24000;
        case ClxBapCodecSamplingFreq_32000Hz:   return 32000;
        case ClxBapCodecSamplingFreq_44100Hz:   return 44100;
        case ClxBapCodecSamplingFreq_48000Hz:   return 48000;
        case ClxBapCodecSamplingFreq_88200Hz:   return 88200;
        case ClxBapCodecSamplingFreq_96000Hz:   return 96000;
        case ClxBapCodecSamplingFreq_176400Hz:  return 176400;
        case ClxBapCodecSamplingFreq_192000Hz:  return 192000;
        case ClxBapCodecSamplingFreq_384000Hz:  return 384000;
        default  : return ClxBapCodecSamplingFreq_INVALID;
   }
}

/*****************************************************************************************************************************************
*                                        getCodecFormat
*
* Get the codec format.
*
* \param format      Spec mentioned codec format value.
*
* \return  s1*                  Codec format.
*
******************************************************************************************************************************************/
const s1* getCodecFormat(ClxBluetoothCodingFormat format)
{
    if (format >= ClxBluetoothCodingFormat_uLaw && format <= ClxBluetoothCodingFormat_G_729A)
    {
        return codecFormat[ format ];
    }
    else if ( ClxBluetoothCodingFormat_VendorSpecific == format )
    {
        return "VendorSpecific";
    }
    else
    {
        return "Unknown";
    }
}

/*****************************************************************************************************************************************
*                                        clxBleAudioGetBISBasicAnnouncement
*
* Get the global variable to store the Basic Audio Announcement of BIS
*
* \return              BIS Basic Audio Announcement
*
****************************************************************************************************************************************/
ClxBleAudioBISBasicAudioAnnouncement* clxBleAudioGetBISBasicAnnouncement ( void )
{
    return &bisBasicAnnouncement;
}

/*****************************************************************************************************************************************
*                                        clxBleAudioInitBasicAnnouncementBuffer
*
* Initialize the given Basic Audio Announcement Buffer by allocating the memory and setting the default values.
*
* \param basicAnnouncement       Basic Audio Announcement Buffer
*
* \return ClxResult        If its NULL then decode will failed.
*                          #CLX_SUCCESS: successful decoding
*                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: provided arguments are invalid.
*
****************************************************************************************************************************************/
ClxResult clxBleAudioInitBasicAnnouncementBuffer ( ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    if ( NULL == basicAnnouncement )
    {
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
    }

    basicAnnouncement->serviceUUID = 0;

    if ( CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED < bleAudioConfig->numberOfSubGrp ||\
        CLX_GATT_MAX_BIS_SUPPORTED < bleAudioConfig->numOfBIS )
        {
            clxConsoleUIEngineText( "\nInvalid SubGroup or BIS Count\n" );
            return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        }

    if ( 0 >= bleAudioConfig->numberOfSubGrp )
    {
        bleAudioConfig->numberOfSubGrp = CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED;
    }

    if ( 0 >= bleAudioConfig->numOfBIS )
    {
        bleAudioConfig->numOfBIS = CLX_GATT_MAX_BIS_SUPPORTED;
    }

    memset ( basicAnnouncement, 0x00, sizeof(basicAnnouncement) );

    basicAnnouncement->subGrp = (ClxBleAudioBISSubGroup*)clxAppAllocZero( sizeof(ClxBleAudioBISSubGroup) * CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED );

    if ( NULL != basicAnnouncement->subGrp )
    {
        u1  subGrpIndex = 0;

        ClxBleAudioBISSubGroup* locSubGrp = basicAnnouncement->subGrp;

        clxBapInitStructureByConfigType ( &locSubGrp->codecInfoForSubGrpSpecific, ClxBapConfigType_CodecConfig);
        clxBapInitStructureByConfigType ( &locSubGrp->metadata, ClxBapConfigType_MetaData);

        for ( subGrpIndex = 0; subGrpIndex < bleAudioConfig->numberOfSubGrp; ++subGrpIndex )
        {
            locSubGrp[subGrpIndex].bisSpecificInfo = (ClxBleAudioBISSpecificCodecInfo*)clxAppAllocZero( sizeof(ClxBleAudioBISSpecificCodecInfo) * CLX_GATT_MAX_BIS_SUPPORTED );

            clxBapInitStructureByConfigType ( &locSubGrp[subGrpIndex].bisSpecificInfo->codecInfoForBISSpecific, ClxBapConfigType_CodecConfig);
        }
    }

    bleAudioSetPeriodicSyncHandle ( CLX_BLE_AUDIO_INVALID_HANDLE_VALUE );

        return CLX_SUCCESS;
}

/*****************************************************************************************************************************************
*                                        clxBleAudioDestroyBasicAnnouncementBuffer
*
* Deallocate the memory of the given Basic Audio Announcement Buffer and initialize it with default values.
*
* \param basicAnnouncement       Basic Audio Announcement Buffer
*
* \return ClxResult        If its NULL then decode will failed.
*                          #CLX_SUCCESS: successful decoding
*                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: provided arguments are invalid.
*
****************************************************************************************************************************************/
ClxResult clxBleAudioDestroyBasicAnnouncementBuffer ( ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    if ( NULL == basicAnnouncement )
    {
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
    }

    if ( NULL == basicAnnouncement->subGrp )
    {
        clxConsoleUIEngineText( "\nDestroy BIS Periodic Adv Info {fail-Already is NULL}\n" );
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
    }

    if ( NULL != basicAnnouncement->subGrp )
    {
        u1  subGrpIndex = 0;

        ClxBleAudioBISSubGroup* locSubGrp = basicAnnouncement->subGrp;

        for ( subGrpIndex = 0; subGrpIndex < bleAudioConfig->numberOfSubGrp; ++subGrpIndex )
        {
            clxPoolsetFree( locSubGrp[subGrpIndex].bisSpecificInfo );
        }
    }

    clxPoolsetFree( basicAnnouncement->subGrp );

    basicAnnouncement->subGrp = NULL;

    memset ( basicAnnouncement, 0x00, sizeof(basicAnnouncement) );

    bleResetIsoStreamHandleIntoAudioSendThrdCxt ( );

    bleAudioSetPeriodicSyncHandle ( CLX_BLE_AUDIO_INVALID_HANDLE_VALUE );

    basicAnnouncement->serviceUUID = 0;

    return CLX_SUCCESS;
}

/*******************************************************************************************************************************
*                                        bleAudioStackMessageHandler
*
* This call-back function is registered for the GAP and GATT profiles, 
* any events raised by GAP profile causes this call-back function executed with
* the associated event and parameters
*
* \param stack          - Local device stack handle.
* \param serviceHandle  - Profile/Service handle.
* \param messageID      - Indication id.
* \param params         - Void pointer to the indication parameters.
* \param errorCode      - Error code returned by stack.
*
* \return boolean       - TRUE If the call-back function handles indication or indication with *_COMPLETE.
*                         Otherwise, return FALSE
*
*******************************************************************************************************************************/
boolean bleAudioStackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    /**
    Object to store the remote device and paired device informations
    */
    extern ClxCentralInstanceInfo centralInfo;

    ClxError ret = CLX_ERROR;

    (void) stack;

    /**
    These (below indications with *_COMPLETE) are command complete indications received when the execution of corresponding API commands
    are completed. The command complete indications are received only when the API has been called in non-blocking mode. 
    The output parameters can be accessed from argument "params".
    */
    if (CLX_GAP_BLE_READ_PERIODIC_ADVERTISER_LIST_SIZE_COMPLETE == messageID)
    {
        ClxGapBleReadPeriodicAdvertiserListSizeComplete* arg = (ClxGapBleReadPeriodicAdvertiserListSizeComplete*)params;

        clxConsoleUIEngineText("\nRead periodic advertiser list completed with the result: %s\n", clxGetErrorCodeText(errorCode));

        if (errorCode == CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nPeriodic Advertiser list size : %u\n", (*arg->advertiserListSize));
        }
    }
    else if (CLX_GAP_BLE_ADD_REMOVE_DEVICE_IN_PERIODIC_ADVERTISER_LIST_COMPLETE == messageID)
    {
        clxConsoleUIEngineText("\nAdd or remove periodic advertiser list completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (CLX_GAP_BLE_CLEAR_ALL_DEVICES_FROM_PERIODIC_ADVERTISER_LIST_COMPLETE == messageID)
    {
        clxConsoleUIEngineText("\nClear all devices from advertiser list completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_DEVICE_EXTENDED_ADVERTISING_INDICATION)
    {
        ClxGapBleDeviceExtendedAdvertisingIndication* arg = (ClxGapBleDeviceExtendedAdvertisingIndication*)params;
        ClxBapBroadcastReceiveState *bassLocReceiveState  = ClxBapBroadcastReceiveStateRecord();

        RemoteDeviceInfo* remoteDeviceInfo = centralInfo.remoteDeviceList.findDeviceByAdressAndSID(arg->remoteAddr, arg->advertisingSID);

        u2 audioRole = 0;

        if (!remoteDeviceInfo)
        {
            u1 deviceNameLength = 0;

            const u1* deviceName  = NULL;

            /* Finding Short name */
            deviceName = clxBleFindExtendedAdvDataField ( arg->advertisingData.data, arg->advertisingData.dataLength, CLX_BLE_GAP_AD_TYPE_SHORTED_LOCAL_DEVICE_NAME, &deviceNameLength );

            if ( !deviceName )
            {
                /* Finding Long name */
                deviceName = clxBleFindExtendedAdvDataField ( arg->advertisingData.data, arg->advertisingData.dataLength, CLX_BLE_GAP_AD_TYPE_COMPLETE_LOCAL_DEVICE_NAME, &deviceNameLength );
            }

            if (!deviceName)
            {
                /* Finding Broadcast name */
                deviceName = clxBleFindExtendedAdvDataField ( arg->advertisingData.data, arg->advertisingData.dataLength, CLX_BLE_GAP_AD_TYPE_BROADCAST_NAME, &deviceNameLength );
            }

            /* Filtering to the report display on console */
            if ( clxGetDeviceNameFilteringOption() && \
                 ( !deviceName && ( 0xFF == arg->advertisingSID ) ) )
            {
                return TRUE;
            }

             /* Finding Broadcast Audio Announcement */
            bassLocReceiveState->broadcastId = 0;
            ret = clxBapFindBroadcastAudioAnnouncement ( &bassLocReceiveState->broadcastId,
                                                         (const u1*)arg->advertisingData.data,
                                                         arg->advertisingData.dataLength );

            if ( CLX_SUCCESS == ret )
            {
               clxConsoleUIEngineText("\nBroadcast Audio Announcement {BroadcastID:[%x]}", bassLocReceiveState->broadcastId);
               clxBleBAupdateAdvInfo(bassLocReceiveState->broadcastId, arg->advertisingSID, arg->remoteAddr);
            }

            /* Finding Audio role*/
            clxGapBleFindAudioRole((const u1*)arg->advertisingData.data, (const u1)arg->advertisingData.dataLength, &audioRole);

            remoteDeviceInfo = centralInfo.remoteDeviceList.addDevice ( arg->remoteAddr, deviceName, deviceNameLength, arg->advertisingSID, arg->rssi, audioRole);

            clxConsoleUIEngineText("\nBLE Device Found : %s (Advertising Type = %02x) (Address Type = %02x) (Address = %02X%02X%02X%02X%02X%02X) (RSSI = %d) (AdvertisingSID = %u)",
                                        remoteDeviceInfo != NULL ? ( remoteDeviceInfo->name[0] != '\0' ? (u1*)remoteDeviceInfo->name : (u1*)"-" ) : (u1*)"-",
                                        arg->advertisingType,
                                        arg->remoteAddr.addressType,
                                        arg->remoteAddr.value[0],
                                        arg->remoteAddr.value[1],
                                        arg->remoteAddr.value[2],
                                        arg->remoteAddr.value[3],
                                        arg->remoteAddr.value[4],
                                        arg->remoteAddr.value[5],
                                        (s4)arg->rssi,
                                        arg->advertisingSID );

            if (audioRole)
            {
                if (audioRole & ClxBleAudioRole_CallGateway)
                {
                    clxConsoleUIEngineText("\nCall Gateway (CG)");
                }

                if (audioRole & ClxBleAudioRole_CallTerminal)
                {
                    clxConsoleUIEngineText("\nCall Terminal (CT)");
                }

                if (audioRole & ClxBleAudioRole_UnicastMediaSender)
                {
                    clxConsoleUIEngineText("\nUnicast Media Sender (UMS)");
                }

                if (audioRole & ClxBleAudioRole_UnicastMediaReceiver)
                {
                    clxConsoleUIEngineText("\nUnicast Media Receiver (UMR)");
                }

                if (audioRole & ClxBleAudioRole_BroadcastMediaSender)
                {
                    clxConsoleUIEngineText("\nBroadcast Media Sender (BMS)");
                }

                if (audioRole & ClxBleAudioRole_BroadcastMediaReceiver)
                {
                    clxConsoleUIEngineText("\nBroadcast Media Receiver (BMR)");
                }
            }
        }
    }
    else if (messageID == CLX_GAP_BLE_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_INDICATION)
    {
        ClxGapBlePeriodicAdvertisingSubEventDataRequestIndication* arg = (ClxGapBlePeriodicAdvertisingSubEventDataRequestIndication*) params;

        clxConsoleUIEngineText("\nPerodic Subevent Data Request: (advHandle = %u), (seStart = %u), (seDataCount = %u)\n",
                                                                                    arg->advertisingHandle,
                                                                                    arg->subEventStart,
                                                                                    arg->subEventDataCount);
    }
    else if (messageID == CLX_GAP_BLE_PERIODIC_ADVERTISING_RESPONSE_REPORT_INDICATION)
    {
        ClxGapBlePeriodicAdvertisingResponseReportIndication* arg = (ClxGapBlePeriodicAdvertisingResponseReportIndication*) params;

        clxConsoleUIEngineText("\nPerodic Response Report: (advHandle = %u), (se = %u), (cteType = %u), (responseSlot = %u), (dataStatus = %u), (dataLen = %u)\n",
                                                                                            arg->advertisingHandle,
                                                                                            arg->subEvent,
                                                                                            arg->cteType,
                                                                                            arg->responseSlot,
                                                                                            arg->dataStatus,
                                                                                            arg->dataLength);
    }
    else if (messageID == CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_INDICATION)
    {
        ClxGapBlePeriodicAdvertisingSyncEstablishedIndication* arg = (ClxGapBlePeriodicAdvertisingSyncEstablishedIndication*)params;

        clxConsoleUIEngineText("\nPeriod Sync Established : (Status == %d) (Address Type = %02x) (Address = %02X%02X%02X%02X%02X%02X) (AdvertisingSID = %u) (SyncHandle = %u)\n",
                                                                                                                                    arg->status,
                                                                                                                                    arg->advertiserDetails.advertiserAddress.addressType,
                                                                                                                                    arg->advertiserDetails.advertiserAddress.value[0],
                                                                                                                                    arg->advertiserDetails.advertiserAddress.value[1],
                                                                                                                                    arg->advertiserDetails.advertiserAddress.value[2],
                                                                                                                                    arg->advertiserDetails.advertiserAddress.value[3],
                                                                                                                                    arg->advertiserDetails.advertiserAddress.value[4],
                                                                                                                                    arg->advertiserDetails.advertiserAddress.value[5],
                                                                                                                                    arg->advertiserDetails.advertisingSID,
                                                                                                                                    arg->syncHandle);

        clxConsoleUIEngineText("\n(se = %u), (seInterval = %u), (slotDelay = %u), (slotSpace = %u)\n", arg->noOfSubEvents, arg->subEventInterval, arg->responseSlotDelay, arg->responseSlotSpacing);

        bleAudioSetPeriodicSyncHandle ( arg->syncHandle );

        clxBleBAupdateSyncInfo(arg->periodicAdvertisingInterval);

        /* Added the device into advertiser list for re-synchronization */
        clxGapBleAddRemoveDeviceInPeriodicAdvertiserList(stack, FALSE, &arg->advertiserDetails, TRUE);
    }
    else if ( messageID == CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_LOST_INDICATION)
    {
        ClxGapBlePeriodicAdvertisingSyncLostIndication* arg = (ClxGapBlePeriodicAdvertisingSyncLostIndication*) params;
        clxConsoleUIEngineText("\nPeriodic advertising sync lost: sync handle %d\n", arg->syncHandle);
    }
    else if ( messageID == CLX_GAP_BLE_PERIODIC_ADVERTISING_REPORT_INDICATION )
    {
        ClxBleAudioBISBasicAudioAnnouncement*  locBasicAnnouncement = NULL;

        ClxGapBlePeriodicAdvertisingReportIndication* arg = (ClxGapBlePeriodicAdvertisingReportIndication*)params;

        locBasicAnnouncement = clxBleAudioGetBISBasicAnnouncement();

        if ( 0 == locBasicAnnouncement->serviceUUID )
        {
            ret = clxBapFindBasicAudioAnnouncement ( locBasicAnnouncement,
                                                     CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED,
                                                     CLX_GATT_MAX_BIS_SUPPORTED,
                                                     (const u1*)arg->data,
                                                     arg->dataSize );

            if ( CLX_SUCCESS == ret )
            {
                clxBleAudioPrintBISBasicAnnouncement ( locBasicAnnouncement );
            }
            else if ( CLX_ERROR_BLE_ATT_INSUFFICIENT_RESOURCES == ret )
            {
                clxConsoleUIEngineText("\n#Error: Decode BIS Basic Announcement Data Failed with %s [Need to Increase MAX supported BIS Count or SubGroup Count]\n", clxGetErrorCodeText(ret));
            }
        }
    }
    else if (messageID == CLX_BLE_ISO_CLIENT_BIG_SYNC_LOST_INDICATION)
    {
        ClxBleIsoClientBigSyncLostIndication* arg = (ClxBleIsoClientBigSyncLostIndication*)params;
        ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement = clxBleAudioGetBISBasicAnnouncement();

        clxConsoleUIEngineText("\nBIG Sync Lost : (BIG-ID = %u) (Reason = 0x%X[%s])\n", arg->bigID.value, arg->reason, clxGetErrorCodeText(arg->reason));

        /* For Temporary call the ISO connection terminate from BIG Sync lost handle */
        isoConnectionTerminated( (struct ClxBleIsoInterface*)NULL, 0 );

        ret = clxBleRemoveISODataPath ( getIsoClientHandle(),
                                       ClxBleIsoDataPathDirection_Output,
                                       ClxBleIsoStreamType_BIS,
                                       bisBasicAnnouncement.subGrp ? bisBasicAnnouncement.subGrp[0].numberOfBIS : (u1)1,
                                       CLX_BLE_AUDIO_BIG_ID );

        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText ( "BLE Remove ISO Data Path Fail- %s\n", clxGetErrorCodeText(ret));
        }

        /* Reset the Basic Announcement Buffer */
        clxBleAudioDestroyBasicAnnouncementBuffer ( basicAnnouncement );
        clxBleAudioInitBasicAnnouncementBuffer ( basicAnnouncement );
    }
    /**
    Indication received when the encryption procedure is completed successfully
    */
    else if (CLX_BLE_ISO_CIS_DISCONNECTED_INDICATION == messageID)
    {
        ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

        ClxBleIsoCisDisconnectedIndication* params_ = (ClxBleIsoCisDisconnectedIndication*)params;

        clxConsoleUIEngineText("\nStream type[%d]:Stream ID[%u]:Group ID[%u]:Reason[%s]",
                                                params_->cis.streamType,
                                                params_->cis.streamID,
                                                params_->cis.groupID,
                                                clxGetErrorCodeText(params_->reason));

        bleAudioConfig->cisConnectStatus = FALSE;

        ret = clxBleRemoveISODataPath ( serviceHandle,
                                        ClxBleIsoDataPathDirection_Output,
                                        params_->cis.streamType,
                                        1,
                                        params_->cis.groupID.value );

        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText ( "BLE Remove ISO Data Path Fail- %s\n", clxGetErrorCodeText(ret));
        }

        clxConsoleUIEngineText("\nCIS disconnected command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_SET_EXTENDED_ADVERTISING_PARAMETERS_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_GAP_BLE_SET_EXTENDED_ADVERTISING_PARAMETERS_COMPLETE with result %s", clxGetErrorCodeText(errorCode));

        if (errorCode == CLX_SUCCESS)
        {
            ClxGapBleSetExtendedAdvertisingParametersComplete* params_ = (ClxGapBleSetExtendedAdvertisingParametersComplete*)params;

            clxConsoleUIEngineText("\nAdvertising Handle value : %u", params_->advertisingHandle);
            clxConsoleUIEngineText("\nAdvertising Handle value : %u", params_->selectedTxPower);
        }
    }
    else if (messageID == CLX_GAP_BLE_SET_EXTENDED_ADVERTISING_DATA_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_GAP_BLE_SET_EXTENDED_ADVERTISING_DATA_COMPLETE with result: %s", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_ENABLE_DISABLE_EXTENDED_ADVERTISING_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_GAP_BLE_ENABLE_DISABLE_EXTENDED_ADVERTISING_COMPLETE with result: %s", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_ENABLE_PERIODIC_ADVERTISING_MODE_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_GAP_BLE_ENABLE_PERIODIC_ADVERTISING_MODE_COMPLETE with result: %s", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_DISABLE_PERIODIC_ADVERTISING_MODE_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_GAP_BLE_DISABLE_PERIODIC_ADVERTISING_MODE_COMPLETE with result: %s", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_GET_EXTENDED_ADVERTISING_CAPABILITIES_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_GAP_BLE_GET_EXTENDED_ADVERTISING_CAPABILITIES_COMPLETE with result: %s", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_REMOVE_EXTENDED_ADVERTISING_SET_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_GAP_BLE_REMOVE_EXTENDED_ADVERTISING_SET_COMPLETE with result: %s", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_CLEAR_EXTENDED_ADVERTISING_SETS_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_GAP_BLE_CLEAR_EXTENDED_ADVERTISING_SETS_COMPLETE with result: %s", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_BLE_ISO_SERVER_BIG_FAILED_INDICATION)
    {
        ClxBleIsoServerBigFailedIndication* params_ = (ClxBleIsoServerBigFailedIndication*)params;

        clxConsoleUIEngineText("\nBIG Failed : (BIG-ID = %u) (Reason = 0x%X[%s])\n", params_->bigID.value, params_->reason, clxGetErrorCodeText(params_->reason));
    }
    else if (messageID == CLX_BLE_ISO_SERVER_CIS_ESTABLISHMENT_COMPLETE_INDICATION)
    {
        ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

        ClxBleIsoServerCisEstablishmentCompleteIndication* params_ = (ClxBleIsoServerCisEstablishmentCompleteIndication*)params;

        clxConsoleUIEngineText("\nCIS Established: Stream Type %u, Group Id %u, Stream Id %u Status %s\n",
                                   params_->cisInfo.cis.streamType,
                                   params_->cisInfo.cis.groupID.value,
                                   params_->cisInfo.cis.streamID.value,
                                   clxGetErrorCodeText(params_->cisInfo.result) );

        bleAudioConfig->cisStreamID[0] = params_->cisInfo.cis.streamID.value;

        ret = clxBleSetupISODataPath ( serviceHandle,
                                       ClxBleIsoDataPathDirection_Output,
                                       params_->cisInfo.cis.streamType,
                                       1,
                                       params_->cisInfo.cis.groupID.value,
                                       TRUE );

        bleAudioConfig->cisConnectStatus = TRUE;

        clxConsoleUIEngineText("\nCIS establishment command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_BLE_ISO_SETUP_DATA_PATH_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_BLE_ISO_SETUP_DATA_PATH_COMPLETE status %s\n", clxGetErrorCodeText(errorCode));
    }

    return true;
}

/*****************************************************************************************************************************************
*                                        clxBLECheckAndWriteCharacteristicsInfo
*
* Check the indication values and write the configured characteristics data into server database
*
* \param characteristicHandle           Local device characteristic handle.
* \param characteristicValue            Characteristic data.
* \param characteristicValueLength      Characteristic data length.
*
* \return ClxResult        If its NULL then decode will failed.
*                          #CLX_SUCCESS: successful decoding
*                          #CLX_ERROR_INVALID_HANDLE: One or more of provided arguments are invalid.
*
****************************************************************************************************************************************/
ClxResult clxBLECheckAndWriteCharacteristicsInfo( u2            characteristicHandle,
                                                  const u1*     characteristicValue,
                                                  ClxSize       characteristicValueLength )
{
    /* Need to hanlde as check and write only the ASE Control point */
    ClxResult errCode  = CLX_SUCCESS;

    if ( NULL == characteristicValue   ||\
         NULL == getGattServerHandle() ||\
         0    == characteristicValueLength )
    {
        clxConsoleUIEngineText("clxBLECheckAndWriteCharacteristicsInfo-Error\n");
        return CLX_ERROR_INVALID_HANDLE;
    }

    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    u1 aseIdList[ 10 ] = { };

    /* Check Characteristic Hanlde is AUDIO_STREAM_CONTROL_CHARACTERISTIC or not */
    errCode = clxBLECheckCharacteristicHandleByCharName ( characteristicHandle,
                                                          (s1*)CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT );

    /* If passed handle is AUDIO_STREAM_CONTROL_CHARACTERISTIC then need to decode, write and notify to client */
    if ( CLX_SUCCESS == errCode )
    {
        ClxBapAudioStreamEndpoint aseInfo  = {};
        ClxBapAudioMetadataLtv    metadata = {};

        u1   opCode       = 0,
             aseindex     = 0;
        ClxSize filledLength = 0;

        u1 buffer[256] = { 0 };
        u2 len = 0;

        u1* data = (u1*)characteristicValue;

        ClxBapAseOpCode* aseCntlPoint = clxBleGetAseControlPoint();

        aseInfo.aseOthersStates.metadata = &metadata;
        clxBapInitStructureByConfigType ( aseInfo.aseOthersStates.metadata, ClxBapConfigType_MetaData);

        /* Get the Opcode */
        opCode = data[ 0 ];

        if ( NULL != aseCntlPoint->opCodeInfo )
        {
            clxPoolsetFree(aseCntlPoint->opCodeInfo);
        }

        memset ( aseCntlPoint, 0x00, sizeof(ClxBapAseOpCode) );

        errCode = clxBapDecodeBasicLevelAseOpCodeData ( data, characteristicValueLength, aseCntlPoint, &filledLength );

        if ( CLX_SUCCESS != errCode )
        {
            clxConsoleUIEngineText("\nclx ASE ControlPoint Basic Decode Completed with Err:%s\n", clxGetErrorCodeText(errCode) );
            return errCode;
        }

        if ( aseCntlPoint->numberOfAses )
        {
            aseCntlPoint->opCodeInfo = (ClxAseOpCodeInfo*)clxAppAllocZero(aseCntlPoint->numberOfAses * sizeof(ClxAseOpCodeInfo));

            if ( NULL == aseCntlPoint->opCodeInfo )
            {
                return CLX_FAIL;
            }

            clxBleInitAseOpCodeInfo ( aseCntlPoint );
        }

        clxDecodeOrgBluetoothCharacteristicAseControlPoint ( data,
                                                            characteristicValueLength,
                                                            aseCntlPoint,
                                                            sizeof ( ClxBapAseOpCode ),
                                                            &errCode );

        if ( CLX_SUCCESS != errCode )
        {
            clxConsoleUIEngineText("\nclx ASE ControlPoint Decode Completed with Err:%s\n", clxGetErrorCodeText(errCode) );
            return errCode;
        }

        clxConsoleUIEngineText ( "BLE Audio End Point State Fill: Num.OFASE[%d] OpCode[%d]\n", aseCntlPoint->numberOfAses, opCode );

        if ( 0 >= aseCntlPoint->numberOfAses )
        {
            clxConsoleUIEngineText("\nNum.Of ASE is %d\n", aseCntlPoint->numberOfAses );
            return errCode;
        }

        for ( aseindex = 0;
              aseindex < aseCntlPoint->numberOfAses && aseCntlPoint->opCodeInfo;
              ++aseindex )
        {
            switch( opCode )
            {
                case ClxBapAEStates_Idle:
                {
                    clxConsoleUIEngineText ( "BLE Audio End Point State : IDLE\n" );
                    break;
                }

                case ClxBapAseOpCodeType_ConfigCodecOperation :
                {
                    /* Fill and update the ASE config with additionl parameters of codec config */
                    ClxBapAseClientOpCodeConfigCodec*  aseCntlPtCodec = &aseCntlPoint->opCodeInfo[ aseindex ].configCodec;

                    /* Identifier of the ASE, assigned by the server. */
                    aseInfo.aseId    = aseCntlPtCodec->aseId;

                    /* State of the ASE */
                    aseInfo.aseState = ClxBapAEStates_CodecConfigured;

                    ClxBapAseServerCodecConfig*  codec = &aseInfo.codec;

                    codec->framing                         = BleAudioPduFraming_UnframedIsoalNotSupported;
                    codec->preferredPhy                    = aseCntlPtCodec->targetPhy;
                    codec->preferredRetransmissionNum      = bleAudioConfig->retransmissions;
                    codec->maxTransportLatency             = bleAudioConfig->maxTransportLatency;
                    codec->presentationDelayMin            = bleAudioConfig->presentationDelay;
                    codec->presentationDelayMax            = bleAudioConfig->presentationDelay;
                    codec->preferredPresentationDelayMin   = bleAudioConfig->presentationDelay;
                    codec->preferredPresentationDelayMax   = bleAudioConfig->presentationDelay;

                    /*!< Coding Format values are defined in Bluetooth Assigned Numbers */
                    memcpy ( &codec->codecId, &aseCntlPtCodec->codecId, sizeof(ClxBluetoothCodec) );

                    memcpy ( &aseInfo.codec.aseCodecSpecificConfig, &aseCntlPtCodec->codecSpecificConfig, sizeof(ClxBapCodecConfig) );

                    clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] : CodecConfigured\n", aseInfo.aseId );

                    break;
                }

                case ClxBapAseOpCodeType_ConfigQosOperation:
                {
                    /* Fill and update the ASE config with additionl parameters of QoS config */
                    ClxBapAseClientOpCodeConfigQos*  aseCntlPtQoS = &aseCntlPoint->opCodeInfo[ aseindex ].configQos;

                    /* Identifier of the ASE, assigned by the server. */
                    aseInfo.aseId    = aseCntlPtQoS->aseId;

                    /* State of the ASE */
                    aseInfo.aseState = ClxBapAEStates_QoSConfigured;

                    ClxBapAseServerQosConfiguration*  qosConfig = &aseInfo.qosConfig;

                    aseInfo.aseOthersStates.cigId = aseCntlPtQoS->cigId;
                    aseInfo.aseOthersStates.cisId = aseCntlPtQoS->cisId;

                    qosConfig->cigId                     = aseCntlPtQoS->cigId;
                    qosConfig->cisId                     = aseCntlPtQoS->cisId;
                    qosConfig->sduInterval               = aseCntlPtQoS->sduInterval;
                    qosConfig->framing                   = aseCntlPtQoS->framing;
                    qosConfig->phy                       = aseCntlPtQoS->phy;
                    qosConfig->retransmissionNum         = aseCntlPtQoS->retransmissionNum;

                    qosConfig->presentationDelay         = aseCntlPtQoS->presentationDelay;
                    qosConfig->maxSdu                    = aseCntlPtQoS->maxSdu;
                    qosConfig->maxTransportLatency       = aseCntlPtQoS->maxTransportLatency;

                    clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] : QoSConfigured\n", aseInfo.aseId );

                    break;
                }

                case ClxBapAseOpCodeType_EnableOperation:
                {
                    /* Fill and update the ASE config with additionl parameters of Enbale Operation */
                    ClxBapAseClientOpCodeEnable*  aseCntlPtEnable = &aseCntlPoint->opCodeInfo[ aseindex ].enable;

                    if ( FALSE == clxBleAudioCheckDataValidtyBasedOnSpecFormat ( &aseCntlPtEnable->metadata, ClxBleAudioSpecStructure_MetaData ) )
                    {
                        clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] :Invalid Metadata\n", aseInfo.aseId );
                        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
                    }

                    /* Identifier of the ASE, assigned by the server. */
                    aseInfo.aseId    = aseCntlPtEnable->aseId;

                    /* State of the ASE */
                    aseInfo.aseState = ClxBapAEStates_Enabling;

                    /* Fill and update the ASE config with additionl parameters of QoS config */
                    ClxBapAseClientOpCodeConfigQos*  aseCntlPtQoS = &aseCntlPoint->opCodeInfo[ aseindex ].configQos;

                    aseInfo.aseOthersStates.cigId = aseCntlPtQoS->cigId;
                    aseInfo.aseOthersStates.cisId = aseCntlPtQoS->cisId;

                    if ( aseInfo.aseOthersStates.metadata )
                    {
                        memcpy ( aseInfo.aseOthersStates.metadata, &aseCntlPtEnable->metadata, sizeof(ClxBapAudioMetadataLtv) );

                        clxBleAudioPrintDataBasedOnSpecFormat( &aseCntlPtEnable->metadata, ClxBleAudioSpecStructure_MetaData );
                    }

                    clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] : Enabling\n", aseInfo.aseId );
                    break;
                }

                case ClxBapAseOpCodeType_ReceiverStartReadyOperation:
                {
                    /* Fill and update the ASE config with additionl parameters of Receiver Ready Operation */
                    ClxBapAseClientOpCodeReceiverStartReady*  aseCntlPtReceiverReady = &aseCntlPoint->opCodeInfo[ aseindex ].receiverReady;

                    /* Identifier of the ASE, assigned by the server. */
                    aseInfo.aseId    = aseCntlPtReceiverReady->aseId;

                    /* State of the ASE */
                    aseInfo.aseState = ClxBapAEStates_Streaming;
                    clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] : ReceiverStartReady ->Streaming\n", aseInfo.aseId );
                    break;
                }

                case ClxBapAseOpCodeType_DisableOperation:
                {
                    /* Fill and update the ASE config with additionl parameters of Disabling Operation */
                    ClxBapAseClientOpCodeDisable* aseCtrlPtDisable = &aseCntlPoint->opCodeInfo[ aseindex ].stateDisable;

                    /* Identifier of the ASE, assigned by the server. */
                    aseInfo.aseId    = aseCtrlPtDisable->aseId;

                    /* State of the ASE */
                    if ( ClxBapAEStates_Streaming != aseInfo.aseState )
                    {
                        aseInfo.aseState = ClxBapAEStates_Disabling;
                        clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] : Disabling\n", aseInfo.aseId );
                    }
                    else
                    {
                        aseInfo.aseState = ClxBapAEStates_QoSConfigured;
                        clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] : Disabling->QoSConfigured\n", aseInfo.aseId );
                    }

                    break;
                }

                case ClxBapAseOpCodeType_ReceiverStopReadyOperation:
                {
                    /* Fill and update the ASE config with additionl parameters of Receiver Stop Ready Operation */
                    ClxBapAseClientOpCodeReceiverStopReady*  aseCntlPtReceiverStop = &aseCntlPoint->opCodeInfo[ aseindex ].receiverStop;

                    /* Identifier of the ASE, assigned by the server. */
                    aseInfo.aseId    = aseCntlPtReceiverStop->aseId;

                    /* State of the ASE */
                    aseInfo.aseState = ClxBapAEStates_QoSConfigured;

                    clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] : ReceiverStopReady ->QoSConfigured\n", aseInfo.aseId );
                    break;
                }

                case ClxBapAseOpCodeType_UpdateMetadataOperation:
                {
                    ClxBapAseServerOtherConfig*  aseAddStates = &aseInfo.aseOthersStates;

                    /* Fill and update the ASE config with additionl parameters of Update MetaData Operation */
                    ClxBapAseClientOpCodeUpdateMetadata*  aseCntlPtUpdateMetadata = &aseCntlPoint->opCodeInfo[ aseindex ].updateMetadata;

                    if ( FALSE == clxBleAudioCheckDataValidtyBasedOnSpecFormat ( &aseCntlPtUpdateMetadata->metadata, ClxBleAudioSpecStructure_MetaData ) )
                    {
                        clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] :Invalid Metadata\n", aseInfo.aseId );
                        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
                    }

                    /* Identifier of the ASE, assigned by the server. */
                    aseInfo.aseId    = aseCntlPtUpdateMetadata->aseId;

                    /* Fill and update the ASE config with additionl parameters of QoS config */
                    ClxBapAseClientOpCodeConfigQos*  aseCntlPtQoS = &aseCntlPoint->opCodeInfo[ aseindex ].configQos;

                    aseAddStates->cigId = aseCntlPtQoS->cigId;
                    aseAddStates->cisId = aseCntlPtQoS->cisId;

                    if ( aseAddStates->metadata )
                    {
                        memcpy ( aseAddStates->metadata, &aseCntlPtUpdateMetadata->metadata, sizeof(ClxBapAudioMetadataLtv) );

                        clxBleAudioPrintDataBasedOnSpecFormat( &aseCntlPtUpdateMetadata->metadata, ClxBleAudioSpecStructure_MetaData );
                    }

                    clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] : UpdateMetaData ->Existing state\n", aseInfo.aseId );
                    break;
                }

                case ClxBapAseOpCodeType_ReleaseOperation:
                {
                    /* Fill and update the ASE config with additionl parameters of Release Operation */
                    ClxBapAseClientOpCodeRelease*  aseCntlPtRelease = &aseCntlPoint->opCodeInfo[ aseindex ].releaseOperation;

                    /* Identifier of the ASE, assigned by the server. */
                    aseInfo.aseId    = aseCntlPtRelease->aseId;

                    /* State of the ASE */
                    aseInfo.aseState = ClxBapAEStates_Releasing;

                    clxConsoleUIEngineText ( "BLE Audio End Point State ID[%d] : Releasing\n", aseInfo.aseId );
                    break;
                }

                default:
                {
                    clxConsoleUIEngineText("BLE Audio End Point State : Unknown[%d]{ERROR}\n", opCode );
                    errCode = CLX_ERROR_INVALID_COMMAND_ARGUMENT;
                    break;
                }
            }

            errCode  = clxBleUnicastSetAudioStreamEndPoint( aseInfo.aseId, &aseInfo );
            if ( CLX_SUCCESS != errCode )
            {
                clxConsoleUIEngineText("\nSet Source/Sink ASE Configuration Failed: %s\n", clxGetErrorCodeText(errCode) );
               return errCode;
            }

            aseIdList[ aseindex ] = aseInfo.aseId;
        }

        len = 0;
        buffer[len++] = aseCntlPoint->opcode;           /* op code   */
        buffer[len++] = aseCntlPoint->numberOfAses;     /* No.of ASE */
        for ( int i = 0; i < aseCntlPoint->numberOfAses; ++i )
        {
            buffer[len++] = aseIdList[ i ];
            buffer[len++] = 0x00;                   /* Response code */
            buffer[len++] = 0x00;                   /* Reason code   */
        }

        /* Response to control point */
        errCode = clxGattWriteLocal ( getGattServerHandle(),
                                      characteristicHandle,
                                      buffer,
                                      len,
                                      WRITE_TIMEOUT_VALUE,
                                      TRUE );

        if ( CLX_SUCCESS != errCode )
        {
            clxConsoleUIEngineText("Response to ASE control point Fail:%s\n", clxGetErrorCodeText(errCode) );
           return errCode;
        }

        /* This condition is only for the PTS test case. Set all ASE states to
           'Streaming' after the ASE Control Point procedure */
        if ( ClxBapAseOpCodeType_EnableOperation == aseCntlPoint->opcode &&\
             TRUE == bleAudioConfig->setEnable2StreamingSts )
        {
            for ( int i = 0; i < aseCntlPoint->numberOfAses; ++i )
            {
                /* State of the ASE */
                aseInfo.aseState = ClxBapAEStates_Streaming;
                aseInfo.aseId    = aseIdList[ i ];

                errCode  = clxBleUnicastSetAudioStreamEndPoint( aseInfo.aseId, &aseInfo );
                if ( CLX_SUCCESS != errCode )
                {
                    clxConsoleUIEngineText("\nSet Source/Sink ASE Configuration Failed: %s\n", clxGetErrorCodeText(errCode) );
                   return errCode;
                }
            }
        }

        return errCode;
    }

    /* Check Characteristic Hanlde is BROADCAST_AUDIO_SCAN_CHARACTERISTIC or not */
    errCode = clxBLECheckCharacteristicHandleByCharName ( characteristicHandle,
                                                          (s1*)CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT );

    /* If passed handle is BROADCAST_AUDIO_SCAN_CHARACTERISTIC then need to decode, write and notify to client */
    if ( CLX_SUCCESS == errCode )
    {
        u1   opCode       = 0;
        boolean broadcastRecvSteChange = FALSE;

        ClxSize filledLength = 0;

        ClxBapBroadcastReceiveState* bassLocReceiveState = ClxBapBroadcastReceiveStateRecord();

        clxConsoleUIEngineText("\nBROADCAST_AUDIO_SCAN_CHARACTERISTIC-Data\n");
        printBufferHexAndChar ( characteristicValue, characteristicValueLength );

        u1* data = (u1*)characteristicValue;

        /* Get the Opcode */
        opCode = data[ 0 ];

        ClxBapBroadcastScanOpCode bassLocalCntlPt = {};

        errCode = clxBapDecodeBasicLevelBroadcastScanOpCodeData ( data, characteristicValueLength, &bassLocalCntlPt, &filledLength );

        if ( CLX_SUCCESS != errCode )
        {
            clxConsoleUIEngineText("\nclx BASS ControlPoint Basic Decode Completed with Err:%s\n", clxGetErrorCodeText(errCode) );
            return errCode;
        }

        u1 subGroupCount = 0;
        if ( ClxBapBassOpCode_AddSource == bassLocalCntlPt.opcode )
        {
            ClxBapBasAddSource* addSource = &bassLocalCntlPt.procedure.addSource;

            subGroupCount = addSource->numSubgroups;
        }
        else if ( ClxBapBassOpCode_ModifySource == bassLocalCntlPt.opcode )
        {
            ClxBapBasModifySource* modifySource = &bassLocalCntlPt.procedure.modifySource;

            subGroupCount = modifySource->numSubgroups;
        }

        if ( subGroupCount )
        {
            clxBleInitBassMetadataBuffer( subGroupCount, NULL, &bassLocalCntlPt );

            errCode = clxBapDecodeExtendedLevelBroadcastScanOpCodeData ( data, characteristicValueLength, &bassLocalCntlPt, &filledLength );

            if ( CLX_SUCCESS != errCode )
            {
                clxConsoleUIEngineText("\nclx BASS ControlPoint Decode Completed with Err:%s\n", clxGetErrorCodeText(errCode) );
                return errCode;
            }
        }

        switch(opCode)
        {
            case ClxBapBassOpCode_RemoveScanStopped:
            {
                clxBleBroadcastSenderStopBIG ( clxGetBTStackHandle() );
            }
            break;

            case ClxBapBassOpCode_RemoteScanStarted:
            {
                clxBleBroadcastSenderStartBIG ( clxGetBTStackHandle() );
            }
            break;

            case ClxBapBassOpCode_AddSource:
            {
                ClxBapBasAddSource* addSource = &bassLocalCntlPt.procedure.addSource;

                if ( CLX_SUCCESS != errCode )
                {
                    clxConsoleUIEngineText("\nclx ASE ControlPoint Basic Decode Completed with Err:%s\n", clxGetErrorCodeText(errCode) );
                    break;
                }

                /* Advertiser_Address_Type */
                bassLocReceiveState->sourceAddrType = addSource->advertiserAddrType;

                /* Advertiser_Address */
                memcpy ( bassLocReceiveState->sourceAddr, addSource->advertiserAddr, CLX_BLE_GAP_ADDRESS_VALUE_LENGTH );

                /* Advertising_SID */
                bassLocReceiveState->sourceAdvSid  = addSource->advertisingSid;

                /* Broadcast_ID */
                bassLocReceiveState->broadcastId  = addSource->broadcastId;

                /* PA_Sync */
                bassLocReceiveState->paSyncState  = addSource->paSync;

                clxBleInitBassMetadataBuffer(addSource->numSubgroups, bassLocReceiveState, NULL);

                /* Num_Subgroups */
                bassLocReceiveState->numSubgroups = addSource->numSubgroups;

                for ( int i = 0; 
                      i < addSource->numSubgroups &&\
                      bassLocReceiveState->bisSyncState && addSource->bisSyncState&& \
                      bassLocReceiveState->metadata && addSource->bisSyncState;
                      ++i )
                {
                    /* BIS_Sync[i] */
                    bassLocReceiveState->bisSyncState[ i ]   = addSource->bisSyncState[ i ];

                    memcpy ( &bassLocReceiveState->metadata[ i ], &addSource->metadata[ i ], sizeof(ClxBapAudioMetadataLtv) );
                }

                broadcastRecvSteChange = TRUE;
            }
            break;

            case ClxBapBassOpCode_ModifySource:
            {
                ClxBapBasModifySource* modifySource = &bassLocalCntlPt.procedure.modifySource;

                if ( modifySource->sourceId != bassLocReceiveState->sourceId )
                {
                    clxConsoleUIEngineText ( "BLE BASS: SourceID MissMatch So Modify Source Failed %u ~ %u]\n",
                                        modifySource->sourceId,
                                        bassLocReceiveState->sourceId );

                    modifySource->sourceId = bassLocReceiveState->sourceId;

                    break;
                }

                /* PA_Sync */
                bassLocReceiveState->paSyncState  = modifySource->paSync;

                clxBleInitBassMetadataBuffer(modifySource->numSubgroups, bassLocReceiveState, NULL);

                /* Num_Subgroups */
                bassLocReceiveState->numSubgroups = modifySource->numSubgroups;

                for ( int i = 0; 
                      i < modifySource->numSubgroups &&\
                      bassLocReceiveState->bisSyncState && modifySource->bisSyncState && \
                      bassLocReceiveState->metadata && modifySource->bisSyncState;
                      ++i )
                {
                    /* BIS_Sync[i] */
                    bassLocReceiveState->bisSyncState[ i ]   = modifySource->bisSyncState[ i ];

                    memcpy ( &bassLocReceiveState->metadata[ i ], &modifySource->metadata[ i ], sizeof(ClxBapAudioMetadataLtv) );
                }

                broadcastRecvSteChange = TRUE;
            }
            break;

            case ClxBapBassOpCode_SetBroadcastCode:
            {
                ClxBapBasSetBroadcastCode* setBroadcastCode = &bassLocalCntlPt.procedure.setBroadcastCode;

                if ( setBroadcastCode->sourceId != bassLocReceiveState->sourceId )
                {
                    clxConsoleUIEngineText ( "BLE BASS: SourceID MissMatch So Set BroadcastCode Failed %u ~ %u]\n",
                                        setBroadcastCode->sourceId,
                                        bassLocReceiveState->sourceId );

                    setBroadcastCode->sourceId = bassLocReceiveState->sourceId;

                    break;
                }

                /* Broadcast_Code */
                if ( 0 == memcmp ( bassLocReceiveState->badCode, setBroadcastCode->broadcastCode, CLX_BAP_BASS_BROADCAST_CODE_LENGTH ) )
                {
                    bassLocReceiveState->bigEncryptionState = ClxBapBIGEncryptionCodeStatus_Decrypting;
                }
                else
                {
                    bassLocReceiveState->bigEncryptionState = ClxBapBIGEncryptionCodeStatus_BadCodeIncorrect;
                    memcpy ( bassLocReceiveState->badCode, setBroadcastCode->broadcastCode, CLX_BAP_BASS_BROADCAST_CODE_LENGTH );
                }

                broadcastRecvSteChange = TRUE;
            }
            break;

            case ClxBapBassOpCode_RemoveSource:
            {
                ClxBapBasRemoveSource* removeSoure = &bassLocalCntlPt.procedure.removeSource;

                if ( removeSoure->sourceId != bassLocReceiveState->sourceId )
                {
                    clxConsoleUIEngineText ( "BLE BASS: SourceID MissMatch So Remove Source Failed %u ~ %u]\n",
                                        removeSoure->sourceId,
                                        bassLocReceiveState->sourceId );

                    removeSoure->sourceId = bassLocReceiveState->sourceId;

                    return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
                }

                clxBleBassInfoReset ( );
            }
            break;

            default: 
            {
                clxConsoleUIEngineText("\n{ClxBassopCodeInfo: Unknown} \n");
                break;
            }
        }

        clxConsoleUIEngineText ( "BLE Server Set: BASS Control point\n");
        clxBleAudioPrintDataBasedOnSpecFormat ( (void*)&bassLocalCntlPt, ClxBleAudioSpecStructure_BASSControlPoint );
        clxBleDeinitBassMetadataBuffer( NULL, &bassLocalCntlPt );

        errCode = clxBapSetBroadcastScanOpCode( getGattServerHandle(),
                                                clxBleGetServerLocalValueHandle( GattService_BroadcastAudioScanServiceIndex,
                                                                                   CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_HANDLE_INDEX ),
                                                characteristicValue,
                                                characteristicValueLength,
                                                TRUE);
        if ( CLX_SUCCESS != errCode )
        {
            clxConsoleUIEngineText ( "BLE: Write BASS Broadcast AudioScan Control Point Failed - %s\n", clxGetErrorCodeText(errCode));
            return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
        }

        if ( TRUE == broadcastRecvSteChange )
        {
            errCode = clxBapEncodeBroadcastReceiveState( static_cast<const ClxBapBroadcastReceiveState*>(bassLocReceiveState),
                                                         (u1*)inputValue,
                                                         MAX_INPUT_SIZE,
                                                         &filledLength );

            if ( CLX_SUCCESS != errCode )
            {
                clxConsoleUIEngineText("\nEncode Source PAC: status - %s\n", clxGetErrorCodeText(errCode));
            }

            errCode = clxBapSetBroadcastReceiveState( getGattServerHandle(),
                                                      clxBleGetServerLocalValueHandle( GattService_BroadcastAudioScanServiceIndex,
                                                                                       CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_HANDLE_INDEX),
                                                      (u1*)inputValue,
                                                      filledLength,
                                                      TRUE );

            if ( CLX_SUCCESS != errCode )
            {
                clxConsoleUIEngineText ( "BLE: Encode BASS ReceiveState Failed - %s\n", clxGetErrorCodeText(errCode));
                return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
            }
            else
            {
                clxConsoleUIEngineText ( "BLE: BASS ReceiveState\n");
                clxBleAudioPrintDataBasedOnSpecFormat ( (void*)bassLocReceiveState, ClxBleAudioSpecStructure_BASSReceiveState );
            }

        }
    }

    return errCode;
}

void clxBleBassInfoReset(void)
{
    ClxBapBroadcastReceiveState* receiveStatte  = ClxBapBroadcastReceiveStateRecord();

    clxBleDeinitBassMetadataBuffer(receiveStatte, NULL);

    clxMemSet(receiveStatte, 0x00, sizeof(ClxBapBroadcastReceiveState));
}

void clxBleBassInfoInit( void )
{
    ClxBapBroadcastReceiveState* receiveState  = ClxBapBroadcastReceiveStateRecord();

    receiveState->sourceId            = 01;
    receiveState->sourceAddrType      = ClxBleAddressType_Public;
    clxGetLocalBluetoothDeviceAddress ( receiveState->sourceAddr );
    receiveState->sourceAdvSid        = 1; //CLX_BLE_INVALID_ADVERTISING_SID_VALUE;
    receiveState->broadcastId         = CLX_BLE_AUDIO_BIG_ID;
    receiveState->paSyncState         = ClxBleAudioPlayState_DoNotSync;
    receiveState->bigEncryptionState  = ClxBapBIGEncryptionCodeStatus_NotEncrypted;
    receiveState->numSubgroups        = CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED;

    u1 encryptionCode[CLX_BLE_BIG_BROADCAST_CODE + 1]  = CLX_BLE_AUDIO_BROADCAST_CODE;
    memcpy ( receiveState->badCode, encryptionCode, CLX_BLE_BIG_BROADCAST_CODE );

    clxBleInitBassMetadataBuffer(CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED,receiveState, NULL);

    for ( int i = 0; 
          i < receiveState->numSubgroups &&\
          receiveState->bisSyncState &&\
          receiveState->metadata;
          ++i )
    {
        receiveState->bisSyncState[ i ]        = (0xFFFFFFFF & (~0x01));

        ClxBapAudioMetadataLtv* metadataInfo = &receiveState->metadata[i];

        /* << Set MetaData Configurations >> */
        if ( metadataInfo )
        {
            /* MetaData LTV 1: Streaming Audio Contexts: */
            metadataInfo->streamingAudioContexts = 0x04;

            /* MetaData LTV 2: Language: */
            /* Language LTV structure Value as English("eng") */
            metadataInfo->languageCode[ 0 ] = 'g';
            metadataInfo->languageCode[ 1 ] = 'n';
            metadataInfo->languageCode[ 2 ] = 'e';

            /* MetaData LTV 3: Program_Info: */
            /* Program_Info LTV structure Length */
            metadataInfo->programTitle[ 0 ] = 2;
            /* Program_Info LTV structure Value */
            metadataInfo->programTitle[ 1 ] = 0x04;
            metadataInfo->programTitle[ 2 ] = 0x00;

        }
    }
}

/*****************************************************************************************************************************************
*                                        setAudioCapabilities
*
* Configure the audio capabilities in Source PAC characteristic
*
* \param sourceOrSink  Used to declare Sink PAC or Source PAC { 1 - SINK & 2 - SOURCE }
*
****************************************************************************************************************************************/
void setAudioCapabilities( ClxBleRoleType sourceOrSink )
{
    ClxResult ret = CLX_SUCCESS;

    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    u1  codeCabLocLength  = 0;
    u1  pacIndex          = 0;
    ClxSize filledLength = 0;

    ClxBapPacRecords  pacInfo = {};

    if ( ClxBleRoleType_SOURCE != sourceOrSink && ClxBleRoleType_SINK != sourceOrSink )
    {
        clxConsoleUIEngineText("\nInvalid Role Selected\n");
        return;
    }

    pacInfo.numberOfPacRecords = (u1) bleAudioConfig->numberOfPacRecords;

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
        /* Set Codec Specific Capabilities data */
        ClxBapCodecCapabilities *codecCabInfo = &pacInfo.pacRecords[pacIndex].capabilities;
        ClxBapAudioMetadataLtv *metadataInfo  = &pacInfo.pacRecords[pacIndex].metadata;

        clxBapInitStructureByConfigType ( codecCabInfo, ClxBapConfigType_CodecCapability);
        clxBapInitStructureByConfigType ( metadataInfo, ClxBapConfigType_MetaData);

        codeCabLocLength  = 0;

        /* Codec ID */
        pacInfo.pacRecords[pacIndex].codecId.format            = CLX_BLE_AUDIO_CODEC_FORMAT;

        pacInfo.pacRecords[pacIndex].codecId.companyID         = CLX_BLE_AUDIO_CODEC_COMPANY_ID;
        pacInfo.pacRecords[pacIndex].codecId.vendorSpecificID  = CLX_BLE_AUDIO_CODEC_VENDOR_SPECIFIC_ID;


        /* LTV 1 : Supported_Sampling_Frequencies LTV structure */
        if ( CLX_BAP_NULL_BYTE != bleAudioConfig->capabilitiesInfo.supportedSamplingFrequencies )
        {
           /* Supported_Sampling_Frequencies LTV structure Value */
           codecCabInfo->supportedSamplingFrequencies   = (u2)bleAudioConfig->capabilitiesInfo.supportedSamplingFrequencies;
        }

        /* LTV 2 : Supported_Frame_Durations LTV structure */
        if ( CLX_BAP_NULL_BYTE != bleAudioConfig->capabilitiesInfo.supportedFrameDurations )
        {
           /* Supported_Frame_Durations LTV structure Value */
           codecCabInfo->supportedFrameDurations        = bleAudioConfig->capabilitiesInfo.supportedFrameDurations;
        }

        /* LTV 3 : Supported_Audio_Channel_Counts LTV structure */
        if ( CLX_BAP_NULL_BYTE != bleAudioConfig->capabilitiesInfo.supportedChannelAllocations )
        {
           /* Supported_Audio_Channel_Counts LTV structure Value */
           codecCabInfo->supportedChannelAllocations     = bleAudioConfig->capabilitiesInfo.supportedChannelAllocations;
        }

        /* LTV 4 : Supported_Octets_Per_Codec_Frame LTV structure */
        if ( CLX_BAP_NULL_BYTE != bleAudioConfig->capabilitiesInfo.supportedFrameLengthRange )
        {
           /* Supported_Octets_Per_Codec_Frame LTV structure Value */
           codecCabInfo->supportedFrameLengthRange       = bleAudioConfig->capabilitiesInfo.supportedFrameLengthRange;
        }

        /* LTV 5 : Supported_Max_Codec_Frames_Per_SDU LTV structure */
        if ( CLX_BAP_NULL_BYTE != bleAudioConfig->capabilitiesInfo.supportedSduIntervals )
        {
           /* Supported_Max_Codec_Frames_Per_SDU LTV structure Value */
           codecCabInfo->supportedSduIntervals              = bleAudioConfig->capabilitiesInfo.supportedSduIntervals;
        }

        /* 2 LTV structures for Subgroup[0], defining: as below */
        /* << Set MetaData Configurations >> */
        if ( metadataInfo )
        {
            /* MetaData LTV 1: Streaming Audio Contexts: */
            /* Preferred_Audio_Contexts LTV structure Value as MEDIA */
            metadataInfo->preferredAudioContexts  = 0x04;
        }
    }

    if ( ClxBleRoleType_SOURCE == sourceOrSink )
    {
        ClxBapPacAudioLocations sourceAudioLoc = {};

        ret = clxBapEncodePacRecord( static_cast<const ClxBapPacRecords*>(&pacInfo),
                                     (u1*)inputValue,
                                     MAX_INPUT_SIZE,
                                     &filledLength );

        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nEncode Source PAC: status - %s\n", clxGetErrorCodeText(ret));
        }

        ret = clxBapSetSourcePac( getGattServerHandle(),
                                 clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                                  CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_HANDLE_INDEX ),
                                 (u1*)inputValue,
                                 filledLength,
                                 TRUE );

        clxConsoleUIEngineText("\nSet Source PAC: status - %s\n", clxGetErrorCodeText(ret));

        sourceAudioLoc.pacAudioLocations = 0x00000000;

        ret = clxBapSetSourceAudioLocation ( getGattServerHandle(),
                                             clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_HANDLE_INDEX ),
                                             sourceAudioLoc,
                                             TRUE );
        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nSet Source Audio Location PAC: status FAIL - %s\n", clxGetErrorCodeText(ret));
        }
    }
    else
    {
        ClxBapPacAudioLocations sinkAudioLoc = {};

        ret = clxBapEncodePacRecord( static_cast<const ClxBapPacRecords*>(&pacInfo),
                                     (u1*)inputValue,
                                     MAX_INPUT_SIZE,
                                     &filledLength );

        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nEncode Sink PAC: status - %s\n", clxGetErrorCodeText(ret));
        }

        ret = clxBapSetSinkPac( getGattServerHandle(),
                                clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                                 CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_HANDLE_INDEX ),
                                (u1*)inputValue,
                                filledLength,
                                TRUE );

        clxConsoleUIEngineText("\nSet Sink PAC: status - %s\n", clxGetErrorCodeText(ret));

        sinkAudioLoc.pacAudioLocations= 0x00000000;

        ret = clxBapSetSinkAudioLocation ( getGattServerHandle(),
                                             clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_HANDLE_INDEX ),
                                             sinkAudioLoc,
                                             TRUE );
        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nSet Sink Audio Location PAC: status FAIL - %s\n", clxGetErrorCodeText(ret));
        }
    }

    if ( pacInfo.pacRecords )
    {
        clxPoolsetFree( pacInfo.pacRecords );
    }

    clxConsoleUIEngineText("\nSet Audio Location: status - %s\n", clxGetErrorCodeText(ret));
}

/*****************************************************************************************************************************************
*                                        configureSupportedAudioContext
*
* Set the supported audio context type for Supported_Audio_Contexts characteristic
*
****************************************************************************************************************************************/
void configureSupportedAudioContext( void )
{
    ClxResult ret = CLX_ERROR;

    ClxBapPacSupportedAudioContext supportedAudioContext = {};
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    supportedAudioContext.supportedSinkContext   = bleAudioConfig->supportedAudioContext;
    supportedAudioContext.supportedSourceContext = bleAudioConfig->supportedAudioContext;

    ret = clxBapSetSupportedAudioContext ( getGattServerHandle(),
                                           clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                                            CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_HANDLE_INDEX ),
                                           supportedAudioContext,
                                           TRUE );

    if ( CLX_SUCCESS != ret )
    {
        clxConsoleUIEngineText("\nSet PAC Supported Audio Context: status FAIL - %s\n", clxGetErrorCodeText(ret));
        return;
    }
    else
    {
        clxConsoleUIEngineText("\nSet Supported Audio Context Data Sink[%04X] Source[%04X]\n",
                                    supportedAudioContext.supportedSinkContext,
                                    supportedAudioContext.supportedSourceContext);
    }

}

/*****************************************************************************************************************************************
*                                        configureAvailableAudioContexts
*
* Available audio contexts characteristic defined in PACS to state which of its Supported Audio Context Types can currently be used to establish an audio stream
*
****************************************************************************************************************************************/
void configureAvailableAudioContexts( )
{
    ClxResult ret = CLX_ERROR;
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();
    ClxBapPacAvailableAudioContext availableAudioContext = {};

    availableAudioContext.sinkContentAvailability   = bleAudioConfig->sinkAvailableAudioContext;
    availableAudioContext.sourceContentAvailability = bleAudioConfig->sourceAvailableAudioContext;

    ret = clxBapSetAvailableAudioContext ( getGattServerHandle(),
                                           clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                                            CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_HANDLE_INDEX ),
                                           availableAudioContext,
                                           TRUE);

    if ( CLX_SUCCESS != ret )
    {
        clxConsoleUIEngineText("\nSet PAC Available Audio Context: status FAIL - %s\n", clxGetErrorCodeText(ret));
        return;
    }
    else
    {
        clxConsoleUIEngineText("\nSet Available Audio Context Data Sink[%04X] Source[%04X]\n",
                                    availableAudioContext.sinkContentAvailability,
                                    availableAudioContext.sourceContentAvailability);
    }
}

/*****************************************************************************************************************************************
*                                        configureVoulmeControl
*
* Configure the Volume Control Service characteristic
*
****************************************************************************************************************************************/
void configureVoulmeControl ( void )
{
    ClxResult ret = CLX_ERROR;
    u4 dataSize = 0;

    ClxVolumeState  volumeState = {};
    ClxVolumeFlag   volumeFlag  = {};

    dataSize = sizeof(ClxVolumeState);

    volumeState.volumeSetting = 0xC3;
    volumeState.mute          = 0x00;
    volumeState.changeCounter = 0x00;

    ret = clxGattEncodeLocalCharacteristicValue(getGattServerHandle(),
                                                clxBleGetServerLocalValueHandle( GattService_VolumeControlGattServiceIndex,
                                                                                 CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_HANDLE_INDEX ),
                                                &volumeState,
                                                dataSize,
                                                TRUE);
    clxConsoleUIEngineText("\nConfigure Volume State: status - %s\n", clxGetErrorCodeText(ret));

    volumeFlag.volumeFlags = 0x00;
    dataSize = sizeof(ClxVolumeFlag);

    ret = clxGattEncodeLocalCharacteristicValue(getGattServerHandle(),
                                                clxBleGetServerLocalValueHandle( GattService_VolumeControlGattServiceIndex,
                                                                                 CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_HANDLE_INDEX ),
                                                &volumeFlag,
                                                dataSize,
                                                TRUE);
    clxConsoleUIEngineText("\nConfigure Volume Flag: status - %s\n", clxGetErrorCodeText(ret));

}

/*******************************************************************************************************************************
*                                        printBufferHexAndChar
*
* Print the Data in Hex and Char
*
* \param buffer       Raw buffer data to print in hex format
* \param length       Raw buffer data length in bytes
*
*******************************************************************************************************************************/
void printBufferHexAndChar( const u1* buffer, s4 length )
{
    s4 i, j;

    clxConsoleUIEngineText("\n");

    clxConsoleUIEngineText("   ##              HEX-Value\n"); 

    for (i = 0; i < length; i += 16) 
    {
        /* Print address in hexadecimal */
        clxConsoleUIEngineText("%08zX  ", i); 

        /* Print hex values for this line */
        for (j = i; j < i + 16 && j < length; j++) 
        {
            clxConsoleUIEngineText("%02X ", buffer[j]);

            /* Add extra space after 8 bytes */
            if ((j + 1) % 8 == 0) 
            {
                clxConsoleUIEngineText(" ");
            }
        }

        /* If fewer than 16 bytes, pad with spaces */
        for (; j < i + 16; j++) 
        {
            clxConsoleUIEngineText("   ");

             /* Add extra space after 8 bytes */
            if ((j + 1) % 8 == 0)
            {
                clxConsoleUIEngineText(" ");
            }
        }

        clxConsoleUIEngineText(" ");

        /* Print characters for this line */
        for (j = i; j < i + 16 && j < length; j++) 
        {
            u1 c = '.';

            if ( 32 <= buffer[j] && 126 >= buffer[j] )
            {
                c = buffer[j];
            }

            clxConsoleUIEngineText("%c", c );
        }

        clxConsoleUIEngineText("\n");
    }

    clxConsoleUIEngineText("\n");
}

void bleAudioSetPeriodicSyncHandle ( u2 handle )
{
    periodicSyncHandle = handle;
}

u2 bleAudioGetPeriodicSyncHandle ( void )
{
    return periodicSyncHandle;
}

ClxBLEAudioConfiguration* clxGetBLEAudioConfigurationInfo ( void )
{
    return &bleAudioSetupConfig;
}

ClxResult clxBleSetupISODataPath ( ClxHandle                      handle,
                                   ClxBleIsoDataPathDirection     pathDirection,
                                   ClxBleIsoStreamType            streamType,
                                   u1                             numberOfStream,
                                   u1                             groupID,
                                   boolean                        block )
{
    ClxResult ret = CLX_FAIL;
    ClxBluetoothCodec codec = { };

    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();
    ClxBleIsoStream*          bisOrCisStream = &bleAudioConfig->bisOrCisStream;

    codec.format            = ClxBluetoothCodingFormat_Transparent;
    codec.companyID         = CLX_BLE_AUDIO_CODEC_COMPANY_ID;
    codec.vendorSpecificID  = CLX_BLE_AUDIO_CODEC_VENDOR_SPECIFIC_ID;

    /* For the testing purpose we have config the first index BIS hanlde */
    for (u4 i = 0; i < numberOfStream; i++)
    {
        bisOrCisStream->streamType       = streamType;
        bisOrCisStream->groupID.value    = groupID;

        bisOrCisStream->streamID.value   = (u1)(i + 1);

        ret = clxBleIsoSetupDataPath(
                                handle,
                                *bisOrCisStream,
                                pathDirection,
                                CLX_BLE_AUDIO_DATA_PATH_ID,
                                &codec,
                                100,
                                0,
                                NULL,
                                block );

        clxConsoleUIEngineText("\nSet-up ISO Data Path #%d: status %s\n", i, clxGetErrorCodeText(ret));

        if (ret != CLX_SUCCESS)
        {
            return ret;
        }
    }

    return ret;
}

ClxResult clxBleRemoveISODataPath ( ClxHandle                      handle,
                                   ClxBleIsoDataPathDirection     pathDirection,
                                   ClxBleIsoStreamType            streamType,
                                   u1                             numberOfStream,
                                   u1                             groupID )
{
    ClxResult ret = CLX_FAIL;
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();
    ClxBleIsoStream*          bisOrCisStream = &bleAudioConfig->bisOrCisStream;

    /* For the testing purpose we have config the first index BIS/CIS hanlde */
    for (u4 i = 0; i < numberOfStream;++i)
    {
        bisOrCisStream->streamType       = streamType;
        bisOrCisStream->groupID.value    = groupID;
        bisOrCisStream->streamID.value   = (u1)(i + 1);

        ret = clxBleIsoRemoveDataPath( handle,
                                       *bisOrCisStream,
                                       pathDirection,
                                       TRUE );

        clxConsoleUIEngineText("\nBLE ISO Remove Data Path: status %s\n", clxGetErrorCodeText(ret));

        if (ret != CLX_SUCCESS)
        {
            return ret;
        }
    }

    return ret;
}

u1 aseGetASECountByRole ( ClxBleRoleType role )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    if ( ClxBleRoleType_SINK == role )
    {
        return bleAudioConfig->currentSinkAseCount;
    }
    else if ( ClxBleRoleType_SOURCE == role )
    {
        return bleAudioConfig->currentSourceAseCount;
    }
    else
    {
        clxConsoleUIEngineText("\nGet ASE Count By Role Failed {INVALID ROLE}\n");
        return 0;
    }
}

u1 aseGetASEIDByRole ( ClxBleRoleType role, u1 index )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    if ( ClxBleRoleType_SINK == role )
    {
        if ( bleAudioConfig->currentSinkAseCount > index )
        {
            return bleAudioConfig->sinkAseRecords[index].aseId;
        }
    }
    else if ( ClxBleRoleType_SOURCE == role )
    {
        if ( bleAudioConfig->currentSourceAseCount > index )
        {
            return bleAudioConfig->sourceAseRecords[index].aseId;
        }
    }

    clxConsoleUIEngineText("\nGet ASEID By Role Failed {INVALID ROLE}\n");
    return 0xFF;
}

void bleInitAudioConfigParams ( boolean initOperation )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();
    u1 loop = 0;

    /*
     * Codec Configuration Param
     */
    bleAudioConfig->codecInfo.samplingFrequency = CLX_BLE_AUDIO_CONFIG_SAMPLING_FREQUENCIES;
    bleAudioConfig->codecInfo.frameDuration     = CLX_BLE_AUDIO_CONFIG_FRAME_DURATIONS;
    bleAudioConfig->codecInfo.channelAllocation = CLX_BLE_AUDIO_CONFIG_AUDIO_CHANNEL_ALLOCATION;
    bleAudioConfig->codecInfo.frameLength       = CLX_BLE_AUDIO_CONFIG_OCTETS_PER_CODEC_FRAME;
    bleAudioConfig->codecInfo.framesPerSdu      = CLX_BLE_AUDIO_CONFIG_CODEC_FRAMES_PER_SDU;

    /*
     * Codec Specific Capabilities Params
     */
    bleAudioConfig->capabilitiesInfo.supportedSamplingFrequencies   = CLX_BLE_CAPABILITY_SAMPLING_FREQUENCIES;
    bleAudioConfig->capabilitiesInfo.supportedFrameDurations        = CLX_BLE_CAPABILITY_FRAME_DURATIONS;
    bleAudioConfig->capabilitiesInfo.supportedChannelAllocations    = CLX_BLE_CAPABILITY_AUDIO_CHANNEL_COUNTS;
    bleAudioConfig->capabilitiesInfo.supportedFrameLengthRange      = CLX_BLE_CAPABILITY_OCTETS_PER_CODEC_FRAME;
    bleAudioConfig->capabilitiesInfo.supportedSduIntervals          = CLX_BLE_CAPABILITY_MAX_CODEC_FRAMES_PER_SDU;

    /*
     * BLE Configuration Param
     */
    bleAudioConfig->sduInterval         = CLX_BLE_ISO_SDU_INTERVAL;
    bleAudioConfig->maxSdu              = CLX_BLE_ISO_MAX_SDU_SIZE;
    bleAudioConfig->maxTransportLatency = CLX_BLE_ISO_MAX_TRANSPORT_LATENCY;
    bleAudioConfig->retransmissions     = CLX_BLE_ISO_RETRANSMISSION;
    bleAudioConfig->presentationDelay   = CLX_BLE_ISO_PRESENTATION_DELAY;

    /*
     * Broadcast Based Params
     */
    bleAudioConfig->bigID               = CLX_BLE_AUDIO_BIG_ID;
    bleAudioConfig->numOfBIS            = CLX_GATT_MAX_BIS_SUPPORTED;
    bleAudioConfig->numberOfSubGrp      = CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED;
    bleAudioConfig->bisActiveStatus     = FALSE;

    /*
     * Unicast Based Params
     */
    bleAudioConfig->supportedAudioContext       = 0x0fff;
    bleAudioConfig->sinkAvailableAudioContext   = 0x0fff;
    bleAudioConfig->sourceAvailableAudioContext = 0x0203;
    bleAudioConfig->announcementType            = 0x00; /* General Announcement */
    bleAudioConfig->numberOfPacRecords          = 1;
    bleAudioConfig->numOfCIS                    = 1;
    bleAudioConfig->currentRole                 = ClxBleRoleType_INVALID;
    bleAudioConfig->currentSinkAseCount         = 0;
    bleAudioConfig->currentSourceAseCount       = 0;
    bleAudioConfig->cisConnectStatus            = FALSE;
    bleAudioConfig->setEnable2StreamingSts      = FALSE;
    bleAudioConfig->cisActiveStatus             = FALSE;

    memset ( &bleAudioConfig->cisStreamID     , 0x00, sizeof ( bleAudioConfig->cisStreamID      ) );

    for (loop = 0; loop < CLX_BLE_UNICAST_SUPPORTED_SINK_ASE_COUNT; ++loop)
    {
        ClxBapAseServerOtherConfig* aseSinkConfig   = &bleAudioConfig->sinkAseRecords[loop].aseOthersStates;
        if ( initOperation )
        {
            if ( aseSinkConfig->metadata )
            {
                clxConsoleUIEngineText("\n#Error:ASE Other Config Info is Already allocated");
            }
            else
            {
                memset ( &bleAudioConfig->sinkAseRecords  , 0x00, sizeof ( bleAudioConfig->sinkAseRecords   ) );
                aseSinkConfig->metadata   = (ClxBapAudioMetadataLtv*)clxAppAllocZero(sizeof(ClxBapAudioMetadataLtv));
                if ( aseSinkConfig->metadata )
                {
                    clxBapInitStructureByConfigType ( aseSinkConfig->metadata, ClxBapConfigType_MetaData);
                }
                else
                {
                    clxConsoleUIEngineText("\n#Error:Metadata allocation failed");
                }
            }
        }
        else
        {
            if ( aseSinkConfig->metadata )
            {
                clxPoolsetFree( aseSinkConfig->metadata );
            }
            memset ( &bleAudioConfig->sinkAseRecords  , 0x00, sizeof ( bleAudioConfig->sinkAseRecords   ) );
        }
    }

    for (loop = 0; loop < CLX_BLE_UNICAST_SUPPORTED_SOURCE_ASE_COUNT; ++loop)
    {
        ClxBapAseServerOtherConfig* aseSourceConfig   = &bleAudioConfig->sourceAseRecords[loop].aseOthersStates;
        if ( initOperation )
        {
            if ( aseSourceConfig->metadata )
            {
                clxConsoleUIEngineText("\n#Error:ASE Other Config Info is Already allocated");
            }
            else
            {
                memset ( &bleAudioConfig->sourceAseRecords  , 0x00, sizeof ( bleAudioConfig->sourceAseRecords   ) );
                aseSourceConfig->metadata   = (ClxBapAudioMetadataLtv*)clxAppAllocZero(sizeof(ClxBapAudioMetadataLtv));
                if ( aseSourceConfig->metadata )
                {
                    clxBapInitStructureByConfigType ( aseSourceConfig->metadata, ClxBapConfigType_MetaData);
                }
                else
                {
                    clxConsoleUIEngineText("\n#Error:Metadata allocation failed");
                }
            }
        }
        else
        {
            if ( aseSourceConfig->metadata )
            {
                clxPoolsetFree( aseSourceConfig->metadata );
            }
            memset ( &bleAudioConfig->sourceAseRecords  , 0x00, sizeof ( bleAudioConfig->sourceAseRecords   ) );
        }
    }

}

ClxBapBroadcastReceiveState* ClxBapBroadcastReceiveStateRecord ( void )
{
    return &bassReceiveState;
}

u1 getPreferredAudioCount(void)
{
    return prefAudioCount;
}

void setPreferredAudioCount(u1 audioCount)
{
    if (prefAudioCount != audioCount)
    {
        prefAudioCount = audioCount;
    }
}

u1 getPreferredStreamId(void)
{
    return prefStreamId;
}

void setPreferredStreamId(u1 streamId)
{
    if (prefStreamId != streamId)
    {
        prefStreamId = streamId;
    }
}

u2 getPreferredStreamHandle(void)
{
    return prefStreamHandle;
}

void setPreferredStreamHandle(u2 streamHandle)
{
    if (prefStreamHandle != streamHandle)
    {
        prefStreamHandle = streamHandle;
    }
}

void getAudioChannelMode( void )
{
    if (ClxAppStreamChannelMode_NotSet == streamChannelMode)
    {
        s1 s_str[5];
        u4 channels = 0;

        do
        {
            ClxConsoleUIEngine::inputBox ("\nSelect the number of channels (Mono - 1, Stereo - 2): ", s_str, sizeof(s_str));
            channels = (u4)atoi(s_str);

            if (2 == channels)
            {
                streamChannelMode = ClxAppStreamChannelMode_Stereo;
            }
            else
            {
                streamChannelMode = ClxAppStreamChannelMode_Mono;
            }
        }while((channels != ClxAppStreamChannelMode_Mono) && (channels != ClxAppStreamChannelMode_Stereo));
    }
}

void resetAudioChannelMode( void )
{
    streamChannelMode = ClxAppStreamChannelMode_NotSet;
}

s4 getBitrate( void )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();
    s4 bitRate = 48000;

    if (ClxBleIsoStreamType_BIS == bleAudioConfig->bisOrCisStream.streamType)
    {
#if defined(CLX_FLOATINGPOINT_LC3)
        /* Set the bitrate defaulted to 80 kbps for a mono channel mode */
        bitRate = 80000;

        if (ClxAppStreamChannelMode_Stereo == streamChannelMode)
        {
            bitRate = 160000;
        }
#endif /* CLX_FLOATINGPOINT_LC3 */
    }

    clxConsoleUIEngineText("\nConfigured Bitrate is %u bps\n", bitRate);

    return bitRate;
}

s2 getNumberOfChannels( void )
{
#if defined(CLX_FLOATINGPOINT_LC3)
    if (ClxAppStreamChannelMode_Stereo == streamChannelMode)
    {
        return 2;
    }
#endif  /* CLX_FLOATINGPOINT_LC3 */

    return 1;
}

ClxBapAseOpCode* clxBleGetAseControlPoint( void )
{
    return &aseCntlPt;
}

void clxBleBapAscsProfileMenu ( ClxStack stack, ClxBleGattRoleType gattRole )
{
    ClxResult ret = CLX_FAIL;

    if ( NULL == stack )
    {
        clxConsoleUIEngineText("\nClarinox Stack has to be initialized first\n");
        return;
    }

    if ( ClxBleGattRoleType_CLIENT != gattRole &&\
         ClxBleGattRoleType_SERVER != gattRole )
    {
        clxConsoleUIEngineText("\nInvalid Gatt Role\n");
        return;
    }

    while ( TRUE )
    {
        const s1* menu =    "Get Sink ASE\0"
                            "Set Sink ASE\0"
                            "Get Source ASE\0"
                            "Set Source ASE\0"
                            "Get ASE OP Code\0"
                            "Set ASE OP Code\0"
                            "Return to previous menu\0";

        BleBapAscsProfileItem index = (BleBapAscsProfileItem)clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, BleBapAscs_TotalItem - 1);

        switch ( index )
        {
            case BleBapAscs_GetSinkASE:
            {
                u4 valueReadLength = 0;
                ClxHandle gatt   = NULL;
                u2        handle = 0;

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_AudioStreamControlIndex,
                                                              CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_HANDLE_INDEX );
                }

                ret = clxBapGetSinkAse ( gatt,
                                         handle,
                                         (u1*)inputValue,
                                         MAX_INPUT_SIZE,
                                         &valueReadLength,
                                         TRUE );

                if ( CLX_SUCCESS == ret && valueReadLength )
                {
                    clxConsoleUIEngineText("\nSink ASE Data\n");
                    printBufferHexAndChar((u1*)inputValue, valueReadLength);
                }
                else
                {
                    clxConsoleUIEngineText("\nGet Sink ASE %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapAscs_SetSinkASE:
            {
                ClxSize filledLength = 0;
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapAudioStreamEndpoint aseInfoLoc = {};
                ClxBapAudioMetadataLtv    metadata   = {};

                aseInfoLoc.aseOthersStates.metadata = &metadata;
                clxBapInitStructureByConfigType ( aseInfoLoc.aseOthersStates.metadata, ClxBapConfigType_MetaData);

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_AudioStreamControlIndex,
                                                              CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_HANDLE_INDEX );
                }

                u4 option = 0;
                u1 loop   = 0;
                u1 aseID  = 1;

                clxConsoleUIEngineInputBox ("Enter {0: Idle, 1: Codec configure, 2: Qos configure, 3: Enable, 4: Streaming, 5: Disable }\n", inputValue, MAX_INPUT_SIZE );
                option = (ClxBapAudioEndpointStates) atoi(inputValue);

                for (loop = 0; loop < CLX_BLE_UNICAST_SUPPORTED_ASE_COUNT; loop++)
                {
                    /* For Temporary: set the ASEId as 1,2,3... (Sink ASE Id's are odd and Source ASE Id's are even numbers) */
                    aseInfoLoc.aseId    = aseID;
                    clxBleUnicastFillASEInfo( (u1) option, &aseInfoLoc );

                    ret = clxBapEncodeSinkAse ( static_cast<const ClxBapAudioStreamEndpoint*>(&aseInfoLoc),
                                                  (u1*)inputValue,
                                                  MAX_INPUT_SIZE,
                                                  &filledLength );

                    if ( CLX_SUCCESS != ret || !filledLength )
                    {
                        clxConsoleUIEngineText("\nEncode Sink ASE: status - %s\n", clxGetErrorCodeText(ret));
                    }

                    clxConsoleUIEngineText("\nSet Sink ASE Data\n");
                    printBufferHexAndChar((u1*)inputValue, filledLength);

                    ret = clxBapSetSinkAse ( gatt,
                                             handle,
                                             (u1*)inputValue,
                                             filledLength,
                                             TRUE );

                    if ( CLX_SUCCESS == ret && filledLength )
                    {
                        clxConsoleUIEngineText("\nSet Sink ASE Done\n");
                    }
                    else
                    {
                        clxConsoleUIEngineText("\nSet Sink ASE %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                    }
                    aseID += 2;
                }
            }
            break;

            case BleBapAscs_GetSourceASE:
            {
                u4 valueReadLength = 0;
                ClxHandle gatt   = NULL;
                u2        handle = 0;

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_AudioStreamControlIndex,
                                                              CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_HANDLE_INDEX );
                }

                ret = clxBapGetSourceAse ( gatt,
                                         handle,
                                         (u1*)inputValue,
                                         MAX_INPUT_SIZE,
                                         &valueReadLength,
                                         TRUE );

                if ( CLX_SUCCESS == ret && valueReadLength )
                {
                    clxConsoleUIEngineText("\nSource ASE Data\n");
                    printBufferHexAndChar((u1*)inputValue, valueReadLength);
                }
                else
                {
                    clxConsoleUIEngineText("\nGet Source ASE %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapAscs_SetSourceASE:
            {
                ClxSize filledLength = 0;
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapAudioStreamEndpoint aseInfoLoc = {};
                ClxBapAudioMetadataLtv    metadata   = {};

                aseInfoLoc.aseOthersStates.metadata = &metadata;
                clxBapInitStructureByConfigType ( aseInfoLoc.aseOthersStates.metadata, ClxBapConfigType_MetaData);

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_AudioStreamControlIndex,
                                                              CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_HANDLE_INDEX );
                }

                u4 option = 0;
                u1 loop   = 0;
                u1 aseID  = 2;

                clxConsoleUIEngineInputBox ("Enter {0: Idle, 1: Codec configure, 2: Qos configure, 3: Enable, 4: Streaming, 5: Disable }\n", inputValue, MAX_INPUT_SIZE );
                option = (ClxBapAudioEndpointStates) atoi(inputValue);

                for (loop = 0; loop < CLX_BLE_UNICAST_SUPPORTED_ASE_COUNT; loop++)
                

{
                    /* For Temporary: set the ASEId as 1,2,3... (Sink ASE Id's are odd and Source ASE Id's are even numbers) */
                    aseInfoLoc.aseId    = aseID;
                    clxBleUnicastFillASEInfo( (u1) option, &aseInfoLoc );

                    ret = clxBapEncodeSourceAse ( static_cast<const ClxBapAudioStreamEndpoint*>(&aseInfoLoc),
                                                  (u1*)inputValue,
                                                  MAX_INPUT_SIZE,
                                                  &filledLength );

                    if ( CLX_SUCCESS != ret || !filledLength )
                    {
                        clxConsoleUIEngineText("\nEncode Source ASE: status - %s\n", clxGetErrorCodeText(ret));
                    }

                    clxConsoleUIEngineText("\nSet Source ASE Data\n");
                    printBufferHexAndChar((u1*)inputValue, filledLength);

                    ret = clxBapSetSourceAse ( gatt,
                                             handle,
                                             (u1*)inputValue,
                                             filledLength,
                                             TRUE );

                    if ( CLX_SUCCESS == ret && filledLength )
                    {
                        clxConsoleUIEngineText("\nSet Source ASE Done\n");
                    }
                    else
                    {
                        clxConsoleUIEngineText("\nSet Source ASE %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                    }
                    aseID += 2;
                }
            }
            break;

            case BleBapAscs_GetASEOpCode:
            {
                u4 valueReadLength = 0;
                ClxHandle gatt   = NULL;
                u2        handle = 0;

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_AudioStreamControlIndex,
                                                              CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_HANDLE_INDEX);
                }

                ret = clxBapGetAseOpCode( gatt,
                                          handle,
                                          (u1*)inputValue,
                                          MAX_INPUT_SIZE,
                                          &valueReadLength,
                                          TRUE );

                if ( CLX_SUCCESS == ret && valueReadLength )
                {
                    clxConsoleUIEngineText("\nASE OP Code Data\n");
                    printBufferHexAndChar((u1*)inputValue, valueReadLength);
                }
                else
                {
                    clxConsoleUIEngineText("\nGet ASE OP Code %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapAscs_SetASEOpCode:
            {
                ClxSize filledLength = 0;
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapAseOpCode aseOpCodeInfo = {};

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_AudioStreamControlIndex,
                                                              CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_HANDLE_INDEX );
                }

                ret = clxBapEncodeAseOpCodeData( static_cast<const ClxBapAseOpCode*>(&aseOpCodeInfo),
                                                 (u1*)inputValue,
                                                 MAX_INPUT_SIZE,
                                                 &filledLength );

                if ( CLX_SUCCESS != ret || !filledLength )
                {
                    clxConsoleUIEngineText("\nEncode ASE OP Code: status - %s\n", clxGetErrorCodeText(ret));
                }

                clxConsoleUIEngineText("\nSet ASE OP Code Data\n");
                printBufferHexAndChar((u1*)inputValue, filledLength);

                ret = clxBapSetAseOpCode( gatt,
                                          handle,
                                          (u1*)inputValue,
                                          filledLength,
                                          TRUE );

                if ( CLX_SUCCESS == ret && filledLength )
                {
                    clxConsoleUIEngineText("\nSet ASE OP Code Done\n");
                }
                else
                {
                    clxConsoleUIEngineText("\nSet ASE OP Code %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapAscs_ReturnToPreviousMenu:
            {
                return;
            }

            default:
            {
                clxConsoleUIEngineText("\nPlease select a valid menu option..\n");
            }
            break;

        } /* switch ( index ) */

    } /* while ( TRUE ) */
}

void clxBleBapPacsProfileMenu ( ClxStack stack, ClxBleGattRoleType gattRole )
{
    ClxResult ret = CLX_FAIL;

    if ( NULL == stack )
    {
        clxConsoleUIEngineText("\nClarinox Stack has to be initialized first\n");
        return;
    }

    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    if ( ClxBleGattRoleType_CLIENT != gattRole &&\
         ClxBleGattRoleType_SERVER != gattRole )
    {
        clxConsoleUIEngineText("\nInvalid Gatt Role\n");
        return;
    }

    while ( TRUE )
    {
        const s1* menu =    "Get Sink PAC\0"
                            "Set Sink PAC\0"
                            "Get Sink Audio Location\0"
                            "Set Sink Audio Location\0"
                            "Get Source PAC\0"
                            "Set Source PAC\0"
                            "Get Source Audio Location\0"
                            "Set Source Audio Location\0"
                            "Get Available Audio Context\0"
                            "Set Available Audio Context\0"
                            "Get Supported Audio Context\0"
                            "Set Supported Audio Context\0"
                            "Return to previous menu\0";

        BleBapPacsProfileItem index = (BleBapPacsProfileItem)clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, BleBapPacs_TotalItem - 1);

        switch ( index )
        {
            case BleBapPacs_GetSinkPAC:
            {
                u4 valueReadLength = 0;
                ClxHandle gatt   = NULL;
                u2        handle = 0;

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_HANDLE_INDEX);
                }

                ret = clxBapGetSinkPac( gatt,
                                        handle,
                                        (u1*)inputValue,
                                        MAX_INPUT_SIZE,
                                        &valueReadLength,
                                        TRUE );

                if ( CLX_SUCCESS == ret && valueReadLength )
                {
                    clxConsoleUIEngineText("\nSink PAC Data\n");
                    printBufferHexAndChar((u1*)inputValue, valueReadLength);
                }
                else
                {
                    clxConsoleUIEngineText("\nGet Sink PAC %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole ? "Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_SetSinkPAC:
            {
                setAudioCapabilities ( ClxBleRoleType_SINK );
                clxConsoleUIEngineText("\nSet Sink PAC %s\n", ClxBleGattRoleType_CLIENT == gattRole ? "Sender":"Receiver");
            }
            break;

            case BleBapPacs_GetSinkAudioLocation:
            {
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapPacAudioLocations sinkAudioLocation = {};

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_HANDLE_INDEX );
                }

                ret = clxBapGetSinkAudioLocation( gatt,
                                                  handle,
                                                  &sinkAudioLocation,
                                                  TRUE );

                if ( CLX_SUCCESS == ret )
                {
                    clxConsoleUIEngineText("\nSink Audio Location Data [%08X]\n",
                                                sinkAudioLocation.pacAudioLocations);
                }
                else
                {
                    clxConsoleUIEngineText("\nGet Sink Audio Location %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_SetSinkAudioLocation:
            {
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapPacAudioLocations sinkAudioLocation = {};

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_UUID);
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_HANDLE_INDEX );
                }

                sinkAudioLocation.pacAudioLocations = 0x00000001;

                clxConsoleUIEngineText("\nSet Sink Audio Location Data [%08X]\n",
                                                sinkAudioLocation.pacAudioLocations);

                ret = clxBapSetSinkAudioLocation( gatt,
                                                  handle,
                                                  sinkAudioLocation,
                                                  TRUE );

                if ( CLX_SUCCESS == ret )
                {
                    clxConsoleUIEngineText("\nSet Sink Audio Location Done\n");
                }
                else
                {
                    clxConsoleUIEngineText("\nSet Sink Audio Location %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_GetSourcePAC:
            {
                u4 valueReadLength = 0;
                ClxHandle gatt   = NULL;
                u2        handle = 0;

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_SOURCE_PAC_UUID);
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_HANDLE_INDEX);
                }

                ret = clxBapGetSourcePac( gatt,
                                        handle,
                                        (u1*)inputValue,
                                        MAX_INPUT_SIZE,
                                        &valueReadLength,
                                        TRUE );

                if ( CLX_SUCCESS == ret && valueReadLength )
                {
                    clxConsoleUIEngineText("\nSource PAC Data\n");
                    printBufferHexAndChar((u1*)inputValue, valueReadLength);
                }
                else
                {
                    clxConsoleUIEngineText("\nGet Source PAC %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_SetSourcePAC:
            {
                setAudioCapabilities ( ClxBleRoleType_SOURCE );
                clxConsoleUIEngineText("\nSet Source PAC %s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver" );
            }
            break;

            case BleBapPacs_GetSourceAudioLocation:
            {
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapPacAudioLocations sourceAudioLocation = {};

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_HANDLE_INDEX);
                }

                ret = clxBapGetSourceAudioLocation( gatt,
                                                    handle,
                                                    &sourceAudioLocation,
                                                    TRUE );

                if ( CLX_SUCCESS == ret )
                {
                    clxConsoleUIEngineText("\nSource Audio Location Data [%08X]\n",
                                                sourceAudioLocation.pacAudioLocations);
                }
                else
                {
                    clxConsoleUIEngineText("\nGet Source Audio Location %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_SetSourceAudioLocation:
            {
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapPacAudioLocations sourceAudioLocation = {};

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_HANDLE_INDEX );
                }

                sourceAudioLocation.pacAudioLocations = 0x00000001;

                clxConsoleUIEngineText("\nSet Source Audio Location Data [%08X]\n",
                                                sourceAudioLocation.pacAudioLocations);

                ret = clxBapSetSourceAudioLocation( gatt,
                                                    handle,
                                                    sourceAudioLocation,
                                                    TRUE );

                if ( CLX_SUCCESS == ret )
                {
                    clxConsoleUIEngineText("\nSet Source Audio Location Done\n");
                }
                else
                {
                    clxConsoleUIEngineText("\nSet Source Audio Location %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_GetAvailableAudioContext:
            {
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapPacAvailableAudioContext availableAudioContext = {};

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_HANDLE_INDEX);
                }

                ret = clxBapGetAvailableAudioContext( gatt,
                                                    handle,
                                                    &availableAudioContext,
                                                    TRUE );

                if ( CLX_SUCCESS == ret )
                {
                    clxConsoleUIEngineText("\nAvailable Audio Context Data Sink[%04X] Source[%04X]\n",
                                                availableAudioContext.sinkContentAvailability,
                                                availableAudioContext.sourceContentAvailability );
                }
                else
                {
                    clxConsoleUIEngineText("\nGet Available Audio Context %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_SetAvailableAudioContext:
            {
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapPacAvailableAudioContext availableAudioContext = {};

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_HANDLE_INDEX );
                }

                availableAudioContext.sourceContentAvailability = bleAudioConfig->sourceAvailableAudioContext;

                availableAudioContext.sinkContentAvailability   = bleAudioConfig->sinkAvailableAudioContext;

                clxConsoleUIEngineText("\nSet Available Audio Context Data Sink[%04X] Source[%04X]\n",
                                            availableAudioContext.sinkContentAvailability,
                                            availableAudioContext.sourceContentAvailability);

                ret = clxBapSetAvailableAudioContext( gatt,
                                                      handle,
                                                      availableAudioContext,
                                                      TRUE );

                if ( CLX_SUCCESS == ret )
                {
                    clxConsoleUIEngineText("\nSet Available Audio Context Done\n");
                }
                else
                {
                    clxConsoleUIEngineText("\nSet Available Audio Context %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_GetSupportedAudioContext:
            {
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapPacSupportedAudioContext supportedAudioContext = {};

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_HANDLE_INDEX);
                }

                ret = clxBapGetSupportedAudioContext( gatt,
                                                      handle,
                                                      &supportedAudioContext,
                                                      TRUE );

                if ( CLX_SUCCESS == ret )
                {
                    clxConsoleUIEngineText("\nSupported Audio Context Data Sink[%04X] Source[%04X]\n",
                                                supportedAudioContext.supportedSinkContext,
                                                supportedAudioContext.supportedSourceContext);
                }
                else
                {
                    clxConsoleUIEngineText("\nGet Supported Audio Context %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_SetSupportedAudioContext:
            {
                ClxHandle gatt   = NULL;
                u2        handle = 0;
                ClxBapPacSupportedAudioContext supportedAudioContext = {};

                if ( ClxBleGattRoleType_CLIENT == gattRole )
                {
                    gatt = getGattClientHandle();
                    handle = GetValueHandle ( getGattClientHandle(),
                                              CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID,
                                              CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_UUID );
                }
                else
                {
                    gatt   = getGattServerHandle();
                    handle = clxBleGetServerLocalValueHandle( GattService_PublishedAudioCapabilitiesIndex,
                                                              CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_HANDLE_INDEX );
                }

                supportedAudioContext.supportedSourceContext = bleAudioConfig->supportedAudioContext;

                supportedAudioContext.supportedSinkContext   = bleAudioConfig->supportedAudioContext;

                clxConsoleUIEngineText("\nSet Supported Audio Context Data Sink[%04X] Source[%04X]\n",
                                            supportedAudioContext.supportedSinkContext,
                                            supportedAudioContext.supportedSourceContext);

                ret = clxBapSetSupportedAudioContext( gatt,
                                                      handle,
                                                      supportedAudioContext,
                                                      TRUE );

                if ( CLX_SUCCESS == ret )
                {
                    clxConsoleUIEngineText("\nSet Supported Audio Context Done\n");
                }
                else
                {
                    clxConsoleUIEngineText("\nSet Supported Audio Context %s-Fail:%s\n", ClxBleGattRoleType_CLIENT == gattRole?"Sender":"Receiver", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBapPacs_ReturnToPreviousMenu:
            {
                return;
            }

            default:
            {
                clxConsoleUIEngineText("\nPlease select a valid menu option..\n");
            }
            break;

        } /* switch ( index ) */

    } /* while ( TRUE ) */
}

void clxBleBapProfileMenu ( ClxStack stack, ClxBleGattRoleType gattRole )
{
    if ( NULL == stack )
    {
        clxConsoleUIEngineText("\nClarinox Stack has to be initialized first\n");
        return;
    }

    if ( ClxBleGattRoleType_CLIENT != gattRole &&\
         ClxBleGattRoleType_SERVER != gattRole )
    {
        clxConsoleUIEngineText("\nInvalid Gatt Role\n");
        return;
    }

    while ( TRUE )
    {
        const s1* menu =    "ASCS Profile\0"
                            "PACS Profile\0"
                            "BASS Profile\0"
                            "Return to previous menu\0";

        BleBapProfileItem index = (BleBapProfileItem)clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, BleBapProfile_TotalItem - 1);

        switch ( index )
        {
            case BleBapProfile_ASCS:
            {
                clxBleBapAscsProfileMenu ( stack, gattRole );
                break;
            }

            case BleBapProfile_PACS:
            {
                clxBleBapPacsProfileMenu ( stack, gattRole );
                break;
            }

            case BleBapProfile_BASS:
            {
                //clxBleBapBassProfileMenu ( stack, gattRole );
                clxConsoleUIEngineText("\nBleBapBassProfileMenu; TODO\n");
            }
            break;

            case BleBapProfile_ReturnToPreviousMenu:
            {
                return;
            }

            default:
            {
                clxConsoleUIEngineText("\nPlease select a valid menu option..\n");
            }
            break;

        } /* switch ( index ) */

    } /* while ( TRUE ) */
}

ClxBapAudioStreamEndpoint* clxBleAppGetSinkAseRecord ( u1 aseIndex )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    if ( aseIndex < CLX_BLE_UNICAST_SUPPORTED_SINK_ASE_COUNT )
    {
        return &bleAudioConfig->sinkAseRecords[ aseIndex ];
    }
    else
    {
        return NULL;
    }
}

ClxBapAudioStreamEndpoint* clxBleAppGetSourceAseRecord ( u1 aseIndex )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    if ( aseIndex < CLX_BLE_UNICAST_SUPPORTED_SOURCE_ASE_COUNT )
    {
        return &bleAudioConfig->sourceAseRecords[ aseIndex ];
    }
    else
    {
        return NULL;
    }
}

void clxBleInitAudioParams ( void )
{
    bleInitAudioConfigParams( TRUE );
    clxBleBassInfoInit();
#if FIX_TIMER
    clxBleBAcreateConnectionMonitoringTimer();
#endif
}

void clxBleTerminateAudioParams ( void )
{
    bleInitAudioConfigParams( FALSE );
    clxBleBassInfoReset();
#if FIX_TIMER
    clxBleBAdestroyConnectionMonitoringTimer();
#endif
}

void clxBleInitAseOpCodeInfo ( ClxBapAseOpCode* aseCntlPoint )
{
    u1 aseindex = 0;

    if ( NULL == aseCntlPoint )
    {
        return;
    }

    for ( aseindex = 0;
          aseindex < aseCntlPoint->numberOfAses && aseCntlPoint->opCodeInfo;
          ++aseindex )
    {
        clxBapInitStructureByConfigType ( &aseCntlPoint->opCodeInfo[aseindex].configCodec.codecSpecificConfig, ClxBapConfigType_CodecConfig);
        clxBapInitStructureByConfigType ( &aseCntlPoint->opCodeInfo[aseindex].updateMetadata.metadata, ClxBapConfigType_MetaData);
        clxBapInitStructureByConfigType ( &aseCntlPoint->opCodeInfo[aseindex].enable.metadata, ClxBapConfigType_MetaData);
    }
}

void clxBapInitializeMetadata(u1 subGroupCount, u1* numSubgroups, u4** bisSyncState, ClxBapAudioMetadataLtv** metadata)
{
    if (*numSubgroups != subGroupCount)
    {
        *numSubgroups = subGroupCount;
        clxPoolsetFree(*bisSyncState);
        clxPoolsetFree(*metadata);
        *bisSyncState = NULL;
        *metadata     = NULL;
    }

    if (!*bisSyncState && *numSubgroups)
    {
        *bisSyncState = (u4*)clxAppAlloc(*numSubgroups * sizeof(u4));
        if (!*bisSyncState)
        {
            *numSubgroups = 0;
        }
    }

    if (!*metadata && *numSubgroups)
    {
        *metadata = (ClxBapAudioMetadataLtv*)clxAppAlloc(*numSubgroups * sizeof(ClxBapAudioMetadataLtv));
        if (!*metadata)
        {
            *numSubgroups = 0;
            clxPoolsetFree(*bisSyncState);
        }
    }
}

ClxResult clxBleInitBassMetadataBuffer ( u1 subGroupCount,
                                         ClxBapBroadcastReceiveState* receiveState,
                                         ClxBapBroadcastScanOpCode* bascontrolPoint )
{
    int i = 0;

    if ( receiveState && receiveState->numSubgroups )
    {
        clxBapInitializeMetadata ( subGroupCount, &receiveState->numSubgroups, &receiveState->bisSyncState, &receiveState->metadata );
    }

    if ( bascontrolPoint )
    {
        if ( ClxBapBassOpCode_AddSource == bascontrolPoint->opcode )
        {
            ClxBapBasAddSource* addSource = &bascontrolPoint->procedure.addSource;

            clxBapInitializeMetadata ( subGroupCount, &addSource->numSubgroups, &addSource->bisSyncState, &addSource->metadata );

            for ( i = 0; i < addSource->numSubgroups; ++i )
            {
                clxBapInitStructureByConfigType ( &addSource->metadata[i], ClxBapConfigType_MetaData);
            }
        }
        else if ( ClxBapBassOpCode_ModifySource == bascontrolPoint->opcode )
        {
            ClxBapBasModifySource* modifySource = &bascontrolPoint->procedure.modifySource;

            clxBapInitializeMetadata ( subGroupCount, &modifySource->numSubgroups, &modifySource->bisSyncState, &modifySource->metadata );

            for ( i = 0; i < modifySource->numSubgroups; ++i )
            {
                clxBapInitStructureByConfigType ( &modifySource->metadata[i], ClxBapConfigType_MetaData);
            }
        }
    }

    return CLX_SUCCESS;
}

void clxBapDeinitMetadata(u1* numSubgroups, u4** bisSyncState, ClxBapAudioMetadataLtv** metadata)
{
    if (*bisSyncState)
    {
        clxPoolsetFree(*bisSyncState);
        *bisSyncState = NULL;
    }

    if (*metadata)
    {
        clxPoolsetFree(*metadata);
        *metadata = NULL;
    }

    *numSubgroups = 0; // Reset subgroup count
}

void clxBleDeinitBassMetadataBuffer(ClxBapBroadcastReceiveState* receiveState, ClxBapBroadcastScanOpCode* bascontrolPoint)
{
    if (receiveState)
    {
        clxBapDeinitMetadata(&receiveState->numSubgroups, &receiveState->bisSyncState, &receiveState->metadata);
    }

    if (bascontrolPoint)
    {
        if (ClxBapBassOpCode_AddSource == bascontrolPoint->opcode)
        {
            ClxBapBasAddSource* addSource = &bascontrolPoint->procedure.addSource;
            clxBapDeinitMetadata(&addSource->numSubgroups, &addSource->bisSyncState, &addSource->metadata);
        }
        else if (ClxBapBassOpCode_ModifySource == bascontrolPoint->opcode)
        {
            ClxBapBasModifySource* modifySource = &bascontrolPoint->procedure.modifySource;
            clxBapDeinitMetadata(&modifySource->numSubgroups, &modifySource->bisSyncState, &modifySource->metadata);
        }
    }
}

u4 getCapSamplingFrequencyFromBitValue(u2 value)
{
    u4 samplingFrequency = 0x00;

    switch (value)
    {
        case ClxBapCapabilitySamplingFreq_8000Hz:
        {
            samplingFrequency = 8000;
            break;
        }

        case ClxBapCapabilitySamplingFreq_11025Hz:
        {
            samplingFrequency = 11025;
            break;
        }

        case ClxBapCapabilitySamplingFreq_16000Hz:
        {
            samplingFrequency = 16000;
            break;
        }

        case ClxBapCapabilitySamplingFreq_22050Hz:
        {
            samplingFrequency = 22050;
            break;
        }

        case ClxBapCapabilitySamplingFreq_24000Hz:
        {
            samplingFrequency = 24000;
            break;
        }

        case ClxBapCapabilitySamplingFreq_32000Hz:
        {
            samplingFrequency = 32000;
            break;
        }

        case ClxBapCapabilitySamplingFreq_44100Hz:
        {
            samplingFrequency = 44100;
            break;
        }

        case ClxBapCapabilitySamplingFreq_48000Hz:
        {
            samplingFrequency = 48000;
            break;
        }

        case ClxBapCapabilitySamplingFreq_88200Hz:
        {
            samplingFrequency = 88200;
            break;
        }

        case ClxBapCapabilitySamplingFreq_96000Hz:
        {
            samplingFrequency = 96000;
            break;
        }

        case ClxBapCapabilitySamplingFreq_176400Hz:
        {
            samplingFrequency = 176400;
            break;
        }

        case ClxBapCapabilitySamplingFreq_192000Hz:
        {
            samplingFrequency = 192000;
            break;
        }

        case ClxBapCapabilitySamplingFreq_384000Hz:
        {
            samplingFrequency = 384000;
            break;
        }

        default:
        {
            clxConsoleUIEngineText("\ngetSamplingFrequencyFromBitValue: Bit Value[%x]\n", value);
            break;
        }
    }

    return samplingFrequency;
}

s1* getCapFrameDurationFromBitValue(u1 value)
{
    if (ClxFrameDurationCap_7_5ms == value)
    {
        return (s1*)"7.5 ms";
    }
    else if (ClxFrameDurationCap_10ms == value)
    {
        return (s1*)"10 ms";
    }
    else if ((ClxFrameDurationCap_7_5ms & value) && (ClxFrameDurationCap_10ms & value))
    {
        return (s1*)"7.5 & 10 ms";
    }
    else
    {
        clxConsoleUIEngineText("\ngetFrameDurationFromBitValue: Bit Value[%x]\n", value);
    }

    return (s1*)"Invalid";
}

s1* getCodingFormatFromBitValue(u1 value)
{
    if (ClxBluetoothCodingFormat_LC3 == value)
    {
        return (s1*)"LC3";
    }
    else if (ClxBluetoothCodingFormat_mSBC == value)
    {
        return (s1*)"SBC";
    }
    else if (ClxBluetoothCodingFormat_LinearPCM == value)
    {
        return (s1*)"PCM";
    }
    else if (ClxBluetoothCodingFormat_VendorSpecific == value)
    {
        return (s1*)"Vendor Specific";
    }
    else
    {
        clxConsoleUIEngineText("\ngetCodingFormatFromBitValue: Bit Value[%x]\n", value);
    }

    return (s1*)"Invalid";
}

/**
Discover the audio capabilities
*/
ClxResult discoverAudioCapability( u2 characteristicUuid)
{
    ClxBapPacRecords   audioCapabilities = { };
    u2 valueHandle = 0;
    ClxResult ret = CLX_ERROR;
    ClxSize filledLength = 0;

    /* Retrieving Sink PAC value handle */
    valueHandle = GetValueHandle(getGattClientHandle(), CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID, characteristicUuid);

    /* Retrieving Sink PAC capabilities */
    ret = clxBapGetSinkPac ( getGattClientHandle(),
                             valueHandle, 
                             (u1*)inputValue,
                             MAX_INPUT_SIZE,
                             &filledLength,
                             TRUE);
    if (CLX_SUCCESS != ret)
    {
        clxConsoleUIEngineText("\nBLE BAP Get Sink PAC failed with error %s\n", clxGetErrorCodeText(ret));
        return ret;
    }

    /* Decode Sink PAC capability values */
    {
        u1  pacIndex = 0;
        u4  octPerCodecFrame = 0;
        u1* octPerCodecBuffer = NULL;
        u2  minOct = 0;
        u2  maxOct = 0;
        ClxSize decodeLength = 0;

        ret = clxBapDecodeBasicLevelPacRecord ((u1*)inputValue, filledLength, &audioCapabilities, &decodeLength );

        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nclx PAC Record Basic Decode Completed with Err:%s\n", clxGetErrorCodeText(ret) );
            return ret;
        }

        if ( audioCapabilities.numberOfPacRecords )
        {
            audioCapabilities.pacRecords = (ClxBapSinglePacRecord*)clxAppAllocZero(audioCapabilities.numberOfPacRecords * sizeof(ClxBapSinglePacRecord));

            if ( NULL == audioCapabilities.pacRecords )
            {
                return CLX_FAIL;
            }

            for (pacIndex = 0; pacIndex < audioCapabilities.numberOfPacRecords; ++pacIndex)
            {
                clxBapInitStructureByConfigType ( &audioCapabilities.pacRecords[pacIndex].capabilities, ClxBapConfigType_CodecCapability);
                clxBapInitStructureByConfigType ( &audioCapabilities.pacRecords[pacIndex].metadata, ClxBapConfigType_MetaData);
            }
        }

        clxDecodeOrgBluetoothCharacteristicSinkOrSourcePac((u1*)inputValue,
                                                           filledLength,
                                                           &audioCapabilities,
                                                           sizeof(ClxBapPacRecords),
                                                           &ret);

        if (CLX_SUCCESS != ret)
        {
            if ( audioCapabilities.pacRecords )
            {
                clxPoolsetFree( audioCapabilities.pacRecords );
            }
            printBufferHexAndChar ( (u1*)inputValue, filledLength );
            clxConsoleUIEngineText("\nDecode Audio Capability completed with the result %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        clxConsoleUIEngineText("\nRemote device audio capabilities");

        if (CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_UUID == characteristicUuid)
        {
            clxConsoleUIEngineText("\nNumber Of Sink Pac Records:%d\n", audioCapabilities.numberOfPacRecords);
        }
        else if (CLX_GATT_PACS_CHARACTERISTIC_SOURCE_PAC_UUID == characteristicUuid)
        {
            clxConsoleUIEngineText("\nNumber Of Source Pac Records:%d\n", audioCapabilities.numberOfPacRecords);
        }
        
        for (pacIndex = 0; pacIndex < audioCapabilities.numberOfPacRecords; ++pacIndex)
        {
            octPerCodecFrame = audioCapabilities.pacRecords[pacIndex].capabilities.supportedFrameLengthRange;
            octPerCodecBuffer = (u1*) &octPerCodecFrame;

            minOct = READ_FROM_LITTLEENDIAN_2((u2*) & octPerCodecBuffer[0]);
            maxOct = READ_FROM_LITTLEENDIAN_2((u2*) & octPerCodecBuffer[2]);

            clxConsoleUIEngineText("\n[#%d] Format[%s] SampFreq[%u Hz] Duration[%s] AudChn[%x] Min.Oct[%02x] Max.Oct[%02x] Max.Codec.Frame[%x]", pacIndex,
                getCodingFormatFromBitValue((u1)audioCapabilities.pacRecords[pacIndex].codecId.format),
                getCapSamplingFrequencyFromBitValue(audioCapabilities.pacRecords[pacIndex].capabilities.supportedSamplingFrequencies),
                getCapFrameDurationFromBitValue(audioCapabilities.pacRecords[pacIndex].capabilities.supportedFrameDurations),
                audioCapabilities.pacRecords[pacIndex].capabilities.supportedChannelAllocations,
                minOct,
                maxOct,
                audioCapabilities.pacRecords[pacIndex].capabilities.supportedSduIntervals);
        }
    }

    if (CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_UUID == characteristicUuid)
    {
        ClxBapPacAudioLocations sinkLocation = {};

        /* Retrieving Sink Audio location value handle */
        valueHandle = GetValueHandle(getGattClientHandle(), CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID, CLX_GATT_PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_UUID);

        /* Retrieving Sink audio location */
        ret = clxBapGetSinkAudioLocation(getGattClientHandle(), valueHandle, &sinkLocation, TRUE);

        if (CLX_SUCCESS != ret)
        {
            if ( audioCapabilities.pacRecords )
            {
                clxPoolsetFree( audioCapabilities.pacRecords );
                audioCapabilities.pacRecords = NULL;
            }

            clxConsoleUIEngineText("\nGet Sink Audio Location completed with the result %s", clxGetErrorCodeText(ret));
            return ret;
        }
        else
        {
            clxConsoleUIEngineText("\nSink audio locations: %x", sinkLocation.pacAudioLocations);
        }
    }
    else if (CLX_GATT_PACS_CHARACTERISTIC_SOURCE_PAC_UUID == characteristicUuid)
    {
        ClxBapPacAudioLocations sourceLocation = {};

        /* Retrieving Source Audio location value handle */
        valueHandle = GetValueHandle(getGattClientHandle(), CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID, CLX_GATT_PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_UUID);

        /* Retrieving Sink audio location */
        ret = clxBapGetSourceAudioLocation(getGattClientHandle(), valueHandle, &sourceLocation, TRUE);

        if (CLX_SUCCESS != ret)
        {
            if ( audioCapabilities.pacRecords )
            {
                clxPoolsetFree( audioCapabilities.pacRecords );
                audioCapabilities.pacRecords = NULL;
            }

            clxConsoleUIEngineText("\nGet Source Audio Location completed with the result %s", clxGetErrorCodeText(ret));
            return ret;
        }
        else
        {
            clxConsoleUIEngineText("\nSource audio locations: %x", sourceLocation.pacAudioLocations);
        }
    }

    if ( audioCapabilities.pacRecords )
    {
        clxPoolsetFree( audioCapabilities.pacRecords );
        audioCapabilities.pacRecords = NULL;
    }

    return ret;
}

/* Discovers the supported and available audio contexts */
void discoverAudioContext( void )
{
    ClxResult ret = CLX_ERROR;

    ClxBapPacSupportedAudioContext  supportedAudioContext = { };
    ClxBapPacAvailableAudioContext  availableAudioContext = { };
    u2 valHandle = 0;

    valHandle = GetValueHandle(getGattClientHandle(), CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID, CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_UUID);

    ret = clxBapGetSupportedAudioContext ( getGattClientHandle(),
                                           valHandle,
                                           &supportedAudioContext,
                                           TRUE);

    if (CLX_SUCCESS != ret)
    {
        clxConsoleUIEngineText("\nBAP Get Supported Audio Context failed with error %s", clxGetErrorCodeText(ret));
        return;
    }

    clxConsoleUIEngineText("\n\nRemote device audio context details");
    clxConsoleUIEngineText("\nSupported Sink Context  :%04x", supportedAudioContext.supportedSinkContext);
    clxConsoleUIEngineText("\nSupported Source Context:%04x", supportedAudioContext.supportedSourceContext);

    valHandle = GetValueHandle(getGattClientHandle(), CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID, CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_UUID);

    ret = clxBapGetAvailableAudioContext( getGattClientHandle(),
                                          valHandle,
                                          &availableAudioContext,
                                          TRUE);

    if (CLX_SUCCESS != ret)
    {
        clxConsoleUIEngineText("\nBAP Get Available Audio Context failed with error %s", clxGetErrorCodeText(ret));
        return;
    }

    clxConsoleUIEngineText("\nAvailable Audio Sink Context  :%02x", availableAudioContext.sinkContentAvailability);
    clxConsoleUIEngineText("\nAvailable Audio Source Context:%02x", availableAudioContext.sourceContentAvailability);
}

#endif /* CLX_BLE_ISOCHRONOUS */

