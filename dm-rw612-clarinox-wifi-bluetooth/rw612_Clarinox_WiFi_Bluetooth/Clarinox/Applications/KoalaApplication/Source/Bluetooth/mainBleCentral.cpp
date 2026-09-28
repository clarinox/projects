/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                mainBleCentral.cpp
* Description         This main application file provides the GATT operations
*                     and main menu.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

// _____________________________________________________________________________
//
#undef  CLX_MODULE_ID
#define CLX_MODULE_ID  20123
// _____________________________________________________________________________
//

#include "ClxBsp.h"
#include "ClarinoxBlue.h"

#include "Gatt.Ble.Common.Api.h"
#include "Gap.Ble.Api.h"
#include "Gap.Ble.Bonding.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Client.Api.h"

#include "mainBluetooth.h"
#include "GattClient.h"
#include "GapBleApp.h"
#include "GattApp.h"

#include "Gatt.Ble.BatteryService.Api.h"
#include "org.bluetooth.service.battery_service.h"
#include "Gatt.Ble.DeviceInfoService.Api.h"
#include "org.bluetooth.service.device_information.h"
//#include "UnicastCommon.h"

#if defined( CLX_BLE_SERVICE_EXTENDED_API )
#include "BleServiceCommon.h"
#endif /* defined( CLX_BLE_SERVICE_EXTENDED_API ) */

#include <stdio.h>
#include <stdlib.h>

extern s1 inputValue[MAX_INPUT_SIZE];

/* Menu options used to invoke BleCentral main menu */
typedef enum BleCentralMenuItemEnum
{
    BleCentralMenuItem_StartScan                    = 1,
    BleCentralMenuItem_StopScan,
    BleCentralMenuItem_SyncPeriodicAdvertisingTrain,
    BleCentralMenuItem_ConnectToDiscoveredDevice,
    BleCentralMenuItem_ChangeConnectionParameters,
#if defined(CLX_OOB_PAIRING_SUPPORT)
    BleCentralMenuItem_GenerateOobKeys,
    BleCentralMenuItem_EnableDisableOobPairing,
#endif
    BleCentralMenuItem_InitiatePairing,
    BleCentralMenuItem_Disconnect,
    BleCentralMenuItem_WhiteList,
    BleCentralMenuItem_GetBatteryLevel,
    BleCentralMenuItem_GetDeviceInformation,
    BleCentralMenuItem_GATT,
    BleCentralMenuItem_DeletePairedDevice,
#if defined( CLX_BLE_SERVICE_EXTENDED_API )
    BleCentralMenuItem_BleServicesMenu,
#endif /* defined( CLX_BLE_SERVICE_EXTENDED_API ) */
    BleCentralMenuItem_ReturnToPreviousMenu,
    BleCentralMenuItem_TotalItems
}BleCentralMenuItem;

/*
String representing no device name
*/
#define NO_DEVICE_NAME                  "<null>"

/* Structure with variables required for LE Central instance */
ClxCentralInstanceInfo centralInfo = {};

/* Indicates whether device filtering by name is enabled or not. By default set as enable */
boolean clxDeviceNameFilteringOption = TRUE;

/*******************************************************************************************************************************
*                                                bleCentralMessageHandler
*
* This call-back function is registered for the GAP profile, 
* any events raised by GAP profile causes this call-back function executed with
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
boolean bleCentralMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    /**
    These (below indications with *_COMPLETE) are command complete indications received when the execution of corresponding API commands
    are completed. The command complete indications are received only when the API has been called in non-blocking mode. 
    The output parameters can be accessed from argument "params".
    */
    if (messageID == CLX_GAP_BLE_START_SCAN_COMPLETE)
    {
        clxConsoleUIEngineText("\nStart Scan command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_STOP_SCAN_COMPLETE)
    {
        clxConsoleUIEngineText("\nStop Scan command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_CONNECT_TO_PERIPHERAL_COMPLETE)
    {
        ClxGapBleConnectToPeripheralComplete *arg = (ClxGapBleConnectToPeripheralComplete*)params;
        
        clxConsoleUIEngineText("\nConnect to peripheral completed with the result %s", clxGetErrorCodeText(errorCode));

        if (CLX_SUCCESS == errorCode)
        {
            /**
            Variable to hold the connection status after connection has established successfully with peripheral.
            */
            centralInfo.isRemoteDeviceConnected = TRUE;

            clxConsoleUIEngineText("\n(Address = %02X%02X%02X%02X%02X%02X)",arg->connectionDetails->remoteDeviceAddr.value[0],
                                                                arg->connectionDetails->remoteDeviceAddr.value[1],
                                                                arg->connectionDetails->remoteDeviceAddr.value[2],
                                                                arg->connectionDetails->remoteDeviceAddr.value[3],
                                                                arg->connectionDetails->remoteDeviceAddr.value[4],
                                                                arg->connectionDetails->remoteDeviceAddr.value[5]);

            clxConsoleUIEngineText("(Connection handle : %x)\n", arg->connectionDetails->connectionHandle);
            clxConsoleUIEngineText("(Connection interval : %x)\n", arg->connectionDetails->connectionInterval);
            clxConsoleUIEngineText("(Connection latency : %x)\n", arg->connectionDetails->connectionLatency);
            clxConsoleUIEngineText("(Supervision timeout : %x)\n", arg->connectionDetails->supervisionTimeout);
        }

        return TRUE;
    }
    /* Print BLE advertising packet and connect to first one found */
    else if (messageID == CLX_GAP_BLE_DEVICE_ADVERTISING_INDICATION)
    {
        ClxGapBleDeviceAdvertisingIndication* arg = (ClxGapBleDeviceAdvertisingIndication*)params;

        RemoteDeviceInfo* remoteDeviceInfo = centralInfo.remoteDeviceList.findDevice(arg->deviceAddr);

        /* Lets see if the advertising data contains the short or long name: */
        u1 nameLength;
        const u1* name = clxBleFindAdvertisingDataField(&arg->advertisingData, 8 /* Short name */, &nameLength);

        if (!name)
        {
            name = clxBleFindAdvertisingDataField(&arg->advertisingData, 9 /* Long name */, &nameLength);
        }

        if (!remoteDeviceInfo)
        {
            remoteDeviceInfo = centralInfo.remoteDeviceList.addDevice(arg->deviceAddr, name, nameLength, CLX_BLE_INVALID_ADVERTISING_SID_VALUE, arg->rssi, 0 /* no ble audio */);
        }

        if (remoteDeviceInfo && name)
        {
            clxConsoleUIEngineText("\nDevice Found : %s (Advertising Type = %02x) (Address Type = %02x) (Address = %02X%02X%02X%02X%02X%02X) (RSSI = %d)\n",
                                                                                                                                remoteDeviceInfo->name,
                                                                                                                                arg->advertisingType,
                                                                                                                                arg->deviceAddr.addressType,
                                                                                                                                arg->deviceAddr.value[0],
                                                                                                                                arg->deviceAddr.value[1],
                                                                                                                                arg->deviceAddr.value[2],
                                                                                                                                arg->deviceAddr.value[3],
                                                                                                                                arg->deviceAddr.value[4],
                                                                                                                                arg->deviceAddr.value[5],
                                                                                                                                (s4)arg->rssi);
        }
        else
        {
            clxConsoleUIEngineText("\nDevice Found : (Advertising Type = %02x) (Address Type = %02x) (Address = %02X%02X%02X%02X%02X%02X) (RSSI = %d)\n",
                                                                                                                                 arg->advertisingType,
                                                                                                                                 arg->deviceAddr.addressType,
                                                                                                                                 arg->deviceAddr.value[0],
                                                                                                                                 arg->deviceAddr.value[1],
                                                                                                                                 arg->deviceAddr.value[2],
                                                                                                                                 arg->deviceAddr.value[3],
                                                                                                                                 arg->deviceAddr.value[4],
                                                                                                                                 arg->deviceAddr.value[5],
                                                                                                                                 (s4)arg->rssi);
        }

        if (remoteDeviceInfo)
        {
            remoteDeviceInfo->rssi = arg->rssi;
        }
    }
    /**
    This indication denotes connection disconnected by remote device.
    */
    else if (messageID == CLX_GAP_BLE_LINK_DISCONNECTION_INDICATION)
    {
        ClxGapBleLinkDisconnectionIndication *arg = (ClxGapBleLinkDisconnectionIndication*)params;

        clxConsoleUIEngineText("\nDisconnected by remote device with the result %s", clxGetErrorCodeText(arg->reason));
        clxConsoleUIEngineText("\nConnection handle: %x\n", arg->connectionHandle);
        centralInfo.isRemoteDeviceConnected = FALSE;

        /* Common indication, so let other roles/handlers too handle this event */
        return FALSE;
    }
    else
    {
        /* BLE Indication handler for events that are common to Central and Peripheral */
        if (TRUE == bleStackMessageHandler(stack, serviceHandle, messageID, params, errorCode))
        {
            return TRUE;
        }
        else if (TRUE == bleGattClientMessageHandler(stack, serviceHandle, messageID, params, errorCode))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    
    return TRUE;
}

/******************************************************************************************************************************************
*                                                       initializeBleCentral
*
* Initializes ClarinoxBlue BLE Central profiles with configuration parameters for Bluetooth stack.
*
* \param stack    - ClarinoxBlue stack.
*
* \return void
*
******************************************************************************************************************************************/
void initializeBleCentral(ClxStack stack)
{
    if (FALSE == centralInfo.isBleCentralInitialized)
    {
        /**
        Create maximum number of GATT client instance to connect to as many GATT servers.
        */
        for (u4 i = 0; i < MAX_NUMBER_OF_HANDLES; i++)
        {
            /**
            Array of object to store the handle of each GATT client instance.
            */
            centralInfo.gattClient[i].handle = createGattClientHandle(stack);
        }

        clxConsoleUIEngineText("\nThere are %u GATT Clients available\n%u is the active Client handle\n", MAX_NUMBER_OF_HANDLES, centralInfo.activeClientIndex);

        centralInfo.isBleCentralInitialized = TRUE;
        clxConsoleUIEngineText("GATT Client created successfully\n");
    }
    else
    {
        clxConsoleUIEngineText("\nBLE Central is already initialized\n");
    }
}

/******************************************************************************************************************************************
*                                                       terminateBleCentral
*
* De-Initializes ClarinoxBlue BLE Central profiles and resources.
*
******************************************************************************************************************************************/
void terminateBleCentral()
{
    if (centralInfo.isBleCentralInitialized)
    {
        for (u4 i = 0; i < MAX_NUMBER_OF_HANDLES; i++)
        {
            /**
            Delete the active GATT client handle before stack termination.
            */
            deleteGattClientHandle(centralInfo.gattClient[i].handle);
            centralInfo.gattClient[i].handle = CLX_BLE_INVALID_HANDLE;
            centralInfo.activeClientIndex = 0;
        }

        centralInfo.isBleCentralInitialized = FALSE;
    }
}

/***************************************************************************************************************************************
*                                              bleCentralGATTMenu
*
* Menu to display Bluetooth Low Energy Central GATT related menu options
*
****************************************************************************************************************************************/
void bleCentralGATTMenu(void)
{
    ClxResult ret = CLX_ERROR;
    while (TRUE)
    {
        const s1* GATTMenu =    "Discover All Primary Services\0"
                                "Discover All Characteristics of a Service\0"
                                "Discover All Descriptors of a Characteristic\0"
                                "Enable Notifications for a Characteristic\0"
                                "Enable Indications for a Characteristic\0"
                                "Read Attribute Value\0"
                                "Write Attribute Value\0"
                                "Return to previous menu\0";

        u4 index = clxConsoleUIEngineShowMenu("Please select how to proceed:", GATTMenu, GATTMenuItem_TotalItems - 1);
        switch (index)
        {
            case GATTMenuItem_DiscoverAllPrimaryServices:
            {
                bleCentralDiscoverAllPrimaryServices(NULL, TRUE);
                break;
            }

            case GATTMenuItem_DiscoverAllCharacteristics:
            {
                u4 serviceIndex = 0xFF;
                clxConsoleUIEngineInputBox("Enter the index of the service (First service has index 0): ", inputValue, MAX_INPUT_SIZE);
                (void)sscanf(inputValue, "%u", &serviceIndex);

                bleCentralDiscoverAllCharacteristics(NULL, serviceIndex);
                break;
            }

            case GATTMenuItem_DiscoverAllDescriptors:
            {
                /* Active GATT Client */
                GattClient *gattClient = &centralInfo.gattClient[centralInfo.activeClientIndex];

                clxConsoleUIEngineInputBox("Enter the index of the characteristic(First characteristic has index 0): ", centralInfo.input_buffer, 128);
                u4 characteristicIndex;
                (void)sscanf(centralInfo.input_buffer, "%u", &characteristicIndex);

                if (characteristicIndex >= MAX_NUM_CHARACTERISTIC_LIST)
                {
                    characteristicIndex = MAX_NUM_CHARACTERISTIC_LIST - 1;
                }

                /**
                Maximum size of characteristics descriptors details that can be stored in the user defined buffer.
                */
                u2 listSize = sizeof(gattClient->descriptorList) / sizeof(ClxGattCharacteristicDescriptorDetail);

                /**
                Variable returning the retrieved descriptors count from server upon successful completion of
                clxGattClientDiscoverCharacteristicDescriptors(..).
                */
                u2 noOfDescriptor = 0;

                /**
                Discovers all descriptors of a characteristic and get the list of attribute handle - value pairs
                corresponding to the characteristic descriptors in the characteristic definition.
                */
                ret = clxGattClientDiscoverCharacteristicDescriptors(gattClient->handle,                                    /* gatt                              */
                                                                     &gattClient->characteristicList[characteristicIndex],  /* characteristic                    */
                                                                     listSize,                                              /* listSize                          */
                                                                     gattClient->descriptorList,                            /* list                              */
                                                                     &gattClient->noOfDescriptor,                           /* numberOfCharacteristicDescriptors */
                                                                     gBlock);                                               /* block                             */

                noOfDescriptor = gattClient->noOfDescriptor;
                if (ret == CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("The number of descriptors found: %u\n", noOfDescriptor);
                    
                    for (u4 i = 0; i < noOfDescriptor; i++)
                    {
                        clxConsoleUIEngineText("\n%u: Handle: %#x Uuid: %#x", i, gattClient->descriptorList[i].handle, (gattClient->descriptorList[i].uuid.value[0]));

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
                        clxConsoleUIEngineText(" Name: %s", getDescriptorName((u2)(gattClient->descriptorList[i].uuid.value[0])));
#endif /* defined(CLX_BLE_GATT_SERVICE_VERBOSE) */

                    }
                }
                else
                {
                    clxConsoleUIEngineText("clxGattClientDiscoverCharacteristicDescriptors failed with error %s\n", clxGetErrorCodeText(ret));
                }

                break;
            }

            case GATTMenuItem_EnableNotification:
            {
                u4 characteristicIndex = 0xFF;
                clxConsoleUIEngineInputBox("Enter the index of the characteristic in the service (First characteristic has index 0): ", inputValue, MAX_INPUT_SIZE);
                (void)sscanf(inputValue, "%u", &characteristicIndex);

                bleCentralEnableNotification(characteristicIndex);
                break;
            }

            case GATTMenuItem_EnableIndication:
            {
                /* Active GATT Client */
                GattClient *gattClient = &centralInfo.gattClient[centralInfo.activeClientIndex];

                clxConsoleUIEngineInputBox("Enter the index of the characteristic in the service (First characteristic has index 0): ", centralInfo.input_buffer, 128);
                u4 characteristicIndex;
                (void)sscanf(centralInfo.input_buffer, "%u", &characteristicIndex);

                if (characteristicIndex >= MAX_NUM_CHARACTERISTIC_LIST)
                {
                    characteristicIndex = MAX_NUM_CHARACTERISTIC_LIST - 1;
                }

                if ((gattClient->characteristicList[characteristicIndex].properties & CLX_GATT_CHARACTERISTIC_PROPERTY_INDICATE) == 0)
                {
                    clxConsoleUIEngineText("The characteristic does not support indications\n");
                }
                else
                {
                    /* Now we search for descriptors: */
                    u2 listSize = sizeof(gattClient->descriptorList)/sizeof(ClxGattCharacteristicDescriptorDetail);
                    u2 noOfDescriptor = 0;

                    ret = clxGattClientDiscoverCharacteristicDescriptors(gattClient->handle,                                    /* gatt                              */
                                                                         &gattClient->characteristicList[characteristicIndex],  /* characteristic                    */
                                                                         listSize,                                              /* listSize                          */
                                                                         gattClient->descriptorList,                            /* list                              */
                                                                         &gattClient->noOfDescriptor,                           /* numberOfCharacteristicDescriptors */
                                                                         gBlock);                                               /* block                             */

                    noOfDescriptor = gattClient->noOfDescriptor;

                    clxConsoleUIEngineText("\nclxGattClientDiscoverCharacteristicDescriptors: status - %s\n", clxGetErrorCodeText(ret));

                    if (ret == CLX_SUCCESS)
                    {
                        for (u4 i = 0; i < noOfDescriptor; i++)
                        {
                            if (gattClient->descriptorList[i].uuid.value[0] == CLX_GATT_CHARACTERISTIC_CLIENT_CONFIG_DESCRIPTOR_UUID)
                            {
                                /**
                                Registers with server to get indications for the user selected characteristics index descriptor. Indication can be configured only on the
                                client characteristic configuration descriptors.
                                */
                                ret = clxGattClientConfigureCharacteristic(gattClient->handle,                          /* gatt             */
                                                                           &gattClient->descriptorList[i],              /* descriptorDetail */
                                                                           CLX_GATT_CLENT_CONFIGURATION_BIT_INDICATE,   /* flag             */
                                                                           TRUE);                                       /* block            */

                                clxConsoleUIEngineText("\nclxGattClientConfigureCharacteristic: status - %s\n", clxGetErrorCodeText(ret));
                            }
                        }
                    }
                }

                break;
            }

            case GATTMenuItem_ReadAttribute:
            {
                /* Active GATT Client */
                GattClient *gattClient = &centralInfo.gattClient[centralInfo.activeClientIndex];

                /* If no write response is required, optionsFlag = 0x1 */
                clxConsoleUIEngineInputBox ("Enter handle of the attribute (hex) to read:", centralInfo.input_buffer, 128);
                u4 handle;
                (void)sscanf(centralInfo.input_buffer, "%x", &handle);

                clxConsoleUIEngineInputBox ("Enter the beginning index to read from (enter 0 to read from the beginning):", centralInfo.input_buffer, 128);
                u4 attrIndex;
                (void)sscanf(centralInfo.input_buffer, "%u", &attrIndex);

                clxConsoleUIEngineInputBox ("Enter the max size to read:", centralInfo.input_buffer, 128);
                u4 size;
                (void)sscanf(centralInfo.input_buffer, "%u", &size);

                u1* readBuf = (u1*)&centralInfo.input_buffer;
                u4 readLength = 0;

                /**
                Reads a characteristic value from server using the characteristic value handle.
                */
                ret = clxGattClientRead(gattClient->handle, (u2)handle, readBuf, size, attrIndex, &readLength, gBlock);

                if (ret == CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("Read Completed Successfully: %u bytes\nData: ", readLength);

                    for (u4 i = 0; i < readLength; i++)
                    {
                        clxConsoleUIEngineText("%02X ", readBuf[i]);
                    }

                    clxConsoleUIEngineText("\n");
                }
                else
                {
                    clxConsoleUIEngineText("clxGattClientRead complete with result %s\n", clxGetErrorCodeText(ret));
                }

                break;
            }

            case GATTMenuItem_WriteAttribute:
            {
                /* Active GATT Client */
                GattClient *gattClient = &centralInfo.gattClient[centralInfo.activeClientIndex];

                /* If no write response is required, optionsFlag = 0x1 */
                ClxGattCharacteristicDetail cd;
                clxConsoleUIEngineInputBox("Enter handle of the attribute (hex) to write to: ", centralInfo.input_buffer, 128);
                u4 numToRead;
                (void)sscanf(centralInfo.input_buffer, "%x", &numToRead);
                cd.valueHandle = (u2)numToRead;

                clxConsoleUIEngineInputBox("Enter the Hex value for the characteristic - beware: NO SIZE CHECK:", centralInfo.input_buffer, sizeof(centralInfo.input_buffer));

                u1 tempBuffer[64] = { 0 };
                u1 length = 0;

                for (u4 count = 0; count < strlen(centralInfo.input_buffer); count++)
                {
                    if ('\n' == centralInfo.input_buffer[count])
                    {
                        centralInfo.input_buffer[count] = '\0';
                    }
                }

                for (u1 loop = 0; loop < strlen(centralInfo.input_buffer); loop += 2)
                {
                    (void)sscanf(centralInfo.input_buffer + loop, "%2x", &numToRead);
                    tempBuffer[length] = (u1)numToRead;
                    length++;
                }

                /**
                Writes a characteristic value to server using the characteristic value handle.
                */
                ret = clxGattClientWrite(gattClient->handle,                        /* gatt       */
                                         cd.valueHandle,                            /* handle     */
                                         ClxGattWriteProcedure_WriteWithResponse,   /* procedure  */
                                         (u1*)tempBuffer,                           /* data       */
                                         length,                                    /* dataLength */
                                         gBlock);                                   /* block      */

                clxConsoleUIEngineText("\nclxGattClientWrite complete with result %s\n", clxGetErrorCodeText(ret));
                break;
            }

            case GATTMenuItem_ReturnToPreviousMenu:
            {
                return;
            }

            default:
            {
                clxConsoleUIEngineText("\nPlease select a valid menu option..\n");
                break;
            }
        }
    }
}

/***************************************************************************************************************************************
*                                                lowEnergyCentralMenu
*
* Menu to display Bluetooth Low Energy Central role related menu options
*
* \param stack      - ClarinoxBlue stack
*
****************************************************************************************************************************************/
void lowEnergyCentralMenu(ClxStack stack)
{
    ClxResult ret = CLX_ERROR;
  
    /** 
    Determines the Legacy or extended mode of Scanning.
    */
    ClxBleAdvOrScanMode scanType = ClxBleAdvOrScanMode_INVALID;

    if (stack == NULL)
    {
        clxConsoleUIEngineText("\nClarinox Stack has to be initialized first\n");
        return;
    }

    while (TRUE)
    {
        const s1* menu =    "Start Scanning\0"
                            "Stop Scanning\0"
                            "Sync Periodic Advertising Train\0"
                            "Connect to a discovered device\0"
                            "Change connection parameters\0"
#if defined(CLX_OOB_PAIRING_SUPPORT)
                            "Generate OOB Keys\0"
                            "Enable/Disable OOB Pairing\0"
#endif
                            "Initiate Pairing\0"
                            "Disconnect\0"
                            "White list\0"
                            "Get Battery Level\0"
                            "Get Device Information\0"
                            "GATT\0"
                            "Delete paired device\0"
#if defined( CLX_BLE_SERVICE_EXTENDED_API )
                            "BLE Service API Menu\0"
#endif /* defined( CLX_BLE_SERVICE_EXTENDED_API ) */
                            "Return to previous menu\0";

        u4 index = clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, BleCentralMenuItem_TotalItems - 1);

        if ((FALSE == centralInfo.isBleCentralInitialized) && (index < BleCentralMenuItem_ReturnToPreviousMenu))
        {
            clxConsoleUIEngineText("\nPlease make sure to initialize the BLE Peripheral first\n");
            continue;
        }

        switch (index)
        {
            case BleCentralMenuItem_StartScan:
            {
                /**
                Reset the previously stored remote device details list in order to store the devices that are to be scanned now
                */
                centralInfo.remoteDeviceList.reset();

                clxConsoleUIEngineInputBox ("Enter the option 1 - Legacy scan, 2 - Extended scan: ", centralInfo.input_buffer, 128);
                (void)sscanf(centralInfo.input_buffer, "%u", (unsigned int*)&scanType);

                clxSetDeviceNameFilteringOption ();

                if ((scanType < ClxBleAdvOrScanMode_Legacy) || (scanType > ClxBleAdvOrScanMode_Extended))
                {
                    clxConsoleUIEngineText ("\nPlease enter the valid option as either 1 or 2");
                }
                else
                {
                    if (ClxBleAdvOrScanMode_Legacy == scanType)
                    {
                        ret = clxGapBleStartScan(stack, ClxBleOwnAddressMode_Identity, BleScanType_Passive, 100, 80, FALSE, TRUE, gBlock);
                        clxConsoleUIEngineText("\nclxGapBleStartScan: status - %s\n", clxGetErrorCodeText(ret));
                    }
                    else if (ClxBleAdvOrScanMode_Extended == scanType)
                    {
                        startExtendedScan(stack, FALSE);
                    }
                }
                break;
            }

            case BleCentralMenuItem_StopScan:
            {
                if (ClxBleAdvOrScanMode_Legacy == scanType)
                {
                    ret = clxGapBleStopScan(stack, gBlock);
                    clxConsoleUIEngineText("\nclxGapBleStopScan: status - %s\n", clxGetErrorCodeText(ret));
                }
                else if (ClxBleAdvOrScanMode_Extended == scanType)
                {
                    ret = clxGapBleDisableExtendedScan(stack, TRUE);
                    clxConsoleUIEngineText("\nclxGapBleDisableExtendedScan: status - %s\n", clxGetErrorCodeText(ret));
                }
                else
                {
                    clxConsoleUIEngineText("\nPerform start scanning first\n");
                }
                break;
            }

            case BleCentralMenuItem_SyncPeriodicAdvertisingTrain:
            {
                ClxBlePeriodicAdvertiserDetails advSet;
                clxMemSet(&advSet, 0x00, sizeof(ClxBlePeriodicAdvertiserDetails));
                
                RemoteDeviceInfo* device = showRemoteDeviceList();

                if (device)
                {
                    if (device->advSID == CLX_BLE_INVALID_ADVERTISING_SID_VALUE)
                    {
                        clxConsoleUIEngineText("\nThe selected Advertising set does not have a valid Advertising SID\n");
                        break;
                    }

                    advSet.advertiserAddress = device->address;
                    advSet.advertisingSID    = device->advSID;
                }

                ret = clxGapBlePeriodicAdvertisingStartSynchronizing ( stack,
                                                                       FALSE,
                                                                       TRUE,
                                                                       &advSet,
                                                                       0,
                                                                       CLX_BLE_PERIODIC_TRAIN_SYNC_TIMEOUT,
                                                                       0,
                                                                       TRUE);

                if (ret == CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("\nWaiting for CLX_GAP_BLE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_INDICATION indication.");
                }
                else
                {
                    clxConsoleUIEngineText("\nclxGapBlePeriodicAdvertisingStartSynchronizing failed with the error %s\n", clxGetErrorCodeText(ret));
                }

                break;
            }

            case BleCentralMenuItem_ConnectToDiscoveredDevice:
            {
                /* In case the scanning is still ongoing: */
                if (ClxBleAdvOrScanMode_Legacy == scanType)
                {
                    ret = clxGapBleStopScan(stack, TRUE);
                }
                else if (ClxBleAdvOrScanMode_Extended == scanType)
                {
                    ret = clxGapBleDisableExtendedScan(stack, TRUE);
                }

                /**
                Object to get the user selected remote device details for connection establishment
                */
                RemoteDeviceInfo* device = showRemoteDeviceList();

                if (device)
                {
                    clxConsoleUIEngineText("\nConnecting to the device %s address Type[%d], using the GATT client %u\n", device->name, device->address.addressType, centralInfo.activeClientIndex);

                    ClxBleConnectionDetails connectionDetails;

                    /**
                    Initiates connection establishment procedure with user selected BLE peripheral device.
                    */
                    if (ClxBleAdvOrScanMode_Legacy == scanType)
                    {
                        ret = clxGapBleConnectToPeripheral(stack,                               /* stack                        */
                                                           FALSE,                               /* performScan                  */
                                                           140,                                 /* scanInterval                 */
                                                           100,                                 /* scanWindow                   */
                                                           &device->address,                    /* peerAddress                  */
                                                           ClxBleOwnAddressMode_Identity,       /* localAddressType             */
                                                           50,                                  /* minimumConnectionInterval    */
                                                           70,                                  /* maximumConnectionInterval    */
                                                           0,                                   /* connectionLatency            */
                                                           2000,                                /* supervisionTimeout           */
                                                           1,                                   /* minimumConnectionEventLength */
                                                           0x0c00,                              /* maximumConnectionEventLength */
                                                           &connectionDetails,                  /* connectionDetails            */
                                                           CONNECTION_TIMEOUT,                  /* connectionTimeoutValue       */
                                                           gBlock);                             /* block                        */
                    }
                    else if (ClxBleAdvOrScanMode_Extended == scanType)
                    {
                        u4 advHandle = 0;
                        u4 subEvent = 0;

#if defined(CLX_BLE_PAWR)
                        clxConsoleUIEngineInputBox ("Enter advertising handle: ", centralInfo.input_buffer, 128);
                        (void)sscanf(centralInfo.input_buffer, "%u", &advHandle);
                        
                        
                        clxConsoleUIEngineInputBox ("Enter sub event: ", centralInfo.input_buffer, 128);
                        (void)sscanf(centralInfo.input_buffer, "%u", &subEvent);
#endif

                        ClxGapBleExtendedConnectParameters    connectParameter_Le1M_PHY = { };

                        connectParameter_Le1M_PHY.scanInterval = 140;
                        connectParameter_Le1M_PHY.scanWindow = 100;
                        connectParameter_Le1M_PHY.connectIntervalMin = 50;
                        connectParameter_Le1M_PHY.connectIntervalMax = 70;
                        connectParameter_Le1M_PHY.connectionLatency = 0;
                        connectParameter_Le1M_PHY.supervisionTimeout = 2000;
                        connectParameter_Le1M_PHY.minCElength = 0x01;
                        connectParameter_Le1M_PHY.maxCElength = 0x0C00;

                        ret = clxGapBleExtendedConnectToPeripheral(stack,                           /* stack                     */
                                                                   (u1)advHandle,                   /* advertising handle        */
                                                                   (u1)subEvent,                    /* sub event                 */
                                                                   ClxBleOwnAddressMode_Identity,   /* localAddressType          */
                                                                   &device->address,                /* peerAddress               */
                                                                   &connectParameter_Le1M_PHY,      /* connectParameter_Le1M_PHY */
                                                                   NULL,                            /* connectParameter_Le2M_PHY */
                                                                   NULL,                            /* connectParameter_Le_Coded */
                                                                   &connectionDetails,              /* connectionDetails         */
                                                                   CONNECTION_TIMEOUT,              /* connectionTimeoutValue    */
                                                                   TRUE);                           /* block                     */
                    }
                    else
                    {
                        clxConsoleUIEngineText("\nInvalid Connection Type\n");
                        break;
                    }

                    if (ret == CLX_SUCCESS)
                    {
                        clxConsoleUIEngineText("\nGATT Connection to the device %s is successful\n", device->name);

                        /**
                        Stores remote device name into the pairing information stored in the application for quick reference
                        */
                        ret = clxGapBleSetPairedDeviceName(stack, connectionDetails.connectionHandle, device->name, (u1)strlen(device->name), TRUE);
                        clxConsoleUIEngineText("\nclxGapBleSetPairedDeviceName: status - %s\n", clxGetErrorCodeText(ret));

                        /* Caching the remote device connection handle, address type and its address for further processing */
                        centralInfo.gattClient[centralInfo.activeClientIndex].connectionHandle = connectionDetails.connectionHandle;
                        centralInfo.gattClient[centralInfo.activeClientIndex].peerDeviceAddress.addressType = connectionDetails.remoteDeviceAddr.addressType;
                        memcpy(centralInfo.gattClient[centralInfo.activeClientIndex].peerDeviceAddress.value, connectionDetails.remoteDeviceAddr.value, CLX_BLE_GAP_ADDRESS_VALUE_LENGTH);

                        /**
                        Variable to store the final MTU size for ATT protocol communication after negotiation with server.
                        */
                        u2 negotiatedMTU;

                        /**
                        Binds this client instance with the server and also negotiate the MTU size for ATT communication.
                        */
                        ret = clxGattClientBind(centralInfo.gattClient[centralInfo.activeClientIndex].handle,
                                                connectionDetails.connectionHandle,
                                                251,
                                                &negotiatedMTU,
                                                gBlock);

                        clxConsoleUIEngineText("\nclxGattClientBind: negotiatedMTU[%u] status - %s\n", negotiatedMTU, clxGetErrorCodeText(ret));
                    }
                    else
                    {
                        clxConsoleUIEngineText("\nPhysical Connection attempt to the device %s failed with error %s\n", device->name, clxGetErrorCodeText(ret));
                    }
                }

                break;
            }

            case BleCentralMenuItem_ChangeConnectionParameters:
            {
                clxConsoleUIEngineText ("\nDo you want to update connection parameter?");
                s1 ch = clxConsoleUIEngineMessageBox("", "yYnN", 4);

                u1 filter = 0x00;

                if ((ch == 'y') || (ch == 'Y'))
                {
                    filter |= ClxBleParameterChangeFilter_ConnectionUpdate;
                }

                clxConsoleUIEngineText("\nDo you want to increase the data length?");
                ch = clxConsoleUIEngineMessageBox("", "yYnN", 4);

                if ((ch == 'y') || (ch == 'Y'))
                {
                    filter |= ClxBleParameterChangeFilter_DataLengthChange;
                }

                clxConsoleUIEngineText ("\nDo you want to change the PHY?");
                ch = clxConsoleUIEngineMessageBox("", "yYnN", 4);

                if ((ch == 'y') || (ch == 'Y'))
                {
                    filter |= ClxBleParameterChangeFilter_PhyUpdate;
                }

                changeConnectionParameters(stack,                                                                   /* stack                        */
                                           centralInfo.gattClient[centralInfo.activeClientIndex].connectionHandle,  /* connectionHandle             */
                                           filter,                                                                  /* filter                       */
                                           6,                                                                       /* minimumConnectionInterval    */
                                           6,                                                                       /* maximumConnectionInterval    */
                                           0,                                                                       /* connectionLatency            */
                                           2000,                                                                    /* supervisionTimeout           */
                                           1,                                                                       /* minimumConnectionEventLength */
                                           0x0c00,                                                                  /* maximumConnectionEventLength */
                                           251,                                                                     /* singlePacketLength           */
                                           0x0848,                                                                  /* singlePacketTransmitTime     */
                                           (ClxBlePhy_ControllerPreferredTx | ClxBlePhy_ControllerPreferredRx),     /* phyPreference                */
                                           ClxBlePhyType_2M,                                                        /* txPhy                        */
                                           ClxBlePhyType_2M,                                                        /* rxPhy                        */
                                           ClxBleLECodedPhy_NoPreference,                                           /* leCodedOptions               */
                                           gBlock);                                                                 /* block                        */

                break;
            }

#if defined(CLX_OOB_PAIRING_SUPPORT)
            case BleCentralMenuItem_GenerateOobKeys:
            {
                /* 
                Generate and store local Out-of-Band (OOB) data for transmission to the remote device, 
                or assign the received remote device OOB data to local variables, 
                preparing it for input to the stack.
                */
                generateOobData(stack);
                break;
            }
            
            case BleCentralMenuItem_EnableDisableOobPairing:
            {
                u4 option = 0;
                clxConsoleUIEngineInputBox("1 - Enable OOB pairing, 0 - Disable OOB pairing, 2 - Exit: ", centralInfo.input_buffer, MAX_INPUT_SIZE);
                (void)sscanf(centralInfo.input_buffer, "%u", &option);
                
                if (option < 2) 
                {
                    /* 
                    Configure OOB pairing in this section. Since the connection handle is already established 
                    (unlike in the Peripheral role), OOB pairing should be performed here before initiating the bonding process.
                    */
                    enableDisableOob(stack, centralInfo.gattClient[centralInfo.activeClientIndex].connectionHandle, (option ? TRUE : FALSE));
                }

                break;
            }
#endif

            case BleCentralMenuItem_InitiatePairing:
            {
                clxConsoleUIEngineInputBox("Enter the option 1 - Legacy pairing, 2 - Secure pairing, 3 - Start encryption: ", centralInfo.input_buffer, 128);
                u4 option;
                (void)sscanf(centralInfo.input_buffer, "%u", &option);

                if ((option < ClxBlePairMode_Legacy) || (option > ClxBlePairMode_StartEncryption))
                {
                    clxConsoleUIEngineText("\nPlease enter the valid option as either 1 or 2 or 3");
                }
                else
                {
                    /**
                    Set the local device in bondable mode.
                    */
                    ret = clxGapBleSetBondable(stack, TRUE, gBlock);
                   
                    if (ret == CLX_SUCCESS)
                    {
                        if (ClxBlePairMode_Legacy == option)
                        {
                            /*
                             Initiate bonding procedure where the security manager uses a key distribution approach to perform identity and encryption functionalities.
                            */
                            (ClxResult) initiateBlePairing(stack,
                                                           centralInfo.gattClient[centralInfo.activeClientIndex].connectionHandle,
                                                           FALSE,
                                                           gBlock);
                        }
                        else if (ClxBlePairMode_Secure == option)
                        {
                            /*
                            Initiate bonding procedure where the security manager uses a key distribution approach to perform identity and encryption functionalities.
                            */
                            (ClxResult) initiateBlePairing(stack,
                                                           centralInfo.gattClient[centralInfo.activeClientIndex].connectionHandle,
                                                           TRUE,
                                                           gBlock);
                        }
                        else
                        {
                            /*
                            We set mitmProtectionRequired to FALSE to make sure the encryption will happen regardless of the strength of the key we have:
                            */
                            startEncryption(stack, centralInfo.gattClient[centralInfo.activeClientIndex].connectionHandle, FALSE, FALSE, gBlock);
                        }
                    }
                    else
                    {
                        clxConsoleUIEngineText("\nLocal device is not bondable: status - %s\n", clxGetErrorCodeText(ret));
                    }
                }

                break;
            }

            case BleCentralMenuItem_Disconnect:
            {
                ret = clxGapBleDisconnectPhysicalLink(stack, centralInfo.gattClient[centralInfo.activeClientIndex].connectionHandle, DISCONNECTION_TIMEOUT, gBlock);
                clxConsoleUIEngineText("\nDisconnection completed with the result %s\n", clxGetErrorCodeText(ret));
                break;
            }

            case BleCentralMenuItem_WhiteList:
            {
                clxConsoleUIEngineInputBox("Enter the option 1 - Add device, 2 - Remove device, 3 - Remove all devices: ", centralInfo.input_buffer, 128);
                u4 option;
                (void)sscanf(centralInfo.input_buffer, "%u", &option);

                if ((option < ClxBleWhitelist_AddDevice) || (option > ClxBleWhitelist_RemoveAllDevices))
                {
                    clxConsoleUIEngineText("\nPlease enter the valid option as either 1 or 2 or 3");
                }
                else
                {
                    if (ClxBleWhitelist_AddDevice == option)
                    {
                        /**
                        Adds a remote device to the white list present in the controller in order to allow advertising packets
                        from the device
                        */
                        ret = clxGapBleManageWhiteList(stack, ClxBleWhiteListOperation_Add, &centralInfo.gattClient[centralInfo.activeClientIndex].peerDeviceAddress, gBlock);
                        clxConsoleUIEngineText("\nAdd white list: status - %s\n", clxGetErrorCodeText(ret));
                    }
                    else if (ClxBleWhitelist_RemoveDevice == option)
                    {
                        /**
                        Remove the remote device from the white list present in the controller.
                        */
                        ret = clxGapBleManageWhiteList(stack, ClxBleWhiteListOperation_Remove, &centralInfo.gattClient[centralInfo.activeClientIndex].peerDeviceAddress, gBlock);
                        clxConsoleUIEngineText("\nRemove White list: status - %s\n", clxGetErrorCodeText(ret));
                    }
                    else
                    {
                        /**
                        Removes all devices from white list stored in the controller.
                        */
                        ret = clxGapBleManageWhiteList(stack, ClxBleWhiteListOperation_Clear, NULL, gBlock);
                        clxConsoleUIEngineText("\nClear White list: status - %s\n", clxGetErrorCodeText(ret));
                    }
                }

                break;
            }

            case BleCentralMenuItem_GetBatteryLevel:
            {
                ClxHandle gatt = getGattClientHandle();
                u1  readbuffer = 0;
                u2  handle     = GetValueHandle(gatt, CLX_GATT_SERVICE_BATTERY_SERVICE_UUID, CLX_GATT_SERVICE_BATTERY_SERVICE_CHARACTERISTIC_BATTERY_LEVEL_UUID);
               
                ret=clxBleGattGetBatteryLevel(gatt, handle, &readbuffer, gBlock);
                if (CLX_SUCCESS == ret)
                {
                    clxConsoleUIEngineText("\nBattery Level: %02x%%\n",readbuffer);
                }
                              
                break;
            }

            case BleCentralMenuItem_GetDeviceInformation:
            {
                /*Get Manufacture Name*/
                clxGetDeviceInfo(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_UUID);
                
                /*Get Device Model Number*/
                clxGetDeviceInfo(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_UUID);
                
                /*Get Device Serial Number*/
                clxGetDeviceInfo(CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_UUID);
                
                break;
            }
            
            case BleCentralMenuItem_GATT:
            {
                bleCentralGATTMenu();
                break;
            }

            case BleCentralMenuItem_DeletePairedDevice:
            {
                clxConsoleUIEngineInputBox("Enter the option 1 - Delete all devices, 2 - Delete a particular device", centralInfo.input_buffer, 128);
                u4 option;
                (void)sscanf(centralInfo.input_buffer, "%u", &option);

                if ((option < ClxBleDeletePairedDevice_DeleteAllDevices) || (option > ClxBleDeletePairedDevice_DeleteaParticularDevice))
                {
                    clxConsoleUIEngineText("\nPlease enter the valid option as either 1 or 2");
                }
                else
                {
                    if (ClxBleDeletePairedDevice_DeleteAllDevices == option)
                    {
                        ret = clxGapBleDeleteAllPairedDevicesInfo(stack, gBlock);
                        clxConsoleUIEngineText("\nclxGapBleDeleteAllPairedDevicesInfo complete with result %s\n", clxGetErrorCodeText(ret));
                    }
                    else
                    {
                        ClxBleBdAddress* device = showPairedDeviceList(stack);
                        if (device)
                        {
                            clxConsoleUIEngineText("\nDeleting pairing info to the device address Type[%d], using the GATT client %u\n", device->addressType, centralInfo.activeClientIndex);

                            ret = clxGapBleDeletePairedDeviceInfo(stack, device, gBlock);
                            clxConsoleUIEngineText("\nclxGapBleDeletePairedDeviceInfo complete with result %s\n", clxGetErrorCodeText(ret));
                        }
                    }
                }
               
                break;
            }
      
#if defined( CLX_BLE_SERVICE_EXTENDED_API )
            case BleCentralMenuItem_BleServicesMenu:
            {
                clxBleServicesMenu( stack, getGattClientHandle() );
            }
            break;
#endif /* defined( CLX_BLE_SERVICE_EXTENDED_API ) */

            case BleCentralMenuItem_ReturnToPreviousMenu:
            {
                return;
            }

            default:
            {
                clxConsoleUIEngineText("\nPlease select a valid menu option..\n");
                break;
            }
        } // switch (index)
    } // while (TRUE)
}

/***************************************************************************************************************************************
*                                                getGattClientInstanceInfo
*
* Get Gatt Client Instance Information
*
* return   ClxCentralInstanceInfo
*
****************************************************************************************************************************************/
ClxCentralInstanceInfo* getGattClientInstanceInfo ( void )
{
    return &centralInfo;
}

/***************************************************************************************************************************************
*                                                bleCentralReadAllCharacteristicsValue
*
* Reads all characteristics values
*
****************************************************************************************************************************************/
ClxResult bleCentralReadAllCharacteristicsValue (void)
{
    ClxResult ret = CLX_FAIL;
    
    /* Active GATT Client */
    GattClient *gattClient = &centralInfo.gattClient[centralInfo.activeClientIndex];
    
    ClxGattServiceDetail sd;

    /* Maximum size of service details which is store in the user defined buffer */
    u2 listSize = sizeof(gattClient->serviceList)/sizeof(ClxGattServiceDetail);

    u1* readBuf = (u1*)&centralInfo.input_buffer;
    u4 readLength = 0;

    /* Discovers all registered services */
    ret = clxGattClientGetListOfServices(gattClient->handle,        /* gatt             */
                                         NULL,                      /* uuid             */
                                         listSize,                  /* listSize         */
                                         gattClient->serviceList,   /* list             */
                                         &gattClient->noOfService,  /* numberOfServices */
                                         gBlock);                   /* block            */
    
    for (u1 serviceIndex = 0; serviceIndex < gattClient->noOfService; serviceIndex++)
    {
        memset(&sd, 0, sizeof(sd));
        
        /* First handle shall be the handle from which the services of those would be discovered */
        sd.firstHandle = gattClient->serviceList[serviceIndex].firstHandle;
        
        /* Last handle shall be the handle till which the services of those would be discovered */
        sd.lastHandle = gattClient->serviceList[serviceIndex].lastHandle;
        
        /* Maximum size of characteristics details that can be stored in the user defined buffer */
        listSize = sizeof(gattClient->characteristicList) / sizeof(ClxGattCharacteristicDetail);
        
        /* Discovers all characteristics of a service */
        ret = clxGattClientDiscoverCharacteristics(getGattClientHandle(),
                                                   NULL,
                                                   &sd,
                                                   listSize,
                                                   gattClient->characteristicList,
                                                   &gattClient->noOfCharacteristics,
                                                   gBlock);
        
        for (u4 characteristicIndex = 0; characteristicIndex < gattClient->noOfCharacteristics; characteristicIndex++)
        {
            ret = clxGattClientRead(getGattClientHandle(),
                                    gattClient->characteristicList[characteristicIndex].valueHandle,
                                    readBuf,
                                    MAX_INPUT_SIZE,
                                    0,
                                    &readLength,
                                    TRUE);
            if (CLX_SUCCESS == ret)
            {
                if (ClxGattUuidType_Uuid2 == gattClient->characteristicList[characteristicIndex].uuid.type)
                {
                    clxConsoleUIEngineText("\n Data of Uuid %02x\n", gattClient->characteristicList[characteristicIndex].uuid.value[0]);

                    for (u4 loop = 0; loop < readLength; loop++)
                    {
                        clxConsoleUIEngineText("%02x ", readBuf[loop]);
                    }
                }
            }
        }
    }
    
    return ret;
}

/***************************************************************************************************************************************
*                                                bleCentralEnableNotificationForAllCharacteristics
*
* Enables the notification for BLE audio services
*
****************************************************************************************************************************************/
ClxResult bleCentralEnableNotificationForAllCharacteristics (u2 serviceUuid)
{
    ClxResult ret = CLX_FAIL;
    
    /* Active GATT Client */
    GattClient *gattClient = &centralInfo.gattClient[centralInfo.activeClientIndex];
    
    ClxGattServiceDetail sd;
    
    ClxGattUuid uuid;
    clxInitGattUuid2(&uuid, serviceUuid);
    
    /* Maximum size of service details which is store in the user defined buffer */
    u2 listSize = sizeof(gattClient->serviceList)/sizeof(ClxGattServiceDetail);
    
    /* Discovers all registered services */
    ret = clxGattClientGetListOfServices(gattClient->handle,        /* gatt             */
                                         &uuid,                     /* uuid             */
                                         listSize,                  /* listSize         */
                                         gattClient->serviceList,   /* list             */
                                         &gattClient->noOfService,  /* numberOfServices */
                                         gBlock);                   /* block            */

    if (!gattClient->noOfService)
    {
        clxConsoleUIEngineText("\nDiscovering the service for uuid %02x is failed with error %s\n", serviceUuid, clxGetErrorCodeText(ret));
        return ret;
    }
    
    memset(&sd, 0, sizeof(sd));
    
    /* First handle shall be the handle from which the services of those would be discovered */
    sd.firstHandle = gattClient->serviceList[0].firstHandle;
    
    /* Last handle shall be the handle till which the services of those would be discovered */
    sd.lastHandle = gattClient->serviceList[0].lastHandle;
    
    /* Maximum size of characteristics details that can be stored in the user defined buffer */
    listSize = sizeof(gattClient->characteristicList) / sizeof(ClxGattCharacteristicDetail);
    
    /* Discovers all characteristics of a service */
    ret = clxGattClientDiscoverCharacteristics(getGattClientHandle(),
                                               NULL,
                                               &sd,
                                               listSize,
                                               gattClient->characteristicList,
                                               &gattClient->noOfCharacteristics,
                                               gBlock);
    
    if (!gattClient->noOfCharacteristics)
    {
        clxConsoleUIEngineText("\nDiscovering the characteristics for the service uuid %02x is failed with error %s\n", serviceUuid, clxGetErrorCodeText(ret));
        return ret;
    }
    
    for (u4 characteristicIndex = 0; characteristicIndex < gattClient->noOfCharacteristics; characteristicIndex++)
    {
        /* Now we search for descriptors: */
        listSize = sizeof(gattClient->descriptorList)/sizeof(ClxGattCharacteristicDescriptorDetail);
        
        ret = clxGattClientDiscoverCharacteristicDescriptors( getGattClientHandle(),
                                                              &gattClient->characteristicList[characteristicIndex],
                                                              listSize,
                                                              gattClient->descriptorList,
                                                              &gattClient->noOfDescriptor,
                                                              gBlock );
        
        for (u4 i = 0; i < gattClient->noOfDescriptor; i++)
        {
            if (gattClient->descriptorList[i].uuid.value[0] == CLX_GATT_CHARACTERISTIC_CLIENT_CONFIG_DESCRIPTOR_UUID)
            {
                /* Register for characteristics notification */
                ret = clxGattClientConfigureCharacteristic(getGattClientHandle(),
                                                           &gattClient->descriptorList[i],
                                                           CLX_GATT_CLENT_CONFIGURATION_BIT_NOTIFY,
                                                           gBlock);
                
                if (CLX_SUCCESS != ret)
                {
                    clxConsoleUIEngineText("\nclxGattClientConfigureCharacteristic: status - %s\n", clxGetErrorCodeText(ret));
                }
            }
        }
        
    }
    
    return ret;
}

/***************************************************************************************************************************************
*                                                bleCentralDiscoverAllPrimaryServices
*
* Discover All Primary Services from remote device
*
* \param serviceUuid The UUID of services to be retrieved. If set to NULL, all services of the remote GATT server will be retrieved.
*
****************************************************************************************************************************************/
ClxResult bleCentralDiscoverAllPrimaryServices ( const ClxGattUuid* serviceUuid, boolean bPrintFlag )
{
    ClxResult ret = CLX_FAIL;

    /* 
    Variable to store the retrieved total number of services from server upon successful 
    completion of clxGattClientGetListOfServices(..)
    */
    u2 numberOfServices = 0;

    /* Active GATT Client */
    GattClient *gattClient = &centralInfo.gattClient[centralInfo.activeClientIndex];

    /**
    Maximum size of service details which is store in the user defined buffer.
    */
    u2 listSize = sizeof(gattClient->serviceList)/sizeof(ClxGattServiceDetail);

    /**
    Discovers all registered services on a server returning attribute handles and attribute values corresponding 
    to the services supported by server.
    */
    ret = clxGattClientGetListOfServices(gattClient->handle,        /* gatt             */
                                         serviceUuid,               /* uuid             */
                                         listSize,                  /* listSize         */
                                         gattClient->serviceList,   /* list             */
                                         &gattClient->noOfService,  /* numberOfServices */
                                         gBlock);                   /* block            */

    numberOfServices = gattClient->noOfService;

    if (ret == CLX_SUCCESS)
    {
        if (bPrintFlag)
        {
            clxConsoleUIEngineText("The number of services found: %u\n", numberOfServices);

            for (u1 i = 0; i < numberOfServices; i++)
            {
                if (gattClient->serviceList[i].uuid.type == ClxGattUuidType_Uuid2)
                {
                    clxConsoleUIEngineText("\n%u: First Handle: %#x Last Handle: %#x Uuid: %#x", i,
                                                                gattClient->serviceList[i].firstHandle,
                                                                gattClient->serviceList[i].lastHandle,
                                                                (gattClient->serviceList[i].uuid.value[0]));
#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
                    u2 serviceUUid = (u2)(gattClient->serviceList[i].uuid.value[0]);
    
                    clxConsoleUIEngineText(" Name: %s", getServiceName(serviceUUid));
#endif /* defined(CLX_BLE_GATT_SERVICE_VERBOSE) */
    
                }
                else
                {
                    clxConsoleUIEngineText("\n%u: First Handle: %#x Last Handle: %#x Uuid: %#x%x%x%x", i,
                                                                gattClient->serviceList[i].firstHandle, 
                                                                gattClient->serviceList[i].lastHandle,
                                                                (gattClient->serviceList[i].uuid.value[0]),
                                                                (gattClient->serviceList[i].uuid.value[1]),
                                                                (gattClient->serviceList[i].uuid.value[2]),
                                                                (gattClient->serviceList[i].uuid.value[3]));
                }
            }
        }
    }
    else
    {
        clxConsoleUIEngineText("clxGattClientGetListOfServices failed with error %s\n", clxGetErrorCodeText(ret));
    }

    return ret;
}

/***************************************************************************************************************************************
*                                                bleCentralDiscoverAllCharacteristics
*
* Discover All Characteristics from remote device
*
* \param charUuid    The UUID of characteristic to be retrieved. If set to NULL, all characteristic of the remote GATT server will be retrieved.
* \param serviceUuid Services Index to be retrieved the services info from Gatt structure.
*
****************************************************************************************************************************************/
ClxResult bleCentralDiscoverAllCharacteristics ( const ClxGattUuid* charUuid, u4 serviceIndex )
{
    ClxResult ret = CLX_FAIL;
    ClxGattServiceDetail sd;
    memset(&sd, 0, sizeof(sd));

    if (serviceIndex >= MAX_NUM_SERVICES)
    {
        serviceIndex = MAX_NUM_SERVICES - 1;
    }

    /* Active GATT Client */
    GattClient* gattClient = &centralInfo.gattClient[centralInfo.activeClientIndex];

    /**
    First handle shall be the handle from which the services of those would be discovered
    */
    sd.firstHandle = gattClient->serviceList[serviceIndex].firstHandle;

    /**
    Last handle shall be the handle till which the services of those would be discovered
    */
    sd.lastHandle = gattClient->serviceList[serviceIndex].lastHandle;

    /**
    Maximum size of characteristics details that can be stored in the user defined buffer.
    */
    u2 listSize = sizeof(gattClient->characteristicList) / sizeof(ClxGattCharacteristicDetail);

    /**
    Variable returning the retrieved characteristics count from server upon successful completion of 
    clxGattClientDiscoverCharacteristics(..).
    */
    u2 noOfCharacteristics = 0;

    /**
    Discovers all characteristics of a service in the server and get the list of attribute handle - value 
    pairs corresponding to the characteristics in the service definition.
    */
    ret = clxGattClientDiscoverCharacteristics(getGattClientHandle(),
                                               charUuid,
                                               &sd,
                                               listSize,
                                               gattClient->characteristicList,
                                               &gattClient->noOfCharacteristics,
                                               gBlock);

    noOfCharacteristics = gattClient->noOfCharacteristics;

    if ( CLX_SUCCESS == ret )
    {
        clxConsoleUIEngineText("The number of characteristics found: %u\n", noOfCharacteristics);

        for (u4 i = 0; i < noOfCharacteristics; i++)
        {
            if (gattClient->characteristicList[i].uuid.type == ClxGattUuidType_Uuid2)
            {
                clxConsoleUIEngineText("\n%u: Value Handle: %#x Properties: %u Uuid: %#x",
                    i,
                    gattClient->characteristicList[i].valueHandle,
                    gattClient->characteristicList[i].properties,
                    (gattClient->characteristicList[i].uuid.value[0]));

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
                clxConsoleUIEngineText(" Name: %s",
                            getCharacteristicName((u2)(gattClient->serviceList[serviceIndex].uuid.value[0]),
                                                  (u2)(gattClient->characteristicList[i].uuid.value[0])));
#endif /* defined(CLX_BLE_GATT_SERVICE_VERBOSE) */

            }
            else
            {
                clxConsoleUIEngineText("\n%u: Value Handle: %#x Properties: %u Uuid: %#x%x%x%x",
                    i,
                    gattClient->characteristicList[i].valueHandle,
                    gattClient->characteristicList[i].properties,
                    (gattClient->characteristicList[i].uuid.value[0]),
                    (gattClient->characteristicList[i].uuid.value[1]),
                    (gattClient->characteristicList[i].uuid.value[2]),
                    (gattClient->characteristicList[i].uuid.value[3]));
            }
        }
    }
    else
    {
        clxConsoleUIEngineText("clxGattDiscoverCharacteristics failed with error %s\n", clxGetErrorCodeText(ret));
    }

    return ret;
}

/***************************************************************************************************************************************
*                                                bleCentralEnableNotification
*
* Enable the notification for the user selected characteristics
*
****************************************************************************************************************************************/
ClxResult bleCentralEnableNotification ( u4 characteristicIndex )
{
    ClxResult ret = CLX_FAIL;

    GattClient* gattClient = getGattClientHandleInfo();

    if (characteristicIndex >= MAX_NUM_CHARACTERISTIC_LIST)
    {
        characteristicIndex = MAX_NUM_CHARACTERISTIC_LIST - 1;
    }

    if ((gattClient->characteristicList[characteristicIndex].properties & CLX_GATT_CHARACTERISTIC_PROPERTY_NOTIFY) == 0)
    {
        clxConsoleUIEngineText("The characteristic does not support notifications\n");
    }
    else
    {
        /* Now we search for descriptors: */
        u2 listSize = sizeof(gattClient->descriptorList)/sizeof(ClxGattCharacteristicDescriptorDetail);
        u2 noOfDescriptor = 0;

        ret = clxGattClientDiscoverCharacteristicDescriptors( getGattClientHandle(),
                                                              &gattClient->characteristicList[characteristicIndex],
                                                              listSize,
                                                              gattClient->descriptorList,
                                                              &gattClient->noOfDescriptor,
                                                              gBlock );

        noOfDescriptor = gattClient->noOfDescriptor;

        clxConsoleUIEngineText("\nclxGattClientDiscoverCharacteristicDescriptors: status - %s\n", clxGetErrorCodeText(ret));

        if (ret == CLX_SUCCESS)
        {
            for (u4 i = 0; i < noOfDescriptor; i++)
            {
                if (gattClient->descriptorList[i].uuid.value[0] == CLX_GATT_CHARACTERISTIC_CLIENT_CONFIG_DESCRIPTOR_UUID)
                {
                    /**
                    Registers with server to get notifications for the user selected characteristics index descriptor. Notification can be configured only on the
                    client characteristic configuration descriptors.
                    */
                    ret = clxGattClientConfigureCharacteristic(getGattClientHandle(),
                                                               &gattClient->descriptorList[i],
                                                               CLX_GATT_CLENT_CONFIGURATION_BIT_NOTIFY,
                                                               gBlock);

                    clxConsoleUIEngineText("\nclxGattClientConfigureCharacteristic: status - %s\n", clxGetErrorCodeText(ret));
                }
            }
        }
    }

    return ret;
}

/***************************************************************************************************************************************
*                                                clxGetDeviceNameFilteringOption
*
* Retrieves the current status of the device name filtering option.
*
****************************************************************************************************************************************/
boolean clxGetDeviceNameFilteringOption ( void )
{
    return clxDeviceNameFilteringOption;
}

/***************************************************************************************************************************************
*                                                clxSetDeviceNameFilteringOption
*
* Sets the device name filtering option based on user input.
*
****************************************************************************************************************************************/
void clxSetDeviceNameFilteringOption ( void )
{
    clxConsoleUIEngineInputBox("\nSelect device filtering option: [0 - Accept all devices / 1 - Exclude devices without name]: ", centralInfo.input_buffer, 128);

    clxDeviceNameFilteringOption = (boolean)atoi(centralInfo.input_buffer);
}


/*******************************************************************************************************************************
*                                                   getGattClientHandle
*
* Get the GATT profile handle with client role on local device.
*
*******************************************************************************************************************************/
ClxHandle getGattClientHandle(void)
{
    return (centralInfo.gattClient[centralInfo.activeClientIndex].handle);
}

GattClient* getGattClientHandleInfo(void)
{
    return (&centralInfo.gattClient[centralInfo.activeClientIndex]);
}

ClxBleConnectionHandle getGattClientConnectionHandle(void)
{
    return (centralInfo.gattClient[centralInfo.activeClientIndex].connectionHandle);
}

ClxHandle clxBleCheckGattClientHandleAvailability( ClxHandle inputHanlde )
{
    if( FALSE == centralInfo.isBleCentralInitialized || NULL == inputHanlde )
    {
        return CLX_BLE_INVALID_HANDLE;
    }

    if( inputHanlde == centralInfo.gattClient[centralInfo.activeClientIndex].handle)
    {
        return (centralInfo.gattClient[centralInfo.activeClientIndex].handle);
    }

    for( int i = 0; i < MAX_NUMBER_OF_HANDLES; ++i )
    {
        if( inputHanlde == centralInfo.gattClient[i].handle)
        {
            return (centralInfo.gattClient[i].handle);
        }
    }

    return CLX_BLE_INVALID_HANDLE;
}


/*******************************************************************************************************************************
*                                                   clxGetDeviceInformation
*
* Get and display a specific Device Information characteristic from the remote GATT server.
*
*******************************************************************************************************************************/
void clxGetDeviceInfo(u2 characteristicUuidValue)
{
    ClxHandle gatt  = getGattClientHandle();
    u2 serviceUuid  = CLX_GATT_SERVICE_DEVICE_INFORMATION_UUID;
    u2 handle       = GetValueHandle(gatt, serviceUuid, characteristicUuidValue);
    u1* readbuffer  = (u1*)&centralInfo.input_buffer;
    u4 bufferLength = 0;
    ClxResult ret   = CLX_ERROR;

    switch (characteristicUuidValue)
    {
        case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MANUFACTURER_NAME_STRING_UUID:
        {
            ret = clxGattDevInfoGetManufacturerName(gatt, handle, readbuffer, &bufferLength, TRUE);
            break;
        }

        case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_MODEL_NUMBER_STRING_UUID:
        {
            ret = clxGattDevInfoGetModelNumber(gatt, handle, readbuffer, &bufferLength, TRUE);
            break;
        }

        case CLX_GATT_SERVICE_DEVICE_INFORMATION_CHARACTERISTIC_SERIAL_NUMBER_STRING_UUID:
        {
            ret = clxGattDevInfoGetSerialNumber(gatt, handle, readbuffer, &bufferLength, TRUE);
            break;
        }
    }

    if (ret == CLX_SUCCESS)
    {
        
#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
        clxConsoleUIEngineText("%-22s :", getCharacteristicName(serviceUuid, characteristicUuidValue));
#endif /* defined(CLX_BLE_GATT_SERVICE_VERBOSE) */

        for (u4 i = 0; i < bufferLength; i++)
        {
           
            clxConsoleUIEngineText("%c", readbuffer[i]);
          
        }

        clxConsoleUIEngineText("\n");

    }
}

