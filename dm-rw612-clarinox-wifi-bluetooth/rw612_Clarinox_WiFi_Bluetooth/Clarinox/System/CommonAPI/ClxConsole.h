#ifndef ClxConsole_h
#define ClxConsole_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxConsole.h
* Description         Declares ClxConsole related declarations
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
Read one character from standard input, without echoing it to the standard output
\return The character read.
*/
extern char clxGetChar( void );

/**
Read one character from standard input, and put it on standard output.
\return The character read.
*/
extern char clxGetCharEcho( void );
/**
Put one character back to the standard input.
\param[ in ] c The character to put back.
*/
extern void clxUnGetChar  ( char c );

/**
Print a string to the standard output. If the function userPrintfFunction() has been implemented by the application,
it will be called. Otherwise, the default "printf" function for the underlying platform will be called.
\param[ in ] string pointer to the null-terminated string to be printed.
*/
extern void clxPrintString ( s1* string );

/**
Get a characters from the standard input. If the function userGetInputFunction() has been implemented by the application,
it will be called. Otherwise, the default "scanf" function for the underlying platform will be called.
\param[ in ] string pointer to be filled with characters read from the standard input.
\param[ in ] bufferSize maximum number of characters to read from the standard input.
*/
extern ClxResult clxGetInput ( s1* string, u4 bufferSize );

/**
Implements the standard C runtime library function sprintf(). 
*/
extern int clxSprintf ( s1 *string, const s1 *format, ... );

/**
Implements the standard C runtime library function vsprintf().
*/
extern int clxVsprintf(s1* string, const s1* format, va_list args);

/**
Implements the standard C runtime library function sscanf().
*/
extern int clxSscanf ( const s1* str, const s1* format, ... );

/**
Writes the C string pointed by format to the standard output.
\param[ in ] arg Formatted C string that contains text to be written to stdout.
\(additional param)[in] Depending on the format string, the function may expect a sequence of additional parameters, each containing a value to be used to replace 
a format specifier in the format string.
*/
extern void CLX_PRINTF ( const s1* arg, ... );

/** 
The same as CLX_PRINTF, with the exception that it appends the current time (as returned by clxTickTime) to the beginning of the text. 

NOTE : A new line character is inserted to the beginning and end of the text by this function.
*/
extern void clxPrintfTimestamped(const s1* format, ...);


#ifdef __cplusplus
}
#endif


#endif    // ClxConsole_h

