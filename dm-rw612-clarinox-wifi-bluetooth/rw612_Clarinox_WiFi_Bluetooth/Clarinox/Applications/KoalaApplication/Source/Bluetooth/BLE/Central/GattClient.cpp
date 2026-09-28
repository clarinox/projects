/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                GattClient.cpp
* Description         This file provides GATT profile handle creation and
*                     deletion, GATT UI menu, and indication call back functions.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#include "ClxCommon.h"
#include "ClarinoxBlue.h"
#include "ClxTime.h"

#include "Gatt.Ble.Common.Api.h"
#include "Gap.Ble.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Server.Api.h"
#include "Gatt.Ble.Client.Api.h"
#include "GattClient.h"
#include "Ble.Bap.Api.h"
#include "BleAudio.Unicast.Client.Api.h"

//#include "BroadcastCommon.h"

/* Structure consisting of variables associated with GATT event from stack */
typedef struct ClxGattEventParametersStruct
{
    ClxGattEvent    gattEvent;              /* Object to received event details from remote GATT server                 */
    u1              gattEventBuffer[1024];  /* Buffer to received new characteristic details from remote GATT server    */
}ClxGattEventParameters;

/* Object associated with GATT event from stack */
ClxGattEventParameters gattEventDetails = {};

/**
Get the GATT service characteristic handle
*/
u2 GetValueHandle(ClxHandle gattClientHandle, u4 serviceUuid, u4 characteristicUuid)
{
    ClxResult ret = CLX_ERROR;

    ClxGattUuid serviceUuidValue = { };
    ClxGattUuid characteristicUuidValue = { };
    u2 valHandle;

    clxInitGattUuid2(&serviceUuidValue, (u2)serviceUuid);
    clxInitGattUuid2(&characteristicUuidValue, (u2)characteristicUuid);

    ret = clxGattClientGetValueHandle(gattClientHandle, &serviceUuidValue, &characteristicUuidValue, &valHandle, TRUE);
    if (CLX_SUCCESS != ret)
    {
        clxConsoleUIEngineText("\nclxGattClientGetValueHandle failed with error %s\n", clxGetErrorCodeText(ret));
    }

    return valHandle;
}

/*******************************************************************************************************************************
*                                                bleGattClientMessageHandler
*
* This call-back function is registered for the GAP and GATT profiles, 
* any events raised by GAP profile causes this call-back function executed with
* the associated event and parameters
*
* \param stack          - Local device stack handle.
* \param serviceHandle  - Profile/Service handle.
* \param messageID      - Indication id.
* \param params         - Void pointer to the indication parameters.
* \param errorCode      - Error code returned by stack.
*
* \return boolean       - TRUE If the call-back function handles indication or indication with *_COMPLETE.
*                         Otherwise, return FALSE
* \note                 - The API should be called in non blocking mode.
*
*******************************************************************************************************************************/
boolean bleGattClientMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    (void)stack;

    ClxError ret = CLX_ERROR;

    if (messageID == CLX_GATT_CLIENT_BIND_COMPLETE)
    {
        ClxGattClientBindComplete *arg = (ClxGattClientBindComplete*)params;
        
        ClxConsoleUIEngine::text("\nClient bind command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
        ClxConsoleUIEngine::text("(Negotiated MTU : %x)\n", *(arg->negotiatedMtu));
    }
    else if (messageID == CLX_GATT_CLIENT_GET_LIST_OF_SERVICES_COMPLETE)
    {
        ClxGattClientGetListOfServicesComplete *arg = (ClxGattClientGetListOfServicesComplete*)params;

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
        /**
        Holds the discovered service UUID value.
        */
        u2 serviceUuid = 0;
#endif

        ClxConsoleUIEngine::text("\nGet list of service completed with the result: %s\n", clxGetErrorCodeText(errorCode));
        ClxConsoleUIEngine::text("The number of services found: %u\n", (*arg->numberOfServices));

        /**
        Prints the discovered service details, if the number of services value is valid.
        */
        if ((*arg->numberOfServices) != 0)
        {
            for (u2 serviceCount = 0; serviceCount < (*arg->numberOfServices); serviceCount++)
            {
                /**
                Splits up the standard and custom services details.
                */
                if (arg->list[serviceCount].uuid.type == ClxGattUuidType_Uuid2)
                {
                    ClxConsoleUIEngine::text("\n%u: First Handle: %#x Last Handle: %#x Uuid: %#x Type: %#x", serviceCount,
                                                                            arg->list[serviceCount].firstHandle,
                                                                            arg->list[serviceCount].lastHandle,
                                                                            (arg->list[serviceCount].uuid.value[0]),
                                                                            arg->list[serviceCount].type);
                                                                            
#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
                    serviceUuid = (u2)(*arg->list[serviceCount].uuid.value);

                    ClxConsoleUIEngine::text(" Name: %s", getServiceName(serviceUuid));
#endif /* defined(CLX_BLE_GATT_SERVICE_VERBOSE) */
                }
                else
                {
                    ClxConsoleUIEngine::text("\n%u: First Handle: %#x Last Handle: %#x Uuid: %#x%x%x%x Type: %#x", serviceCount,
                                                                             arg->list[serviceCount].firstHandle,
                                                                             arg->list[serviceCount].lastHandle,
                                                                             (arg->list[serviceCount].uuid.value[0]),
                                                                             (arg->list[serviceCount].uuid.value[1]),
                                                                             (arg->list[serviceCount].uuid.value[2]),
                                                                             (arg->list[serviceCount].uuid.value[3]),
                                                                             arg->list[serviceCount].type);

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
                    serviceUuid = (u2)(*arg->list[serviceCount].uuid.value);

                    ClxConsoleUIEngine::text(" Name: %s", getServiceName(serviceUuid));
#endif /* defined(CLX_BLE_GATT_SERVICE_VERBOSE) */
                }
            }
            
            ClxConsoleUIEngine::text("\n");
        }
    }
    else if (messageID == CLX_GATT_CLIENT_DISCOVER_CHARACTERISTICS_COMPLETE)
    {
        ClxGattClientDiscoverCharacteristicsComplete *arg = (ClxGattClientDiscoverCharacteristicsComplete*)params;
        
        ClxConsoleUIEngine::text("\nDiscover characteristics completed with the result: %s\n", clxGetErrorCodeText(errorCode));
        ClxConsoleUIEngine::text("The number of characteristics found: %u\n", (*arg->numberOfCharacteristics));

        /**
        Prints the service characteristic details, if the number of characteristics value is valid.
        */
        if ((*arg->numberOfCharacteristics) != 0)
        {
            for (u2 characteristicsCount = 0; characteristicsCount < (*arg->numberOfCharacteristics); characteristicsCount++)
            {
                /**
                Splits up the standard and custom characteristics details.
                */
                if (arg->list[characteristicsCount].uuid.type == ClxGattUuidType_Uuid2)
                {
                    ClxConsoleUIEngine::text("\n%u: Dec Handle: %#x Value Handle: %#x Properties: %u End Handle: %#x Uuid: %#x",
                                             characteristicsCount,
                                             arg->list[characteristicsCount].declarationHandle,
                                             arg->list[characteristicsCount].valueHandle,
                                             arg->list[characteristicsCount].properties,
                                             arg->list[characteristicsCount].endHandle,
                                             arg->list[characteristicsCount].uuid.value[0]);
                }
                else
                {
                     ClxConsoleUIEngine::text("\n%u: Dec Handle: %#x Value Handle: %#x Properties: %u End Handle: %#x Uuid: %#x",
                                              characteristicsCount,
                                              arg->list[characteristicsCount].declarationHandle,
                                              arg->list[characteristicsCount].valueHandle,
                                              arg->list[characteristicsCount].properties,
                                              arg->list[characteristicsCount].endHandle,
                                              (arg->list[characteristicsCount].uuid.value[0]),
                                              (arg->list[characteristicsCount].uuid.value[1]),
                                              (arg->list[characteristicsCount].uuid.value[2]),
                                              (arg->list[characteristicsCount].uuid.value[3]));
                }
            }

            ClxConsoleUIEngine::text("\n");
        }
    }
    else if (messageID == CLX_GATT_CLIENT_DISCOVER_CHARACTERISTIC_DESCRIPTORS_COMPLETE)
    {
        ClxGattClientDiscoverCharacteristicDescriptorsComplete *arg = (ClxGattClientDiscoverCharacteristicDescriptorsComplete*)params;

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
        /**
        Holds the discovered descriptors UUID value.
        */
        u2 descriptorUuid = 0;
#endif

        ClxConsoleUIEngine::text("\nDiscover characteristic descriptor completed with the result: %s\n", clxGetErrorCodeText(errorCode));
        ClxConsoleUIEngine::text("The number of descriptors found: %u\n", (*arg->numberOfCharacteristicDescriptors));

        /**
        Prints the characteristic descriptor details, if the number of characteristic descriptor value is valid.
        */
        if ((*arg->numberOfCharacteristicDescriptors) != 0)
        {
            for (u2 descriptorCount = 0; descriptorCount < (*arg->numberOfCharacteristicDescriptors); descriptorCount++)
            {
                ClxConsoleUIEngine::text("\n%u: Handle: %#x Uuid: %#x", descriptorCount, arg->list[descriptorCount].handle,
                                                                           (arg->list[descriptorCount].uuid.value[0]));

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
                descriptorUuid = (u2)(*arg->list[descriptorCount].uuid.value);
                ClxConsoleUIEngine::text(" Name: %s", getDescriptorName(descriptorUuid));
#endif /* defined(CLX_BLE_GATT_SERVICE_VERBOSE) */
            }

            ClxConsoleUIEngine::text("\n");
        }
    }
    else if (messageID == CLX_GATT_CLIENT_READ_COMPLETE)
    {
        ClxGattClientReadComplete *arg = (ClxGattClientReadComplete*)params;

        if (errorCode == CLX_SUCCESS)
        {
            ClxConsoleUIEngine::text("\nReadLength: %u\n", (*arg->readLength));

            /**
            Prints the read characteristic value.
            */
            if ((*arg->readLength) != 0)
            {
                for (u4 i = 0; i < (*arg->readLength); i++)
                {
                    ClxConsoleUIEngine::text("%02X ", arg->buffer[i]);
                }
            }
        }
    }
    else if (messageID == CLX_GATT_CLIENT_WRITE_COMPLETE)
    {
        ClxConsoleUIEngine::text("\nClient write completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GATT_CLIENT_CONFIGURE_CHARACTERISTIC_COMPLETE)
    {
        ClxConsoleUIEngine::text("\nClient configure characteristic completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GATT_GET_PENDING_EVENT_COMPLETE)
    {
        ClxGattGetPendingEventComplete *arg = (ClxGattGetPendingEventComplete*)params;

        ClxConsoleUIEngine::text("\nGet Pending Event command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
        
        if (errorCode == CLX_SUCCESS)
        {
            ClxConsoleUIEngine::text("\nEventType : %x ", arg->event->eventType);
            ClxConsoleUIEngine::text("\nDataLength: %u", arg->event->dataLength);
            ClxConsoleUIEngine::text("\nCharacteristicValueHandle: %02x\nData: ", arg->event->characteristicValueHandle);
            
            for(u4 i = 0; i < arg->event->dataLength; i++)
            {
                ClxConsoleUIEngine::text("%02X ", arg->buffer[i]);
            }
            
            ClxConsoleUIEngine::text("\n");
        }
    }
    /**
    This indication is received when the characteristic value got modified/updated in remote GATT server. 
    The server informs client via notification or indication.
    */
    else if (messageID == CLX_GATT_CLIENT_EVENT_RECEIVED_INDICATION)
    {
        /**
        Get the details of the characteristic that was modified/updated in the server for which the notification or 
        indication is received
        */
        ret = clxGattGetPendingEvent(serviceHandle, &gattEventDetails.gattEvent, gattEventDetails.gattEventBuffer, sizeof(gattEventDetails.gattEventBuffer), TRUE);
        
        if (ret == CLX_SUCCESS)
        {
            if (ClxGattEventType_Notification == gattEventDetails.gattEvent.eventType)
            {
                ClxConsoleUIEngine::text("\nNotification received for characteristic value handle %02X\nData: ", gattEventDetails.gattEvent.characteristicValueHandle);
            }
            else if(ClxGattEventType_Indication == gattEventDetails.gattEvent.eventType)
            {
                ClxConsoleUIEngine::text("\nIndication received for characteristic value handle %02X\nData: ", gattEventDetails.gattEvent.characteristicValueHandle);
            }

            for(u4 i = 0; i < gattEventDetails.gattEvent.dataLength; i++)
            {
                ClxConsoleUIEngine::text("%02X ", gattEventDetails.gattEvent.data[i]);
            }

#if defined(CLX_BLE_ISOCHRONOUS)
            if (clxBleBAgetReceiveStateAttributeHandle() == gattEventDetails.gattEvent.characteristicValueHandle)
            {
                clxBleBAprocessReceiveStateNotification(gattEventDetails.gattEvent.data, gattEventDetails.gattEvent.dataLength);
            }
#endif /* defined(CLX_BLE_ISOCHRONOUS) */
            
            ClxConsoleUIEngine::text("\n");
        }
        else
        {
            ClxConsoleUIEngine::text("\nGet Pending Event command failed with the result: %s\n", clxGetErrorCodeText(errorCode));
        }
    }
    else if (messageID ==  CLX_BLE_AUDIO_GET_AUDIO_CAPABILITIES_COMPLETE)
    {
        ClxConsoleUIEngine::text("\nGet audio capabilities command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID ==  CLX_BLE_AUDIO_GET_ASE_ID_COMPLETE)
    {
        ClxConsoleUIEngine::text("\nGet Ase ID command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID ==  CLX_BLE_AUDIO_GET_SUPPORTED_AUDIO_CONTEXTS_COMPLETE)
    {
        ClxConsoleUIEngine::text("\nGet supported audio contexts command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID ==  CLX_BLE_AUDIO_GET_AVAILABLE_AUDIO_CONTEXTS_COMPLETE)
    {
        ClxConsoleUIEngine::text("\nGet available audio contexts command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else
    {
        return FALSE;
    }
    
    return TRUE;
}

/*******************************************************************************************************************************
*                                                   createGattClientHandle
*
* Create the GATT profile handle with client role on local device.
*
* \param stack       - Local device stack handle
*
* \return ClxHandle  - GATT client handle
*
*******************************************************************************************************************************/
ClxHandle createGattClientHandle(ClxStack stack)
{
    /**
    Create GATT client handle. This handle to be passed for other GATT client API commands.
    */
    ClxHandle gattClientHandle = clxGattCreateClient(stack, bleGattClientMessageHandler);
    if (!gattClientHandle)
    {
        ClxConsoleUIEngine::text ("\nGATT Client instance creation failed\n");
        CLX_ASSERT((NULL != gattClientHandle));
    }

    return gattClientHandle;
}

/*******************************************************************************************************************************
*                                                    deleteGattClientHandle
*
* Delete the GATT profile handle when there is no use for this profile.
*
* \param handle  - GATT client handle
*
*******************************************************************************************************************************/
void deleteGattClientHandle(ClxHandle handle)
{
    if (handle != NULL)
    {
        /**
        Close the GATT client handle which does the windup procedures and releases all associated resources in stack.
        */
        clxCloseHandle(handle);
    }
    else
    {
        ClxConsoleUIEngine::text("\nInvalid handle\n");
    }
}

