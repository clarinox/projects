#ifndef __Ble_Audio_Common_h__
#define __Ble_Audio_Common_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                BleAudioCommon.h
* Description         Declares ClarinoxBlue LE Audio Common service and 
                      characteristics declarations.
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/
#if defined(CLX_BLE_ISOCHRONOUS)

#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "mainBluetooth.h"

#if defined (CLX_WINDOWS)
#include <direct.h>
#endif /* defined (CLX_WINDOWS) */
#include "Gap.Api.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gap.Ble.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Client.Api.h"
#include "Gatt.Ble.Server.Api.h"

#include "Ble.Bap.Api.h"

#include "Gatt.Ble.Includes.h"

#include "Iso.Ble.Common.Api.h"
#include "Iso.Ble.Server.Api.h"
#include "Iso.Ble.Interface.h"

#include "GattApp.h"
#include "Gap.Ble.Bonding.Api.h"
#include "GapBleApp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
Audio Stream Control Service uuid.
*/
#define CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID                              0x184E

/**
Sink ASE Characteristic:
*/
#define CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID                              0x2BC4
#define CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_PROPERTY                          (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)

/**
Source ASE Characteristic:
*/
#define CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_UUID                            0x2BC5
#define CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_PROPERTY                        (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)

/**
Size of ASE characteristic
For more deatils please refer #ClxBapAudioStreamEndpoint
*/
#define CLX_GATT_ASCS_CHARACTERISTIC_ASE_SIZE                                   CLX_GATT_MAX_LTV_RECORD_LENGTH


/**
ASE Control Point Characteristic:
*/
#define CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID                     0x2BC6
#define CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_PROPERTY                (CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_SIZE                     CLX_GATT_MAX_LTV_RECORD_LENGTH

/**
Published Audio Capabilities GATT Service.
*/
#define CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID                      0x1850

/**
Sink PAC Characteristic:
*/
#define CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_UUID                              0x2BC9
#define CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_PROPERTY                          (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE )

/**
Sink Audio Location Characteristic:
*/
#define CLX_GATT_PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_UUID                   0x2BCA
#define CLX_GATT_PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_PROPERTY               (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE )

/**
Source PAC Characteristic:
*/
#define CLX_GATT_PACS_CHARACTERISTIC_SOURCE_PAC_UUID                            0x2BCB
#define CLX_GATT_PACS_CHARACTERISTIC_SOURCE_PAC_PROPERTY                        (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE )

/**
Size of Sink or Source PAC characteristic
For more deatils please refer #ClxRemoteAudioCapabilities
*/
#define CLX_GATT_PACS_CHARACTERISTIC_PAC_SIZE                                   CLX_GATT_MAX_LTV_RECORD_LENGTH

/**
Source Audio Location Characteristic:
*/
#define CLX_GATT_PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_UUID                 0x2BCC
#define CLX_GATT_PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_PROPERTY             (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE )

/**
Size of Sink or Source Audio Location Characteristic
*/
#define CLX_GATT_PACS_CHARACTERISTIC_AUDIO_LOCATION_SIZE                        sizeof(u4)

/**
Available Audio Contexts Characteristic:
*/
#define CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_UUID              0x2BCD
#define CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_PROPERTY          (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE )
#define CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_SIZE              sizeof(ClxBapPacAvailableAudioContext)

/**
Supported Audio Content Characteristic:
*/
#define CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_UUID               0x2BCE
#define CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_PROPERTY           (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE )
#define CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_SIZE               sizeof(ClxBapPacSupportedAudioContext)

/**
Audio Input Control Service uuid
*/
#define CLX_GATT_AUDIO_INPUT_CONTROL_SERVICE_UUID                               0x1843

/**
Audio Input State Characteristic:
*/
#define CLX_GATT_AICS_CHARACTERISTIC_AUDIO_INPUT_STATE_UUID                     0x2B77
#define CLX_GATT_AICS_CHARACTERISTIC_AUDIO_INPUT_STATE_PROPERTY                 (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_AICS_CHARACTERISTIC_AUDIO_INPUT_STATE_SIZE                     sizeof(ClxAudioInputState)

/**
Gain Settings Characteristic:
*/
#define CLX_GATT_AICS_CHARACTERISTIC_GAIN_SETTINGS_UUID                         0x2B78
#define CLX_GATT_AICS_CHARACTERISTIC_GAIN_SETTINGS_PROPERTY                     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_AICS_CHARACTERISTIC_GAIN_SETTINGS_SIZE                         sizeof(ClxGainSettingProperties)

/**
Broadcast Audio Scan GATT Service:
*/
#define CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID                               0x184F

/**
Broadcast Audio Scan Control Point Characteristic:
*/
#define CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID     0x2BC7
#define CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_PROPERTY (CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE)
#define CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_SIZE     CLX_GATT_MAX_LTV_RECORD_LENGTH

/**
Broadcast Receive State Characteristic:
*/
#define CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_UUID               0x2BC8
#define CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_PROPERTY           (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_SIZE               CLX_GATT_MAX_LTV_RECORD_LENGTH

#define CLX_GATT_CODEC_ID_LENGTH                                                5   /* Bytes */

#define CLX_GATT_SDU_INTERVAL                                                   3   /* Bytes */

#define CLX_GATT_AUDIO_INPUT_LENGTH                                             8   /* Bytes */

#define CLX_GATT_BROADCAST_ID_LENGTH                                            3   /* Bytes */

#define CLX_BLE_LC3_ENCODE_SIZE                             60  /* Bytes */

#define CLX_BLE_GAP_AD_TYPE_BROADCAST_NAME                  0x30

/**
 * Maximum number of PAC record supported by the system.
 * This value is set to a temporary limit of 8 until the actual maximum supported value can be confirmed from the specification.
 * Adjust this value once the accurate specification reference is available or If need more.
 */
#define CLX_GATT_MAX_PAC_RECORD_SUPPORTED                  2
/**
 * Maximum number of subgroups within a Broadcast Isochronous Stream(BIS) supported by the system.
 * Similar to the above define, this value is set temporarily to 1 pending confirmation from the specification.
 * Adjust this value once the accurate specification reference is available or If need more.
 */
#define CLX_GATT_MAX_BIS_SUB_GROUP_SUPPORTED                1

/**
 * Maximum number of Broadcast Isochronous Stream(BIS) supported by the system.
 * This value is set to a temporary limit of 1 until the actual maximum supported value can be confirmed from the specification.
 * Adjust this value once the accurate specification reference is available or If need more.
 */
#define CLX_GATT_MAX_BIS_SUPPORTED                          1

/**
 * LC3 audio Input file
 */
#define CLX_BLE_AUDIO_INPUT_FILE_1                          "./Wav_48000/Mono/BailaConmigo.wav"

#define CLX_BLE_AUDIO_INPUT_FILE_1_DURATION_IN_SEC          219

#define CLX_BLE_MONO_AUDIO_SUPPORTED_FILE_COUNT             15

#define CLX_BLE_STEREO_AUDIO_SUPPORTED_FILE_COUNT           10

#define CLX_BLE_AUDIO_CODEC_FORMAT                          ClxBluetoothCodingFormat_LC3
#define CLX_BLE_AUDIO_CODEC_COMPANY_ID                      BLUETOOTH_CLARINOX_COMPANY_ID
#define CLX_BLE_AUDIO_CODEC_VENDOR_SPECIFIC_ID              BLUETOOTH_CLARINOX_COMPANY_ID

/**
 * Data Path ID for setup data path
 * 0x00         - HCI
 * 0x01 to 0xFE - Logical_Channel_Number. The meaning of the logical channel is vendorspecific.
 * 0xFF         - Reserved for future use
 */
#define CLX_BLE_AUDIO_DATA_PATH_ID                          0x00

/**
 * Big ID or Handle.
 */
#define CLX_BLE_AUDIO_BIG_ID                                1

/**
 * Broadcast Source id.
 */
#define CLX_BLE_AUDIO_BROADCAST_SOURCE_ID                   0x01

/**
 * Invalid Big ID or Handle.
 */
#define CLX_BLE_AUDIO_INVALID_BROADCAST_ID                  0xFF

/**
 * Invalid BLE audio Handle.value
 */
#define CLX_BLE_AUDIO_INVALID_HANDLE_VALUE                  0xFFFF

/**
 * Remote device connection timeout
 */
#define CLX_BLE_CONNECTION_TIMEOUT                          100000

/**
 * Synchronization timeout for the BIG
 */
#define CLX_BLE_AUDIO_BIG_SYNC_TIMEOUT                      0x4000

/**
MAX SDU data size in Octals/Bytes.
*/
#if defined(CLX_FLOATINGPOINT_LC3)
#define CLX_BLE_ISO_MAX_SDU_SIZE                            0xC8
#else
#define CLX_BLE_ISO_MAX_SDU_SIZE                            0x3C
#endif /* defined(CLX_FLOATINGPOINT_LC3) */

/**
SDU Interval size
*/
#define CLX_BLE_ISO_SDU_INTERVAL                            10000

/**
BLE Audio Max Transport Latency
*/
#define CLX_BLE_ISO_MAX_TRANSPORT_LATENCY                   95

/**
BLE Audio Retransmissions value
*/
#define CLX_BLE_ISO_RETRANSMISSION                          1

/**
Presentation Delay.
*/
#define CLX_BLE_ISO_PRESENTATION_DELAY                      20512

/**
BLE CIG ID
*/
#define CLX_BLE_ISO_CIG_ID                                  0x01

/**
 * BLE LC3 audio configurations.
 */
#define CLX_BLE_AUDIO_SAMPLING_FREQUENCIES_VALUE            48000
#define CLX_BLE_AUDIO_NUMBER_OF_CHANNELS                    1       /* Note: Multi-channel support has not been validated for Fixed LC3. */
#define CLX_BLE_AUDIO_FRAME_DURATION                        100
#define CLX_BLE_AUDIO_MAX_NUMBER_OF_CHANNELS                2

#if defined(CLX_FLOATINGPOINT_LC3)
/* Below values are according to the Bluetooth Spec. Refer to SIG Assigned numbers document */
#define CLX_BLE_PREFERRED_STEREO_CHANNEL_ALLOCATION         3
#define CLX_BLE_PREFERRED_MONO_CHANNEL_ALLOCATION           4

/* TODO: To be exchanged from sender via adv configuration parameters for BIS */
#define CLX_BLE_RECEIVER_PCM_BIT_DEPTH                      16
#endif

#define CLX_BLE_PTSCASE_ADVERTISING_TIME_OFFSET             ( 15 * 1000 )

/**
 * BLE audio Codec specific configurations LTV structures length
 */
#define CLX_BLE_CAPABILITY_SAMPLING_FREQUENCIES_LENGTH                0x03
#define CLX_BLE_CAPABILITY_FRAME_DURATIONS_LENGTH                     0x02
#define CLX_BLE_CAPABILITY_AUDIO_CHANNEL_COUNTS_LENGTH                0x02
#define CLX_BLE_CAPABILITY_OCTETS_PER_CODEC_FRAME_LENGTH              0x05
#define CLX_BLE_CAPABILITY_MAX_CODEC_FRAMES_PER_SDU_LENGTH            0x02

/**
Codec_Specific_Capabilities LTV Structures values.
*/
#define CLX_BLE_CAPABILITY_SAMPLING_FREQUENCIES                0x00F5
#define CLX_BLE_CAPABILITY_FRAME_DURATIONS                     0x03
#define CLX_BLE_CAPABILITY_AUDIO_CHANNEL_COUNTS                0x01
#define CLX_BLE_CAPABILITY_OCTETS_PER_CODEC_FRAME              0x00C8001A
#define CLX_BLE_CAPABILITY_MAX_CODEC_FRAMES_PER_SDU            0x03

/**
 * BLE audio Codec specific configurations values for BIS/CIS.
 */
 
 /*
  *    0x01:  8000
  *    0x02: 11025
  *    0x03: 16000
  *    0x04: 22050
  *    0x05: 24000
  *    0x06: 32000
  *    0x07: 44100
  *    0x08: 48000
  *    0x09: 88200
  *    0x0A: 96000
  *    0x0B: 176400
  *    0x0C: 192000
  *    0x0D: 384000
  */
#define CLX_BLE_AUDIO_CONFIG_SAMPLING_FREQUENCIES           0x08  /* 48000 Hz */
#define CLX_BLE_AUDIO_CONFIG_FRAME_DURATIONS                0x01  /* 10 ms codec frame */
#define CLX_BLE_AUDIO_CONFIG_AUDIO_CHANNEL_ALLOCATION       0x01  /* Channel count */
#define CLX_BLE_AUDIO_CONFIG_OCTETS_PER_CODEC_FRAME         0x50  /* No. of Bytes per codec Frame*/
#define CLX_BLE_AUDIO_CONFIG_CODEC_FRAMES_PER_SDU           0x01  /* No. Of Blocks of codec Frame per SDU */

/**
 * BLE audio Codec specific configurations LTV structures length
 */
#define CLX_SAMPLING_FREQUENCIES_LENGTH                     0x02
#define CLX_FRAME_DURATIONS_LENGTH                          0x02
#define CLX_AUDIO_CHANNEL_ALLOCATION_LENGTH                 0x05
#define CLX_OCTETS_PER_CODEC_FRAME_LENGTH                   0x03
#define CLX_CODEC_FRAMES_PER_SDU_LENGTH                     0x02

#if defined( CLX_BLE_NRF5340_AUDIO_TEST )
/* 
 * Set the broadcast name for the nRF5340 Box (Serial Number: 1050105355) as "NRF5340_BROADCASTER_55".
 */
#define CLX_BLE_AUDIO_BROADCAST_NAME                        "NRF5340_BROADCASTER"
#else
#define CLX_BLE_AUDIO_BROADCAST_NAME                        "ClxBleAudioBroadcaster"
#endif /* ! defined( CLX_BLE_NRF5340_AUDIO_TEST ) */

/**
 * "BLE Audio Send Thread Name will be stored in the ClxBLEAudioSendThrdContext structure in the fixed-size array with 30 Bytes.
 * Therefore, if any changes are made, the size of the array needs to be updated."
 */
#define CLX_BLE_AUDIO_SEND_THREAD_NAME                      "BLEAudioSendThread"

/* 
 * BLE Audio Broadcast code (16bytes)
 */
#define CLX_BLE_AUDIO_BROADCAST_CODE                        "8888888888888888"

/**
 * BLE Audio Send Thread stack Szie
 */
#define CLX_BLE_AUDIO_SEND_THREAD_STACK_SIZE                1024

/**
 * BLE Unicast audio Supported ASE Count
 */
#define CLX_BLE_UNICAST_SUPPORTED_SINK_ASE_COUNT            2
#define CLX_BLE_UNICAST_SUPPORTED_SOURCE_ASE_COUNT          1

#define CLX_BLE_UNICAST_SUPPORTED_ASE_COUNT                 (CLX_BLE_UNICAST_SUPPORTED_SINK_ASE_COUNT + CLX_BLE_UNICAST_SUPPORTED_SOURCE_ASE_COUNT)

#define MAX_SUPPORT_CIS_COUNT                               1

/*
BLE ISO Group type enum
*/
typedef enum ClxBleISOGrpTypeEnum
{
    ClxBleISOGrpType_CIG      = 0,                     /* Connected Isochronous Group */
    ClxBleISOGrpType_BIG                               /* Broadcast Isochronous Group */
}ClxBleISOGrpType;

/*
BLE Role type enum
*/
typedef enum ClxBleRoleTypeEnum
{
    ClxBleRoleType_INVALID     = 0,                    /* Invalid Role */
    ClxBleRoleType_SINK        = 1,                    /* Sink Role    */
    ClxBleRoleType_SOURCE      = 2,                    /* Source Role  */
    ClxBleRoleType_BOTH        = 3,                    /* Support Both Sink and Source Role */
}ClxBleRoleType;

/*
BLE Audio Periodic Advertisement Synchronize State enum
*/
typedef enum ClxBleAudioPASyncStateEnum
{
    ClxBleAudioPlayState_DoNotSync      = 0,            /* 0x00: Do not synchronize to PA */
    ClxBleAudioPlayState_PASyncAvailable,               /* 0x01: Synchronize to PA – PAST available */
    ClxBleAudioPlayState_PASyncNotAvailable             /* 0x02: Synchronize to PA – PAST not available */
}ClxBleAudioPASyncState;

/**
BLE Broadcast audio encode or decode type enum
*/
typedef enum ClxBleAudioSpecStructureTypeEnum
{
    ClxBleAudioSpecStructure_CodecConfig      = ClxBapConfigType_CodecConfig,     /*!< Codec Specific Configuration data */
    ClxBleAudioSpecStructure_CodecCapability  = ClxBapConfigType_CodecCapability, /*!< Codec Specific Capabilities data */
    ClxBleAudioSpecStructure_MetaData         = ClxBapConfigType_MetaData,        /*!< BLE audio metadata LTV data */
    ClxBleAudioSpecStructure_BASSControlPoint,                                    /*!< Broadcast Audio Scan Control Point Characteristic Structure */
    ClxBleAudioSpecStructure_BASSReceiveState,                                    /*!< Broadcast Receive State Characteristic Structure */

}ClxBleAudioSpecStructureType;

/**
Sink/Source PAC characteristic format
*/
typedef struct ClxRemoteAudioCapabilitiesStruct
{
    u1                      numberOfPacRecords;                                 /*!< Number of sink PAC records */
    ClxBluetoothCodec       codecId;                                            /*!< Coding format values of the sink PAC records */
    u1                      codecSpecificCapabilitiesLength;                    /*!< Codec specific capabilities value length */
    ClxBapCodecCapabilities codecCapabilities;                                  /*!< Codec specific capabilities value of the PAC record */
    u1                      metaDataLength;                                     /*!< Metadata(PAC record) length */
    ClxBapAudioMetadataLtv  metadataLtv;                                        /*!< LTV formatted metadata applicable to the PAC record */
} ClxRemoteAudioCapabilities;

/**
Audio input state characteristic format
*/
typedef struct ClxAudioInputState
{
    u1 gainSetting;                                                             /*!< Value to be set the current gain of the audio input signal */
    u1 mute;                                                                    /*!< Value to be set the current mute state of the audio */
    u1 gainMode;                                                                /*!< It reflects whether gain mode are manual or automatic */
    u1 changeCounter;                                                           /*!< The server shall initialize the change counter field to an arbitrary value */
} ClxAudioInputState;

/**
Gain setting characteristic format
*/
typedef struct ClxGainSettingProperties
{
    u1 gainSettingUnits;                                                        /*!< Single increment or decrement of the Gain Setting value */
    s1 gainSettingMin;                                                          /*!< Minimum allowable value of the gain setting field value */
    s1 gainSettingMax;                                                          /*!< Maximum allowable value of the gain setting field value */
} ClxGainSettingProperties;

/**
The audio input control point characteristic set gain setting procedure format
*/
typedef struct ClxSetgainSettingProcedure
{
    u1 changeCounter;                                                           /*!< Change counter field of the audio input state characteristic */
    u1 gainSetting;                                                             /*!< Gain setting field value to change the new audio input state value */
} ClxSetgainSettingProcedure;

/**
The audio input control point characteristic unmute procedure format
*/
typedef struct ClxUnmuteProcedure
{
    u1 changeCounter;                                                           /*!< Change the counter field unmute value to the audio input state characteristic */
} ClxUnmuteProcedure;

/**
The audio input control point characteristic mute procedure format
*/
typedef struct ClxMuteProcedure
{
    u1 changeCounter;                                                           /*!< Change the counter field mute value to the audio input state characteristic */
} ClxMuteProcedure;

/**
The audio input control point characteristic set manual gain mode procedure format
*/
typedef struct ClxSetManualGainModeProcedure
{
    u1 changeCounter;                                                           /*!< Change the counter field to set manual gain mode to the audio input state characteristic */
} ClxSetManualGainModeProcedure;

/**
The audio input control point characteristic set automatic gain mode procedure format
*/
typedef struct ClxSetAutomaticGainModeProcedure
{
    u1 changeCounter;                                                           /*!< Change the counter field to set automatic gain mode to the audio input state characteristic */
} ClxSetAutomaticGainModeProcedure;

/**
Audio input control point characteristic format
*/
typedef struct ClxAudioInputControlPoint
{
    u1 opcode;                                                                  /*!< Audio input control point Request opcode for specific procedure to be executed */

    union
    {
        ClxSetgainSettingProcedure          gainSetting;                        /*!< Gain setting mode procedure shall set to a value current gain of audio input signal*/
        ClxUnmuteProcedure                  unmute;                             /*!< The unmute procedure shall notify the new audio input state characteristic value */
        ClxMuteProcedure                    mute;                               /*!< The mute procedure shall notify the new audio input state characteristic value */
        ClxSetManualGainModeProcedure       manualGainMode;                     /*!< Manual gain mode procedure shall set to the gain mode manual */
        ClxSetAutomaticGainModeProcedure    automaticGainMode;                  /*!< Automatic gain mode procedure shall set to the gain mode automatic */
    } opcodeProcedure;

} ClxAudioInputControlPoint;

/**
Audio input description characteristic format.
*/
typedef struct ClxAudioInputDescription
{
    u1 audioInputSize[CLX_GATT_AUDIO_INPUT_LENGTH];                             /*!< Set to a description of the audio input */
} ClxAudioInputDescription;

typedef struct ClxBLEAudioConfigurationStruct
{
    /*
     * Codec Configuration Param
     */
    ClxBapCodecConfig           codecInfo;

    /*
     * Codec Specific Capabilities Params
     */
    ClxBapCodecCapabilities     capabilitiesInfo;

    /*
     * BLE Configuration Param
     */
    u4                          sduInterval;
    u2                          maxSdu;
    u2                          maxTransportLatency;
    u1                          retransmissions;
    u1                          advSID;
    u4                          presentationDelay;
    ClxBleIsoStream             bisOrCisStream;

    /*
     * Broadcast Based Params
     */
    u1                          bigID;
    u1                          numOfBIS;
    u1                          numberOfSubGrp;
    boolean                     bisActiveStatus;

    /*
     * Unicast Based Params
     */
    boolean                     cisConnectStatus;
    boolean                     setEnable2StreamingSts;
    u2                          supportedAudioContext;
    u2                          sinkAvailableAudioContext;
    u2                          sourceAvailableAudioContext;
    u2                          announcementType;
    u2                          numberOfPacRecords;
    u1                          numOfCIS;
    u1                          currentSinkAseCount;
    u1                          currentSourceAseCount;
    ClxBleRoleType              currentRole;
    u1                          cisActiveStatus;
    u1                          cisStreamID[MAX_SUPPORT_CIS_COUNT];
    ClxBapAudioStreamEndpoint   sinkAseRecords[ CLX_BLE_UNICAST_SUPPORTED_SINK_ASE_COUNT ];          /*!< It contain the Current Sink ASE role of ASE ID's */
    ClxBapAudioStreamEndpoint   sourceAseRecords[ CLX_BLE_UNICAST_SUPPORTED_SOURCE_ASE_COUNT ];      /*!< It contain the Current Source ASE role of ASE ID's */
} ClxBLEAudioConfiguration;

/**
Isochronous related API's. Refere the "ClxBleIsoInterface" structure in Iso.Ble.Interface.h file
*/
ClxResult isoInit             ( _in_ struct ClxBleIsoInterface* thisObj, _in_ u2 maxTxIsoFragmentLength                               );
void isoDestroy               ( _in_ struct ClxBleIsoInterface* thisObj                                                               );
void isoRxReceived            ( _in_ struct ClxBleIsoInterface* thisObj, _in_ struct ClxBleIsoRxBuffer* data, _in_ boolean isrContext );
void isoConnectionEstablished ( _in_ struct ClxBleIsoInterface* thisObj, _in_ const ClxBleIsoConnectionDetails* connectionDetails     );
void isoConnectionTerminated  ( _in_ struct ClxBleIsoInterface* thisObj, u2 isoConnectionHandle                                       );

/**
Register the Isochronous related API's using ISO Interface structure
*/
ClxBleIsoInterface* clxCreateIsoInterface ( void );

#ifdef __cplusplus
}
#endif

typedef enum ClxAppStreamChannelMode_Enum
{
    ClxAppStreamChannelMode_NotSet     = 0,
    ClxAppStreamChannelMode_Mono,
    ClxAppStreamChannelMode_Stereo
}ClxAppStreamChannelMode;

extern ClxAppStreamChannelMode streamChannelMode;

void getAudioChannelMode ( void );
void resetAudioChannelMode ( void );

/**
Handle Creation and deletion for ISO Server (BIS)
*/
void       bleCreateIsoServer ( ClxStack stack );
void       bleDeleteIsoServer ( void           );
ClxHandle  getIsoServerHandle ( void           );

/**
Handle Creation and deletion for ISO Client (CIS)
*/
void       bleCreateIsoClient ( ClxStack stack );
void       bleDeleteIsoClient ( void           );
ClxHandle  getIsoClientHandle ( void           );

/**
The following APIs have the definitions for both unicast and broadcast modes of the Bluetooth Low Energy Audio menu.
* Menu to display Bluetooth Low Energy Audio menu options
*/
void bluetoothLowEnergyAudioMenu             ( ClxStack stack );

/**
Get the actual Sampling Frequency value from the specification value.

\param value      Spec mentioned Sampling Frequency value.

\return  s4                  Actual Sampling Frequency.
*/
s4  getSamplingFrequencyFromValue ( u1 value );

/**
Get the codec format.

\param format      Spec mentioned codec format value.

\return  s1*                  Codec format.
*/
const s1* getCodecFormat(ClxBluetoothCodingFormat format);

/**
Get the global variable to store the Basic Audio Announcement of BIS

\return ClxBleAudioBISBasicAudioAnnouncement             BIS Basic Audio Announcement
*/
ClxBleAudioBISBasicAudioAnnouncement* clxBleAudioGetBISBasicAnnouncement ( void );

/**
Initialize the given Basic Audio Announcement Buffer by allocating the memory and setting the default values.

\param basicAnnouncement       Basic Audio Announcement Buffer

\return ClxResult        If its NULL then decode will failed.
                         #CLX_SUCCESS: successful decoding
                         #CLX_ERROR_INVALID_COMMAND_ARGUMENT: provided arguments are invalid.
*/
ClxResult clxBleAudioInitBasicAnnouncementBuffer (ClxBleAudioBISBasicAudioAnnouncement * basicAnnouncement);

/**
Deallocate the memory of the given Basic Audio Announcement Buffer and initialize it with default values.

\param basicAnnouncement       Basic Audio Announcement Buffer

\return ClxResult        If its NULL then decode will failed.
                         #CLX_SUCCESS: successful decoding
                         #CLX_ERROR_INVALID_COMMAND_ARGUMENT: provided arguments are invalid.
*/
ClxResult clxBleAudioDestroyBasicAnnouncementBuffer ( ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement );

/**
This call-back function is registered for the GAP and GATT profiles, * any events raised by GAP profile causes this call-back function executed with
the associated event and parameters

\param stack           Local device stack handle.
\param serviceHandle   Profile/service handle.
\param messageID       Indication id.
\param params          Void pointer to the indication parameters.
\param errorCode       Contains the error code.

\return boolean        TRUE If the call-back function handles indication or indication with *_COMPLETE Otherwise, return FALSE
 Note                  The API should be called in non blocking mode.
*/
boolean bleAudioStackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);

/**
Check the indication values and write the configured characteristics data into service data base.ss

\param characteristicHandle           Local device characteristic handle.
\param characteristicValue            Characteristic data.
\param characteristicValueLength      Characteristic data length.

\return ClxResult        If its NULL then decode will failed.
                         #CLX_SUCCESS: successful decoding
                         #CLX_ERROR_INVALID_HANDLE: provided arguments are invalid.
*/
ClxResult clxBLECheckAndWriteCharacteristicsInfo( u2            characteristicHandle,
                                                  const u1*     characteristicValue,
                                                  ClxSize       characteristicValueLength );

/**
Configure the audio capabilities in Source PAC characteristic

\param sourceOrSink  Used to declare Sink PAC or Source PAC { 1 - SINK & 2 - SOURCE }
*/
void setAudioCapabilities( void );

/**
Set the supported audio context type for Supported_Audio_Contexts characteristic
*/
void configureSupportedAudioContext( void );

/**
Available audio contexts characteristic defined in PACS to state which of its Supported Audio Context Types can
currently be used to establish an audio stream
*/
void configureAvailableAudioContexts( );

/**
Configure the Volume Control Service characteristic
*/
void configureVoulmeControl ( void );

/**
Configure the audio Stream End point
*/
ClxResult setAudioStreamEndPoint ( ClxBleRoleType sourceOrSink, u1 aseID, u1 opCode );

/**
Print the Basic Audio Announcement of BIS

\param basicAnnouncement       Basic Audio Announcement Buffer
*/
void clxBleAudioPrintBISBasicAnnouncement ( ClxBleAudioBISBasicAudioAnnouncement*   basicAnnouncement );

/**
Print the Data Based On Spec mentioned Structure Format like Codec Specific Configuration, Capability and Metadata info's

\param sourceBuffer       It contains data in the defined spec-based structure. and use the ClxBapConfigType enum to know config type.
\param sourceBufferType   Structure Format type enum
*/
void clxBleAudioPrintDataBasedOnSpecFormat ( void*                        sourceBuffer,
                                             ClxBleAudioSpecStructureType dataType );

/**
Validate the Data Based On Spec mentioned Structure Format like Codec Specific Configuration, Capability, Metadata info's , etc...

\param sourceBuffer       It contains data in the defined spec-based structure. and use the ClxBapConfigType enum to know config type.
\param sourceBufferType   Structure Format type enum

\return      TRUE  - Data is valid
             FALSE - Invalid Data
*/
boolean clxBleAudioCheckDataValidtyBasedOnSpecFormat ( void*                        sourceBuffer,
                                                       ClxBleAudioSpecStructureType dataType );


/**
Print the Data in Hex and Char

\param buffer       Raw buffer data to print in hex format
\param length       Raw buffer data length in bytes
*/
void printBufferHexAndChar( const u1* buffer, s4 length );

void bleInitAudioConfigParams ( boolean initOperation );

ClxBLEAudioConfiguration* clxGetBLEAudioConfigurationInfo ( void );


void clxBleGapDestroyExtAdvertisingBuffer ( ClxBleExtendedAdvertisingData*  extAdvBufferObj );

ClxResult clxBleSetupISODataPath ( ClxHandle                      handle,
                                   ClxBleIsoDataPathDirection     pathDirection,
                                   ClxBleIsoStreamType            streamType,
                                   u1                             numberOfStream,
                                   u1                             groupID,
                                   boolean                        block );

ClxResult clxBleRemoveISODataPath ( ClxHandle                      handle,
                                   ClxBleIsoDataPathDirection     pathDirection,
                                   ClxBleIsoStreamType            streamType,
                                   u1                             numberOfStream,
                                   u1                             groupID );

void bleAudioSetPeriodicSyncHandle ( u2 handle );

u2 bleAudioGetPeriodicSyncHandle ( void );

u1 aseGetASECountByRole ( ClxBleRoleType role );

u1 aseGetASEIDByRole ( ClxBleRoleType role, u1 index );

void clxBleBassInfoInit(void);

void clxBleBassInfoReset(void);

ClxBapBroadcastReceiveState* ClxBapBroadcastReceiveStateRecord ( void );

u1 getPreferredStreamId(void);

void setPreferredStreamId(u1 streamId);

u2 getPreferredStreamHandle(void);

void setPreferredStreamHandle(u2 streamHandle);

u1 getPreferredAudioCount(void);

void setPreferredAudioCount(u1 audioCount);

s4 getBitrate( void );

s2 getNumberOfChannels( void );

ClxBapAseOpCode* clxBleGetAseControlPoint( void );

void clxBleBapProfileMenu ( ClxStack stack, ClxBleGattRoleType gattRole );

ClxBapAudioStreamEndpoint* clxBleAppGetSinkAseRecord ( u1 aseIndex );

ClxBapAudioStreamEndpoint* clxBleAppGetSourceAseRecord ( u1 aseIndex );

void clxBleInitAudioParams ( void );

void clxBleTerminateAudioParams ( void );

void clxBleInitAseOpCodeInfo ( ClxBapAseOpCode* aseCntlPoint );

ClxResult clxBleInitBassMetadataBuffer ( u1 subGroupCount,
                                         ClxBapBroadcastReceiveState* receiveState,
                                         ClxBapBroadcastScanOpCode* bascontrolPoint );

void clxBleDeinitBassMetadataBuffer(ClxBapBroadcastReceiveState* receiveState, ClxBapBroadcastScanOpCode* bascontrolPoint);

u4 getCapSamplingFrequencyFromBitValue(u2 value);

s1* getCapFrameDurationFromBitValue(u1 value);

s1* getCodingFormatFromBitValue(u1 value);

ClxResult discoverAudioCapability( u2 characteristicUuid);

void discoverAudioContext( void );

#endif /* CLX_BLE_ISOCHRONOUS */

#endif /* __Ble_Audio_Common_h__ */

