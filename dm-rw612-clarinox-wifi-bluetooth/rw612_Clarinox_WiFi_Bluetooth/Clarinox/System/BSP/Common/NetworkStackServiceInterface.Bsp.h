#ifndef NetworkStackServiceInterface_Bsp_h
#define NetworkStackServiceInterface_Bsp_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                NetworkStackServiceInterface.Bsp.h
* Description         Network Stack Service BSP Interface
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#define CLX_LIMITED_BROADCAST_IP    CLX_IP4_ADDRESS(255, 255, 255, 255)

#define CLX_IPV4_PORT_ADDRSTRLEN    22  /* Bytes */
#define CLX_IPV6_PORT_ADDRSTRLEN    54  /* Bytes */
#define CLX_MAC_ADDRSTRLEN          18  /* Bytes */


#ifdef __cplusplus
extern "C" {
#endif


CLX_DECLARE_C_OBJECT_RTTI(ClxAsyncNetworkUdpSocket);
CLX_DECLARE_C_OBJECT_RTTI(ClxAsyncNetworkTcpClientSocket);
CLX_DECLARE_C_OBJECT_RTTI(ClxAsyncNetworkTcpListenSocket);          /* Only the methods ClxAsyncNetworkSocket->init(), ClxAsyncNetworkSocket->terminate() and ClxAsyncNetworkSocket->destroy() need to be implemented */
CLX_DECLARE_C_OBJECT_RTTI(ClxAsyncNetworkEchoRequestSocket);        /* May not be available in all platforms */


struct ClxAsyncNetworkSocketStruct;
typedef struct ClxAsyncNetworkSocketStruct* ClxAsyncNetworkSocket;


/**
The Network Service address type
*/
enum ClxNetworkServiceAddressType
{
    ClxNetworkServiceAddressType_IP4 = 0,
    ClxNetworkServiceAddressType_IP6,
    ClxNetworkServiceAddressType_Ethernet
};


/**
The Network Service source or destination IPv4 address
*/
struct ClxNetworkServiceIpv4Address
{
    ClxSocketIpv4Address  addr;                  /*!< IPv4 address in host byte order */ 
    u2                    port;                  /*!< TCP/UDP port in host byte order */ 
};
    

/**
The Network Service source or destination IPv6 address
*/
struct ClxNetworkServiceIpv6Address
{
    u4  addr[CLX_IPV6_ADDR_SIZE/sizeof(u4)];    /*!< IPv6 address in host byte order (treated a 16-byte array of type u1) */
    u2  port;                                   /*!< TCP/UDP port in host byte order */
};


/**
The Network Service source or destination Ethernet address
*/
struct ClxNetworkServiceEtehrnetAddress
{
    u1  addr[CLX_MAC_ADDRESS_LENGTH];           /*!< Ethernet MAC Address in network byte order */
};


/**
The Network Service source or destination address 
*/
typedef struct ClxNetworkServiceAddressStruct
{
    enum ClxNetworkServiceAddressType	         type;		/*!< Actual type of this structure */
    
    union Union
    {
        struct ClxNetworkServiceIpv4Address      ip4;
        struct ClxNetworkServiceEtehrnetAddress  ip6;
        struct ClxNetworkServiceEtehrnetAddress  eth;
    } u;
} ClxNetworkServiceAddress;


/**
Parses the string containing a MAC address in the format XX:XX:XX:XX:XX:XX (Null terminated),
and returns the MAC address in binary format (CLX_MAC_ADDRESS_LENGTH bytes, no null termination).

\param[ in ] str The Null-terminated string buffer containing the MAC address in HEX format.
\param[ out ] macAddrBuf A caller-allocated buffer which on return will carry the MAC address in binary format (only if the return
value of the function is TRUE). The size of this buffer MUST BE at least CLX_MAC_ADDRESS_LENGTH bytes.

\return TRUE The conversion has been successful.
FALSE The string is not in the correct HEX format.
*/
boolean clxParseMacAddressString(const s1* str, u1* macAddrBuf);


/**
Converts an address (IPv4, IPv6, or MAC) into its standard string representation.

\param[ in ] src The IP address to be converted to the standard string representation.
                 NOTE: In case of IPv4 and IPv6 addresses, the port value is represented in the output string ONLY if its value is not 0. Otherwise, it is ignored.
                 NOTE: IPV6 addresses are not supported at this moment.

\param[ in ] dst The output buffer which, on a successful operation, will contain the standard string representation of address provided.
                 The output will be NULL-terminated. The size of this buffer MUST be as follows:

                 - If the input is an IPv4 address, the output buffer must at least CLX_IPV4_PORT_ADDRSTRLEN bytes.
                 - If the input is an IPv6 address, the output buffer must be at least CLX_IPV6_PORT_ADDRSTRLEN bytes.
                 - If the input is a MAC address, the output buffer must be at least CLX_MAC_ADDRSTRLEN bytes.

\param[ in ] size the size of output buffer (dst).

\return If successful, returns the output buffer (dst). Otherwise, returns NULL.
        Failure could be due to one of the following reasons:
            - src or/and dst is NULL.
            - The type of the input address is not supported.
            - Size of output buffer is not enough to contain the standard string representation of the address (including the NULL-termination character).
*/
extern const s1* clxNetAddr2Str(_in_ const ClxNetworkServiceAddress* src, _out_ s1* dst, _in_ size_t size);

/**
Converts the standard string representation of an address (IPv4, IPv6, or MAC) into a ClxNetworkServiceAddress object.
s
\param[ in ] srcType The source address type.
                     NOTE: IPV6 addresses are not supported at this moment.

\param[ in ] src The standard string representation of the address (as per the address type).
\param[ in ] dst Pointer to a dst object which, on a successful return, will contain the address.
                 NOTE : In case of IPv4 and IPv6 addresses, if the string representation does not contain the port value, the port in dst will be set to 0. 

\return CLX_SUCCESS : Successful.
        CLX_SYSTEM_EAFNOSUPPORT : The address is not supported.
        CLX_ERROR_INVALID_COMMAND_ARGUMENT : Either src is NULL, or is not in the valid standard string representation.
*/
extern ClxResult clxNetStr2Addr(_in_ enum ClxNetworkServiceAddressType srcType, _in_ const s1* src, _out_ ClxNetworkServiceAddress* dst);


/**
A generic call-back based interface for a network service. A network service could to be the client side or the server side of a network protocol (e.g. DHCP, FTP, ...).

All call-back functions are called in the context of a single thread (network sub-system thread). The APIs in this file can only be called in the context of this thread (e.g. they can only be called
inside the implementations of call-back functions on this interface).
*/
struct ClxNetworkService
{
    /**
    The socket task callback. Each socket (of type ClxAsyncNetworkSocket) has a task which may be scheduled by a call to its ClxAsyncNetworkSocket.scheduleTask() method.
    
    The task may be re-schediled inside the implementation of this callback function.

    \param[ in ] service This object
    \param[ in ] socket The socket object
    */
    void (*runSocketTask) (_in_ struct ClxNetworkService* service,
                           _in_ ClxAsyncNetworkSocket socket);

    /**
    Called by the network socket to inform the interface implementation that the initialization of the socket has been complete, either with success or in error. 

    NOTE : A successfully initialized socket may be terminated at any time by a call to its ClxAsyncNetworkSocket.terminate() method.

    If initialization has failed, the implementation MUST destroy the socket by a call to its ClxAsyncNetworkSocket.destroy() method. 
    In this case, the ClxAsyncNetworkSocket.terminate() method MUST NOT be called.

    \param[ in ] service        This object
    \param[ in ] socket         The socket object
    \param[ in ] localAddress   The address of the local side of the socket. This cannot be NULL
    \param[ in ] remoteAddr     The address of the remote side of the socket. This may be NULL
    \param[ in ] result         The result of the initialization
    */
    void (*socketInitComplete) (_in_ struct ClxNetworkService* service,
                                _in_ ClxAsyncNetworkSocket socket,
                                _in_ const ClxNetworkServiceAddress* localAddress,
                                _in_ const ClxNetworkServiceAddress* remoteAddr,
                                _in_ ClxResult result);
    
    /**
    Called by the sub-system to inform the interface that a socket has been terminated so it cannot be used to send/receive data any longer.
    
    This may be called as a result of a previous call to the socket ClxAsyncNetworkSocket.terminate() method, or due to an error occurred during the socket operation.

    NOTE : If the socket initialization has failed, this method is NOT called for the socket. 
    The implementation MUST destroy the socket by a call to its ClxAsyncNetworkSocket.destroy() method. ClxAsyncNetworkSocket.destroy() may be called inside this method.

    \param[ in ] service  This object
    \param[ in ] socket   The socket object
    \param[ in ] reason   The reason of socket termination.
    */
    void (*socketTerminated) (_in_ struct ClxNetworkService* service,
                              _in_ ClxAsyncNetworkSocket socket,
                              _in_ ClxResult reason);

    /**
    Called by the network sub-system to inform the interface implementation that the currently pending transmission operation is complete either with success or in error.
    This is called as a result of a previous call to the socket ClxAsyncNetworkSocket.send() method.

    NOTE : If the call to the socket ClxAsyncNetworkSocket.send() has not returned CLX_ERROR_COMPLETION_PENDING, this method is NOT called.
    NOTE : If a transmission operation is pending and the socket is terminated for any reason, this method will NOT be called. Instead, socketTerminated() will be called.

    \param[ in ] service    This object
    \param[ in ] socket     The socket object
    \param[ in ] desc       The descriptor object containing the transmitted data. This is the same object passed to ClxAsyncNetworkSocket.send().
    \param[ in ] remoteAddr The destination address for the transmitted data. This may be NULL if the socket has been configured to send data to a specific target.

    \param[ in ] result CLX_SUCCESS                 The entire data was transmitted successfully 
                        CLX_ERROR_TIMEOUT_OCCURRED  The operation timed out before the entire data could be sent to the target.
                        Any other value indicates that either part or all of the data could not be sent to the target due to an error.
    */
    void (*socketSendComplete) (_in_ struct ClxNetworkService* service,
                                _in_ ClxAsyncNetworkSocket socket,
                                _user_in_ ClxNetworkBufferDescriptor* desc,
                                _in_ const ClxNetworkServiceAddress* remoteAddr,
                                _in_ ClxResult result);
    
    /**
    Called by the network sub-system to inform the interface implementation that the currently pending reception operation is complete either with success or in error.
    
    This is called as a result of a previous call to the socket ClxAsyncNetworkSocket.recv() method.

    NOTE : If the call to the socket ClxAsyncNetworkSocket.recv() has not returned CLX_ERROR_COMPLETION_PENDING, this method is NOT called.
    NOTE : If a reception operation is pending and the socket is terminated for any reason, this method will NOT be called. Instead, socketTerminated() will be called.

    \param[ in ] service    This object
    \param[ in ] socket     The socket object
    \param[ in ] desc       The descriptor object containing the received data. This is the same object passed to ClxAsyncNetworkSocket.recv().
    \param[ in ] remoteAddr The source address of the received data. This may be NULL if the socket has been configured to receive data from a specific target.

    \param[ in ] result CLX_SUCCESS                 The descriptor object contains the received data.
                        CLX_ERROR_TIMEOUT_OCCURRED  The operation timed out before any data is received from the target.
                        Any other value indicates that either part or all of the received data was lost to due to an error.
    */
    void (*socketRecvComplete) (_in_ struct ClxNetworkService* service,
                                _in_ ClxAsyncNetworkSocket socket,
                                _user_in_ ClxNetworkBufferDescriptor* desc,
                                _in_ ClxNetworkServiceAddress* remoteAddr,
                                _in_ ClxResult result);
};


/**
Interface for asynchronous sockets. Any method marked as CLX_ASYNC may either complete immediately or may return CLX_ERROR_COMPLETION_PENDING.
indicating that the operation will be complete later. In the latter case, upon completion of the requested operation, the corresponding method of the network service will be called.

There is no standard function to create a socket object. Each platform or network stack (e.g. LWIP) may have its own creation functions.
*/
struct ClxAsyncNetworkSocketStruct
{
    /**
    Optional parent service data. May be used by the service.
    */
    void* serviceData;

    /**
    Type of the socket. Must return one of the following:

    CLX_C_STRUCTURE_TYPE(ClxAsyncNetworkUdpSocket)
    CLX_C_STRUCTURE_TYPE(ClxAsyncNetworkTcpClientSocket)
    CLX_C_STRUCTURE_TYPE(ClxAsyncNetworkTcpListenSocket)
    CLX_C_STRUCTURE_TYPE(ClxAsyncNetworkEchoRequestSocket)
    
    \param[ in ] this_ This object
    */
    const void* (*type) (_in_ ClxAsyncNetworkSocket this_);

    /**
    Initializes the socket. The implementation may be a combination of bind() and connect() if applicable.

    \param[ in ] this_          This object
    \param[ in ] service        The network service object to which this socket belongs. The implementation must store this object for future use.
    \param[ in ] localAddress   The local address of the socket. This CANNOT be NULL.
    \param[ in ] remoteAddr     The remote address of the socket. This may be NULL if the socket is not to bound to a specific target.
    \param[ in ] options        For future use

    \return CLX_SUCCESS                     Initialization has been successful and the socket is now ready to send/receive data.
            CLX_ERROR_COMPLETION_PENDING    The operation has started. Upon completion of the operation, the method ClxNetworkService.socketInitComplete() of the parent service will be called.
            Any other error indicates a failure. In this case, the parent service MUST destroy the socket by a call to its ClxAsyncNetworkSocket.destroy() method.
    */
    ClxResult CLX_ASYNC (*init) (_in_ ClxAsyncNetworkSocket this_,
                                 _in_ struct ClxNetworkService* service, 
                                 _in_ const ClxNetworkServiceAddress* localAddress,
                                 _in_ const ClxNetworkServiceAddress* remoteAddr,
                                 _inout_ ClxConfigList* options);

    /**
    Sends data to the target over the socket.
    If this is a datagram-based socket, the provided data will be considered a single packet.

    the provided data may be fragmented into two or more chunks. In this case, the chunks must form a ClxNetworkBufferDescriptor chain.

    The operation will complete when the entire data has been sent to the target, or an error occurs.

    NOTE : If this operation fails for any reason, this does NOT indicate that the socket is unusable. In case of a fatal error, the method ClxNetworkService.socketTerminated() of the parent service will be called.

    \param[ in ] this_          This object
    \param[ in ] desc           The descriptor object (or chain) containing the data to send. This object (or chain) and the associated data buffers MUST NOT be modified, accessed or deleted until the operation is complete.
    \param[ in ] remoteAddr     The address of the target. This may be NULL if the socket is bound to a specific target.
    \param[ in ] timeout        Operation timeout value, in milliseconds. If the operation times out before the entire data has been sent, the operation will be complete with the error CLX_ERROR_TIMEOUT_OCCURRED.
                                The value 0 indicates that the implementation CANNOT return CLX_ERROR_COMPLETION_PENDING.
                                The value CLX_INFINITE indicates that operation must not complete until the entire data has been sent, or an error occurs.

    \return CLX_SUCCESS                     The entire data has been successfully passed to the network stack. This does NOT mean that the data has been successfully received by the target.
            CLX_ERROR_COMPLETION_PENDING    The operation has started. Upon completion of the operation, the method ClxNetworkService.socketSendComplete() of the parent service will be called.
            Any other error indicates a failure.
    */
    ClxResult CLX_ASYNC (*send) (_in_ ClxAsyncNetworkSocket this_,
                                 _user_in_ ClxNetworkBufferDescriptor* desc,
                                 _in_ const ClxNetworkServiceAddress* remoteAddr,
                                 _in_ u4 timeout);

    /**
    Receives data from the target over the socket.
    If this is a datagram-based socket, the operation will be complete with success only if an entire packet has been received.
    If this is a stream-based socket, the operation may be complete with success if at least one byte of data has been received.

    NOTE : Non-contiguous received buffers are NOT supported. Therefore, a ClxNetworkBufferDescriptor chain MAY NOT be passed to this method. 

    NOTE : If this operation fails for any reason, this does NOT indicate that the socket is unusable. In case of a fatal error, the method ClxNetworkService.socketTerminated() of the parent service will be called.

    \param[ in ] this_          This object
    \param[ in ] desc           The descriptor object containing the buffer in which the received data will be copied. This object and the associated data buffer MUST NOT be modified, accessed or deleted until the operation is complete.
    \param[ in ] remoteAddr     The address of the target. This may be NULL if the socket is bound to a specific target.
    \param[ in ] timeout        Operation timeout value, in milliseconds. If the operation times out before a complete packet is received (in case of datagram-based sockets), 
                                or no data has been received (in case of stream-based sockets), the operation will be complete with the error CLX_ERROR_TIMEOUT_OCCURRED.
                                The value 0 indicates that the implementation CANNOT return CLX_ERROR_COMPLETION_PENDING.
                                The value CLX_INFINITE indicates that operation must not complete until an entire packet (in case of datagram-based sockets) or any data (in case of stream-based sockets)
                                is received, or an error occurs.

    \return CLX_SUCCESS                     The operation has been successful. The descriptor contains the entire received packet (in case of datagram-based sockets) or at least one byte of received data (in case of stream-based sockets).
            CLX_ERROR_COMPLETION_PENDING    The operation has started. Upon completion of the operation, the method ClxNetworkService.socketRecvComplete() of the parent service will be called.
            Any other error indicates a failure.
    */
    ClxResult CLX_ASYNC (*recv) (_in_ ClxAsyncNetworkSocket this_,
                                 _user_in_ ClxNetworkBufferDescriptor* desc,
                                 _out_ ClxNetworkServiceAddress* remoteAddr,
                                 _in_ u4 timeout);

    /**
    Terminates the socket. Upon termination, the parent service is responsible for destroying this socket object by a call to its ClxAsyncNetworkSocket.destroy() method.
    
    When this method is called, other methods of the socket MUST NOT be called.

    \param[ in ] this_ This object

    \return CLX_SUCCESS                     The socket has been terminated successfully.
            CLX_ERROR_COMPLETION_PENDING    The operation has started. Upon completion of the operation, the method ClxNetworkService.socketTerminated() of the parent service will be called.
            Any other error indicates a failure. In this case, the socket object must still be removed by a call to its ClxAsyncNetworkSocket.destroy() method.
    */
    ClxResult CLX_ASYNC (*terminate) (_in_ ClxAsyncNetworkSocket this_);

    /**
    Schedules the socket task. When the task is scheduled, it CANNOT be re-scheduled until the method ClxNetworkService.runSocketTask() of the parent service is called. 

    The parent service MUST use the socket task to avoid nested calls to socket methods which may result in undefined behaviour or deadlock.

    \param[ in ] this_ This object

    This method never fails.
    */
    void CLX_ASYNC (*scheduleTask) (_in_ ClxAsyncNetworkSocket this_);

    /**
    Physically destroys the socket object. This MUST be called by the parent service ONLY when the socket is terminated.
    The socket object MUST NOT be accessed after this method returns.

    This method never fails.
    */
    void (*destroy) (_in_ ClxAsyncNetworkSocket this_);
};



#ifdef __cplusplus
}
#endif


#endif // NetworkStackServiceInterface_Bsp_h

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : A function should be used in preference to a function-like */
/*                 macro.                                                     */ 
/* Rule          : MISRA-C:2004 Rule 19.7                                     */ 
/* Justification : No risk identified. Used to provide better performance in  */
/*                 embedded system environments that do not support efficient */
/*				   functions inlining.                                        */
/******************************************************************************/

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
