#ifndef ClxThread_h
#define ClxThread_h

/******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxThread.h
* Description         Declares ClxThread APIs
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#if !defined(CLX_BARE_METAL_SOFTFRAME) 


#ifdef __cplusplus
extern "C" {
#endif
  
  
/**
A typedef for generic thread id. ClxThread is not a pointer to the thread.
For more high level event driven architectures, use Module class.
\sa Module
*/
typedef void* ClxThreadID;
typedef void* ClxThreadHandle;

#define CLX_CALLBACK

/**
A typedef for thread function pointer.
*/
typedef ClxResult ( CLX_CALLBACK *ClxThreadFunction )( void* data );

/**
Clarinox internal thread priority index used by wireless stacks. 
If a user directly uses create thread function, they are not bound by these priority settings.
*/
enum ClxThreadPriority
{
    ClxThreadPriority_Highest = 0,
    ClxThreadPriority_High    = 1,
    ClxThreadPriority_Medium  = 2,
    ClxThreadPriority_Low     = 3,
    ClxThreadPriority_Lowest  = 4
};

enum ClxSoftFrameThreadStackSize
{
  CLX_SOFTFRAME_TIMER_THREAD_STACK_SIZE            = 0,                              
  CLX_SOFTFRAME_DEBUG_THREAD_STACK_SIZE,                
  CLX_SOFTFRAME_UI_THREAD_STACK_SIZE,                   
  CLX_SOFTFRAME_TERMINAL_EMULATOR_THREAD_STACK_SIZE ,
  CLX_SOFTFRAME_A2L_RPC_APPLICATION_THREAD_STACK_SIZE,
  CLX_SOFTFRAME_A2L_RPC_STACK_THREAD_STACK_SIZE
};

enum ClxBluetoothThreadStackSize
{
  CLX_BLUETOOTH_APPLICATION_THREAD_STACK_SIZE      = 0,          
  CLX_BLUETOOTH_STACK_THREAD_STACK_SIZE,                                
  CLX_BLUETOOTH_UARTRX_THREAD_STACK_SIZE
};

enum ClxWlanThreadStackSize
{
  CLX_WLAN_STACK_THREAD_STACK_SIZE                 = 0,                      	                    
  CLX_WLAN_APPLICATION_THREAD_STACK_SIZE                                  
};


#if defined(CLX_SYSTEM_THREADS_SUPPORTED)

typedef struct ClxSystemThreadStruct
{
    const s1*           name;
    ClxMaxAlignType*    stackPTR;
    u4                  stackSizeInBytes;
    u2                  priority;
    void*               platformSpecificData;
} ClxSystemThread;


typedef const ClxSystemThread* ClxSystemThreadID;


#ifdef __cplusplus
#   define CLX_DEFINE_SYSTEM_THREAD(ThreadName)                                                                     \
    extern "C" const ClxSystemThread  C_clx_SystemThread_##ThreadName             
#else               
#   define CLX_DEFINE_SYSTEM_THREAD(ThreadName)                                                                     \
    extern const ClxSystemThread      C_clx_SystemThread_##ThreadName      
#endif

    

#ifdef __cplusplus  
#   define CLX_INSTANTIATE_SYSTEM_THREAD(ThreadName, stackPTR, stackSizeInBytes, priority, platformSpecificData)    \
    extern "C" const ClxSystemThread C_clx_SystemThread_##ThreadName = {#ThreadName,                                \
                                                                        stackPTR,                                   \
                                                                        stackSizeInBytes,                           \
                                                                        priority,                                   \
                                                                          platformSpecificData}
#else
#   define CLX_INSTANTIATE_SYSTEM_THREAD(ThreadName, stackPTR, stackSizeInBytes, priority, platformSpecificData)    \
    const ClxSystemThread C_clx_SystemThread_##ThreadName = {#ThreadName,                                           \
                                                             stackPTR,                                              \
                                                             stackSizeInBytes,                                      \
                                                             priority,                                              \
                                                               platformSpecificData}
#endif // #ifdef __cplusplus
    
    
#define CLX_SYSTEM_THREAD_ID(ThreadName)   &C_clx_SystemThread_##ThreadName   

#define _clxBeginSystemThread_(function, parameter, ThreadID, flags)                                                \
    __clxBeginSystemThread__(function, parameter, ThreadID, flags)

#define clxBeginSystemThread(function, parameter, ThreadName, not_used0, not_used1,  not_used2)                     \
    _clxBeginSystemThread_(function, parameter, CLX_SYSTEM_THREAD_ID(ThreadName), 0)

#else

#define clxBeginSystemThread(function, parameter, ThreadName, stackSize, platformPriorityTable,  priority)          \
    clxBeginThread(function, parameter, #ThreadName, stackSize, platformPriorityTable,  priority)

#endif // #if defined(CLX_SYSTEM_THREADS_SUPPORTED)



/**
This function creates a thread in the system.
\param function is a pointer to the entry point of the thread
\param parameter is a generic parameter that may be passed to the thread
\param name is the name associated with the thread.
\param stackSize is the size of the stack required to run the thread.
\param platformPriorityTable priority table array, defines Clarinox thread priorities as defined in ClxThreadPriority enum set. 
Clarinox code internally uses these values for the threads required by the wireless stacks used.
\param priority current priority assigned for this specific thread.
A zero value indicates the default stack size is being used.
\return The thread handle. It is used for terminating the thread.
Will be NULL if the function was not successful.
*/
#ifdef __cplusplus
extern ClxThreadHandle  clxBeginThread( ClxThreadFunction function, void* parameter, const char* name, u4 stackSize, u2* platformPriorityTable = NULL, ClxThreadPriority priority = ClxThreadPriority_Medium);
#else
extern ClxThreadHandle  clxBeginThread( ClxThreadFunction function, void* parameter, const char* name, u4 stackSize, u2* platformPriorityTable, enum ClxThreadPriority priority);
#endif


#if defined(CLX_SYSTEM_THREADS_SUPPORTED)
extern ClxThreadHandle  __clxBeginSystemThread__(ClxThreadFunction function, void* parameter, ClxSystemThreadID systemThread, u4 flags);
#endif


/**
Deletes the thread. This function blocks until the thread has terminated.
Then it will cleanup after the thread.

\param[ in ] threadHandle the handle to the thread.
\param[ in ] timeout is the value in milliseconds for waiting graceful termination. 
When the thread returns or timeout occurs, then the RTOS delete function will be executed.
\remark This function does NOT force the thread to terminate.
It only waits until the thread terminates on its own.
*/
#ifdef __cplusplus
extern boolean          clxDeleteThread(ClxThreadHandle threadHandle, u4 timeout = 0xFFFFFFFF);
#else
extern boolean          clxDeleteThread(ClxThreadHandle threadHandle, u4 timeout);
#endif


/**
The purpose of this function is to allow thread to relinquish control of the processor to another thread,
which has the same or higher priority.

This function can only be called within the context of a thread and will only work if the other thread
has the same priority.
\return status
\retval CLX_SUCCESS Operation completed successfully.
\retval CLX_FAIL    function failed.
*/
extern void             clxYieldCurrentThread(void);

/**
Each thread is assigned with a unique ID by the operating system;
this function gets the current thread id.
\return ClxThread
\retval current thread id.
*/
extern ClxThreadID        clxGetCurrentThreadId(void);

/**
Suspends the thread with the handle of threadHandle.
NOTE : Support of this operation is optional. If not supported by the underlying
OS (or BSP), a value of CLX_ERROR_INVALID_REQUEST will be returned.
*/
extern ClxResult          clxSuspendThread(ClxThreadHandle threadHandle);

/**
Resumes the thread with the handle of threadHandle. The thread must have been previously suspended
by a call to clxSuspendThread() function.
NOTE : Support of this operation is optional. If not supported by the underlying
OS (or BSP), a value of CLX_ERROR_INVALID_REQUEST will be returned.
*/
extern ClxResult          clxResumeThread(ClxThreadHandle threadHandle);

/**
In a multi-core platform, binds a thread to be scheduled and executed on only one of the processor cores.

NOTE : Support of this operation is optional. If not supported by the underlying
OS (or BSP), a value of CLX_SUCCESS will be returned.
*/
extern ClxResult          clxBindThreadToProcessor(ClxThreadHandle threadHandle, u4 processorIndex);

/**
Thread API functionality.
*/

#ifdef __cplusplus
}
#endif


#if defined(CLX_SYSTEM_THREADS_SUPPORTED)    

    CLX_DEFINE_SYSTEM_THREAD(ClarinoxBlueStackThread);    
    CLX_DEFINE_SYSTEM_THREAD(ClarinoxBlueUartDataRx);   
    CLX_DEFINE_SYSTEM_THREAD(ClarinoxBlueApplicationThread);   
    
    CLX_DEFINE_SYSTEM_THREAD(A2dpSbcSinkGeneratorThread);
    CLX_DEFINE_SYSTEM_THREAD(A2dpSbcSourceGeneratorThread); 
    
    CLX_DEFINE_SYSTEM_THREAD(ClxA2lRpcServerStackThread);      
    CLX_DEFINE_SYSTEM_THREAD(ClxA2lRpcClientStackThread);       
    CLX_DEFINE_SYSTEM_THREAD(ClxA2lRpcClientIndicationThread);     
    
    CLX_DEFINE_SYSTEM_THREAD(SoftFrameDebugThread);  
    CLX_DEFINE_SYSTEM_THREAD(SoftFrameTimerThread);      
    CLX_DEFINE_SYSTEM_THREAD(ClxTerminalRxThread);    
    CLX_DEFINE_SYSTEM_THREAD(ClxRMTPThread);

    CLX_DEFINE_SYSTEM_THREAD(ClarinoxWlanApplicationThread); 
    CLX_DEFINE_SYSTEM_THREAD(ClarinoxWlanStackThread);      
    CLX_DEFINE_SYSTEM_THREAD(WpaSupplicantStackThread); 
    
#endif // #if defined(CLX_SYSTEM_THREADS_SUPPORTED)


    
#endif // #if !defined(CLX_BARE_METAL_SOFTFRAME) 

#endif    // ClxThread_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/
