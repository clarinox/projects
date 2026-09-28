/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                BleIso.cpp
* Description         This file BLE audio ISO Common APIs
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX
#include "Clarinox.h"
#endif /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */

#include "BleAudioCommon.h"
#include "Iso.Ble.Interface.h"
#include "AudioInterface.h"
#include "BleLc3Common.h"
#include "BleIso.h"

/*===================================== GLOBAL VARIABLES =======================================*/

ClxBLEAudioSendThrdContext clxAudioSendThreadCxt[ CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT ]  = {};

static ClxBleIsoInterface isoInterface;

#if defined(CLX_LC3_SINK)
BleLc3Decode bleLc3AudioParams = {};
AudioOutputStream* audioOut = NULL;
#endif /* CLX_LC3_SINK */

/* BLE task priority table */
extern u2* clarinoxBluePlatformTaskPriorityTable;

const s1** bleInputFileName = NULL;

const s1* bleInputMonoFileName[ CLX_BLE_MONO_AUDIO_SUPPORTED_FILE_COUNT ] = {
                                                                        CLX_BLE_AUDIO_INPUT_FILE_1,
                                                                        "./Wav_48000/Mono/BreakingTheRule.wav",
                                                                        "./Wav_48000/Mono/Closer.wav",
                                                                        "./Wav_48000/Mono/ColdWater.wav",
                                                                        "./Wav_48000/Mono/DanceMonkey.wav",
                                                                        "./Wav_48000/Mono/GetOnTheFloor.wav",
                                                                        "./Wav_48000/Mono/Happy.wav",
                                                                        "./Wav_48000/Mono/ImagineDragons.wav",
                                                                        "./Wav_48000/Mono/JustinBieber.wav",
                                                                        "./Wav_48000/Mono/MoveIt.wav",
                                                                        "./Wav_48000/Mono/Senorita.wav",
                                                                        "./Wav_48000/Mono/ShapeofYou.wav",
                                                                        "./Wav_48000/Mono/Starboy.wav",
                                                                        "./Wav_48000/Mono/Thunder.wav",
                                                                        "./Wav_48000/Mono/WeDontTalk.wav"
                                                                    };

const s1* bleInputStereoFileName[ CLX_BLE_STEREO_AUDIO_SUPPORTED_FILE_COUNT ] = {
                                                                        "./Wav_48000/Stereo/WeDontTalkStereo.wav",
                                                                        "./Wav_48000/Stereo/ThunderStereo.wav",
                                                                        "./Wav_48000/Stereo/StarboyStereo.wav",
                                                                        "./Wav_48000/Stereo/ShapeofYouStereo.wav",
                                                                        "./Wav_48000/Stereo/SenoritaStereo.wav",
                                                                        "./Wav_48000/Stereo/ImagineDragonsStereo.wav",
                                                                        "./Wav_48000/Stereo/DanceMonkeyStereo.wav",
                                                                        "./Wav_48000/Stereo/CloserStereo.wav",
                                                                        "./Wav_48000/Stereo/BreakingTheRuleStereo.wav",
                                                                        "./Wav_48000/Stereo/BailaConmigoStereo.wav"
                                                                    };


/*==============================================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

ClxResult isoInit( _in_ struct ClxBleIsoInterface* thisObj, _in_ u2 maxTxIsoFragmentLength )
{
    (void)thisObj;

    clxConsoleUIEngineText("\nISO initialized: Packet length %u\n", maxTxIsoFragmentLength);

    return CLX_SUCCESS;
}

void isoDestroy ( _in_ struct ClxBleIsoInterface* thisObj )
{
    (void)thisObj;

    clxConsoleUIEngineText("\nISO terminated\n");
}

void isoRxReceived ( _in_ struct ClxBleIsoInterface* thisObj, _in_ struct ClxBleIsoRxBuffer* data, _in_ boolean isrContext )
{
    (void)thisObj;
    (void)isrContext;

    if (!data)
    {
        clxConsoleUIEngineText("\nisoRxReceived: Invalid Rx data\n");
        return;
    }

#if defined(CLX_LC3_SINK)
    if (getPreferredStreamHandle() == data->isoHandle)
    {
        ClxResult ret = CLX_ERROR;
        s4* bytes = NULL;
        u4 sizeOfDecodedData = 0;

        if ( !bleLc3AudioParams.isLc3Intialized )
        {
            clxConsoleUIEngineText("LC3 Decode not Intialized Yet !!\n");
        }

        if (FALSE == bleLc3DecodeStream(&bleLc3AudioParams, data->buffer, data->dataLength, &bytes, &sizeOfDecodedData))
        {
            clxConsoleUIEngineText("Decode failed\n");
        }
        else
        {
#if defined(CLX_FLOATINGPOINT_LC3)        
            u2 pcmBytes = (CLX_BLE_RECEIVER_PCM_BIT_DEPTH / 8);
            ret = audioOut->write((u1*)bytes, sizeOfDecodedData * pcmBytes * bleLc3AudioParams.noOfChannels);
#else
            ret = audioOut->write((u1*)bytes, sizeOfDecodedData);
#endif  /* CLX_FLOATINGPOINT_LC3 */

            if (CLX_SUCCESS != ret)
            {
                clxConsoleUIEngineText("\nAudio write failed with %s\n", clxGetErrorCodeText(ret));
            }
        }
    }
#else
    clxConsoleUIEngineText("\nError: CLX LC3 Sink not enabled\n");
#endif /* CLX_LC3_SINK */

    clxBleIsoReleaseRxBuffer(data);
}

void isoConnectionEstablished ( _in_ struct ClxBleIsoInterface* thisObj, _in_ const ClxBleIsoConnectionDetails* connectionDetails )
{
    (void)thisObj;

    if (!connectionDetails)
    {
        clxConsoleUIEngineText("\nisoConnectionEstablished: Invalid connecton details\n");
        return;
    }

    clxConsoleUIEngineText("\nISO connection established: Stream Id %u, Con.Handle %u\n", connectionDetails->streamId, connectionDetails->streamHandle);

    bleFillIsoStreamHandleIntoAudioSendThrdCxt(connectionDetails->streamHandle);

#if defined(CLX_LC3_SINK)
    if (connectionDetails->streamId == getPreferredStreamId())
    {
        setPreferredStreamHandle(connectionDetails->streamHandle);

        ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement = clxBleAudioGetBISBasicAnnouncement();

        s4 sampleRate       = CLX_BLE_AUDIO_SAMPLING_FREQUENCIES_VALUE;
        s4 frameDuration    = CLX_BLE_AUDIO_FRAME_DURATION;
        s4 bitRate          = getBitrate();
        u1 numChannels      = 0;

#if defined(CLX_FLOATINGPOINT_LC3)
        if (CLX_BLE_PREFERRED_MONO_CHANNEL_ALLOCATION == getPreferredAudioCount())
        {
            numChannels         = 1;
        }
        else
        {
            numChannels         = 2;
        }
#else
        numChannels         = getPreferredAudioCount();
#endif

        if (basicAnnouncement && basicAnnouncement->serviceUUID != 0)
        {
            for (u4 groupIndex  = 0; groupIndex < basicAnnouncement->numberOfSubGrp; groupIndex++)
            {
                s4 sampleFreq = getSamplingFrequencyFromValue(basicAnnouncement->subGrp[groupIndex].codecInfoForSubGrpSpecific.samplingFrequency);

                if (sampleFreq)
                {
                    sampleRate = sampleFreq;
                }

                u1 frameRate = basicAnnouncement->subGrp[groupIndex].codecInfoForSubGrpSpecific.frameDuration;

                if (frameRate == 0x00)      /* 7.5 ms */
                {
                    frameDuration = 75;
                }
                else if (frameRate == 0x01) /* 10 ms */
                {
                    frameDuration = 100;
                }
            }
        }

        if (!numChannels)
        {
            numChannels = CLX_BLE_AUDIO_NUMBER_OF_CHANNELS;
        }

        if ( FALSE == bleLc3AudioParams.isLc3Intialized )
        {
            if (FALSE == bleLc3InitDecoder(&bleLc3AudioParams, sampleRate, frameDuration, bitRate, numChannels))
            {
                clxConsoleUIEngineText("Initializing Decoder failed\n");
            }
        }

        if (NULL == audioOut)
        {
            audioOut = new OSAudioOutputStream;

            ClxAudioConfigStruct audioConfig = { };

            audioConfig.numberOfChannels    = numChannels;
            audioConfig.samplingFrequency   = sampleRate;
            audioConfig.format = ClxAudioConfigFormat_s16LE;

            clxConsoleUIEngineText("\nAudio start configuration: Samp.Freq[%u] Aud.Chn[%u]\n", sampleRate, numChannels);

            if (NULL != audioOut)
            {
                ClxResult ret = audioOut->start(audioConfig);
                
                if (CLX_SUCCESS != ret)
                {
                    clxConsoleUIEngineText("\nAudio start failed with %s\n", clxGetErrorCodeText(ret));
                }
            }
        }
        else
        {
            clxConsoleUIEngineText("\nAudio interface is already Initialized\n");
        }
    }
#endif /* defined(CLX_LC3_SINK) */
}

void isoConnectionTerminated ( _in_ struct ClxBleIsoInterface* thisObj, u2 isoConnectionHandle )
{
    (void)thisObj;

    clxConsoleUIEngineText("\nISO connection terminated: Con.Handle %u\n", isoConnectionHandle);

    u1 index  = 0;

#if defined(CLX_LC3_SINK)
    if (FALSE == bleLc3DeinitDecoder(&bleLc3AudioParams))
    {
        clxConsoleUIEngineText("De-Initializing Decoder failed\n");
    }

    if (NULL != audioOut)
    {
        delete audioOut;
        audioOut = NULL;
    }
#endif /* CLX_LC3_SINK */

    for ( index  = 0; index  < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
    {
        bleSetAudioSendThreadState ( ClxBleAudioPlayState_STOP, index );
    }

    bleResetIsoStreamHandleIntoAudioSendThrdCxt ( );
}

ClxBleIsoInterface* clxCreateIsoInterface ( void )
{
    isoInterface.isoInit                    = isoInit;
    isoInterface.isoDestroy                 = isoDestroy;
    isoInterface.isoRxReceived              = isoRxReceived;
    isoInterface.isoConnectionEstablished   = isoConnectionEstablished;
    isoInterface.isoConnectionTerminated    = isoConnectionTerminated;

    return &isoInterface;
}

#ifdef __cplusplus
}
#endif

/*******************************************************************************************************************************
*                                        bleInitAudioSendThread
*
* Initialize the Audio send context structure fields and call the create the Audio Send Thread function.
*
*******************************************************************************************************************************/
void bleInitAudioSendThread ( u1 index )
{
    if ( ! CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT )
    {
        clxConsoleUIEngineText("\n{Init FAIL} CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT[%d]\n", CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT );
        return;
    }

    if ( CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT <= index )
    {
        clxConsoleUIEngineText("\n{Init FAIL} Invalid BLE Audio Send thread Context Index[%d]\n", index );
        return;
    }

    if ( NULL != clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle )
    {
        clxConsoleUIEngineText("\n{Init FAIL} BLE Audio Send thread Already Created for context Index[%d]\n", index );
        return;
    }

    clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle   = NULL;
    clxAudioSendThreadCxt[ index ].bleAudioSendSemaphore      = NULL;
    clxAudioSendThreadCxt[ index ].bleCurrentPlayState        = ClxBleAudioPlayState_IDLE;

    clxAudioSendThreadCxt[ index ].bleAudioSendSemaphore      = clxCreateSemaphore(0);
    clxAudioSendThreadCxt[ index ].bleISOStreamHandle         = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;

    clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount = CLX_BLE_MONO_AUDIO_SUPPORTED_FILE_COUNT;
    clxAudioSendThreadCxt[ index ].bleCurrentFileIndex        = 0;
    bleInputFileName                                          = bleInputMonoFileName;

    bleLc3InitStreamParams (&clxAudioSendThreadCxt[ index ].lc3Encode);

#if defined(CLX_FLOATINGPOINT_LC3)
    if (2 == getNumberOfChannels())
    {
        clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount   = CLX_BLE_STEREO_AUDIO_SUPPORTED_FILE_COUNT;
        bleInputFileName                                            = bleInputStereoFileName;
    }
#endif  /* CLX_FLOATINGPOINT_LC3 */

#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX
    clxAudioSendThreadCxt[ index ].bleISOTxSemaphore         = clxCreateSemaphore(0);

    bleCreateIsoSendTimer( index );
#endif /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */

    clxAudioSendThreadCxt[ index ].bleAudioSendThreadKillSemaphore = clxCreateSemaphore(0);

    bleCreateAudioSendThread( index );
}

/*******************************************************************************************************************************
*                                        bleDestroyAudioSendThread
*
* Reset the Audio send context structure fields and destroy the Audio Send Thread resources.
*
*******************************************************************************************************************************/
void bleDestroyAudioSendThread ( u1 index )
{
    if ( CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT <= index )
    {
        clxConsoleUIEngineText("\n{Destroy FAIL} Invalid BLE Audio Send thread Context Index[%d]\n", index );
        return;
    }

    if ( NULL == clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle )
    {
        clxConsoleUIEngineText("\nBLE Audio Send thread not created yet\n");
        return;
    }

    if ( ClxBleAudioPlayState_IDLE == clxAudioSendThreadCxt[ index ].bleCurrentPlayState )
    {
        bleSetAudioSendThreadState ( ClxBleAudioPlayState_TERMINATE, index );
        clxReleaseSemaphore( clxAudioSendThreadCxt[ index ].bleAudioSendSemaphore );
    }
    else
    {
        bleSetAudioSendThreadState ( ClxBleAudioPlayState_TERMINATE, index );
    }

    /* Wait Still to break the thread loop */
    clxAcquireSemaphore( clxAudioSendThreadCxt[ index ].bleAudioSendThreadKillSemaphore );

    if ( clxAudioSendThreadCxt[ index ].bleAudioSendSemaphore )
    {
        clxDeleteSemaphore ( clxAudioSendThreadCxt[ index ].bleAudioSendSemaphore );
    }

    clxDeleteThread( clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle );

    clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle   = NULL;
    clxAudioSendThreadCxt[ index ].bleAudioSendSemaphore      = NULL;
    clxAudioSendThreadCxt[ index ].bleCurrentPlayState        = ClxBleAudioPlayState_IDLE;
    clxAudioSendThreadCxt[ index ].bleISOStreamHandle         = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;

    clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount = CLX_BLE_MONO_AUDIO_SUPPORTED_FILE_COUNT;
    clxAudioSendThreadCxt[ index ].bleCurrentFileIndex        = 0;
    bleInputFileName                                          = bleInputMonoFileName;

#if defined(CLX_FLOATINGPOINT_LC3)
    if (2 == getNumberOfChannels())
    {
        clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount   = CLX_BLE_STEREO_AUDIO_SUPPORTED_FILE_COUNT;
        bleInputFileName                                            = bleInputStereoFileName;
    }
#endif  /* CLX_FLOATINGPOINT_LC3 */

#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX
    bleDestroyIsoSendTimer ( &clxAudioSendThreadCxt[ index ] );

    if ( clxAudioSendThreadCxt[ index ].bleISOTxSemaphore )
    {
        clxDeleteSemaphore ( clxAudioSendThreadCxt[ index ].bleISOTxSemaphore );
    }

    clxAudioSendThreadCxt[ index ].bleISOTxSemaphore          = NULL;
#endif /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */

    if ( clxAudioSendThreadCxt[ index ].bleAudioSendThreadKillSemaphore )
    {
        clxDeleteSemaphore ( clxAudioSendThreadCxt[ index ].bleAudioSendThreadKillSemaphore );
    }
    clxAudioSendThreadCxt[ index ].bleAudioSendThreadKillSemaphore = NULL;

    clxConsoleUIEngineText("BLE Audio Send Thread TERMINATE Success [#%d]\n", index );
}

/*******************************************************************************************************************************
*                                        bleAudioSendThreadHandler
*
* BLE Audio send Thread handler function.
*
* \param data  Thread input data.
*
*******************************************************************************************************************************/
ClxResult bleAudioSendThreadHandler ( void* data )
{
    u4 count    = 0;
    boolean returnStates = FALSE;

#if defined(CLX_WINDOWS)
    HANDLE timer = CreateWaitableTimerEx(
        NULL,
        NULL,
        CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
        TIMER_ALL_ACCESS
    );

    LARGE_INTEGER waitTime;
#endif  /* CLX_WINDOWS */

    u1 index = 0xFF;
    u1 fillOpenFailCount = 0;

    if ( data )
    {
        index = ((ClxBLEAudioSendThrdContext*)data)->bleThreadContextIndex;
    }

    if ( CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT <= index )
    {
        clxConsoleUIEngineText("\n{THREAD FAIL} Invalid BLE Audio Send thread Context Index[%d]\n", index );
        return CLX_FAIL;
    }

    while (TRUE)
    {
        if ( ClxBleAudioPlayState_IDLE == clxAudioSendThreadCxt[ index ].bleCurrentPlayState )
        {
            clxAcquireSemaphore( clxAudioSendThreadCxt[ index ].bleAudioSendSemaphore );
        }

        /* Terminate the thread */
        if ( ClxBleAudioPlayState_TERMINATE == clxAudioSendThreadCxt[ index ].bleCurrentPlayState )
        {
            clxConsoleUIEngineText("\nBLE Audio Send KILL[#%d]\n", index );
            
            returnStates = bleLc3DeinitEncoder (&clxAudioSendThreadCxt[ index ].lc3Encode);
            if ( FALSE == returnStates )
            {
                clxConsoleUIEngineText("\nBLE Audio DeInit Encoder Failed\n");
            }

            clxReleaseSemaphore( clxAudioSendThreadCxt[ index ].bleAudioSendThreadKillSemaphore );
            break;
        }

        if ( ClxBleAudioPlayState_STOP == clxAudioSendThreadCxt[ index ].bleCurrentPlayState )
        {
            clxConsoleUIEngineText("\nBLE Audio Send Stop[#%d]\n", index );

            clxAudioSendThreadCxt[ index ].bleCurrentFileIndex = 0;

            bleSetAudioSendThreadState ( ClxBleAudioPlayState_IDLE, index );

            bleLc3ResetNowPlayingTrack(&clxAudioSendThreadCxt[ index ].lc3Encode);
            continue;
        }

        /* Audio File gets end so need to reinit the params and read new */
        if ( bleLc3IsEndOfNowPlayingTrack(&clxAudioSendThreadCxt[ index ].lc3Encode) )
        {
            returnStates = bleLc3DeinitEncoder (&clxAudioSendThreadCxt[ index ].lc3Encode);
            if ( FALSE == returnStates )
            {
                clxConsoleUIEngineText("\nBLE Audio DeInit Encoder Failed\n");
                bleSetAudioSendThreadState ( ClxBleAudioPlayState_IDLE, index );
            }

            count  = 0;

            if ( ClxBleAudioPlayState_GoNext == clxAudioSendThreadCxt[ index ].bleCurrentPlayState )
            {
                if ( (clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount - 1) <= clxAudioSendThreadCxt[ index ].bleCurrentFileIndex )
                {
                    clxAudioSendThreadCxt[ index ].bleCurrentFileIndex = 0;
                }
                else
                {
                    ++clxAudioSendThreadCxt[ index ].bleCurrentFileIndex;
                }
                bleSetAudioSendThreadState ( ClxBleAudioPlayState_PLAY, index);
            }
            else if ( ClxBleAudioPlayState_GoPrevious == clxAudioSendThreadCxt[ index ].bleCurrentPlayState )
            {
                if ( 0 == clxAudioSendThreadCxt[ index ].bleCurrentFileIndex )
                {
                    clxAudioSendThreadCxt[ index ].bleCurrentFileIndex = clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount - 1;
                }
                else
                {
                    --clxAudioSendThreadCxt[ index ].bleCurrentFileIndex;
                }

                bleSetAudioSendThreadState ( ClxBleAudioPlayState_PLAY, index );
            }

            if ( clxAudioSendThreadCxt[ index ].bleCurrentFileIndex >= clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount )
            {
                clxAudioSendThreadCxt[ index ].bleCurrentFileIndex = 0;
            }

            returnStates = bleLc3InitEncoder ( &clxAudioSendThreadCxt[ index ].lc3Encode, bleInputFileName[clxAudioSendThreadCxt[index].bleCurrentFileIndex] );

            if ( FALSE == returnStates )
            {
                ++fillOpenFailCount;

                clxConsoleUIEngineText("\nBLe LC3 Init Encoder Fail- [%s]\n", bleInputFileName[clxAudioSendThreadCxt[ index ].bleCurrentFileIndex]);

                clxAudioSendThreadCxt[ index ].bleCurrentFileIndex += 1;

                /* If any of the listed files encounter an issue during initialization, then go to the idle state. */
                if ( fillOpenFailCount == clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount )
                {
                    clxConsoleUIEngineText("\nFailed to Open All listed Audio files\n");
                    bleSetAudioSendThreadState ( ClxBleAudioPlayState_IDLE, index );

                    clxAudioSendThreadCxt[ index ].bleCurrentFileIndex = 0;
                }
                continue;
            }
            else
            {
                fillOpenFailCount = 0;
            }

            clxConsoleUIEngineText(
                "\nLC3 data transmission initiated with audio file '%s' in Context[%d] using the %s method, with a TimeOffset of [%d] milliseconds.\n",
                bleInputFileName[clxAudioSendThreadCxt[index].bleCurrentFileIndex],
                index,
#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX
                "Timer-based",
#else
                "High-Resolution Time-based",
#endif /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */
                CLX_BLE_AUDIO_LC3_SEND_OFFSET
            );
        }

        if ( CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE == clxAudioSendThreadCxt[ index ].bleISOStreamHandle )
        {
            clxConsoleUIEngineText("\nBLE Audio Send thread ISO Stream Handle Invalid Error #%d\n", index);
            bleSetAudioSendThreadState ( ClxBleAudioPlayState_IDLE, index );
            continue;
        }

#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX
        if ( TRUE == clxTimerRunning ( clxAudioSendThreadCxt[ index ].isoTxTimer ) )
        {
            clxStopTimer ( clxAudioSendThreadCxt[ index ].isoTxTimer );
            lll( "BLE Send Audio Timer Stop I[%u]", index);
        }
#endif /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */

#if defined(CLX_WINDOWS)
        u4 timeStamp = 0;
        s4 offset = 0;
        u4 frame_ms = (clxAudioSendThreadCxt[ index ].lc3Encode.frameDuration);
#endif  /* CLX_WINDOWS */

        while ( TRUE )
        {
            if ( ClxBleAudioPlayState_IDLE      == clxAudioSendThreadCxt[ index ].bleCurrentPlayState ||\
                 ClxBleAudioPlayState_STOP      == clxAudioSendThreadCxt[ index ].bleCurrentPlayState ||\
                 ClxBleAudioPlayState_TERMINATE == clxAudioSendThreadCxt[ index ].bleCurrentPlayState)
            {
                break;
            }

            bleLc3ResetEncodedDataSize(&clxAudioSendThreadCxt[ index ].lc3Encode);

            returnStates = bleLc3EncodeStream( &clxAudioSendThreadCxt[ index ].lc3Encode,
                                                  (ClxBleAudioPlayState_PLAY != clxAudioSendThreadCxt[index].bleCurrentPlayState));

            if ( FALSE == returnStates )
            {
                clxConsoleUIEngineText("\nPlay next track\n",
                                                    bleInputFileName[clxAudioSendThreadCxt[ index ].bleCurrentFileIndex]);
                
                bleLc3ResetNowPlayingTrack(&clxAudioSendThreadCxt[ index ].lc3Encode);
            }

#if !defined(CLX_FLOATINGPOINT_LC3)
            if ( CLX_BLE_ISO_MAX_SDU_SIZE < bleLc3GetEncodedDataSize(&clxAudioSendThreadCxt[ index ].lc3Encode) )
            {
                clxConsoleUIEngineText ( "\n #Error# ISO LC3 data length(%u) is grater then Max SDU length(%u)", 
                                           bleLc3GetEncodedDataSize(&clxAudioSendThreadCxt[index].lc3Encode), CLX_BLE_ISO_MAX_SDU_SIZE );
            }
#endif  /* !CLX_FLOATINGPOINT_LC3 */

            if ( ClxBleAudioPlayState_GoNext     == clxAudioSendThreadCxt[ index ].bleCurrentPlayState ||\
                 ClxBleAudioPlayState_GoPrevious == clxAudioSendThreadCxt[ index ].bleCurrentPlayState )
            {
                bleLc3ResetNowPlayingTrack(&clxAudioSendThreadCxt[ index ].lc3Encode);
            }
            else if (bleLc3IsEndOfNowPlayingTrack(&clxAudioSendThreadCxt[ index ].lc3Encode))
            {
                ++clxAudioSendThreadCxt[ index ].bleCurrentFileIndex;
            }
            else if (!bleLc3GetEncodedDataSize(&clxAudioSendThreadCxt[ index ].lc3Encode))
            {
                bleLc3ResetNowPlayingTrack(&clxAudioSendThreadCxt[ index ].lc3Encode);
            }

            /* Exit when file is done */
            if (bleLc3IsEndOfNowPlayingTrack(&clxAudioSendThreadCxt[ index ].lc3Encode))
            {
                break;
            }

            u4 encodedDataSize = 0;
            u1* encodedData = bleLc3GetEncodedDataBytes(&clxAudioSendThreadCxt[ index ].lc3Encode, &encodedDataSize);

            ClxBleIsoTxBuffer* txBuffer = clxBleIsoGetTxBuffer ( (u2)encodedDataSize );

            if ( NULL != txBuffer )
            {
                txBuffer->isoHandle  = clxAudioSendThreadCxt[ index ].bleISOStreamHandle;
                memcpy ( txBuffer->buffer, encodedData, txBuffer->bufferSize );
                txBuffer->dataLength = txBuffer->bufferSize;

#if defined(CLX_WINDOWS)
                u4 timeNow = clxHighResolutionTime();
                if (timeStamp)
                {
                    /* If the timer is late, add to offset. If the timer is early, reduce from offset */
                    if ((timeNow - timeStamp) > frame_ms)
                    {
                        offset = ((timeNow - timeStamp) - frame_ms);
                    }
                    else
                    {
                        offset = (frame_ms - (timeNow - timeStamp));
                    }
                }

                /* Add or subtract the offset time to adjust to the interval of 10 or 7.5 ms, for the next send */
                waitTime.QuadPart = -((LONGLONG)(frame_ms * 10LL) - (LONGLONG)(offset * 10LL));  // 10 ms in 100ns units (negative = relative)

                timeStamp = clxHighResolutionTime();

                SetWaitableTimer(timer, &waitTime, 0, NULL, NULL, FALSE);

                WaitForSingleObject(timer, INFINITE);
#endif  /* CLX_WINDOWS */

                clxBleIsoSendData ( txBuffer );

#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX
#ifdef CLX_WINDOWS
                if ( TRUE != clxTimerRunning ( clxAudioSendThreadCxt[ index ].isoTxTimer ) )
#endif /* CLX_WINDOWS */
                {
                    clxStartTimer ( clxAudioSendThreadCxt[ index ].isoTxTimer, CLX_BLE_AUDIO_LC3_SEND_OFFSET );
                    lll( "BLE Send Audio Timer Start I[%u]", index);
                }

                clxAcquireSemaphore( clxAudioSendThreadCxt[ index ].bleISOTxSemaphore );
#else
#if !defined(CLX_WINDOWS)
                /* Send each packet with 10 ms delay */
                u4 timeStamp = clxHighResolutionTime();

                while (TRUE)
                {
                    u4 timeNow = clxHighResolutionTime();

                    if ( ((timeNow - timeStamp) >= CLX_BLE_AUDIO_LC3_SEND_OFFSET ) ||\
                         ( ClxBleAudioPlayState_STOP      == clxAudioSendThreadCxt[ index ].bleCurrentPlayState ) ||\
                         ( ClxBleAudioPlayState_TERMINATE == clxAudioSendThreadCxt[ index ].bleCurrentPlayState))
                    {
                        break;
                    }
                }
#endif  /* !CLX_WINDOWS */
#endif  /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */
            }
            else
            {
                clxConsoleUIEngineText("\nISO Tx Buffer Allocation Failed #%d\n", index);
            }
            ++count;
        }
    }

#if defined(CLX_WINDOWS)
    CloseHandle(timer);
#endif  /* CLX_WINDOWS */

    return CLX_SUCCESS;
}

/*******************************************************************************************************************************
*                                        bleCreateAudioSendThread
*
* Function to create the BLE Audio send Thread 
*
*******************************************************************************************************************************/
void bleCreateAudioSendThread ( u1 index )
{
    if ( NULL == clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle )
    {
        clxAudioSendThreadCxt[ index ].bleThreadContextIndex    = index;

        snprintf ( clxAudioSendThreadCxt[ index ].bleThreadName,
                   sizeof(clxAudioSendThreadCxt[ index ].bleThreadName),
                   "%s_%02d",
                   CLX_BLE_AUDIO_SEND_THREAD_NAME,
                   index);

        clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle = clxBeginThread ( bleAudioSendThreadHandler,
                                                                                     (void*)&clxAudioSendThreadCxt[ index ],
                                                                                     clxAudioSendThreadCxt[ index ].bleThreadName,
                                                                                     CLX_BLE_AUDIO_SEND_THREAD_STACK_SIZE,
                                                                                     clarinoxBluePlatformTaskPriorityTable,
                                                                                     ClxThreadPriority_Lowest );

        if ( !clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle )
        {
            clxConsoleUIEngineText("\n%s creation failed Context Index[%d]\n", clxAudioSendThreadCxt[ index ].bleThreadName, index );
        }
        else
        {
            clxConsoleUIEngineText("\n%s creation Success Context Index[%d]\n", clxAudioSendThreadCxt[ index ].bleThreadName, index );
        }
    }
    else
    {
        clxConsoleUIEngineText("\nBLE Audio Send thread Already Created for context Index[%d]\n", index );
    }
}

/*******************************************************************************************************************************
*                                        bleStartAudioSendProcess
*
* Set the play status as PLAY and signal to semaphore for start the Audio send process
*
*******************************************************************************************************************************/
void bleStartAudioSendProcess ( u1 index )
{
    if ( CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT <= index )
    {
        clxConsoleUIEngineText("\n{START FAIL} Invalid BLE Audio Send thread Context Index[%d]\n", index );
        return;
    }

    if ( NULL == clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle )
    {
        clxConsoleUIEngineText("\nBLE Audio Send thread not yet created\n");
        return;
    }

    if ( ClxBleAudioPlayState_PLAY == clxAudioSendThreadCxt[ index ].bleCurrentPlayState )
    {
        clxConsoleUIEngineText("\nBLE Audio Sending Already\n");
        return;
    }

    clxConsoleUIEngineText( "\nBLE Start Audio Send Process #%d {Status[%u ->%u]}\n",
                                    index,
                                    clxAudioSendThreadCxt[ index ].bleCurrentPlayState,
                                    ClxBleAudioPlayState_PLAY );

    clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount = CLX_BLE_MONO_AUDIO_SUPPORTED_FILE_COUNT;
    clxAudioSendThreadCxt[ index ].bleCurrentFileIndex        = 0;

#if defined(CLX_FLOATINGPOINT_LC3)
    if (2 == getNumberOfChannels())
    {
        clxAudioSendThreadCxt[ index ].bleSupportedAudioFileCount   = CLX_BLE_STEREO_AUDIO_SUPPORTED_FILE_COUNT;
        bleInputFileName                                            = bleInputStereoFileName;
    }
#endif  /* CLX_FLOATINGPOINT_LC3 */

    bleSetAudioSendThreadState ( ClxBleAudioPlayState_PLAY, index );
    clxReleaseSemaphore( clxAudioSendThreadCxt[ index ].bleAudioSendSemaphore );
}

/*******************************************************************************************************************************
*                                        bleSetAudioSendThreadState
*
* User to set the Audio send thread play status into the Context structure
*
* \param  newState    User BLE Audio Play State enum
*
*******************************************************************************************************************************/
void bleSetAudioSendThreadState ( ClxBleAudioPlayState  newState, u1 index )
{
    if ( CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT <= index )
    {
        clxConsoleUIEngineText("\n{SetStatus FAIL} Invalid BLE Audio Send thread Context Index[%d]\n", index );
        return;
    }

    if ( NULL == clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle )
    {
        clxConsoleUIEngineText("\nBLE Audio Send thread not yet created\n");
        return;
    }

    clxAudioSendThreadCxt[ index ].bleCurrentPlayState = newState;
}

/*******************************************************************************************************************************
*                                        bleGetAudioSendThreadState
*
* Get the Audio send thread play status from the Context structure
*
* \return      BLE Audio Play State enum from the context structure
*
*******************************************************************************************************************************/
ClxBleAudioPlayState bleGetAudioSendThreadState ( u1 index )
{
    if ( CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT <= index )
    {
        clxConsoleUIEngineText("\n{GetStatus FAIL} Invalid BLE Audio Send thread Context Index[%d]\n", index );
        return ClxBleAudioPlayState_IDLE;
    }

    if ( NULL == clxAudioSendThreadCxt[ index ].bleAudioSendThreadHandle )
    {
        clxConsoleUIEngineText("\nBLE Audio Send thread not yet created\n");
        return ClxBleAudioPlayState_IDLE;
    }

    return clxAudioSendThreadCxt[ index ].bleCurrentPlayState;
}

/*******************************************************************************************************************************
*                                        bleGetAudioSendThrdCxtInfo
*
* Get the Audio send thread Context structure
*
* \param  index    BLE Audio Send thread Context Index
*
* \return      Address of the context structure by given index
*
*******************************************************************************************************************************/
ClxBLEAudioSendThrdContext* bleGetAudioSendThrdCxtInfo ( u1 index )
{
    if ( CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT <= index )
    {
        clxConsoleUIEngineText("\n{GetInfo FAIL} Invalid BLE Audio Send thread Context Index[%d]\n", index );
        return NULL;
    }

    return &clxAudioSendThreadCxt[ index ];
}

/*******************************************************************************************************************************
*                                        bleFillIsoStreamHandleIntoAudioSendThrdCxt
*
* Fill ISO Stream Handle into the Audio Send Thread context structure.
*
* \param  isoStreamHandle      ISO Stream Handle
*
*******************************************************************************************************************************/
void bleFillIsoStreamHandleIntoAudioSendThrdCxt ( u2 isoStreamHandle )
{
    u1 index  = 0;

    boolean fillStatus = FALSE;

    if ( CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT <= index )
    {
        clxConsoleUIEngineText("\n{SetHandle FAIL} Invalid BLE Audio Send thread Context Index[%d]\n", index );
        return;
    }

    for ( index = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
    {
        if ( CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE == clxAudioSendThreadCxt[ index ].bleISOStreamHandle )
        {
            clxAudioSendThreadCxt[ index ].bleISOStreamHandle = isoStreamHandle;

            clxConsoleUIEngineText("\n<FILE HANDLE SUCCESS> Context[#%d] ISOStream Handle[%u]\n", index, clxAudioSendThreadCxt[ index ].bleISOStreamHandle );

            fillStatus = TRUE;
            break;
        }
    }

    if ( FALSE == fillStatus )
    {
        clxConsoleUIEngineText("\nContext Not Available\n");

        for ( index = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
        {
            clxConsoleUIEngineText("\nContext[#%d] ISOStream Handle[%u]\n", index, clxAudioSendThreadCxt[ index ].bleISOStreamHandle );
        }
    }
}

/*******************************************************************************************************************************
*                                        bleResetIsoStreamHandleIntoAudioSendThrdCxt
*
* Reset ISO Stream Handle into the Audio Send Thread context structure.
*
*******************************************************************************************************************************/
void bleResetIsoStreamHandleIntoAudioSendThrdCxt ( void )
{
    u1 index  = 0;

    for ( index = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
    {
        clxAudioSendThreadCxt[ index ].bleISOStreamHandle = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;
    }
}

#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX

bool clxBLEIsoSendTimerMessage (void* data)
{
    u1 index = (u1)(uintptr_t)data;
    clxReleaseSemaphore( clxAudioSendThreadCxt[ index ].bleISOTxSemaphore );

    lll( "BLE Send Audio Timer HIT [%u]", index);

    return true;
}

ClxResult bleCreateIsoSendTimer ( u1 index )
{
    ClxTimerMode mode = TM_ONESHOT;

    if ( CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT <= index )
    {
        clxConsoleUIEngineText("\n{Create ISO Send Timer FAIL} Invalid BLE Audio Send thread Context Index[%d]\n", index );
        return CLX_ERROR;
    }

    if ( clxAudioSendThreadCxt[ index ].isoTxTimer )
    {
        clxConsoleUIEngineText("\n ### ISO Tx TIMER Is already Created###\n" );
        return CLX_ERROR;
    }


#ifdef CLX_WINDOWS
    mode = TM_PERIODIC;
#endif /* CLX_WINDOWS */

    clxAudioSendThreadCxt[ index ].isoTxTimer = clxCreateTimer ( CLX_BLE_AUDIO_LC3_SEND_OFFSET, (ClxTimerHandler)clxBLEIsoSendTimerMessage, (void*)index, mode );

    if ( NULL == clxAudioSendThreadCxt[ index ].isoTxTimer )
    {
        return CLX_ERROR;
    }

    return CLX_SUCCESS;
}

ClxResult bleDestroyIsoSendTimer ( ClxBLEAudioSendThrdContext* clxAudioSendThreadCxtInfo )
{

    if ( !clxAudioSendThreadCxtInfo->isoTxTimer )
    {
        clxConsoleUIEngineText("\n ### ISO Tx TIMER Is not Created###\n" );
        return CLX_ERROR;
    }

    clxDeleteTimer ( clxAudioSendThreadCxtInfo->isoTxTimer );
    clxAudioSendThreadCxtInfo->isoTxTimer = NULL;

    return CLX_SUCCESS;
}

#endif /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */

#endif /* CLX_BLE_ISOCHRONOUS */

