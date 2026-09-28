/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                HardwareUart.cpp
* Description		  MCU specific Uart module functions
*
* This file contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#include "ClxTypes.h"
#include "ClxBsp.h"
#include "Uart.Bsp.h"
#include "ClxBspConfig.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
//#include "fsl_lpuart_edma.h"
//#include "fsl_dmamux.h"
#include "fsl_common.h"

/*******************************************************************************
* Definitions
******************************************************************************/

#define OPEN_CLX_BSP_UART_DEBUG_PRINTS  0

#define CLX_USE_STATIC_BUFFERS_AT_UART_COMMUNICATION

//#define LPUART_TX_DMA_CHANNEL           0U
//#define LPUART_RX_DMA_CHANNEL           1U

//#define MAX_BUFFER_LENGTH               256

//#define ACTRONICA_BLUETOOTH_UART_PORT	LPUART3
//#define ACTRONICA_BLUETOOTH_UART_DMA_REQUEST_MUX_TX	kDmaRequestMuxLPUART3Tx
//#define ACTRONICA_BLUETOOTH_UART_DMA_REQUEST_MUX_RX	kDmaRequestMuxLPUART3Rx

/*******************************************************************************
* Constants
******************************************************************************/
//const IRQn_Type g_kaeDmaIRQNumber[][FSL_FEATURE_EDMA_MODULE_CHANNEL] = DMA_CHN_IRQS;

/*******************************************************************************
* Variables
******************************************************************************/
//lpuart_edma_handle_t g_lpuartEdmaHandle;
//edma_handle_t g_lpuartTxEdmaHandle;
//edma_handle_t g_lpuartRxEdmaHandle;
SemaphoreHandle_t g_rxSemaphore;
SemaphoreHandle_t g_txSemaphore;
//AT_NONCACHEABLE_SECTION_INIT(uint8_t g_txBuffer[MAX_BUFFER_LENGTH]) = { 0 };
//AT_NONCACHEABLE_SECTION_INIT(uint8_t g_rxBuffer[MAX_BUFFER_LENGTH]) = { 0 };

#ifdef CLX_USE_STATIC_BUFFERS_AT_UART_COMMUNICATION
// If a BLACKBOX error is seen at write_Bluetooth or read_Bluetooth, an increase in size (CLX_UART_READ_WRITE_BUFFER_SIZE) may be needed.
#define CLX_UART_READ_WRITE_BUFFER_SIZE 1024
//static uint8_t hardwareUartReadBuf[CLX_UART_READ_WRITE_BUFFER_SIZE];
//static uint8_t hardwareUartWriteBuf[CLX_UART_READ_WRITE_BUFFER_SIZE];
#endif
/*******************************************************************************
* Prototypes
******************************************************************************/
//static void bluetooth_task(void *pvParameters);
//void LPUART_UserCallback(LPUART_Type *base, lpuart_edma_handle_t *handle, status_t status, void *userData);
void SendBTMessage(uint8_t *buffer, size_t length);
void ReceiveBTMessage(uint8_t *buffer, size_t length);
int DbgConsole_SendDataReliable(uint8_t *ch, size_t size);

/*******************************************************************************
* Code
******************************************************************************/

/**
Initializes the serial port connected to the Clarinox debugger/Bluetooth Baseband controller.

\param[ in ] portName Specifies the UART/USART port to be initialized.
\param[ in ] baudRate specifies the baud rate to be used.
\param[ in ] numOfDataBits Specifies the number of data bits to be used.
\param[ in ] parity specifies the parity.
\param[ in ] numOfStopBits: specifies the number of stop bits.
\param[ in ] userParams In case, if the user wants to pass any input.
\param[ in ] handle Handle refers to the UART/USART port being used.

\return CLX_SUCCESS if the operation has been successful.
Any other value indicates an error.
*/
static ClxResult openPort_Bluetooth (const s1* portName,
                            u4 baudRate,
                            enum ClxUartDataBits numOfDataBits,
                            enum ClxUartParity parity,
                            enum ClxUartStopBit numOfStopBits,
                            const ClxConfigParam* userParams,
                            ClxUartPort* handle)
{
    return(CLX_SUCCESS);
}

/**
Write data to the serial port connected to the Clarinox Debugger/Bluetooth Baseband controller

\param[ in ] handle Handle refers to the UART/USART port being used.
\param[ in ] data specifies the address of the data to be written.
\param[ in ] dataLength Specifies the length of the data to be written.
\param[ in ] lengthWritten contains the value of the number of data written.

\return CLX_SUCCESS if the operation has been successful.
Any other value indicates an error.
*/
static ClxResult write_Bluetooth (ClxUartPort handle,
                        const u1* data,
                        size_t dataLength,
                        size_t* lengthWritten)
{
    return(CLX_SUCCESS);
}

/**
Reads data from the serial port connected to the Clarinox debugger/Bluetooth Baseband controller

\param[ in ] handle Handle refers to the UART/USART port being used.
\param[ in ] buf Contains read values.
\param[ in ] bufLength Specifies the length of the data to be read.
\param[ in ] lengthRead contains the value of the number of data read.

\return CLX_SUCCESS if the operation has been successful.
Any other value indicates an error.
*/
static ClxResult read_Bluetooth (ClxUartPort handle,
                        u1* buf,
                        size_t bufLength,
                        size_t* lengthRead,
                        u4 timeout)
{
    return(CLX_SUCCESS);
}

/**
Closes the UART port connected to the Clarinox Debugger/Bluetooth Baseband controller

\param[ in ] handle Handle refers to the UART/USART port being used.

\return CLX_SUCCESS if the operation has been successful.
Any other value indicates an error.
*/
static ClxResult closePort_Bluetooth (ClxUartPort handle)
{
    return(CLX_SUCCESS);
}

/* LPUART user callback */
//void LPUART_UserCallback(LPUART_Type *base, lpuart_edma_handle_t *handle, status_t status, void *userData)
//{
//
//}

void clxInitBluetoothUartInterface(ClxUartBspInterface* uartIF)
{
    uartIF->openPort  = openPort_Bluetooth;
    uartIF->write     = write_Bluetooth;
    uartIF->read      = read_Bluetooth;
    uartIF->closePort = closePort_Bluetooth;
}

static ClxResult openPort_ClariFi (const s1* portName,
                            u4 baudRate,
                            enum ClxUartDataBits numOfDataBits,
                            enum ClxUartParity parity,
                            enum ClxUartStopBit numOfStopBits,
                            const ClxConfigParam* userParams,
                            ClxUartPort* handle)
{
    return CLX_SUCCESS;
}

static ClxResult write_ClariFi (ClxUartPort handle,
                        const u1* data,
                        size_t dataLength,
                        size_t* lengthWritten)
{
	DbgConsole_SendDataReliable ((u1*)data, dataLength);
	*lengthWritten = dataLength;
	return CLX_SUCCESS;
}

static ClxResult read_ClariFi (ClxUartPort handle,
                        u1* buf,
                        size_t bufLength,
                        size_t* lengthRead,
                        u4 timeout)
{
	if (bufLength != 1) // we expect debugger to read one at a time at least for now
	{
		BLACKBOX;
	}
	int ret = -1;
	while(ret == -1)
	{
		clxSleep(20);
		ret = DbgConsole_Getchar();
	}
	*buf = (u1)ret;
	*lengthRead = bufLength;
	return CLX_SUCCESS;
}

static ClxResult closePort_ClariFi (ClxUartPort handle)
{
	return CLX_SUCCESS;
}

void clxInitDebugUartInterface(ClxUartBspInterface* uartIF)
{
    uartIF->openPort  = openPort_ClariFi;
    uartIF->write     = write_ClariFi;
    uartIF->read      = read_ClariFi;
    uartIF->closePort = closePort_ClariFi;
}
