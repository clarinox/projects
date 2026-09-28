#ifndef __Ble_Lc3_Common_h__
#define __Ble_Lc3_Common_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                BleLc3Common.h
* Description         Declares ClarinoxBlue LE LC3 Audio Common declarations.
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if defined(CLX_FLOATINGPOINT_LC3)
#include "FloatingpointLc3.h"
#endif /* defined(CLX_FLOATINGPOINT_LC3) */
#include "FixedpointLc3.h"
#include "Wav.h"

#if defined(CLX_BLE_ISOCHRONOUS)

/* Structure consisting of all the necessary parameters required for LC3 encoding */
typedef struct BleLc3EncodeStruct
{
    boolean isLc3Intialized;
    s4  sampleRate;                              /*!< Sampling Frequency rate for LC3 codec encode */
    s4  bitRate;                                 /*!< Bitrate for LC3 codec encode */
    s2  numChannels;                             /*!< Number of channels for LC3 codec encode */
    u4  numSamplesFile;
    u4  numberSamplesRead;                       /*!< Audio size read from Wav */
    u4  numBytes;                                /*!< Buffer size of Encoded Audio data */

#if !defined(CLX_FLOATINGPOINT_LC3)
    u4                        frameDuration;     /*!< Frame Duration for LC3 codec encode */
    u1*                       bytes;             /*!< Buffer to hod the Encoded Audio data */
    s4*                       frameBuffer;       /*!< Frame Buffer to hod the raw Audio data before encode */
    u4                        frameBufferBytes;  /*!< Actual Frame Buffer size of raw Audio data */
    ClxFixedpointLc3Encoder   lc3Encoder;        /*!< Encoder handle */
    WAVEFILEIN*               inputWav;          /*!< Wav file reference */

#else
    s4  blockBytes;
    s4  frameBytes;
    s4  frameSamples;
    s4  encodeSamples;
    s4  hrmode;
    s4  encoderSize;
    void* encoderMemory[ CLX_BLE_AUDIO_MAX_NUMBER_OF_CHANNELS ];

    s4  pcmBits;
    s4  pcmBytes;
    s4  frameDuration;
    FILE *fp_in;

    s4  maxPcmBytesSize;
    s4  maxEncodedBytesSize;

    ClxFloatingpointLc3PcmFormat  pcmFormat;
    u1  *pcm;
    u1  *bytes;

    ClxFloatingpointLc3Encoder enc[ CLX_BLE_AUDIO_MAX_NUMBER_OF_CHANNELS ];
#endif /* !CLX_FLOATINGPOINT_LC3 */
}BleLc3Encode;

/* Structure consisting of all the necessary parameters required for LC3 decoding */
typedef struct BleLc3DecodeStruct
{
    boolean                         isLc3Intialized;
    s4                              sampleRate;
    s2                              noOfChannels;
    s4                              decodedBufferSize;

#if !defined(CLX_FLOATINGPOINT_LC3)
    u4                              frameDuration;
    s4                              bitRate;
    ClxFixedpointLc3Decoder*        lc3Decoder;
    s4*                             decodedBuffer;
#else
    s4                              frameDuration;
    s4                              frameSamples;
    s4                              bitDepth;
    void*                           memory[CLX_BLE_AUDIO_MAX_NUMBER_OF_CHANNELS];
    ClxFloatingpointLc3PcmFormat    pcmFormat;
    ClxFloatingpointLc3Decoder      dec[CLX_BLE_AUDIO_MAX_NUMBER_OF_CHANNELS];
    u1*                             decodedBuffer;
#endif /* !CLX_FLOATINGPOINT_LC3 */

}BleLc3Decode;

/* Functions declared implementing current Clarinox LC3 Codec */
void bleLc3InitStreamParams (BleLc3Encode* bleLc3AudioParams);

boolean bleLc3InitEncoder (BleLc3Encode* bleLc3AudioParams, const s1* trackName);

boolean bleLc3DeinitEncoder (BleLc3Encode* bleLc3AudioParams);

boolean bleLc3EncodeStream(BleLc3Encode* bleLc3AudioParams, boolean isPsuedoEncode);

void bleLc3ResetNowPlayingTrack(BleLc3Encode* bleLc3AudioParams);

boolean bleLc3IsEndOfNowPlayingTrack(BleLc3Encode* bleLc3AudioParams);

u1* bleLc3GetEncodedDataBytes(BleLc3Encode* bleLc3AudioParams, u4* sizeOfEncodedData);

u4 bleLc3GetEncodedDataSize(BleLc3Encode* bleLc3AudioParams);

void bleLc3ResetEncodedDataSize(BleLc3Encode* bleLc3AudioParams);

boolean bleLc3InitDecoder (BleLc3Decode*    bleLc3AudioParams,
                           s4               sampleRate,
                           u4               frameDuration,
                           s4               bitRate,
                           s2               noOfChannels);

boolean bleLc3DeinitDecoder(BleLc3Decode* bleLc3AudioParams);

boolean bleLc3DecodeStream(BleLc3Decode* bleLc3AudioParams, const u1* data, u2 dataLength, s4** decodedData, u4* decodedDataSize);

#if defined(CLX_FLOATINGPOINT_LC3)

/* Functions declared implementing Floating Point LC3 Codec */
void bleFloatingpointLc3InitStreamParams(BleLc3Encode* bleFloatingpointLc3AudioParams);

boolean bleFloatingpointLc3InitStream(BleLc3Encode* bleFloatingpointLc3AudioParams, const s1* trackName);

boolean bleFloatingpointLc3DeinitStream(BleLc3Encode* bleFloatingpointLc3AudioParams);

boolean bleFloatingpointLc3EncodeStream(BleLc3Encode* bleFloatingpointLc3AudioParams, boolean isPsuedoEncode);

void bleFloatingpointLc3ResetNowPlayingTrack(BleLc3Encode* bleFloatingpointLc3AudioParams);

boolean bleFloatingpointLc3IsEndOfNowPlayingTrack(BleLc3Encode* bleFloatingpointLc3AudioParams);

u1* bleFloatingpointLc3GetEncodedDataBytes(BleLc3Encode* bleFloatingpointLc3AudioParams, u4* sizeOfEncodedData);

u4 bleFloatingpointLc3GetEncodedDataSize(BleLc3Encode* bleFloatingpointLc3AudioParams);

void bleFloatingpointLc3ResetEncodedDataSize(BleLc3Encode* bleFloatingpointLc3AudioParams);

boolean bleFloatingpointLc3InitDecoder(BleLc3Decode* bleFloatingpointLc3AudioParams,
                                       s4            sampleRate,
                                       s4            frameDuration,
                                       s4            bitDepth,
                                       s2            noOfChannels);

boolean bleFloatingpointLc3DeinitDecoder(BleLc3Decode* bleFloatingpointLc3AudioParams);

boolean bleFloatingpointLc3DecodeStream(BleLc3Decode* bleFloatingpointLc3AudioParams, const u1* data, u2 dataLength,
                                        s4** decodedData, u4* decodedDataSize);

#endif /* CLX_FLOATINGPOINT_LC3 */

#endif /* CLX_BLE_ISOCHRONOUS */

#endif /* __Ble_Lc3_Common_h__ */

