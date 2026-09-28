/*******************************************************************************
*
* Project             ClarinoxBlue Low Energy
* File                org.bluetooth.service.generic_attribute.cpp
* Description         Implements the GATT service Generic Attribute
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/


#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"
#include <new>


/* GATT Service Definition for "Generic Attribute" with the UUID "1801" : */

class ClxGenericAttributeGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Service Changed */
    ClxBleCharacteristicDeclarationAttribute                serviceChanged_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      serviceChanged_CharacteristicValueAttribute;
    u4                                                      serviceChanged_Storage[(CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        serviceChanged_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Client Supported Feature */
    ClxBleCharacteristicDeclarationAttribute                clientSupportedFeature_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      clientSupportedFeature_CharacteristicValueAttribute;
    u4                                                      clientSupportedFeature_Storage[(CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_SIZE + 3)/4];
    
    /* Characteristic : Database Hash */
    ClxBleCharacteristicDeclarationAttribute                databaseHash_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      databaseHash_CharacteristicValueAttribute;
    u4                                                      databaseHash_Storage[(CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_SIZE + 3)/4];
    
    /* Characteristic : Server Supported Feature */
    ClxBleCharacteristicDeclarationAttribute                serverSupportedFeature_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      serverSupportedFeature_CharacteristicValueAttribute;
    u4                                                      serverSupportedFeature_Storage[(CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_SIZE + 3)/4];
    
    ClxBleAttribute*                                        list[10];

public:
    ClxGenericAttributeGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&serviceChanged_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&serviceChanged_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&serviceChanged_CharacteristicClientConfigurationAttribute;
        list[4] = (ClxBleAttribute*)&clientSupportedFeature_CharacteristicDeclarationAttribute;
        list[5] = (ClxBleAttribute*)&clientSupportedFeature_CharacteristicValueAttribute;
        list[6] = (ClxBleAttribute*)&databaseHash_CharacteristicDeclarationAttribute;
        list[7] = (ClxBleAttribute*)&databaseHash_CharacteristicValueAttribute;
        list[8] = (ClxBleAttribute*)&serverSupportedFeature_CharacteristicDeclarationAttribute;
        list[9] = (ClxBleAttribute*)&serverSupportedFeature_CharacteristicValueAttribute;
    }
};


static ClxBleGattDatabase* initGenericAttributeGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxGenericAttributeGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, 0, sizeof(ClxGenericAttributeGattServiceDatabase))) ClxGenericAttributeGattServiceDatabase;
#else
    ClxGenericAttributeGattServiceDatabase* ret = new ClxGenericAttributeGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Service Changed : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->serviceChanged_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->serviceChanged_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_VALUE_TYPE, (u1*)&ret->serviceChanged_Storage, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_SIZE, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGattServiceChanged, clxDecodeOrgBluetoothCharacteristicGattServiceChanged);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->serviceChanged_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Client Supported Feature : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->clientSupportedFeature_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->clientSupportedFeature_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_VALUE_TYPE, (u1*)&ret->clientSupportedFeature_Storage, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_SIZE, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGattClientSupportedFeature, clxDecodeOrgBluetoothCharacteristicGattClientSupportedFeature);
        }
        /* </Value> */
    }

    /* Database Hash : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->databaseHash_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->databaseHash_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_VALUE_TYPE, (u1*)&ret->databaseHash_Storage, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_SIZE, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGattDatabaseHash, clxDecodeOrgBluetoothCharacteristicGattDatabaseHash);
        }
        /* </Value> */
    }

    /* Server Supported Feature : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->serverSupportedFeature_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->serverSupportedFeature_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_VALUE_TYPE, (u1*)&ret->serverSupportedFeature_Storage, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_SIZE, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGattServerSupportedFeature, clxDecodeOrgBluetoothCharacteristicGattServerSupportedFeature);
        }
        /* </Value> */
    }

    return ret;
}

static void destroyGenericAttributeGattServiceDatabase(ClxBleGattDatabase* database)
{
    clxBleGattServiceList[GattService_GenericAttributeIndex].handleBase = INVALID_SERVICE_BASE_HANDLE;
    delete static_cast<ClxGenericAttributeGattServiceDatabase*>(database);
}

static void genericAttributeServiceBaseHandleUpdated(u2 baseHandle)
{
    clxBleGattServiceList[GattService_GenericAttributeIndex].handleBase = baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxGenericAttributeGattServiceInterface = 
    {
        initGenericAttributeGattServiceDatabase,
        destroyGenericAttributeGattServiceDatabase,
        genericAttributeServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetGenericAttributeGattServiceInterface()
    {
        return &clxGenericAttributeGattServiceInterface;
    }

    const s1* clxGetGenericAttributeGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVICE_CHANGED;
            case CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_CLIENT_SUPPORTED_FEATURE;
            case CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_DATABASE_HASH;
            case CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE;
            default : return NULL;
        }
    }
}

