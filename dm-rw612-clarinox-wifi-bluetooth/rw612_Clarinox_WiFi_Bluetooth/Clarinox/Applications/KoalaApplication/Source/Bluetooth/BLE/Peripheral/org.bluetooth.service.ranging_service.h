#ifndef __org_bluetooth_service_ranging_service_h__
#define __org_bluetooth_service_ranging_service_h__

/***********************************************************************************
*
* Project             Custom Channel Sounding Reflector
* File                org.bluetooth.service.ranging_service.h
* Description         Declares definitions for the Ranging Service (RAS)
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by
* Clarinox Technologies Pty. Ltd.
*
***********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#define CLX_GATT_SERVICE_RANGING_SERVICE_NAME                     "Ranging Service"
#define CLX_GATT_SERVICE_RANGING_SERVICE_UUID                     0x185B

/* ---- RAS Features ---- */

#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES                                    "RAS Features"
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_HANDLE_INDEX                       2
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_PERMISSIONS                        (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE)
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_STRUCT                             struct ClxOrgBluetoothCharacteristicRasFeaturesFields
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_VALUE_TYPE                         ClxOrgBluetoothCharacteristicRasFeaturesFields_Type
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_DATA_SIZE                          ClxOrgBluetoothCharacteristicRasFeaturesFields_Size
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_FEATURES_UUID                               0x2C14


struct ClxOrgBluetoothCharacteristicRasFeaturesFields
{
    u4 featureBits;
};

typedef enum ClxBleRasFeaturesEnum
{
    ClxBleRasFeatures_RealTimeRangingData,
    ClxBleRasFeatures_RetrieveLostRangingDataSegments,
    ClxBleRasFeatures_AbortOperation,
    ClxBleRasFeatures_FilterRangingData
    /* Reserved: 4 - 31 */
} ClxBleRasFeatures;

#define ClxOrgBluetoothCharacteristicRasFeaturesFields_Type ClxBleAttributeValueType_FixedLength
#define ClxOrgBluetoothCharacteristicRasFeaturesFields_Size       (4)

/* ---- Real-time Data ---- */

#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA                                 "Real-time Ranging Data"
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_HANDLE_INDEX                    4
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_PERMISSIONS                     (CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_STRUCT                          struct ClxOrgBluetoothCharacteristicRasRealtimeDataFields
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_VALUE_TYPE                      ClxOrgBluetoothCharacteristicRasRealtimeDataFields_Type
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_SIZE                            ClxOrgBluetoothCharacteristicRasRealtimeDataFields_Size
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_REALTIME_DATA_UUID                            0x2C15

struct ClxOrgBluetoothCharacteristicRasRealtimeDataFields
{
    u1 data[498];
};

#define ClxOrgBluetoothCharacteristicRasRealtimeDataFields_Type    ClxBleAttributeValueType_VariableLength
#define ClxOrgBluetoothCharacteristicRasRealtimeDataFields_Size    512

/* ---- On-demand Data ---- */

#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA                                "On-demand Ranging Data"
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_HANDLE_INDEX                   7
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_PERMISSIONS                    (CLX_GATT_ATTRIBUTE_PERMISSION_INDICATABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE)
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_STRUCT                         struct ClxOrgBluetoothCharacteristicRasOnDemandDataFields
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_VALUE_TYPE                     ClxOrgBluetoothCharacteristicRasOnDemandDataFields_Type
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_SIZE                           ClxOrgBluetoothCharacteristicRasOnDemandDataFields_Size
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_ONDEMAND_DATA_UUID                           0x2C16

struct ClxOrgBluetoothCharacteristicRasOnDemandDataFields
{
    u1 segmentation;
    u1 data[32];
};

#define ClxOrgBluetoothCharacteristicRasOnDemandDataFields_Type  ClxBleAttributeValueType_VariableLength
#define ClxOrgBluetoothCharacteristicRasOnDemandDataFields_Size     (1 + 32)

/* ---- Control Point ---- */

#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT                               "RAS Control Point"
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_HANDLE_INDEX                  10
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_PERMISSIONS                   (CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_INDICATABLE)
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_STRUCT                        struct ClxOrgBluetoothCharacteristicRasControlPointFields
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_VALUE_TYPE                    ClxOrgBluetoothCharacteristicRasControlPointFields_Type
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_SIZE                          ClxOrgBluetoothCharacteristicRasControlPointFields_Size
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_CONTROL_POINT_UUID                          0x2C17

struct ClxOrgBluetoothCharacteristicRasControlPointFields
{
    u1 opcode;
    u1 parameters[32];
};

#define ClxOrgBluetoothCharacteristicRasControlPointFields_Type ClxBleAttributeValueType_VariableLength
#define ClxOrgBluetoothCharacteristicRasControlPointFields_Size    (1 + 32)

/* ---- Data Ready ---- */

#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY                                  "Ranging Data Ready"
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_HANDLE_INDEX                     13
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_PERMISSIONS                      (CLX_GATT_ATTRIBUTE_PERMISSION_INDICATABLE)
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_STRUCT                           struct ClxOrgBluetoothCharacteristicRasDataReadyFields
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_VALUE_TYPE                       ClxOrgBluetoothCharacteristicRasDataReadyFields_Type
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_SIZE                             ClxOrgBluetoothCharacteristicRasDataReadyFields_Size
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_READY_UUID                             0x2C18

struct ClxOrgBluetoothCharacteristicRasDataReadyFields
{
    u2 ready;
};

#define ClxOrgBluetoothCharacteristicRasDataReadyFields_Type ClxBleAttributeValueType_FixedLength
#define ClxOrgBluetoothCharacteristicRasDataReadyFields_Size       (2)

/* ---- Data Overwritten ---- */

#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN                            "Ranging Data Overwritten"
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_HANDLE_INDEX               16
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_PERMISSIONS                (CLX_GATT_ATTRIBUTE_PERMISSION_INDICATABLE)
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_STRUCT                     struct ClxOrgBluetoothCharacteristicRasDataOverwrittenFields
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_VALUE_TYPE                 ClxOrgBluetoothCharacteristicRasDataOverwrittenFields_Type
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_SIZE                       ClxOrgBluetoothCharacteristicRasDataOverwrittenFields_Size
#define CLX_GATT_SERVICE_RAS_CHARACTERISTIC_DATA_OVERWRITTEN_UUID                       0x2C19

struct ClxOrgBluetoothCharacteristicRasDataOverwrittenFields
{
    u2 overwritten;
};

#define ClxOrgBluetoothCharacteristicRasDataOverwrittenFields_Type ClxBleAttributeValueType_FixedLength
#define ClxOrgBluetoothCharacteristicRasDataOverwrittenFields_Size (2)

extern const ClxBleGattServiceInterface* clxGetRangingServiceGattServiceInterface();
#ifdef __cplusplus
}
#endif

#endif /* __org_bluetooth_service_ranging_service_h__ */
