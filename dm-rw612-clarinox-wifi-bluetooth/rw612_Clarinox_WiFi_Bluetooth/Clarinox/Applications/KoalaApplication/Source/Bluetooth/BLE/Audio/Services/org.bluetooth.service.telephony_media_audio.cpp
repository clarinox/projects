/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.telephony_media_audio.cpp
* Description         Implements the Telephony Meida Audio Service.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)
#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"
#include <new>

/* GATT Service Definition for "Telephony Media Audio Service" with the UUID 0x1855 : */

class ClxTelephonyMediaAudioServiceGattDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : TMAP Role */
    ClxBleCharacteristicDeclarationAttribute                role_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      role_CharacteristicValueAttribute;
    u4                                                      role_Storage[(CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_SIZE + 3)/4];
    
    ClxBleAttribute*                                        list[3];

public:
    ClxTelephonyMediaAudioServiceGattDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&role_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&role_CharacteristicValueAttribute;
    }
};


static ClxBleGattDatabase* initTelephonyMediaAudioServiceGattDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxTelephonyMediaAudioServiceGattDatabase* ret = new (clxAppPoolsetAlloc(0, 0, sizeof(ClxTelephonyMediaAudioServiceGattDatabase))) ClxTelephonyMediaAudioServiceGattDatabase;
#else
    ClxTelephonyMediaAudioServiceGattDatabase* ret = new ClxTelephonyMediaAudioServiceGattDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* TMAP Role : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->role_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->role_CharacteristicValueAttribute, &uuid, CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_VALUE_TYPE, (u1*)&ret->role_Storage, CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_SIZE, CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_PERMISSIONS, NULL, NULL);
        }
        /* </Value> */
    }

    return ret;
}

static void destroyTelephonyMediaAudioServiceGattDatabase(ClxBleGattDatabase* database)
{
    clxBleGattServiceList[GattService_TelephonyMediaAudioServiceIndex].handleBase = INVALID_SERVICE_BASE_HANDLE;
    delete static_cast<ClxTelephonyMediaAudioServiceGattDatabase*>(database);
}

static void telephonyMediaAudioServiceBaseHandleUpdated(u2 baseHandle)
{
    clxBleGattServiceList[GattService_TelephonyMediaAudioServiceIndex].handleBase = baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxTelephonyMediaAudioServiceGattInterface = 
    {
        initTelephonyMediaAudioServiceGattDatabase,
        destroyTelephonyMediaAudioServiceGattDatabase,
        telephonyMediaAudioServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetTelephonyMediaAccessServiceInterface()
    {
        return &clxTelephonyMediaAudioServiceGattInterface;
    }

    const s1* clxGetTelephonyMediaAudioServiceGattCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_HANDLE_INDEX : return CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE;
            default : return NULL;
        }
    }
}
#endif /* defined(CLX_BLE_ISOCHRONOUS) */


