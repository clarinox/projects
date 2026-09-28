/*******************************************************************************
*
* Project             ClarinoxSoftframe
* File                UartBsp.c
* Description         UART interface
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

struct UartPort
{
    ClxUartBspInterface interface;
    ClxUartPort         handle;
};

#if defined (CLX_UART_BLUETOOTH)
static struct UartPort bluetoothPort;
#endif

#if defined(CLX_UART_DEBUG) || defined(CLX_JLINK_RTT_DEBUG_INTERFACE)
static struct UartPort debugPort;
#endif


#if defined(CLX_UART_DEBUG) && defined(CLX_JLINK_RTT_DEBUG_INTERFACE)
#error "Define only one of CLX_UART_DEBUG or CLX_JLINK_RTT_DEBUG_INTERFACE"
#endif

#if !defined(CLX_UART_DEBUG) && !defined(CLX_JLINK_RTT_DEBUG_INTERFACE)
#error "Define one of CLX_UART_DEBUG or CLX_JLINK_RTT_DEBUG_INTERFACE"
#endif


#if defined(CLX_UART_DEBUG)
extern  void clxInitDebugUartInterface(ClxUartBspInterface* uartIF);
#endif

#if defined (CLX_UART_BLUETOOTH)
extern  void clxInitBluetoothUartInterface(ClxUartBspInterface* uartIF);
#endif

#if defined(CLX_JLINK_RTT_DEBUG_INTERFACE)
extern  void  clxInitDebugJLinkRTTInterface(ClxUartBspInterface* uartIF);
#endif

/***************************************************************************************
  * brief  Initializes both Bluetooth and Debug serial port.
  * param  portName: Specifies the UART/USART port to be initialized.
  * param  baudRate: specifies the baud rate to be used.
  * param  numOfDataBits: Specifies the number of data bits to be used.
  * param  parity: specifies the parity.
  * param  numOfStopBits: specifies the number of stop bits.
  * param  userParams: In case, if the user wants to pass any input.
  * param  handle: Handle refers to the UART/USART port being used.
  * retval CLX_SUCCESS/CLX_FAIL.
  ************************************************************************************/

static ClxResult openPort (const s1* portName,
                            u4 baudRate,
                            enum ClxUartDataBits numOfDataBits,
                            enum ClxUartParity parity,
                            enum ClxUartStopBit numOfStopBits,
                            const ClxConfigParam* userParams,
                            ClxUartPort* handle)
{

   ClxResult ret = CLX_FAIL;

#if defined (CLX_UART_BLUETOOTH)
   if(strcmp( "BLUETOOTH_PORT", portName ) == 0)
   {
       clxInitBluetoothUartInterface(&bluetoothPort.interface);

       ret = bluetoothPort.interface.openPort(portName,
                                              baudRate,
                                              numOfDataBits,
                                              parity,
                                              numOfStopBits,
                                              userParams,
                                              &bluetoothPort.handle);

       if (ret == CLX_SUCCESS)
       {
           *handle = (ClxUartPort)&bluetoothPort;
       }
   }
#endif

#if defined(CLX_UART_DEBUG) || defined(CLX_JLINK_RTT_DEBUG_INTERFACE)
   if(strcmp( "DEBUG_PORT", portName ) == 0)
   {
#if defined(CLX_JLINK_RTT_DEBUG_INTERFACE)
       clxInitDebugJLinkRTTInterface(&debugPort.interface);
#else
       clxInitDebugUartInterface(&debugPort.interface);
#endif
       ret = debugPort.interface.openPort(portName,
                                          baudRate,
                                          numOfDataBits,
                                          parity,
                                          numOfStopBits,
                                          userParams,
                                          &debugPort.handle);

       if (ret == CLX_SUCCESS)
       {
           *handle = (ClxUartPort)&debugPort;
       }
   }
#endif

   return ret;
}

/****************************************************************************************
  * brief  Write to both Debug and Bluetooth Ports.
  * param  handle: Handle refers to the UART/USART port being used.
  * param  data: specifies the address of the data bus to be written.
  * param  dataLength: Specifies the length of the data to be written.
  * param  lengthWritten: contains the value of the number of data written.
  * retval CLX_SUCCESS/CLX_FAIL.
  ************************************************************************************/		

static ClxResult write (ClxUartPort handle,
                        const u1* dataUart,
                        size_t dataLengthUart,
                        size_t* lengthWritten)
{
	
   struct UartPort* port = (struct UartPort*)handle;

   return port->interface.write(port->handle,
                                dataUart,
                                dataLengthUart,
                                lengthWritten);

}

/*************************************************************************************
  * brief  Write to both Debug and Bluetooth Ports.
  * param  handle: Handle refers to the UART/USART port being used.
  * param  buf: Contains read values.
  * param  bufLength: Specifies the length of the data to be read.
  * param  lengthRead: contains the value of the number of data read.
  * retval CLX_SUCCESS/CLX_FAIL.
  ************************************************************************************/

static ClxResult read (ClxUartPort handle,
                        u1* buf,
                        size_t bufLength,
                    size_t* lengthRead,
                    u4 timeout)
{

   struct UartPort* port = (struct UartPort*)handle;

   return port->interface.read(port->handle,
                               buf,
                               bufLength,
                                lengthRead,
                                timeout);
}


/**************************************************************************************
  * brief  Write to both Debug and Bluetooth Ports.
  * param  handle: Handle refers to the UART/USART port being used.
  * retval CLX_SUCCESS/CLX_FAIL.
  ************************************************************************************/	
static ClxResult closePort (ClxUartPort handle)
{
   struct UartPort* port = (struct UartPort*)handle;

   return port->interface.closePort(port->handle);
}

ClxUartBspInterface clxUartGenericBspInterface = { &openPort,
                                                   &write,
                                                   &read,
                                                   &closePort};
