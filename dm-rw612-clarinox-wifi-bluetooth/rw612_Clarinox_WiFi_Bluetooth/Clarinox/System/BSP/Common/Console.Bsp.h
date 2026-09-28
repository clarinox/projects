#ifndef Console_Bsp_h
#define Console_Bsp_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                Console.Bsp.h
* Description         Console IO interface for BSP
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
External print function prototype is used by an application to redirect printf/cout function calls.
If this function pointer is assigned to a user "printf" function, then the debug prints will be redirected here.
Otherwise platform specific default "printf" function will be used.
Print a \p formatted printable string to the user defined printf function.
\param[ in ] formattedOutput is the null-terminated string containing the formatted printable string.
*/
extern void (*userPrintfFunction) ( s1* formattedOutput );

/**
Called by ClarinoxSoftFrame when a string of characters needs to be provided by the user. If this function pointer is not assigned to a
user-defined function, scanf will be used.
*/
extern s4 (*userGetInputFunction) ( s1* buffer, u4 bufferSize );


#ifdef __cplusplus
}
#endif


#endif // Console_Bsp_h
