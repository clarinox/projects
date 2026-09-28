/********************************************************************************
*
* Project             Clarinox Reference Application
* File                ServiceVerbose.cpp
* Description         This file provides the list of standard services,
*                     characteristics and descriptors details for GATT client
*                     operations.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#include "ClxCommon.h"
#include "ClarinoxBlue.h"
#include "ClxTime.h"

#include "Gap.Api.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gap.Ble.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Server.Api.h"
#include "Gatt.Ble.Client.Api.h"

#include "GattApp.h"
#include "ServiceVerbose.h"

#include "string.h"
#include "stdio.h"
#include <assert.h>

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)

typedef struct StandardNameInfoStruct
{
    const s1*   name;
    u2          uuid;
} StandardNameInfo;

/* Standard Service list defined by SIG */
StandardNameInfo sigServiceInfoDetails[SERVICE_LIST_SIZE]    =  {
                                                                    {GENERIC_ACCESS_SERVICE_NAME, GENERIC_ACCESS_SERVICE_UUID},
                                                                    {ALERT_NOTIFICATION_SERVICE_NAME, ALERT_NOTIFICATION_SERVICE_UUID},
                                                                    {AUTOMATION_IO_SEVICE_NAME, AUTOMATION_IO_SEVICE_UUID},
                                                                    {BATTERY_SERVICE_NAME, BATTERY_SERVICE_UUID},
                                                                    {BODY_COMPOSITION_SERVICE, BODY_COMPOSITION_SERVICE_UUID},
                                                                    {BOND_MANAGEMENT_SERVICE_NAME, BOND_MANAGEMENT_SERVICE_UUID},
                                                                    {CONTINUOUS_GLUCOSE_MONITORING_SERVICE_NAME, CONTINUOUS_GLUCOSE_MONITORING_SERVICE_UUID},
                                                                    {CURRENT_TIME_SERVICE_NAME, CURRENT_TIME_SERVICE_UUID},
                                                                    {CYCLING_POWER_SERVICE_NAME, CYCLING_POWER_SERVICE_UUID},
                                                                    {CYCLING_SPEED_AND_CADENCE_SERVICE_NAME, CYCLING_SPEED_AND_CADENCE_SERVICE_UUID},
                                                                    {DEVICE_INFORMATION_SERVICE_NAME, DEVICE_INFORMATION_SERVICE_UUID},
                                                                    {ENVIRONMENTAL_SENSING_SERVICE_NAME, ENVIRONMENTAL_SENSING_SERVICE_UUID},
                                                                    {FITNESS_MACHINE_SERVICE_NAME, FITNESS_MACHINE_SERVICE_UUID},
                                                                    {GENERIC_ATTRIBUTE_SERVICE_NAME, GENERIC_ATTRIBUTE_SERVICE_UUID},
                                                                    {GLUCOSE_SERVICE_NAME, GLUCOSE_SERVICE_UUID},
                                                                    {HEALTH_THERMOMETER_SERVICE_NAME, HEALTH_THERMOMETER_SERVICE_UUID},
                                                                    {HEART_RATE_SERVICE_NAME, HEART_RATE_SERVICE_UUID},
                                                                    {HTTP_PROXY_SERVICE_NAME, HTTP_PROXY_SERVICE_UUID},
                                                                    {HUMAN_INTERFACE_DEVICE_SERVICE_NAME, HUMAN_INTERFACE_DEVICE_SERVICE_UUID},
                                                                    {IMMEDIATE_ALERT_SERVICE_NAME, IMMEDIATE_ALERT_SERVICE_UUID},
                                                                    {INDOOR_POSITIONING_SERVICE_NAME, INDOOR_POSITIONING_SERVICE_UUID},
                                                                    {INTERNET_PROTOCOL_SUPPORT_SERVICE_NAME, INTERNET_PROTOCOL_SUPPORT_SERVICE_UUID},
                                                                    {LINK_LOSS_SERVICE_NAME, LINK_LOSS_SERVICE_UUID},
                                                                    {LOCATION_AND_NAVIGATION_SERVICE_NAME, LOCATION_AND_NAVIGATION_SERVICE_UUID},
                                                                    {MESH_PROVISIONING_SERVICE_NAME, MESH_PROVISIONING_SERVICE_UUID},
                                                                    {MESH_PROXY_SERVICE_NAME, MESH_PROXY_SERVICE_UUID},
                                                                    {NEXT_DST_CHANGE_SERVICE_NAME, NEXT_DST_CHANGE_SERVICE_UUID},
                                                                    {OBJECT_TRANSFER_SERVICE_NAME, OBJECT_TRANSFER_SERVICE_UUID},
                                                                    {PHONE_ALERT_STATUS_SERVICE_NAME, PHONE_ALERT_STATUS_SERVICE_UUID},
                                                                    {PULSE_OXIMETER_SERVICE_NAME, PULSE_OXIMETER_SERVICE_UUID},
                                                                    {RECONNECTION_CONFIGURATION_SERVICE_NAME, RECONNECTION_CONFIGURATION_SERVICE_UUID},
                                                                    {REFERENCE_TIME_UPDATE_SERVICE_NAME, REFERENCE_TIME_UPDATE_SERVICE_UUID},
                                                                    {RUNNING_SPEED_AND_CADENCE_SERVICE_NAME, RUNNING_SPEED_AND_CADENCE_SERVICE_UUID},
                                                                    {SCAN_PARAMETERS_SERVICE_NAME, SCAN_PARAMETERS_SERVICE_UUID},
                                                                    {TRANSPORT_DISCOVERY_SERVICE_NAME, TRANSPORT_DISCOVERY_SERVICE_UUID},
                                                                    {TX_POWER_SERVICE_NAME, TX_POWER_SERVICE_UUID},
                                                                    {USER_DATA_SERVICE_NAME, USER_DATA_SERVICE_UUID},
                                                                    {WIGHT_SCALE_SERVICE_NAME, WIGHT_SCALE_SERVICE_UUID},
                                                                    {BROADCAST_AUDIO_SCAN_SERVICE_NAME, BROADCAST_AUDIO_SCAN_SERVICE_UUID},
                                                                    {AUDIO_STRAM_CONTROL_SERVICE_NAME, AUDIO_STRAM_CONTROL_SERVICE_UUID},
                                                                    {PUBLISHED_AUDIO_CAPABILITIES_SERVICE_NAME, PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID},
                                                                    {VOLUME_CONTROL_SERVICE_NAME, VOLUME_CONTROL_SERVICE_UUID},
                                                                    {COORDINATED_SET_IDENTIFICATION_SERVICE_NAME, COORDINATED_SET_IDENTIFICATION_SERVICE_UUID},
                                                                    {COMMON_AUDIO_SERVICE_NAME, COMMON_AUDIO_SERVICE_UUID}
                                                                };

/* Standard Descriptor list defined by SIG */
StandardNameInfo sigDescriptorInfoDetails[DESCRIPTOR_LIST_SIZE] =   {
                                                                        {EXTENDED_PROPERTIES_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_EXTENDED_PROPERTIES_DESCRIPTOR_UUID},
                                                                        {USER_DESCRIPTION_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_USER_DESCRIPTION_UUID},
                                                                        {CLIENT_CONFIG_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_CLIENT_CONFIG_DESCRIPTOR_UUID},
                                                                        {SERVER_CONFIG_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_SERVER_CONFIG_DESCRIPTOR_UUID},
                                                                        {PRESENTATION_FORMAT_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_PRESENTATION_FORMAT_DESCRIPTOR_UUID},
                                                                        {AGGREGATE_FORMAT_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_AGGREGATE_FORMAT_UUID},
                                                                        {VALID_RANGE_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_VALID_RANGE_DESCRIPTOR_UUID},
                                                                        {ER_REFERENCE_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_ER_REFERENCE_DESCRIPTOR_UUID},
                                                                        {REPORT_REFERENCE_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_REPORT_REFERENCE_DESCRIPTOR_UUID},
                                                                        {NUMBER_OF_DIGITALS_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_NUMBER_OF_DIGITALS_DESCRIPTOR_UUID},
                                                                        {VALUE_TRIGGER_SETTING_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_VALUE_TRIGGER_SETTING_DESCRIPTOR_UUID},
                                                                        {ES_CONFIGURATION_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_ES_CONFIGURATION_DESCRIPTOR_UUID},
                                                                        {ES_MEASUREMENT_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_ES_MEASUREMENT_DESCRIPTOR_UUID},
                                                                        {ES_TRIGGER_SETTING_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_ES_TRIGGER_SETTING_DESCRIPTOR_UUID},
                                                                        {TIME_TRIGGER_SETTING_DESCRIPTOR_NAME, CLX_GATT_CHARACTERISTIC_TIME_TRIGGER_SETTING_DESCRIPTOR_UUID}
                                                                    };

/* Generic Access Service Characteristics */
StandardNameInfo gasCharacteristics[GAS_CHARACTERISTIC_COUNT] = {
                                                                    {GAS_CHARACTERISTIC_DEVICE_NAME, GAS_CHARACTERISTIC_DEVICE_NAME_UUID},
                                                                    {GAS_CHARACTERISTIC_APPEARANCE, GAS_CHARACTERISTIC_APPEARANCE_UUID},
                                                                    {GAS_CHARACTERISTIC_PRIVACY_FLAG, GAS_CHARACTERISTIC_PRIVACY_FLAG_UUID},
                                                                    {GAS_CHARACTERISTIC_RECONNECTION_ADDRESS, GAS_CHARACTERISTIC_RECONNECTION_ADDRESS_UUID},
                                                                    {GAS_CHARACTERISTIC_CONNECTION_PARAMETERS, GAS_CHARACTERISTIC_CONNECTION_PARAMETERS_UUID}
                                                                };

/* Alert Notification Service Characteristics */
StandardNameInfo ansCharacteristics[ANS_CHARACTERISTIC_COUNT] = {
                                                                    {ANS_CHARACTERISTIC_NEW_ALERT_CATEGORY, ANS_CHARACTERISTIC_NEW_ALERT_CATEGORY_UUID},
                                                                    {ANS_CHARACTERISTIC_NEW_ALERT, ANS_CHARACTERISTIC_NEW_ALERT_UUID},
                                                                    {ANS_CHARACTERISTIC_UNREAD_ALERT_CATEGORY, ANS_CHARACTERISTIC_UNREAD_ALERT_CATEGORY_UUID},
                                                                    {ANS_CHARACTERISTIC_UNREAD_ALERT_STATUS, ANS_CHARACTERISTIC_UNREAD_ALERT_STATUS_UUID},
                                                                    {ANS_CHARACTERISTIC_CONTROL_POINT, ANS_CHARACTERISTIC_CONTROL_POINT_UUID}
                                                                };

/* Automation IO Service Characteristics */
StandardNameInfo aiosCharacteristics[AIOS_CHARACTERISTIC_COUNT] =   {
                                                                        {AIOS_CHARACTERISTIC_DIGITAL, AIOS_CHARACTERISTIC_DIGITAL_UUID},
                                                                        {AIOS_CHARACTERISTIC_ANALOG, AIOS_CHARACTERISTIC_ANALOG_UUID},
                                                                        {AIOS_CHARACTERISTIC_AGGREGATE, AIOS_CHARACTERISTIC_AGGREGATE_UUID}
                                                                    };

/* Battery Service Characteristics */
StandardNameInfo basCharacteristics[BAS_CHARACTERISTIC_COUNT] = {
                                                                    {BAS_CHARACTERISTIC_BATTERY_LEVEL, BAS_CHARACTERISTIC_BATTERY_LEVEL_UUID}
                                                                };

/* Blood Pressure Service Characteristics */
StandardNameInfo bpsCharacteristics[BPS_CHARACTERISTIC_COUNT] = {
                                                                    {BPS_CHARACTERISTIC_MEASUREMENT, BPS_CHARACTERISTIC_MEASUREMENT_UUID},
                                                                    {BPS_CHARACTERISTIC_INTERMEDIATE_CUFF_PRESSURE, BPS_CHARACTERISTIC_INTERMEDIATE_CUFF_PRESSURE_UUID},
                                                                    {BPS_CHARACTERISTIC_FEATURE, BPS_CHARACTERISTIC_FEATURE_UUID}
                                                                };

/* Body Composition Service Characteristics */
StandardNameInfo bcsCharacteristics[BCS_CHARACTERISTIC_COUNT] = {
                                                                    {BCS_CHARACTERISTIC_FEATURE, BCS_CHARACTERISTIC_FEATURE_UUID},
                                                                    {BCS_CHARACTERISTIC_MEASUREMENT, BCS_CHARACTERISTIC_MEASUREMENT_UUID}
                                                                };

/* Bond Management Service Characteristics */
StandardNameInfo bmsCharacteristics[BMS_CHARACTERISTIC_COUNT] = {
                                                                    {BMS_CHARACTERISTIC_CONTROL_POINT, BMS_CHARACTERISTIC_CONTROL_POINT_UUID},
                                                                    {BMS_CHARACTERISTIC_FEATURE, BMS_CHARACTERISTIC_FEATURE_UUID}
                                                                };

/* Continuous Glucose Monitoring Service Characteristics */
StandardNameInfo cgmsCharacteristics[CGMS_CHARACTERISTIC_COUNT] =   {
                                                                        {CGMS_CHARACTERISTIC_MEASUREMENT, CGMS_CHARACTERISTIC_MEASUREMENT_UUID},
                                                                        {CGMS_CHARACTERISTIC_FEATURE, CGMS_CHARACTERISTIC_FEATURE_UUID},
                                                                        {CGMS_CHARACTERISTIC_STATUS, CGMS_CHARACTERISTIC_STATUS_UUID},
                                                                        {CGMS_CHARACTERISTIC_SESSION_START_TIME, CGMS_CHARACTERISTIC_SESSION_START_TIME_UUID},
                                                                        {CGMS_CHARACTERISTIC_SESSION_RUN_TIME, CGMS_CHARACTERISTIC_SESSION_RUN_TIME_UUID},
                                                                        {CGMS_CHARACTERISTIC_RECORD_ACCESS_CONTROL_POINT, CGMS_CHARACTERISTIC_RECORD_ACCESS_CONTROL_POINT_UUID},
                                                                        {CGMS_CHARACTERISTIC_SPECIFIC_OPS_CONTROL_POINT, CGMS_CHARACTERISTIC_SPECIFIC_OPS_CONTROL_POINT_UUID}
                                                                    };

/* Current Time Service Characteristics */
StandardNameInfo ctsCharacteristics[CTS_CHARACTERISTIC_COUNT] = {
                                                                    {CTS_CHARACTERISTIC_CURRENT_TIME, CTS_CHARACTERISTIC_CURRENT_TIME_UUID},
                                                                    {CTS_CHARACTERISTIC_LOCAL_TIME_INFORMATION, CTS_CHARACTERISTIC_LOCAL_TIME_INFORMATION_UUID},
                                                                    {CTS_CHARACTERISTIC_REFERENCE_TIME_INFORMATION, CTS_CHARACTERISTIC_REFERENCE_TIME_INFORMATION_UUID}
                                                                };

/* Cycling Power Service Characteristics */
StandardNameInfo cpsCharacteristics[CPS_CHARACTERISTIC_COUNT] = {
                                                                    {CPS_CHARACTERISTIC_MEASUREMENT, CPS_CHARACTERISTIC_MEASUREMENT_UUID},
                                                                    {CPS_CHARACTERISTIC_FEATURE, CPS_CHARACTERISTIC_FEATURE_UUID},
                                                                    {CPS_CHARACTERISTIC_SENSOR_LOCATION, CPS_CHARACTERISTIC_SENSOR_LOCATION_UUID},
                                                                    {CPS_CHARACTERISTIC_VECTOR, CPS_CHARACTERISTIC_VECTOR_UUID},
                                                                    {CPS_CHARACTERISTIC_CONTROL_POINT, CPS_CHARACTERISTIC_CONTROL_POINT_UUID}
                                                                };

/* Cycling Speed and Cadence Service Characteristics */
StandardNameInfo cscsCharacteristics[CSCS_CHARACTERISTIC_COUNT] =   {
                                                                        {CSCS_CHARACTERISTIC_MEASUREMENT, CSCS_CHARACTERISTIC_MEASUREMENT_UUID},
                                                                        {CSCS_CHARACTERISTIC_FEATURE, CSCS_CHARACTERISTIC_FEATURE_UUID},
                                                                        {CSCS_CHARACTERISTIC_SENSOR_LOCATION, CSCS_CHARACTERISTIC_SENSOR_LOCATION_UUID},
                                                                        {CSCS_CHARACTERISTIC_CONTROL_POINT, CSCS_CHARACTERISTIC_CONTROL_POINT_UUID}
                                                                    };

/* Device Information Service Characteristics */
StandardNameInfo disCharacteristics[DIS_CHARACTERISTIC_COUNT] = {
                                                                    {DIS_CHARACTERISTIC_MANUFACTURE_NAME, DIS_CHARACTERISTIC_MANUFACTURE_NAME_UUID},
                                                                    {DIS_CHARACTERISTIC_MODEL_NUMBER, DIS_CHARACTERISTIC_MODEL_NUMBER_UUID},
                                                                    {DIS_CHARACTERISTIC_SERIAL_NUMBER, DIS_CHARACTERISTIC_SERIAL_NUMBER_UUID},
                                                                    {DIS_CHARACTERISTIC_HW_REVISION, DIS_CHARACTERISTIC_HW_REVISION_UUID},
                                                                    {DIS_CHARACTERISTIC_SW_REVISION, DIS_CHARACTERISTIC_SW_REVISION_UUID},
                                                                    {DIS_CHARACTERISTIC_FIRMWARE_REVISION, DIS_CHARACTERISTIC_FIRMWARE_REVISION_UUID},
                                                                    {DIS_CHARACTERISTIC_SYSTEM_ID, DIS_CHARACTERISTIC_SYSTEM_ID_UUID},
                                                                    {DIS_CHARACTERISTIC_CERTIFY_DATA_LIST, DIS_CHARACTERISTIC_CERTIFY_DATA_LIST_UUID},
                                                                    {DIS_CHARACTERISTIC_PNP_ID, DIS_CHARACTERISTIC_PNP_ID_UUID}
                                                                };

/* Environmental Sensing Service Characteristics */
StandardNameInfo essCharacteristics[ESS_CHARACTERISTIC_COUNT] = {
                                                                    {ESS_CHARACTERISTIC_DESCRIPTOR_VALUE_CHANGED, ESS_CHARACTERISTIC_DESCRIPTOR_VALUE_CHANGED_UUID},
                                                                    {ESS_CHARACTERISTIC_APPARENT_WIND_DIRECTION, ESS_CHARACTERISTIC_APPARENT_WIND_DIRECTION_UUID},
                                                                    {ESS_CHARACTERISTIC_APPARENT_WIND_SPEED, ESS_CHARACTERISTIC_APPARENT_WIND_SPEED_UUID},
                                                                    {ESS_CHARACTERISTIC_DEW_POINT, ESS_CHARACTERISTIC_DEW_POINT_UUID},
                                                                    {ESS_CHARACTERISTIC_ELEVATION, ESS_CHARACTERISTIC_ELEVATION_UUID},
                                                                    {ESS_CHARACTERISTIC_GUST_FACTOR, ESS_CHARACTERISTIC_GUST_FACTOR_UUID},
                                                                    {ESS_CHARACTERISTIC_HEAT_INDEX, ESS_CHARACTERISTIC_HEAT_INDEX_UUID},
                                                                    {ESS_CHARACTERISTIC_HUMIDITY, ESS_CHARACTERISTIC_HUMIDITY_UUID},
                                                                    {ESS_CHARACTERISTIC_IRRADIANCE, ESS_CHARACTERISTIC_IRRADIANCE_UUID},
                                                                    {ESS_CHARACTERISTIC_POLLEN_CONCENTRATION, ESS_CHARACTERISTIC_POLLEN_CONCENTRATION_UUID},
                                                                    {ESS_CHARACTERISTIC_RAINFALL, ESS_CHARACTERISTIC_RAINFALL_UUID},
                                                                    {ESS_CHARACTERISTIC_PRESSURE, ESS_CHARACTERISTIC_PRESSURE_UUID},
                                                                    {ESS_CHARACTERISTIC_TEMPERATURE, ESS_CHARACTERISTIC_TEMPERATURE_UUID},
                                                                    {ESS_CHARACTERISTIC_TRUEWIND_DIRECTION, ESS_CHARACTERISTIC_TRUEWIND_DIRECTION_UUID},
                                                                    {ESS_CHARACTERISTIC_TRUEWIND_SPEED, ESS_CHARACTERISTIC_TRUEWIND_SPEED_UUID},
                                                                    {ESS_CHARACTERISTIC_UV_INDEX, ESS_CHARACTERISTIC_UV_INDEX_UUID},
                                                                    {ESS_CHARACTERISTIC_WIND_CHILL, ESS_CHARACTERISTIC_WIND_CHILL_UUID},
                                                                    {ESS_CHARACTERISTIC_BAROMETRIC_PRESSURE_TREND, ESS_CHARACTERISTIC_BAROMETRIC_PRESSURE_TREND_UUID},
                                                                    {ESS_CHARACTERISTIC_MAGNETIC_DECLINATION, ESS_CHARACTERISTIC_MAGNETIC_DECLINATION_UUID},
                                                                    {ESS_CHARACTERISTIC_MAGNETIC_FLEX_DENSITY_2D, ESS_CHARACTERISTIC_MAGNETIC_FLEX_DENSITY_2D_UUID},
                                                                    {ESS_CHARACTERISTIC_MAGNETIC_FLEX_DENSITY_3D, ESS_CHARACTERISTIC_MAGNETIC_FLEX_DENSITY_3D_UUID}
                                                                };

/* Fitness Machine Service Characteristics */
StandardNameInfo fmsCharacteristics[FMS_CHARACTERISTIC_COUNT] = {
                                                                    {FMS_CHARACTERISTIC_FEATURE, FMS_CHARACTERISTIC_FEATURE_UUID},
                                                                    {FMS_CHARACTERISTIC_TREADMILLDATA, FMS_CHARACTERISTIC_TREADMILLDATA_UUID},
                                                                    {FMS_CHARACTERISTIC_CROSS_TRAINER_DATA, FMS_CHARACTERISTIC_CROSS_TRAINER_DATA_UUID},
                                                                    {FMS_CHARACTERISTIC_STEP_CLIMBER_DATA, FMS_CHARACTERISTIC_STEP_CLIMBER_DATA_UUID},
                                                                    {FMS_CHARACTERISTIC_STAIR_CLIMBER_DATA, FMS_CHARACTERISTIC_STAIR_CLIMBER_DATA_UUID},
                                                                    {FMS_CHARACTERISTIC_ROWER_DATA, FMS_CHARACTERISTIC_ROWER_DATA_UUID},
                                                                    {FMS_CHARACTERISTIC_INDOOR_BIKE_DATA, FMS_CHARACTERISTIC_INDOOR_BIKE_DATA_UUID},
                                                                    {FMS_CHARACTERISTIC_TRAINING_STATUS, FMS_CHARACTERISTIC_TRAINING_STATUS_UUID},
                                                                    {FMS_CHARACTERISTIC_SPEED_RANGE, FMS_CHARACTERISTIC_SPEED_RANGE_UUID},
                                                                    {FMS_CHARACTERISTIC_INCLINATION_RANGE, FMS_CHARACTERISTIC_INCLINATION_RANGE_UUID},
                                                                    {FMS_CHARACTERISTIC_RESISTANCE_LEVEL_CHANGE, FMS_CHARACTERISTIC_RESISTANCE_LEVEL_CHANGE_UUID},
                                                                    {FMS_CHARACTERISTIC_POWER_CHANGE, FMS_CHARACTERISTIC_POWER_CHANGE_UUID},
                                                                    {FMS_CHARACTERISTIC_HEART_RATE_RANGE, FMS_CHARACTERISTIC_HEART_RATE_RANGE_UUID},
                                                                    {FMS_CHARACTERISTIC_CONTROL_POINT, FMS_CHARACTERISTIC_CONTROL_POINT_UUID},
                                                                    {FMS_CHARACTERISTIC_STATUS, FMS_CHARACTERISTIC_STATUS_UUID}
                                                                };

/* Generic Attribute Service Characteristics */
StandardNameInfo gatsCharacteristics[GATS_CHARACTERISTIC_COUNT] =   {
                                                                        {GATS_CHARACTERISTIC_SERVICE_CHANGED, GATS_CHARACTERISTIC_SERVICE_CHANGED_UUID}
                                                                    };

/* Glucose Service Characteristics */
StandardNameInfo glsCharacteristics[GLS_CHARACTERISTIC_COUNT] = {
                                                                    {GLS_CHARACTERISTIC_MEASUREMENT, GLS_CHARACTERISTIC_MEASUREMENT_UUID},
                                                                    {GLS_CHARACTERISTIC_MEASUREMENT_CONTEXT, GLS_CHARACTERISTIC_MEASUREMENT_CONTEXT_UUID},
                                                                    {GLS_CHARACTERISTIC_FEATURE, GLS_CHARACTERISTIC_FEATURE_UUID},
                                                                    {GLS_CHARACTERISTIC_RECORD_ACCESS_CONTROLPOINT, GLS_CHARACTERISTIC_RECORD_ACCESS_CONTROLPOINT_UUID}
                                                                };

/* Health Thermometer Service Characteristics */
StandardNameInfo htsCharacteristics[HTS_CHARACTERISTIC_COUNT] = {
                                                                    {HTS_CHARACTERISTIC_MEASUREMENT, HTS_CHARACTERISTIC_MEASUREMENT_UUID},
                                                                    {HTS_CHARACTERISTIC_TEMPERATURE_TYPE, HTS_CHARACTERISTIC_TEMPERATURE_TYPE_UUID},
                                                                    {HTS_CHARACTERISTIC_IMMEDIATE_TEMPERATURE, HTS_CHARACTERISTIC_IMMEDIATE_TEMPERATURE_UUID},
                                                                    {HTS_CHARACTERISTIC_MEASUREMENT_TYPE, HTS_CHARACTERISTIC_MEASUREMENT_TYPE_UUID}
                                                                };

/* Heart Rate Service Characteristics */
StandardNameInfo hrsCharacteristics[HRS_CHARACTERISTIC_COUNT] = {
                                                                    {HRS_CHARACTERISTIC_MEASUREMENT, HRS_CHARACTERISTIC_MEASUREMENT_UUID},
                                                                    {HRS_CHARACTERISTIC_BODY_SENSOR_LOCATION, HRS_CHARACTERISTIC_BODY_SENSOR_LOCATION_UUID},
                                                                    {HRS_CHARACTERISTIC_CONTROLPOINT, HRS_CHARACTERISTIC_CONTROLPOINT_UUID}
                                                                };

/* HTTP Proxy Service Characteristics */
StandardNameInfo hpsCharacteristics[HPS_CHARACTERISTIC_COUNT] = {
                                                                    {HPS_CHARACTERISTIC_URI, HPS_CHARACTERISTIC_URI_UUID},
                                                                    {HPS_CHARACTERISTIC_HEADERS, HPS_CHARACTERISTIC_HEADERS_UUID},
                                                                    {HPS_CHARACTERISTIC_ENTITY_BODY, HPS_CHARACTERISTIC_ENTITY_BODY_UUID},
                                                                    {HPS_CHARACTERISTIC_CONTROL_POINT, HPS_CHARACTERISTIC_CONTROL_POINT_UUID},
                                                                    {HPS_CHARACTERISTIC_STATUS_CODE, HPS_CHARACTERISTIC_STATUS_CODE_UUID},
                                                                    {HPS_CHARACTERISTIC_SECURITY, HPS_CHARACTERISTIC_SECURITY_UUID}
                                                                };

/* Human Interface Device Service Characteristics */
StandardNameInfo hidsCharacteristics[HIDS_CHARACTERISTIC_COUNT] =   {
                                                                        {HIDS_CHARACTERISTIC_PROTOCOL_MODE, HIDS_CHARACTERISTIC_PROTOCOL_MODE_UUID},
                                                                        {HIDS_CHARACTERISTIC_REPORT, HIDS_CHARACTERISTIC_REPORT_UUID},
                                                                        {HIDS_CHARACTERISTIC_REPORTMAP, HIDS_CHARACTERISTIC_REPORTMAP_UUID},
                                                                        {HIDS_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT, HIDS_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_UUID},
                                                                        {HIDS_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT, HIDS_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_UUID},
                                                                        {HIDS_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT, HIDS_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT_UUID},
                                                                        {HIDS_CHARACTERISTIC_BOOT_HID_INFORMATION, HIDS_CHARACTERISTIC_BOOT_HID_INFORMATION_UUID},
                                                                        {HIDS_CHARACTERISTIC_BOOT_CONTROL_POINT, HIDS_CHARACTERISTIC_BOOT_CONTROL_POINT_UUID}
                                                                    };

/* Immediate Alert Service Characteristics */
StandardNameInfo iasCharacteristics[IAS_CHARACTERISTIC_COUNT] = {
                                                                    {IAS_CHARACTERISTIC_ALERT_LEVEL, IAS_CHARACTERISTIC_ALERT_LEVEL_UUID}
                                                                };

/* Indoor Positioning Service Characteristics */
StandardNameInfo ipsCharacteristics[IPS_CHARACTERISTIC_COUNT] = {
                                                                    {IPS_CHARACTERISTIC_CONFIGURATION, IPS_CHARACTERISTIC_CONFIGURATION_UUID},
                                                                    {IPS_CHARACTERISTIC_LATITUDE, IPS_CHARACTERISTIC_LATITUDE_UUID},
                                                                    {IPS_CHARACTERISTIC_LONGITUDE, IPS_CHARACTERISTIC_LONGITUDE_UUID},
                                                                    {IPS_CHARACTERISTIC_LOCAL_NORTH_COORDINATE, IPS_CHARACTERISTIC_LOCAL_NORTH_COORDINATE_UUID},
                                                                    {IPS_CHARACTERISTIC_LOCAL_EAST_COORDINATE, IPS_CHARACTERISTIC_LOCAL_EAST_COORDINATE_UUID},
                                                                    {IPS_CHARACTERISTIC_FLOOR_NUMBER, IPS_CHARACTERISTIC_FLOOR_NUMBER_UUID},
                                                                    {IPS_CHARACTERISTIC_ALTITUDE, IPS_CHARACTERISTIC_ALTITUDE_UUID},
                                                                    {IPS_CHARACTERISTIC_UNCERTAINTY, IPS_CHARACTERISTIC_UNCERTAINTY_UUID},
                                                                    {IPS_CHARACTERISTIC_LOCATION_NAME, IPS_CHARACTERISTIC_LOCATION_NAME_UUID}
                                                                };

/* Link Loss Service Characteristics */
StandardNameInfo llsCharacteristics[LLS_CHARACTERISTIC_COUNT] = {
                                                                    {LLS_CHARACTERISTIC_ALERT_LEVEL, LLS_CHARACTERISTIC_ALERT_LEVEL_UUID}
                                                                };

/* Location and Navigation Service Characteristics */
StandardNameInfo lasCharacteristics[LAS_CHARACTERISTIC_COUNT] = {
                                                                    {LAS_CHARACTERISTIC_LN_FEATURE, LAS_CHARACTERISTIC_LN_FEATURE_UUID},
                                                                    {LAS_CHARACTERISTIC_LOCATION_AND_SPEED, LAS_CHARACTERISTIC_LOCATION_AND_SPEED_UUID},
                                                                    {LAS_CHARACTERISTIC_POSITION_QUALITY, LAS_CHARACTERISTIC_POSITION_QUALITY_UUID},
                                                                    {LAS_CHARACTERISTIC_CONTROL_POINT, LAS_CHARACTERISTIC_CONTROL_POINT_UUID},
                                                                    {LAS_CHARACTERISTIC_NAVIGATION, LAS_CHARACTERISTIC_NAVIGATION_UUID}
                                                                };

/* Mesh Provisioning Service Characteristics */
StandardNameInfo mpsCharacteristics[MPS_CHARACTERISTIC_COUNT] = {
                                                                    {MPS_CHARACTERISTIC_DATA_IN, MPS_CHARACTERISTIC_DATA_IN_UUID},
                                                                    {MPS_CHARACTERISTIC_DATA_OUT, MPS_CHARACTERISTIC_DATA_OUT_UUID}
                                                                };

/* Mesh Proxy Service Characteristics */
StandardNameInfo mpxyCharacteristics[MESH_PROXY_CHARACTERISTIC_COUNT] = {
                                                                            {MESH_PROXY_CHARACTERISTIC_DATA_IN, MESH_PROXY_CHARACTERISTIC_DATA_IN_UUID},
                                                                            {MESH_PROXY_CHARACTERISTIC_DATA_OUT, MESH_PROXY_CHARACTERISTIC_DATA_OUT_UUID}
                                                                        };

/* Next DST Change Service Characteristics */
StandardNameInfo ndcsCharacteristics[NDCS_CHARACTERISTIC_COUNT] =   {
                                                                        {NDCS_CHARACTERISTIC_TIME_WITH_DST, NDCS_CHARACTERISTIC_TIME_WITH_DST_UUID}
                                                                    };

/* Object Transfer Service Characteristics */
StandardNameInfo otsCharacteristics[OTS_CHARACTERISTIC_COUNT] = {
                                                                    {OTS_CHARACTERISTIC_FEATURE, OTS_CHARACTERISTIC_FEATURE_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_NAME, OTS_CHARACTERISTIC_OBJECT_NAME_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_TYPE, OTS_CHARACTERISTIC_OBJECT_TYPE_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_SIZE, OTS_CHARACTERISTIC_OBJECT_SIZE_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_FIRST_CREATED, OTS_CHARACTERISTIC_OBJECT_FIRST_CREATED_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_LAST_MODIFIED, OTS_CHARACTERISTIC_OBJECT_LAST_MODIFIED_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_ID, OTS_CHARACTERISTIC_OBJECT_ID_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_PROPERTIES, OTS_CHARACTERISTIC_OBJECT_PROPERTIES_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_ACTION_CONTROL_POINT, OTS_CHARACTERISTIC_OBJECT_ACTION_CONTROL_POINT_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_LIST_CONTROL_POINT, OTS_CHARACTERISTIC_OBJECT_LIST_CONTROL_POINT_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_LIST_FILTER, OTS_CHARACTERISTIC_OBJECT_LIST_FILTER_UUID},
                                                                    {OTS_CHARACTERISTIC_OBJECT_CHANGED, OTS_CHARACTERISTIC_OBJECT_CHANGED_UUID}
                                                                };

/* Phone Alert Status Service Characteristics */
StandardNameInfo passCharacteristics[PASS_CHARACTERISTIC_COUNT] =   {
                                                                        {PASS_CHARACTERISTIC_ALERT_STATUS, PASS_CHARACTERISTIC_ALERT_STATUS_UUID},
                                                                        {PASS_CHARACTERISTIC_RINGER_SETTING, PASS_CHARACTERISTIC_RINGER_SETTING_UUID},
                                                                        {PASS_CHARACTERISTIC_RINGER_CONTROL_POINT, PASS_CHARACTERISTIC_RINGER_CONTROL_POINT_UUID}
                                                                    };

/* Pulse Oximeter Service Characteristics */
StandardNameInfo plxCharacteristics[PLX_CHARACTERISTIC_COUNT] = {
                                                                    {PLX_CHARACTERISTIC_SPOT_CHECK_MEASUREMENT, PLX_CHARACTERISTIC_SPOT_CHECK_MEASUREMENT_UUID},
                                                                    {PLX_CHARACTERISTIC_CONTINUOUS_MEASUREMENT, PLX_CHARACTERISTIC_CONTINUOUS_MEASUREMENT_UUID},
                                                                    {PLX_CHARACTERISTIC_FEATURE, PLX_CHARACTERISTIC_FEATURE_UUID},
                                                                    {PLX_CHARACTERISTIC_RECORD_ACCESS_CONTROL_POINT, PLX_CHARACTERISTIC_RECORD_ACCESS_CONTROL_POINT_UUID}
                                                                };

/* Reconnection Configuration Service Characteristics */
StandardNameInfo rcsCharacteristics[RCS_CHARACTERISTIC_COUNT] = {
                                                                    {RCS_CHARACTERISTIC_FEATURES, RCS_CHARACTERISTIC_FEATURES_UUID},
                                                                    {RCS_CHARACTERISTIC_SETTINGS, RCS_CHARACTERISTIC_SETTINGS_UUID},
                                                                    {RCS_CHARACTERISTIC_CONTROL_POINT, RCS_CHARACTERISTIC_CONTROL_POINT_UUID}
                                                                };

/* Reference Time Update Service Characteristics */
StandardNameInfo rtusCharacteristics[RTUS_CHARACTERISTIC_COUNT] =   {
                                                                        {RTUS_CHARACTERISTIC_CONTROL_POINT, RTUS_CHARACTERISTIC_CONTROL_POINT_UUID},
                                                                        {RTUS_CHARACTERISTIC_STATE, RTUS_CHARACTERISTIC_STATE_UUID}
                                                                    };

/* Running Speed and Cadence Service Characteristics */
StandardNameInfo rscsCharacteristics[RSCS_CHARACTERISTIC_COUNT] =   {
                                                                        {RSCS_CHARACTERISTIC_MEASUREMENT, RSCS_CHARACTERISTIC_MEASUREMENT_UUID},
                                                                        {RSCS_CHARACTERISTIC_FEATURE, RSCS_CHARACTERISTIC_FEATURE_UUID},
                                                                        {RSCS_CHARACTERISTIC_SENSOR_LOCATION, RSCS_CHARACTERISTIC_SENSOR_LOCATION_UUID},
                                                                        {RSCS_CHARACTERISTIC_CONTROL_POINT, RSCS_CHARACTERISTIC_CONTROL_POINT_UUID}
                                                                    };

/* Scan Parameters Service Characteristics */
StandardNameInfo spsCharacteristics[SPS_CHARACTERISTIC_COUNT] = {
                                                                    {SPS_CHARACTERISTIC_SCAN_INTERVAL_WINDOW, SPS_CHARACTERISTIC_SCAN_INTERVAL_WINDOW_UUID},
                                                                    {SPS_CHARACTERISTIC_SCAN_REFRESH, SPS_CHARACTERISTIC_SCAN_REFRESH_UUID}
                                                                };

/* Transport Discovery Service Characteristics */
StandardNameInfo tdsCharacteristics[TDS_CHARACTERISTIC_COUNT] = {
                                                                    {TDS_CHARACTERISTIC_CONTROL_POINT, TDS_CHARACTERISTIC_CONTROL_POINT_UUID}
                                                                };

/* Tx Power Service Characteristics */
StandardNameInfo tpsCharacteristics[TPS_CHARACTERISTIC_COUNT] = {
                                                                    {TPS_CHARACTERISTIC_TX_POWER_LEVEL, TPS_CHARACTERISTIC_TX_POWER_LEVEL_UUID}
                                                                };

/* User Data Service Characteristics */
StandardNameInfo udsCharacteristics[UDS_CHARACTERISTIC_COUNT] = {
                                                                    {UDS_CHARACTERISTIC_FIRST_NAME, UDS_CHARACTERISTIC_FIRST_NAME_UUID},
                                                                    {UDS_CHARACTERISTIC_LAST_NAME, UDS_CHARACTERISTIC_LAST_NAME_UUID},
                                                                    {UDS_CHARACTERISTIC_EMAIL_ADDRESS, UDS_CHARACTERISTIC_EMAIL_ADDRESS_UUID},
                                                                    {UDS_CHARACTERISTIC_AGE, UDS_CHARACTERISTIC_AGE_UUID},
                                                                    {UDS_CHARACTERISTIC_DOB, UDS_CHARACTERISTIC_DOB_UUID},
                                                                    {UDS_CHARACTERISTIC_GENDER, UDS_CHARACTERISTIC_GENDER_UUID},
                                                                    {UDS_CHARACTERISTIC_WEIGHT, UDS_CHARACTERISTIC_WEIGHT_UUID},
                                                                    {UDS_CHARACTERISTIC_HEIGHT, UDS_CHARACTERISTIC_HEIGHT_UUID},
                                                                    {UDS_CHARACTERISTIC_V02MAX, UDS_CHARACTERISTIC_V02MAX_UUID},
                                                                    {UDS_CHARACTERISTIC_HEART_RATE_MAX, UDS_CHARACTERISTIC_HEART_RATE_MAX_UUID},
                                                                    {UDS_CHARACTERISTIC_RESETTING_HEART_RATE, UDS_CHARACTERISTIC_RESETTING_HEART_RATE_UUID},
                                                                    {UDS_CHARACTERISTIC_MAX_RECOMMENDED_HEART_RATE, UDS_CHARACTERISTIC_MAX_RECOMMENDED_HEART_RATE_UUID},
                                                                    {UDS_CHARACTERISTIC_AEROBIC_THRESHOLD, UDS_CHARACTERISTIC_AEROBIC_THRESHOLD_UUID},
                                                                    {UDS_CHARACTERISTIC_ANAEROBIC_THRESHOLD, UDS_CHARACTERISTIC_ANAEROBIC_THRESHOLD_UUID},
                                                                    {UDS_CHARACTERISTIC_SPORT_TYPE, UDS_CHARACTERISTIC_SPORT_TYPE_UUID},
                                                                    {UDS_CHARACTERISTIC_THRESHOLD_ASSESSMENT_DATE, UDS_CHARACTERISTIC_THRESHOLD_ASSESSMENT_DATE_UUID},
                                                                    {UDS_CHARACTERISTIC_WEIGHT_CIRCUMFERENCE, UDS_CHARACTERISTIC_WEIGHT_CIRCUMFERENCE_UUID},
                                                                    {UDS_CHARACTERISTIC_HIP_CIRCUMFERENCE, UDS_CHARACTERISTIC_HIP_CIRCUMFERENCE_UUID},
                                                                    {UDS_CHARACTERISTIC_FAT_BURN_HR_LOWER_LIMIT, UDS_CHARACTERISTIC_FAT_BURN_HR_LOWER_LIMIT_UUID},
                                                                    {UDS_CHARACTERISTIC_FAT_BURN_HR_UPPER_LIMIT, UDS_CHARACTERISTIC_FAT_BURN_HR_UPPER_LIMIT_UUID},
                                                                    {UDS_CHARACTERISTIC_AEROBIC_HR_LOWER_LIMIT, UDS_CHARACTERISTIC_AEROBIC_HR_LOWER_LIMIT_UUID},
                                                                    {UDS_CHARACTERISTIC_AEROBIC_HR_UPPER_LIMIT, UDS_CHARACTERISTIC_AEROBIC_HR_UPPER_LIMIT_UUID},
                                                                    {UDS_CHARACTERISTIC_ANAEROBIC_HR_LOWER_LIMIT, UDS_CHARACTERISTIC_ANAEROBIC_HR_LOWER_LIMIT_UUID},
                                                                    {UDS_CHARACTERISTIC_ANAEROBIC_HR_UPPER_LIMIT, UDS_CHARACTERISTIC_ANAEROBIC_HR_UPPER_LIMIT_UUID},
                                                                    {UDS_CHARACTERISTIC_FIVE_ZONE_HR_LIMITS, UDS_CHARACTERISTIC_FIVE_ZONE_HR_LIMITS_UUID},
                                                                    {UDS_CHARACTERISTIC_THREE_ZONE_HR_LIMITS, UDS_CHARACTERISTIC_THREE_ZONE_HR_LIMITS_UUID},
                                                                    {UDS_CHARACTERISTIC_TWO_ZONE_HR_LIMITS, UDS_CHARACTERISTIC_TWO_ZONE_HR_LIMITS_UUID},
                                                                    {UDS_CHARACTERISTIC_DATABASE_CHANGE_INCREMENT, UDS_CHARACTERISTIC_DATABASE_CHANGE_INCREMENT_UUID},
                                                                    {UDS_CHARACTERISTIC_USER_INDEX, UDS_CHARACTERISTIC_USER_INDEX_UUID},
                                                                    {UDS_CHARACTERISTIC_USER_CONTROL_POINT, UDS_CHARACTERISTIC_USER_CONTROL_POINT_UUID},
                                                                    {UDS_CHARACTERISTIC_LANGUAGE, UDS_CHARACTERISTIC_LANGUAGE_UUID}
                                                                };

/* Weight Scale Service Characteristics */
StandardNameInfo wssCharacteristics[WSS_CHARACTERISTIC_COUNT] = {
                                                                    {WSS_CHARACTERISTIC_FEATURE, WSS_CHARACTERISTIC_FEATURE_UUID},
                                                                    {WSS_CHARACTERISTIC_MEASUREMENT, WSS_CHARACTERISTIC_MEASUREMENT_UUID}
                                                                };

/* Broadcast Audio Scan Service Characteristics */
StandardNameInfo bassCharacteristics[BASS_CHARACTERISTIC_COUNT] = {
                                                                    {BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT, BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID},
                                                                    {BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE, BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_UUID}
                                                                  };

/* Audio Stream Control service Characteristics */
StandardNameInfo ascsCharacteristics[ASCS_CHARACTERISTIC_COUNT] = {
                                                                    {ASCS_CHARACTERISTIC_AUDIO_STRAM_CONTROL_POINT, ASCS_CHARACTERISTIC_AUDIO_STRAM_CONTROL_POINT_UUID},
                                                                    {ASCS_CHARACTERISTIC_SINK_AUDIO_STRAM_CONTROL, ASCS_CHARACTERISTIC_SINK_AUDIO_STRAM_CONTROL_UUID},
                                                                    {ASCS_CHARACTERISTIC_SOURCE_AUDIO_STRAM_CONTROL, ASCS_CHARACTERISTIC_SOURCE_AUDIO_STRAM_CONTROL_UUID}
                                                                  };

/* Published Audio Capabilities service Characteristics */
StandardNameInfo pacsCharacteristics[PACS_CHARACTERISTIC_COUNT] = {
                                                                    {PACS_CHARACTERISTIC_SINK_PUBLISHED_AUDIO_CAPABILITIES, PACS_CHARACTERISTIC_SINK_PUBLISHED_AUDIO_CAPABILITIES_UUID},
                                                                    {PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION, PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_UUID},
                                                                    {PACS_CHARACTERISTIC_SOURCE_PUBLISHED_AUDIO_CAPABILITIES, PACS_CHARACTERISTIC_SOURCE_PUBLISHED_AUDIO_CAPABILITIES_UUID},
                                                                    {PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION, PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_UUID},
                                                                    {PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS, PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_UUID},
                                                                    {PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS, PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_UUID}
                                                                  };

/* Volume Control service Characteristics */
StandardNameInfo vcsCharacteristics[VCS_CHARACTERISTIC_COUNT] = {
                                                                    {VCS_CHARACTERISTIC_VOLUME_STATE, VCS_CHARACTERISTIC_VOLUME_STATE_UUID},
                                                                    {VCS_CHARACTERISTIC_VOLUME__CONTROL_POINT, VCS_CHARACTERISTIC_VOLUME__CONTROL_POINT_UUID},
                                                                    {VCS_CHARACTERISTIC_VOLUME_FLAGS, VCS_CHARACTERISTIC_VOLUME_FLAGS_UUID}
                                                                };

/* Coordinated Set Identification service Characteristics */
StandardNameInfo csisCharacteristics[CSIS_CHARACTERISTIC_COUNT] = {
                                                                    {CSIS_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY, CSIS_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_UUID},
                                                                    {CSIS_CHARACTERISTIC_COORDINATED_SET_SIZE, CSIS_CHARACTERISTIC_COORDINATED_SET_SIZE_UUID},
                                                                    {CSIS_CHARACTERISTIC_SET_MEMBER_LOCK, CSIS_CHARACTERISTIC_SET_MEMBER_LOCK_UUID},
                                                                    {CSIS_CHARACTERISTIC_SET_MEMBER_RANK, CSIS_CHARACTERISTIC_SET_MEMBER_RANK_UUID}
                                                                 };

/*************************************************************************************************************************************
*                                                  getServiceName
*
* Searches for the services name string of UUID using the given service uuid and returns string name of UUID
*
* \param uuid  - Service UUID.
* 
* \return s1*  - Registered service name
*
**************************************************************************************************************************************/
const s1* getServiceName(u2 uuid)
{
    for (u4 i = 0; i < SERVICE_LIST_SIZE; i++)
    {
        if (uuid == sigServiceInfoDetails[i].uuid)
        {
            return sigServiceInfoDetails[i].name;
        }
    }

    return UNKNOWN_SERVICE_NAME;
}

/***************************************************************************************************************************************
*                                                   getDescriptorName
*
* Searches for the descriptor name using the given descriptor UUID and returns string name of descriptor
*
* \param uuid  - Descriptor UUID.
*
* \return s1*  - Registered descriptor name.
*
***************************************************************************************************************************************/
const s1* getDescriptorName(u2 uuid)
{
    for (u4 i = 0; i < DESCRIPTOR_LIST_SIZE; i++)
    {
        if (uuid == sigDescriptorInfoDetails[i].uuid)
        {
            return sigDescriptorInfoDetails[i].name;
        }
    }

    return UNKNOWN_DESCRIPTOR_NAME;
}

/***************************************************************************************************************************************
*                                                   getCharacteristicName
*
* Searches for the characteristics name using the given service and characteristics uuid and returns string name of characteristics 
*
* \param serviceUuid         - Service UUID.
* \param characteristicUuid  - Characteristic UUID.
*
* \return s1*                - Registered characteristic name.
*
****************************************************************************************************************************************/
const s1* getCharacteristicName(u2 serviceUuid, u2 characteristicUuid)
{
    StandardNameInfo* characteristicDetails = NULL;
    u2 characteristicCount = 0;

    switch (serviceUuid)
    {
        case GENERIC_ACCESS_SERVICE_UUID:
        {
            characteristicDetails = gasCharacteristics;
            characteristicCount = GAS_CHARACTERISTIC_COUNT;
            break;
        }

        case ALERT_NOTIFICATION_SERVICE_UUID:
        {
            characteristicDetails = ansCharacteristics;
            characteristicCount = ANS_CHARACTERISTIC_COUNT;
            break;
        }

        case AUTOMATION_IO_SEVICE_UUID:
        {
            characteristicDetails = aiosCharacteristics;
            characteristicCount = AIOS_CHARACTERISTIC_COUNT;
            break;
        }

        case BATTERY_SERVICE_UUID:
        {
            characteristicDetails = basCharacteristics;
            characteristicCount = BAS_CHARACTERISTIC_COUNT;
            break;
        }

        case BODY_COMPOSITION_SERVICE_UUID:
        {
            characteristicDetails = bcsCharacteristics;
            characteristicCount = BCS_CHARACTERISTIC_COUNT;
            break;
        }

        case BOND_MANAGEMENT_SERVICE_UUID:
        {
            characteristicDetails = bmsCharacteristics;
            characteristicCount = BMS_CHARACTERISTIC_COUNT;
            break;
        }

        case CONTINUOUS_GLUCOSE_MONITORING_SERVICE_UUID:
        {
            characteristicDetails = cgmsCharacteristics;
            characteristicCount = CGMS_CHARACTERISTIC_COUNT;
            break;
        }

        case CURRENT_TIME_SERVICE_UUID:
        {
            characteristicDetails = ctsCharacteristics;
            characteristicCount = CTS_CHARACTERISTIC_COUNT;
            break;
        }

        case CYCLING_POWER_SERVICE_UUID:
        {
            characteristicDetails = cpsCharacteristics;
            characteristicCount = CPS_CHARACTERISTIC_COUNT;
            break;
        }

        case CYCLING_SPEED_AND_CADENCE_SERVICE_UUID:
        {
            characteristicDetails = cscsCharacteristics;
            characteristicCount = CSCS_CHARACTERISTIC_COUNT;
            break;
        }

        case DEVICE_INFORMATION_SERVICE_UUID:
        {
            characteristicDetails = disCharacteristics;
            characteristicCount = DIS_CHARACTERISTIC_COUNT;
            break;
        }

        case ENVIRONMENTAL_SENSING_SERVICE_UUID:
        {
            characteristicDetails = essCharacteristics;
            characteristicCount = ESS_CHARACTERISTIC_COUNT;
            break;
        }

        case FITNESS_MACHINE_SERVICE_UUID:
        {
            characteristicDetails = fmsCharacteristics;
            characteristicCount = FMS_CHARACTERISTIC_COUNT;
            break;
        }

        case GENERIC_ATTRIBUTE_SERVICE_UUID:
        {
            characteristicDetails = gatsCharacteristics;
            characteristicCount = GATS_CHARACTERISTIC_COUNT;
            break;
        }

        case GLUCOSE_SERVICE_UUID:
        {
            characteristicDetails = glsCharacteristics;
            characteristicCount = GLS_CHARACTERISTIC_COUNT;
            break;
        }

        case HEALTH_THERMOMETER_SERVICE_UUID:
        {
            characteristicDetails = htsCharacteristics;
            characteristicCount = HTS_CHARACTERISTIC_COUNT;
            break;
        }

        case HEART_RATE_SERVICE_UUID:
        {
            characteristicDetails = hrsCharacteristics;
            characteristicCount = HRS_CHARACTERISTIC_COUNT;
            break;
        }

        case HTTP_PROXY_SERVICE_UUID:
        {
            characteristicDetails = hpsCharacteristics;
            characteristicCount = HPS_CHARACTERISTIC_COUNT;
            break;
        }

        case HUMAN_INTERFACE_DEVICE_SERVICE_UUID:
        {
            characteristicDetails = hidsCharacteristics;
            characteristicCount = HIDS_CHARACTERISTIC_COUNT;
            break;
        }

        case IMMEDIATE_ALERT_SERVICE_UUID:
        {
            characteristicDetails = iasCharacteristics;
            characteristicCount = IAS_CHARACTERISTIC_COUNT;
            break;
        }

        case INDOOR_POSITIONING_SERVICE_UUID:
        {
            characteristicDetails = ipsCharacteristics;
            characteristicCount = IPS_CHARACTERISTIC_COUNT;
            break;
        }

        case INTERNET_PROTOCOL_SUPPORT_SERVICE_UUID:
        {
            /* No characteristics defined by SIG */
            break;
        }

        case LINK_LOSS_SERVICE_UUID:
        {
            characteristicDetails = llsCharacteristics;
            characteristicCount = LLS_CHARACTERISTIC_COUNT;
            break;
        }

        case LOCATION_AND_NAVIGATION_SERVICE_UUID:
        {
            characteristicDetails = lasCharacteristics;
            characteristicCount = LAS_CHARACTERISTIC_COUNT;
            break;
        }

        case MESH_PROVISIONING_SERVICE_UUID:
        {
            characteristicDetails = mpsCharacteristics;
            characteristicCount = MPS_CHARACTERISTIC_COUNT;
            break;
        }

        case MESH_PROXY_SERVICE_UUID:
        {
            characteristicDetails = mpxyCharacteristics;
            characteristicCount = MESH_PROXY_CHARACTERISTIC_COUNT;
            break;
        }

        case NEXT_DST_CHANGE_SERVICE_UUID:
        {
            characteristicDetails = ndcsCharacteristics;
            characteristicCount = NDCS_CHARACTERISTIC_COUNT;
            break;
        }

        case OBJECT_TRANSFER_SERVICE_UUID:
        {
            characteristicDetails = otsCharacteristics;
            characteristicCount = OTS_CHARACTERISTIC_COUNT;
            break;
        }

        case PHONE_ALERT_STATUS_SERVICE_UUID:
        {
            characteristicDetails = passCharacteristics;
            characteristicCount = PASS_CHARACTERISTIC_COUNT;
            break;
        }

        case PULSE_OXIMETER_SERVICE_UUID:
        {
            characteristicDetails = plxCharacteristics;
            characteristicCount = PLX_CHARACTERISTIC_COUNT;
            break;
        }

        case RECONNECTION_CONFIGURATION_SERVICE_UUID:
        {
            characteristicDetails = rcsCharacteristics;
            characteristicCount = RCS_CHARACTERISTIC_COUNT;
            break;
        }

        case REFERENCE_TIME_UPDATE_SERVICE_UUID:
        {
            characteristicDetails = rtusCharacteristics;
            characteristicCount = RTUS_CHARACTERISTIC_COUNT;
            break;
        }

        case RUNNING_SPEED_AND_CADENCE_SERVICE_UUID:
        {
            characteristicDetails = rscsCharacteristics;
            characteristicCount = RSCS_CHARACTERISTIC_COUNT;
            break;
        }

        case SCAN_PARAMETERS_SERVICE_UUID:
        {
            characteristicDetails = spsCharacteristics;
            characteristicCount = SPS_CHARACTERISTIC_COUNT;
            break;
        }

        case TRANSPORT_DISCOVERY_SERVICE_UUID:
        {
            characteristicDetails = tdsCharacteristics;
            characteristicCount = TDS_CHARACTERISTIC_COUNT;
            break;
        }

        case TX_POWER_SERVICE_UUID:
        {
            characteristicDetails = tpsCharacteristics;
            characteristicCount = TPS_CHARACTERISTIC_COUNT;
            break;
        }

        case USER_DATA_SERVICE_UUID:
        {
            characteristicDetails = udsCharacteristics;
            characteristicCount = UDS_CHARACTERISTIC_COUNT;
            break;
        }

        case WIGHT_SCALE_SERVICE_UUID:
        {
            characteristicDetails = wssCharacteristics;
            characteristicCount = WSS_CHARACTERISTIC_COUNT;
            break;
        }

        case BROADCAST_AUDIO_SCAN_SERVICE_UUID :
        {
            characteristicDetails = bassCharacteristics;
            characteristicCount   = BASS_CHARACTERISTIC_COUNT;
            break;
        }

        case AUDIO_STRAM_CONTROL_SERVICE_UUID :
        {
            characteristicDetails = ascsCharacteristics;
            characteristicCount   = ASCS_CHARACTERISTIC_COUNT;
            break;
        }

        case PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID :
        {
            characteristicDetails = pacsCharacteristics;
            characteristicCount   = PACS_CHARACTERISTIC_COUNT;
            break;
        }

        case VOLUME_CONTROL_SERVICE_UUID :
        {
            characteristicDetails = vcsCharacteristics;
            characteristicCount   = VCS_CHARACTERISTIC_COUNT;
            break;
        }

        case COORDINATED_SET_IDENTIFICATION_SERVICE_UUID :
        {
            characteristicDetails = csisCharacteristics;
            characteristicCount   = CSIS_CHARACTERISTIC_COUNT;
            break;
        }

    }

    for (u4 i = 0; i < characteristicCount; i++)
    {
        if (characteristicUuid == characteristicDetails[i].uuid)
        {
            return characteristicDetails[i].name;
        }
    }

    return UNKNOWN_CHARACTERISTIC_NAME;
}

#endif /* defined(CLX_BLE_GATT_SERVICE_VERBOSE) */

