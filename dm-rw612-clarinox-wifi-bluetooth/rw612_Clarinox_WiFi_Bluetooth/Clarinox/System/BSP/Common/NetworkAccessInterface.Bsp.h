#ifndef NetworkAccessInterface_Bsp_h
#define NetworkAccessInterface_Bsp_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                NetworkAccessInterface.Bsp.h
* Description         Defines Network Access Interface
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/




#define CLX_NETWORK_PACKET_FRAGMENT_TYPE_NULL					                                0x00        /*!< The object does not contain any valid data (it is a free buffer descriptor */
#define CLX_NETWORK_PACKET_FRAGMENT_TYPE_COMPLETE				                                0x01        /*!< The object contains a complete network packet */
#define CLX_NETWORK_PACKET_FRAGMENT_TYPE_START					                                0x02        /*!< The object contains the beginning of a network packet. The rest of the packet is chained to this object */
#define CLX_NETWORK_PACKET_FRAGMENT_TYPE_CONTINUE				                                0x03        /*!< The object contains a part of a network packet which is not the first or last part of the packet. The rest of the packet is chained to this object */
#define CLX_NETWORK_PACKET_FRAGMENT_TYPE_END					                                0x04        /*!< The object contains the last part of a network packet */

#define CLX_NETWORK_HEADER_TYPE_ETHERNET						                                0x00        /*!< 14-Byte Ethernet V2 header */
#define CLX_NETWORK_HEADER_TYPE_IPV4							                                0x01        /*!< IPv4 header */
#define CLX_NETWORK_HEADER_TYPE_IPV6							                                0x02        /*!< Uncompressed IPv6 header */


#define CLX_NETWORK_ACCESS_INTERFACE_STATUS_RUNNING                                             0x0001      /*!< The interface has started and running */
#define CLX_NETWORK_ACCESS_INTERFACE_STATUS_LINK_UP                                             0x0002      /*!< Link is Up (There is at least one link over which packets may be send and received) */
#define CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_RX_PACKETS                                  0x0004      /*!< There is one or more received packets pending to be delivered to the network interface */
#define CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_COMPLETED_TX_BUFFERS                        0x0008      /*!< There is one or more TX buffers which are completed and pending to be released back to the network interface */
#define CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_MESSAGES                                    0x0010      /*!< There is one or more indication (message) pending to be delivered to the network interface */



#define CLX_DESC_HEAD_ROOM(desc)                                                                ( (size_t)(desc).data - (size_t)(desc).bufferAddr )
#define CLX_DESC_TAIL_ROOM(desc)                                                                ( CLX_DESC_HEAD_ROOM(desc) + (desc).dataLength - (desc).bufferSize )


#define CLX_VERIFY_DESC_DATA_ALIGNMENT(desc, size)                                              FAST_PATH_ASSERT( ( (size_t)(desc).data & (size - 1) ) == 0 )


#define CLX_DESC_SANITY_CHECK(desc)                                                             \
    FAST_PATH_ASSERT(((desc).data != NULL) && ((desc).bufferAddr != NULL));                     \
    FAST_PATH_ASSERT((size_t)(desc).data >= (size_t)(desc).bufferAddr);                         \
    FAST_PATH_ASSERT((CLX_DESC_HEAD_ROOM(desc) + (desc).dataLength) <= (desc).bufferSize)
    

#define CLX_NUMBER_OF_ETHERNET_SERVICE_CLASSES                                                  8



/**
The indication CLX_NETWORK_ACCESS_INTERFACE_INDICATION_NEW_LINK is received by the network interface implementation when a new data link is available. 
Devices which are in the ClxNetworkDeviceRoleEnum_Client role generally have only one link. However, devices which are in ClxNetworkDeviceRoleEnum_Client,
or ClxNetworkDeviceRoleEnum_GroupOwner role may have multiple roles (e.g. one per available remote client, and one for multicast).

The indication object is of type #ClxNetworkInterfaceIndication_NewLink.
*/
#define CLX_NETWORK_ACCESS_INTERFACE_INDICATION_NEW_LINK                    0x0005


/**
The indication CLX_NETWORK_ACCESS_INTERFACE_INDICATION_LINK_DISCONNECTED is received by the network interface implementation when a data link has become unavailable. 

The indication object is of type #ClxNetworkInterfaceIndication_LinkDisconnected.
*/
#define CLX_NETWORK_ACCESS_INTERFACE_INDICATION_LINK_DISCONNECTED           0x0006


/**
The indication CLX_NETWORK_ACCESS_INTERFACE_INDICATION_LINK_STATUS_UPDATED is received by the network interface implementation when the link status has changed.

The indication object is of type #ClxNetworkInterfaceIndication_LinkStatusUpdated.
*/
#define CLX_NETWORK_ACCESS_INTERFACE_INDICATION_LINK_STATUS_UPDATED         0x0007


/**
The indication CLX_NETWORK_ACCESS_INTERFACE_INDICATION_STARTED is received by the network interface implementation when the interface has started.
This indication is sent right after the start() method of the network interface implementation has returned.

The indication object is of type #ClxNetworkInterfaceIndication.
*/
#define CLX_NETWORK_ACCESS_INTERFACE_INDICATION_STARTED                     0x0008


/**
The indication CLX_NETWORK_ACCESS_INTERFACE_INDICATION_STOPPED is received by the network interface implementation when the interface has stopped.
This indication is sent right before the stop() method of the network interface implementation is called.

The indication object is of type #ClxNetworkInterfaceIndication.
*/
#define CLX_NETWORK_ACCESS_INTERFACE_INDICATION_STOPPED                     0x0009


#define CLX_NETWORK_ADDRESS_MAX_SIZE                                        16    /*!< Maximum size of network addresses supported */



#ifdef __cplusplus
extern "C" {
#endif

    /**
    Handle to the network transport module. The network transport may be WLAN, Bluetooth (PAN), Bluetooth Low Energy (IPSP), ...
    */
    struct ClxNetworkTransportHandle;
    
    /**
    Network Access BSP Interface. 
    */
    struct ClxNetworkAccessInterface;
    
  
    /**
    Enumerates network address types.
    */
    typedef enum ClxNetworkAddressTypeEnum
    {
        ClxNetworkAddressType_IPv4 = 0,                     /*!< 32 bit IPv4 address */
        ClxNetworkAddressType_IPv6 = 1,                     /*!< 128 bit IPv6 address */
        ClxNetworkAddressType_EUI64 = 2,                    /*!< 64 bit EUI address */
        ClxNetworkAddressType_IEEE80215_SHORT = 3,          /*!< 16 bit short address used in IEEE802.15 networks */
        ClxNetworkAddressType_MAC = 4                       /*!< 48 bit IEEE physical address */
    } ClxNetworkAddressType;


    /**
    Enumerates data link types.
    */
    typedef enum ClxNetworkLinkTypeEnum
    {
        ClxNetworkLinkType_Node2Router = 0,                 /*!< The local machine is a client node; The remote end of the link is a router */
        ClxNetworkLinkType_Router2Node = 1,                 /*!< The local machine is a router; The remote end of the link is a client node */
        ClxNetworkLinkType_Node2Node = 2,                   /*!< A peer to peer link between the local machine and a single remote network machine */
        ClxNetworkLinkType_Multicast = 3,                   /*!< The link is used to send multicast packets to the network */
        ClxNetworkLinkType_VendorSpecific = 4,              /*!< A vendor-specific link */
        ClxNetworkLinkType_LocalBridge = 5                  /*!< A bridge between two local network interfaces */
    } ClxNetworkLinkType;


    /**
    Enumerates network interface roles.
    */
    typedef enum ClxNetworkDeviceRoleEnum
    {
        ClxNetworkDeviceRoleEnum_Client = 0,                /*!< The virtual network interface is a client node */
        ClxNetworkDeviceRoleEnum_Router = 1,                /*!< The virtual network interface is a router */
        ClxNetworkDeviceRoleEnum_GroupOwner = 2,            /*!< The virtual network interface is a master (owner) of a group of client nodes */
        ClxNetworkDeviceRoleEnum_VendorSpecific = 3         /*!< The virtual network interface has a vendor-specific role */
    } ClxNetworkDeviceRole;


    /**
    Enumerates Ethernet Class Of Service (COS) values.
    */
    typedef enum ClxEthernetCoSEnum
    {
	    ClxEthernetCoS_Background = 1,                      /*!< Lowest Priority */			
	    ClxEthernetCoS_Spare = 2,
	    ClxEthernetCoS_BestEffort = 0,
	    ClxEthernetCoS_ExcellentEffort = 3,
	    ClxEthernetCoS_ControlledLoad = 4,
	    ClxEthernetCoS_Video = 5,
	    ClxEthernetCoS_Voice = 6,
	    ClxEthernetCoS_NetworkControl = 7                   /*!< Highest Priority */	
    } ClxEthernetCoS;


    /**
    Represents a network address. 
    An object of type ClxNetworkAddress is able to store a network address of maximum CLX_NETWORK_ADDRESS_MAX_SIZE bytes long.
    */
    typedef struct ClxNetworkAddressStruct
    {
        u4                      value[CLX_NETWORK_ADDRESS_MAX_SIZE/4];  /*!< The address value */
        ClxNetworkAddressType   type;                                   /*!< Type of the address stored in this object. The type also determines the size of the address */
    } ClxNetworkAddress;


    /**
    Encodes an address object of type ClxNetworkAddress into a memory buffer. The output will have the standard (network) byte order.

    \param[ in ] address The address object
    \param[ out ] out A caller-provided buffer which, on return, will hold the address in byte-stream format. The size of the buffer is determined
    by the type of the address.
    */
    extern void clxNetworkAddressEncode(const ClxNetworkAddress* address, u1* out);
    
    /**
    Decodes an address object of type #ClxNetworkAddress from a byte stream. The input (the byte stream) is assumed to have the standard (network) byte order.

    \param[ out ] address The address object which, on return, will hold the address. address->type SHALL be set to the type of the input address.
    \param[ in ] in A caller-provided buffer which holds the address in byte-stream format. The size of the buffer is determined
    by the type of the address.
    */   
    extern void clxNetworkAddressDecode(ClxNetworkAddress* address, const u1* in);

    /**
    Copies an address object of type #ClxNetworkAddress to another object of type #ClxNetworkAddress.

    \param[ out ] out The output object.
    \param[ in ] in The input object.
    */   
    extern void clxNetworkAddressCopy(ClxNetworkAddress* out, const ClxNetworkAddress* in);

    /**
    Determines if two objects of type #ClxNetworkAddress carry same addresses. 
    In order for two addresses to be equal, both the address type and the address value must be same.

    \param[ in ] arg1 The first input object.
    \param[ in ] arg2 The second input object.

    \return TRUE if two addresses are equal. FALSE otherwise.
    */   
    extern boolean clxNetworkAddressIsEqual(const ClxNetworkAddress* arg1, const ClxNetworkAddress* arg2);

    /**
    Sets an object of type #ClxNetworkAddress to the broadcast address of the specified address type. 

    \param[ out ] address The caller-provided address object. address->type SHALL be set to the desired address type.
    */   
	extern void clxNetworkAddressSetToBroadcast(ClxNetworkAddress* address);

    /**
    Extracts the source address a network packet from its header. 
    
    \param[ in ] data A pointer to the packet data. The packet must contain a header.
    \param[ in ] dataLength The total size of the packet, including the header.
    \param[ in ] headerType Type of the header at the beginning of the packet. The following values are supported:
        - #CLX_NETWORK_HEADER_TYPE_ETHERNET
        - #CLX_NETWORK_HEADER_TYPE_IPV4	
        - #CLX_NETWORK_HEADER_TYPE_IPV6	
    \param[ out ] out A caller-provided object of type #ClxNetworkAddress which on a successful return will carry the source address of the packet. The type of the address
    will be determined by \p headerType.
    
    \return TRUE if the operation was successful. FALSE otherwise.
    */
    extern boolean clxNetworkAddressGetSourceAddress(const u1* data, u4 dataLength, u1 headerType, ClxNetworkAddress* out);

    /**
    Extracts the destination address a network packet from its header. 
    
    \param[ in ] data A pointer to the packet data. The packet must contain a header.
    \param[ in ] dataLength The total size of the packet, including the header.
    \param[ in ] headerType Type of the header at the beginning of the packet. The following values are supported:
        - #CLX_NETWORK_HEADER_TYPE_ETHERNET
        - #CLX_NETWORK_HEADER_TYPE_IPV4	
        - #CLX_NETWORK_HEADER_TYPE_IPV6	
    \param[ out ] out A caller-provided object of type #ClxNetworkAddress which on a successful return will carry the destination address of the packet. The type of the address
    will be determined by \p headerType.
    
    \return TRUE if the operation was successful. FALSE otherwise.
    */
    extern boolean clxNetworkAddressGetDestinationAddress(const u1* data, u4 dataLength, u1 headerType, ClxNetworkAddress* out);



    /**
    Base type for all indications
    */
    typedef struct ClxNetworkInterfaceIndicationStruct
    {
        u2                      indicationID;       /*!< The indication ID, which determines the runtime type of this object */
    } ClxNetworkInterfaceIndication;


	/**
	Base type for all commands.
	*/
    typedef ClxA2lDispCommandArgs ClxNetworkInterfaceCommand;


    /**
    Object type for the indication #CLX_NETWORK_ACCESS_INTERFACE_INDICATION_NEW_LINK
    */
    typedef struct ClxNetworkInterfaceIndication_NewLinkStruct
    {
        ClxNetworkInterfaceIndication base;         /*!< SHALL be the first member */

        ClxNetworkAddress          destPhysicalAddress;           /*!< MAC address of the client associated to the local AccessPoint or P2P GO */
        ClxNetworkLinkType         linkType;
        u2                         linkID;                       /*!< The numeric unique ID the client associated to the local AccessPoint or P2P GO (assigned by ClarinoxWLAN) */
    }  ClxNetworkInterfaceIndication_NewLink;


    /**
    Object type for the indication #CLX_NETWORK_ACCESS_INTERFACE_INDICATION_LINK_DISCONNECTED
    */
    typedef struct ClxNetworkInterfaceIndication_LinkDisconnectedStruct
    {
        ClxNetworkInterfaceIndication base;         /*!< SHALL be the first member */

        ClxNetworkAddress          destPhysicalAddress;           /*!< MAC address of the client associated to the local AccessPoint or P2P GO */
        ClxNetworkLinkType         linkType;
        u2                         linkID;                       /*!< The numeric unique ID the client associated to the local AccessPoint or P2P GO (assigned by ClarinoxWLAN) */
    }  ClxNetworkInterfaceIndication_LinkDisconnected;



    /**
    Enumerates the possible link status of a network interface
    */
    typedef enum ClxNetworkAccessInterfaceLinkStatusEnum
    {
        ClxNetworkAccessInterfaceLinkStatus_Down = 0x0,     /*!< There are no links */
        ClxNetworkAccessInterfaceLinkStatus_Up = 0x01       /*!< There is at least one link over which packets may be send and received */
    } ClxNetworkAccessInterfaceLinkStatus;


    /**
    Object type for the indication #CLX_NETWORK_ACCESS_INTERFACE_INDICATION_LINK_STATUS_UPDATED
    */
    typedef struct ClxNetworkInterfaceIndication_LinkStatusUpdatedStruct
    {
        ClxNetworkInterfaceIndication           base;         /*!< SHALL be the first member */

        ClxNetworkAccessInterfaceLinkStatus     newStatus;    /* New status of the interface */
    }  ClxNetworkInterfaceIndication_LinkStatusUpdated;


    /**
    Network buffer descriptor. An object describes a single contiguous buffer which is used to carry network data.
    */
    typedef struct ClxNetworkBufferDescriptorStruct
    {
        u1                                          signature;              /*!< Initialized by the transport layer. SHALL NOT be modified by the network interface implementation */
        u1                                          fragmentType;           /*!< The type of the fragment of the data packet stored in this buffer */

        /** 
        header members shall be set if this is the first fragment of a network packet 
        (e.g. when fragmentType is either #CLX_NETWORK_PACKET_FRAGMENT_TYPE_COMPLETE or #CLX_NETWORK_PACKET_FRAGMENT_TYPE_START).
        Otherwise, it shall be ignored. 
        */
        struct Header
        {
            u2             totalPacketLength;       /*!< Total length of this packet */
            ClxEthernetCoS classOfService;          /*!< Class of Service (COS) to which the packet belongs */
        } header;
        
        /**
         Buffer Layout
        ---------------  <--- bufferAddr
        |     ...     |
        |             |  <--- data (bufferAddr + CLX_DESC_HEAD_ROOM)
        |     ...     |
        |             |  <--- data + dataLength
        |     ...     |
        ---------------  <--- bufferAddr + bufferSize (data + dataLength + CLX_DESC_TAIL_ROOM)
        */

        u1*                                         bufferAddr;            /*!< Address of the buffer */
        u1*                                         data;                  /*!< Pointer to the beginning of data currently stored in the buffer */

        u2                                          bufferSize;            /*!< Size of the buffer in bytes */

        u2                                          dataLength;            /*!< Length of the data currently stored in this buffer */                                    

        void*                                       userData;              /*!< User data. Optionally may be used by the user */
        struct ClxNetworkBufferDescriptorStruct*    next;                  /*!< Pointer to the next buffer in the buffer chain */
    } ClxNetworkBufferDescriptor;



    /**
    Represents a linked-list-based chain of objects of type #ClxNetworkBufferDescriptor.
    The chain may contain a single network packet or multiple network packets (chained sequentially).
    */
    typedef struct ClxNetworkBufferDescriptorChainStruct
    {
        ClxNetworkBufferDescriptor* first;                              /*!< First descriptor in the chain */
        ClxNetworkBufferDescriptor* current;                            /*!< Last descriptor in the chain */
    } ClxNetworkBufferDescriptorChain;


    /**
    Represents a chain of type #ClxNetworkBufferDescriptor. The chain carries ONE single network packet only.
    multiple packets SHALL not be chained together in an object of type #ClxNetworkPacket.
    */
    typedef ClxNetworkBufferDescriptorChain ClxNetworkPacket;

    /**
    Initializes an object of type #ClxNetworkBufferDescriptorChain. An object must NOT be used before it is initialized by a call to this function.

    \param[ in ] list Object to be initialized.
    */
    extern void                         clxNetworkBufferDescriptorChainInit				(ClxNetworkBufferDescriptorChain* list);
    

    /**
    Pushes a single descriptor to the end of a list of type #ClxNetworkBufferDescriptorChain.

    \param[ in ] list The list to the end of which the descriptor chain is to be attached.
    \param[ in ] descriptor The descriptor to be attached to the end of the list. This argument CANNOT be NULL. Also, descriptor->next MUST be NULL.
    */
    extern void                         clxNetworkBufferDescriptorChainPushSingle       (ClxNetworkBufferDescriptorChain* list, ClxNetworkBufferDescriptor* descriptor);

    /**
    Pushes a chain of descriptors to the end of a list of type #ClxNetworkBufferDescriptorChain.

    \param[ in ] list The list to the end of which the descriptor chain is to be attached.
    \param[ in ] descriptorChain A chain of one or more descriptors to be attached to the end of the list.
    */
    extern void                         clxNetworkBufferDescriptorChainPushAll			(ClxNetworkBufferDescriptorChain* list, ClxNetworkBufferDescriptor* descriptorChain);

    /**
    Appends a list of type #ClxNetworkBufferDescriptorChain to the end of another list. The source list object will NOT be modified.

    \param[ in ] list1 The list to the end of which the items of the source list are to be attached.
    \param[ in ] list2 The source list, items of which are to be attached to the list1. This list will not be modified.
    */
    extern void                         clxNetworkBufferDescriptorChainAppend			(ClxNetworkBufferDescriptorChain* list1, const ClxNetworkBufferDescriptorChain* list2);

    /**
    Appends a list of type #ClxNetworkBufferDescriptorChain to the end of another list. The source list object will then be emptied.

    \param[ in ] list1 The list to the end of which the items of the source list are to be attached.
    \param[ in ] list2 The source list, items of which are to be attached to the list1. This list will be emptied (will contain no items) afterwards.
    */
    extern void                         clxNetworkBufferDescriptorChainAppendAndReset	(ClxNetworkBufferDescriptorChain* list1, ClxNetworkBufferDescriptorChain* list2);

    /**
    Extracts one object of type #ClxNetworkBufferDescriptor from the beginning of a list of type #ClxNetworkBufferDescriptorChain.

    \param[ in ] list The list from the beginning of which a descriptor is to be extracted.

    \return The first descriptor object of the list which has been extracted and free (it is not in the list any more). NULL if the list is empty.
    */
    extern ClxNetworkBufferDescriptor*  clxNetworkBufferDescriptorChainPopFirst			(ClxNetworkBufferDescriptorChain* list);

    /**
    Extracts all items of a list of type #ClxNetworkBufferDescriptorChain. Afterwards, the list will be empty.

    \param[ in ] list The list, all items of which are to be extracted.

    \return The items of the list as a chain of descriptor objects. NULL if the list is empty.
    */
    extern ClxNetworkBufferDescriptor*  clxNetworkBufferDescriptorChainPopAll			(ClxNetworkBufferDescriptorChain* list);

    /**
    Extracts A complete network packet from the beginning of a list of type #ClxNetworkBufferDescriptorChain. The packet will be returned as a chain of all parts of the packet.

    \param[ in ] list The list, the first network packet of which is to be extracted. 
    \param[ out] packet A chain of one or more descriptors which contain a complete network packet. 

    \return A chain of one or more descriptors which contain a complete network packet. NULL if the list is empty or does not contain a complete packet.
    */
    extern boolean                      clxNetworkBufferPopPacket                       (_in_ ClxNetworkBufferDescriptorChain* list, _out_ ClxNetworkPacket* packet);

    

    /**
    Prototype for the indication handler function of the network interface. A pointer to the implementation is passed to #clxNetworkInterfaceHandleIndication.
    */
    typedef void (*ClxNetworkAccessInterfaceIndicationHandler) (_in_ struct ClxNetworkAccessInterface* thisObj, 
                                                                _in_ const ClxNetworkInterfaceIndication* indication);


    /**
    Generic Network Access Interface
    */
    typedef struct ClxNetworkAccessInterface
    {
        void* userData;

        void (*init) (_in_ struct ClxNetworkAccessInterface*     thisObj);
        void (*destroy) (_in_ struct ClxNetworkAccessInterface*  thisObj);


        /**
        Starts the network interface in a specific role. When this function is called, the interface is in Started state. 
        This means that the implementation of network interface is able to call any API function defined in this file. 

        If any error occurs, an implementation must return an error (any value other than CLX_SUCCESS).

        NOTE : if this function succeeds, the link is still down. The link should be considered up only when the indication #ClxNetworkInterfaceIndication_LinkStatusUpdated
        is received with the new status set to #ClxNetworkAccessInterfaceLinkStatus_Up.

        \param[ in ] thisObj A pointer to this object.
        \param[ in ] transportHandle The transport handle for this network interface. This handle must be passed to all API functions declared in this file.
        \param[ in ] localPhysicalAddress The local physical address assigned to this interface.
        \param[ in ] localDeviceRole The device role assigned to this interface.
        \param[ in ] configList An optional list of configuration parameters which may be used to correctly initialize the interface. The configuration parameters
        which may be passed to this function are specific to the interface type, the stack and the application.

        \return CLX_SUCCESS if the procedure has been successful. In this case, the interface is started.
        Any other value indicates an error.
        */
        ClxResult (*start) (_in_ struct ClxNetworkAccessInterface*    thisObj,
                            _in_ struct ClxNetworkTransportHandle*    transportHandle,
                            _in_ const ClxNetworkAddress*             localPhysicalAddress,
                            _in_ ClxNetworkDeviceRole                 localDeviceRole,
                            _in_ const ClxConfigList*                 configList);


        /**
        Stops the network interface. When this function RETURNS, the interface will be in Stopped state.
        This means that after this function returns, none of API function defined in this file may be called.

        \param[ in ] thisObj A pointer to this object.
        */
        void (*stop) (_in_ struct ClxNetworkAccessInterface* thisObj);


        /**
        This function is called when there is an indication pending. An indication has the base type #ClxNetworkInterfaceIndication.
        The indicationID member of #ClxNetworkInterfaceIndication determines the actual type of the indication. Based on indicationID, the indication object
        can be cast to the correct type (if there is a special structure defined for that indication) and the other members of the indication can be accessed.

        This function is called only if the new indication is the very first indication in the queue. For subsequent indications, this function will not be called.
        The interface shall call the API function #clxNetworkInterfaceHandleIndication in order to get the actual indications and its members.

        \param[ in ] thisObj A pointer to this object.
        */
        void  (*indicationPending) (_in_ struct ClxNetworkAccessInterface* thisObj);


        /**
        Called when the status bitmap variable is about to be accessed (read or modified) by the transport layer in order to lock access to the status variable. 
        An implementation SHALL be mutual exclusion lock (e.g. a Mutex). In other words, when access to the status variable is locked,
        no other context shall be able to access the variable until access to the status is unlocked.
    
        NOTE : this lock SHALL be acquired before #clxNetworkInterfaceGetCurrentStatus is called.

        \param[ in ] thisObj A pointer to this object.
        */
        void (*lockStatus) (_in_ struct ClxNetworkAccessInterface* thisObj);

        /**
        Called by the transport layer in order to unlock access to the status variable. This is called only when access has already been locked (by a previous call to lockStatus).
        When this function returns, access to the status variable will not be protected from multi-thread access any longer.

        \param[ in ] thisObj A pointer to this object.
        */
        void (*unlockStatus) (_in_ struct ClxNetworkAccessInterface* thisObj);

        /**
        Called when there are one or more packets received from the stack. The interface must use 
        #clxNetworkInterfaceGetPendingRxPacket() function to retrieve the packets. The interface must be in enabled
        state when this function is called.
      
        \param[ in ] thisObj A pointer to this object.
        */
        void (*rxPacketsPending) (_in_ struct ClxNetworkAccessInterface* thisObj);

        /**
        Called when the stack requires a free RX buffer and no free RX buffer is available to the stack at this moment.

        \param[ in ] thisObj A pointer to this object.

        \return If the interface has a free RX buffer, it should return a pointer to it. Otherwise, it SHALL return NULL.
        */
        ClxNetworkBufferDescriptor* (*getFreeRxBuffer) (_in_ struct ClxNetworkAccessInterface* thisObj, u2 requiredSize);

        /**
        Called when one or more TX buffers are released and can be reused for other TX packets.
        The interface must call #clxNetworkInterfaceGetReleasedTxBuffers() function to retrieve the released TX buffers.
        The interface must be in enabled state when this function is called.

        \param[ in ] thisObj A pointer to this object.
        */
        void  (*txBuffersComplete) (_in_ struct ClxNetworkAccessInterface* thisObj);
    } ClxNetworkAccessInterface;


    /**
    Returns the current status variable for the network interface. The status variable is a bitmap flag which determines the actions which need to be taken
    by the interface implementation.

    The return value will be an OR-ed combination of the following bits:

        - #CLX_NETWORK_ACCESS_INTERFACE_STATUS_RUNNING
        - #CLX_NETWORK_ACCESS_INTERFACE_STATUS_LINK_UP                    
        - #CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_RX_PACKETS           
        - #CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_COMPLETED_TX_BUFFERS 
        - #CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_MESSAGES              

    NOTE : When this function is called, access to the status variable SHALL already have been locked.

    \param[ in ] transport The transport handle as passed to start method of the interface.
    */
    extern u2 clxNetworkInterfaceGetCurrentStatus(_in_ struct ClxNetworkTransportHandle* transport);

    /**
    Queues a TX packet into the stack. This function will not send the packet to the network. The function #clxNetworkInterfaceFlushPendingTxPackets must be called 
    in order to send all pending TX packets.

    \param[ in ] transport The transport handle as passed to start method of the interface.
    \param[ in ] packet The TX packet to be queued.
    */
    extern void clxNetworkInterfaceQueueTxPacket (_in_ struct ClxNetworkTransportHandle*   transport,
                                                  _in_ const ClxNetworkPacket*             packet);


    /**
    Sends all pending (queued) TX packets to the network. An implementation must call this function frequently 
    in order to make sure the packets will be sent to the network. When the packets are sent to the network
    (either with success or in error), the TX buffers will be released and accessible by a call to #clxNetworkInterfaceGetReleasedTxBuffers() function.
    
    \param[ in ] transport The transport handle as passed to start method of the interface.
    */
    extern boolean clxNetworkInterfaceFlushPendingTxPackets (_in_ struct ClxNetworkTransportHandle* transport);

    /**
    Retrieves one pending RX packet. This function shall be called when the bit #CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_RX_PACKETS is set
    in the interface status bitmap.


    \param[ in ] transport The transport handle as passed to start method of the interface.
    \param[ out ] packet A caller-provided object of type #ClxNetworkPacket which, on a successful return, will hold the received packet as a chain of one or more buffers.

    \return TRUE if a RX packet has been returned.
    FALSE if there is no RX packet pending.
    */
    extern boolean clxNetworkInterfaceGetPendingRxPacket (_in_ struct ClxNetworkTransportHandle* transport, _out_ ClxNetworkPacket* packet);

    /**
    Retrieves all pending RX packets as a chain of ClxNetworkBufferDescriptor objects. If there is no pending RX packet, this function will return NULL.

    \param[ in ] transport The transport handle as passed to start method of the interface.

    \return The chain of pending RX packets. NULL if there is no pending RX packet. 
    */
    extern ClxNetworkBufferDescriptor* clxNetworkInterfaceGetPendingRxPackets (_in_ struct ClxNetworkTransportHandle* transport);

    /**
    Releases free TX buffers. This function shall be called when the bit #CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_COMPLETED_TX_BUFFERS is set
    in the interface status bitmap.


    \param[ in ] transport The transport handle as passed to start method of the interface.

    \return The chain of all released TX buffers. Will be NULL if there is no released TX buffer pending.
    */
    extern ClxNetworkBufferDescriptor* clxNetworkInterfaceGetReleasedTxBuffers (_in_ struct ClxNetworkTransportHandle* transport);


    /**
    Handle a single pending indication. This function shall be called when the bit #CLX_NETWORK_ACCESS_INTERFACE_STATUS_PENDING_MESSAGES is set
    in the interface status bitmap.


    \param[ in ] transport The transport handle as passed to start method of the interface.
    \param[ in ] handler A caller-provided handler function which will be called to handle the indication.

    \return TRUE if an indication was handled.
    FALSE if there is no indication pending.
    */
    extern boolean clxNetworkInterfaceHandleIndication(_in_ struct ClxNetworkTransportHandle* transport,
                                                       _in_ ClxNetworkAccessInterfaceIndicationHandler handler);

    /**
    Allocates and returns an object of type #ClxNetworkBufferDescriptor. The object can be used to represent a interface-allocated buffer
    to be used for TX or RX operations.

    The returned object shall be freed, when not used any more, by a call to #clxNetworkInterfaceFreeBufferDescriptor.

    \return A stack-allocated object of type ClxNetworkBufferDescriptor. NULL if there is not enough memory to allocate a new object.
    */
    extern ClxNetworkBufferDescriptor* clxNetworkInterfaceAllocateBufferDescriptor (void);


    /**
    Frees an object of type #ClxNetworkBufferDescriptor. The object has been returned by a previous call to #clxNetworkInterfaceAllocateBufferDescriptor.

    \param[ in ] desc The descriptor object to be freed.
    */
    extern void clxNetworkInterfaceFreeBufferDescriptor (_in_ ClxNetworkBufferDescriptor* desc);


    /**
    Sends a command to the transport layer.

    \param[ in ] transport The transport handle as passed to start method of the interface.
    \param[ in ] command The command object.

    \return CLX_SUCCESS if the command was successful.
    CLX_ERROR_ANOTHER_COMMAND_IN_PROGRESS if another command of this very type has been already issued 	and is pending completion.
    CLX_ERROR_COMMAND_NOT_SUPPORTED The command is not supported for this transport.
    Any other value indicates an error in processing of the command by the transport layer. 
    */
	extern ClxResult clxNetworkInterfaceIssueCommand(_in_ struct ClxNetworkTransportHandle*  transport,
													 _inout_ ClxNetworkInterfaceCommand* command);


    /**
    Creates and returns a NULL network access interface (e.g. an implementation of ClxNetworkAccessInterface which does nothing).
    This may be used during the development phase for testing purposes.
    */
    extern struct ClxNetworkAccessInterface* clxCreateNullNetworkAccessInterface();

    /**
    Returns the device role of the network interface. The return value will be the same as the value passed to ClxNetworkAccessInterface.start()

    \param[ in ] transport The transport handle as passed to start method of the interface.
    */
    extern ClxNetworkDeviceRole clxGetNetworkInterfaceRole(_in_ struct ClxNetworkTransportHandle* transport);


#ifdef __cplusplus
}
#endif

#endif  // NetworkAccessInterface_Bsp_h

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
/* Message       : A project should not contain unused type declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.3                                      */ 
/* Justification : Unused type declarations are to be used in user 		      */
/* 				   applications.      										  */
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
/* Message       : A project should not contain unused macro declarations 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/
