/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.battery_service.cpp
* Description         Implements the GATT Battery Service
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/


#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"
#include <new>


/* GATT Service Definition for "Battery Service" with the UUID "180F" : */

class ClxBatteryServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Battery Level */
    ClxBleCharacteristicDeclarationAttribute                batteryLevel_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      batteryLevel_CharacteristicValueAttribute;
    u4                                                      batteryLevel_Storage[(CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        batteryLevel_CharacteristicClientConfigurationAttribute;
    
    ClxBleAttribute*                                        list[4];

public:
    ClxBatteryServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&batteryLevel_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&batteryLevel_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&batteryLevel_CharacteristicClientConfigurationAttribute;
    }
};


static ClxBleGattDatabase* initBatteryServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxBatteryServiceGattServiceDatabase* ret = new (clxAppPoolsetAlloc(0, 0, sizeof(ClxBatteryServiceGattServiceDatabase))) ClxBatteryServiceGattServiceDatabase;
#else
    ClxBatteryServiceGattServiceDatabase* ret = new ClxBatteryServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_BATTERY_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Battery Level : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->batteryLevel_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->batteryLevel_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_VALUE_TYPE, (u1*)&ret->batteryLevel_Storage, CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_SIZE, CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicBatteryLevel, clxDecodeOrgBluetoothCharacteristicBatteryLevel);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->batteryLevel_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    return ret;
}

static void destroyBatteryServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    clxBleGattServiceList[GattService_BatteryIndex].handleBase = INVALID_SERVICE_BASE_HANDLE;
    delete static_cast<ClxBatteryServiceGattServiceDatabase*>(database);
}

static void batteryServiceBaseHandleUpdated(u2 baseHandle)
{
    clxBleGattServiceList[GattService_BatteryIndex].handleBase = baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxBatteryServiceGattServiceInterface =
    {
        initBatteryServiceGattServiceDatabase,
        destroyBatteryServiceGattServiceDatabase,
        batteryServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetBatteryServiceGattServiceInterface()
    {
        return &clxBatteryServiceGattServiceInterface;
    }

    const s1* clxGetBatteryServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_HANDLE_INDEX : return CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL;
            default : return NULL;
        }
    }
}

