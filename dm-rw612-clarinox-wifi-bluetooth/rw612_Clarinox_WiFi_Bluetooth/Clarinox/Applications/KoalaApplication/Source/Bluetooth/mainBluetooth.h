#ifndef _mainBluetooth_h_
#define _mainBluetooth_h_

/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                mainBluetooth.h
* Description         Application common definitions used across Bluetooth files
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

extern boolean gBlock;

/*
Size of buffer to get input from user
*/
#define MAX_INPUT_SIZE                  255

#define CLX_BLE_INVALID_HANDLE          NULL
/**
Determines the Normal or extended mode of Advertising or Scanning.
*/
typedef enum ClxBleAdvertisingOrScanModeEnum
{
    ClxBleAdvOrScanMode_INVALID = 0x00,
    ClxBleAdvOrScanMode_Legacy,
    ClxBleAdvOrScanMode_Extended,
}ClxBleAdvOrScanMode;

/**
Determines the Legacy or secure mode of pairing.
*/
typedef enum ClxBlePairModeEnum
{    
    ClxBlePairMode_Legacy = 1,
    ClxBlePairMode_Secure,
    ClxBlePairMode_StartEncryption,
}ClxBlePairMode;

/**
Determines the Legacy or secure mode of pairing.
*/
typedef enum ClxBleWhitelistEnum
{
    ClxBleWhitelist_AddDevice = 1,
    ClxBleWhitelist_RemoveDevice,
    ClxBleWhitelist_RemoveAllDevices,
}ClxBleWhitelist;

/**
Menu options used to invoke GATT menu 
*/
typedef enum GATTMenuItemEnum
{
    GATTMenuItem_DiscoverAllPrimaryServices = 1,
    GATTMenuItem_DiscoverAllCharacteristics,
    GATTMenuItem_DiscoverAllDescriptors,
    GATTMenuItem_EnableNotification,
    GATTMenuItem_EnableIndication,
    GATTMenuItem_ReadAttribute,
    GATTMenuItem_WriteAttribute,
    GATTMenuItem_ReturnToPreviousMenu,
    GATTMenuItem_TotalItems
}GATTMenuItem;

/**
Determines the Delete all devices or Delete a particular device.
*/
typedef enum ClxBleDeletePairedDeviceEnum
{
    ClxBleDeletePairedDevice_DeleteAllDevices = 1,
    ClxBleDeletePairedDevice_DeleteaParticularDevice,
}ClxBleDeletePairedDevice;

/*
BLE Gatt Role type enum
*/
typedef enum ClxBleGattRoleTypeEnum
{
    ClxBleGattRoleType_INVALID     = 0,                    /* Invalid Role */
    ClxBleGattRoleType_CLIENT      = 1,                    /* Client Role  */
    ClxBleGattRoleType_SERVER      = 2,                    /* Server Role  */
}ClxBleGattRoleType;

/* Primary functions required to be implemented by the other modules based on what is supported */
#if defined(CLX_BT_CLASSIC)
void     initializeClassic(ClxStack stack);
void     terminateClassic();
void     classicMenu(ClxStack stack, const s1* deviceName);
boolean  classicStackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);
void     initializeClassicProfiles(ClxStack stack);
void     terminateClassicProfiles();
void     allProfilesMenuFunction(ClxStack stack, ClxDeviceId deviceId, const s1* deviceName);
void     sdapMenuFunction(ClxStack stack, ClxDeviceId deviceId);
void     scoBridgeMenu(ClxStack stack, const s1* deviceName);
ClxDeviceId selectPairedDevice(ClxStack stack);
#endif

#if defined(CLX_BLE_CENTRAL)
void     initializeBleCentral(ClxStack stack);
void     terminateBleCentral();
void     bleCentralGATTMenu( void );
void     lowEnergyCentralMenu(ClxStack stack);
boolean  bleCentralMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);
#endif

#if defined(CLX_BLE_PERIPHERAL)
void     initializeBlePeripheral(ClxStack stack);
void     terminateBlePeripheral();
void     lowEnergyPeripheralMenu(ClxStack stack, const s1* deviceName);
boolean  blePeripheralMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);
#endif

#if defined(CLX_BLE_CS_REFLECTOR)
void    lowEnergyCSReflectorMenu(ClxStack stack, const s1* deviceName);
#endif

/*
This call-back function is called when any events raised by GAP profile causes this call-back function executed with
the associated event and parameters
*/
boolean stackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);

const s1* clxGetBTLocalDeviceName ( void );

ClxStack clxGetBTStackHandle ( void );

ClxHandle clxBleCheckGattClientHandleAvailability( ClxHandle inputHanlde );

ClxHandle clxBleCheckGattServerHandleAvailability( ClxHandle inputHanlde );

/**
The local device input/output capability for security procedure
*/
u1 getIoCapability();

#endif /* _mainBluetooth_h_ */

