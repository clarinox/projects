/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.generic_media_control_service.cpp
* Description         Implements the GATT service Generic Media Control Service
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
#include "org.bluetooth.service.generic_media_control_service.h"
#include "org.bluetooth.service.media_control_service.h"
#include <new>

/* GATT Service Definition for "Generic Media Control Service" with the UUID "1849" : */

class ClxGenericMediaControlServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Media Player Name */
    ClxBleCharacteristicDeclarationAttribute                mediaPlayerName_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      mediaPlayerName_CharacteristicValueAttribute;
    u4                                                      mediaPlayerName_Storage[(CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        mediaPlayerName_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Track Changed */
    ClxBleCharacteristicDeclarationAttribute                trackChanged_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      trackChanged_CharacteristicValueAttribute;
    u4                                                      trackChanged_Storage[(CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        trackChanged_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Track Title */
    ClxBleCharacteristicDeclarationAttribute                trackTitle_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      trackTitle_CharacteristicValueAttribute;
    u4                                                      trackTitle_Storage[(CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_SIZE + 3)/4];
    
    /* Characteristic : Track Duration */
    ClxBleCharacteristicDeclarationAttribute                trackDuration_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      trackDuration_CharacteristicValueAttribute;
    u4                                                      trackDuration_Storage[(CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_SIZE + 3)/4];
    
    /* Characteristic : Track Position */
    ClxBleCharacteristicDeclarationAttribute                trackPosition_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      trackPosition_CharacteristicValueAttribute;
    u4                                                      trackPosition_Storage[(CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_SIZE + 3)/4];
    
    /* Characteristic : Media State */
    ClxBleCharacteristicDeclarationAttribute                mediaState_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      mediaState_CharacteristicValueAttribute;
    u4                                                      mediaState_Storage[(CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        mediaState_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Content Control ID */
    ClxBleCharacteristicDeclarationAttribute                contentControlId_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      contentControlId_CharacteristicValueAttribute;
    u4                                                      contentControlId_Storage[(CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_SIZE + 3)/4];
    
    ClxBleAttribute*                                        list[18];

public:
    ClxGenericMediaControlServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&mediaPlayerName_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&mediaPlayerName_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&mediaPlayerName_CharacteristicClientConfigurationAttribute;
        list[4] = (ClxBleAttribute*)&trackChanged_CharacteristicDeclarationAttribute;
        list[5] = (ClxBleAttribute*)&trackChanged_CharacteristicValueAttribute;
        list[6] = (ClxBleAttribute*)&trackChanged_CharacteristicClientConfigurationAttribute;
        list[7] = (ClxBleAttribute*)&trackTitle_CharacteristicDeclarationAttribute;
        list[8] = (ClxBleAttribute*)&trackTitle_CharacteristicValueAttribute;
        list[9] = (ClxBleAttribute*)&trackDuration_CharacteristicDeclarationAttribute;
        list[10] = (ClxBleAttribute*)&trackDuration_CharacteristicValueAttribute;
        list[11] = (ClxBleAttribute*)&trackPosition_CharacteristicDeclarationAttribute;
        list[12] = (ClxBleAttribute*)&trackPosition_CharacteristicValueAttribute;
        list[13] = (ClxBleAttribute*)&mediaState_CharacteristicDeclarationAttribute;
        list[14] = (ClxBleAttribute*)&mediaState_CharacteristicValueAttribute;
        list[15] = (ClxBleAttribute*)&mediaState_CharacteristicClientConfigurationAttribute;
        list[16] = (ClxBleAttribute*)&contentControlId_CharacteristicDeclarationAttribute;
        list[17] = (ClxBleAttribute*)&contentControlId_CharacteristicValueAttribute;
    }
};


static ClxBleGattDatabase* initGenericMediaControlServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxGenericMediaControlServiceGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, sizeof(ClxGenericMediaControlServiceGattServiceDatabase))) ClxGenericMediaControlServiceGattServiceDatabase;
#else
    ClxGenericMediaControlServiceGattServiceDatabase* ret = new ClxGenericMediaControlServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Media Player Name : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->mediaPlayerName_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->mediaPlayerName_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_VALUE_TYPE, (u1*)&ret->mediaPlayerName_Storage, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_SIZE, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicMediaPlayerName, clxDecodeOrgBluetoothCharacteristicMediaPlayerName);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->mediaPlayerName_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Track Changed : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->trackChanged_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->trackChanged_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_VALUE_TYPE, (u1*)&ret->trackChanged_Storage, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_SIZE, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicTrackChanged, clxDecodeOrgBluetoothCharacteristicTrackChanged);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->trackChanged_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Track Title : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->trackTitle_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->trackTitle_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_VALUE_TYPE, (u1*)&ret->trackTitle_Storage, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_SIZE, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicTrackTitle, clxDecodeOrgBluetoothCharacteristicTrackTitle);
        }
        /* </Value> */
    }

    /* Track Duration : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->trackDuration_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->trackDuration_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_VALUE_TYPE, (u1*)&ret->trackDuration_Storage, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_SIZE, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicTrackDuration, clxDecodeOrgBluetoothCharacteristicTrackDuration);
        }
        /* </Value> */
    }

    /* Track Position : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->trackPosition_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->trackPosition_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_VALUE_TYPE, (u1*)&ret->trackPosition_Storage, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_SIZE, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicTrackPosition, clxDecodeOrgBluetoothCharacteristicTrackPosition);
        }
        /* </Value> */
    }

    /* Media State : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->mediaState_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->mediaState_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_VALUE_TYPE, (u1*)&ret->mediaState_Storage, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_SIZE, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicMediaState, clxDecodeOrgBluetoothCharacteristicMediaState);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->mediaState_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Content Control ID : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->contentControlId_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->contentControlId_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_VALUE_TYPE, (u1*)&ret->contentControlId_Storage, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_SIZE, CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicContentControlId, clxDecodeOrgBluetoothCharacteristicContentControlId);
        }
        /* </Value> */
    }

    return ret;
}

static void destroyGenericMediaControlServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxGenericMediaControlServiceGattServiceDatabase*>(database);
}

void genericMediaControlServiceBaseHandleUpdated(u2 baseHandle)
{
}

extern "C"
{

    static ClxBleGattServiceInterface clxGenericMediaControlServiceGattServiceInterface =
    {
        initGenericMediaControlServiceGattServiceDatabase,
        destroyGenericMediaControlServiceGattServiceDatabase,
        genericMediaControlServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetGenericMediaControlServiceGattServiceInterface()
    {
        return &clxGenericMediaControlServiceGattServiceInterface;
    }

    const s1* clxGetGenericMediaControlServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME;
            case CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED;
            case CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE;
            case CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION;
            case CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION;
            case CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE;
            case CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID;
            default : return NULL;
        }
    }
}
