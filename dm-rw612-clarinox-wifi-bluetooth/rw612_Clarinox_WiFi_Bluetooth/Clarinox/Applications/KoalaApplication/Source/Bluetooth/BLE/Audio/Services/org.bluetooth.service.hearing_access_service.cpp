/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.hearing_access_service.cpp
* Description         Implements the GATT service Hearing Access Service
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
#include "org.bluetooth.service.hearing_access_service.h"
#include <new>

/* GATT Service Definition for "Hearing Access Service" with the UUID "1854" : */

class ClxHearingAccessServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Hearing Aid Features */
    ClxBleCharacteristicDeclarationAttribute                hearingAidFeatures_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      hearingAidFeatures_CharacteristicValueAttribute;
    u4                                                      hearingAidFeatures_Storage[(CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        hearingAidFeatures_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Hearing Aid Preset Control Point */
    ClxBleCharacteristicDeclarationAttribute                hearingAidPresetControlPoint_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      hearingAidPresetControlPoint_CharacteristicValueAttribute;
    u4                                                      hearingAidPresetControlPoint_Storage[(CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_SIZE + 3)/4];
    
    /* Characteristic : Active Preset Index */
    ClxBleCharacteristicDeclarationAttribute                activePresetIndex_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      activePresetIndex_CharacteristicValueAttribute;
    u4                                                      activePresetIndex_Storage[(CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        activePresetIndex_CharacteristicClientConfigurationAttribute;
    
    ClxBleAttribute*                                        list[9];

public:
    ClxHearingAccessServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&hearingAidFeatures_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&hearingAidFeatures_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&hearingAidFeatures_CharacteristicClientConfigurationAttribute;
        list[4] = (ClxBleAttribute*)&hearingAidPresetControlPoint_CharacteristicDeclarationAttribute;
        list[5] = (ClxBleAttribute*)&hearingAidPresetControlPoint_CharacteristicValueAttribute;
        list[6] = (ClxBleAttribute*)&activePresetIndex_CharacteristicDeclarationAttribute;
        list[7] = (ClxBleAttribute*)&activePresetIndex_CharacteristicValueAttribute;
        list[8] = (ClxBleAttribute*)&activePresetIndex_CharacteristicClientConfigurationAttribute;
    }
};


static ClxBleGattDatabase* initHearingAccessServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxHearingAccessServiceGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, sizeof(ClxHearingAccessServiceGattServiceDatabase))) ClxHearingAccessServiceGattServiceDatabase;
#else
    ClxHearingAccessServiceGattServiceDatabase* ret = new ClxHearingAccessServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Hearing Aid Features : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->hearingAidFeatures_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->hearingAidFeatures_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_VALUE_TYPE, (u1*)&ret->hearingAidFeatures_Storage, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_SIZE, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicHearingAidFeatures, clxDecodeOrgBluetoothCharacteristicHearingAidFeatures);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->hearingAidFeatures_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Hearing Aid Preset Control Point : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->hearingAidPresetControlPoint_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->hearingAidPresetControlPoint_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_VALUE_TYPE, (u1*)&ret->hearingAidPresetControlPoint_Storage, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_SIZE, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicHearingAidPresetControlPoint, clxDecodeOrgBluetoothCharacteristicHearingAidPresetControlPoint);
        }
        /* </Value> */
    }

    /* Active Preset Index : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->activePresetIndex_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->activePresetIndex_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_VALUE_TYPE, (u1*)&ret->activePresetIndex_Storage, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_SIZE, CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicActivePresetIndex, clxDecodeOrgBluetoothCharacteristicActivePresetIndex);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->activePresetIndex_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    return ret;
}

static void destroyHearingAccessServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxHearingAccessServiceGattServiceDatabase*>(database);
}

void hearingAccessServiceBaseHandleUpdated(u2 baseHandle)
{
}

extern "C"
{

    static ClxBleGattServiceInterface clxHearingAccessServiceGattServiceInterface =
    {
        initHearingAccessServiceGattServiceDatabase,
        destroyHearingAccessServiceGattServiceDatabase,
        hearingAccessServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetHearingAccessServiceGattServiceInterface()
    {
        return &clxHearingAccessServiceGattServiceInterface;
    }

    const s1* clxGetHearingAccessServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES_HANDLE_INDEX : return CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_FEATURES;
            case CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT_HANDLE_INDEX : return CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_HEARING_AID_PRESET_CONTROL_POINT;
            case CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX_HANDLE_INDEX : return CLX_GATT_SERVICE_HEARING_ACCESS_SERVICE_CHARACTERISTIC_ACTIVE_PRESET_INDEX;
            default : return NULL;
        }
    }
}
