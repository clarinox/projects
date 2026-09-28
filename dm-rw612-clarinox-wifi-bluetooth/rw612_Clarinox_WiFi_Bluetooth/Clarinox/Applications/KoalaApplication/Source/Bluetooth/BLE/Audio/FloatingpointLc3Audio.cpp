/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                FloatingpointLc3Audio.cpp
* Description         This file BLE audio Floating Point API interfaces
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#if defined(CLX_FLOATINGPOINT_LC3)
#include <stdio.h>
#include "FloatingpointLc3.h"
#include "BleAudioCommon.h"
#include "GattApp.h"
#include "GattServer.h"
#include "GattClient.h"
#include "Iso.Ble.Client.Api.h"
#include "BleLc3Common.h"
#include "BleIso.h"

/**********************************************************************************************************************
*                                           bleFloatingpointLc3InitStreamParams
*
* Initialize Clarinox Floating Point LC3 codec parameters.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return void
*
***********************************************************************************************************************/
void bleFloatingpointLc3InitStreamParams(BleLc3Encode* bleFloatingpointLc3AudioParams)
{
    if (FALSE == bleFloatingpointLc3AudioParams->isLc3Intialized)
    {
        clxConsoleUIEngineText("Initializing Floating Point LC3 Parameters..\n");

        getAudioChannelMode();

        bleFloatingpointLc3AudioParams->bitRate            = getBitrate();
        bleFloatingpointLc3AudioParams->numChannels        = getNumberOfChannels();
        bleFloatingpointLc3AudioParams->frameDuration      = CLX_BLE_AUDIO_FRAME_DURATION * 100;
        bleFloatingpointLc3AudioParams->sampleRate         = CLX_BLE_AUDIO_SAMPLING_FREQUENCIES_VALUE;
        bleFloatingpointLc3AudioParams->pcmFormat          = ClxFloatingpointLc3PcmFormat_S16;
        bleFloatingpointLc3AudioParams->blockBytes         = clxFloatingpointLc3GetBlockBytes(bleFloatingpointLc3AudioParams->frameDuration,
                                                                                              bleFloatingpointLc3AudioParams->sampleRate,
                                                                                              bleFloatingpointLc3AudioParams->numChannels,
                                                                                              bleFloatingpointLc3AudioParams->bitRate);
        bleFloatingpointLc3AudioParams->numSamplesFile     = 0;
        bleFloatingpointLc3AudioParams->numberSamplesRead  = 0;
        bleFloatingpointLc3AudioParams->numBytes           = 0;
        bleFloatingpointLc3AudioParams->frameBytes         = clxFloatingpointLc3GetFrameBytes(bleFloatingpointLc3AudioParams->frameDuration, bleFloatingpointLc3AudioParams->sampleRate, (bleFloatingpointLc3AudioParams->bitRate / bleFloatingpointLc3AudioParams->numChannels));
        bleFloatingpointLc3AudioParams->frameSamples       = clxFloatingpointLc3GetFrameSamples(bleFloatingpointLc3AudioParams->frameDuration, bleFloatingpointLc3AudioParams->sampleRate);
        bleFloatingpointLc3AudioParams->encodeSamples      = 0;      /* Gives total samples to be encoded. Not used for now. */
        bleFloatingpointLc3AudioParams->hrmode             = FALSE;  /* TRUE - If required, optionally used beyond 48K frequency */
        bleFloatingpointLc3AudioParams->encoderSize        = 0;

        bleFloatingpointLc3AudioParams->pcmBits            = 0;
        bleFloatingpointLc3AudioParams->pcmBytes           = 0;

        bleFloatingpointLc3AudioParams->fp_in              = NULL;

        bleFloatingpointLc3AudioParams->maxPcmBytesSize        = (2 * clxFloatingpointLc3GetMaxFrameSamples() * 4);
        bleFloatingpointLc3AudioParams->maxEncodedBytesSize    = (2 * clxFloatingpointLc3GetMaxFrameBytes());

        bleFloatingpointLc3AudioParams->pcm           = (u1*)clxAppAllocZero( bleFloatingpointLc3AudioParams->maxPcmBytesSize );
        bleFloatingpointLc3AudioParams->bytes         = (u1*)clxAppAllocZero( bleFloatingpointLc3AudioParams->maxEncodedBytesSize );

        memset(bleFloatingpointLc3AudioParams->pcm, 0, bleFloatingpointLc3AudioParams->maxPcmBytesSize);
        memset(bleFloatingpointLc3AudioParams->bytes, 0, bleFloatingpointLc3AudioParams->maxEncodedBytesSize);

        /*
        clxConsoleUIEngineText("frameSamples for pcm: %u\n", bleFloatingpointLc3AudioParams->frameSamples);
        clxConsoleUIEngineText("frameBytes for enc bytes: %u\n", bleFloatingpointLc3AudioParams->frameBytes);
        clxConsoleUIEngineText("bleFloatingpointLc3AudioParams->maxPcmBytesSize: %u\n", bleFloatingpointLc3AudioParams->maxPcmBytesSize);
        clxConsoleUIEngineText("bleFloatingpointLc3AudioParams->maxEncodedBytesSize: %u\n", bleFloatingpointLc3AudioParams->maxEncodedBytesSize);
        */

        bleFloatingpointLc3AudioParams->isLc3Intialized = TRUE;

        clxConsoleUIEngineText("Initializing Floating Point LC3 Parameters... ...COMPLETED\n");
    }
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3InitStream
*
* Initialize Clarinox Floating Point LC3 codec implementation like setting up encoder/decoder, etc.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param trackName                       - Name of the sound track that has to be streamed from source to sink
*
* \return boolean                        - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleFloatingpointLc3InitStream(BleLc3Encode* bleFloatingpointLc3AudioParams, const s1* trackName)
{
    boolean ret = TRUE;

    bleFloatingpointLc3InitStreamParams(bleFloatingpointLc3AudioParams);

    clxConsoleUIEngineText("Initializing Floating Point LC3 Encoder..\n");

    if ((bleFloatingpointLc3AudioParams->fp_in = fopen(trackName, "rb")) == NULL)
    {
        clxConsoleUIEngineText("Open Error: %s\n", trackName);
        return FALSE;
    }

    fseek(bleFloatingpointLc3AudioParams->fp_in, 0, SEEK_SET);

    clxConsoleUIEngineText("Reading Wav file header\n");
    if( clxFloatingpointWaveReadHeader( bleFloatingpointLc3AudioParams->fp_in, 
                                        &bleFloatingpointLc3AudioParams->pcmBits,
                                        &bleFloatingpointLc3AudioParams->pcmBytes,
                                        &bleFloatingpointLc3AudioParams->sampleRate,
                                       (int*)&bleFloatingpointLc3AudioParams->numChannels,
                                       (int*)&bleFloatingpointLc3AudioParams->numSamplesFile) < 0 )
    {
        clxConsoleUIEngineText( "Bad or unsupported WAVE input file" );
        fclose(bleFloatingpointLc3AudioParams->fp_in);
        return FALSE;
    }

    clxConsoleUIEngineText("PCM Bytes: %u, PCM Bits: %u, Sample Rate: %u Hz, Number of Channels: %u, Frame duration: %u ms, Number of Samples: %u\n", 
                              bleFloatingpointLc3AudioParams->pcmBytes, 
                              bleFloatingpointLc3AudioParams->pcmBits, 
                              bleFloatingpointLc3AudioParams->sampleRate, 
                              bleFloatingpointLc3AudioParams->numChannels, 
                              ((bleFloatingpointLc3AudioParams->frameDuration)/1000),
                              bleFloatingpointLc3AudioParams->numSamplesFile);

    /* Calculate the number of encoded bytes each ISO packet is made up of */
    bleFloatingpointLc3AudioParams->frameBytes     = clxFloatingpointLc3GetFrameBytes(
                                                        bleFloatingpointLc3AudioParams->frameDuration, 
                                                        bleFloatingpointLc3AudioParams->sampleRate, 
                                                        (bleFloatingpointLc3AudioParams->bitRate / bleFloatingpointLc3AudioParams->numChannels));
    clxConsoleUIEngineText("Bytes/Frame: %u\n", bleFloatingpointLc3AudioParams->frameBytes);

#if 0
    int bitrate = clxFloatingpointLc3GetDelaySamples(
                    bleFloatingpointLc3AudioParams->frameDuration, 
                    bleFloatingpointLc3AudioParams->sampleRate);
    clxConsoleUIEngineText("resolved bitrate: %u\n", bitrate);

    bleFloatingpointLc3AudioParams->encodeSamples  = bleFloatingpointLc3AudioParams->numSamplesFile + 
                                                        clxFloatingpointLc3GetDelaySamples(
                                                        bleFloatingpointLc3AudioParams->frameDuration, 
                                                        bleFloatingpointLc3AudioParams->sampleRate);
    clxConsoleUIEngineText("encodeSamples: %u\n", bleFloatingpointLc3AudioParams->encodeSamples);
#endif

    /* Calculate the number of samples for each ISO packet sent */
    bleFloatingpointLc3AudioParams->frameSamples   = clxFloatingpointLc3GetFrameSamples(bleFloatingpointLc3AudioParams->frameDuration, bleFloatingpointLc3AudioParams->sampleRate);
    clxConsoleUIEngineText("Samples/Frame: %u\n", bleFloatingpointLc3AudioParams->frameSamples);

    bleFloatingpointLc3AudioParams->pcmFormat = (bleFloatingpointLc3AudioParams->pcmBytes == 32/8 ) ? ClxFloatingpointLc3PcmFormat_S24 : \
                                         (bleFloatingpointLc3AudioParams->pcmBytes == 24/8 ) ? ClxFloatingpointLc3PcmFormat_3LE : ClxFloatingpointLc3PcmFormat_S16;

    /* Calculated the size required by the encoder */
    bleFloatingpointLc3AudioParams->encoderSize = clxFloatingpointLc3GetEncoderSize(bleFloatingpointLc3AudioParams->frameDuration, bleFloatingpointLc3AudioParams->sampleRate);

    clxConsoleUIEngineText( "\nEncoder Setup: hrmode[%u] frameDuration[%u] sampleRate[%u] encoderSize[%u] \n", 
                                 bleFloatingpointLc3AudioParams->hrmode,
                                 bleFloatingpointLc3AudioParams->frameDuration,
                                 bleFloatingpointLc3AudioParams->sampleRate,
                                 bleFloatingpointLc3AudioParams->encoderSize);

    for (int ich = 0; ich < bleFloatingpointLc3AudioParams->numChannels; ich++)
    {
        bleFloatingpointLc3AudioParams->encoderMemory[ich] = clxAppAllocZero( bleFloatingpointLc3AudioParams->encoderSize );

        bleFloatingpointLc3AudioParams->enc[ich] = clxFloatingpointLc3SetupEncoder(bleFloatingpointLc3AudioParams->frameDuration,
                                                                                   bleFloatingpointLc3AudioParams->sampleRate,
                                                                                   bleFloatingpointLc3AudioParams->encoderMemory[ich]);
        if (!bleFloatingpointLc3AudioParams->enc[ich])
        {
            clxConsoleUIEngineText( "\nLC3 Encoder initialization failed\n" );
            ret = FALSE;
            break;
        }
    }
    
    if (FALSE == ret)
    {
        bleFloatingpointLc3DeinitStream(bleFloatingpointLc3AudioParams);
        bleFloatingpointLc3AudioParams->isLc3Intialized = FALSE;
    }

    clxConsoleUIEngineText("Initializing Floating Point LC3 Encoder... ...COMPLETED\n");

    return TRUE;
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3DeinitStream
*
* De-Initialize Clarinox Floating Point LC3 codec implementation like freeing up buffers and other resources, etc.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return boolean                        - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleFloatingpointLc3DeinitStream(BleLc3Encode* bleFloatingpointLc3AudioParams)
{
    clxConsoleUIEngineText("De-Initializing Floating Point LC3..\n");

    if (bleFloatingpointLc3AudioParams->fp_in)
    {
        fclose(bleFloatingpointLc3AudioParams->fp_in);
        bleFloatingpointLc3AudioParams->fp_in = NULL;
    }

    /* ReInit the Encoder handles */
    for (int ich = 0; ich < bleFloatingpointLc3AudioParams->numChannels; ++ich)
    {
        if (bleFloatingpointLc3AudioParams->encoderMemory[ich])
        {
            clxPoolsetFree( bleFloatingpointLc3AudioParams->encoderMemory[ich] );
            bleFloatingpointLc3AudioParams->encoderMemory[ich] = NULL;
        }

        bleFloatingpointLc3AudioParams->enc[ich] = NULL;
    }

    if (bleFloatingpointLc3AudioParams->bytes)
    {
        clxPoolsetFree( bleFloatingpointLc3AudioParams->bytes );
        bleFloatingpointLc3AudioParams->bytes = NULL;
    }

    if (bleFloatingpointLc3AudioParams->pcm)
    {
        clxPoolsetFree( bleFloatingpointLc3AudioParams->pcm );
        bleFloatingpointLc3AudioParams->pcm = NULL;
    }

    bleFloatingpointLc3AudioParams->isLc3Intialized = FALSE;

    clxConsoleUIEngineText("De-Initializing Floating Point LC3... ...COMPLETED\n");

    return TRUE;
}

/* Attenuate/reduce the amplitude of the audio to avoid distortion */
void attenuateAudio(s2 *samples, u4 numSamples, s2 noOfChannels)
{
    for (u4 index = 0; index < numSamples * noOfChannels; index++) 
    {
        samples[index] = samples[index] >> 1;  // divide by 2
    }
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3EncodeStream
*
* Encode pcm data to encoded LC3 bytes using Clarinox Floating Point LC3 codec implementation.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param isPsuedoEncode                  - Specifies if pcm data to be encoded or return dummy bytes
*
* \return boolean                        - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleFloatingpointLc3EncodeStream(BleLc3Encode* bleFloatingpointLc3AudioParams, boolean isPsuedoEncode)
{
    int samplesRead = 0;

    /*for (int i = 0; (i * bleFloatingpointLc3AudioParams->frameSamples) < bleFloatingpointLc3AudioParams->encodeSamples; i++) */
    {
        memset(bleFloatingpointLc3AudioParams->pcm, 0, bleFloatingpointLc3AudioParams->maxPcmBytesSize);
        memset(bleFloatingpointLc3AudioParams->bytes, 0, bleFloatingpointLc3AudioParams->maxEncodedBytesSize);

        /* 
         * To avoid the issue of audio stopping on the remote device, send dummy (zero-filled) packets during non-play states. 
         * So read the wav file only When in the Play state condition 
         */
        if( FALSE == isPsuedoEncode )
        {
            /* Read the frames from the Wav file that has to be streamed */
            samplesRead = clxFloatingpointWavReadPcm( bleFloatingpointLc3AudioParams->fp_in, 
                                                      bleFloatingpointLc3AudioParams->pcmBytes, 
                                                      bleFloatingpointLc3AudioParams->numChannels, 
                                                      bleFloatingpointLc3AudioParams->frameSamples, 
                                                      bleFloatingpointLc3AudioParams->pcm );
            if (!samplesRead)
            {
                clxConsoleUIEngineText("\nEnd of file. Total Samples read: %u\n", bleFloatingpointLc3AudioParams->numberSamplesRead);
                bleFloatingpointLc3AudioParams->numberSamplesRead = 0;

                return FALSE;
            }

            attenuateAudio(((s2*)bleFloatingpointLc3AudioParams->pcm), samplesRead, bleFloatingpointLc3AudioParams->numChannels);
        }

        bleFloatingpointLc3AudioParams->numberSamplesRead += samplesRead;
        
        memset(bleFloatingpointLc3AudioParams->pcm + samplesRead * bleFloatingpointLc3AudioParams->numChannels * bleFloatingpointLc3AudioParams->pcmBytes, 0,
                    bleFloatingpointLc3AudioParams->numChannels * (bleFloatingpointLc3AudioParams->frameSamples - samplesRead) * bleFloatingpointLc3AudioParams->pcmBytes);

        bleFloatingpointLc3AudioParams->numBytes = 0;

        u1* outPtr = bleFloatingpointLc3AudioParams->bytes;

        /* Encode the data for as many channels as the source */
        for (int ich = 0; ich < bleFloatingpointLc3AudioParams->numChannels; ich++)
        {
            int frameBytes = bleFloatingpointLc3AudioParams->blockBytes / bleFloatingpointLc3AudioParams->numChannels + 
                             (ich < bleFloatingpointLc3AudioParams->blockBytes % bleFloatingpointLc3AudioParams->numChannels);

#if defined( CLX_LC3_PERFORMANCE_MEASUREMENT )
            clxLc3StartCpuUtilisationCapture( clxGetLc3EncoderCpuUtilisation() );
#endif /* defined( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

            ClxResult ret = clxFloatingpointLc3Encode(bleFloatingpointLc3AudioParams->enc[ich],
                                                      bleFloatingpointLc3AudioParams->pcmFormat,
                                                      bleFloatingpointLc3AudioParams->pcm + ich * bleFloatingpointLc3AudioParams->pcmBytes,
                                                      bleFloatingpointLc3AudioParams->numChannels,
                                                      frameBytes,
                                                      outPtr);

#if defined( CLX_LC3_PERFORMANCE_MEASUREMENT )
            clxLc3StopCpuUtilisationCapture( clxGetLc3EncoderCpuUtilisation() );
#endif /* defined( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

            bleFloatingpointLc3AudioParams->numBytes += frameBytes;
            outPtr += frameBytes;

            if (CLX_SUCCESS != ret)
            {
                clxConsoleUIEngineText("Encode failed: %s\n", clxGetErrorCodeText(ret));
            }
        }
    }

    return TRUE;
}


/**********************************************************************************************************************
*                                           bleFloatingpointLc3ResetNowPlayingTrack
*
* Reset variables to stop encoding/streaming the current sound track using Clarinox Floating Point LC3 codec implementation.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return void
*
***********************************************************************************************************************/
void bleFloatingpointLc3ResetNowPlayingTrack(BleLc3Encode* bleFloatingpointLc3AudioParams)
{
    bleFloatingpointLc3AudioParams->numberSamplesRead = 0;
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3IsEndOfNowPlayingTrack
*
* Returns if the current playing sound track is completed or not.
* Uses Clarinox Floating Point LC3 codec implementation.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return boolean                        - TRUE if ended and FALSE otherwise
*
***********************************************************************************************************************/
boolean bleFloatingpointLc3IsEndOfNowPlayingTrack(BleLc3Encode* bleFloatingpointLc3AudioParams)
{
    return !bleFloatingpointLc3AudioParams->numberSamplesRead;
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3GetEncodedDataBytes
*
* Returns the encoded LC3 bytes along with the total size of the encoded data.
* Uses Clarinox Floating Point LC3 codec implementation.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param sizeOfEncodedData               - Size of encoded data bytes returned
*
* \return u1*                            - Encoded data bytes
*
***********************************************************************************************************************/
u1* bleFloatingpointLc3GetEncodedDataBytes(BleLc3Encode* bleFloatingpointLc3AudioParams, u4* sizeOfEncodedData)
{
    *sizeOfEncodedData = bleFloatingpointLc3AudioParams->numBytes;
    return bleFloatingpointLc3AudioParams->bytes;
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3GetEncodedDataSize
*
* Returns the number of encoded LC3 bytes using Clarinox Floating Point LC3 codec implementation.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return u4                             - Number of encoded data bytes
*
***********************************************************************************************************************/
u4 bleFloatingpointLc3GetEncodedDataSize(BleLc3Encode* bleFloatingpointLc3AudioParams)
{
    return bleFloatingpointLc3AudioParams->numBytes;
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3ResetEncodedDataSize
*
* Resets the number of encoded LC3 bytes using Clarinox Floating Point LC3 codec implementation.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return void
*
***********************************************************************************************************************/
void bleFloatingpointLc3ResetEncodedDataSize(BleLc3Encode* bleFloatingpointLc3AudioParams)
{
    bleFloatingpointLc3AudioParams->numBytes = 0;
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3InitDecoder
*
* Initialize Clarinox Floating Point LC3 codec implementation like setting up encoder/decoder, etc.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param sampleRate                      - Sample rate in Hz, 8000, 16000, 24000, 32000, 48000 or 96000
* \param frameDuration      -              Frame duration in us, 2500, 5000, 7500 or 10000
* \param bitRate                         - Target bitrate in bit per second
* \param noOfChannels       -              The number of channels (or frames) in the block (<= 8)
*
* \return boolean           -              TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleFloatingpointLc3InitDecoder(BleLc3Decode* bleFloatingpointLc3AudioParams,
                                       int           sampleRate,
                                       int           frameDuration,
                                       int           bitDepth,
                                       s2            noOfChannels)
{
    clxConsoleUIEngineText("Initializing Floating Point LC3 Decoder..\n");

    boolean ret = TRUE;

    if (FALSE == bleFloatingpointLc3AudioParams->isLc3Intialized)
    {
        bleFloatingpointLc3AudioParams->sampleRate       = sampleRate;
        bleFloatingpointLc3AudioParams->frameDuration    = frameDuration;
        bleFloatingpointLc3AudioParams->bitDepth         = bitDepth;
        bleFloatingpointLc3AudioParams->noOfChannels     = noOfChannels;
        bleFloatingpointLc3AudioParams->pcmFormat        = ClxFloatingpointLc3PcmFormat_S16; //TODO to be obtained from adv config params
        bleFloatingpointLc3AudioParams->frameSamples     = clxFloatingpointLc3GetFrameSamples(bleFloatingpointLc3AudioParams->frameDuration, bleFloatingpointLc3AudioParams->sampleRate);

        /* Bit Depth passed to this function is not correct */
#if 0
        bleFloatingpointLc3AudioParams->pcmFormat        = (bitDepth == 32 ) ? ClxFloatingpointLc3PcmFormat_S24 : \
                                                  (bitDepth == 24 ) ? ClxFloatingpointLc3PcmFormat_3LE : ClxFloatingpointLc3PcmFormat_S16;
#endif

        bleFloatingpointLc3AudioParams->decodedBufferSize    = (2 * clxFloatingpointLc3GetMaxFrameSamples() * 4);

#if defined( CLX_LC3_PERFORMANCE_MEASUREMENT )
        clxLc3CpuUtilisationInfo* lc3CpuUtil = clxGetLc3DecoderCpuUtilisation();

        if( lc3CpuUtil )
        {
            lc3CpuUtil->currentAudioFileName            = (s1*)CLX_BLE_AUDIO_INPUT_FILE_1;
            lc3CpuUtil->currentAudioFileDurationInSec   = CLX_BLE_AUDIO_INPUT_FILE_1_DURATION_IN_SEC;
        }
#endif /* defined( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

        clxConsoleUIEngineText("\nLC3 Decode Init params: SampleRate[%d] FrameDuration[%d] bitDepth[%d] No.OF.Channels[%d]\n",
                                  bleFloatingpointLc3AudioParams->sampleRate,
                                  bleFloatingpointLc3AudioParams->frameDuration,
                                  bleFloatingpointLc3AudioParams->bitDepth,
                                  bleFloatingpointLc3AudioParams->noOfChannels);

        clxConsoleUIEngineText("PCM Format[%d] Decoded Buffer Size[%d]\n", 
                                 bleFloatingpointLc3AudioParams->pcmFormat, 
                                 bleFloatingpointLc3AudioParams->decodedBufferSize);

        bleFloatingpointLc3AudioParams->decodedBuffer    = (u1*)clxAppAllocZero( bleFloatingpointLc3AudioParams->decodedBufferSize );

        for (int ich = 0; ich < bleFloatingpointLc3AudioParams->noOfChannels; ich++)
        {
            bleFloatingpointLc3AudioParams->memory[ich] = clxAppAllocZero( clxFloatingpointLc3GetDecoderSize(bleFloatingpointLc3AudioParams->frameDuration, bleFloatingpointLc3AudioParams->sampleRate) );
        
            bleFloatingpointLc3AudioParams->dec[ich] = clxFloatingpointLc3SetupDecoder(bleFloatingpointLc3AudioParams->frameDuration,
                                                                                       bleFloatingpointLc3AudioParams->sampleRate,
                                                                                       bleFloatingpointLc3AudioParams->memory[ich]);
            if (!bleFloatingpointLc3AudioParams->dec[ich])
            {
                clxConsoleUIEngineText( "\nLC3 Decoder initialization failed\n" );
                ret = FALSE;
                break;
            }
        }

        if (FALSE == ret)
        {
            bleFloatingpointLc3DeinitDecoder(bleFloatingpointLc3AudioParams);
        }
        else
        {
            bleFloatingpointLc3AudioParams->isLc3Intialized = TRUE;
        }
    }

    clxConsoleUIEngineText("Initializing Floating Point LC3 Decoder......COMPLETED\n");

    return TRUE;
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3DeinitDecoder
*
* De-Initialize Clarinox Floating Point LC3 codec implementation like freeing up buffers and other resources, etc.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return boolean           -              TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleFloatingpointLc3DeinitDecoder(BleLc3Decode* bleFloatingpointLc3AudioParams)
{
    clxConsoleUIEngineText("De-Initializing Floating Point LC3..\n");

    if (bleFloatingpointLc3AudioParams->isLc3Intialized)
    {
        for (int ich = 0; ich < bleFloatingpointLc3AudioParams->noOfChannels; ich++)
        {
            /* The following variable previously held a reference to bleFloatingpointLc3AudioParams->memory */
            bleFloatingpointLc3AudioParams->dec[ich] = NULL;

            if (bleFloatingpointLc3AudioParams->memory[ich])
            {
                clxPoolsetFree( bleFloatingpointLc3AudioParams->memory[ich] );
                bleFloatingpointLc3AudioParams->memory[ich] = NULL;
            }
        }

        if (bleFloatingpointLc3AudioParams->decodedBuffer)
        {
            clxPoolsetFree( bleFloatingpointLc3AudioParams->decodedBuffer );
            bleFloatingpointLc3AudioParams->decodedBuffer = NULL;
        }

        bleFloatingpointLc3AudioParams->isLc3Intialized = FALSE;
    }

    clxConsoleUIEngineText("De-Initializing Floating Point LC3... ...COMPLETED\n");
    return TRUE;
}

/**********************************************************************************************************************
*                                           bleFloatingpointLc3DecodeStream
*
* Decode encoded LC3 bytes to pcm data using Clarinox Floating Point LC3 codec implementation.
*
* \param bleFloatingpointLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param data                            - Data received from encoder
* \param dataLength                        Length of the received encoded data
* \param decodedData                     - Output decoded data
* \param decodedDataSize                 - Output size of the decoded data
*
* \return boolean                        - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleFloatingpointLc3DecodeStream(BleLc3Decode* bleFloatingpointLc3AudioParams, const u1* data, u2 dataLength, s4** decodedData, u4* decodedDataSize)
{
    boolean ret     = TRUE;
    s4 funcRet      = FALSE;
    s4 pcmBytes     = 0;

    if( FALSE == bleFloatingpointLc3AudioParams->isLc3Intialized )
    {
        return FALSE;
    }

    memset(bleFloatingpointLc3AudioParams->decodedBuffer, 0, bleFloatingpointLc3AudioParams->decodedBufferSize);
    *decodedDataSize = 0;

    pcmBytes = (bleFloatingpointLc3AudioParams->bitDepth / 8);
    const u1* inPtr = data;

    for (int ich = 0; ich < bleFloatingpointLc3AudioParams->noOfChannels; ich++)
    {
        int frameBytes = dataLength / bleFloatingpointLc3AudioParams->noOfChannels + 
                         (ich < dataLength % bleFloatingpointLc3AudioParams->noOfChannels);

        funcRet = clxFloatingpointLc3Decode(bleFloatingpointLc3AudioParams->dec[ich],
                                        inPtr,
                                        frameBytes,
                                        bleFloatingpointLc3AudioParams->pcmFormat,
                                        bleFloatingpointLc3AudioParams->decodedBuffer + ich * pcmBytes,
                                        bleFloatingpointLc3AudioParams->noOfChannels);

        inPtr += frameBytes;
        
        if (0 != funcRet)
        {
            clxConsoleUIEngineText("Decode failed\n");
            if (TRUE == ret)
            {
                ret = FALSE;
            }
        }
    }

    *decodedData = (s4*)bleFloatingpointLc3AudioParams->decodedBuffer;
    *decodedDataSize = bleFloatingpointLc3AudioParams->frameSamples;

    return ret;
}

#endif /* CLX_FLOATINGPOINT_LC3 */

#endif /* CLX_BLE_ISOCHRONOUS */

