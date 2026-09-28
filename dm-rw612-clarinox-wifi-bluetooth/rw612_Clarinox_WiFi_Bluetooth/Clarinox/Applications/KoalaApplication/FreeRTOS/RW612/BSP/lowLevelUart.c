/*******************************************************************************
*
* Project
* File                lowLevelUart.c
* Description	      RW612 Specific low level Uart module functions
*
* This file contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

/*******************************************************************************
 * These functions could not be placed in HardwareUart.c file because the
 * function prototypes in fio.h header file conflicts with the UART interface
 * structure function prototype definitions.
*******************************************************************************/
#include "ClxBsp.h"

static void* fd;
// TODO if we need to use UART, fix this file

/**
Opens the uart
*/
void* debugUartOpen (void)
{
    void *file_ptr;

    fd = 0;//fopen ("ittya:", NULL);
    if (fd == NULL) {
           return 0;
       }
    file_ptr = (void*) fd;
    return (file_ptr);
}

/**
Reads data from Uart
*/
s4 debugUartRead (void *file_ptr, void *buffer, u4 n_bytes)
{
    int ret;

    ret = 0; //fread (buffer, 1, n_bytes, fd);
    return(ret);
}

/**
Write data to Uart
*/
s4 debugUartWrite (void *file_ptr, void *data, u4 n_bytes)
{
    int len;

    len = 0;//fwrite(data, 1, n_bytes, fd);
    if(len != n_bytes) {
        return (1);
    }
    return (len);
}
