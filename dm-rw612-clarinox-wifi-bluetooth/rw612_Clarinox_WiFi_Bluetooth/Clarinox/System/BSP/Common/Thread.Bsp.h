#ifndef Thread_Bsp_h
#define Thread_Bsp_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                Thread.Bsp.h
* Description         Declares an OS thread interface implemented by BSP 
*                     call-back functions
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


/**
This following functions make up the BSP thread interface which is used by SoftFrame threading architecture.

NOTE : The following functions are not to be called directly by the application. The application MUST use the SoftFrame
threading API functions instead. However, when this interface is defined, it is possible to use SoftFrame threading API
functions WITHOUT initializing SoftFrame (by a call to initializeClarinoxSoftFrame() function). This is useful when using the
threading API functions is desired while the entire services of ClarinoxSoftFrame is not required.
*/

#ifdef __cplusplus
extern "C" {
#endif

  
#if defined(CLX_BSP_THREAD_INTERFACE)
  
/**
An object which identifies a valid thread in the underlying operating system. 
The value is specific to the BSP implementation of the thread interface.
A value of NULL implies that the variable does not identify a valid thread.
*/
typedef void* ClxOSThread;

/**
The entry function of all BSP threads. The implementation of this function calls the correct entry function for each thread.
NOTE : Not to be called directly. Must be passed to the OS-specific thread initialization API function as the entry function
of the thread.

\param[ in ] handle An internal handle which is used by SoftFrame to identify the thread. This is the same value as passed to
the implementation of ClxThreadBspInterfaceStruct.createThread (first argument).

\return The return value of the thread when terminated.
*/
extern ClxResult clxThreadEntryDispatcher( void* handle );

/**
Creates and starts a new OS thread. The internally-defined function clxThreadEntryDispatcher must always be passed to the
newly-created thread as the entry point, with "handle" passed as the argument of the entry function. clxThreadEntryDispatcher will
then call the correct entry function on behalf of the BSP implementation.

\param[ in ] handle An internal Clarinox-specific handle to the thread. This value must be passed to clxThreadEntryDispatcher entry
function as its single argument.

\param[ in ] name Name of the new thread as a null-terminated UTF-8 string. May be ignored if the underlying platform does not support
names for threads.

\param[ in ] stackSize The size, in bytes, of the thread stack for this new thread. If 0, the implementation must use a default value.

\param[ in ] priority The priority of the new thread.

\return An implementation-specific object which identifies the new thread. This object will be passed to other function of this interface.
*/
extern ClxOSThread clxBspThreadInterfaceCreate (void* handle, 
                                                const char* name, 
                                                u4 stackSize, 
                                                u4 priority);


#if defined(CLX_SYSTEM_THREADS_SUPPORTED)
/**
Creates and starts a new OS thread. The internally-defined function clxThreadEntryDispatcher must always be passed to the
newly-created thread as the entry point, with "handle" passed as the argument of the entry function. clxThreadEntryDispatcher will
then call the correct entry function on behalf of the BSP implementation.

\param[ in ] handle An internal Clarinox-specific handle to the thread. This value must be passed to clxThreadEntryDispatcher entry
function as its single argument.

\param[ in ] name Name of the new thread as a null-terminated UTF-8 string. May be ignored if the underlying platform does not support
names for threads.

\param[ in ] stackSize The size, in bytes, of the thread stack for this new thread. If 0, the implementation must use a default value.

\param[ in ] priority The priority of the new thread.

\return An implementation-specific object which identifies the new thread. This object will be passed to other function of this interface.
*/
extern ClxOSThread clxBspThreadInterfaceCreateSystemThread (void* handle, 
                                                            ClxSystemThreadID systemThread,
                                                            u4 flags);

#endif // #if defined(CLX_SYSTEM_THREADS_SUPPORTED)

/**
Suspends the execution of a thread as identified by the "thread" argument. The current thread (in the context of which this function is called)
MUST NOT be suspended by a call to this function.
    
This function MUST be implemented if the underlying operating system supports this operation.
Otherwise, the function MUST return CLX_ERROR_INVALID_REQUEST.

\param[ in ] thread The object identifying the thread.

\return CLX_SUCCESS if the operation has been successful.
Any other value specifies failure.
*/
extern ClxResult clxBspThreadInterfaceSuspend (ClxOSThread thread);

/**
Resumes the execution of a thread as identified by the "thread" argument. The thread must have been previously suspended by a call to suspendThread().
    
This function MUST be implemented if the underlying operating system supports this operation.
Otherwise, the function MUST return CLX_ERROR_INVALID_REQUEST.

\param[ in ] thread The object identifying the thread.

\return CLX_SUCCESS if the operation has been successful.
Any other value specifies failure.
*/
extern ClxResult clxBspThreadInterfaceResume (ClxOSThread thread);

/**
In a multi-core platform, binds a thread to be scheduled and executed on only one of the processor cores.
    
This function MUST be implemented if the underlying operating system and platform supports this operation.
Otherwise, the function MUST return CLX_SUCCESS.

\param[ in ] thread The object identifying the thread.
\param[ in ] processorIndex The index of the processor core on which the thread is to be bound. This is a
zero-based index (e.g. The first processor core has index 0).

\return CLX_SUCCESS if the operation has been successful, or the operation is not supported by the
underlying operating system or platform.
Any other value specifies failure.
*/
extern ClxResult clxBspThreadInterfaceBindToProcessor (ClxOSThread thread, u4 processorIndex);

/**
Destroys any object (memory) associated to the thread as identified by the "thread" argument. 
    
NOTE : Generally, this function is called only when the thread has already terminated (its entry function has returned).
However, in rare cases, this function may be called when the thread is still running. An implementation must be able to
handle this situation peacefully (e.g. the implementation must not crash or lead to memory corruption).

\param[ in ] thread The object identifying the thread.
*/
extern void clxBspThreadInterfaceDestroy (ClxOSThread thread);

/**
Ends the execution of the current thread (in the context of which this function has been called).
    
This function MUST be implemented if the underlying operating system supports this operation.
Otherwise, the function MUST return CLX_SUCCESS.

\return CLX_SUCCESS if the operation has been successful.
Any other value specifies failure.
*/
extern ClxResult clxBspThreadInterfaceEndCurrentThread (void);

/**
Yields the execution of the current thread (in the context of which this function has been called).
    
This function MUST be implemented if the underlying operating system supports this operation.
Otherwise, the function can be implemented as empty.
*/
extern void clxBspThreadInterfaceYieldCurrentThread (void);

/**
Returns the OS-specific ID of the current thread (in the context of which this function has been called).
The value of the returned value is OS specific but the following rules apply:

- The ID must be unique among all the threads active in the system.
    
- The ID must not change in the life time of the thread.

\return The OS-specific ID of the current thread.
NULL if any error occurs.
*/
extern void* clxBspThreadInterfaceGetCurrentThreadOsID(void);

#endif // CLX_BSP_THREAD_INTERFACE


#if defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
/**
Disables the operating system scheduler. When this function returns, the current thread will not be preempted until #clxBspEnableOsScheduler() is called.

NOTE : two or pairs of clxBspDisableOsScheduler()-clxBspEnableOsScheduler() pair may be nested.

This BSP function MUST be implemented if this feature is supported by the OS. Otherwise, this function MUST NOT be implemented.

The implementation may return an optional opaque value as the local context for the OS scheduler. The very same value must be passed to the corresponding clxBspEnableOsScheduler()
call.

NOTE : If the clxBspDisableOsScheduler()-clxBspEnableOsScheduler() pair is nested, the code MUST maintain the local context for each pair separately.
       This is usually done by storing the local context for each pair in a separate local variable on the stack of current context/thread.
       Each clxBspEnableOsScheduler() call must be fed the local context returned by its corresponding clxBspDisableOsScheduler() call.

NOTE : A return value of NULL does NOT indicate an error. It is assumed that an implementation of this function cannot fail.

\return The local context as an opaque void* value.
*/
extern void* clxBspDisableOsScheduler();

/**
Enables the operating system scheduler. When this function returns, the current thread may be preempted at any time.
This function must only be called when the operating system scheduler has already been disabled by a previous call to #clxBspDisableOsScheduler().

NOTE : If this function is called when the operating system scheduler is already enabled, the behaviour will be undefined
	   and might be different in different platforms.

This BSP function MUST be implemented if this feature is supported by the OS. Otherwise, this function MUST NOT be implemented.

\param[ in ] localCtx The local context value that was returned by the corresponding call to clxBspDisableOsScheduler().
*/
extern void clxBspEnableOsScheduler(void* localCtx);

#endif // #if defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)


#ifdef __cplusplus
}
#endif


#endif // Thread_Bsp_h
