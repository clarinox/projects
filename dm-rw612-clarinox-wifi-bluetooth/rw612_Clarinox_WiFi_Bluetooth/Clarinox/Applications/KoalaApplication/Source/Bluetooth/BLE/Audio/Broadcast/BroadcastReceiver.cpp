/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                BroadcastReceiver.cpp
* Description         This provides the GATT operations
*                     and menu option for BLE Broadcast audio Receiver.
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
#include "Ble.Bap.Api.h"
#include "Iso.Ble.Client.Api.h"
#include "GattApp.h"
#include "GattClient.h"
#include "BleLc3Common.h"
#include "BleIso.h"

#include <stdio.h>
#include <stdlib.h>

/**
Menu options used to invoke BLE Broadcast Receiver main menu 
*/
typedef enum BroadcastReceiverItemEnum
{
    BroadcastReceiverMenuItem_StartExtendedScan                    = 1,
    BroadcastReceiverMenuItem_StopExtendedScan,
    BroadcastReceiverMenuItem_StartExtendedAdvertising,
    BroadcastReceiverMenuItem_StopExtendedAdvertising,
    BroadcastReceiverMenuItem_PrintAdvertisingData,
    BroadcastReceiverMenuItem_SyncPeriodicAdvertTrain,
    BroadcastReceiverMenuItem_CreateBIGSync,
    BroadcastReceiverMenuItem_BIGSyncTerminate,
    BroadcastReceiverMenuItem_ReturnToPreviousMenu,
    BroadcastReceiverMenuItem_TotalItem

}BroadcastReceiverMenuItem;

extern s1 inputValue[MAX_INPUT_SIZE];
extern ClxBleExtendedAdvertisingData advBufferObj;

ClxResult clxBleBassConfigureBroadcastReceiveState(void)
{
    ClxBapBroadcastReceiveState* receiveState = ClxBapBroadcastReceiveStateRecord();
    receiveState->bigEncryptionState = ClxBapBIGEncryptionCodeStatus_BroadcastCodeRequired;

    return CLX_SUCCESS;
}

void selectPreferredAudio(ClxBleAudioBISBasicAudioAnnouncement* bisBasicAnnouncement, u1 prefCount)
{
    u1 bisStreamId = 0;
    u4 audioCount  = 0;
    u4 loop = 0;

    for (u4 groupIndex = 0; groupIndex < bisBasicAnnouncement->numberOfSubGrp; groupIndex++)
    {
        u1 noOfBis = bisBasicAnnouncement->subGrp[groupIndex].numberOfBIS;

        for (loop = 0; loop < noOfBis; loop++)
        {
            audioCount = bisBasicAnnouncement->subGrp[groupIndex].bisSpecificInfo[loop].codecInfoForBISSpecific.channelAllocation;

            if (prefCount == audioCount)
            {
                bisStreamId = bisBasicAnnouncement->subGrp[groupIndex].bisSpecificInfo[loop].bisIndex;
                break;
            }
        }
    }

    clxConsoleUIEngineText("\nPreferred BIS is %u and its audio channel is %u\n", bisStreamId, audioCount);

    setPreferredStreamId(bisStreamId);
    setPreferredAudioCount((u1)audioCount);
}

/***************************************************************************************************************************************
*                                                BLE Broadcast Receiver Menu
*
* Menu to display Bluetooth Low Energy Broadcast Receiver main menu options
*
* \param stack      - ClarinoxBlue stack
*
****************************************************************************************************************************************/
void bluetoothLowEnergyBroadcastReceiverMenu ( ClxStack stack )
{
    ClxResult ret = CLX_FAIL;

    if (stack == NULL)
    {
        clxConsoleUIEngineText("\nClarinox Stack has to be initialized first\n");
        return;
    }

    if ( NULL == getIsoClientHandle() )
    {
        clxConsoleUIEngineText("\nIsochronous Client creation failed\n");
    }
    
    ClxBapBroadcastReceiveState *bassLocReceiveState = ClxBapBroadcastReceiveStateRecord();

    while ( TRUE )
    {
        const s1* menu =
                            "Scan for Broadcaster\0"
                            "Stop Scan\0"
                            "Start Extended Advertising\0"
                            "Stop Extended Advertising\0"
                            "Print Advertising Data\0"
                            "Sync Periodic Advertising Train\0"
                            "Create BIG Sync\0"
                            "BIG Sync Terminate\0"
                            "Return to previous menu\0";

        u4 index = clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, BroadcastReceiverMenuItem_TotalItem - 1);

        ClxBleAudioBISBasicAudioAnnouncement* basic = clxBleAudioGetBISBasicAnnouncement();

        if ((NULL == basic->subGrp ) && ( BroadcastReceiverMenuItem_StartExtendedScan != index && index < BroadcastReceiverMenuItem_ReturnToPreviousMenu ) )
        {
            clxConsoleUIEngineText("\nPlease make sure to initialize the BLE Sink menu first\n");
            continue;
        }

        switch ( index )
        {
            case BroadcastReceiverMenuItem_StartExtendedScan:
            {
                ClxBLEAudioConfiguration*     bleAudioConfig      = clxGetBLEAudioConfigurationInfo();

#if !defined ( CLX_LC3_SINK )
                clxConsoleUIEngineText("\nPlease make sure to enable CLX_LC3_SINK\n");
#endif /* ! CLX_LC3_SINK */
                ret = clxBleAudioInitBasicAnnouncementBuffer ( clxBleAudioGetBISBasicAnnouncement() );

                bassLocReceiveState->broadcastId = CLX_BLE_AUDIO_INVALID_BROADCAST_ID;

                clxBleGapInitExtAdvertisingBuffer(&advBufferObj);

                bleAudioConfig->bisOrCisStream.streamType    = ClxBleIsoStreamType_BIS;

                clxConsoleUIEngineText("\nBLE Broadcast Receiver Initialize: status - %s\n", clxGetErrorCodeText(ret));

                resetRemoteDeviceList();

                startExtendedScan(stack, FALSE);
            }
            break;

            case BroadcastReceiverMenuItem_StopExtendedScan:
            {
                ret = clxGapBleDisableExtendedScan(stack, TRUE);
                clxConsoleUIEngineText("\nclxGapBleDisableExtendedScan: status - %s\n", clxGetErrorCodeText(ret));
            }
            break;

            case BroadcastReceiverMenuItem_StartExtendedAdvertising:
            {
                u1 flagAdvData    = CLX_BLE_AD_FLAG_GENERAL_DISCOVERABLE_MODE;
                u2 basServiceUUID = CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID;

                /* AD Flag */
                clxBleAddExtendedAdvertisingDataField(&advBufferObj,
                                                      CLX_BLE_GAP_AD_TYPE_FLAG,
                                                      (u1*)&flagAdvData,
                                                      (u1)sizeof(flagAdvData));

                /* Broadcast Audio Scan Service */
                clxBleAddExtendedAdvertisingDataField(&advBufferObj,
                                                      CLX_BLE_GAP_AD_TYPE_16_BIT_SERVICE_DATA,
                                                      (u1*)&basServiceUUID,
                                                      (u1)sizeof(basServiceUUID));

                /* Local device name */
                clxBleAddExtendedAdvertisingDataField(&advBufferObj,
                                                      CLX_BLE_GAP_AD_TYPE_COMPLETE_LOCAL_DEVICE_NAME,
                                                      (u1*)clxGetBTLocalDeviceName(),
                                                      (u1)strlen(clxGetBTLocalDeviceName()));

                bleStartExtendedAdvertising(stack, &advBufferObj, TRUE);

                clxBleBassConfigureBroadcastReceiveState();
            }
            break;

            case BroadcastReceiverMenuItem_StopExtendedAdvertising:
            {
                bleStopExtendedAdvertising(stack, &advBufferObj);
            }
            break;

            case BroadcastReceiverMenuItem_PrintAdvertisingData:
            {
                clxConsoleUIEngineText("\nBIS Broadcast Announcement {BroadcastID[%d]", bassLocReceiveState->broadcastId );

                clxBleAudioPrintBISBasicAnnouncement ( clxBleAudioGetBISBasicAnnouncement () );
            }
            break;

            case BroadcastReceiverMenuItem_SyncPeriodicAdvertTrain:
            {
                boolean bUseAdvertiserList = FALSE;
                ClxBlePeriodicAdvertiserDetails advSet;
                u4 option = 0;

                clxMemSet(&advSet, 0x00, sizeof(ClxBlePeriodicAdvertiserDetails));

                clxConsoleUIEngineInputBox ("Enter the option 1 - New synchronize, 2 - Re-synchronize: ", inputValue, MAX_INPUT_SIZE);
                (void)sscanf(inputValue, "%u", &option);

                if (option == 1)
                {
                    RemoteDeviceInfo* device = showRemoteDeviceList();

                    if (device)
                    {
                        if (device->advSID == CLX_BLE_INVALID_ADVERTISING_SID_VALUE)
                        {
                            clxConsoleUIEngineText("\nThe selected Advertising set does not have a valid Advertising SID\n");
                            break;
                        }

                        advSet.advertiserAddress = device->address;
                        advSet.advertisingSID    = device->advSID;
                    }
                }
                else if (option == 2)
                {
                    bUseAdvertiserList = TRUE;
                }
                else
                {
                    clxConsoleUIEngineText("\nPlease enter valid options");
                    break;
                }

                ret = clxGapBlePeriodicAdvertisingStartSynchronizing ( stack,
                                                                       bUseAdvertiserList,
                                                                       TRUE,
                                                                       &advSet,
                                                                       0,
                                                                       CLX_BLE_PERIODIC_TRAIN_SYNC_TIMEOUT,
                                                                       0,
                                                                       TRUE);

                if (ret == CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("\nWaiting for CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_INDICATION indication.");
                }
                else
                {
                    clxConsoleUIEngineText("\nclxGapBlePeriodicAdvertisingStartSynchronizing failed with the error %s\n", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BroadcastReceiverMenuItem_CreateBIGSync:
            {
                u2 syncHandle = 0xFF;
                boolean encryptionSts = FALSE;

                ClxBleAudioBISBasicAudioAnnouncement*   bisBasicAnnouncement = clxBleAudioGetBISBasicAnnouncement ();

                if ( CLX_BLE_AUDIO_INVALID_HANDLE_VALUE == bleAudioGetPeriodicSyncHandle() )
                {
                    clxConsoleUIEngineText("\nInvalid PeriodicSync Handle - Retry after reveive the PERIODIC_ADVERTISING_SYNC_ESTABLISHED_INDICATION\n");
                    break;
                }

                if ( 0 == bisBasicAnnouncement->serviceUUID ||\
                     CLX_BLE_AUDIO_INVALID_HANDLE_VALUE == bleAudioGetPeriodicSyncHandle() )
                {
                    clxConsoleUIEngineText("\nInvalid Param Create BIG Sync Failed {UUID[%u]PeriodicSyncHdl[%u]}\n",
                                                                    bisBasicAnnouncement->serviceUUID,
                                                                    bleAudioGetPeriodicSyncHandle() );
                    break;
                }

                syncHandle = bleAudioGetPeriodicSyncHandle();

                /* There is only one BIS in the BIG, If we want to config more BIS then fill that index on below */
                u1 bisIndex[CLX_GATT_MAX_BIS_SUPPORTED] = { };

                ClxBleBigClientParameters params = { };
                params.bigID.value      = CLX_BLE_AUDIO_BIG_ID;
                params.syncHandle       = syncHandle;
                params.syncTimeout      = CLX_BLE_AUDIO_BIG_SYNC_TIMEOUT;
                params.maximumSubEvents = 0;
                params.useEncryption    = FALSE;

                clxConsoleUIEngineInputBox ("Do you Enable Encryption?[ 0:Disable / 1:Enable ]:\n", inputValue, MAX_INPUT_SIZE);
                encryptionSts = (boolean)atoi(inputValue); 

                if ( 0 == encryptionSts )
                {
                    params.useEncryption       = FALSE;
                }
                else
                {
                    u1 encryptionCode[CLX_BLE_BIG_BROADCAST_CODE + 1]  = CLX_BLE_AUDIO_BROADCAST_CODE;
                    params.useEncryption       = TRUE;
                    memcpy ( &params.broadcastCode, encryptionCode, CLX_BLE_BIG_BROADCAST_CODE );
                }

                if ( bisBasicAnnouncement->serviceUUID != 0 )
                {
                    u1 locBISIndex = 0;
                    ClxBleAudioBISSubGroup* locSubGrp = NULL;

                    params.numOfBIS    = bisBasicAnnouncement->subGrp[0].numberOfBIS;
                    locSubGrp = (bisBasicAnnouncement->subGrp + 0);

                    for ( locBISIndex = 0; locBISIndex < params.numOfBIS; ++locBISIndex )
                    {
                       bisIndex[ locBISIndex ] = locSubGrp->bisSpecificInfo[locBISIndex].bisIndex;
                    }
                }
                else
                {
                    params.numOfBIS = 1;
                    bisIndex[0]     = 1;
                }

                params.bisIndices   = bisIndex;

                ClxBleEstablishedBigParameters result;

                ret = clxBleIsoClientCreateBigSync( getIsoClientHandle(), &params, &result, TRUE );

                clxConsoleUIEngineText("\nclxBleIsoClientCreateBigSync complete with the result %s\n", clxGetErrorCodeText(ret));

                if (CLX_SUCCESS == ret)
                {
#if defined(CLX_FLOATINGPOINT_LC3)
                    /* Get the channel mode to listen to, from the user */
                    getAudioChannelMode();

                    /* Based on user preference, Set the preferred audio channel to sync with the matching stream, from advertising */
                    if (ClxAppStreamChannelMode_Stereo == streamChannelMode)
                    {
                        selectPreferredAudio(bisBasicAnnouncement, CLX_BLE_PREFERRED_STEREO_CHANNEL_ALLOCATION);
                    }
                    else
                    {
                        selectPreferredAudio(bisBasicAnnouncement, CLX_BLE_PREFERRED_MONO_CHANNEL_ALLOCATION);
                    }
#else
                    selectPreferredAudio(bisBasicAnnouncement, CLX_BLE_AUDIO_NUMBER_OF_CHANNELS);
#endif

                    ret = clxBleSetupISODataPath ( getIsoClientHandle(),
                                                   ClxBleIsoDataPathDirection_Output,
                                                   ClxBleIsoStreamType_BIS,
                                                   result.numberOfBis,
                                                   CLX_BLE_AUDIO_BIG_ID,
                                                   TRUE );

                    clxConsoleUIEngineText("\nclxBleSetupISODataPath complete with the result %s\n", clxGetErrorCodeText(ret));
                }
            }
            break;

            case BroadcastReceiverMenuItem_BIGSyncTerminate:
            {
                ClxBleIsoGroupID  bigID = { };
                bigID.value = CLX_BLE_AUDIO_BIG_ID;

                /* Terminate BIG Sync */
                ret = clxBleIsoClientTerminateBigSync ( getIsoClientHandle(),
                                                        bigID,
                                                        TRUE );

                clxConsoleUIEngineText("\nclxBleIsoClientTerminateBigSync complete with the result %s\n", clxGetErrorCodeText(ret));

                bassLocReceiveState->broadcastId = CLX_BLE_AUDIO_INVALID_BROADCAST_ID;

                ret = clxBleAudioDestroyBasicAnnouncementBuffer ( clxBleAudioGetBISBasicAnnouncement() );

                clxConsoleUIEngineText("\nBLE Broadcast Receiver Terminate: status - %s\n", clxGetErrorCodeText(ret));

                resetRemoteDeviceList();

                clxBleGapDestroyExtAdvertisingBuffer(&advBufferObj);
            }
            break;

            case BroadcastReceiverMenuItem_ReturnToPreviousMenu:
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
#endif /* CLX_BLE_ISOCHRONOUS */

