#ifndef __org_bluetooth_service_alert_notification_h__
#define __org_bluetooth_service_alert_notification_h__

/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.alert_notification.h
* Description         Declares definitions for the GATT service 
*                     Alert Notification Service
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
Alert Notification Service GATT Service:
Alert Notification service exposes:
The different types of alerts with the short text messages.
The information how many count of new alert messages.
The information how many count of unread alerts.
*/
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_NAME    "Alert Notification Service"
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_UUID    0x1811

/**
Supported New Alert Category Characteristic:
This characteristic exposes what categories of new alert are supported in the server.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY                 "Supported New Alert Category"
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_STRUCT          struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_VALUE_TYPE      ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields_Type
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_SIZE            ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields_Size
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_NEW_ALERT_CATEGORY_UUID            0x2A47


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicSupportedNewAlertCategory.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicSupportedNewAlertCategory.
*/
struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields
{
    /**
    Field : Category ID Bit Mask 0
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Value Enumerations :
    {
        0 : Not Supported
        1 : Supported
    }
    */
    u1 categoryIdBitMask0;

    /**
    Field : Category ID Bit Mask 1
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Optional
    Value Enumerations :
    {
        0 : Not Supported
        1 : Supported
    }
    */
    u1 categoryIdBitMask1;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields
*/
#define ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields
*/
#define ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields_Size    (1 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSupportedNewAlertCategory(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSupportedNewAlertCategoryFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSupportedNewAlertCategory(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);


/**
New Alert Characteristic:
This characteristic exposes information about the count of new alerts (for a given category).
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicNewAlertFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT                 "New Alert"
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_HANDLE_INDEX    4
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_STRUCT          struct ClxOrgBluetoothCharacteristicNewAlertFields
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_VALUE_TYPE      ClxOrgBluetoothCharacteristicNewAlertFields_Type
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_SIZE            ClxOrgBluetoothCharacteristicNewAlertFields_Size
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_NEW_ALERT_UUID            0x2A46


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicNewAlert.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicNewAlert.
*/
struct ClxOrgBluetoothCharacteristicNewAlertFields
{
    /**
    Field : Category ID
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 255
    Value Enumerations :
    {
        0 : Simple Alert: General text alert or non-text alert
        1 : Email: Alert when Email messages arrives
        2 : News: News feeds such as RSS, Atom
        3 : Call: Incoming call
        4 : Missed call: Missed Call
        5 : SMS/MMS: SMS/MMS message arrives
        6 : Voice mail: Voice mail
        7 : Schedule: Alert occurred on calendar, planner
        8 : High Prioritized Alert: Alert that should be handled as high priority
        9 : Instant Message: Alert for incoming instant messages
        251 - 255 : Defined in the service specification
    }
    */
    u1 categoryId;

    /**
    Field : Number of New Alert
    Format : uint8
    Unit : Not Available
    Description : This field provides the number of new alerts in the server.
    Requirement : Mandatory
    Minimum : 0
    Maximum : 255
    */
    u1 numberOfNewAlert;

    /**
    Field : Text String Information
    Format : utf8s
    Unit : Not Available
    Description : The field provides brief text information for the last alert.
    Requirement : Optional
    Minimum : 0
    Maximum : 7
    */
    s1 textStringInformation[16];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicNewAlertFields
*/
#define ClxOrgBluetoothCharacteristicNewAlertFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicNewAlertFields
*/
#define ClxOrgBluetoothCharacteristicNewAlertFields_Size    (1 + 1 + 16)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicNewAlertFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicNewAlertFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicNewAlertFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicNewAlert(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicNewAlertFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicNewAlertFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicNewAlertFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicNewAlert(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Supported Unread Alert Category Characteristic:
This characteristic exposes what categories of unread alert are supported in the server.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY                 "Supported Unread Alert Category"
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_HANDLE_INDEX    7
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_STRUCT          struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_VALUE_TYPE      ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields_Type
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_SIZE            ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields_Size
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_SUPPORTED_UNREAD_ALERT_CATEGORY_UUID            0x2A48


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicSupportedUnreadAlertCategory.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicSupportedUnreadAlertCategory.
*/
struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields
{
    /**
    Field : Category ID Bit Mask 0
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Value Enumerations :
    {
        0 : Not Supported
        1 : Supported
    }
    */
    u1 categoryIdBitMask0;

    /**
    Field : Category ID Bit Mask 1
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Optional
    Value Enumerations :
    {
        0 : Not Supported
        1 : Supported
    }
    */
    u1 categoryIdBitMask1;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields
*/
#define ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields
*/
#define ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields_Size    (1 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSupportedUnreadAlertCategory(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSupportedUnreadAlertCategoryFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSupportedUnreadAlertCategory(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);

/**
Unread Alert Status Characteristic:
This characteristic exposes the count of unread alert events existing in the server
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicUnreadAlertStatusFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS                 "Unread Alert Status"
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_HANDLE_INDEX    9
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_STRUCT          struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_VALUE_TYPE      ClxOrgBluetoothCharacteristicUnreadAlertStatusFields_Type
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_SIZE            ClxOrgBluetoothCharacteristicUnreadAlertStatusFields_Size
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_UNREAD_ALERT_STATUS_UUID            0x2A45

/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicUnreadAlertStatus.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicUnreadAlertStatus.
*/
struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields
{
    /**
    Field : Category ID
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 255
    Value Enumerations :
    {
        0 : Simple Alert: General text alert or non-text alert
        1 : Email: Alert when Email messages arrives
        2 : News: News feeds such as RSS, Atom
        3 : Call: Incoming call
        4 : Missed call: Missed Call
        5 : SMS/MMS: SMS/MMS message arrives
        6 : Voice mail: Voice mail
        7 : Schedule: Alert occurred on calendar, planner
        8 : High Prioritized Alert: Alert that should be handled as high priority
        9 : Instant Message: Alert for incoming instant messages
        251 - 255 : Defined in the service specification
    }
    */
    u1 categoryId;

    /**
    Field : Unread count
    Format : uint8
    Unit : Not Available
    Description : How many unread alerts exist on the server.
If the value is 255, it means Unread count is greater than 254.
    Requirement : Mandatory
    Minimum : 0
    Maximum : 255
    */
    u1 unreadCount;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicUnreadAlertStatusFields
*/
#define ClxOrgBluetoothCharacteristicUnreadAlertStatusFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicUnreadAlertStatusFields
*/
#define ClxOrgBluetoothCharacteristicUnreadAlertStatusFields_Size    (1 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicUnreadAlertStatusFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicUnreadAlertStatusFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicUnreadAlertStatus(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicUnreadAlertStatusFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicUnreadAlertStatusFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicUnreadAlertStatusFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicUnreadAlertStatus(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);

/**
Alert Notification Control Point Characteristic:
This characteristic allows the peer device to enable/disable the alert notification of new alert and unread event more
selectively than can be done by setting or clearing the notification bit in the Client Characteristic Configuration for each alert
characteristic.
The UUID of this characteristic is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT                 "Alert Notification Control Point"
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_HANDLE_INDEX    12
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE)
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_STRUCT          struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_VALUE_TYPE      ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields_Type
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_SIZE            ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields_Size
#define CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_CHARACTERISTIC_ALERT_NOTIFICATION_CONTROL_POINT_UUID            0x2A44

/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicAlertNotificationControlPoint.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicAlertNotificationControlPoint.
*/
struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields
{
    /**
    Field : Command ID
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Value Enumerations :
    {
        0 : Enable New Incoming Alert Notification
        1 : Enable Unread Category Status Notification
        2 : Disable New Incoming Alert Notification
        3 : Disable Unread Category Status Notification
        4 : Notify New Incoming Alert immediately
        5 : Notify Unread Category Status immediately
    }
    */
    u1 commandId;

    /**
    Field : Category ID
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    Minimum : 0
    Maximum : 255
    Value Enumerations :
    {
        0 : Simple Alert: General text alert or non-text alert
        1 : Email: Alert when Email messages arrives
        2 : News: News feeds such as RSS, Atom
        3 : Call: Incoming call
        4 : Missed call: Missed Call
        5 : SMS/MMS: SMS/MMS message arrives
        6 : Voice mail: Voice mail
        7 : Schedule: Alert occurred on calendar, planner
        8 : High Prioritized Alert: Alert that should be handled as high priority
        9 : Instant Message: Alert for incoming instant messages
        251 - 255 : Defined in the service specification
    }
    */
    u1 categoryId;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields
*/
#define ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields
*/
#define ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields_Size    (1 + 1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicAlertNotificationControlPoint(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicAlertNotificationControlPointFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicAlertNotificationControlPoint(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);

/**
Returns the interface to Alert Notification Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Alert Notification Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetAlertNotificationServiceGattServiceInterface();

#ifdef __cplusplus
}
#endif

#endif /* __org_bluetooth_service_alert_notification_h__ */

