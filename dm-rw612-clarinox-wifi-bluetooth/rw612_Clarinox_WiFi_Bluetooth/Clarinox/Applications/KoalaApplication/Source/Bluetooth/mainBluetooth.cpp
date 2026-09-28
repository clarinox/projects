/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                mainBluetooth.cpp
* Description         This file provides a main menu of the application with 
*                     the options of initialization and termination of the 
*                     Bluetooth stack and Bluetooth connectivity options.
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

#include "mainBluetooth.h"

#if defined(CLX_BT_CLASSIC)
#if defined(CLX_BT_CLASSIC_TEST_MODE)
#include "Gap.Api.h"
#endif
#endif

#if defined(CLX_BLE_CENTRAL) || defined(CLX_BLE_PERIPHERAL)
#include "GapBleApp.h"
#endif

#if defined(CLX_BLE_ISOCHRONOUS)
#include "BleAudioCommon.h"
#endif /* CLX_BLE_ISOCHRONOUS */

#if defined (CLX_WINDOWS)
/*  Total memory used by RAM */
extern u4 totalMemoryUsed;
#endif

/*
Main function for ClarinoxBlue stack
*/
int mainClarinoxBlue(void);

#ifdef __cplusplus
extern "C" {
#endif

extern  ClxConfigList* initializeClarinoxBlueBspConfigParameters(void);
int mainBluetooth(void);

int mainBluetooth(void)
{
    return mainClarinoxBlue();
}

#ifdef __cplusplus
}
#endif

/* Menu options used to invoke Bluetooth main menu */
typedef enum BluetoothMenuItemEnum
{
    BluetoothMenuItem_InitializeStack               = 1,
    BluetoothMenuItem_TerminateStack,
#if defined(CLX_BT_CLASSIC)
    BluetoothMenuItem_ClassicMenu,
#endif
#if defined(CLX_BLE_CENTRAL)
    BluetoothMenuItem_LowEnergyCentralMenu,
#endif
#if defined(CLX_BLE_PERIPHERAL)
    BluetoothMenuItem_LowEnergyPeripheralMenu,
#endif
#if defined(CLX_BLE_ISOCHRONOUS)
    BluetoothMenuItem_BleAudioMenu,
#endif /* defined(CLX_BLE_ISOCHRONOUS) */
#if defined(CLX_BLE_CS_REFLECTOR)
    BluetoothMenuItem_BleCsReflector,
#endif
    BluetoothMenuItem_TotalMemoryUsage,
    BluetoothMenuItem_ReturnToPreviousMenu,
    BluetoothMenuItem_TotalItems
}BluetoothMenuItem;

/**
Local Bluetooth Device name
*/
const s1*   deviceName = "ClxBluetoothRwApp";

/* 
Variables associated with Bluetooth object 
*/
typedef struct ClxBluetoothInfoStruct
{
    ClxStack        stack;                          /* Bluetooth stack object                                       */
    u1              ioCapability;                   /* Input Output Capability of the local device                  */
    boolean         isBluetoothStackInitialized;    /* Indicate if the Bluetooth stack is initialized or not        */
    ClxConfigList*  configList;                     /* BSP Configuration list used to initialize stack              */
}ClxBluetoothInfo;

/* Structure with variables required for Bluetooth instance */
ClxBluetoothInfo bluetoothInfo = {};

/**
Variable to specify the API's mode.

TRUE    - Blocking mode
FALSE   - Non blocking mode

Please note that if it is Non-blocking then the API output parameters should be declared as global scope or need to alloate the memory.
*/
boolean gBlock = TRUE;

/*
This call-back function is called when any events raised by GAP profile causes this call-back function executed with
the associated event and parameters
*/
boolean stackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);

/* Initializes ClarinoxBlue stack with configuration parameters for Bluetooth stack. */
boolean initializeClarinoxBlue(ClxStack* stack);


/*******************************************************************************************************************************
*                                                getIoCapability
*
* Returns the local device input/output capability for security procedure
*
* \return u1            - IO Capability of local device
*
*******************************************************************************************************************************/

/**
Returns the local device input/output capability for security procedure
*/
u1 getIoCapability()
{
    return bluetoothInfo.ioCapability;
}

/*******************************************************************************************************************************
*                                                stackMessageHandler
*
* This call-back function is registered for the GAP and GATT profiles, 
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
boolean stackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    /* Indication of stack initialization completion */
    if (messageID == CLX_INIT_CLARINOX_BLUE_COMPLETE)
    {
        if (errorCode == CLX_SUCCESS)
        {
            /* Now ready to call Bluetooth API functions */
            clxConsoleUIEngineText("\nClarinoxBlue initialization completed\n");
        }
        else
        {
            clxConsoleUIEngineText("\nClarinoxBlue initialization failed with error: %s\n", clxGetErrorCodeText(errorCode));
        }
    }
    /* Indication of stack termination completion */
    else if (messageID == CLX_TERMINATE_CLARINOX_BLUE_COMPLETE)
    {
        if (errorCode == CLX_SUCCESS)
        {
            /* Now ready to destroy the stack */
            clxConsoleUIEngineText("\nClarinoxBlue termination completed\n");
        }
        else
        {
            clxConsoleUIEngineText("\nStack termination was not successful (error : %s)", clxGetErrorCodeText(errorCode));
        }
    }
    else if (messageID == CLX_BLUETOOTH_LICENSE_EXPIRED_INDICATION)
    {
        clxConsoleUIEngineText("\nEvaluation license has expired. Please contact Clarinox for further assistance\n");
    }
    else
    {

#if defined(CLX_BT_CLASSIC)
        if (classicStackMessageHandler(stack, serviceHandle, messageID, params, errorCode))
        {
            return TRUE;
        }
#endif

#if defined(CLX_BLE_CENTRAL)
        if (bleCentralMessageHandler(stack, serviceHandle, messageID, params, errorCode))
        {
            return TRUE;
        }
#endif

#if defined(CLX_BLE_PERIPHERAL)
        if (blePeripheralMessageHandler(stack, serviceHandle, messageID, params, errorCode))
        {
            return TRUE;
        }
#endif

#if defined(CLX_BLE_ISOCHRONOUS)
        if ( bleAudioStackMessageHandler ( stack, serviceHandle, messageID, params, errorCode ) )
        {
            return TRUE;
        }
#endif /* CLX_BLE_ISOCHRONOUS */
    }

    return TRUE;
}

/*****************************************************************************************************************************************
*                                                       initializeClarinoxBlue
*
* Initializes ClarinoxBlue stack with configuration parameters for Bluetooth stack.
*
* \param stack    - ClarinoxBlue stack.
*
* \return boolean - TRUE - If clxInitClarinoxBlue API returns CLX_SUCCESS, FALSE - Otherwise
*
******************************************************************************************************************************************/
boolean initializeClarinoxBlue(ClxStack* stack)
{
    boolean ret = TRUE;

    struct GenericConfigParameters
    {
        ClxConfigInteger ioCapabilities;
        ClxConfigString localDeviceName;
    };

    /*
    Object to store the device configuration parameters for clarinoxBlue stack initialization. 
    */
    GenericConfigParameters genericConfigParameters;

    /* Initialize the memory for the configuration list and initialize BSP related configuration parameters for stack bring up */
    bluetoothInfo.configList = initializeClarinoxBlueBspConfigParameters();

    /* Initialize device configuration parameters */
    clxConfigInitIntegerParam(&genericConfigParameters.ioCapabilities,          "IoCapabilities",           bluetoothInfo.ioCapability, bluetoothInfo.configList);
    clxConfigInitStringParam(&genericConfigParameters.localDeviceName,          "LocalDeviceName", clxGetBTLocalDeviceName(), bluetoothInfo.configList);
    
    /**
    Initialize the Bluetooth stack
    */
    if (clxInitClarinoxBlue(bluetoothInfo.configList,
                            NULL,
                            stackMessageHandler,
                            stack, 
                            gBlock) != CLX_SUCCESS)
    {
        clxConsoleUIEngineText("Initialization of ClarinoxBlue failed\n");
            releaseClarinoxBlueBspConfigParameters(bluetoothInfo.configList);
        ret = FALSE;
    }
    else
    {
        /**
        Prints ClarinoxBlue Stack, SoftFrame and other device details.
        */
        clxConsoleUIEngineText("ClarinoxSoftFrame version: %s \n",
                                  clxGetClarinoxSoftFrameVersion());

        clxConsoleUIEngineText("ClarinoxBlue version:      %s \n",
                                  clxGetClarinoxBlueVersion());

        u1 tempBuffer[40] = {};
        clxGetLocalBluetoothDeviceAddress(tempBuffer);
        clxConsoleUIEngineText("Local Device Address:      %s\n", tempBuffer);
        clxGetLocalBluetoothHciVersion(tempBuffer);
        clxConsoleUIEngineText("Local Device HCI Version:  %s\n", tempBuffer);
        clxGetLocalBluetoothHciRevision(tempBuffer);
        clxConsoleUIEngineText("Local Device HCI Revision: %s\n", tempBuffer);
        clxGetLocalBluetoothDeviceManufacturer(tempBuffer);
        clxConsoleUIEngineText("Local Device Manufacturer: %s\n", tempBuffer);
    }

    return ret;
}

/***************************************************************************************************************************************
*                                                mainBluetooth
*
* Initialize BSP and UI interface, and provide the main UI menu for Bluetooth.
* Initializes the ClarinoxBlue stack
*
****************************************************************************************************************************************/
int mainClarinoxBlue(void)
{
    /* Assigns the Input/Output capabilities of the local device */
    bluetoothInfo.ioCapability = IO_DISPLAY_YES_NO;

    while (TRUE)
    {
        const s1* menu =    "Initialize Bluetooth Stack\0"
                            "Terminate Bluetooth Stack\0"
#if defined(CLX_BT_CLASSIC)
                            "Classic Menu\0"
#endif
#if defined(CLX_BLE_CENTRAL)
                            "Low Energy Central Menu\0"
#endif
#if defined(CLX_BLE_PERIPHERAL)
                            "Low Energy Peripheral Menu\0"
#endif
#if defined(CLX_BLE_ISOCHRONOUS)
                            "LE Audio Menu\0"
#endif /* defined(CLX_BLE_ISOCHRONOUS) */
#if defined(CLX_BLE_CS_REFLECTOR)
                            "LE CS Reflector\0"
#endif
                            "Total memory usage\0"
                            "Return to Previous Menu\0";

        u4 index = clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, BluetoothMenuItem_TotalItems - 1);

        if ((index > BluetoothMenuItem_InitializeStack) && (bluetoothInfo.stack == NULL) && (index < BluetoothMenuItem_TotalMemoryUsage))
        {
            clxConsoleUIEngineText("\nPlease make sure to initialize the Bluetooth Stack first\n");
        }
        else
        {
            switch (index)
            {
                case BluetoothMenuItem_InitializeStack:
                {
                    if (bluetoothInfo.stack == NULL)
                    {
                        /*
                        Initialize the Bluetooth stack with the parameters; params, event call-back function; stackMessageHandler
                        and the exception handler; userExceptionHandler
                        */
                        if (!initializeClarinoxBlue(&bluetoothInfo.stack))
                        {
                            bluetoothInfo.stack = NULL;
                            return 0;
                        }

#if defined(CLX_BT_CLASSIC)
                        (void)initializeClassic(bluetoothInfo.stack);
#endif
#if defined(CLX_BLE_CENTRAL)
                        (void)initializeBleCentral(bluetoothInfo.stack);
#endif
#if defined(CLX_BLE_PERIPHERAL)
                        (void)initializeBlePeripheral(bluetoothInfo.stack);
#endif

#if defined(CLX_BLE_ISOCHRONOUS)
                        bleCreateIsoServer(bluetoothInfo.stack);
                        bleCreateIsoClient(bluetoothInfo.stack);
                        clxBleInitAudioParams();
#endif /* defined(CLX_BLE_ISOCHRONOUS) */
                        
                        clxConsoleUIEngineText("\nBluetooth Stack initialized successfully\n");

#if defined(CLX_BT_CLASSIC_TEST_MODE)
                        ClxResult ret = clxBluetoothClassicEnableDeviceTestMode(bluetoothInfo.stack, TRUE);
                        clxConsoleUIEngineText("\nEntering device under test mode completed : %s\n", clxGetErrorCodeText(ret));
                        clxConsoleUIEngineText("NOTE:- To exit from test mode, terminate the stack\n");
#endif
                    }
                    else
                    {
                        clxConsoleUIEngineText("\nBluetooth Stack is already created\n");
                    }

                    break;
                }

                case BluetoothMenuItem_TerminateStack:
                {
                    if (NULL != bluetoothInfo.stack)
                    {
                        releaseClarinoxBlueBspConfigParameters(bluetoothInfo.configList);

#if defined(CLX_BT_CLASSIC)
                        terminateClassic();
#endif
#if defined(CLX_BLE_CENTRAL)
                        terminateBleCentral();
#endif
#if defined(CLX_BLE_PERIPHERAL)
                        terminateBlePeripheral();
#endif

#if defined(CLX_BLE_ISOCHRONOUS)
                        bleDeleteIsoServer();
                        bleDeleteIsoClient();
                        clxBleTerminateAudioParams();
#endif /* defined(CLX_BLE_ISOCHRONOUS) */

                        /*
                        Terminate the stack
                        */
                        ClxResult ret = clxTerminateClarinoxBlue(bluetoothInfo.stack, TRUE);
                        if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                        {
                            clxConsoleUIEngineText("\nclxTerminateClarinoxBlue command failed with the result: %s\n", clxGetErrorCodeText(ret));
                        }

                        /*
                        Destroy the stack, after this call is completed, stack can be initialized again
                        */
                        clxDestroyClarinoxBlue(bluetoothInfo.stack);
                        bluetoothInfo.stack = NULL;
                        clxConsoleUIEngineText("\nBluetooth Stack terminated\n");
                    }
                    break;
                }

#if defined(CLX_BT_CLASSIC)
                case BluetoothMenuItem_ClassicMenu:
                {
                    classicMenu(bluetoothInfo.stack, clxGetBTLocalDeviceName());
                    break;
                }
#endif

#if defined(CLX_BLE_CENTRAL)
                case BluetoothMenuItem_LowEnergyCentralMenu:
                {
                    lowEnergyCentralMenu(bluetoothInfo.stack);
                    break;
                }
#endif

#if defined(CLX_BLE_PERIPHERAL)
                case BluetoothMenuItem_LowEnergyPeripheralMenu:
                {
                    lowEnergyPeripheralMenu(bluetoothInfo.stack, clxGetBTLocalDeviceName());
                    break;
                }
#endif

#if defined(CLX_BLE_ISOCHRONOUS)
                case BluetoothMenuItem_BleAudioMenu:
                {
                    bluetoothLowEnergyAudioMenu( bluetoothInfo.stack );
                    break;
                }
#endif /* defined(CLX_BLE_ISOCHRONOUS) */

#if defined(CLX_BLE_CS_REFLECTOR)
                case BluetoothMenuItem_BleCsReflector:
                {
                    lowEnergyCSReflectorMenu(bluetoothInfo.stack, clxGetBTLocalDeviceName());
                    break;
                }
#endif

                case BluetoothMenuItem_TotalMemoryUsage:
                {
#if defined(CLX_WINDOWS)
                    clxConsoleUIEngineText("\nTotal memory usage is %d bytes\n", totalMemoryUsed);
#else
                    clxConsoleUIEngineText("\nAvailable only on Windows\n");
#endif
                    break;
                }

                case BluetoothMenuItem_ReturnToPreviousMenu:
                {
                    return 0;
                }

                default:
                {
                    clxConsoleUIEngineText("\nPlease select the valid menu options...\n");
                    break;
                }
            } // switch (index)
        } // if
    } // while (TRUE)
}

const s1* clxGetBTLocalDeviceName ( void )
{
    return deviceName;
}

ClxStack clxGetBTStackHandle ( void )
{
    return bluetoothInfo.stack;
}
