#ifndef ClarinoxBlueUartDriverBsp_h
#define ClarinoxBlueUartDriverBsp_h

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                ClarinoxBlue.Driver.Bsp.h
* Description         ClarinoxBlue Driver BSP interface
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


/** 
Maximum SCO packet size, used by the stack
*/
#define CLX_BLUE_MAX_RX_SCO_PACKET_SIZE               (CLX_SCO_HDR_LEN + 255)

/* The flags in the HCI header */
#define CLX_ACL_FRAME_START_NON_FLUSHABLE             0x00
#define CLX_ACL_FRAME_START                           0x02
#define CLX_ACL_FRAME_CONT                            0x01
#define CLX_ACL_FRAME_FULL_PACKET_FLUSHABLE           0x03   /* Added in Bluetooth V4.0 specification */

#define CLX_HCI_HDR_LEN     1
#define CLX_ACL_HDR_LEN     4
#define CLX_SCO_HDR_LEN     3
#define CLX_CMD_HDR_LEN     3
#define CLX_EVENT_HDR_LEN   2
#define CLX_ISO_HDR_LEN     4


#ifdef __cplusplus
extern "C" {
#endif

typedef enum ClxBluetoothPacketTypeEnum
{
    ClxBluetoothPacketType_hciCommand = 1,
    ClxBluetoothPacketType_hciACL = 2,
    ClxBluetoothPacketType_hciSCO = 3,
    ClxBluetoothPacketType_hciEvent = 4,
    ClxBluetoothPacketType_hciISO = 5,
} ClxBluetoothPacketType;


typedef ClxUartBspInterface ClxVendorSpecificBtH4BspInterface;


/**
SCO Rx Buffer (defined in ClarinoxBlueScoInterface.h)
*/
struct ClxRxScoBuffer;


/** 
ACL RX Buffer
*/
struct ClxRxAclBuffer
{
    u1* address;                  /*!< buffer containing data received from an ACL channel. The data can be an entire or a fragment of a higher layer (L2CAP) message. 
                                       The data excludes 1-byte packet type header and any HCI/ACL headers */

    u2  bufferSize;               /*!< buffer size */

    u2  connectionHandle;         /*!< the ACL connection handle. SHALL be set to the same value in all fragments of a single Higher layer (L2CAP) packet */

    u1  pbFlag;                   /*!< The Packet Boundary flag */
    u1  bcFlag;                   /*!< The BroadCast flag */

    u2  length;                   /*!< Length of data stored in this buffer */
};

/**
ISO Rx Buffer (defined in Iso.Ble.Interface.h)
*/
struct ClxBleIsoRxBuffer;

/**
ClarinoxBlue driver interface. An implementation will interface ClarinoxBlue stack to the Bluetooth controller hardware.

NOTE : This is an optional BSP interface. If an implementation does not exist as part of the BSP, an internal implementation
will be used. The internal implementation may employ other BSP interfaces (e.g. UART BSP interface) to communicate with the Bluetooth
controller hardware.

If an implementation exists, it will overwrite any internal implementation. In this case, the variable #clarinoxBlueDriverInterface shall be set to the address of the implementation instance.

NOTE : An implementation shall be able to receive incoming data, find the packet boundaries, and process HCI events, and incoming ACL and SCO packets. In other words, an implementation shall
have a basic knowledge of HCI packets and their structure to be able to process the packets.
*/
struct ClarinoxBlueDriverInterface
{
    /**
    Called by ClarinoxBlue to initialize the driver interface. It shall initialize any local resources required.

	IMPORTANT : When this method returns, this interface is initialized successfully, but not started yet.
	Therefore, driver API functions are not allowed to be called until #start() is called. 

    This method is called during the initialization of ClarinoxBlue. If this method returns any value other than CLX_SUCCESS, the initialization of ClarinoxBlue will fail.
    */
	void (*init) ();

	/**
	Called by ClarinoxBlue to start the driver interface. An implementation shall initialize the Bluetooth controller hardware.
	If an implementation returns CLX_SUCCESS, then the Bluetooth controller hardware is assumed to be up and running, and the interface has started 
	listening for incoming data from the controller hardware.
	Also, when this method returns, the implementation shall be able send packets to the controller hardware (as a result of a call to #sendData method).

	When this function is called, all driver API functions are permitted to be called by this driver interface.

	This method is called during the initialization of ClarinoxBlue. If this method returns any value other than CLX_SUCCESS, the initialization of ClarinoxBlue will fail.

	NOTE : When this function is called, the driver has NOT been locked (refer to #lock method). If required, this shall be done explicitly by the implementation.

	IMPORTANT : The RX path of the interface is assumed to be asynchronous. An implementation shall wait for incoming data and inform the stack of incoming packets
	only when there are completely received. This may be done from the context of a hardware interrupt handlers, a software interrupt handler or a thread which has been started
	by the interface.

	This function is called in the context of ClarinoxBlue stack thread.

	\param[ in ] configList The list of configuration parameters. This is the same list which has been passed to clxInitClarinoxBlue() function. The list may contain configuration parameters
	related to the driver interface (e.g. UART port, baud rate, ...). An implementation may define its own set of configuration parameters.

	\return CLX_SUCCESS if the interface and the Bluetooth controller hardware have both been started successfully.
	Any other value indicates an error. In this case, the method #destroy will be called to destroy the interface object.
	*/
	ClxResult (*start) (_in_ const ClxConfigList* configList);

	/**
	Called by ClarinoxBlue to stop the driver interface. An implementation shall stop listening to incoming data (and cancel any ongoing procedures). When this method
	returns, the interface is NOT allowed to call any driver API functions any more.

	NOTE : If the interface has started a thread to listen for incoming data, it shall stop the thread before this method returns.

	NOTE : When this function is called, the driver has NOT been locked (refer to #lock method). If required, this shall be done explicitly by the implementation.
	*/
	void (*stop) ();

    /**
    Called by ClarinoxBlue to destroy the driver interface. An implementation shall terminate and destroy any software resources owned by the interface.

    This method is called during termination of ClarinoxBlue stack. This method cannot fail.

    NOTE : When this function is called, the driver has NOT been locked (refer to #lock method). If required, this shall be done explicitly by the implementation.
    */
	void (*destroy) ();

    /**
    Called by ClarinoxBlue to send a packet to the controller hardware. The packet may be a HCI command, and ACL packet or a SCO packet. The first byte of data indicates the type of the packet.
    Please refer to Bluetooth spec for more information.

    NOTE : An implementation shall be synchronous (blocking). In other words, this function shall NOT return until the packet transmission is complete, either in error or with success.

    NOTE : This function is called in the context of ClarinoxBlue stack thread. Therefore, an implementation shall NOT block the execution of the stack for a long time. Otherwise, the stack will become
    unresponsive.

    NOTE : When this function is called, the driver has NOT been locked (refer to #lock method). If required, this shall be done explicitly by the implementation.

    \param[ in ] data The packet to send to the controller, as a contiguous buffer in the memory. The memory for this buffer is guaranteed to have been allocated by a call to #allocateMem method.
    The buffer contains the 1-byte packet type header in the beginning.
    \param[ in ] dataLength Total length of the packet. This includes the 1-byte packet type header as well.
    */
	void (*sendData) (_in_ const u1* data, _in_ ClxSize dataLength);


    /**
    Called by ClarinoxBlue to set the total bandwidth for all SCO connections currently available.

    An implementation is optional. An implementation is only necessary if SCO packets are passed via HCI,
    and the driver needs to know the total bandwidth in order to adjust its internal members (e.g. USB).

    NOTE : This function is called in the context of ClarinoxBlue stack thread. Therefore, an implementation shall NOT block the execution of the stack for a long time. Otherwise, the stack will become
    unresponsive.

    NOTE : When this function is called, the driver has NOT been locked (refer to #lock method). If required, this shall be done explicitly by the implementation.

    \param[ in ] bandwidth The total bandwidth of all currently connected SCO links, in bytes per seconds. If all SCO links have been disconnected,
    					   this value shall be set to 0.

    \return CLX_SUCCESS if the operation has been successful. Any other value indicates an error.
    */
	ClxResult (*setTotalScoBandwidth) (_in_ u4 bandwidth);


	/**
    The Soft IRQ handler. Called by ClarinoxBlue in the context of the stack thread if the Soft IRQ has been scheduled by previous calls to #clxBlueDriverScheduleSoftIrqHandler().
    Refer to the documentation of #clxBlueDriverScheduleSoftIrqHandler API function for more information.

    NOTE : An implementation of this method is MANDATORY if #clxBlueDriverScheduleSoftIrqHandler() is called. Otherwise, an implementation is optional.
    */
	void (*softIrqHandler) ();


	/**
    Called by ClarinoxBlue to lock access to the driver. When the driver is locked, it is guaranteed that only one context will be able to access ClarinoxBlue IO buffers. 
    
    This function is called in the context of ClarinoxBlue stack thread.

    If an implementation might call any of driver API functions from the context of a thread, it may acquire a mutex to lock access. 
    If an implementation might call any of driver API functions from a CPU Interrupt Service Routine (ISR), this function shall disable that interrupt.
    */
	void (*lock) ();

    /**
    Called by ClarinoxBlue to unlock access to the driver. This is called only after #lock has previously been called.

    This function is called in the context of ClarinoxBlue stack thread.

    If an implementation might call any of driver API functions from the context of a thread, it may release a mutex to unlock access. 
    If an implementation might call any of driver API functions from a CPU Interrupt Service Routine (ISR), this function shall enable that interrupt.
    */
	void (*unlock) ();

    /**
    Called by ClarinoxBlue if some memory needs to be allocated. This memory is used for both TX and RX buffers.

	NOTE : Some platforms require TX/RX buffers to have special properties such as DMA-able or non-cache-able. Since all TX/RX buffers are allocated by a call
	to this method, an implementation may need to take these properties into consideration.

	\param[ in ] moduleID The numeric ID of the module (file) inside ClarinoxBlue which has called this method. Used for debugging purposes.
	\param[ in ] line The line of the code in the module which this method has been called. Used for debugging purposes.
	\param[ in ] size Size, in bytes, of the memory buffer to be allocated. The returned buffer shall be at least of this size.

	\return A pointer to the allocated buffer. This pointer will be passed to #freeMem later on to be freed.
	If a free buffer of requested size is not available, the return value shall be NULL.
    */
	void* (*allocateMem) (const ClxPackage* package, u2 moduleID, u4 line, u4 size);

    /**
    Called by ClarinoxBlue if allocated memory needs to be freed.

	\param[ in ] ptr Pointer to the buffer to be freed. This buffer was previously allocated by a call to #allocateMem.
    */
	void(*freeMem) (void* ptr);
};

/**
Called by the driver interface to queue an ACL buffer containing a single received ACL packet. This API function may be called in the context of a CPU Interrupt Service Routine (ISR).

NOTE : This method does NOT send the buffer to ClarinoxBlue stack. It only queues them internally so they can be flushed later on. In order to flush all queued ACL buffers
to ClarinoxBlue stack, #clxBlueDriverFlushRxAclBuffers() shall be called. 

IMPORTANT : In order to avoid synchronization loss, received ACL packets SHALL be queued in the same order that they have been received from the controller hardware.

NOTE : If a single ClarinoxBlue-allocated RX ACL buffer is not large enough to store a single ACL packet. The driver interface implementation SHALL perform fragmentation by storing the ACL
packet into two or more RX ACL buffers. The following rule shall apply:

- The packet boundary flag (ClxRxAclBuffer.pbFlag) of the first RX ACL buffer object shall be set to the packet boundary flag of the ACL packet (refer to Bluetooth specification for more information).
- The packet boundary flag (ClxRxAclBuffer.pbFlag) of the rest of RX ACL buffer objects of this ACL packet SHALL be set to 2 (Continuing packet). 
- The fragments of the same ACL packet shall be queued in the same order as the data has been received from the controller.

\param[ in ] buffer Pointer to a ClarinoxBlue-allocated object of type #ClxRxAclBuffer which contains the received ACL packet. This buffer has been obtained by a previous call to #clxBlueDriverGetFreeRxAclBuffer()
function.
*/
extern void clxBlueDriverQueueRxAclBuffer(_in_ struct ClxRxAclBuffer* buffer);

/**
Called by the driver interface to flush all queued RX ACL packets to ClarinoxBlue stack. This API function may be called in the context of a CPU Interrupt Service Routine (ISR).

The queued buffers will be released by ClarinoxBlue stack when they are processed.

NOTE : lock() and unlock() methods of the interface are internally called by this function to protect access to the RX buffers.

NOTE : This function shall be called frequently in order to avoid excessive latencies.

\param[ in ] isrContext TRUE if this function is being called in the context of a CPU interrupt service routine. FALSE otherwise.
*/
extern void clxBlueDriverFlushRxAclBuffers(boolean isrContext);

/**
Called by the driver interface to submit a received SCO buffer. The buffer has been obtained by a previous call to #clxBlueReleaseRxScoBuffer() API function.

Please refer to documentation of #ClarinoxBlueScoInterface interface for more information.

\param[ in ] buffer A ClarinoxBlue-allocated object of type ClxRxScoBuffer which contains one single RX SCO packet.
\param[ in ] isrContext TRUE if this function is being called in the context of a CPU interrupt service routine. FALSE otherwise.
*/
extern void clxBlueDriverSubmitRxScoBuffer(_in_ struct ClxRxScoBuffer* buffer, boolean isrContext);

/**
Called by the driver interface to get a contiguous buffer from the internal HCI event FIFO to store the next received HCI event. The interface needs to write the received HCI event into the provided buffer, and then call
#clxBlueDriverSubmitRxHciEvent to submit the complete HCI event packet.

IMPORTANT : ClarinoxBlue uses different FIFOs for different types of HCI events. Therefore, it is very important to pass the correct event type (which is the first byte of the HCI event packet) as the first argument
            of this type. Otherwise, the behaviour will be undefined.

NOTE : This function does NOT allocate any buffer (e.g. does not advance the FIFO write index). The buffer will be allocated only when #clxBlueDriverSubmitRxHciEvent is called afterwards.

NOTE : lock() and unlock() methods of the interface are internally called by this function to protect access to the internal HCI event FIFO.

\param[ in ] hciEventType The type of received event (the very first byte in the standard HCI event header). ClariboxBlue may return a buffer form a HCI event FIFO specific to this type.
\param[ in ] bufferSize The minimum buffer size required to contain the entire HCI event (including the standard HCI event header).

\return A contiguous buffer from the internal HCI event FIFO to store the next received HCI event. If a buffer of the requested size does not exist, a BLACKBOX will happen. 
*/
extern u1* clxBlueDriverGetRxHciEventBuffer(_in_ u1 hciEventType, _in_ u2 bufferSize);

/**
Called by the driver interface to submit the received HCI event. This API function may be called in the context of a CPU Interrupt Service Routine (ISR).

NOTE : The provided HCI event packet shall contain the standard HCI event header. The type and the length of the HCI event will be extracted from the header.

NOTE : lock() and unlock() methods of the interface are internally called by this function to protect access to the internal HCI event FIFO.

\param[ in ] buffer The buffer containing the HCI event. This MUST be the very same buffer returned by the last call to #clxBlueDriverGetRxHciEventBuffer.
                    The very first byte of the HCI event packet MUST be the same as "hciEventType" argument passed to the last call to #clxBlueDriverGetRxHciEventBuffer.

\param[ in ] isrContext TRUE if this function is being called in the context of a CPU interrupt service routine. FALSE otherwise.
*/
extern void clxBlueDriverSubmitRxHciEvent(_in_ u1* buffer, boolean isrContext);

/**
Called by the driver interface to obtain a free RX ACL buffer. The buffer is allocated by ClarinoxBlue stack and may be used by the driver to store incoming ACL data only.
This API function may be called in the context of an interrupt handler.

NOTE : lock() and unlock() methods of the interface are internally called by this function to protect access to the RX buffers.

If there is no free RX ACL buffer, the return value will be NULL.

After storing an incoming ACL packet, or a fragment of it (please refer to #clxBlueDriverQueueRxAclBuffer() documentation), the API function #clxBlueDriverQueueRxAclBuffer() shall be
called to hand the buffer back to ClarinoxBlue stack.

\return A pointer to a free RX ACL buffer. NULL if there is no free RX ACL buffer available at this moment.
*/
extern struct ClxRxAclBuffer* clxBlueDriverGetFreeRxAclBuffer ();

/**
Called by the driver interface to obtain a free RX SCO buffer. The buffer is allocated by ClarinoxBlue stack and may be used by the driver to store incoming SCO data only.

Please refer to documentation of #ClarinoxBlueScoInterface interface for more information.

\param[ in ] bufferSize The size of buffer to be allocated for the SCO RX packet. If there is not enough space in the SCO interface private heap, this function will return NULL.

\return a pointer to a ClarinoxBlue-allocated RX SCO buffer. will be NULL if there is no free RX SCO buffer of the requested size available at this moment. 
*/
extern struct ClxRxScoBuffer* clxBlueDriverGetFreeRxScoBuffer (u1 bufferSize);

/**
Called by the driver interface to obtain a free RX ISO buffer. The buffer is allocated by ClarinoxBlue stack and may be used by the driver to store incoming ISO data only.

Please refer to documentation of #ClxBleIsoInterface interface for more information.

\param[ in ] bufferSize The size of buffer to be allocated for the ISO RX packet. If there is not enough space in the ISO interface private heap, this function will return NULL.

\return a pointer to a ClarinoxBlue-allocated RX ISO buffer. will be NULL if there is no free RX ISO buffer of the requested size available at this moment. 
*/
extern struct ClxBleIsoRxBuffer* clxBlueDriverGetFreeRxIsoBuffer (u2 bufferSize);

/**
Called by the driver interface to schedule and run the interface Soft IRQ handler function (ClarinoxBlueDriverInterface.softIrqHandler) in the context of ClarinoxBlue stack. 
This may be used by the interface implementation to move some part or all of the processing from the hardware ISR to the context of the ClarinoxBlue thread.

This API function may be called in the context of a CPU Interrupt Service Routine (ISR).

IMPORTANT : If this function is used, an implementation for ClarinoxBlueDriverInterface.softIrqHandler is mandatory.

ClarinoxBlue maintains a SoftIRQ counter for the driver. Every time this functions is called, the counter is incremented. Evey time the Soft IRQ handler function is called, the counter is decremented.
The stack will keep scheduling the Soft IRQ handler until the counter reaches zero.

NOTE : All the ClarinoxBlue driver APIs (defined in ClarinoxBlue.Driver.Bsp.h), and ClarinoxBlue SCO interface APIs (defined in ClarinoxBlueScoInterface.h) may be called from within the IRQ handler function.
NOTE : The function clxBlueDriverScheduleSoftIrqHandler() may be called from within the IRQ handler function.

\param[ in ] isrContext TRUE if this function is being called in the context of a CPU interrupt service routine. FALSE otherwise.
*/
extern void clxBlueDriverScheduleSoftIrqHandler (boolean isrContext);


/**
A pointer to the driver interface implementation instance.
*/
extern struct ClarinoxBlueDriverInterface* clarinoxBlueDriverInterface;

/**
A pointer to the Vendor specific Bluetooth H4 BSP interface.
*/
extern ClxVendorSpecificBtH4BspInterface* clxVendorSpecificBtH4BspInterface;


#ifdef __cplusplus
}
#endif


#endif // ClarinoxBlueUartDriverBsp_h

