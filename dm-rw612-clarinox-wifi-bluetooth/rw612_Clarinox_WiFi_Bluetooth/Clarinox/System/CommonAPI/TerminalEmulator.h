#ifndef TerminalEmulator_h
#define TerminalEmulator_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                TerminalEmulator.h
* Description         Declares TerminalEmulator
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/



#define CLX_TERMINAL_INPUT_BUFFER_SIZE	        256		/* Must be a power of 2. SHALL NOT BE LESS THAN CLX_TERMINAL_INPUT_BUFFER_SIZE_MIN_SIZE */


#define _CLX_TE_SET_COLOR_(Color)               clxTerminalEmulatorSetTextColor(ClxTerminalColor_##Color)
#define _CLX_TE_SET_BG_COLOR_(Color)            clxTerminalEmulatorSetBackgroundColor(ClxTerminalColor_##Color)


/** 
Sets the foreground color for the subsequent text sent to the Terminal Emulator.
The color applies to all text sent afterwards until a new color is set, or the color is reset (by a call to CLX_TE_RESET_COLOR macro or clxTerminalEmulatorResetTextColor() function).

\param[ in ] Color the name of the color to set for the subsequent text. The following colors are available (the names are case sensitive):
    
    Black,  Orange,  Green,       Peach, 
    Blue,   Magenta, Cyan,        Gray, 
    Khaki,  Red,     BrightGreen, Yellow,
    Purple, Brown,   SkyBlue,     White
*/
#define CLX_TE_SET_COLOR(Color)                 _CLX_TE_SET_COLOR_(Color)

/**
Sets the background color for the subsequent text sent to the Terminal Emulator.
The color applies to all text sent afterwards until a new color is set, or the color is reset (by a call to CLX_TE_RESET_BG_COLOR macro or clxTerminalEmulatorResetBackgroundColor() function).

\param[ in ] Color the name of the color to set for the subsequent text. The following colors are available (the names are case sensitive):

    Black,  Orange,  Green,       Peach,
    Blue,   Magenta, Cyan,        Gray,
    Khaki,  Red,     BrightGreen, Yellow,
    Purple, Brown,   SkyBlue,     White
*/
#define CLX_TE_SET_BG_COLOR(Color)              _CLX_TE_SET_BG_COLOR_(Color)

/**
Resets the Terminal Emulator foreground color to its default value. 
NOTE : The default foreground color is determined by ClariFi Virtual Console.
*/
#define CLX_TE_RESET_COLOR                      clxTerminalEmulatorResetTextColor()


/**
Resets the Terminal Emulator background color to its default value.
NOTE : The default background color is determined by ClariFi Virtual Console.
*/
#define CLX_TE_RESET_BG_COLOR                   clxTerminalEmulatorResetBackgroundColor()




#ifdef __cplusplus
extern "C" {
#endif


enum ClxTerminalColor
{
    ClxTerminalColor_Black			= 0,
    ClxTerminalColor_Orange			= 1,
    ClxTerminalColor_Green			= 2,
    ClxTerminalColor_Peach			= 3,
    ClxTerminalColor_Blue			= 4,
    ClxTerminalColor_Magenta		= 5,
    ClxTerminalColor_Cyan			= 6,
    ClxTerminalColor_Gray			= 7,
    ClxTerminalColor_Khaki		    = 8,
    ClxTerminalColor_Red		    = 9,
    ClxTerminalColor_BrightGreen    = 10,
    ClxTerminalColor_Yellow	        = 11,
    ClxTerminalColor_Purple		    = 12,
    ClxTerminalColor_Brown	        = 13,
    ClxTerminalColor_SkyBlue		= 14,
    ClxTerminalColor_White	        = 15
};



/**
Terminal Emulator is a SoftFrame module which emulates a text-based terminal (input and output) on a remote machine. In debug version, this module
communicates with ClarinoxDebugger virtual console via the same communication link used to send debugging data. In release version, a 
dedicated communication link will be assigned to Terminal Emulator.

If enabled, the Terminal Emulator communication link is established during Clarinox SoftFrame initialization, and terminated during Clarinox SoftFrame
termination. In release version, the user is able to provide the communication link configuration settings in the file SoftFrame.cfg. All configuration
settings' names start with TE_ (short for Terminal Emulator). Refer to the contents of the standard SoftFrame.cfg provided by Clarinox for more
information.

When enabled, the application developer can use Terminal Emulator API functions (defined below) to send and receive text and characters to and from the remote
machine. These functions can ONLY be used after the initialization of ClarinoxSoftFrame.

NOTE : It is safe to call these functions if the Terminal Emulator API is not enabled. In this case, these functions will return an error. Make sure these
functions are not running when the module is being terminated. Otherwise, the behaviour of these functions will be undefined.

Clarinox internal IO operations:
The code provided by Clarinox may need to use a text-based terminal for user interaction. All output operations are redirected to the user-defined print function, called userPrintfFunction. This is a function
pointer which can be set to a user-defined function. Also, all input operations are redirected to the user-defined function pointers userGetCharFunction (when a single character is
required) and userGetInputFunction (when a text string is required to be provided by the user). The Clarinox internal code never directly calls Terminal Emulator API functions. 

If it is desired to use the Terminal Emulator module for these internal IO operations, these user-defined functions must explicitly call Terminal Emulator API functions. In the sample BSP file
provided by Clarinox for each project, a sample implementation of these functions are provided which depicts how this can be achieved. Contact Clarinox if you do not have access to these sample functions.

NOTE : All Terminal Emulator API functions (except for clxTerminalEmulatorPrint) are thread-safe.
*/

/**
Specifies if the Terminal Emulator module is enabled at this moment. In debug version, the module is enabled as long as the debug sub-system is enabled and connected to ClarinoxDebugger.
In release version, the module is enabled if it has been configured by the user via the file SoftFrame.h and a communication link has been established to the remote machine.  

\return TRUE if the module is enabled. FALSE if it is not enabled.
*/
boolean clxTerminalEmulatorEnabled(void);


/**
Obtains a string of characters from the remote machine. The function will store the input characters in a caller-provided buffer, and it will not return
until a caller-defined specific character (called termination signal) is received, or the buffer becomes full, or an error occurs.
The returned string will not include the termination signal (it will be replaced by the null-termination character).

\param[ in ] buffer A caller-provided buffer which, on return, will hold the received input. If the function returns CLX_SUCCESS, The buffer will include a null-terminated string.
                    Otherwise, the contents of this buffer will be undefined.
\param[ in ] bufferSize The size of the buffer provided by the caller. This includes the null-termination character. Therefore, the maximum size of the returned string will be bufferSize-1.
\param[ in ] echo If TRUE, the received characters will be echoed back to the remote machine.
\param[ in ] flushInputQueue If TRUE, all characters already received and stored in the internal buffer will be removed. This function will wait for new characters.

/return CLX_SUCCESS if the operation has been successful
CLX_FAIL otherwise
*/
ClxResult clxTerminalEmulatorGetInput(s1* buffer, 
                                      u4 bufferSize, 
                                      boolean echo,
                                      boolean flushInputQueue);

/**
Sends a string of characters to the remote machine.

NOTE : This function is not thread-safe. If two or more threads try to use this function at the same time, the result will
be undefined. If this is not desirable, an external protection mechanism must be employed.

\param[ in ] str The string of characters to be sent to the module. This string does not need to be null-terminated.
\param[ in ] strLen The length of the string provided by the caller.
*/
void clxTerminalEmulatorPrint(const u1* str, ClxSize strLen);

/**
Sets the foreground color for new text. The foreground color will be applied to all subsequent text sent to the terminal (via subsequent calls to #clxTerminalEmulatorPrint).
This function has no effect on the text previously sent to the terminal.
In order to reset the text color to its default value, call #clxTerminalEmulatorResetTextColor().

NOTE : The Terminal Emulator employs a proprietary protocol. As a result, the color change command is correctly decoded only if ClarinoxDebugger Virtual Console plugin is used for the terminal.

\param[ in ] color The foreground color to be used for all subsequent text.
*/
void clxTerminalEmulatorSetTextColor(enum ClxTerminalColor color);

/**
Sets the background color for new text. The background color will be applied to all subsequent text sent to the terminal (via subsequent calls to #clxTerminalEmulatorPrint).
This function has no effect on the text previously sent to the terminal.
In order to reset the text color to its default value, call #clxTerminalEmulatorResetBackgroundColor().

NOTE : The Terminal Emulator employs a proprietary protocol. As a result, the color change command is correctly decoded only if ClarinoxDebugger Virtual Console plugin is used for the terminal.

\param[ in ] color The background color to be used for all subsequent text.
*/
void clxTerminalEmulatorSetBackgroundColor(enum ClxTerminalColor color);

/**
Resets the foreground color to the terminal's default color. The default foreground color will be applied to all subsequent text sent to the terminal (via subsequent calls to #clxTerminalEmulatorPrint).
This function has no effect on the text previously sent to the terminal.

NOTE : The Terminal Emulator employs a proprietary protocol. As a result, the color change command is correctly decoded only if ClarinoxDebugger Virtual Console plugin is used for the terminal.
*/
void clxTerminalEmulatorResetTextColor(void);

/**
Resets the background color to the terminal's default color. The default background color will be applied to all subsequent text sent to the terminal (via subsequent calls to #clxTerminalEmulatorPrint).
This function has no effect on the text previously sent to the terminal.

NOTE : The Terminal Emulator employs a proprietary protocol. As a result, the color change command is correctly decoded only if ClarinoxDebugger Virtual Console plugin is used for the terminal.
*/
void clxTerminalEmulatorResetBackgroundColor(void);
    


#ifdef __cplusplus
}
#endif


#endif    // TerminalEmulator_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/

