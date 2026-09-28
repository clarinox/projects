/*******************************************************************************
*
* Project             Koala Application
* File                ClxBspInit.cpp
* Description         Clarinox heap functions and variables are defined here.
*
* This file contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#include "ClxBsp.h"
#include "ClarinoxBlueConst.h"
#include "Bsp.h"
#include "ClxBspConfig.h"
#include "ClxBspInit.h"

#if defined (CLX_BLE_ISOCHRONOUS)
#include "Iso.Ble.Interface.h"
#endif /* defined (CLX_BLE_ISOCHRONOUS) */

static const s1*  debugConfigFileName 	   = "SoftFrame.cfg";

extern    void                               initCpuCycleCounter();
extern    void                               clxWlanLowLevelInit();

#if defined (CLX_BLE_ISOCHRONOUS)
extern struct ClxBleIsoInterface* clxCreateIsoInterface(void);
#endif /* #if defined (CLX_BLE_ISOCHRONOUS) */

static void processSoftFrameConfigParams(ClxGetSoftFrameIntegerParam getIntParam, ClxGetSoftFrameStringParam getStrParam)
{
    clxProcessSoftFrameConfigParamsForWlan(getIntParam, getStrParam);
}

void clxInitBsp (void)
{
#if defined(CLX_TRACE)
    clxTraceInit();
#endif

    /* Configure CPU clock counter register */
    initCpuCycleCounter();

    /* User provided printf/scanf functions that handles redirected debug printf/scanf calls. 
     *Otherwise platform specific default printf/scanf functions will be used 
     */
    userPrintfFunction                               = &printfFunction;
    userGetInputFunction                             = &getInputFunction;

    /*Hook to user provided SDIO BSP implementation for a target platform to interface with the Wilink-8 chip*/
    //clxSdioBspInterface                              = &clxSdioTargetSpecificBspInterface;

    //clxHciSendVendorSpecificCommands                 = PLATFORM_VendorSpecificInit;

    /*These values map the ClarinoxWifi platform-independent thread priorities to underlying platform priorities.*/
    clarinoxWlanPlatformTaskPriorityTable            = (u2*)&wlanPlatformTaskPriorityTable;

    /*These values map the Clarinox Bluetooth platform-independent thread priorities to underlying platform priorities.*/
    clarinoxBluePlatformTaskPriorityTable            = (u2*)&bluetoothPlatformTaskPriorityTable;

#if defined(CLX_ENABLE_BLUETOOTH)
    /*Hook to Bluetooth BSP driver interface.*/
    clarinoxBlueDriverInterface                      = &clxBlueDriverInterface;
#endif // #if defined(CLX_ENABLE_BLUETOOTH)

    /* Hook to user provided Vendor Specific BSP implementation for a target platform to interface with the SDIO interface */
    //clxUartBspInterface                               = &clxUartTargetSpecificBspInterface;
    clxUartBspInterface                              = &clxUartGenericBspInterface;

    /*User provided stack size for Clarinox SoftFrame threads*/
    clarinoxPlatformSoftFrameTaskStackSizeTable      = (u2*)&clarinoxFreeRTOSSoftFrameTaskStackSizeTable;

    /*User provided stack size for Clarinox WLAN threads*/
    clarinoxPlatformWlanTaskStackSizeTable			 = (u2*)&clarinoxFreeRTOSWlanTaskStackSizeTable;

    /*User provided stack size for Clarinox Bluetooth threads*/
    clarinoxPlatformBluetoothTaskStackSizeTable		 = (u2*)&clarinoxFreeRTOSBluetoothTaskStackSizeTable;

    /*
    Name of the debugging configuration file:
    */
    clxSoftFrameConfigFileName                       = debugConfigFileName;

    /*Hook that defines user implementations for the non-volatile storage system implementation*/
    clxFileBspInterface                              = &clxMemoryFileInterface;

#if defined (CLX_BLE_ISOCHRONOUS)
    clxBleIsoInterface = clxCreateIsoInterface();
#endif /* defined (CLX_BLE_ISOCHRONOUS) */

    userExceptionFunction                            = &userExceptionHandler;

    clxProcessSoftFrameConfigParams = processSoftFrameConfigParams;

    /* Configure the WL_EN and WL_IRQ pin */
    clxWlanLowLevelInit();

    initROMFileSystemMap();
}

