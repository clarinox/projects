/*******************************************************************************
*
* Project             Koala Application
* File                ClxBspThread.c
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
#include "ClxBspConfig.h"
#include "ClxBspInit.h"

extern int                  	clarinoxMain(void);

/**
An array of 5, and type u2, which maps the ClarinoxBlue platform-independent thread priorities
to underlying platform priorities. The first index (index 0) of the array represents the highest priority,
while the last index (index 4) of the array represents the lowest priority.
If the table is not defined in the BSP, the default priority of the underlying platform will be used for all
threads. 

ALL priorities MUST be defined.

Clarinox threads:
- Driver thread                         : Highest priority (index 0)
- Stack thread                          : Medium priority  (index 2)
- Application Callback thread           : Medium priority  (index 2)
- Timer thread                          : High priority    (index 1)
- Debug thread (if available)           : Lowest priority  (index 4)
- Console Engine thread (if available)  : Lowest priority  (index 4)
*/

const u2 wlanPlatformTaskPriorityTable[5]               = { DEFAULT_WLAN_DRIVER_HIGH_TASK_PRIORITY,
                                                        DEFAULT_WLAN_DRIVER_MEDIUM_HIGH_TASK_PRIORITY,
                                                        DEFAULT_WLAN_DRIVER_MEDIUM_TASK_PRIORITY,
                                                        DEFAULT_WLAN_DRIVER_MEDIUM_LOW_TASK_PRIORITY,
                                                        DEFAULT_WLAN_DRIVER_LOW_TASK_PRIORITY};

const u2 bluetoothPlatformTaskPriorityTable[5]          = { DEFAULT_BLUETOOTH_DRIVER_HIGH_TASK_PRIORITY,
                                                        DEFAULT_BLUETOOTH_DRIVER_MEDIUM_HIGH_TASK_PRIORITY,
                                                        DEFAULT_BLUETOOTH_DRIVER_MEDIUM_TASK_PRIORITY,
                                                        DEFAULT_BLUETOOTH_DRIVER_MEDIUM_LOW_TASK_PRIORITY,
                                                        DEFAULT_BLUETOOTH_DRIVER_LOW_TASK_PRIORITY };


const u2 clarinoxFreeRTOSSoftFrameTaskStackSizeTable[4] = { CLARINOX_SOFTFRAME_TIMER_THREAD_STACK_SIZE,
                                                        CLARINOX_SOFTFRAME_DEBUG_THREAD_STACK_SIZE,
                                                        CLARINOX_SOFTFRAME_UI_THREAD_STACK_SIZE,
                                                        CLARINOX_SOFTFRAME_TERMINAL_EMULATOR_THREAD_STACK_SIZE };

const u2 clarinoxFreeRTOSWlanTaskStackSizeTable[2]      = { CLARINOX_WLAN_STACK_THREAD_STACK_SIZE,
                                                        CLARINOX_WLAN_APPLICATION_THREAD_STACK_SIZE };

const u2 clarinoxFreeRTOSBluetoothTaskStackSizeTable[3] = { CLARINOX_BLUETOOTH_APPLICATION_THREAD_STACK_SIZE,
                                                        CLARINOX_BLUETOOTH_STACK_THREAD_STACK_SIZE,
                                                        CLARINOX_BLUETOOTH_UARTRX_THREAD_STACK_SIZE };

/**
This is the first thread entry function. This function calls the Clarinox application (clarinoxMain).
*/
ClxResult mainThreadEntry(void* arg)
{
    clarinoxMain();
    return CLX_SUCCESS;
 }


