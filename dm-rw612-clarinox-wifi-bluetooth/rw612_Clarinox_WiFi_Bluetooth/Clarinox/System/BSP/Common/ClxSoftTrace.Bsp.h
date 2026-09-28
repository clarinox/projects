#ifndef __ClxTrace_Bsp__
#define __ClxTrace_Bsp__

/*******************************************************************************
* 
* Project           :   Clarinox Debugger
* File              :   ClxTrace.Bsp.h
* Description       :   ClariFi Insight (ClarinoxTrace) BSP interface
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif


#if defined(CLX_TRACE)


extern void* clxTraceBsp_Init(u4* traceBufferSizeInBytes);

extern void* clxTraceBsp_Lock();

extern void clxTraceBsp_Unlock(void* lockStatus);

extern u2 clxTraceBsp_GetTimeStampMultiplier();
extern u2 clxTraceBsp_GetTimeStampDivider();

extern void clxTraceBsp_GetTimeStamp(u2* timeStamp_MSB, u4* timeStamp_LSB);


#endif // #if defined(CLX_TRACE)


#ifdef __cplusplus
}
#endif


#endif  // __ClxTrace_Bsp__
