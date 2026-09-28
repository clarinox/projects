/*******************************************************************************
*
* Project             ClarinoxBlue
* File                JLinkRTT.DebugInterface.Bsp.c
* Description         JLink RTT ClarinoxDebugger Interface
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
#include "assert.h"

#if defined(CLX_JLINK_RTT_DEBUG_INTERFACE)

#define CLX_TERMINAL_INPUT_BUFFER_SIZE    256

#if !defined(CLX_JLINK_RTT_DEBUG_CHANNEL)
#   define CLX_JLINK_RTT_DEBUG_CHANNEL    1
#endif

#if !defined(CLX_JLINK_RTT_DEBUG_OUTPUT_BUFFER_SIZE)
#   define CLX_JLINK_RTT_DEBUG_OUTPUT_BUFFER_SIZE    2048 /* Bytes */
#endif

#define CLX_JLINK_RTT_DEBUG_INPUT_BUFFER_SIZE    CLX_TERMINAL_INPUT_BUFFER_SIZE /* Bytes */

#if !defined(CLX_JLINK_RTT_DEBUG_INPUT_SLEEP_VALUE)
#   define CLX_JLINK_RTT_DEBUG_INPUT_SLEEP_VALUE    100 /* ms */
#endif

#include "JLinkRTT/SEGGER_RTT.h"

// Function to initialize the JLink RTT debug interface
void clxInitDebugJLinkRTTInterface(ClxUartBspInterface* uartIF);

// Structure to hold the JLink RTT debug handle
struct ClxJLinkRttDebugHandle
{
    u1 txBuffer[CLX_JLINK_RTT_DEBUG_OUTPUT_BUFFER_SIZE];
    u1 rxBuffer[CLX_JLINK_RTT_DEBUG_INPUT_BUFFER_SIZE];

    boolean terminated;
};

// Declare a static instance of ClxJLinkRttDebugHandle
static struct ClxJLinkRttDebugHandle jlinkHandle; 

// Function to open the communication port
static ClxResult openPort(const s1* portName,
                           u4 baudRate,
                           enum ClxUartDataBits numOfDataBits,
                           enum ClxUartParity parity,
                           enum ClxUartStopBit numOfStopBits,
                           const ClxConfigParam* userParams,
                           ClxUartPort* handle)
{
    // Unused parameters
    (void)portName;
    (void)baudRate;
    (void)numOfDataBits;
    (void)parity;
    (void)numOfStopBits;
    (void)userParams;

    // Initialize the JLink RTT
    SEGGER_RTT_Init();
    
    // Initialize the JLink RTT debug handle
    jlinkHandle.terminated = FALSE;
        
    // Configure the up buffer for transmitting
    if (SEGGER_RTT_ConfigUpBuffer(CLX_JLINK_RTT_DEBUG_CHANNEL,
                                  "ClarinoxDebugger_TX",
                                  jlinkHandle.txBuffer,
                                  sizeof(jlinkHandle.txBuffer),
                                  SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL) < 0)
    {
        return CLX_FAIL;
    }
    
    // Configure the down buffer for receiving
    if (SEGGER_RTT_ConfigDownBuffer(CLX_JLINK_RTT_DEBUG_CHANNEL,
                                    "ClarinoxDebugger_RX",
                                    jlinkHandle.rxBuffer,
                                    sizeof(jlinkHandle.rxBuffer),
                                    SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL) < 0)
    {
        return CLX_FAIL;
    }
    
    // Set the handle to the address of the jlinkHandle
    *handle = (ClxUartPort)&jlinkHandle;
    
    return CLX_SUCCESS;
}

// Function to write data to the communication port
static ClxResult write(ClxUartPort handle,
                       const u1* data,
                       size_t dataLength,
                       size_t* lengthWritten)
{ 
    // Ensure that the handle is pointing to jlinkHandle
    assert(handle == &jlinkHandle);
    
    // Write data to the JLink RTT channel
    *lengthWritten = SEGGER_RTT_Write(CLX_JLINK_RTT_DEBUG_CHANNEL,
                                      data,
                                      dataLength);
    return CLX_SUCCESS;
}

// Function to read data from the communication port
static ClxResult read(ClxUartPort handle,
                      u1* buf,
                      size_t bufLength,
                      size_t* lengthRead,
                      u4 timeout)
{
    // Ensure that the handle is pointing to jlinkHandle
    assert(handle == &jlinkHandle);

    // Variables for tracking available data and time
    u4 availableDataLength;
    u4 startTime = clxTickTime();
      
    // Continue reading until terminated or timeout
    while (!jlinkHandle.terminated)
    {
        u4 currentTime = clxTickTime();
        // Check for timeout
        if ((currentTime - startTime) >= timeout)
        {
            return CLX_ERROR_TIMEOUT_OCCURRED;
        }
        
        // Check for available data
        availableDataLength = SEGGER_RTT_HasData(CLX_JLINK_RTT_DEBUG_CHANNEL);
        
        if (availableDataLength > 0)
        {
            u4 len2Read = MIN(bufLength, availableDataLength);
            
            // Read data from the JLink RTT channel
            *lengthRead = SEGGER_RTT_Read(CLX_JLINK_RTT_DEBUG_CHANNEL, buf, len2Read);
            
            return CLX_SUCCESS;
        }
        
        // Calculate the time to sleep
        u4 time2Sleep = MIN(((startTime + timeout) - currentTime), CLX_JLINK_RTT_DEBUG_INPUT_SLEEP_VALUE);
          
        clxSleep(time2Sleep);
    }

    return CLX_FAIL;
}

// Function to close the communication port
static ClxResult closePort(ClxUartPort handle)
{
    // Ensure that the handle is pointing to jlinkHandle
    assert(handle == &jlinkHandle);
    
    // Set the terminated flag to TRUE
    jlinkHandle.terminated = TRUE;
    
    return CLX_SUCCESS;
}

// Initialization function for the JLink RTT debug interface
void clxInitDebugJLinkRTTInterface(ClxUartBspInterface* uartIF)
{
    // Assign the functions to the interface
    uartIF->openPort = openPort;
    uartIF->write = write;
    uartIF->read = read;
    uartIF->closePort = closePort; 
}

#endif // #if defined(CLX_JLINK_RTT_DEBUG_INTERFACE)
