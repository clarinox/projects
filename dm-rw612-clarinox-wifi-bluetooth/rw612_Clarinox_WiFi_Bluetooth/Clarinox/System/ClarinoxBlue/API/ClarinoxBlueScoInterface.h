#ifndef _ClarinoxBlueScoInterface_h_
#define _ClarinoxBlueScoInterface_h_

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                ClarinoxBlueScoInterface.h
* Description         ClarinoxBlue Bluetooth Protocol SCO Interface
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#define ClxRxScoStatusFlag_Valid                    0x00
#define ClxRxScoStatusFlag_PossiblyInvalid          0x01
#define ClxRxScoStatusFlag_Lost                     0x02
#define ClxRxScoStatusFlag_PartiallyLost            0x03


#ifdef __cplusplus
extern "C" {
#endif

/** 
SCO TX Buffer is filled by the interface implementation  and used by stack
*/
struct ClxTxScoBuffer
{
    struct ClxCQueueable        queueable;      /*!< Internal use */

    u1*                         buffer;         /*!< buffer containing data to be sent to a SCO channel */

    u2                          scoHandle;      /*!< SCO connection handle */
    u1                          bufferSize;     /*!< Buffer size */

    u1                          dataLength;     /*!< payload data length (excluding the SCO header) */
};



/** 
SCO RX Buffer
*/
struct ClxRxScoBuffer
{
    struct ClxCQueueable        queueable;      /*!< Queueable object */

    u1*                         buffer;         /*!< buffer containing data received from a SCO channel */

    u2                          scoHandle;      /*!< SCO connection handle */
    u1                          dataLength;     /*!< received payload data length (excluding the SCO header) */

    u1                          statusFlag;     /*!< The status flag (the value is one of ClxRxScoStatusFlag_??? definitions) */
};


/** 
Specifies the type of a SCO connection:
*/
typedef enum ClxScoConnectionTypeEnum
{	ClxScoConnectionType_LegacySCO = 0,        /*!< Legacy SCO connection */
    ClxScoConnectionType_eSCO = 2              /*!< eSCO connection */
} ClxScoConnectionType;


/** 
Contains the details of a SCO connection:
*/
typedef struct ClxScoConnectionDetailsStruct
{
    ClxScoConnectionType        connectionType;                 /*!< Connection type */
	u2		                    scoConnectionHandle;			/*!< The SCO or eSCO connection handle */
    
    u2                          voiceSetting;                   /*!< Various settings for voice connections encoded as a 2-byte value. Use #clxDecodeScoVoiceSetting to extract individual voice settings.
                                                                     Note: The air coding format value encoded in this parameter is the value requested by the host interface implementation . The actual air coding format is
                                                                     determined by the member ClxScoConnectionDetails.airCodingFormat */

    u4		                    transmitBandwidth;              /*!< Transmit bandwidth in octets per second */
    u4		                    receiveBandwidth;               /*!< Receive bandwidth in octets per second */
    ClxScoAirCodingFormat		airCodingFormat;                /*!< Coding format of the audio data over the air */

    u1				            eScoTransmissionInterval;       /*!< Time between two consecutive eSCO instants measured in slots. Set to zero for Legacy SCO links */
    u1				            eScoRetransmissionWindow;       /*!< The size of the retransmission window measured in slots. Set to zero for Legacy SCO links */
    u2				            eScoRxPacketLength;             /*!< Length in bytes of the eSCO payload in the receive direction. Set to zero for Legacy SCO links */
    u2				            eScoTxPacketLength;             /*!< Length in bytes of the eSCO payload in the transmit direction. Set to zero for Legacy SCO links */
} ClxScoConnectionDetails;




/** 
SCO Interface structure declares bindings via the stack SCO function pointers
*/
struct ClarinoxBlueScoInterface
{
    /**
    Initializes the SCO interface. This is called by the ClarinoxBlue during the initialization of the Bluetooth stack.
    The arguments 'maxTxScoPayloadLength' and 'numOfControllerTxScoBuffers' are determined by the Bluetooth controller and may be used
    to generate an optimum stream of TX SCO packets.

    The Bluetooth controller has a fixed number of TX SCO buffers (numOfControllerTxScoBuffers), each of which can store a single TX SCO packet of the maximum payload length (maxTxScoPayloadLength). 
    If a TX packet is sent to the Bluetooth controller while there is no free TX buffer, A single TX packet will be dropped.
    NOTE : The TX buffers are shared by all active SCO connections. If there is more than one active SCO connection, the interface implementation is responsible for properly scheduling the TX streams.

    NOTE : This method is called in the context of the ClarinoxBlue stack thread.

    If any error occurs, an implementation must return an error (any value other than CLX_SUCCESS).
    NOTE : If the initialization of the interface fails for any reason, the method #destroy will not be called.

    \param[ in ] thisObj A pointer to this object.
    \param[ in ] maxTxScoPayloadLength The maximum payload length of a TX SCO packet.
    \param[ in ] numOfControllerTxScoBuffers Number of TX SCO buffers of the maximum size in the Bluetooth controller hardware. This is maximum number of TX SCO packets that may be pending transmission
                                             in the controller at any time. 

    \return CLX_SUCCESS if the procedure has been successful. In this case, the interface is initialized.
    Any other value indicates an error.
    */
    ClxResult (*init)                   (_in_ struct ClarinoxBlueScoInterface* thisObj, u1 maxTxScoPayloadLength, u2 numOfControllerTxScoBuffers);

    /**
    Destroys the already-initialized interface. This is called by the ClarinoxBlue during the termination of the Bluetooth stack.
    
    NOTE : This method is called in the context of the ClarinoxBlue stack thread.

    NOTE : This method CANNOT fail.

    \param[ in ] thisObj A pointer to this object.
    */
    void (*destroy)                     (_in_ struct ClarinoxBlueScoInterface* thisObj);      

    /**
    Called when a SCO packet is received. The received packet is stored in a #ClxRxScoBuffer object. When the RX buffer is not needed any longer, 
    the interface implementation is responsible to release the #ClxRxScoBuffer object by calling the API function #clxBlueReleaseRxScoBuffer. 
    The RX buffer may be released inside the implementation of this method or in another context.
    
    NOTE : This method is called in the context of the Bluetooth driver. Based on the implementation of the Bluetooth driver in the underlying platform, this may be a thread or an ISR.
           
    NOTE : For synchronization purposes, the implementation may temporarily disable the SCO packet reception context by calling the API function #clxBlueDisableScoRx. When this context
           is disabled, this method will not be called until the API function #clxBlueEnableScoRx is called to re-enable the context.
           Note that the API functions #clxBlueDisableScoRx and #clxBlueEnableScoRx MUST NOT be called inside the implementation of this method as it may lead to a deadlock.

    \param[ in ] thisObj A pointer to this object.
    \param[ in ] packet A stack-allocated object of type #ClxRxScoBuffer which contains the received SCO packet. This object must be released by a call to the API function #clxBlueReleaseRxScoBuffer.
    \param[ in ] isrContext If TRUE, this method has been called in the context of an ISR. If FALSE, this method has been called in the context of a thread. 
    */
    void (*rxReceived)                  (_in_ struct ClarinoxBlueScoInterface* thisObj, _in_ struct ClxRxScoBuffer* packet, _in_ boolean isrContext);

    /**
    Called when a new SCO connection is successfully established. A SCO connection is identified by its connection handle.

    NOTE : This method is called in the context of the ClarinoxBlue stack thread.

    \param[ in ] thisObj A pointer to this object.
    \param[ in ] scoConnectionDetails An object of type ClxScoConnectionDetails containing all the details of the established connection, including the SCO connection handle which is required for the TX stream path.
    */
    void (*scoConnectionEstablished)    (_in_ struct ClarinoxBlueScoInterface* thisObj, _in_ const ClxScoConnectionDetails* scoConnectionDetails);

    /**
    Called when an existing SCO connection is terminated. The terminated SCO connection is identified by its connection handle.

    NOTE : This method is called in the context of the ClarinoxBlue stack thread.

    \param[ in ] thisObj A pointer to this object.
    \param[ in ] scoConnectionDetails Connection handle of the SCO connection. Note that the same connection handle may be used by the Bluetooth controller for future SCO connections.
    */
    void (*scoConnectionTerminated)     (_in_ struct ClarinoxBlueScoInterface* thisObj, u2 scoConnectionHandle);

    /** 
    Unused by Clarinox stack. May be set by the implementation of this interface.
    */
    void* userData;                                                                                                     
};

/**
Returns a TX SCO buffer to the interface implementation for filling with SCO data. 

The buffer (and its associated #ClxTxScoBuffer object) is allocated from a private heap designated for SCO packets. 
If the requested buffer cannot be allocated (due to insufficient memory), this function will return NULL.

NOTE : If a valid object of type #ClxTxScoBuffer is returned, the actual buffer size will be stored in the member 'bufferSize' of the #ClxTxScoBuffer object. This value can only be less than the requested buffer size
if the requested size is more than the maximum SCO TX payload length (as passed to the #ClarinoxBlueScoInterface.init method of the interface implementation).

the following members of the object must be properly set by the interface implementation before the object is passed to the API function #clxBlueSendTxScoPacket :

 - #ClxTxScoBuffer.scoHandle
 - #ClxTxScoBuffer.dataLength

NOTE : This function CANNOT be called in the context of an ISR. However, it may be called in the context of any thread.

NOTE : A successful allocation of a #ClxTxScoBuffer object (and its associated data buffer) does NOT imply that there is any free TX buffer in the Bluetooth controller hardware.

\param[ in ] bufferSize The size of the buffer, in bytes. This size excludes the SCO header (e.g. this is length of the SCO packet payload).

\return An object of type #ClxTxScoBuffer which contains the details of the TX buffer. If there is not enough memory to allocate the requested buffer, NULL will be returned.
*/
extern struct ClxTxScoBuffer* clxBlueGetTxScoBuffer(_in_ u1 bufferSize);

/**
Releases an unused TX SCO buffer. This function is only required to be called if, for any reason, the interface implementation cannot pass the obtained #ClxTxScoBuffer object to the API function #clxBlueSendTxScoPacket.

NOTE : If the TX buffer has already (or is going to be) passed to the API function #clxBlueSendTxScoPacket, this function MUST NOT be called. Otherwise, the behaviour will be undefined.

NOTE : This function CANNOT be called in the context of an ISR. However, it may be called in the context of any thread.

\param[ in ] buffer The object of type #ClxTxScoBuffer which is to be released. Both the object and its associated data buffer will be released.
                    This object must have been obtained by a previous call to #clxBlueGetTxScoBuffer.
*/
extern void clxBlueReleaseTxScoBuffer(_in_ struct ClxTxScoBuffer* buffer);

/**
Releases RX SCO buffer after it is being consumed by the interface implementation  

NOTE : This function may be called in any context (including an ISR).

\param[ in ] buffer The object of type #ClxRxScoBuffer which is to be released. Both the object and its associated data buffer will be released.
                    This object must have been passed to the method #ClarinoxBlueScoInterface.rxReceived of the interface implementation.
*/
extern void clxBlueReleaseRxScoBuffer(_in_ struct ClxRxScoBuffer* buffer);


/**
Disables reception of new SCO RX packets. When this function returns, the method #ClarinoxBlueScoInterface.rxReceived of the interface implementation will not be called
until the RX path is re-enabled by a call to #clxBlueEnableScoRx.

This API may be used to ensure the synchronisation of the RX path between the SCO interface and the Bluetooth driver.

NOTE : This function may be called in any context (including an ISR). However, this function MUST NOT be called inside the 
       implementation of the method #ClarinoxBlueScoInterface.rxReceived of the interface implementation. Otherwise, a deadlock may occur.

NOTE : This function simply calls the method 'lock' of the ClarinoxBlue driver BSP interface (ClarinoxBlueDriverInterface.lock method).
       Refer to the implementation of the ClarinoxBlueDriverInterface.lock() method for more information on the specific behaviour of this API in the current platform.
*/
extern void clxBlueDisableScoRx();


/**
Re-enables reception of new SCO RX packets. The RX path must already have been disabled by a previous call to #clxBlueDisableScoRx().
When this function returns, the method #ClarinoxBlueScoInterface.rxReceived of the interface implementation might be called by the Bluetooth driver
at any time.

NOTE : This function may be called in any context (including an ISR). However, this function MUST NOT be called inside the 
       implementation of the method #ClarinoxBlueScoInterface.rxReceived of the interface implementation. Otherwise, a deadlock may occur.

NOTE : This function simply calls the method 'unlock' of the ClarinoxBlue driver BSP interface (ClarinoxBlueDriverInterface.unlock method).
       Refer to the implementation of the ClarinoxBlueDriverInterface.unlock() method for more information on the specific behaviour of this API in the current platform.
*/
extern void clxBlueEnableScoRx();

/**
Sends a TX SCO packet to the Bluetooth driver. If the SCO connection identified by its connection handle in the packet descriptor object (packet->scoHandle)
does not currently exist, the packet will be silently discarded. Otherwise, it will be passed to the Bluetooth driver. In either case, the descriptor object (packet)
will be released internally.

NOTE : This function CANNOT be called in the context of an ISR. However, it may be called in the context of any thread.

NOTE : The interface implementation is responsible for adjusting the timing of the TX stream.

\param[ in ] packet An object of type #ClxTxScoBuffer containing the TX data details. This object must have been obtained by a previous call to #clxBlueGetTxScoBuffer.
                    The object MUST NOT have been queued in a queue object (of type ClxCQueue).
*/
extern void clxBlueSendTxScoPacket(_in_ struct ClxTxScoBuffer* packet);

/** 
SCO Interface structure instance declaration
*/
extern struct ClarinoxBlueScoInterface* clarinoxBlueScoInterface;



#ifdef __cplusplus
}
#endif


#endif // _ClarinoxBlueScoInterface_h_

