#ifndef __org_bluetooth_service_telephony_media_audio_h__
#define __org_bluetooth_service_telephony_media_audio_h__

/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.telephony_media_audio.h
* Description         Declares definitions for the Telephony Media Audio Service.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/**
Telephony Media Audio Service:
The TMA service exposes the supported role.
*/
#define CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_NAME         "Telephony Media Audio Service"
#define CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_UUID         0x1855

/**
TMAP role Characteristic:
Rx data buffer
The UUID of this characteristic is defined by #CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_UUID.

The value of this characteristic is of type #ClxGattTelephonyMediaAudioCharacteristcRoleFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_PERMISSIONS.
*/
#define CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE                 "TMAP Role"
#define CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_HANDLE_INDEX    2
#define CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_STRUCT          struct ClxGattTelephonyMediaAudioCharacteristcRoleFields
#define CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_VALUE_TYPE      ClxGattTelephonyMediaAudioCharacteristcRoleFields_Type
#define CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_SIZE            ClxGattTelephonyMediaAudioCharacteristcRoleFields_Size
#define CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_CHARACTERISTIC_ROLE_UUID            0x2B51

struct ClxGattTelephonyMediaAudioCharacteristcRoleFields
{
    /**
    Field : TMAP role
    Format : uint16
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u2 role;
};

/**
Defines the value type of the structure #ClxGattTelephonyMediaAudioCharacteristcRoleFields
*/
#define ClxGattTelephonyMediaAudioCharacteristcRoleFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxGattTelephonyMediaAudioCharacteristcRoleFields
*/
#define ClxGattTelephonyMediaAudioCharacteristcRoleFields_Size    (2)


/**
Returns the interface to Telephony Media Audio service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Telephony Media Audio service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetTelephonyMediaAccessServiceInterface();


#ifdef __cplusplus
}
#endif

#endif // __org_bluetooth_service_telephony_media_audio_h__

