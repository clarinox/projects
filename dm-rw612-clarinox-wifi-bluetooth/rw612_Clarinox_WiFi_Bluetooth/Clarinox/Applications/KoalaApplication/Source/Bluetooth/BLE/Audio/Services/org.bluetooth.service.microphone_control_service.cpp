/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.microphone_control_service.cpp
* Description         Implements the GATT service Microphone Control Service
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2024 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "org.bluetooth.service.microphone_control_service.h"
#include <new>


/* GATT Service Definition for "Microphone Control Service" with the UUID "184D" : */

class ClxMicrophoneControlServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Mute */
    ClxBleCharacteristicDeclarationAttribute                mute_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      mute_CharacteristicValueAttribute;
    u4                                                      mute_Storage[(CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        mute_CharacteristicClientConfigurationAttribute;
    
    ClxBleAttribute*                                        list[4];

public:
    ClxMicrophoneControlServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&mute_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&mute_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&mute_CharacteristicClientConfigurationAttribute;
    }
};


static ClxBleGattDatabase* initMicrophoneControlServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxMicrophoneControlServiceGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, sizeof(ClxMicrophoneControlServiceGattServiceDatabase))) ClxMicrophoneControlServiceGattServiceDatabase;
#else
    ClxMicrophoneControlServiceGattServiceDatabase* ret = new ClxMicrophoneControlServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Mute : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->mute_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->mute_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_VALUE_TYPE, (u1*)&ret->mute_Storage, CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_SIZE, CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicMute, clxDecodeOrgBluetoothCharacteristicMute);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->mute_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    return ret;
}

static void destroyMicrophoneControlServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxMicrophoneControlServiceGattServiceDatabase*>(database);
}

void microphoneControlServiceBaseHandleUpdated(u2 baseHandle)
{
}

extern "C"
{

    static ClxBleGattServiceInterface clxMicrophoneControlServiceGattServiceInterface =
    {
        initMicrophoneControlServiceGattServiceDatabase,
        destroyMicrophoneControlServiceGattServiceDatabase,
        microphoneControlServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetMicrophoneControlServiceGattServiceInterface()
    {
        return &clxMicrophoneControlServiceGattServiceInterface;
    }

    const s1* clxGetMicrophoneControlServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE_HANDLE_INDEX : return CLX_GATT_SERVICE_MICROPHONE_CONTROL_SERVICE_CHARACTERISTIC_MUTE;
            default : return NULL;
        }
    }
}
