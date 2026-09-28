/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.alert_notification.cpp
* Description         Implements the GATT service Alert Notification Service
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


/* GATT Service Definition for "Alert Notification Service" with the UUID "1811" : */

class ClxAlertNotificationServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;

    /* Characteristic : Supported New Alert Category */
    ClxBleCharacteristicDeclarationAttribute                supportedNewAlertCategory_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      supportedNewAlertCategory_CharacteristicValueAttribute;
    u4                                                      supportedNewAlertCategory_Storage[(CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_SIZE + 3)/4];

    /* Characteristic : New Alert */
    ClxBleCharacteristicDeclarationAttribute                newAlert_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      newAlert_CharacteristicValueAttribute;
    u4                                                      newAlert_Storage[(CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        newAlert_CharacteristicClientConfigurationAttribute;

    /* Characteristic : Supported Unread Alert Category */
    ClxBleCharacteristicDeclarationAttribute                supportedUnreadAlertCategory_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      supportedUnreadAlertCategory_CharacteristicValueAttribute;
    u4                                                      supportedUnreadAlertCategory_Storage[(CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_SIZE + 3)/4];

    /* Characteristic : Unread Alert Status */
    ClxBleCharacteristicDeclarationAttribute                unreadAlertStatus_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      unreadAlertStatus_CharacteristicValueAttribute;
    u4                                                      unreadAlertStatus_Storage[(CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        unreadAlertStatus_CharacteristicClientConfigurationAttribute;

    /* Characteristic : Alert Notification Control Point */
    ClxBleCharacteristicDeclarationAttribute                alertNotificationControlPoint_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      alertNotificationControlPoint_CharacteristicValueAttribute;
    u4                                                      alertNotificationControlPoint_Storage[(CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_SIZE + 3)/4];

    ClxBleAttribute*                                        list[13];

public:
    ClxAlertNotificationServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&supportedNewAlertCategory_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&supportedNewAlertCategory_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&newAlert_CharacteristicDeclarationAttribute;
        list[4] = (ClxBleAttribute*)&newAlert_CharacteristicValueAttribute;
        list[5] = (ClxBleAttribute*)&newAlert_CharacteristicClientConfigurationAttribute;
        list[6] = (ClxBleAttribute*)&supportedUnreadAlertCategory_CharacteristicDeclarationAttribute;
        list[7] = (ClxBleAttribute*)&supportedUnreadAlertCategory_CharacteristicValueAttribute;
        list[8] = (ClxBleAttribute*)&unreadAlertStatus_CharacteristicDeclarationAttribute;
        list[9] = (ClxBleAttribute*)&unreadAlertStatus_CharacteristicValueAttribute;
        list[10] = (ClxBleAttribute*)&unreadAlertStatus_CharacteristicClientConfigurationAttribute;
        list[11] = (ClxBleAttribute*)&alertNotificationControlPoint_CharacteristicDeclarationAttribute;
        list[12] = (ClxBleAttribute*)&alertNotificationControlPoint_CharacteristicValueAttribute;
    }
};


static ClxBleGattDatabase* initAlertNotificationServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxAlertNotificationServiceGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, 0, sizeof(ClxAlertNotificationServiceGattServiceDatabase))) ClxAlertNotificationServiceGattServiceDatabase;
#else
    ClxAlertNotificationServiceGattServiceDatabase* ret = new ClxAlertNotificationServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Supported New Alert Category : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->supportedNewAlertCategory_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->supportedNewAlertCategory_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_VALUE_TYPE, (u1*)&ret->supportedNewAlertCategory_Storage, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_SIZE, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicSupportedNewAlertCategory, clxDecodeOrgBluetoothCharacteristicSupportedNewAlertCategory);
        }
        /* </Value> */
    }

    /* New Alert : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->newAlert_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->newAlert_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_VALUE_TYPE, (u1*)&ret->newAlert_Storage, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_SIZE, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicNewAlert, clxDecodeOrgBluetoothCharacteristicNewAlert);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->newAlert_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Supported Unread Alert Category : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->supportedUnreadAlertCategory_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->supportedUnreadAlertCategory_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_VALUE_TYPE, (u1*)&ret->supportedUnreadAlertCategory_Storage, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_SIZE, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicSupportedUnreadAlertCategory, clxDecodeOrgBluetoothCharacteristicSupportedUnreadAlertCategory);
        }
        /* </Value> */
    }

    /* Unread Alert Status : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->unreadAlertStatus_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->unreadAlertStatus_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_VALUE_TYPE, (u1*)&ret->unreadAlertStatus_Storage, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_SIZE, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicUnreadAlertStatus, clxDecodeOrgBluetoothCharacteristicUnreadAlertStatus);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->unreadAlertStatus_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Alert Notification Control Point : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->alertNotificationControlPoint_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->alertNotificationControlPoint_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_VALUE_TYPE, (u1*)&ret->alertNotificationControlPoint_Storage, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_SIZE, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicAlertNotificationControlPoint, clxDecodeOrgBluetoothCharacteristicAlertNotificationControlPoint);
        }
        /* </Value> */
    }

    return ret;
}

static void destroyAlertNotificationServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxAlertNotificationServiceGattServiceDatabase*>(database);
}

static void alertNotificationServiceBaseHandleUpdated(u2 baseHandle)
{
    clxBleGattServiceList[GattService_AlertNotificationIndex].handleBase = baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxAlertNotificationServiceGattServiceInterface = 
    {
        initAlertNotificationServiceGattServiceDatabase,
        destroyAlertNotificationServiceGattServiceDatabase,
        alertNotificationServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetAlertNotificationServiceGattServiceInterface()
    {
        return &clxAlertNotificationServiceGattServiceInterface;
    }

    const s1* clxGetAlertNotificationServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_HANDLE_INDEX : return CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY;
            case CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_HANDLE_INDEX : return CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT;
            case CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_HANDLE_INDEX : return CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY;
            case CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_HANDLE_INDEX : return CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS;
            case CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_HANDLE_INDEX : return CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT;
            default : return NULL;
        }
    }
}

