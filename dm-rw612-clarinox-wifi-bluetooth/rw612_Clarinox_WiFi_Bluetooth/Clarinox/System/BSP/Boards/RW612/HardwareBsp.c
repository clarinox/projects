/*******************************************************************************
*
* Project
* File                HardwareBsp.c
* Description         Hardware related functions are defined here.
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

void initCpuCycleCounter (void);
u4   readCpuCycleCounter (void);
void hardwareInit        (void);
ClxResult   chkCpuCycleCountTask    (void*);
extern void checkCpuCycleCounter(void);
typedef  volatile  unsigned int CPU_REG32;
CPU_REG32* BSP_REG_DWT_CYCCNT;
CPU_REG32* BSP_REG_DWT_CONTROL;
CPU_REG32* BSP_REG_DWT_DEMCR;

void initCpuCycleCounter()
{
    BSP_REG_DWT_CYCCNT   = (CPU_REG32 *)0xE0001004;
    BSP_REG_DWT_CONTROL  = (CPU_REG32 *)0xE0001000;
    BSP_REG_DWT_DEMCR    = (CPU_REG32 *)0xE000EDFC;

    *BSP_REG_DWT_DEMCR   = *BSP_REG_DWT_DEMCR | 0x01000000;
    *BSP_REG_DWT_CONTROL = *BSP_REG_DWT_CONTROL | 1 ;
}

u4 readCpuCycleCounter (void)
{
    u4  ret;
    ret = *BSP_REG_DWT_CYCCNT;
    return (ret);
}
  
/* Initialize Hardware Modules */
void hardwareInit()
{
    initCpuCycleCounter();

    static ClxThreadHandle chkCpuCycleCountTaskHandle = NULL;

    if(chkCpuCycleCountTaskHandle == NULL)
    {
    	chkCpuCycleCountTaskHandle = clxBeginThread( chkCpuCycleCountTask, 0, "chkCpuCycleCountTask", 256U, clarinoxWlanPlatformTaskPriorityTable, ClxThreadPriority_Lowest);
    }
}

/**
This task periodically checks whether the CPU Cycle count hardware register has overflowed,
and maintains a higher level Software counter.
 */
ClxResult   chkCpuCycleCountTask    (void* x)
{
	while(1)
	{
		/* Check whether the Cpu Cycle Counter has overflown */
		// TODO  we need to find a cleaner way to have timer overflow. checkCpuCycleCounter();
		clxSleep(5);
	}

	//return CLX_SUCCESS;
}
