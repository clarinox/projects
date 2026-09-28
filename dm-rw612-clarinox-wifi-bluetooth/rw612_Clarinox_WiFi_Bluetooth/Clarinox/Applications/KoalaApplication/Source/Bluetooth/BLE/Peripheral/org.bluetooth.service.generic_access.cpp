/*******************************************************************************
*
* Project             ClarinoxBlue Low Energy
* File                org.bluetooth.service.generic_access.cpp
* Description         Implements the GATT service Generic Access
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

/*********************************************
ClxBleNullAttribute (Only used for handle 0):
**********************************************/
typedef struct ClxBleNullAttributeStruct
{
    ClxBleAttribute               base;
} ClxBleNullAttribute;

ClxSize getCurrentValueLength_ClxBleNullAttribute (const ClxBleAttributeStruct* attr, u1 remoteDeviceIndex)
{
    (void) attr;
    (void) remoteDeviceIndex;
    return 0;
}

u1 readValue_ClxBleNullAttribute (const ClxBleAttributeStruct* attr,
                                  u1 remoteDeviceIndex,
                                  u1* buf, 
                                  ClxSize offset, 
                                  ClxSize maxLengthToRead)
{
    (void) attr;
    (void) remoteDeviceIndex;
    (void) buf;
    (void) offset;
    (void) maxLengthToRead;
    return ClxBleErrorCode_InvalidHandle;
}

u1 writeValue_ClxBleNullAttribute (ClxBleAttributeStruct* attr,
                                   u1 remoteDeviceIndex,
                                   const u1* data,
                                   ClxSize offset,
                                   ClxSize dataLen)
{
    (void) attr;
    (void) remoteDeviceIndex;
    (void) data;
    (void) offset;
    (void) dataLen;
    return ClxBleErrorCode_InvalidHandle;
}

boolean compareValue_ClxBleNullAttribute(const ClxBleAttributeStruct* attr,
                                        u1 remoteDeviceIndex,
                                        const u1* data)
{
    (void) attr;
    (void) remoteDeviceIndex;
    (void) data;
    return FALSE;
}

/* GATT Service Definition for "Generic Access" with the UUID "1800" : */

class ClxGenericAccessGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBleNullAttribute                                     nullAttr;
    
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Device Name */
    ClxBleCharacteristicDeclarationAttribute                deviceName_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      deviceName_CharacteristicValueAttribute;
    u4                                                      deviceName_Storage[(CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_SIZE + 3)/4];
    
    /* Characteristic : Appearance */
    ClxBleCharacteristicDeclarationAttribute                appearance_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      appearance_CharacteristicValueAttribute;
    u4                                                      appearance_Storage[(CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_SIZE + 3)/4];
    
    /* Characteristic : Peripheral Preferred Connection Parameters */
    ClxBleCharacteristicDeclarationAttribute                peripheralPreferredConnectionParameters_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      peripheralPreferredConnectionParameters_CharacteristicValueAttribute;
    u4                                                      peripheralPreferredConnectionParameters_Storage[(CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_SIZE + 3)/4];
    
    /* Characteristic : Central Address Resolution */
    ClxBleCharacteristicDeclarationAttribute                centralAddressResolution_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      centralAddressResolution_CharacteristicValueAttribute;
    u4                                                      centralAddressResolution_Storage[(CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_SIZE + 3)/4];
    
    /* Characteristic : Resolvable Private Address Only */
    ClxBleCharacteristicDeclarationAttribute                resolvablePrivateAddressOnly_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      resolvablePrivateAddressOnly_CharacteristicValueAttribute;
    u4                                                      resolvablePrivateAddressOnly_Storage[(CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_SIZE + 3)/4];
    
    /* Characteristic : Encrypted Data Key Material */
    ClxBleCharacteristicDeclarationAttribute                encryptedDataKeyMaterial_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      encryptedDataKeyMaterial_CharacteristicValueAttribute;
    u4                                                      encryptedDataKeyMaterial_Storage[(CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_SIZE + 3)/4];
    
    /* Characteristic : LE GATT Security Levels */
    ClxBleCharacteristicDeclarationAttribute                leGattSecurityLevels_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      leGattSecurityLevels_CharacteristicValueAttribute;
    u4                                                      leGattSecurityLevels_Storage[(CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_SIZE + 3)/4];
    
    ClxBleAttribute*                                        list[16];

public:
    ClxGenericAccessGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&nullAttr;
        list[1] = (ClxBleAttribute*)&primaryService;
        list[2] = (ClxBleAttribute*)&deviceName_CharacteristicDeclarationAttribute;
        list[3] = (ClxBleAttribute*)&deviceName_CharacteristicValueAttribute;
        list[4] = (ClxBleAttribute*)&appearance_CharacteristicDeclarationAttribute;
        list[5] = (ClxBleAttribute*)&appearance_CharacteristicValueAttribute;
        list[6] = (ClxBleAttribute*)&peripheralPreferredConnectionParameters_CharacteristicDeclarationAttribute;
        list[7] = (ClxBleAttribute*)&peripheralPreferredConnectionParameters_CharacteristicValueAttribute;
        list[8] = (ClxBleAttribute*)&centralAddressResolution_CharacteristicDeclarationAttribute;
        list[9] = (ClxBleAttribute*)&centralAddressResolution_CharacteristicValueAttribute;
        list[10] = (ClxBleAttribute*)&resolvablePrivateAddressOnly_CharacteristicDeclarationAttribute;
        list[11] = (ClxBleAttribute*)&resolvablePrivateAddressOnly_CharacteristicValueAttribute;
        list[12] = (ClxBleAttribute*)&encryptedDataKeyMaterial_CharacteristicDeclarationAttribute;
        list[13] = (ClxBleAttribute*)&encryptedDataKeyMaterial_CharacteristicValueAttribute;
        list[14] = (ClxBleAttribute*)&leGattSecurityLevels_CharacteristicDeclarationAttribute;
        list[15] = (ClxBleAttribute*)&leGattSecurityLevels_CharacteristicValueAttribute;
    }
};


static ClxBleGattDatabase* initGenericAccessGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxGenericAccessGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, 0, sizeof(ClxGenericAccessGattServiceDatabase))) ClxGenericAccessGattServiceDatabase;
#else
    ClxGenericAccessGattServiceDatabase* ret = new ClxGenericAccessGattServiceDatabase;
#endif

    /*  Handle 0 (Invalid): */
    ret->nullAttr.base.base.rtti = NULL;
    ret->nullAttr.base.valueType = ClxBleAttributeValueType_FixedLength;
    clxInitGattUuid16FromAscii(&ret->nullAttr.base.uuid, "0000-0000-0000-0000-0000-0000-0000-0000");
    ret->nullAttr.base.handle = 0;
    ret->nullAttr.base.permissions = 0;
    ret->nullAttr.base.groupEndHandle = CLX_GATT_INVALID_GROUP_END_HANDLE;
    ret->nullAttr.base.initAttribute = NULL;
    ret->nullAttr.base.getCurrentValueLength = getCurrentValueLength_ClxBleNullAttribute;
    ret->nullAttr.base.readValue = readValue_ClxBleNullAttribute;
    ret->nullAttr.base.writeValue = writeValue_ClxBleNullAttribute;
    ret->nullAttr.base.compare = compareValue_ClxBleNullAttribute;

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Device Name : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->deviceName_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->deviceName_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_VALUE_TYPE, (u1*)&ret->deviceName_Storage, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_SIZE, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGapDeviceName, clxDecodeOrgBluetoothCharacteristicGapDeviceName);
        }
        /* </Value> */
    }

    /* Appearance : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->appearance_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->appearance_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_VALUE_TYPE, (u1*)&ret->appearance_Storage, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_SIZE, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGapAppearance, clxDecodeOrgBluetoothCharacteristicGapAppearance);
        }
        /* </Value> */
    }

    /* Peripheral Preferred Connection Parameters : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->peripheralPreferredConnectionParameters_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->peripheralPreferredConnectionParameters_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_VALUE_TYPE, (u1*)&ret->peripheralPreferredConnectionParameters_Storage, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_SIZE, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParameters, clxDecodeOrgBluetoothCharacteristicGapPeripheralPreferredConnectionParameters);
        }
        /* </Value> */
    }

    /* Central Address Resolution : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->centralAddressResolution_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->centralAddressResolution_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_VALUE_TYPE, (u1*)&ret->centralAddressResolution_Storage, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_SIZE, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGapCentralAddressResolutionSupport, clxDecodeOrgBluetoothCharacteristicGapCentralAddressResolutionSupport);
        }
        /* </Value> */
    }

    /* Resolvable Private Address Only : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->resolvablePrivateAddressOnly_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->resolvablePrivateAddressOnly_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_VALUE_TYPE, (u1*)&ret->resolvablePrivateAddressOnly_Storage, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_SIZE, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly, clxDecodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly);
        }
        /* </Value> */
    }

    /* Encrypted Data Key Material : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->encryptedDataKeyMaterial_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->encryptedDataKeyMaterial_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_VALUE_TYPE, (u1*)&ret->encryptedDataKeyMaterial_Storage, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_SIZE, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly, clxDecodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly);
        }
        /* </Value> */
    }

    /* LE GATT Security Levels : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->leGattSecurityLevels_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->leGattSecurityLevels_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_VALUE_TYPE, (u1*)&ret->leGattSecurityLevels_Storage, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_SIZE, CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGapLeGattSecurityLevels, clxDecodeOrgBluetoothCharacteristicGapLeGattSecurityLevels);
        }
        /* </Value> */
    }

    return ret;
}

static void destroyGenericAccessGattServiceDatabase(ClxBleGattDatabase* database)
{
    clxBleGattServiceList[GattService_GenericAccessIndex].handleBase = INVALID_SERVICE_BASE_HANDLE;
    delete static_cast<ClxGenericAccessGattServiceDatabase*>(database);
}

static void genericAccessBaseHandleUpdated(u2 baseHandle)
{
    clxBleGattServiceList[GattService_GenericAccessIndex].handleBase = baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxGenericAccessGattServiceInterface = 
    {
        initGenericAccessGattServiceDatabase,
        destroyGenericAccessGattServiceDatabase,
        genericAccessBaseHandleUpdated

    };

    const ClxBleGattServiceInterface* clxGetGenericAccessGattServiceInterface()
    {
        return &clxGenericAccessGattServiceInterface;
    }

    const s1* clxGetGenericAccessGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME;
            case CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE;
            case CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS;
            case CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_CENTRAL_ADDRESS_RESOLUTION;
            case CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_RESOLVABLE_PRIVATE_ADDRESS_ONLY;
            case CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_ENCRYPTED_DATA_KEY_MATERIAL;
            case CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS_HANDLE_INDEX : return CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_LE_GATT_SECURITY_LEVELS;
            default : return NULL;
        }
    }
}

