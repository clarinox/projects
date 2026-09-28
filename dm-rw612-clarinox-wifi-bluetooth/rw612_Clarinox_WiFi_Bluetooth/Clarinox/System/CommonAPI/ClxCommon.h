#ifndef ClxCommon_h
#define ClxCommon_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxCommon.h
* Description         ClarinoxSoftFrame Common header file
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#if defined(CLX_MICROSOFT) 
#   define CLX_USE_STD_STRING_H
#   define CLX_VARIADIC_MACROS_SUPPORTED
#   define CLX_COMPILER_INLINE_FUNC_KEYWORD     	__inline    
#elif defined(CLX_GNU) 
#   define CLX_USE_STD_STRING_H
#   define CLX_VARIADIC_MACROS_SUPPORTED
#	if !defined(__cplusplus) && (__STDC_VERSION__ >= 199901L)
#		define CLX_COMPILER_INLINE_FUNC_KEYWORD 	static inline
#	endif
#elif defined(CLX_IAR)
#   define CLX_USE_STD_STRING_H
#   define CLX_VARIADIC_MACROS_SUPPORTED
#   define CLX_COMPILER_INLINE_FUNC_KEYWORD     	static __inline
#elif defined(CLX_MULTI)
#   define CLX_USE_STD_STRING_H
#   define CLX_COMPILER_INLINE_FUNC_KEYWORD static inline
#elif defined(CLX_KEIL) 
#   define CLX_USE_STD_STRING_H
#elif defined(CLX_CLANG)
#   define CLX_USE_STD_STRING_H
#elif defined(CLX_DIAB)
#   define CLX_USE_STD_STRING_H
#elif defined (CLX_TASKING)
#   define CLX_USE_STD_STRING_H
#else
#   error "Please define the compiler"
#endif


#if defined(__cplusplus)
#   define CLX_INLINE   inline
#elif defined(CLX_COMPILER_INLINE_FUNC_KEYWORD)
#   define CLX_INLINE   CLX_COMPILER_INLINE_FUNC_KEYWORD
#endif


#if defined( CLX_LINUX ) || defined( CLX_WINDOWS )
/* For Windows & Linux (Posix) we have the OS bindings implemented as part of the SoftFrame */

#  if defined(CLX_BSP_THREAD_INTERFACE)
#    undef CLX_BSP_THREAD_INTERFACE
#  endif
#  if defined(CLX_BSP_MUTEX_INTERFACE)
#    undef CLX_BSP_MUTEX_INTERFACE
#  endif
#  if defined(CLX_BSP_SEMAPHORE_INTERFACE)
#    undef CLX_BSP_SEMAPHORE_INTERFACE
#  endif
#  if defined(CLX_BSP_TIME_INTERFACE)
#    undef CLX_BSP_TIME_INTERFACE
#  endif

#else

#  if !defined(CLX_BSP_THREAD_INTERFACE)
#    define CLX_BSP_THREAD_INTERFACE
#  endif
#  if !defined(CLX_BSP_MUTEX_INTERFACE)
#    define CLX_BSP_MUTEX_INTERFACE
#endif
#  if !defined(CLX_BSP_SEMAPHORE_INTERFACE)
#    define CLX_BSP_SEMAPHORE_INTERFACE
#  endif
#  if !defined(CLX_BSP_TIME_INTERFACE)
#    define CLX_BSP_TIME_INTERFACE
#  endif

#endif


#include <stddef.h>
#include <stdarg.h>
#if defined(CLX_USE_STD_STRING_H)
#   include <string.h>
#endif

#include "ClxTypes.h"
#include "ClxPackages.h"
#include "ClxCommonDefines.h"
#include "ClxMemoryPoolset.h"
#include "ClarinoxConst.h"
#include "ClarinoxErrorCodes.h"
#include "ClxConsole.h"
#include "ClxFile.h"
#include "ClxSemaphore.h"
#include "ClxMutex.h"
#include "ClxThread.h"
#include "ClxTime.h"
#include "ClxStandard.h"
#include "ClxCQueueable.h"
#include "ClxQueueTemplate.h"
#include "ConsoleUIEngine.h"
#include "ClxPrivateMemoryPool.h"
#include "ClxConfigParams.h"
#include "ClxFifoList.h"
#include "ClxTaskSchedulerApi.h"
#include "A2L.h"
#include "A2L.RPC.h"
#include "ClxDataConversion.h"
#include "TerminalEmulator.h"
#include "ClxCQueueable.h"
#include "ClxQueueTemplate.h"
#include "ClxPrivateMemoryPool.h"
#include "ClxBuddyMemoryHeap.h"
#include "ClxPriorityQueueHeap.h"
#include "ClxDataFIFO.h"
#include "ClxMailBox.h"
#include "ClxSocketWrapper.h"
#include "Clarinox.Test.h"
#include "ClxSoftTrace.h"
#include "ClarinoxCLI.h"


/** \file ClxCommon.h
    \brief ClxCommon.h contains the ClarinoxSoftFrame common include files
*/


#endif    // ClxCommon_h
