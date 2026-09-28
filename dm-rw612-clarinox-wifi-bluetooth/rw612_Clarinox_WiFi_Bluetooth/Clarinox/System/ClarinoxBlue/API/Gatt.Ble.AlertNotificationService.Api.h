#ifndef __Gatt_Ble_AlertNotificationService_Api_h__
#define __Gatt_Ble_AlertNotificationService_Api_h__

/********************************************************************************
*
* Project             GattBleAlertNotificationService
* File                Gatt.Ble.AlertNotificationService.Api.h
* Description         Declares API Functions and Definitions For GattBleAlertNotificationService
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/**
Refer to #clxGattGetAlertCategory function.
*/
#define CLX_GATT_GET_ALERT_CATEGORY_COMPLETE                                                0x7201

/**
Refer to #clxGattSetAlertCategory function.
*/
#define CLX_GATT_SET_ALERT_CATEGORY_COMPLETE                                                0x7202

/**
Refer to #clxGattSetAlert function.
*/
#define CLX_GATT_SET_ALERT_COMPLETE                                                         0x7203

/**
Refer to #clxGattGetUnreadAlertCategory function.
*/
#define CLX_GATT_GET_UNREAD_ALERT_CATEGORY_COMPLETE                                         0x7204

/**
Refer to #clxGattSetUnreadAlertCategory function.
*/
#define CLX_GATT_SET_UNREAD_ALERT_CATEGORY_COMPLETE                                         0x7205

/**
Refer to #clxGattSetUnreadAlertStatus function.
*/
#define CLX_GATT_SET_UNREAD_ALERT_STATUS_COMPLETE                                           0x7206

/**
Refer to #clxGattConfigureAlertNotification function.
*/
#define CLX_GATT_CONFIGURE_ALERT_NOTIFICATION_COMPLETE                                      0x7207

/**
Valid values for Alert Category ID.
*/
typedef enum ClxAlertCategoryIdEnum
{
    ClxAlertCategoryId_SimpleAlert            = 0x00,    /*!< General text alert or non-text alert.          */
    ClxAlertCategoryId_EmailAlert             = 0x01,    /*!< Alert when Email messages arrives.             */
    ClxAlertCategoryId_NewsAlert              = 0x02,    /*!< News feeds such as RSS, Atom.                  */
    ClxAlertCategoryId_IncomingCallAlert      = 0x03,    /*!< Incoming call.                                 */
    ClxAlertCategoryId_MissedCallAlert        = 0x04,    /*!< Missed Call.                                   */
    ClxAlertCategoryId_SmsMmsAlert            = 0x05,    /*!< SMS/MMS message arrives.                       */
    ClxAlertCategoryId_VoiceMailAlert         = 0x06,    /*!< Voice mail.                                    */
    ClxAlertCategoryId_ScheduleAlert          = 0x07,    /*!< Alert occurred on calendar, planner.           */
    ClxAlertCategoryId_HighPrioritizedAlert   = 0x08,    /*!< Alert that should be handled as high priority. */
    ClxAlertCategoryId_InstantMessageAlert    = 0x09     /*!< Alert for incoming instant messages.           */
} ClxAlertCategoryId;

/**
Valid values for Alert Command ID.
*/
typedef enum ClxAlertCommandIdEnum
{
    ClxAlertCommandId_EnableNewIncomingAlert                  = 0x00,    /*!< Enable new incoming alert notification.      */
    ClxAlertCommandId_EnableUnreadCategoryStatus              = 0x01,    /*!< Enable unread category status notification.  */
    ClxAlertCommandId_DisableNewIncomingAlert                 = 0x02,    /*!< Disable new incoming alert notification.     */
    ClxAlertCommandId_DisableUnreadCategoryStatus             = 0x03,    /*!< Disable unread category status notification. */
    ClxAlertCommandId_NotifyNewAlertImmediately               = 0x04,    /*!< Notify new incoming alert immediately.       */
    ClxAlertCommandId_NotifyUnreadCategoryStatusImmediately   = 0x05     /*!< Notify unread category status immediately.   */
} ClxAlertCommandId;

/**
More information about the Alert details.
*/
typedef struct ClxAlertDetailsStruct
{
    u1   categoryId;            /*!< Category of the alert */
    u1   numberOfNewAlert;      /*!< Total number of new alert */
    s1*  AdditionalInfo;        /*!< Additional Information of the alert.Maximum size of AdditionalInfo is 16 bytes */
    u1   AdditionalInfoLength;  /*!< Total length of the AdditionalInfo */
} ClxAlertDetails;

/**
More information about the Supported Alert Category.
*/
typedef struct ClxAlertCategoryStruct
{
    u1  categoryIdBitMask0;    /*!< Category ID Bit Mask 0 */
    u1  categoryIdBitMask1;    /*!< Category ID Bit Mask 1 */
} ClxAlertCategory;

/**
Data Structure for the indication #CLX_GATT_GET_ALERT_CATEGORY_COMPLETE
*/
typedef struct ClxGattGetAlertCategoryCompleteStruct
{
    _user_out_ ClxAlertCategory*  supportedCategory;    /*!< A caller-allocated structure of type 'ClxAlertCategory', will contain the value of supported alert category upon successful 
                                                             completion.The buffer shall be not modified or deleted until this command is complete. */
} ClxGattGetAlertCategoryComplete;

/**
This API retrieves the supported new alert category from GATT database. It can be used by both roles GATT client (Central) and GATT Server (Peripheral).

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_GET_ALERT_CATEGORY_COMPLETE.
                   The parameter of this indication is of type #ClxGattGetAlertCategoryComplete.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             The value handle of the 'supported new alert category' characteristic. If the local device operates as a GATT client, 
                                   the value handle of the 'supported new alert category' characteristic can be obtained using the #clxGattClientGetValueHandle API.
                                   If the local device functions as a GATT server, the handle value should be derived from the base handle plus the handle index of the 'supported new alert category' characteristic.
\param[  in   ] inputBuffer        The user should allocate a sizeof(ClxAlertCategory) bytes to retrieve the supported new alert category.
\param[  out  ] supportedCategory  A caller-allocated structure of type 'ClxAlertCategory', will contain the value of supported new alert category upon successful 
                                   completion.The buffer shall be not modified or deleted until this command is complete.
\param[  in   ] block              Type of the operation.
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

        - #CLX_SUCCESS: Operation is successful
        - #Any other error code: This operation has failed
*/
ClxResult clxGattGetAlertCategory(_in_ ClxHandle                gatt,
                                  _in_ u2                       handle,
                                  _user_in_ u1*                 inputBuffer,
                                  _user_out_ ClxAlertCategory*  supportedCategory,
                                  _in_ boolean                  block);

/**
This API sets the supported alert category into GATT database. It can be used by GATT Server (Peripheral) only.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_SET_ALERT_CATEGORY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt           The handle of the GATT server.
\param[  in   ] handle         The value handle of the supported new alert category characteristic. The handle value should be derived from the base handle plus the 
                               handle index of the supported new alert category characteristic.
\param[  in   ] alertCategory  Supported alert category value to write to the New Alert Category Characteristic.
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

        - #CLX_SUCCESS: Operation is successful
        - #Any other error code: This operation has failed
*/
ClxResult clxGattSetAlertCategory(_in_ ClxHandle               gatt,
                                  _in_ u2                      handle,
                                  _user_in_ ClxAlertCategory*  alertCategory,
                                  _in_ boolean                 block);

/**
This API sets the new Alert into GATT database.It can be used by GATT Server (Peripheral)only.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_SET_ALERT_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt          The handle of the GATT server.
\param[  in   ] handle        The value handle of the 'New Alert' characteristic. The handle value should be derived
                              from the base handle plus the handle index of the 'New Alert' characteristic.
\param[  in   ] alertDetails  Input alert details to set the GATT database
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

        - #CLX_SUCCESS: Operation is successful
        - #CLX_ERROR_COMMAND_NOT_SUPPORTED: If GATT Server/ANS is not supported by/enabled in stack
        - #CLX_ERROR_BLE_ATT_INVALID_HANDLE: The value handle given was not valid on this server
        - #CLX_ERROR_BLE_ATT_WRITE_NOT_PERMITTED: The attribute cannot be written
        - #CLX_ERROR_TIMEOUT_OCCURRED: Set new alert done, but timeout occurred for sending notification/indication due to no response from remote device
*/
ClxResult clxGattSetAlert(_in_ ClxHandle                    gatt,
                          _in_ u2                           handle,
                          _user_in_ ClxAlertDetails*        alertDetails,
                          _in_ boolean                      block);

/**
Data Structure for the indication #CLX_GATT_GET_UNREAD_ALERT_CATEGORY_COMPLETE
*/
typedef struct ClxGattGetUnreadAlertCategoryCompleteStruct
{
    _user_out_ ClxAlertCategory*  supportedCategory;    /*!< A caller-allocated structure of type 'ClxAlertCategory', will contain the value of supported unread alert category upon successful 
                                                             completion. The buffer shall be not modified or deleted until this command is complete. */
} ClxGattGetUnreadAlertCategoryComplete;

/**
This API retrieves the supported unread alert category from GATT database. It can be used by both roles GATT Client (Central) and GATT Server (Peripheral).

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_GET_UNREAD_ALERT_CATEGORY_COMPLETE.
                   The parameter of this indication is of type #ClxGattGetUnreadAlertCategoryComplete.

\param[  in   ] gatt               The handle of the GATT client or server.
\param[  in   ] handle             The value handle of the 'supported unread alert category' characteristic. If the local device operates as a GATT client, 
                                   the value handle of the 'supported unread alert category' characteristic can be obtained using the #clxGattClientGetValueHandle API.
                                   If the local device functions as a GATT server, the handle value should be derived from the base handle plus the handle index of the 'supported unread alert category' characteristic.
\param[  in   ] inputBuffer        The user should allocate a sizeof(ClxAlertCategory) bytes to retrieve the supported unread alert category.
\param[  out  ] supportedCategory  A caller-allocated structure of type 'ClxAlertCategory', will contain the value of supported unread alert category upon successful completion.
                                   The buffer shall be not modified or deleted until this command is complete.
\param[  in   ] block              Type of the operation.
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

        - #CLX_SUCCESS: Operation is successful
        - #Any other error code: This operation has failed
*/
ClxResult clxGattGetUnreadAlertCategory(_in_ ClxHandle                gatt,
                                        _in_ u2                       handle,
                                        _user_in_ u1*                 inputBuffer,
                                        _user_out_ ClxAlertCategory*  supportedCategory,
                                        _in_ boolean                  block);


/**
This API sets the supported un read alert category into GATT database. It can be used by GATT Server (Peripheral) only.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_SET_UNREAD_ALERT_CATEGORY_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt           The handle of the GATT server.
\param[  in   ] handle         The value handle of the supported unread alert category characteristic. The handle value should be derived from the base handle plus the 
                               handle index of the supported unread alert category characteristic.
\param[  in   ] alertCategory  Supported unread alert category value to write to the Unread Alert Category Characteristic.
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

        - #CLX_SUCCESS: Operation is successful
        - #Any other error code: This operation has failed
*/
ClxResult clxGattSetUnreadAlertCategory(_in_ ClxHandle                     gatt,
                                        _in_ u2                            handle,
                                        _user_in_ ClxAlertCategory*        alertCategory,
                                        _in_ boolean                       block);

/**
This API sets the unread alert events into GATT database. It can be used by GATT Server (Peripheral) only.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_SET_UNREAD_ALERT_STATUS_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt         The handle of the GATT server.
\param[  in   ] handle       The value handle of the unread alert status characteristic. The handle value should be derived from the base handle plus the 
                             handle index of the unread alert status characteristic.
\param[  in   ] categoryID   Specifies the Category ID to be set. This parameter is of type #ClxAlertCategoryId.
\param[  in   ] unreadCount  The number of unread alerts to set or update.
\param[  in   ] block        Type of the operation.
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

        - #CLX_SUCCESS: Operation is successful
        - #Any other error code: This operation has failed
*/
ClxResult clxGattSetUnreadAlertStatus(_in_ ClxHandle            gatt,
                                      _in_ u2                   handle,
                                      _in_ ClxAlertCategoryId   categoryID,
                                      _in_ u1                   unreadCount,
                                      _in_ boolean              block);

/**
This API allows a client device to send commands to enable or disable notifications for a specific alert on a GATT server device.
It can be used by GATT Client (Central) only.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CONFIGURE_ALERT_NOTIFICATION_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt        The handle of the GATT server.
\param[  in   ] handle      The value handle of the unread alert status characteristic. The handle value should be derived from the base handle plus the 
                            handle index of the unread alert status characteristic.
\param[  in   ] commandId   Specifies the Alert command ID to enable or disable the notification of specific alert. This parameter is of type #ClxAlertCommandId.
\param[  in   ] categoryId  Specifies the Alert category ID to enable or disable alert notification. This parameter is of type #ClxAlertCategoryId.
\param[  in   ] block       Type of the operation.
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

        - #CLX_SUCCESS: Operation is successful
        - #Any other error code: This operation has failed
*/
ClxResult clxGattConfigureAlertNotification(_in_ ClxHandle           gatt,
                                            _in_ u2                  handle,
                                            _in_ ClxAlertCommandId   commandId,
                                            _in_ ClxAlertCategoryId  categoryId,
                                            _in_ boolean             block);

#ifdef __cplusplus
}
#endif



#endif // __Gatt_Ble_AlertNotificationService_Api_h__
