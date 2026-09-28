#ifndef _GAP_API_H_
#define _GAP_API_H_

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gap.Api.h
* Description         Declares ClarinoxBlue Generic Access Profile API
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

#define CLX_GAP_VENDOR_SPECIFIC_OGF                             0x3F


/**
Refer to #clxGapStartInquiry function.
*/
#define CLX_GAP_START_INQUIRY_COMPLETE                          0x4500

/**
Refer to #clxGapStartLimitedInquiry function.
*/
#define CLX_GAP_START_LIMITED_INQUIRY_COMPLETE                  CLX_GAP_START_INQUIRY_COMPLETE

/**
Refer to #clxGapStopInquiry function.
*/
#define CLX_GAP_STOP_INQUIRY_COMPLETE                           0x4501

/**
Refer to #clxGapInitiateBonding function.
*/
#define CLX_GAP_INITIATE_BONDING_COMPLETE                       0x4503

/**
Refer to #clxGapPinCodeRequestReply function.
*/
#define CLX_GAP_PIN_CODE_REQUEST_REPLY_COMPLETE                 0x4504

/**
Refer to #clxGapAcceptConnectionRequest function.
*/
#define CLX_GAP_ACCEPT_CONNECTION_REQUEST_COMPLETE              0x4505

/**
Refer to #clxGapRejectConnectionRequest function.
*/
#define CLX_GAP_REJECT_CONNECTION_REQUEST_COMPLETE              0x4506

/**
Refer to #clxGapSetDiscoverability function.
*/
#define CLX_GAP_SET_DISCOVERABILITY_COMPLETE                    0x4507

/**
Refer to #clxGapSetConnectability function.
*/
#define CLX_GAP_SET_CONNECTABILITY_COMPLETE                     0x4508

/**
Refer to #clxGapUserPasskeyRequestReply function.
*/    
#define CLX_GAP_USER_PASSKEY_REQUEST_REPLY_COMPLETE             0x450A

/**
Refer to #clxGapUserConfirmationRequestReply function.
*/
#define CLX_GAP_USER_CONFIRMATION_REQUEST_REPLY_COMPLETE        0x450B

/**
Refer to #clxGapDeletePairedDeviceInfo function.
*/
#define CLX_GAP_DELETE_PAIRED_DEVICE_INFO_COMPLETE              0x450C

/**
Refer to #clxGapDeleteAllPairedDevicesInfo function.
*/

#define CLX_GAP_DELETE_ALL_PAIRED_DEVICES_INFO_COMPLETE         0x450D

/**
Refer to #clxGapSetBondability function.
*/
#define CLX_GAP_SET_BONDABILITY_COMPLETE                        0x450E

/**
Refer to #clxGapGetLocalBtAddress function.
*/
#define CLX_GAP_GET_LOCAL_BT_ADDRESS_COMPLETE                   0x450F

/**
Refer to #clxGapDisconnectPhysicalLink function.
*/
#define CLX_GAP_DISCONNECT_PHYSICAL_LINK_COMPLETE               0x4510


/**
Refer to #clxGapWriteConfigurationParameters function.
*/
#define CLX_GAP_WRITE_CONFIGURATION_PARAMETERS_COMPLETE         0x4511


/**
Refer to #clxGapSendHciCommand function.
*/
#define CLX_GAP_SEND_HCI_COMMAND_COMPLETE                       0x4512


/**
Refer to #clxGapRequestRemoteDeviceName function.
*/
#define CLX_GAP_REQUEST_REMOTE_DEVICE_NAME_COMPLETE             0x4513


/**
Refer to #clxGapGetDiscoveredDeviceByIndex function.
*/
#define CLX_GAP_GET_DISCOVERED_DEVICE_BY_INDEX_COMPLETE         0x4514


/**
Refer to #clxGapGetPairedDeviceByIndex function.
*/
#define CLX_GAP_GET_PAIRED_DEVICE_BY_INDEX_COMPLETE             0x4515


/**
Refer to #clxBluetoothClassicEnableDeviceTestMode function.
*/
#define CLX_BLUETOOTH_CLASSIC_ENABLE_DEVICE_TEST_MODE_COMPLETE  0x4516


/**
Used internally.
*/
#define CLX_GAP_RUN_GENERIC_COMMAND_COMPLETE                    0x4517

/**
Refer to #clxGapSetLimitedDiscoverability function.
*/
#define CLX_GAP_SET_LIMITED_DISCOVERABILITY_COMPLETE            0x4518

/**
Refer to #clxGapGetRssiValue function.
*/
#define CLX_GAP_GET_RSSI_VALUE_COMPLETE                         0x4519

/**
This indication is received during inquiry procedure, which indicates
a device has been discovered in the vicinity. A ClxDeviceDetail object will be passed
to the user with this message. This object will be valid until the next clxGapStartInquiry
or clxGapStartLimitedInquiry API function call.

The parameter for this indication is of type #ClxGapDeviceDiscoveredIndication.
*/
#define CLX_GAP_DEVICE_DISCOVERED_INDICATION                0x8510

/**
This indication is received during connection/authentication procedure,
which indicates that the user of the local device must enter a pin code or reject
the authentication request. Upon reception of this indication, the function
#clxGapPinCodeRequestReply MUST be called.

This indication does not have any parameter (params argument of the call-back function
will be NULL).
*/
#define CLX_GAP_PIN_CODE_REQUEST_INDICATION                 0x8511

/**
This indication is received when there is a physical-layer (ACL) connection request
from a remote device. Upon reception of this indication, either the function
#clxGapAcceptConnectionRequest or #clxGapRejectConnectionRequest MUST be called.

This indication does not have any parameter (params argument of the call-back function
will be NULL).
*/
#define CLX_GAP_INCOMING_CONNECTION_REQUEST_INDICATION      0x8512

/**
This indication is received when the physical (ACL) link to a remote device has failed. When the physical link
fails, all service-level connections to the remote device will also fail automatically. Therefore, there is no need
to disconnect the service-level connections manually.

The parameter for this indication is of type #ClxGapLinkDisconnectionIndication.
*/
#define CLX_GAP_LINK_DISCONNECTION_INDICATION               0x8513

/**
This indication is received during authentication procedure when the Bluetooth controller asks the local device
to provide a passkey or reject the authentication request. Upon reception of this indication, the function
#clxGapUserPasskeyRequestReply MUST be called.

The parameter for this indication is of type #ClxGapUserPasskeyRequestIndication.
*/
#define CLX_GAP_USER_PASSKEY_REQUEST_INDICATION             0x8514

/**
This indication is received during authentication procedure when the Bluetooth controller asks the local device
to display a passkey on its display/monitor/LCD. This indication is only received when the local device has display
capabilities. Upon reception of this indication, the local application MUST display the passkey to the user, and must
keep displaying the passkey until the indication #CLX_GAP_PAIRING_COMPLETE_INDICATION is received.

The parameter for this indication is of type #ClxGapUserPasskeyNotificationIndication.
*/
#define CLX_GAP_USER_PASSKEY_NOTIFICATION_INDICATION        0x8515

/**
This indication is received during authentication procedure when the Bluetooth controller asks the local device
to confirm or reject the connection to a remote device. The indication contains a passkey as well. If the local device
has display capabilities, it must display the passkey to the user and asks for confirmation or rejection. Otherwise, it may
directly confirm or reject the request by calling the function #clxGapUserConfirmationRequestReply.

The parameter for this indication is of type #ClxGapUserConfirmationRequestIndication.
*/
#define CLX_GAP_USER_CONFIRMATION_REQUEST_INDICATION        0x8516

/**
This indication is received during authentication procedure when the pairing procedure is complete. In case of legacy pairing, failure will
not cause this indication to occur. Whereas when simple secure pairing is used, this indication will occur either with success
or in error. This indication is received by both the initiator of the authentication procedure, and the responder to the authentication procedure.
If the local device is currently displaying a passkey to the user, or asking the user to provide a passkey, or confirming or rejecting an authentication
request, it may cancel the operation upon reception of this indication.

NOTE:-
The parameter 'isBonded' value as FALSE denotes that the remote device doesn't accept storing pairing information.
In such cases, when there is a need arises to use the pairing information next time, a fresh pairing procedure might be needed.
The parameter of this indication is of type #ClxGapPairingCompleteIndication.
*/
#define CLX_GAP_PAIRING_COMPLETE_INDICATION                 0x8517


/**
Parameter type of following indications:

- #CLX_GAP_DEVICE_DISCOVERED_INDICATION
- #CLX_GAP_PIN_CODE_REQUEST_INDICATION
- #CLX_GAP_INCOMING_CONNECTION_REQUEST_INDICATION
- #CLX_GAP_LINK_DISCONNECTION_INDICATION
- #CLX_GAP_USER_PASSKEY_REQUEST_INDICATION
*/
typedef struct ClxDeviceDetail
{
    s1                          deviceName[CLX_BLUETOOTH_DEVICE_NAME_MAX_LENGTH + 1];               /*!< Name of the device as a null-terminated UTF-8 encoded string */  
    ClxDeviceId                 deviceId;                                                           /*!< The ClarinoxBlue-assigned device ID which is fixed throughout a single session of ClarinoxBlue stack */
    u4                          serviceClasses;                                                     /*!< The combination (bit-wide or-ed) value of generic services which are supported by the device. Refer to #ClxDeviceServiceClass enum for more information */
    enum ClxMajorDeviceClass    majorClassOfDevice;                                                 /*!< The major class of device. Refer to ClarinoxBlueConst.h for more information */
    u1                          minorClassOfDevice;                                                 /*!< The minor class of device which is interpreted in the context of the major class. Refer to ClarinoxBlue.h for more information */
    s1                          rssi;                                                               /*!< The RSSI value obtained by the remote device during device discovery process */
} ClxDeviceDetail CLX_CTYPE;



/**
Enumerates the possible types of an HCI command response
*/
typedef enum clxGapSendHciCommandResponseTypeEnum
{
    clxGapSendHciCommandResponseType_CommandStatus     = 0x00,    /*!< A command status event is received for the command. The status determines whether or not the HCI command has been
                                                                       successfully started.
                                                                       If successful, another event will be received when the command is complete either in error or with success.
                                                                       The type of this event is specific to the command. */
    clxGapSendHciCommandResponseType_CommandComplete   = 0x01

} clxGapSendHciCommandResponseType;


/**
Determines the reason why an incoming connection request is being rejected by the local device.
*/
enum ClxConnectionRequestRejectReason 
{
    ClxLimitedResources                 = 0x0D, 
    ClxSecurity                         = 0x0E, 
    ClxUnacceptableBluetoothAddress     = 0x0F, 
    ClxUnspecified                      = 0x1F
};


/**
Determines which of parameters of the structure #ClxGapInquiryFilter have valid values.
*/
enum ClxGapInquiryFilterMask
{
    ClxNoInquiryFilter                  = 0x00,         /*!< All parameters have invalid values (no filtering is to be performed) */
    ClxMajorClass                       = 0x01,         /*!< Only #ClxGapInquiryFilter.majorClass has a valid value */
    ClxMajorAndMinorClass               = 0x03,         /*!< Only #ClxGapInquiryFilter.majorClass and #ClxGapInquiryFilter.minorClass have valid values */
    ClxServiceClass                     = 0x04,         /*!< Only #ClxGapInquiryFilter.serviceClass has a valid value */
    ClxMajorAndServiceClass             = 0x05,         /*!< Only #ClxGapInquiryFilter.majorClass and #ClxGapInquiryFilter.serviceClass have valid values */
    ClxMajorMinorServiceClass           = 0x07          /*!< All three parameters have valid values */
};

/**
Determines the type of filtering which is to be used when #clxGapStartInquiry function is called.
*/
struct ClxGapInquiryFilter
{
    enum ClxGapInquiryFilterMask    filterMask;         /*!< Determines which of the following three parameters have valid values. 
                                                             If set to ClxNoInquiryFilter, then no filtering is applied */
    enum ClxMajorDeviceClass        majorClass;         /*!< The major device class according to which discovered devices must be filtered */
    u1                              minorClass;         /*!< The minor device class according to which discovered devices must be filtered */ 
    u4                              serviceClass;       /*!< The service class(es) according to which discovered devices must be filtered */
};


/**
Used internally.
*/
typedef ClxResult (*ClxGapGenericCommand) (void* input, void* output);


/**
Data Structure for the indication #CLX_GAP_DEVICE_DISCOVERED_INDICATION
*/
typedef struct ClxGapDeviceDiscoveredIndicationStruct
{
    ClxDeviceDetail  deviceDetail;    /*!< Details of the remote device */
} ClxGapDeviceDiscoveredIndication;

/**
Data Structure for the indication #CLX_GAP_PIN_CODE_REQUEST_INDICATION
*/
typedef struct ClxGapPinCodeRequestIndicationStruct
{
    ClxDeviceDetail  deviceDetail;    /*!< Details of the remote device */
} ClxGapPinCodeRequestIndication;

/**
Data Structure for the indication #CLX_GAP_INCOMING_CONNECTION_REQUEST_INDICATION
*/
typedef struct ClxGapIncomingConnectionRequestIndicationStruct
{
    ClxDeviceDetail  deviceDetail;    /*!< Details of the remote device */
} ClxGapIncomingConnectionRequestIndication;

/**
Data Structure for the indication #CLX_GAP_LINK_DISCONNECTION_INDICATION
*/
typedef struct ClxGapLinkDisconnectionIndicationStruct
{
    ClxDeviceDetail  deviceDetail;           /*!< Details of the remote device */
    u1               disconnectionReason;    /*!< The reason of disconnection as defined in Bluetooth Core Specification */
} ClxGapLinkDisconnectionIndication;

/**
Data Structure for the indication #CLX_GAP_USER_PASSKEY_REQUEST_INDICATION
*/
typedef struct ClxGapUserPasskeyRequestIndicationStruct
{
    ClxDeviceDetail  deviceDetail;    /*!< Details of the remote device */
} ClxGapUserPasskeyRequestIndication;

/**
Data Structure for the indication #CLX_GAP_USER_PASSKEY_NOTIFICATION_INDICATION
*/
typedef struct ClxGapUserPasskeyNotificationIndicationStruct
{
    ClxDeviceDetail  deviceDetail;    /*!< Details of the remote device */
    u4               value;           /*!< The value of the passkey which is to be displayed on the screen and/or confirmed by the local user. It will be 0 through 999999 decimal */
} ClxGapUserPasskeyNotificationIndication;

/**
Data Structure for the indication #CLX_GAP_USER_CONFIRMATION_REQUEST_INDICATION
*/
typedef struct ClxGapUserConfirmationRequestIndicationStruct
{
    ClxDeviceDetail  deviceDetail;    /*!< Details of the remote device */
    u4               value;           /*!< The value of the passkey which is to be displayed on the screen and/or confirmed by the local user. It will be 0 through 999999 decimal */
} ClxGapUserConfirmationRequestIndication;

/**
Data Structure for the indication #CLX_GAP_PAIRING_COMPLETE_INDICATION
*/
typedef struct ClxGapPairingCompleteIndicationStruct
{
    ClxDeviceDetail  deviceDetail;    /*!< The details of the remote device for which simple pairing procedure has just completed */
    u1               status;          /*!< The result of the simple pairing procedure, a value of 0 indicates success */
    boolean          isBonded;        /*!< FALSE indicates that remote device displayed 'No Bonding' capability while pairing. (Bonding details not intended to be stored) */
} ClxGapPairingCompleteIndication;


struct ClxGapGetLocalBtAddressComplete
{
	_user_out_ u1* btAddress;
};

/** 
Extracts the OCF part from HCI command op-code 

\param[ in ]  opcodePTR little endian buffer pointer containing the combined op-code
\return u2 ocf
*/
extern u2 clxGetHciOcf(u2* opcodePTR);

/* 
Extracts the OGF part from HCI command op-code 

param[ in ]  little endian buffer pointer containing the combined op-code
\return u2 ogf
*/
extern u2 clxGetHciOgf(u2* opcodePTR);

/**
Returns the Bluetooth address of a remote device identified by its Device ID.

\param[  in   ] deviceID   The ID of the device ID as returned by other GAP API.
\param[  out  ] btAddress  Pointer to a caller-defined buffer with the size of at least CLX_BLUETOOTH_ADDRESS_LENGTH bytes, 
                           which on return will contain the Bluetooth address of the remote device.
                           Please note the btAddress byte order is in Little Endian, the application usage needs to convert to network order.

\return TRUE,  if the Bluetooth address was successfully returned.  
        FALSE, if deviceID is invalid (e.g. CLX_IS_DEVICE_ID_VALID(deviceID) would return FALSE)

*/
extern boolean clxGapGetRemoteDeviceBtAddress(_in_ ClxDeviceId  deviceID,
                                              _user_out_ u1*    btAddress);

/**
Retrieves the local device Bluetooth address.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_GET_LOCAL_BT_ADDRESS_COMPLETE.
                   The parameter of this indication is of type #ClxGapGetLocalBtAddressComplete.

\param[  in   ] stack      Local device stack handle. A stack object must be created before a GAP API used.
\param[  out  ] btAddress  A pointer to the local Bluetooth address.
\param[  in   ] block      Type of the operation.  
                            - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                            - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
*/
ClxError clxGapGetLocalBtAddress(_in_ ClxStack   stack, 
                                 _user_out_ u1*  btAddress,
                                 _in_ boolean    block );

/**
Starts inquiry from the local device. If any Bluetooth devices in the vicinity are found, then 
#CLX_GAP_DEVICE_DISCOVERED_INDICATION message will be received via the callback function. A name 
request will be performed for each new discovered device which is not already in the pairing list.

Optionally, a filter may be used to limit the discovered devices to a specific device class (or a combination of device classes).

The maximum number of discovered device reports returned would be up-to as many as that are configured in BSP parameter 'MaxNoOfDiscoveredDevices'

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_START_INQUIRY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                   Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] inquiryFilter           A pointer to a data structure determining the type of filtering (if any) which is to be used. This parameter CANNOT be NULL.
\param[  in   ] isLimitedInquiryAccess  TRUE to start limited inquiry (Same as #clxGapStartLimitedInquiry), FALSE to start general inquiry access.
\param[  in   ] maxInquiryPeriod        Maximum searching period. The value range starts from 0x03 to 0xFFFF. For example: 1.25 x 'n' seconds.
\param[  in   ] minInquiryPeriod        Minimum searching period. The value range starts from 0x02 to 0xFFFE. For example: 1.25 x 'n' seconds.
\param[  in   ] maxInquiryTimeUnits     Maximum amount of time specified before the Inquiry is halted. The value range starts from 0x01 to 0x30. For example: 1.25 x 'n' seconds.
\param[  in   ] block                   Type of the operation.  
                                        - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INQUIRY_IN_PROGRESS: Inquiry process is currently in progress.
        - #CLX_FAIL: If Inquiry period (BSP Parameter MaxInquiryPeriod) is out of range.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapStartInquiry(_in_ ClxStack                                stack, 
                            _user_in_ const struct ClxGapInquiryFilter*  inquiryFilter,
                            _in_ boolean                                 isLimitedInquiryAccess,
                            _in_ u2                                      maxInquiryPeriod,
                            _in_ u2                                      minInquiryPeriod,
                            _in_ u1                                      maxInquiryTimeUnits,
                            _in_ boolean                                 block);

/**
Starts a limited inquiry from the local device. If any Bluetooth devices in the vicinity are found, then 
#CLX_GAP_DEVICE_DISCOVERED_INDICATION message will be received via the callback function. A name request 
will be performed for each new discovered device which is not already in the pairing list.

The limited inquiry is similar to standard inquiry (as performed by #clxGapStartInquiry), but it is only able to discover
devices which are in limited discovery mode. All parameters, and indications of this functions is the same as #clxGapStartInquiry.

Optionally, a filter may be used to limit the discovered devices to a specific device class (or a combination of device classes).

This API uses the following default Inquiry parameters values;
- maxInquiryPeriod as 10 (10 x 1.25 seconds)
- minInquiryPeriod as 9 (9 x 1.25 seconds)
- maxInquiryTimeUnits as 8 (8 x 1.25 seconds)
The maximum number of discovered device reports returned would be up-to as many as that are configured in BSP parameter 'MaxNoOfDiscoveredDevices'

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_START_LIMITED_INQUIRY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack          Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] inquiryFilter  A pointer to a data structure determining the type of filtering (if any) which is to be used. This parameter CANNOT be NULL.
\param[  in   ] block          Type of the operation.  
                                - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INQUIRY_IN_PROGRESS: Inquiry process is currently in progress.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapStartLimitedInquiry(_in_ ClxStack                                stack, 
                                   _user_in_ const struct ClxGapInquiryFilter*  inquiryFilter,
                                   _in_ boolean                                 block );

/**
Stop inquiry from the local device. This operation will stop any on-going inquiry operation, as has been initiated by #clxGapStartInquiry or
#clxGapStartLimitedInquiry command.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_STOP_INQUIRY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack  Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] block  Type of the operation.  
                        - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INQUIRY_NOT_IN_PROGRESS: There is no inquiry process currently in progress.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapStopInquiry(_in_ ClxStack   stack, 
                           _in_ boolean    block );


/**
Data Structure for the indication #CLX_GAP_GET_DISCOVERED_DEVICE_BY_INDEX_COMPLETE
*/
typedef struct ClxGapGetDiscoveredDeviceByIndexCompleteStruct
{
    _user_out_ ClxDeviceDetail*  detail;    /*!< A caller-allocated object to store the details of the discovered device. */
} ClxGapGetDiscoveredDeviceByIndexComplete;

/**
Get details of a discovered device found during the inquiry operation. The device is identified by its index.
This command may be used to get the list of discovered devices one by one. This command should not be issued during device discovery procedure.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_GET_DISCOVERED_DEVICE_BY_INDEX_COMPLETE.
                   The parameter of this indication is of type #ClxGapGetDiscoveredDeviceByIndexComplete.

\param[  in   ] stack   Local device stack handle. A stack object must be created before a GAP API used.
\param[  out  ] detail  A caller-allocated object to store the details of the discovered device.
\param[  in   ] index   The zero-based index of the device for which the details are to be returned. If the index is out of range, this command will complete with an error
\param[  in   ] block   Type of the operation.  
                        - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: If the index is greater than total no.of paired devices
*/
ClxResult clxGapGetDiscoveredDeviceByIndex(_in_ ClxStack                stack,
                                           _user_out_ ClxDeviceDetail*  detail,
                                           _in_ u4                      index,
                                           _in_ boolean                 block);

/**
clxGapInitiateBonding() function is used to initiate bonding procedure to a remote device. The remote device id is retrieved from an inquiry operation.
For faster operation, inquiry operation must be stopped before this function is called. In order to bonding operation
to be successful, both local device and remote device must be in bondable mode.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_INITIATE_BONDING_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId       Remote device id.
\param[  in   ] securityRequirement  The security level required for the bonding process. It is highly recommended that the value of #ClxAutomaticSecurity be set for  
                                     this parameter. Refer to the documentation of #ClxSecurityRequirement for more information.
\param[  in   ] block                Type of the operation.  
                                     - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                     - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_GAP_LOCAL_DEVICE_NOT_BONDABLE: Bonding is not possible since the local device is in non-bondable mode
        - #CLX_ERROR_GAP_REMOTE_DEVICE_NOT_BONDABLE: Bonding is not possible since the remote device is in non-bondable mode
        - #CLX_ERROR_INVALID_DEVICE_ID: Given remoteDeviceId is invalid
        - #CLX_ERROR_INTERNAL_ERROR: State/resource related error internal to Stack.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
        - #CLX_ERROR_GAP_PAIRED_DEVICES_COUNT_MAX_LIMIT_REACHED: When the configured maximum no of paired devices count (MaxNoOfPairedDevices) reached.

\remarks
Bonding is the procedure of pairing to a remote device permanently, by storing pairing information in a local storage area. When bonding is successful,
the devices can communicate without authentication and security measures as long as bonding information is not deleted by either the local device or the
remote device.
clxGapInitiateBonding() is used to pair to a device permanently without an intention to connect to any specific service on the remote device. Any attempt
to connect to a remote device to use a service (except for SDAP) will automatically result in bonding as well (as long as both the local device and
the remote device are in bondable mode). Therefore, calling this function to pair to a remote device in order to use a service on that device is not
necessary.

The following code example shows how to initiate bonding to the first remote device 
of the discovered devices list.
\code
    ClxDeviceDetail list[20];
    u4 listSize = 20;

    ClxError err = clxGapGetListOfDiscoveredDevices(gap, list, &listSize, TRUE);

    if (listSize)
    {
        err = clxGapInitiateBonding(gap, list[0].deviceId, TRUE);
    }

\endcode
*/
ClxError clxGapInitiateBonding(_in_ ClxStack                       stack, 
                               _in_ ClxDeviceId                    remoteDeviceId,
                               _in_ enum ClxSecurityRequirement    securityRequirement,
                               _in_ boolean                        block );

/**
Pin code response during a pairing operation. This function is only used if either the local or the remote device does not support
Simple Secure Pairing.

NOTE: this function must only be called upon the reception of a #CLX_GAP_PIN_CODE_REQUEST_INDICATION indication.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_PIN_CODE_REQUEST_REPLY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId  Id of the remote device.
\param[  in   ] pinCode         Pin code (up to 16 bytes long). If NULL, the pin code request will be rejected.
\param[  in   ] pinCodeLength   Length of the provided pin code. Maximum 16 bytes.
\param[  in   ] block           Type of the operation.  
                                - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_DEVICE_ID: Given remoteDeviceId is invalid
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapPinCodeRequestReply(_in_ ClxStack    stack,
                                   _in_ ClxDeviceId remoteDeviceId,
                                   _in_ const u1*   pinCode,
                                   _in_ u4          pinCodeLength,
                                   _in_ boolean     block);

/**
Accept connection request function is used, if a remote device is trying to connect to the local device and user wishes to accept the connection request.
This command will be complete when the connection to the remote device is complete (either with success or in error). 

NOTE: this function must only be called upon the reception of a #CLX_GAP_INCOMING_CONNECTION_REQUEST_INDICATION indication.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_ACCEPT_CONNECTION_REQUEST_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId  Id of the remote device.
\param[  in   ] block           Type of the operation.  
                                - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_DEVICE_ID: Given remoteDeviceId is invalid
        - #CLX_ERROR_INTERNAL_ERROR: State/resource related error internal to Stack.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapAcceptConnectionRequest(_in_ ClxStack    stack,
                                       _in_ ClxDeviceId remoteDeviceId,
                                       _in_ boolean     block);

/**
Reject connection request function is used, if a remote device is trying to connect to the local device and user does not accept the connection request.

NOTE: this function must only be called upon the reception of a #CLX_GAP_INCOMING_CONNECTION_REQUEST_INDICATION indication.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_REJECT_CONNECTION_REQUEST_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId  Id of the remote device.
\param[  in   ] reason          Reason for the rejection, selections are given in #ClxConnectionRequestRejectReason
\param[  in   ] block           Type of the operation.  
                                - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_DEVICE_ID: Given remoteDeviceId is invalid
        - #CLX_ERROR_INTERNAL_ERROR: State/resource related error internal to Stack.
*/
ClxError clxGapRejectConnectionRequest(_in_ ClxStack                                stack,
                                       _in_ ClxDeviceId                             remoteDeviceId,
                                       _in_ enum ClxConnectionRequestRejectReason   reason,
                                       _in_ boolean                                 block);

/**
Disconnects the physical link to a remote device. This is the link over which all upper layer data is sent to and received from this remote device. When the physical link
is terminated, no data can be sent and received between the local device and the remote device any more. 

If there is a physical link to the specified remote device, this command will not be complete until the connection is successfully terminated, or a timeout occurs.

IMPORTANT : If this command is successful, all service-level connections to the remote device will also be automatically terminated. As a result,
an appropriate indication is sent to the affected services, indicating the loss of the service-level connection.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_DISCONNECT_PHYSICAL_LINK_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId  Id of the remote device.
\param[  in   ] block           Type of the operation.  
                                - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_DEVICE_ID: The provided device ID is not associated to any remote device.
        - #CLX_ERROR_DISCONNECTION_IN_PROGRESS: The physical link is currently disconnecting from the remote device.
        - #CLX_ERROR_CONNECTION_NOT_EXIST: There is no physical link to the remote device.
*/
ClxResult clxGapDisconnectPhysicalLink(_in_ ClxStack    stack,
                                       _in_ ClxDeviceId remoteDeviceId,
                                       _in_ boolean     block);

/**
Set discoverability is used to make the local device discoverable or non-discoverable.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_SET_DISCOVERABILITY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] discoverable         Set to TRUE to make the local device discoverable.
\param[  in   ] inquiryScanInterval  The time between consecutive inquiry scans, time interval between consecutive searchable time period. 
                                     (N * 0.625 ms). 'N' range: 0x0012 to 0x1000; only even values are valid. 
                                     This value will be ignored if the parameter discoverable is FALSE.
\param[  in   ] inquiryScanWindow    The time for the duration of the inquiry scan, the time when chip is searchable. (N * 0.625 ms). 'N' range: 0x0011 to 0x1000. 
                                     This value will be ignored if the parameter discoverable is FALSE.
\param[  in   ] block                Type of the operation.  
                                     - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                     - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapSetDiscoverability(_in_ ClxStack stack,
                                  _in_ boolean  discoverable,
                                  _in_ u2       inquiryScanInterval,
                                  _in_ u2       inquiryScanWindow,
                                  _in_ boolean  block);

/**
Set Connectability is used to make the local device connectable or non-connectable.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_SET_CONNECTABILITY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack             Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectable       Set to TRUE to make the local device connectable.
\param[  in   ] pageScanInterval  The time between consecutive page scans, time interval between consecutive connectable time period. 
                                  (N * 0.625 ms). 'N' range: 0x0012 to 0x1000; only even values are valid. 
                                  This value will be ignored if the parameter connectable is FALSE
\param[  in   ] pageScanWindow    The time for the duration of the page scan, the time when chip is connectable. (N * 0.625 ms). 'N' range: 0x0011 to 0x1000. 
                                  This value will be ignored if the parameter connectable is FALSE.
\param[  in   ] block             Type of the operation.  
                                  - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                  - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapSetConnectability(_in_ ClxStack  stack,
                                 _in_ boolean   connectable,
                                 _in_ u2        pageScanInterval,
                                 _in_ u2        pageScanWindow,
                                 _in_ boolean   block);

/**
Set Bondability is used to make the local device bondable or non-bondable. The local device is in bondable mode by default.
When the local device is in non-bondable mode, only already-paired devices are able to make a connection request to the local device. Also, when in
non-bondable mode, a connection attempt by the local device to a not-paired remote device will not result in bonding, and may fail based on the configuration
of the remote device.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_SET_BONDABILITY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack     Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] bondable  Set to TRUE to make the local device bondable. set to FALSE to make the local device non-bondable.
\param[  in   ] block     Type of the operation.  
                            - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                            - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
*/
ClxError clxGapSetBondability(_in_ ClxStack stack,
                              _in_ boolean  bondable,
                              _in_ boolean  block);

/**
Data Structure for the indication #CLX_GAP_GET_PAIRED_DEVICE_BY_INDEX_COMPLETE
*/
typedef struct ClxGapGetPairedDeviceByIndexCompleteStruct
{
    _user_out_ ClxDeviceDetail*  detail;    /*!< A caller-allocated object to store the details of the paired device. */
} ClxGapGetPairedDeviceByIndexComplete;

/**
Get details of a paired device. The device is identified by its zero-based index.
This command may be used to get the list of paired devices one by one. This command should not be issued during bonding procedure.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_GET_PAIRED_DEVICE_BY_INDEX_COMPLETE.
                   The parameter of this indication is of type #ClxGapGetPairedDeviceByIndexComplete.

\param[  in   ] stack   Local device stack handle. A stack object must be created before a GAP API used.
\param[  out  ] detail  A caller-allocated object to store the details of the paired device.
\param[  in   ] index   The zero-based index of the device for which the details are to be returned. If the index is out of range, this command will complete with an error.
\param[  in   ] block   Type of the operation.  
                        - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INTERNAL_ERROR: State/resource related error internal to Stack.
        - #CLX_ERROR_DATABASE_RECORD_NOT_FOUND: Paired device record not found in database.
        - #CLX_ERROR_DATABASE_NOT_EXIST: ClarinoxBlue.cfg file/Paired device detail storage database is not available.
        - #CLX_ERROR_INVALID_REQUEST: Configuration file is not initialized properly.
*/
ClxResult clxGapGetPairedDeviceByIndex(_in_ ClxStack                stack,
                                       _user_out_ ClxDeviceDetail*  detail,
                                       _in_ u4                      index,
                                       _in_ boolean                 block);

/**
Replies to the Bluetooth controller's request to enter a passkey, by either providing a passkey, or rejecting the request. This function is only used if both the local
device and the remote device support Simple Secure Pairing.

NOTE: this function must only be called upon the reception of a #CLX_GAP_USER_PASSKEY_REQUEST_INDICATION indication.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_USER_PASSKEY_REQUEST_REPLY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack               Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId      Id of the remote device.
\param[  in   ] userEnteredPasskey  It has to be TRUE, if the user has entered a passkey. FALSE, if the user has rejected the passkey request.
\param[  in   ] userPasskey         The passkey entered by the user, as an integer. The value must be 0 through 999999 decimal. This parameter
                                    will be ignored if userEnteredPasskey is FALSE.
\param[  in   ] block               Type of the operation.  
                                    - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_DEVICE_ID: The device ID is invalid.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapUserPasskeyRequestReply(_in_ ClxStack    stack,
                                       _in_ ClxDeviceId remoteDeviceId,
                                       _in_ boolean     userEnteredPasskey,
                                       _in_ u4          userPasskey,
                                       _in_ boolean     block);

/**
Replies to the Bluetooth controller's request to confirm an authentication request from a remote device, by either confirming or rejecting the request. 
This function is only used if both the local device and the remote device support Simple Secure Pairing.

NOTE: this function must only be called upon the reception of a #CLX_GAP_USER_CONFIRMATION_REQUEST_INDICATION indication.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_USER_CONFIRMATION_REQUEST_REPLY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack            Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId   Id of the remote device.
\param[  in   ] userSelectedYes  It has to be TRUE, if the user has confirmed the request. FALSE, if the user has rejected the request.
\param[  in   ] block            Type of the operation.  
                                 - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                 - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_DEVICE_ID: The device ID is invalid.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapUserConfirmationRequestReply(_in_ ClxStack       stack,
                                            _in_ ClxDeviceId    remoteDeviceId,
                                            _in_ boolean        userSelectedYes,
                                            _in_ boolean        block);

/**
Deletes pairing information of an already-paired remote device. If the remote device is also bonded, the pairing information will also be deleted from
the persistent storage.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_DELETE_PAIRED_DEVICE_INFO_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId  Id of the remote device of which the pairing information is to be deleted.
\param[  in   ] block           Type of the operation.  
                                - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_DEVICE_ID: The device ID is invalid.
        - #CLX_ERROR_INTERNAL_ERROR: State/resource related error internal to Stack.
        - #CLX_ERROR_INVALID_REQUEST: When the device information to be deleted is not found.
*/
ClxError clxGapDeletePairedDeviceInfo(_in_ ClxStack     stack,
                                      _in_ ClxDeviceId  remoteDeviceId,
                                      _in_ boolean      block);

/**
Deletes pairing information of all already-paired remote devices. If a remote device is also bonded, the pairing information will also be deleted from
the persistent storage.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_DELETE_ALL_PAIRED_DEVICES_INFO_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack  Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] block  Type of the operation.  
                        - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INTERNAL_ERROR: State/resource related error internal to Stack.
        - #CLX_ERROR_INVALID_REQUEST: When the device information to be deleted is not found.
*/
ClxError clxGapDeleteAllPairedDevicesInfo(_in_ ClxStack stack,
                                          _in_ boolean  block);

/**
Data Structure for the indication #CLX_GAP_REQUEST_REMOTE_DEVICE_NAME_COMPLETE
*/
typedef struct ClxGapRequestRemoteDeviceNameCompleteStruct
{
    _user_out_ ClxDeviceDetail*  deviceDetail;    /*!< A caller-allocated structure to store the details of the device (only in blocking mode). */
} ClxGapRequestRemoteDeviceNameComplete;

/**
Request of the remote name function will return the remote device within the ClxDeviceDetail structure. This function is generally needed 
when the name request times out during an inquiry operation. Most Bluetooth chips have trouble responding to a name request if the inquiry 
operation is going on. 

Any connection requests to the same remote device during this request will fail. The reason is there would be a LMP connection 
established with the remote device during the remote name request. If this call executes successfully, then the stored device name will be replaced with 
the obtained name. This call will send a name request to the remote device only when the name is not available with the stack.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_REQUEST_REMOTE_DEVICE_NAME_COMPLETE.
                   The parameter of this indication is of type #ClxGapRequestRemoteDeviceNameComplete.

\param[  in   ] stack           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId  Remote device id.
\param[  in   ] requestTimeout  Request timeout in milliseconds.
\param[  out  ] deviceDetail    A caller-allocated structure to store the details of the device (only in blocking mode).
\param[  in   ] block           Type of the operation.  
                                - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_DEVICE_ID: The device ID provided is invalid.
        - #CLX_ERROR_INTERNAL_ERROR: State/resource related error internal to Stack.
*/
ClxError clxGapRequestRemoteDeviceName(_in_ ClxStack                stack,
                                       _in_ ClxDeviceId             remoteDeviceId,
                                       _in_ u4                      requestTimeout,
                                       _user_out_ ClxDeviceDetail*  deviceDetail,
                                       _in_ boolean                 block);

/**
This function can be used to dynamically configure some global parameters of the stack. The parameters that can be configured with this function are

1. Major Class of Device
2. Minor Class of Device
3. Service Class
4. Local Device Name

NOTE : While this function immediately applies the new values of the parameters, the new values might not be immediately reflected in the remote devices since
many Bluetooth stacks are by default configured to discover these parameters only during pairing. Therefore, the pairing information stored in the remote device may need to be deleted before
the new values of these parameters appear.

Therefore, these parameters should be dynamically modified ONLY if it is deemed necessary.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_WRITE_CONFIGURATION_PARAMETERS_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] parameterConfigList  The list of configuration parameters to modify in the stack. If a configuration parameter does not exist in the list, 
                                     it's current value will not be modified.
\param[  in   ] block                Type of the operation.  
                                     - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                     - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
*/
ClxError clxGapWriteConfigurationParameters(_in_ ClxStack            stack, 
                                            _user_in_ ClxConfigList* parameterConfigList,
                                            _in_ boolean             block);

/**
Data Structure for the indication #CLX_GAP_SEND_HCI_COMMAND_COMPLETE
*/
typedef struct ClxGapSendHciCommandCompleteStruct
{
    _user_out_ u1*  responseBuffer;      /*!< A caller-provided buffer in which the response payload will be stored. This buffer shall not be modified or deleted
                                              until the API command is complete. This argument may be set to NULL if the response does not have a payload or
                                              the response payload is not required.
                                              NOTE: Only a Command Complete response may have a payload. A Command Status response never has a payload. */
    _inout_ u1*     responseDataSize;    /*!< As an input, this specifies the size of #responseBuffer, in bytes. As an output, it will contain
                                              the length of payload which was copied into #responseBuffer. This value will never be larger than the response buffer size.
                                              NOTE: If the payload is larger than the buffer size, it will be truncated. */
} ClxGapSendHciCommandComplete;


/**
Prototype for a callback function which may be passed to clxGapSendHciCommand_V2. If provided, the function will be called by ClarioxBlue stack after the HCI command has been sent but
before a response has been received. An implementation may try to change the ClarinoxBlue driver configuration before a response can be received. For instance, an implementation may need to
change the UART baud-rate before a response can be received.

\param[ in ] ogf                    The Op-code Group Field of the HCI command which has been sent successfully.
\param[ in ] ocf                    The Op-code Command Field of the HCI command which has been sent successfully.
\param[ in ] commandPayload         The payload of the HCI command which has been sent successfully.
\param[ in ] commandPayloadLength   The length of the HCI command payload.

\return CLX_SUCCESS if the operation has been successful, and the stack can go ahead and receive the response.
        Any other value indicates an error. In this case, clxGapSendHciCommand_V2 will be complete with the same error code.
*/
typedef ClxResult (*ClxGapHciCommandSentCallback) (u2 ogf, u2 ocf, const u1* commandPayload, u1 commandPayloadLength);


/**
Sends an HCI command to the Bluetooth controller. This API command is completed when the HCI command response
is received from the controller, or timeout occurs.
This API command can be issued at any time.

NOTE: This API function cannot be used to send any arbitrary HCI command. The main purpose of this API function is to
send standard RESET command and vendor specific commands to the controller. If an attempt is made to send an HCI command which is not supported, an error will be returned.
To support such commands a custom library needs to be generated.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_SEND_HCI_COMMAND_COMPLETE.
                   The parameter of this indication is of type #ClxGapSendHciCommandComplete.

\param[  in   ] stack                   Bluetooth stack handle
\param[  in   ] ogf                     The Op-code Group Field of the HCI command.
                                        For vendor specific HCI commands, OGF is defined as #CLX_GAP_VENDOR_SPECIFIC_OGF.
\param[  in   ] ocf                     The Op-code Command Field of the HCI command.
\param[  in   ] commandPayload          A pointer to the payload of the HCI command which is to be sent to the controller. If the HCI command does not have a payload,
                                        this argument shall be set to NULL.

\param[  in   ] commandPayloadLength    The length of the command payload. This may be 0 only if \p commandPayload is set to NULL.
                                        Maximum possible payload length for an HCI command is 255 bytes.

\param[  in   ] hciCommandSentCallback  Optional callback function which will be called when the command has been sent, but before a response has been received. This argument may be NULL.
\param[  in   ] responseType            The type of the response for the HCI command which is expected to be received from the controller.
                                        This API command will not be complete until the response is received from the controller, or a timeout occurs.

\param[  out  ] responseBuffer          A caller-provided buffer in which the response payload will be stored. This buffer shall not be modified or deleted
                                        until the API command is complete. This argument may be set to NULL if the response does not have a payload or
                                        the response payload is not required.
                                        NOTE: Only a Command Complete response may have a payload. A Command Status response never has a payload.

\param[ inout ] responseDataSize        As an input, this specifies the size of \p responseBuffer, in bytes. As an output, it will contain
                                        the length of payload which was copied into \p responseBuffer. This value will never be larger than the response buffer size.
                                        NOTE: If the payload is larger than the buffer size, it will be truncated.

\param[  in   ] block                   Indicates mode of operation:
                                        - TRUE: Blocking mode
                                        - FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_REQUEST: Sending an HCI command with the specified OGF/OCF is not permitted
        - #CLX_ERROR_TIMEOUT_OCCURRED: Timeout occurred before the response to the HCI command is received
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapSendHciCommand_V2(_in_ ClxStack                             stack,
                                  _in_ u2                                   ogf,
                                  _in_ u2                                   ocf,
                                  _user_in_ const u1*                       commandPayload,
                                  _in_ u1                                   commandPayloadLength,
                                  _in_ ClxGapHciCommandSentCallback         hciCommandSentCallback,
                                  _in_ clxGapSendHciCommandResponseType     responseType,
                                  _user_out_ u1*                            responseBuffer,
                                  _inout_ u1*                               responseDataSize,
                                  _in_ boolean                              block);


/**
This API is the same as #clxGapSendHciCommand_V2, except that the argument hciCommandSentCallback does not exist.
Please refer to #clxGapSendHciCommand_V2 documentation for more details.
*/
#define clxGapSendHciCommand(stack, ogf, ocf, commandPayload, commandPayloadLength, responseType, responseBuffer, responseDataSize, block)          \
    clxGapSendHciCommand_V2(stack, ogf, ocf, commandPayload, commandPayloadLength, NULL, responseType, responseBuffer, responseDataSize, block)



/**
This API is used to make the local device in limited discoverable or non-discoverable mode.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_SET_LIMITED_DISCOVERABILITY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack         Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] discoverable  Set to TRUE to make the local device in limited discoverable.
\param[  in   ] block         Type of the operation.  
                                - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxError clxGapSetLimitedDiscoverability(_in_ ClxStack  stack,
                                         _in_ boolean   discoverable,
                                         _in_ boolean   block);


/**
Helper function used to send HCI RESET command to the controller. Internally it calls #clxGapSendHciCommand() API function in blocking mode. This function may be called in any context in which it is possible to call
#clxGapSendHciCommand() API function.

The function keeps sending the HCI RESET command until a success response is received from the Bluetooth controller or the command has been sent \p maxNumberOfResetCommands times.

\param[  in   ] stack                       Bluetooth stack handle
\param[  in   ] maxNumberOfResetCommands    The maximum number of times the HCI RESET command may be sent before a success response is received from the Bluetooth controller.

\return #CLX_SUCCESS is successful.
        If the operation fails, this function returns the return value of the last call to #clxGapSendHciCommand() API function.
*/
ClxError clxGapSendHciResetCommand(ClxStack stack, 
                                   u4       maxNumberOfResetCommands);

/**
Allows the local BR/EDR Controller to enter test mode.  
After the API returns CLX_SUCCESS, the test scenarios can be executed using LMP commands by the remote device.  
ClarinoxBlue stack shall be initialized before calling this API. 
To disable and exit the Device Under Test Mode, terminate the ClarinoxBlue stack using APIs #clxTerminateClarinoxBlue and #clxDestroyClarinoxBlue.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BLUETOOTH_CLASSIC_ENABLE_DEVICE_TEST_MODE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack  Local device stack handle. A stack object must be created before this API is used.
\param[  in   ] block  Type of the operation.  
                         - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                         - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxBluetoothClassicEnableDeviceTestMode(_in_ ClxStack  stack,
                                                  _in_ boolean   block);


/**
Data Structure for the indication #CLX_GAP_GET_RSSI_VALUE_COMPLETE
*/
typedef struct ClxGapGetRssiValueCompleteStruct
{
    _user_out_ s1*  rssi;    /*!< Pointer to a memory location to store the retrieved RSSI value. 
                                  The caller must allocate at least 1 byte for this parameter. */
} ClxGapGetRssiValueComplete;

/**
Retrieves the current Received Signal Strength Indication (RSSI) value from a specified connected remote Bluetooth device. 

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_GET_RSSI_VALUE_COMPLETE.
                   The parameter of this indication is of type #ClxGapGetRssiValueComplete.

\param[  in   ] stack           Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] remoteDeviceId  Identifier of the remote device whose RSSI value is to be retrieved.
\param[  out  ] rssi            Pointer to a memory location to store the retrieved RSSI value. The caller must allocate at least 1 byte for this parameter.
\param[  in   ] block           Type of the operation.
                                - TRUE:  API will be blocked until this command is completed (successfully or failed). 
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle
        - CLX_ERROR_CONNECTION_NOT_EXIST : There is no ACL connection to a remote device.

        - CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapGetRssiValue(_in_ ClxStack     stack,
                             _in_ ClxDeviceId  remoteDeviceId,
                             _user_out_ s1*    rssi,
                             _in_ boolean      block);

#ifdef __cplusplus
}
#endif


#endif // _GAP_API_H_

