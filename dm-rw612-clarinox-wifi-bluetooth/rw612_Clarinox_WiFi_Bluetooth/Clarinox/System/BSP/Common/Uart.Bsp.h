#ifndef Uart_Bsp_h
#define Uart_Bsp_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                Uart.Bsp.h
* Description         Declares a UART interface implemented by BSP 
*                      call-back functions
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#define CLX_USER_UART_BSP_INTERFACE_CONFIG_FILE_NAME        "SoftFrame.cfg"
#define CLX_USER_UART_BSP_INTERFACE_CONFIG_NAMESPACE        "ClxUartUserApi"

/*
User configuration parameters for UART BSP interface may be defined as CLX_USER_UART_API_CONFIG_FILE_NAME.
within the namespace as defined by CLX_USER_UART_API_CONFIG_NAMESPACE.
*/
#define CLX_USER_UART_API_MAX_CONFIG_PARAMS        10

/*
Uart read default timeout value.
*/
#define CLX_USER_UART_READ_DEFAULT_TIMEOUT         5000

#ifdef __cplusplus
extern "C" {
#endif

enum ClxUartParity
{
    ClxUartParity_Even = 0,
    ClxUartParity_Odd  = 1,
    ClxUartParity_None = 2
};

enum ClxUartStopBit
{
    ClxUartStopBit_One     = 0,
    ClxUartStopBit_OneHalf = 1,
    ClxUartStopBit_Two     = 2
};

enum ClxUartDataBits
{
    ClxUartDataBits_7 = 7,
    ClxUartDataBits_8 = 8
};

typedef void* ClxUartPort;
/**
Callback function prototypes used by BSP to handle stack function calls. 
*/
typedef struct ClxUartBspInterfaceStruct
{
    /**
    This Callback function called when open port request is received from the system.
    \param[ in ] portName NULL terminated string as listed in configuration file.
    \param[ in ] baudRate value in kbps.
    \param[ in ] numOfDataBits Number of Data bits as per #ClxUartDataBits.
    \param[ in ] parity parity type supported as per #ClxUartParity.
    \param[ in ] userParams user configuration parameters of the type #ClxConfigParam
    \param[ in ] handle port handle of type #ClxUartPort returned upon successful port open operation.

    \return ClxResult. Function must return either of the following result codes. 
    - CLX_SUCCESS: if operation is successful.
    - CLX_FILE_NOT_EXIST: if either portName, parity, numOfStopBits or userParams does not exist
    - CLX_FILE_OPEN_FAILED: if port cannot be opened.
    - CLX_FILE_IS_OPEN: if port is already in use/opened.
    - CLX_FILE_UNSPECIFIED_ERROR: if handle cannot be created for unknown reasons.
    */
    ClxResult (*openPort) (const s1* portName,
                            u4 baudRate,
                            enum ClxUartDataBits numOfDataBits,
                            enum ClxUartParity parity,
                            enum ClxUartStopBit numOfStopBits,
                            const ClxConfigParam* userParams,
                            ClxUartPort* handle);

    /**
    This Callback function called when a WRITE request is received from the system. Note that the write function call does not dictate the complete writing of the dataLength
    \param[ in ] handle UART handle of type #ClxUartPort.
    \param[ in ] data pointer to the dataBuffer which contains data to be written.
    \param[ in ] dataLength length of the data to be written.
    \param[ in ] lengthWritten if the function returns then this variable indicates the length of the data written so far....
                                In case function returns ClxResult which is other than CLX_SUCCESS, lengthRead must be ignored.
    \return ClxResult. Function must return either of the following result codes. 
    - CLX_SUCCESS: if operation is successful.
    - CLX_FILE_INVALID_HANDLE: if handle is invalid
    - CLX_FILE_ERROR_WRITING: if there is problem with write operation.
    - CLX_FILE_ACCESS_DENIED: if the file cannot be written due to e.g. file permissions being set to Read-only, file already open etc...
    - CLX_FILE_NOT_EXIST: if file does not exist.
    */
    ClxResult (*write) (ClxUartPort handle,
                        const u1* data,
                        size_t dataLength,
                        size_t* lengthWritten);

    /**
    This Callback function called when a READ request is received from the system. Note that the READ function call does not dictate the complete reading of the dataLength.
    This call is in blocking nature, i.e. read function must not return if there is no data read. 
    \param[ in ] handle UART handle of type #ClxUartPort. The content of this value is implementation-specific. If the port is opened successfully, this value CANNOT be NULL. 
    \param[ in ] data pointer to the data Buffer which contains data read.
    \param[ in ] dataLength length of the data to be read.
    \param[ in ] lengthRead if the function returns then this variable indicates the length of the data read so far....
                               In case function returns ClxResult which is other than CLX_SUCCESS, lengthRead must be ignored.
    \return ClxResult. Function must return either of the following result codes. 
    - CLX_SUCCESS: if operation is successful.
    - CLX_FILE_INVALID_HANDLE: if handle is invalid
    - CLX_FILE_ERROR_READING: if there is problem with read operation.
    - CLX_FILE_NOT_READABLE: if the file read is forbidden.
    - CLX_FILE_ACCESS_DENIED: if the file cannot be written due to for e.g. file permissions are set such that READ is forbidden, file already open, file cannot be opened etc...
    - CLX_FILE_NOT_EXIST: if file does not exist.
    */
    ClxResult (*read) (ClxUartPort handle,
                        u1* data,
                        size_t dataLength,
                        size_t* lengthRead,
                        u4 timeout);

    /**
    This Callback function called when close port request is received from the system.
    \param[ in ] handle UART handle of type #ClxUartPort.
   
    \return ClxResult. Function must return either of the following result codes. 
    - CLX_SUCCESS: if operation is successful.
    - CLX_INVALID_HANDLE: if handle is invalid.
    - CLX_FILE_UNSPECIFIED_ERROR: if closing the port failed with an unspecified error.
    */
    ClxResult (*closePort) (ClxUartPort handle);
} ClxUartBspInterface;

/**
Clarinox stacks internally use the clxUartBspInterface hook for allowing developers to provide their own UART BSP implementation for a target platform. 
These implementations need to implement all of the functions defined as part of the #ClxUartBspInterfaceStruct structure.
*/
extern ClxUartBspInterface* clxUartBspInterface;


#ifdef __cplusplus
}
#endif

#endif // Uart_Bsp_h

/******************************************************************************/
/* 1. MISRA C 2004 RULE VIOLATION:                                            */
/* Message       : Identifiers (internal and external) shall not rely on the  */
/*                 significance of more than 31 characters.                   */
/* Rule          : MISRA-C:2004 Rule 5.1                                      */
/* Justification : Improves clarity of macro definitions. The compiler used   */
/*                 supports symbols longer than 31 characters, hence no risks.*/
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
