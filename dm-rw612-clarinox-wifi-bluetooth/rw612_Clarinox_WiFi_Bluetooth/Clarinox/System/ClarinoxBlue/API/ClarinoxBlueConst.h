#ifndef _ClarinoxBlueConst_h_
#define _ClarinoxBlueConst_h_

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                ClarinoxBlueConst.h
* Description         ClarinoxBlue Bluetooth Protocol Stack constants and types
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#include "ClarinoxConst.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
The company id is used to publish the vendor via the DeviceId profile
*/
#define BLUETOOTH_CLARINOX_COMPANY_ID                                          0x00B3

#define CLX_BLUETOOTH_ADDRESS_LENGTH                                           6  /* Bytes */

#define CLX_BLUETOOTH_DEVICE_NAME_MAX_LENGTH                                   32 /* Bytes */

#define CLX_BLUETOOTH_MAX_NUMBER_OF_CLASSIC_ACL_CONNECTIONS                    7  /* As per Bluetooth standard */

#define CLX_BLE_ADVERTISING_DATA_MAX_LENGTH                                    31 /* Bytes */

#define CLX_BLUETOOTH_INVALID_CONNECTION_HANDLE                                0xFFFF

#define CLX_BLUETOOTH_INDICATION_SCHEDULER_NAME                              "ClarinoxBlue.Indication"

#define CLX_BLUETOOTH_STACK_SCHEDULER_NAME                                   "ClarinoxBlue.Stack"

/**
An array of 5, and type u2, which maps the ClarinoxBlue platform-independent thread priorities
to underlying platform priorities. The first index (index 0) of the array represents the highest priority,
while the last index (index 4) of the array represents the lowest priority.
If the table is not defined in BSP, the default priority of the underlying platform will be used for all
threads. 

ALL priorities MUST be defined.

ClarinoxBlue threads:

- Driver thread : Uses Highest priority (index 0).
- Stack thread : Uses Medium priority (index 2).
- Application Callback thread : Uses Medium priority (index 2).
- Timer thread : Uses High priority (index 1).
- Debug thread (if available) : Uses Lowest priority (index 4).
- Console Engine thread (if available) : Uses Lowest priority (index 4).
*/
extern u2* clarinoxBluePlatformTaskPriorityTable;


/**
Defines the id associated to each paired or discovered device. It is guaranteed not to change
until stack is terminated. Assigning to an invalid value requires use of CLX_INVALID_DEVICE_ID macro
*/

typedef struct ClxDeviceIdStruct
{
    u4 msb;
    u2 lsb;
} ClxDeviceId;


extern const ClxDeviceId CLX_INVALID_DEVICE_ID;


#define CLX_IS_DEVICE_ID_VALID(deviceID)  (((deviceID.msb != CLX_INVALID_DEVICE_ID.msb) || (deviceID.lsb != CLX_INVALID_DEVICE_ID.lsb)) ? TRUE : FALSE)


/**
Defines the Input/Output capabilities of the local device. This is used for security purposes.
Applicable only to local devices supporting Simple Secure Pairing. Only one can be selected.
*/
enum ClxGapIoCapability
{
    IO_DISPLAY_ONLY         = 0,    /*!< The local device is capable of displaying a 6-digit decimal number to the user (or an equivalent alternative). */
    IO_DISPLAY_YES_NO       = 1,    /*!< The local device is capable of displaying a 6-digit decimal number to the user (or an equivalent alternative).
                                         Also, the local device provides a means for the user to indicate a YES or NO response to a request (e.g. a simple button). */
    IO_KEYBOARD_ONLY        = 2,    /*!< The local device provides a key pad which enables the user to enter a decimal number (or an equivalent alternative).
                                         But, the local device is not capable of providing the user with a 6-digit decimal number. */
    IO_NONE                 = 3,    /*!< The local device does not have any appropriate input or output capability( When selected, an authentication with high level security is not possible.) */

    IO_KEYBOARD_DISPLAY     = 4,    /*!< The local device is capable of displaying passkey to the user and a key pad which enables the user to enter a passkey */
    IO_CAPABILITY_COUNT
};

/** 
Defines the security level required by a specific service. Refer to GAP documentation for more
information.
*/
enum ClxSecurityRequirement 
{
    ClxHighSecurity         = 0,    /*!< Protection against Man-In-The-Middle (MITM) attacks is required. Over-the-air data encryption is required (not compatible with many devices). */
    ClxMediumSecurity       = 1,    /*!< Protection against Man-In-The-Middle (MITM) attacks is not required. Over-the-air data encryption is required. */
    ClxLowSecurity          = 2,    /*!< Protection against Man-In-The-Middle (MITM) attacks is not required. Over-the-air data encryption is not required. */
    ClxAutomaticSecurity    = 3,    /*!< Select the highest possible security level based on the configuration and input/output capabilities of both the local and the remote machine. 
                                         The selected security level will be either ClxHighSecurity or ClxMediumSecurity. Recommended option */
    ClxSdpNoSecurity        = 4     /*!< Select no security for SDP only. This cannot be used for other profiles as of version 2.1 */
};

/**
Defines the device role being a client or server, used for SPP profile.
*/
enum ClxServiceType
{
    ClxClient = 0,
    ClxServer = 1
};

/*
    Class ID values added to the XML should be same as these values.
    This list should be maintained manually to make sure no duplications.

    Class IDs 0x05 through 0x30 (inclusive) are reserved for ClarinoxBlue.
*/
#define CLARINOX_BLUE_GAP_CLASS_ID                          0x05
#define CLARINOX_BLUE_SDAP_CLASS_ID                         0x06
#define CLARINOX_BLUE_SPP_CLASS_ID                          0x07
#define CLARINOX_BLUE_HSP_HS_CLASS_ID                       0x08
#define CLARINOX_BLUE_HSP_AG_CLASS_ID                       0x09
#define CLARINOX_BLUE_PCE_CLASS_ID                          0x0A
#define CLARINOX_BLUE_MCE_CLASS_ID                          0x0B
#define CLARINOX_BLUE_HFP_HF_CLASS_ID                       0x0C
#define CLARINOX_BLUE_HFP_AG_CLASS_ID                       0x0D
#define CLARINOX_BLUE_A2DP_CLASS_ID                         0x0F
#define CLARINOX_BLUE_OPC_CLASS_ID                          0x10
#define CLARINOX_BLUE_FTC_CLASS_ID                          0x11
#define CLARINOX_BLUE_FTS_CLASS_ID                          0x12
#define CLARINOX_BLUE_OPS_CLASS_ID                          0x13
#define CLARINOX_BLUE_AVRCP_CLASS_ID                        0x14
#define CLARINOX_BLUE_LE_GAP_ID                             0x15
#define CLARINOX_BLUE_BIP_INITIATOR_CLASS_ID                0x16
#define CLARINOX_BLUE_BIP_ACCEPTOR_CLASS_ID                 0x17
#define CLARINOX_BLUE_CTN_CLIENT_CLASS_ID                   0x18
#define CLARINOX_BLUE_HDP_CLASS_ID                          0x19
#define CLARINOX_BLUE_HID_CLIENT_CLASS_ID                   0x1A
#define CLARINOX_BLUE_HID_SERVER_CLASS_ID                   0x1B
#define CLARINOX_BLUE_PAN_CLASS_ID                          0x1C

#define CLARINOX_BLUE_LE_GATT_CLIENT_ID                     0x1F
#define CLARINOX_BLUE_LE_GATT_SERVER_ID                     0x20
#define CLARINOX_BLUE_IPSP_CLASS_ID                         0x21
#define CLARINOX_BLUE_LE_HRCP_ID                            0x22
#define CLARINOX_BLUE_BPP_SENDER_CLASS_ID                   0x23
#define CLARINOX_BLUE_HID_CLASS_ID                          0x24
#define CLARINOX_BLUE_BPP_PRINTER_CLASS_ID                  0x25
#define CLARINOX_BLUE_MESH_CLASS_ID                         0x26
#define CLARINOX_BLUE_ISOCHRONOUS_SERVICE_CLASS_ID          0x27


 /*
Class IDs 60 to 63 can be used for user-defined commands/indications
*/
#define CLARINOX_USER_DEFINED_CLASS_ID           60

/* 
Flags bits for the configuration parameter "clxBlueMonitorPacketCaptureFilter".
When a bit (as defined below) is set, the corresponding packets will not be sent to ClariFi.
*/
#define CLX_BLUE_MONITOR_FILTER_INCOMING_SCO      CLX_SET_BIT(2)
#define CLX_BLUE_MONITOR_FILTER_OUTGOING_SCO      CLX_SET_BIT(3)
#define CLX_BLUE_MONITOR_FILTER_INCOMING_ISO      CLX_SET_BIT(4)
#define CLX_BLUE_MONITOR_FILTER_OUTGOING_ISO      CLX_SET_BIT(5)


/**
Default value for ClarinoxBlue configuration parameters:
*/
/* The following MACRO definitions could be used as default parameters. 
 * User must customize these values for a specific purpose (i.e. MTU sizes etc.)
 */
#define CLARINOXBLUE_DEFAULT_SOFTFRAME_INITIALIZED_WITH_STACK                               TRUE
#define CLARINOXBLUE_DEFAULT_STACK_SERVICES_CLEANUP_TIMEOUT                                 3000           /*!< milliseconds required during stack termination. Timeout is required for a graceful termination of existing remote connections */
#define CLARINOXBLUE_DEFAULT_MAX_NO_OF_PAIRED_DEVICES                                       16             /*!< maximum list size for paired devices, persistent storage is required for that many devices. */
#define CLARINOXBLUE_DEFAULT_MAX_NO_OF_DISCOVERED_DEVICES                                   12             /*!< maximum number of discovered devices during inquiry */ 

#define CLARINOXBLUE_DEFAULT_IO_CAPABILITIES                                                IO_NONE
#define CLARINOXBLUE_DEFAULT_LOCAL_DEVICE_NAME                                              "Clarinox"
#define CLARINOXBLUE_DEFAULT_MAJOR_CLASS_OF_DEVICE                                          MJ_UNCATEGORIZED
#define CLARINOXBLUE_DEFAULT_MINOR_CLASS_OF_DEVICE                                          0
#define CLARINOXBLUE_DEFAULT_SERVICE_CLASSES                                                0
#define CLARINOXBLUE_DEFAULT_LINK_REQUEST_TIMEOUT                                           60000          /*!< times 0.625 milliseconds */
#define CLARINOXBLUE_DEFAULT_SUPPORT_SIMPLE_SECURE_PAIRING                                  TRUE
#define CLARINOXBLUE_DEFAULT_ENABLE_LINK_LEVEL_AUTHENTICATION                               FALSE
#define CLARINOXBLUE_DEFAULT_MAX_NUMBER_OF_SIMULTANEOUS_ACL_CONNECTIONS                     32

#define CLARINOXBLUE_DEFAULT_CLX_BLUE_PACKET_CAPTURE_FILTER_VALUE                           0

#define CLARINOXBLUE_DEFAULT_USB_PORT_NAME                                                  "\\\\.\\CSR0"
#define CLARINOXBLUE_DEFAULT_TRANSPORT_TYPE                                                 "TT_USB"
#define CLARINOXBLUE_DEFAULT_COM_PORT_NAME                                                  "COM1"
#define CLARINOXBLUE_DEFAULT_COM_PORT_SPEED                                                 115200

#define CLARINOXBLUE_DEFAULT_EXTENDED_INQUIRY_RESPONSE                                      "TRUE"
#define CLARINOXBLUE_DEFAULT_DEVICE_ID_SERVICE                                              "TRUE"

#define CLARINOXBLUE_DEFAULT_INQUIRY_TX_POWER                                               0              /*!< dBm */
#define CLARINOXBLUE_DEFAULT_MAX_NO_OF_REMOTE_DEVICES                                       20             /*!< No of devices */

#define CLARINOXBLUE_DEFAULT_NUMBER_OF_NETWORK_BUFFER_DESCRIPTORS                           16
#define CLARINOXBLUE_DEFAULT_NUMBER_OF_NETWORK_BUFFER_DUPLICATE_DESCRIPTORS                 8

#define CLARINOXBLUE_DEFAULT_SECURE_CONNECTIONS_ONLY_MODE                                   FALSE
#define CLARINOXBLUE_DEFAULT_MINIMUM_ENCRYPTION_KEY_SIZE                                    7

// L2CAP
#define CLARINOXBLUE_DEFAULT_L2CAP_OUTGOING_BUFFER_SIZE                                     1024           /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_INCOMING_BUFFER_SIZE                                     1024           /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_SIGNAL_CHANNEL_OUTPUT_CONTAINER_SIZE                     1024           /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_SIGNAL_CHANNEL_INPUT_CONTAINER_SIZE                      1024           /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_SIGNAL_CHANNEL_MTU                                       672            /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_MANAGER_MAX_NUM_OF_SYSTEM_WIDE_L2CAP_CONNECTIONS         50

// BLE
#define CLARINOXBLUE_DEFAULT_LOW_ENERGY_L2CAP_SIGNAL_CHANNEL_OUTPUT_CONTAINER_SIZE          512            /*!< bytes */
#define CLARINOXBLUE_DEFAULT_LOW_ENERGY_L2CAP_SIGNAL_CHANNEL_INPUT_CONTAINER_SIZE           512            /*!< bytes */
#define CLARINOXBLUE_DEFAULT_LOW_ENERGY_MAX_NUMBER_OF_PAIRED_DEVICES                        16             /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_ATT_INCOMING_BUFFER_SIZE                                 1024           /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_ATT_OUTGOING_BUFFER_SIZE                                 1024           /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_ATT_QUEUED_WRITE_CONTAINER_SIZE                          1024           /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_ATT_CHANNEL_MAX_MTU                                      672            /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_ATT_CLIENT_NOTIFICATION_QUEUE_SIZE                       1024           /*!< bytes */
#define CLARINOXBLUE_DEFAULT_L2CAP_ATT_CLIENT_RESPONSE_TIME_PERIOD                          3000           /*!< ms    */
#define CLARINOXBLUE_DEFAULT_LOW_ENERGY_SECURITY_MANAGER_MIN_SUPPORTED_KEY_SIZE             7              /*!< Bytes */

#define CLARINOXBLUE_DEFAULT_ADVERTISING_REPORT_QUEUE_SIZE                                  2048           /*!< Bytes */

#if CLX_PACKAGE_CLARINOXBLUE_BLE_ISOCHRONOUS
#define CLARINOXBLUE_DEFAULT_MAX_NUMBER_OF_ISOCHRONOUS_STREAMS                              4
#define CLARINOXBLUE_DEFAULT_ISO_BUFFER_HEAP_SIZE                                           2048           /*!< Bytes */
#endif /* CLX_PACKAGE_CLARINOXBLUE_BLE_ISOCHRONOUS */

#if defined(CLX_BLE_MESH_RELAY_SUPPORTED)
#   define CLARINOXBLUE_DEFAULT_NUMBER_OF_MESH_NETWORK_BUFFERS                              18      /* Buffers */
#else
#   define CLARINOXBLUE_DEFAULT_NUMBER_OF_MESH_NETWORK_BUFFERS                              6       /* Buffers */
#endif

#define CLARINOXBLUE_DEFAULT_BLE_MESH_NETWORK_PDU_CACHE_CAPACITY                            16      /* PDUs */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_RX_HEAP_SIZE                                          512     /* Bytes */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_MAX_TX_ACCESS_MESSAGE_SIZE                            384     /* Bytes */  
#define CLARINOXBLUE_DEFAULT_BLE_MESH_MAX_NUMBER_OF_TX_MESSAGE_RETRIES                      3       /* Times */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_SEQ_AUTH_LIST_SIZE                                    32      /* Entries */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_TX_TTL_VALUE                                          3
#define CLARINOXBLUE_DEFAULT_BLE_MESH_TX_SEGMENT_RETRANSMISSION_TIMEOUT                     200     /* ms */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_RX_MESSAGE_ACKNOWLEDGEMENT_TIMEOUT                    150     /* ms */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_RX_SEGMENTED_MESSAGE_COMPLETION_TOMEOUT               10000   /* ms */

#define CLARINOXBLUE_DEFAULT_BLE_MESH_NETWORK_PDU_COUNT                                     1       /* Times */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_NETWORK_PDU_INTERVAL                                  100     /* ms */

#define CLARINOXBLUE_DEFAULT_BLE_MESH_NETWORK_RELAY_COUNT                                   1       /* Times */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_NETWORK_RELAY_INTERVAL                                100     /* ms */

#define CLARINOXBLUE_DEFAULT_BLE_MESH_SCAN_INTERVAL                                         0x10    /* 10 ms */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_SCAN_WINDOW                                           0x10    /* 10 ms */

#define CLARINOXBLUE_DEFAULT_BLE_MESH_COMPANY_IDENTIFIER                                    BLUETOOTH_CLARINOX_COMPANY_ID   /*!< Clarinox Identifier added by default, it could be overwritten by application */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_VENDOR_PRODUCT_IDENTIFIER                             BLUETOOTH_CLARINOX_COMPANY_ID   /*!< Clarinox Identifier added by default, it could be overwritten by application */
#define CLARINOXBLUE_DEFAULT_BLE_MESH_VENDOR_PRODUCT_VERSION                                0x0001  /*!< The version number could be incremented gradually */

#if defined(CLX_BLE_MESH_PROVISIONING_SUPPORTED)
#define CLARINOXBLUE_DEFAULT_BLE_MESH_PROVISIONING_TIME_OUT                                 60000   /* 60 seconds */
#endif /* defined(CLX_BLE_MESH_PROVISIONING_SUPPORTED) */

#if defined(CLX_BLE_MESH_FRIEND_SUPPORTED)
#define CLARINOXBLUE_DEFAULT_MESH_FRIEND_RECEIVE_WINDOW                                     255     /*!< Time within which friend node can send message to low power node. (in milliseconds - maximum is 255) */
#define CLARINOXBLUE_DEFAULT_MESH_FRIEND_MESSAGE_QUEUE_MAX_SIZE                             10      /*!< Number of messages a friend node can store for low power node (maximum limit is 255) */
#define CLARINOXBLUE_DEFAULT_MESH_FRIEND_SUBSCRIPTION_LIST_MAX_SIZE                         10      /*!< Number of Subscription address a friend node can allow low power node to subscribe (maximum limit is 255) */
#define CLARINOXBLUE_DEFAULT_MESH_FRIEND_LOW_POWER_NODE_MAX_COUNT                           2       /*!< Maximum number of low power nodes for whom a friend node can be a friend of */
#endif /* #if defined(CLX_BLE_MESH_FRIEND_SUPPORTED) */

#if defined(CLX_BLE_MESH_PROXY_SUPPORTED)
#define CLARINOXBLUE_DEFAULT_MESH_PROXY_ADDRESS_FILTER_SIZE                                 5       /*!< Default maximum capacity of address filter list in proxy node >*/
#endif /* defined(CLX_BLE_MESH_PROXY_SUPPORTED) */

#if defined(CLX_BLE_MESH_LOW_POWER_NODE)
#define CLARINOXBLUE_DEFAULT_MESH_LPN_RSSI_FACTOR                                           0x02        /*!< The configuration value measured by friend node to calculate friend offer delay */
#define CLARINOXBLUE_DEFAULT_MESH_LPN_RECEIVE_WINDOW_FACTOR                                 0x02        /*!< The configuration value used by friend node to calculate friend offer delay */
#define CLARINOXBLUE_DEFAULT_MESH_LPN_MIN_QUEUE_SIZE_LOG                                    0x03        /*!< The minimum number of messages that the friend node stores in its friend queue */
#define CLARINOXBLUE_DEFAULT_MESH_LPN_RECEIVE_DELAY                                         0x0B        /*!< Receive delay requested by LPN */
#define CLARINOXBLUE_DEFAULT_MESH_LPN_POLL_TIMEOUT                                          0x1770      /*!< Default LPN poll timeout value 10 mins, it should be in the range of 0x00000A–0x34BBFF in units of 100 ms */
#define CLARINOXBLUE_DEFAULT_MESH_LPN_NO_OF_ELEMENTS                                        0x01        /*!< Number of elements supported by LPN */
#define CLARINOXBLUE_DEFAULT_MESH_LPN_WAKEUP_TIME_PERIOD                                    0xC8        /*!< Default LPN wakeup time period 20 secs, it should be less than poll timeout value */
#endif /* defined(CLX_BLE_MESH_LOW_POWER_NODE) */

#if defined(CLX_BLE_MESH_SECURE_NETWORK_BEACON)
#define CLARINOXBLUE_DEFAULT_MESH_SECURE_NW_BEACON_RISK_MONITORING_TIME_PERIOD              3600000     /*!< Risk monitoring timer configured as 1 hour to ensure the sequence number never wrap around */
#endif /* defined(CLX_BLE_MESH_SECURE_NETWORK_BEACON) */


// HCI
#define CLARINOXBLUE_DEFAULT_HCI_DRIVER_INCOMING_BUFFER_SIZE                                7000           /*!< bytes - if default MTU size is selected for RFCOMM then this HCI size is sufficient. */
/**
 * NO L2CAP incoming MTU can be larger than CLARINOXBLUE_DEFAULT_HCI_DEVICE_INCOMING_BUFFER_SIZE - 8 (L2CAP and ACL headers), 
 * otherwise it will be limited to CLARINOXBLUE_DEFAULT_HCI_DEVICE_INCOMING_BUFFER_SIZE - 8.
 */
#define CLARINOXBLUE_DEFAULT_HCI_DEVICE_INCOMING_BUFFER_SIZE                                1028           /*!< MAX ACL PACKET SIZE + 4 (acl header) */
#define CLARINOXBLUE_DEFAULT_CLARINOXBLUE_DEFAULT_HCI_QUEUE_MAX_NUM_OF_OUTGOING_PACKETS     10             /*!< packets. */
#define CLARINOXBLUE_DEFAULT_HCI_LINK_SUPERVISION_TIMEOUT                                   32767          /*!< 20.45sec (count * 0.625 ms inactivity causes link to drop, 0: never disconnect). Max allowed value is 0xFFFF */
#define CLARINOXBLUE_DEFAULT_HCI_NUMBER_OF_RX_ACL_BUFFERS                                   10
#define CLARINOXBLUE_DEFAULT_HCI_RX_ACL_SINGLE_BUFFER_SIZE                                  512
#define CLARINOXBLUE_DEFAULT_HCI_EVENT_BUFFER_SIZE                                          1024

// RFCOMM
#define CLARINOXBLUE_DEFAULT_RFCOMM_INCOMING_QUEUE_SIZE                                     8192           /*!< bytes - RFCOMM can have maximum this much incoming buffer space */
#define CLARINOXBLUE_DEFAULT_RFCOMM_OUTGOING_QUEUE_SIZE                                     4096           /*!< bytes - RFCOMM can have maximum this much outgoing buffer space */
#define CLARINOXBLUE_DEFAULT_RFCOMM_MAX_NUM_OF_L2CAP_CONNECTIONS                            7              /*!< RFCOMM can have maximum this many L2CAP connections */
#define CLARINOXBLUE_DEFAULT_RFCOMM_INCOMING_MTU                                            672            /*!< bytes - RFCOMM can receive up to 666 bytes from the remote unit. */
#define CLARINOXBLUE_DEFAULT_RFCOMM_MAX_OUTGOING_DATA_SIZE                                  672            /*!< bytes - RFCOMM can send up to 666 bytes at once */
#define CLARINOXBLUE_DEFAULT_RFCOMM_MAX_REMOTE_CREDIT                                        7               /*!< Max number of credits which may be granted to the remote RFCOMM service */
#define CLARINOXBLUE_DEFAULT_RFCOMM_SECURITY_REQUIREMENT                                    ClxAutomaticSecurity
#define CLARINOXBLUE_DEFAULT_RFCOMM_DISCONNECT_TIME_PERIOD                                  100            /*!< Time period to wait before sending the RFCOMM disconnect response to remote (in ms) */

// SDP
#define CLARINOXBLUE_DEFAULT_SDP_MAX_NUM_OF_L2CAP_CONNECTIONS                               8
#define CLARINOXBLUE_DEFAULT_SDP_INCOMING_MTU                                               672            /*!< bytes. */
#define CLARINOXBLUE_DEFAULT_SDP_SECURITY_REQUIREMENT                                       ClxSdpNoSecurity
#define CLARINOXBLUE_DEFAULT_SDP_MAX_PDU_SIZE                                               2048

// AVRCP
#define CLARINOXBLUE_DEFAULT_AVRCP_BROWSE_SECURITY_REQUIREMENT                              ClxAutomaticSecurity
#define CLARINOXBLUE_DEFAULT_AVRCP_BROWSE_INCOMING_MTU                                      335             /*!< bytes - AVRCP BROWSE can receive up to this much bytes from the remote unit. */
#define CLARINOXBLUE_DEFAULT_AVRCP_BROWSE_MAX_OUTGOING_DATA_SIZE                            512             /*!< bytes - AVRCP BROWSE can send up to this much bytes at once */
#define CLARINOXBLUE_DEFAULT_AVRCP_BROWSE_INCOMING_BUFFER_SIZE                              512             /*!< bytes - AVRCP BROWSE can have maximum this much incoming buffer space */
#define CLARINOXBLUE_DEFAULT_AVRCP_BROWSE_OUTGOING_BUFFER_SIZE                              512             /*!< bytes - AVRCP BROWSE can have maximum this much outgoing buffer space */

// OBEX
#define CLARINOXBLUE_DEFAULT_OBEX_OVER_L2CAP_INCOMING_MTU                                   672
#define CLARINOXBLUE_DEFAULT_OBEX_OVER_L2CAP_MAX_OUTGOING_DATA_SIZE                         672
#define CLARINOXBLUE_DEFAULT_OBEX_MAX_RECV_PACKET_LENGTH                                    2048
#define CLARINOXBLUE_DEFAULT_OBEX_REMOTE_RESPONSE_TIMEOUT_VALUE                             4000

// HDP
#define CLARINOXBLUE_DEFAULT_HDP_ROLE                                                       0                 /*!< By default, No role is set for MCAP/HDP instance */
#define CLARINOXBLUE_DEFAULT_HDP_INCOMING_MTU                                               335               /*!< bytes - HDP can receive up to this much bytes from the remote unit. */
#define CLARINOXBLUE_DEFAULT_HDP_MAX_OUTGOING_DATA_SIZE                                     335               /*!< bytes - HDP can send up to this much bytes at once */
#define CLARINOXBLUE_DEFAULT_HDP_INCOMING_BUFFER_SIZE                                       512               /*!< bytes - HDP can have maximum this much incoming buffer space */
#define CLARINOXBLUE_DEFAULT_HDP_OUTGOING_BUFFER_SIZE                                       512               /*!< bytes - HDP can have maximum this much outgoing buffer space */
#define CLARINOXBLUE_DEFAULT_HDP_SECURITY_REQUIREMENT                                       ClxAutomaticSecurity

// HID
#define CLARINOXBLUE_DEFAULT_HID_SECURITY_REQUIREMENT                                       ClxAutomaticSecurity
#define CLARINOXBLUE_DEFAULT_HID_INCOMING_BUFFER_SIZE                                       1024 /*512*/       /*!< bytes - HID can have this much incoming buffer space as maximum */
#define CLARINOXBLUE_DEFAULT_HID_OUTGOING_BUFFER_SIZE                                       1024 /*512*/       /*!< bytes - HID can have this much outgoing buffer space as maximum */
#define CLARINOXBLUE_DEFAULT_HID_INCOMING_MTU                                               672  /*335*/       /*!< bytes - HID can receive up to this much bytes from the remote unit */
#define CLARINOXBLUE_DEFAULT_HIDP_MAX_OUTGOING_DATA_SIZE                                    672  /*335*/       /*!< bytes - HID can send up to this much bytes at once */
#define CLARINOXBLUE_DEFAULT_HID_MAX_NUMBER_OF_HID_L2CAP_CHANNELS                           7                  /*!< HID can have maximum this many L2CAP connections */

// BNEP 
#define CLARINOXBLUE_DEFAULT_BNEP_INCOMING_MTU                                               1691              /*!< bytes - BNEP can receive up to this much bytes from the remote unit. */
#define CLARINOXBLUE_DEFAULT_BNEP_MAX_OUTGOING_DATA_SIZE                                     1691              /*!< bytes - BNEP can send up to this much bytes at once */
#define CLARINOXBLUE_DEFAULT_BNEP_INCOMING_BUFFER_SIZE                                       4096              /*!< bytes - BNEP can have maximum this much incoming buffer space */
#define CLARINOXBLUE_DEFAULT_BNEP_OUTGOING_BUFFER_SIZE                                       4096              /*!< bytes - BNEP can have maximum this much outgoing buffer space */
#define CLARINOXBLUE_DEFAULT_BNEP_SECURITY_REQUIREMENT                                       ClxAutomaticSecurity
#define CLARINOXBLUE_DEFAULT_BNEP_MAX_NUMBER_OF_L2CAP_CHANNELS                               7                 /*!< Max number of L2cap channels BNEP can have (as many devices can connect to) */
#define CLARINOXBLUE_DEFAULT_BNEP_MAX_RETRANSMIT_TIMEOUT                                     1000              /*!< bytes - BNEP will trasmit the failed packet send after this timeout(ms) */
#define CLARINOXBLUE_DEFAULT_BNEP_MAX_RETRANSMIT_ATTEMPT                                     3                 /*!< bytes - BNEP will re-transmit the failed packet send for this many number of times */
#define CLARINOXBLUE_DEFAULT_BNEP_MAX_CONN_RETRY_ATTEMPTS                                    3                 /*!< bytes - BNEP will attempt to retry the connection requestfor this many no of times */

// HCRP
#define CLARINOXBLUE_DEFAULT_HCRP_SECURITY_REQUIREMENT                                       ClxAutomaticSecurity
#define CLARINOXBLUE_DEFAULT_HCRP_INCOMING_BUFFER_SIZE                                       1024                /*!< bytes - HCRP can have this much incoming buffer space as maximum */
#define CLARINOXBLUE_DEFAULT_HCRP_OUTGOING_BUFFER_SIZE                                       1024                /*!< bytes - HCRP can have this much outgoing buffer space as maximum */
#define CLARINOXBLUE_DEFAULT_HCRP_INCOMING_MTU                                               512                 /*!< bytes - HCRP can receive up to this much bytes from the remote unit */
#define CLARINOXBLUE_DEFAULT_HCRP_MAX_OUTGOING_DATA_SIZE                                     512                 /*!< bytes - HCRP can send up to this much bytes at once */
#define CLARINOXBLUE_DEFAULT_HCRP_MAX_NUMBER_L2CAP_CHANNELS                                  7                   /*!< HCRP can have maximum this many L2CAP connections */

// A2DP
#define CLARINOXBLUE_DEFAULT_A2DP_MINIMUM_MTU_SIZE                                          335                 /*!< Bytes - A2DP Minimum MTU size for a A2DP channel that is to be configured */
#define CLARINOXBLUE_DEFAULT_A2DP_NUMBER_OF_FRAMES_PER_PERIOD                               40                  /*!< Bytes - A2DP Encoded data needed per cycle is calculated from number of frames per period */
#define CLARINOXBLUE_DEFAULT_A2DP_STREAM_SOURCE_OUTGOING_MAX_SIZE                           670                 /*!< Bytes - A2DP Maximum outgoing MTU size for source stream channel */ 
#define CLARINOXBLUE_DEFAULT_A2DP_STREAM_SOURCE_OUTGOING_L2CAP_BUFFER                       4096                /*!< Bytes - A2DP Outgoing L2cap buffer size for source streaming channel */
#define CLARINOXBLUE_DEFAULT_A2DP_STREAM_SINK_INCOMING_L2CAP_BUFFER                         1024                /*!< Bytes - A2DP Incoming L2cap buffer size for sink streaming channel */

// SCO
#define CLARINOXBLUE_DEFAULT_SCO_SCO_OVER_HCI_FLAG                                          FALSE                /*!< Indicates whether SCO packets sent over HCI or handled by Chip. By default it is disabled. */
#define CLARINOXBLUE_DEFAULT_SCO_BUFFER_HEAP_SIZE                                           2048                 /*!< The size of the private heap from which SCO TX/RX descriptors and buffer are allocated. */

// HFP HF
#define CLARINOXBLUE_DEFAULT_HFP_HF_AT_COMMAND_RESPONSE_TIMEOUT                             5000                /*!< Milliseconds - Time period to wait for response after sending HFP HF AT command to AG */

/**
** <!-- ----------------------------------------------------------------- -->
** <!-- ENUM: DeviceServiceClass -->
**
** <!-- DESCRIPTION:-->
** \brief
** DeviceServiceClass defines values that are contained in the Class-of-Device.
** The implementer, needs to make a decision about which "Service Class" bits to set in the
** class-of-device based on the services that are supported and the same services can be
** advertised via SDP. There is no obvious mapping, because it is not possible to define all
** the possible Bluetooth services.
** The Class-of-Service service class bits are intended to be used as "hints" to filter devices and
** help to choose which devices to further interact with, by performing
** SDP transactions or other means, to get further details about the services.
** Values may be combined (bit-wise or-ed) in order to form the desired service class.
**
**<!-- ----------------------------------------------------------------- -->
*/
enum ClxDeviceServiceClass
{
    ST_LIMITED_DISCOVERABLE_MODE                    = 0x0001,    /*!< Limited Discoverable */
    ST_LE_AUDIO                                     = 0x0002,    /*!< LE Audio support */
    ST_POSITIONING                                  = 0x0008,    /*!< Location Identification */
    ST_NETWORKING                                   = 0x0010,    /*!< LAN, Ad hoc */
    ST_RENDERING                                    = 0x0020,    /*!< Printing, Speaker */
    ST_CAPTURING                                    = 0x0040,    /*!< Scanner, Microphone */
    ST_OBJECT_TRANSFER                              = 0x0080,    /*!< v_Inbox, v_Folder */
    ST_AUDIO                                        = 0x0100,    /*!< Speaker, Microphone, Headset service */
    ST_TELEPHONY                                    = 0x0200,    /*!< Cordless telephony, Modem, Headset service */
    ST_INFORMATION                                  = 0x0400     /*!< WEB-server, WAP-server */
};


/**
** <!-- ----------------------------------------------------------------- -->
** <!-- ENUM: MajorDeviceClass -->
**
** <!-- DESCRIPTION:-->
** \brief
** MajorDeviceClass defines values that are contained in the Class-of-Device.
** The implementer, needs to make a decision about which "Major Device Class" bits to set in the
** class-of-device based on the services that are supported ,see DeviceClass .
**
**
**<!-- ----------------------------------------------------------------- -->
*/
enum ClxMajorDeviceClass
{

    MJ_MISCELLANEOUS                                = 0x0000,    /*!< Miscellaneous */ 
    MJ_COMPUTER                                     = 0x0001,    /*!< Desktop, Notebook, PDA, Organizers */ 
    MJ_PHONE                                        = 0x0002,    /*!< Cellular, Cordless, Payphone, Modem */ 
    MJ_LAN                                          = 0x0003,    /*!< Network Access Point */ 
    MJ_AUDIO_VIDEO                                  = 0x0004,    /*!< Headset, Speaker, Stereo, Video Display, VCR */ 
    MJ_PERIPHERAL                                   = 0x0005,    /*!< Mouse, Joystick, Keyboards */  
    MJ_IMAGING                                      = 0x0006,    /*!< Printing, Scanner, Camera, Display */   
    MJ_WEARABLE                                     = 0x0007,    /*!< Wearable */ 
    MJ_TOY                                          = 0x0008,    /*!< Toy */ 
    MJ_HEALTH                                       = 0x0009,    /*!< Health */ 
    MJ_UNCATEGORIZED                                = 0x001f     /*!< Uncategorized, devices that do not have a major class code */     
};


/**
Minor class of device when major class of device is MJ_COMPUTER. Only one can be selected.
*/
enum ClxComputerMinorDeviceClass
{
    CMI_UNCATEGORIZED                               = 0x0000,    /*!< Uncategorized, code for device not assigned */
    CMI_DESKTOP                                     = 0x0001,    /*!< Desktop workstation */    
    CMI_SERVER                                      = 0x0002,    /*!< Server-class computer */
    CMI_LAPTOP                                      = 0x0003,    /*!< Laptop */
    CMI_PDA                                         = 0x0004,    /*!< Handheld PC/PDA (clam shell) */
    CMI_PALM                                        = 0x0005,    /*!< Palm sized PC/PDA */
    CMI_WEARABLE                                    = 0x0006     /*!< Wearable computer (Watch sized) */
};

/**
Minor class of device when major class of device is MJ_PHONE. Only one can be selected.
*/
enum ClxPhoneMinorDeviceClass
{
    PHMI_UNCATEGORIZED                              = 0x0000,    /*!< Uncategorized, code for device not assigned */
    PHMI_CELLULAR                                   = 0x0001,    /*!< Cellular */
    PHMI_CORDLESS                                   = 0x0002,    /*!< Cordless */
    PHMI_SMART                                      = 0x0003,    /*!< Smart phone */
    PHMI_MODEM                                      = 0x0004,    /*!< Wired modem or voice gateway */
    PHMI_ISDN                                       = 0x0005     /*!< Common ISDN Access */
};


/**
Minor class of device when major class of device is MJ_LAN. Only one can be selected.

The exact loading formula is not standardized. It is up to each LAN/Network Access Point implementation 
to determine what internal conditions to report as a utilization percentage. The only requirement is that 
the number reflects an ever-increasing utilization of communication resources within the box. As a recommendation, 
a client that locates multiple LAN/Network Access Points should attempt to connect to the one reporting the lowest load.
*/
enum ClxLanMinorDeviceClass
{
    LMI_FULL                                        = 0x0000,    /*!< Fully available */
    LMI_17                                          = 0x0008,    /*!< 1 - 17% utilized */
    LMI_33                                          = 0x0010,    /*!< 17 - 33% utilized */
    LMI_50                                          = 0x0018,    /*!< 33 - 50% utilized */
    LMI_67                                          = 0x0020,    /*!< 50 - 67% utilized */
    LMI_83                                          = 0x0028,    /*!< 67 - 83% utilized */
    LMI_99                                          = 0x0030,    /*!< 83 - 99% utilized */
    LMI_NO_SERVICE                                  = 0x0038     /*!< No service available */
};


/**
Minor class of device when major class of device is MJ_AUDIO_VIDEO. Only one can be selected.
*/
enum ClxAudioVideoMinorDeviceClass
{
    AVMI_UNCATEGORIZED                              = 0x0000,    /*!< Uncategorized, code not assigned */
    AVMI_WEARABLE                                   = 0X0001,    /*!< Wearable Headset Device */
    AVMI_HANDS_FREE                                 = 0x0002,    /*!< Hands-free Device */
    AVMI_MICROPHONE                                 = 0x0004,    /*!< Microphone */
    AVMI_SPEAKER                                    = 0x0005,    /*!< Loudspeaker */
    AVMI_HEADPHONES                                 = 0x0006,    /*!< Headphones */
    AVMI_PORTABLE                                   = 0x0007,    /*!< Portable Audio */
    AVMI_CAR_AUDIO                                  = 0x0008,    /*!< Car audio */
    AVMI_SETTOP_BOX                                 = 0x0009,    /*!< Set-top box */
    AVMI_HIFI                                       = 0x000A,    /*!< HiFi Audio Device */
    AVMI_VCR                                        = 0x000B,    /*!< VCR */
    AVMI_CAMERA                                     = 0x000C,    /*!< Video Camera */
    AVMI_CAMCORDER                                  = 0x000D,    /*!< Camcorder */
    AVMI_MONITOR                                    = 0x000E,    /*!< Video Monitor */
    AVMI_DISPLAY_SPEAKER                            = 0x000F,    /*!< Video Display and Loudspeaker */
    AVMI_CONFERENCING                               = 0x0010,    /*!< Video Conferencing */
    AVMI_GAMING                                     = 0x0012     /*!< Gaming/Toy */
};


/**
Minor class of device when major class of device is MJ_PERIPHERAL.
One of these values may be combined (bit-wise or-ed) with one of the values in
ClxPeripheralMinorDeviceClass2 enumerator to form the desired minor class ID
for peripherals.
This enumeration constitutes the two most significant bits (bits 5 to 7) 
*/
enum ClxPeripheralMinorDeviceClass1
{
    PMI_NO_KEYBOARD                                 = 0x0000,    /*!< Not Keyboard / Not Pointing Device */
    PMI_KEYBAORD                                    = 0x0010,    /*!< Keyboard */
    PMI_POINTING_DEVICE                             = 0x0020,    /*!< Pointing device */
    PMI_COMBO                                       = 0x0030     /*!< Combo keyboard/pointing device */
};


/**
Minor class of device when major class of device is MJ_PERIPHERAL.
One of these values may be combined (bit-wise or-ed) with one of the values in
ClxPeripheralMinorDeviceClass1 enumerator to form the desired minor class ID
for peripherals.

This enumeration constitutes the four least significant bits (bits 1 to 4) 
*/
enum ClxPeripheralMinorDeviceClass2
{
    PMI_UNCATEGORIZED                               = 0x0000,    /*!< Uncategorized device */
    PMI_JOYSTICK                                    = 0x0001,    /*!< Joystick */
    PMI_GAMEPAD                                     = 0x0002,    /*!< Gamepad */
    PMI_REMOTE_CONTROL                              = 0x0003,    /*!< Remote control */
    PMI_SENSOR                                      = 0x0004,    /*!< Sensing device */
    PMI_DIGITIZER                                   = 0x0005,    /*!< Digitizer tablet */
    PMI_CARD_READER                                 = 0x0006,    /*!< Card Reader (e.g. SIM Card Reader) */
    PMI_PEN                                         = 0x0007,    /*!< Digital Pen */
    PMI_HANDHELD_SCANNER                            = 0x0008,    /*!< Handheld scanner for bar-codes, RFID, etc. */
    PMI_HANDHELD_GESTURAL                           = 0x0009     /*!< Handheld gestural input device (e.g., "wand" form factor) */
};


/**
Minor class of device when major class of device is MJ_IMAGING. The values may be combined
(bit-wise or-ed) in order to form the desired minor class for imaging devices.
*/
enum ClxImagingMinorDeviceClass
{
    IMI_DISPLAY                                     = 0x0004,
    IMI_CAMERA                                      = 0x0008,
    IMI_SCANNER                                     = 0x0010,
    IMI_PRINTER                                     = 0x0020
};


/**
Minor class of device when major class of device is MJ_WEARABLE. Only one can be selected.
*/
enum ClxWearableMinorDeviceClass
{
    WMI_WATCH                                       = 0x0001,
    WMI_PAGER                                       = 0x0002,
    WMI_JACKET                                      = 0x0003,
    WMI_HELMET                                      = 0x0004,
    WMI_GLASSES                                     = 0x0005
};


/**
Minor class of device when major class of device is MJ_TOY. Only one can be selected.
*/
enum ClxToyMinorDeviceClass
{
    TMI_ROBOT                                       = 0x0001,
    TMI_VEHICLE                                     = 0x0002,
    TMI_DOLL                                        = 0x0003,
    TMI_CONTROLLER                                  = 0x0004,
    TMI_GAME                                        = 0x0005
};


/**
Minor class of device when major class of device is MJ_HEALTH. Only one can be selected.
*/
enum ClxHealthMinorDeviceClass
{
    HMI_UNDEFINED                                   = 0x0000,    /*!< Undefined */
    HMI_BLOOD_MONITOR                               = 0x0001,    /*!< Blood Pressure Monitor */
    HMI_THERMOMETER                                 = 0x0002,    /*!< Thermometer */
    HMI_WEIGHING_SCALE                              = 0x0003,    /*!< Weighing Scale */
    HMI_GLUCOSE_METER                               = 0x0004,    /*!< Glucose Meter */
    HMI_PULSE_OXIMETER                              = 0x0005,    /*!< Pulse Oximeter */
    HMI_HEART_MONITOR                               = 0x0006,    /*!< Heart/Pulse Rate Monitor */
    HMI_HEALTH_DISPLAY                              = 0x0007,    /*!< Health Data Display */
    HMI_STEP_COUNTER                                = 0x0008,    /*!< Step Counter */
    HMI_BODY_ANALYZER                               = 0x0009,    /*!< Body Composition Analyzer */
    HMI_PEAK_FLOW_MONITOR                           = 0x000A,    /*!< Peak Flow Monitor */
    HMI_MEDICATION_MONITOR                          = 0x000B,    /*!< Medication Monitor */
    HMI_KNEE_PROTHESIS                              = 0x000C,    /*!< Knee Prosthesis */
    HMI_ANKLE_PROTHESIS                             = 0x000D,    /*!< Ankle Prosthesis */
    HMI_HEALTH_MANAGER                              = 0x000E     /*!< Generic Health Manager */
};


typedef enum ClxSecurityRequirement             CLX_CTYPE ClxSecurityRequirement;
typedef enum ClxDeviceServiceClass              CLX_CTYPE ClxDeviceServiceClass;
typedef enum ClxComputerMinorDeviceClass        CLX_CTYPE ClxComputerMinorDeviceClass;
typedef enum ClxPhoneMinorDeviceClass           CLX_CTYPE ClxPhoneMinorDeviceClass;
typedef enum ClxLanMinorDeviceClass             CLX_CTYPE ClxLanMinorDeviceClass;
typedef enum ClxAudioVideoMinorDeviceClass      CLX_CTYPE ClxAudioVideoMinorDeviceClass;
typedef enum ClxPeripheralMinorDeviceClass1     CLX_CTYPE ClxPeripheralMinorDeviceClass1;
typedef enum ClxPeripheralMinorDeviceClass2     CLX_CTYPE ClxPeripheralMinorDeviceClass2;
typedef enum ClxImagingMinorDeviceClass         CLX_CTYPE ClxImagingMinorDeviceClass;
typedef enum ClxWearableMinorDeviceClass        CLX_CTYPE ClxWearableMinorDeviceClass;
typedef enum ClxToyMinorDeviceClass             CLX_CTYPE ClxToyMinorDeviceClass;
typedef enum ClxHealthMinorDeviceClass          CLX_CTYPE ClxHealthMinorDeviceClass;


/** 
Response codes for OBEX-based profiles with server role: 
*/
typedef enum ClxObexResponseEnum
{
    CLX_OBEX_RSP_CONTINUE                           = 0x10,
    CLX_OBEX_RSP_SWITCH_PRO                         = 0x11,
    CLX_OBEX_RSP_SUCCESS                            = 0x20,
    CLX_OBEX_RSP_CREATED                            = 0x21,
    CLX_OBEX_RSP_ACCEPTED                           = 0x22,
    CLX_OBEX_RSP_NON_AUTHORITATIVE                  = 0x23,
    CLX_OBEX_RSP_NO_CONTENT                         = 0x24,
    CLX_OBEX_RSP_RESET_CONTENT                      = 0x25,
    CLX_OBEX_RSP_PARTIAL_CONTENT                    = 0x26,
    CLX_OBEX_RSP_MULTIPLE_CHOICES                   = 0x30,
    CLX_OBEX_RSP_MOVED_PERMANENTLY                  = 0x31,
    CLX_OBEX_RSP_MOVED_TEMPORARILY                  = 0x32,
    CLX_OBEX_RSP_SEE_OTHER                          = 0x33,
    CLX_OBEX_RSP_NOT_MODIFIED                       = 0x34,
    CLX_OBEX_RSP_USE_PROXY                          = 0x35,
    CLX_OBEX_RSP_BAD_REQUEST                        = 0x40,
    CLX_OBEX_RSP_UNAUTHORIZED                       = 0x41,
    CLX_OBEX_RSP_PAYMENT_REQUIRED                   = 0x42,
    CLX_OBEX_RSP_FORBIDDEN                          = 0x43,
    CLX_OBEX_RSP_NOT_FOUND                          = 0x44,
    CLX_OBEX_RSP_METHOD_NOT_ALLOWED                 = 0x45,
    CLX_OBEX_RSP_NOT_ACCEPTABLE                     = 0x46,
    CLX_OBEX_RSP_PROXY_AUTH_REQUIRED                = 0x47,
    CLX_OBEX_RSP_REQUEST_TIME_OUT                   = 0x48,
    CLX_OBEX_RSP_CONFLICT                           = 0x49,
    CLX_OBEX_RSP_GONE                               = 0x4a,
    CLX_OBEX_RSP_LENGTH_REQUIRED                    = 0x4b,
    CLX_OBEX_RSP_PRECONDITION_FAILED                = 0x4c,
    CLX_OBEX_RSP_REQ_ENTITY_TOO_LARGE               = 0x4d,
    CLX_OBEX_RSP_REQ_URL_TOO_LARGE                  = 0x4e,
    CLX_OBEX_RSP_UNSUPPORTED_MEDIA_TYPE             = 0x4f,
    CLX_OBEX_RSP_INTERNAL_SERVER_ERROR              = 0x50,
    CLX_OBEX_RSP_NOT_IMPLEMENTED                    = 0x51,
    CLX_OBEX_RSP_BAD_GATEWAY                        = 0x52,
    CLX_OBEX_RSP_SERVICE_UNAVAILABLE                = 0x53,
    CLX_OBEX_RSP_GATEWAY_TIMEOUT                    = 0x54,
    CLX_OBEX_RSP_VERSION_NOT_SUPPORTED              = 0x55,
    CLX_OBEX_RSP_DATABASE_FULL                      = 0x60,
    CLX_OBEX_RSP_DATABASE_LOCKED                    = 0x61,
    CLX_OBEX_ACL_FAILED                             = 0x62
} ClxObexResponse;

typedef enum ClxObexCommandEnum
{
     CLX_OBEX_CMD_CONNECT                           = 0x00,
     CLX_OBEX_CMD_DISCONNECT                        = 0x01,
     CLX_OBEX_CMD_PUT                               = 0x02,
     CLX_OBEX_CMD_GET                               = 0x03,
     CLX_OBEX_CMD_SETPATH                           = 0x05,
     CLX_OBEX_CMD_SESSION                           = 0x07, /* used for reliable session support */
     CLX_OBEX_CMD_ABORT                             = 0x7f,
     CLX_OBEX_FINAL                                 = 0x80
} ClxObexCommand;

typedef enum ClxObexEventEnum
{
     CLX_OBEX_EVENT_PROGRESS                        = 0,    /* Progress has been made */
     CLX_CLX_OBEX_EVENT_REQHINT                     = 1,    /* An incoming request is about to come */
     CLX_OBEX_EVENT_REQ                             = 2,    /* An incoming request has arrived */
     CLX_OBEX_EVENT_REQDONE                         = 3,    /* Request has finished */
     CLX_OBEX_EVENT_LINKERR                         = 4,    /* Link has been disconnected */
     CLX_OBEX_EVENT_PARSEERR                        = 5,    /* Malformed data encountered */
     CLX_OBEX_EVENT_ACCEPTHINT                      = 6,    /* Connection accepted */
     CLX_OBEX_EVENT_ABORT                           = 7,    /* Request was aborted */
     CLX_OBEX_EVENT_STREAMEMPTY                     = 8,    /* Need to feed more data when sending a stream */
     CLX_OBEX_EVENT_STREAMAVAIL                     = 9,    /* Time to pick up data when receiving a stream */
     CLX_OBEX_EVENT_UNEXPECTED                      = 10,   /* Unexpected data, not fatal */
     CLX_OBEX_EVENT_REQCHECK                        = 11,
     CLX_OBEX_EVENT_TIMEDOUT                        = 12    /* Obex request has been timed out with no response from remote */
} ClxObexEvent;

typedef enum ClxObexObjHdrEnum
{
     CLX_OBEX_OBJECT_FIT_ONE_PACKET                 = 0x01,  /* This header must fit in one packet */
     CLX_OBEX_OBJECT_STREAM_START                   = 0x02,  /* Start of streaming body */
     CLX_OBEX_OBJECT_STREAM_DATA                    = 0x04,  /* Body-stream data */
     CLX_OBEX_OBJECT_STREAM_DATAEND                 = 0x08,  /* Body stream last data */
     CLX_OBEX_OBJECT_SUSPEND                        = 0x10   /* Suspend after sending this header */
} ClxObexObjHdr;

typedef enum ClxObexHeaderEnum
{
     CLX_OBEX_HEADER_EMPTY                          = 0x00, /* Empty header (buggy OBEX servers) */
     CLX_OBEX_HEADER_COUNT                          = 0xc0, /* Number of objects (used by connect) */
     CLX_OBEX_HEADER_NAME                           = 0x01, /* Name of the object */
     CLX_OBEX_HEADER_IMG_HANDLE                     = 0x30, /* Image handle */
     CLX_OBEX_HEADER_IMG_DESCRIPTOR                 = 0x71, /* Image Descriptor */
     CLX_OBEX_HEADER_TYPE                           = 0x42, /* Type of the object */
     CLX_OBEX_HEADER_LENGTH                         = 0xc3, /* Total lenght of object */
     CLX_OBEX_HEADER_TIME                           = 0x44, /* Last modification time of (ISO8601) */
     CLX_OBEX_HEADER_TIME2                          = 0xC4, /* Deprecated use HDR_TIME instead */
     CLX_OBEX_HEADER_DESCRIPTION                    = 0x05, /* Description of object */
     CLX_OBEX_HEADER_TARGET                         = 0x46, /* Identifies the target for the object */
     CLX_OBEX_HEADER_HTTP                           = 0x47, /* An HTTP 1.x header */
     CLX_OBEX_HEADER_BODY                           = 0x48, /* Data part of the object */
     CLX_OBEX_HEADER_BODY_END                       = 0x49, /* Last data part of the object */
     CLX_OBEX_HEADER_WHO                            = 0x4a, /* Identifies the sender of the object */
     CLX_OBEX_HEADER_CONNECTION                     = 0xcb, /* Connection identifier */
     CLX_OBEX_HEADER_APPARAM                        = 0x4c, /* Application parameters */
     CLX_OBEX_HEADER_AUTHCHAL                       = 0x4d, /* Authentication challenge */
     CLX_OBEX_HEADER_AUTHRESP                       = 0x4e, /* Authentication response */
     CLX_OBEX_HEADER_CREATOR                        = 0xcf, /* indicates the creator of an object */
     CLX_OBEX_HEADER_WANUUID                        = 0x50, /* uniquely identifies the network client (OBEX server) */
     CLX_OBEX_HEADER_ID_SRM                         = 0x97, /* response mode selection */
     CLX_OBEX_HEADER_ID_SRM_FLAGS                   = 0x98, /* flags for single response mode */
     CLX_OBEX_HEADER_OBJECTCLASS                    = 0x51, /* OBEX Object class of object */
     CLX_OBEX_HEADER_SESSIONPARAM                   = 0x52  /* Parameters used in session commands/responses */
#define CLX_OBEX_HEADER_SESSIONSEQ                    0x93  /* Sequence number used in each OBEX packet for reliability */
} ClxObexHeader;

typedef enum ScoPacketTypeParameterEnum
{
    USE_PT_HV1                                      = 0x0001,    /*!< HV1 may be used */
    USE_PT_HV2                                      = 0x0002,    /*!< HV2 may be used */
    USE_PT_HV3                                      = 0x0004,    /*!< HV3 may be used */
    USE_PT_EV3                                      = 0x0008,    /*!< EV3 may be used */
    USE_PT_EV4                                      = 0x0010,    /*!< EV4 may be used */
    USE_PT_EV5                                      = 0x0020,    /*!< EV5 may be used */
    NOT_USE_PT_2_EV3                                = 0x0040,    /*!< 2-EV3 may not be used */
    NOT_USE_PT_3_EV3                                = 0x0080,    /*!< 3-EV3 may not be used */
    NOT_USE_PT_2_EV5                                = 0x0100,    /*!< 2-EV5 may not be used */
    NOT_USE_PT_3_EV5                                = 0x0200     /*!< 3-EV5 may not be used */
} ScoPacketTypeParameter;

#define CLX_ALL_AVAILABLE_SCO_PACKETS                 0xFFFF


typedef enum ClxBluetoothCodingFormatEnum
{
    ClxBluetoothCodingFormat_uLaw                   = 0x00,
    ClxBluetoothCodingFormat_aLaw                   = 0x01,
    ClxBluetoothCodingFormat_CVSD                   = 0x02,
    ClxBluetoothCodingFormat_Transparent            = 0x03,     /*!< Indicates that the controller does not do any transcoding or re-sampling.
                                                                     See the command description for restrictions on the use of this value */
    ClxBluetoothCodingFormat_LinearPCM              = 0x04,
    ClxBluetoothCodingFormat_mSBC                   = 0x05,
    ClxBluetoothCodingFormat_LC3                    = 0x06,
    ClxBluetoothCodingFormat_G_729A                 = 0x07,
    ClxBluetoothCodingFormat_VendorSpecific         = 0xFF      /*!< The codec is vendor-specific, as defined by ClxBluetoothCodec */ 
} ClxBluetoothCodingFormat;


typedef enum ClxBluetoothPcmDataFormatEnum
{
    ClxBluetoothPcmDataFormat_NA                    = 0x00,     /*!< This value does not apply to the coding format in use */
    ClxBluetoothPcmDataFormat_1sComplement          = 0x01,
    ClxBluetoothPcmDataFormat_2sComplement          = 0x02,
    ClxBluetoothPcmDataFormat_SignMagnitude         = 0x03,
    ClxBluetoothPcmDataFormat_Unsigned              = 0x04
} ClxBluetoothPcmDataFormat;


typedef enum ClxBluetoothPcmSampleSizeEnum
{    ClxBluetoothPcmSampleSize_8Bits = 0,
    ClxBluetoothPcmSampleSize_16Bits = 1,
    ClxBluetoothPcmSampleSize_24Bits = 2,
    ClxBluetoothPcmSampleSize_32Bits = 3,
} ClxBluetoothPcmSampleSize;


typedef enum ClxScoAirCodingFormatEnum
{   ClxScoAirCodingFormat_uLaw              = 0,
    ClxScoAirCodingFormat_aLaw              = 1,
    ClxScoAirCodingFormat_CVSD              = 2,
    ClxScoAirCodingFormat_TransparentData   = 3,
    ClxScoAirCodingFormat_Unknwon           = 0xFF
} ClxScoAirCodingFormat;


 /** User configurable Audio Channel parameters are used in HSP Audio Gateway profile,
     in addition, they are also used in HFP/HF and HFP/AG profiles 

     Voice Setting is a 16 bit field with the following structure;
     - 00XXXXXXXX Input Coding: Linear
     - 01XXXXXXXX Input Coding: u-law Input Coding
     - 10XXXXXXXX Input Coding: A-law Input Coding
     - 11XXXXXXXX Reserved for future use
     - XX00XXXXXX Input Data Format: 1's complement
     - XX01XXXXXX Input Data Format: 2's complement
     - XX10XXXXXX Input Data Format: Sign-Magnitude
     - XX11XXXXXX Input Data Format: Unsigned
     - XXXX0XXXXX Input Sample Size: 8-bit (only for linear PCM)
     - XXXX1XXXXX Input Sample Size: 16-bit (only for linear PCM)
     - XXXXXnnnXX Linear_PCM_Bit_Pos: # bit positions that MSB of sample is away from starting at MSB (only for Linear PCM).
     - XXXXXXXX00 Air Coding Format: CVSD
     - XXXXXXXX01 Air Coding Format: u-law
     - XXXXXXXX10 Air Coding Format: A-law
     - XXXXXXXX11 Air Coding Format: Transparent Data
*/
typedef struct ClxBluetoothAudioChannelParams
{
    u4 transmitBandwidth;
    u4 receiveBandwidth;
    u2 maxLatency;
    u2 voiceSetting;
    u2 packetType;
    u1 retransmissionEffort;
} ClxBluetoothAudioChannelParams;

typedef struct ClxBluetoothCodecStruct
{
    ClxBluetoothCodingFormat    format;             /*!< The coding format */
    u2                          companyID;          /*!< The company to which the codec belongs. 
                                                         Defined on https://www.bluetooth.com/specifications/assigned-numbers/company-identifiers/ */
    u2                          vendorSpecificID;   /* Vendor specific codec ID. Shall be ignored if the coding format is not #ClxBluetoothCodingFormat_VendorSpecific */
} ClxBluetoothCodec;


#ifdef __cplusplus
}
#endif

#endif // _ClarinoxBlueConst_h_

