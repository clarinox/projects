#ifndef ClxTaskSchedulerApi_h
#define ClxTaskSchedulerApi_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxTaskSchedulerApi.h
* Description         C-Style simple API for Tasking Architecture  
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/



#define CLX_SCHEDULER_HIGHEST_PRIOIRTY          1
#define CLX_SCHEDULER_DEFAULT_PRIOIRTY          7
#define CLX_SCHEDULER_LOWEST_PRIOIRTY           15



#ifdef __cplusplus
extern "C" {
#endif
  
enum ClxSchedulerMessageHandlerAction
{
    ClxSchedulerMessageHandlerAction_Process,      /* Process the message */
    ClxSchedulerMessageHandlerAction_Discard       /* Discard the message */
};

enum ClxSchedulerTimerStatus
{
    ClxSchedulerTimerStatus_Idle = 0,
    ClxSchedulerTimerStatus_Pending = 1,
    ClxSchedulerTimerStatus_Expired = 2,
    ClxSchedulerTimerStatus_Invalid = 0xFF
};


/**
These structures (ClxSchedulerTask, ClxSchedulerTimer, ClxSchedulerMessage, and ClxSchedulerMessageHandler) serve as base classes for the actual structures used in the application. 
For instance:

struct MySchedulerMessage
{
    struct ClxSchedulerMessage base;  // This SHALL be the very first member of MySchedulerMessage

    // Rest of the definition ...
};

or 

class MySchedulerMessage : public ClxSchedulerMessage
{
    // Definition
};

The macros CLX_DECLARE_C_OBJECT_RTTI and CLX_INSTANTIATE_C_OBJECT_RTTI may be used to define real time type information for each structure/class deriving
from these base structures, and stored in 'type' member.

In C++ applications, ClxCQueue template class may be used to queue the structures.
*/
struct ClxSchedulerTask 
{
    struct ClxCQueueable  queueable;  
    void*                 type;   
};

struct ClxSchedulerTimer 
{ 
    struct ClxCQueueable  queueable;  
    void*                 type;   
};

struct ClxSchedulerMessage 
{ 
    void*                 type;   
};

struct ClxSchedulerMessageHandler 
{ 
    struct ClxCQueueable  queueable;  
    void*                 type;   
};

struct ClxSchedulerIdleContext 
{  
    void* userData;
};


/* Scheduler object: */
struct ClxScheduler_t;
typedef struct ClxScheduler_t* ClxScheduler;


/* Message Handler Call-back Prototype: */ 
typedef void (*ClxSchedulerMessageHandlerCallback) (struct ClxSchedulerMessageHandler* context, 
                                                    struct ClxSchedulerMessage* message,
                                                    enum ClxSchedulerMessageHandlerAction action);  
  
/* Task Call-back Prototype: */ 
typedef void (*ClxSchedulerTaskCallback) (struct ClxSchedulerTask* task);  


/* Timer Call-back Prototype: */ 
typedef void (*ClxSchedulerTimerCallback) (struct ClxSchedulerTimer* timer);

/* Idle context Call-back Prototype: */ 
typedef void (*ClxSchedulerIdleContextCallback) (struct ClxSchedulerIdleContext* this_);


extern ClxScheduler clxCreateScheduler();

extern ClxScheduler clxCreateNamedScheduler(const s1* name);

extern boolean clxBindSchedulerToCurrentThread(ClxScheduler scheduler);
extern void clxRunSchedulerLoop(ClxScheduler scheduler);
extern ClxResult clxTryRunSchedulerLoop(ClxScheduler scheduler);
extern void clxTerminateScheduler(ClxScheduler scheduler);
extern void clxDeleteScheduler(ClxScheduler scheduler);

extern struct ClxSchedulerMessageHandler* clxCreateSchedulerMessageHandler(ClxScheduler scheduler, 
                                                                           const s1* name, 
                                                                           ClxSchedulerMessageHandlerCallback callback, 
                                                                           size_t objectSize, 
                                                                           u1 priority);

extern struct ClxSchedulerMessage* clxCreateSchedulerMessage(size_t messageSize);

extern struct ClxSchedulerIdleContext* clxCreateSchedulerIdleContext(ClxSchedulerIdleContextCallback callback, 
                                                                     size_t objectSize);

extern void clxDeleteSchedulerIdleContext(struct ClxSchedulerIdleContext* arg);

extern void clxSetSchedulerIdleContext(ClxScheduler scheduler, struct ClxSchedulerIdleContext* context);


void clxRemoveUnusedSchedulerMessage(struct ClxSchedulerMessage* arg);


extern void clxQueueSchedulerMessage(struct ClxSchedulerMessageHandler* messageHandler, 
                                     struct ClxSchedulerMessage* message);

extern void clxDeleteSchedulerMessageHandler(struct ClxSchedulerMessageHandler* arg);


extern struct ClxSchedulerTask* clxCreateSchedulerTask(ClxScheduler scheduler, 
                                                       const s1* name, 
                                                       ClxSchedulerTaskCallback callback, 
                                                       size_t objectSize, 
                                                       u1 priority);

extern ClxResult clxWakeUpSchedulerTask(struct ClxSchedulerTask* arg);

extern void clxDeleteSchedulerTask(struct ClxSchedulerTask* arg);

extern struct ClxSchedulerTimer* clxCreateSchedulerTimer(ClxScheduler scheduler, 
                                                         const s1* name, 
                                                         ClxSchedulerTimerCallback callback, 
                                                         size_t objectSize, 
                                                         u1 priority);

extern ClxResult clxStartSchedulerTimer(struct ClxSchedulerTimer* timer, u4 timeout);

extern ClxResult clxStopSchedulerTimer(struct ClxSchedulerTimer* timer);

extern ClxResult clxRestartSchedulerTimer(struct ClxSchedulerTimer* timer, u4 timeout);

extern void clxDeleteSchedulerTimer(struct ClxSchedulerTimer* timer);

extern enum ClxSchedulerTimerStatus clxGetSchedulerTimerStatus(struct ClxSchedulerTimer* timer);

extern u4 clxGetSchedulerTimerRemainingTime(struct ClxSchedulerTimer* timer);


#ifdef __cplusplus
}
#endif 



#endif // ClxTaskSchedulerApi_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/
