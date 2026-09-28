#ifndef __org_bluetooth_service_generic_media_control_service_h__
#define __org_bluetooth_service_generic_media_control_service_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.generic_media_control_service.h
* Description         Declares definitions for the GATT service Generic Media Control Service
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2024 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/**
Generic Media Control Service GATT Service:
This specification describes two services: Media Control Service (MCS) and Generic Media Control
Service (GMCS).
*/
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_NAME    "Generic Media Control Service"
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_UUID    0x1849

/**
Media Player Name Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicMediaPlayerNameFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME                 "Media Player Name"
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_STRUCT          struct ClxOrgBluetoothCharacteristicMediaPlayerNameFields
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_VALUE_TYPE      ClxOrgBluetoothCharacteristicMediaPlayerNameFields_Type
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_SIZE            ClxOrgBluetoothCharacteristicMediaPlayerNameFields_Size
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_PLAYER_NAME_UUID            0x2B93

/**
Track Changed Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicTrackChangedFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED                 "Track Changed"
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_HANDLE_INDEX    5
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_STRUCT          struct ClxOrgBluetoothCharacteristicTrackChangedFields
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_VALUE_TYPE      ClxOrgBluetoothCharacteristicTrackChangedFields_Type
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_SIZE            ClxOrgBluetoothCharacteristicTrackChangedFields_Size
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_CHANGED_UUID            0x2B96

/**
Track Title Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicTrackTitleFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE                 "Track Title"
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_HANDLE_INDEX    8
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_STRUCT          struct ClxOrgBluetoothCharacteristicTrackTitleFields
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_VALUE_TYPE      ClxOrgBluetoothCharacteristicTrackTitleFields_Type
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_SIZE            ClxOrgBluetoothCharacteristicTrackTitleFields_Size
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_TITLE_UUID            0x2B97

/**
Track Duration Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicTrackDurationFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION                 "Track Duration"
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_HANDLE_INDEX    10
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_STRUCT          struct ClxOrgBluetoothCharacteristicTrackDurationFields
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_VALUE_TYPE      ClxOrgBluetoothCharacteristicTrackDurationFields_Type
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_SIZE            ClxOrgBluetoothCharacteristicTrackDurationFields_Size
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_DURATION_UUID            0x2B98

/**
Track Position Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicTrackPositionFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION                 "Track Position"
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_HANDLE_INDEX    12
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE_WITHOUT_RESPONSE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_STRUCT          struct ClxOrgBluetoothCharacteristicTrackPositionFields
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_VALUE_TYPE      ClxOrgBluetoothCharacteristicTrackPositionFields_Type
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_SIZE            ClxOrgBluetoothCharacteristicTrackPositionFields_Size
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_TRACK_POSITION_UUID            0x2B99

/**
Media State Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicMediaStateFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE                 "Media State"
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_HANDLE_INDEX    14
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_STRUCT          struct ClxOrgBluetoothCharacteristicMediaStateFields
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_VALUE_TYPE      ClxOrgBluetoothCharacteristicMediaStateFields_Type
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_SIZE            ClxOrgBluetoothCharacteristicMediaStateFields_Size
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_MEDIA_STATE_UUID            0x2BA3

/**
Content Control ID Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicContentControlIdFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID                 "Content Control ID"
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_HANDLE_INDEX    17
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_STRUCT          struct ClxOrgBluetoothCharacteristicContentControlIdFields
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_VALUE_TYPE      ClxOrgBluetoothCharacteristicContentControlIdFields_Type
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_SIZE            ClxOrgBluetoothCharacteristicContentControlIdFields_Size
#define CLX_GATT_SERVICE_GENERIC_MEDIA_CONTROL_SERVICE_CHARACTERISTIC_CONTENT_CONTROL_ID_UUID            0x2BBA

/**
Returns the interface to Generic Media Control Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Generic Media Control Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetGenericMediaControlServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __org_bluetooth_service_generic_media_control_service_h__

