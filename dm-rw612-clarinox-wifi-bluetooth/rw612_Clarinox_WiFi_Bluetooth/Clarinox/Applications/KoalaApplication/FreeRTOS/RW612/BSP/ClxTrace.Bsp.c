/*******************************************************************************
* 
* Project           :   Clarinox Debugger
* File              :   ClxSoftTrace.Bsp.c
* Description       :   Clarinox SoftTrace BSP Implementation
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/


#include "ClxBsp.h"
//#include <cr_section_macros.h>


#if defined(CLX_TRACE)
#include "memory_sections.h"

#define INSIGHT_TRACE_BUFFER_SIZE			1024*1024
DATA_NORMAL_NON_INIT(static u4 insightTraceBuffer[INSIGHT_TRACE_BUFFER_SIZE / 4]);


void* clxTraceBsp_Init(u4* traceBufferSizeInBytes)
{
	*traceBufferSizeInBytes = INSIGHT_TRACE_BUFFER_SIZE;

	return insightTraceBuffer;
}

void* clxTraceBsp_Lock()
{
	TX_INTERRUPT_SAVE_AREA

	TX_DISABLE
	return (void*)interrupt_save;
}

void clxTraceBsp_Unlock(void* lockContext)
{
	TX_INTERRUPT_SAVE_AREA

	interrupt_save = (unsigned int)lockContext;
	TX_RESTORE
}

u2 clxTraceBsp_GetTimeStampMultiplier()
{
	return 1;
}

u2 clxTraceBsp_GetTimeStampDivider()
{
	return 600;
}

void clxTraceBsp_GetTimeStamp(u2* timeStamp_MSB, u4* timeStamp_LSB)
{
	*timeStamp_MSB = 0;
	*timeStamp_LSB = TX_TRACE_TIME_SOURCE;
}


#endif // #if defined(CLX_TRACE)

