/** @file main.c
 *
 *  @brief main file
 *
 *  Copyright 2020 NXP
 *  All rights reserved.
 *
 *  SPDX-License-Identifier: BSD-3-Clause
 */

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////

// SDK Included Files
#include "board.h"
#include "fsl_debug_console.h"
#include "wifi_bt_module_config.h"
#include "app.h"
#ifndef RW610
#include "wifi_bt_config.h"
#else
#include "fsl_power.h"
#include "fsl_ocotp.h"
#endif
#if CONFIG_HOST_SLEEP
#include "host_sleep.h"
#endif

#include "task.h"

#include "ClxBspConfig.h"
//#include "led_button_if.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Task priorities. */
#define clx_wlan_task_PRIORITY (configMAX_PRIORITIES - 1)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void clx_application_task(void *pvParameters);
extern int clarinoxMain();

/*******************************************************************************
 * Code
 ******************************************************************************/

static void printSeparator(void)
{
    PRINTF("========================================\r\n");
}

int main(void)
{
    BaseType_t result = 0;
    (void)result;

    BOARD_InitHardware();
#ifdef RW610
    POWER_PowerOffBle();
#endif

    printSeparator();
    (void)PRINTF("clarinox wifi and bluetooth demo\r\n");
    printSeparator();

    if (xTaskCreate(clx_application_task, "clx_application_task", MAIN_THREAD_STACK_SIZE, NULL, clx_wlan_task_PRIORITY, NULL) !=
        pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }

    vTaskStartScheduler();
    for (;;)
        ;
}

static void clx_application_task(void *pvParameters)
{
    clarinoxMain();
}
