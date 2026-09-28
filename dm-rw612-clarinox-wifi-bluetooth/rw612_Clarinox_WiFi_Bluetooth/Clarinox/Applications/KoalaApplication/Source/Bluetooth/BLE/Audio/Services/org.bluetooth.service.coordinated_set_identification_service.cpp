/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.coordinated_set_identification_service.cpp
* Description         Implements the GATT service Coordinated Set Identification Service
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
#include "Gatt.Ble.Includes.h"
#include <new>
#include "org.bluetooth.service.coordinated_set_identification_service.h"


/* GATT Service Definition for "Coordinated Set Identification Service" with the UUID "1846" : */

class ClxCoordinatedSetIdentificationServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Set Identity Resolving Key */
    ClxBleCharacteristicDeclarationAttribute                setIdentityResolvingKey_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      setIdentityResolvingKey_CharacteristicValueAttribute;
    u4                                                      setIdentityResolvingKey_Storage[(CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_SIZE + 3)/4];
    
    /* Characteristic : Coordinated Set Size */
    ClxBleCharacteristicDeclarationAttribute                coordinatedSetSize_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      coordinatedSetSize_CharacteristicValueAttribute;
    u4                                                      coordinatedSetSize_Storage[(CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_SIZE + 3)/4];
    
    /* Characteristic : Set Member Lock */
    ClxBleCharacteristicDeclarationAttribute                setMemberLock_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      setMemberLock_CharacteristicValueAttribute;
    u4                                                      setMemberLock_Storage[(CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        setMemberLock_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Set Member Rank */
    ClxBleCharacteristicDeclarationAttribute                setMemberRank_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      setMemberRank_CharacteristicValueAttribute;
    u4                                                      setMemberRank_Storage[(CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_SIZE + 3)/4];
    
    ClxBleAttribute*                                        list[10];

public:
    ClxCoordinatedSetIdentificationServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&setIdentityResolvingKey_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&setIdentityResolvingKey_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&coordinatedSetSize_CharacteristicDeclarationAttribute;
        list[4] = (ClxBleAttribute*)&coordinatedSetSize_CharacteristicValueAttribute;
        list[5] = (ClxBleAttribute*)&setMemberLock_CharacteristicDeclarationAttribute;
        list[6] = (ClxBleAttribute*)&setMemberLock_CharacteristicValueAttribute;
        list[7] = (ClxBleAttribute*)&setMemberLock_CharacteristicClientConfigurationAttribute;
        list[8] = (ClxBleAttribute*)&setMemberRank_CharacteristicDeclarationAttribute;
        list[9] = (ClxBleAttribute*)&setMemberRank_CharacteristicValueAttribute;
    }
};


static ClxBleGattDatabase* initCoordinatedSetIdentificationServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxCoordinatedSetIdentificationServiceGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, sizeof(ClxCoordinatedSetIdentificationServiceGattServiceDatabase))) ClxCoordinatedSetIdentificationServiceGattServiceDatabase;
#else
    ClxCoordinatedSetIdentificationServiceGattServiceDatabase* ret = new ClxCoordinatedSetIdentificationServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Set Identity Resolving Key : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->setIdentityResolvingKey_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->setIdentityResolvingKey_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_VALUE_TYPE, (u1*)&ret->setIdentityResolvingKey_Storage, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_SIZE, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicSetIdentityResolvingKey, clxDecodeOrgBluetoothCharacteristicSetIdentityResolvingKey);
        }
        /* </Value> */
    }

    /* Coordinated Set Size : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->coordinatedSetSize_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->coordinatedSetSize_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_VALUE_TYPE, (u1*)&ret->coordinatedSetSize_Storage, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_SIZE, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicCoordinatedSetSize, clxDecodeOrgBluetoothCharacteristicCoordinatedSetSize);
        }
        /* </Value> */
    }

    /* Set Member Lock : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->setMemberLock_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->setMemberLock_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_VALUE_TYPE, (u1*)&ret->setMemberLock_Storage, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_SIZE, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicSetMemberLock, clxDecodeOrgBluetoothCharacteristicSetMemberLock);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->setMemberLock_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Set Member Rank : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->setMemberRank_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->setMemberRank_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_VALUE_TYPE, (u1*)&ret->setMemberRank_Storage, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_SIZE, CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicSetMemberRank, clxDecodeOrgBluetoothCharacteristicSetMemberRank);
        }
        /* </Value> */
    }

    return ret;
}

static void destroyCoordinatedSetIdentificationServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxCoordinatedSetIdentificationServiceGattServiceDatabase*>(database);
}

void coordinatedSetIdentificationServiceBaseHandleUpdated(u2 baseHandle)
{
}

extern "C"
{

    static ClxBleGattServiceInterface clxCoordinatedSetIdentificationServiceGattServiceInterface =
    {
        initCoordinatedSetIdentificationServiceGattServiceDatabase,
        destroyCoordinatedSetIdentificationServiceGattServiceDatabase,
        coordinatedSetIdentificationServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetCoordinatedSetIdentificationServiceGattServiceInterface()
    {
        return &clxCoordinatedSetIdentificationServiceGattServiceInterface;
    }

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
    const s1* clxGetCoordinatedSetIdentificationServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_HANDLE_INDEX : return CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY;
            case CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_HANDLE_INDEX : return CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE;
            case CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_HANDLE_INDEX : return CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK;
            case CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_HANDLE_INDEX : return CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK;
            default : return NULL;
        }
    }
#endif /* CLX_BLE_GATT_SERVICE_VERBOSE */
}

