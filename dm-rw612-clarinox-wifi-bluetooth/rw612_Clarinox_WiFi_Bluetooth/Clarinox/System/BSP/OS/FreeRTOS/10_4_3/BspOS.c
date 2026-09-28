/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                BspOS.c
* Description         Implementation of BSP interfaces and functions for 
*                     Vector Microsar OS
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include "ClxCommon.h"
#include "Thread.Bsp.h"

#include "ClxSemaphore.h"
#include "ClxThread.h"
#include "ClxMutex.h"
#include "ClxTime.h"
#include "ClxBspOsTimer.h"
#include "ClarinoxErrorCodes.h" 

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

//ClxExceptionCallback clxOsAbstractionLayerExceptionFunction = NULL;

static u4 cpuCycleCountH = 0;

ClxResult clxBspThreadInterfaceBindToProcessor (ClxOSThread thread, u4 processorIndex)
{
    return CLX_SUCCESS;
}

/**
 *
 * Thread Interface:
 */
ClxOSThread clxBspThreadInterfaceCreate (void* handle,
                              const char* name,
                              u4 stackSize,
                              u4 priority)
{
    ClxOSThread ret = NULL;
    s4 clxResult = 0;
    clxResult = xTaskCreate((pdTASK_CODE)clxThreadEntryDispatcher,
                                         name,
                            (unsigned short)stackSize,
                                         handle,
                            (unsigned portBASE_TYPE)priority,
                            (xTaskHandle*)&ret);

    if(clxResult != pdPASS)
    {
        while(1);
    }
    else
    {
        return ret;
    }
    
}

ClxResult clxBspThreadInterfaceSuspend (ClxOSThread thread)
{
    /* Individual thread suspension not supported */
    vTaskSuspend((xTaskHandle)thread);
    return (ClxResult)CLX_SUCCESS;
}

ClxResult clxBspThreadInterfaceResume (ClxOSThread thread)
{
    /* Individual thread suspension not supported */
    vTaskResume((xTaskHandle)thread);
    return (ClxResult)CLX_SUCCESS;
}

void clxBspThreadInterfaceDestroy (ClxOSThread thread)
{
   vTaskDelete((xTaskHandle)thread);
}

ClxResult clxBspThreadInterfaceEndCurrentThread (void)
{
   vTaskSuspend(NULL);
   return CLX_SUCCESS;
}

void clxBspThreadInterfaceYieldCurrentThread (void)
{
   taskYIELD();
}

void* clxBspThreadInterfaceGetCurrentThreadOsID(void)
{
    return  (ClxThreadID )xTaskGetCurrentTaskHandle();
}

/**
 *
 * Semaphore Interface:
 */
ClxSemaphore clxCreateSemaphore_( s4 initialValue, const char* file, unsigned int line )
{
    return ( ClxSemaphore ) xSemaphoreCreateCounting(50, initialValue);
}

void clxDeleteSemaphore( ClxSemaphore semaphore )
{
   vSemaphoreDelete((xSemaphoreHandle)semaphore);
}

void clxAcquireSemaphore( ClxSemaphore semaphore )
{
   if( xSemaphoreTake((xSemaphoreHandle)semaphore, (portTickType ) portMAX_DELAY) != pdTRUE )
    {
        BLACKBOX;
        while(1);
    }
}


ClxBinarySemaphore clxCreateBinarySemaphore( boolean initialValue )
{
	ClxBinarySemaphore s = (ClxBinarySemaphore)xSemaphoreCreateBinary();
	if(initialValue)
	{
		clxReleaseBinarySemaphore(s);
	}
    return s;
}

void clxAcquireBinarySemaphore( ClxBinarySemaphore semaphore )
{
    clxAcquireSemaphore( (ClxSemaphore)semaphore);
}


void clxReleaseBinarySemaphore( ClxBinarySemaphore semaphore )
{
    clxReleaseSemaphore( (ClxSemaphore)semaphore);
}

void clxDeleteBinarySemaphore( ClxBinarySemaphore semaphore )
{
    clxDeleteSemaphore( (ClxSemaphore) semaphore);
}

void clxReleaseBinarySemaphoreFromISR ( ClxBinarySemaphore semaphore )
{
	clxReleaseSemaphoreFromISR((ClxSemaphore)semaphore);
}

boolean externalInterruptHandler = FALSE;
void clxReleaseSemaphore( ClxSemaphore semaphore )
{
  if( !externalInterruptHandler )
  {
   if( xSemaphoreGive( (xSemaphoreHandle)semaphore ) != pdTRUE )
    {
    //  clxConsoleUIEngineText("The semaphore count is more than the max uxMaxCount. Please see clxCreateSemaphore \n");
    }
  }
  else
  {
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    if( xSemaphoreGiveFromISR((xSemaphoreHandle)semaphore, &xHigherPriorityTaskWoken) != pdTRUE )
    {
        BLACKBOX;
        while(1);
    }
  }
}

void clxReleaseSemaphoreFromISR( ClxSemaphore semaphore )
{
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    if( xSemaphoreGiveFromISR((xSemaphoreHandle)semaphore, &xHigherPriorityTaskWoken) != pdTRUE )
    {
       // TODO: Find a way to stop from interrupt.
	   // BLACKBOX;
        while(1);
    }
    /* if xHigherPriorityTaskWoken is set to TRUE then request a context switch */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

ClxResult clxTryAcquireSemaphore( ClxSemaphore semaphore )
{
   if(xSemaphoreTake((xSemaphoreHandle)semaphore, (portTickType ) 0) != pdTRUE )
    {
        BLACKBOX;
        while(1);
    }
    else
    {
      return CLX_SUCCESS;
    }
}

ClxResult clxAcquireSemaphoreTimed( ClxSemaphore semaphore, s4 milliseconds )
{
   /*
    * No of ticks are equal to milliseconds, we can directly use milliseconds as tick for time functions
    */
    if( semaphore != NULL )
    {
      if(xSemaphoreTake((xSemaphoreHandle)semaphore, (portTickType ) ( milliseconds / portTICK_RATE_MS )) != pdTRUE )
      {
        return CLX_FAIL;
      }
      else
      {
        return CLX_SUCCESS;
      }
    }
    else
    {
        BLACKBOX;
        while(1);
    }
}

/**
 *
 * Mutex Interface:
 */
#if defined( CLX_DEBUG )
ClxMutex clxCreateMutex_( const char* file, unsigned int line )
#else
ClxMutex clxCreateMutex_( void )
#endif
{
   return ( ClxMutex )xSemaphoreCreateMutex();
}


void clxDeleteMutex( ClxMutex mutex )
{
   vSemaphoreDelete((xSemaphoreHandle)mutex);
}

void clxAcquireMutex( ClxMutex mutex )
{
   xSemaphoreTake((xSemaphoreHandle)mutex, (portTickType ) portMAX_DELAY);
}

void clxReleaseMutex( ClxMutex mutex )
{
   if( xSemaphoreGive( (xSemaphoreHandle)mutex ) != pdTRUE )
    {
        BLACKBOX;
        while(1);
    }
}

ClxResult clxTryAcquireMutex( ClxMutex mutex )
{
   if(xSemaphoreTake((xSemaphoreHandle)mutex, (portTickType ) 0) != pdTRUE )
    {
        BLACKBOX;
        while(1);
    }
    else
    {
      return CLX_SUCCESS;
    }
}

/**
 *
 * Required Time Functions:
 */
void clxSleep( u4 milliseconds )
{
   /*
    * No of ticks are equal to milliseconds we can use ticks instead of milliseconds
    */
   vTaskDelay(milliseconds / portTICK_RATE_MS);
}

void clxGetCurrentTime( struct ClxTimeval* t )
{
  u4 ms = clxTickTime();

  t->tv_sec = ms / 1000;
  t->tv_usec = (ms % 1000) * 1000;
}

u4 clxGetCurrentDate()
{
   return 0;
}

u4 clxTickTime()
{
   //return ( xTaskGetTickCount() / portTICK_RATE_MS );
   return ( xTaskGetTickCount() * portTICK_PERIOD_MS );
}

extern  u4 readCpuCycleCounter (void);
extern uint32_t SystemCoreClock;
u4 clxHighResolutionTime()
{
	/*
	Return value is in microseconds:
	*/
    u4 denum = SystemCoreClock/1000000;
    u4 currentTick = readCpuCycleCounter()/denum;
	return currentTick;
}

void clxUSleep(u4 microseconds)
{
    u4 t1 = clxHighResolutionTime();

    while ((clxHighResolutionTime() - t1) < microseconds)
    {}
}

/**
This function checks whether the Cpu cycle count register has overflown and increments 
an a global 32 bit cpuCycleCountH counter variable.
This functionality enables to maintain 64 bit CPU Cycle count allowing longer
period for high resolution time.

checkCpuCycleCounter() needs to be periodically called via a Timer interrupt or 
"vApplicationTickHook" to ensure overlow of CPU cycle register is detected.
*/
void checkCpuCycleCounter(void)
{
    static u1 cpuCycleCountOverFlowPending = 0;
	u4 cpuCycleCountL = readCpuCycleCounter();

	if(cpuCycleCountL > 0x0FFFFFFFU)
	{
		cpuCycleCountOverFlowPending = 1;
	}

	if((cpuCycleCountL < 0x0FFFFFFFU) && (cpuCycleCountOverFlowPending == 1))
	{
		cpuCycleCountOverFlowPending = 0;
		cpuCycleCountH++;
	}
}


#if defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)

void* clxBspDisableOsScheduler()
{
	vTaskSuspendAll();
	return (void*)NULL;
}

void clxBspEnableOsScheduler(void* lockContext)
{
	xTaskResumeAll();
}


void enableOsScheduler()
{
   vTaskStartScheduler();
}


void disableOsScheduler()
{
   vTaskEndScheduler();
}

#endif // CLX_OS_SCHEDULER_DISABLE_SUPPORTED


void* clarinoxHeapAlloc (u4 size)
{
  return clxAppPoolsetAlloc(  0, __LINE__, size ); // Was implemented by Clarinox as the following (but our hook is different): clxAppPoolsetAlloc(  0, __LINE__, size );
}

void clarinoxHeapFree (void* poolAddress)
{
  clxPoolsetFree( poolAddress );
}

void vendorSpecificEvent(u1 *buffer, u4 length, u4 eventCode)
{
}

void vendorSpecificReturnCode(u4 ocf, u1* data)
{
}

void clxTimeInit()
{
}


/**
 *
 * Timer Interface:
 */
typedef struct ClxOsTimerImp_t
{
    StaticTimer_t          base;

    TimerHandle_t          handle;
    ClxOsTimerCallbackFunc callbackFunc;
    void*                  callbackData;
} ClxOsTimerImp_t;

/*
static void bspOsTimerCallback (TimerHandle_t xTimer)
{
    ClxOsTimerImp_t* osTimer = (ClxOsTimerImp_t*)pvTimerGetTimerID(xTimer);

    osTimer->callbackFunc(osTimer->callbackData);
}
*/
ClxResult clxBspOsTimerCreate(ClxOsTimer*            timer,
                              const char*            name,
                              u4                     period,
                              ClxOsTimerCallbackFunc callbackFunc,
                              void*                  callbackData,
                              ClxOsTimerType         type)
{
    TimerHandle_t    handle  = NULL;
    ClxOsTimerImp_t* osTimer = NULL;

    //int autoReload = (type == ClxOsTimerType_OneShot) ? pdFALSE : pdTRUE;

    if ((timer == NULL) || (callbackFunc == NULL))
    {
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;
    }

    osTimer = (ClxOsTimerImp_t*)clxAppAllocZero(sizeof(ClxOsTimerImp_t));
    CLX_ASSERT(osTimer);
/*
    handle = xTimerCreateStatic(name,
                                pdMS_TO_TICKS(period),
                                (UBaseType_t)autoReload,
                                (void*)osTimer,
                                bspOsTimerCallback,
                                &osTimer->base);
*/
    if (handle == NULL)
    {
        clxPoolsetFree((void*)osTimer);
        return CLX_FAIL;
    }

    osTimer->handle       = handle;
    osTimer->callbackFunc = callbackFunc;
    osTimer->callbackData = callbackData;

    *timer = (ClxOsTimer)osTimer;

    return CLX_SUCCESS;
}

ClxResult clxBspOsTimerStart(ClxOsTimer timer)
{
    int ret;
    ClxOsTimerImp_t* osTimer = (ClxOsTimerImp_t*)timer;

    if (osTimer == NULL)
    {
        return CLX_ERROR_INVALID_HANDLE;
    }

    ret = xTimerStart(osTimer->handle, portMAX_DELAY);

    return ret == pdPASS ? CLX_SUCCESS : CLX_FAIL;
}

boolean clxBspOsTimerIsRunning(ClxOsTimer timer)
{
    int ret;
    ClxOsTimerImp_t* osTimer = (ClxOsTimerImp_t*)timer;

    if (osTimer == NULL)
    {
        return FALSE;
    }

    ret = xTimerIsTimerActive(osTimer->handle);
    return ret == pdFALSE ? FALSE : TRUE;
}

ClxResult clxBspOsTimerRestart(ClxOsTimer timer, u4 newPeriod)
{
    int ret;
    ClxOsTimerImp_t* osTimer = (ClxOsTimerImp_t*)timer;

    if (osTimer == NULL)
    {
        return CLX_ERROR_INVALID_HANDLE;
    }

    if (newPeriod > 0)
    {
        ret = xTimerChangePeriod(osTimer->handle, pdMS_TO_TICKS(newPeriod), portMAX_DELAY);

        if (ret != pdPASS)
        {
            return CLX_FAIL;
        }
    }

    ret = xTimerReset(osTimer->handle, portMAX_DELAY);

    return ret == pdPASS ? CLX_SUCCESS : CLX_FAIL;
}

ClxResult clxBspOsTimerStop(ClxOsTimer timer)
{
    int ret;
    ClxOsTimerImp_t* osTimer = (ClxOsTimerImp_t*)timer;

    if (osTimer == NULL)
    {
        return CLX_ERROR_INVALID_HANDLE;
    }

    ret = xTimerStop(osTimer->handle, portMAX_DELAY);

    return ret == pdPASS ? CLX_SUCCESS : CLX_FAIL;
}

ClxResult clxBspOsTimerDelete(ClxOsTimer timer)
{
    int ret;
    ClxOsTimerImp_t* osTimer = (ClxOsTimerImp_t*)timer;

    if (osTimer == NULL)
    {
        return CLX_ERROR_INVALID_HANDLE;
    }

    /* First, stop the timer (in case it's running): */
    ret = xTimerStop(osTimer->handle, portMAX_DELAY);

    if (ret != pdPASS)
    {
        return CLX_FAIL;
    }

    /* Wait until the timer is not running any longer: */
    while (xTimerIsTimerActive(osTimer->handle) != pdFALSE)
    {
        clxSleep(10);
    }

    /* Now, we can delete the timer: */
    ret = xTimerDelete(osTimer->handle, portMAX_DELAY);

    if (ret != pdPASS)
    {
        return CLX_FAIL;
    }

    clxPoolsetFree((void*)timer);

    return CLX_SUCCESS;
}

/*Need to implement applicationidletask() in Bsp.cpp*/
extern void applicationidletask(void);
void vApplicationIdleHook( void )
{
   applicationidletask();
}

void vApplicationTickHook( void )
{
   /* Check whether the Cpu Cycle Counter has overflown */
   checkCpuCycleCounter();
}

/**
IDLE TASK HOOK
Description : This is a Idle task hook function.
This function should be called by the OS idle task and it should not block.
The global externed variable "sleepModeEnabled" is used to control entering and exiting sleep mode
*/
boolean sleepModeEnabled = FALSE;

void applicationidletask(void)
{
    if(sleepModeEnabled)
    {
         /* Clear SLEEPDEEP bit of Cortex-M7 System Control Register */
         // SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
         /* Enter sleep mode and wake up on sys tick interrupt */
         //__WFI();

    }
}
