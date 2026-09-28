/********************************************************************************
*
* Project             Clarinox Reference Application
* File                Gatt.cpp
* Description         This file provides GATT profile handle creation and
*                     deletion. GATT UI menu, and indication call back functions.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#include "ClxCommon.h"
#include "ClarinoxBlue.h"

#include "Gap.Api.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gap.Ble.Api.h"
#include "Gap.Ble.Bonding.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Server.Api.h"
#include "Gatt.Ble.Client.Api.h"

#include "GattApp.h"
#include "GattClient.h"
#include "Gatt.Ble.Includes.h"

/**
Object to store the remote device and paired device informations
*/
extern ClxCentralInstanceInfo centralInfo;

/*******************************************************************************************************************************
*                                                   createGattHandle
*
* Create the GATT profile handle with client role on local device.
*
* \param stack       - Local device stack handle
*
* \return ClxHandle  - GATT client handle
*
*******************************************************************************************************************************/
ClxHandle createGattHandle(ClxStack stack)
{
    /**
    Create GATT client handle. This handle to be passed for other GATT client API commands.
    */
    return clxGattCreateClient(stack, stackMessageHandler);
}

/*******************************************************************************************************************************
*                                                    deleteGattHandle
*
* Delete the GATT profile handle when there is no use for this profile.
*
* \param handle  - GATT client handle
*
*******************************************************************************************************************************/
void deleteGattHandle(ClxHandle handle)
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
        clxConsoleUIEngineText("\nInvalid handle\n");
    }
}

/********************************************************************************************************************************
*                                                   resetRemoteDeviceList
*
* This function is used to reset the device list counter while scan operation begins
*
**********************************************************************************************************************************/
void resetRemoteDeviceList()
{
    centralInfo.remoteDeviceList.reset();
}

/**********************************************************************************************************************************
*                                                   showRemoteDeviceList
*
* The discovered remote devices are displayed by index
* Provides selection menu for user to select required device to connect to
*
* \return RemoteDeviceInfo  - User selected remote device details.
*
***********************************************************************************************************************************/
RemoteDeviceInfo* showRemoteDeviceList()
{
    const s1 returnText[] = {"Return to previous menu"};

    u4 numberOfDevices = centralInfo.remoteDeviceList.currentSize();

    if (numberOfDevices)
    {
        u4 menuSize = numberOfDevices * (MAX_REMOTE_DEVICE_NAME_SIZE + 2 + 12 + 1 + 1) + sizeof(returnText);

        s1* menu = (s1*)clxAppPoolsetAlloc ( 0, __LINE__, menuSize );

        u4 index = 0;

        for (u4 i = 0; i < numberOfDevices; i++)
        {
            const s1* name = (centralInfo.remoteDeviceList)[i].name;
            const u1* addr = (centralInfo.remoteDeviceList)[i].address.value;
            u1 advSID = (centralInfo.remoteDeviceList)[i].advSID;

            if (strcmp(name, NO_DEVICE_NAME))
            {
                sprintf (menu + index, "%s [%02x] (%02X%02X%02X%02X%02X%02X)", name, advSID,  addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
            }
            else
            {
                sprintf (menu + index, "[%02x] %02X%02X%02X%02X%02X%02X", advSID, addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
            }

            index += (strlen(menu + index) + 1);
        }

        strcpy (menu + index, returnText);

        CLX_ASSERT(strlen(menu) < menuSize);

        u4 selection = clxConsoleUIEngineShowMenu("Please select a device", menu, numberOfDevices + 1);
        
        clxPoolsetFree(menu);

        if (selection <= numberOfDevices)
        {
            return &(centralInfo.remoteDeviceList)[selection - 1];
        }
    }
    else
    {
        clxConsoleUIEngineText("\nThere is no device in the list\n");
    }

    return NULL;
}

/******************************************************************************************************************************************
*                                                    showPairedDeviceList
*
* This function used to get the list of paired devices details from stack using API clxGapBleGetListOfPairedDevices(..)
* Display the remote device and user can select the device to reconnect instantly
*
* \param stack             - Local device stack handle
*
* \return ClxBleBdAddress  - User selected paired device address.
*
*******************************************************************************************************************************************/
ClxBleBdAddress* showPairedDeviceList(ClxStack stack)
{
    ClxError ret = CLX_ERROR;
    u4 noOfPairedDevices = 0;

    memset(centralInfo.pairedDeviceList, 0, sizeof(ClxBleBdAddress) * CLARINOXBLUE_DEFAULT_LOW_ENERGY_MAX_NUMBER_OF_PAIRED_DEVICES);

    /**
    Retrieves the list of paired devices from stack.
    */
    ret = clxGapBleGetListOfPairedDevices(stack, centralInfo.pairedDeviceList, CLARINOXBLUE_DEFAULT_LOW_ENERGY_MAX_NUMBER_OF_PAIRED_DEVICES, &noOfPairedDevices, TRUE);

    if ((ret == CLX_SUCCESS) && (noOfPairedDevices))
    {
        clxConsoleUIEngineText("\nclxGapBleGetListOfPairedDevices: noOfPairedDevices - %d\n", noOfPairedDevices);

        const s1 returnText[] = {"Return to previous menu"};

        u4 menuSize = noOfPairedDevices * (MAX_REMOTE_DEVICE_NAME_SIZE + 6 + 2 + 12 + 1 + 1) + sizeof(returnText);

        s1* menu = (s1*)clxAppAlloc( menuSize );

        u4 index = 0;

        for (u4 i = 0; i < noOfPairedDevices; i++)
        {
            const u1* addr = centralInfo.pairedDeviceList[i].value;

            ClxGapBlePairedDeviceDetail deviceDetail = {};

            /**
            Retrieves the device name from paired device details and print them
            */
            ret = clxGapBleGetPairedDeviceName(stack, &centralInfo.pairedDeviceList[i], &deviceDetail, TRUE);

            if (ret == CLX_SUCCESS)
            {
                sprintf (menu + index, "%s (%02X%02X%02X%02X%02X%02X)", deviceDetail.name,addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
            }
            else
            {
                sprintf (menu + index, "%02X%02X%02X%02X%02X%02X", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
            }

            index += (strlen(menu + index) + 1);
        }

        strcpy (menu + index, returnText);

        CLX_ASSERT(strlen(menu) < menuSize);

        u4 selection = clxConsoleUIEngineShowMenu("Please select a device to connect", menu, noOfPairedDevices + 1);

        clxPoolsetFree(menu);

        if (selection <= noOfPairedDevices)
        {
            return &centralInfo.pairedDeviceList[selection - 1];
        }
    }

    return NULL;
}

ClxResult clxBLECheckCharacteristicHandleByCharName( u2     characteristicHandle, s1*    charName )
{
    extern ClxBleGattServiceInfo clxBleGattServiceList[NumberOfBleGattServices];

    if ( 0    == characteristicHandle ||\
         NULL == charName )
    {
        return CLX_ERROR_INVALID_HANDLE;
    }

    u2 serviceHandleBase = clxBleGetServiceHandleBaseFromHandle( characteristicHandle );

    for (u4 i = 0; i < sizeof(clxBleGattServiceList)/sizeof(ClxBleGattServiceInfo); i++)
    {
        if (clxBleGattServiceList[i].handleBase == serviceHandleBase)
        {
            const s1* characteristicName = clxBleGattServiceList[i].getGattServiceCharacteristicName(clxBleGetServiceAttributeIndexFromHandle(characteristicHandle));

            if (characteristicName == NULL)
            {
                characteristicName = "Unknown Characteristic";
            }

            if ( 0 == strcmp( characteristicName, charName ) )
            {
                clxConsoleUIEngineText("\nService : %s\n", clxBleGattServiceList[i].name);
                clxConsoleUIEngineText("Characteristic : %s\n", characteristicName);

                return CLX_SUCCESS;
            }
        }
    }

    return CLX_ERROR_INTERNAL_ERROR;
}

