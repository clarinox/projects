#ifndef __GattServer_h__
#define __GattServer_h__

/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                GattServer.h
* Description         This file provides GATT Application functions declarations.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#include"Gatt.Ble.Includes.h"

/**
Timeout value for local write command
*/
#define WRITE_TIMEOUT_VALUE                     2000

/*
Create BLE GATT Server handle if this profile is used
*/
ClxHandle createGattServerHandle(ClxStack stack);

/*
Delete BLE GATT Server handle when there is no use for this profile
*/
void deleteGattServerHandle(ClxHandle gattServer);

/*
This callback function is registered for the BLE GATT Server, any events raised by BLE GATT Server, causes this
callback function executed with the associated event and parameters. Executed from the stack thread context
*/
boolean bleGattServerMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);

/*
Registers the GATT services in local server
*/
ClxError registerLocalService(ClxHandle gattServer, u2 serviceIndex);

/*
Deregisters the GATT service
*/
ClxError unRegisterLocalService(ClxHandle gattServer, u2 serviceIndex);

/*
Registers the BLE audio services in local server
*/
ClxError registerBleAudioServices(ClxHandle gattServer);

/**
Get gatt server handle
*/
ClxHandle getGattServerHandle();

/**
Returns whether BLE peripheral role is initialized or not
*/
boolean isBlePeripheralInitialized(void);

/**
Returns the active connection handle
*/
u2 getConnectionHandle(void);

/**
Gets base handle of given service index
*/
u2 getLocalServiceBaseHandle(u2 serviceIndex);

/**
Gets base Local Characteristic handle of given service and characteristic index
*/
u2 clxBleGetServerLocalValueHandle ( GattServicesIndex serviceIndex, s4 characteristicIndex );

#endif /* _GattServer_h__ */

