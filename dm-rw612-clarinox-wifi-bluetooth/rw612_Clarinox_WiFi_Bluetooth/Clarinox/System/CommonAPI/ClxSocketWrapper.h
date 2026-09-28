#ifndef ClxSocketWrapper_h
#define ClxSocketWrapper_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxSocketWrapper.h
* Description         Declares ClxSocket related classes, types and macros
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif


/**
Converts a 32bit value from the host byte order to the network (big endian) byte order.

\param[ in ] value A 32bit value in the host (current platform) byte order.

\return The value in the network byte order.
*/
extern u4 CLX_HTONL(u4 value);


/**
Converts a 16bit value from the host byte order to the network (big endian) byte order.

\param[ in ] value A 16bit value in the host (current platform) byte order.

\return The value in the network byte order.
*/
extern u2 CLX_HTONS(u2 value);

/**
Converts a 32bit value from the network (big endian) byte order to the host byte order.

\param[ in ] long_value A 32bit value in the network (big endian) byte order.

\return The value in the host (current platform) byte order
*/
#define CLX_NTOHL(long_value)        CLX_HTONL(long_value)

/**
Converts a 16bit value from the network (big endian) byte order to the host byte order.

\param[ in ] short_value A 16bit value in the network (big endian) byte order.

\return The value in the host (current platform) byte order
*/
#define CLX_NTOHS(short_value)       CLX_HTONS(short_value)


/**
Returns the IP4 address 'a.b.c.d' as an integer of type ClxSocketIpv4Address.
NOTE : The return value is in the host byte order:
*/
#define CLX_IP4_ADDRESS(a, b, c, d)    (((u4)a << 24) | ((u4)b << 16) | ((u4)c << 8) | (u4)d)

/**
Returns the first (MSB) byte of the given IPv4 address. For an IP address in the format a.b.c.d, this macro returns a.
addr is assumed to be in the host byte order.
*/
#define CLX_IP4_ADDRESS_A(addr)        (((u4)addr & 0xFF000000) >> 24)

/**
Returns the second byte of the given IPv4 address. For an IP address in the format a.b.c.d, this macro returns b.
addr is assumed to be in the host byte order.
*/
#define CLX_IP4_ADDRESS_B(addr)        (((u4)addr & 0x00FF0000) >> 16)

/**
Returns the third byte of the given IPv4 address. For an IP address in the format a.b.c.d, this macro returns c.
addr is assumed to be in the host byte order.
*/
#define CLX_IP4_ADDRESS_C(addr)        (((u4)addr & 0x0000FF00) >> 8)

/**
Returns the forth (LSB) byte of the given IPv4 address. For an IP address in the format a.b.c.d, this macro returns d.
addr is assumed to be in the host byte order.
*/
#define CLX_IP4_ADDRESS_D(addr)         ((u4)addr & 0x000000FF)



#define CLX_MAC_ADDR_PRINTF_FORMAT                         "%02X:%02X:%02X:%02X:%02X:%02X"
#define CLX_IPV4_ADDR_PRINTF_FORMAT                        "%u.%u.%u.%u"

#define CLX_IPV4_ADDR_SIZE                                 4 /* Bytes */
#define CLX_IPV6_ADDR_SIZE                                 16 /* Bytes */


/**
Maximum size of the a socket address which an instance of ClxSocketAddressContainer can hold.
*/
#define CLX_SOCKETS_MAX_ADDRESS_SIZE                        32


#define CLX_SOCKET_ADDRESS_FAMILY_UNKNOWN                   0x0000
#define CLX_SOCKET_ADDRESS_FAMILY_IPV4                      0x0001
#define CLX_SOCKET_ADDRESS_FAMILY_IPV6                      0x0002


#define CLX_SOCKET_TYPE_STREAM                              0x0001             /*!< The ClxSocket object is associated to a TCP socket */
#define CLX_SOCKET_TYPE_DATAGRAM                            0x0002             /*!< The ClxSocket object is associated to a UDP socket */
#define CLX_SOCKET_TYPE_RAW                                 0x0003             /*!< The ClxSocket object is associated to a Layer3 IP socket (the packets contain the IP header and all upper layer headers) */
#define CLX_SOCKET_TYPE_ETHERNET                            0x0004             /*!< The ClxSocket object is associated to a Layer2 Ethernet socket (the packets contain Ethernet2 header and all upper layer headers) */


/**
Protocol type : Automatically recognize according to the type of socket.
*/
#define CLX_SOCKET_PROTOCOL_AUTO		                    0x00000



/**
An object of type ClxSocket is a handle for a network socket. 
*/
typedef void* ClxSocket;


/**
An instance of ClxSocketAddressContainer contains a socket (local or remote) address. 
This object does NOT represent a socket address of a specific type. It is only a container which can hold a socket address of any type.
When constructed, the container will not contain any valid address. Use a proper initialization function (e.g. clxSocketInitIpv4Address for IPv4 addresses) to initialize
the container objects with address details.

All addresses passed to ClxSocket API functions are of type ClxSocketAddressContainer.
*/
typedef struct ClxSocketAddressContainerStruct
{
    CLX_PLATFORM_ALIGNED_BUFFER (buffer, CLX_SOCKETS_MAX_ADDRESS_SIZE);
    ClxSize  length;
} ClxSocketAddressContainer;


extern u2           clxSocketGetAddressFamily(const ClxSocketAddressContainer* obj);
extern void         clxSocketCopyAddress(ClxSocketAddressContainer* dest, const ClxSocketAddressContainer* src);
extern boolean      clxSocketIsSameAddress(const ClxSocketAddressContainer* addr1, const ClxSocketAddressContainer* addr2);

/**
Defines the type of a variable which contains an IP address in the host byte order.
*/
typedef u4 ClxSocketIpv4Address;


/***********************
ClxNetworkIpv4Address
************************/
typedef struct ClxNetworkIpv4AddressStruct
{
    ClxSocketIpv4Address address;
    ClxSocketIpv4Address netmask;
    ClxSocketIpv4Address gateway;
} ClxNetworkIpv4Address;


/**
Functions to initialize and work with ClxSocketAddressContainer objects as IPv4 addresses. 
*/
extern void                 clxSocketInitIpv4AddressContainer(ClxSocketAddressContainer* obj);
extern void                 clxSocketSetIpv4Address(ClxSocketAddressContainer* obj, ClxSocketIpv4Address value);
extern void                 clxSocketSetIpv4Port(ClxSocketAddressContainer* obj, u2 value);
extern ClxSocketIpv4Address clxSocketGetIpv4Address(const ClxSocketAddressContainer* obj);
extern u2                   clxSocketGetIpv4Port(const ClxSocketAddressContainer* obj);
extern ClxSocketIpv4Address clxSocketConvertAscii_To_Ipv4(const s1* ipAddr);
extern const s1*            clxSocketConvertIpv4_To_Ascii(ClxSocketIpv4Address addr);
extern u4                   clxSocketGetIpv4AddressByName(const s1* name, ClxSocketIpv4Address* addressList, u4 addressListSize);


/**
An element in the IPv4 ARP cache. Used for testing purposes only. Sent to the stack as the value of a ClxConfigValue object.
*/
typedef struct ClxArpCacheElementStruct
{
    u1                            macAddress[CLX_MAC_ADDRESS_LENGTH];   /* MAC address. macAddress[0] specifies the most significant byte. */
    ClxSocketIpv4Address          ip4;                                  /* IPv4 address in host (native) byte order */
} ClxArpCacheElement;

/**
An object of type ClxSocketSet is a set (container) for sockets (of type ClxSocket). ClxSocketSet objects are used along with #clxSocketSelect().

NOTE : The maximum number of sockets that can be queued into a ClxSocketSet object is platform-dependent. Refer to the documentation of the fd_set structure for more information.
*/
struct ClxSocketSet;

/**
Allocates a ClxSocketSet object.

\return a pointer to an object of type ClxSocketSet.
*/
extern struct ClxSocketSet* clxSocketSetAllocate();

/**
Frees an object of type ClxSocketSet. The object must have been previously allocated by a call to #clxSocketSetAllocate.

\param[ in ] set The object to free.
*/
extern void clxSocketSetFree(struct ClxSocketSet* set);

/**
Clears a ClxSocketSet object by removing all socket objects from it.

\param[ in ] set The ClxSocketSet object.
*/
extern void clxSocketSetClear(struct ClxSocketSet* set);

/**
Adds a socket to a ClxSocketSet object.

\param[ in ] set The ClxSocketSet object.
\param[ in ] socket The socket object to add to the set.
*/
extern void clxSocketSetAdd(struct ClxSocketSet* set, ClxSocket socket);

/**
Checks whether or not a socket is in a ClxSocketSet object.

\param[ in ] set The ClxSocketSet object.
\param[ in ] socket The socket object to check for in the set.

\return TRUE if the socket is in the set. FALSE otherwise.
*/
extern boolean clxSocketSetCheck(const struct ClxSocketSet* set, ClxSocket socket);


/**
Initializes the socket interface.

\return CLX_SUCCESS if the initialization has been successful.
Any other value will indicate an error.
*/
extern ClxResult clxInitSocketInterface();

/**
Initializes an ClxSocket object, and associates it to a new underlying network socket.
   
\param [ in ] addressFamily The address family to which the new socket will belong.
\param [ in ] type The type of the underlying network socket which this object will represent.
\param [ in ] protocol the protocol to be used for this socket. If set CLX_SOCKET_PROTOCOL_AUTO, then the appropriate protocol
will be chosen based on the socket type.
\param [ out ] socket The new socket. If not successful, this value will not be valid.

\return CLX_SUCCESS if the address of the peer socket was retrieved successfully.
Any other value will indicate an error.
*/
extern ClxResult clxSocketOpen (u2 addressFamily, u2 type, u2 protocol, ClxSocket* socket);
    

/**
Sets the socket blocking mode for this socket.

\param[ in ] socket socket object.
\param[ in ] nonblockingMode If TRUE, the socket will be in non-blocking mode. If FALSE, the socket will be in blocking mode. 

\return CLX_SUCCESS if successful.
Any other value will indicate an error.
*/
ClxResult clxSocketSetMode (ClxSocket socket, boolean nonblockingMode);


/**
Binds the socket to a local address.
    
\param[ in ] socket socket object.
\param[ in ] localAddress the local address to which this socket is to bind. The family of the local address must be compatible with the
type of the socket.

\return CLX_SUCCESS if the address of the peer socket was retrieved successfully.
Any other value will indicate an error.
*/
extern ClxResult clxSocketBind(ClxSocket socket, const ClxSocketAddressContainer* localAddress);

/**
Establishes a connection to a peer socket. If successful, this socket can then only send to and receive from this peer socket. Based on the actual type of the socket, this function may try to establish
a connection to a remote device by protocol handshaking (e.g. in case of TCP), or it may just internally set the target of all sending and receiving operations to this address (e.g. in case of UDP).

If this is a non-blocking socket, this function will return immediately. If the return value is CLX_SOCKET_EWOULDBLOCK, the connection cannot complete synchronously. Use #clxSocketSelect() to wait for the connection completion.
If this is a blocking socket, this function will not return until the connection procedure is complete (either with success or in error).
    
NOTE : Some socket types might not implement this function. In this case, this function will return an error.

\param[ in ] socket socket object.
\param[ in ] peerAddress The address of the peer socket. The family of this address MUST be the same as the family of the local address as passed to #clxSocketBind().

\return CLX_SUCCESS if the connection procedure has been successful.
CLX_SOCKET_EWOULDBLOCK if the socket is in non-blocking mode and the connection procedure cannot complete asynchronously.
Any other value will indicate an error.
*/
extern ClxResult clxSocketConnect(ClxSocket socket, const ClxSocketAddressContainer* peerAddress);


/**
Places the network socket into listening mode. A listening socket cannot be used to connect to a peer socket, or send and receive data. It can only be used to listen for incoming connection requests.
Call this function when the local application is to act as a server.

If this function succeeds, the application can accept incoming connection requests by calling #clxSocketAccept().

\param[ in ] socket socket object.
\param[ in ] maxNumberOfPendingRequests Maximum number of connection requests which can be pending at any given time. Use this argument to limit the number of connections that the local server is able to handle.
    
\return CLX_SUCCESS if the socket was successfully placed in listening mode.
Any other value will indicate an error.
*/
extern ClxResult clxSocketListen(ClxSocket socket, u4 maxNumberOfPendingRequests);

/**
Accepts a connection request from a peer socket and returns a new ClxSocket object which is associated to this new connection. Before this function is called, the #clxSocketListen() must have been called in order
to place this network socket into listening mode.

In case of the listening socket being in the non-blocking mode, if there is no connection request pending when this function is called, the function will return immediately with the error CLX_SOCKET_EWOULDBLOCK.
In case of the listening socket being in the blocking mode, if there is no connection request pending when this function is called, the function will block until a connection request is received and then accept it.

\param[ in ] socket socket object.
\param[ out ] peerAddress A pointer to a caller-provided container object of type ClxSocketAddressContainer which on a successful return will hold the address of the peer socket. The family of the address will be the same of the
family of the local address as passed to #clxSocketOpen().
\param[ out ] newSocket A new ClxSocket object which (in case of success) is associated to a valid network socket which represents the new accepted connection. If this function is not successful,
this argument will not contain a valid socket object.

\return CLX_SUCCESS if a connection request was successfully accepted. In this case, the return ClxSocket object will be associated to a valid underlying network socket.
CLX_SOCKET_EWOULDBLOCK if the socket is in non-blocking mode and there is no incoming connection request currently pending to be accepted.
Any other value will indicate an error.
*/
extern ClxResult clxSocketAccept(ClxSocket socket, ClxSocketAddressContainer* peerAddress, ClxSocket* newSocket);

/**
Sends data to the connected peer socket. Based on the type of the network socket, The data will be sent as a separate packet, or might be encoded in one or more packets as part of a stream. 

\param[ in ] socket socket object.
\param[ in ] data A pointer to the data which is to be sent to the connected peer socket.
\param[ in ] dataLength The length of the data, in bytes, to be sent to the peer socket.
\param[ out] written A pointer to a caller-provided variable of type ClxSize which on a successful return will hold the length of data, in bytes, which was actually sent
to the peer socket. This value might be less than the length of the data which was passed to this function.If the function returns any value other than CLX_SUCCESS, 
this value must be ignored. 

\return CLX_SUCCESS if the operation was successful, the value of written argument specifies the number of bytes which were actually sent to the peer socket.
CLX_SOCKET_EWOULDBLOCK if the socket is in non-blocking mode and the sending operation cannot complete synchronously at this moment.
Any other value will indicate an error.
*/
extern ClxResult clxSocketSend(ClxSocket socket, const void* data, ClxSize dataLength, ClxSize* written);

/**
Sends data to an arbitrary remote address. This is used when there is no connection to a peer socket. This function cannot be used with socket types which require a connection to a peer socket (e.g. TCP).
Based on the type of the network socket, The data will be sent as a separate packet, or might be encoded in one or more packets as part of a stream. 

This function can be used to send data to a single remote device or multicast/broadcast it to several relevant remote devices.

\param[ in ] socket socket object.
\param[ in ] remoteAddress The address of the remote device to which the data is to be sent.
\param[ in ] data A pointer to the data which is to be sent to the remote device.
\param[ in ] dataLength The length of the data, in bytes, to be sent to the remote device.
\param[ out] written A pointer to a caller-provided variable of type ClxSize which on a successful return will hold the length of data, in bytes, which was actually sent
to the remote device. This value might be less than the length of the data which was passed to this function. If the function returns any value other than CLX_SUCCESS,
this value must be ignored. 

\return CLX_SUCCESS if the operation was successful, the value written argument specifies the number of bytes which were actually sent to the remote device.
CLX_SOCKET_EWOULDBLOCK if the socket is in non-blocking mode and the sending operation cannot complete synchronously at this moment.
Any other value will indicate an error.
*/
extern ClxResult clxSocketSendTo(ClxSocket socket, const ClxSocketAddressContainer* remoteAddress, const void* data, ClxSize dataLength, ClxSize* written);

/**
Receives data from the connected peer and copies it into the caller-provided memory buffer. Based on the socket type, the received data might be a single packet or part of the incoming data stream.
In the former case, if the size of the buffer provided is smaller than the size of the received packet, some part of the data in the packet may be lost.

\param[ in ] socket socket object.
\param[ out ] buffer A caller-provided buffer which on a successful return will contain the received data.
\param[ in ] bufferSize size of the caller-provided buffer, in bytes. This is the maximum length of the data which can be copied. The actual received data might be smaller.
\param[ out ] read A pointer to a caller-provided variable of type ClxSize which on a successful return will hold the actual number of bytes which were copied into the provided memory buffer.
If this function returns CLX_SUCCESS, this value can be 0 only if the connection to the peer socket was closed before any data was received.

\return CLX_SUCCESS if the operation was successful, the value of read argument specifies the number of bytes which were actually copied into the provided buffer.
CLX_SOCKET_EWOULDBLOCK if the socket is in non-blocking mode and there is no incoming data received from the peer socket and pending at this moment.
Any other value will indicate an error.
*/
extern ClxResult clxSocketReceive(ClxSocket socket, const void* buffer, ClxSize bufferSize, ClxSize* read);

/**
Receives data from any remote device and copies it into the caller-provided memory buffer. This function cannot be used with socket types which require a connection to a peer socket (e.g. TCP).
Based on the socket type, the received data might be a single packet or part of the incoming data stream.
In the former case, if the size of the buffer provided is smaller than the size of the received packet, some part of the data in the packet may be lost.

This function can be used to receive both unicast data (destined to our local address) and multicast/broadcast data.

\param[ in ] socket socket object.
\param[ out ] buffer A caller-provided buffer which on a successful return will contain the received data.
\param[ in ] bufferSize Size of the caller-provided buffer, in bytes. This is the maximum length of the data which can be copied. The actual received data might be smaller.
\param[ out ] remoteAddress A pointer to a caller-provided container object of type ClxSocketAddressContainer which on a successful return will contain the address of the remote socket from which the
data has been received. The family of this address will be the same as the family of the local address as passed to #clxSocketOpen().
NOTE : remoteAddress object MUST be initialized with the relevant function (e.g. for instance, #clxSocketInitIpv4AddressContainer() for IPv4 addresses) before being passed to this function.  
\param[ out ] read A pointer to a caller-provided variable of type ClxSize which on a successful return will hold the actual number of bytes which were copied into the provided memory buffer.

\return CLX_SUCCESS if the operation was successful, the value of received argument specifies the number of bytes which were actually copied into the provided buffer.
CLX_SOCKET_EWOULDBLOCK if the socket is in non-blocking mode and there is no incoming data received from a remote socket and pending at this moment.
Any other value will indicate an error.
*/
extern ClxResult clxSocketReceiveFrom(ClxSocket socket, const void* buffer, ClxSize bufferSize, ClxSocketAddressContainer* remoteAddress, ClxSize* read);

/**
Closes the socket object.

\param[ in ] socket socket object.

\return CLX_SUCCESS if successful.
Any other value will indicate an error.
*/
extern ClxResult clxSocketClose(ClxSocket socket);

/**
Blocks until an event occurs on a non-blocking socket. For more information, please refer to https://en.wikipedia.org/wiki/Select_(Unix)

NOTE : In the standard BSD socket interface, there is an argument called nfds. clxSocketSelect() calculates this argument automatically.

\param[ in ] readSockets The set of non-blocking sockets for which this function must wait until at least one becomes readable.
\param[ in ] writeSockets The set of non-blocking sockets for which this function must wait until at least one becomes writable.
\param[ in ] exceptSockets The set of non-blocking sockets for which this function must wait until at least one throws an exception.

\param[ in ] timeout The timeout value for this operation. This argument may be set to NULL. In this case, there will be no timeout.

\return CLX_SUCCESS if successful.
Any other value will indicate an error.
*/
extern ClxResult clxSocketSelect(struct ClxSocketSet* readSockets, struct ClxSocketSet* writeSockets, struct ClxSocketSet* exceptSockets, const struct ClxTimeval* timeout);

/**
Returns the local address of this socket.

\param[ in ] socket socket object.
\param[ out ] localAddress A pointer to a caller-provided container object of type ClxSocketAddressContainer which on a successful return will contain the local address of this socket.

\return CLX_SUCCESS if the local address was retrieved successfully.
Any other value will indicate an error.
*/
extern ClxResult clxSocketGetLocalAddress(ClxSocket socket, ClxSocketAddressContainer* localAddress);


/**
Returns the address of the peer socket to which there is a connection.

\param[ in ] socket socket object.
\param[ out ] peerAddress A pointer to a caller-provided container object of type ClxSocketAddressContainer which on a successful return will contain the address of the peer socket.

\return CLX_SUCCESS if the address of the peer socket was retrieved successfully.
Any other value will indicate an error.
*/
extern ClxResult clxSocketGetPeerAddress(ClxSocket socket, ClxSocketAddressContainer* peerAddress);



#ifdef __cplusplus
}
#endif

#endif   // ClxSocketWrapper_h
