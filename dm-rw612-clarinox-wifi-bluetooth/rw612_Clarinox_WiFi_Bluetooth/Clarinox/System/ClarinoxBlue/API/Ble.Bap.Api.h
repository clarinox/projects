#ifndef __Ble_Bap_Api_h__
#define __Ble_Bap_Api_h__

/*******************************************************************************
*
* Project             Clarinox Bluetooth Low Energy Audio
* File                Ble.Bap.Api.h
* Description         Declares API Functions,Definitions For Basic Audio Profile
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
Use this to initialize u1 or 8-bit fields when the value is unset or invalid in BLE BAP structures.
*/
#define CLX_BAP_INVALID_FIELD_U8                                                            (0xFF)

/**
Use this to initialize u2 or 16-bit fields when the value is unset or invalid in BLE BAP structures.
*/
#define CLX_BAP_INVALID_FIELD_U16                                                           (0xFFFF)

/**
Use this to initialize u4 or 32-bit fields when the value is unset or invalid in BLE BAP structures.
*/
#define CLX_BAP_INVALID_FIELD_U32                                                           (0xFFFFFFFF)

/**
Use this when explicitly clearing or resetting fields in BLE BAP structures.
*/
 #define CLX_BAP_NULL_BYTE                                                                   (0x00)

/**
Presentation delay length
*/
#define CLX_GATT_PRESENTATION_DELAY_LENGTH                                                  3   /* Bytes */

/**
Maximum LTV (Length-Type-Value) record length.
Total size includes 1 byte for the length field and up to 254 bytes for the record data.
*/
#define CLX_GATT_MAX_LTV_RECORD_LENGTH                                                      (1 + 254)    /* 1 byte for length + 254 bytes of data */

/**
BLE Audio Codec Specific Configuration LTV Structure Lengths
These macros define the lengths (in bytes) of various LTV structures used in BLE Audio codec-specific configurations.
*/
#define CLX_BAP_CODEC_SPECIFIC_CONFIG_SAMPLING_FREQUENCIES_LENGTH                           0x02
#define CLX_BAP_CODEC_SPECIFIC_CONFIG_FRAME_DURATIONS_LENGTH                                0x02
#define CLX_BAP_CODEC_SPECIFIC_CONFIG_AUDIO_CHANNEL_ALLOCATION_LENGTH                       0x05
#define CLX_BAP_CODEC_SPECIFIC_CONFIG_OCTETS_PER_CODEC_FRAME_LENGTH                         0x03
#define CLX_BAP_CODEC_SPECIFIC_CONFIG_CODEC_FRAMES_PER_SDU_LENGTH                           0x02

/**
BLE Audio Codec Capability Configuration LTV Structure Lengths
These macros define the lengths (in bytes) of various LTV structures used in BLE Audio codec capability configurations.
*/
#define CLX_BAP_CODEC_CAPABILITY_CONFIG_SAMPLING_FREQUENCIES_LENGTH                         0x03
#define CLX_BAP_CODEC_CAPABILITY_CONFIG_FRAME_DURATIONS_LENGTH                              0x02
#define CLX_BAP_CODEC_CAPABILITY_CONFIG_AUDIO_CHANNEL_COUNTS_LENGTH                         0x02
#define CLX_BAP_CODEC_CAPABILITY_CONFIG_OCTETS_PER_CODEC_FRAME_LENGTH                       0x05
#define CLX_BAP_CODEC_CAPABILITY_CONFIG_MAX_CODEC_FRAMES_PER_SDU_LENGTH                     0x02

/**
BLE Audio Metadata LTV Structure Lengths
These macros define the lengths (in bytes) of various LTV structures used in BLE Audio metadata fields.
*/
#define CLX_BAP_METADATA_PREFERRED_AUDIO_CONTEXTS_LENGTH                                    0x03
#define CLX_BAP_METADATA_STREAMING_AUDIO_CONTEXTS_LENGTH                                    0x03
#define CLX_BAP_METADATA_LANGUAGE_LENGTH                                                    0x04
#define CLX_BAP_METADATA_PARENTAL_RATING_LENGTH                                             0x02
#define CLX_BAP_METADATA_AUDIO_ACTIVE_STATE_LENGTH                                          0x02
#define CLX_BAP_METADATA_BROADCAST_AUDIO_IMMEDIATE_RENDERING_FLAG_LENGTH                    0x01
#define CLX_BAP_METADATA_ASSISTED_LISTENING_STREAM_LENGTH                                   0x02

/*====================================================ASCS====================================================*/
/**
Refer to #clxBapGetSinkAse function.
*/
#define CLX_BAP_GET_SINK_ASE_COMPLETE                                                       0x5f00

/**
Refer to #clxBapSetSinkAse function.
*/
#define CLX_BAP_SET_SINK_ASE_COMPLETE                                                       0x5f01

/**
Refer to #clxBapGetSourceAse function.
*/
#define CLX_BAP_GET_SOURCE_ASE_COMPLETE                                                     0x5f02

/**
Refer to #clxBapSetSourceAse function.
*/
#define CLX_BAP_SET_SOURCE_ASE_COMPLETE                                                     0x5f03

/**
Refer to #clxBapGetAseOpCode function.
*/
#define CLX_BAP_GET_ASE_OP_CODE_COMPLETE                                                    0x5f04

/**
Refer to #clxBapSetAseOpCode function.
*/
#define CLX_BAP_SET_ASE_OP_CODE_COMPLETE                                                    0x5f05

/*====================================================PACS====================================================*/
/**
Refer to #clxBapGetSinkPac function.
*/
#define CLX_BAP_GET_SINK_PAC_COMPLETE                                                       0x5f00

/**
Refer to #clxBapSetSinkPac function.
*/
#define CLX_BAP_SET_SINK_PAC_COMPLETE                                                       0x5f01

/**
Refer to #clxBapGetSinkAudioLocation function.
*/
#define CLX_BAP_GET_SINK_AUDIO_LOCATION_COMPLETE                                            0x5f02

/**
Refer to #clxBapSetSinkAudioLocation function.
*/
#define CLX_BAP_SET_SINK_AUDIO_LOCATION_COMPLETE                                            0x5f03

/**
Refer to #clxBapGetSourcePac function.
*/
#define CLX_BAP_GET_SOURCE_PAC_COMPLETE                                                     0x5f04

/**
Refer to #clxBapSetSourcePac function.
*/
#define CLX_BAP_SET_SOURCE_PAC_COMPLETE                                                     0x5f05

/**
Refer to #clxBapGetSourceAudioLocation function.
*/
#define CLX_BAP_GET_SOURCE_AUDIO_LOCATION_COMPLETE                                          0x5f06

/**
Refer to #clxBapSetSourceAudioLocation function.
*/
#define CLX_BAP_SET_SOURCE_AUDIO_LOCATION_COMPLETE                                          0x5f07

/**
Refer to #clxBapGetAvailableAudioContext function.
*/
#define CLX_BAP_GET_AVAILABLE_AUDIO_CONTEXT_COMPLETE                                        0x5f08

/**
Refer to #clxBapSetAvailableAudioContext function.
*/
#define CLX_BAP_SET_AVAILABLE_AUDIO_CONTEXT_COMPLETE                                        0x5f09

/**
Refer to #clxBapGetSupportedAudioContext function.
*/
#define CLX_BAP_GET_SUPPORTED_AUDIO_CONTEXT_COMPLETE                                        0x5f0a

/**
Refer to #clxBapSetSupportedAudioContext function.
*/
#define CLX_BAP_SET_SUPPORTED_AUDIO_CONTEXT_COMPLETE                                        0x5f0b

/*====================================================BASS====================================================*/

#define CLX_BAP_BASS_BAD_CODE_LENGTH                                                        16  /* Bytes */

#define CLX_BAP_BASS_BROADCAST_CODE_LENGTH                                                  16  /* Bytes */

/**
Refer to #clxBapGetBroadcastScanOpCode function.
*/
#define CLX_BAP_GET_BROADCAST_SCAN_OP_CODE_COMPLETE                                         0x5f00

/**
Refer to #clxBapSetBroadcastScanOpCode function.
*/
#define CLX_BAP_SET_BROADCAST_SCAN_OP_CODE_COMPLETE                                         0x5f01

/**
Refer to #clxBapGetBroadcastReceiveState function.
*/
#define CLX_BAP_GET_BROADCAST_RECEIVE_STATE_COMPLETE                                        0x5f02

/**
Refer to #clxBapSetBroadcastReceiveState function.
*/
#define CLX_BAP_SET_BROADCAST_RECEIVE_STATE_COMPLETE                                        0x5f03

/**
BLE audio BAP configuration type(Encode or Decode) enum
*/
typedef enum ClxBapConfigTypeEnum
{
    ClxBapConfigType_CodecConfig      = 0,                     /*!< Codec Specific Configuration data */
    ClxBapConfigType_CodecCapability,                          /*!< Codec Specific Capabilities data */
    ClxBapConfigType_MetaData,                                 /*!< BLE audio metadata LTV data */
}ClxBapConfigType;

/**
Enum representing valid codec sampling frequencies.
Used for BLE Audio Codec configuration.
*/
typedef enum ClxBapCodecSamplingFrequencyEnum
{
    ClxBapCodecSamplingFreq_INVALID   = CLX_BAP_NULL_BYTE,  /*!< Invalid or uninitialized value */
    ClxBapCodecSamplingFreq_8000Hz    = 0x01,
    ClxBapCodecSamplingFreq_11025Hz   = 0x02,
    ClxBapCodecSamplingFreq_16000Hz   = 0x03,
    ClxBapCodecSamplingFreq_22050Hz   = 0x04,
    ClxBapCodecSamplingFreq_24000Hz   = 0x05,
    ClxBapCodecSamplingFreq_32000Hz   = 0x06,
    ClxBapCodecSamplingFreq_44100Hz   = 0x07,
    ClxBapCodecSamplingFreq_48000Hz   = 0x08,
    ClxBapCodecSamplingFreq_88200Hz   = 0x09,
    ClxBapCodecSamplingFreq_96000Hz   = 0x0A,
    ClxBapCodecSamplingFreq_176400Hz  = 0x0B,
    ClxBapCodecSamplingFreq_192000Hz  = 0x0C,
    ClxBapCodecSamplingFreq_384000Hz  = 0x0D
} ClxBapCodecSamplingFrequency;

/**
Enum representing valid frame duration
Used for BLE Audio Codec configuration.
*/
typedef enum ClxBapCodecFrameDurationEnum
{
    ClxBapCodecFrameDuration_7_5_MS   = 0x00,
    ClxBapCodecFrameDuration_10_MS    = 0x01,
    ClxBapCodecFrameDuration_INVALID  = CLX_BAP_INVALID_FIELD_U8      /*!< Invalid or uninitialized value */
} ClxBapCodecFrameDuration;

/**
BLE audio Codec Specific Configuration structures types enum
*/
typedef enum ClxBapCodecConfigTypeEnum
{
    ClxBapCodecCfg_Invalid               = 0x00,                /*!< Invalid configuration type */
    ClxBapCodecCfg_SamplingFrequency     = 0x01,                /*!< Sampling Frequencies */
    ClxBapCodecCfg_FrameDuration         = 0x02,                /*!< Frame Durations */
    ClxBapCodecCfg_ChannelAllocation     = 0x03,                /*!< Audio Channel Allocation */
    ClxBapCodecCfg_OctetsPerFrame        = 0x04,                /*!< Octets per Codec Frame */
    ClxBapCodecCfg_FramesPerSDU          = 0x05                 /*!< Codec Frames per SDU */
} ClxBapCodecCfgType;

/**
BLE audio Codec Specific Capabilities structures types enum
*/
typedef enum ClxBapCodecCapabilitiesTypeEnum
{
    ClxBapCodecCap_Invalid               = 0x00,                /*!< Invalid capability type */
    ClxBapCodecCap_SamplingFrequency     = 0x01,                /*!< Supported Sampling Frequencies */
    ClxBapCodecCap_FrameDuration         = 0x02,                /*!< Supported Frame Durations */
    ClxBapCodecCap_ChannelCount          = 0x03,                /*!< Supported Audio Channel Counts */
    ClxBapCodecCap_OctetsPerFrame        = 0x04,                /*!< Supported Octets per Codec Frame */
    ClxBapCodecCap_MaxFramesPerSDU       = 0x05                 /*!< Supported Max Codec Frames per SDU */
} ClxBapCodecCapType;

/**
BLE audio Metadata structures types enum
*/
typedef enum ClxBapAudioMetadataTypeEnum
{
    ClxBapMetadataType_INVALID                     = 0x00,      /*!< Invalid or undefined metadata type */
    ClxBapMetadataType_PreferredAudioContexts      = 0x01,      /*!< Preferred audio contexts (Assigned Numbers) */
    ClxBapMetadataType_StreamingAudioContexts      = 0x02,      /*!< Streaming audio contexts (Assigned Numbers) */
    ClxBapMetadataType_ProgramInfo                 = 0x03,      /*!< Program information (Title/Summary in UTF-8 format) */
    ClxBapMetadataType_Language                    = 0x04,      /*!< Language code (3-byte ISO 639-3) */
    ClxBapMetadataType_CCIDList                    = 0x05,      /*!< List of CC Ids */
    ClxBapMetadataType_ParentalRating              = 0x06,      /*!< Parental rating */
    ClxBapMetadataType_ProgramInfoURI              = 0x07,      /*!< URI to program information (UTF-8 URL) */
    ClxBapMetadataType_AudioActivityState          = 0x08,      /*!< Audio activity state (0x00: No data, 0x01: Transmitting) */
    ClxBapMetadataType_BroadcastAudioImmediateFlag = 0x09,      /*!< Broadcast immediate rendering flag (0x01: Set, 0x00: Not set) */
    ClxBapMetadataType_AssistedListeningStream     = 0x0A,      /*!< Assisted Listening Stream (0x00 – unspecified audio enhancement) */
    ClxBapMetadataType_BroadcastName               = 0x0B,      /*!< The UTF-8 string of the Broadcast Name */
    ClxBapMetadataType_ExtendedMetadata            = 0xFE,      /*!< Extended metadata (custom structure) */
    ClxBapMetadataType_VendorspecificValue         = 0xFF       /*!< Extended metadata (custom structure) */
}ClxBapAudioMetadataType;

/**
ASE Control Point Operation
*/
typedef enum ClxBapAseOpCodeTypeEnum
{
    ClxBapAseOpCodeType_ConfigCodecOperation        = 0x01,     /*!< Config Codec operation */
    ClxBapAseOpCodeType_ConfigQosOperation,                     /*!< Config QoS operation */
    ClxBapAseOpCodeType_EnableOperation,                        /*!< Enable operation */
    ClxBapAseOpCodeType_ReceiverStartReadyOperation,            /*!< Receiver Start Ready operation */
    ClxBapAseOpCodeType_DisableOperation,                       /*!< Disable operation */
    ClxBapAseOpCodeType_ReceiverStopReadyOperation,             /*!< Receiver Stop Ready operation */
    ClxBapAseOpCodeType_UpdateMetadataOperation,                /*!< Update Metadata operation */
    ClxBapAseOpCodeType_ReleaseOperation                        /*!< Release operation */
}ClxBapAseOpCodeType;

/**
ASE states
*/
typedef enum ClxBapAudioEndpointStatesEnum
{
    ClxBapAEStates_Idle                 = 0x00,                 /*!< ASE at idle state */
    ClxBapAEStates_CodecConfigured      = 0x01,                 /*!< Codec configuration applied */
    ClxBapAEStates_QoSConfigured        = 0x02,                 /*!< Codec and QoS configuration applied */
    ClxBapAEStates_Enabling             = 0x03,                 /*!< Ready to stream */
    ClxBapAEStates_Streaming            = 0x04,                 /*!< Currently streaming audio data */
    ClxBapAEStates_Disabling            = 0x05,                 /*!< Source ASE decoupled from CIS */
    ClxBapAEStates_Releasing            = 0x06,                 /*!< All configuration reset, CIS disconnecting */
    ClxBapAEStates_Unknown
}ClxBapAudioEndpointStates;

/**
Audio contexts of supported Codec Capabilities
*/
typedef enum ClxBapAudioContextEnum
{
    ClxBapAudioContext_None              = 0x00000000,
    ClxBapAudioContext_Unspecified       = 0x00000001,
    ClxBapAudioContext_Conversational    = 0x00000002,
    ClxBapAudioContext_Media             = 0x00000004,
    ClxBapAudioContext_Game              = 0x00000008,
    ClxBapAudioContext_Instructional     = 0x00000010,
    ClxBapAudioContext_VoiceAssistants   = 0x00000020,
    ClxBapAudioContext_Live              = 0x00000040,
    ClxBapAudioContext_SoundEffects      = 0x00000080,
    ClxBapAudioContext_Notifications     = 0x00000100,
    ClxBapAudioContext_Ringtone          = 0x00000200,
    ClxBapAudioContext_Alerts            = 0x00000400,
    ClxBapAudioContext_EmergencyAlarm    = 0x00000800,
    ClxBapAudioContext_Reserved
}ClxBapAudioContext;

/**
Audio locations definitions for Codec Specific Configurations
*/
typedef enum ClxBapAudioLocationsEnum
{
    ClxBapAudioLocations_NotAllowed               = 0x00000000,
    ClxBapAudioLocations_FrontLeft                = 0x00000001,
    ClxBapAudioLocations_FrontRight               = 0x00000002,
    ClxBapAudioLocations_FrontCenter              = 0x00000004,
    ClxBapAudioLocations_LowFrequencyEffects_1    = 0x00000008,
    ClxBapAudioLocations_BackLeft                 = 0x00000010,
    ClxBapAudioLocations_BackRight                = 0x00000020,
    ClxBapAudioLocations_FrontLeftOfCenter        = 0x00000040,
    ClxBapAudioLocations_FrontRightOfCenter       = 0x00000080,
    ClxBapAudioLocations_BackCenter               = 0x00000100,
    ClxBapAudioLocations_LowFrequencyEffects_2    = 0x00000200,
    ClxBapAudioLocations_SideLeft                 = 0x00000400,
    ClxBapAudioLocations_SideRight                = 0x00000800,
    ClxBapAudioLocations_TopFrontLeft             = 0x00001000,
    ClxBapAudioLocations_TopFrontRight            = 0x00002000,
    ClxBapAudioLocations_TopFrontCenter           = 0x00004000,
    ClxBapAudioLocations_TopCenter                = 0x00008000,
    ClxBapAudioLocations_TopBackLeft              = 0x00010000,
    ClxBapAudioLocations_TopBackRight             = 0x00020000,
    ClxBapAudioLocations_TopSideLeft              = 0x00040000,
    ClxBapAudioLocations_TopSideRight             = 0x00080000,
    ClxBapAudioLocations_TopBackCenter            = 0x00100000,
    ClxBapAudioLocations_BottomFrontCenter        = 0x00200000,
    ClxBapAudioLocations_BottomFrontLeft          = 0x00400000,
    ClxBapAudioLocations_BottomFrontRight         = 0x00800000,
    ClxBapAudioLocations_FrontLeftWide            = 0x01000000,
    ClxBapAudioLocations_FrontRightWide           = 0x02000000,
    ClxBapAudioLocations_LeftSurround             = 0x04000000,
    ClxBapAudioLocations_RightSurround            = 0x08000000,
    ClxBapAudioLocations_RFU                      = 0x10000000
}ClxBapAudioLocations;

/**
Coding format of supported Codec Capabilities
*/
typedef enum CodingFormatEnum
{
    CodingFormat_SBC                    = 0x00,
    CodingFormat_MPEG_1_2_Audio         = 0x01,
    CodingFormat_MPEG_2_4_AAC           = 0x02,
    CodingFormat_Atrac                  = 0x04,
    CodingFormat_Others                 = 0xFF
} CodingFormat;

/**
Sampling frequency of supported Codec Capabilities
*/
typedef enum ClxBapSamplingFrequencyCapabilityEnum
{
    ClxBapCapabilitySamplingFreq_None          = 0x0000,
    ClxBapCapabilitySamplingFreq_8000Hz        = 0x0001,
    ClxBapCapabilitySamplingFreq_11025Hz       = 0x0002,
    ClxBapCapabilitySamplingFreq_16000Hz       = 0x0004,
    ClxBapCapabilitySamplingFreq_22050Hz       = 0x0008,
    ClxBapCapabilitySamplingFreq_24000Hz       = 0x0010,
    ClxBapCapabilitySamplingFreq_32000Hz       = 0x0020,
    ClxBapCapabilitySamplingFreq_44100Hz       = 0x0040,
    ClxBapCapabilitySamplingFreq_48000Hz       = 0x0080,
    ClxBapCapabilitySamplingFreq_88200Hz       = 0x0100,
    ClxBapCapabilitySamplingFreq_96000Hz       = 0x0200,
    ClxBapCapabilitySamplingFreq_176400Hz      = 0x0400,
    ClxBapCapabilitySamplingFreq_192000Hz      = 0x0800,
    ClxBapCapabilitySamplingFreq_384000Hz      = 0x1000
} ClxBapSamplingFrequencyCapability;

/**
Frame duration of supported Codec Capabilities
*/
typedef enum ClxFrameDurationCapabilityEnum
{
    ClxFrameDurationCap_None              = 0x0000,
    ClxFrameDurationCap_7_5ms             = 0x0001,
    ClxFrameDurationCap_10ms              = 0x0002,
    ClxFrameDurationCap_Reserved1         = 0x0004,
    ClxFrameDurationCap_Reserved2         = 0x0008,
    ClxFrameDurationCap_7_5ms_preferred   = 0x0010,
    ClxFrameDurationCap_10ms_preferred    = 0x0020,
    ClxFrameDurationCap_Reserved3         = 0x0040,
    ClxFrameDurationCap_Reserved4         = 0x0080
} ClxFrameDurationCapability;

/**
PDU Frame configuration of Codec Capabilities
*/
typedef enum BleAudioPduFramingEnum
{
    BleAudioPduFraming_UnframedIsoalSupported       = 0x00,
    BleAudioPduFraming_UnframedIsoalNotSupported    = 0x01
} BleAudioPduFraming;

/**
Target Latency configuration of supported Codec Capabilities
*/
typedef enum BleAudioTargetLatencyEnum
{
    BleAudioTargetLatency_LowLatency            = 0x01,
    BleAudioTargetLatency_Balanced              = 0x02,
    BleAudioTargetLatency_HighReliability       = 0x03
} BleAudioTargetLatency;

/**
Target PHY configuration of supported Codec Capabilities.
Values according to ASCS spec. If any changes to it, to be updated here
*/
typedef enum BleAudioTargetPhyEnum
{
    BleAudioTargetPhy_LE_1M         = 0x01,
    BleAudioTargetPhy_LE_2M         = 0x02,
    BleAudioTargetPhy_LE_Coded      = 0x03
} BleAudioTargetPhy;

/*
BLE BIG Encryption Code Status enum
*/
typedef enum ClxBapBIGEncryptionCodeStatusEnum
{
    ClxBapBIGEncryptionCodeStatus_NotEncrypted          = 0,    /* 0x00: Not encrypted */
    ClxBapBIGEncryptionCodeStatus_BroadcastCodeRequired,        /* 0x01: Broadcast_Code required */
    ClxBapBIGEncryptionCodeStatus_Decrypting,                   /* 0x02: Decrypting */
    ClxBapBIGEncryptionCodeStatus_BadCodeIncorrect              /* 0x03: Bad_Code (incorrect encryption key) */
}ClxBapBIGEncryptionCodeStatus;

/**
Broadcast Audio Scan Control Point Operation
*/
typedef enum ClxBapBassOpCodeTypeEnum
{
    ClxBapBassOpCode_RemoveScanStopped       = 0x00,            /*!< Remote Scan Stopped operation */
    ClxBapBassOpCode_RemoteScanStarted       = 0x01,            /*!< Remote Scan Started operation */
    ClxBapBassOpCode_AddSource               = 0x02,            /*!< Add Source operation */
    ClxBapBassOpCode_ModifySource            = 0x03,            /*!< Modify Source operation */
    ClxBapBassOpCode_SetBroadcastCode        = 0x04,            /*!< Set Broadcast_Code operation */
    ClxBapBassOpCode_RemoveSource            = 0x05,            /*!< Remove Source operation */
    ClxBapBassOpCode_Unknown                                    /*!< Reserved for future use */
}ClxBapBassOpCodeType;

/**
Generic audio codec specific configuration.
Each field must be initialized with valid values as per the BLE Audio specification.
Refer to the detailed comment next to each field for valid ranges and usage.
*/
typedef struct ClxBapCodecConfigStruct
{
    u1 samplingFrequency;                                       /*!< Sampling Frequency:
                                                                        Valid values:
                                                                            0x01 to 0x0D : ClxBapCodecSamplingFrequency
                                                                        Invalid/Initialized value: 0x00 (CLX_BAP_NULL_BYTE)
                                                                */
    u1 frameDuration;                                           /*!< Frame Duration:
                                                                        Valid values: as per ClxBapCodecFrameDuration
                                                                            0x00: 7.5 ms
                                                                            0x01: 10 ms
                                                                        Invalid/Initialized value: 0xFF (CLX_BAP_INVALID_FIELD_U8)
                                                                 */

    u4 channelAllocation;                                       /*!< Audio Channel Allocation:
                                                                        Bitfield representing channel positions.
                                                                        Valid combinations as per ClxBapAudioLocations
                                                                        Invalid/Initialized value: 0x00000000 (CLX_BAP_NULL_BYTE)
                                                                 */

    u2 frameLength;                                             /*!< Codec Frame Length:
                                                                        Specifies the length of the codec frame in octets.
                                                                        Valid range: 0x0001 to 0xFFFF
                                                                        Invalid/Initialized value: 0x0000 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 framesPerSdu;                                            /*!< Frame Blocks per SDU:
                                                                        Number of codec frames per SDU.
                                                                        Valid range: 0x01 to 0xFF
                                                                        Invalid/Initialized value: 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */
} ClxBapCodecConfig;

/**
Generic audio codec specific capabilities.
Each field must be initialized with valid values as per the BLE Audio specification.
Refer to the detailed comment next to each field for valid ranges and usage.
*/
typedef struct ClxBapCodecCapabilitiesStruct
{
    u2 supportedSamplingFrequencies;                            /*!< Sampling Frequency Capabilities:
                                                                        Bitfield representing supported frequencies.
                                                                        Each bit corresponds to a frequency as defined in the ClxBapSamplingFrequencyCapability.
                                                                        Invalid/Initialized value: 0x0000 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 supportedFrameDurations;                                 /*!< Frame Duration Capabilities:
                                                                        Bitfield representing supported frame durations as defined in the ClxFrameDurationCapability
                                                                        Bit 0: 7.5 ms
                                                                        Bit 1: 10 ms
                                                                        Invalid/Initialized value: 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 supportedChannelAllocations;                             /*!< Audio Channel Capabilities:
                                                                        Bitfield representing supported channel configurations.
                                                                        Valid combinations per Bluetooth specifications.
                                                                        Invalid/Initialized value: 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */

    u4 supportedFrameLengthRange;                               /*!< Codec Frame Length Capabilities:
                                                                        Specifies the range of supported codec frame lengths.
                                                                            Octet 0-1: Minimum number of octets supported per codec frame
                                                                            Octet 2-3: Maximum number of octets supportedper codec frame
                                                                        Valid range: 0x00000001 to 0xFFFFFFFF
                                                                        Invalid/Initialized value: 0x00000000 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 supportedSduIntervals;                                   /*!< SDU Interval Capabilities:
                                                                        Specifies supported SDU intervals.
                                                                        Valid values is maximum number of codec frames per SDU supported by this device
                                                                        Invalid/Initialized value: 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */
} ClxBapCodecCapabilities;

/**
Generic audio metadata LTV structures
Each field must be initialized with valid values as per the BLE Audio specification.
Refer to the detailed comment next to each field for valid ranges and usage.
*/
typedef struct ClxBapAudioMetadataLtvStruct
{
    u2 preferredAudioContexts;                                  /*!< Preferred Audio Contexts:
                                                                       Bitfield representing preferred audio contexts.
                                                                       Each bit corresponds to a context as defined in the ClxBapAudioContext.
                                                                       Invalid/Initialized value: 0x0000 (CLX_BAP_NULL_BYTE)
                                                                 */

    u2 streamingAudioContexts;                                  /*!< Streaming Audio Contexts:
                                                                       Bitfield representing streaming audio contexts.
                                                                       Each bit corresponds to a context as defined in the ClxBapAudioContext.
                                                                       Invalid/Initialized value: 0x0000 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 programTitle[CLX_GATT_MAX_LTV_RECORD_LENGTH];            /*!< Program Information:
                                                                        UTF-8 encoded title or summary of the audio stream.
                                                                        Index 0 indicates the actual length of the program info.
                                                                        Invalid/Initialized value: Index 0 = 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 languageCode[3];                                         /*!< Language Code:
                                                                       3-byte lowercase language code as per ISO 639-3 standard.
                                                                       Example: 'eng' for English.
                                                                       Invalid/Initialized value: All bytes = 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 ccIDList[CLX_GATT_MAX_LTV_RECORD_LENGTH];                /*!< Content Control Identifier (CCID) List:
                                                                       List of CCIDs.
                                                                       Index 0 indicates the actual length of the list.
                                                                       Invalid/Initialized value: Index 0 = 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 parentalRating;                                          /*!< Parental Rating:
                                                                       0x00: No rating
                                                                       0x01: Suitable for all ages
                                                                       0x02–0x0F: Refer to "EN 300 707 v1.2.1" for detailed rating definitions
                                                                       0x10–0xFF: Reserved
                                                                       Invalid/Initialized value: 0xFF (CLX_BAP_INVALID_FIELD_U8)
                                                                 */

    u1 programInfoURI[CLX_GATT_MAX_LTV_RECORD_LENGTH];          /*!< Program Information URI:
                                                                       UTF-8 encoded URL pointing to additional program information.
                                                                       Index 0 indicates the actual length of the URL.
                                                                       Invalid/Initialized value: Index 0 = 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 audioActivityState;                                      /*!< Audio Activity State:
                                                                       0x00: No audio data is being transmitted
                                                                       0x01: Audio data is being transmitted
                                                                       Invalid/Initialized value: 0xFF (CLX_BAP_INVALID_FIELD_U8)
                                                                 */

    u1 broadcastAudioImmediateFlag;                             /*!< Broadcast Audio Immediate Rendering Flag:
                                                                        0x00: Immediate rendering not required
                                                                        0x01: Immediate rendering required
                                                                        Invalid/Initialized value: 0xFF (CLX_BAP_INVALID_FIELD_U8)
                                                                 */

    u1 assistedListeningType;                                   /*!< Assisted Listening Stream:
                                                                        0x00: Unspecified audio enhancement
                                                                        0x01–0xFF: Reserved
                                                                        Invalid/Initialized value: 0xFF (CLX_BAP_INVALID_FIELD_U8)
                                                                 */

    u1 broadcastName[CLX_GATT_MAX_LTV_RECORD_LENGTH];           /*!< Broadcast Name:
                                                                         UTF-8 encoded broadcast name.
                                                                         Index 0 indicates the actual length of the name.
                                                                         Invalid/Initialized value: Index 0 = 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 extendedMetadataLtv[CLX_GATT_MAX_LTV_RECORD_LENGTH];     /*!< Extended Metadata:
                                                                        Octet 0: Length of extended metadata
                                                                        Octets 1–2: Extended metadata type
                                                                        Octets 3–254: Extended metadata content
                                                                        Invalid/Initialized value: Octet 0 = 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */

    u1 vendorMetadataLtv[CLX_GATT_MAX_LTV_RECORD_LENGTH];       /*!< Vendor-Specific Metadata:
                                                                        Octet 0: Length of vendor-specific metadata
                                                                        Octets 1–2: Company ID (Bluetooth Assigned Numbers)
                                                                        Octets 3–254: Vendor-specific metadata content
                                                                        Invalid/Initialized value: Octet 0 = 0x00 (CLX_BAP_NULL_BYTE)
                                                                 */
}ClxBapAudioMetadataLtv;

/**
Audio stream endpoint codec configuration
*/
typedef struct ClxBapAseServerCodecConfigurationStruct
{
    u1                  framing;                                /*!< Server support for unframed - 0x00:Supported, 0x01:Not supported */
    u1                  preferredPhy;                           /*!< Server preferred value for the PHY parameter. 0x00 - No preference
                                                                       0b00000001 - LE 1M PHY, 0b00000010 - LE 2M PHY, 0b00000100 - LE coded PHY */
    u1                  preferredRetransmissionNum;             /*!< Server preferred value for the Retransmission_Number parameter. Range - 0x00 - 0xFF */
    u2                  maxTransportLatency;                    /*!< Server preferred value for the max transport latency parameter. Range - 0x0005 - 0x0FA0 */
    u4                  presentationDelayMin;                   /*!< Minimum server supported Presentation Delay for this ASE */
    u4                  presentationDelayMax;                   /*!< Maximum server supported Presentation Delay for this ASE */
    u4                  preferredPresentationDelayMin;          /*!< Server preferred minimum Presentation Delay for this ASE */
    u4                  preferredPresentationDelayMax;          /*!< Server preferred maximum Presentation Delay for this ASE */
    ClxBluetoothCodec   codecId;                                /*!< Coding Format values are defined in Bluetooth Assigned Numbers */
    u1                  codecSpecificConfigLength;              /*!< Length of the ASE codec specific configuration */
    ClxBapCodecConfig   aseCodecSpecificConfig;                 /*!< Codec specific configuration for this ASE */
}ClxBapAseServerCodecConfig;

/**
Audio stream endpoint QoS configuration
*/
typedef struct ClxBapAseQosConfigurationStruct
{
    u1 cigId;                                                   /*!< The CIG_ID value is written by client for the qos operation */
    u1 cisId;                                                   /*!< The CIS_ID value is written by client for the qos operation */
    u4 sduInterval;                                             /*!< The SDU_Interval value is written by client for the qos operation */
    u1 framing;                                                 /*!< The Framing value is written by client for the qos operation */
    u1 phy;                                                     /*!< The Phy value is written by client for the qos operation */
    u1 retransmissionNum;                                       /*!< The retransmission number value written by client for the qos operation */
    u2 maxSdu;                                                  /*!< The max SDU parameter value is written by client for the qos operation */
    u2 maxTransportLatency;                                     /*!< The max transport latency parameter value is written by client for the qos operation */
    u4 presentationDelay;                                       /*!< Presentation delay parameter value is written by client for the qos operation */
}ClxBapAseServerQosConfiguration;

/**
Audio stream endpoint additional parameter field when ASE state enabling(0x03), streaming(0x04), or disabling(0x05)
*/
typedef struct ClxBapAseOtherConfigStruct
{
    u1                       cigId;                             /*!< CIG_ID parameter value for this ASE */
    u1                       cisId;                             /*!< CIS_ID parameter value for this ASE */
    ClxBapAudioMetadataLtv*  metadata;                          /*!< ASE metadata values */
}ClxBapAseServerOtherConfig;

/**
Audio stream endpoint characteristic structure for both Source and Sink.
*/
typedef struct ClxBleBapAudioStreamEndpointStruct
{
    u1                              aseId;                      /*!< ASE id assigned by the server */
    u1                              aseState;                   /*!< State of the audio stream endpoint with respect to the ASE state machine. Value: 0x00 - 0x06 */
    ClxBapAseServerCodecConfig      codec;                      /*!< Codec configuration format for this ASE */
    ClxBapAseServerQosConfiguration qosConfig;                  /*!< Qos configuaration format for this ASE */
    ClxBapAseServerOtherConfig      aseOthersStates;            /*!< Additional state params format for this ASE */
}ClxBapAudioStreamEndpoint;

/**
The ASE control point config codec operation structure
*/
typedef struct ClxBapAseClientOpCodeConfigCodecOperationStruct
{
    u1                  aseId;                                  /*!< Ase id for the ASE */
    u1                  targetLatency;                          /*!< Provides context for the server to return meaningful values for QoS preferences */
    u1                  targetPhy;                              /*!< PHY parameter target to achieve the Target_Latency value */
    ClxBluetoothCodec   codecId;                                /*!< Coding Format values are defined in Bluetooth Assigned Numbers */
    ClxBapCodecConfig   codecSpecificConfig;                    /*!< Codec specific configuration for this ASE */
}ClxBapAseClientOpCodeConfigCodec;

/**
The ASE control point config qos operation structure
*/
typedef struct ClxBapAseClientOpCodeConfigQosOperationStruct
{
    u1 aseId;                                                   /*!< ID for this ASE */
    u1 cigId;                                                   /*!< CIG_ID value is written by the client for this ASE */
    u1 cisId;                                                   /*!< CIS_ID value is written by the client for this ASE */
    u4 sduInterval;                                             /*!< SDU interval is written by the client for this ASE */
    u1 framing;                                                 /*!< Framing value is written by the client for this ASE */
    u1 phy;                                                     /*!< PHY value is written by the client for this ASE */
    u1 retransmissionNum;                                       /*!< Retransmission param value is written by the client for this ASE */
    u2 maxSdu;                                                  /*!< Max SDU param wriiten by the client for this ASE */
    u2 maxTransportLatency;                                     /*!< Max transport latency param value is written by the client for this ASE */
    u4 presentationDelay;                                       /*!< Presentation delay param value is written by the client for this ASE */
}ClxBapAseClientOpCodeConfigQos;

/**
The ASE control point enable operation structure
*/
typedef struct ClxBapAseClientOpCodeEnableOperationStruct
{
    u1                       aseId;                             /*!< ASE id for this ASE */
    ClxBapAudioMetadataLtv   metadata;                          /*!< ASE metadata values */
}ClxBapAseClientOpCodeEnable;

/**
The ASE control point receiver start ready operation structure
*/
typedef struct ClxBapAseClientOpCodeReceiverStartReadyOperationStruct
{
    u1 aseId;                                                  /*!< ASE id for the receiver ready operation */
}ClxBapAseClientOpCodeReceiverStartReady;

/**
The ASE control point disable operation structure
*/
typedef struct ClxBapAseClientOpCodeDisableOperationStruct
{
    u1 aseId;                                                  /*!< ASE id for the disable operation */
}ClxBapAseClientOpCodeDisable;

/**
The ASE control point receiver stop ready structure
*/
typedef struct ClxBapAseClientOpCodeReceiverStopReadyOperationStruct
{
    u1 aseId;                                                  /*!< ASE id for the receiver stop ready operation */
}ClxBapAseClientOpCodeReceiverStopReady;

/**
The ASE control point update metadata operation structure
*/
typedef struct ClxBapAseClientOpCodeUpdateMetadataOperationStruct
{
    u1                       aseId;                            /*!< ASE id for the metadata operation */
    ClxBapAudioMetadataLtv   metadata;                         /*!< ASE metadata values */
}ClxBapAseClientOpCodeUpdateMetadata;

/**
The ASE control point release operation structure
*/
typedef struct ClxBapAseClientOpCodeReleaseOperationStruct
{
    u1 aseId;                                                  /*!< ASE id for the release operation */
}ClxBapAseClientOpCodeRelease;

/**
The ASE control point operations
*/
typedef struct ClxAseOpCodeInfoStruct
{
    ClxBapAseClientOpCodeConfigCodec        configCodec;       /*!< Config codec format for the control point config codec operation */
    ClxBapAseClientOpCodeConfigQos          configQos;         /*!< Config QoS format for the control point config qos operation */
    ClxBapAseClientOpCodeEnable             enable;            /*!< State enabling format for control point state enabling operation */
    ClxBapAseClientOpCodeReceiverStartReady receiverReady;     /*!< Receiver start ready format for control point receiver start ready operation */
    ClxBapAseClientOpCodeDisable            stateDisable;      /*!< Disable state format for control point disable operation */
    ClxBapAseClientOpCodeReceiverStopReady  receiverStop;      /*!< Receiver stop ready operation format for control point receiver stop ready operation */
    ClxBapAseClientOpCodeUpdateMetadata     updateMetadata;    /*!< Update metadata format for control point update metadata operation */
    ClxBapAseClientOpCodeRelease            releaseOperation;  /*!< Release operation format for control point release operation */
}ClxAseOpCodeInfo;

/**
The ASE control point operation structure
*/
typedef struct ClxBapAseOpCodeStruct
{
    u1                          opcode;                    /*!< Opcode is used by the server to determine the ASE control operation is being initiated by the client */
    u1                          numberOfAses;              /*!< Total number of ASE ids used for the ASE operations */
    ClxAseOpCodeInfo*           opCodeInfo;                /*!< ASE control point operations for all ASEs */
}ClxBapAseOpCode;

/**
Structure representing a single PAC (Published Audio Capabilities) record for Sink and Source characteristics.
*/
typedef struct ClxBapSinglePacRecordStruct
{
    ClxBluetoothCodec         codecId;                        /*!< Codec information for the corresponding PAC
                                                                   Octet 0  : Coding_Format
                                                                   Octet 1–2: Company ID
                                                                   Octet 3–4: Vendor-specific codec_ID
                                                               */
    ClxBapCodecCapabilities   capabilities;                   /*!< Codec Capabilities parameters. */
    ClxBapAudioMetadataLtv    metadata;                       /*!< Metadata parameters for the current PAC record */
}ClxBapSinglePacRecord;

/**
Structure holding multiple PAC records.
*/
typedef struct ClxBapPacRecordsStruct
{
    /* Number of PAC records */
    u1                       numberOfPacRecords;              /*!< Number of PAC records available.*/
    ClxBapSinglePacRecord*   pacRecords;                      /*!< Pointer to an array of PAC records. */
}ClxBapPacRecords;

/**
Audio Locations characteristic structure for Sink and Source role
*/
typedef struct ClxBapPacAudioLocationsStruct
{
    u4 pacAudioLocations;                                     /*!< Supported audio location are defined in ClxBapAudioLocations */
}ClxBapPacAudioLocations;

/**
Available Audio Contexts characteristic structure
*/
typedef struct ClxBapPacAvailableAudioContextStruct
{
    u2 sinkContentAvailability;                               /*!< Audio data context type values available for reception */
    u2 sourceContentAvailability;                             /*!< Audio data Context Type values available for transmission */
}ClxBapPacAvailableAudioContext;

/**
Supported Audio Contexts characteristic structure
*/
typedef struct ClxBapPacSupportedAudioContextStruct
{
    u2 supportedSinkContext;                                  /*!< Audio data context type values for reception */
    u2 supportedSourceContext;                                /*!< Audio data context type values supported for transmission */
}ClxBapPacSupportedAudioContext;

/**
Structure for Add Source operation in Broadcast audio scan control point.
*/
typedef struct ClxBapBasAddSourceStruct
{
    u1  advertiserAddrType;                                     /*!< Broadcast source address type:
                                                                       0x00 - Public identity,
                                                                       0x01 - Random identity,
                                                                       Others - RFU 
                                                                 */
    u1  advertiserAddr[CLX_BLE_GAP_ADDRESS_VALUE_LENGTH];       /*!< Broadcast source advertiser address */
    u1  advertisingSid;                                         /*!< Advertising SID */
    u4  broadcastId;                                            /*!< Broadcast ID identifying the source */
    u1  paSync;                                                 /*!< Periodic Advertising sync option:
                                                                       0x01 - Sync with PAST,
                                                                       0x02 - Sync without PAST 
                                                                 */
    u2  paInterval;                                             /*!< Periodic Advertising interval value from SyncInfo */
    u1  numSubgroups;                                           /*!< Number of subgroups in BIG */
    u4* bisSyncState;                                           /*!< BIS sync bitmask array:
                                                                       Bit 0–30: BIS index 1–31;
                                                                       0x00 - Do not sync,
                                                                       0x01 - Sync,
                                                                       0xFF - No preference 
                                                                 */
    ClxBapAudioMetadataLtv* metadata;                           /*!< Pointer to metadata array (LTV format) per subgroup */
} ClxBapBasAddSource;

/**
Structure for Modify Source operation in Broadcast audio scan control point.
*/
typedef struct ClxBapBasModifySourceStruct
{
    u1  sourceId;                                               /*!< Server-assigned source ID */
    u1  paSync;                                                 /*!< Sync/unsync request:
                                                                       0x00 - Do not sync,
                                                                       0x01 - Sync 
                                                                 */
    u2  paInterval;                                             /*!< Periodic Advertising interval value */
    u1  numSubgroups;                                           /*!< Number of subgroups */
    u4* bisSyncState;                                           /*!< BIS sync bitmask array:
                                                                       Bit 0–30: BIS index 1–31;
                                                                       0x00 - Do not sync,
                                                                       0x01 - Sync,
                                                                       0xFF - No preference 
                                                                 */
    ClxBapAudioMetadataLtv* metadata;                           /*!< Pointer to metadata array (LTV format) per subgroup */
}ClxBapBasModifySource;

/**
Structure for Set Broadcast Code operation in Broadcast audio scan control point.
*/
typedef struct ClxBapBasSetBroadcastCodeStruct
{
    u1 sourceId;                                                /*!< Server-assigned source ID */
    u1 broadcastCode[CLX_BAP_BASS_BROADCAST_CODE_LENGTH];       /*!< 16-byte broadcast code for decryption */
}ClxBapBasSetBroadcastCode;

/**
Structure for Remove Source operation in Broadcast audio scan control point.
*/
typedef struct ClxBapBasRemoveSourceStruct
{
    u1 sourceId;                                                /*!< Server-assigned source ID */
}ClxBapBasRemoveSource;

/**
Control Point structure containing all possible Broadcast Audio Scan Control Point operations(Op Code).
*/
typedef struct ClxBapBroadcastScanOpCode
{
    u1 opcode;                                                  /*!< Control operation code(opcode) as ClxBapBassOpCodeType */
    union {
        ClxBapBasAddSource           addSource;                 /*!< Add source request */
        ClxBapBasModifySource        modifySource;              /*!< Modify source request */
        ClxBapBasSetBroadcastCode    setBroadcastCode;          /*!< Set broadcast code */
        ClxBapBasRemoveSource        removeSource;              /*!< Remove source */
    } procedure;
}ClxBapBroadcastScanOpCode;

/**
Structure representing the Broadcast Receive State characteristic.
*/
typedef struct ClxBapBroadcastReceiveStateStruct
{
    u1  sourceId;                                               /*!< Server-assigned source ID */
    u1  sourceAddrType;                                         /*!< Broadcast source address type */
    u1  sourceAddr[CLX_BLE_GAP_ADDRESS_VALUE_LENGTH];           /*!< Broadcast source address */
    u1  sourceAdvSid;                                           /*!< Advertising SID */
    u4  broadcastId;                                            /*!< Broadcast ID */
    u1  paSyncState;                                            /*!< PA sync state:
                                                                       0x00 - Not synchronized,
                                                                       0x01 - SyncInfo requested,
                                                                       0x02 - Synchronized,
                                                                       0x03 - Sync failed,
                                                                       0x04 - No PAST,
                                                                       Others - RFU 
                                                                 */
    u1  bigEncryptionState;                                     /*!< BIG encryption state: as ClxBapBIGEncryptionCodeStatus
                                                                       0x00 - Not encrypted,
                                                                       0x01 - Code required,
                                                                       0x02 - Decrypting,
                                                                       0x03 - Bad code,
                                                                       Others - RFU 
                                                                 */
    u1  badCode[CLX_BAP_BASS_BAD_CODE_LENGTH];                  /*!< Last failed broadcast code (if bigEncryptionState is Bad code(0x030)) */
    u1  numSubgroups;                                           /*!< Number of subgroups */
    u4* bisSyncState;                                           /*!< BIS sync bitmask array:
                                                                       Bit 0–30: BIS index 1–31;
                                                                       0x00 - Do not sync,
                                                                       0x01 - Sync,
                                                                       0xFF - No preference 
                                                                 */
    ClxBapAudioMetadataLtv* metadata;                           /*!< Pointer to metadata array (LTV format) per subgroup */
}ClxBapBroadcastReceiveState;

/**
Genreric strcuture for BLE Broadcast audio configuration data encode or decode
*/
typedef struct ClxBapBroadcastAudioConfigurationInfoStruct
{
    ClxBapConfigType                configDataType;           /*!< Configuration type enum */

    union
    {
        ClxBapCodecConfig           codecConfig;              /*!< Codec Specific Configuration data */
        ClxBapCodecCapabilities     codecCapablilty;          /*!< Codec Specific Capabilities data */
        ClxBapAudioMetadataLtv      metadata;                 /*!< BLE audio metadata LTV data */
    }Config;                                                  /*!< Variable to pass the BLE Configuration Info */
}ClxBapBroadcastAudioConfigInfo;

/**
Level 3: BIS level data based on the number of BIS field 
*/
typedef struct ClxBleAudioBISSpecificCodecInfoStruct
{
    u1                  bisIndex;                                        /*!< BIS_index value for the current BIS in the corresponding subgroup */
    ClxBapCodecConfig   codecInfoForBISSpecific;                         /*!< Codec-specific configuration parameters for the current BIS in the corresponding subgroup */
}ClxBleAudioBISSpecificCodecInfo;

/**
Level 2: Subgroup level. A subgroup is a collection of one or more BISes present in the BIG. 
*/
typedef struct ClxBleAudioBISSubGroupStruct
{
    u1                                  numberOfBIS;                   /*!< Number of BIS is used into the subgroup in the BIG Shall be at least 1 as defined as the Basic Audio Profile Specification(3.7.2.2 Basic Audio Announcements) */

    ClxBluetoothCodec                   codecId;                       /*!< Codec information for the corresponding BIG subgroup
                                                                            Octet 0  : Coding_Format
                                                                            Octet 1–2: Company ID
                                                                            Octet 3–4: Vendor-specific codec_ID
                                                                        */
    ClxBapCodecConfig                   codecInfoForSubGrpSpecific;    /*!< Codec-specific configuration parameters for the current subgroup */
    ClxBapAudioMetadataLtv              metadata;                      /*!< Metadata parameters for the current subgroup */
    ClxBleAudioBISSpecificCodecInfo*    bisSpecificInfo;               /*!< Level 3: BIS level data based on the number of BIS field */
}ClxBleAudioBISSubGroup;

/**
BIG Information for a Synchronized Receiver to synchronize to a BIG that is being broadcast by an Isochronous Broadcaster.
BIG info fields are defined in Volume 6, Part B, Section 4.4.6.11 in core specification 
 */
typedef struct ClxBleAudioUserBigInfoStruct
{
    u2    bigOffset;
    u2    isoInterval;

    u1    bigOffsetUnits;
    u1    numberOfBIS;
    u1    numberOfSubEvent;
    u1    burstNumber;

    u4    subInterval;
    u4    bisSpacing;

    u1    pto;
    u1    irc;
    u1    maxPDU;
    u1    rfu;

    u4    seedAccessAddress;
    u4    sduInterval;

    u2    maxSDU;
    u2    baseCRCInit;

    u1    chM [ 5 ];
    u1    phy;
    u1    framing;
    u1    giv;

    u1    bisPayloadCount [ 5 ];
    u2    gskd;
}ClxBleAudioUserBigInfo;

/**
Basic Audio Announcements used to expose broadcast Audio Stream parameters used for the Broadcast Periodic extended advertising data.
Level 1: Group level. The BIG is the group.
Level 2: Subgroup level. A subgroup is a collection of one or more BISes present in the BIG.
Level 3: BIS level.
*/
typedef struct ClxBleAudioBISBasicAudioAnnoucementConfigInfoStruct
{
    u2           serviceUUID;                                              /*!< Basic Audio Announcement Service UUID. Its defined in the Bluetooth Assigned Numbers */
    u1           presentationDelay [ CLX_GATT_PRESENTATION_DELAY_LENGTH ]; /*!< Configure the Presentation delay as based on the Basic Audio Profile Specification(Section 7) */
    u1           numberOfSubGrp;                                           /*!< Number of subgroups used to group BISes present in the BIG Shall be at least 1 as defined as the Basic Audio Profile Specification(3.7.2.2 Basic Audio Announcements) */
    ClxBleAudioBISSubGroup* subGrp;                                        /*!< Level 2: Subgroup level. A subgroup is a collection of one or more BISes present in the BIG. */

    boolean                            bigInfoAvailStatus;                 /*!< Flag to know the BIG Information available or not */
    ClxBleAudioUserBigInfo             bigInfo;                            /*!< Define BIG Information (Option data)*/
}ClxBleAudioBISBasicAudioAnnouncement;

/**
Adds the Broadcast Audio Announcement data into extended advertising.

\param[  in   ] broadcastID        User-provided Broadcast ID to be encoded into the Broadcast Source extended advertising data.
\param[  out  ] extAdvDataObj      Extended advertising data structure to store the encoded Broadcast ID.

\return                            #CLX_SUCCESS: successful encoding
                                   #CLX_ERROR_INVALID_COMMAND_PARAMETER: One or more of provided arguments are invalid.
*/
ClxResult clxBapAddBroadcastAudioAnnouncement(_in_       u4                              broadcastID,
                                              _user_out_ ClxBleExtendedAdvertisingData*  extAdvDataObj);

/**
Decode and find the Broadcast Audio Announcement UUID data from the Broadcast Source extended advertising data based on the Basic Audio Profile.

\param[  out  ] broadcastID        Decoded and filled Broadcast ID from the extended advertising data.
\param[  in   ] payload            Extended advertising payload
\param[  in   ] payloadLength      Length of the extended advertising payload in bytes.

\return                            #CLX_SUCCESS: Successful decoding
                                   #CLX_FAIL: Failed
                                   #CLX_ERROR_INVALID_COMMAND_PARAMETER: One or more of provided arguments are invalid.
*/
ClxResult clxBapFindBroadcastAudioAnnouncement(_user_out_ u4*        broadcastID,
                                               _user_in_  const u1*  payload,
                                               _in_       const u1   payloadLength);

/**
Adds the Basic audio announcement data into extended advertising buffer.

\param[  in   ] basicAnnouncement  Encode mandatory user-provided Basic Audio Announcement UUID data and optional BIG (Broadcast Isochronous Group) information into the extended advertising data.
\param[  in   ] maxSubGroupCount   Maximum supported SubGroup count in Basic Announcement. Defined in Application side.
\param[  in   ] maxBISCount        Maximum supported BIS count in Basic Announcement. Defined in Application side.
\param[  out  ] extAdvDataObj      Extended advertising data structure to store the encoded Basic Audio Announcement UUID data.

\return                            #CLX_SUCCESS: successful encoding
                                   #CLX_FAIL: Failed. If Basic Audio Announcement UUID data is missing in the input field, the API returns FAIL because Basic Audio Announcement UUID is mandatory data.
                                   #CLX_ERROR_INVALID_COMMAND_PARAMETER: One or more of provided arguments are invalid.
                                   #CLX_ERROR_BLE_ATT_INSUFFICIENT_RESOURCES: SubGroup Count or BIS Count in Basic Announcement data is grater than supported count.
*/
ClxResult clxBapAddBasicAudioAnnouncement(_user_in_  ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement,
                                          _user_in_  u1                                    maxSubGroupCount,
                                          _user_in_  u1                                    maxBISCount,
                                          _user_out_ ClxBleExtendedAdvertisingData*        extAdvDataObj);

/**
Finds the Basic audio announcement data from periodic advertisement report.

\param[  out  ] basicAnnouncement  Decoded and filled Basic Audio Announcement UUID data from the extended advertising data.
\param[  in   ] maxSubGroupCount   Maximum supported SubGroup count in Basic Announcement. Defined in Application side.
\param[  in   ] maxBISCount        Maximum supported BIS count in Basic Announcement. Defined in Application side.
\param[  in   ] payload            Extended advertising payload
\param[  in   ] payloadLength      Length of the extended advertising payload in bytes.

\return                            #CLX_SUCCESS: Successful decoding
                                   #CLX_FAIL: Failed. If Basic Audio Announcement UUID data is missing in the advertising data, the API returns FAIL because Basic Audio Announcement UUID is mandatory data.s
                                   #CLX_ERROR_INVALID_COMMAND_PARAMETER: One or more of provided arguments are invalid.
                                   #CLX_ERROR_BLE_ATT_INSUFFICIENT_RESOURCES: SubGroup Count or BIS Count in Basic Announcement data is grater than supported count.
*/
ClxResult clxBapFindBasicAudioAnnouncement(_user_out_ ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement,
                                           _user_in_  u1                                    maxSubGroupCount,
                                           _user_in_  u1                                    maxBISCount,
                                           _user_in_  const u1*                             payload,
                                           _in_       const u1                              payloadLength);

/**
Initialize the user-given structure buffer by user-mentioned specification structure type.

\param[  in   ] sourceBuffer        user-given structure buffer for initialize based on the specification
\param[  in   ] configType          BLE Broadcast audio encode type enum.

\return ClxResult         If NULL, encoding failed.
                          #CLX_SUCCESS: Successful encoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
*/
ClxResult clxBapInitStructureByConfigType(_user_in_  void*             sourceBuffer,
                                          _in_       ClxBapConfigType  configType);

/**
Encode the data into the user-given raw buffer based on the user-mentioned specification structure from the source buffer.

\param[  in   ] sourceBuffer            It contains the user-info-filled data in the defined spec-based structure. Use the ClxBapConfigType enum to know the config type.
\param[  in   ] sourceBufferType        BLE Broadcast audio encode type enum.
\param[  out  ] destinationBuffer       Allocated raw buffer to encode from the user-provided source buffer.
\param[  in   ] desBufferLength         Actual destination buffer length in bytes.
\param[  out  ] filledLength            Length of data filled into the destination buffer.

\return ClxResult         If NULL, encoding failed.
                          #CLX_SUCCESS: Successful encoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
*/
ClxResult clxBapEncodeByConfigType(_user_in_  void*             sourceBuffer,
                                   _in_       ClxBapConfigType  sourceBufferType,
                                   _user_out_ u1*               destinationBuffer,
                                   _in_       ClxSize           desBufferLength,
                                   _user_out_ ClxSize*          filledLength);

/**
Decode data from the user-provided raw buffer based on the user-specified config type and store it in the destination buffer.

\param[  in   ] rawBuffer           Raw buffer data to be decoded.
\param[  in   ] configType          Use the ClxBapConfigType enum to specify the expected structure.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] destinationStruct   Decoded structure will be filled based on the config type.
\param[  out  ] filledLength        Length of data filled into the destination buffer.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeByConfigType(_user_in_  const u1*        rawBuffer,
                                   _in_       ClxBapConfigType configType,
                                   _in_       ClxSize          rawBufferLength,
                                   _user_out_ void*            destinationStruct,
                                   _user_out_ ClxSize*         filledLength);

/*====================================================ASCS====================================================*/

/**
Encode the Sink ASE data into the user-given raw buffer.

\param[  in   ] sinkAse                Audio stream Endpoint data.
\param[  out  ] destinationBuffer      Allocated raw buffer to encode from the user-provided ASE info.
\param[  in   ] destinationBufferSize  Actual destination buffer length in bytes.
\param[  out  ] filledLength           Length of data filled into the destination buffer.

\return ClxResult         If NULL, encoding failed.
                          #CLX_SUCCESS: Successful encoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
*/
ClxResult clxBapEncodeSinkAse(_user_in_  const ClxBapAudioStreamEndpoint*   sinkAse,
                              _user_out_ u1*                                destinationBuffer,
                              _in_       ClxSize                            destinationBufferSize,
                              _user_out_ ClxSize*                           filledLength);

/**
Decode the Sink ASE data from the user-provided raw buffer.

\param[  in   ] rawBuffer           Raw buffer data to be decoded.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] sinkAse             Output structure to store decoded Sink ASE data.
\param[  out  ] filledLength        Decoded data length.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeSinkAse(_user_in_  const u1*                      rawBuffer,
                              _in_       ClxSize                        rawBufferLength,
                              _user_out_ ClxBapAudioStreamEndpoint*     sinkAse,
                              _user_out_ ClxSize*                       filledLength);

/**
Encode the Source ASE data into the user-given raw buffer.

\param[  in   ] sourceAse               Audio stream Endpoint data.
\param[  out  ] destinationBuffer       Allocated raw buffer to encode from the user-provided ASE info.
\param[  in   ] destinationBufferSize   Actual destination buffer length in bytes.
\param[  out  ] filledLength            Length of data filled into the destination buffer.

\return ClxResult         If NULL, encoding failed.
                          #CLX_SUCCESS: Successful encoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
*/
ClxResult clxBapEncodeSourceAse(_user_in_  const ClxBapAudioStreamEndpoint*   sourceAse,
                                _user_out_ u1*                                destinationBuffer,
                                _in_       ClxSize                            destinationBufferSize,
                                _user_out_ ClxSize*                           filledLength);

/**
Decode the Source ASE data from the user-provided raw buffer.

\param[  in   ] rawBuffer           Raw buffer data to be decoded.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] sourceAse           Output structure to store decoded Source ASE data.
\param[  out  ] filledLength        Decoded data length.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeSourceAse(_user_in_  const u1*                      rawBuffer,
                                _in_       ClxSize                        rawBufferLength,
                                _user_out_ ClxBapAudioStreamEndpoint*     sourceAse,
                                _user_out_ ClxSize*                       filledLength);

/**
Encode the ASE Control Point data into the user-given raw buffer.

\param[  in   ] aseOpCodeInfo           Audio stream Endpoint Control Point data.
\param[  out  ] destinationBuffer       Allocated raw buffer to encode from the user-provided ASE Control Point info.
\param[  in   ] destinationBufferSize   Actual destination buffer length in bytes.
\param[  out  ] filledLength            Length of data filled into the destination buffer.

\return ClxResult         If NULL, encoding failed.
                          #CLX_SUCCESS: Successful encoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
*/
ClxResult clxBapEncodeAseOpCodeData(_user_in_  const ClxBapAseOpCode* aseOpCodeInfo,
                                    _user_out_ u1*                    destinationBuffer,
                                    _in_       ClxSize                destinationBufferSize,
                                    _user_out_ ClxSize*               filledLength);

/**
This function decodes only the static fields (basic level) of the ASE Control Point. It must be
called first before decoding any extended/dynamic level data. Use this to determine the structure
layout and allocate memory (if needed) before proceeding to decode the extended level.

\param[  in   ] rawBuffer           Pointer to the raw buffer containing the encoded ASE Control Point data.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] aseOpCodeInfo       Pointer to the output structure to populate with decoded static data.
\param[  out  ] filledLength        Number of bytes consumed from the raw buffer during decoding.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeBasicLevelAseOpCodeData(_user_in_  const u1*        rawBuffer,
                                              _in_       ClxSize          rawBufferLength,
                                              _user_out_ ClxBapAseOpCode* aseOpCodeInfo,
                                              _user_out_ ClxSize*         filledLength);

/**
This function should be called after `clxBapDecodeBasicLevelAseControlPoint()` has been successfully invoked.
It decodes dynamic/extended fields and fills the appropriate sections in the `ClxBapAseOpCode` structure.
Ensure dynamic memory allocation (if required) is completed before calling this.

\param[  in   ] rawBuffer           Pointer to the raw buffer containing the encoded ASE Control Point data.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] aseOpCodeInfo       Pointer to the already-filled ASE Control Point structure.
\param[  out  ] filledLength        Number of bytes consumed from the raw buffer during decoding.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeExtendedLevelAseOpCodeData(_user_in_  const u1*        rawBuffer,
                                                 _in_       ClxSize          rawBufferLength,
                                                 _user_out_ ClxBapAseOpCode* aseOpCodeInfo,
                                                 _user_out_ ClxSize*         filledLength);

/**
Data Structure for the indication #CLX_BAP_GET_SINK_ASE_COMPLETE
*/
typedef struct ClxBapGetSinkAseCompleteStruct
{
    _user_out_ u1*       valueBuffer;        /*!< Caller-provided buffer to store the retrieved Sink ASE value.
                                                    This buffer must remain valid and unmodified until the operation completes. */
    _user_out_ u4*       valueReadLength;    /*!< Actual characteristic read length (in bytes) */
}ClxBapGetSinkAseComplete;

/**
This API retrieves the Sink ASE value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_SINK_ASE_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetSinkAseComplete.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             Value handle of the Sink ASE characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] valueBuffer        Caller-provided buffer to store the retrieved Sink ASE value.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the output buffer.
\param[  out  ] valueReadLength    Actual characteristic read length (in bytes)
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetSinkAse(_in_       ClxHandle gatt,
                           _in_       u2        handle,
                           _user_out_ u1*       valueBuffer,
                           _in_       u4        valueBufferLength,
                           _user_out_ u4*       valueReadLength,
                           _in_       boolean   block);

/**
This API is used to write a valid Sink ASE characteristic value into the GATT database. It can be used by only GATT Server (Peripheral) role.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_SINK_ASE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt               The handle of the GATT server.
\param[  in   ] handle             Value handle of the Sink ASE characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] valueBuffer        Caller-provided buffer containing the Sink ASE value to be written.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the input buffer.
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetSinkAse(_in_      ClxHandle       gatt,
                           _in_      u2              handle,
                           _user_in_ const u1*       valueBuffer,
                           _in_      u4              valueBufferLength,
                           _in_      boolean         block);

/**
Data Structure for the indication #CLX_BAP_GET_SOURCE_ASE_COMPLETE
*/
typedef struct ClxBapGetSourceAseCompleteStruct
{
    _user_out_ u1*       valueBuffer;        /*!< Caller-provided buffer to store the retrieved Source ASE value.
                                                    This buffer must remain valid and unmodified until the operation completes. */
    _user_out_ u4*       valueReadLength;    /*!< Actual characteristic read length (in bytes) */
}ClxBapGetSourceAseComplete;

/**
This API retrieves the Source ASE value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_SOURCE_ASE_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetSourceAseComplete.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             Value handle of the Source ASE characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] valueBuffer        Caller-provided buffer to store the retrieved Source ASE value.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the output buffer.
\param[  out  ] valueReadLength    Actual characteristic read length (in bytes)
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetSourceAse(_in_       ClxHandle gatt,
                             _in_       u2        handle,
                             _user_out_ u1*       valueBuffer,
                             _in_       u4        valueBufferLength,
                             _user_out_ u4*       valueReadLength,
                             _in_       boolean   block);

/**
This API is used to write a valid Source ASE characteristic value into the GATT database. It can be used by only GATT Server (Peripheral) role.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_SOURCE_ASE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt               The handle of the GATT server.
\param[  in   ] handle             Value handle of the Sink ASE characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] valueBuffer        Caller-provided buffer containing the Source ASE value to be written.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the input buffer.
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetSourceAse(_in_      ClxHandle  gatt,
                             _in_      u2         handle,
                             _user_in_ const u1*  valueBuffer,
                             _in_      u4         valueBufferLength,
                             _in_      boolean    block);

/**
Data Structure for the indication #CLX_BAP_GET_ASE_OP_CODE_COMPLETE
*/
typedef struct ClxBapGetAseOpCodeCompleteStruct
{
    _user_out_ u1*       valueBuffer;        /*!< Caller-provided buffer to store the retrieved ASE Control Point value.
                                                    This buffer must remain valid and unmodified until the operation completes. */
    _user_out_ u4*       valueReadLength;    /*!< Actual characteristic read length (in bytes) */
}ClxBapGetAseOpCodeComplete;

/**
This API is used to write a valid ASE Control Point characteristic value into the GATT database. It can be used by only GATT Server (Peripheral) role.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_ASE_OP_CODE_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetAseOpCodeComplete.

\param[  in   ] gatt               The handle of the GATT server.
\param[  in   ] handle             Value handle of the ASE Control Point characteristic.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] valueBuffer        Caller-provided buffer to store the retrieved ASE Control Point value.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the output buffer.
\param[  out  ] valueReadLength    Actual characteristic read length (in bytes)
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetAseOpCode(_in_       ClxHandle gatt,
                             _in_       u2        handle,
                             _user_out_ u1*       valueBuffer,
                             _in_       u4        valueBufferLength,
                             _user_out_ u4*       valueReadLength,
                             _in_       boolean   block);

/**
This API retrieves the ASE Control Point value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_ASE_OP_CODE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             Value handle of the ASE Control Point characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  in   ] valueBuffer        Caller-provided buffer containing the ASE Control Point value to be written.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the input buffer.
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetAseOpCode(_in_      ClxHandle       gatt,
                             _in_      u2              handle,
                             _user_in_ const u1*       valueBuffer,
                             _in_      u4              valueBufferLength,
                             _in_      boolean         block);

/*====================================================PACS====================================================*/

/**
Encode the PAC data into the user-given raw buffer.

\param[  in   ] pacData                 Public Audio Capability data.
\param[  out  ] destinationBuffer       Allocated raw buffer to encode from the user-provided PAC info.
\param[  in   ] destinationBufferSize   Actual destination buffer length in bytes.
\param[  out  ] filledLength            Length of data filled into the destination buffer.

\return ClxResult         If NULL, encoding failed.
                          #CLX_SUCCESS: Successful encoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
*/
ClxResult clxBapEncodePacRecord(_user_in_  const ClxBapPacRecords* pacData,
                                _user_out_ u1*                     destinationBuffer,
                                _in_       ClxSize                 destinationBufferSize,
                                _user_out_ ClxSize*                filledLength);

/**
This function decodes only the static fields (basic level) of the Public Audio Capability. It must be
called first before decoding any extended/dynamic level data. Use this to determine the structure
layout and allocate memory (if needed) before proceeding to decode the extended level.

\param[  in   ] rawBuffer           Pointer to the raw buffer containing the encoded Public Audio Capability data.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] pacData             Pointer to the output structure to populate with decoded static data.
\param[  out  ] filledLength        Number of bytes consumed from the raw buffer during decoding.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeBasicLevelPacRecord(_user_in_  const u1*         rawBuffer,
                                          _in_       ClxSize           rawBufferLength,
                                          _user_out_ ClxBapPacRecords* pacData,
                                          _user_out_ ClxSize*          filledLength);

/**
This function should be called after `clxBapDecodeBasicLevelPacRecord()` has been successfully invoked.
It decodes dynamic/extended fields and fills the appropriate sections in the `ClxBapPacRecords` structure.
Ensure dynamic memory allocation (if required) is completed before calling this.

\param[  in   ] rawBuffer           Pointer to the raw buffer containing the encoded Public Audio Capability data.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] pacData             Pointer to the already-filled Public Audio Capability structure.
\param[  out  ] filledLength        Number of bytes consumed from the raw buffer during decoding.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeExtendedLevelPacRecord(_user_in_  const u1*         rawBuffer,
                                             _in_       ClxSize           rawBufferLength,
                                             _user_out_ ClxBapPacRecords* pacData,
                                             _user_out_ ClxSize*          filledLength);

/**
Data Structure for the indication #CLX_BAP_GET_SINK_PAC_COMPLETE
*/
typedef struct ClxBapGetSinkPacCompleteStruct
{
    _user_out_ u1*  valueBuffer;        /*!< Caller-provided buffer to store the retrieved Sink PAC value.
                                        This buffer must remain valid and unmodified until the operation completes. */
    _user_out_ u4*  valueReadLength;    /*!< Actual characteristic read length (in bytes) */
}ClxBapGetSinkPacComplete;

/**
This API retrieves the Sink PAC value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_SINK_PAC_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetSinkPacComplete.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             Value handle of the Sink PAC characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] valueBuffer        Caller-provided buffer to store the retrieved Sink PAC value.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the output buffer.
\param[  out  ] valueReadLength    Actual characteristic read length (in bytes)
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetSinkPac(_in_       ClxHandle gatt,
                           _in_       u2        handle,
                           _user_out_ u1*       valueBuffer,
                           _in_       u4        valueBufferLength,
                           _user_out_ u4*       valueReadLength,
                           _in_       boolean   block);

/**
This API is used to write a valid Sink PAC characteristic value into the GATT database. It can be used by only GATT Server (Peripheral)) role

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_SINK_PAC_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt               The handle of the GATT server.
\param[  in   ] handle             Value handle of the Sink PAC characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] valueBuffer        Caller-provided buffer containing the Sink PAC value to be written.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the input buffer.
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetSinkPac(_in_      ClxHandle gatt,
                           _in_      u2        handle,
                           _user_in_ const u1* valueBuffer,
                           _in_      u4        valueBufferLength,
                           _in_      boolean   block);

/**
Data Structure for the indication #CLX_BAP_GET_SINK_AUDIO_LOCATION_COMPLETE
*/
typedef struct ClxBapGetSinkAudioLocationCompleteStruct
{
    _user_out_ ClxBapPacAudioLocations*  sinkAudioLocation;    /*!<Caller-provided structure pointer to store the retrieved Sink Audio Location value. */
}ClxBapGetSinkAudioLocationComplete;

/**
This API retrieves the Sink Audio Location value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_SINK_AUDIO_LOCATION_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetSinkAudioLocationComplete.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             Value handle of the Sink Audio Location characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] sinkAudioLocation Caller-provided structure pointer to store the retrieved Sink Audio Location value.
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetSinkAudioLocation(_in_       ClxHandle                gatt,
                                     _in_       u2                       handle,
                                     _user_out_ ClxBapPacAudioLocations* sinkAudioLocation,
                                     _in_       boolean                  block);

/**
This API is used to write a valid Sink Audio Location characteristic value into the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_SINK_AUDIO_LOCATION_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             Value handle of the Sink Audio Location characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] sinkAudioLocation  Containing the Sink Audio Location value to be written.
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetSinkAudioLocation(_in_ ClxHandle                gatt,
                                     _in_ u2                       handle,
                                     _in_ ClxBapPacAudioLocations  sinkAudioLocation,
                                     _in_ boolean                  block);

/**
Data Structure for the indication #CLX_BAP_GET_SOURCE_PAC_COMPLETE
*/
typedef struct ClxBapGetSourcePacCompleteStruct
{
    _user_out_ u1*  valueBuffer;        /*!< Caller-provided buffer to store the retrieved Source PAC value.
                                        This buffer must remain valid and unmodified until the operation completes. */
    _user_out_ u4*  valueReadLength;    /*!< Actual characteristic read length (in bytes) */
}ClxBapGetSourcePacComplete;

/**
This API retrieves the Source PAC value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_SOURCE_PAC_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetSourcePacComplete.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             Value handle of the Source PAC characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] valueBuffer        Caller-provided buffer to store the retrieved Source PAC value.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the output buffer.
\param[  out  ] valueReadLength    Actual characteristic read length (in bytes)
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetSourcePac(_in_       ClxHandle   gatt,
                             _in_       u2          handle,
                             _user_out_ u1*         valueBuffer,
                             _in_       u4          valueBufferLength,
                             _user_out_ u4*         valueReadLength,
                             _in_       boolean     block);

/**
This API is used to write a valid Source PAC characteristic value into the GATT database. It can be used by only GATT Server (Peripheral)) role

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_SOURCE_PAC_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt               The handle of the GATT server.
\param[  in   ] handle             Value handle of the Sink PAC characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] valueBuffer        Caller-provided buffer containing the Source PAC value to be written.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the input buffer.
\param[  in   ] block              Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetSourcePac(_in_      ClxHandle gatt,
                             _in_      u2        handle,
                             _user_in_ const u1* valueBuffer,
                             _in_      u4        valueBufferLength,
                             _in_      boolean   block);

/**
Data Structure for the indication #CLX_BAP_GET_SOURCE_AUDIO_LOCATION_COMPLETE
*/
typedef struct ClxBapGetSourceAudioLocationCompleteStruct
{
    _user_out_ ClxBapPacAudioLocations*  sourceAudioLocation;    /*!<Caller-provided structure pointer to store the retrieved Source Audio Location value. */
}ClxBapGetSourceAudioLocationComplete;

/**
This API retrieves the Source Audio Location value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_SOURCE_AUDIO_LOCATION_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetSourceAudioLocationComplete.

\param[  in   ] gatt                 The handle of the GATT client or server.
\param[  in   ] handle               Value handle of the Source Audio Location characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] sourceAudioLocation Caller-provided structure pointer to store the retrieved Source Audio Location value.
\param[  in   ] block                Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetSourceAudioLocation(_in_       ClxHandle                gatt,
                                       _in_       u2                       handle,
                                       _user_out_ ClxBapPacAudioLocations* sourceAudioLocation,
                                       _in_       boolean                  block);

/**
This API is used to write a valid Source Audio Location characteristic value into the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_SOURCE_AUDIO_LOCATION_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt                 The handle of the GATT client or server.
\param[  in   ] handle               Value handle of the Source Audio Location characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] sourceAudioLocation  Containing the Source Audio Location value to be written.
\param[  in   ] block                Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetSourceAudioLocation(_in_ ClxHandle                gatt,
                                       _in_ u2                       handle,
                                       _in_ ClxBapPacAudioLocations  sourceAudioLocation,
                                       _in_ boolean                  block);

/**
Data Structure for the indication #CLX_BAP_GET_AVAILABLE_AUDIO_CONTEXT_COMPLETE
*/
typedef struct ClxBapGetAvailableAudioContextCompleteStruct
{
    _user_out_ ClxBapPacAvailableAudioContext*  availableAudioContext;    /*!<Caller-provided structure pointer to store the retrieved Available Audio Context value. */
}ClxBapGetAvailableAudioContextComplete;

/**
This API retrieves the Available Audio Context value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_AVAILABLE_AUDIO_CONTEXT_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetAvailableAudioContextComplete.

\param[  in   ] gatt                   The handle of the GATT client or server.
\param[  in   ] handle                 Value handle of the Available Audio Context characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] availableAudioContext Caller-provided structure pointer to store the retrieved Available Audio Context value.
\param[  in   ] block                  Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetAvailableAudioContext(_in_       ClxHandle                       gatt,
                                         _in_       u2                              handle,
                                         _user_out_ ClxBapPacAvailableAudioContext* availableAudioContext,
                                         _in_       boolean                         block);

/**
This API is used to write a valid Available Audio Context characteristic value into the GATT database. It can be used by only GATT Server (Peripheral)) role

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_AVAILABLE_AUDIO_CONTEXT_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt                   The handle of the GATT server.
\param[  in   ] handle                 Value handle of the Available Audio Context characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] availableAudioContext  Containing the Available Audio Context value to be written.
\param[  in   ] block                  Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetAvailableAudioContext(_in_ ClxHandle                       gatt,
                                         _in_ u2                              handle,
                                         _in_ ClxBapPacAvailableAudioContext  availableAudioContext,
                                         _in_ boolean                         block);

/**
Data Structure for the indication #CLX_BAP_GET_SUPPORTED_AUDIO_CONTEXT_COMPLETE
*/
typedef struct ClxBapGetSupportedAudioContextCompleteStruct
{
    _user_out_ ClxBapPacSupportedAudioContext*  supportedAudioContext;    /*!<Caller-provided structure pointer to store the retrieved Supported Audio Context value. */
}ClxBapGetSupportedAudioContextComplete;

/**
This API retrieves the Supported Audio Context value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_SUPPORTED_AUDIO_CONTEXT_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetSupportedAudioContextComplete.

\param[  in   ] gatt                   The handle of the GATT client or server.
\param[  in   ] handle                 Value handle of the Supported Audio Context characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] supportedAudioContext Caller-provided structure pointer to store the retrieved Supported Audio Context value.
\param[  in   ] block                  Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetSupportedAudioContext(_in_       ClxHandle                       gatt,
                                         _in_       u2                              handle,
                                         _user_out_ ClxBapPacSupportedAudioContext* supportedAudioContext,
                                         _in_       boolean                         block);

/**
This API is used to write a valid Supported Audio Context characteristic value into the GATT database. It can be used by only GATT Server (Peripheral)) role

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_SUPPORTED_AUDIO_CONTEXT_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt                   The handle of the GATT server.
\param[  in   ] handle                 Value handle of the Supported Audio Context characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] supportedAudioContext  Containing the Supported Audio Context value to be written.
\param[  in   ] block                  Type of the operation.
                                        - TRUE : API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetSupportedAudioContext(_in_ ClxHandle                       gatt,
                                         _in_ u2                              handle,
                                         _in_ ClxBapPacSupportedAudioContext  supportedAudioContext,
                                         _in_ boolean                         block);

/*====================================================BASS====================================================*/

/**
Encode the Broadcast Scan Control Point data into the user-given raw buffer.

\param[  in   ] bscOpCodeInfo           Audio stream Endpoint Control Point data.
\param[  out  ] destinationBuffer       Allocated raw buffer to encode from the user-provided Broadcast Scan Control Point info.
\param[  in   ] destinationBufferSize   Actual destination buffer length in bytes.
\param[  out  ] filledLength            Length of data filled into the destination buffer.

\return ClxResult         If NULL, encoding failed.
                          #CLX_SUCCESS: Successful encoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
*/
ClxResult clxBapEncodeBroadcastScanOpCodeData(_user_in_  const ClxBapBroadcastScanOpCode* bscOpCodeInfo,
                                              _user_out_ u1*                              destinationBuffer,
                                              _in_       ClxSize                          destinationBufferSize,
                                              _user_out_ ClxSize*                         filledLength);

/**
This function decodes only the static fields (basic level) of the Broadcast Scan Control Point. It must be
called first before decoding any extended/dynamic level data. Use this to determine the structure
layout and allocate memory (if needed) before proceeding to decode the extended level.

\param[  in   ] rawBuffer           Pointer to the raw buffer containing the encoded Broadcast Scan Control Point data.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] bscOpCodeInfo       Pointer to the output structure to populate with decoded static data.
\param[  out  ] filledLength        Number of bytes consumed from the raw buffer during decoding.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeBasicLevelBroadcastScanOpCodeData(_user_in_  const u1*                  rawBuffer,
                                                        _in_       ClxSize                    rawBufferLength,
                                                        _user_out_ ClxBapBroadcastScanOpCode* bscOpCodeInfo,
                                                        _user_out_ ClxSize*                   filledLength);

/**
This function should be called after `clxBapDecodeBasicLevelBroadcastScanOpCodeData()` has been successfully invoked
It decodes dynamic/extended fields and fills the appropriate sections in the `ClxBapBroadcastScanOpCode` structure.
Note: This API is not required if the opCode is either "ClxBapBassOpCode_RemoveScanStopped" or 
"ClxBapBassOpCode_RemoteScanStarted",as these opcodes do not include extended fields.
Ensure dynamic memory allocation (if required) is completed before calling this.

\param[  in   ] rawBuffer           Pointer to the raw buffer containing the encoded Broadcast Scan Control Point data.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] bscOpCodeInfo       Pointer to the already-filled Broadcast Scan Control Point structure.
\param[  out  ] filledLength        Number of bytes consumed from the raw buffer during decoding.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeExtendedLevelBroadcastScanOpCodeData(_user_in_  const u1*                  rawBuffer,
                                                           _in_       ClxSize                    rawBufferLength,
                                                           _user_out_ ClxBapBroadcastScanOpCode* bscOpCodeInfo,
                                                           _user_out_ ClxSize*                   filledLength);

/**
Encode the Broadcast Receive State data into the user-given raw buffer.

\param[  in   ] receiveState           Audio stream Endpoint Control Point data.
\param[  out  ] destinationBuffer       Allocated raw buffer to encode from the user-provided Broadcast Receive State info.
\param[  in   ] destinationBufferSize   Actual destination buffer length in bytes.
\param[  out  ] filledLength            Length of data filled into the destination buffer.

\return ClxResult         If NULL, encoding failed.
                          #CLX_SUCCESS: Successful encoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
*/
ClxResult clxBapEncodeBroadcastReceiveState(_user_in_  const ClxBapBroadcastReceiveState* receiveState,
                                              _user_out_ u1*                              destinationBuffer,
                                              _in_       ClxSize                          destinationBufferSize,
                                              _user_out_ ClxSize*                         filledLength);

/**
This function decodes only the static fields (basic level) of the Broadcast Receive State. It must be
called first before decoding any extended/dynamic level data. Use this to determine the structure
layout and allocate memory (if needed) before proceeding to decode the extended level.

\param[  in   ] rawBuffer           Pointer to the raw buffer containing the encoded Broadcast Receive State data.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] receiveState       Pointer to the output structure to populate with decoded static data.
\param[  out  ] filledLength        Number of bytes consumed from the raw buffer during decoding.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeBasicLevelBroadcastReceiveState(_user_in_  const u1*                    rawBuffer,
                                                      _in_       ClxSize                      rawBufferLength,
                                                      _user_out_ ClxBapBroadcastReceiveState* receiveState,
                                                      _user_out_ ClxSize*                     filledLength);

/**
This function should be called after `clxBapDecodeBasicLevelBroadcastReceiveState()` has been successfully invoked.
It decodes dynamic/extended fields and fills the appropriate sections in the `ClxBapBroadcastReceiveState` structure.
Ensure dynamic memory allocation (if required) is completed before calling this.

\param[  in   ] rawBuffer           Pointer to the raw buffer containing the encoded Broadcast Receive State data.
\param[  in   ] rawBufferLength     Actual length of the raw buffer in bytes.
\param[  out  ] receiveState       Pointer to the already-filled Broadcast Receive State structure.
\param[  out  ] filledLength        Number of bytes consumed from the raw buffer during decoding.

\return ClxResult         If NULL, decoding failed.
                          #CLX_SUCCESS: Successful decoding.
                          #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of the provided arguments are invalid.
                          #CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH: Given input length is invalid.
*/
ClxResult clxBapDecodeExtendedLevelBroadcastReceiveState(_user_in_  const u1*                    rawBuffer,
                                                         _in_       ClxSize                      rawBufferLength,
                                                         _user_out_ ClxBapBroadcastReceiveState* receiveState,
                                                         _user_out_ ClxSize*                     filledLength);

/**
Data Structure for the indication #CLX_BAP_GET_BROADCAST_SCAN_OP_CODE_COMPLETE
*/
typedef struct ClxBapGetBroadcastScanOpCodeCompleteStruct
{
    _user_out_ u1*  valueBuffer;        /*!< Caller-provided buffer to store the retrieved Broadcast Scan Op Code value.
                                        This buffer must remain valid and unmodified until the operation completes. */
    _user_out_ u4*  valueReadLength;    /*!< Actual characteristic read length (in bytes) */
} ClxBapGetBroadcastScanOpCodeComplete;

/**
This API retrieves the Broadcast Scan Op Code value from the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_BROADCAST_SCAN_OP_CODE_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetBroadcastScanOpCodeComplete.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             Value handle of the Broadcast Scan Op Code characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] valueBuffer        Caller-provided buffer to store the retrieved Broadcast Scan Op Code value.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the output buffer.
\param[  out  ] valueReadLength    Actual characteristic read length (in bytes)
\param[  in   ] block              Type of the operation.
                                        - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetBroadcastScanOpCode(_in_       ClxHandle  gatt,
                                       _in_       u2         handle,
                                       _user_out_ u1*        valueBuffer,
                                       _in_       u4         valueBufferLength,
                                       _user_out_ u4*        valueReadLength,
                                       _in_       boolean    block);

/**
This API is used to write a valid Broadcast Scan Op Code characteristic value into the GATT database. It can be used by only GATT Server (Peripheral) role

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_BROADCAST_SCAN_OP_CODE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt               The handle of the GATT server.
\param[  in   ] handle             Value handle of the Broadcast Scan Op Code characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] valueBuffer        Caller-provided buffer containing the Broadcast Scan Op Code value to be written.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the input buffer.
\param[  in   ] block              Type of the operation.
                                        - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetBroadcastScanOpCode(_in_      ClxHandle  gatt,
                                       _in_      u2         handle,
                                       _user_in_ const u1*  valueBuffer,
                                       _in_      u4         valueBufferLength,
                                       _in_      boolean    block);

/**
Data Structure for the indication #CLX_BAP_GET_BROADCAST_RECEIVE_STATE_COMPLETE
*/
typedef struct ClxBapGetBroadcastReceiveStateCompleteStruct
{
    _user_out_ u1*  valueBuffer;        /*!< Caller-provided buffer to store the retrieved Broadcast Receive State value.
                                        This buffer must remain valid and unmodified until the operation completes. */
    _user_out_ u4*  valueReadLength;    /*!< Actual characteristic read length (in bytes) */
} ClxBapGetBroadcastReceiveStateComplete;

/**
This API retrieves the Broadcast Receive State value from the GATT database. It can be used by only GATT Server (Peripheral) role

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_GET_BROADCAST_RECEIVE_STATE_COMPLETE.
                   The parameter of this indication is of type #ClxBapGetBroadcastReceiveStateComplete.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             Value handle of the Broadcast Receive State characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API.
                                        - If the local device acts as a GATT server, compute the handle using the base handle and characteristic index.
\param[  out  ] valueBuffer        Caller-provided buffer to store the retrieved Broadcast Receive State value.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the output buffer.
\param[  out  ] valueReadLength    Actual characteristic read length (in bytes)
\param[  in   ] block              Type of the operation.
                                        - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapGetBroadcastReceiveState(_in_       ClxHandle  gatt,
                                         _in_       u2         handle,
                                         _user_out_ u1*        valueBuffer,
                                         _in_       u4         valueBufferLength,
                                         _user_out_ u4*        valueReadLength,
                                         _in_       boolean    block);

/**
This API is used to write a valid Broadcast Receive State characteristic value into the GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BAP_SET_BROADCAST_RECEIVE_STATE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt               The handle of the GATT server.
\param[  in   ] handle             Value handle of the Broadcast Receive State characteristic.
                                        - If the local device acts as a GATT client, the handle can be retrieved using the #clxGattClientGetValueHandle API
\param[  in   ] valueBuffer        Caller-provided buffer containing the Broadcast Receive State value to be written.
                                        This buffer must remain valid and unmodified until the operation completes.
\param[  in   ] valueBufferLength  Length (in bytes) of the input buffer.
\param[  in   ] block              Type of the operation.
                                        - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

        Furthermore, the result of the command may be one of the following codes.
        In blocking mode, the result will be returned by this function. In non-blocking mode, the result will be passed to the call-back function:

        - CLX_SUCCESS: Operation is successful
        - Any other error code: This operation has failed
*/
ClxResult clxBapSetBroadcastReceiveState(_in_      ClxHandle  gatt,
                                         _in_      u2         handle,
                                         _user_in_ const u1*  valueBuffer,
                                         _in_      u4         valueBufferLength,
                                         _in_      boolean    block);

#ifdef __cplusplus
}
#endif

#endif /* __Ble_Bap_Api_h__ */

