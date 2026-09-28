#ifndef ClarinoxErrorCodes_h
#define ClarinoxErrorCodes_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClarinoxErrorCodes.h
* Description         ClarinoxSoftFrame common error code definitions
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#if !defined(CLX_SUCCESS)
#define CLX_SUCCESS                                             0
#endif

#if !defined(CLX_FAIL)
#define CLX_FAIL                                                (-1)
#endif

#if !defined(CLX_ERROR)
#define CLX_ERROR                                               (-1)
#endif

/**
Error codes 0 to 0x0FFF are reserved for Clarinox common (non-stack-specific) errors.
*/
#define CLX_ERROR_COMMON_LAST									            0x1000


#define CLX_ERROR_COMPLETION_PENDING                                        0x0101      /* Not indicating an error. Indicates that an initiated procedure will continue asynchronously 
                                                                                           in a context different from the one in which this error has been received */ 
#define CLX_ERROR_INTERNAL_ERROR                                            0x0102
#define CLX_ERROR_INVALID_CALLBACK                                          0x0103
#define CLX_ERROR_INVALID_HANDLE                                            0x0104
#define CLX_ERROR_INVALID_COMMAND_ARGUMENT                                  0x0105
#define CLX_ERROR_COMMAND_NOT_COMPLETE                                      0x0106
#define CLX_ERROR_COMMAND_UNSUCCESSFUL                                      0x0107
#define CLX_ERROR_COMMAND_CANCELLED                                         0x0108
#define CLX_ERROR_TIMEOUT_OCCURRED                                          0x0109
#define CLX_ERROR_ANOTHER_COMMAND_IN_PROGRESS                               0x010A
#define CLX_ERROR_CONNECTION_FAILED                                         0x010B
#define CLX_ERROR_CONNECTION_EXISTS                                         0x010C
#define CLX_ERROR_CONNECTION_NOT_EXIST                                      0x010D
#define CLX_ERROR_CONNECTION_ESTABLISHMENT_IN_PROGRESS                      0x010E
#define CLX_ERROR_CONNECTION_INITIATION_NOT_ALLOWED                         0x010F
#define CLX_ERROR_DISCONNECTION_IN_PROGRESS                                 0x0110
#define CLX_ERROR_INVALID_REQUEST                                           0x0111
#define CLX_ERROR_HANDLE_COMMANDS_PENDING                                   0x0112
#define CLX_ERROR_COMMAND_NOT_SUPPORTED                                     0x0113
#define CLX_ERROR_COMMAND_NOT_HANDLED                                       0x0114
#define CLX_ERROR_BAD_STATE                                                 0x0115
#define CLX_ERROR_TASK_CONTEXT_SCHEDULED	                                0x0116
#define CLX_ERROR_TASK_EVENT_ATTACHED		                                0x0117
#define CLX_ERROR_TASK_CONTEXT_NOT_SCHEDULED			                    0x0118
#define CLX_ERROR_TASK_TERMINATED		                                    0x0119
#define CLX_ERROR_TASK_TIMER_NOT_RUNNING		                            0x011A
#define CLX_ERROR_TASK_TIMER_INVALID_INTERVAL		                        0x011B
#define CLX_ERROR_TASK_WRONG_CONTEXT_STATE                                  0x011C
#define CLX_ERROR_TASK_SCHEDULER_TERMINATED                                 0x011D
#define CLX_ERROR_TASK_SCHEDULER_NO_CONTEXT_PENDING                         0x011E
#define CLX_ERROR_HARDWARE_ERROR                                            0x011F
#define CLX_ERROR_UNEXPECTED_ARGUMENT_TYPE                                  0x0120
#define CLX_ERROR_A2L_RPC_MORE_DATA_REQUIRED                                0x0121
#define CLX_STATUS_A2L_RPC_MORE_FRAGMENTS						            0x0122
#define CLX_ERROR_A2L_RPC_NO_LINK								            0x0123
#define CLX_ERROR_A2L_RPC_LINK_FAILED							            0x0124
#define CLX_ERROR_A2L_RPC_INVALID_COMMAND_CONTEXT				            0x0125
#define CLX_ERROR_A2L_RPC_PENDING_COMMAND_FOR_CONTEXT			            0x0126
#define CLX_ERROR_A2L_RPC_INVALID_RESPONSE_A2L_ID				            0x0127
#define CLX_ERROR_A2L_RPC_NO_COMMAND_PENDING					            0x0128
#define CLX_ERROR_A2L_RPC_NO_ENOUGH_CONTEXT_MEMORY				            0x0129
#define CLX_ERROR_A2L_RPC_DUPLICATE_COMMAND_CONTEXT_ID			            0x012A
#define CLX_ERROR_A2L_RPC_DUPLICATE_SERVICE_ID					            0x012B
#define CLX_ERROR_INVALID_VIRTUAL_STACK_ALLOCATION				            0x012C
#define CLX_ERROR_A2L_COMMAND_NOT_KNOWN							            0x012D
#define CLX_ERROR_A2L_INDICATION_NOT_KNOWN						            0x012E
#define CLX_ERROR_DATABASE_RECORD_EXISTS						            0x012F
#define CLX_ERROR_DATABASE_RECORD_NOT_FOUND						            0x0130
#define CLX_SERIAL_ERROR_NO_MORE_ELEMENTS				                    0x0131
#define CLX_SERIAL_ERROR_INVALID_TYPE					                    0x0132
#define CLX_SERIAL_ERROR_NOT_ENOUGH_SPACE				                    0x0133
#define CLX_SERIAL_ERROR_INVALID_SERIALIZATION			                    0x0134
#define CLX_SERIAL_ERROR_ARGUMENTS_NEEDED				                    0x0135
#define CLX_SERIAL_ERROR_NO_ARGUMENT_EXPECTED			                    0x0136
#define CLX_SERIAL_ERROR_INVALID_ARRAY_SIZE				                    0x0137 
#define CLX_ERROR_DATABASE_NOT_EXIST						                0x0138
#define CLX_ERROR_DATABASE_PAIRED_DATABASE_CORRUPTED			            0x0139
#define CLX_ERROR_COROUTINE_CANCELLED                                       0x013A
#define CLX_ERROR_TERMINAL_IN_BINARY_MODE                                   0x013B
#define CLX_ERROR_TASK_SCHEDULER_LOOP_BROKEN                                0x013C
#define CLX_ERROR_NO_CONTROL_CHANNEL_CONNECTION                             0x013D
#define CLX_ERROR_CONTROL_CHANNEL_CONNECTION_FAILED                         0x013E
#define CLX_ERROR_FUNCTION_NOT_EXIST_ON_CONTROL_CHANNEL                     0x013F
#define CLX_ERROR_CONTROL_CHANNEL_CALLBACK_NOT_EXIST                        0x0140
#define CLX_ERROR_EXCEPTION_IN_CONTROL_CHANNEL_CALLBACK_HANDLER             0x0141  

#define CLX_ERROR_NOT_COMPLETE                                              0x0142
#define CLX_ERROR_NOT_FOUND                                                 0x0143
#define CLX_ERROR_NOT_AVAILABLE                                             0x0144
#define CLX_ERROR_TERMINATED                                                0x0145
#define CLX_ERROR_NO_CONNECTION                                             0x0146
#define CLX_ERROR_BUSY                                                      0x0147
#define CLX_ERROR_CANCELLED                                                 0x0148
#define CLX_ERROR_REQUEST_CANCELLED                                         0x0149
#define CLX_ERROR_REQUEST_CANNOT_BE_CANCELLED                               0x014A
#define CLX_ERROR_OUT_OF_RANGE                                              0x014B

#define CLX_ERROR_MEMORY_EXHAUSTED                                          0x014C
#define CLX_ERROR_MEMORY_BUFFERS_NOT_IN_ORDER                               0x014D
#define CLX_ERROR_MEMORY_INCORRECT_HEAP_SIZE                                0x014E
#define CLX_ERROR_SEARCHED_ITEM_NOT_FOUND                                   0x014F
#define CLX_ERROR_INVALID_STATE                                             0x0150
#define CLX_ERROR_FLOW_STOPPED                                              0x0151
#define CLX_ERROR_MEMORY_INCORRECT_BUFFER_SIZE                              0x0152

#define CLX_ERROR_CONTROL_CHANNEL_INVALID_ACTION_TYPE                       0x0153
#define CLX_ERROR_CONTROL_CHANNEL_INVALID_ACTION_DATA                       0x0154
#define CLX_ERROR_TEST_CASE_NOT_EXIST                                       0x0155
#define CLX_ERROR_TEST_CASE_EXECUTION_FAILED                                0x0156

#define CLX_ERROR_SDIO_COM_CRC_FAILED                                       0x0157      /* CRC error reported by the SDIO card */
#define CLX_ERROR_SDIO_CMD_RSP_CRC_FAIL                                     0x0158      /* CRC error reported by the local SDIO host */
#define CLX_ERROR_SDIO_DATA_CRC_FAIL                                        0x0159      /* CRC error reported by the local SDIO host */
#define CLX_ERROR_SDIO_CMD_RSP_TIMEOUT                                      0x015A
#define CLX_ERROR_SDIO_DATA_TIMEOUT                                         0x015B
#define CLX_ERROR_SDIO_ILLEGAL_CMD                                          0x015C
#define CLX_ERROR_SDIO_GENERAL_UNKNOWN_ERROR                                0x015D
#define CLX_ERROR_SDIO_INVALID_VOLTAGE                                      0x015E
#define CLX_ERROR_SDIO_OUT_OF_RANGE                                         0x015F
#define CLX_ERROR_SDIO_UNKNOWN_FUNCTION                                     0x0160
#define CLX_ERROR_SDIO_INVALID_FUNCTION_OPERATION                           0x0161                                                                                            
#define CLX_ERROR_SDIO_INTERNAL_ERROR		                                0x0162
#define CLX_ERROR_A2L_RPC_LINK_ACK_TIMEOUT                                  0x0163          
          
/**
Standard System Error codes. The values of these error codes are independent from
the underlying platform error codes.
*/
#define CLX_SYSTEM_EPERM                                        1 
#define CLX_SYSTEM_ENOENT                                       2 
#define CLX_SYSTEM_ESRCH                                        3 
#define CLX_SYSTEM_EINTR                                        4 
#define CLX_SYSTEM_EIO                                          5 
#define CLX_SYSTEM_ENXIO                                        6 
#define CLX_SYSTEM_E2BIG                                        7 
#define CLX_SYSTEM_ENOEXEC                                      8 
#define CLX_SYSTEM_EBADF                                        9 
#define CLX_SYSTEM_ECHILD                                       10 
#define CLX_SYSTEM_EAGAIN                                       11 
#define CLX_SYSTEM_ENOMEM                                       12 
#define CLX_SYSTEM_EACCES                                       13 
#define CLX_SYSTEM_EFAULT                                       14 
#define CLX_SYSTEM_ENOTBLK                                      15 
#define CLX_SYSTEM_EBUSY                                        16 
#define CLX_SYSTEM_EEXIST                                       17 
#define CLX_SYSTEM_EXDEV                                        18 
#define CLX_SYSTEM_ENODEV                                       19 
#define CLX_SYSTEM_ENOTDIR                                      20 
#define CLX_SYSTEM_EISDIR                                       21 
#define CLX_SYSTEM_EINVAL                                       22 
#define CLX_SYSTEM_ENFILE                                       23 
#define CLX_SYSTEM_EMFILE                                       24 
#define CLX_SYSTEM_ENOTTY                                       25 
#define CLX_SYSTEM_ETXTBSY                                      26 
#define CLX_SYSTEM_EFBIG                                        27 
#define CLX_SYSTEM_ENOSPC                                       28 
#define CLX_SYSTEM_ESPIPE                                       29 
#define CLX_SYSTEM_EROFS                                        30 
#define CLX_SYSTEM_EMLINK                                       31 
#define CLX_SYSTEM_EPIPE                                        32 
#define CLX_SYSTEM_EDOM                                         33 
#define CLX_SYSTEM_ERANGE                                       34 
#define CLX_SYSTEM_EDEADLK                                      35
#define CLX_SYSTEM_ENAMETOOLONG                                 36
#define CLX_SYSTEM_ENOLCK                                       37
#define CLX_SYSTEM_ENOSYS                                       38
#define CLX_SYSTEM_ENOTEMPTY                                    39
#define CLX_SYSTEM_ELOOP                                        40
#define CLX_SYSTEM_EWOULDBLOCK                                  (CLX_SYSTEM_EAGAIN)

/* Generally Socket-related: */  
#define CLX_SYSTEM_ENOTSOCK                                     88   
#define CLX_SYSTEM_EDESTADDRREQ                                 89   
#define CLX_SYSTEM_EMSGSIZE                                     90   
#define CLX_SYSTEM_EPROTOTYPE                                   91   
#define CLX_SYSTEM_ENOPROTOOPT                                  92   
#define CLX_SYSTEM_EPROTONOSUPPORT                              93   
#define CLX_SYSTEM_ESOCKTNOSUPPORT                              94   
#define CLX_SYSTEM_EOPNOTSUPP                                   95   
#define CLX_SYSTEM_EPFNOSUPPORT                                 96   
#define CLX_SYSTEM_EAFNOSUPPORT                                 97   
#define CLX_SYSTEM_EADDRINUSE                                   98   
#define CLX_SYSTEM_EADDRNOTAVAIL                                99   
#define CLX_SYSTEM_ENETDOWN                                     100   
#define CLX_SYSTEM_ENETUNREACH                                  101   
#define CLX_SYSTEM_ENETRESET                                    102   
#define CLX_SYSTEM_ECONNABORTED                                 103   
#define CLX_SYSTEM_ECONNRESET                                   104   
#define CLX_SYSTEM_ENOBUFS                                      105   
#define CLX_SYSTEM_EISCONN                                      106   
#define CLX_SYSTEM_ENOTCONN                                     107   
#define CLX_SYSTEM_ESHUTDOWN                                    108
#define CLX_SYSTEM_ETOOMANYREFS                                 109
#define CLX_SYSTEM_ETIMEDOUT                                    110   
#define CLX_SYSTEM_ECONNREFUSED                                 111   
#define CLX_SYSTEM_EHOSTDOWN                                    112   
#define CLX_SYSTEM_EHOSTUNREACH                                 113  
#define CLX_SYSTEM_EALREADY                                     114   
#define CLX_SYSTEM_EINPROGRESS                                  115 
#define CLX_SYSTEM_ESTALE                                       116
#define CLX_SYSTEM_EUCLEAN                                      117
#define CLX_SYSTEM_ENOTNAM                                      118
#define CLX_SYSTEM_ENAVAIL                                      119
#define CLX_SYSTEM_EISNAM                                       120
#define CLX_SYSTEM_EREMOTEIO                                    121
#define CLX_SYSTEM_EDQUOT                                       122
#define CLX_SYSTEM_ENOMEDIUM                                    123
#define CLX_SYSTEM_EMEDIUMTYPE                                  124
#define CLX_SYSTEM_ECANCELED                                    125

#define CLX_SYSTEM_UNKNOWN_ERROR                                0x0FFF


#endif // ClarinoxErrorCodes_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/
