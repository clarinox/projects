/*********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.device_information.cpp
* Description         Implements the GATT Device Information service
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*********************************************************************************/


#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"
#include <new>


/* GATT Service Definition for "Device Information" with the UUID "180A" : */

class ClxDeviceInformationGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Manufacturer Name String */
    ClxBleCharacteristicDeclarationAttribute                manufacturerNameString_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      manufacturerNameString_CharacteristicValueAttribute;
    u4                                                      manufacturerNameString_Storage[(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_SIZE + 3)/4];
    
    /* Characteristic : Model Number String */
    ClxBleCharacteristicDeclarationAttribute                modelNumberString_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      modelNumberString_CharacteristicValueAttribute;
    u4                                                      modelNumberString_Storage[(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_SIZE + 3)/4];
    
    /* Characteristic : Serial Number String */
    ClxBleCharacteristicDeclarationAttribute                serialNumberString_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      serialNumberString_CharacteristicValueAttribute;
    u4                                                      serialNumberString_Storage[(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_SIZE + 3)/4];
    
    /* Characteristic : Hardware Revision String */
    ClxBleCharacteristicDeclarationAttribute                hardwareRevisionString_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      hardwareRevisionString_CharacteristicValueAttribute;
    u4                                                      hardwareRevisionString_Storage[(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_SIZE + 3)/4];
    
    /* Characteristic : Firmware Revision String */
    ClxBleCharacteristicDeclarationAttribute                firmwareRevisionString_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      firmwareRevisionString_CharacteristicValueAttribute;
    u4                                                      firmwareRevisionString_Storage[(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_SIZE + 3)/4];
    
    /* Characteristic : Software Revision String */
    ClxBleCharacteristicDeclarationAttribute                softwareRevisionString_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      softwareRevisionString_CharacteristicValueAttribute;
    u4                                                      softwareRevisionString_Storage[(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_SIZE + 3)/4];
    
    /* Characteristic : System ID */
    ClxBleCharacteristicDeclarationAttribute                systemId_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      systemId_CharacteristicValueAttribute;
    u4                                                      systemId_Storage[(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_SIZE + 3)/4];
    
    /* Characteristic : IEEE 11073-20601 Regulatory Certification Data List */
    ClxBleCharacteristicDeclarationAttribute                ieee11073_20601RegulatoryCertificationDataList_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      ieee11073_20601RegulatoryCertificationDataList_CharacteristicValueAttribute;
    u4                                                      ieee11073_20601RegulatoryCertificationDataList_Storage[(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_SIZE + 3)/4];
    
    /* Characteristic : PnP ID */
    ClxBleCharacteristicDeclarationAttribute                pnpId_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      pnpId_CharacteristicValueAttribute;
    u4                                                      pnpId_Storage[(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_SIZE + 3)/4];
    
    ClxBleAttribute*                                        list[19];

public:
    ClxDeviceInformationGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&manufacturerNameString_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&manufacturerNameString_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&modelNumberString_CharacteristicDeclarationAttribute;
        list[4] = (ClxBleAttribute*)&modelNumberString_CharacteristicValueAttribute;
        list[5] = (ClxBleAttribute*)&serialNumberString_CharacteristicDeclarationAttribute;
        list[6] = (ClxBleAttribute*)&serialNumberString_CharacteristicValueAttribute;
        list[7] = (ClxBleAttribute*)&hardwareRevisionString_CharacteristicDeclarationAttribute;
        list[8] = (ClxBleAttribute*)&hardwareRevisionString_CharacteristicValueAttribute;
        list[9] = (ClxBleAttribute*)&firmwareRevisionString_CharacteristicDeclarationAttribute;
        list[10] = (ClxBleAttribute*)&firmwareRevisionString_CharacteristicValueAttribute;
        list[11] = (ClxBleAttribute*)&softwareRevisionString_CharacteristicDeclarationAttribute;
        list[12] = (ClxBleAttribute*)&softwareRevisionString_CharacteristicValueAttribute;
        list[13] = (ClxBleAttribute*)&systemId_CharacteristicDeclarationAttribute;
        list[14] = (ClxBleAttribute*)&systemId_CharacteristicValueAttribute;
        list[15] = (ClxBleAttribute*)&ieee11073_20601RegulatoryCertificationDataList_CharacteristicDeclarationAttribute;
        list[16] = (ClxBleAttribute*)&ieee11073_20601RegulatoryCertificationDataList_CharacteristicValueAttribute;
        list[17] = (ClxBleAttribute*)&pnpId_CharacteristicDeclarationAttribute;
        list[18] = (ClxBleAttribute*)&pnpId_CharacteristicValueAttribute;
    }
};


static ClxBleGattDatabase* initDeviceInformationGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxDeviceInformationGattServiceDatabase* ret = new (clxAppPoolsetAlloc(0, 0, sizeof(ClxDeviceInformationGattServiceDatabase))) ClxDeviceInformationGattServiceDatabase;
#else
    ClxDeviceInformationGattServiceDatabase* ret = new ClxDeviceInformationGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Manufacturer Name String : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->manufacturerNameString_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->manufacturerNameString_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_VALUE_TYPE, (u1*)&ret->manufacturerNameString_Storage, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_SIZE, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicManufacturerNameString, clxDecodeOrgBluetoothCharacteristicManufacturerNameString);
        }
        /* </Value> */
    }

    /* Model Number String : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->modelNumberString_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->modelNumberString_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_VALUE_TYPE, (u1*)&ret->modelNumberString_Storage, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_SIZE, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicModelNumberString, clxDecodeOrgBluetoothCharacteristicModelNumberString);
        }
        /* </Value> */
    }

    /* Serial Number String : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->serialNumberString_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->serialNumberString_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_VALUE_TYPE, (u1*)&ret->serialNumberString_Storage, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_SIZE, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicSerialNumberString, clxDecodeOrgBluetoothCharacteristicSerialNumberString);
        }
        /* </Value> */
    }

    /* Hardware Revision String : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->hardwareRevisionString_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->hardwareRevisionString_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_VALUE_TYPE, (u1*)&ret->hardwareRevisionString_Storage, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_SIZE, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicHardwareRevisionString, clxDecodeOrgBluetoothCharacteristicHardwareRevisionString);
        }
        /* </Value> */
    }

    /* Firmware Revision String : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->firmwareRevisionString_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->firmwareRevisionString_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_VALUE_TYPE, (u1*)&ret->firmwareRevisionString_Storage, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_SIZE, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicFirmwareRevisionString, clxDecodeOrgBluetoothCharacteristicFirmwareRevisionString);
        }
        /* </Value> */
    }

    /* Software Revision String : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->softwareRevisionString_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->softwareRevisionString_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_VALUE_TYPE, (u1*)&ret->softwareRevisionString_Storage, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_SIZE, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicSoftwareRevisionString, clxDecodeOrgBluetoothCharacteristicSoftwareRevisionString);
        }
        /* </Value> */
    }

    /* System ID : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->systemId_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->systemId_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_VALUE_TYPE, (u1*)&ret->systemId_Storage, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_SIZE, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicSystemId, clxDecodeOrgBluetoothCharacteristicSystemId);
        }
        /* </Value> */
    }

    /* IEEE 11073-20601 Regulatory Certification Data List : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->ieee11073_20601RegulatoryCertificationDataList_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->ieee11073_20601RegulatoryCertificationDataList_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_VALUE_TYPE, (u1*)&ret->ieee11073_20601RegulatoryCertificationDataList_Storage, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_SIZE, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataList, clxDecodeOrgBluetoothCharacteristicIeee11073_20601RegulatoryCertificationDataList);
        }
        /* </Value> */
    }

    /* PnP ID : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->pnpId_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->pnpId_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_VALUE_TYPE, (u1*)&ret->pnpId_Storage, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_SIZE, CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicPnpId, clxDecodeOrgBluetoothCharacteristicPnpId);
        }
        /* </Value> */
    }

    return ret;
}

static void destroyDeviceInformationGattServiceDatabase(ClxBleGattDatabase* database)
{
    clxBleGattServiceList[GattService_DeviceInformationIndex].handleBase = INVALID_SERVICE_BASE_HANDLE;
    delete static_cast<ClxDeviceInformationGattServiceDatabase*>(database);
}

static void deviceInformationServiceBaseHandleUpdated(u2 baseHandle)
{
    clxBleGattServiceList[GattService_DeviceInformationIndex].handleBase = baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxDeviceInformationGattServiceInterface = 
    {
        initDeviceInformationGattServiceDatabase,
        destroyDeviceInformationGattServiceDatabase,
        deviceInformationServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetDeviceInformationGattServiceInterface()
    {
        return &clxDeviceInformationGattServiceInterface;
    }

    const s1* clxGetDeviceInformationGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_HANDLE_INDEX : return CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING;
            case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_HANDLE_INDEX : return CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING;
            case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_HANDLE_INDEX : return CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING;
            case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_HANDLE_INDEX : return CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING;
            case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_HANDLE_INDEX : return CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING;
            case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING_HANDLE_INDEX : return CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SOFTWARE_REVISION_STRING;
            case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID_HANDLE_INDEX : return CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SYSTEM_ID;
            case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_HANDLE_INDEX : return CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST;
            case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID_HANDLE_INDEX : return CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_PNP_ID;
            default : return NULL;
        }
    }
}

