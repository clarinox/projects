/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.broadcast_audioscan.cpp
* Description         Implements the GATT service Broadcast Audio Scan
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2024 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"
#include <new>


/* GATT Service Definition for "Broadcast Audio Scan" with the UUID "184F" : */

class ClxBroadcastAudioScanGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Broadcast Audio Scan Control Point */
    ClxBleCharacteristicDeclarationAttribute                broadcastAudioScanControlPoint_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      broadcastAudioScanControlPoint_CharacteristicValueAttribute;
    u4                                                      broadcastAudioScanControlPoint_Storage[(CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_SIZE + 3)/4];
    
    /* Characteristic : Broadcast Receive State */
    ClxBleCharacteristicDeclarationAttribute                broadcastReceiveState_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      broadcastReceiveState_CharacteristicValueAttribute;
    u4                                                      broadcastReceiveState_Storage[(CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        broadcastReceiveState_CharacteristicClientConfigurationAttribute;
    
    ClxBleAttribute*                                        list[6];

public:
    ClxBroadcastAudioScanGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&broadcastAudioScanControlPoint_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&broadcastAudioScanControlPoint_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&broadcastReceiveState_CharacteristicDeclarationAttribute;
        list[4] = (ClxBleAttribute*)&broadcastReceiveState_CharacteristicValueAttribute;
        list[5] = (ClxBleAttribute*)&broadcastReceiveState_CharacteristicClientConfigurationAttribute;
    }
};


static ClxBleGattDatabase* initBroadcastAudioScanGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxBroadcastAudioScanGattServiceDatabase* ret = new (clxAppPoolsetAlloc(0, 0, sizeof(ClxBroadcastAudioScanGattServiceDatabase))) ClxBroadcastAudioScanGattServiceDatabase;
#else
    ClxBroadcastAudioScanGattServiceDatabase* ret = new ClxBroadcastAudioScanGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Broadcast Audio Scan Control Point : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->broadcastAudioScanControlPoint_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->broadcastAudioScanControlPoint_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_VALUE_TYPE, (u1*)&ret->broadcastAudioScanControlPoint_Storage, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_SIZE, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_PROPERTY, clxEncodeOrgBluetoothCharacteristicBroadcastAudioscancontrolpoint, clxDecodeOrgBluetoothCharacteristicBroadcastAudioscancontrolpoint);
        }
        /* </Value> */
    }

    /* Broadcast Receive State : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->broadcastReceiveState_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->broadcastReceiveState_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_VALUE_TYPE, (u1*)&ret->broadcastReceiveState_Storage, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_SIZE, CLX_GATT_BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_PROPERTY, clxEncodeOrgBluetoothCharacteristicBroadcastReceivestate, clxDecodeOrgBluetoothCharacteristicBroadcastReceivestate);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->broadcastReceiveState_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    return ret;
}

static void destroyBroadcastAudioScanGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxBroadcastAudioScanGattServiceDatabase*>(database);
}

void broadcastAudioScanServiceBaseHandleUpdated(u2 baseHandle)
{
    (void)baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxBroadcastAudioScanGattServiceInterface =
    {
        initBroadcastAudioScanGattServiceDatabase,
        destroyBroadcastAudioScanGattServiceDatabase,
        broadcastAudioScanServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetBroadcastAudioScanGattServiceInterface()
    {
        return &clxBroadcastAudioScanGattServiceInterface;
    }

    const s1* clxGetBroadcastAudioScanGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_HANDLE_INDEX : return CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT;
            case CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_HANDLE_INDEX : return CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_CHARACTERISTIC_BROADCAST_RECEIVE_STATE;
            default : return NULL;
        }
    }
}

#endif /* CLX_BLE_ISOCHRONOUS */

