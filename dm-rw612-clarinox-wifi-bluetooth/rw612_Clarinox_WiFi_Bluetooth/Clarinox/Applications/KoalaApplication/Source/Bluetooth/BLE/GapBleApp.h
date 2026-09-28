#ifndef __GapBleApp_h__
#define __GapBleApp_h__

/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                GapBleApp.h
* Description         This file provides GATT Application functions declarations.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#include "Gatt.Ble.Common.Api.h"
#include "Gap.Ble.Api.h"
#include "Gap.Ble.Bonding.Api.h"

#include "mainBluetooth.h"

/* Connection timeout in milliseconds */
#define CONNECTION_TIMEOUT          10000

/* Disconnection timeout in milliseconds */
#define DISCONNECTION_TIMEOUT       2000

/*  Periodic train Synchronization timeout */
#define CLX_BLE_PERIODIC_TRAIN_SYNC_TIMEOUT                 0x4000

#if defined(CLX_OOB_PAIRING_SUPPORT)
/* Length of the Public key X, Y and Private key */
#define LE_PUBLIC_PRIVATE_KEY_LENGTH        32

/* Length of the Confirm and Random values */
#define LE_RANDOM_CONFIRM_VALUE_LENGTH      16

typedef struct AppOobData_Struct
{
    u1 publicKeyX[LE_PUBLIC_PRIVATE_KEY_LENGTH];
    u1 publicKeyY[LE_PUBLIC_PRIVATE_KEY_LENGTH];
    u1 privateKey[LE_PUBLIC_PRIVATE_KEY_LENGTH];
    
    u1 randomLocal[LE_RANDOM_CONFIRM_VALUE_LENGTH];
    u1 confirmLocal[LE_RANDOM_CONFIRM_VALUE_LENGTH];

    u1 randomRemote[LE_RANDOM_CONFIRM_VALUE_LENGTH];
    u1 confirmRemote[LE_RANDOM_CONFIRM_VALUE_LENGTH];

    /* Pointers containing stack generated/OOB keys that are to be passed to stack as input */
    ClxBleOobKeyDetails ptrStackOobKeys;

    /* OOB can be legacy or secure, indicated by this varaible */
    ClxBlePairMode pairingMode;

    /* OOB can be enabled or disabled, based on this variable */
    boolean enableOobPairing;

    /* Input buffer used to get and store the confirm and random keys entered as input from the user */
    s1 input_buffer[MAX_INPUT_SIZE];
}AppOobData;

extern AppOobData oobData;
#endif /* CLX_OOB_PAIRING_SUPPORT */

/*
This callback function is registered for the BLE, any events raised by BLE, causes this
callback function executed with the associated event and parameters. Executed from the stack thread context
*/
boolean bleStackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);

/*
Initiates BLE pairing procedure with the given remote device whose connection handle is passed as parameter
*/
ClxResult initiateBlePairing(ClxStack stack, ClxBleConnectionHandle connectionHandle, boolean secureFlag, boolean blocking);

/*
Initiate Encryption procedure with the given remote device whose connection handle is passed as parameter
*/
void startEncryption(ClxStack stack, ClxBleConnectionHandle connectionHandle, boolean secureFlag, boolean securityRequest, boolean blocking);

/*
Disconnect connection with the connected remote device which is represented by the given connection handle
*/
void disconnectFromConnectedDevice(ClxStack stack, ClxBleConnectionHandle connectionHandle, boolean blocking);

/*
Returns the connection details of the connection whose handle is passed
*/
void getCurrentConnectionDetails(ClxStack stack, ClxBleConnectionHandle connectionHandle, boolean blocking);

/*
Delete paired devide details that is stored
*/
void deleteBlePairedDeviceInfo(ClxStack stack, ClxBleBdAddress* remoteDeviceAddress, boolean isOldestInfo, boolean blocking);

/**
Updates the connection parameter, tx/rx PHY and extending the packet length
*/
void changeConnectionParameters(ClxStack              stack,
                                u2                    conHandle,
                                u1                    filter,
                                u2                    minConInterval,
                                u2                    maxConInterval,
                                u2                    conLatency,
                                u2                    supTimeout,
                                u2                    minConEventLen,
                                u2                    maxConEventLen,
                                u2                    singlePackLen,
                                u2                    singlePacTransTime,
                                u1                    phyPreference,
                                ClxBlePhyType         txPhy,
                                ClxBlePhyType         rxPhy,
                                ClxBleLECodedPhy      leCodedOptions,
                                boolean               blocking);

/**
Starts the extended scan
*/
void startExtendedScan(ClxStack stack, boolean bNameFilter);

/**
Start the Bluetooth Low Energy Advertising
*/
void startBleAdvertising(ClxStack stack);

/**
Deallocate the memory of the given Extended Advertising Data Buffer and initialize it with default values.
*/
void clxBleGapDestroyExtAdvertisingBuffer ( ClxBleExtendedAdvertisingData*  extAdvBufferObj );

/**
Start the Bluetooth Low Energy Extended Advertising
*/
void bleStartExtendedAdvertising ( ClxStack stack, ClxBleExtendedAdvertisingData* extendedAdvObj, boolean connectionFlag );

/**
Stop the Bluetooth Low Energy Extended Advertising
*/
void bleStopExtendedAdvertising ( ClxStack stack, ClxBleExtendedAdvertisingData* extendedAdvObj );

/**
Initialize the given Extended Advertising Data Buffer by allocating the memory and setting the default values.
*/
void clxBleGapInitExtAdvertisingBuffer(ClxBleExtendedAdvertisingData* extAdvBufferObj);

/**
Retrieves the current status of the device name filtering option.
*/
boolean clxGetDeviceNameFilteringOption ( void );

/**
Sets the device name filtering option based on user input.
*/
void clxSetDeviceNameFilteringOption ( void );

#if defined(CLX_BLE_CS_REFLECTOR)
void csInitialize(ClxStack stack);
#endif

#if defined(CLX_OOB_PAIRING_SUPPORT)
/**
Present the user menu and generate the OOB keys based on the user selection option and by calling the appropriate stack APIs.
*/
void generateOobData(ClxStack stack);

/**
Enable or disable OOB authentication in the stack by calling the appropriate APIs based on user input
*/
void enableDisableOob(ClxStack stack, ClxBleConnectionHandle bleConnectionHandle, boolean enable);
#endif

/**
Returns the active connection handle
*/
u2 getConnectionHandle(void);

#endif /* __GapBleApp_h__ */

