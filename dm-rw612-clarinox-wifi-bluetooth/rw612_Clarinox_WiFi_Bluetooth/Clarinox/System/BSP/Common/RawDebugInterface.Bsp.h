#ifndef RawDebugInterface_Bsp_h
#define RawDebugInterface_Bsp_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                RawDebugInterface.Bsp.h
* Description         Raw One-way (e.g. output-only) Debug BSP interface
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


/**
Raw Debug Interface structure declares function pointers serving as interface between application and SoftFrame debug subsystem
for handling debug logs. This is a one-way (output-only) interface.
*/
struct ClxBspRawDebugInterface
{
    /**
    Initializes the raw debug interface.
    This is called by the stack during the initialization of the SoftFrame debug subsystem.

    NOTE : This method is called in the context of the stack thread.

    If any error occurs, an implementation must return an error (any value other than CLX_SUCCESS).

    NOTE : If the initialization of the interface fails for any reason,
    the other methods of the structure ClxBspRawDebugInterface will not be called.

    \return CLX_SUCCESS if the procedure has been successful. In this case, the interface is initialized.
    Any other value indicates an error.
    */
    ClxResult(*init)       ();

    /**
    Destroys the already-initialized interface. This is called by the stack during the termination of the Clarinox stack
    and shutdown of the stack debug system.

    NOTE : This method is called in the context of the stack thread.

    NOTE : This method CANNOT fail.
    */
    void (*destroy)         ();

    /**
    Called when a debug log event is available to be logged. This interface function is called whenever a new debug log event is
    generated internally by the stack modules and could be logged by the application.

    The application can implement the desired logging mechanism to handle these debug log events, based on the requirement.

    Example:-
    The function can implement the logic to save the log data to a .cdd file. This gives the application the freedom and flexibility to
    manage the size and contents of the log file according to the limitations of the application.

    NOTE : This method is called in the context of the stack.

    \param[ in ] buff       A stack-allocated buffer memory containing the debug log event.
    \param[ in ] dataLength Length of the debug log event string returned in #buff
    */
    void (*logReceived)     (_in_ const void* buff, _in_ u4 dataLength);

    /**
    Unused by Clarinox stack. May be set by the implementation of this interface.
    */
    void* userData;
};


/*
Raw debug interface structure consisting of pointers to the interface functions implemented by the application.
The structure is defined in the stack and called by the stack's debug system
*/
extern struct ClxBspRawDebugInterface* clxBspRawDebugInterface;


#ifdef __cplusplus
}
#endif




#endif // RawDebugInterface_Bsp_h
