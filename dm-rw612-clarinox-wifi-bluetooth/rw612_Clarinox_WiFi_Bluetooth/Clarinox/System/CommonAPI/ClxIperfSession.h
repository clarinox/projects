#ifndef ClxIperfSession_h
#define ClxIperfSession_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxIperfSession.h
* Description         Defines UDP/TCP Iperf Session Manager
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


struct ClxUdpIperfClientSession;
struct ClxUdpIperfServerSession;

struct ClxTcpIperfSession;



/**
Creates an instance of TCP Iperf (Client or Server) Session object. The object manages a single TCP Iperf session  (e.g. a single TCP connection).

\param[ in ] interval The interval (in ms) in which the report has to be generated and displayed.
\param[ in ] sessionPeriod The session period (in ms). When the session period elapses, clxTcpIperfSession_DataTransferred() will return FALSE for this session.

\return Handle of the created instance.
*/
extern struct ClxTcpIperfSession* clxTcpIperfSession_Create(u2 interval, u4 sessionPeriod);


/**
Destroys a instance of TCP Iperf Session object.

\param[ in ] handle Handle of the session object to be destroyed.
*/
extern void clxTcpIperfSession_Destroy(struct ClxTcpIperfSession* handle);


/**
Reports to the session that data has been sent or received. This function MUST be called after each TCP transfer.

\param[ in ] handle Handle of the session object.
\param[ in ] dataLength The length of data sent. If set to 0, it indicates that the session has ended (and so this function will return FALSE).

\return TRUE if the session is ongoing. FALSE if the session has ended (either because the session period has elapsed, or dataLength has been set to 0)
*/
extern boolean clxTcpIperfSession_DataTransferred(struct ClxTcpIperfSession* handle, u4 dataLength);



/**
Creates an instance of UDP Iperf Client Session object. The object manages a single UDP Iperf session on the client side.

\param[ in ] bps The target bandwidth in bits per second.
\param[ in ] interval The interval (in ms) in which the report has to be generated and displayed.

\return Handle of the created instance.
*/
extern struct ClxUdpIperfClientSession* clxUdpIperfClientSession_Create(u4 bps, u2 interval);


/**
Destroys a instance of UDP Iperf Client Session object.

\param[ in ] handle Handle of the session object to be destroyed.
*/
extern void clxUdpIperfClientSession_Destroy(struct ClxUdpIperfClientSession* handle);

/**
Generates the payload of the UDP Iperf packet.

\param[ in ] handle Handle of the session object.
\param[ in ] buffer The caller-allocated buffer for the payload of the UDP packet.
\param[ in ] packetLength The length of the data in buffer.
\param[ in ] currentTime The current time.
\param[ in ] lastPacket Determines whether or not this is the last packet of this session.
*/
extern void clxUdpIperfClientSession_generateUdpPacket(struct ClxUdpIperfClientSession* handle, u1* buffer, u4 packetLength, struct ClxTimeval* currentTime, boolean lastPacket);


/**
Reports to the session that data has been sent. This function MUST be called after transmission of each UDP packet. 

\param[ in ] handle Handle of the session object.
\param[ in ] dataLength The length of data sent.
\param[ in ] currentTime The current time.

\return The amount of time, in milliseconds, to wait before trying to send the next UDP packet.
*/
extern u4 clxUdpIperfClientSession_dataSent(struct ClxUdpIperfClientSession* handle, u4 dataLength, struct ClxTimeval* currentTime);


/**
Creates an instance of UDP Iperf Server Session module. The module manages the Iperf server-side sessions and generates reports.

\param[ in ] localAddress The local address. This is only used in the reports.
\param[ in ] interval The interval (in ms) in which the report has to be generated and displayed.

\return Handle of the created module instance.
*/
extern struct ClxUdpIperfServerSession* clxUdpIperfServerSession_Create(const ClxSocketAddressContainer* localAddress, u2 interval);

/**
Destroys a instance of UDP Iperf Server Session module.

\param[ in ] handle Handle of the module instance to be destroyed.
*/
extern void clxUdpIperfServerSession_Destroy(struct ClxUdpIperfServerSession* handle);

/**
Called by the UDP Iperf server logic for each UDP packet received.

\param[ in ] handle Handle of the UDP Iperf Session Manager module.
\param[ in ] data Pointer to the the beginning of the Iperf payload in the UDP packet (e.g. exlusing IP and UDP headers).
\param[ in ] dataLength Length of the IPerf payload (e.g. exlusing IP and UDP headers).
\param[ in ] remoteAddress The address of the remote client. This is only used in the reports. 

\return TRUE if the session is ongoing. FALSE if this was the last packet of the session.
*/
extern boolean clxUdpIperfServerSession_processUdpPacket(struct ClxUdpIperfServerSession* handle, const u1* data, u4 dataLength, const ClxSocketAddressContainer* remoteAddress);


#ifdef __cplusplus
}
#endif

#endif    // ClxIperfSession_h
