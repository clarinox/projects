/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                BroadcastSelector.cpp
* Description         This application file provides the BLE audio Broadcast Selector
*                     operations menu.
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

#include "Ble.Bap.Api.h"
#include "GattApp.h"
#include "GattClient.h"
#include "Gap.Ble.Bonding.Api.h"

/* Menu options used to invoke Broadcast Selector main menu */
typedef enum BroadcastSelectorMenuItemEnum
{
    BroadcastSelectorMenuItem_StartScan                        = 1,
    BroadcastSelectorMenuItem_StopScan,
    BroadcastSelectorMenuItem_ConnectToSinkDevice,
    BroadcastSelectorMenuItem_DisconnectFromSinkDevice,
    BroadcastSelectorMenuItem_ReturnToPreviousMenu,
    BroadcastSelectorMenuItem_TotalItems
} BroadcastSelectorMenuItem;

/* BASS broadcast receive characteristic's sync state */
typedef enum BroadcastReceiveStateEnum
{
    BroadcastReceiveState_NotSynchronized       = 0x00,
    BroadcastReceiveState_SyncInfoRequest       = 0x01,
    BroadcastReceiveState_SynchronizedToPA      = 0x02,
    BroadcastReceiveState_FailedToSynchronize   = 0x03,
    BroadcastReceiveState_NoPAST                = 0x04
    /* All other values are RFU */
} BroadcastReceiveState;

/* Broadcast Selector state machine values */
typedef enum BroadcastSelectorMonitoringStateEnum
{
    Selector_Idle,
    Selector_SearchSource,
    Selector_SelectSource,
    Selector_Synchronize,
    Selector_AddSource,
    Selector_SyncTransfer,
    Selector_Streaming
} BroadcastSelectorMonitoringState;

#define CLX_BLE_BA_CONNECTION_MONITORING_TIMER_DURATION     5000

ClxBleBroadcastSelectorInfo gBroadcastSelectorInfo ={ 0 };

extern s1  inputValue[MAX_INPUT_SIZE];

#if FIX_TIMER
ClxTimer gConnectionTimer = NULL;
#endif

static ClxCentralInstanceInfo *gsGattClientInfo = NULL;
static BroadcastSelectorMonitoringState gsBsState = Selector_Idle;

/* Function used to cache the Broadcast Id, Adv Sid and advertiser address type and its value */
void clxBleBAupdateAdvInfo(u4 broadcastId, u1 advSid, ClxBleBdAddress addr)
{
    /* Broadcast Id */
    gBroadcastSelectorInfo.broadcastId[0] = (u1) ( broadcastId & 0x000000FF );
    gBroadcastSelectorInfo.broadcastId[1] = (u1) (( broadcastId & 0x0000FF00 ) >> 8);
    gBroadcastSelectorInfo.broadcastId[2] = (u1) (( broadcastId & 0x00FF0000 ) >> 16);

    /* Advertising SID */
    gBroadcastSelectorInfo.advSID = advSid;

    /* Advertiser address type */
    gBroadcastSelectorInfo.addrType = (u1) addr.addressType;

    /* Advertiser address */
    clxMemCpy(&gBroadcastSelectorInfo.address, &addr.value, 6);
}

/* Function used to cache the periodic advertisement interval and its sync state */
void clxBleBAupdateSyncInfo(u2 PaInterval)
{
    /* Periodic advertisement interval */
    gBroadcastSelectorInfo.paInterval = PaInterval;

    /* Periodic advertisement sync state */
    /* 0x00 - no synchronize, 0x01 - PAST available, 0x02 - PAST not available */
    gBroadcastSelectorInfo.paSync = 0x01;

    if (gsBsState == Selector_Synchronize)
    {
        gsBsState = Selector_AddSource;
    }

    clxGapBleDisableExtendedScan(clxGetBTStackHandle(), TRUE);
}

/* Returns the value handle of BASS receive state characteristics */
u2 clxBleBAgetReceiveStateAttributeHandle(void)
{
    return gBroadcastSelectorInfo.receiveStateValueHandle;
}

/* Notifies to sink device that the remote scan has stopped */
void clxBleBassClientRemoteScanStopped(void)
{
    ClxResult ret = CLX_ERROR;
    ClxHandle gatt = getGattClientHandle();
    u2 valueHandle = GetValueHandle(gatt, CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID);
    u1 data = ClxBleBassOpcode_RemoteScanStopped;
    
    ret = clxGattClientWrite(gatt,
                             valueHandle,
                             ClxGattWriteProcedure_WriteWithResponse,
                             &data,
                             sizeof(data),
                             TRUE);

    if (CLX_SUCCESS != ret)
    {
        clxConsoleUIEngineText("\nWriting BASS client's Remote Scan Stopped failed with error %s\n", clxGetErrorCodeText(ret));
    }
}

/* Notifies to sink device that the remote scan has started */
void clxBleBassClientRemoteScanStarted(void)
{
    ClxResult ret = CLX_ERROR;
    ClxHandle gatt = getGattClientHandle();
    u2 valueHandle = GetValueHandle(gatt, CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID);
    u1 data = ClxBleBassOpcode_RemoteScanStarted;
    
    ret = clxGattClientWrite(gatt,
                             valueHandle,
                             ClxGattWriteProcedure_WriteWithResponse,
                             &data,
                             sizeof(data),
                             TRUE);

    if (CLX_SUCCESS != ret)
    {
        clxConsoleUIEngineText("\nWriting BASS client's Remote Scan Started failed with error %s\n", clxGetErrorCodeText(ret));
    }
}

/* Notifies to sink device that the synchronized source details are added */
void clxBleBassClientAddSource(void)
{
    ClxResult ret = CLX_ERROR;
    ClxHandle gatt = getGattClientHandle();
    u2 valueHandle = GetValueHandle(gatt, CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID);
    u1 data[21] = {0};

    // Op code
    data[0] = ClxBleBassOpcode_AddSource;
    
    // Advertiser address type
    data[1] = gBroadcastSelectorInfo.addrType;
    
    //Address
    clxMemCpy(&data[2], &gBroadcastSelectorInfo.address, 6);
    
    // Advertising SID
    data[8] = gBroadcastSelectorInfo.advSID;
    
    // Broadcast Id
    data[9] = gBroadcastSelectorInfo.broadcastId[0];
    data[10] = gBroadcastSelectorInfo.broadcastId[1];
    data[11] = gBroadcastSelectorInfo.broadcastId[2];
    
    // PA sync
    data[12] = gBroadcastSelectorInfo.paSync;
    
    // PA Interval
    data[13] = (gBroadcastSelectorInfo.paInterval & 0x00FF);
    data[14] = ((gBroadcastSelectorInfo.paInterval & 0xFF00) >> 8);
    
    // Number of sub.group
    data[15] = 0x01;
    
    // BIS Sync
    data[16] = 0x01;
    
    // Meta data length
    data[20] = 0x00;
    
    ret = clxGattClientWrite(gatt,
                             valueHandle,
                             ClxGattWriteProcedure_WriteWithResponse,
                             data,
                             sizeof(data),
                             TRUE);

    if (CLX_SUCCESS != ret)
    {
        clxConsoleUIEngineText("\nWriting BASS client's Remote Scan Started failed with error %s\n", clxGetErrorCodeText(ret));
    }
}

/* Notifies to sink device that the synchronized source details are removed */
void clxBleBassClientRemoveSource(void)
{
    ClxResult ret = CLX_ERROR;
    ClxHandle gatt = getGattClientHandle();
    u2 valueHandle = GetValueHandle(gatt, CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID);
    u1 data[2] = {0};

    // Op code
    data[0] = ClxBleBassOpcode_RemoveSource;
    
    // source Id
    data[1] = gBroadcastSelectorInfo.sourceId;
    
    ret = clxGattClientWrite(gatt,
                             valueHandle,
                             ClxGattWriteProcedure_WriteWithResponse,
                             data,
                             sizeof(data),
                             TRUE);

    if (CLX_SUCCESS != ret)
    {
        clxConsoleUIEngineText("\nWriting BASS client's Remote Scan Started failed with error %s\n", clxGetErrorCodeText(ret));
    }
}

/* Handles the notification from Sink device */
void clxBleBAprocessReceiveStateNotification(u1* data, u4 dataLength)
{
    ClxResult ret = CLX_ERROR;
    u1 syncState;

    /* Sanity check: BASS receive state characteristic should contain the minimum of 15 bytes */
    if (dataLength < 15)
    {
        clxConsoleUIEngineText("\nBASS Receive state: Invalid data\n");
        return;
    }

    syncState = data[12];

    switch (syncState)
    {
        case BroadcastReceiveState_NotSynchronized:
        {
            u1 numSubGroups = data[14];
            
            clxConsoleUIEngineText("\nNot synchronized to PA\n");

            if (numSubGroups == 0)
            {
                clxConsoleUIEngineText("\nSync lost with the current broadcast, please do search and synchronize with new source\n");

                ret = clxGapBlePeriodicAdvertisingStopSynchronizing(clxGetBTStackHandle(), bleAudioGetPeriodicSyncHandle(), TRUE);

                if (CLX_SUCCESS == ret)
                {
                    clxBleBassClientRemoveSource();
                    gsBsState = Selector_SearchSource;
                }
                else
                {
                    clxConsoleUIEngineText("\nPeriodic Advertising stop synchronization failed with error %s\n", clxGetErrorCodeText(ret));
                }
            }
            break;
        }

        case BroadcastReceiveState_SyncInfoRequest:
        {
            clxConsoleUIEngineText("\nSync info request\n");
            break;
        }

        case BroadcastReceiveState_SynchronizedToPA:
        {
            clxConsoleUIEngineText("\nSynchronized to PA\n");
            gBroadcastSelectorInfo.sourceId = data[0];

            clxBleBassClientRemoteScanStopped();

            break;
        }

        case BroadcastReceiveState_FailedToSynchronize:
        {
            clxConsoleUIEngineText("\nFailed to synchronize to PA\n");
            break;
        }

        case BroadcastReceiveState_NoPAST:
        {
            clxConsoleUIEngineText("\nNo PAST\n");
            break;
        }

        default:
            clxConsoleUIEngineText("\nUnknown sync state: %u\n", syncState);
            break;
    }
}

/**
Timer handler function to perform

1. Keep the active connection between selector and sink device
2. Perform scanning and identify the available sources
3. Establishes the synchronization
4. Trnasfer the synchronization details to sink device
*/
void clxBleBAconnectionMonitoringTimerHandler(void* data)
{
    ClxResult ret = CLX_ERROR;

    (void*)data;

    /* Reconnects with sink device */
    if (!gsGattClientInfo->isRemoteDeviceConnected)
    {
        /* In case the scanning is still ongoing: */
        clxGapBleStopScan(clxGetBTStackHandle(), TRUE);

        ClxBleConnectionDetails connectionDetails;
        ClxGapBleExtendedConnectParameters    connectParameter_Le1M_PHY = { };
        u2 negotiatedMTU = 0;
        ClxBleBdAddress remoteDeviceAddr;
        u4 noOfPairedDevices = 0;

        ret= clxGapBleGetListOfPairedDevices(clxGetBTStackHandle(), &remoteDeviceAddr, 1, &noOfPairedDevices, TRUE);

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\nRetrieving the paired devices failed with error %s\n", clxGetErrorCodeText(ret));
            return;
        }

        connectParameter_Le1M_PHY.scanInterval       = 140;
        connectParameter_Le1M_PHY.scanWindow         = 100;
        connectParameter_Le1M_PHY.connectIntervalMin = 50;
        connectParameter_Le1M_PHY.connectIntervalMax = 70;
        connectParameter_Le1M_PHY.connectionLatency  = 0;
        connectParameter_Le1M_PHY.supervisionTimeout = 2000;
        connectParameter_Le1M_PHY.minCElength        = 0x01;
        connectParameter_Le1M_PHY.maxCElength        = 0x0C00;

        ret = clxGapBleExtendedConnectToPeripheral( clxGetBTStackHandle(),
                                                    0x00,
                                                    0x00,
                                                    ClxBleOwnAddressMode_Identity,
                                                    &remoteDeviceAddr,
                                                    &connectParameter_Le1M_PHY,
                                                    NULL,
                                                    NULL,
                                                    &connectionDetails,
                                                    CONNECTION_TIMEOUT,
                                                    TRUE );

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\nReConnection attempt to sink device failed with error %s\n", clxGetErrorCodeText(ret));
            return;
        }

        ret = clxGapBleEncrypt(clxGetBTStackHandle(), connectionDetails.connectionHandle, getBondingProperty(TRUE, FALSE, FALSE), TRUE);

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\nEncryption failed with error %s\n", clxGetErrorCodeText(ret));
            return;
        }

        ret = clxGattClientBind(getGattClientHandle(), connectionDetails.connectionHandle, 500, &negotiatedMTU, TRUE);

        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\nBind failed with error %s\n", clxGetErrorCodeText(ret));
            return;
        }

        gsGattClientInfo->isRemoteDeviceConnected = TRUE;
    }
    else
    {
        clxConsoleUIEngineText("\nSelector State: %d\n", gsBsState);
        
        switch (gsBsState)
        {
            case Selector_SearchSource:
            {
                resetRemoteDeviceList();
                startExtendedScan(clxGetBTStackHandle(), FALSE);

                if (gsGattClientInfo->isRemoteDeviceConnected)
                {
                    clxBleBassClientRemoteScanStarted();
                    clxBleAudioInitBasicAnnouncementBuffer(clxBleAudioGetBISBasicAnnouncement());
                    
                    gsBsState = Selector_SelectSource;
                }
                break;
            }

            case Selector_SelectSource:
            {
                RemoteDeviceInfo* device = gsGattClientInfo->remoteDeviceList.findAudioSource();

                if (device)
                {
                    ClxBlePeriodicAdvertiserDetails advSet;
                    clxMemSet(&advSet, 0x00, sizeof(ClxBlePeriodicAdvertiserDetails));

                    advSet.advertiserAddress = device->address;
                    advSet.advertisingSID    = device->advSID;

                    ret = clxGapBlePeriodicAdvertisingStartSynchronizing ( clxGetBTStackHandle(),
                                                                           FALSE,
                                                                           TRUE,
                                                                           &advSet,
                                                                           0,
                                                                           CLX_BLE_PERIODIC_TRAIN_SYNC_TIMEOUT,
                                                                           0,
                                                                           TRUE);

                    if (ret == CLX_SUCCESS)
                    {
                        gsBsState = Selector_Synchronize;
                        clxConsoleUIEngineText("\nWaiting for CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_INDICATION indication.");
                    }
                    else
                    {
                        gsBsState = Selector_SearchSource;
                        clxConsoleUIEngineText("\nclxGapBlePeriodicAdvertisingStartSynchronizing failed with the error %s\n", clxGetErrorCodeText(ret));
                    }
                }
                else
                {
                    /* Perform scan again */
                    gsBsState = Selector_SearchSource;
                }

                break;
            }

            case Selector_AddSource:
            {
                if (gsGattClientInfo->isRemoteDeviceConnected)
                {
                    clxBleBassClientAddSource();
                    gsBsState = Selector_SyncTransfer;
                }
                else
                {
                    gsBsState = Selector_SearchSource;
                }
                break;
            }

            case Selector_SyncTransfer:
            {
                ret = clxGapBlePeriodicAdvertisingSyncTransfer(clxGetBTStackHandle(),
                                                               gBroadcastSelectorInfo.connectionHandle,
                                                               0x0001,
                                                               bleAudioGetPeriodicSyncHandle(),
                                                               TRUE);

                if (CLX_SUCCESS == ret)
                {
                    gsBsState = Selector_Streaming;
                }
                else
                {
                    clxConsoleUIEngineText("\nPeriodic Advertising Sync Transfer failed with error %s\n", clxGetErrorCodeText(ret));
                }
                break;
            }
        }
    }

}

#if FIX_TIMER
/* Creates the monitoring timer */
ClxResult clxBleBAcreateConnectionMonitoringTimer(void)
{
    if (gConnectionTimer)
    {
        clxConsoleUIEngineText("\nConnection monitoring timer is already created\n");
        return CLX_ERROR;
    }

    gConnectionTimer = clxCreateTimer(CLX_BLE_BA_CONNECTION_MONITORING_TIMER_DURATION,
                                      clxBleBAconnectionMonitoringTimerHandler,
                                      "Connection monitoring timer",
                                      TM_PERIODIC);

    if (NULL == gConnectionTimer)
    {
        clxConsoleUIEngineText("\nFatil to create connection monitoring timer\n");
        return CLX_ERROR;
    }

    return CLX_SUCCESS;
}

/* Terminates the monitoring timer */
ClxResult clxBleBAdestroyConnectionMonitoringTimer(void)
{
    if (!gConnectionTimer)
    {
        clxConsoleUIEngineText("\nConnection monitoring timer is not yet created\n");
        return CLX_ERROR;
    }

    clxDeleteTimer(gConnectionTimer);
    gConnectionTimer = NULL;

    return CLX_SUCCESS;
}
#endif

/***************************************************************************************************************************************
*                                                Broadcast Selector Menu
*
* Menu to display Low Energy broadcast selector role related menu options
*
****************************************************************************************************************************************/
void bluetoothLowEnergyBroadcastSelectorMenu ( ClxStack stack )
{
    ClxResult ret = CLX_ERROR;

    if ( NULL == getGattClientHandle() )
    {
        clxConsoleUIEngineText("\nINVALID Gatt Client Handle");
        return;
    }

    /**
    Object to store a local gatt client instance handle for GATT API commands
    */
    gsGattClientInfo = getGattClientInstanceInfo();

    if ( NULL == gsGattClientInfo )
    {
        clxConsoleUIEngineText("\nINVALID Gatt Client Instance Info");
        return;
    }
#if FIX_TIMER
    if (clxTimerRunning(gConnectionTimer))
    {
        clxStopTimer(gConnectionTimer);
    }
#endif
    while (TRUE)
    {
        const s1* BroadcastSelectorMenu =   "Start scan\0"
                                            "Stop Scan\0"
                                            "Connect to sink device\0"
                                            "Disconnect from sink device\0"
                                            "Return to previous menu\0";

        u4 BroadcastSelectorIndex = clxConsoleUIEngineShowMenu("Please select how to proceed:",
                                                                BroadcastSelectorMenu,
                                                                BroadcastSelectorMenuItem_TotalItems - 1);

        switch (BroadcastSelectorIndex)
        {
            case BroadcastSelectorMenuItem_StartScan:
            {
                resetRemoteDeviceList();
                startExtendedScan(stack, FALSE);
                break;
            }

            case BroadcastSelectorMenuItem_StopScan:
            {
                ret = clxGapBleDisableExtendedScan(stack, TRUE);
                clxConsoleUIEngineText("\nclxGapBleDisableExtendedScan: status - %s\n", clxGetErrorCodeText(ret));
                break;
            }

            case BroadcastSelectorMenuItem_ConnectToSinkDevice:
            {
                /* In case the scanning is still ongoing: */
                clxGapBleStopScan(stack, TRUE);

                clxGapBleDeleteAllPairedDevicesInfo(stack, TRUE);

                RemoteDeviceInfo* device = showRemoteDeviceList();

                if (device)
                {
                    ClxBleConnectionDetails connectionDetails;
                    ClxGapBleExtendedConnectParameters    connectParameter_Le1M_PHY = { };
                    ClxGattUuid characteristcUuid = { };
                    u2 negotiatedMTU = 0;

                    connectParameter_Le1M_PHY.scanInterval       = 140;
                    connectParameter_Le1M_PHY.scanWindow         = 100;
                    connectParameter_Le1M_PHY.connectIntervalMin = 50;
                    connectParameter_Le1M_PHY.connectIntervalMax = 70;
                    connectParameter_Le1M_PHY.connectionLatency  = 0;
                    connectParameter_Le1M_PHY.supervisionTimeout = 2000;
                    connectParameter_Le1M_PHY.minCElength        = 0x01;
                    connectParameter_Le1M_PHY.maxCElength        = 0x0C00;

                    ret = clxGapBleExtendedConnectToPeripheral( stack,
                                                                0x00,
                                                                0x00,
                                                                ClxBleOwnAddressMode_Identity,
                                                                &device->address,
                                                                &connectParameter_Le1M_PHY,
                                                                NULL,
                                                                NULL,
                                                                &connectionDetails,
                                                                CONNECTION_TIMEOUT,
                                                                TRUE );

                    if (CLX_SUCCESS != ret)
                    {
                        clxConsoleUIEngineText("\nPhysical Connection attempt to the device %s failed with error %s\n", device->name, clxGetErrorCodeText(ret));
                        break;
                    }

                    /* Caching the remote device connection handle, address type and its address for further processing */
                    gsGattClientInfo->gattClient[ 0 ].connectionHandle = connectionDetails.connectionHandle;
                    gsGattClientInfo->gattClient[ 0 ].peerDeviceAddress.addressType = connectionDetails.remoteDeviceAddr.addressType;

                    memcpy( gsGattClientInfo->gattClient[ 0 ].peerDeviceAddress.value,
                            connectionDetails.remoteDeviceAddr.value,
                            CLX_BLE_GAP_ADDRESS_VALUE_LENGTH);

                    ret = clxGapBleStartBondingProcedure(stack,
                                          gsGattClientInfo->gattClient[ 0 ].connectionHandle,
                                          ClxBleSmpBondingType_Bonding,
                                          getBondingProperty ( TRUE, FALSE, FALSE ),
                                          16,
                                          (u1)ClxBleSmpKeyDistribution_EncryptionKey | (u1)ClxBleSmpKeyDistribution_IdentityKey,
                                          (u1)ClxBleSmpKeyDistribution_EncryptionKey | (u1)ClxBleSmpKeyDistribution_IdentityKey,
                                          TRUE);

                    if (CLX_SUCCESS != ret)
                    {
                        clxConsoleUIEngineText("\nPairing attempt to the device %s failed with error %s\n", device->name, clxGetErrorCodeText(ret));
                        break;
                    }

                    /* Stores the paired device name */
                    ret = clxGapBleSetPairedDeviceName(stack, connectionDetails.connectionHandle, device->name, (u1)strlen(device->name), TRUE);

                    if (CLX_SUCCESS != ret)
                    {
                        clxConsoleUIEngineText("\nclxGapBleSetPairedDeviceName failed with error %s\n", clxGetErrorCodeText(ret));
                        break;
                    }

                    ret = clxGattClientBind(getGattClientHandle(), connectionDetails.connectionHandle, 500, &negotiatedMTU, TRUE);

                    if (CLX_SUCCESS != ret)
                    {
                        clxConsoleUIEngineText("\nBinding attempt to the device %s failed with error %s\n", device->name, clxGetErrorCodeText(ret));
                        break;
                    }

                    clxConsoleUIEngineText("\nPlease wait to discover the audio capabilities\n");

                    /* Discover the audio capabilities */
                    discoverAudioCapability( CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_UUID);

                    /* Discover the audio contexts */
                    discoverAudioContext();

                    /* Enable notification to the characteristics in BASS  */
                    bleCentralEnableNotificationForAllCharacteristics(CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID);

                    gBroadcastSelectorInfo.receiveStateValueHandle = GetValueHandle(getGattClientHandle(), CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_UUID);
                    gBroadcastSelectorInfo.connectionHandle = connectionDetails.connectionHandle;

                    gsGattClientInfo->isRemoteDeviceConnected = TRUE;

                    gsBsState = Selector_SearchSource;
#if FIX_TIMER
                    clxStartTimer(gConnectionTimer, CLX_BLE_BA_CONNECTION_MONITORING_TIMER_DURATION);
#endif
                }

                break;
            }

            case BroadcastSelectorMenuItem_DisconnectFromSinkDevice:
            {
                ret = clxGapBleDisconnectPhysicalLink ( stack,
                                                        gsGattClientInfo->gattClient[ 0 ].connectionHandle,
                                                        DISCONNECTION_TIMEOUT,
                                                        TRUE );

                gsGattClientInfo->isRemoteDeviceConnected = FALSE;

                clxConsoleUIEngineText("\nDisconnection completed with the result %s\n", clxGetErrorCodeText(ret));
                break;
            }

            case BroadcastSelectorMenuItem_ReturnToPreviousMenu:
            {
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

