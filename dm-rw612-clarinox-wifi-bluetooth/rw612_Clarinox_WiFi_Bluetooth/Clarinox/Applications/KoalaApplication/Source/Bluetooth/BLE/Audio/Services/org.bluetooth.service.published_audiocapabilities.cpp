/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.published_audiocapabilities.cpp
* Description         Implements the GATT service Published Audio Capabilities
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
#include "org.bluetooth.service.published_audiocapabilities.h"

#include <new>

/* GATT Service Definition for "Published Audio Capabilities" with the UUID "1833" : */

class ClxPublishedAudioCapabilitiesGattServiceDatabase : public ClxBleGattDatabase
{
public:
    ClxBlePrimaryServiceAttribute                           primaryService;

    /* Characteristic : Sink PAC */
    ClxBleCharacteristicDeclarationAttribute                sinkPac_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      sinkPac_CharacteristicValueAttribute;
    u4                                                      sinkPac_Storage[(CLX_GATT_PACS_CHARACTERISTIC_PAC_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        sinkPac_CharacteristicClientConfigurationAttribute;

    /* Characteristic : Sink Audio Location */
    ClxBleCharacteristicDeclarationAttribute                sinkAudioLocation_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      sinkAudioLocation_CharacteristicValueAttribute;
    u4                                                      sinkAudioLocation_Storage[(CLX_GATT_PACS_CHARACTERISTIC_AUDIO_LOCATION_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        sinkAudioLocation_CharacteristicClientConfigurationAttribute;

    /* Characteristic : Source PAC */
    ClxBleCharacteristicDeclarationAttribute                sourcePac_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      sourcePac_CharacteristicValueAttribute;
    u4                                                      sourcePac_Storage[(CLX_GATT_PACS_CHARACTERISTIC_PAC_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        sourcePac_CharacteristicClientConfigurationAttribute;

    /* Characteristic : Source Audio Location */
    ClxBleCharacteristicDeclarationAttribute                sourceAudioLocation_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      sourceAudioLocation_CharacteristicValueAttribute;
    u4                                                      sourceAudioLocation_Storage[(CLX_GATT_PACS_CHARACTERISTIC_AUDIO_LOCATION_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        sourceAudioLocation_CharacteristicClientConfigurationAttribute;

    /* Characteristic : Available Audio Contexts */
    ClxBleCharacteristicDeclarationAttribute                availableAudioContexts_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      availableAudioContexts_CharacteristicValueAttribute;
    u4                                                      availableAudioContexts_Storage[(CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        availableAudioContexts_CharacteristicClientConfigurationAttribute;

    /* Characteristic : Supported Audio Contexts */
    ClxBleCharacteristicDeclarationAttribute                supportedAudioContexts_CharacteristicDeclarationAttribute;
    ClxBleCharacteristicValueAttribute                      supportedAudioContexts_CharacteristicValueAttribute;
    u4                                                      supportedAudioContexts_Storage[(CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_SIZE + 3)/4];
    ClxBleCharacteristicClientConfigurationAttribute        supportedAudioContexts_CharacteristicClientConfigurationAttribute;

    ClxBleAttribute*                                        list[19];

public:
    ClxPublishedAudioCapabilitiesGattServiceDatabase()
    {
        ClxBleGattDatabase::attrList = list;
        ClxBleGattDatabase::numberOfAttributes = sizeof(list)/sizeof(ClxBleAttribute*);

        list[0] = (ClxBleAttribute*)&primaryService;
        list[1] = (ClxBleAttribute*)&sinkPac_CharacteristicDeclarationAttribute;
        list[2] = (ClxBleAttribute*)&sinkPac_CharacteristicValueAttribute;
        list[3] = (ClxBleAttribute*)&sinkPac_CharacteristicClientConfigurationAttribute;
        list[4] = (ClxBleAttribute*)&sinkAudioLocation_CharacteristicDeclarationAttribute;
        list[5] = (ClxBleAttribute*)&sinkAudioLocation_CharacteristicValueAttribute;
        list[6] = (ClxBleAttribute*)&sinkAudioLocation_CharacteristicClientConfigurationAttribute;
        list[7] = (ClxBleAttribute*)&sourcePac_CharacteristicDeclarationAttribute;
        list[8] = (ClxBleAttribute*)&sourcePac_CharacteristicValueAttribute;
        list[9] = (ClxBleAttribute*)&sourcePac_CharacteristicClientConfigurationAttribute;
        list[10] = (ClxBleAttribute*)&sourceAudioLocation_CharacteristicDeclarationAttribute;
        list[11] = (ClxBleAttribute*)&sourceAudioLocation_CharacteristicValueAttribute;
        list[12] = (ClxBleAttribute*)&sourceAudioLocation_CharacteristicClientConfigurationAttribute;
        list[13] = (ClxBleAttribute*)&availableAudioContexts_CharacteristicDeclarationAttribute;
        list[14] = (ClxBleAttribute*)&availableAudioContexts_CharacteristicValueAttribute;
        list[15] = (ClxBleAttribute*)&availableAudioContexts_CharacteristicClientConfigurationAttribute;
        list[16] = (ClxBleAttribute*)&supportedAudioContexts_CharacteristicDeclarationAttribute;
        list[17] = (ClxBleAttribute*)&supportedAudioContexts_CharacteristicValueAttribute;
        list[18] = (ClxBleAttribute*)&supportedAudioContexts_CharacteristicClientConfigurationAttribute;
    }
};


static ClxBleGattDatabase* initPublishedAudioCapabilitiesGattServiceDatabase(const ClxConfigList*)
{
#if defined(USE_CLARINOX_POOLSET)
    ClxPublishedAudioCapabilitiesGattServiceDatabase* ret = new (clxPoolsetAlloc(0, 0, sizeof(ClxPublishedAudioCapabilitiesGattServiceDatabase))) ClxPublishedAudioCapabilitiesGattServiceDatabase;
#else
    ClxPublishedAudioCapabilitiesGattServiceDatabase* ret = new ClxPublishedAudioCapabilitiesGattServiceDatabase;
#endif

    ClxGattUuid uuid;

    /* Primary Service: */
    {
        clxInitGattUuid2(&uuid, CLX_GATT_PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID);
        clxInitBlePrimaryServiceAttribute(&ret->primaryService, &uuid, (sizeof(ret->list) / sizeof(ClxBleAttribute*) - 1));
    }

    /* Sink PAC : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->sinkPac_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_UUID);
            clxInitBleCharacteristicValueAttribute ( 
                         &ret->sinkPac_CharacteristicValueAttribute,
                         &uuid,
                         CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_VALUE_TYPE,
                         (u1*)&ret->sinkPac_Storage,
                         CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_SIZE,
                         CLX_GATT_PACS_CHARACTERISTIC_SINK_PAC_PROPERTY,
                         clxEncodeOrgBluetoothCharacteristicSinkOrSourcePac,
                         clxDecodeOrgBluetoothCharacteristicSinkOrSourcePac );
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->sinkPac_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Sink Audio Location : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->sinkAudioLocation_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_UUID);
            clxInitBleCharacteristicValueAttribute(
                            &ret->sinkAudioLocation_CharacteristicValueAttribute,
                            &uuid,
                            CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_VALUE_TYPE,
                            (u1*)&ret->sinkAudioLocation_Storage,
                            CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_SIZE,
                            CLX_GATT_PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_PROPERTY,
                            clxEncodeOrgBluetoothCharacteristicSinkAudioLocation,
                            clxDecodeOrgBluetoothCharacteristicSinkAudioLocation );
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->sinkAudioLocation_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Source PAC : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SOURCE_PAC_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->sourcePac_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SOURCE_PAC_UUID);
            clxInitBleCharacteristicValueAttribute(
                            &ret->sourcePac_CharacteristicValueAttribute,
                            &uuid,
                            CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_VALUE_TYPE,
                            (u1*)&ret->sourcePac_Storage,
                            CLX_GATT_PACS_CHARACTERISTIC_PAC_SIZE,
                            CLX_GATT_PACS_CHARACTERISTIC_SOURCE_PAC_PROPERTY,
                            clxEncodeOrgBluetoothCharacteristicSinkOrSourcePac,
                            clxDecodeOrgBluetoothCharacteristicSinkOrSourcePac );
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->sourcePac_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Source Audio Location : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->sourceAudioLocation_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */
        
        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_UUID);
            clxInitBleCharacteristicValueAttribute(
                        &ret->sourceAudioLocation_CharacteristicValueAttribute,
                        &uuid,
                        CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_VALUE_TYPE,
                        (u1*)&ret->sourceAudioLocation_Storage,
                        CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_SIZE,
                        CLX_GATT_PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_PROPERTY,
                        clxEncodeOrgBluetoothCharacteristicSourceAudioLocation,
                        clxDecodeOrgBluetoothCharacteristicSourceAudioLocation );
        }
        /* </Value> */
        
        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->sourceAudioLocation_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Available Audio Contexts : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->availableAudioContexts_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_UUID);
            clxInitBleCharacteristicValueAttribute(
                        &ret->availableAudioContexts_CharacteristicValueAttribute,
                        &uuid,
                        CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_VALUE_TYPE,
                        (u1*)&ret->availableAudioContexts_Storage,
                        CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_SIZE,
                        CLX_GATT_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_PROPERTY,
                        clxEncodeOrgBluetoothCharacteristicAvailableAudioContexts,
                        clxDecodeOrgBluetoothCharacteristicAvailableAudioContexts );
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->availableAudioContexts_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    /* Supported Audio Contexts : */
    {
        /* <Declaration> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_UUID);
            clxInitBleCharacteristicDeclarationAttribute(&ret->supportedAudioContexts_CharacteristicDeclarationAttribute, &uuid);
        }
        /* </Declaration> */

        /* <Value> */
        {
            clxInitGattUuid2(&uuid, CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_UUID);
            clxInitBleCharacteristicValueAttribute(
                        &ret->supportedAudioContexts_CharacteristicValueAttribute,
                        &uuid,
                        CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_VALUE_TYPE,
                        (u1*)&ret->supportedAudioContexts_Storage,
                        CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_SIZE,
                        CLX_GATT_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_PROPERTY,
                        clxEncodeOrgBluetoothCharacteristicSupportedAudioContexts,
                        clxDecodeOrgBluetoothCharacteristicSupportedAudioContexts );
        }
        /* </Value> */

        /* <ClientConfiguration> */
        clxInitBleCharacteristicClientConfigurationAttribute(&ret->supportedAudioContexts_CharacteristicClientConfigurationAttribute);
        /* </ClientConfiguration> */
    }

    return ret;
}

static void destroyPublishedAudioCapabilitiesGattServiceDatabase(ClxBleGattDatabase* database)
{
    delete static_cast<ClxPublishedAudioCapabilitiesGattServiceDatabase*>(database);
}

void publishedAudioCapabilitiesBaseHandleUpdated (u2 baseHandle)
{
    (void)baseHandle;
}

extern "C"
{

    static ClxBleGattServiceInterface clxPublishedAudioCapabilitiesGattServiceInterface =
    {
        initPublishedAudioCapabilitiesGattServiceDatabase,
        destroyPublishedAudioCapabilitiesGattServiceDatabase,
        publishedAudioCapabilitiesBaseHandleUpdated
    };

    const ClxBleGattServiceInterface* clxGetPublishedAudioCapabilitiesGattServiceInterface( void )
    {
        return &clxPublishedAudioCapabilitiesGattServiceInterface;
    }

    const s1* clxGetPublishedAudioCapabilitiesGattServiceCharacteristicName(u2 handleIndex)
    {
        switch (handleIndex)
        {
            case CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC_HANDLE_INDEX : return CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_PAC;
            case CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION_HANDLE_INDEX : return CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SINK_AUDIO_LOCATION;
            case CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC_HANDLE_INDEX : return CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_PAC;
            case CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_HANDLE_INDEX : return CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SOURCE_AUDIO_LOCATION;
            case CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_HANDLE_INDEX : return CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS;
            case CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_HANDLE_INDEX : return CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS;
            default : return NULL;
        }
    }
}

#endif /* CLX_BLE_ISOCHRONOUS */

