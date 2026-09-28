#ifndef __GAP_BLE_BONDING_API_h__
#define __GAP_BLE_BONDING_API_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gap.Ble.Bonding.Api.h
* Description         Declares API Functions and Definitions For Gap Ble Bonding 
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#define CLX_BLE_NUM_ECC_DIGITS                                                              8

/**
Refer to #clxGapBleSetBondable function.
*/
#define CLX_GAP_BLE_SET_BONDABLE_COMPLETE                                                   0x7300

/**
Refer to #clxGapBleStartBondingProcedure function.
*/
#define CLX_GAP_BLE_START_BONDING_PROCEDURE_COMPLETE                                        0x7301

/**
Refer to #clxGapBleRejectBondingProcedure function.
*/
#define CLX_GAP_BLE_REJECT_BONDING_PROCEDURE_COMPLETE                                       0x7302

/**
Refer to #clxGapBleUserPasskeyRequestReply function.
*/
#define CLX_GAP_BLE_USER_PASSKEY_REQUEST_REPLY_COMPLETE                                     0x7303

/**
Refer to #clxGapBleUserConfirmationRequestReply function.
*/
#define CLX_GAP_BLE_USER_CONFIRMATION_REQUEST_REPLY_COMPLETE                                0x7304

/**
Refer to #clxGapBleGetPairedDeviceName function.
*/
#define CLX_GAP_BLE_GET_PAIRED_DEVICE_NAME_COMPLETE                                         0x7305

/**
Refer to #clxGapBleGetListOfPairedDevices function.
*/
#define CLX_GAP_BLE_GET_LIST_OF_PAIRED_DEVICES_COMPLETE                                     0x7306

/**
Refer to #clxGapBleSetPairedDeviceName function.
*/
#define CLX_GAP_BLE_SET_PAIRED_DEVICE_NAME_COMPLETE                                         0x7307

/**
Refer to #clxGapBleDeletePairedDeviceInfo function.
*/
#define CLX_GAP_BLE_DELETE_PAIRED_DEVICE_INFO_COMPLETE                                      0x7308

/**
Refer to #clxGapBleDeleteAllPairedDevicesInfo function.
*/
#define CLX_GAP_BLE_DELETE_ALL_PAIRED_DEVICES_INFO_COMPLETE                                 0x7309

/**
Refer to #clxGapBleGenerateOobData function.
*/
#define CLX_GAP_BLE_GENERATE_OOB_DATA_COMPLETE                                              0x7310

/**
Refer to #clxGapBleEnableDisableOobPairing function.
*/
#define CLX_GAP_BLE_ENABLE_DISABLE_OOB_PAIRING_COMPLETE                                     0x7311

/**
This indication is received during authentication procedure when the Bluetooth controller asks the local device
to provide a passkey or reject the authentication request. Upon reception of this indication, the function
#clxGapBleUserPasskeyRequestReply MUST be called within 30 seconds from the time this indication has been
received. Otherwise, the bonding procedure will fail with the error #CLX_ERROR_BLE_SMP_PASSKEY_ENTRY_FAILED.

The parameter for this indication is of type #ClxGapBleUserPasskeyRequestIndication.
*/
#define CLX_GAP_BLE_USER_PASSKEY_REQUEST_INDICATION                                         0x9300
/**
This indication is received during authentication procedure when the Bluetooth controller asks the local device
to display a passkey on its display/monitor/LCD. This indication is only received when the local device has display
capabilities. Upon reception of this indication, the local application MUST display the passkey to the user, and must
keep displaying the passkey until returning the api #clxGapBleStartBondingProcedure in blocking mode otherwise
receiving the indication #CLX_GAP_BLE_START_BONDING_PROCEDURE_COMPLETE in non blocking mode.

The parameter for this indication is of type #ClxGapBleUserPasskeyNotificationIndication.
*/
#define CLX_GAP_BLE_USER_PASSKEY_NOTIFICATION_INDICATION                                    0x9301

/**
This indication is received when the remote device has requested that bonding procedure be carried out.

As a response to this request, the application MUST call either #clxGapBleStartBondingProcedure or #clxGapBleRejectBondingProcedure
within 30 seconds from the time this indication has been received. Otherwise, the request may be canceled.

This indication may be received only if the local device is in central role.

The parameter for this indication is of type #ClxGapBleSecurityRequestIndication
*/
#define CLX_GAP_BLE_SECURITY_REQUEST_INDICATION                                             0x9302

/**
This indication is received when the remote device has requested the pairing request.

As a response to this request, the application MUST call either #clxGapBleStartBondingProcedure or #clxGapBleRejectBondingProcedure
within 30 seconds from the time this indication has been received. Otherwise, the request may be canceled.

This indication may be received only if the local device is in peripheral role.

The parameter for this indication is of type #ClxGapBlePairingRequestIndication
*/
#define CLX_GAP_BLE_PAIRING_REQUEST_INDICATION                                              0x9303

/**
This indication is received during authentication procedure when the Bluetooth controller asks the local device
to confirm or reject the connection to a remote device. The indication contains a passkey as well. If the local device
has display capabilities, it must display the passkey to the user and asks for confirmation or rejection. Otherwise, it may
directly confirm or reject the request by calling the function #clxGapBleUserConfirmationRequestReply.
Please note that this indication should be received when both local and remote device should support LE secure pairing(4.2 compliance).

The parameter for this indication is of type #ClxGapBleUserConfirmationRequestIndication.
*/
#define CLX_GAP_BLE_USER_CONFIRMATION_REQUEST_INDICATION                                    0x9304

typedef enum ClxBleSmpBondingTypeEnum
{
    ClxBleSmpBondingType_NoBonding = 0x00,    /*!< Device in non bondable mode */
    ClxBleSmpBondingType_Bonding   = 0x01     /*!< Device in bondable mode */
} ClxBleSmpBondingType;

typedef enum ClxBleSmpSecureBondingPropertyEnum
{
    ClxBleSmpSecureBondingProperty_MitmNotRequired  = 0x01,    /*!< No man-in-the-middle (MITM) protection during pairing */
    ClxBleSmpSecureBondingProperty_MitmRequired     = 0x02,    /*!< Enabling authenticated man-in-the-middle (MITM) protection */
    ClxBleSmpSecureBondingProperty_SecureBonding    = 0x04,    /*!< Enabling LE secure pairing, which is supported in LE 4.2 */
    ClxBleSmpSecureBondingProperty_SecurityRequest  = 0x08,    /*!< Peripheral uses this enum to initiate the security request */
    ClxBleSmpSecureBondingProperty_CrossTransport   = 0x10     /*!< Enabling Cross Transport Key Derivation support */
} ClxBleSmpSecureBondingProperty;

typedef enum ClxBleSmpKeyDistributionEnum
{
    ClxBleSmpKeyDistribution_EncryptionKey  = 0x01,    /*!< Distributing Long Term Key */
    ClxBleSmpKeyDistribution_IdentityKey    = 0x02,    /*!< Distributing Identity Resolving Key */
    ClxBleSmpKeyDistribution_SignatureKey   = 0x04,    /*!< Distributing Connection Signature Resolving Key */
    ClxBleSmpKeyDistribution_LinkKey        = 0x08     /*!< Indicates to derive link key from LTK */
} ClxBleSmpKeyDistribution;


typedef struct ClxGapBlePairedDeviceDetailStruct
{
    s1  name[CLX_BLE_ADVERTISING_DATA_MAX_LENGTH + 1];    /*!< Name of the device as a null-terminated UTF-8 encoded string */
} ClxGapBlePairedDeviceDetail;

/**
Data Structure for the indication #CLX_GAP_BLE_GET_PAIRED_DEVICE_NAME_COMPLETE
*/
typedef struct ClxGapBleGetPairedDeviceNameCompleteStruct
{
    _user_out_ ClxGapBlePairedDeviceDetail* deviceDetail;    /*!< Application allocated buffer to store remote device name. */
} ClxGapBleGetPairedDeviceNameComplete;

/**
Data Structure for the indication #CLX_GAP_BLE_USER_PASSKEY_REQUEST_INDICATION
*/
typedef struct ClxGapBleUserPasskeyRequestIndicationStruct
{
    ClxBleConnectionHandle  connectionHandle;
} ClxGapBleUserPasskeyRequestIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_USER_PASSKEY_NOTIFICATION_INDICATION
*/
typedef struct ClxGapBleUserPasskeyNotificationIndicationStruct
{
    ClxBleConnectionHandle  connectionHandle;
    u4                      value;
} ClxGapBleUserPasskeyNotificationIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_SECURITY_REQUEST_INDICATION
*/
typedef struct ClxGapBleSecurityRequestIndicationStruct
{
    ClxBleConnectionHandle  connectionHandle;
    ClxBleSmpBondingType    bondingType;
    boolean                 mitmProtectionRequired;
    boolean                 securityFlag;
    boolean                 crossTransportFlag;
} ClxGapBleSecurityRequestIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_USER_CONFIRMATION_REQUEST_INDICATION
*/
typedef struct ClxGapBleUserConfirmationRequestIndicationStruct
{
    ClxBleConnectionHandle  connectionHandle;
    u4                      value;
} ClxGapBleUserConfirmationRequestIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_GET_LIST_OF_PAIRED_DEVICES_COMPLETE
*/
typedef struct ClxGapBleGetListOfPairedDevicesCompleteStruct
{
    _user_out_ ClxBleBdAddress* deviceAddrList;           /*!< A caller-allocated array to store the list of paired devices. If a NULL value is passed, then the size of the paired list will be returned. */
    _user_out_ u4*              numberOfPairedDevices;    /*!< The actual number of paired devices. If this value is greater than \p listSize, only
                                                               the first listSize number of paired devices have been returned in the caller-provided list. If this value is
                                                               smaller than listSize, only the first listSize elements of the list have valid values. */
} ClxGapBleGetListOfPairedDevicesComplete;

/**
Data Structure for the indication #CLX_GAP_BLE_PAIRING_REQUEST_INDICATION
*/
typedef struct ClxGapBlePairingRequestIndicationStruct
{
    ClxBleConnectionHandle  connectionHandle;
    ClxBleSmpBondingType    bondingType;
    boolean                 mitmProtection;
    boolean                 secureConnection;
    u1                      encryptionKeySize;
    u1                      distributedKeys;
    u1                      crossTransport;
} ClxGapBlePairingRequestIndication;

/**
Defines the Ble secure bonding curves
*/
typedef struct ClxBleCurveStruct
{
    u4  pCurve[CLX_BLE_NUM_ECC_DIGITS];
    u4  bCurve[CLX_BLE_NUM_ECC_DIGITS];
    u4  nCurve[CLX_BLE_NUM_ECC_DIGITS];
}ClxBleCurve;

/**
Keys required for OOB pairing. Pass the pointers with valid values which are applicable.
*/
typedef struct ClxBleOobKeyDetailsStruct
{
    u1* localPublicKeyX;    /*!< Public key X for local device */
    u1* localPublicKeyY;    /*!< Public key Y for local device */
    u1* localPrivateKey;    /*!< Private key X for local device */
    u1* randomLocal;        /*!< Random key for local device */
    u1* confirmLocal;       /*!< Confirm key for local device */
    u1* randomRemote;       /*!< Random key for remote device */
    u1* confirmRemote;      /*!< Confirm key for remote device */
} ClxBleOobKeyDetails;

/**
Data Structure for the indication #CLX_GAP_BLE_GENERATE_OOB_DATA_COMPLETE
*/
typedef struct ClxGapBleGenerateOobDataCompleteStruct
{
    _user_out_ ClxBleOobKeyDetails* oobData;       /*!< Generated OOB keys of local device. Pass the pointer with valid values for whichever applicable.
                                                        Public Key X, Y, Private key shall not be NULL.
                                                        If OOB data for local has to be generated, pass the Random and Confirm Local a valid pointer.
                                                        If remote has shared its OOB data, it can be set to oobData structure outside this function */
} ClxGapBleGenerateOobDataComplete;


/**
Set Bondable is used to make the local device bondable or non-bondable. The local device is in bondable mode by default.
A device in bondable mode is able to store bonding information of other devices in a permanent storage. A device in non-bondable mode
is still able to bond with other devices but will not store the bonding information in a permanent storage. Therefore, the bonding information will
not be available after the stack has re-started.

When the local device is in non-bondable mode, a request to perform permanent bonding (either from the local application or the remote device) will be rejected.

A device in bondable mode is able to perform both permanent and non-permanent bonding with other devices.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_SET_BONDABLE_COMPLETE.
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
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_COMMAND_NOT_SUPPORTED: When ClarinoxBlueLowEnergy.cfg file/paired device details storage database is not accessible.
*/
ClxResult clxGapBleSetBondable(_in_ ClxStack  stack,
                               _in_ boolean   bondable,
                               _in_ boolean   block);

/**
This API used to start the pairing procedure with the remote device. It is used for both Central and Peripheral roles.

In Central role, this API shall be called after using #clxGapBleConnectToPeripheral to establish the ACL connection.
Also, the same API shall be called once receiving the indication #CLX_GAP_BLE_SECURITY_REQUEST_INDICATION. This indication had received when the remote
peripheral device would sent a request to start the pairing procedure.

In Peripheral role, this API shall be called after receiving the indication #CLX_GAP_BLE_PAIRING_REQUEST_INDICATION to response the pairing request from central.
Also, the same API shall be called with \a bondingProperties value as #ClxBleSmpSecureBondingProperty_SecurityRequest to request the central to initiate pairing or bonding for new devices or encrypts
the connection for already paired devices.

NOTE:
In order for pairing procedure to be successful, both local device and remote device must be in bondable mode.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_START_BONDING_PROCEDURE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                 Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle      The handle of the physical connection to the remote device to which the bonding procedure is to be initiated.
\param[  in   ] bondingType           When this variable is set to TRUE, the bonding process will store the LTK (after bonding) if successful. If set to FALSE, pairing will be short term.
\param[  in   ] bondingProperties     Configuring the bonding properties, refer to #ClxBleSmpSecureBondingProperty.
\param[  in   ] maxEncryptionKeySize  Negotiating the encryption key size based on the local device.
\param[  in   ] localDistributeKeys   Configuring the local distribute keys, refer to #ClxBleSmpKeyDistribution.
\param[  in   ] remoteDistributeKeys  Configuring the remote distribute keys, refer to #ClxBleSmpKeyDistribution.
\param[  in   ] block                 Type of the operation.
                                        - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_GAP_LOCAL_DEVICE_NOT_BONDABLE: bonding is not possible since the local device is in non-bondable mode
        - #CLX_ERROR_BAD_STATE: The command is called at an inappropriate sequence/state.
        - #CLX_ERROR_GAP_PAIRED_DEVICES_COUNT_MAX_LIMIT_REACHED: When the configured maximum no of paired devices count (Ble.MaxNoOfPairedDevices) reached.
        - #CLX_ERROR_BLE_SMP_PASSKEY_ENTRY_FAILED: The user input of passkey failed, for example, the user canceled the operation.
        - #CLX_ERROR_BLE_SMP_OOB_NOT_AVAILABLE: The OOB data is not available.
        - #CLX_ERROR_BLE_SMP_AUTHENTICATION_REQUIREMENTS: The pairing procedure cannot be performed as authentication requirements cannot be met due to IO capabilities of one or both devices.
        - #CLX_ERROR_BLE_SMP_CONFIRM_VALUE_FAILED: The confirm value does not match the calculated compare value.
        - #CLX_ERROR_BLE_SMP_PAIRING_NOT_SUPPORTED: Pairing is not supported by the device.
        - #CLX_ERROR_BLE_SMP_ENCRYPTION_KEY_SIZE: The resultant encryption key size is insufficient for the security requirements of this device.
        - #CLX_ERROR_BLE_SMP_COMMAND_NOT_SUPPORTED: The SMP command received is not supported on this device.
        - #CLX_ERROR_BLE_SMP_UNSPECIFIED_REASON: Pairing failed due to an unspecified reason.
        - #CLX_ERROR_BLE_SMP_REPEATED_ATTEMPTS: Pairing or authentication procedure is disallowed because too little time has elapsed since last pairing request or security request.
        - #CLX_ERROR_BLE_SMP_INVALID_PARAMETERS: The Invalid Parameters error code indicates the command length is invalid a parameter is outside of the specified range.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid.
\remarks
Bonding is the procedure of pairing to a remote device permanently, by storing pairing information in a local storage area. When bonding is successful,
the devices can communicate without authentication and security measures as long as bonding information is not deleted by either the local device or the
remote device.
#clxGapBleStartBondingProcedure() is used to pair to a device permanently without an intention to connect to any specific service on the remote device. Any attempt
to connect to a remote device to use a service (except for SDAP) will automatically result in bonding as well (as long as both the local device and
the remote device are in bondable mode). Therefore, calling this function to pair to a remote device in order to use a service on that device is not
necessary.

Please refer the pairing procedure in \ref sec_sspble.
*/
ClxResult clxGapBleStartBondingProcedure(_in_ ClxStack                stack,
                                         _in_ ClxBleConnectionHandle  connectionHandle,
                                         _in_ ClxBleSmpBondingType    bondingType,
                                         _in_ u1                      bondingProperties,
                                         _in_ u1                      maxEncryptionKeySize,
                                         _in_ u1                      localDistributeKeys,
                                         _in_ u1                      remoteDistributeKeys,
                                         _in_ boolean                 block);



/**
This API used to reject the pairing request from central device. Also, the same API used to reject the security request from peripheral device.
In Central role, this API shall be called after receiving the indication #CLX_GAP_BLE_SECURITY_REQUEST_INDICATION.
In Peripheral role, this API shall be called after receiving the indication #CLX_GAP_BLE_PAIRING_REQUEST_INDICATION.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_REJECT_BONDING_PROCEDURE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack             Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle  The handle of the established physical connection.
\param[  in   ] block             Type of the operation.
                                    - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
*/
ClxResult clxGapBleRejectBondingProcedure(_in_ ClxStack                stack,
                                          _in_ ClxBleConnectionHandle  connectionHandle,
                                          _in_ boolean                 block);

/**
Replies to the Bluetooth controller's request to enter a passkey, by either providing a passkey, or rejecting the request. This function is only used if both the local
device and the remote device support Simple Secure Pairing.

NOTE: this function must only be called upon the reception of a #CLX_GAP_BLE_USER_PASSKEY_REQUEST_INDICATION indication.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_USER_PASSKEY_REQUEST_REPLY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack               Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle    The handle of the physical connection to the remote device.
\param[  in   ] userEnteredPasskey  If TRUE, the user has entered a passkey. If FALSE, the user has rejected the passkey request.
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
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BAD_STATE: The command is called at an inappropriate sequence/state.

\remarks
Please refer the pairing procedure in \ref sec_sspble.
*/
ClxResult clxGapBleUserPasskeyRequestReply(_in_ ClxStack                stack,
                                           _in_ ClxBleConnectionHandle  connectionHandle,
                                           _in_ boolean                 userEnteredPasskey,
                                           _in_ u4                      userPasskey,
                                           _in_ boolean                 block);

/**
Replies to the Bluetooth controller's request to confirm an authentication request from a remote device, by either confirming or rejecting the request.
This function is only used if both the local device and the remote device support LE secure pairing(4.2 compliance).

NOTE: this function must only be called upon the reception of a #CLX_GAP_BLE_USER_CONFIRMATION_REQUEST_INDICATION indication.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_USER_CONFIRMATION_REQUEST_REPLY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack             Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle  The handle of the physical connection to the remote device.
\param[  in   ] userOption        If TRUE, the user has confirmed the request. If FALSE, the user has rejected the request.
\param[  in   ] block             Type of the operation.
                                    - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BAD_STATE: The command is called at an inappropriate sequence/state.
*/
ClxResult clxGapBleUserConfirmationRequestReply(_in_ ClxStack                stack,
                                                _in_ ClxBleConnectionHandle  connectionHandle,
                                                _in_ boolean                 userOption,
                                                _in_ boolean                 block);

/**
This API is used to retrieve the stored remote device name from pairing information in local storage area.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_GET_PAIRED_DEVICE_NAME_COMPLETE.
                   The parameter of this indication is of type #ClxGapBleGetPairedDeviceNameComplete.

\param[  in   ] stack         Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] deviceAddr    The remote device address to retrieve the corresponding name.
\param[  out  ] deviceDetail  Application allocated buffer to store remote device name.
\param[  in   ] block         Type of the operation.
                                - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_BLE_REMOTE_DEVICE_NOT_FOUND_BY_IDENTITY_ADDRESS: There is no paired device exist for the given Bluetooth device address.
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid.
        - #CLX_ERROR_BLE_REMOTE_DEVICE_NAME_NOT_FOUND: If the device name is not found in stack database or not stored in the stack.
*/
ClxResult clxGapBleGetPairedDeviceName(_in_ ClxStack                            stack,
                                       _in_ const ClxBleBdAddress*              deviceAddr,
                                       _user_out_ ClxGapBlePairedDeviceDetail*  deviceDetail,
                                       _in_ boolean                             block);

/**
Get list of Paired Devices function will return a list of paired devices.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_GET_LIST_OF_PAIRED_DEVICES_COMPLETE.
                   The parameter of this indication is of type #ClxGapBleGetListOfPairedDevicesComplete.

Note that in the non-blocking mode, the list of paired devices will be stored in
a stack-provided buffer.

\param[  in   ] stack                  Local device stack handle. A stack object must be created before a GAP API used.
\param[  out  ] deviceAddrList         A caller-allocated array to store the list of paired devices. If a NULL value is passed, then the size of the paired list will be returned.
\param[  in   ] listSize               Maximum size of the above-mentioned list, if more devices are paired to the local device, returned list will be limited.
                                       This parameter MUST be zero when \p list is NULL.

\param[  out  ] numberOfPairedDevices  The actual number of paired devices. If this value is greater than \p listSize, only
                                       the first listSize number of paired devices have been returned in the caller-provided list. If this value is
                                       smaller than listSize, only the first listSize elements of the list have valid values.

\param[  in   ] block                  Type of the operation.
                                        - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                        - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_COMMAND_PARAMETER: One or more of provided arguments are invalid.
*/
ClxResult clxGapBleGetListOfPairedDevices(_in_ ClxStack                 stack,
                                          _user_out_ ClxBleBdAddress*   deviceAddrList,
                                          _in_ u4                       listSize,
                                          _user_out_ u4*                numberOfPairedDevices,
                                          _in_ boolean                  block);

/**
This API is used to store the user provided remote name into the pairing information in local storage area. Please note that this API should be called before calling the API #clxGapBleStartBondingProcedure.
In Central role, the local device may receive the remote device name through the indication #CLX_GAP_BLE_DEVICE_ADVERTISING_INDICATION.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_SET_PAIRED_DEVICE_NAME_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack             Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle  The handle of the established physical connection.
\param[  in   ] remoteDeviceName  The remote device name.
\param[  in   ] length            Remote device name length.
\param[  in   ] block             Type of the operation.
                                    - TRUE:  API will be blocked until this command is completed (successfully or failed).
                                    - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: One or more of provided arguments are invalid.

\remarks
Please note that the given name should be stored into pairing information when the local and remote devices have bonded successfully.
*/
ClxResult clxGapBleSetPairedDeviceName(_in_ ClxStack                stack,
                                       _in_ ClxBleConnectionHandle  connectionHandle,
                                       _in_ const s1*               remoteDeviceName,
                                       _in_ u1                      length,
                                       _in_ boolean                 block);

/**
Deletes pairing information of an already-paired remote device. If the remote device is also bonded, the pairing information will also be deleted from
the persistent storage.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_DELETE_PAIRED_DEVICE_INFO_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack       Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] deviceAddr  Bluetooth Address of the remote device of which the pairing information is to be deleted.
\param[  in   ] block       Type of the operation.
                            - TRUE:  API will be blocked until this command is completed (successfully or failed).
                            - FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_INVALID_DEVICE_ID: The device ID provided is invalid.
        - #CLX_ERROR_CONNECTION_EXISTS: Active connection exists to the paired device whose details are to be deleted.
        - #CLX_ERROR_BLE_DEVICE_NOT_PAIRED: Device whose details are to be deleted is not paired.
*/
ClxResult clxGapBleDeletePairedDeviceInfo(_in_ ClxStack                   stack,
                                          _in_ const ClxBleBdAddress*     deviceAddr,
                                          _in_ boolean                    block);

/**
Deletes pairing information of all already-paired remote devices. If a remote device is also bonded, the pairing information will also be deleted from
the persistent storage.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the GAP call-back function will be called with an indication of type #CLX_GAP_BLE_DELETE_ALL_PAIRED_DEVICES_INFO_COMPLETE.
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
        - #CLX_ERROR_COMMAND_CANCELLED: The handle to GAP was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - #CLX_ERROR_CONNECTION_EXISTS: Active connection exists to a paired device.
        - #CLX_ERROR_BLE_DEVICE_NOT_PAIRED: There are no paired devices.
*/
ClxResult clxGapBleDeleteAllPairedDevicesInfo(_in_ ClxStack  stack,
                                              _in_ boolean   block);
/**
This command generates new Out-of-Band (OOB) data and key material for the local device. The generated keys can be used for OOB pairing and shared with the remote device when required.

Keys are generated only for parameters that point to valid memory locations; any null or invalid pointers will be ignored by the stack.
It is mandatory to provide valid memory for localPublicKeyX, localPublicKeyY, and localPrivateKey.

To generate and share OOB data (randomLocal and confirmLocal) via NFC, valid memory pointers must be provided for these fields.
The parameters randomRemote and confirmRemote are not applicable for this API.

If isSecureBonding is set to false, the fields randomLocal and confirmLocal will be filled with zeros.

Once these keys are generated, enable the OOB method of authentication using #clxGapBleEnableDisableOobPairing

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                    When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_GENERATE_OOB_DATA_COMPLETE.
                    The parameter of this indication is of type #ClxGapBleGenerateOobDataComplete.

\param[  in   ] stack            Stack
\param[  in   ] isSecureBonding  Secure connections or legacy
\param[  out  ] oobData          Generated OOB keys of local device. Pass the pointer with valid values for whichever applicable.
                                    Public Key X, Y, Private key shall not be NULL.
                                    If OOB data for local has to be generated, pass the Random and Confirm Local a valid pointer.
                                    If remote has shared its OOB data, it can be set to oobData structure outside this function
\param[  in   ] block            Indicates mode of operation:TRUE : Blocking mode FALSE : Non-blocking mode

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

*/
ClxResult clxGapBleGenerateOobData(_in_ ClxStack                    stack,
                                   _in_ boolean                     isSecureBonding,
                                   _user_out_ ClxBleOobKeyDetails*  oobData,
                                   _in_ boolean                     block);

/**
This command enables or disables Out-of-Band (OOB) pairing using the specified OOB data of the local and remote devices.

The provided OOB data keys are utilized during the subsequent OOB pairing procedure. The OOB data keys can be generated using #clxGapBleGenerateOobData.
The parameters randomRemote and confirmRemote should contain the values obtained from the remote device via NFC. If these values are not available, they may be omitted.
After the pairing procedure is completed, it is recommended to disable OOB pairing.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                    When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_ENABLE_DISABLE_OOB_PAIRING_COMPLETE.
                    This indication does not have any parameters.

\param[  in   ] stack             Stack
\param[  in   ] connectionHandle  GAP BLE ACL Connection Handle
\param[  in   ] enable            TRUE: to enable the OOB pairing and FALSE to disable.
\param[  in   ] isSecureBonding   Secure connections or legacy
\param[  in   ] oobData           Generated OOB keys of local device. If remote device has provided its OOB data,
                                    it has to be provided to this key details by assigning the remote Random and Confirm values.
                                    oobData isn't applicable is enable is FALSE.
\param[  in   ] block             Indicates mode of operation:TRUE : Blocking mode FALSE : Non-blocking mode

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

*/
ClxResult clxGapBleEnableDisableOobPairing(_in_ ClxStack                         stack,
                                           _in_ ClxBleConnectionHandle           connectionHandle,
                                           _in_ boolean                          enable,
                                           _in_ boolean                          isSecureBonding,
                                           _user_in_ const ClxBleOobKeyDetails*  oobData,
                                           _in_ boolean                          block);


#ifdef __cplusplus
}
#endif

#endif  // __GAP_BLE_BONDING_API_h__
