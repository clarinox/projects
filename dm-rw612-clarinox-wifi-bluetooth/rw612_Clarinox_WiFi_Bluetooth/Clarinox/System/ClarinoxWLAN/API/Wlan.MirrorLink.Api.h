#ifndef MirrorLink_API_h
#define MirrorLink_API_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                Wlan.MirrorLink.Api.h
* Description         ClarinoxWlan MirrorLink (CCC) API functions
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

/**
Using Mirror Link:

In order to set the CCC sub-elements for the local device, the following configuration parameter may be used:

name : Local_CCC_SubElement
type : ClxWlanCccSubElement (initialize the parameter using the function #clxWlanConfigCccSubElement)

this configuration parameter must be passed to #clxWlanSetParametersValue. The members ClxWlanCccSubElement.id,
ClxWlanCccSubElement.payload and ClxWlanCccSubElement.payloadLength must be set. If it is intended to remove a sub-element
which has been added before, the member ClxWlanCccSubElement.payload must be set to NULL, and the member 
ClxWlanCccSubElement.payloadLengt must be set to 0.

In order to obtain a CCC sub element belonging to a peer P2P device, the following configuration parameter may be used:

name : Peer_CCC_SubElement
type : ClxWlanCccPeerSubElement (initialize the parameter using the function #clxWlanConfigCccPeerSubElement)

The member ClxWlanCccPeerSubElement.peerDeviceAddress must be set to the device address of the peer device.
The member ClxWlanCccPeerSubElement.subElement.id must be set to the ID of the CCC sub-element which is to be obtained.
The member ClxWlanCccPeerSubElement.subElement.payload must be set to an application-provided empty buffer (of size
ClxWlanCccPeerSubElement.subElement.payloadLength) which will contain the payload of the obtained CCC sub-element of
the peer device. If the length of the CCC sub-element payload is not known in advance, a buffer must be provided which
is big enough to accommodate the maximum size of the sub-element.

Then, the configuration parameter should be passed to the function #clxWlanGetParametersValue.
*/

/**
Represents a single sub-element in the CCC Information Element of a P2P device. This configuration parameter
may be use to set a CCC sub-element (only in case of the local device), or obtain a CCC sub-element (of any discovered P2P peer, or the local device).
*/
struct ClxWlanCccSubElement
{
    ClxConfigParam        paramInfo;                                        /*!< To be used internally by the stack */ 
        
    u2                    id;                                               /*!< The ID of the CCC sub-element */ 
    u1*                   payload;                                          /*!< The payload of the CCC sub-element */ 
    ClxSize               payloadLength;                                    /*!< The length, in bytes, of the payload of the CCC sub-element */ 
};


/**
Initializes a member of parentList with the given object of type #ClxWlanCccSubElement.
*/
void clxWlanConfigCccSubElement(ClxWlanCccSubElement* object,
                                const s1* paramName,
                                u2 id,
                                u1* payload,
                                ClxSize payloadLength,
                                ClxConfigList* parentList);




struct ClxWlanCccPeerSubElement
{
    ClxConfigParam            paramInfo;                                    /*!< To be used internally by the stack */ 
    u1                        peerDeviceAddress[CLX_MAC_ADDRESS_LENGTH];          /*!< The device address of the peer. The CCC sub-element will extracted for this device.
                                                                                 It could be any device which has been discovered in the latest discovery procedure,
                                                                                 the group owner of the group which the local device has joined, or any member of the group
                                                                                 which the local device has joined. Do not use this structure for the local device */
    ClxWlanCccSubElement    subElement;                                     /*!< Details of the CCC sub-element to be extracted from the peer device CCC Information Element */
};


/**
Initializes a member of parentList with the given object of type #ClxWlanCccSubElement.
*/
void clxWlanConfigCccPeerSubElement(ClxWlanCccPeerSubElement* object,
                                    const s1* paramName,
                                    const u1* peerDeviceAddress,
                                    u2 id,
                                    u1* payload,
                                    ClxSize payloadLength,
                                    ClxConfigList* parentList);


CLX_DEFINE_CONFIG_TYPE(ClxWlanCccSubElement);
CLX_DEFINE_CONFIG_TYPE(ClxWlanCccPeerSubElement);


#ifdef __cplusplus
}
#endif


#endif // MirrorLink_API_h
