#ifndef WlanStackPacketCaptureInterface_h
#define WlanStackPacketCaptureInterface_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                WlanStackPacketCaptureInterface.h
* Description         Clarinox WLAN stack Packet Capture interface
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
Frame types as flag bits.
*/
#define CLX_WLAN_FRAME_TYPE_UNKNOWN                 0x00001
#define CLX_WLAN_FRAME_TYPE_CONTROL_FRAME           0x00002
#define CLX_WLAN_FRAME_TYPE_BEACON                  0x00004
#define CLX_WLAN_FRAME_TYPE_ASSOC_REQUEST           0x00008
#define CLX_WLAN_FRAME_TYPE_ASSOC_RESPONSE          0x00010
#define CLX_WLAN_FRAME_TYPE_REASSOC_REQUEST         0x00020
#define CLX_WLAN_FRAME_TYPE_REASSOC_RESPONSE        0x00040
#define CLX_WLAN_FRAME_TYPE_PROBE_REQUEST           0x00080
#define CLX_WLAN_FRAME_TYPE_PROBE_RESPONSE          0x00100
#define CLX_WLAN_FRAME_TYPE_ATIM                    0x00200
#define CLX_WLAN_FRAME_TYPE_DEASSOCIATION           0x00400
#define CLX_WLAN_FRAME_TYPE_AUTHENTICATION          0x00800
#define CLX_WLAN_FRAME_TYPE_DEAUTHENTICATION        0x01000
#define CLX_WLAN_FRAME_TYPE_ACTION                  0x02000
#define CLX_WLAN_FRAME_TYPE_DATA_EAPOL              0x04000
#define CLX_WLAN_FRAME_TYPE_DATA_ARP                0x08000
#define CLX_WLAN_FRAME_TYPE_DATA_IPv4               0x10000
#define CLX_WLAN_FRAME_TYPE_DATA_IPv6               0x20000
#define CLX_WLAN_FRAME_TYPE_DATA_UNKNOWN            0x40000


typedef enum ClxWlanCapturedPacketDirectionEnum
{
    ClxWlanCapturedPacketDirection_Tx,
    ClxWlanCapturedPacketDirection_Rx
} ClxWlanCapturedPacketDirection; 


typedef enum ClxWlanPacketStatusStruct
{
    ClxWlanPacketStatus_Success = 0,                    /*!< Successfully submitted to the driver/hardware, or successfully sent to the remote station */
    ClxWlanPacketStatus_NoLink = 1,                     /*!< No wireless link is available to send this MSDU */
    ClxWlanPacketStatus_LinkNotAuthenticated = 2,       /*!< The link is not authenticated */
    ClxWlanPacketStatus_AckFailed = 3,                  /*!< Failed due to acknowledgement failure from the destination */
    ClxWlanPacketStatus_Cancelled = 4,                  /*!< The stack cancelled sending of the TX MSDU */
    ClxWlanPacketStatus_Timeout = 5,                    /*!< Hardware-Specific or Software-Specific timeout occurred before the TX MSDU is sent or successfully acknowledged */                
    ClxWlanPacketStatus_NoResources = 6,                /*!< Dropped due to not enough resources on the driver/hardware */ 
    ClxWlanPacketStatus_HardwareError = 7,              /*!< Failed due to an unknown hardware error */
    ClxWlanPacketStatus_CRC_Failed = 8,                 /*!< CRC verification failed for the RX packet */
    ClxWlanPacketStatus_IntegrityFailed = 9,            /*!< Packet integrity test failed for the RX packet (applies to encrypted packets only) */
    ClxWlanPacketStatus_UnknownError = 10,              /*!< Unknown error occurred during transfer or reception of this packet */
    ClxWlanPacketStatus_Unsupported = 11                /*!< Transmission of the frame is not supported (e.g. for instance, transmission of control frames is not supported) */
} ClxWlanPacketStatus;


typedef struct ClxWlanCapturedPacketInfoStruct
{
    ClxWlanPacketStatus                status;
    u4                                 type;
    ClxWlanCapturedPacketDirection     direction;
    u4                                 timeStamp_s; 
    u4                                 timeStamp_us;
	const u1*						   header;
	u1								   headerLength;
}ClxWlanCapturedPacketInfo;




typedef void (*ClxWlanPacketCaptured) (ClxHandle interfaceHandle,                       /* Handle to the interface via which this packet has been sent. */
                                       void* interfaceObject,                           /* Pointer to the driver interface object (of type ClarinoxWLAN::VirtualInterface). 
                                                                                           To be used by the driver only (if this function is implemented by the driver). */
                                       const ClxWlanCapturedPacketInfo* frameInfo,      /* Information about the captured packet. */
									   const ClxNetworkBufferDescriptor* payload);      /* Array of type ClxCapturedPacketData, containing the chunks of the packet data.
                                                                                           The last element in the array is set to NULL, specifying the end of the array. */

extern ClxWlanPacketCaptured clxWlanPacketCaptured;


#ifdef __cplusplus
}
#endif


#endif    // WlanStackPacketCaptureInterface_h

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
