/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                GattServer.cpp
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
#include "GattServer.h"
#include "Gatt.Ble.Includes.h"
#include "mainBluetooth.h"

/*******************************************************************************************************************************
*                                                   createGattServerHandle
*
* Create the GATT profile with the server role.
*
* \param stack             - Local device stack handle.
*
* \return ClxHandle        - GATT server handle.
*
*******************************************************************************************************************************/
ClxHandle createGattServerHandle(ClxStack stack)
{
    /**
    Create GATT server handle. This handle to be passed for other GATT server API commands.
    */
    ClxHandle gattServerHandle = clxGattCreateServer(stack, stackMessageHandler);
    if (!gattServerHandle)
    {
        ClxConsoleUIEngine::text ("\nGATT Server instance creation failed\n");
        CLX_ASSERT((NULL != gattServerHandle));
    }

    return gattServerHandle;
}

/*******************************************************************************************************************************
*                                                   deleteGattServerHandle
*
* Delete the GATT profile service handle. 
*
* \param gattServer  - GATT server handle.
*
*******************************************************************************************************************************/
void deleteGattServerHandle(ClxHandle gattServer)
{
    if (gattServer)
    {
        /**
        Close the GATT server handle which does the windup procedures and releases all associated resources in stack.
        */
        clxCloseHandle(gattServer);
    }
    else
    {
        ClxConsoleUIEngine::text("\nInvalid Handle\n");
    }
}

u2 getLocalServiceBaseHandle(u2 serviceIndex)
{
    u2 baseHandle = 0;

    if (serviceIndex < NumberOfBleGattServices)
    {
        baseHandle = clxBleGattServiceList[serviceIndex].handleBase;
    }
    else
    {
        ClxConsoleUIEngine::text("\nInvalid service Index");
    }

    return baseHandle;
}

u2 clxBleGetServerLocalValueHandle ( GattServicesIndex serviceIndex, s4 characteristicIndex )
{
    if ( NumberOfBleGattServices <= serviceIndex )
    {
        clxConsoleUIEngineText("Invlaid Service Index\n");
        return 0;
    }
    return clxBleGattServiceList[serviceIndex].handleBase + (u2)characteristicIndex;
}

#if defined(CLX_BLE_HID)
void configureHidInformation(ClxHandle gattServer)
{
    ClxError ret = CLX_ERROR;

    /* Protocol mode */
    u1 mode = 0x00;         // Boot protocol
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_HumanInterfaceDeviceIndex].handleBase + CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_PROTOCOL_MODE_HANDLE_INDEX),
                            (u1*)&mode,
                            sizeof(mode),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring HID protocol mode failed with error %s",clxGetErrorCodeText(ret));
        return;
    }

    /* HID Information */
    u1 hidDevInfo[4];

    hidDevInfo[0] = 0x11;
    hidDevInfo[1] = 0x01;       // bcdHID
    hidDevInfo[2] = 0x00;       // country code
    hidDevInfo[3] = 0x02;       // flag - normally connectable
    
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_HumanInterfaceDeviceIndex].handleBase + CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_HID_INFORMATION_HANDLE_INDEX),
                            hidDevInfo,
                            sizeof(hidDevInfo),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring HID information failed with error %s",clxGetErrorCodeText(ret));
        return;
    }

    /* Report Map */
    u1 reportMap[] =    {
                            0x05, 0x01,             // Usage Page (Generic Desktop)
                            0x09, 0x06,             // Usage (Keyboard)
                            0xA1, 0x01,             // Collection (Application)
                            0x85, 0x01,             // Report ID = 1
                            0x05, 0x07,             // Usage Page (Keyboard)
                            0x19, 0xE0,             // Usage Minimum (Keyboard LeftControl)
                            0x29, 0xE7,             // Usage Maximum (Keyboard Right GUI)
                            0x15, 0x00,             // Logical Min (0)
                            0x25, 0x01,             // Logical Max (1)
                            0x75, 0x01,             // Report Size (1)
                            0x95, 0x08,             // Report Count (8 modifier bits)
                            0x81, 0x02,             // Input (Data,Var,Abs) ? Modifiers
                            0x95, 0x01,             // Report Count (1)
                            0x75, 0x08,             // Report Size (8)
                            0x81, 0x01,             // Input (Const,Array,Abs) ? Reserved byte
                            0x95, 0x06,             // Report Count (6 keys)
                            0x75, 0x08,             // Report Size (8)
                            0x15, 0x00,             // Logical Min (0)
                            0x25, 0x65,             // Logical Max (101 keys)
                            0x05, 0x07,             // Usage Page (Keyboard)
                            0x19, 0x00,             // Usage Min (0)
                            0x29, 0x65,             // Usage Max (101)
                            0x81, 0x00,             // Input (Data,Array) ? Keycodes
                            0xC0                    //  End Collection
                        };

    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_HumanInterfaceDeviceIndex].handleBase + CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_REPORT_MAP_HANDLE_INDEX),
                            reportMap,
                            sizeof(reportMap),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring Report map failed with error %s",clxGetErrorCodeText(ret));
        return;
    }

    /* Boot keyboard input report */
    u1 inputReport[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_HumanInterfaceDeviceIndex].handleBase + CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_HANDLE_INDEX),
                            inputReport,
                            sizeof(inputReport),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring boot keyboard input report failed with error %s",clxGetErrorCodeText(ret));
        return;
    }
}
#endif /* defined(CLX_BLE_HID) */

void configureDeviceInformation(ClxHandle gattServer)
{
    ClxError ret = CLX_ERROR;

    /* Manufacture name */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_DeviceInformationIndex].handleBase + CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_HANDLE_INDEX),
                            (u1*)"Clarinox",
                            strlen("Clarinox"),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);
    
    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring Manufacture name failed with error %s",clxGetErrorCodeText(ret));
        return;
    }

    /* Model Number */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_DeviceInformationIndex].handleBase + CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_HANDLE_INDEX),
                            (u1*)"clx-0083-01",
                            strlen("clx-0083-01"),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring Model number failed with error %s",clxGetErrorCodeText(ret));
        return;
    }

    /* Serial Number */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_DeviceInformationIndex].handleBase + CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_HANDLE_INDEX),
                            (u1*)"0083-25-01",
                            strlen("0083-25-01"),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring Serial number failed with error %s",clxGetErrorCodeText(ret));
        return;
    }

    /* H/W revision */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_DeviceInformationIndex].handleBase + CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_HARDWARE_REVISION_STRING_HANDLE_INDEX),
                            (u1*)"0083-0001-0001",
                            strlen("0083-0001-0001"),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring h/w revision failed with error %s",clxGetErrorCodeText(ret));
        return;
    }

    /* Firmware revision */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_DeviceInformationIndex].handleBase + CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_FIRMWARE_REVISION_STRING_HANDLE_INDEX),
                            (u1*)"0083-0000-0001",
                            strlen("0083-0000-0001"),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring firmware revision failed with error %s",clxGetErrorCodeText(ret));
        return;
    }
}

void configureGenericAccessDetails(ClxHandle gattServer)
{
#define APPERANCE_GENERIC_WEARABLE_AUDIO_DEVICE             0x0940
#define APPERANCE_HID_KEYBOARD                              0x03C1

    ClxError ret = CLX_ERROR;
    u2 apperance;
    
    /* Local device name */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_GenericAccessIndex].handleBase + CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_DEVICE_NAME_HANDLE_INDEX),
                            (u1*)clxGetBTLocalDeviceName(),
                            strlen(clxGetBTLocalDeviceName()),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);
    
    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring local device name failed with error %s",clxGetErrorCodeText(ret));
    }

#if defined(CLX_BLE_HID)
    apperance = APPERANCE_HID_KEYBOARD;
#else
    apperance = APPERANCE_GENERIC_WEARABLE_AUDIO_DEVICE;
#endif /* defined(CLX_BLE_HID) */

    /* Local device apperance */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_GenericAccessIndex].handleBase + CLX_GATT_SERVICE_GENERIC_ACCESS_CHARACTERISTIC_APPEARANCE_HANDLE_INDEX),
                            (u1*)&apperance,
                            sizeof(apperance),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);
    
    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring local device apperance failed with error %s",clxGetErrorCodeText(ret));
    }
}

#if defined(CLX_BLE_ISOCHRONOUS)
void configureTmapRole(ClxHandle gattServer)
{
    ClxError ret = CLX_ERROR;
    
    u2 audioRole = ClxBleAudioRole_UnicastMediaReceiver | ClxBleAudioRole_BroadcastMediaReceiver;
    u1 buffer[2] = {0};
    
    WRITE_TO_LITTLEENDIAN_2(audioRole, (u2*)buffer);
    
    /* TMAP role */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_TelephonyMediaAudioServiceIndex].handleBase + CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_HANDLE_INDEX),
                            buffer,
                            sizeof(buffer),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);
    
    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring TMAP role failed with error %s",clxGetErrorCodeText(ret));
    }
}
#endif /* defined(CLX_BLE_ISOCHRONOUS) */

void configureGenericAttributeDetails(ClxHandle gattServer)
{
    ClxError ret = CLX_ERROR;
    u1 feature = 0x00;
    
    /* Server supported feature */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_GenericAttributeIndex].handleBase + CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_CHARACTERISTIC_SERVER_SUPPORTED_FEATURE_HANDLE_INDEX),
                            &feature,
                            sizeof(feature),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);
    
    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring Server supported feature failed with error %s",clxGetErrorCodeText(ret));
    }
}

void configureBatteryLevel(ClxHandle gattServer)
{
    ClxError ret = CLX_ERROR;
    u1 level = 80;
    
    /* Battery level */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_BatteryIndex].handleBase + CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_HANDLE_INDEX),
                            &level,
                            sizeof(level),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);
    
    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring Server supported feature failed with error %s",clxGetErrorCodeText(ret));
    }
}

#if defined(CLX_BLE_CS_REFLECTOR)
void configureRangingFeature(ClxHandle gattServer)
{
    ClxError ret = CLX_ERROR;

    u4 feature = (1 << ClxBleRasFeatures_RealTimeRangingData);
    u1 buffer[4] = {0};

    WRITE_TO_LITTLEENDIAN_4(feature, buffer);

    /* Ranging feature */
    ret = clxGattWriteLocal(gattServer,
                            (u2)(clxBleGattServiceList[GattService_RangingServiceIndex].handleBase + CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_HANDLE_INDEX),
                            buffer,
                            sizeof(buffer),
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        ClxConsoleUIEngine::text("\nConfiguring the Ranging feature failed with error %s",clxGetErrorCodeText(ret));
    }

}
#endif /* defined(CLX_BLE_CS_REFLECTOR) */

/*******************************************************************************************************************************
*                                                   registerLocalService
*
* Registers the GATT services in local server.
*
* \param gattServer  - GATT server handle.
*
* \return ClxError   - API error code returned by stack.
*
*******************************************************************************************************************************/
ClxError registerLocalService(ClxHandle gattServer, u2 serviceIndex)
{
    ClxError ret = CLX_ERROR;
    
    if (gattServer && (serviceIndex < NumberOfBleGattServices))
    {
        /**
        Registers GATT services in local GATT server.
        */
        ret = clxGattRegisterLocalService(gattServer,
                                          clxBleGattServiceList[serviceIndex].gettGattServiceInterface(),
                                          NULL,
                                          &clxBleGattServiceList[serviceIndex].handleBase,
                                          gBlock);

        if (CLX_SUCCESS == ret)
        {
            ClxConsoleUIEngine::text("\"%s\" created successfully base handle %x\n", clxBleGattServiceList[serviceIndex].name, clxBleGattServiceList[serviceIndex].handleBase);
        }
        else
        {
            ClxConsoleUIEngine::text("\nclxGattRegisterLocalService: status %s",clxGetErrorCodeText(ret));
        }

        switch (serviceIndex)
        {
            case GattService_GenericAccessIndex:
            {
                configureGenericAccessDetails(gattServer);
                break;
            }
            
            case GattService_GenericAttributeIndex:
            {
                configureGenericAttributeDetails(gattServer);
                break;
            }
            
            case GattService_BatteryIndex:
            {
                configureBatteryLevel(gattServer);
                break;
            }
            
            case GattService_DeviceInformationIndex:
            {
                configureDeviceInformation(gattServer);
                break;
            }

#if defined(CLX_BLE_CS_REFLECTOR)
            case GattService_RangingServiceIndex:
            {
                configureRangingFeature(gattServer);
                break;
            }
#endif /* defined(CLX_BLE_CS_REFLECTOR) */

#if defined(CLX_BLE_HID)
            case GattService_HumanInterfaceDeviceIndex:
            {
                configureHidInformation(gattServer);
                break;
            }
#endif /* defined(CLX_BLE_HID) */

#if defined(CLX_BLE_ISOCHRONOUS)
            case GattService_TelephonyMediaAudioServiceIndex:
            {
                configureTmapRole(gattServer);
                break;
            }
#endif /* defined(CLX_BLE_ISOCHRONOUS) */
        }
    }
    else
    {
        ClxConsoleUIEngine::text("\nInvalid parameter\n");
    }

    return ret;
}

ClxError unRegisterLocalService(ClxHandle gattServer, u2 serviceIndex)
{
    ClxError ret = CLX_ERROR;

    if (gattServer && (serviceIndex < NumberOfBleGattServices))
    {
        ret = clxGattUnregisterLocalService(gattServer, clxBleGattServiceList[serviceIndex].handleBase, gBlock);
        
        if (CLX_SUCCESS == ret)
        {
            ClxConsoleUIEngine::text("\"%s\" destroyed successfully\n", clxBleGattServiceList[serviceIndex].name);
        }
        else
        {
            ClxConsoleUIEngine::text("\nclxGattUnregisterLocalService: status %s",clxGetErrorCodeText(ret));
        }
    }
    else
    {
        ClxConsoleUIEngine::text("\nInvalid parameter\n");
    }

    return ret;
}

#if defined(CLX_BLE_ISOCHRONOUS)
ClxResult writeAse(ClxHandle gattServer, u2 handleIndex,u1* data, u2 length)
{
    /* Write ASE (Either Sink or Source) */
    ClxResult ret = clxGattWriteLocal(gattServer,
                                     (u2)(clxBleGattServiceList[GattService_AudioStreamControlIndex].handleBase + handleIndex),
                                     data,
                                     length,
                                     WRITE_TIMEOUT_VALUE,
                                     TRUE);
    return ret;
}

void aseCodecConfigure(u2 handleIndex)
{
    ClxResult  ret = CLX_FAIL;
    u1 metaData[256] = { 0 };
    u1 index = 0;
    u1 aseId = 0x01;

    if (handleIndex == CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_CHARACTERISTIC_SOURCE_ASE_HANDLE_INDEX)
    {
        aseId = 0x02;
    }

    metaData[index++] = aseId;          // Ase Id
    metaData[index++] = 0x01;           // Codec config
    metaData[index++] = 0x00;           // Framing
    metaData[index++] = 0x01;           // Preferred phy
    metaData[index++] = 0x00;           // Preferred retransmission no
    metaData[index++] = 0x05;
    metaData[index++] = 0x00;           // Max Transport latency
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;           // Presentation delay min
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;           // Presentation delay max
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;           // Preferred presentation delay min
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;           // Preferred presentation delay max
    metaData[index++] = 0x06;
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;           // codec id
    metaData[index++] = 0x13;           // Codec specific config length
    metaData[index++] = 0x02;           // Sampling freq
    metaData[index++] = 0x01;
    metaData[index++] = 0x08;
    metaData[index++] = 0x02;           // frame duration
    metaData[index++] = 0x02;
    metaData[index++] = 0x01;
    metaData[index++] = 0x05;           // Audio channel count
    metaData[index++] = 0x03;
    metaData[index++] = 0x01;
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;
    metaData[index++] = 0x00;
    metaData[index++] = 0x03;           // Number of octects
    metaData[index++] = 0x04;
    metaData[index++] = 0x3c;
    metaData[index++] = 0x00;
    metaData[index++] = 0x02;           // codec frames
    metaData[index++] = 0x05;
    metaData[index++] = 0x01;
    
    ret = clxGattWriteLocal(getGattServerHandle(),
                            (u2)(clxBleGattServiceList[GattService_AudioStreamControlIndex].handleBase + handleIndex),
                            metaData,
                            index,
                            WRITE_TIMEOUT_VALUE,
                            TRUE);

    if (CLX_SUCCESS != ret)
    {
        clxConsoleUIEngineText("\nCodec configuring failed with error %s", clxGetErrorCodeText(ret));
    }
}
#endif /* defined(CLX_BLE_ISOCHRONOUS) */

/*******************************************************************************************************************************
*                                                bleGattServerMessageHandler
*
* This call-back function is registered for the GAP and GATT profiles, 
* any events raised by GATT Server profile causes this call-back function executed with
* the associated event and parameters
*
* \param stack          - Local device stack handle.
* \param serviceHandle  - Profile/service handle.
* \param messageID      - Indication id.
* \param params         - Void pointer to the indication parameters.
* \param errorCode      - Contains the error code.
*
* \return boolean       - TRUE If the call-back function handles indication or indication with *_COMPLETE.
*                         Otherwise, return FALSE
* \note                 - The API should be called in non blocking mode.
*
*******************************************************************************************************************************/
boolean bleGattServerMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    (void)stack;
    (void)serviceHandle;

    /**
    These (below indications with *_COMPLETE) are command complete indications received when the execution of corresponding API commands
    are completed. The command complete indications are received only when the API has been called in non-blocking mode. 
    The output parameters can be accessed from argument "params".
    */
    if (messageID == CLX_GATT_WRITE_LOCAL_COMPLETE)
    {
        ClxConsoleUIEngine::text("\nWrite command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GATT_REGISTER_LOCAL_SERVICE_COMPLETE)
    {
        ClxGattRegisterLocalServiceComplete* arg = (ClxGattRegisterLocalServiceComplete*)params;
        
        if (errorCode == CLX_SUCCESS)
        {
            ClxConsoleUIEngine::text("\n:Register local service complete with handle base %x\n", (*arg->serviceHandleBase));
        }
    }
    else if (messageID == CLX_GATT_READ_LOCAL_COMPLETE)
    {
        if (errorCode == CLX_SUCCESS)
        {
            ClxGattReadLocalComplete* params_ = (ClxGattReadLocalComplete*)params;
            ClxConsoleUIEngine::text("The updated value of testData is: ");

            for(u4 i = 0; i < *(params_->readCharacteristicValueLength); i++)
            {
                ClxConsoleUIEngine::text("%02X ", params_->characteristicValueBuffer[i]);
            }
        }
        else
        {
            ClxConsoleUIEngine::text("clxGattReadLocal failed with error %u\n", errorCode);
        }
    }
    /**
    Indicates that the client has written to local device characteristics
    */
    else if (messageID == CLX_GATT_VALUE_UPDATED_INDICATION)
    {
        ClxGattValueUpdatedIndication* params_ = (ClxGattValueUpdatedIndication*)params;

        ClxConsoleUIEngine::text("\nThe value of the handle 0x%X updated\n", params_->characteristicHandle);

        u2 serviceHandleBase = (u2)clxBleGetServiceHandleBaseFromHandle(params_->characteristicHandle);

        for (u4 i = 0; i < sizeof(clxBleGattServiceList)/sizeof(ClxBleGattServiceInfo); i++)
        {
            if (clxBleGattServiceList[i].handleBase == serviceHandleBase)
            {
                const s1* characteristicName = clxBleGattServiceList[i].getGattServiceCharacteristicName(clxBleGetServiceAttributeIndexFromHandle(params_->characteristicHandle));

                if (characteristicName == NULL)
                {
                    characteristicName = "Unknown Characteristic";
                }

                ClxConsoleUIEngine::text("Service : %s\n", clxBleGattServiceList[i].name);
                ClxConsoleUIEngine::text("Characteristic : %s\n", characteristicName);
            }
        }

#if defined(CLX_BLE_ISOCHRONOUS)
        ClxResult ret = clxBLECheckAndWriteCharacteristicsInfo ( params_->characteristicHandle,
                                                       params_->characteristicValueBuffer,
                                                       params_->valueLength );
        if ( CLX_SUCCESS != ret )
        {
            ClxConsoleUIEngine::text("Value:\n");
            printBufferHexAndChar( params_->characteristicValueBuffer, params_->valueLength );
        }
#else
        ClxConsoleUIEngine::text("Data:");
        for (u4 i = 0; i < params_->valueLength; i++)
        {
            ClxConsoleUIEngine::text(" %02x", params_->characteristicValueBuffer[i]);
        }
#endif /* CLX_BLE_ISOCHRONOUS */
    }
    else if (messageID == CLX_GATT_MTU_VALUE_UPDATED_INDICATION)
    {
        ClxGattMtuValueUpdatedIndication* arg = (ClxGattMtuValueUpdatedIndication*)params;
        ClxConsoleUIEngine::text("\nMtu value updated %x", arg->negotiatedMtu);
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

