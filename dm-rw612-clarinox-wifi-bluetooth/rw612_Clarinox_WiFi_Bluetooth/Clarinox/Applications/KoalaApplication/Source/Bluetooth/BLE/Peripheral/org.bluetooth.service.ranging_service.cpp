/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.ranging_service.cpp
* Description         Implements the GATT Ranging Service (RAS)
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by
* Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/

#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"
#include <new>

#if defined(CLX_BLE_CS_REFLECTOR)

/* GATT Service Definition for "Ranging Service" UUID 0x185B */

class ClxRangingServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    /* Primary Service */
    ClxBlePrimaryServiceAttribute                       primaryService;

    /* === RAS Features === */
    ClxBleCharacteristicDeclarationAttribute            rasFeatures_Declaration;
    ClxBleCharacteristicValueAttribute                  rasFeatures_Value;
    u4                                                  rasFeatures_Storage[(ClxOrgBluetoothCharacteristicRasFeaturesFields_Size + 3) / 4];

    /* === Real-time Ranging Data === */
    ClxBleCharacteristicDeclarationAttribute            realtimeData_Declaration;
    ClxBleCharacteristicValueAttribute                  realtimeData_Value;
    u4                                                  realtimeData_Storage[(ClxOrgBluetoothCharacteristicRasRealtimeDataFields_Size + 3) / 4];
    ClxBleCharacteristicClientConfigurationAttribute    realtimeData_CharacteristicClientConfigurationAttribute;

    /* === On-demand Ranging Data === */
    ClxBleCharacteristicDeclarationAttribute            ondemandData_Declaration;
    ClxBleCharacteristicValueAttribute                  ondemandData_Value;
    u4                                                  ondemandData_Storage[(ClxOrgBluetoothCharacteristicRasOnDemandDataFields_Size + 3) / 4];
    ClxBleCharacteristicClientConfigurationAttribute    ondemandData_CharacteristicClientConfigurationAttribute;

    /* === RAS Control Point === */
    ClxBleCharacteristicDeclarationAttribute            controlPoint_Declaration;
    ClxBleCharacteristicValueAttribute                  controlPoint_Value;
    u4                                                  controlPoint_Storage[(ClxOrgBluetoothCharacteristicRasControlPointFields_Size + 3) / 4];
    ClxBleCharacteristicClientConfigurationAttribute    controlPoint_CharacteristicClientConfigurationAttribute;

    /* === Ranging Data Ready === */
    ClxBleCharacteristicDeclarationAttribute            dataReady_Declaration;
    ClxBleCharacteristicValueAttribute                  dataReady_Value;
    u4                                                  dataReady_Storage[(ClxOrgBluetoothCharacteristicRasDataReadyFields_Size + 3) / 4];
    ClxBleCharacteristicClientConfigurationAttribute    dataReady_CharacteristicClientConfigurationAttribute;

    /* === Ranging Data Overwritten === */
    ClxBleCharacteristicDeclarationAttribute            dataOverwritten_Declaration;
    ClxBleCharacteristicValueAttribute                  dataOverwritten_Value;
    u4                                                  dataOverwritten_Storage[(ClxOrgBluetoothCharacteristicRasDataOverwrittenFields_Size + 3) / 4];
    ClxBleCharacteristicClientConfigurationAttribute    dataOverwritten_CharacteristicClientConfigurationAttribute;

    ClxBleAttribute* list[18];

public:
    ClxRangingServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list) / sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;

        list[1] = (ClxBleAttribute*)&rasFeatures_Declaration;
        list[2] = (ClxBleAttribute*)&rasFeatures_Value;

        list[3] = (ClxBleAttribute*)&realtimeData_Declaration;
        list[4] = (ClxBleAttribute*)&realtimeData_Value;
        list[5] = (ClxBleAttribute*)&realtimeData_CharacteristicClientConfigurationAttribute;

        list[6] = (ClxBleAttribute*)&ondemandData_Declaration;
        list[7] = (ClxBleAttribute*)&ondemandData_Value;
        list[8] = (ClxBleAttribute*)&ondemandData_CharacteristicClientConfigurationAttribute;

        list[9] = (ClxBleAttribute*)&controlPoint_Declaration;
        list[10] = (ClxBleAttribute*)&controlPoint_Value;
        list[11] = (ClxBleAttribute*)&controlPoint_CharacteristicClientConfigurationAttribute;

        list[12] = (ClxBleAttribute*)&dataReady_Declaration;
        list[13] = (ClxBleAttribute*)&dataReady_Value;
        list[14] = (ClxBleAttribute*)&dataReady_CharacteristicClientConfigurationAttribute;

        list[15] = (ClxBleAttribute*)&dataOverwritten_Declaration;
        list[16] = (ClxBleAttribute*)&dataOverwritten_Value;
        list[17] = (ClxBleAttribute*)&dataOverwritten_CharacteristicClientConfigurationAttribute;
    }
};


static ClxBleGattDatabase* initRangingServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxRangingServiceGattServiceDatabase* ret = new (clxAppPoolsetAlloc(0, 0, sizeof(ClxRangingServiceGattServiceDatabase)))
        ClxRangingServiceGattServiceDatabase;
#else
    ClxRangingServiceGattServiceDatabase* ret = new ClxRangingServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RANGING_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* ---- RAS Features ---- */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->rasFeatures_Declaration, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->rasFeatures_Value,
                                                   &uuid,
                                                   ClxOrgBluetoothCharacteristicRasFeaturesFields_Type,
                                                   (u1*)&ret->rasFeatures_Storage,
                                                   ClxOrgBluetoothCharacteristicRasFeaturesFields_Size,
                                                   CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_PERMISSIONS,
                                                   NULL,
                                                   NULL);
        }
        /* </Value> */
    }

    /* ---- Real-time Data ---- */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->realtimeData_Declaration, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->realtimeData_Value,
                                                   &uuid,
                                                   ClxOrgBluetoothCharacteristicRasRealtimeDataFields_Type,
                                                   (u1*)&ret->realtimeData_Storage,
                                                   ClxOrgBluetoothCharacteristicRasRealtimeDataFields_Size,
                                                   CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_PERMISSIONS,
                                                   NULL,
                                                   NULL);
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->realtimeData_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* ---- On-demand Data ---- */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->ondemandData_Declaration, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->ondemandData_Value,
                                                   &uuid,
                                                   ClxOrgBluetoothCharacteristicRasOnDemandDataFields_Type,
                                                   (u1*)&ret->ondemandData_Storage,
                                                   ClxOrgBluetoothCharacteristicRasOnDemandDataFields_Size,
                                                   CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_PERMISSIONS,
                                                   NULL,
                                                   NULL);
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->ondemandData_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* ---- Control Point ---- */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->controlPoint_Declaration, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->controlPoint_Value,
                                                   &uuid,
                                                   ClxOrgBluetoothCharacteristicRasControlPointFields_Type,
                                                   (u1*)&ret->controlPoint_Storage,
                                                   ClxOrgBluetoothCharacteristicRasControlPointFields_Size,
                                                   CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_PERMISSIONS,
                                                   NULL,
                                                   NULL);
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->controlPoint_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* ---- Data Ready ---- */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->dataReady_Declaration, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->dataReady_Value,
                                                   &uuid,
                                                   ClxOrgBluetoothCharacteristicRasDataReadyFields_Type,
                                                   (u1*)&ret->dataReady_Storage,
                                                   ClxOrgBluetoothCharacteristicRasDataReadyFields_Size,
                                                   CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_PERMISSIONS,
                                                   NULL,
                                                   NULL);
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->dataReady_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* ---- Data Overwritten ---- */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->dataOverwritten_Declaration, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->dataOverwritten_Value,
                                                   &uuid,
                                                   ClxOrgBluetoothCharacteristicRasDataOverwrittenFields_Type,
                                                   (u1*)&ret->dataOverwritten_Storage,
                                                   ClxOrgBluetoothCharacteristicRasDataOverwrittenFields_Size,
                                                   CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_PERMISSIONS,
                                                   NULL,
                                                   NULL);
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->dataOverwritten_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    return ret;
}


static void destroyRangingServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxRangingServiceGattServiceDatabase*>(database);
}

static void rangingServiceBaseHandleUpdated(u2 baseHandle)
{
    clxBleGattServiceList[GattService_RangingServiceIndex].handleBase = baseHandle;
}

extern "C"
{
    static ClxBleGattServiceInterface clxRangingServiceGattServiceInterface =
    {
        initRangingServiceGattServiceDatabase,
        destroyRangingServiceGattServiceDatabase,
        rangingServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetRangingServiceGattServiceInterface()
    {
        return &clxRangingServiceGattServiceInterface;
    }

    const s1* clxGetRangingServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
        case CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_HANDLE_INDEX: return CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES;
        case CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_HANDLE_INDEX: return CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA;
        case CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_HANDLE_INDEX: return CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA;
        case CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_HANDLE_INDEX: return CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT;
        case CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_HANDLE_INDEX: return CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY;
        case CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_HANDLE_INDEX: return CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN;
        default: return NULL;
        }
    }
}

#endif
