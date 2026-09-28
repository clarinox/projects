#ifndef _ClarinoxBlueErrorCodes_
#define _ClarinoxBlueErrorCodes_

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                ClarinoxBlueErrorCodes.h
* Description         Declares ClarinoxBlue errors
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#include "ClarinoxErrorCodes.h"


#define CLX_CLARINOX_BLUE_ERROR_CODE_BASE												0x2000
#define CLX_CLARINOX_BLUE_ERROR_CODE_END												0x2800  /* 2048 error codes are reserved for ClarinoxBlue */


#define CLX_ERROR_CLARINOX_BLUE_FAILED                                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 0)
#define CLX_ERROR_CLARINOX_BLUE_TERMINATED                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 1)
#define CLX_ERROR_INVALID_DEVICE_ID                                                     (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 2)
#define CLX_ERROR_DEVICE_ALREADY_PAIRED                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 3)
#define CLX_ERROR_INQUIRY_IN_PROGRESS                                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 4)
#define CLX_ERROR_INVALID_COMMAND_PARAMETER                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 5)
#define CLX_ERROR_INQUIRY_NOT_IN_PROGRESS                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 6)
#define CLX_ERROR_GAP_PROCEDURE_IN_PROGRESS                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 7)
#define CLX_ERROR_GAP_CONNECTION_NOT_SUCCESSFUL                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 8)
#define CLX_ERROR_GAP_LOCAL_DEVICE_NOT_BONDABLE                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 9)
#define CLX_ERROR_GAP_REMOTE_DEVICE_NOT_BONDABLE                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 10)
#define CLX_ERROR_SERVICE_DISCOVERY_FAILED                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 11)
#define CLX_ERROR_SERVICE_DISCOVERY_IN_PROGRESS                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 12)
#define CLX_ERROR_NOT_SUPPORTED_BY_REMOTE_MACHINE                                       (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 13)
#define CLX_ERROR_OBEX_OBJECT_TRANSFER_IN_PROGRESS                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 14)
#define CLX_ERROR_SPP_UNDISCOVERED_COM_PORT                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 15)

#define CLX_ERROR_AUDIO_CONNECTION_EXISTS                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 16)
#define CLX_ERROR_AUDIO_CONNECTION_NOT_EXIST                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 17)
#define CLX_ERROR_AUDIO_CONNECTION_IN_PROGRESS                                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 18)
#define CLX_ERROR_AUDIO_DISCONNECTION_IN_PROGRESS                                       (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 19)
#define CLX_ERROR_AUDIO_CONNECTION_FAILED                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 20)

#define CLX_ERROR_MCE_NO_BOUND_DEVICE                                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 21)
#define CLX_ERROR_MCE_BINDING_IN_PROGRESS                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 22)
#define CLX_ERROR_MCE_UNBINDING_IN_PROGRESS                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 23)
#define CLX_ERROR_MCE_ALREADY_BOUND                                                     (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 24)
#define CLX_ERROR_MCE_NO_SERVERS_AVAILABLE                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 25)
#define CLX_ERROR_MCE_INVALID_SERVER_ID                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 26)

#define CLX_ERROR_OBEX_APP_PARAMS_TOO_BIG                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 27)
#define CLX_ERROR_OBEX_BAD_REQUEST                                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 28)
#define CLX_ERROR_OBEX_NOT_FOUND                                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 29)
#define CLX_ERROR_OBEX_FORBIDDEN                                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 30)
#define CLX_ERROR_OBEX_INTERNAL_SERVER_ERROR                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 31)
#define CLX_ERROR_OBEX_UNAUTHORIZED                                                     (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 32)
#define CLX_ERROR_OBEX_OPERATION_ABORTED                                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 33)
#define CLX_ERROR_OBEX_NOT_ACCEPTABLE                                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 34)

#define CLX_ERROR_A2DP_SIGNALING_CONN_DROPPED                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 35)
#define CLX_ERROR_A2DP_STREAMING_CONN_DROPPED                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 36)
#define CLX_ERROR_A2DP_SIGNALING_TIMEOUT                                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 37)
#define CLX_ERROR_A2DP_NO_MATCHING_ENDPOINT                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 38)
#define CLX_ERROR_A2DP_WRONG_STATE                                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 39)
#define CLX_ERROR_A2DP_ALREADY_CONNECTED                                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 40)
#define CLX_ERROR_A2DP_CONNECTING                                                       (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 41)
#define CLX_ERROR_A2DP_INVALID_STATE                                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 42)
#define CLX_ERROR_A2DP_ENDPOINT_IN_USE                                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 43)
#define CLX_ERROR_A2DP_LOCAL_SERVICE_ACCEPTOR                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 44)
#define CLX_ERROR_A2DP_CONFIG_NOT_SUPPORTED_BY_REMOTE_MACHINE                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 45)
#define CLX_ERROR_A2DP_CONFIG_NOT_SUPPORTED_BY_LOCAL_CODEC                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 46)
#define CLX_ERROR_A2DP_PLAYING                                                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 47)
#define CLX_ERROR_A2DP_PAUSED                                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 48)
#define CLX_ERROR_A2DP_ABORTED                                                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 49)
#define CLX_ERROR_A2DP_INVALID_MEDIA_CODEC                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 50)


#define CLX_ERROR_HFP_AG_CALL_SETUP_IN_PROGRESS                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 51)
#define CLX_ERROR_HFP_AG_CALL_IS_ACTIVE                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 52)
#define CLX_ERROR_HFP_AG_NO_CALL_IS_ACTIVE                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 53)
#define CLX_ERROR_HFP_AG_NO_OUTGOING_CALL_SETUP                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 54)
#define CLX_ERROR_HFP_AG_NO_OUTGOING_CALL_REQUEST_PENDING                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 55)
#define CLX_ERROR_HFP_AG_NO_INCOMING_CALL_REQUEST_PENDING                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 56)
#define CLX_ERROR_HFP_AG_INBAND_RING_NOT_SUPPORTED                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 57)
#define CLX_ERROR_HFP_AG_CALL_WITH_SAME_INDEX_EXISTS                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 58)
#define CLX_ERROR_HFP_AG_INVALID_CALL_INDEX                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 59)
#define CLX_ERROR_HFP_AG_CALL_CANNOT_BE_ACTIVATED                                       (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 60)

#define CLX_ERROR_HFP_HF_WRONG_STATE                                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 61)
#define CLX_ERROR_HFP_HF_SUBSCRIBER_NUM_INFO_NOT_SUPPORTED_IN_AG                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 62)
#define CLX_ERROR_HFP_HF_VOICE_RECOGNITION_NOT_SUPPORTED_IN_AG                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 63)
#define CLX_ERROR_HFP_HF_CALLING_LINE_ID_NOT_SUPPORTED_IN_AG                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 64)
#define CLX_ERROR_HFP_HF_FEATURE_NOT_SUPPORTED_IN_AG                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 65)
#define CLX_ERROR_HFP_HF_FEATURE_NOT_SUPPORTED_IN_HF                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 66)
#define CLX_ERROR_HFP_HF_REQUEST_DENIED_BY_AG                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 67)

#define CLX_ERROR_AVRCP_NOT_SUPPORTED_IN_TARGET                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 68)

#define CLX_ERROR_BLE_ATT_INVALID_BASE_HANDLE                              				(CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 69)
#define CLX_ERROR_BLE_ATT_INTERNAL_ERROR                                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 70)
#define CLX_ERROR_BLE_ATT_INVALID_HANDLE                                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 71)
#define CLX_ERROR_BLE_ATT_READ_NOT_PERMITTED                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 72)
#define CLX_ERROR_BLE_ATT_WRITE_NOT_PERMITTED                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 73)
#define CLX_ERROR_BLE_ATT_INVALID_PDU                                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 74)
#define CLX_ERROR_BLE_ATT_INSUFFICIENT_AUTHENTICATION                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 75)
#define CLX_ERROR_BLE_ATT_REQUEST_NOT_SUPPORTED                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 76)
#define CLX_ERROR_BLE_ATT_INVALID_OFFSET                                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 77)
#define CLX_ERROR_BLE_ATT_INSUFFICIENT_AUTHORIZATION                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 78)
#define CLX_ERROR_BLE_ATT_PREPARE_QUEUE_FULL                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 79)
#define CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_FOUND                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 80)
#define CLX_ERROR_BLE_ATT_ATTRIBUTE_NOT_LONG                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 81)
#define CLX_ERROR_BLE_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 82)
#define CLX_ERROR_BLE_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 83)
#define CLX_ERROR_BLE_ATT_UNLIKELY_ERROR                                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 84)
#define CLX_ERROR_BLE_ATT_INSUFFICIENT_ENCRYPTION                                       (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 85)
#define CLX_ERROR_BLE_ATT_UNSUPPORTED_GROUP_TYPE                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 86)
#define CLX_ERROR_BLE_ATT_INSUFFICIENT_RESOURCES                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 87)
#define CLX_ERROR_BLE_CODEC_NOT_IMPLEMENTED                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 88)
#define CLX_ERROR_BLE_WRONG_ENCODED_DATA_LENGTH                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 89)
#define CLX_ERROR_BLE_NOT_CHARACTERISTIC_VALUE_ATTRIBUTE                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 90)

#define CLX_ERROR_AVRCP_INSUFFICIENT_MINIMUM_BUFFER_MEMORY                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 91)
#define CLX_ERROR_AVRCP_CORRUPTED_BROWSE_RESPONSE_PACKET                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 92)

#define CLX_ERROR_NETWORK_SERVICE_INTERFACE_IN_WRONG_STATUS                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 93)

#define CLX_ERROR_IPSP_NOT_SUPPORTED_BY_LOCAL_ROLE                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 94)
#define CLX_ERROR_IPSP_INTERFACE_ALREADY_STARTED                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 95)
#define CLX_ERROR_IPSP_INTERFACE_NOT_STARTED                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 96)
#define CLX_ERROR_IPSP_NO_PHYSICAL_LINK_TO_PERIPHERAL                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 97)
#define CLX_ERROR_IPSP_CONNECTION_LIMIT_REACHED                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 98)
#define CLX_ERROR_IPSP_ANOTHER_PROCEDURE_IN_PROGRESS                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 99)

#define CLX_ERROR_BLE_SMP_PASSKEY_ENTRY_FAILED                                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 100)
#define CLX_ERROR_BLE_SMP_OOB_NOT_AVAILABLE                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 101)
#define CLX_ERROR_BLE_SMP_AUTHENTICATION_REQUIREMENTS                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 102)
#define CLX_ERROR_BLE_SMP_CONFIRM_VALUE_FAILED                                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 103)
#define CLX_ERROR_BLE_SMP_PAIRING_NOT_SUPPORTED                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 104)
#define CLX_ERROR_BLE_SMP_ENCRYPTION_KEY_SIZE                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 105)
#define CLX_ERROR_BLE_SMP_COMMAND_NOT_SUPPORTED                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 106)
#define CLX_ERROR_BLE_SMP_UNSPECIFIED_REASON                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 107)
#define CLX_ERROR_BLE_SMP_REPEATED_ATTEMPTS                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 108)
#define CLX_ERROR_BLE_SMP_INVALID_PARAMETERS                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 109)

#define CLX_ERROR_BLE_DEVICE_NOT_PAIRED                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 110)
#define CLX_ERROR_BLE_DEVICE_NOT_FOUND                                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 111)

#define CLX_ERROR_BLE_GATT_NOT_SUPPORTED_BY_LOCAL_ROLE                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 112)
#define CLX_ERROR_BLE_GATT_CLIENT_NOT_BOUND                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 113)
#define CLX_ERROR_BLE_GATT_CLIENT_ALREADY_BOUND                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 114)
#define CLX_ERROR_BLE_GATT_DEVICE_ALREADY_BOUND                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 115)
#define CLX_ERROR_BLE_GATT_WRONG_STATE                                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 116)
#define CLX_ERROR_BLE_GATT_INVALID_CHARACTERISTIC                                       (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 117)
#define CLX_ERROR_BLE_GATT_NO_EVENT_PENDING                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 118)
#define CLX_ERROR_BLE_GATT_WRITE_INTEGRITY_CHECK_FAILED                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 119)

#define CLX_ERROR_HID_DEVICE_NOT_READY                                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 120)
#define CLX_ERROR_HID_INVALID_REPORT_ID                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 121)
#define CLX_ERROR_HID_UNSUPPORTED_REQUEST                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 122)
#define CLX_ERROR_HID_INVALID_PARAMETER                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 123)
#define CLX_ERROR_HID_UNKNOWN                                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 124)
#define CLX_ERROR_HID_FATAL                                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 125)
#define CLX_ERROR_HID_CONTROL_CONNECTION_FAILED                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 126)
#define CLX_ERROR_HID_INTERRUPT_CONNECTIION_FAILED                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 127)
#define CLX_ERROR_HID_CONTROL_DISCONNECTION_FAILED                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 128)
#define CLX_ERROR_HID_INTERRUPT_DISCONNECTIION_FAILED                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 129)

#define CLX_ERROR_PAN_NOT_SUPPORTED_BY_REMOTE_DEVICE                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 130)
#define CLX_ERROR_PAN_INTERFACE_NOT_INITIATED                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 131)
#define CLX_ERROR_PAN_INTERFACE_NOT_STARTED                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 132)

#define CLX_ERROR_HFP_AG_INDICATORS_NOT_SUPPORTED_BY_HF                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 133)
#define CLX_ERROR_HFP_HF_INDICATORS_NOT_SUPPORTED_BY_AG                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 134)
#define CLX_ERROR_HFP_HF_INDICATORS_DISABLED_IN_AG                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 135)
#define CLX_ERROR_HFP_HF_INDICATOR_VALUE_OUT_OF_RANGE                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 136)
#define CLX_ERROR_HFP_INDICATOR_INVALID                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 137)

#define CLX_ERROR_BIP_OBEX_INTERNAL_ERROR                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 138)
#define CLX_ERROR_BIP_SDP_ERROR                                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 139)
#define CLX_ERROR_BIP_ANOTHER_OPERATION_INPROGRESS                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 140)
#define CLX_ERROR_BIP_INVALID_OPERATION                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 141)

#define CLX_ERROR_AVRCP_BROWSING_NOT_SUPPORTED_IN_LOCAL_DEVICE                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 142)

#define CLX_ERROR_PAN_ALREADY_CONNECTED                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 143)
#define CLX_ERROR_PAN_NOT_CONNECTED                                                     (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 144)

#define CLX_ERROR_BLE_SMP_IR_PARAMETER_NOT_CONFIGURED                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 145)
#define CLX_ERROR_BLE_REMOTE_DEVICE_NOT_FOUND_BY_IDENTITY_ADDRESS                       (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 146)

#define CLX_ERROR_CTN_ALREADY_CONNECTED                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 147)
#define CLX_ERROR_CTN_NOT_SUPPORTED_BY_REMOTE_DEVICE                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 148)
#define CLX_ERROR_CTN_NOT_INITIALIZED                                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 149)
#define CLX_ERROR_CTN_ERROR_SERVICE_DISCOVERY                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 150)

#define CLX_ERROR_BLE_SMP_DHKY_CHECKVALUE_FAILED                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 151)
#define CLX_ERROR_BLE_SMP_NUMERIC_COMPARISON_FAILED                                     (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 152)
#define CLX_ERROR_BLE_SMP_BREDR_PAIRING_INPROGRESS                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 153)
#define CLX_ERROR_BLE_SMP_CROSS_TRANSPORT_KEY_DERIVATION_NOT_ALLOWED                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 154)

#define CLX_ERROR_GAP_PAIRED_DEVICES_COUNT_MAX_LIMIT_REACHED                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 155)
#define CLX_ERROR_SERVICE_NOT_SUPPORTED_BY_REMOTE_DEVICE                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 156)

#define CLX_ERROR_AVRCP_BROWSING_NOT_SUPPORTED_IN_TARGET_DEVICE                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 157)
#define CLX_ERROR_HFP_HF_AG_INITIATES_AUDIO_CONNECTION                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 158)

#define CLX_ERROR_OBEX_NOT_IMPLEMENTED                                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 159)
#define CLX_ERROR_OBEX_SERVICE_UNAVAILABLE                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 160)
#define CLX_ERROR_OBEX_VERSION_NOT_SUPPORTED                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 161)

#define CLX_ERROR_SLC_DISCONNECTED                                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 162)
#define CLX_ERROR_OBEX_NO_OBJECT_TRANSFER_IN_PROGRESS                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 163)
#define CLX_ERROR_OPERATION_TIMED_OUT                                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 164)

#define CLX_ERROR_HCI_RESET_COMMAND_NO_RESPONSE											(CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 165)
#define CLX_ERROR_HCI_VENDOR_BAUD_RATE_SET_FAILED										(CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 166)
#define CLX_ERROR_HCI_VENDOR_FIRMWARE_DOWNLOAD_UNSUCCESSFUL								(CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 167)
#define CLX_ERROR_HCI_VENDOR_COMMAND_UNSUCCESSFUL										(CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 168)

#define CLX_ERROR_TRANSPORT_USB_PORT_OPEN_UNSUCCESSFUL									(CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 169)

#define CLX_ERROR_HID_NOT_SUPPORTED_BY_REMOTE_DEVICE                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 170)
#define CLX_ERROR_HID_SDP_REQUEST_TO_REMOTE_DEVICE_FAILED                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 171)

#define CLX_ERROR_BLE_REMOTE_DEVICE_NAME_NOT_FOUND                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 172)

#define CLX_ERROR_AVRCP_REMOTE_DEVICE_ERROR                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 173)
#define CLX_ERROR_AVRCP_INTERNAL                                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 174)

#define CLX_ERROR_AVRCP_UTILITY_END_OF_BUFFER_REACHED                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 175)
#define CLX_ERROR_AVRCP_UTILITY_PARSE_BUFFER_NOT_SET                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 176)
#define CLX_ERROR_AVRCP_UTILITY_ERROR_PARSE_BUFFER_CORRUPTED                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 177)

#define CLX_ERROR_BLE_MESH_NO_ROUTE_FOR_PDU                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 178)
#define CLX_ERROR_BLE_MESH_UNAUTHORISED_NETWORK_LINK_HANDLE                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 179)
#define CLX_ERROR_BLE_MESH_UNKNOWN_GLOBAL_NETWORK_KEY_INDEX                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 180)
#define CLX_ERROR_BLE_MESH_UNKNOWN_APPLICATION_KEY_HANDLE                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 181)
#define CLX_ERROR_BLE_MESH_MESSAGE_TOO_BIG                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 182)
#define CLX_ERROR_BLE_MESH_NO_LOCAL_ELEMENT                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 183)
#define CLX_ERROR_BLE_MESH_CANCELED_BY_REMOTE_DEVICE                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 184)
#define CLX_ERROR_BLE_MESH_ACK_FAILED                                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 185)
#define CLX_ERROR_BLE_MESH_LINK_FAILED                                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 186)
#define CLX_ERROR_BLE_MESH_OPERATION_NOT_ALLOWED                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 187)
#define CLX_ERROR_BLE_MESH_PROVISIONING_INTERNAL_ERROR                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 188)
#define CLX_ERROR_BLE_MESH_PROVISIONING_AUTHENTICATION_FAILED                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 189)
#define CLX_ERROR_BLE_MESH_PROVISIONING_OUT_OF_RESOURCES_ERROR                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 190)
#define CLX_ERROR_BLE_MESH_PROVISIONING_TIMED_OUT_ERROR                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 191)
#define CLX_ERROR_BLE_MESH_PROVISIONING_CONNECTION_LOST_ERROR                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 192)
#define CLX_ERROR_BLE_MESH_PROVISIONING_INVALID_OPERATION                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 193)
#define CLX_ERROR_BLE_MESH_PROXY_INVALID_PDU_DATA                                       (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 194)
#define CLX_ERROR_BLE_MESH_MODEL_REQUEST_CANCELLED                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 195)

/**
This error code will be thrown when receiving the invalid response from remote device
*/
#define CLX_ERROR_BLE_ATT_UNEXPECTED_RESPONSE                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 196)

#define CLX_ERROR_BLE_MESH_MODEL_NOT_SUPPORTED                                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 197)
#define CLX_ERROR_BLE_MESH_MODEL_MESSAGE_NOT_SUPPORTED                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 198)

#define CLX_ERROR_L2CAP_REFUSED_BAD_PSM                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 199)
#define CLX_ERROR_L2CAP_REFUSED_SECURITY                                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 200)
#define CLX_ERROR_L2CAP_REFUSED_NO_RESOURCE                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 201)
#define CLX_ERROR_L2CAP_UNKNOWN                                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 202)
#define CLX_ERROR_L2CAP_NO_LOCAL_RESOURCE                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 203)
#define CLX_ERROR_L2CAP_TIMEOUT                                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 204)
#define CLX_ERROR_L2CAP_ALREADY_EXISTS                                                  (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 205)
#define CLX_ERROR_L2CAP_ACL_FAILED                                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 206)
#define CLX_ERROR_L2CAP_AUTHENTICATION_FAILED                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 207)
#define CLX_ERROR_L2CAP_AUTHERIZATION_FAILED                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 208)
#define CLX_ERROR_L2CAP_UNKNOWN_COMMAND                                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 209)
#define CLX_ERROR_L2CAP_SIGNAL_MTU_TOO_BIG                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 210)
#define CLX_ERROR_L2CAP_INVALID_CID_IN_REQUEST                                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 211)
#define CLX_ERROR_L2CAP_INSUFFICIENT_CHUNKS                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 212)
#define CLX_ERROR_L2CAP_MALFORMED_PACKET                                                (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 213)
#define CLX_ERROR_L2CAP_ALREADY_DISCONNECTED                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 214)
#define CLX_ERROR_L2CAP_WRONG_STATE                                                     (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 215)

#define CLX_ERROR_AUTHENTICATION_FAIL                                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 216)
#define CLX_ERROR_AUTHENTICATION_FAIL_FATAL                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 217)
#define CLX_ERROR_AUTHENTICATION_FAIL_AUTHENTICATION_COMMAND_NOT_SUPPORTED              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 218)
#define CLX_ERROR_AUTHENTICATION_FAIL_NO_ACL                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 219)
#define CLX_ERROR_AUTHENTICATION_FAIL_ACL_FAILED                                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 220)
#define CLX_ERROR_AUTHENTICATION_FAIL_FEATURES_COLLECTION_FAILED                        (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 221)
#define CLX_ERROR_AUTHENTICATION_FAIL_SECURITY_LEVEL_NOT_ACHIEVED                       (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 222)
#define CLX_ERROR_AUTHENTICATION_FAIL_ENCRYPTION_FAILED                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 223)
#define CLX_ERROR_AUTHENTICATION_FAIL_STACK_SHUT_DOWN                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 224)

#define CLX_ERROR_BLE_MESH_FRIENDSHIP_ESTABLISHMENT_TIMEOUT                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 225)
#define CLX_ERROR_BLE_MESH_FRIENDSHIP_ALREADY_ESTABLISHED                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 226)
#define CLX_ERROR_BLE_MESH_FRIENDSHIP_INVALID_LPN_WAKEUP_TIME                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 227)
#define CLX_ERROR_BLE_MESH_FRIENDSHIP_INVALID_LPN_POLLTIMEOUT                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 228)
#define CLX_ERROR_BLE_MESH_NO_ACTIVE_FRIENDSHIP                                         (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 229)
#define CLX_ERROR_BLE_MESH_FRIENDSHIP_TERMINATE_TIMEOUT                                 (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 230)
#define CLX_ERROR_BLE_MESH_FRIENDSHIP_SUBSCRIPTION_TIMEOUT                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 231)
#define CLX_ERROR_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE                                   (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 232)
#define CLX_ERROR_BLE_NO_MORE_EXTENDED_ADVERTISING_SET                                      (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 233)

#define CLX_ERROR_BLE_ISO_STREAM_NOT_EXIST                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 234)
#define CLX_ERROR_BLE_ISO_GROUP_NOT_EXIST                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 235)
#define CLX_ERROR_BLE_CIS_NOT_ESTABLISHED                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 236)
#define CLX_ERROR_BLE_INVALID_ISO_GROUP_ID                                              (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 237)
#define CLX_ERROR_BLE_INVALID_ISO_STREAM_ID                                             (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 238)
#define CLX_ERROR_BLE_DUPLICATE_ISO_STREAM_ID                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 239)
#define CLX_ERROR_BLE_CIS_ALREADY_CREATED                                               (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 240)
#define CLX_ERROR_BLE_DUPLICATE_ISO_GROUP_ID                                            (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 241)

#define CLX_ERROR_BLE_ADVERTISING_REPORT_QUEUE_EMPTY                                    (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 242)

#define CLX_ERROR_AVRCP_FEATURE_NOT_SUPPORTED_IN_TARGET_DEVICE                          (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 243)

#define CLX_ERROR_BLE_ATT_REQUEST_NOT_ALLOWED											(CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 244)


/** 
Error codes CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE to (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x100) 
are directly mapped to Bluetooth standard HCI error codes: 
*/ 
#define CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE                                           (CLX_CLARINOX_BLUE_ERROR_CODE_BASE + 0x700)

#define CLX_ERROR_HCI_UNKNOWN_HCI_COMMAND                                               (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x01)
#define CLX_ERROR_HCI_UNKNOWN_CONNECTION_IDENTIFIER                                     (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x02)
#define CLX_ERROR_HCI_HARDWARE_FAILURE                                                  (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x03)
#define CLX_ERROR_HCI_PAGE_TIMEOUT                                                      (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x04)
#define CLX_ERROR_HCI_AUTHENTICATION_FAILURE                                            (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x05)
#define CLX_ERROR_HCI_PIN_OR_KEY_MISSING                                                (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x06)
#define CLX_ERROR_HCI_MEMORY_CAPACITY_EXCEEDED                                          (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x07)
#define CLX_ERROR_HCI_CONNECTION_TIMEOUT                                                (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x08)
#define CLX_ERROR_HCI_CONNECTION_LIMIT_EXCEEDED                                         (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x09)
#define CLX_ERROR_HCI_SYNCHRONOUS_CONNECTION_LIMIT_TO_A_DEVICE_EXCEEDED                 (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x0A)
#define CLX_ERROR_HCI_ACL_CONNECTION_ALREADY_EXISTS                                     (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x0B)
#define CLX_ERROR_HCI_COMMAND_DISALLOWED                                                (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x0C)
#define CLX_ERROR_HCI_CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES                      (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x0D)
#define CLX_ERROR_HCI_CONNECTION_REJECTED_DUE_TO_SECURITY_REASONS                       (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x0E)
#define CLX_ERROR_HCI_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR                   (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x0F)
#define CLX_ERROR_HCI_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED                                (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x10)
#define CLX_ERROR_HCI_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE                            (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x11)
#define CLX_ERROR_HCI_INVALID_HCI_COMMAND_PARAMETERS                                    (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x12)
#define CLX_ERROR_HCI_REMOTE_USER_TERMINATED_CONNECTION                                 (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x13)
#define CLX_ERROR_HCI_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES          (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x14)
#define CLX_ERROR_HCI_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_POWER_OFF              (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x15)
#define CLX_ERROR_HCI_CONNECTION_TERMINATED_BY_LOCAL_HOST                               (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x16)
#define CLX_ERROR_HCI_REPEATED_ATTEMPTS                                                 (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x17)
#define CLX_ERROR_HCI_PAIRING_NOT_ALLOWED                                               (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x18)
#define CLX_ERROR_HCI_UNKNOWN_LMP_PDU                                                   (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x19)
#define CLX_ERROR_HCI_UNSUPPORTED_REMOTE_FEATURE_UNSUPPORTED_LMP_FEATURE                (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x1A)
#define CLX_ERROR_HCI_SCO_OFFSET_REJECTED                                               (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x1B)
#define CLX_ERROR_HCI_SCO_INTERVAL_REJECTED                                             (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x1C)
#define CLX_ERROR_HCI_SCO_AIR_MODE_REJECTED                                             (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x1D)
#define CLX_ERROR_HCI_INVALID_LMP_PARAMETERS_INVALID_LL_PARAMETERS                      (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x1E)
#define CLX_ERROR_HCI_UNSPECIFIED_ERROR                                                 (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x1F)
#define CLX_ERROR_HCI_UNSUPPORTED_LMP_PARAMETER_VALUE_UNSUPPORTED_LL_PARAMETER_VALUE    (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x20)
#define CLX_ERROR_HCI_ROLE_CHANGE_NOT_ALLOWED                                           (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x21)
#define CLX_ERROR_HCI_LMP_RESPONSE_TIMEOUT_LL_RESPONSE_TIMEOUT                          (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x22)
#define CLX_ERROR_HCI_LMP_ERROR_TRANSACTION_COLLISION                                   (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x23)
#define CLX_ERROR_HCI_LMP_PDU_NOT_ALLOWED                                               (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x24)
#define CLX_ERROR_HCI_ENCRYPTION_MODE_NOT_ACCEPTABLE                                    (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x25)
#define CLX_ERROR_HCI_LINK_KEY_CANNOT_BE_CHANGED                                        (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x26)
#define CLX_ERROR_HCI_REQUESTED_QOS_NOT_SUPPORTED                                       (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x27)
#define CLX_ERROR_HCI_INSTANT_PASSED                                                    (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x28)
#define CLX_ERROR_HCI_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED                               (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x29)
#define CLX_ERROR_HCI_DIFFERENT_TRANSACTION_COLLISION                                   (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x2A)
/* #define CLX_ERROR_HCI_RESERVED_2B                                                    (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x2B) */
#define CLX_ERROR_HCI_QOS_UNACCEPTABLE_PARAMETER                                        (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x2C)
#define CLX_ERROR_HCI_QOS_REJECTED                                                      (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x2D)
#define CLX_ERROR_HCI_CHANNEL_CLASSIFICATION_NOT_SUPPORTED                              (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x2E)
#define CLX_ERROR_HCI_INSUFFICIENT_SECURITY                                             (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x2F)
#define CLX_ERROR_HCI_PARAMETER_OUT_OF_MANDATORY_RANGE                                  (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x30)
/* #define CLX_ERROR_HCI_RESERVED_31                                                    (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x31) */
#define CLX_ERROR_HCI_ROLE_SWITCH_PENDING                                               (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x32)
/* #define CLX_ERROR_HCI_RESERVED_33                                                    (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x33) */
#define CLX_ERROR_HCI_RESERVED_SLOT_VIOLATION                                           (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x34)
#define CLX_ERROR_HCI_ROLE_SWITCH_FAILED                                                (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x35)
#define CLX_ERROR_HCI_EXTENDED_INQUIRY_RESPONSE_TOO_LARGE                               (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x36)
#define CLX_ERROR_HCI_SECURE_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST                       (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x37)
#define CLX_ERROR_HCI_HOST_BUSY_PAIRING                                                 (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x38)
#define CLX_ERROR_HCI_CONNECTION_REJECTED_DUE_TO_NO_SUITABLE_CHANNEL_FOUND              (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x39)
#define CLX_ERROR_HCI_CONTROLLER_BUSY                                                   (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x3A)
#define CLX_ERROR_HCI_UNACCEPTABLE_CONNECTION_PARAMETERS                                (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x3B)
#define CLX_ERROR_HCI_DIRECTED_ADVERTISING_TIMEOUT                                      (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x3C)
#define CLX_ERROR_HCI_CONNECTION_TERMINATED_DUE_TO_MIC_FAILURE                          (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x3D)
#define CLX_ERROR_HCI_CONNECTION_FAILED_TO_BE_ESTABLISHED                               (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x3E)
#define CLX_ERROR_HCI_MAC_CONNECTION_FAILED                                             (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x3F)
#define CLX_ERROR_HCI_COARSE_CLOCK                                                      (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x40)
#define CLX_ERROR_HCI_TYPE0_SUBMAP_NOT_DEFINED                                          (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x41)
#define CLX_ERROR_HCI_UNKNOWN_ADVERTISING_IDENTIFIER                                    (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x42)
#define CLX_ERROR_HCI_LIMIT_REACHED                                                     (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x43)
#define CLX_ERROR_HCI_OPERATION_CANCELLED_BY_HOST                                       (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x44)
#define CLX_ERROR_HCI_PACKET_TOO_LONG                                                   (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x45)
#define CLX_ERROR_HCI_TOO_LATE                                                          (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x46)
#define CLX_ERROR_HCI_TOO_EARLY                                                         (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x47)
#define CLX_ERROR_HCI_INSUFFICIENT_CHANNELS                                             (CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE + 0x48)



#endif // _ClarinoxBlueErrorCodes_
