/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                Gatt.custom_service.cpp
* Description         Implements the GATT Custom Service.
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


#ifdef __cplusplus
extern "C" {
#endif

extern boolean clxInitGattUuid16FromAscii(ClxGattUuid* obj,
                                          const s1* str);


#ifdef __cplusplus
}
#endif

/* GATT Service Definition for "Custom Service" with the UUID "65f2c16489ab523865f2c16489ab5238" : */

class ClxCustomServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Rx Data */
    ClxBleCharacteristicDeclarationAttribute                rxData_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      rxData_CharacteristicValueAttribute;
    u4                                                      rxData_Storage[CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_SIZE];
    ClxBleCharacteristicClientConfigurationAttribute        rxData_CharacteristicClientConfigurationAttribute;

    /* Characteristic : Tx Data */
    ClxBleCharacteristicDeclarationAttribute                txData_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      txData_CharacteristicValueAttribute;
    u4                                                      txData_Storage[CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_SIZE];
    ClxBleCharacteristicClientConfigurationAttribute        txData_CharacteristicClientConfigurationAttribute;
    
    ClxBleAttribute*                                        list[7];

public:
    ClxCustomServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&rxData_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&rxData_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&rxData_CharacteristicClientConfigurationAttribute;
        list[4] = (ClxBleAttribute*)&txData_CharacteristicDeclarationAttribute;
        list[5] = (ClxBleAttribute*)&txData_CharacteristicValueAttribute;
        list[6] = (ClxBleAttribute*)&txData_CharacteristicClientConfigurationAttribute;
    }
};


static ClxBleGattDatabase* initCustomServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxCustomServiceGattServiceDatabase* ret = new (clxAppPoolsetAlloc(0, 0, sizeof(ClxCustomServiceGattServiceDatabase))) ClxCustomServiceGattServiceDatabase;
#else
    ClxCustomServiceGattServiceDatabase* ret = new ClxCustomServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        if(!clxInitGattUuid16FromAscii(&uuid, CLX_GATT_SERVICE_CUSTOM_SERVICE_UUID))
        {
            return NULL;
        }
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Rx Data : */
    {
        /* <Declaration> */
        {
            if(!clxInitGattUuid16FromAscii(&uuid, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_UUID))
            {
                return NULL;
            }
            clxInitBleCharacteristicDeclarationAttribute(&ret->rxData_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            if(!clxInitGattUuid16FromAscii(&uuid, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_UUID))
            {
                return NULL;
            }
            clxInitBleCharacteristicValueAttribute(&ret->rxData_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_VALUE_TYPE, (u1*)&ret->rxData_Storage, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_SIZE, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_PERMISSIONS, clxEncodeGattCustomCharacteristicRxdata, clxDecodeGattCustomCharacteristicRxdata);
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->rxData_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Tx Data : */
    {
        /* <Declaration> */
        {
            if(!clxInitGattUuid16FromAscii(&uuid, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_UUID))
            {
                return NULL;
            }
            clxInitBleCharacteristicDeclarationAttribute(&ret->txData_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            if(!clxInitGattUuid16FromAscii(&uuid, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_UUID))
            {
                return NULL;
            }
            clxInitBleCharacteristicValueAttribute(&ret->txData_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_VALUE_TYPE, (u1*)&ret->txData_Storage, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_SIZE, CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_PERMISSIONS, clxEncodeGattCustomCharacteristicTxdata, clxDecodeGattCustomCharacteristicTxdata);
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->txData_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    return ret;
}

static void destroyCustomServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    clxBleGattServiceList[GattService_CustomIndex].handleBase = INVALID_SERVICE_BASE_HANDLE;
    delete static_cast<ClxCustomServiceGattServiceDatabase*>(database);
}

static void customServiceBaseHandleUpdated(u2 baseHandle)
{
    clxBleGattServiceList[GattService_CustomIndex].handleBase = baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxCustomServiceGattServiceInterface = 
    {
        initCustomServiceGattServiceDatabase,
        destroyCustomServiceGattServiceDatabase,
        customServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetCustomServiceGattServiceInterface()
    {
        return &clxCustomServiceGattServiceInterface;
    }

    const s1* clxGetCustomServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA_HANDLE_INDEX : return CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_RX_DATA;
            case CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA_HANDLE_INDEX : return CLX_GATT_SERVICE_CUSTOM_SERVICE_CHARACTERISTIC_TX_DATA;
            default : return NULL;
        }
    }
}

