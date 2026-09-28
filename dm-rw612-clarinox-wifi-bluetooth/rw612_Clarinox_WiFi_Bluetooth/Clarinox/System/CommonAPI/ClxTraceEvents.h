#ifndef __ClxTraceEvents__
#define __ClxTraceEvents__

/*******************************************************************************
* 
* Project           :   Clarinox SoftFrame
* File              :   ClxTraceEvents.h
* Description       :   ClariFi Insight Events
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


/** 
List of Defined ClariFi Insight Events. 

Event IDs CLX_TRACE_MIN_EVENT_ID through CLX_TRACE_MAX_EVENT_ID may be used to define an event.

IMPORTANT : EventID 0 is invalid and CANNOT be used.

In order to avoid duplicate values, all event IDs must be listed in this file. 
NOTE : Event IDs for temporary events (e.g. project-specific or for temporary testing purposes) do not need to be listed here. 

Event Name Format:

For the sake of consistency, the name of each event should follow the following format:

#define CLX_TRACE_EVENT_<CategoryName>_<EventName>

Where <CategoryName> is the name of the event category to which the event belongs. <Event_Name> should be in upper case.
*/

#define CLX_TRACE_MIN_EVENT_ID									1			/* DO NOT MODIFY */
#define CLX_TRACE_MAX_EVENT_ID									0x3F00		/* DO NOT MODIFY */


/* Generic Events */
#define CLX_TRACE_EVENT_GENERIC_TEST							1
#define CLX_TRACE_EVENT_GENERIC_BLACKBOX						2

/* Network Interface (NET) Events: */
#define CLX_TRACE_EVENT_NET_ALLOC_TX_BUFFER						101
#define CLX_TRACE_EVENT_NET_FREE_TX_BUFFER						102
#define CLX_TRACE_EVENT_NET_TX_FRAME_STACK_TO_DRV				104
#define CLX_TRACE_EVENT_NET_TX_FRAME_AGGREGATE					105
#define CLX_TRACE_EVENT_NET_TX_FRAME_DRV_TO_HW					106
#define CLX_TRACE_EVENT_NET_TX_DATA_DRV_TO_HW					107
#define CLX_TRACE_EVENT_NET_TX_FRAME_COMPLETE					108
#define CLX_TRACE_EVENT_NET_TX_FRAME_COPY						109
#define CLX_TRACE_EVENT_NET_FLUSH_PENDING_TX_FRAMES				110
#define CLX_TRACE_EVENT_NET_FLUSH_COMPLETED_TX_FRAMES			111

#define CLX_TRACE_EVENT_NET_ALLOC_RX_BUFFER						112
#define CLX_TRACE_EVENT_NET_FREE_RX_BUFFER						113
#define CLX_TRACE_EVENT_NET_RX_FRAME_HW_TO_DRV					114
#define CLX_TRACE_EVENT_NET_RX_DATA_HW_TO_DRV					115
#define CLX_TRACE_EVENT_NET_RX_FRAME_DEAGGREGATE				116
#define CLX_TRACE_EVENT_NET_RX_FRAME_COPY						117
#define CLX_TRACE_EVENT_NET_RX_FRAME_DRV_TO_STACK				118
#define CLX_TRACE_EVENT_NET_FLUSH_PENDING_RX_FRAMES				119
#define CLX_TRACE_EVENT_NET_RX_FRAME_STACK_TO_NETIF				120

/* IPv4-related (IPV4) Events: */
#define CLX_TRACE_EVENT_IPV4_TX_FRAME							121
#define CLX_TRACE_EVENT_IPV4_RX_FRAME							122
#define CLX_TRACE_EVENT_IPV4_UDP_TX_FRAME						123
#define CLX_TRACE_EVENT_IPV4_UDP_RX_FRAME						124
#define CLX_TRACE_EVENT_IPV4_TCP_TX_FRAME						125
#define CLX_TRACE_EVENT_IPV4_TCP_RX_FRAME						126

/* ClarinoxWLAN (WLAN) Events: */
#define CLX_TRACE_EVENT_WLAN_ALLOC_MGMT_TX_FRAME				129
#define CLX_TRACE_EVENT_WLAN_ALLOC_MGMT_RX_FRAME				130
#define CLX_TRACE_EVENT_WLAN_FREE_MGMT_TX_FRAME					131
#define CLX_TRACE_EVENT_WLAN_FREE_MGMT_RX_FRAME					132


/* ClarinoxWLAN Mesh (MESH) Events: */
#define CLX_TRACE_EVENT_MESH_ALLOC_BUFFER				        133
#define CLX_TRACE_EVENT_MESH_DUPLICATE_BUFFER				    134
#define CLX_TRACE_EVENT_MESH_RELEASE_BUFFER				        135
#define CLX_TRACE_EVENT_MESH_FREE_BUFFER				        136

#define CLX_TRACE_EVENT_MESH_PROCESS_DOWNLINK_MULTICAST_FRAME	137
#define CLX_TRACE_EVENT_MESH_PROCESS_DOWNLINK_UNICAST_FRAME		138
#define CLX_TRACE_EVENT_MESH_PROCESS_UPLINK_MULTICAST_FRAME		139
#define CLX_TRACE_EVENT_MESH_PROCESS_UPLINK_UNICAST_FRAME		140
#define CLX_TRACE_EVENT_MESH_PROCESS_LOCAL_MULTICAST_FRAME		141
#define CLX_TRACE_EVENT_MESH_PROCESS_LOCAL_UNICAST_FRAME		142

/* NXP MLAN Events: */
#define CLX_TRACE_EVENT_MLAN_PCIE_IRQ							143
#define CLX_TRACE_EVENT_MLAN_PCIE_TX							144
#define CLX_TRACE_EVENT_MLAN_PCIE_RX							145
#define CLX_TRACE_EVENT_MLAN_MEM_ALLOC_TX_PBUF					146
#define CLX_TRACE_EVENT_MLAN_MEM_ALLOC_RX_PBUF					147
#define CLX_TRACE_EVENT_MLAN_MEM_MALLOC							148
#define CLX_TRACE_EVENT_MLAN_MEM_VALLOC							149
#define CLX_TRACE_EVENT_MLAN_MEM_FREE_TX_PBUF					150
#define CLX_TRACE_EVENT_MLAN_MEM_FREE_RX_PBUF					151
#define CLX_TRACE_EVENT_MLAN_MEM_MFREE							152
#define CLX_TRACE_EVENT_MLAN_MEM_VFREE							153
#define CLX_TRACE_EVENT_MLAN_TASK_IRQ_HANDLER_BEGIN				154
#define CLX_TRACE_EVENT_MLAN_TASK_IRQ_HANDLER_END				155
#define CLX_TRACE_EVENT_MLAN_TASK_DEFER_MAIN					156
#define CLX_TRACE_EVENT_MLAN_TASK_DEFER_RX						157
#define CLX_TRACE_EVENT_MLAN_TASK_MAIN_BEGIN					158
#define CLX_TRACE_EVENT_MLAN_TASK_MAIN_END						159
#define CLX_TRACE_EVENT_MLAN_TASK_RX_BEGIN						160
#define CLX_TRACE_EVENT_MLAN_TASK_RX_END						161
#define CLX_TRACE_EVENT_MLAN_PCIE_READ_REGISTER					162
#define CLX_TRACE_EVENT_MLAN_PCIE_WRITE_REGISTER				163


/* More ClarinoxWLAN (WLAN) Events: */
#define CLX_TRACE_EVENT_WLAN_ALLOC_STACK_BUFFER				    164     /* OBSOLETE */
#define CLX_TRACE_EVENT_WLAN_FREE_STACK_BUFFER					165     /* OBSOLETE */
#define CLX_TRACE_EVENT_WLAN_INC_REF_MGMT_TX_FRAME				167  
#define CLX_TRACE_EVENT_WLAN_INC_REF_MGMT_RX_FRAME				168  
#define CLX_TRACE_EVENT_WLAN_DEC_REF_MGMT_TX_FRAME			    170  
#define CLX_TRACE_EVENT_WLAN_DEC_REF_MGMT_RX_FRAME				171  


/* ClxReferenceable Events: */
#define CLX_TRACE_EVENT_POOLSET_REFERENCEABLE_BUFFER_ALLOC 		172
#define CLX_TRACE_EVENT_POOLSET_REFERENCEABLE_BUFFER_FREE		173
#define CLX_TRACE_EVENT_REFERENCEABLE_INC_REF			        174
#define CLX_TRACE_EVENT_REFERENCEABLE_DEC_REF			        175

/* TI Wilink8 Events: */
#define CLX_TRACE_EVENT_WILINK8_ROLE_ENABLE                     200
#define CLX_TRACE_EVENT_WILINK8_ROLE_DISABLE                    201
#define CLX_TRACE_EVENT_WILINK8_STA_ROLE_START                  202
#define CLX_TRACE_EVENT_WILINK8_STA_ROLE_STOP                   203
#define CLX_TRACE_EVENT_WILINK8_STA_ROLE_JOIN                   204
#define CLX_TRACE_EVENT_WILINK8_STA_ROLE_DISJOIN                205
#define CLX_TRACE_EVENT_WILINK8_AP_ROLE_START                   206
#define CLX_TRACE_EVENT_WILINK8_AP_ROLE_STOP                    207
#define CLX_TRACE_EVENT_WILINK8_AP_ADD_CLIENT                   208   
#define CLX_TRACE_EVENT_WILINK8_AP_REMOVE_CLIENT                209   
#define CLX_TRACE_EVENT_WILINK8_FW_EVENT_RECEIVED               210
#define CLX_TRACE_EVENT_WILINK8_LINK_LOSS_RECEIVED              211
#define CLX_TRACE_EVENT_WILINK8_INACTIVE_STA_RECEIVED           212
#define CLX_TRACE_EVENT_WILINK8_MAX_TX_FAILURE_RECEIVED         213
#define CLX_TRACE_EVENT_WILINK8_PEER_REMOVE_COMPLETE_RECEIVED   214
#endif  // __ClxTraceEvents__
