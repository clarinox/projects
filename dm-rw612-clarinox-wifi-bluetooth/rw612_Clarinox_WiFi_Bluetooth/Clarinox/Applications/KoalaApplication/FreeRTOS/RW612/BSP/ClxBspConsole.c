/*******************************************************************************
*
* Project             Koala Application
* File                ClxBspConsole.c
* Description         Clarinox heap functions and variables are defined here.
*
* This file contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include "stdio.h"

/**
User can overload the default printf function used by the stack. if userPrintfFunction (function pointer) is not assigned, 
then the platform default printf will be used
*/
void printfFunction ( char* formattedOutput )
{
    if (clxTerminalEmulatorEnabled())
    {
        clxTerminalEmulatorPrint((const u1*)formattedOutput, strlen(formattedOutput));
    }
    else
    {
        // printf (formattedOutput);
    }
}

/**
User can overload the default userScanf function used by the stack. if userGetInputFunction (function pointer) is not assigned, 
then the platform default userScanf will be used
*/
int getInputFunction ( char* buffer, unsigned int bufferSize )
{
    if (clxTerminalEmulatorEnabled())
    {
        clxTerminalEmulatorGetInput(buffer, 
                                    bufferSize, 
                                    TRUE,
                                    TRUE);    /* Flush the input queue to get rid of the old characters */
    }
    else
    {
        //scanf ("%s", buffer);
    }

    return 0 /* Success */;
}


