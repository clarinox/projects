/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.volume_control_service.cpp
* Description         Implements the GATT service Volume Control Service
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
#include "org.bluetooth.service.volume_control_service.h"
#include "org.bluetooth.service.volume_offset_control_service.h"
#include <new>


/* GATT Service Definition for "Volume Control Service" with the UUID "1844" : */

class ClxVolumeControlServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Volume State */
    ClxBleCharacteristicDeclarationAttribute                volumeState_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      volumeState_CharacteristicValueAttribute;
    u4                                                      volumeState_Storage[(CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        volumeState_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Volume Control Point */
    ClxBleCharacteristicDeclarationAttribute                volumeControlPoint_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      volumeControlPoint_CharacteristicValueAttribute;
    u4                                                      volumeControlPoint_Storage[(CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_SIZE + 3)/4];
    
    /* Characteristic : Volume Flags */
    ClxBleCharacteristicDeclarationAttribute                volumeFlags_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      volumeFlags_CharacteristicValueAttribute;
    u4                                                      volumeFlags_Storage[(CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        volumeFlags_CharacteristicClientConfigurationAttribute;

    /* Secondary service */
    ClxBleSecondaryServiceAttribute                         secondaryService;

    /* Include service */
    ClxBleCharacteristicIncludeDefinitionAttribute          includeService;

    /* Characteristic : Offset State */
    ClxBleCharacteristicDeclarationAttribute                offsetState_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      offsetState_CharacteristicValueAttribute;
    u4                                                      offsetState_Storage[(CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        offsetState_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Audio Location */
    ClxBleCharacteristicDeclarationAttribute                audioLocation_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      audioLocation_CharacteristicValueAttribute;
    u4                                                      audioLocation_Storage[(CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        audioLocation_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Volume Offset Control Point */
    ClxBleCharacteristicDeclarationAttribute                volumeOffsetControlPoint_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      volumeOffsetControlPoint_CharacteristicValueAttribute;
    u4                                                      volumeOffsetControlPoint_Storage[(CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_SIZE + 3)/4];
    
    /* Characteristic : Audio Output Description */
    ClxBleCharacteristicDeclarationAttribute                audioOutputDescription_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      audioOutputDescription_CharacteristicValueAttribute;
    u4                                                      audioOutputDescription_Storage[(CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        audioOutputDescription_CharacteristicClientConfigurationAttribute;
    
    ClxBleAttribute*                                        list[22];

public:
    ClxVolumeControlServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&volumeState_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&volumeState_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&volumeState_CharacteristicClientConfigurationAttribute;
        list[4] = (ClxBleAttribute*)&volumeControlPoint_CharacteristicDeclarationAttribute;
        list[5] = (ClxBleAttribute*)&volumeControlPoint_CharacteristicValueAttribute;
        list[6] = (ClxBleAttribute*)&volumeFlags_CharacteristicDeclarationAttribute;
        list[7] = (ClxBleAttribute*)&volumeFlags_CharacteristicValueAttribute;
        list[8] = (ClxBleAttribute*)&volumeFlags_CharacteristicClientConfigurationAttribute;
        list[9] = (ClxBleAttribute*)&secondaryService;
        list[10] = (ClxBleAttribute*)&includeService;
        list[11] = (ClxBleAttribute*)&offsetState_CharacteristicDeclarationAttribute;
        list[12] = (ClxBleAttribute*)&offsetState_CharacteristicValueAttribute;
        list[13] = (ClxBleAttribute*)&offsetState_CharacteristicClientConfigurationAttribute;
        list[14] = (ClxBleAttribute*)&audioLocation_CharacteristicDeclarationAttribute;
        list[15] = (ClxBleAttribute*)&audioLocation_CharacteristicValueAttribute;
        list[16] = (ClxBleAttribute*)&audioLocation_CharacteristicClientConfigurationAttribute;
        list[17] = (ClxBleAttribute*)&volumeOffsetControlPoint_CharacteristicDeclarationAttribute;
        list[18] = (ClxBleAttribute*)&volumeOffsetControlPoint_CharacteristicValueAttribute;
        list[19] = (ClxBleAttribute*)&audioOutputDescription_CharacteristicDeclarationAttribute;
        list[20] = (ClxBleAttribute*)&audioOutputDescription_CharacteristicValueAttribute;
        list[21] = (ClxBleAttribute*)&audioOutputDescription_CharacteristicClientConfigurationAttribute;
    }
};


static ClxBleGattDatabase* initVolumeControlServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxVolumeControlServiceGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, sizeof(ClxVolumeControlServiceGattServiceDatabase))) ClxVolumeControlServiceGattServiceDatabase;
#else
    ClxVolumeControlServiceGattServiceDatabase* ret = new ClxVolumeControlServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Volume State : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->volumeState_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->volumeState_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_VALUE_TYPE, (u1*)&ret->volumeState_Storage, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_SIZE, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicVolumeState, clxDecodeOrgBluetoothCharacteristicVolumeState);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->volumeState_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Volume Control Point : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->volumeControlPoint_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->volumeControlPoint_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_VALUE_TYPE, (u1*)&ret->volumeControlPoint_Storage, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_SIZE, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicVolumeControlPoint, clxDecodeOrgBluetoothCharacteristicVolumeControlPoint);
        }
        /* </Value> */
    }

    /* Volume Flags : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->volumeFlags_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->volumeFlags_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_VALUE_TYPE, (u1*)&ret->volumeFlags_Storage, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_SIZE, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicVolumeFlags, clxDecodeOrgBluetoothCharacteristicVolumeFlags);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->volumeFlags_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }
    
    /* Secondary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_UUID);
        clxInitBleSecondaryServiceAttribute(&ret->secondaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }
    
    /* Include Volume Offset Control Service */
    {
        clxInitBleCharacteristicIncludeDefinitionAttribute(&ret->includeService, 11, 20, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_UUID);
    }
    
    /* Offset State : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->offsetState_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->offsetState_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_VALUE_TYPE, (u1*)&ret->offsetState_Storage, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_SIZE, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_OFFSET_STATE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicVolumeOffsetState, clxDecodeOrgBluetoothCharacteristicVolumeOffsetState);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->offsetState_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }
    
    /* Audio Location : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->audioLocation_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->audioLocation_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_VALUE_TYPE, (u1*)&ret->audioLocation_Storage, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_SIZE, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_LOCATION_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicAudioLocation, clxDecodeOrgBluetoothCharacteristicAudioLocation);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->audioLocation_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }
    
    /* Volume Offset Control Point : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->volumeOffsetControlPoint_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->volumeOffsetControlPoint_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_VALUE_TYPE, (u1*)&ret->volumeOffsetControlPoint_Storage, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_SIZE, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_OFFSET_CONTROL_POINT_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicVolumeOffsetControlPoint, clxDecodeOrgBluetoothCharacteristicVolumeOffsetControlPoint);
        }
        /* </Value> */
    }
    
    /* Audio Output Description : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->audioOutputDescription_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->audioOutputDescription_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_VALUE_TYPE, (u1*)&ret->audioOutputDescription_Storage, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_SIZE, CLX_GATT_SERVICE_VOLUME_OFFSET_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_OUTPUT_DESCRIPTION_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicAudioOutputDescription, clxDecodeOrgBluetoothCharacteristicAudioOutputDescription);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->audioOutputDescription_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }
    
    return ret;
}

static void destroyVolumeControlServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxVolumeControlServiceGattServiceDatabase*>(database);
}

void volumeControlServiceBaseHandleUpdated (u2 baseHandle)
{
    (void)baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxVolumeControlServiceGattServiceInterface =
    {
        initVolumeControlServiceGattServiceDatabase,
        destroyVolumeControlServiceGattServiceDatabase,
        volumeControlServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetVolumeControlServiceGattServiceInterface()
    {
        return &clxVolumeControlServiceGattServiceInterface;
    }

    const s1* clxGetVolumeControlServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE_HANDLE_INDEX : return CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_STATE;
            case CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT_HANDLE_INDEX : return CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_CONTROL_POINT;
            case CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS_HANDLE_INDEX : return CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_CHARACTERISTIC_VOLUME_FLAGS;
            default : return NULL;
        }
    }
}
