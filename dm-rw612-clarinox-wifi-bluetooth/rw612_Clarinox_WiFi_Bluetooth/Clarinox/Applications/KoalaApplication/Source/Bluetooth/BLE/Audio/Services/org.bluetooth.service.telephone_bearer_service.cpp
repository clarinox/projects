/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.telephone_bearer_service.cpp
* Description         Implements the GATT service Telephone Bearer Service
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
#include "org.bluetooth.service.telephone_bearer_service.h"
#include "org.bluetooth.service.media_control_service.h"
#include <new>


/* GATT Service Definition for "Telephone Bearer Service" with the UUID "184B" : */

class ClxTelephoneBearerServiceGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Bearer Provider Name */
    ClxBleCharacteristicDeclarationAttribute                bearerProviderName_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      bearerProviderName_CharacteristicValueAttribute;
    u4                                                      bearerProviderName_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        bearerProviderName_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Bearer UCI */
    ClxBleCharacteristicDeclarationAttribute                bearerUci_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      bearerUci_CharacteristicValueAttribute;
    u4                                                      bearerUci_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_SIZE + 3)/4];
    
    /* Characteristic : Bearer Technology */
    ClxBleCharacteristicDeclarationAttribute                bearerTechnology_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      bearerTechnology_CharacteristicValueAttribute;
    u4                                                      bearerTechnology_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        bearerTechnology_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Bearer URI Schemes Supported List */
    ClxBleCharacteristicDeclarationAttribute                bearerUriSchemesSupportedList_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      bearerUriSchemesSupportedList_CharacteristicValueAttribute;
    u4                                                      bearerUriSchemesSupportedList_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_SIZE + 3)/4];
    
    /* Characteristic : Bearer List Current Calls */
    ClxBleCharacteristicDeclarationAttribute                bearerListCurrentCalls_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      bearerListCurrentCalls_CharacteristicValueAttribute;
    u4                                                      bearerListCurrentCalls_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        bearerListCurrentCalls_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Content Control ID */
    ClxBleCharacteristicDeclarationAttribute                contentControlId_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      contentControlId_CharacteristicValueAttribute;
    u4                                                      contentControlId_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_SIZE + 3)/4];
    
    /* Characteristic : Status Flags */
    ClxBleCharacteristicDeclarationAttribute                statusFlags_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      statusFlags_CharacteristicValueAttribute;
    u4                                                      statusFlags_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        statusFlags_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Call State */
    ClxBleCharacteristicDeclarationAttribute                callState_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      callState_CharacteristicValueAttribute;
    u4                                                      callState_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        callState_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Call Control Point */
    ClxBleCharacteristicDeclarationAttribute                callControlPoint_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      callControlPoint_CharacteristicValueAttribute;
    u4                                                      callControlPoint_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        callControlPoint_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Call Control Point Optional Opcode */
    ClxBleCharacteristicDeclarationAttribute                callControlPointOptionalOpcode_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      callControlPointOptionalOpcode_CharacteristicValueAttribute;
    u4                                                      callControlPointOptionalOpcode_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_SIZE + 3)/4];
    
    /* Characteristic : Termination Reason */
    ClxBleCharacteristicDeclarationAttribute                terminationReason_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      terminationReason_CharacteristicValueAttribute;
    u4                                                      terminationReason_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        terminationReason_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Incoming Call */
    ClxBleCharacteristicDeclarationAttribute                incomingCall_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      incomingCall_CharacteristicValueAttribute;
    u4                                                      incomingCall_Storage[(CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        incomingCall_CharacteristicClientConfigurationAttribute;
    
    ClxBleAttribute*                                        list[33];

public:
    ClxTelephoneBearerServiceGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&bearerProviderName_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&bearerProviderName_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&bearerProviderName_CharacteristicClientConfigurationAttribute;
        list[4] = (ClxBleAttribute*)&bearerUci_CharacteristicDeclarationAttribute;
        list[5] = (ClxBleAttribute*)&bearerUci_CharacteristicValueAttribute;
        list[6] = (ClxBleAttribute*)&bearerTechnology_CharacteristicDeclarationAttribute;
        list[7] = (ClxBleAttribute*)&bearerTechnology_CharacteristicValueAttribute;
        list[8] = (ClxBleAttribute*)&bearerTechnology_CharacteristicClientConfigurationAttribute;
        list[9] = (ClxBleAttribute*)&bearerUriSchemesSupportedList_CharacteristicDeclarationAttribute;
        list[10] = (ClxBleAttribute*)&bearerUriSchemesSupportedList_CharacteristicValueAttribute;
        list[11] = (ClxBleAttribute*)&bearerListCurrentCalls_CharacteristicDeclarationAttribute;
        list[12] = (ClxBleAttribute*)&bearerListCurrentCalls_CharacteristicValueAttribute;
        list[13] = (ClxBleAttribute*)&bearerListCurrentCalls_CharacteristicClientConfigurationAttribute;
        list[14] = (ClxBleAttribute*)&contentControlId_CharacteristicDeclarationAttribute;
        list[15] = (ClxBleAttribute*)&contentControlId_CharacteristicValueAttribute;
        list[16] = (ClxBleAttribute*)&statusFlags_CharacteristicDeclarationAttribute;
        list[17] = (ClxBleAttribute*)&statusFlags_CharacteristicValueAttribute;
        list[18] = (ClxBleAttribute*)&statusFlags_CharacteristicClientConfigurationAttribute;
        list[19] = (ClxBleAttribute*)&callState_CharacteristicDeclarationAttribute;
        list[20] = (ClxBleAttribute*)&callState_CharacteristicValueAttribute;
        list[21] = (ClxBleAttribute*)&callState_CharacteristicClientConfigurationAttribute;
        list[22] = (ClxBleAttribute*)&callControlPoint_CharacteristicDeclarationAttribute;
        list[23] = (ClxBleAttribute*)&callControlPoint_CharacteristicValueAttribute;
        list[24] = (ClxBleAttribute*)&callControlPoint_CharacteristicClientConfigurationAttribute;
        list[25] = (ClxBleAttribute*)&callControlPointOptionalOpcode_CharacteristicDeclarationAttribute;
        list[26] = (ClxBleAttribute*)&callControlPointOptionalOpcode_CharacteristicValueAttribute;
        list[27] = (ClxBleAttribute*)&terminationReason_CharacteristicDeclarationAttribute;
        list[28] = (ClxBleAttribute*)&terminationReason_CharacteristicValueAttribute;
        list[29] = (ClxBleAttribute*)&terminationReason_CharacteristicClientConfigurationAttribute;
        list[30] = (ClxBleAttribute*)&incomingCall_CharacteristicDeclarationAttribute;
        list[31] = (ClxBleAttribute*)&incomingCall_CharacteristicValueAttribute;
        list[32] = (ClxBleAttribute*)&incomingCall_CharacteristicClientConfigurationAttribute;
    }
};


static ClxBleGattDatabase* initTelephoneBearerServiceGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxTelephoneBearerServiceGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, sizeof(ClxTelephoneBearerServiceGattServiceDatabase))) ClxTelephoneBearerServiceGattServiceDatabase;
#else
    ClxTelephoneBearerServiceGattServiceDatabase* ret = new ClxTelephoneBearerServiceGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Bearer Provider Name : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->bearerProviderName_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->bearerProviderName_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_VALUE_TYPE, (u1*)&ret->bearerProviderName_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicBearerProviderName, clxDecodeOrgBluetoothCharacteristicBearerProviderName);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->bearerProviderName_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Bearer UCI : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->bearerUci_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->bearerUci_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_VALUE_TYPE, (u1*)&ret->bearerUci_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicBearerUniformCallerIdentifier, clxDecodeOrgBluetoothCharacteristicBearerUniformCallerIdentifier);
        }
        /* </Value> */
    }

    /* Bearer Technology : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->bearerTechnology_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->bearerTechnology_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_VALUE_TYPE, (u1*)&ret->bearerTechnology_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicBearerTechnology, clxDecodeOrgBluetoothCharacteristicBearerTechnology);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->bearerTechnology_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Bearer URI Schemes Supported List : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->bearerUriSchemesSupportedList_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->bearerUriSchemesSupportedList_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_VALUE_TYPE, (u1*)&ret->bearerUriSchemesSupportedList_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicBearerUriSchemesSupportedList, clxDecodeOrgBluetoothCharacteristicBearerUriSchemesSupportedList);
        }
        /* </Value> */
    }

    /* Bearer List Current Calls : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->bearerListCurrentCalls_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->bearerListCurrentCalls_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_VALUE_TYPE, (u1*)&ret->bearerListCurrentCalls_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicBearerListCurrentCalls, clxDecodeOrgBluetoothCharacteristicBearerListCurrentCalls);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->bearerListCurrentCalls_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Content Control ID : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->contentControlId_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->contentControlId_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_VALUE_TYPE, (u1*)&ret->contentControlId_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicContentControlId, clxDecodeOrgBluetoothCharacteristicContentControlId);
        }
        /* </Value> */
    }

    /* Status Flags : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->statusFlags_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->statusFlags_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_VALUE_TYPE, (u1*)&ret->statusFlags_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicStatusFlags, clxDecodeOrgBluetoothCharacteristicStatusFlags);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->statusFlags_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Call State : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->callState_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->callState_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_VALUE_TYPE, (u1*)&ret->callState_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicCallState, clxDecodeOrgBluetoothCharacteristicCallState);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->callState_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Call Control Point : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->callControlPoint_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->callControlPoint_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_VALUE_TYPE, (u1*)&ret->callControlPoint_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicCallControlPoint, clxDecodeOrgBluetoothCharacteristicCallControlPoint);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->callControlPoint_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Call Control Point Optional Opcode : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->callControlPointOptionalOpcode_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->callControlPointOptionalOpcode_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_VALUE_TYPE, (u1*)&ret->callControlPointOptionalOpcode_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicCallControlPointOptionalOpcode, clxDecodeOrgBluetoothCharacteristicCallControlPointOptionalOpcode);
        }
        /* </Value> */
    }

    /* Termination Reason : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->terminationReason_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->terminationReason_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_VALUE_TYPE, (u1*)&ret->terminationReason_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicTerminationReason, clxDecodeOrgBluetoothCharacteristicTerminationReason);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->terminationReason_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Incoming Call : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->incomingCall_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->incomingCall_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_VALUE_TYPE, (u1*)&ret->incomingCall_Storage, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_SIZE, CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicIncomingCall, clxDecodeOrgBluetoothCharacteristicIncomingCall);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->incomingCall_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    return ret;
}

static void destroyTelephoneBearerServiceGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxTelephoneBearerServiceGattServiceDatabase*>(database);
}

void telephoneBearerServiceBaseHandleUpdated(u2 baseHandle)
{
}

extern "C"
{

    static ClxBleGattServiceInterface clxTelephoneBearerServiceGattServiceInterface =
    {
        initTelephoneBearerServiceGattServiceDatabase,
        destroyTelephoneBearerServiceGattServiceDatabase,
        telephoneBearerServiceBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetTelephoneBearerServiceGattServiceInterface()
    {
        return &clxTelephoneBearerServiceGattServiceInterface;
    }

    const s1* clxGetTelephoneBearerServiceGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_PROVIDER_NAME;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_UCI;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_TECHNOLOGY;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_URI_SCHEMES_SUPPORTED_LIST;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_BEARER_LIST_CURRENT_CALLS;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_STATUS_FLAGS;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_STATE;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_CALL_CONTROL_POINT_OPTIONAL_OPCODE;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_TERMINATION_REASON;
            case CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL_HANDLE_INDEX : return CLX_GATT_SERVICE_TELEPHONE_BEARER_SERVICE_CHARACTERISTIC_INCOMING_CALL;
            default : return NULL;
        }
    }
}
