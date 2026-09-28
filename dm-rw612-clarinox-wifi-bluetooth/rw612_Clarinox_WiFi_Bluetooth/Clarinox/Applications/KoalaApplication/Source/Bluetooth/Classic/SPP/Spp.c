/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                Spp.cpp
* Description         This file provides SPP profile handle creation / deletion, 
                      SPP UI menu, and indication call back functions.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2021 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/


/*******************************************************************************************************************************
a.  Spp.cpp has a call-back function (stackMessageHandler) that handles stack events. 
    clxSppReceive() needs to be invoked to prepare a receive. 
    The receive completed event (CLX_SPP_RECEIVE_COMPLETE) indicates reception of data and provides the buffer 
    (with the data received from the other device). This call-back function should not be blocked. 
    If the call after receiving data needs to be blocking, then the received buffer can be passed into a queue and 
    signal a semaphore to wake up another task and do the rest of the processing in that task. 

b.  To send a buffer from another task, clxSppSend() needs to be called for sending a buffer (after the connection is made; 
    i.e. event CLX_SPP_CONNECTION_INDICATION is received)  and wait for     CLX_SPP_SEND_COMPLETE event. 
    This way is preferred for interfacing in a multi-threaded architecture. 
    Send and receive calls can be used in blocking mode from a single thread as well but it is more restrictive.
*******************************************************************************************************************************/

#include "ClxCommon.h"
#include "ClarinoxBlue.h"
#include "ClxTime.h"

#include "Gap.Api.h"
#include "Spp.Api.h"
#include "Spp.h"


/* Enum for menu items */
typedef enum ClxSppMenuEnum
{
    ClxSppMenu_Connect                 = 1,
    ClxSppMenu_WaitForConnection,
    ClxSppMenu_SendAsciiText,
    ClxSppMenu_SendPrebuiltTestData,
    ClxSppMenu_Disconnect,
    ClxSppMenu_ReturnToPreviousMenu,
    ClxSppMenu_Total
}ClxSppMenu;

/* 
Macros to define data sizes for SPP Speed test between the SPP devices. 
*/
#define TX_RX_DATA_BLOCK_SIZE           333
#define NUMBER_OF_DATA_BLOCKS           130
#define HEADER_SIGNATURE                0x41

/* 
Maximum size of buffer to get the user input to transmit to the remote device 
*/
#define MAX_TEXT_SIZE                   48

/*
Maximum size of the print message displayed to user to get relevant input.
To be altered if any of the message size goes beyond this limit
*/
#define MAX_MESSAGE_SIZE                52

/* 
Maximum length of receive buffer 
*/
#define CLX_RX_BUFFER_SIZE              (3*TX_RX_DATA_BLOCK_SIZE)

/* 
Variables associated with SPP object 
*/
typedef struct ClxSppInstanceInfoStruct
{
    ClxHandle   spp;                                /* SPP profile handle                                               */

    u1          sppReceive[TX_RX_DATA_BLOCK_SIZE];  /* Buffer to receive SPP data                                       */
    ClxSize     sppReceiveDataSize;                 /* Size of receive buffer                                           */
    u1          testBlock[TX_RX_DATA_BLOCK_SIZE];   /* Buffer to send test SPP data                                     */
    u1          rxBuffer[CLX_RX_BUFFER_SIZE];       /* Buffer to store SPP stream data received from remote device      */
    s1          in[MAX_TEXT_SIZE];                  /* Buffer to get the user input to transmit to the remote device    */

    ClxSize     receivedDataLength;                 /* Variables to store received data length and count                */
    ClxSize     testDataCount;                      /* Variables to store number of received data blocks                */
    boolean        server;                             /* Default is server, if client will change on connection           */
}ClxSppInstanceInfo;

/* Structure with variables required for SPP instance */
ClxSppInstanceInfo sppInfo  = {};

/*******************************************************************************************************************************
*                                                sppIndicationHandler
*
* This call-back function is registered for the GAP and SPP profiles, 
* any events raised by GAP profile causes this call-back function executed with
* the associated event and parameters 
*
* \param stack         - Local device stack handle
* \param serviceHandle - Profile/service handle
* \param messageID     - Indication id
* \param params        - Void pointer to the indication parameters
* \param errorCode     - Contains the error code
*
* \return boolean      - TRUE If the call-back function handles indication or indication with *_COMPLETE.
*                        Otherwise, it will return FALSE
*
*******************************************************************************************************************************/
boolean sppIndicationHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    /* Indicates the completion of SPP connection establishment initialted by remote device */
    if (messageID == CLX_SPP_CONNECTION_INDICATION)
    {
        struct ClxSppConnectionIndication* arg = (struct ClxSppConnectionIndication*) params;
        
        /* Start receiving data from the remote device */
        ClxResult ret = clxSppReceive(serviceHandle, TX_RX_DATA_BLOCK_SIZE, sppInfo.sppReceive, &sppInfo.sppReceiveDataSize, FALSE);
        if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
        {
            clxConsoleUIEngineText("\nclxSppReceive command failed with the result: %s\n", clxGetErrorCodeText(ret));
        }

        /* Now that the connection with the remote SPP device has established, the local device need not be in discoverable and connectable mode */
        ret = clxGapSetConnectability(stack, FALSE, 2048, 400, FALSE);
        if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
        {
            clxConsoleUIEngineText("clxGapSetConnectability command failed with the result: %s\n", clxGetErrorCodeText(ret));
        }

        ret = clxGapSetDiscoverability(stack, FALSE, 2048, 1800, FALSE);
        if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
        {
            clxConsoleUIEngineText("clxGapSetDiscoverability command failed with the result: %s\n", clxGetErrorCodeText(ret));
        }

        clxConsoleUIEngineText ("\nSPP connected to remote device ID:(%08X%04X)\n", arg->deviceId.msb,arg->deviceId.lsb);
    }
    /* Indicates that the SPP connection with remote device is disconnected */
    else if (messageID == CLX_SPP_DISCONNECTION_INDICATION)
    {
        struct ClxSppConnectionIndication* arg = (struct ClxSppConnectionIndication*)params;
        clxConsoleUIEngineText ("\nSPP disconnected from remote device ID:(%08X%04X)\n", arg->deviceId.msb,arg->deviceId.lsb);
    }
    /**  
    These (below indications with *_COMPLETE) are command complete indications received when the corresponding API commands are called 
    in non-blocking mode. The output parameters can be accessed from argument "params".
    */
    else if (messageID == CLX_SPP_CONNECT_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_SPP_CONNECT_COMPLETE: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_SPP_DISCOVER_REMOTE_COM_PORTS_COMPLETE)
    {
        struct ClxSppDiscoverRemoteComPortsComplete * arg = (struct ClxSppDiscoverRemoteComPortsComplete*)params;
        clxConsoleUIEngineText("\nCLX_SPP_DISCOVER_REMOTE_COM_PORTS_COMPLETE: %s\n", clxGetErrorCodeText(errorCode));
        clxConsoleUIEngineText ("\nNumber Of Discovered Com Ports : %d", *(arg->numberOfDiscoveredCommPorts));
        clxConsoleUIEngineText ("\nDevice ID                      : %08X%04X", arg->comPortsList->deviceId.msb, arg->comPortsList->deviceId.lsb);
        clxConsoleUIEngineText ("\nPort Channel ID                : %d", arg->comPortsList->portChannelId);
        clxConsoleUIEngineText ("\nPortName                       : %s", arg->comPortsList->portName);
    }
    else if (messageID == CLX_SPP_DISCONNECT_COMPLETE)
    {
        if (errorCode == CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nDisconnection was successful");
        }
        else
        {
            clxConsoleUIEngineText ("\nclxSppDisconnect failed with error %d (%s)\n",
                                      errorCode,
                                      clxGetErrorCodeText(errorCode));
        }
    }
    else if (messageID == CLX_SPP_SEND_COMPLETE)
    {
        if (errorCode != CLX_SUCCESS)
        {
            clxConsoleUIEngineText ("\nSPP1 clxSppSend completed with error %d (%s)\n",
                                      errorCode,
                                      clxGetErrorCodeText(errorCode));
        }
    }
    /*
    Indication of SPP data reception
    */
    else if (messageID == CLX_SPP_RECEIVE_COMPLETE)
    {
        if (errorCode == CLX_SUCCESS )
        {
            struct ClxSppReceiveComplete* arg = (struct ClxSppReceiveComplete*)params;
            sppInfo.receivedDataLength = *arg->receivedDataLength;

            /* 
            If the received data length is > MAX_TEST_SIZE, it means that the client has sent a 
            perbuilt test block data of fixed length (Refer menu option 3), else user specified ASCII text data 
            */
            if(sppInfo.receivedDataLength > MAX_TEXT_SIZE)
            {
                /* Add the received data length until all the data sent by remote device is received */
                sppInfo.testDataCount += sppInfo.receivedDataLength;

                /* Print the total number of bytes received when all the data blocks are received */
                if(sppInfo.testDataCount == (sizeof(sppInfo.testBlock) * NUMBER_OF_DATA_BLOCKS))
                {
                    clxConsoleUIEngineText ("\nTotal Bytes Received : %d ", sppInfo.testDataCount);
                    sppInfo.testDataCount = 0;
                }
            }
            else
            {
                /* 
                Display the ASCII text sent by the remote SPP device.
                Data length will be less than MAX_TEXT_SIZE.
                */
                u1* rxPointer    = sppInfo.rxBuffer;
                memcpy(rxPointer, arg->buffer, sppInfo.receivedDataLength);
                if (sppInfo.receivedDataLength != 0)
                {
                    clxConsoleUIEngineText("%s", rxPointer);
                }

                memset(sppInfo.rxBuffer, 0, sizeof(sppInfo.rxBuffer));
            }

            if (sppInfo.receivedDataLength != 0)
            {
                /* Start receiving data from the remote client */
                ClxResult ret = clxSppReceive(serviceHandle, TX_RX_DATA_BLOCK_SIZE, sppInfo.sppReceive, &sppInfo.sppReceiveDataSize, FALSE);
                if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                {
                    clxConsoleUIEngineText("\nclxSppReceive command failed with the result: %s\n", clxGetErrorCodeText(ret));
                }
            }
        }
        else if (errorCode != CLX_ERROR_CONNECTION_NOT_EXIST )
        {
            clxConsoleUIEngineText ("\nSPP1 clxSppReceive completed with error %d (%s)\n",
                                      errorCode, 
                                      clxGetErrorCodeText(errorCode));
        }
    }
    else
    {
        return FALSE;
    }
    
    return TRUE;
}

/*******************************************************************************************************************************
*                                                   createSppHandle
*
* Creates the SPP profile with the server or client role. This will advertise the SPP functionality via the SDP server

* \param stack      - ClarinoxBlue stack
* \param server     - SPP role
*
* \return void
*
*******************************************************************************************************************************/
void createSppHandle(ClxStack stack, boolean server)
{
    /*
    Initialize the test block and calculate checksum 0..3 is used for header, 4..7 used for checksum 
    endianness must be the same for both sending and receiving devices
    */
    u4 checksum = 0;
    memset(sppInfo.testBlock, (s4)HEADER_SIGNATURE, sizeof(u4));
    for (u4 i = sizeof(u4); i < TX_RX_DATA_BLOCK_SIZE; i++)
    {
        if (i > 7)
        {
            checksum += (i & 0xFF);
        }
        sppInfo.testBlock[i] = (u1)i;
    }
    *((u4*)(&sppInfo.testBlock[4])) = checksum;

    if(!server)
    {
        if( sppInfo.spp == NULL)
        {
            /* Create SPP client handle. This handle to be passed to other SPP API commands. */
            sppInfo.spp = clxSppCreate(stack, NULL, "Port1", ClxClient, sppIndicationHandler, ClxMediumSecurity);
            if (sppInfo.spp)
            {
                sppInfo.server = FALSE;
                clxConsoleUIEngineText ("SPP Client instance created successfully\n");
            }
            else
            {
                clxConsoleUIEngineText ("SPP Client instance creation failed\n");
                CLX_ASSERT((NULL != sppInfo.spp));
            }
        }
    }
    else
    {
        if( sppInfo.spp == NULL)
        {
            /* Create SPP server handle. This handle to be passed to other SPP API commands. */
            sppInfo.spp = clxSppCreate(stack, NULL, "Port1", ClxServer, sppIndicationHandler, ClxMediumSecurity);
            if (sppInfo.spp)
            {
                sppInfo.server = TRUE;
                clxConsoleUIEngineText ("SPP Server instance created successfully\n");
            }
            else
            {
                clxConsoleUIEngineText ("SPP Server instance creation failed\n");
                CLX_ASSERT((NULL != sppInfo.spp));
            }
        }
    }
}

/*******************************************************************************************************************************
*                                                    deleteSppHandle
*
* Deletes the SPP profile handle when there is no use for this profile.
*
*******************************************************************************************************************************/
void deleteSppHandle(void)
{
    if( sppInfo.spp != NULL)
    {
        /* Close the SPP handle which does the windup procedures and releases all associated resources in stack  */
        clxCloseHandle(sppInfo.spp);
        sppInfo.spp = NULL;
    }
}

/*******************************************************************************************************************************
*                                                    sppMenuFunction
*
* Provide the SPP UI menu.

* \param stack      - ClarinoxBlue stack
* \param deviceId   - Device ID of the remote device that is to be connected
*
*******************************************************************************************************************************/
void sppMenuFunction(ClxStack stack, ClxDeviceId id)
{
    ClxError ret;

    const s1* menu =    "Connect to SPP\0"
                        "Wait for incoming SPP Connect request\0"
                        "Send ASCII Text\0"
                        "Send Prebuilt Test Data\0"
                        "Disconnect from SPP\0"
                        "Return to previous menu";

    while(TRUE)
    {
        /*
        Display the secondary SPP menu and handle user selection
        */
        u4 index = clxConsoleUIEngineShowMenu("Enter your selection:", menu, ClxSppMenu_Total - 1);
        switch(index)
        {
            case ClxSppMenu_Connect:
            {
                /* 
                Create the SPP profile as client role. 
                This is because it is usually the client role which searches for the server and connects to.
                */
                createSppHandle(stack, FALSE);

                /*
                Assuming maximum 12 SPP ports on the remote device
                */
                struct ClxRemoteComPort ports[12];
                u4 numberOfDiscoveredPorts = 0;
                
                if (!sppInfo.server)
                {
                    clxConsoleUIEngineText ("Discovering COM ports on the remote device . . .\n");
                    
                    /*
                    Discover remote comm ports via SDP operation, if a suitable SPP port is found then 
                    connect to that port by using the parameters retrieved via SDP operation
                    This is only applicable to client side
                    */
                    ret = clxSppDiscoverRemoteComPorts(sppInfo.spp,
                                                       NULL,
                                                       id,
                                                       sizeof(ports)/sizeof(struct ClxRemoteComPort),
                                                       ports,
                                                       &numberOfDiscoveredPorts,
                                                       TRUE);

                    if (ret != CLX_SUCCESS)
                    {
                        clxConsoleUIEngineText ("\nError : clxSppDiscoverRemoteComPorts failed with error: %d (%s)\n", ret, clxGetErrorCodeText(ret));
                    }
                
                    if (numberOfDiscoveredPorts)
                    {
                        clxConsoleUIEngineText ("Connecting to COM port \"%s\" on the remote device . . .\n", ports[0].portName);

                        /* Connects to the first available port */
                        ret = clxSppConnect(sppInfo.spp, id, ports[0].portChannelId, TRUE);
                        if (ret != CLX_SUCCESS)
                        {
                            clxConsoleUIEngineText("SPP connection failed\n");
                            clxConsoleUIEngineText ("\nError : clxSppConnect failed with error: %d (%s)\n", ret, clxGetErrorCodeText(ret));
                        }
                        else
                        {
                            /*
                            Start the asynchronous receive
                            */
                            ret = clxGapSetConnectability(stack, FALSE, 2048, 400, FALSE);
                            if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                            {
                                clxConsoleUIEngineText("\nclxGapSetConnectability command failed with the result: %s\n", clxGetErrorCodeText(ret));
                            }

                            ret = clxGapSetDiscoverability(stack, FALSE, 2048, 1800, FALSE);
                            if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                            {
                                clxConsoleUIEngineText("\nclxGapSetDiscoverability command failed with the result: %s\n", clxGetErrorCodeText(ret));
                            }

                            /* Wait for an incoming data which could be received from the remote device at any point of time, we call the API beforehand in order to receive it */
                            ret = clxSppReceive(sppInfo.spp, TX_RX_DATA_BLOCK_SIZE, sppInfo.sppReceive, &sppInfo.sppReceiveDataSize, FALSE);
                            if (ret != CLX_SUCCESS && ret != CLX_ERROR_COMPLETION_PENDING)
                            {
                                clxConsoleUIEngineText("SPP buffer receive failed\n");
                                clxConsoleUIEngineText ("\nError : clxSppReceive failed with error: %d (%s)\n", ret, clxGetErrorCodeText(ret));
                            }
                        }
                    }
                    else
                    {
                        clxConsoleUIEngineText ("No SPP COM ports discovered\n");
                    }
                }
                else
                {
                    clxConsoleUIEngineText ("Only clients can connect to server devices and not the other way.\n");

                    /* 
                    Do nothing if client
                    */
                    ret = CLX_SUCCESS;
                }
            }
            break;

            case ClxSppMenu_WaitForConnection:
            {
                /* 
                Usually a server role of SPP would wait for incoming connection request from client SPP device.
                So create the SPP profile with the server role.
                */
                createSppHandle(stack, TRUE);

                /* 
                Makes the local device discoverable. 
                The purpose is to respond to a device that makes a general inquiry 
                */
                ret = clxGapSetDiscoverability(stack, TRUE, 2048, 1800, TRUE);
                if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                {
                    clxConsoleUIEngineText("\nclxGapSetDiscoverability command failed with the result: %s\n", clxGetErrorCodeText(ret));
                }

                /* Makes the local device connectable mode for the remote device to send connection request */
                ret = clxGapSetConnectability(stack, TRUE, 2048, 400, TRUE);
                if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                {
                    clxConsoleUIEngineText("\nclxGapSetConnectability command failed with the result: %s\n", clxGetErrorCodeText(ret));
                }

                clxConsoleUIEngineText("Device put in Discoverable mode.\n");
                break;
            }

            case ClxSppMenu_SendAsciiText:
            {
                /* Get user input to send over SPP */
                s1 message[MAX_MESSAGE_SIZE+1] = {};
                clxSprintf(message, "Enter text to send (maximum of %u characters): ", MAX_TEXT_SIZE);
                clxConsoleUIEngineInputBox (message, sppInfo.in, MAX_TEXT_SIZE);

                /* Append CR LF to the string as some receiving applications would expect at the end */
                u4 msgSize = strlen(sppInfo.in);
                if(msgSize > MAX_TEXT_SIZE - 4)
                {
                    msgSize = MAX_TEXT_SIZE - 4;
                }
                sppInfo.in[msgSize++] = 0x0A;
                sppInfo.in[msgSize++] = 0x0D;
                sppInfo.in[msgSize]   = 0x00;
                /* Sends the user entered data to the remote SPP device */
                ret = clxSppSend( sppInfo.spp, (u1*)sppInfo.in, strlen(sppInfo.in), TRUE );
                if (ret != CLX_SUCCESS)
                {
                    clxConsoleUIEngineText ("\nError : clxSppSend failed with error: %d (%s)\n", ret, clxGetErrorCodeText(ret));
                }
            }
            break;

            case ClxSppMenu_SendPrebuiltTestData:
            {
                /*
                This option is used to test the speed of data transfer between the SPP devices. 
                Once the data transfer is completed, the transfer duration will be displayed in milliseconds and 
                the transfer speed will be displayed in bytes/sec and bits/sec
                */
                for (u4 i = 0; i < sizeof(sppInfo.testBlock); i++)
                {
                    sppInfo.testBlock[i] = (u1)(i+33);
                }
                
                u4 start = clxTickTime();
                
                for (u4 i = 0; i < NUMBER_OF_DATA_BLOCKS; i++)
                {
                    ret = clxSppSend(sppInfo.spp, sppInfo.testBlock, sizeof(sppInfo.testBlock), TRUE);
                    if (ret != CLX_SUCCESS)
                    {
                        clxConsoleUIEngineText ("\nError : clxSppSend failed with error: %d (%s)\n", ret, clxGetErrorCodeText(ret));
                        break;
                    }
                }
                
                u4 end = clxTickTime();
                clxConsoleUIEngineText ("\nSpeed = %u Bytes/Sec", NUMBER_OF_DATA_BLOCKS *sizeof(sppInfo.testBlock) / (end - start) * 1000);
            }
            break;
            
            case ClxSppMenu_Disconnect:
            {
                /* Disconnects from the remote SPP device */
                ret = clxSppDisconnect(sppInfo.spp, TRUE);
                if (ret != CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("Disconnection failed\n");
                    clxConsoleUIEngineText ("\nError : clxSppDisconnect failed with error: %d (%s)\n", ret, clxGetErrorCodeText(ret));
                }
            }
            break;

            case ClxSppMenu_ReturnToPreviousMenu:
            {
                return;
            }
            break;

            default:
            {

            }
            break;
        }
    }
}

