#ifndef _ClarinoxBlue_h_
#define _ClarinoxBlue_h_

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                ClarinoxBlue..h
* Description         ClarinoxBlue Bluetooth Protocol Stack common include file
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#include "ClarinoxBlueConst.h"
#include "ClarinoxBlueErrorCodes.h"

/**
The minimum size of the output buffer which is passed to #clxConvertBluetoothAddressToAscii function.
*/
#define CLX_BLUETOOTH_ADDRESS_ASCII_MIN_BUFFER_SIZE                18


/**
This indication is received when the initialization of the stack is
complete either with success or in error.

The argument errorCode of the call-back function will be one of the following:
 
 - CLX_SUCCESS : the stack is successfully initialized and ready to use.
 - CLX_ERROR_CLARINOX_BLUE_FAILED : the stack could not be initialized. Although the
   stack is not initialized, but still the stack object has been created (and received
   as the argument stack of the call-back function). Therefore, the object still needs
   to be destroyed by calling #clxDestroyClarinoxBlue (or the equivalent in the target platform). 
   Note that, in this case, the function #clxTerminateClarinoxBlue (or the equivalent in the target platform)
   MUST NOT be called since the stack has never been initialized, hence no need for termination.

This indication does not have any parameter (params argument of the call-back function
will be NULL).
*/
#define CLX_INIT_CLARINOX_BLUE_COMPLETE                    0x453C

/**
This indication is received when the local application has requested for the stack to terminate, and the first phase of termination is complete.
Upon reception of this indication, the stack MUST be destroyed by calling the function provided to destroy the stack (this function may be different
for different platforms). Note that, the stack CANNOT be destroyed within the context of the call-back function thread.

This indication does not have any parameter (params argument of the call-back function
will be NULL). Also, all other arguments of the call-back function (except for indicationID) will have INVALID values.
*/
#define CLX_TERMINATE_CLARINOX_BLUE_COMPLETE               0x453D

/**
Used internally.
*/
#define CLX_DESTROY_CLARINOX_BLUE_COMPLETE                 0x453E

/**
Refer to #clxBluetoothStackPing function.
*/
#define CLX_BLUETOOTH_STACK_PING_COMPLETE                  0x453F

/**
This indication is sent to the application when the Clarinox Bluetooth evaluation license period has expired.
*/
#define CLX_BLUETOOTH_LICENSE_EXPIRED_INDICATION           0x8540

/**
External reference for initialization and release of Bluetooth configuration parameters
*/

#ifdef __cplusplus
extern "C" {
#endif

ClxConfigList*   initializeClarinoxBlueBspConfigParameters(void);
void             releaseClarinoxBlueBspConfigParameters(ClxConfigList* configList);

extern ClxStack clarinoxBlueStackObject;

/**
ClarinoxBlue configuration file name
*/
extern const s1* clxClarinoxBlueConfigFileName;

/**
ClarinoxBlue Low Energy configuration file name
*/
extern const s1* clxClarinoxBlueLEConfigFileName;


/**
This function is called by ClarinoxBlue during the stack initialization in order to send
vendor specific HCI commands to the Bluetooth controller. 
The function is invoked before any other HCI commands sent to the wireless chip.
Usually, this function manages some of these following tasks;
 - loading firmware to the wireless chip
 - running the loaded firmware
 - setting the local Bluetooth device address
 - setting the audio path
 - setting the audio parameters
 - setting RF power levels
 - sending HCI reset command to the wireless chip (note that this is the only HCI command which is not a vendor specific command)

\param[ in ] stack Local device stack handle. A stack object must be created before a Vendor Specific command is sent.

\return CLX_ERROR_INVALID_COMMAND_ARGUMENT the argument eventPacket is NULL.
        CLX_ERROR_COMMAND_NOT_COMPLETE a previous Vendor Specific command has not returned yet.
        CLX_ERROR_TIMEOUT_OCCURRED Timeout occurred before a response to the command was received.
        CLX_SUCCESS The command was successfully sent to the Bluetooth controller and a response was received with a pointer to the response buffer
        being returned as the argument eventPacket.

\remark If this function returns anything other than CLX_SUCCESS, the stack initialization will be immediately complete with failure.
*/
extern ClxError (*clxHciSendVendorSpecificCommands)( ClxStack stack );

/**
Initiates ClarinoxBlue stack. When this function is used in non-blocking mode returns immediately. Upon initialization of the stack is complete, 
an indication of type CLX_INIT_CLARINOX_BLUE_COMPLETE will be sent to the GAP call-back function. 
The errorCode parameter of the call-back function must be checked, to see if the stack has been initialized successfully. 

Below shows error handling when a non-blocking initialization call is made;;
\code
if (clxInitClarinoxBlue(&params, FALSE, stackMessageHandler, &stack, FALSE) != CLX_ERROR_COMPLETION_PENDING)
{
       clxConsoleUIEngineText ("Initialization of ClarinoxBlue failed\n");
       return 0;
}
\endcode


If this function is used in blocking mode, then it returns upon successful completion of the Bluetooth stack.
\code
if (clxInitClarinoxBlue(&params, FALSE, stackMessageHandler, &stack, TRUE) != CLX_SUCCESS)
{
       clxConsoleUIEngineText ("Initialization of ClarinoxBlue failed\n");
       return 0;
}
\endcode


\param[  in  ] parameterConfigList      The global parameters of the stack. If a configuration parameter does not exist in the list,
                                        the default value will be used for that parameter. This argument may be NULL. In this case, the default value will be used for all parameters.
\param[  in  ] indicationScheduler      An optional scheduler object to be used for scheduling ClarinoxBlue application indications. If NULL, a new thread with its own dedicated scheduler 
                                        will be internally started for the application indications. This is intended for Clarinox internal use (DO NOT CHANGE).
\param[  in  ] gapCallbackFunc          A pointer to the GAP call-back functions which will receive GAP-related indications. This parameter CANNOT be NULL.
\param[  out ] stack                    A pointer to clarinoxBlue stack object.
\param[  in  ] block                    Type of the operation.
                                        - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError error code for the operation.
                - CLX_ERROR_COMPLETION_PENDING: initialization is in progress, operation will be completed asynchronously (only in non-blocking mode)
                - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
                - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet.
                - CLX_ERROR_INVALID_HANDLE: invalid handle.
                In case of blocking mode the following error codes may also be returned.
                - CLX_SUCCESS: operation is successful

\remark exceptionCallback is a user-defined function which is called when a fatal error occurs inside the
        stack. The reason for the fatal error is a BLACKBOX which represents an error condition from which the stack cannot recover.
        Upon reception of an exception, the user should:
        - record the moduleID and line information passed to the callback function, and present it to Clarinox for investigation.
        - restart the entire application without trying to terminate or destroy the stack instance.

The application must not continue execution when an exception has happened. The following example shows an exception handler;
\code

void userExceptionHandler( s4 moduleId, s4 lineNumber )
{
    printf("ClarinoxBlue raised an exception in module: %u, line: %u\n", moduleId, lineNumber);
}

// the following must be set before calling the initialization function;
// userExceptionFunction = userExceptionHandler;
\endcode

A more complete example detailing initialization is shown below;
\code
    // configuration parameters that would override default parameter 
    struct GenericConfigParameters
    {
        ClxConfigInteger supportSecureSimplePairing;
        ClxConfigInteger enableLinkLevelAuthentication;
        ClxConfigInteger ioCapabilities;
        ClxConfigInteger linkRequestTimeout;
        ClxConfigInteger majorClassOfDevice;
        ClxConfigInteger minorClassOfDevice;
        ClxConfigInteger serviceClasses;
        ClxConfigString localDeviceName;
    };

    GenericConfigParameters genericConfigParameters;

    clxConfigInitIntegerParam(&genericConfigParameters.supportSecureSimplePairing,      "SupportSecureSimplePairing",       TRUE,             configList); 
    clxConfigInitIntegerParam(&genericConfigParameters.enableLinkLevelAuthentication,   "EnableLinkLevelAuthentication",    FALSE,            configList); 
    clxConfigInitIntegerParam(&genericConfigParameters.ioCapabilities,                  "IoCapabilities",                   IO_NONE,          configList); 
    clxConfigInitIntegerParam(&genericConfigParameters.linkRequestTimeout,              "LinkRequestTimeout",               16000,            configList); 
    clxConfigInitIntegerParam(&genericConfigParameters.majorClassOfDevice,              "MajorClassOfDevice",               MJ_AUDIO_VIDEO,   configList); 
    clxConfigInitIntegerParam(&genericConfigParameters.minorClassOfDevice,              "MinorClassOfDevice",               AVMI_CAR_AUDIO,   configList); 
    clxConfigInitStringParam (&genericConfigParameters.localDeviceName,                 "LocalDeviceName",                  deviceName,       configList); 

    clxConfigInitIntegerParam(&genericConfigParameters.serviceClasses,                  "ServiceClasses",                   ( ST_LIMITED_DISCOVERABLE_MODE |
                                                                                                                              ST_POSITIONING               |
                                                                                                                              ST_NETWORKING                |
                                                                                                                              ST_RENDERING                 |
                                                                                                                              ST_CAPTURING                 |
                                                                                                                              ST_OBJECT_TRANSFER           |
                                                                                                                              ST_AUDIO                     |
                                                                                                                              ST_TELEPHONY                 |
                                                                                                                              ST_INFORMATION ),   configList); 

    // Initialize the Bluetooth stack 
    if (clxInitClarinoxBlue(NULL,
                            NULL,
                            stackMessageHandler,
                            stack, 
                            TRUE ) != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("Initialization of ClarinoxBlue failed\n");
            ret = FALSE;
        }
        else
        {
            clxConsoleUIEngineText("ClarinoxBlue version %s\n",
                                    clxGetClarinoxBlueVersion());
       }

\endcode

*/
ClxError clxInitClarinoxBlue(_user_in_ ClxConfigList*               parameterConfigList,
                             _in_      ClxScheduler                 indicationScheduler,
                             _in_      ClxApplicationCallbackFunc   gapCallbackFunc,
                             _out_     ClxStack*                    stack,
                             _in_      boolean                      block);


/**
Initiates the first phase of the stack termination. The first phase includes cleaning up the stack by disconnecting from the remote services.
This function is non-blocking and returns immediately. When the first phase is complete, an indication of type CLX_TERMINATE_CLARINOX_BLUE_COMPLETE
will be received by the GAP call-back function. At that moment, the second phase of ClarinoxBlue termination must be performed by calling #clxDestroyClarinoxBlue.

IMPORTANT : All open handles belonging to this instance of stack MUST BE CLOSED before this function is called. Otherwise, the behaviour will be undefined, and the stack
may even crash.

Below example demonstrates how to terminate stack;

\code
// This code must be executed in the context of a user_thread
    clxCloseHandle(someSppHandle);                  // close all the handles for open profiles
    clxTerminateClarinoxBlue(stack, FALSE);         // terminate ClarinoxBlue
    clxAcquireSemaphore(terminationSemaphore);      // wait for termination completion
    clxDeleteSemaphore(terminationSemaphore);       // semaphore is not required anymore
        
    clxDestroyClarinoxBlue(stack);                  // Destroy the stack, after this call is completed, stack can be initialized again
    stack = NULL;
    ClxConsoleUIEngine::destroy();                  // Whole SoftFrame is destroyed, after this point only user applications (threads) are active
\endcode

To be able to achieve this code the stack call-back handler must implement 

\code
// stackMessageHandler must be assigned as stack call-back handler
boolean stackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    if(messageID == CLX_TERMINATE_CLARINOX_BLUE_COMPLETE)       // indication of stack termination completion
    {                                                           // now ready to destroy the stack, so synchronize with the user thread             
        if (errorCode == 0)
        { 
            clxConsoleUIEngineText("ClarinoxBlue termination completed\n");
            clxReleaseSemaphore (terminationSemaphore);         // synchronize with the user thread for destruction
        }
        else
        {
            clxConsoleUIEngineText("\nStack termination was not successful (error : %s)", clxGetErrorCodeText(errorCode));
        }
    }
    return TRUE;
}
\endcode

\param[ in ] clarinoxBlue   The ClarinoxBlue stack object.
\param[ in ] block          Type of the operation.
                            - TRUE:  API will be blocked until this command is completed (successfully or failed).
                            - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxResult error code for the operation.
                - CLX_ERROR_COMPLETION_PENDING: initialization is in progress, operation will be completed asynchronously (only in non-blocking mode)
                - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
                - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet.
                - CLX_ERROR_INVALID_HANDLE: invalid handle.
                In case of blocking mode the following error codes may also be returned.
                - CLX_SUCCESS: operation is successful

*/
ClxResult clxTerminateClarinoxBlue(_in_ ClxStack clarinoxBlue,
                                   _in_ boolean  block);

/**
Performs the second (last) phase of ClarinoxBlue termination by deleting the objects, threads, and timers. It also releases all the memory used by the stack.
This function MUST ONLY be called when the first phase of stack termination is complete (in case clxTerminateClarinoxBlue is called in non-blocking mode, 
an indication of type CLX_TERMINATE_CLARINOX_BLUE_COMPLETE has been received). When this function returns, the stack is completely terminated.

IMPORTANT : Note that this function CANNOT be called within the context of the GAP call-back function (or any other service call-back functions) thread.
This is due to the fact that the call-back thread must also be terminated and cleaned up by this function. The developer must devise a mechanism in order to 
call this function outside of the call-back function.
\see clxTerminateClarinoxBlue for an example code snippet for termination and destruction of the Bluetooth stack

\param[ in ] clarinoxBlue   The ClarinoxBlue stack object.
*/
void clxDestroyClarinoxBlue(_in_ ClxStack clarinoxBlue);

/**
Returns a text string containing the name of the error code. This function only returns the string in debug mode.
In release mode, the return string is always an empty string.

\param[ in ] errorCode The error code for which a string representation must be returned.

\return A stack-allocated string containing the string representation of the error code. This string MUST not be modified or deleted.
*/
const s1* clxGetErrorCodeText(ClxError errorCode);

/**
Returns the ClarinoxBlue version.
\return A function-allocated buffer containing the version as a null-terminated string.
        The buffer must NOT be modified by the caller.
        Version is in the form of "[major_version].[minor_version].[revision].p[patch_no]"
*/
const s1* clxGetClarinoxBlueVersion(void);

/**
Returns the ClarinoxBlue repository revision number
\returns the repository revision as an unsigned integer number 
*/
u4 clxGetClarinoxBlueRevision(void);

/**
Returns the Local Bluetooth device address as a NULL terminated string
\param[ in ] asciiOutput User provided storage; requires 13 bytes
*/
void clxGetLocalBluetoothDeviceAddress(u1* asciiOutput);

/**
Returns the Local Bluetooth device HCI version as a NULL terminated string
\param[ in ] asciiOutput User provided storage; requires 3 bytes
*/
void clxGetLocalBluetoothHciVersion(u1* asciiOutput);

/**
Returns the Local Bluetooth device HCI revision as a NULL terminated string
\param[ in ] asciiOutput User provided storage; requires 5 bytes
*/
void clxGetLocalBluetoothHciRevision(u1* asciiOutput);

/**
Returns the Local Bluetooth device manufacturer name as a NULL terminated string
In the release version, first 2 bytes of the asciiOutput populated with the manufacturer code 
in little-endian format
\param[ in ] asciiOutput User provided storage; requires 9 bytes. 
*/
void clxGetLocalBluetoothDeviceManufacturer(u1* asciiOutput);

/**
writes the ASCII representation of a Bluetooth address into a caller-provided buffer of size CLX_BLUETOOTH_ADDRESS_ASCII_MIN_BUFFER_SIZE bytes. The ASCII representation is in the format XX:XX:XX:XX:XX:XX

\param[ in ] address The Bluetooth address, as 6-byte binary data.
\param[ out ] asciiOutput A buffer which on return will hold the Bluetooth address in ASCII format. The size of this buffer SHALL be at least CLX_BLUETOOTH_ADDRESS_ASCII_MIN_BUFFER_SIZE bytes.
The output will be NULL terminated.

\return A pointer to the output buffer (same as asciiOutput).
*/
s1* clxConvertBluetoothAddressToAscii(const u1* address, s1* asciiOutput);

/**
Encodes SCO voice setting details into a 2-byte SCO voice setting value.

\param[ in ] voiceSetting On a successful return (e.g. when the function returns TRUE), this value will contain the encoded 2-byte SCO voice setting value. This argument CANNOT be NULL.
\param[ in ] inputCodingFormat Input coding format. The only valid values are #ClxBluetoothCodingFormat_uLaw, #ClxBluetoothCodingFormat_aLaw, #ClxBluetoothCodingFormat_LinearPCM, and #ClxBluetoothCodingFormat_Transparent.
                                                    Any other value will result in this function returning FALSE.
\param[ in ] inputPcmFormat Input PCM data format. 
                            Relevant only if inputCodingFormat is set to ClxBluetoothCodingFormat_LinearPCM..
\param[ in ] pcmSampleSize Input PCM sample size. The only valid values are #ClxBluetoothPcmSampleSize_8Bits, and #ClxBluetoothPcmSampleSize_16Bits. 
                           Any other value will result in this function returning FALSE.
                           Relevant only if inputCodingFormat is set to ClxBluetoothCodingFormat_LinearPCM..
\param[ in ] pcmBitPosition Number of bit positions that the MSB of the sample is from the MSB of the value.
                            Relevant only if inputCodingFormat is set to ClxBluetoothCodingFormat_LinearPCM..
\param[ in ] airCoding The Air coding.

\return TRUE, if the encoding has been successful. In this case, the encoded value is stored in the first argument.
        FALSE, if the encoding has failed due to one or more arguments containing invalid values.
*/
extern boolean clxEncodeScoVoiceSetting(_out_ u2* voiceSetting,
                                        _in_ ClxBluetoothCodingFormat inputCodingFormat, 
                                        _in_ ClxBluetoothPcmDataFormat inputPcmFormat,
                                        _in_ ClxBluetoothPcmSampleSize pcmSampleSize,
                                        _in_ u1 pcmBitPosition,
                                        _in_ ClxScoAirCodingFormat airCoding);

/**
Decodes a 2-byte SCO voice setting value into SCO voice setting details.

\param[ in ] voiceSetting the encoded 2-byte SCO voice setting value which is to decoded.
\param[ in ] inputCodingFormat Input coding format. This argument may be NULL.
\param[ in ] inputPcmFormat Input PCM data format. This argument may be NULL.
\param[ in ] pcmSampleSize Input PCM sample size. This argument may be NULL.
\param[ in ] pcmBitPosition Number of bit positions that the MSB of the sample is from the MSB of the value. This argument may be NULL.
\param[ in ] airCoding The Air coding. This argument may be NULL.
*/
extern void clxDecodeScoVoiceSetting(_in_ u2 voiceSetting,
                                     _out_ ClxBluetoothCodingFormat* inputCodingFormat, 
                                     _out_ ClxBluetoothPcmDataFormat* inputPcmFormat,
                                     _out_ ClxBluetoothPcmSampleSize* pcmSampleSize,
                                     _out_ u1* pcmBitPosition,
                                     _out_ ClxScoAirCodingFormat* airCoding);

/**
Pings ClarinoxBlue stack to check whether it is responsive to user commands.
This API can be used for implementing Watchdog mechanism for monitoring Bluetooth task lock up conditions.
The Bluetooth stack must be initialized before this API can be used.

This API is non-blocking and will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.

When the command is complete, the call-back function will be called with an indication of type #CLX_BLUETOOTH_STACK_PING_COMPLETE.
This indication does not have any parameters.

\param[  in   ] stack  Local device stack handle. A stack object must be created before this API is used.

\return #CLX_SUCCESS if successful, the result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
*/
ClxResult clxBluetoothStackPing(_in_ ClxStack  stack);

#ifdef __cplusplus
}
#endif


#endif // _ClarinoxBlue_h_

