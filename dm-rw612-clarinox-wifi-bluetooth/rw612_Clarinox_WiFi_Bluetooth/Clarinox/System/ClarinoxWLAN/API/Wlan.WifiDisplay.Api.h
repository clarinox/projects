#ifndef WLAN_WIFI_DISPLAY_API_h
#define WLAN_WIFI_DISPLAY_API_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                Wlan.WifiDisaplay.Api.h
* Description         ClarinoxWlan WIFI Display (WFD) API functions
*
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


#define CLX_WLAN_WFD_SUBELEMENT_DEVICE_INFO                 0
#define CLX_WLAN_WFD_SUBELEMENT_ASSOCIATED_BSSID            1
#define CLX_WLAN_WFD_SUBELEMENT_AUDIO_FORMATS               2
#define CLX_WLAN_WFD_SUBELEMENT_VIDEO_FORMATS               3
#define CLX_WLAN_WFD_SUBELEMENT_3D_VIDEO_FORMATS            4
#define CLX_WLAN_WFD_SUBELEMENT_CONTENT_PROTECTION          5
#define CLX_WLAN_WFD_SUBELEMENT_COUPLED_SINK                6
#define CLX_WLAN_WFD_SUBELEMENT_EXT_CAPAB                   7
#define CLX_WLAN_WFD_SUBELEMENT_LOCAL_IP_ADDRESS            8
#define CLX_WLAN_WFD_SUBELEMENT_SESSION_INFO                9


/**
Using WI-FI Display:

In order to set the WFD sub-elements for the local device, the following configuration parameter may be used:

name : Local_WFD_SubElement
type : ClxWlanWfdSubElement (initialize the parameter using the function #clxWlanConfigWfdSubElement)

this configuration parameter must be passed to #clxWlanSetParametersValue. The members ClxWlanWfdSubElement.id,
ClxWlanWfdSubElement.payload and ClxWlanWfdSubElement.payloadLength must be set. If it is intended to remove a sub-element
which has been added before, the member ClxWlanWfdSubElement.payload must be set to NULL, and the member 
ClxWlanWfdSubElement.payloadLengt must be set to 0.

In order to obtain a WFD sub element belonging to a peer P2P device, the following configuration parameter may be used:

name : Peer_WFD_SubElement
type : ClxWlanWfdPeerSubElement (initialize the parameter using the function #clxWlanConfigWfdPeerSubElement)

The member ClxWlanWfdPeerSubElement.peerDeviceAddress must be set to the device address of the peer device.
The member ClxWlanWfdPeerSubElement.subElement.id must be set to the ID of the WFD sub-element which is to be obtained.
The member ClxWlanWfdPeerSubElement.subElement.payload must be set to an application-provided empty buffer (of size
ClxWlanWfdPeerSubElement.subElement.payloadLength) which will contain the payload of the obtained WFD sub-element of
the peer device. If the length of the WFD sub-element payload is not known in advance, a buffer must be provided which
is big enough to accommodate the maximum size of the sub-element.

Then, the configuration parameter should be passed to the function #clxWlanGetParametersValue.
*/


/**
Represents a single sub-element in the WFD Information Element of a P2P device. This configuration parameter
may be use to set a WFD sub-element (only in case of the local device), or obtain a WFD sub-element (of any discovered P2P peer, or the local device).
*/
struct ClxWlanWfdSubElement
{
    ClxConfigParam          paramInfo;                                          /*!< To be used internally by the stack */        
    u2                      id;                                                 /*!< The ID of the WFD sub-element */ 
    u1*                     payload;                                            /*!< The payload of the WFD sub-element */ 
    ClxSize                 payloadLength;                                      /*!< The length, in bytes, of the payload of the WFD sub-element */ 
};


/**
Initializes a member of parentList with the given object of type #ClxWlanWfdSubElement.
*/
void clxWlanConfigWfdSubElement(ClxWlanWfdSubElement* object,
                                const s1* paramName,
                                u2 id,
                                u1* payload,
                                ClxSize payloadLength,
                                ClxConfigList* parentList);




struct ClxWlanWfdPeerSubElement
{
    ClxConfigParam          paramInfo;                                          /*!< To be used internally by the stack */ 
    u1                      peerDeviceAddress[CLX_MAC_ADDRESS_LENGTH];                /*!< The device address of the peer. The WFD sub-element will extracted for this device.
                                                                                     It could be any device which has been discovered in the latest discovery procedure,
                                                                                     the group owner of the group which the local device has joined, or any member of the group
                                                                                     which the local device has joined. Do not use this structure for the local device */
    ClxWlanWfdSubElement    subElement;                                         /*!< Details of the WFD sub-element to be extracted from the peer device WFD Information Element */
};


/**
Initializes a member of parentList with the given object of type #ClxWlanWfdSubElement.
*/
void clxWlanConfigWfdPeerSubElement(ClxWlanWfdPeerSubElement* object,
                                    const s1* paramName,
                                    const u1* peerDeviceAddress,
                                    u2 id,
                                    u1* payload,
                                    ClxSize payloadLength,
                                    ClxConfigList* parentList);


CLX_DEFINE_CONFIG_TYPE(ClxWlanWfdSubElement);
CLX_DEFINE_CONFIG_TYPE(ClxWlanWfdPeerSubElement);


#ifdef __cplusplus
}
#endif


#endif // WLAN_WIFI_DISPLAY_API_h
