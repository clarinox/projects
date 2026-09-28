#ifndef ClarinoxCLI_h
#define ClarinoxCLI_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClarinoxCLI.h
* Description         Command Line Interpreter
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


/**
Defines a new variable, finds an CLI argument on the provided argument list using its index, and stores its value in the new variable. 

NOTE : If the argument is not found, or it does not have any value, the variable will be set to NULL.

NOTE : If the argument has more than one value, the variable will point to the first value. 

\param[ in ] var Name of the new variable (of type const s1*) which will point to the value of the found argument.
\param[ in ] argList Pointer to an argument list of type ClxCliArgumentList. This cannot be NULL.
\param[ in ] index The zero-based index of the CLI argument.
*/
#define CLI_ARG_VALUE(var, arglist, index)                              \
    const s1* var = clxCliGetArgValue(arglist, index)


/**
Defines a new variable, finds an CLI argument on the provided argument list using its index, and stores its value in the new variable.

NOTE : If the argument is not found, or it does not have any value, the current function will return with the error CLX_ERROR_INVALID_COMMAND_ARGUMENT.

NOTE : If the argument has more than one value, the variable will point to the first value.

\param[ in ] var Name of the new variable (of type const s1*) which will point to the value of the found argument.
\param[ in ] argList Pointer to an argument list of type ClxCliArgumentList. This cannot be NULL.
\param[ in ] index The zero-based index of the CLI argument.
*/
#define CLI_ARG_VALUE_M(var, arglist, index)                            \
    const s1* var = clxCliGetArgValue(arglist, index);                  \
    if (var == NULL)                                                    \
    {                                                                   \
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;                      \
    }


/**
Defines a new variable, finds a named CLI argument on the provided argument list, and stores its value in the new variable.

NOTE : If the argument is not found, or it does not have any value, the variable will be set to NULL.

NOTE : If the argument has more than one value, the variable will point to the first value.

\param[ in ] var Name of the new variable (of type const s1*) which will point to the value of the found argument.
\param[ in ] argList Pointer to an argument list of type ClxCliArgumentList. This cannot be NULL.
\param[ in ] name Name of the argument. The name is case insensitive. This cannot be NULL.
*/
#define CLI_NAMED_ARG_VALUE(var, arglist, name)                         \
    const s1* var = clxCliGetNamedArgValue(arglist, name, NULL)


/**
Defines a new variable, finds a named CLI argument on the provided argument list, and stores its value in the new variable.

NOTE : If the argument is not found, or it does not have any value, the current function will return with the error CLX_ERROR_INVALID_COMMAND_ARGUMENT.

NOTE : If the argument has more than one value, the variable will point to the first value.

\param[ in ] var Name of the new variable (of type const s1*) which will point to the value of the found argument.
\param[ in ] argList Pointer to an argument list of type ClxCliArgumentList. This cannot be NULL.
\param[ in ] name Name of the argument. The name is case insensitive. This cannot be NULL.
*/
#define CLI_NAMED_ARG_VALUE_M(var, arglist, name)                       \
    const s1* var = clxCliGetNamedArgValue(arglist, name, NULL);        \
    if (var == NULL)                                                    \
    {                                                                   \
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;                      \
    }


/**
Defines a new variable of type ClxCliStackArgument, finds a named CLI argument on the provided argument list, and stores its information in the new variable.

NOTE : If the argument is not found, the ClxCliStackArgument.values parameter of the new variable will be NULL.

\param[ in ] var Name of the new variable (of type const s1*) which will point to the value of the found argument.
\param[ in ] argList Pointer to an argument list of type ClxCliArgumentList. This cannot be NULL.
\param[ in ] name Name of the argument. The name is case insensitive. This cannot be NULL.
*/
#define CLI_NAMED_ARG(var, arglist, name)                               \
    ClxCliStackArgument var = clxCliGetNamedArg(arglist, name, NULL)


/**
Defines a new variable of type ClxCliStackArgument, finds a named CLI argument on the provided argument list, and stores its information in the new variable.

NOTE : If the argument is not found, the current function will return with the error CLX_ERROR_INVALID_COMMAND_ARGUMENT.

\param[ in ] var Name of the new variable (of type const s1*) which will point to the value of the found argument.
\param[ in ] argList Pointer to an argument list of type ClxCliArgumentList. This cannot be NULL.
\param[ in ] name Name of the argument. The name is case insensitive. This cannot be NULL.
*/
#define CLI_NAMED_ARG_M(var, arglist, name, minValues)                  \
    ClxCliStackArgument var = clxCliGetNamedArg(arglist, name, NULL);   \
    if (var.noOfValues < minValues)                                     \
    {                                                                   \
        return CLX_ERROR_INVALID_COMMAND_ARGUMENT;                      \
    }


#ifdef __cplusplus
extern "C" {
#endif


CLX_DECLARE_C_OBJECT_RTTI(ClxCliA2lIndication);



/*******************************
ClxCliValue :
********************************/
typedef const s1* ClxCliValue;



/*******************************
clxCliPrint :
********************************/
extern void (*clxCliPrint) (const s1* format, ...);



/*******************************
ClxCliEvent :
********************************/
typedef struct ClxCliEventStruct
{
    u1 _unused;
} ClxCliEvent;



/*******************************
ClxCliA2lIndication :
********************************/
typedef struct ClxCliA2lIndicationStruct
{
    ClxCliEvent  base;

    ClxStack     stack;
    ClxHandle    serviceHandle;
    u4           indicationID;
    void*        params;
    ClxError     errorCode;
} ClxCliA2lIndication;




/*******************************
ClxCliStackArgument :
********************************/
typedef struct ClxCliStackArgumentStruct
{
    const s1*       name;

    ClxCliValue*    values;             /*!< If this object does not hold information on a valid CLI argument, this member will be NULL. 
                                             Otherwise, this member will not be NULL, even if noOfValues is 0. */
    u4              noOfValues;
} ClxCliStackArgument;



/*******************************
ClxCliArgumentList :
********************************/
typedef struct ClxCliArgumentListStruct
{
    ClxCliStackArgument*  list;
    u4                    noOfArgs;
} ClxCliArgumentList;



/**
Function prototype for CLI commands. Any CLI command must register a handler function of this type.
The command is considered running as soon as its handler function is called, and it is considered complete as soon as its handler function returns.

\param[ in ] args The input argument list. This object and all the arguments it contains (e.g. argument names and values) remain valid until this function returns.

\return The command result. This value will be returned by the ongoing clxCliRunCommand() call.
*/
typedef ClxResult (*ClxCliCommand) (const ClxCliArgumentList* args);


/**
Function prototype for CLI event handlers. Each CLI event (as passed to #clxCliQueueEvent() function) must provide a handler function.
The handler function will be called when the event is being processed. This function will be called in the context of the CLI engine
(e.g. same context in which the CLI commands are called).

\param[ in ] eventType The event RTTI (RunTime Type Information) which has been provided when the event object has been created.
\param[ in ] event The event object as returned by a call to #clxCliAllocateEvent() or #clxCliAllocateA2lIndication() function. 
*/
typedef void (*ClxCliEventHandler) (void* eventType,
                                    ClxCliEvent* event);


/**
Initializes the CLI engine. The engine is bound to the calling thread and all subsequent CLI APIs must be called in the context of the same thread
(except for the API function #clxCliQueueEvent() which may be called from any thread).

\param[ in ] maxNumberOfCommands The maximum number of commands that may be registered by subsequent calls to the function #clxCliRegisterCommand().
\param[ in ] stackSize The size of the CLI stack, in bytes, which is used to store information of the calling commands and their input/return arguments. 

\return CLX_SUCCESS if this function succeeds. Any other value indicates an error.
*/
ClxResult clxCliInitEngine(u4 maxNumberOfCommands,
                           u4 stackSize);


/**
Destroys the initialized CLI engine.
*/
void clxCliDestroyEngine();


/**
Registers a new command with the CLI engine.

\param[ in ] name Name of the command. The name is case insensitive. This argument CANNOT be NULL.
                  NOTE : The name of the command is NOT copied onto the CLI stack. Therefore, the caller must make sure that the name buffer remains valid until the function
                         #clxCliUnregisterCommand() is called for this command, or #clxCliDestroyEngine() is called.

\param[ in ] handler The handler function which implements this command. This argument CANNOT be NULL.

\return CLX_SUCCESS if this function succeeds. Any other value indicates an error.
*/
ClxResult clxCliRegisterCommand(const s1* name,
                                ClxCliCommand handler);

/**
Unregisters a command and removes its entry from the CLI engine. 

NOTE : If a command is currently running (or has been pushed onto the CLI stack to be executed), it can still be unregistered safely as long as the buffer containing
       the name of the command remains valid until the command is popped off the CLI stack.

\param[ in ] name Name of the command. The name is case insensitive. This argument CANNOT be NULL.

\return CLX_SUCCESS if this function succeeds. Any other value indicates an error.
*/
ClxResult clxCliUnregisterCommand(const s1* name);

/**
Determines if a command is registered with the CLI engine.

\param[ in ] name Name of the command. The name is case insensitive. This argument CANNOT be NULL.

\return TRUE if the command is currently registered. FALSE otherwise.
*/
boolean clxCliIsCommandRegistered(const s1* name);

/**
Pushes a command onto the CLI stack. If successful, zero or more arguments may be pushed for the command, and finally #clxCliRunCommand() may be called
to actually execute the command. When the command is not needed any more, it needs to be popped off the CLI stack. Please refer to documentation of the function #clxCliPopCommand()
for more information.

NOTE : This function will not check if a command with the provided name is currently registered with the CLI engine. This will be done only when #clxCliRunCommand() is called.

NOTE : It is possible to push a new command onto the CLI stack in the context of the currently-running command.

NOTE : Only one non-running command may be pushed onto the top of the CLI stack at any time. The non-running command at the top of the stack must be popped
       (e.g. by a subsequent call to #clxCliPopCommand() function) before another command can be pushed onto the stack.

\param[ in ] name Name of the command. The name is case insensitive. This argument CANNOT be NULL.
\param[ in ] maxNumOfInputArgs Maximum number of input arguments which may be pushed onto the CLI stack for this command.
                               An attempt to push more input arguments than this value will fail with an error.
\param[ in ] maxNumOfReturnArgs Maximum number of return arguments which may be returned by this command.
                                An attempt to push more return arguments than this value will fail with an error.

\return CLX_SUCCESS if this function succeeds.
        CLX_ERROR_BAD_STATE if there exists another non-running command at the top of the CLI stack.
        CLX_SYSTEM_ENOMEM if there is not enough space on the CLI stack for this command.
        Any other value indicates an error.
*/
ClxResult clxCliPushCommand(const s1* commandName,
                            u4 maxNumOfInputArgs,
                            u4 maxNumOfReturnArgs);

/**
Executes the non-running command at the top of the CLI stack. 

NOTE : Before calling the command handler function, any currently queued events will be handled. 
       The implementation of the command may wait for other events by a call to #clxCliWaitForUpdate().

NOTE : After the command is executed, it needs to be popped off the CLI stack. Please refer to documentation of the function #clxCliPopCommand() for more information.

\param[ in ] returnArgs On a successful call, this argument will point to a CLI-provided list of return arguments (of type ClxCliArgumentList*).
                        The list and all its members (e.g. argument names and vales) will remain valid until the command is popped off the CLI stack.
                        Please refer to documentation of the function #clxCliPopCommand() for more information.
                        This argument may be NULL if the command is not expected to have any return argument, or the caller is not interested in the return arguments.

\return If successful (e.g. the command is actually executed), this function will return the same error code as returned by the command handler function.
        If failed, one of the following error codes may be returned:
            CLX_ERROR_BAD_STATE if there is no non-running command at the top of the CLI stack.
            CLX_ERROR_COMMAND_NOT_SUPPORTED if the command at the top of the CLI stack is not currently registered.
*/
ClxResult clxCliRunCommand(_out_ const ClxCliArgumentList** returnArgs);


/**
Pops the non-running command off the top of the CLI stack. This function pops all the command input and return arguments as well.
This function will not have any impact on the currently-running command.

NOTE : When a command is executed and returns, its return arguments will remain valid until the command is popped off the CLI stack.
       When the command is popped, none of its return arguments may be accessed any longer.

NOTE : The non-running command at the top of the CLI stack may be popped in one of the following manners:
    
    - The command may be popped manually by a call to this function at any time.
    - If a child command is executed in the context of another (parent) command and the parent command is terminated without calling this function, the child command will be automatically
      popped. This is safe since the return arguments of the child command cannot be accessed when the parent command is terminated.

\return CLX_SUCCESSFUL if the non-running command at the top of the CLI stack is popped successfully.
        CLX_ERROR_BAD_STATE if there is exists no non-running command at the top of the CLI stack. 
*/
ClxResult clxCliPopCommand();


/**
Pushes an argument onto the CLI stack. An argument may have a name, and zero or more values. The argument name and all its values are NULL-terminated strings.
If this function is successful, the argument values can be pushed subsequently by zero or more calls to #clxCliPushCopyValue() or #clxCliPushCopyValue().

This argument is either an input argument for the command at the top of the CLI stack, or the return argument for the currently running command.
The type of the argument is determined as follows:

    - If there exists a non-running command at the top of the CLI stack, this new argument will be considered an input argument to that command.
    - Otherwise, this argument will be considered a return argument for the currently running command.

\param[ in ] name Name of the argument. This argument may be NULL.
\param[ in ] maxNumOfValues Maximum number of values for this argument. The argument may be 0.
\param[ in ] copyName If TRUE, the name of the argument (if not NULL) will be copied onto the CLI stack. Otherwise, the pointer to the provided buffer will be pushed.
                      In this case, the caller must make sure the name buffer will remain valid as long as this argument is on CLI stack.

\return TRUE If the argument is successfully pushed onto the CLI stack.
        FALSE otherwise.
*/
boolean clxCliPushArg(const s1* name, u4 maxNumOfValues, boolean copyName);

/**
Pushes a value for the currently-pushed argument at the top of the CLI stack.
Only the address of the value buffer will be pushed onto the stack. The caller must make sure the value buffer will remain valid until the parent argument is popped off the CLI stack

This function will fail if there is no argument at the top of the stack, or the maximum number of values has been reached for the argument, or there is not enough space of the CLI stack
for this value.

\param[ in ] The value as a NULL-terminated string. This argument CANNOT be NULL.

\return TRUE if the function succeeds.
        FALSE otherwise.
*/
boolean clxCliPushValue(const s1* value);

/**
Pushes a value for the currently-pushed argument at the top of the CLI stack.
The value will be copied onto the stack. Therefore, the value buffer may be modified as soon as this function returns.

This function will fail if there is no argument at the top of the stack, or the maximum number of values has been reached for the argument, or there is not enough space of the CLI stack
for this value.

\param[ in ] The value as a NULL-terminated string. This argument CANNOT be NULL.

\return TRUE if the function succeeds.
        FALSE otherwise.
*/
boolean clxCliPushCopyValue(const s1* value);


/**
Helper function to push a single-value argument onto the CLI stack.
This function is equivalent to the following (error handling code is removed):
    
    clxCliPushArg(name, 1, FALSE);
    clxCliPushValue(value);

\param [ in ] name Name of the argument. This argument may be NULL.
\param [ in ] value The value of the argument. This argument CANNOT be NULL.

\return TRUE if the function succeeds.
        FALSE otherwise.
*/
boolean clxCliPushSingleValueArg(const s1* name,
                                 const s1* value);


/**
Helper function to push a single-value argument onto the CLI stack.
This function is equivalent to the following (error handling code is removed):

    clxCliPushArg(name, 1, TRUE);
    clxCliPushCopyValue(value);

\param [ in ] name Name of the argument. This argument may be NULL.
\param [ in ] value The value of the argument. This argument CANNOT be NULL.

\return TRUE if the function succeeds.
        FALSE otherwise.
*/
boolean clxCliPushCopySingleValueArg(const s1* name,
                                     const s1* value);

/**
Helper function to push a multiple-value argument onto the CLI stack.
This function is equivalent to the following (error handling code is removed):

    clxCliPushArg(name, numOfValues, FALSE);
    for (u4 i = 0; i < numOfValues; i++)
    {
        clxCliPushValue(values[i]);
    }

\param [ in ] name Name of the argument. This argument may be NULL.
\param [ in ] value The array of values for this the argument. This argument CANNOT be NULL.
\param [ in ] numOfValues The number of values in the value array. This argument CANNOT be 0.

\return Actual number of arguments pushed onto the CLI stack. This could be less than numOfValues if an error happens.
*/
u4 clxCliPushMultiValueArg(const s1* name,
                           const ClxCliValue* values,
                           u4 numOfValues);

/**
Helper function to push a multiple-value argument onto the CLI stack.
This function is equivalent to the following (error handling code is removed):

    clxCliPushArg(name, numOfValues, FALSE);
    for (u4 i = 0; i < numOfValues; i++)
    {
        clxCliPushCopyValue(values[i]);
    }

\param [ in ] name Name of the argument. This argument may be NULL.
\param [ in ] value The array of values for this the argument. This argument CANNOT be NULL.
\param [ in ] numOfValues The number of values in the value array. This argument CANNOT be 0.

\return Actual number of arguments pushed onto the CLI stack. This could be less than numOfValues if an error happens.
*/
u4 clxCliPushCopyMultiValueArg(const s1* name,
                               const ClxCliValue* values,
                               u4 numOfValues);


/**
Returns the value of the positional argument on the list provided. 

NOTE : If an argument exists at the provided index but it has a name, this function will return NULL. 

NOTE : If the argument exists but has more than one value, the first value will be returned.

\param[ in ] args List of arguments. This could be either the input arguments of the currently running command, 
                  or the return arguments of the command which was terminated.

\param[ in ] index The zero-based index of the argument.

\return The value of the requested argument, or NULL if the requested value does not exist.
*/
const s1* clxCliGetArgValue(const ClxCliArgumentList* args,
                            u4 index);


/**
Returns the value of a named argument on the list provided.

NOTE : If the argument exists but has more than one value, the first value will be returned.

\param[ in ] args List of arguments. This could be either the input arguments of the currently running command,
                  or the return arguments of the command which was terminated.

\param[ in ] name Name of the argument. This argument is case insensitive. This argument CANNOT be NULL.
\param[ in ] index As an input, it determines the first index (zero-based) at which searching for the argument must start.
                   If NULL, the index 0 is used.
                   As an output, it determines the index of the found argument.

\return The value of the requested argument, or NULL if the requested value does not exist.
*/
const s1* clxCliGetNamedArgValue(const ClxCliArgumentList* args,
                                 const s1* name,
                                 u4* index);


/**
Returns the argument at the provided index.

\param[ in ] args List of arguments. This could be either the input arguments of the currently running command,
                  or the return arguments of the command which was terminated.

\param[ in ] index The zero-based index of the argument.

\return An object of type #ClxCliStackArgument. 
        If the requested argument does not exist, the ClxCliStackArgument.values parameter of the return object will be NULL.
*/
ClxCliStackArgument clxCliGetArg(const ClxCliArgumentList* args,
                                 u4 index);


/**
Returns the argument with the provided name.

\param[ in ] args List of arguments. This could be either the input arguments of the currently running command,
                  or the return arguments of the command which was terminated.

\param[ in ] name Name of the argument. This argument is case insensitive. This argument CANNOT be NULL.
\param[ in ] index As an input, it determines the first index (zero-based) at which searching for the argument must start.
                   If NULL, the index 0 is used.
                   As an output, it determines the index of the found argument.

\return An object of type #ClxCliStackArgument.
        If the requested argument does not exist, the ClxCliStackArgument.values parameter of the return object will be NULL.

*/
ClxCliStackArgument clxCliGetNamedArg(const ClxCliArgumentList* args,
                                      const s1* name,
                                      u4* index);


/**
Allocates an event object to be queued into the CLI engine.

\param[ in ] objectSize Size of the event object to allocate. Lets say the object is of the following format:
       struct MyEvent
       {
            ClxCliEvent base;
            // Rest of the parameters:
            ...
       }
    
       The value sizeof(MyEvent) must be passed for this argument. 

\param[ in ] eventType Type of the event object, as returned by #CLX_C_STRUCTURE_TYPE() macro. This argument may be NULL if the event type is not important.
\param[ in ] eventHandlerProc The handler function for the event. This argument must not be NULL.

\return The event object which can be passed to #clxCliQueueEvent(). NULL only if #eventHandlerProc is NULL.
*/
ClxCliEvent* clxCliAllocateEvent(u4 objectSize,
                                 void* eventType,
                                 ClxCliEventHandler eventHandlerProc);


/**
Allocates an event object of type of type #ClxCliA2lIndication (e.g. the event type is CLX_C_STRUCTURE_TYPE(ClxCliA2lIndication)) to be queued into the CLI engine.

\param[ in ] params The parameter object to be copied into this event object. This argument may be NULL.
\param[ in ] paramsLength The length of the parameter object. This argument may be 0 only if params is NULL.
\param[ in ] eventHandlerPro The handler function for the event. This argument must not be NULL.

\return The event object which can be passed to #clxCliQueueEvent(). NULL only if #eventHandlerProc is NULL.
*/
ClxCliA2lIndication* clxCliAllocateA2lIndication(void* params,
                                                 u4 paramsLength,
                                                 ClxCliEventHandler eventHandlerProc);


/**
Queues an event to the CLI engine. Thus function may be called in the context of any thread.
The event is processed when a CLI command is called, or the function #clxCliWaitForUpdate() is called.

\param[ in ] event The event object to be queued,
*/
void clxCliQueueEvent(ClxCliEvent* event);

/**
Waits until at least a single event has been processed or timeout occurs. If timeout is set to 0, then only events already queued will be processed.

\param[ in ] timeout The timeout in milliseconds.

\return TRUE if at least one event is processed. FALSE if the timeout occurs. 
*/
boolean clxCliWaitForUpdate(u4 timeout);


/**
Finds a command with a prefix.

\param[ in ] prefix The beginning of a command name.

\return The found command name, or NULL if a command with the provided prefix was not found.
*/
const s1* clxCliFindCommandByPrefix(const s1* prefix);




#ifdef __cplusplus
}
#endif



#endif // ClarinoxCLI_h
