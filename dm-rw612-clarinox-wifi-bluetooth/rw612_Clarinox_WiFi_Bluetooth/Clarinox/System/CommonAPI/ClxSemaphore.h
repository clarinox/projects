#ifndef ClxSemaphore_h
#define ClxSemaphore_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxSemaphore.h
* Description         Includes target Operating System dependent definitions
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

// _____________________________________________________________________________
//
// ClxSemaphore
// _____________________________________________________________________________
//

#ifdef __cplusplus
extern "C" {
#endif


/**
A type for holding the semaphore handle for the current operating system.
Clarinox Semaphore APIs use this semaphore handle for most of the semaphore operations.
*/
typedef void* ClxSemaphore;

/**
The purpose of this function is to create a semaphore and initialize it.
Semaphore pointer is returned to be used in the other semaphore APIs.
\param[ in ] initialValue is the initial value of the semaphore.
\param[ in ] file is the file name where this function is called. Used for the debug version of the stack.
\param[ in ] line is the line number where this function is called. Used for the debug version of the stack.
Usually zero to indicate no events have occurred on the semaphore.
\return ClxSemaphore
\retval Non-zero         ClxSemaphore handle
\retval zero             clxCreateSemaphore failed
*/
extern  ClxSemaphore clxCreateSemaphore_( s4 initialValue, const char* file, unsigned int line );
#define clxCreateSemaphore( X ) clxCreateSemaphore_( (X), __FILE__, __LINE__ )

/**
The purpose of this function is to create a semaphore and initialize it.
Semaphore pointer is returned to be used in the other semaphore APIs.
\param[ in ] initialValue is the initial value of the semaphore.
\param[ in ] name is the name to uniquely identify the semaphore. Used for identify the semaphore during run time with OS statistics.
Usually zero to indicate no events have occurred on the semaphore.
\return ClxSemaphore
\retval Non-zero         ClxSemaphore handle
\retval zero             clxCreateSemaphore failed
*/
extern  ClxSemaphore clxCreateNamedSemaphore_( s4 initialValue, const char* name);
#define clxCreateNamedSemaphore( X , NAME ) clxCreateNamedSemaphore_( (X) , (NAME) )

/**
This function deletes the semaphore specified by the handle.
** <!-- Parameters -->
\param[ in ] semaphore is the handle for the semaphore
*/
extern  void       clxDeleteSemaphore              ( ClxSemaphore semaphore );

/**
This function helps to restrict access to a shared resource and lock it for other's use.
The acquire operation decrements the value of the semaphore. If the value is already zero
then the current thread starts waiting for the semaphore to be released.
\param[ in ] semaphore is the handle for the semaphore
*/
extern  void       clxAcquireSemaphore             ( ClxSemaphore semaphore );

/**
The purpose of this function is to release an access to a shared resource
by unlocking it for other's use. If there are no threads blocked for this
semaphore then this call increments the value of the semaphore.
If there is a thread waiting for this semaphore, then the scheduler adds that thread into
the ready list for execution. Execution time would depend on the operating system's scheduling settings.

NOTE : Do not call this function in the context of a CPU Interrupt Service Routine (ISR). Call #clxReleaseSemaphoreFromISR instead.
\param[ in ] semaphore is the handle for the semaphore
*/
extern  void       clxReleaseSemaphore             ( ClxSemaphore semaphore );

/**
This function is the same as clxReleaseSemaphore. However, it is called only in the context
of a CPU interrupt service routine.

NOTE : Do not call this function in the context of an OS thread/task. Call #clxReleaseSemaphore instead.

\param[ in ] semaphore is the handle for the semaphore
*/
extern  void       clxReleaseSemaphoreFromISR             ( ClxSemaphore semaphore );

/**
This function is a non-blocking version of clxAcquireSemaphore.
\sa clxAcquireSemaphore. It does function very similar to the
clxAcquireSemaphore, except if the value of the semaphore is already zero then the function
returns with a failed status. If the resource is available,
then the function works exactly the same way as clxAcquireSemaphore would do.
\param[ in ] semaphore is the handle for the semaphore
\return status
\retval CLX_SUCCESS Operation completed successfully.
\retval CLX_FAIL    Semaphore is already taken
*/
extern  ClxResult  clxTryAcquireSemaphore          ( ClxSemaphore semaphore );

/**
This function is a timed version of clxAcquireSemaphore. It is very similar to the
clxAcquireSemaphore, except if the resource is busy it waits for the time given in milliseconds
parameter. The status returns as fail if the resource is not released within this waiting period.
\param[ in ] semaphore is the handle for the semaphore
\param[ in ] milliseconds is the time out period in milliseconds
\return status
\retval CLX_SUCCESS Operation completed successfully.
\retval CLX_FAIL    Semaphore could not be taken within given time (timed out)
*/
extern  ClxResult  clxAcquireSemaphoreTimed        ( ClxSemaphore semaphore, s4 milliseconds );


struct ClxBinarySemaphoreStruct;

/**
A type for holding a handle to a binary semaphore object.
*/
typedef struct ClxBinarySemaphoreStruct* ClxBinarySemaphore;

/**
The purpose of this function is to create a binary semaphore and initialize it.
Binary semaphore pointer is returned to be used in the other binary semaphore APIs.

\param[ in ] initiallySet TRUE if the binary semaphore is initially available. FALSE otherwise.
\return ClxBinarySemaphore
\retval Non-zero         ClxBinarySemaphore handle
\retval zero             clxCreateBinarySemaphore failed
*/
extern ClxBinarySemaphore clxCreateBinarySemaphore(boolean initiallySet);

/**
Acquires the binary semaphore.
\param[ in ] semaphore is the handle for the binary semaphore.
*/
extern void clxAcquireBinarySemaphore ( ClxBinarySemaphore semaphore );

/**
Releases the binary semaphore. This function shall NOT be called in the context of an ISR.
\param[ in ] semaphore is the handle for the binary semaphore.
*/
extern  void clxReleaseBinarySemaphore ( ClxBinarySemaphore semaphore );

/**
Releases the binary semaphore. his function shall be called in the context of an ISR.  
\param[ in ] semaphore is the handle for the binary semaphore.
*/
extern  void clxReleaseBinarySemaphoreFromISR ( ClxBinarySemaphore semaphore );

/**
Deletes the binary semaphore object. If any thread is currently sleeping on this object, a BLACKBOX will occur.
\param[ in ] semaphore is the handle for the binary semaphore.
*/
extern  void clxDeleteBinarySemaphore ( ClxBinarySemaphore semaphore );


/**
ClxSemaphore.h contains the semaphore implementation
*/

#ifdef __cplusplus
}
#endif


#endif    // ClxSemaphore_h

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
