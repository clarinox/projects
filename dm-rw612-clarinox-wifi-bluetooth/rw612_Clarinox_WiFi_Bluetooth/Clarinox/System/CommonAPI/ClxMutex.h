#ifndef ClxMutex_h
#define ClxMutex_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxMutex.h
* Description         Includes target Operating System dependent definitions
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



// _____________________________________________________________________________
//
// ClxMutex     (There is no timed wait support)
// _____________________________________________________________________________
//


/**
Mutex handle.
*/
#if defined(CLX_BARE_METAL_SOFTFRAME)

typedef u1 ClxMutex;

#   define clxCreateMutex()             0
#   define clxDeleteMutex(mutex)
#   define clxAcquireMutex(mutex)
#   define clxTryAcquireMutex(mutex)
#   define clxReleaseMutex(mutex)

#else

typedef void* ClxMutex;


/**
The purpose of this function is to create and initialize a mutex.

\return ClxMutex
\retval Non-zero         Operation completed successfully.
\retval zero             clxCreateMutex failed.
*/

#if defined( CLX_DEBUG )
extern ClxMutex clxCreateMutex_( const char* file, unsigned int line );
#   define clxCreateMutex() clxCreateMutex_( __FILE__, __LINE__ )
#else
extern ClxMutex clxCreateMutex_( void );
#   define clxCreateMutex() clxCreateMutex_()
#endif
/**
The purpose of this function is to delete a mutex when it is no longer required.
\param[ in ] mutex is the handle for the mutex
*/
extern  void            clxDeleteMutex                  ( ClxMutex mutex );

/**
The purpose of this function is to access to a resource and lock it for other's use.
Once a resource is accessed then other threads requiring access are blocked until
this mutex is released.
\param[ in ] mutex is the handle for the mutex
*/
extern  void            clxAcquireMutex                 ( ClxMutex mutex );

/**
This function is a non-blocking version of clxAcquireMutex. It does function very similar to the
clxAcquireMutex, except if the mutex is already acquired then this function returns with a failed status.
If the resource is available, then the function works exactly the same way as clxAcquireMutex would do.
\param[ in ] mutex is the handle for the mutex
\return status
\retval CLX_SUCCESS Operation completed successfully.
\retval CLX_FAIL    Mutex is already taken
*/
extern  ClxResult       clxTryAcquireMutex              ( ClxMutex mutex );

/**
The purpose of this function is to release a resource by unlocking it for other's use.
If there is a thread waiting for this mutex, then the scheduler adds that thread into
the ready list for execution. Execution time would depend on the operating system's scheduling settings.
\param[ in ] mutex is the handle for the mutex
*/
extern  void            clxReleaseMutex                 ( ClxMutex mutex );

/**
ClxMutex.h contains the ClarinoxSoftFrame mutex implementation
*/

#endif // #if defined(CLX_BARE_METAL_SOFTFRAME)

#ifdef __cplusplus
}
#endif

#endif    // ClxMutex_h

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : C macros shall only expand to a braced initialiser,        */
/*                 a constant, a string literal, a parenthesised expression,  */ 
/*				   a type qualifier, a storage class specifier,               */
/*				   or a do-whilezero construct.                               */ 
/* Rule          : MISRA-C:2004 Rule 19.4                                     */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */ 
/*                 platforms. Used to provide better flexibility for templated*/ 
/*				   code to eliminate programmer errors.                       */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : A function should be used in preference to a function-like */
/*                 macro.                                                     */ 
/* Rule          : MISRA-C:2004 Rule 19.7                                     */ 
/* Justification : No risk identified. Used to provide better performance in  */
/*                 embedded system environments that do not support efficient */
/*				   functions inlining.                                        */
/******************************************************************************/


/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/
