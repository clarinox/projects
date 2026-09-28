#ifndef A2l_h
#define A2l_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                A2l.h
* Description         Declares Clarinox Application Adaptation Layer related 
*                     types and macros
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


CLX_DECLARE_C_OBJECT_RTTI(ClxLocalService);
CLX_DECLARE_C_OBJECT_RTTI(ClxRemoteService);
CLX_DECLARE_C_OBJECT_RTTI(ClxDispatchableCommandModule);



/**
Used Internally:
*/
#define CLX_SEND_TEST_COMMAND_COMPLETE							    0x40FF


#define CLX_PING_STACK_COMPLETE							            0x4001


/**
ComamndComplete Indication ID for all Dispatchable commands (e.g. any command issued by ClxA2L::issueDispatchableCommand).
The parameter of this indication is of type #ClxA2lDispCommandArgsComplete.
*/
#define CLX_A2L_DISPATCHABLE_COMMAND_ISSUE_COMPLETE                 0x4002


/**
Invalid Dispatchable Command Module ID.
*/
#define CLX_A2L_INVALID_DISPATCHABLE_COMMAND_MODULE_ID			    0


#define CLX_A2L_MAX_DISPATCHABLE_COMMAND_ID_IN_BITS                 22   /* Bits (Up to 2^22 = 4M command IDs are supported (DO NOT MODIFY) */  


#if defined(CLX_DEBUG)
#   define CLX_A2L_INIT_DISPATHCABLE_COMMAND_ARGS(args, ID)         \
       (args).commandID = ID;                                       \
       (args).commandName = #ID
#else
#   define CLX_A2L_INIT_DISPATHCABLE_COMMAND_ARGS(args, ID)         \
       (args).commandID = ID;                                       \
       (args).commandName = NULL
#endif



/**
Unique identifier for an A2L dispatchable command module. The ID MUST be unique among all A2L command modules owned by the parent ClxStack object.
*/
typedef u4 ClxA2lDispCommandModuleID;


/**
ClxA2lDispCommandArgs specifies the Command ID and the input/output arguments of a dispatchable command. 

A dispatchable command is dispatched to a Command Module via a Command Dispatcher owned by the ClxStack object to which the command is issued.

The logic of a dispatchable command is implemented by the Command Module to which this command is issued.
A dispatchable command argument structure must be defined as follows:

NOTE : Use the macro #CLX_A2L_INIT_DISPATHCABLE_COMMAND_ARGS() to initialize commandID and commandName.

struct SomeDispatchableCommand
{
    ClxA2lDispCommandArgs base;  // MUST BE the very first member

    // Rest of the command input/output arguments.
};

NOTE : Dispatchable commands are generally to be used for internal communications within the system (across different threads), or for testing purposes.
       These commands are not meant to be used to implement public APIs exposed to the application.

NOTE : When a dispatchable command is issued, the caller MUST NOT modify or delete the associated ClxA2lDispCommandArgs object until
       the command is complete.
*/
typedef struct ClxA2lDispCommandArgsStruct
{
    _in_ u4         commandID:CLX_A2L_MAX_DISPATCHABLE_COMMAND_ID_IN_BITS;     /*!< The command ID, which determines the runtime type of this object */
    _in_ const s1*  commandName;                                                /*!< An optional NULL-terminated string which identifies the command type for debugging purposed.
                                                                                     If not used, MUST be set NULL. */
} ClxA2lDispCommandArgs;


/**
The argument type of Command Complete Indication of any dispatchable command (when issued in non-blocking mode).
*/
typedef struct ClxA2lDispCommandArgsCompleteStruct
{
    _inout_ ClxA2lDispCommandModuleID*  moduleID;       /*!< The Module ID of the module which has successfully handled the command. MUST be ignored if the command is complete in error */ 
    _inout_ ClxA2lDispCommandArgs*      args;           /*!< pointer to the very same ClxA2lDispCommandArgs object provided by the caller */
} ClxA2lDispCommandArgsComplete;        



/********************************************
ClxA2lTestCommandOutput
*********************************************/
typedef struct ClxA2lTestCommandOutputStruct
{
	const s1*	command;
    s1*			response;
} ClxA2lTestCommandOutput;



/** 
A variable of type ClxService represents an instance of either a local (non-RPC) service or an RPC service on a remote system. 
An object of this type may be passed to API functions which implement the logic for both non-RPC, and RPC services. 
*/
typedef struct ClxServiceStruct
{
    void* rtti;
    union U
    {
        ClxHandle localHandle;
        
        struct RpcServiceHandle
        {
            u2 serviceID;
            u2 commandContext;
        } rpcHandle;
    } u;
} ClxService;


/**
Initializes an object of type ClxService for a local (non-RPC) service.

\param[ in ] serviceHandle The A2L service handle.
\param[ out ] out The ClxService object to be initialized.
*/
void clxInitLocalServiceObject(_in_ ClxHandle serviceHandle, _out_ ClxService* out);


/**
Initializes an object of type ClxService for a remote (RPC) service.

\param[ in ] serviceID The RPC service ID.
\param[ in ] commandContext The RPC command context.
\param[ out ] out The ClxService object to be initialized.
*/
void clxInitRemoteServiceObject(_in_ u2 serviceID, _in_ u2 commandContext, _out_ ClxService* out);


/**
Represents an A2L-based command which is defined in the application.
*/
typedef struct ClxA2lAppCommandStruct
{
    CLX_STATIC_METHOD const s1*     (*name) (void);                                             /*!< Returns the name of the command, used for debugging purposes. May be set to NULL */
    u2                  			commandCompleteID;                                          /*!< The A2L ID of the command complete indication. This is the indication ID when the command is issued in non-blocking mode */

    ClxResult           			(*handleCommand) (struct ClxA2lAppCommandStruct* self);     /*!< Called in the context of the stack to handle the command. When this function returns, the command is deemed complete with the
																									 return value as the result of the command. This argument CANNOT be NULL. */
    CLX_STATIC_METHOD void          (*remove) (void* arg);                                  	/*!< Called when the command object is not required any longer, in order to remove the object.
																									 This argument CANNOT be NULL. */
} ClxA2lAppCommand;


/**
Returns the scheduler object used to schedule indications on the application call-back (indication) thread for a stack.

NOTE : The stack must already have been successfully initialized and not have been terminated yet.

\param[ in ] stack The stack for which the indication scheduler object to be returned.

\return The scheduler object.
*/
ClxScheduler clxA2lGetStackIndicationScheduler(ClxStack stack);


/**
Pings the stack to assure its responsiveness. 

An application may issue this command periodically to verify that the stack is responsive. Upon issuing this command for a stack, the application should also start a timer with a predefined timeout value.
If this command is not complete before the timer expires, the corresponding stack should be considered non-responsive and recovery procedures should be initiated.

In blocking mode, the command is complete when the function returns. This function should return immediately, or in a timely manner.

In non-blocking mode, the command is complete when the command complete indication of type #CLX_PING_STACK_COMPLETE is received. The indication should be received in a timely manner. 
This indication will be received in the indication handler function which is passed to the initialization function of the stack (e.g. clxInitClarinoxBlue() for ClarinoxBlue, and clxInitClarinoxWlan() for ClarinoxWLAN).

NOTE : It is recommended that this command be issued in the non-blocking mode since this will verify responsiveness of both the stack thread and the indication handling thread. 

\param[ in ] stack the stack (e.g. ClarinoxBlue or ClarinoxWLAN) object.
\param[ in ] block type of the operation.
                - TRUE:  API will be blocked until this command is completed (successfully or failed).
                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_SUPPORTED: If this command is not supported by the stack
*/
ClxResult clxPingStack(_in_ ClxStack stack, _in_ boolean block);


/**
Duplicates a service handle by incrementing its internal reference counter. This function can be used in multi-threaded applications in order to provide a safe mechanism for
deleting the service object.

NOTE : When a handle is created, its reference counter is set to 1. Every time clxDuplicateHandle() is called, the reference counter of the handle is incremented by 1.
On the other hand, every time the handle is passed to clxCloseHandle(), and clxCloseHandle returns CLX_SUCCESS, the reference counter is decremented by 1. The service object
is physically deleted only when the reference counter reaches 0.

The first time clxCloseHandle() returns CLX_SUCCEESS, the handle is in Closed state (it is fully closed). But, the corresponding service will not be deleted until the reference count
reaches 0.

NOTE : It is not possible to duplicate a handle which is not in Active state (A handle is not in Active state if it has already been closed or is being closed).

\param[ in ] handle The handle to be duplicated.

\return CLX_SUCCESS                 The handle was duplicated successfully. 
        CLX_ERROR_INVALID_HANDLE    The handle specified is not valid (e.g. it is not in Active state)
*/
ClxResult clxDuplicateHandle(_in_ ClxHandle handle);

/**
Closes a service handle (of type ClxHandle). 

The service associated to this handle enters closed state if this function returns CLX_SUCCESS. A service in closed state does not accept any command from the application.
Also, it will not send any indication to the application any longer.

NOTE : Assume clxDuplicateHandle() has been called N times for a service handle. Then for that handle, clxCloseHandle() shall be called (N + 1) times, and clxCloseHandle() shall have returned CLX_SUCCESS for (N + 1) times
before the service is closed and successfully deleted.

NOTE : When the service is physically deleted from the memory, any reference to the handle may result in undefined behavior.

Pending Commands:
If there is any pending commands (in either blocking or non-blocking mode), clxCloseHandle() will return CLX_ERROR_HANDLE_COMMANDS_PENDING.
It is the application responsibility to wait until all pending commands are completed peacefully, before calling clxCloseHandle().

IMPORTANT : When clxCloseHandle() operation is progress, other threads are NOT allowed to call new API functions for this handle. This may result in undefined behaviour or a crash.
In multi-threaded designs, the application shall make sure this will not happen by setting a flag, or modifying the state of a state machine, in a manner that implies that the handle is being closed, 
before calling clxCloseHandle().

The function may be used with any service handle which is of type ClxHandle.

\param[ in ] handle a service handle which is to be closed.

\return CLX_SUCCESS                         The handle was closed successfully. 
                                            The service might have been also physically deleted from the memory if all duplicates, along with the original handle, have also been closed.
        CLX_ERROR_INVALID_HANDLE            The handle specified is not valid (it is in a wrong state, or it is already closed)
        CLX_ERROR_HANDLE_COMMANDS_PENDING   One or more commands are pending at the time of calling this function.
        CLX_ERROR_INTERNAL_ERROR            Internal error occurred.
*/
ClxError clxCloseHandle(_in_ ClxHandle handle);

/**
Stores an application specific "data" in the given service handle for later use.
\code
Comm::Comm(ClxStack stack, DataFormat currentDataFormat, u1 ExpansionOptionEnabled, boolean server)
{
    // create a SPP profile handle and store "this" pointer (Comm object) in the handle. 
    // This information could be retrieved later on by using #clxGetHandleUserData
    spp_ = clxSppCreate(stack, NULL, "SPPCommPort", ClxServer, messageHandler, ClxAutomaticSecurity);
    clxSetHandleUserData(spp_, this);
}
\endcode

\param[ in ] handle The service handle that the data will be stored in.
\param[ in ] data user data that will be stored.
*/
void clxSetHandleUserData (ClxHandle handle, void* data);

/**
Retrieves the stored application specific data of a handle.
\code
boolean Comm::messageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    // retrieve saved Comm object in the message handler call back stored by using #clxSetHandleUserData
    Comm* this_ = reinterpret_cast<Comm*>(clxGetHandleUserData(serviceHandle));
}
\endcode

\param[ in ] handle The service handle from which the data will be retrieved.
\return The stored application specific data. Will be NULL if there is no application specific data stored in this handle.
*/
void* clxGetHandleUserData (ClxHandle handle);



/* 
Issues a dispatchable command to a ClxStack object. The command is dispatched to a module or module(s) which have registered a command handler for the specified handler.

NOTE : Only stacks which own Command Dispatcher object support dispatchable commands. Please refer to documentation or sample applications for more information.

More than one dispatchable command may be issued and pending on a ClxStack object.
The Command Dispatcher associated with the stack will make sure only one command of a specific command ID may be issued to and pending on a specific Command module as any time.

The command may be issued to a specific module identified by its moduleID (as the third argument), or sent to all modules of a specific type (identified by the second argument).
In the latter case, the Command Dispatcher tries each module of the specified type (which has registered a handler for the provided command) until one of the modules handles the
command and returns a value other than CLX_ERROR_COMMAND_NOT_HANDLED. If no module handles the command, the command will get complete with the error CLX_ERROR_COMMAND_NOT_HANDLED.
    
NOTE: If a module type is provided, only modules with the EXACT type will be tried. Derived modules will not be tried.

NOTE: If a module type is not provided (e.g. second argument is set to NULL), A valid ModuleID MUST be provided as the third argument.

Blocking mode: This function will not return until the command is complete. The function return value indicates the
                result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                    When the command is complete, the call-back function will be called with an indication of type #CLX_A2L_DISPATCHABLE_COMMAND_ISSUE_COMPLETE.
                    TThe parameter of this indication is of type #ClxA2lDispCommandArgsComplete.

\param[ in ] stack       The stack object to which the command is to be dispatched. The stack object must own a CommandDispatcher object and a base service handle.
\param[ in ] moduleType  The type of modules to which the command is to be dispatched. If provided, the command is issued to all registered modules of the specified type until one of the modules handles the command or there is no more module of the specified type to handle the command.
                         If set to NULL, the command will be issued only to the modules identified by the ModuleID provided as the argument 'moduleID' (third argument).
                         The module type may be obtained using the macro #CLX_C_STRUCTURE_TYPE.
\param[ in ] moduleID    Pointer to a variable of type ClxA2lDispCommandModuleID. This argument CANNOT be NULL. 
                         As an input, if the argument 'moduleType' is NULL, this variable MUST contain the unique ID of the module to which the command is to be dispatched
                         As an output, if the command is complete with success, this variable will contain the ModuleID of the module which handled the command. If the command is complete in error, the value of this variable MUST be ignored.
                         NOTE : This variable MUST remain valid and MUST NOT be modified or deleted until this command is complete (either in blocking or non-blocking mode).
\param[ in ] args        The caller-allocated command arguments. This argument CANNOT be NULL. This object MUST remain valid and MUST NOT be modified or deleted until this command is complete (either in blocking or non-blocking mode).

\param[ in ] block       Indicates mode of operation:
                                TRUE: Blocking mode
                                FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet

        - #CLX_ERROR_ANOTHER_COMMAND_IN_PROGRESS :  Another command of the same type is currently pending on the Module identified by 'moduleID'.
        - #CLX_ERROR_INVALID_REQUEST :              The ClxStack object does not own either a CommandDispatcher object or a base service handle.
        - #CLX_ERROR_INVALID_HANDLE :               moduleID is an invalid value.
        - #CLX_ERROR_COMMAND_NOT_SUPPORTED:         The command is not supported by the module identified by moduleID.
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT:      The argument 'stack', 'moduleID' or 'args' is NULL. 
        - #CLX_ERROR_COMMAND_NOT_HANDLED :          The command was not handled by any module (only when the command is issued to a Module Type).
        - Any other value indicates an error.
*/
ClxResult clxIssueDispatchableCommand(_in_ ClxStack                        stack,
                                      _in_ const void*                     moduleType,
                                      _inout_ ClxA2lDispCommandModuleID*   moduleID,
                                      _inout_ ClxA2lDispCommandArgs*       args,
                                      _in_ boolean                         block);


#ifdef __cplusplus
}
#endif


#endif // A2l_h

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : Unions shall not be used.                                  */ 
/* Rule          : MISRA-C:2004 Rule 18.4                                     */ 
/* Justification : No risk identified. Unions are used in this instance for   */
/*                 providing a different  type of service handle, a 	      */
/*				   "ClxHandle" for a local API call or a "rpcHandle" for a    */
/*				   Remort Procedure Call (RPC) service API. Therefore these   */
/*				   union data records will not be misrepresented because the  */
/*				   relavent union data type will only used with the respective*/ 
/*				   type of API (local or RPC).                                */
/******************************************************************************/


/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused type declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.3                                      */ 
/* Justification : Unused type declarations are to be used in user 		      */
/* 				   applications.      										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : The character sequences Slash'/' Star'*' and Slash'/'      */
/*				   Slash'/'  shall not be used within a comment. 	  		  */
/* Rule          : MISRA-C:2012 Rule 3.1                                      */ 
/* Justification : Only used for example code to clarify the use. As we		  */	
/*				   generate API documentation from header files (using 		  */
/*				   Doxygen), this is necessary.							  	  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : The union keyword should not be used.					  */
/* Rule          : MISRA-C:2012 Rule 19.2                                     */ 
/* Justification : No risk identified. Unions are used in this instance for   */
/*                 packing and unpacking data / sending and receiving data    */ 
/*				   back and forth between the application side and the WLAN   */
/*				   stack side of the code. Depending on the direction the data*/ 
/*				   is sent the type of the data used will differ.             */
/******************************************************************************/
