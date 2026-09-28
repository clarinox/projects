/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                ClxBlueConfig.c
* Description         Bluetooth stack configuration parameters are set here
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


/**
ClarinoxBlue configuration parameters configure the ClarinoxBlue stack to suit the user application.
Defines the structure of ClarinoxBlue config parameters who's values are assigned in the function initializeClarinoxBlueBspConfigParameters()
These parameters must be set during initialization of stack.
*/  
typedef struct ClarinoxBlueParametersStruct
{
    ClxConfigList       parentList;   /* SHALL be the very first member of the structure */

    /* Add any BSP-specific parameter in here: */
    ClxConfigString    transportType;
    ClxConfigString    comPortName;
    ClxConfigInteger   comPortSpeed;
    
    ClxConfigInteger   maxNoOfPairedDevices;
    
    ClxConfigInteger   l2capOutgoingBufferSize;
    ClxConfigInteger   l2capIncomingBufferSize;
    ClxConfigInteger   l2capSignalChannelInputContainerSize;
    ClxConfigInteger   l2capSignalChannelOutputContainerSize;
    ClxConfigInteger   l2capMaxNumberOfStackWideL2capConnections;
    ClxConfigInteger   l2capSignalChannelMtu;
    
    ClxConfigInteger   hciCommandBufferSize;
    ClxConfigInteger   hciEventBufferSize;
    ClxConfigInteger   hciNumberOfRxAclBuffers;
    ClxConfigInteger   hciRxAclSingleBufferSize;
    ClxConfigInteger   eventBufferSize;
    
    ClxConfigInteger   rfcommIncomingQueueSize;
    ClxConfigInteger   rfcommOutgoingQueueSize;
    ClxConfigInteger   rfcommMaxNumberOfL2capConnections;
    ClxConfigInteger   rfcommIncomingMtu;
    ClxConfigInteger   rfcommMaxOutgoingDataSize;
    ClxConfigInteger   rfcommMaxRemoteCredits;
    
    ClxConfigInteger   sdpMaxNumberOfL2capConnections;
    ClxConfigInteger   sdpIncomingMtu;
    
#if defined(CLX_BLE_CENTRAL) || defined(CLX_BLE_PERIPHERAL)
    ClxConfigInteger   attChannelInputContainerSize;
    ClxConfigInteger   attChannelOutputContainerSize;
    ClxConfigInteger   attChannelMaxMtu;
    ClxConfigInteger   attChannelQueuedWritesContainerSize;
    ClxConfigInteger   bleMaxNoOfPairedDevices;
    ClxConfigInteger   isoBufferHeapSize;
    
    /**
    Configuration parameter for storing local supported keys. Note: Disabling these configuration, the stack does not
    store the keys for reconnection
    */
    ClxConfigData      bleSmpEr;
    ClxConfigData      bleSmpIr;
#endif  /* #if defined(CLX_BLE_CENTRAL) || defined(CLX_BLE_PERIPHERAL) */
}ClarinoxBlueParameters;

/* Local supported keys: LTK, IRK */
const u1 bleSmpEr[16] = {0x8a, 0x5a, 0x02, 0x12, 0x61, 0xaa, 0x11, 0xa4, 0xe3, 0xb9, 0x3b, 0xa6, 0xba, 0xb4, 0xfc, 0xbb};
const u1 bleSmpIr[16] = {0xaa, 0x3e, 0xd6, 0x32, 0x88, 0xaa, 0xb5, 0x32, 0xc6, 0x6f, 0x00, 0x7a, 0xcc, 0x10, 0x5c, 0x87};

/**
User defined values for ClarinoxBlue configuration parameters. The default values of these parameters are defined in the API file ClarinoxBlueConst.h
Users can customize these values based on the underlying platform. Clarinox heap size is determined based on the buffer sizes defined here. 
*/
ClxConfigList* initializeClarinoxBlueBspConfigParameters()
{
    ClarinoxBlueParameters* configParameters = (ClarinoxBlueParameters*)clxAppPoolsetAlloc ( 0, __LINE__, sizeof(ClarinoxBlueParameters) );

    /*
    Initialize the parent list object (configParameters->parentList) which is to hold all other configuration objects (SHALL be initialized first):
    */
    clxConfigInitParamsList    (&configParameters->parentList, NULL, NULL);
    clxConfigInitStringParam   (&configParameters->transportType,                              "TransportType",                                "TT_UART_H4",               &configParameters->parentList);
    clxConfigInitStringParam   (&configParameters->comPortName,                                "ComPortName",                                  "BLUETOOTH_PORT",     &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->comPortSpeed,                               "ComPortSpeed",                                 115200,    &configParameters->parentList);


    clxConfigInitIntegerParam  (&configParameters->maxNoOfPairedDevices,                       "MaxNoOfPairedDevices",                         4,                          &configParameters->parentList);
    
    clxConfigInitIntegerParam  (&configParameters->l2capOutgoingBufferSize,                    "L2cap.OutgoingBufferSize",                     1010,                       &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->l2capIncomingBufferSize,                    "L2cap.IncomingBufferSize",                     1010,                       &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->l2capSignalChannelInputContainerSize,       "L2cap.SignalChannelInputContainerSize",        256,                        &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->l2capSignalChannelOutputContainerSize,      "L2cap.SignalChannelOutputContainerSize",       256,                        &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->l2capMaxNumberOfStackWideL2capConnections,  "L2cap.MaxNumberOfStackWideL2capConnections",   8,                          &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->l2capSignalChannelMtu,                      "L2cap.SignalChannelMtu",                       190,                        &configParameters->parentList);

    clxConfigInitIntegerParam  (&configParameters->hciRxAclSingleBufferSize,	               "Hci.RxAclSingleBufferSize",                    680,                        &configParameters->parentList);
    /* We need lots of hciNumberOfRxAclBuffers for A2DP - 40 for release, 60 for debug mode */
    clxConfigInitIntegerParam  (&configParameters->hciNumberOfRxAclBuffers,                    "Hci.NumberOfRxAclBuffers",                     80,                         &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->eventBufferSize,                            "Hci.EventBufferSize",                          6000,                         &configParameters->parentList);


    
    clxConfigInitIntegerParam  (&configParameters->rfcommIncomingQueueSize,                    "Rfcomm.IncomingQueueSize",                     4096,                       &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->rfcommOutgoingQueueSize,                    "Rfcomm.OutgoingQueueSize",                     4096,                       &configParameters->parentList);

    clxConfigInitIntegerParam  (&configParameters->rfcommMaxNumberOfL2capConnections,          "Rfcomm.MaxNumberOfL2capConnections",           2,                          &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->rfcommIncomingMtu,                          "Rfcomm.IncomingMtu",                           520,                        &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->rfcommMaxOutgoingDataSize,                  "Rfcomm.MaxOutgoingDataSize",                   520,                        &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->rfcommMaxRemoteCredits,                     "Rfcomm.RfcommMaxRemoteCredit",                 4,                          &configParameters->parentList);

    clxConfigInitIntegerParam  (&configParameters->sdpMaxNumberOfL2capConnections,             "Sdp.MaxNumberOfL2capConnections",              4,                          &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->sdpIncomingMtu,                             "Sdp.IncomingMtu",                              48,                         &configParameters->parentList);

#if defined(CLX_BLE_CENTRAL) || defined(CLX_BLE_PERIPHERAL)
    /*
    Initialize the parent list object (configParameters->parentList) which is to hold all other configuration objects (SHALL be initialized first):
    */
    
    /* For BLE, the maximum number of simultaneous connections depend on the chip. WL8 supports the maximum of 10 simultaneous connections */
    clxConfigInitIntegerParam  (&configParameters->bleMaxNoOfPairedDevices,                    "Ble.MaxNoOfPairedDevices",                     2,                  &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->attChannelInputContainerSize,               "Ble.AttChannel.InputContainerSize",            512,                &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->attChannelOutputContainerSize,              "Ble.AttChannel.OutputContainerSize",           512,                &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->attChannelMaxMtu,                           "Ble.AttChannel.MaxMtu",                        300,                &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->attChannelQueuedWritesContainerSize,        "Ble.AttChannel.QueuedWritesContainerSize",     1024,               &configParameters->parentList);
    clxConfigInitIntegerParam  (&configParameters->isoBufferHeapSize,                          "Ble.IsoBufferHeapSize",                        20480,              &configParameters->parentList);

    /* Configuration parameter for storing Long Term Key */
    clxConfigInitDataParam     (&configParameters->bleSmpEr,                                   "Ble.Smp.ER",    bleSmpEr,                      sizeof(bleSmpEr),   &configParameters->parentList);

    /* Configuration parameter for storing Identity Resolving Key */
    clxConfigInitDataParam     (&configParameters->bleSmpIr,                                   "Ble.Smp.IR",    bleSmpIr,                      sizeof(bleSmpIr),   &configParameters->parentList);
#endif /* #if defined(CLX_BLE_CENTRAL) || defined(CLX_BLE_PERIPHERAL) */

    return &configParameters->parentList;
}

/**
Release the memory allocated to store the ClarinoxBlue config parameters
*/
void releaseClarinoxBlueBspConfigParameters(ClxConfigList* configParameters)
{
    clxPoolsetFree((ClarinoxBlueParameters*)configParameters);
}

