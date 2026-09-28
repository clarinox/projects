/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                Gatt.Ble.Includes.cpp
* Description         This file provides the list of GATT service details
*                     and its function declarations.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/

#include "ClxBsp.h"
#include "ClarinoxBlue.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Includes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
Include the Bluetooth SIG and custom services to local GATT server.
*/
ClxBleGattServiceInfo clxBleGattServiceList[NumberOfBleGattServices] =
                                            {
                                                  {0, CLX_GATT_SERVICE_GENERIC_ACCESS_NAME, clxGetGenericAccessGattServiceInterface, clxGetGenericAccessGattServiceCharacteristicName}
                                                , {0, CLX_GATT_SERVICE_GENERIC_ATTRIBUTE_NAME, clxGetGenericAttributeGattServiceInterface, clxGetGenericAttributeGattServiceCharacteristicName}
                                                , {0, CLX_GATT_SERVICE_CUSTOM_SERVICE_NAME, clxGetCustomServiceGattServiceInterface, clxGetCustomServiceGattServiceCharacteristicName}
                                                , {0, CLX_GATT_SERVICE_BATTERY_SERVICE_NAME, clxGetBatteryServiceGattServiceInterface, clxGetBatteryServiceGattServiceCharacteristicName}
                                                , {0, CLX_GATT_SERVICE_DEVICE_INFORMATION_NAME, clxGetDeviceInformationGattServiceInterface, clxGetDeviceInformationGattServiceCharacteristicName}
                                                , {0, CLX_GATT_SERVICE_ALERT_NOTIFICATION_SERVICE_NAME, clxGetAlertNotificationServiceGattServiceInterface, clxGetAlertNotificationServiceGattServiceCharacteristicName}
#if defined(CLX_BLE_CS_REFLECTOR)
                                                , {0, CLX_GATT_SERVICE_RANGING_SERVICE_NAME, clxGetRangingServiceGattServiceInterface, clxGetRangingServiceGattServiceCharacteristicName}
#endif
#if defined(CLX_BLE_HID)
                                                , {0, CLX_GATT_SERVICE_HUMAN_INTERFACE_DEVICE_NAME, clxGetHumanInterfaceDeviceGattServiceInterface, clxGetHumanInterfaceDeviceGattServiceCharacteristicName}
#endif /* defined(CLX_BLE_HID) */
#if defined(CLX_BLE_ISOCHRONOUS)
                                                , {0, CLX_GATT_SERVICE_AUDIO_STREAM_CONTROL_NAME, clxGetAudioStreamControlGattServiceInterface, clxGetAudioStreamControlGattServiceCharacteristicName}
                                                , {0, CLX_GATT_SERVICE_PUBLISHED_AUDIO_CAPABILITIES_NAME, clxGetPublishedAudioCapabilitiesGattServiceInterface, clxGetPublishedAudioCapabilitiesGattServiceCharacteristicName}
                                                , {0, CLX_GATT_SERVICE_VOLUME_CONTROL_SERVICE_NAME, clxGetVolumeControlServiceGattServiceInterface, clxGetVolumeControlServiceGattServiceCharacteristicName}
                                                , {0, CLX_GATT_SERVICE_BROADCAST_AUDIO_SCAN_NAME, clxGetBroadcastAudioScanGattServiceInterface, clxGetBroadcastAudioScanGattServiceCharacteristicName}
                                                , {0, CLX_GATT_TELEPHONY_MEDIA_AUDIO_SERVICE_NAME, clxGetTelephonyMediaAccessServiceInterface, clxGetTelephonyMediaAudioServiceGattCharacteristicName}
#endif /* #if defined(CLX_BLE_ISOCHRONOUS) */
                                            };

#ifdef __cplusplus
}
#endif

