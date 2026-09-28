/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                BleLc3Common.cpp
* Description         This file BLE audio LC3 related APIs
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
#if defined( CLX_LC3_PERFORMANCE_MEASUREMENT )
#include "CodecCpuUtilisation.h"
#include "LC3.Test.h"
#endif /* defined( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

#include "BleIso.h"

/**********************************************************************************************************************
*                                           bleLc3InitStreamParams
*
* Initialize Clarinox LC3 codec parameters.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return void
*
***********************************************************************************************************************/
void bleLc3InitStreamParams (BleLc3Encode* bleLc3AudioParams)
{
    if (NULL == bleLc3AudioParams)
    {
        return;
    }

#if !defined(CLX_FLOATINGPOINT_LC3)
    clxConsoleUIEngineText("Initializing LC3 Parameters..\n");

    bleLc3AudioParams->sampleRate            = CLX_BLE_AUDIO_SAMPLING_FREQUENCIES_VALUE;
    bleLc3AudioParams->frameDuration         = CLX_BLE_AUDIO_FRAME_DURATION;
    bleLc3AudioParams->bitRate               = getBitrate();
    bleLc3AudioParams->numChannels           = CLX_BLE_AUDIO_NUMBER_OF_CHANNELS;

    bleLc3AudioParams->numberSamplesRead     = 0;

    bleLc3AudioParams->bytes                 = NULL;
    bleLc3AudioParams->numBytes              = 0;

    bleLc3AudioParams->frameBuffer           = NULL;
    bleLc3AudioParams->frameBufferBytes      = 0;

    memset ( &bleLc3AudioParams->lc3Encoder, 0x00, sizeof(ClxFixedpointLc3Encoder) );
    bleLc3AudioParams->inputWav              = NULL;

#else /* !CLX_FLOATINGPOINT_LC3 */
    bleFloatingpointLc3InitStreamParams(bleLc3AudioParams);
#endif /* !CLX_FLOATINGPOINT_LC3 */

    return;
}

/**********************************************************************************************************************
*                                           bleLc3InitEncoder
*
* Initialize Clarinox LC3 codec implementation like setting up encoder/decoder, etc.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param trackName          - Name of the sound track that has to be streamed from source to sink
*
* \return boolean           - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleLc3InitEncoder (BleLc3Encode* bleLc3AudioParams, const s1* trackName )
{
    boolean returnSts = FALSE;

    if ((NULL == bleLc3AudioParams) || (NULL == trackName))
    {
        return returnSts;
    }

#if defined ( CLX_LC3_PERFORMANCE_MEASUREMENT )
    if ( NULL == clxInitializeLc3EncoderCpuUtilisation ( ) )
    {
        clxConsoleUIEngineText("Initializing LC3 Encoder CPU Utilisation: FAIL\n");
    }
#endif /* defined ( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

#if !defined(CLX_FLOATINGPOINT_LC3)
    ClxFixedpointLc3Encoder* lc3Encoder   = &bleLc3AudioParams->lc3Encoder;
    u4 numberOfSamplesPerFrame            = 0;
    s2 bipsIn                             = 0;

    clxConsoleUIEngineText("Initializing LC3 Encoder..\n");

    bleLc3AudioParams->inputWav = OpenWav(trackName,
                                          (u4*)&bleLc3AudioParams->sampleRate,
                                          &bleLc3AudioParams->numChannels,
                                          &bleLc3AudioParams->numSamplesFile,
                                          &bipsIn);

    if ( NULL == bleLc3AudioParams->inputWav )
    {
        clxConsoleUIEngineText("\nUnable to open %s audio file\n", trackName);
        return returnSts;
    }

    clxConsoleUIEngineText("\n LC3 Encode Init params #%s {SampleRate[%u]:FrameDuration[%u]:BitRate[%u]:No.OF.Channels[%u]:bitDepth[%u]}\n",
                              trackName,
                              bleLc3AudioParams->sampleRate, 
                              bleLc3AudioParams->frameDuration, 
                              bleLc3AudioParams->bitRate, 
                              bleLc3AudioParams->numChannels,
                              bipsIn );

    returnSts = clxInitFixedpointLc3Encoder( lc3Encoder,
                                             bleLc3AudioParams->sampleRate,
                                             bleLc3AudioParams->frameDuration,
                                             bleLc3AudioParams->bitRate,
                                             bleLc3AudioParams->numChannels );

    if ( returnSts )
    {
#define LC3_MAX_BYTES        400

        numberOfSamplesPerFrame               = lc3Encoder->channels * lc3Encoder->frameLength;
        bleLc3AudioParams->frameBufferBytes   = sizeof(s4) * numberOfSamplesPerFrame;

        bleLc3AudioParams->bytes              = (u1*)clxAppAllocZero(LC3_MAX_BYTES);
        bleLc3AudioParams->frameBuffer        = (s4*)clxAppAllocZero(sizeof(s4) * numberOfSamplesPerFrame);

        if ( NULL == bleLc3AudioParams->frameBuffer || NULL == bleLc3AudioParams->bytes )
        {
            clxConsoleUIEngineText("\nBLE Audio Encode Buffer Allocation Failed\n");
            return returnSts;
        }

    }

    clxConsoleUIEngineText("Initializing LC3 Encoder... ...COMPLETED\n");

#else /* !CLX_FLOATINGPOINT_LC3 */
    returnSts = bleFloatingpointLc3InitStream(bleLc3AudioParams, trackName);
#endif /* !CLX_FLOATINGPOINT_LC3 */

    return returnSts;
}

/**********************************************************************************************************************
*                                           bleLc3DeinitEncoder
*
* De-Initialize Clarinox LC3 codec implementation like freeing up buffers and other resources, etc.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return boolean           - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleLc3DeinitEncoder (BleLc3Encode* bleLc3AudioParams)
{
    boolean returnSts = FALSE;

    if (NULL == bleLc3AudioParams)
    {
        return returnSts;
    }

#if !defined(CLX_FLOATINGPOINT_LC3)
    if ( bleLc3AudioParams->inputWav )
    {
        /* Close Wav input and bitstream output file */
        CloseWavIn(bleLc3AudioParams->inputWav);
    }

    if ( bleLc3AudioParams->frameBuffer )
    {
        clxPoolsetFree(bleLc3AudioParams->frameBuffer);
    }

    if ( bleLc3AudioParams->bytes )
    {
        clxPoolsetFree(bleLc3AudioParams->bytes);
    }

    bleLc3AudioParams->inputWav         = NULL;
    bleLc3AudioParams->frameBuffer      = NULL;
    bleLc3AudioParams->bytes            = NULL;
    bleLc3AudioParams->numBytes         = 0;
    bleLc3AudioParams->frameBufferBytes = 0;

    returnSts = TRUE;

#else /* !CLX_FLOATINGPOINT_LC3 */
    returnSts = bleFloatingpointLc3DeinitStream(bleLc3AudioParams);
#endif /* !CLX_FLOATINGPOINT_LC3 */

#if defined ( CLX_LC3_PERFORMANCE_MEASUREMENT )
    clxDestroyLc3EncoderCpuUtilisation();
#endif /* defined ( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

    return returnSts;
}

/**********************************************************************************************************************
*                                           bleLc3EncodeStream
*
* Encode pcm data to encoded LC3 bytes using Clarinox LC3 codec implementation.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param isPsuedoEncode     - Specifies if pcm data to be encoded or return dummy bytes
*
* \return boolean           - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleLc3EncodeStream(BleLc3Encode* bleLc3AudioParams, boolean isPsuedoEncode)
{
    boolean returnSts = FALSE;

    if (NULL == bleLc3AudioParams)
    {
        return returnSts;
    }

#if !defined(CLX_FLOATINGPOINT_LC3)
    if ( NULL == bleLc3AudioParams->frameBuffer )
    {
        clxConsoleUIEngineText("\nBLE Audio Frame Buffer Not Yet Allocated\n");
        return returnSts;
    }

    memset ( bleLc3AudioParams->frameBuffer, 0x00, bleLc3AudioParams->frameBufferBytes );

    ClxFixedpointLc3Encoder* lc3Encoder   = &bleLc3AudioParams->lc3Encoder;

    /* 
     * To avoid the issue of audio stopping on the remote device, send dummy (zero-filled) packets during non-play states. 
     * So read the wav file only When in the Play state condition 
     */
    if ( FALSE == isPsuedoEncode )
    {
        ReadWavInt( bleLc3AudioParams->inputWav,
                    bleLc3AudioParams->frameBuffer,
                    (lc3Encoder->channels * lc3Encoder->frameLength),
                    &bleLc3AudioParams->numberSamplesRead );
    }

#if defined ( CLX_LC3_PERFORMANCE_MEASUREMENT )
    clxLc3StartCpuUtilisationCapture ( clxGetLc3EncoderCpuUtilisation() );
#endif /* defined ( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

    bleLc3AudioParams->numBytes = clxFixedpointLc3Encode ( lc3Encoder,
                                                           bleLc3AudioParams->bytes,
                                                           (s4*)bleLc3AudioParams->frameBuffer );
#if defined ( CLX_LC3_PERFORMANCE_MEASUREMENT )
    clxLc3StopCpuUtilisationCapture ( clxGetLc3EncoderCpuUtilisation() );
#endif /* defined ( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

    if ( ! bleLc3AudioParams->numBytes )
    {
        return returnSts;
    }
    returnSts = TRUE;

#else /* !CLX_FLOATINGPOINT_LC3 */
    returnSts = bleFloatingpointLc3EncodeStream(bleLc3AudioParams, isPsuedoEncode);
#endif /* !CLX_FLOATINGPOINT_LC3 */

    return returnSts;
}

/**********************************************************************************************************************
*                                           bleLc3ResetNowPlayingTrack
*
* Reset variables to stop encoding/streaming the current sound track using Clarinox LC3 codec implementation.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return void
*
***********************************************************************************************************************/
void bleLc3ResetNowPlayingTrack(BleLc3Encode* bleLc3AudioParams)
{
    if (NULL == bleLc3AudioParams)
    {
        return;
    }

#if !defined(CLX_FLOATINGPOINT_LC3)
    bleLc3AudioParams->numberSamplesRead = 0;
#else
    bleFloatingpointLc3ResetNowPlayingTrack(bleLc3AudioParams);
#endif /* !CLX_FLOATINGPOINT_LC3 */
}

/**********************************************************************************************************************
*                                           bleLc3IsEndOfNowPlayingTrack
*
* Returns if the current playing sound track is completed or not.
* Uses Clarinox LC3 codec implementation.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return boolean           - TRUE if ended and FALSE otherwise
*
***********************************************************************************************************************/
boolean bleLc3IsEndOfNowPlayingTrack(BleLc3Encode* bleLc3AudioParams)
{
    boolean ret = TRUE;

    if (NULL == bleLc3AudioParams)
    {
        return ret;
    }

#if !defined(CLX_FLOATINGPOINT_LC3)
    ret = !bleLc3AudioParams->numberSamplesRead;
#else
    ret = bleFloatingpointLc3IsEndOfNowPlayingTrack(bleLc3AudioParams);
#endif /* !CLX_FLOATINGPOINT_LC3 */

    return ret;
}

/**********************************************************************************************************************
*                                           bleLc3GetEncodedDataBytes
*
* Returns the encoded LC3 bytes along with the total size of the encoded data.
* Uses Clarinox LC3 codec implementation.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param sizeOfEncodedData  - Size of encoded data bytes returned
*
* \return u1*               - Encoded data bytes
*
***********************************************************************************************************************/
u1* bleLc3GetEncodedDataBytes(BleLc3Encode* bleLc3AudioParams, u4* sizeOfEncodedData)
{
    u1* ret = NULL;
    if ((NULL == bleLc3AudioParams) || (NULL == sizeOfEncodedData))
    {
        return ret;
    }

#if !defined(CLX_FLOATINGPOINT_LC3)
    *sizeOfEncodedData = bleLc3AudioParams->numBytes;
    ret = bleLc3AudioParams->bytes;
#else
    ret = bleFloatingpointLc3GetEncodedDataBytes(bleLc3AudioParams, sizeOfEncodedData);
#endif /* !CLX_FLOATINGPOINT_LC3 */

    return ret;
}

/**********************************************************************************************************************
*                                           bleLc3GetEncodedDataSize
*
* Returns the number of encoded LC3 bytes using Clarinox LC3 codec implementation.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return u4                - Number of encoded data bytes
*
***********************************************************************************************************************/
u4 bleLc3GetEncodedDataSize(BleLc3Encode* bleLc3AudioParams)
{
    u4 ret = 0;

    if (NULL == bleLc3AudioParams)
    {
        return ret;
    }

#if !defined(CLX_FLOATINGPOINT_LC3)
    ret = bleLc3AudioParams->numBytes;
#else
    ret = bleFloatingpointLc3GetEncodedDataSize(bleLc3AudioParams);
#endif /* !CLX_FLOATINGPOINT_LC3 */

    return ret;
}

/**********************************************************************************************************************
*                                           bleLc3ResetEncodedDataSize
*
* Resets the number of encoded LC3 bytes using Clarinox LC3 codec implementation.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return void
*
***********************************************************************************************************************/
void bleLc3ResetEncodedDataSize(BleLc3Encode* bleLc3AudioParams)
{
    if (NULL == bleLc3AudioParams)
    {
        return;
    }


#if !defined(CLX_FLOATINGPOINT_LC3)
    bleLc3AudioParams->numBytes = 0;
#else
    bleFloatingpointLc3ResetEncodedDataSize(bleLc3AudioParams);
#endif /* !CLX_FLOATINGPOINT_LC3 */
}

/**********************************************************************************************************************
*                                           bleLc3InitDecoder
*
* Initialize Clarinox LC3 codec implementation like setting up encoder/decoder, etc.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param sampleRate         - Sample rate in Hz, 8000, 16000, 24000, 32000, 48000 or 96000
* \param frameDuration      - Frame duration 75 or 100
* \param bitRate            - Target bitrate in bit per second
* \param noOfChannels       - The number of channels (or frames) in the block (<= 8)
*
* \return boolean           - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleLc3InitDecoder (BleLc3Decode*    bleLc3AudioParams,
                           s4               sampleRate,
                           u4               frameDuration,
                           s4               bitRate,
                           s2               noOfChannels)
{
    boolean returnSts = FALSE;

    if (NULL == bleLc3AudioParams)
    {
        return returnSts;
    }

#if defined ( CLX_LC3_PERFORMANCE_MEASUREMENT )
    if ( NULL == clxInitializeLc3DecoderCpuUtilisation ( ) )
    {
        clxConsoleUIEngineText("Initializing LC3 Decoder CPU Utilisation: FAIL\n");
    }
#endif /* defined ( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

#if !defined(CLX_FLOATINGPOINT_LC3)
    if (NULL == bleLc3AudioParams->lc3Decoder)
    {
        clxConsoleUIEngineText("Initializing LC3 Decoder..\n");

        bleLc3AudioParams->sampleRate       = sampleRate;
        bleLc3AudioParams->frameDuration    = frameDuration;
        bleLc3AudioParams->bitRate          = bitRate;
        bleLc3AudioParams->noOfChannels     = noOfChannels;

#if defined ( CLX_LC3_PERFORMANCE_MEASUREMENT )
        clxLc3CpuUtilisationInfo* lc3CpuUtil = clxGetLc3DecoderCpuUtilisation();

        if ( lc3CpuUtil )
        {
            lc3CpuUtil->currentAudioFileName            = (s1*)CLX_BLE_AUDIO_INPUT_FILE_1;
            lc3CpuUtil->currentAudioFileDurationInSec   = CLX_BLE_AUDIO_INPUT_FILE_1_DURATION_IN_SEC;
        }
#endif /* defined ( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

        bleLc3AudioParams->lc3Decoder       = (ClxFixedpointLc3Decoder*)clxAppAllocZero(sizeof(ClxFixedpointLc3Decoder));

        if( NULL == bleLc3AudioParams->lc3Decoder )
        {
            clxConsoleUIEngineText("Initializing LC3 Decoder.Failed.\n");
            return returnSts;
        }

        clxConsoleUIEngineText("\nLC3 Decode Init params {SampleRate[%d]:FrameDuration[%u]:BitRate[%u]:No.OF.Channels[%u]}\n",
                                  bleLc3AudioParams->sampleRate,
                                  bleLc3AudioParams->frameDuration,
                                  bleLc3AudioParams->bitRate,
                                  bleLc3AudioParams->noOfChannels);

        clxInitFixedpointLc3Decoder(bleLc3AudioParams->lc3Decoder,
                                    bleLc3AudioParams->sampleRate,
                                    bleLc3AudioParams->frameDuration,
                                    bleLc3AudioParams->bitRate,
                                    bleLc3AudioParams->noOfChannels);

        bleLc3AudioParams->decodedBufferSize = (sizeof(s4) * bleLc3AudioParams->lc3Decoder->channels * bleLc3AudioParams->lc3Decoder->frame_Length);

        bleLc3AudioParams->decodedBuffer     = (s4*)clxAppAllocZero(bleLc3AudioParams->decodedBufferSize);

        bleLc3AudioParams->noOfChannels      = bleLc3AudioParams->lc3Decoder->channels;
        returnSts = TRUE;

        bleLc3AudioParams->isLc3Intialized = TRUE;

        clxConsoleUIEngineText("Initializing LC3 Decoder... ...COMPLETED\n");
    }
#else /* !CLX_FLOATINGPOINT_LC3 */
	(void)bitRate;
    returnSts = bleFloatingpointLc3InitDecoder(bleLc3AudioParams, sampleRate, (frameDuration*100), CLX_BLE_RECEIVER_PCM_BIT_DEPTH, noOfChannels);
#endif /* !CLX_FLOATINGPOINT_LC3 */

    return returnSts;
}

/**********************************************************************************************************************
*                                           bleLc3DeinitDecoder
*
* De-Initialize Clarinox LC3 codec implementation like freeing up buffers and other resources, etc.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
*
* \return boolean           - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleLc3DeinitDecoder (BleLc3Decode* bleLc3AudioParams)
{
    boolean returnSts = FALSE;

    if (NULL == bleLc3AudioParams)
    {
        return returnSts;
    }

#if defined ( CLX_LC3_PERFORMANCE_MEASUREMENT )
    clxDestroyLc3DecoderCpuUtilisation();
#endif /* defined ( CLX_LC3_PERFORMANCE_MEASUREMENT ) */

#if !defined(CLX_FLOATINGPOINT_LC3)
    if ( bleLc3AudioParams->decodedBuffer )
    {
        clxPoolsetFree(bleLc3AudioParams->decodedBuffer);
        bleLc3AudioParams->decodedBuffer = NULL;
    }

    if ( bleLc3AudioParams->lc3Decoder )
    {
        clxPoolsetFree(bleLc3AudioParams->lc3Decoder);
        bleLc3AudioParams->lc3Decoder = NULL;
    }

    returnSts = TRUE;
#else /* !CLX_FLOATINGPOINT_LC3 */
    returnSts = bleFloatingpointLc3DeinitDecoder(bleLc3AudioParams);
#endif /* !CLX_FLOATINGPOINT_LC3 */

    bleLc3AudioParams->isLc3Intialized = FALSE;

    return returnSts;
}

/**********************************************************************************************************************
*                                           bleLc3DecodeStream
*
* Decode encoded LC3 bytes to pcm data using Clarinox LC3 codec implementation.
*
* \param bleLc3AudioParams  - Structure consisting of parameters required by LC3 interfacing implementation
* \param data               - Data received from encoder
* \param dataLength         - Length of the received encoded data
* \param decodedData        - Output decoded data
* \param decodedDataSize    - Output size of the decoded data
*
* \return boolean           - TRUE if success and FALSE in case of errors
*
***********************************************************************************************************************/
boolean bleLc3DecodeStream(BleLc3Decode* bleLc3AudioParams, const u1* data, u2 dataLength, s4** decodedData, u4* decodedDataSize)
{
    boolean returnSts = FALSE;

    if ((NULL == bleLc3AudioParams) || (NULL == decodedData) || (NULL == data) || (NULL == decodedDataSize))
    {
        return returnSts;
    }

    if( 0 == dataLength )
    {
        clxConsoleUIEngineText("\n###ERROR### Encode Data Invalid\n");
        return returnSts;
    }

#if !defined(CLX_FLOATINGPOINT_LC3)
    if (bleLc3AudioParams->lc3Decoder && bleLc3AudioParams->decodedBuffer)
    {
        clxFixedpointLc3Decode(bleLc3AudioParams->lc3Decoder, (u1*)data, bleLc3AudioParams->decodedBuffer, dataLength, 0, 16);
        *decodedData = bleLc3AudioParams->decodedBuffer;
        *decodedDataSize = (sizeof(s4) * bleLc3AudioParams->noOfChannels * bleLc3AudioParams->lc3Decoder->frame_Length);

        returnSts = TRUE;
    }
#else /* !CLX_FLOATINGPOINT_LC3 */
    returnSts = bleFloatingpointLc3DecodeStream(bleLc3AudioParams, data, dataLength, decodedData, decodedDataSize);
#endif /* !CLX_FLOATINGPOINT_LC3 */

    return returnSts;
}

#endif /* CLX_BLE_ISOCHRONOUS */

