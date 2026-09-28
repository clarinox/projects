#ifndef __GattBleIncludes__
#define __GattBleIncludes__

/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                Gatt.Ble.Includes.h
* Description         This file has defined the BLE GATT services
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/

/*
GATT services indexs
*/
typedef enum GattServicesIndexEnum
{
    GattService_GenericAccessIndex             = 0,
    GattService_GenericAttributeIndex,
    GattService_CustomIndex,
    GattService_BatteryIndex,
    GattService_DeviceInformationIndex,
    GattService_AlertNotificationIndex,
#if defined(CLX_BLE_CS_REFLECTOR)
    GattService_RangingServiceIndex,
#endif
#if defined(CLX_BLE_HID)
    GattService_HumanInterfaceDeviceIndex,
#endif /* defined(CLX_BLE_HID) */
#if defined(CLX_BLE_ISOCHRONOUS)
    GattService_AudioStreamControlIndex,
    GattService_PublishedAudioCapabilitiesIndex,
    GattService_VolumeControlGattServiceIndex,
    GattService_BroadcastAudioScanServiceIndex,
    GattService_TelephonyMediaAudioServiceIndex,
#endif /* defined(CLX_BLE_ISOCHRONOUS) */
    NumberOfBleGattServices
}GattServicesIndex;

/**
Include GATT service headers
*/
#include "org.bluetooth.service.generic_access.h"
#include "org.bluetooth.service.generic_attribute.h"
#include "Gatt.custom_service.h"
#include "org.bluetooth.service.battery_service.h"
#include "org.bluetooth.service.device_information.h"
#include "org.bluetooth.service.alert_notification.h"
#include "org.bluetooth.characteristic.gap.resolvable_private_address_only.h"
#if defined(CLX_BLE_CS_REFLECTOR)
#include "org.bluetooth.service.ranging_service.h"
#endif
#if defined(CLX_BLE_HID)
#include "org.bluetooth.service.human_interface_device.h"
#endif /* defined(CLX_BLE_HID) */

#if defined(CLX_BLE_ISOCHRONOUS)
#include "org.bluetooth.service.audiostream_control.h"
#include "org.bluetooth.service.audio_input_control_service.h"
#include "org.bluetooth.service.published_audiocapabilities.h"
#include "org.bluetooth.service.volume_control_service.h"
#include "org.bluetooth.service.volume_offset_control_service.h"
#include "org.bluetooth.service.broadcast_audioscan.h"
#include "org.bluetooth.service.telephony_media_audio.h"
#endif /* defined(CLX_BLE_ISOCHRONOUS) */

#define INVALID_SERVICE_BASE_HANDLE     0xFFFF

#ifdef __cplusplus
extern "C" {
#endif

const s1* clxGetGenericAccessGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetGenericAttributeGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetCustomServiceGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetBatteryServiceGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetDeviceInformationGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetAlertNotificationServiceGattServiceCharacteristicName(u2 handleIndex);
#if defined(CLX_BLE_CS_REFLECTOR)
const s1* clxGetRangingServiceGattServiceCharacteristicName(u2 handleIndex);
#endif
#if defined(CLX_BLE_HID)
const s1* clxGetHumanInterfaceDeviceGattServiceCharacteristicName(u2 handleIndex);
#endif /* defined(CLX_BLE_HID) */

#if defined(CLX_BLE_ISOCHRONOUS)
const s1* clxGetAudioStreamControlGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetAudioInputControlServiceGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetPublishedAudioCapabilitiesGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetVolumeControlServiceGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetBroadcastAudioScanGattServiceCharacteristicName(u2 handleIndex);
const s1* clxGetTelephonyMediaAudioServiceGattCharacteristicName(u2 handleIndex);
#endif /* defined(CLX_BLE_ISOCHRONOUS) */

extern ClxBleGattServiceInfo clxBleGattServiceList[NumberOfBleGattServices];

#ifdef __cplusplus
}
#endif

#endif // __GattBleIncludes__

