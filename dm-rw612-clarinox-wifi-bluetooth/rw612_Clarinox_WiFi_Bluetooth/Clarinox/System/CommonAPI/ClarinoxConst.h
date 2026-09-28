#ifndef ClarinoxConst_h
#define ClarinoxConst_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClarinoxConst.h
* Description         Declares Clarinox Stack constants and types
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


struct ClxHandleBase;
struct ClxStackBase;

/** A handle represents an instance of a local (non-RPC) service */
typedef struct ClxHandleBase*   ClxHandle;

/** A variable of type ClxStack represents an instance of a local (non-RPC) Clarinox stack */
typedef struct ClxStackBase*    ClxStack;


#if defined(_in_)
#   undef _in_
#endif
/** parameters with an attribute _in_ are input-only variables which are provided by the user. 
The memory may be destroyed after the API function returns (in either blocking or non-blocking mode).*/
#define _in_

#if defined(_out_)
#   undef _out_
#endif
/** 
Parameters with an attribute _out_ point to a buffer which must be provided by the user in blocking mode API function calls. 
These parameters are not used in non-blocking mode and may be set to NULL. In non-blocking mode, the same data elements are
accessible in a temporary buffer provided and owned by the stack.
*/
#define _out_

#if defined(_user_in_)
#   undef _user_in_
#endif
/** 
Parameters with an attribute _user_in_ are input-only pointers which point to a memory buffer provided by the user. 
The buffer must NOT be touched or destroyed until the API command is complete (in either blocking or non-blocking mode).
The buffer may only be destroyed when the command is complete.
*/
#define _user_in_

#if defined(_user_out_)
#   undef _user_out_
#endif
/** 
Parameters with an attribute _user_out_ point to a buffer provided by the user.
The buffer may NOT be modified or destroyed until the command is complete (in either blocking or non-blocking mode).
*/
#define _user_out_

#if defined(_inout_)
#   undef _inout_
#endif

/**
Parameters with an attribute _inout_ are served as both input and output. These parameters are always defined as a pointer. 
This attribute is never used with a buffer. It is only used along with numeric parameters.
*/
#define _inout_

/** 
Callback function prototype is used by application to handle stack callback function calls 

\param[ in ] stack			Local device stack handle
\param[ in ] serviceHandle	A service handle represents a Wireless LAN/Bluetooth service(WLAN: AP/Station/P2P; Bluetooth: SPP/A2DP/BLE), implemented 
							as a part of ClarinoxWiFi/ClarinoxBlue stack. The user must create a handle to a service when required, and close it when 
							not needed. Each API group provides its own API function which can be used to create a handle to an instance of the corresponding wireless mode. The obtained handle 
							may be passed to other API functions of the same mode. It is worthwhile mentioning that a handle to an instance of a 
							specific mode CANNOT be passed to API functions of a DIFFERENT mode.
\param[ in ] indicationID	Each indication has its own unique ID and also may have data arguments. From the message-oriented programming point of view, 
							indications are equivalent to messages where "indicationID" represents the message type, and "params" represents the message body
\param[ in ] params			If the Indication contains any data parameters, the "params" argument of the callback function will be a pointer to a C struct. 
							The type of the structure will be fixed for a given indication.
							Please note that "params" only points to a temporary data structure which is supplied by the stack. As soon as the callback function returns,
							the pointer will be deemed invalid. Therefore, the pointer must not be stored to be used in the future, If the application needs to keep the
							response data parameters, it has to make a deep copy of it and store it in an application-provided memory buffer.
\param[ in ] errorCode		An error code is generated as the response to a previously issued command when the API function was called in the non-blocking mode. 
							In this case, "errorCode" argument of the callback function represents the error code returned by the command.							

\return                     For backward compatibility with older systems only. The return value is ignored in the current system.                            
*/
typedef boolean (*ClxApplicationCallbackFunc) (ClxStack stack, ClxHandle serviceHandle, u4 indicationID, const void* params, ClxError errorCode); 




#ifdef __cplusplus
}
#endif


#endif // ClarinoxConst_h

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : Define or undefine of reserved identifier                  */
/* Rule          : MISRA-C:2004 Rule 20.1                                     */ 
/* Justification : No risk identified. Used for clarity in API definitions    */
/*                 only limited to _in_, _out_, _user_in, _user_out_ , _inout_*/
/******************************************************************************/


/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : #define and #undef shall not be used on a reserved 		  */
/*				   identifier or reserved macro name                  		  */
/* Rule          : MISRA-C:2012 Rule 21.1                                     */ 
/* Justification : No risk identified. Used for clarity in API definitions    */
/*                 only limited to _in_, _out_, _user_in, _user_out_ , _inout_*/
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A reserved identifier or macro name shall not be delcared  */            
/* Rule          : MISRA-C:2012 Rule 21.2                                     */ 
/* Justification : No risk identified. Used for clarity in API definitions    */
/*                 only limited to _in_, _out_, _user_in, _user_out_ , _inout_*/
/******************************************************************************/
