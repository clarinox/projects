/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                mainBlePeripheral.cpp
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
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Server.Api.h"

#include "mainBluetooth.h"
#include "GattServer.h"
#include "Gatt.Ble.Includes.h"

#include "Gap.Ble.Bonding.Api.h"
#include "GapBleApp.h"
#include "GattApp.h"

#if defined( CLX_BLE_SERVICE_EXTENDED_API )
#include "BleServiceCommon.h"
#endif /* defined( CLX_BLE_SERVICE_EXTENDED_API ) */

#include <stdio.h>
#include <stdlib.h>


/**
Maximum data length of an advertising set. Obtained and updated from the Capabilities API
*/
u2 maxDataLengthOfAdvSet = MAX_INPUT_SIZE;

/**
Initial maximum number of advertising sets
*/
#define INITIAL_MAX_NUMBER_OF_ADVERTISING_SETS          2

/**
Maximum number of controller supported advertising sets. Obtained and updated from the Capabilities API
*/
u1 maxAdvertisingSets = INITIAL_MAX_NUMBER_OF_ADVERTISING_SETS;

/**
Array to get console input operations from user
*/
s1 inputValue[MAX_INPUT_SIZE];

/**
To maintain the Extended Advertising Handles
*/
ClxBleExtendedAdvertisingHandle  extendedAdvertisingHandle         = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;
ClxBleExtendedAdvertisingHandle  periodicExtendedAdvertisingHandle = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;

/* Menu options used to invoke BlePeripheral main menu */
typedef enum BlePeripheralMenuItemEnum
{
    BlePeripheralMenuItem_StartAdvertising              = 1,
    BlePeripheralMenuItem_StopAdvertising,
    BlePeripheralMenuItem_WriteLocalCharacteristics,
    BlePeripheralMenuItem_ReadLocalCharacteristics,
#if defined(CLX_OOB_PAIRING_SUPPORT)
    BlePeripheralMenuItem_GenerateOobKeys,
    BlePeripheralMenuItem_EnableDisableOobPairing,
#endif
    BlePeripheralMenuItem_InitiateLegacyPairing,
    BlePeripheralMenuItem_InitiateSecurePairing,
    BlePeripheralMenuItem_DiconnectFromPairedDevice,
    BlePeripheralMenuItem_GetCurrentConnectionDetails,
    BlePeripheralMenuItem_DeleteOldPairingInformation,
    BlePeripheralMenuItem_DeleteAllPairedDevices,
    BlePeripheralMenuItem_ChangeConnectionParameters,
#if defined( CLX_BLE_SERVICE_EXTENDED_API )
    BlePeripheralMenuItem_BleServicesMenu,
#endif /* defined( CLX_BLE_SERVICE_EXTENDED_API ) */
    BlePeripheralMenuItem_ReturnToPreviousMenu,
    BlePeripheralMenuItem_TotalItems
}BlePeripheralMenuItem;

/**
Local Bluetooth Device name
*/
const s1* longName   = "ClxBleCustomServicePeripheral";

/* 
Variables associated with LE Peripheral object 
*/
typedef struct ClxPeripheralInstanceInfoStruct
{
    s1          message[128];                   /* Buffer to get console input                                          */
    ClxSize     readSize;                       /* Length of the read local characteristic value                        */
    ClxHandle   gattHandle;                     /* Local gatt server handle                                             */
    boolean     isBlePeripheralInitialized;     /* Indicate if the classic part of stack init are initialized or not    */

    ClxBleConnectionHandle  connectionHandle;   /* Variable to store the value of remote device connection handle       */
    ClxBleAdvertisingData   advertisingData;    /* Buffer for local device advertising data                             */
    ClxBleAdvertisingData   scanResponseData;   /* Buffer for local device advertising scan response data               */
    ClxBleBdAddress         remoteDeviceAddress;/* Remote device address for future reference                           */

#if defined(WHITE_LIST_SUPPORT)
    ClxBleBdAddress         whiteListAddress;   /* BD address of white listed device                                    */
#endif
}ClxPeripheralInstanceInfo;

/* Structure with variables required for LE Peripheral instance */
ClxPeripheralInstanceInfo peripheralInfo = {};

ClxBleExtendedAdvertisingData advBufferObj = { };

/* Initialize and add the local device custom data like device name, service UUID, manufacturer data, etc */
void initAdvertisingData(const s1* deviceName);

/* Advertise data and make local device discoverable or connectable mode using API clxGapBleStartAdvertising(..) */
void startBleAdvertising(ClxStack stack);

/* 
This call-back function is called if any events raised by GAP profile causes this call-back function executed 
with the associated event and parameters
*/
boolean blePeripheralMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);

/* Menu to display Bluetooth Low Energy Peripheral role related menu options */
void lowEnergyPeripheralMenu(ClxStack stack, const s1* deviceName);

/* Initializes ClarinoxBlue BLE Peripheral profiles with configuration parameters for Bluetooth stack. */
void initializeBlePeripheral(ClxStack stack);

/* De-Initializes ClarinoxBlue BLE Peripheral profiles and resources. */
void terminateBlePeripheral();

/****************************************************************************************************************************************
*                                                      initAdvertisingData
*
* Initialize and add the local device custom data like device name, service UUID, manufacturer data, etc
*
****************************************************************************************************************************************/
void initAdvertisingData(const s1* deviceName)
{
#if defined(CLX_BLE_CS_REFLECTOR)
    u2 rangingServiceUuid = 0x185B;     //Ranging service uuid
#endif

    /* Shortened Local Name */
    clxBleInitAdvertisingData(&peripheralInfo.advertisingData);
    clxBleAddAdvertisingDataField(&peripheralInfo.advertisingData, 8, (u1*)deviceName, (u1)strlen(deviceName));

    /*AD type flag*/
    u1 flagAdvData = CLX_BLE_AD_FLAG_GENERAL_DISCOVERABLE_MODE;

#if defined(CLX_BLE_CS_REFLECTOR)
    flagAdvData |= CLX_BLE_AD_FLAG_BR_EDR_NOT_SUPPORTED;
#endif

    clxBleAddAdvertisingDataField(&peripheralInfo.advertisingData, CLX_BLE_GAP_AD_TYPE_FLAG, (u1*)&flagAdvData, (u1)sizeof(flagAdvData));

#if defined(CLX_BLE_CS_REFLECTOR)
    /* Ranging Service */
    clxBleAddAdvertisingDataField(&peripheralInfo.advertisingData, CLX_BLE_GAP_AD_TYPE_INCOMPLETE_LIST_OF_16_BIT_SERVICE_UUID, (u1*)&rangingServiceUuid, (u1)sizeof(rangingServiceUuid));
#endif

    /* Complete Local Name */
    clxBleInitAdvertisingData(&peripheralInfo.scanResponseData);
    clxBleAddAdvertisingDataField(&peripheralInfo.scanResponseData, 9, (u1*)longName, (u1)strlen(longName));
}

/****************************************************************************************************************************************
*                                                       startBleAdvertising
*
* Advertise data and make local device discoverable or connectable mode using API clxGapBleStartAdvertising(..)
*
* \param stack  - Local device stack handle.
*
****************************************************************************************************************************************/
void startBleAdvertising(ClxStack stack)
{
    /**
    Configure the advertising filter policy so that anyone can scan and connect to
    */
    ClxBleAdvertisingFilterPolicy filter_policy = ClxBleAdvertisingFilterPolicy_ScanConnectionAnyone;
    ClxBleBdAddress* peerAddress = (ClxBleBdAddress*) clxAppAllocZero (sizeof(ClxBleBdAddress));

    memset(peerAddress, 0, sizeof(ClxBleBdAddress));

#if defined(WHITE_LIST_SUPPORT)
    clxConsoleUIEngineInputBox ("Press 1 to be connectable by any device or 2 by only white list device: ", peripheralInfo.message, 128);
    u4 index = atoi(peripheralInfo.message);
    
    if (index == 2)
    {
        /**
        Configure advertising filter policy so that only the white listed devices would be able to scan and connect to
        */
        filter_policy = ClxBleAdvertisingFilterPolicy_ScanWhitelistConnectionWhitelist;

        peerAddress->addressType = peripheralInfo.whiteListAddress.addressType;
        memcpy(peerAddress->value, peripheralInfo.whiteListAddress.value, 6);
    }
#endif /* defined(WHITE_LIST_SUPPORT) */

    ClxResult ret = clxGapBleStartAdvertising(stack,
                                              3000,
                                              4000,
                                              ClxBleAdvertisingType_ConnectableUndirected,
                                              ClxBleOwnAddressMode_Identity,
                                              peerAddress,
                                              CLX_BLE_ALL_ADVERTISING_CHANNELS,
                                              filter_policy,
                                              &peripheralInfo.advertisingData,
                                              gBlock);

    if (ret == CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nStart Advertising Success\n");

        ret = clxGapBleSetScanResponseData(stack, &peripheralInfo.scanResponseData, TRUE);

        if (ret == CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nAdvertising the Scan Response Data Success\n");
        }
        else
        {
            clxConsoleUIEngineText("\nAdvertising the Scan Response Data failed with error: %s\n", clxGetErrorCodeText(ret));
        }
    }
    else
    {
        clxConsoleUIEngineText("\nStart Advertising failed with error: %s\n", clxGetErrorCodeText(ret));
    }

    delete peerAddress;
}

/*******************************************************************************************************************************
*                                                blePeripheralMessageHandler
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
boolean blePeripheralMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    /**
    These (below indications with *_COMPLETE) are command complete indications received when the execution of corresponding API commands
    are completed. The command complete indications are received only when the API has been called in non-blocking mode. 
    The output parameters can be accessed from argument "params".
    */
    if (messageID == CLX_GAP_BLE_START_ADVERTISING_COMPLETE)
    {
        clxConsoleUIEngineText("\nStart Advertising command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
        return TRUE;
    }
    else if (messageID == CLX_GAP_BLE_STOP_ADVERTISING_COMPLETE)
    {
        clxConsoleUIEngineText("\nStop Advertising command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
        return TRUE;
    }
    else if (messageID == CLX_GAP_BLE_SET_SCAN_RESPONSE_DATA_COMPLETE)
    {
        clxConsoleUIEngineText("\nSet Scan Response Data command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
        return TRUE;
    }
    /**
    Indicates when physical link (ACL)connection has been established successfully by Central device.
    */
    else if (messageID == CLX_GAP_BLE_CONNECTION_ESTABLISHED_BY_REMOTE_CENTRAL_INDICATION)
    {
        ClxGapBleConnectionEstablishedByRemoteCentralIndication* arg = (ClxGapBleConnectionEstablishedByRemoteCentralIndication*)params;

        /**
        Remote device connection details are stored for future use in GATT server API commands.
        */
        peripheralInfo.connectionHandle = arg->connectionDetails.connectionHandle;
        memcpy (peripheralInfo.remoteDeviceAddress.value, arg->connectionDetails.remoteDeviceAddr.value, 6);
        peripheralInfo.remoteDeviceAddress.addressType = arg->connectionDetails.remoteDeviceAddr.addressType;

        clxConsoleUIEngineText("Connection established to %02X%02X%02X%02X%02X%02X\n",
                                                    arg->connectionDetails.remoteDeviceAddr.value[0],
                                                    arg->connectionDetails.remoteDeviceAddr.value[1],
                                                    arg->connectionDetails.remoteDeviceAddr.value[2],
                                                    arg->connectionDetails.remoteDeviceAddr.value[3],
                                                    arg->connectionDetails.remoteDeviceAddr.value[4],
                                                    arg->connectionDetails.remoteDeviceAddr.value[5]);
        /**
        Adds the device to controller's white list if white list feature is supported.
        */  
#if defined(WHITE_LIST_SUPPORT)
        clxConsoleUIEngineText ("\nPlease confirm to add white list?");
        s1 ch = clxConsoleUIEngineMessageBox("", "yYnN", 4);

        if ((ch == 'y') || (ch == 'Y'))
        {
            memcpy (peripheralInfo.whiteListAddress.value, arg->connectionDetails.remoteDeviceAddr.value, 6);
            peripheralInfo.whiteListAddress.addressType = arg->connectionDetails.remoteDeviceAddr.addressType;
            ClxResult ret = clxGapBleManageWhiteList(stack, ClxBleWhiteListOperation_Add, &peripheralInfo.whiteListAddress, FALSE);
            if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
            {
                clxConsoleUIEngineText("\nclxGapBleManageWhiteList command failed with the result: %s\n", clxGetErrorCodeText(ret));
            }
        }
#endif /* defined(WHITE_LIST_SUPPORT) */

        return TRUE;
    }
    /**
     This indication denotes connection disconnected by remote device.
    */
    else if (messageID == CLX_GAP_BLE_LINK_DISCONNECTION_INDICATION)
    {
        ClxGapBleLinkDisconnectionIndication* arg = (ClxGapBleLinkDisconnectionIndication*)params;
        
        clxConsoleUIEngineText("\nDisconnected by remote device with the result %s", clxGetErrorCodeText(arg->reason));
        clxConsoleUIEngineText("\nConnection handle is %x", arg->connectionHandle);
        //startBleAdvertising(stack);

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
        else if (TRUE == bleGattServerMessageHandler(stack, serviceHandle, messageID, params, errorCode))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

/******************************************************************************************************************************************
*                                                       initializeBlePeripheral
*
* Initializes ClarinoxBlue BLE Peripheral profiles with configuration parameters for Bluetooth stack.
*
* \param stack    - ClarinoxBlue stack.
*
* \return void
*
******************************************************************************************************************************************/
void initializeBlePeripheral(ClxStack stack)
{
    if (FALSE == peripheralInfo.isBlePeripheralInitialized)
    {
        if (peripheralInfo.gattHandle == NULL)
        {
            /**
            Create GATT server handle for local device.
            */
            peripheralInfo.gattHandle = createGattServerHandle(stack);

            if (peripheralInfo.gattHandle)
            {
                /**
                Registers local GATT services.
                */
                registerLocalService(peripheralInfo.gattHandle, GattService_GenericAccessIndex);
                registerLocalService(peripheralInfo.gattHandle, GattService_GenericAttributeIndex);
                registerLocalService(peripheralInfo.gattHandle, GattService_CustomIndex);
                registerLocalService(peripheralInfo.gattHandle, GattService_BatteryIndex);
                //registerLocalService(peripheralInfo.gattHandle, GattService_DeviceInformationIndex);
                //registerLocalService(peripheralInfo.gattHandle, GattService_AlertNotificationIndex);
#if defined(CLX_BLE_CS_REFLECTOR)
                registerLocalService(peripheralInfo.gattHandle, GattService_RangingServiceIndex);
#endif
#if defined(CLX_BLE_HID)
                registerLocalService(peripheralInfo.gattHandle, GattService_HumanInterfaceDeviceIndex);
#endif /* defined(CLX_BLE_HID) */

#if defined(CLX_BLE_ISOCHRONOUS)
                registerLocalService(peripheralInfo.gattHandle, GattService_AudioStreamControlIndex);
                registerLocalService(peripheralInfo.gattHandle, GattService_PublishedAudioCapabilitiesIndex);
                registerLocalService(peripheralInfo.gattHandle, GattService_VolumeControlGattServiceIndex);
                registerLocalService(peripheralInfo.gattHandle, GattService_BroadcastAudioScanServiceIndex);
#endif /* defined(CLX_BLE_ISOCHRONOUS) */

                clxConsoleUIEngineText("\nGATT Server created successfully\n");
            }
            else
            {
                clxConsoleUIEngineText("\nGATT Server creation failed\n");
            }
        }
        else
        {
            clxConsoleUIEngineText("\nPeripheral is already initialized\n");
        }
    
        peripheralInfo.isBlePeripheralInitialized = TRUE;
    }
    else
    {
        clxConsoleUIEngineText("\nBLE Peripheral is already initialized\n");
    }
}

/******************************************************************************************************************************************
*                                                       terminateBlePeripheral
*
* De-Initializes ClarinoxBlue BLE Peripheral profiles and resources.
*
******************************************************************************************************************************************/
void terminateBlePeripheral()
{
    if (peripheralInfo.isBlePeripheralInitialized)
    {
        /**
        Delete the active GATT server handle before stack termination.
        */
        deleteGattServerHandle(peripheralInfo.gattHandle);

        /**
        Reset the connection handle after successfully closing GATT profile handle.
        */
        peripheralInfo.connectionHandle = 0;

        peripheralInfo.gattHandle = NULL;
        peripheralInfo.isBlePeripheralInitialized = FALSE;
    }
}

/**
Returns GATT server handle
*/
ClxHandle getGattServerHandle()
{
    return peripheralInfo.gattHandle;
}

/**
Returns whether BLE peripheral role is initialized or not
*/
boolean isBlePeripheralInitialized(void)
{
    return peripheralInfo.isBlePeripheralInitialized;
}

/**
Returns the active connection handle
*/
u2 getConnectionHandle(void)
{
    return peripheralInfo.connectionHandle;
}

/***************************************************************************************************************************************
*                                                lowEnergyPeripheralMenu
*
* Menu to display Bluetooth Low Energy Peripheral role related menu options
*
* \param stack      - ClarinoxBlue stack
* \param deviceName - Name string of the remote device
*
****************************************************************************************************************************************/
void lowEnergyPeripheralMenu(ClxStack stack, const s1* deviceName)
{
    ClxResult ret = CLX_ERROR;

    u4 advertisingFlag = FALSE;

    if (stack == NULL)
    {
        clxConsoleUIEngineText("\nClarinox Stack has to be initialized first\n");
        return;
    }

    initAdvertisingData(deviceName);

    while (TRUE)
    {
        const s1* menu = "Start Advertising\0"
                         "Stop Advertising\0"
                         "Write Local Characteristics\0"
                         "Read Local Characteristics\0"
#if defined(CLX_OOB_PAIRING_SUPPORT)
                        "Generate OOB Keys\0"
                        "Enable/Disable OOB Pairing\0"
#endif
                         "Initiate Legacy Pairing\0"
                         "Initiate Secure Pairing\0"
                         "Disconnect from paired device\0"
                         "Get current connection Details\0"
                         "Delete the oldest pairing information\0"
                         "Delete all paired devices\0"
                         "Change connection parameters\0"
#if defined( CLX_BLE_SERVICE_EXTENDED_API )
                         "BLE Service API Menu\0"
#endif /* defined( CLX_BLE_SERVICE_EXTENDED_API ) */
                         "Return to previous menu\0";

        u4 index = clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, BlePeripheralMenuItem_TotalItems - 1);

        if ((FALSE == peripheralInfo.isBlePeripheralInitialized) && (index < BlePeripheralMenuItem_ReturnToPreviousMenu))
        {
            clxConsoleUIEngineText("\nPlease make sure to initialize the BLE Peripheral first\n");
            continue;
        }

        switch (index)
        {
            case BlePeripheralMenuItem_StartAdvertising:
            {
                clxConsoleUIEngineInputBox ("Enter 1-Legacy Advertising / 2-Extended Advertising : ", inputValue, MAX_INPUT_SIZE);
                advertisingFlag = atoi(inputValue);

                if (1 == advertisingFlag)
                {
                    /**
                    Enables advertising mode. Stack starts advertising packets.
                    */
                    startBleAdvertising(stack);
                }
                else if (2 == advertisingFlag)
                {
                     clxBleGapInitExtAdvertisingBuffer(&advBufferObj);

                     /* Local device name */
                     clxBleAddExtendedAdvertisingDataField(&advBufferObj,
                                                           CLX_BLE_GAP_AD_TYPE_COMPLETE_LOCAL_DEVICE_NAME,
                                                           (u1*)clxGetBTLocalDeviceName(),
                                                           (u1)strlen(clxGetBTLocalDeviceName()));

                     bleStartExtendedAdvertising(stack, &advBufferObj, FALSE);

                    clxConsoleUIEngineText ("\nDo you want to do periodic advertising?");
                    s1 ch = clxConsoleUIEngineMessageBox("", "yYnN", 4);
                    
                    if ((ch == 'y') || (ch == 'Y'))
                    {
                        /* Now, make the advertising set a periodic one: */
                        ret = clxGapBleEnablePeriodicAdvertisingMode(stack, extendedAdvertisingHandle, 100, 200, 0, 0, 0, 0, 0, 0, TRUE);

                        if (ret != CLX_SUCCESS)
                        {
                           clxConsoleUIEngineText("\nEnabling periodic advertising failed with error %s\n", clxGetErrorCodeText(ret));
                           return;
                        }
                        
                        ret = clxGapBleSetExtendedAdvertisingData(
                                                        stack,                                             /* stack              */
                                                        extendedAdvertisingHandle,                         /* advertisingHandle  */
                                                        ClxBleAdvertisingDataType_PeriodicAdvertising,     /* dataType           */
                                                        (u1*)advBufferObj.data,                            /* data               */
                                                        (u4)advBufferObj.dataLength,                       /* dataLength         */
                                                        ClxBleAdvertisingFragmentPreference_DoNotFragment, /* fragmentPreference */
                                                        TRUE                                               /* block              */
                                                        );
                        
                        if (ret != CLX_SUCCESS)
                        {
                           clxConsoleUIEngineText("\nExtended Periodic Advertising Data failed with error %s\n", clxGetErrorCodeText(ret));
                           return;
                        }
                    }
                }
                else
                {
                    clxConsoleUIEngineText("\nInvalid Start Advertising Option\n");
                }
                break;
            }

            case BlePeripheralMenuItem_StopAdvertising:
            {
                if (1 == advertisingFlag)
                {
                    /**
                    Disables advertising mode. Stack stops advertising packets.
                    */
                    ret = clxGapBleStopAdvertising(stack, gBlock);
                    clxConsoleUIEngineText("\nclxGapBleStopAdvertising: status - %s\n", clxGetErrorCodeText(ret));
                }
                else if (2 == advertisingFlag)
                {
                    bleStopExtendedAdvertising(stack, &advBufferObj);
                }
                else
                {
                    clxConsoleUIEngineText("\nInvalid Stop Advertising Option\n");
                }
                break;
            }

            case BlePeripheralMenuItem_WriteLocalCharacteristics:
            {
                /**
                Variables to store local service details.
                */
                const u4 numberOfServices = sizeof(clxBleGattServiceList)/sizeof(ClxBleGattServiceInfo);
                s1 servicesList[numberOfServices*(MAX_SERVICE_NAME_LENGTH_VERBOSE+1)];
                u4 serviceIndex = 0;
                u4 current = 0;

                memset(servicesList, 0, sizeof(servicesList));

                for (u4 i = 0; i < sizeof(clxBleGattServiceList)/sizeof(ClxBleGattServiceInfo); i++)
                {
                    u4 length = MIN(MAX_SERVICE_NAME_LENGTH_VERBOSE, strlen(clxBleGattServiceList[i].name));

                    memcpy(servicesList + current, clxBleGattServiceList[i].name, length);
                    servicesList[current + length] = '\0';
                    current += (length + 1);
                }

                serviceIndex = clxConsoleUIEngineShowMenu("Select the service:", servicesList, numberOfServices);
                --serviceIndex;

                clxConsoleUIEngineInputBox ("Enter the characteristic handle index: ", peripheralInfo.message, 128);
                u4 handleIndex = (u4)atoi(peripheralInfo.message);

                clxConsoleUIEngineInputBox ("Enter the Hex value for the characteristic - beware: NO SIZE CHECK:", peripheralInfo.message, 128);

                u1 tempBuffer[64] = {};
                u1 length = 0;
                u4 numToRead = 0;

                for (u4 count = 0; count < strlen(peripheralInfo.message); count++)
                {
                    if ('\n' == peripheralInfo.message[count])
                    {
                        peripheralInfo.message[count] = '\0';
                    }
                }

                for (u1 loop = 0; loop < strlen(peripheralInfo.message); loop+=2)
                {
                    (void)sscanf(peripheralInfo.message + loop, "%2x", &numToRead);
                    tempBuffer[length] = (u1)numToRead;
                    length++;
                }

                /**
                Writes a value in local characteristics. when the client has configured to receive notification or indication, then the
                updated value would be sent to the registered client.
                */
                ret = clxGattWriteLocal(peripheralInfo.gattHandle, clxBleGattServiceList[serviceIndex].handleBase + (u2)handleIndex, tempBuffer, length, WRITE_TIMEOUT_VALUE, gBlock);
                clxConsoleUIEngineText("\nclxGattWriteLocal: status - %s\n", clxGetErrorCodeText(ret));
                break;
            }

            case BlePeripheralMenuItem_ReadLocalCharacteristics:
            {
                /**
                Variables to store local service details.
                */
                const u4 numberOfServices = sizeof(clxBleGattServiceList)/sizeof(ClxBleGattServiceInfo);
                s1 servicesList[numberOfServices*(MAX_SERVICE_NAME_LENGTH_VERBOSE+1)];
                u4 serviceIndex = 0;
                u4 current = 0;

                memset(servicesList, 0, sizeof(servicesList));

                for (u4 i = 0; i < sizeof(clxBleGattServiceList)/sizeof(ClxBleGattServiceInfo); i++)
                {
                    u4 length = MIN(MAX_SERVICE_NAME_LENGTH_VERBOSE, strlen(clxBleGattServiceList[i].name));

                    memcpy(servicesList + current, clxBleGattServiceList[i].name, length);
                    servicesList[current + length] = '\0';
                    current += (length + 1);
                }

                serviceIndex = clxConsoleUIEngineShowMenu("Select the service:", servicesList, numberOfServices);
                --serviceIndex;

                clxConsoleUIEngineInputBox ("Enter the characteristic handle index: ", peripheralInfo.message, 128);
                u4 handleIndex = (u4)atoi(peripheralInfo.message);

                clxConsoleUIEngineInputBox ("Enter the max size to read:", peripheralInfo.message, 128);
                u4 size;
                (void)sscanf(peripheralInfo.message, "%u", &size);

                u1* readBuf = (u1*)&peripheralInfo.message;

                /**
                Reads local characteristic value
                */
                ret = clxGattReadLocal(peripheralInfo.gattHandle, clxBleGattServiceList[serviceIndex].handleBase + (u2)handleIndex, readBuf, size, &peripheralInfo.readSize, gBlock);

                if (ret == CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("Read Completed Successfully: %u bytes\nData: ", peripheralInfo.readSize);

                    for(u4 i = 0; i < peripheralInfo.readSize; i++)
                    {
                        clxConsoleUIEngineText("%02X ", readBuf[i]);
                    }

                    clxConsoleUIEngineText("\n");
                }
                else
                {
                    clxConsoleUIEngineText("clxGattReadLocal complete with result %s\n", clxGetErrorCodeText(ret));
                }

                break;
            }

#if defined(CLX_OOB_PAIRING_SUPPORT)
            case BlePeripheralMenuItem_GenerateOobKeys:
            {
                /* 
                Generate and store local Out-of-Band (OOB) data for transmission to the remote device, 
                or assign the received remote device OOB data to local variables, 
                preparing it for input to the stack.
                */
                generateOobData(stack);
                break;
            }
            
            case BlePeripheralMenuItem_EnableDisableOobPairing:
            {
                u4 option = 0;
                clxConsoleUIEngineInputBox("1 - Enable OOB pairing, 0 - Disable OOB pairing, 2 - Exit: ", oobData.input_buffer, MAX_INPUT_SIZE);
                (void)sscanf(oobData.input_buffer, "%u", &option);
                
                (option == 1) ? oobData.enableOobPairing = TRUE : oobData.enableOobPairing = FALSE;

                /* 
                Configure OOB pairing in this section. Since the connection handle is already established 
                (unlike in the Peripheral role), OOB pairing should be performed here before initiating the bonding process.

                When OOB pairing is disabled, perform the necessary actions here, as the connection handle is already available.
                When OOB pairing is enabled, defer the operation until the connection handle has been created and 
                immediately before initiating the bonding process.
                */
                if ((option < 2) && (FALSE == oobData.enableOobPairing))
                {
                    enableDisableOob(stack, peripheralInfo.connectionHandle, oobData.enableOobPairing);
                }

                break;
            }
#endif

            case BlePeripheralMenuItem_InitiateLegacyPairing:
            case BlePeripheralMenuItem_InitiateSecurePairing:
            {
                boolean secureFlag = FALSE;

                if (index == BlePeripheralMenuItem_InitiateSecurePairing)
                {
                    /**
                    Enables LE secure pairing procedure in stack.
                    */
                    secureFlag = TRUE;
                }

                (ClxResult) initiateBlePairing(stack,
                                               peripheralInfo.connectionHandle,
                                               secureFlag,
                                               gBlock);
                break;
            }

            case BlePeripheralMenuItem_DiconnectFromPairedDevice:
            {
                disconnectFromConnectedDevice(stack, peripheralInfo.connectionHandle, gBlock);
                break;
            }

            case BlePeripheralMenuItem_GetCurrentConnectionDetails:
            {
                /**
                Retrieves the active connection details.
                */
                getCurrentConnectionDetails(stack, peripheralInfo.connectionHandle, gBlock);
                break;
            }

            case BlePeripheralMenuItem_DeleteOldPairingInformation:
            {
                ClxBleBdAddress* removeDevice = showPairedDeviceList(stack);

                if(removeDevice)
                {
                    deleteBlePairedDeviceInfo(stack, removeDevice, TRUE, gBlock);
                }
                break;
            }

            case BlePeripheralMenuItem_DeleteAllPairedDevices:
            {
                deleteBlePairedDeviceInfo(stack, NULL, FALSE, gBlock);
                break;
            }

            case BlePeripheralMenuItem_ChangeConnectionParameters:
            {
                clxConsoleUIEngineText ("\nDo you want to update connection parameter?");
                s1 ch = clxConsoleUIEngineMessageBox("", "yYnN", 4);

                u1 filter = 0x00;

                if ((ch == 'y') || (ch == 'Y'))
                {
                    filter |= ClxBleParameterChangeFilter_ConnectionUpdate;
                }

                clxConsoleUIEngineText ("\nDo you want to increase the data length?");
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
                                           peripheralInfo.connectionHandle,                                         /* connectionHandle             */
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

#if defined( CLX_BLE_SERVICE_EXTENDED_API )
            case BlePeripheralMenuItem_BleServicesMenu:
            {
                clxBleServicesMenu( stack, getGattServerHandle() );
            }
            break;
#endif /* defined( CLX_BLE_SERVICE_EXTENDED_API ) */

            case BlePeripheralMenuItem_ReturnToPreviousMenu:
            {
                return;
            }

            default:
            {
                clxConsoleUIEngineText("\nPlease select the valid menu options...\n");
                break;
            }
        } // switch (index)
    } // while (TRUE)
}

/*****************************************************************************************************************************************
*                                        clxBleGapInitExtAdvertisingBuffer
*
* Initialize the given Extended Advertising Data Buffer by allocating the memory and setting the default values.
*
* \param extAdvBufferObj       Extended Advertising Data Buffer
*
****************************************************************************************************************************************/
void clxBleGapInitExtAdvertisingBuffer ( ClxBleExtendedAdvertisingData*  extAdvBufferObj )
{
    if ( extAdvBufferObj )
    {
        if ( NULL == extAdvBufferObj-> data )
        {
            extAdvBufferObj-> data             =  (u1*)clxAppAllocZero( CLX_BLE_EXTENDED_ADVERTISING_DATA_MAX_SIZE );
            extAdvBufferObj-> actualDataLength =  CLX_BLE_EXTENDED_ADVERTISING_DATA_MAX_SIZE;
        }
        extAdvBufferObj-> dataLength       =  0;
    }
}

/*****************************************************************************************************************************************
*                                        clxBleGapDestroyExtAdvertisingBuffer
*
* Deallocate the memory of the given Extended Advertising Data Buffer and initialize it with default values.
*
* \param extAdvBufferObj       Extended Advertising Data Buffer
*
****************************************************************************************************************************************/
void clxBleGapDestroyExtAdvertisingBuffer ( ClxBleExtendedAdvertisingData*  extAdvBufferObj )
{
    if ( extAdvBufferObj )
    {
        if (extAdvBufferObj-> data )
        {
            clxPoolsetFree( extAdvBufferObj-> data );
        }
        extAdvBufferObj-> data             =  NULL;
        extAdvBufferObj-> actualDataLength =  0;
        extAdvBufferObj-> dataLength       =  0;
    }
}

/*********************************************************************************************************************************
*                                                 enableAndDisableExtendedAdvertising
*
* This function is used to enable/disable one or more advertising sets.
* The advertising sets identified by the advertising handle parameter. 
*
* \param stack      - ClarinoxBlue stack
*
***********************************************************************************************************************************/
void enableAndDisableExtendedAdvertising ( ClxStack stack )
{
    ClxResult ret = CLX_ERROR;
    ClxBleAdvertisingSetInfo extAdvSet;

    /* Maximum advertising sets to set for extended advertising */
    u1 numberofAdvetisingSets;

    /* If want to get the options from the user need to enable the below snippet */
    numberofAdvetisingSets = (u1)0x01;

    extAdvSet.handle               = extendedAdvertisingHandle;
    extAdvSet.duration             = 0;
    extAdvSet.maxAdvertisingEvents = 0;

    ret = clxGapBleEnableDisableExtendedAdvertising ( 
                                        stack,
                                        &extAdvSet,
                                        numberofAdvetisingSets,
                                        FALSE,
                                        TRUE);

    clxConsoleUIEngineText("\nclxGapBleEnableDisableExtendedAdvertising status: %s", clxGetErrorCodeText(ret));
}

/*********************************************************************************************************************************
*                                                 bleStartExtendedAdvertising
*
* Start the Bluetooth Low Energy Extended Advertising
*
* \param extAdvDataObj      - Extended Advertising Object
*
***********************************************************************************************************************************/
void bleStartExtendedAdvertising ( ClxStack stack, ClxBleExtendedAdvertisingData* extendedAdvObj, boolean connectionFlag )
{
    ClxResult  ret = CLX_FAIL;

    /**
    Handle to an extended advertising set
    */
    ClxBleExtendedAdvertisingHandle extendedAdvHandle = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;

    /**
    Handle to identify the advertising set whose parameters are being configured
    */
    ClxBleExtendedAdvertisingHandle advertisingHandle = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;

    s1 selectedTxPower = 0;

    ClxBleBdAddress peerAddress = {};

    u1 advSID = (u1)0x02;

    if ( NULL == extendedAdvObj || \
         0 == extendedAdvObj->dataLength )
    {
        clxConsoleUIEngineText ( "\nInvalid Advertising buffer\n" );
    }

    /* First, start an extended advertising */
    ClxBleExtendedAdvertisingSetTypeFlags typeFlags;
    typeFlags.connectable = connectionFlag;
    typeFlags.directed    = FALSE;
    typeFlags.highDuty    = FALSE;
    typeFlags.scannable   = FALSE;

    ret = clxGapBleSetExtendedAdvertisingParameters (
                                         stack,                                             /* stack                          */
                                         advertisingHandle,                                 /* existingAdvertisingHandle      */
                                         300,                                               /* advertisingIntervalMin         */
                                         400,                                               /* advertisingIntervalMax         */
                                         ClxBleExtendedAdvertisingFlag_InludeTxPower,       /* advertisingFlags               */
                                         typeFlags,                                         /* advertisingType                */
                                         ClxBleOwnAddressMode_Identity,                     /* localAddressType               */
                                         &peerAddress,                                      /* peerAddress                    */
                                         CLX_BLE_ALL_ADVERTISING_CHANNELS,                  /* primaryAdvertisingChannelsToUse*/
                                         ClxBleAdvertisingFilterPolicy_ScanConnectionAnyone,/* advertisingFilterPolicy        */
                                         0,                                                 /* advertisingTxPower             */
                                         ClxBlePhyType_1M,                                  /* primaryPhyType                 */
                                         0,                                                 /* secondaryAdvertisignMaxSkip    */
                                         ClxBlePhyType_1M,                                  /* secondaryPhyType               */
                                         advSID,                                            /* advertisingSID                 */
                                         FALSE,                                             /* enableScanRequestNotification  */
                                         ClxBlePhyOptions_NoPreference,                     /* primary phy options            */
                                         ClxBlePhyOptions_NoPreference,                     /* secondary phy options          */
                                         &extendedAdvHandle,                                /* advertisingHandle              */
                                         &selectedTxPower,                                  /* selectedTxPower                */
                                         TRUE                                               /* block                          */
                                         );

    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nclxGapBleSetExtendedAdvertisingParameters failed with error %s\n", clxGetErrorCodeText(ret));
        return;
    }

    clxConsoleUIEngineText("\nclxGapBleSetExtendedAdvertisingParameters SUCCESS with %s\n", clxGetErrorCodeText(ret));

    clxConsoleUIEngineText("\nExtended advertising handle: %u\n", extendedAdvHandle);
    extendedAdvertisingHandle  =  extendedAdvHandle;

    ret = clxGapBleSetExtendedAdvertisingData(
                                        stack,                                              /* stack                */
                                        extendedAdvHandle,                                  /* advertisingHandle    */
                                        ClxBleAdvertisingDataType_Advertising,              /* dataType             */
                                        (u1*)extendedAdvObj-> data,                         /* data                 */
                                        (u4)extendedAdvObj-> dataLength,                    /* dataLength           */
                                        ClxBleAdvertisingFragmentPreference_DoNotFragment,  /* fragmentPreference   */
                                        TRUE                                                /* block                */
                                        );

    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nclxGapBleSetExtendedAdvertisingData failed with error %s\n", clxGetErrorCodeText(ret));
        return;
    }

    clxConsoleUIEngineText("\nclxGapBleSetExtendedAdvertisingData SUCCESS with %s\n", clxGetErrorCodeText(ret));

    ClxBleAdvertisingSetInfo extAdvSet;
    extAdvSet.handle                       = extendedAdvHandle;
    extAdvSet.duration                     = 0;
    extAdvSet.maxAdvertisingEvents         = 0;

    ret = clxGapBleEnableDisableExtendedAdvertising (
                                stack,
                                &extAdvSet,
                                1,
                                TRUE,
                                TRUE);

    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("\nclxGapBleEnableDisableExtendedAdvertising failed with error %s\n", clxGetErrorCodeText(ret));
        return;
    }

    clxConsoleUIEngineText("\nclxGapBleEnableDisableExtendedAdvertising SUCCESS with %s\n", clxGetErrorCodeText(ret));

}

/*********************************************************************************************************************************
*                                                 bleStopExtendedAdvertising
*
* Stop the Bluetooth Low Energy Extended Advertising
*
* \param extAdvDataObj      - Extended Advertising Object
*
***********************************************************************************************************************************/
void bleStopExtendedAdvertising ( ClxStack stack, ClxBleExtendedAdvertisingData* extendedAdvObj )
{
    ClxResult ret = CLX_SUCCESS;

    if ( CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE == extendedAdvertisingHandle )
    {
        clxConsoleUIEngineText("\nPlease make sure to start the Extended Advertising first\n");
        return;
    }

    clxBleGapDestroyExtAdvertisingBuffer ( extendedAdvObj );

    enableAndDisableExtendedAdvertising ( stack );

    ret = clxGapBleRemoveExtendedAdvertisingSet ( stack,
                                                  extendedAdvertisingHandle,
                                                  TRUE );

    clxConsoleUIEngineText("\nclxGapBleRemoveExtendedAdvertisingSet status: %s", clxGetErrorCodeText(ret));

    extendedAdvertisingHandle  = CLX_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE;
}

ClxHandle clxBleCheckGattServerHandleAvailability( ClxHandle inputHanlde )
{
    if( FALSE == peripheralInfo.isBlePeripheralInitialized || NULL == inputHanlde )
    {
        return CLX_BLE_INVALID_HANDLE;
    }

    if( inputHanlde == getGattServerHandle())
    {
        return getGattServerHandle();
    }

    return CLX_BLE_INVALID_HANDLE;
}

