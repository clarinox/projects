/********************************************************************************
*
* Project             BLE GATT Combined SIG Application
* File                org.bluetooth.service.human_interface_device.cpp
* Description         Implements the GATT Human Interface Device Service.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/


#if defined(CLX_BLE_HID)
#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"
#include <new>


/* GATT Service Definition for "Human Interface Device" with the UUID "1812" : */

class ClxHumanInterfaceDeviceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Protocol Mode */
    ClxBleCharacteristicDeclarationAttribute                protocolMode_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      protocolMode_CharacteristicValueAttribute;
    u4                                                      protocolMode_Storage[(CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_SIZE + 3)/4];
    
    /* Characteristic : Report */
    ClxBleCharacteristicDeclarationAttribute                report_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      report_CharacteristicValueAttribute;
    u4                                                      report_Storage[(CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        report_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Report Map */
    ClxBleCharacteristicDeclarationAttribute                reportMap_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      reportMap_CharacteristicValueAttribute;
    u4                                                      reportMap_Storage[(CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_SIZE + 3)/4];
    
    /* Characteristic : Boot Keyboard Input Report */
    ClxBleCharacteristicDeclarationAttribute                bootKeyboardInputReport_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      bootKeyboardInputReport_CharacteristicValueAttribute;
    u4                                                      bootKeyboardInputReport_Storage[(CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        bootKeyboardInputReport_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Boot Keyboard Output Report */
    ClxBleCharacteristicDeclarationAttribute                bootKeyboardOutputReport_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      bootKeyboardOutputReport_CharacteristicValueAttribute;
    u4                                                      bootKeyboardOutputReport_Storage[(CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_SIZE + 3)/4];
    
    /* Characteristic : HID Information */
    ClxBleCharacteristicDeclarationAttribute                hidInformation_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      hidInformation_CharacteristicValueAttribute;
    u4                                                      hidInformation_Storage[(CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_SIZE + 3)/4];
    
    /* Characteristic : HID Control Point */
    ClxBleCharacteristicDeclarationAttribute                hidControlPoint_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      hidControlPoint_CharacteristicValueAttribute;
    u4                                                      hidControlPoint_Storage[(CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_SIZE + 3)/4];
    
    ClxBleAttribute*                                        list[17];

public:
    ClxHumanInterfaceDeviceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&protocolMode_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&protocolMode_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&report_CharacteristicDeclarationAttribute;
        list[4] = (ClxBleAttribute*)&report_CharacteristicValueAttribute;
        list[5] = (ClxBleAttribute*)&report_CharacteristicClientConfigurationAttribute;
        list[6] = (ClxBleAttribute*)&reportMap_CharacteristicDeclarationAttribute;
        list[7] = (ClxBleAttribute*)&reportMap_CharacteristicValueAttribute;
        list[8] = (ClxBleAttribute*)&bootKeyboardInputReport_CharacteristicDeclarationAttribute;
        list[9] = (ClxBleAttribute*)&bootKeyboardInputReport_CharacteristicValueAttribute;
        list[10] = (ClxBleAttribute*)&bootKeyboardInputReport_CharacteristicClientConfigurationAttribute;
        list[11] = (ClxBleAttribute*)&bootKeyboardOutputReport_CharacteristicDeclarationAttribute;
        list[12] = (ClxBleAttribute*)&bootKeyboardOutputReport_CharacteristicValueAttribute;
        list[13] = (ClxBleAttribute*)&hidInformation_CharacteristicDeclarationAttribute;
        list[14] = (ClxBleAttribute*)&hidInformation_CharacteristicValueAttribute;
        list[15] = (ClxBleAttribute*)&hidControlPoint_CharacteristicDeclarationAttribute;
        list[16] = (ClxBleAttribute*)&hidControlPoint_CharacteristicValueAttribute;
    }
};


static ClxBleGattDatabase* initHumanInterfaceDeviceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxHumanInterfaceDeviceGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, sizeof(ClxHumanInterfaceDeviceGattServiceDatabase))) ClxHumanInterfaceDeviceGattServiceDatabase;
#else
    ClxHumanInterfaceDeviceGattServiceDatabase* ret = new ClxHumanInterfaceDeviceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Protocol Mode : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->protocolMode_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->protocolMode_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_VALUE_TYPE, (u1*)&ret->protocolMode_Storage, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_SIZE, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_PERMISSIONS, NULL, NULL);
        }
        /* </Value> */
    }

    /* Report : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->report_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->report_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_VALUE_TYPE, (u1*)&ret->report_Storage, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_SIZE, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_PERMISSIONS, NULL, NULL);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->report_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Report Map : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->reportMap_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->reportMap_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_VALUE_TYPE, (u1*)&ret->reportMap_Storage, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_SIZE, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_PERMISSIONS, NULL, NULL);
        }
        /* </Value> */
    }

    /* Boot Keyboard Input Report : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->bootKeyboardInputReport_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->bootKeyboardInputReport_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_VALUE_TYPE, (u1*)&ret->bootKeyboardInputReport_Storage, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_SIZE, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_PERMISSIONS, NULL, NULL);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->bootKeyboardInputReport_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Boot Keyboard Output Report : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->bootKeyboardOutputReport_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->bootKeyboardOutputReport_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_VALUE_TYPE, (u1*)&ret->bootKeyboardOutputReport_Storage, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_SIZE, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_PERMISSIONS, NULL, NULL);
        }
        /* </Value> */
    }

    /* HID Information : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->hidInformation_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->hidInformation_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_VALUE_TYPE, (u1*)&ret->hidInformation_Storage, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_SIZE, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_PERMISSIONS, NULL, NULL);
        }
        /* </Value> */
    }

    /* HID Control Point : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->hidControlPoint_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->hidControlPoint_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_VALUE_TYPE, (u1*)&ret->hidControlPoint_Storage, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_SIZE, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_PERMISSIONS, NULL, NULL);
        }
        /* </Value> */
    }

    return ret;
}

static void destroyHumanInterfaceDeviceGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxHumanInterfaceDeviceGattServiceDatabase*>(database);
}

extern "C"
{

    static ClxBleGattServiceInterface clxHumanInterfaceDeviceGattServiceInterface = 
    {
        initHumanInterfaceDeviceGattServiceDatabase,
        destroyHumanInterfaceDeviceGattServiceDatabase
    };

    const ClxBleGattServiceInterface* clxGetHumanInterfaceDeviceGattServiceInterface()
    {
        return &clxHumanInterfaceDeviceGattServiceInterface;
    }

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
    const s1* clxGetHumanInterfaceDeviceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_HANDLE_INDEX : return CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE;
            case CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_HANDLE_INDEX : return CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT;
            case CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_HANDLE_INDEX : return CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP;
            case CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_HANDLE_INDEX : return CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT;
            case CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_HANDLE_INDEX : return CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT;
            case CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_HANDLE_INDEX : return CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION;
            case CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT_HANDLE_INDEX : return CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_CONTROL_POINT;
            default : return NULL;
        }
    }
#endif // CLX_BLE_GATT_SERVICE_VERBOSE
}
#endif /* defined(CLX_BLE_HID) */

