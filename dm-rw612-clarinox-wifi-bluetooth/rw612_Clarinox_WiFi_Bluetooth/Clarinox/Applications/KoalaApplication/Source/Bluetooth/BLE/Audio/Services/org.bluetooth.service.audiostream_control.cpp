/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.audiostream_control.cpp
* Description         Implements the GATT service Audio Stream Control
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2024 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "BleAudioCommon.h"
#include "org.bluetooth.service.audiostream_control.h"
#include "org.bluetooth.service.audio_input_control_service.h"
#include <new>

#define INCLUDE_AICS_IN_ASCS


/* GATT Service Definition for "Audio Stream Control" with the UUID "184E" : */

class ClxAudioStreamControlGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;
    
    /* Characteristic : Sink ASE Instance One */
    ClxBleCharacteristicDeclarationAttribute                sinkAseInstanceOne_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      sinkAseInstanceOne_CharacteristicValueAttribute;
    u4                                                      sinkAseInstanceOne_Storage[(CLX_GATT_ASCS_CHARACTERISTIC_ASE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        sinkAseInstanceOne_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Sink ASE Instance Two */
    ClxBleCharacteristicDeclarationAttribute                sinkAseInstanceTwo_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      sinkAseInstanceTwo_CharacteristicValueAttribute;
    u4                                                      sinkAseInstanceTwo_Storage[(CLX_GATT_ASCS_CHARACTERISTIC_ASE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        sinkAseInstanceTwo_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Source ASE */
    ClxBleCharacteristicDeclarationAttribute                sourceAse_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      sourceAse_CharacteristicValueAttribute;
    u4                                                      sourceAse_Storage[(CLX_GATT_ASCS_CHARACTERISTIC_ASE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        sourceAse_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : ASE Control Point */
    ClxBleCharacteristicDeclarationAttribute                aseControlPoint_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      aseControlPoint_CharacteristicValueAttribute;
    u4                                                      aseControlPoint_Storage[(CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        aseControlPoint_CharacteristicClientConfigurationAttribute;

#if defined(INCLUDE_AICS_IN_ASCS)
    /* Secondary service */
    ClxBleSecondaryServiceAttribute                         secondaryService;
    
    /* Include service */
    ClxBleCharacteristicIncludeDefinitionAttribute          includeService;

    /* Characteristic : Audio Input State */
    ClxBleCharacteristicDeclarationAttribute                audioInputState_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      audioInputState_CharacteristicValueAttribute;
    u4                                                      audioInputState_Storage[(CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        audioInputState_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Gain Settings */
    ClxBleCharacteristicDeclarationAttribute                gainSettings_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      gainSettings_CharacteristicValueAttribute;
    u4                                                      gainSettings_Storage[(CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_SIZE + 3)/4];
    
    /* Characteristic : Audio Input Type */
    ClxBleCharacteristicDeclarationAttribute                audioInputType_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      audioInputType_CharacteristicValueAttribute;
    u4                                                      audioInputType_Storage[(CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_SIZE + 3)/4];
    
    /* Characteristic : Audio Input Status */
    ClxBleCharacteristicDeclarationAttribute                audioInputStatus_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      audioInputStatus_CharacteristicValueAttribute;
    u4                                                      audioInputStatus_Storage[(CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        audioInputStatus_CharacteristicClientConfigurationAttribute;
    
    /* Characteristic : Audio Input Control Point */
    ClxBleCharacteristicDeclarationAttribute                audioInputControlPoint_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      audioInputControlPoint_CharacteristicValueAttribute;
    u4                                                      audioInputControlPoint_Storage[(CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_SIZE + 3)/4];
    
    /* Characteristic : Audio Input Description */
    ClxBleCharacteristicDeclarationAttribute                audioInputDescription_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      audioInputDescription_CharacteristicValueAttribute;
    u4                                                      audioInputDescription_Storage[(CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        audioInputDescription_CharacteristicClientConfigurationAttribute;
    
    ClxBleAttribute*                                        list[30];
#else
    ClxBleAttribute*                                        list[13];
#endif /* defined(INCLUDE_AICS_IN_ASCS) */

public:
    ClxAudioStreamControlGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&sinkAseInstanceOne_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&sinkAseInstanceOne_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&sinkAseInstanceOne_CharacteristicClientConfigurationAttribute;
        list[4] = (ClxBleAttribute*)&sinkAseInstanceTwo_CharacteristicDeclarationAttribute;
        list[5] = (ClxBleAttribute*)&sinkAseInstanceTwo_CharacteristicValueAttribute;
        list[6] = (ClxBleAttribute*)&sinkAseInstanceTwo_CharacteristicClientConfigurationAttribute;
        list[7] = (ClxBleAttribute*)&sourceAse_CharacteristicDeclarationAttribute;
        list[8] = (ClxBleAttribute*)&sourceAse_CharacteristicValueAttribute;
        list[9] = (ClxBleAttribute*)&sourceAse_CharacteristicClientConfigurationAttribute;
        list[10] = (ClxBleAttribute*)&aseControlPoint_CharacteristicDeclarationAttribute;
        list[11] = (ClxBleAttribute*)&aseControlPoint_CharacteristicValueAttribute;
        list[12] = (ClxBleAttribute*)&aseControlPoint_CharacteristicClientConfigurationAttribute;

#if defined(INCLUDE_AICS_IN_ASCS)
        list[13] = (ClxBleAttribute*)&secondaryService;
        list[14] = (ClxBleAttribute*)&includeService;
        list[15] = (ClxBleAttribute*)&audioInputState_CharacteristicDeclarationAttribute;
        list[16] = (ClxBleAttribute*)&audioInputState_CharacteristicValueAttribute;
        list[17] = (ClxBleAttribute*)&audioInputState_CharacteristicClientConfigurationAttribute;
        list[18] = (ClxBleAttribute*)&gainSettings_CharacteristicDeclarationAttribute;
        list[19] = (ClxBleAttribute*)&gainSettings_CharacteristicValueAttribute;
        list[20] = (ClxBleAttribute*)&audioInputType_CharacteristicDeclarationAttribute;
        list[21] = (ClxBleAttribute*)&audioInputType_CharacteristicValueAttribute;
        list[22] = (ClxBleAttribute*)&audioInputStatus_CharacteristicDeclarationAttribute;
        list[23] = (ClxBleAttribute*)&audioInputStatus_CharacteristicValueAttribute;
        list[24] = (ClxBleAttribute*)&audioInputStatus_CharacteristicClientConfigurationAttribute;
        list[25] = (ClxBleAttribute*)&audioInputControlPoint_CharacteristicDeclarationAttribute;
        list[26] = (ClxBleAttribute*)&audioInputControlPoint_CharacteristicValueAttribute;
        list[27] = (ClxBleAttribute*)&audioInputDescription_CharacteristicDeclarationAttribute;
        list[28] = (ClxBleAttribute*)&audioInputDescription_CharacteristicValueAttribute;
        list[29] = (ClxBleAttribute*)&audioInputDescription_CharacteristicClientConfigurationAttribute;
#endif /* defined(INCLUDE_AICS_IN_ASCS) */
    }
};


static ClxBleGattDatabase* initAudioStreamControlGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxAudioStreamControlGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, sizeof(ClxAudioStreamControlGattServiceDatabase))) ClxAudioStreamControlGattServiceDatabase;
#else
    ClxAudioStreamControlGattServiceDatabase* ret = new ClxAudioStreamControlGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_AUDIO_STREAM_CONTROL_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Sink ASE First Instance : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->sinkAseInstanceOne_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID);
            clxInitBleCharacteristicValueAttribute( &ret->sinkAseInstanceOne_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_VALUE_TYPE, (u1*)&ret->sinkAseInstanceOne_Storage, CLX_GATT_ASCS_CHARACTERISTIC_ASE_SIZE, CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_PROPERTY, clxEncodeOrgBluetoothCharacteristicSourceOrSinkAse, clxDecodeOrgBluetoothCharacteristicSourceOrSinkAse );
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->sinkAseInstanceOne_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Sink ASE Second Instance : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->sinkAseInstanceTwo_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_UUID);
            clxInitBleCharacteristicValueAttribute( &ret->sinkAseInstanceTwo_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_VALUE_TYPE, (u1*)&ret->sinkAseInstanceTwo_Storage, CLX_GATT_ASCS_CHARACTERISTIC_ASE_SIZE, CLX_GATT_ASCS_CHARACTERISTIC_SINK_ASE_PROPERTY, clxEncodeOrgBluetoothCharacteristicSourceOrSinkAse, clxDecodeOrgBluetoothCharacteristicSourceOrSinkAse );
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->sinkAseInstanceTwo_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Source ASE : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->sourceAse_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_UUID);
            clxInitBleCharacteristicValueAttribute( &ret->sourceAse_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_VALUE_TYPE, (u1*)&ret->sourceAse_Storage, CLX_GATT_ASCS_CHARACTERISTIC_ASE_SIZE, CLX_GATT_ASCS_CHARACTERISTIC_SOURCE_ASE_PROPERTY, clxEncodeOrgBluetoothCharacteristicSourceOrSinkAse, clxDecodeOrgBluetoothCharacteristicSourceOrSinkAse );
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->sourceAse_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* ASE Control Point : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);
            
            clxInitBleCharacteristicDeclarationAttribute(&ret->aseControlPoint_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->aseControlPoint_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_VALUE_TYPE, (u1*)&ret->aseControlPoint_Storage, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_SIZE, CLX_GATT_ASCS_CHARACTERISTIC_ASE_CONTROL_POINT_PROPERTY, clxEncodeOrgBluetoothCharacteristicAseControlPoint, clxDecodeOrgBluetoothCharacteristicAseControlPoint);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->aseControlPoint_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

#if defined(INCLUDE_AICS_IN_ASCS)
    /* Secondary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_UUID);
        clxInitBleSecondaryServiceAttribute(&ret->secondaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Include Volume Offset Control Service */
    {
        clxInitBleCharacteristicIncludeDefinitionAttribute(&ret->includeService, 13, 29, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_UUID);
    }

    /* Audio Input State : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->audioInputState_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->audioInputState_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_VALUE_TYPE, (u1*)&ret->audioInputState_Storage, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_SIZE, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicAudioInputState, clxDecodeOrgBluetoothCharacteristicAudioInputState);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->audioInputState_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Gain Settings : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->gainSettings_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->gainSettings_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_VALUE_TYPE, (u1*)&ret->gainSettings_Storage, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_SIZE, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_GAIN_SETTINGS_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicGainSettings, clxDecodeOrgBluetoothCharacteristicGainSettings);
        }
        /* </Value> */
    }

    /* Audio Input Type : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->audioInputType_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->audioInputType_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_VALUE_TYPE, (u1*)&ret->audioInputType_Storage, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_SIZE, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_TYPE_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicAudioInputType, clxDecodeOrgBluetoothCharacteristicAudioInputType);
        }
        /* </Value> */
    }

    /* Audio Input Status : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->audioInputStatus_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->audioInputStatus_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_VALUE_TYPE, (u1*)&ret->audioInputStatus_Storage, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_SIZE, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_STATUS_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicAudioInputStatus, clxDecodeOrgBluetoothCharacteristicAudioInputStatus);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->audioInputStatus_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Audio Input Control Point : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->audioInputControlPoint_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->audioInputControlPoint_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_VALUE_TYPE, (u1*)&ret->audioInputControlPoint_Storage, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_SIZE, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_CONTROL_POINT_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicAudioInputControlPoint, clxDecodeOrgBluetoothCharacteristicAudioInputControlPoint);
        }
        /* </Value> */
    }

    /* Audio Input Description : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->audioInputDescription_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_UUID);
            clxInitBleCharacteristicValueAttribute(&ret->audioInputDescription_CharacteristicValueAttribute, &uuid, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_VALUE_TYPE, (u1*)&ret->audioInputDescription_Storage, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_SIZE, CLX_GATT_SERVICE_AUDIO_INPUT_CONTROL_SERVICE_CHARACTERISTIC_AUDIO_INPUT_DESCRIPTION_PERMISSIONS, clxEncodeOrgBluetoothCharacteristicAudioInputDescription, clxDecodeOrgBluetoothCharacteristicAudioInputDescription);
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->audioInputDescription_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }
#endif /* defined(INCLUDE_AICS_IN_ASCS) */

    return ret;
}

static void destroyAudioStreamControlGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxAudioStreamControlGattServiceDatabase*>(database);
}

void audioStreamControlBaseHandleUpdated (u2 baseHandle)
{
    (void)baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxAudioStreamControlGattServiceInterface =
    {
        initAudioStreamControlGattServiceDatabase,
        destroyAudioStreamControlGattServiceDatabase,
        audioStreamControlBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetAudioStreamControlGattServiceInterface()
    {
        return &clxAudioStreamControlGattServiceInterface;
    }
    
    const s1* clxGetAudioStreamControlGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE_HANDLE_INDEX : return CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SINK_ASE;
            case CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_HANDLE_INDEX : return CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE;
            case CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT_HANDLE_INDEX : return CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_ASE_CONTROL_POINT;
            default : return NULL;
        }
    }
}

#endif /* CLX_BLE_ISOCHRONOUS */

