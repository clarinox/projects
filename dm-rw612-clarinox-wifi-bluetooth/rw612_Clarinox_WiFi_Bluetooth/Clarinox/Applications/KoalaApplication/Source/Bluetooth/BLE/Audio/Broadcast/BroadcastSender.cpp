/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                BroadcastSender.cpp
* Description         This provides the GATT operations
*                     and menu option for BLE Broadcast audio source.
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
#include "BroadcastCommon.h"
#include "GattServer.h"
#include "Ble.Bap.Api.h"
#include "Ble.Pbp.Api.h"
#include "BleLc3Common.h"
#include "BleIso.h"

static ClxBleExtendedAdvertisingHandle bigAdvHandle = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;
extern ClxBleExtendedAdvertisingData          advBufferObj;
/**
To maintain the BIG Result
*/
ClxBleIsoServerEstablishBigResult      bigResult    = { };

extern s1 inputValue[MAX_INPUT_SIZE];

/**
Menu options used to invoke BLE Broadcast Source main menu
*/
typedef enum BleBroadcastSenderItemEnum
{
    BleBroadcastSenderMenuItem_StartAdvertising            = 1,
    BleBroadcastSenderMenuItem_StopAdvertising,
    BleBroadcastSenderMenuItem_ConfigBroadcastReceiveState,
    BleBroadcastSenderMenuItem_PrintLocalData,
    BleBroadcastSenderMenuItem_StartBIG,
    BleBroadcastSenderMenuItem_SetupISODataPath,
    BleBroadcastSenderMenuItem_Play,
    BleBroadcastSenderMenuItem_Pause,
    BleBroadcastSenderMenuItem_Next,
    BleBroadcastSenderMenuItem_Previous,
    BleBroadcastSenderMenuItem_RemoveISODataPath,
    BleBroadcastSenderMenuItem_StopBIG,
    BleBroadcastSenderMenuItem_ReturnToPreviousMenu,
    BleBroadcastSenderMenuItem_TotalItem

}BleBroadcastSenderMenuItem;

/************************************************** PROTOTYPES *********************************************************************/

ClxResult clxBleBroadcastSenderStartBIG          ( ClxStack stack                                                );

#if defined(CLX_FLOATINGPOINT_LC3)
ClxResult clxBleBroadcastSender( ClxStack stack );
#endif /* defined(CLX_FLOATINGPOINT_LC3) */

ClxResult clxBleBroadcastSenderStopBIG           ( ClxStack stack                                                );

void clxBleBroadcastSenderAddBIGInfo             ( ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement       );

void clxBleBroadcastSoureAddCodecAndMetadataInfo ( ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement       );


/***********************************************************************************************************************************/

/***********************************************************************************************************************************
*                                        BLE Broadcast Source Menu
*
* Menu to display Bluetooth Low Energy Broadcast Source main menu options
*
* \param stack      - ClarinoxBlue stack
*
************************************************************************************************************************************/
void bluetoothLowEnergyBroadcastSenderMenu ( ClxStack stack )
{
    ClxResult ret = CLX_FAIL;

    ClxBLEAudioConfiguration*     bleAudioConfig     = clxGetBLEAudioConfigurationInfo();
    ClxBapBroadcastReceiveState* bassLocReceiveState = ClxBapBroadcastReceiveStateRecord();

    if (stack == NULL)
    {
        clxConsoleUIEngineText("\nClarinox Stack has to be initialized first\n");
        return;
    }

    initAdvertisingData(clxGetBTLocalDeviceName());

    while ( TRUE )
    {
        const s1* menu =
                            "Start Extended Advertising\0"
                            "Stop Extended Advertising\0"
                            "Config Broadcast Receive State\0"
                            "Print Local Data\0"
                            "Start BIG\0"
                            "Setup ISO DataPath\0"
                            "Play\0"
                            "Pause\0"
                            "Next\0"
                            "Previous\0"
                            "Remove ISO DataPath\0"
                            "Stop BIG\0"
                            "Return to previous menu\0";

        u4 optionIndex = clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, BleBroadcastSenderMenuItem_TotalItem - 1);

        if ((FALSE == bleAudioConfig->bisActiveStatus ) && ( BleBroadcastSenderMenuItem_StartBIG < optionIndex && optionIndex < BleBroadcastSenderMenuItem_ReturnToPreviousMenu ) )
        {
            clxConsoleUIEngineText("\nPlease make sure to start the BLE BIG first by selection option#%u \n", BleBroadcastSenderMenuItem_StartBIG );
            continue;
        }

        switch ( optionIndex )
        {
            case BleBroadcastSenderMenuItem_StartAdvertising:
            {
                u1 flagAdvData     = CLX_BLE_AD_FLAG_GENERAL_DISCOVERABLE_MODE;
                u2 basServiceUUID = CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID;

                clxBleGapInitExtAdvertisingBuffer ( &advBufferObj );

                /* AD Flag */
                clxBleAddExtendedAdvertisingDataField(&advBufferObj,
                                                      CLX_BLE_GAP_AD_TYPE_FLAG,
                                                      (u1*)&flagAdvData,
                                                      (u1)sizeof(flagAdvData));

                /* Broadcast Audio Announcement Service */
                ret = clxBapAddBroadcastAudioAnnouncement ( bassLocReceiveState->broadcastId, &advBufferObj );

                if ( CLX_SUCCESS != ret )
                {
                    clxConsoleUIEngineText("\nclxBleEncodeBroadcastAudioExtendedAdvData failed with error %s\n", clxGetErrorCodeText(ret));
                    return;
                }

                /* Broadcast Audio Scan Service */
                clxBleAddExtendedAdvertisingDataField( &advBufferObj,
                                                       CLX_BLE_GAP_AD_TYPE_16_BIT_SERVICE_DATA,
                                                       (u1*)&basServiceUUID,
                                                       (u1)sizeof(basServiceUUID));

                /* Local device name */
                clxBleAddExtendedAdvertisingDataField( &advBufferObj,
                                                       CLX_BLE_GAP_AD_TYPE_COMPLETE_LOCAL_DEVICE_NAME,
                                                       (u1*)clxGetBTLocalDeviceName(),
                                                       (u1)strlen( clxGetBTLocalDeviceName() ) );

                bleStartExtendedAdvertising ( stack, &advBufferObj, TRUE);
            }
            break;

            case BleBroadcastSenderMenuItem_StopAdvertising:
            {
                bleStopExtendedAdvertising ( stack, &advBufferObj );

                clxBleGapDestroyExtAdvertisingBuffer ( &advBufferObj );
            }
            break;

            case BleBroadcastSenderMenuItem_ConfigBroadcastReceiveState:
            {
                ClxResult errCode  = CLX_SUCCESS;
                ClxSize filledLength = 0;

                errCode = clxBapEncodeBroadcastReceiveState( static_cast<const ClxBapBroadcastReceiveState*>(bassLocReceiveState),
                                                             (u1*)inputValue,
                                                             MAX_INPUT_SIZE,
                                                             &filledLength );

                if ( CLX_SUCCESS != errCode )
                {
                    clxConsoleUIEngineText("\nEncode Source PAC: status - %s\n", clxGetErrorCodeText(ret));
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
                    break;
                }
                else
                {
                    clxConsoleUIEngineText ( "BLE: BASS ReceiveState\n");
                    clxBleAudioPrintDataBasedOnSpecFormat ( (void*)bassLocReceiveState, ClxBleAudioSpecStructure_BASSReceiveState );
                }
            }
            break;

            case BleBroadcastSenderMenuItem_PrintLocalData:
            {
                clxBleAudioPrintDataBasedOnSpecFormat ( bassLocReceiveState, ClxBleAudioSpecStructure_BASSReceiveState );
            }
            break;

            case BleBroadcastSenderMenuItem_StartBIG:
            {
                u1 index  = 0;

                clxBleGapInitExtAdvertisingBuffer ( &advBufferObj );

                bleAudioConfig->bisOrCisStream.streamType    = ClxBleIsoStreamType_BIS;

                for ( index  = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
                {
                    /* Call init function to create the Audio Send thread */
                    bleInitAudioSendThread ( index );
                }
                
#if defined(CLX_FLOATINGPOINT_LC3)
                getAudioChannelMode();

                clxBleBroadcastSender(stack);
                clxConsoleUIEngineText("High Quality audio\n");
#else
                clxConsoleUIEngineText("Low Quality audio\n");
                clxBleBroadcastSenderStartBIG( stack );
#endif  /* CLX_FLOATINGPOINT_LC3 */
            }
            break;

            case BleBroadcastSenderMenuItem_SetupISODataPath:
            {
                ret = clxBleSetupISODataPath ( getIsoServerHandle(),
                                               ClxBleIsoDataPathDirection_Input,
                                               ClxBleIsoStreamType_BIS,
                                               bigResult.params.numberOfBis,
                                               CLX_BLE_AUDIO_BIG_ID,
                                               TRUE );
            }
            break;

            case BleBroadcastSenderMenuItem_Play:
            {
                u1 index = 0;

                for ( index  = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
                {
                    bleStartAudioSendProcess ( index );
                }
            }
            break;

            case BleBroadcastSenderMenuItem_Pause:
            {
                u1 index = 0;

                for ( index  = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
                {
                    clxConsoleUIEngineText( "\nBLE Audio sending Paused #%d {Status Changed[%u -> %u]}\n",
                                            index,
                                            bleGetAudioSendThreadState ( index ),
                                            ClxBleAudioPlayState_PAUSE );

                    bleSetAudioSendThreadState ( ClxBleAudioPlayState_PAUSE, index );
                }
            }
            break;

            case BleBroadcastSenderMenuItem_Next:
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

            case BleBroadcastSenderMenuItem_Previous:
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

            case BleBroadcastSenderMenuItem_RemoveISODataPath:
            {
                ret = clxBleRemoveISODataPath ( getIsoServerHandle(),
                                                ClxBleIsoDataPathDirection_Input,
                                                ClxBleIsoStreamType_BIS,
                                                bigResult.params.numberOfBis,
                                                CLX_BLE_AUDIO_BIG_ID );

                if ( CLX_SUCCESS != ret )
                {
                    clxConsoleUIEngineText ( "BLE Remove ISO Data Path Fail- %s\n", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BleBroadcastSenderMenuItem_StopBIG:
            {
                u1 index  = 0;

#if defined(CLX_FLOATINGPOINT_LC3)
                resetAudioChannelMode();
#endif  /* CLX_FLOATINGPOINT_LC3 */

                clxBleBroadcastSenderStopBIG ( stack );

                for ( index  = 0; index < CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT; ++index )
                {
                    bleDestroyAudioSendThread( index );
                }

                clxBleGapDestroyExtAdvertisingBuffer ( &advBufferObj );
            }
            break;

            case BleBroadcastSenderMenuItem_ReturnToPreviousMenu:
            {
                return;
            }
            break;

            default:
            {
                clxConsoleUIEngineText("\nPlease select a valid menu option..\n");
            }
            break;

        } /* switch ( index ) */

    } /* while ( TRUE ) */
}

/****************************************************************************************************************************************
*                                        clxBleBroadcastSenderStartBIG
*
* Frame and fill the BIG configuration params and audio announcement data then create the BIG on broadcaster side using API ClxBleIsoServerEstablishBigResult(..)
*
* \param stack              - Local device stack handle.
* 
* \return ClxResult 
*
****************************************************************************************************************************************/
ClxResult clxBleBroadcastSenderStartBIG ( ClxStack stack )
{
    ClxResult ret  = CLX_FAIL;
    u2 basServiceUUID = CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID;
    u1 flagAdvData = CLX_BLE_AD_FLAG_GENERAL_DISCOVERABLE_MODE;

    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    ClxBapBroadcastReceiveState *bassLocReceiveState = ClxBapBroadcastReceiveStateRecord();

    if (getIsoServerHandle())
    {
        ClxBleExtendedAdvertisingSetTypeFlags typeFlags;
        ClxBleAdvertisingSetInfo extAdvSet;

        /* First, start an extended advertising */
        if ( CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE != bigAdvHandle )
        {
            clxConsoleUIEngineText("\nBIG is Already Created");
            return ret;
        }

        u1 advSID = (u1)bassLocReceiveState->sourceAdvSid;

        typeFlags.connectable = FALSE;
        typeFlags.directed    = FALSE;
        typeFlags.highDuty    = FALSE;
        typeFlags.scannable   = FALSE;

        s1 selectedTxPower = 20;

        ret = clxGapBleSetExtendedAdvertisingParameters(stack,
                        bigAdvHandle,
                        3000,                                     /* _in_ u4                                  advertisingIntervalMin */
                        4000,                                     /* _in_ u4                                  advertisingIntervalMax */ 
                        0,                                        /* _in_ u4                                  advertisingFlags */ 
                        typeFlags,                                /* _in_ ClxBleExtendedAdvertisingSetTypeFlags   advertisingType */ 
                        ClxBleOwnAddressMode_Identity,            /* _in_ ClxBleOwnAddressMode                localAddressType */
                        NULL,                                     /* _user_in_ const ClxBleBdAddress*         peerAddress */
                        CLX_BLE_ALL_ADVERTISING_CHANNELS,         /* _in_ u1                                  primaryAdvertisingChannelsToUse */
                        ClxBleAdvertisingFilterPolicy_ScanConnectionAnyone, /* ClxBleAdvertisingFilterPolicy  advertisingFilterPolicy */
                        selectedTxPower,                          /* _in_ s1                                  advertisingTxPower */
                        ClxBlePhyType_1M,                         /* _in_ ClxBlePhyType                       primaryPhyType */
                        0,                                        /* _in_ u1                                  secondaryAdvertisignMaxSkip */
                        ClxBlePhyType_1M,                         /* _in_ ClxBlePhyType                       secondaryPhyType */
                        advSID,                                   /* _in_ u1                                  advertisingSID */
                        FALSE,                                    /* _in_ boolean                             enableScanRequestNotification */
                        ClxBlePhyOptions_NoPreference,            /* primary phy options */
                        ClxBlePhyOptions_NoPreference,            /* secondary phy options */
                        &bigAdvHandle,                            /* _user_out_ ClxBleExtendedAdvertisingHandle*     advertisingHandle */
                        &selectedTxPower,                         /* _user_out_ s1*                           selectedTxPower */
                        TRUE);                                    /* _in_ boolean                             block */

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxGapBleSetExtendedAdvertisingParameters failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        clxBleGapInitExtAdvertisingBuffer ( &advBufferObj );

        /* AD Flag */
        clxBleAddExtendedAdvertisingDataField(&advBufferObj,
                                              CLX_BLE_GAP_AD_TYPE_FLAG,
                                              (u1*)&flagAdvData,
                                              (u1)sizeof(flagAdvData));

        /* Broadcast Audio Announcement Service */
        ret = clxBapAddBroadcastAudioAnnouncement ( bassLocReceiveState->broadcastId, &advBufferObj );

        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nclxBleEncodeBroadcastAudioExtendedAdvData failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        /* Broadcast Audio Scan Service */
        basServiceUUID = CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID;
        clxBleAddExtendedAdvertisingDataField( &advBufferObj,
                                               CLX_BLE_GAP_AD_TYPE_16_BIT_SERVICE_DATA,
                                               (u1*)&basServiceUUID,
                                               (u1)sizeof(basServiceUUID));

        /* Local device name */
        clxBleAddExtendedAdvertisingDataField( &advBufferObj,
                                               CLX_BLE_GAP_AD_TYPE_COMPLETE_LOCAL_DEVICE_NAME,
                                               (u1*)clxGetBTLocalDeviceName(),
                                               (u1)strlen( clxGetBTLocalDeviceName() ) );

        /* Broadcast name */
        clxBleAddExtendedAdvertisingDataField( &advBufferObj,
                                               CLX_BLE_GAP_AD_TYPE_BROADCAST_NAME,
                                               (u1*)CLX_BLE_AUDIO_BROADCAST_NAME,
                                               (u1)strlen( CLX_BLE_AUDIO_BROADCAST_NAME ) );

        ret = clxGapBleSetExtendedAdvertisingData(
                                            stack,                                              /* stack                */
                                            bigAdvHandle,                                       /* advertisingHandle    */
                                            ClxBleAdvertisingDataType_Advertising,              /* dataType             */
                                            (u1*)advBufferObj.data,                             /* data                 */
                                            (u4)advBufferObj.dataLength,                        /* dataLength           */
                                            ClxBleAdvertisingFragmentPreference_DoNotFragment,  /* fragmentPreference   */
                                            TRUE                                                /* block                */
                                            );

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxGapBleSetExtendedAdvertisingData failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        extAdvSet.handle               = bigAdvHandle;
        extAdvSet.duration             = 0;
        extAdvSet.maxAdvertisingEvents = 0;
        ret = clxGapBleEnableDisableExtendedAdvertising(stack, &extAdvSet, 1, TRUE, TRUE);

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxGapBleEnable ExtendedAdvertising failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        /* Now, make the advertising set a periodic one: */
        ret = clxGapBleEnablePeriodicAdvertisingMode(stack, bigAdvHandle, 100, 200, 0, 0, 0, 0, 0, 0, TRUE);

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxGapBleEnablePeriodicAdvertisingMode failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        clxConsoleUIEngineText("\nPeriodic advertisement enabled successfully\n");

        /* Set the BIG info and configuration data as the advertising data */
        /* {{{ */
        memset ( advBufferObj.data, 0x00, sizeof(advBufferObj) );
        advBufferObj.dataLength = 0;

        ret = clxBleAudioInitBasicAnnouncementBuffer ( clxBleAudioGetBISBasicAnnouncement() );

        clxBleBroadcastSenderAddBIGInfo ( clxBleAudioGetBISBasicAnnouncement() );
        clxBleBroadcastSoureAddCodecAndMetadataInfo ( clxBleAudioGetBISBasicAnnouncement() );

        clxBleAudioPrintBISBasicAnnouncement( clxBleAudioGetBISBasicAnnouncement() );

        clxBleAddExtendedAdvertisingDataField( &advBufferObj, CLX_BLE_GAP_AD_TYPE_COMPLETE_LOCAL_DEVICE_NAME, (u1*)clxGetBTLocalDeviceName(), (u1)strlen(clxGetBTLocalDeviceName()) );

        ret  = clxBapAddBasicAudioAnnouncement ( clxBleAudioGetBISBasicAnnouncement(),
                                                 bleAudioConfig->numberOfSubGrp,
                                                 bleAudioConfig->numOfBIS,
                                                 &advBufferObj );

        if ( CLX_SUCCESS != ret )
        {
           clxConsoleUIEngineText("\n Adding basic audio annoucement failed with error %s\n", clxGetErrorCodeText(ret));
           return ret;
        }

        ret = clxGapBleSetExtendedAdvertisingData(
                                        stack,                                             /* stack              */
                                        bigAdvHandle,                                      /* advertisingHandle  */
                                        ClxBleAdvertisingDataType_PeriodicAdvertising,     /* dataType           */
                                        (u1*)advBufferObj.data,                            /* data               */
                                        (u4)advBufferObj.dataLength,                       /* dataLength         */
                                        ClxBleAdvertisingFragmentPreference_DoNotFragment, /* fragmentPreference */
                                        TRUE                                               /* block              */
                                        );

        if (ret != CLX_SUCCESS)
        {
           clxConsoleUIEngineText("\nExtended Periodic Advertising Data failed with error %s\n", clxGetErrorCodeText(ret));
           return ret;
        }

        clxConsoleUIEngineText("\nBasic Audio Announcement completed with %s\n", clxGetErrorCodeText(ret));

        /* }}} */
 
        /* Now, start a BIG over the periodic advertising set: */
        ClxBleBigServerParameters bigParams;
        boolean encryptionSts = FALSE;

        bigParams.bigID.value         = bleAudioConfig->bigID;
        bigParams.advertisingHandle   = bigAdvHandle;

        /* If want to config more than one BIS then set it on that field */
        bigParams.numOfBIS            = bleAudioConfig->numOfBIS;

        bigParams.sduInterval         = bleAudioConfig->sduInterval;

        /* MAx SDU size is must bigger than ISO data send packet size */
        bigParams.maxSdu              = bleAudioConfig->maxSdu;
        bigParams.maxTransportLatency = bleAudioConfig->maxTransportLatency;
        bigParams.retransmissions     = bleAudioConfig->retransmissions;

        bigParams.phys.phy_1M         = FALSE;
        bigParams.phys.phy_2M         = TRUE;
        bigParams.phys.phy_Coded      = FALSE;

        bigParams.packing             = ClxBleCigPacking_Sequential;
        bigParams.framing             = ClxBleCigFraming_Unframed;

        clxConsoleUIEngineInputBox ("Enter the BLE Audio Broadcast Encryption Status [ 0- Disable /1- Enable ]:", inputValue, sizeof(inputValue));
        encryptionSts = (u1)atoi(inputValue); 

        if ( 0 == encryptionSts )
        {
            bigParams.useEncryption       = FALSE;
        }
        else
        {
            u1 encryptionCode[CLX_BLE_BIG_BROADCAST_CODE + 1]  = CLX_BLE_AUDIO_BROADCAST_CODE;
            bigParams.useEncryption       = TRUE;
            memcpy ( &bigParams.broadcastCode, encryptionCode, CLX_BLE_BIG_BROADCAST_CODE );
        }

        clxMemSet ( &bigResult, 0x00, sizeof( ClxBleIsoServerEstablishBigResult ) );

        ret = clxBleIsoServerEstablishBig(getIsoServerHandle(), &bigParams, &bigResult, TRUE);

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxBleIsoServerEstablishBig failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        bleAudioConfig->bisActiveStatus = TRUE;

        clxConsoleUIEngineText("\nclxBleIsoServerEstablishBig BIG-Hdl[%u] ISO-Hdl[%u] SUCCESS with %s\n", bigAdvHandle, getIsoServerHandle(), clxGetErrorCodeText(ret) );
     }

    return ret;
}

#if defined(CLX_FLOATINGPOINT_LC3)
/* TODO: Need to modify based on bitrate. Currently, it is configured for Sam.Freq 48000 Hz, Frame duration 10 ms and bitrate as 80 kbps */
void fillBasicAudioAnnouncement(ClxBleExtendedAdvertisingData* advData)
{
/* Based on the Assigned number spec section 6.12.1 */
#   define FRONT_LEFT      0x01
#   define FRONT_RIGHT     0x02

    u1 index = 0;
    u2 uuid = CLX_GATT_BASIC_AUDIO_ANNOUNCEMENT_UUID;
    u2 octectPerCodecFrame = (s2)((getBitrate() * ((CLX_BLE_AUDIO_FRAME_DURATION/10))) / 
                                    (1000 * 8 * getNumberOfChannels()));
    u4 audioChannelLocation = 0;

    /* 
    If mono, set the audio location to "Mono/Center Channel" - bit 3 (value 4)
    else if stereo, set the audio location to "Left" - bit 0 and "Right" - bit 1
    */
    if (1 == getNumberOfChannels())
    {
        audioChannelLocation = FRONT_LEFT;
    }
    else
    {
        audioChannelLocation = (FRONT_LEFT | FRONT_RIGHT);
    }

    /* Length */
    advData->data[index ++] = 0x21;     // Audio announcement length
    
    /* Type */
    advData->data[index ++] = 0x16;     // UUID type for Basic Audio Announcement
    
    /* uuid */
    advData->data[index ++] = uuid & 0xff;
    advData->data[index ++] = (uuid >> 8) & 0xff;
    
    /* Presentation delay */
    advData->data[index ++] = 0x00;
    advData->data[index ++] = 0x00;
    advData->data[index ++] = 0x00;
    
    /* no.of sub group */
    advData->data[index ++] = 0x01;     // Number of sub.group
    
    /* no of bis */
    advData->data[index ++] = 0x01;     // Number of bis
    
    /* codec id */
    advData->data[index ++] = 0x06;     // LC3
    advData->data[index ++] = 0x00;
    advData->data[index ++] = 0x00;
    advData->data[index ++] = 0x00;
    advData->data[index ++] = 0x00;
    
    /* codec config length */
    advData->data[index ++] = 0x0a;
    
    /* Sampling frequency */
    advData->data[index ++] = 0x02;       // length
    advData->data[index ++] = 0x01;       // type
    advData->data[index ++] = 0x08;       // 48000 Hz
    
    /* Frame duration */
    advData->data[index ++] = 0x02;       // length
    advData->data[index ++] = 0x02;       // type
    advData->data[index ++] = 0x01;       // 10 ms
    
    /* Octect per codec frame */
    advData->data[index ++] = 0x03;       // length
    advData->data[index ++] = 0x04;       // type
    advData->data[index ++] = octectPerCodecFrame & 0xff;
    advData->data[index ++] = (octectPerCodecFrame >> 8) & 0xff;
    
    /* Meta data length */
    advData->data[index ++] = 0x00;

    /* Bis Index */
    advData->data[index ++] = 0x01;
    
    /* codec specific configuration */
    advData->data[index ++] = 0x06;
    
    /* Audio channel allocation */
    advData->data[index ++] = 0x05;       // length
    advData->data[index ++] = 0x03;       // type
    advData->data[index ++] = audioChannelLocation & 0xff;
    advData->data[index ++] = (audioChannelLocation >> 8) & 0xff;
    advData->data[index ++] = (audioChannelLocation >> 16) & 0xff;
    advData->data[index ++] = (audioChannelLocation >> 24) & 0xff;
    
    advData->dataLength = index;
}

ClxResult clxBleBroadcastSender( ClxStack stack )
{
    ClxResult ret  = CLX_FAIL;

    if (getIsoServerHandle())
    {
        ClxBleExtendedAdvertisingSetTypeFlags typeFlags;
        ClxBleAdvertisingSetInfo extAdvSet;

        ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

        /* First, start an extended advertising */
        if ( CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE != bigAdvHandle )
        {
            clxConsoleUIEngineText("\nBIG is Already Created");
            return ret;
        }

        u1 advSID = (u1)0x01;

        typeFlags.connectable = FALSE;
        typeFlags.directed    = FALSE;
        typeFlags.highDuty    = FALSE;
        typeFlags.scannable   = FALSE;

        s1 selectedTxPower = 20;

        ret = clxGapBleSetExtendedAdvertisingParameters(stack,
                        bigAdvHandle,
                        50,                                       /* _in_ u4                                  advertisingIntervalMin */
                        100,                                      /* _in_ u4                                  advertisingIntervalMax */ 
                        0,                                        /* _in_ u4                                  advertisingFlags */ 
                        typeFlags,                                /* _in_ ClxBleExtendedAdvertisingSetTypeFlags   advertisingType */ 
                        ClxBleOwnAddressMode_Identity,            /* _in_ ClxBleOwnAddressMode                localAddressType */
                        NULL,                                     /* _user_in_ const ClxBleBdAddress*         peerAddress */
                        CLX_BLE_ALL_ADVERTISING_CHANNELS,         /* _in_ u1                                  primaryAdvertisingChannelsToUse */
                        ClxBleAdvertisingFilterPolicy_ScanConnectionAnyone, /* ClxBleAdvertisingFilterPolicy  advertisingFilterPolicy */
                        selectedTxPower,                          /* _in_ s1                                  advertisingTxPower */
                        ClxBlePhyType_1M,                         /* _in_ ClxBlePhyType                       primaryPhyType */
                        0,                                        /* _in_ u1                                  secondaryAdvertisignMaxSkip */
                        ClxBlePhyType_1M,                         /* _in_ ClxBlePhyType                       secondaryPhyType */
                        advSID,                                   /* _in_ u1                                  advertisingSID */
                        FALSE,                                    /* _in_ boolean                             enableScanRequestNotification */
                        ClxBlePhyOptions_NoPreference,            /* primary phy options */
                        ClxBlePhyOptions_NoPreference,            /* secondary phy options */
                        &bigAdvHandle,                            /* _user_out_ ClxBleExtendedAdvertisingHandle*     advertisingHandle */
                        &selectedTxPower,                         /* _user_out_ s1*                           selectedTxPower */
                        TRUE);                                    /* _in_ boolean                             block */

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxGapBleSetExtendedAdvertisingParameters failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        clxBleGapInitExtAdvertisingBuffer ( &advBufferObj );

        /* Broadcast Audio Announcement Service */
        ret = clxBapAddBroadcastAudioAnnouncement ( 0x5b5501, &advBufferObj );

        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nclxBapAddBroadcastAudioAnnouncement failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        /* Public Broadcast Announcement Service */
        ret = clxBlePbpAddAnnouncement(0x04, 0, NULL, &advBufferObj);
        if ( CLX_SUCCESS != ret )
        {
            clxConsoleUIEngineText("\nclxBlePbpAddAnnouncement failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        /* TMAP Role */
        clxGapBleSetAudioRole(ClxBleAudioRole_BroadcastMediaSender, &advBufferObj);

        /* Broadcast name */
        clxBleAddExtendedAdvertisingDataField( &advBufferObj,
                                               CLX_BLE_GAP_AD_TYPE_BROADCAST_NAME,
                                               (u1*)CLX_BLE_AUDIO_BROADCAST_NAME,
                                               (u1)strlen( CLX_BLE_AUDIO_BROADCAST_NAME ) );

        ret = clxGapBleSetExtendedAdvertisingData(
                                            stack,                                              /* stack                */
                                            bigAdvHandle,                                       /* advertisingHandle    */
                                            ClxBleAdvertisingDataType_Advertising,              /* dataType             */
                                            (u1*)advBufferObj.data,                             /* data                 */
                                            (u4)advBufferObj.dataLength,                        /* dataLength           */
                                            ClxBleAdvertisingFragmentPreference_DoNotFragment,  /* fragmentPreference   */
                                            TRUE                                                /* block                */
                                            );

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxGapBleSetExtendedAdvertisingData failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        extAdvSet.handle               = bigAdvHandle;
        extAdvSet.duration             = 0;
        extAdvSet.maxAdvertisingEvents = 0;
        ret = clxGapBleEnableDisableExtendedAdvertising(stack, &extAdvSet, 1, TRUE, TRUE);

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxGapBleEnable ExtendedAdvertising failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        /* Now, make the advertising set a periodic one: */
        ret = clxGapBleEnablePeriodicAdvertisingMode(stack, bigAdvHandle, 50, 100, 0, 0, 0, 0, 0, 0, TRUE);

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxGapBleEnablePeriodicAdvertisingMode failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        clxConsoleUIEngineText("\nPeriodic advertisement enabled successfully\n");

        /* Set the BIG info and configuration data as the advertising data */
        /* {{{ */
        memset ( advBufferObj.data, 0x00, sizeof(advBufferObj) );
        fillBasicAudioAnnouncement(&advBufferObj);
            
        ret = clxGapBleSetExtendedAdvertisingData(
                                        stack,                                             /* stack              */
                                        bigAdvHandle,                                      /* advertisingHandle  */
                                        ClxBleAdvertisingDataType_PeriodicAdvertising,     /* dataType           */
                                        (u1*)advBufferObj.data,                            /* data               */
                                        (u4)advBufferObj.dataLength,                       /* dataLength         */
                                        ClxBleAdvertisingFragmentPreference_DoNotFragment, /* fragmentPreference */
                                        TRUE                                               /* block              */
                                        );

        if (ret != CLX_SUCCESS)
        {
           clxConsoleUIEngineText("\nExtended Periodic Advertising Data failed with error %s\n", clxGetErrorCodeText(ret));
           return ret;
        }

        clxConsoleUIEngineText("\nBasic Audio Announcement completed with %s\n", clxGetErrorCodeText(ret));

        /* }}} */
 
        /* Now, start a BIG over the periodic advertising set: */
        ClxBleBigServerParameters bigParams;
        boolean encryptionSts = FALSE;

        bigParams.bigID.value         = 0x01;           // Big Id
        bigParams.advertisingHandle   = bigAdvHandle;

        /* If want to config more than one BIS then set it on that field */
        bigParams.numOfBIS            = 0x01;           // Number of BIS

        /* Based on BAP Spec, 6.3 Broadcast Audio Stream configuration */
        /* TODO: Need to modify based on bitrate. Currently, it is configured for Sam,Freq 48000 Hz, Frame duration 10 ms and Bit rate as 80 kbps */
        bigParams.sduInterval         = 10000;          // Interval

#if defined(CLX_FLOATINGPOINT_LC3)
        bigParams.maxSdu              = (u2)((getBitrate() * ((CLX_BLE_AUDIO_FRAME_DURATION/10))) / (1000 * 8));
#else
        bigParams.maxSdu              = 0x64;           // Max SDU
#endif  /* CLX_FLOATINGPOINT_LC3 */

        bigParams.maxTransportLatency = 0x14;           // Max Latency
        bigParams.retransmissions     = 0x01;           // Retransmission

        bigParams.phys.phy_1M         = FALSE;
        bigParams.phys.phy_2M         = TRUE;
        bigParams.phys.phy_Coded      = FALSE;

        bigParams.packing             = ClxBleCigPacking_Sequential;
        bigParams.framing             = ClxBleCigFraming_Unframed;

        clxConsoleUIEngineInputBox ("Enter the BLE Audio Broadcast Encryption Status [ 0- Disable /1- Enable ]:", inputValue, sizeof(inputValue));
        encryptionSts = (u1)atoi(inputValue); 

        if ( 0 == encryptionSts )
        {
            bigParams.useEncryption       = FALSE;
        }
        else
        {
            u1 encryptionCode[CLX_BLE_BIG_BROADCAST_CODE + 1]  = CLX_BLE_AUDIO_BROADCAST_CODE;
            bigParams.useEncryption       = TRUE;
            memcpy ( &bigParams.broadcastCode, encryptionCode, CLX_BLE_BIG_BROADCAST_CODE );
        }

        clxMemSet ( &bigResult, 0x00, sizeof( ClxBleIsoServerEstablishBigResult ) );

        ret = clxBleIsoServerEstablishBig(getIsoServerHandle(), &bigParams, &bigResult, TRUE);

        if (ret != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nclxBleIsoServerEstablishBig failed with error %s\n", clxGetErrorCodeText(ret));
            return ret;
        }

        bleAudioConfig->bisActiveStatus = TRUE;
     }

    return ret;
}
#endif /* defined(CLX_FLOATINGPOINT_LC3) */

/****************************************************************************************************************************************
*                                        clxBleBroadcastSenderStopBIG
*
* Terminate the BIG on broadcaster side using API ClxBleIsoServerEstablishBigResult(..)
*
* \param stack  - Local device stack handle.
* 
* \return ClxResult 
*
****************************************************************************************************************************************/

ClxResult clxBleBroadcastSenderStopBIG ( ClxStack stack )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();

    ClxBleIsoGroupID bigID;
    bigID.value = bleAudioConfig->bigID;

    ClxResult ret = clxBleIsoServerTerminateBig( getIsoServerHandle(), bigID, CLX_ERROR_HCI_CONNECTION_TERMINATED_BY_LOCAL_HOST, TRUE );

    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nclxBleIsoServerTerminateBig failed with error %s\n", clxGetErrorCodeText(ret));

        bleAudioConfig->bisActiveStatus = FALSE;

        return ret;
    }

    ret = clxGapBleDisablePeriodicAdvertisingMode(stack, bigAdvHandle, TRUE);

    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nclxGapBleDisablePeriodicAdvertisingMode failed with error %s\n", clxGetErrorCodeText(ret));
        return ret;
    }

    ClxBleAdvertisingSetInfo extAdvSet;
    extAdvSet.handle               = bigAdvHandle;
    extAdvSet.duration             = 0;
    extAdvSet.maxAdvertisingEvents = 0;

    ret = clxGapBleEnableDisableExtendedAdvertising(stack, &extAdvSet, 1, FALSE, TRUE);

    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nclxGapBleEnableDisableExtendedAdvertising failed with error %s\n", clxGetErrorCodeText(ret));
        return ret;
    }

    ret = clxGapBleRemoveExtendedAdvertisingSet ( stack, bigAdvHandle, TRUE );

    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nclxGapBleRemoveExtendedAdvertisingSet failed with error %s\n", clxGetErrorCodeText(ret));
        return ret;
    }

    clxBleGapDestroyExtAdvertisingBuffer ( &advBufferObj );

#if !defined(CLX_FLOATINGPOINT_LC3)
    ret = clxBleAudioDestroyBasicAnnouncementBuffer ( clxBleAudioGetBISBasicAnnouncement() );
#endif /* !defined(CLX_FLOATINGPOINT_LC3) */

    clxConsoleUIEngineText("\nBLE Broadcast Source Terminate: status - %s\n", clxGetErrorCodeText(ret));

    bigAdvHandle = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;
    bleAudioConfig->bisActiveStatus = FALSE;
    return ret;
}

/****************************************************************************************************************************************
*                                            clxBleBroadcastSenderAddBIGInfo
*
* Used for fill the user configured BIG info into the extended advertising data buffer.
* Note: User must allocate the advertising data with sufficient size and fill the size on actual size field.
*
* \param[  out  ] basicAnnouncement     Source buffer with BIG info to set on advertising buffer
* 
****************************************************************************************************************************************/
void clxBleBroadcastSenderAddBIGInfo ( ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();
    if ( NULL == basicAnnouncement ) { return; }

    ClxBleAudioUserBigInfo* bigInfo = &basicAnnouncement->bigInfo;

    basicAnnouncement->bigInfoAvailStatus      = TRUE;

    bigInfo->bigOffset             =    100;
    bigInfo->bigOffsetUnits        =    0;
    bigInfo->isoInterval           =    100;
    bigInfo->numberOfBIS           =    bleAudioConfig->numOfBIS;
    bigInfo->numberOfSubEvent      =    2;
    bigInfo->burstNumber           =    1;
    bigInfo->subInterval           =    100;
    bigInfo->pto                   =    10;
    bigInfo->bisSpacing            =    100;
    bigInfo->irc                   =    2;
    bigInfo->maxPDU                =    10;
    bigInfo->rfu                   =    1 << 7;

    /* Set seed Access Address as 0 */
    bigInfo->seedAccessAddress     =    0x00;

    bigInfo->sduInterval           =    bleAudioConfig->sduInterval;

    /* MAX SDU size is must bigger than ISO data send packet size */
    /* Set MAX SDU size as 50 */
    bigInfo->maxSDU                =    bleAudioConfig->maxSdu;

    bigInfo->baseCRCInit           =    0;

    bigInfo->chM[ 0 ]             =    CLX_BLE_ALL_ADVERTISING_CHANNELS;
    bigInfo->chM[ 1 ]             =    0x00;
    bigInfo->chM[ 2 ]             =    0x00;
    bigInfo->chM[ 3 ]             =    0x00;
    bigInfo->chM[ 4 ]             =    0x00;

    bigInfo->phy                   =    ClxBlePhyType_1M;

    u4 locBISPayloadCount = 10;
    bigInfo->bisPayloadCount[ 0 ] =    (u1)locBISPayloadCount;
    bigInfo->bisPayloadCount[ 1 ] =    0;
    bigInfo->bisPayloadCount[ 2 ] =    0;
    bigInfo->bisPayloadCount[ 3 ] =    0;
    bigInfo->bisPayloadCount[ 4 ] =    0;

    bigInfo->framing               =    ClxBleCigFraming_Unframed;
    bigInfo->giv                   =    0;
    bigInfo->gskd                  =    0;
}

/****************************************************************************************************************************************
*                                           clxBleBroadcastSoureAddCodecAndMetadataInfo
*
* Used for fill the user configured Codec and metadata into the extended advertising data buffer.
* Note: User must allocate the advertising data with sufficient size and fill the size on actual size field.
*
* \param[  out  ] basicAnnouncement   Source buffer to set the Basic Audio Announcements on advertising buffer of BIS parameters
* 
****************************************************************************************************************************************/
void clxBleBroadcastSoureAddCodecAndMetadataInfo ( ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement )
{
    ClxBLEAudioConfiguration* bleAudioConfig = clxGetBLEAudioConfigurationInfo();
    u1 subgrpIndex                    = 0,
       bisIndex                       = 0;

    ClxBleAudioBISSpecificCodecInfo* bisInfo = NULL;

    if ( NULL == basicAnnouncement) { return; }

    clxConsoleUIEngineText("\nBasic Audio Announcement starts\n");

    basicAnnouncement->serviceUUID = CLX_GATT_BASIC_AUDIO_ANNOUNCEMENT_UUID;

    /* Presentation delay */
    basicAnnouncement->presentationDelay[ 0 ] =  0x00;
    basicAnnouncement->presentationDelay[ 1 ] =  0x9C;
    basicAnnouncement->presentationDelay[ 2 ] =  0x40;

    /* No. Of sub-grps */
    basicAnnouncement->numberOfSubGrp          = bleAudioConfig->numberOfSubGrp;

    /* Set Sub-Group#1 Info */
    for ( subgrpIndex = 0; subgrpIndex < basicAnnouncement->numberOfSubGrp; ++subgrpIndex )
    {
        ClxBleAudioBISSubGroup* subGrp = ( basicAnnouncement->subGrp + subgrpIndex );

        /* No. Of BISes */
        subGrp->numberOfBIS              = bleAudioConfig->numOfBIS;

        /* Codec ID */
        subGrp->codecId.format           = CLX_BLE_AUDIO_CODEC_FORMAT;
        subGrp->codecId.companyID        = CLX_BLE_AUDIO_CODEC_COMPANY_ID;
        subGrp->codecId.vendorSpecificID = CLX_BLE_AUDIO_CODEC_VENDOR_SPECIFIC_ID;

        /* << Set codec Specification Configurations >> */
        {
            ClxBapCodecConfig* codecInfo = &subGrp->codecInfoForSubGrpSpecific;

            /* LTV 1 : Sampling Frequency LTV structure */
            if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.samplingFrequency )
            {
                /* Sampling Frequency LTV structure Value as 48000 Hz  */
                codecInfo->samplingFrequency    = bleAudioConfig->codecInfo.samplingFrequency;
            }

            /* LTV 2 : Frame Duration LTV structure */
            if ( CLX_BAP_INVALID_FIELD_U8 != bleAudioConfig->codecInfo.frameDuration )
            {
                /* Frame Duration LTV structure Value */
                codecInfo->frameDuration        = bleAudioConfig->codecInfo.frameDuration;
            }

            /* LTV 3 : Audio channel Allocation LTV structure */
            if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.channelAllocation )
            {
                /* Audio channel Allocation LTV structure Value */
                codecInfo->channelAllocation     = bleAudioConfig->codecInfo.channelAllocation;
            }

            /* LTV 4 : Octets Per Codec Frame LTV structure */
            if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.frameLength )
            {
                /* Octets Per Codec Frame LTV structure Value */
                codecInfo->frameLength       = bleAudioConfig->codecInfo.frameLength;
            }

            /* LTV 5 : Codec Frames per SDU LTV structure */
            if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.framesPerSdu )
            {
                /* Codec Frames per SDU LTV structure Value */
                codecInfo->framesPerSdu      = bleAudioConfig->codecInfo.framesPerSdu;
            }
        }

        ClxBapAudioMetadataLtv* metadataInfo = &subGrp->metadata;

        /* 2 LTV structures for Subgroup[0], defining: as below */
        /* << Set MetaData Configurations >> */
        if ( metadataInfo )
        {
            /* MetaData LTV 1: Streaming Audio Contexts: */
            /* Streaming Audio Contexts LTV structure Value as MEDIA */
            metadataInfo->streamingAudioContexts = 0x04;

            /* MetaData LTV 2: Language: */
            /* Language LTV structure Value as English("eng") */
            metadataInfo->languageCode[ 0 ] = 'g';
            metadataInfo->languageCode[ 1 ] = 'n';
            metadataInfo->languageCode[ 2 ] = 'e';

            /* MetaData LTV 3: Program_Info: */
            metadataInfo->programTitle[ 0 ] = 2;
            /* Program_Info LTV structure Value */
            metadataInfo->programTitle[ 1 ] = 0x04;
            metadataInfo->programTitle[ 2 ] = 0x00;
        }

        for ( bisIndex = 0; bisIndex < subGrp->numberOfBIS; ++bisIndex )
        {
            bisInfo = ( subGrp->bisSpecificInfo + bisIndex );

            /* BIS index reference */
            bisInfo->bisIndex = bisIndex + 1;

            /* << Set codec Specification Configurations >> */
            {
                ClxBapCodecConfig* bisCodec = &bisInfo->codecInfoForBISSpecific;

                /* BIS index :[bisIndex]*/
                /* LTV structure: */
                /* Sampling Frequency LTV structure Length */
                /* LTV 1 : Audio Channel Allocation LTV structure Index :0*/
                if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.samplingFrequency )
                {
                    /* Sampling Frequency structure Value as Front Left */
                    bisCodec->samplingFrequency = bleAudioConfig->codecInfo.samplingFrequency;
                }

                /* LTV 2 : Frame Duration LTV structure */
                if ( CLX_BAP_INVALID_FIELD_U8 != bleAudioConfig->codecInfo.frameDuration )
                {
                    /* Frame Duration LTV structure Value */
                    bisCodec->frameDuration     = bleAudioConfig->codecInfo.frameDuration;
                }

                /* LTV 3 : Audio channel Allocation LTV structure */
                if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.channelAllocation )
                {
                    /* Audio channel Allocation LTV structure Value */
                    bisCodec->channelAllocation      = bleAudioConfig->codecInfo.channelAllocation;
                }

                /* LTV 5 : Codec Frames per SDU LTV structure */
                if ( CLX_BAP_NULL_BYTE != bleAudioConfig->codecInfo.framesPerSdu )
                {
                    /* Codec Frames per SDU LTV structure Value */
                    bisCodec->framesPerSdu       = bleAudioConfig->codecInfo.framesPerSdu;
                }
            }
        }
    }
}
#endif /* CLX_BLE_ISOCHRONOUS */

