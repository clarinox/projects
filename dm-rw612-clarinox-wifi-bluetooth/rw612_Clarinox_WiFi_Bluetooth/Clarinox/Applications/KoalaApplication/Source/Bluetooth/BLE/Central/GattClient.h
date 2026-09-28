#ifndef __GattClient_h__
#define __GattClient_h__

/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                GattClient.h
* Description         This file provides GATT Application functions declarations.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#include "mainBluetooth.h"
#include "GattApp.h"

#if defined(CLX_WINDOWS)
#define MAX_NUMBER_OF_HANDLES           4
#else
#define MAX_NUMBER_OF_HANDLES           1
#endif /* defined(CLX_WINDOWS) */

#if defined(CLX_WINDOWS)
#define MAX_NUM_SERVICES                100
#define MAX_NUM_CHARACTERISTIC_LIST     100
#define MAX_NUM_DESCRIPTORS_LIST        100
#else
#define MAX_NUM_SERVICES                5
#define MAX_NUM_CHARACTERISTIC_LIST     10
#define MAX_NUM_DESCRIPTORS_LIST        3
#endif /* defined(CLX_WINDOWS) */

/*
Size of the remote device name string
*/
#define MAX_REMOTE_DEVICE_NAME_SIZE     31

/**
Structure to store GATT client instance and GATT service attributes information.
*/
typedef struct GattClientStruct
{
    ClxHandle                               handle;
    ClxBleConnectionHandle                  connectionHandle;
    ClxGattServiceDetail                    serviceList[MAX_NUM_SERVICES];
    u2                                      noOfService;
    ClxGattCharacteristicDetail             characteristicList[MAX_NUM_CHARACTERISTIC_LIST];
    u2                                      noOfCharacteristics;
    ClxGattCharacteristicDescriptorDetail   descriptorList[MAX_NUM_DESCRIPTORS_LIST];
    u2                                      noOfDescriptor;
    ClxBleBdAddress                         peerDeviceAddress;
}GattClient;

/* 
Variables associated with LE Central object 
*/
typedef struct ClxCentralInstanceInfoStruct
{
    s1          input_buffer[MAX_INPUT_SIZE];       /* Buffer to get console input                                          */
    GattClient  gattClient[MAX_NUMBER_OF_HANDLES];  /* Array of a local gatt client handle                                  */
    u4          activeClientIndex;                  /* Current gatt client handle for all operations                        */
    boolean     isRemoteDeviceConnected;            /* Flag to indicate connection status                                   */
    boolean     isBleCentralInitialized;            /* Indicate if the classic part of stack init are initialized or not    */
    RemoteDeviceList remoteDeviceList;              /* Object to store the remote device details                            */

    ClxBleBdAddress pairedDeviceList[CLARINOXBLUE_DEFAULT_LOW_ENERGY_MAX_NUMBER_OF_PAIRED_DEVICES]; /* Buffer to store paired device informations */
}ClxCentralInstanceInfo;

/*
Create BLE GATT Client handle if this profile is used
*/
ClxHandle createGattClientHandle(ClxStack stack);

/*
Delete BLE GATT Client handle when there is no use for this profile
*/
void deleteGattClientHandle(ClxHandle handle);

/*
This callback function is registered for the BLE GATT Client, any events raised by BLE GATT Client, causes this
callback function executed with the associated event and parameters. Executed from the stack thread context
*/
boolean bleGattClientMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);

/*
To Get the GATT Client Instance Handle.
*/
ClxCentralInstanceInfo* getGattClientInstanceInfo ( void );

/**
Discover All Primary Services from remote device
*/
ClxResult bleCentralDiscoverAllPrimaryServices ( const ClxGattUuid* serviceUuid, boolean bPrintFlag);

/* Enables the notification for BAP services */
ClxResult bleCentralEnableNotificationForAllCharacteristics (u2 serviceUuid);

/* Enables the notification for BAP services */
ClxResult bleCentralReadAllCharacteristicsValue (void);

/**
Discover All Characteristics from remote device
*/
ClxResult bleCentralDiscoverAllCharacteristics ( const ClxGattUuid* charUuid, u4 serviceIndex );

/**
Enable the notification for the user selected characteristics
*/
ClxResult bleCentralEnableNotification ( u4 characteristicIndex );

ClxHandle getGattClientHandle(void);

GattClient* getGattClientHandleInfo(void);

ClxBleConnectionHandle getGattClientConnectionHandle(void);

/*
Reads the Device Information characteristic from a remote device 
*/
void clxGetDeviceInfo(u2 characteristicUuidValue);

u2 GetValueHandle(ClxHandle gattClientHandle, u4 serviceUuid, u4 characteristicUuid);

#endif /* __GattClient_h__ */

