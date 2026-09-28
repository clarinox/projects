#ifndef ClxBsp_Errors_h
#define ClxBsp_Errors_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxBsp.Errors.h
* Description         Error codes to be reported by BSP-related functions
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if !defined(CLX_SUCCESS)
#   define CLX_SUCCESS                                   0
#endif

#define CLX_ERROR_SDIO_REQUEST_PENDING                  (CLX_ERROR_COMPLETION_PENDING)
#define CLX_ERROR_SDIO_DRIVER_NOT_EXIST                 (CLX_SYSTEM_ENOENT)
#define CLX_ERROR_SDIO_WRONG_STATE                      (CLX_SYSTEM_EBUSY)
#define CLX_ERROR_SDIO_INIT_FAILED                      (CLX_SYSTEM_EIO)
#define CLX_ERROR_SDIO_FAILED_TO_OPEN_DRIVER            (CLX_SYSTEM_EIO)
#define CLX_ERROR_SDIO_NO_CARD_INSERTED                 (CLX_SYSTEM_ENODEV)
#define CLX_ERROR_SDIO_DEVICE_DRIVER_SHUT_DOWN          (CLX_SYSTEM_EBADF)
#define CLX_ERROR_SDIO_IO_FUNCTION_NOT_EXIST            (CLX_SYSTEM_ENOSYS)
#define CLX_ERROR_SDIO_REQUEST_NOT_PROCESSED            (CLX_SYSTEM_EIO)
#define CLX_ERROR_SDIO_REQUEST_TYPE_NOT_RECOGNISED      (CLX_SYSTEM_ENOPROTOOPT)
#define CLX_ERROR_SDIO_REQUEST_NOT_SUCCESSFUL           (CLX_SYSTEM_EFAULT)

#define CLX_FILE_END_OF_FILE                            (EOF)
#define CLX_FILE_NOT_EXIST                              (CLX_SYSTEM_ENOENT)
#define CLX_FILE_IS_OPEN                                (CLX_SYSTEM_EBUSY)
#define CLX_FILE_NOT_WRITABLE                           (CLX_SYSTEM_EPERM)
#define CLX_FILE_NOT_READABLE                           (CLX_SYSTEM_EPERM)
#define CLX_FILE_NOT_APPENDABLE                         (CLX_SYSTEM_EPERM)
#define CLX_FILE_OPEN_FAILED                            (CLX_SYSTEM_EIO)
#define CLX_FILE_CREATE_FAILED                          (CLX_SYSTEM_EIO)
#define CLX_FILE_ACCESS_DENIED                          (CLX_SYSTEM_EACCES)
#define CLX_FILE_INVALID_HANDLE                         (CLX_SYSTEM_EBADF)
#define CLX_FILE_UNSPECIFIED_ERROR                      (CLX_SYSTEM_UNKNOWN_ERROR)
#define CLX_FILE_OPEN_FLAG_NOT_CONSISTENT               (CLX_SYSTEM_EINVAL)
#define CLX_FILE_LEN_OVER_4GB_NOT_SUPPORTED             (CLX_SYSTEM_EFBIG)
#define CLX_FILE_ERROR_WRITING                          (CLX_SYSTEM_EIO)
#define CLX_FILE_ERROR_READING                          (CLX_SYSTEM_EIO)


#ifndef EOF
#   define EOF (-1)
#endif

#endif // ClxBsp_Errors_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/
