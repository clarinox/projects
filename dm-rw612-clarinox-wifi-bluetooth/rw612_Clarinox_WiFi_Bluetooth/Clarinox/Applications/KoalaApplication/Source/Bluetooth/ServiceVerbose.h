#ifndef __ServiceVerbose_h__
#define __ServiceVerbose_h__

/********************************************************************************
*
* Project             Clarinox Reference Application
* File                ServiceVerbose.h
* Description         The file has defined the standard services, characteristics
*                     and descriptors details.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#if defined(CLX_BLE_GATT_SERVICE_VERBOSE)
/* Generic Access Service */
#define GENERIC_ACCESS_SERVICE_NAME                             "Generic Access Service"
#define GENERIC_ACCESS_SERVICE_UUID                             0x1800
#define GENERIC_ACCESS_SERVICE_INDEX                            0

#define GAS_CHARACTERISTIC_COUNT                                5
#define GAS_CHARACTERISTIC_DEVICE_NAME                          "Device Name"
#define GAS_CHARACTERISTIC_DEVICE_NAME_UUID                     0x2A00
#define GAS_CHARACTERISTIC_APPEARANCE                           "Appearance"
#define GAS_CHARACTERISTIC_APPEARANCE_UUID                      0x2A01
#define GAS_CHARACTERISTIC_PRIVACY_FLAG                         "Privacy Flag"
#define GAS_CHARACTERISTIC_PRIVACY_FLAG_UUID                    0x2A02
#define GAS_CHARACTERISTIC_RECONNECTION_ADDRESS                 "Reconnection Address"
#define GAS_CHARACTERISTIC_RECONNECTION_ADDRESS_UUID            0x2A03
#define GAS_CHARACTERISTIC_CONNECTION_PARAMETERS                "Connection Parameters"
#define GAS_CHARACTERISTIC_CONNECTION_PARAMETERS_UUID           0x2A04

/* Alert Notification Service */
#define ALERT_NOTIFICATION_SERVICE_NAME                         "Alert Notification Service"
#define ALERT_NOTIFICATION_SERVICE_UUID                         0x1811
#define ALERT_NOTIFICATION_SERVICE_INDEX                        1

#define ANS_CHARACTERISTIC_COUNT                                5
#define ANS_CHARACTERISTIC_NEW_ALERT_CATEGORY                   "New Alert Category"
#define ANS_CHARACTERISTIC_NEW_ALERT_CATEGORY_UUID              0x2A47
#define ANS_CHARACTERISTIC_NEW_ALERT                            "New Alert"
#define ANS_CHARACTERISTIC_NEW_ALERT_UUID                       0x2A46
#define ANS_CHARACTERISTIC_UNREAD_ALERT_CATEGORY                "Unread Alert Category"
#define ANS_CHARACTERISTIC_UNREAD_ALERT_CATEGORY_UUID           0x2A48
#define ANS_CHARACTERISTIC_UNREAD_ALERT_STATUS                  "Unread Alert Status"
#define ANS_CHARACTERISTIC_UNREAD_ALERT_STATUS_UUID             0x2A45
#define ANS_CHARACTERISTIC_CONTROL_POINT                        "Alert Notification Control Point"
#define ANS_CHARACTERISTIC_CONTROL_POINT_UUID                   0x2A44

/* Automation IO service */
#define AUTOMATION_IO_SEVICE_NAME                               "Automation IO"
#define AUTOMATION_IO_SEVICE_UUID                               0x1815
#define AUTOMATION_IO_SEVICE_INDEX                              2

#define AIOS_CHARACTERISTIC_COUNT                               3
#define AIOS_CHARACTERISTIC_DIGITAL                             "Digital"
#define AIOS_CHARACTERISTIC_DIGITAL_UUID                        0x2A56
#define AIOS_CHARACTERISTIC_ANALOG                              "Analog"
#define AIOS_CHARACTERISTIC_ANALOG_UUID                         0x2A58
#define AIOS_CHARACTERISTIC_AGGREGATE                           "Aggregate"
#define AIOS_CHARACTERISTIC_AGGREGATE_UUID                      0x2A5A

/* Battery service */
#define BATTERY_SERVICE_NAME                                    "Battery Service"
#define BATTERY_SERVICE_UUID                                    0x180F
#define BATTERY_SERVICE_INDEX                                   3

#define BAS_CHARACTERISTIC_COUNT                                1
#define BAS_CHARACTERISTIC_BATTERY_LEVEL                        "Battery Level"
#define BAS_CHARACTERISTIC_BATTERY_LEVEL_UUID                   0x2A19

/* Blood pressure service */
#define BLOOD_PRESSURE_SERVICE_NAME                             "Blood Pressure Service"
#define BLOOD_PRESSURE_SERVICE_UUID                             0x1810
#define BLOOD_PRESSURE_SERVICE_INDEX                            4

#define BPS_CHARACTERISTIC_COUNT                                3
#define BPS_CHARACTERISTIC_MEASUREMENT                          "Blood Pressure Measurement"
#define BPS_CHARACTERISTIC_MEASUREMENT_UUID                     0x2A35
#define BPS_CHARACTERISTIC_INTERMEDIATE_CUFF_PRESSURE           "Intermediate Cuff Pressure"
#define BPS_CHARACTERISTIC_INTERMEDIATE_CUFF_PRESSURE_UUID      0x2A36
#define BPS_CHARACTERISTIC_FEATURE                              "Blood Pressure Feature"
#define BPS_CHARACTERISTIC_FEATURE_UUID                         0x2A49

/* Body composition service */
#define BODY_COMPOSITION_SERVICE                                "Body Composition Service"
#define BODY_COMPOSITION_SERVICE_UUID                           0x181B
#define BODY_COMPOSITION_SERVICE_INDEX                          5

#define BCS_CHARACTERISTIC_COUNT                                2
#define BCS_CHARACTERISTIC_FEATURE                              "Body Composition Feature"
#define BCS_CHARACTERISTIC_FEATURE_UUID                         0x2A9B
#define BCS_CHARACTERISTIC_MEASUREMENT                          "Body Composition Measurement"
#define BCS_CHARACTERISTIC_MEASUREMENT_UUID                     0x2A9C

/* Bond management service */
#define BOND_MANAGEMENT_SERVICE_NAME                            "Bond Management Service"
#define BOND_MANAGEMENT_SERVICE_UUID                            0x181E
#define BOND_MANAGEMENT_SERVICE_INDEX                           6

#define BMS_CHARACTERISTIC_COUNT                                2
#define BMS_CHARACTERISTIC_CONTROL_POINT                        "Bond Management Control Point"
#define BMS_CHARACTERISTIC_CONTROL_POINT_UUID                   0x2AA4
#define BMS_CHARACTERISTIC_FEATURE                              "Bond Management Feature"
#define BMS_CHARACTERISTIC_FEATURE_UUID                         0x2AA5

/* Continuous glucose monitoring service */
#define CONTINUOUS_GLUCOSE_MONITORING_SERVICE_NAME              "Continuous Glucose Monitoring"
#define CONTINUOUS_GLUCOSE_MONITORING_SERVICE_UUID              0x181F
#define CONTINUOUS_GLUCOSE_MONITORING_SERVICE_INDEX             7

#define CGMS_CHARACTERISTIC_COUNT                               7
#define CGMS_CHARACTERISTIC_MEASUREMENT                         "CGMS Measurement"
#define CGMS_CHARACTERISTIC_MEASUREMENT_UUID                    0x2AA7
#define CGMS_CHARACTERISTIC_FEATURE                             "CGMS Feature"
#define CGMS_CHARACTERISTIC_FEATURE_UUID                        0x2AA8
#define CGMS_CHARACTERISTIC_STATUS                              "CGMS Status"
#define CGMS_CHARACTERISTIC_STATUS_UUID                         0x2AA9
#define CGMS_CHARACTERISTIC_SESSION_START_TIME                  "CGMS Session Start Time"
#define CGMS_CHARACTERISTIC_SESSION_START_TIME_UUID             0x2AAA
#define CGMS_CHARACTERISTIC_SESSION_RUN_TIME                    "CGMS Session Run Time"
#define CGMS_CHARACTERISTIC_SESSION_RUN_TIME_UUID               0x2AAB
#define CGMS_CHARACTERISTIC_RECORD_ACCESS_CONTROL_POINT         "CGMS Record Access Control Point"
#define CGMS_CHARACTERISTIC_RECORD_ACCESS_CONTROL_POINT_UUID    0x2A52
#define CGMS_CHARACTERISTIC_SPECIFIC_OPS_CONTROL_POINT          "CGMS Specific OPS Control Point"
#define CGMS_CHARACTERISTIC_SPECIFIC_OPS_CONTROL_POINT_UUID     0x2AAC

/* Current time service */
#define CURRENT_TIME_SERVICE_NAME                               "Current Time Service"
#define CURRENT_TIME_SERVICE_UUID                               0x1805
#define CURRENT_TIME_SERVICE_INDEX                              8

#define CTS_CHARACTERISTIC_COUNT                                3
#define CTS_CHARACTERISTIC_CURRENT_TIME                         "Current Time"
#define CTS_CHARACTERISTIC_CURRENT_TIME_UUID                    0x2A2B
#define CTS_CHARACTERISTIC_LOCAL_TIME_INFORMATION               "Local Time Information"
#define CTS_CHARACTERISTIC_LOCAL_TIME_INFORMATION_UUID          0x2A0F
#define CTS_CHARACTERISTIC_REFERENCE_TIME_INFORMATION           "Reference Time Information"
#define CTS_CHARACTERISTIC_REFERENCE_TIME_INFORMATION_UUID      0x2A14

/* Cycling power service */
#define CYCLING_POWER_SERVICE_NAME                              "Cycling Power Service"
#define CYCLING_POWER_SERVICE_UUID                              0x1818
#define CYCLING_POWER_SERVICE_INDEX                             9

#define CPS_CHARACTERISTIC_COUNT                                5
#define CPS_CHARACTERISTIC_MEASUREMENT                          "CPS Measurement"
#define CPS_CHARACTERISTIC_MEASUREMENT_UUID                     0x2A63
#define CPS_CHARACTERISTIC_FEATURE                              "CPS Feature"
#define CPS_CHARACTERISTIC_FEATURE_UUID                         0x2A65
#define CPS_CHARACTERISTIC_SENSOR_LOCATION                      "CPS Sensor Location"
#define CPS_CHARACTERISTIC_SENSOR_LOCATION_UUID                 0x2A5D
#define CPS_CHARACTERISTIC_VECTOR                               "CPS Vector"
#define CPS_CHARACTERISTIC_VECTOR_UUID                          0x2A64
#define CPS_CHARACTERISTIC_CONTROL_POINT                        "CPS Control Point"
#define CPS_CHARACTERISTIC_CONTROL_POINT_UUID                   0x2A66

/* Cycling speed and cadence service */
#define CYCLING_SPEED_AND_CADENCE_SERVICE_NAME                  "Cycling Speed and Cadence Service"
#define CYCLING_SPEED_AND_CADENCE_SERVICE_UUID                  0x1816
#define CYCLING_SPEED_AND_CADENCE_SERVICE_INDEX                 10

#define CSCS_CHARACTERISTIC_COUNT                               4
#define CSCS_CHARACTERISTIC_MEASUREMENT                         "CSCS Measurement"
#define CSCS_CHARACTERISTIC_MEASUREMENT_UUID                    0x2A5B
#define CSCS_CHARACTERISTIC_FEATURE                             "CSCS Feature"
#define CSCS_CHARACTERISTIC_FEATURE_UUID                        0x2A5C
#define CSCS_CHARACTERISTIC_SENSOR_LOCATION                     "CSCS Sensor Location"
#define CSCS_CHARACTERISTIC_SENSOR_LOCATION_UUID                0x2A5D
#define CSCS_CHARACTERISTIC_CONTROL_POINT                       "CSCS Control Point"
#define CSCS_CHARACTERISTIC_CONTROL_POINT_UUID                  0x2A55

/* Device information service */
#define DEVICE_INFORMATION_SERVICE_NAME                         "Device Information Service"
#define DEVICE_INFORMATION_SERVICE_UUID                         0x180A
#define DEVICE_INFORMATION_SERVICE_INDEX                        11

#define DIS_CHARACTERISTIC_COUNT                                9
#define DIS_CHARACTERISTIC_MANUFACTURE_NAME                     "Manufacturer Name"
#define DIS_CHARACTERISTIC_MANUFACTURE_NAME_UUID                0x2A29
#define DIS_CHARACTERISTIC_MODEL_NUMBER                         "Model Number"
#define DIS_CHARACTERISTIC_MODEL_NUMBER_UUID                    0x2A24
#define DIS_CHARACTERISTIC_SERIAL_NUMBER                        "Serial Number"
#define DIS_CHARACTERISTIC_SERIAL_NUMBER_UUID                   0x2A25
#define DIS_CHARACTERISTIC_HW_REVISION                          "Hardware Revision"
#define DIS_CHARACTERISTIC_HW_REVISION_UUID                     0x2A27
#define DIS_CHARACTERISTIC_SW_REVISION                          "Software Revision"
#define DIS_CHARACTERISTIC_SW_REVISION_UUID                     0x2A28
#define DIS_CHARACTERISTIC_FIRMWARE_REVISION                    "Firmware Revision"
#define DIS_CHARACTERISTIC_FIRMWARE_REVISION_UUID               0x2A26
#define DIS_CHARACTERISTIC_SYSTEM_ID                            "System ID"
#define DIS_CHARACTERISTIC_SYSTEM_ID_UUID                       0x2A23
#define DIS_CHARACTERISTIC_CERTIFY_DATA_LIST                    "Certification Data List"
#define DIS_CHARACTERISTIC_CERTIFY_DATA_LIST_UUID               0x2A2A
#define DIS_CHARACTERISTIC_PNP_ID                               "Pnp ID"
#define DIS_CHARACTERISTIC_PNP_ID_UUID                          0x2A50

/* Environmental sensing service */
#define ENVIRONMENTAL_SENSING_SERVICE_NAME                      "Environmental Sensing Service"
#define ENVIRONMENTAL_SENSING_SERVICE_UUID                      0x181A
#define ENVIRONMENTAL_SENSING_SERVICE_INDEX                     12

#define ESS_CHARACTERISTIC_COUNT                                21
#define ESS_CHARACTERISTIC_DESCRIPTOR_VALUE_CHANGED             "Descriptor Value Changed"
#define ESS_CHARACTERISTIC_DESCRIPTOR_VALUE_CHANGED_UUID        0x2A7D
#define ESS_CHARACTERISTIC_APPARENT_WIND_DIRECTION              "Apparent Wind Direction"
#define ESS_CHARACTERISTIC_APPARENT_WIND_DIRECTION_UUID         0x2A73
#define ESS_CHARACTERISTIC_APPARENT_WIND_SPEED                  "Apparent Wind Speed"
#define ESS_CHARACTERISTIC_APPARENT_WIND_SPEED_UUID             0x2A72
#define ESS_CHARACTERISTIC_DEW_POINT                            "Dew Point"
#define ESS_CHARACTERISTIC_DEW_POINT_UUID                       0x2A7B
#define ESS_CHARACTERISTIC_ELEVATION                            "Elevation"
#define ESS_CHARACTERISTIC_ELEVATION_UUID                       0x2A6C
#define ESS_CHARACTERISTIC_GUST_FACTOR                          "Gust Factor"
#define ESS_CHARACTERISTIC_GUST_FACTOR_UUID                     0x2A74
#define ESS_CHARACTERISTIC_HEAT_INDEX                           "Heat Index"
#define ESS_CHARACTERISTIC_HEAT_INDEX_UUID                      0x2A7A
#define ESS_CHARACTERISTIC_HUMIDITY                             "Humidity"
#define ESS_CHARACTERISTIC_HUMIDITY_UUID                        0x2A6F
#define ESS_CHARACTERISTIC_IRRADIANCE                           "Irradiance"
#define ESS_CHARACTERISTIC_IRRADIANCE_UUID                      0x2A77
#define ESS_CHARACTERISTIC_POLLEN_CONCENTRATION                 "Pollen Concentration"
#define ESS_CHARACTERISTIC_POLLEN_CONCENTRATION_UUID            0x2A75
#define ESS_CHARACTERISTIC_RAINFALL                             "Rainfall"
#define ESS_CHARACTERISTIC_RAINFALL_UUID                        0x2A78
#define ESS_CHARACTERISTIC_PRESSURE                             "Pressure"
#define ESS_CHARACTERISTIC_PRESSURE_UUID                        0x2A6D
#define ESS_CHARACTERISTIC_TEMPERATURE                          "Temperature"
#define ESS_CHARACTERISTIC_TEMPERATURE_UUID                     0x2A6E
#define ESS_CHARACTERISTIC_TRUEWIND_DIRECTION                   "True Wind Direction"
#define ESS_CHARACTERISTIC_TRUEWIND_DIRECTION_UUID              0x2A71
#define ESS_CHARACTERISTIC_TRUEWIND_SPEED                       "True Wind Speed"
#define ESS_CHARACTERISTIC_TRUEWIND_SPEED_UUID                  0x2A70
#define ESS_CHARACTERISTIC_UV_INDEX                             "UV Index"
#define ESS_CHARACTERISTIC_UV_INDEX_UUID                        0x2A76
#define ESS_CHARACTERISTIC_WIND_CHILL                           "Wind Chill"
#define ESS_CHARACTERISTIC_WIND_CHILL_UUID                      0x2A79
#define ESS_CHARACTERISTIC_BAROMETRIC_PRESSURE_TREND            "Barometric Pressure Trend"
#define ESS_CHARACTERISTIC_BAROMETRIC_PRESSURE_TREND_UUID       0x2AA3
#define ESS_CHARACTERISTIC_MAGNETIC_DECLINATION                 "Magnetic Declination"
#define ESS_CHARACTERISTIC_MAGNETIC_DECLINATION_UUID            0x2A2C
#define ESS_CHARACTERISTIC_MAGNETIC_FLEX_DENSITY_2D             "Magnetic Flux Density - 2D"
#define ESS_CHARACTERISTIC_MAGNETIC_FLEX_DENSITY_2D_UUID        0x2AA0
#define ESS_CHARACTERISTIC_MAGNETIC_FLEX_DENSITY_3D             "Magnetic Flux Density - 3D"
#define ESS_CHARACTERISTIC_MAGNETIC_FLEX_DENSITY_3D_UUID        0x2AA1

/* Fitness machine service */
#define FITNESS_MACHINE_SERVICE_NAME                            "Fitness Machine Service"
#define FITNESS_MACHINE_SERVICE_UUID                            0x1826
#define FITNESS_MACHINE_SERVICE_INDEX                           13

#define FMS_CHARACTERISTIC_COUNT                                15
#define FMS_CHARACTERISTIC_FEATURE                              "FMS Feature"
#define FMS_CHARACTERISTIC_FEATURE_UUID                         0x2ACC
#define FMS_CHARACTERISTIC_TREADMILLDATA                        "Treadmill Data"
#define FMS_CHARACTERISTIC_TREADMILLDATA_UUID                   0x2ACD
#define FMS_CHARACTERISTIC_CROSS_TRAINER_DATA                   "Cross Trainer Data"
#define FMS_CHARACTERISTIC_CROSS_TRAINER_DATA_UUID              0x2ACE
#define FMS_CHARACTERISTIC_STEP_CLIMBER_DATA                    "Step Climber Data"
#define FMS_CHARACTERISTIC_STEP_CLIMBER_DATA_UUID               0x2ACF
#define FMS_CHARACTERISTIC_STAIR_CLIMBER_DATA                   "Stair Climber Data"
#define FMS_CHARACTERISTIC_STAIR_CLIMBER_DATA_UUID              0x2AD0
#define FMS_CHARACTERISTIC_ROWER_DATA                           "Rower Data"
#define FMS_CHARACTERISTIC_ROWER_DATA_UUID                      0x2AD1
#define FMS_CHARACTERISTIC_INDOOR_BIKE_DATA                     "Indoor Bike Data"
#define FMS_CHARACTERISTIC_INDOOR_BIKE_DATA_UUID                0x2AD2
#define FMS_CHARACTERISTIC_TRAINING_STATUS                      "Training Status"
#define FMS_CHARACTERISTIC_TRAINING_STATUS_UUID                 0x2AD3
#define FMS_CHARACTERISTIC_SPEED_RANGE                          "Speed Range"
#define FMS_CHARACTERISTIC_SPEED_RANGE_UUID                     0x2AD4
#define FMS_CHARACTERISTIC_INCLINATION_RANGE                    "Inclination Range"
#define FMS_CHARACTERISTIC_INCLINATION_RANGE_UUID               0x2AD5
#define FMS_CHARACTERISTIC_RESISTANCE_LEVEL_CHANGE              "Resistance Level Range"
#define FMS_CHARACTERISTIC_RESISTANCE_LEVEL_CHANGE_UUID         0x2AD6
#define FMS_CHARACTERISTIC_POWER_CHANGE                         "Power Range"
#define FMS_CHARACTERISTIC_POWER_CHANGE_UUID                    0x2AD8
#define FMS_CHARACTERISTIC_HEART_RATE_RANGE                     "Heart Rate Range"
#define FMS_CHARACTERISTIC_HEART_RATE_RANGE_UUID                0x2AD7
#define FMS_CHARACTERISTIC_CONTROL_POINT                        "Control Point"
#define FMS_CHARACTERISTIC_CONTROL_POINT_UUID                   0x2AD9
#define FMS_CHARACTERISTIC_STATUS                               "Status"
#define FMS_CHARACTERISTIC_STATUS_UUID                          0x2ADA

/* Generic attribute service */
#define GENERIC_ATTRIBUTE_SERVICE_NAME                          "Generic Attribute Service"
#define GENERIC_ATTRIBUTE_SERVICE_UUID                          0x1801
#define GENERIC_ATTRIBUTE_SERVICE_INDEX                         14

#define GATS_CHARACTERISTIC_COUNT                               1
#define GATS_CHARACTERISTIC_SERVICE_CHANGED                      "Service Changed"
#define GATS_CHARACTERISTIC_SERVICE_CHANGED_UUID                 0x2A05

/* Glucose service */
#define GLUCOSE_SERVICE_NAME                                    "Glucose Service"
#define GLUCOSE_SERVICE_UUID                                    0x1808
#define GLUCOSE_SERVICE_INDEX                                   15

#define GLS_CHARACTERISTIC_COUNT                                4
#define GLS_CHARACTERISTIC_MEASUREMENT                          "Measurement"
#define GLS_CHARACTERISTIC_MEASUREMENT_UUID                     0x2A18
#define GLS_CHARACTERISTIC_MEASUREMENT_CONTEXT                  "Measurement Context"
#define GLS_CHARACTERISTIC_MEASUREMENT_CONTEXT_UUID             0x2A34
#define GLS_CHARACTERISTIC_FEATURE                              "Feature"
#define GLS_CHARACTERISTIC_FEATURE_UUID                         0x2A51
#define GLS_CHARACTERISTIC_RECORD_ACCESS_CONTROLPOINT           "Record Access Control Point"
#define GLS_CHARACTERISTIC_RECORD_ACCESS_CONTROLPOINT_UUID      0x2A52

/* Health thermometer service */
#define HEALTH_THERMOMETER_SERVICE_NAME                         "Health Thermometer Service"
#define HEALTH_THERMOMETER_SERVICE_UUID                         0x1809
#define HEALTH_THERMOMETER_SERVICE_INDEX                        16

#define HTS_CHARACTERISTIC_COUNT                                4
#define HTS_CHARACTERISTIC_MEASUREMENT                          "Measurement"
#define HTS_CHARACTERISTIC_MEASUREMENT_UUID                     0x2A1C
#define HTS_CHARACTERISTIC_TEMPERATURE_TYPE                     "Temperature Type"
#define HTS_CHARACTERISTIC_TEMPERATURE_TYPE_UUID                0x2A1D
#define HTS_CHARACTERISTIC_IMMEDIATE_TEMPERATURE                "Intermediate Temperature"
#define HTS_CHARACTERISTIC_IMMEDIATE_TEMPERATURE_UUID           0x2A1E
#define HTS_CHARACTERISTIC_MEASUREMENT_TYPE                     "Measurement Interval"
#define HTS_CHARACTERISTIC_MEASUREMENT_TYPE_UUID                0x2A21

/* Heart rate service */
#define HEART_RATE_SERVICE_NAME                                 "Heart Rate Service"
#define HEART_RATE_SERVICE_UUID                                 0x180D
#define HEART_RATE_SERVICE_INDEX                                17

#define HRS_CHARACTERISTIC_COUNT                                3
#define HRS_CHARACTERISTIC_MEASUREMENT                          "Measurement"
#define HRS_CHARACTERISTIC_MEASUREMENT_UUID                     0x2A37
#define HRS_CHARACTERISTIC_BODY_SENSOR_LOCATION                 "Sensor Location"
#define HRS_CHARACTERISTIC_BODY_SENSOR_LOCATION_UUID            0x2A38
#define HRS_CHARACTERISTIC_CONTROLPOINT                         "Control Point"
#define HRS_CHARACTERISTIC_CONTROLPOINT_UUID                    0x2A39

/* HTTP proxy service */
#define HTTP_PROXY_SERVICE_NAME                                 "HTTP Proxy Service"
#define HTTP_PROXY_SERVICE_UUID                                 0x1823
#define HTTP_PROXY_SERVICE_INDEX                                18

#define HPS_CHARACTERISTIC_COUNT                                6
#define HPS_CHARACTERISTIC_URI                                  "URI"
#define HPS_CHARACTERISTIC_URI_UUID                             0x2AB6
#define HPS_CHARACTERISTIC_HEADERS                              "Headers"
#define HPS_CHARACTERISTIC_HEADERS_UUID                         0x2AB7
#define HPS_CHARACTERISTIC_ENTITY_BODY                          "Entity Body"
#define HPS_CHARACTERISTIC_ENTITY_BODY_UUID                     0x2AB9
#define HPS_CHARACTERISTIC_CONTROL_POINT                        "Control Point"
#define HPS_CHARACTERISTIC_CONTROL_POINT_UUID                   0x2ABA
#define HPS_CHARACTERISTIC_STATUS_CODE                          "Status Code"
#define HPS_CHARACTERISTIC_STATUS_CODE_UUID                     0x2AB8
#define HPS_CHARACTERISTIC_SECURITY                             "Security"
#define HPS_CHARACTERISTIC_SECURITY_UUID                        0x2ABB

/* Human interface device service */
#define HUMAN_INTERFACE_DEVICE_SERVICE_NAME                     "Human Interface Device Service"
#define HUMAN_INTERFACE_DEVICE_SERVICE_UUID                     0x1812
#define HUMAN_INTERFACE_DEVICE_SERVICE_INDEX                    19

#define HIDS_CHARACTERISTIC_COUNT                               8
#define HIDS_CHARACTERISTIC_PROTOCOL_MODE                       "Protocol Mode"
#define HIDS_CHARACTERISTIC_PROTOCOL_MODE_UUID                  0x2A4E
#define HIDS_CHARACTERISTIC_REPORT                              "Report"
#define HIDS_CHARACTERISTIC_REPORT_UUID                         0x2A4D
#define HIDS_CHARACTERISTIC_REPORTMAP                           "Report Map"
#define HIDS_CHARACTERISTIC_REPORTMAP_UUID                      0x2A4B
#define HIDS_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT          "Boot Keyboard Input Report"
#define HIDS_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_UUID     0x2A22
#define HIDS_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT         "Boot Keyboard Output Report"
#define HIDS_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_UUID    0x2A32
#define HIDS_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT             "Boot Mouse Input Report"
#define HIDS_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT_UUID        0x2A33
#define HIDS_CHARACTERISTIC_BOOT_HID_INFORMATION                "HID Information"
#define HIDS_CHARACTERISTIC_BOOT_HID_INFORMATION_UUID           0x2A4A
#define HIDS_CHARACTERISTIC_BOOT_CONTROL_POINT                  "Control Point"
#define HIDS_CHARACTERISTIC_BOOT_CONTROL_POINT_UUID             0x2A4C

/* Immediate alert service */
#define IMMEDIATE_ALERT_SERVICE_NAME                            "Immediate Alert Service"
#define IMMEDIATE_ALERT_SERVICE_UUID                            0x1802
#define IMMEDIATE_ALERT_SERVICE_INDEX                           20

#define IAS_CHARACTERISTIC_COUNT                                1
#define IAS_CHARACTERISTIC_ALERT_LEVEL                          "Alert Level"
#define IAS_CHARACTERISTIC_ALERT_LEVEL_UUID                     0x2A06

/* Indoor positioning service */
#define INDOOR_POSITIONING_SERVICE_NAME                         "Indoor Positioning Service"
#define INDOOR_POSITIONING_SERVICE_UUID                         0x1821
#define INDOOR_POSITIONING_SERVICE_INDEX                        21

#define IPS_CHARACTERISTIC_COUNT                                9
#define IPS_CHARACTERISTIC_CONFIGURATION                        "Configuration"
#define IPS_CHARACTERISTIC_CONFIGURATION_UUID                   0x2AAD
#define IPS_CHARACTERISTIC_LATITUDE                             "Latitude"
#define IPS_CHARACTERISTIC_LATITUDE_UUID                        0x2AAE
#define IPS_CHARACTERISTIC_LONGITUDE                            "Longitude"
#define IPS_CHARACTERISTIC_LONGITUDE_UUID                       0x2AAF
#define IPS_CHARACTERISTIC_LOCAL_NORTH_COORDINATE               "Local North Coordinate"
#define IPS_CHARACTERISTIC_LOCAL_NORTH_COORDINATE_UUID          0x2AB0
#define IPS_CHARACTERISTIC_LOCAL_EAST_COORDINATE                "Local East Coordinate"
#define IPS_CHARACTERISTIC_LOCAL_EAST_COORDINATE_UUID           0x2AB1
#define IPS_CHARACTERISTIC_FLOOR_NUMBER                         "Floor Number"
#define IPS_CHARACTERISTIC_FLOOR_NUMBER_UUID                    0x2AB2
#define IPS_CHARACTERISTIC_ALTITUDE                             "Altitude"
#define IPS_CHARACTERISTIC_ALTITUDE_UUID                        0x2AB3
#define IPS_CHARACTERISTIC_UNCERTAINTY                          "Uncertainty"
#define IPS_CHARACTERISTIC_UNCERTAINTY_UUID                     0x2AB4
#define IPS_CHARACTERISTIC_LOCATION_NAME                        "Location Name"
#define IPS_CHARACTERISTIC_LOCATION_NAME_UUID                   0x2AB5

/* Internet protocol and support service */
#define INTERNET_PROTOCOL_SUPPORT_SERVICE_NAME                  "Internet Protocol Support Service"
#define INTERNET_PROTOCOL_SUPPORT_SERVICE_UUID                  0x1820
#define INTERNET_PROTOCOL_SUPPORT_SERVICE_INDEX                 22

/* Link loss service */
#define LINK_LOSS_SERVICE_NAME                                  "Link Loss Service"
#define LINK_LOSS_SERVICE_UUID                                  0x1803
#define LINK_LOSS_SERVICE_INDEX                                 23

#define LLS_CHARACTERISTIC_COUNT                                1
#define LLS_CHARACTERISTIC_ALERT_LEVEL                          "Alert Level"
#define LLS_CHARACTERISTIC_ALERT_LEVEL_UUID                     0x2A06

/* Location and navigation service */
#define LOCATION_AND_NAVIGATION_SERVICE_NAME                    "Location and Navigation Service"
#define LOCATION_AND_NAVIGATION_SERVICE_UUID                    0x1819
#define LOCATION_AND_NAVIGATION_SERVICE_INDEX                   24

#define LAS_CHARACTERISTIC_COUNT                                5
#define LAS_CHARACTERISTIC_LN_FEATURE                           "LN Feature"
#define LAS_CHARACTERISTIC_LN_FEATURE_UUID                      0x2A6A
#define LAS_CHARACTERISTIC_LOCATION_AND_SPEED                   "Location and Speed"
#define LAS_CHARACTERISTIC_LOCATION_AND_SPEED_UUID              0x2A67
#define LAS_CHARACTERISTIC_POSITION_QUALITY                     "Position Quality"
#define LAS_CHARACTERISTIC_POSITION_QUALITY_UUID                0x2A69
#define LAS_CHARACTERISTIC_CONTROL_POINT                        "LN Control Point"
#define LAS_CHARACTERISTIC_CONTROL_POINT_UUID                   0x2A6B
#define LAS_CHARACTERISTIC_NAVIGATION                           "Navigation"
#define LAS_CHARACTERISTIC_NAVIGATION_UUID                      0x2A68

/* Mesh provisioning service */
#define MESH_PROVISIONING_SERVICE_NAME                          "Mesh Provisioning Service"
#define MESH_PROVISIONING_SERVICE_UUID                          0x1827
#define MESH_PROVISIONING_SERVICE_INDEX                         25

#define MPS_CHARACTERISTIC_COUNT                                2
#define MPS_CHARACTERISTIC_DATA_IN                              "Data In"
#define MPS_CHARACTERISTIC_DATA_IN_UUID                         0x2ADB
#define MPS_CHARACTERISTIC_DATA_OUT                             "Data Out"
#define MPS_CHARACTERISTIC_DATA_OUT_UUID                        0x2ADC

/* Mesh proxy service */
#define MESH_PROXY_SERVICE_NAME                                 "Mesh Proxy Service"
#define MESH_PROXY_SERVICE_UUID                                 0x1828
#define MESH_PROXY_SERVICE_INDEX                                26

#define MESH_PROXY_CHARACTERISTIC_COUNT                         2
#define MESH_PROXY_CHARACTERISTIC_DATA_IN                       "Data In"
#define MESH_PROXY_CHARACTERISTIC_DATA_IN_UUID                  0x2ADD
#define MESH_PROXY_CHARACTERISTIC_DATA_OUT                      "Data Out"
#define MESH_PROXY_CHARACTERISTIC_DATA_OUT_UUID                 0x2ADE

/* Next DST change service */
#define NEXT_DST_CHANGE_SERVICE_NAME                            "Next DST Change Service"
#define NEXT_DST_CHANGE_SERVICE_UUID                            0x1807
#define NEXT_DST_CHANGE_SERVICE_INDEX                           27

#define NDCS_CHARACTERISTIC_COUNT                               1
#define NDCS_CHARACTERISTIC_TIME_WITH_DST                       "Time with DST"
#define NDCS_CHARACTERISTIC_TIME_WITH_DST_UUID                  0x2A11

/* Object transfer service */
#define OBJECT_TRANSFER_SERVICE_NAME                            "Object Transfer Service"
#define OBJECT_TRANSFER_SERVICE_UUID                            0x1825
#define OBJECT_TRANSFER_SERVICE_INDEX                           28

#define OTS_CHARACTERISTIC_COUNT                                12
#define OTS_CHARACTERISTIC_FEATURE                              "OTS Feature"
#define OTS_CHARACTERISTIC_FEATURE_UUID                         0x2ABD
#define OTS_CHARACTERISTIC_OBJECT_NAME                          "Object Name"
#define OTS_CHARACTERISTIC_OBJECT_NAME_UUID                     0x2ABE
#define OTS_CHARACTERISTIC_OBJECT_TYPE                          "Object Type"
#define OTS_CHARACTERISTIC_OBJECT_TYPE_UUID                     0x2ABF
#define OTS_CHARACTERISTIC_OBJECT_SIZE                          "Object Size"
#define OTS_CHARACTERISTIC_OBJECT_SIZE_UUID                     0x2AC0
#define OTS_CHARACTERISTIC_OBJECT_FIRST_CREATED                 "Object First Created"
#define OTS_CHARACTERISTIC_OBJECT_FIRST_CREATED_UUID            0x2AC1
#define OTS_CHARACTERISTIC_OBJECT_LAST_MODIFIED                 "Object Last Modified"
#define OTS_CHARACTERISTIC_OBJECT_LAST_MODIFIED_UUID            0x2AC2
#define OTS_CHARACTERISTIC_OBJECT_ID                            "Object Id"
#define OTS_CHARACTERISTIC_OBJECT_ID_UUID                       0x2AC3
#define OTS_CHARACTERISTIC_OBJECT_PROPERTIES                    "Object Properties"
#define OTS_CHARACTERISTIC_OBJECT_PROPERTIES_UUID               0x2AC4
#define OTS_CHARACTERISTIC_OBJECT_ACTION_CONTROL_POINT          "Object Action Control Point"
#define OTS_CHARACTERISTIC_OBJECT_ACTION_CONTROL_POINT_UUID     0x2AC5
#define OTS_CHARACTERISTIC_OBJECT_LIST_CONTROL_POINT            "Object List Control Point"
#define OTS_CHARACTERISTIC_OBJECT_LIST_CONTROL_POINT_UUID       0x2AC6
#define OTS_CHARACTERISTIC_OBJECT_LIST_FILTER                   "Object List Filter"
#define OTS_CHARACTERISTIC_OBJECT_LIST_FILTER_UUID              0x2AC7
#define OTS_CHARACTERISTIC_OBJECT_CHANGED                       "Object Changed"
#define OTS_CHARACTERISTIC_OBJECT_CHANGED_UUID                  0x2AC8

/* Phone alert status service */
#define PHONE_ALERT_STATUS_SERVICE_NAME                         "Phone Alert Status Service"
#define PHONE_ALERT_STATUS_SERVICE_UUID                         0x180E
#define PHONE_ALERT_STATUS_SERVICE_INDEX                        29

#define PASS_CHARACTERISTIC_COUNT                               3
#define PASS_CHARACTERISTIC_ALERT_STATUS                        "Alert Status"
#define PASS_CHARACTERISTIC_ALERT_STATUS_UUID                   0x2A3F
#define PASS_CHARACTERISTIC_RINGER_SETTING                      "Ringer Setting"
#define PASS_CHARACTERISTIC_RINGER_SETTING_UUID                 0x2A41
#define PASS_CHARACTERISTIC_RINGER_CONTROL_POINT                "Ringer Control Point"
#define PASS_CHARACTERISTIC_RINGER_CONTROL_POINT_UUID           0x2A40

/* Pulse oximeter service */
#define PULSE_OXIMETER_SERVICE_NAME                             "Pulse Oximeter Service"
#define PULSE_OXIMETER_SERVICE_UUID                             0x1822
#define PULSE_OXIMETER_SERVICE_INDEX                            30

#define PLX_CHARACTERISTIC_COUNT                                4
#define PLX_CHARACTERISTIC_SPOT_CHECK_MEASUREMENT               "Spot-check Measurement"
#define PLX_CHARACTERISTIC_SPOT_CHECK_MEASUREMENT_UUID          0x2A5E
#define PLX_CHARACTERISTIC_CONTINUOUS_MEASUREMENT               "Continuous Measurement"
#define PLX_CHARACTERISTIC_CONTINUOUS_MEASUREMENT_UUID          0x2A5F
#define PLX_CHARACTERISTIC_FEATURE                              "Features"
#define PLX_CHARACTERISTIC_FEATURE_UUID                         0x2A60
#define PLX_CHARACTERISTIC_RECORD_ACCESS_CONTROL_POINT          "Record Access Control Point"
#define PLX_CHARACTERISTIC_RECORD_ACCESS_CONTROL_POINT_UUID     0x2A52

/* Reconnection configuration service */
#define RECONNECTION_CONFIGURATION_SERVICE_NAME                 "Reconnection Configuration Service"
#define RECONNECTION_CONFIGURATION_SERVICE_UUID                 0x1829
#define RECONNECTION_CONFIGURATION_SERVICE_INDEX                31

#define RCS_CHARACTERISTIC_COUNT                                3
#define RCS_CHARACTERISTIC_FEATURES                             "Feature"
#define RCS_CHARACTERISTIC_FEATURES_UUID                        0x2B1D
#define RCS_CHARACTERISTIC_SETTINGS                             "Settings"
#define RCS_CHARACTERISTIC_SETTINGS_UUID                        0x2B1E
#define RCS_CHARACTERISTIC_CONTROL_POINT                        "Control Point"
#define RCS_CHARACTERISTIC_CONTROL_POINT_UUID                   0x2B1F

/* Reference time update service */
#define REFERENCE_TIME_UPDATE_SERVICE_NAME                      "Reference Time Update Service"
#define REFERENCE_TIME_UPDATE_SERVICE_UUID                      0x1806
#define REFERENCE_TIME_UPDATE_SERVICE_INDEX                     32

#define RTUS_CHARACTERISTIC_COUNT                               2
#define RTUS_CHARACTERISTIC_CONTROL_POINT                       "Control Point"
#define RTUS_CHARACTERISTIC_CONTROL_POINT_UUID                  0x2A16
#define RTUS_CHARACTERISTIC_STATE                               "State"
#define RTUS_CHARACTERISTIC_STATE_UUID                          0x2A17

/* Running speed and cadence service */
#define RUNNING_SPEED_AND_CADENCE_SERVICE_NAME                  "Running Speed and Cadence Service"
#define RUNNING_SPEED_AND_CADENCE_SERVICE_UUID                  0x1814
#define RUNNING_SPEED_AND_CADENCE_SERVICE_INDEX                 33

#define RSCS_CHARACTERISTIC_COUNT                               4
#define RSCS_CHARACTERISTIC_MEASUREMENT                         "Measurement"
#define RSCS_CHARACTERISTIC_MEASUREMENT_UUID                    0x2A53
#define RSCS_CHARACTERISTIC_FEATURE                             "Feature"
#define RSCS_CHARACTERISTIC_FEATURE_UUID                        0x2A54
#define RSCS_CHARACTERISTIC_SENSOR_LOCATION                     "Sensor Location"
#define RSCS_CHARACTERISTIC_SENSOR_LOCATION_UUID                0x2A5D
#define RSCS_CHARACTERISTIC_CONTROL_POINT                       "Control Point"
#define RSCS_CHARACTERISTIC_CONTROL_POINT_UUID                  0x2A55

/* Scan parameters service */
#define SCAN_PARAMETERS_SERVICE_NAME                            "Scan Parameters Service"
#define SCAN_PARAMETERS_SERVICE_UUID                            0x1813
#define SCAN_PARAMETERS_SERVICE_INDEX                           34

#define SPS_CHARACTERISTIC_COUNT                                2
#define SPS_CHARACTERISTIC_SCAN_INTERVAL_WINDOW                 "Scan Interval Window"
#define SPS_CHARACTERISTIC_SCAN_INTERVAL_WINDOW_UUID            0x2A4F
#define SPS_CHARACTERISTIC_SCAN_REFRESH                         "Scan Refresh"
#define SPS_CHARACTERISTIC_SCAN_REFRESH_UUID                    0x2A31

/* Transport discovery service */
#define TRANSPORT_DISCOVERY_SERVICE_NAME                        "Transport Discovery Service"
#define TRANSPORT_DISCOVERY_SERVICE_UUID                        0x1824
#define TRANSPORT_DISCOVERY_SERVICE_INDEX                       35

#define TDS_CHARACTERISTIC_COUNT                                1
#define TDS_CHARACTERISTIC_CONTROL_POINT                        "Control Point"
#define TDS_CHARACTERISTIC_CONTROL_POINT_UUID                   0x2ABC

/* Tx power service */
#define TX_POWER_SERVICE_NAME                                   "Tx Power Service"
#define TX_POWER_SERVICE_UUID                                   0x1804
#define TX_POWER_SERVICE_INDEX                                  36

#define TPS_CHARACTERISTIC_COUNT                                1
#define TPS_CHARACTERISTIC_TX_POWER_LEVEL                       "Tx Power Level"
#define TPS_CHARACTERISTIC_TX_POWER_LEVEL_UUID                  0x2A07

/* User data service */
#define USER_DATA_SERVICE_NAME                                  "User Data Service"
#define USER_DATA_SERVICE_UUID                                  0x181C
#define USER_DATA_SERVICE_INDEX                                 37

#define UDS_CHARACTERISTIC_COUNT                                31
#define UDS_CHARACTERISTIC_FIRST_NAME                           "First Name"
#define UDS_CHARACTERISTIC_FIRST_NAME_UUID                      0x2A8A
#define UDS_CHARACTERISTIC_LAST_NAME                            "Last Name"
#define UDS_CHARACTERISTIC_LAST_NAME_UUID                       0x2A90
#define UDS_CHARACTERISTIC_EMAIL_ADDRESS                        "Email Address"
#define UDS_CHARACTERISTIC_EMAIL_ADDRESS_UUID                   0x2A87
#define UDS_CHARACTERISTIC_AGE                                  "Age"
#define UDS_CHARACTERISTIC_AGE_UUID                             0x2A80
#define UDS_CHARACTERISTIC_DOB                                  "Date of Birth"
#define UDS_CHARACTERISTIC_DOB_UUID                             0x2A85
#define UDS_CHARACTERISTIC_GENDER                               "Gender"
#define UDS_CHARACTERISTIC_GENDER_UUID                          0x2A8C
#define UDS_CHARACTERISTIC_WEIGHT                               "Weight"
#define UDS_CHARACTERISTIC_WEIGHT_UUID                          0x2A98
#define UDS_CHARACTERISTIC_HEIGHT                               "Height"
#define UDS_CHARACTERISTIC_HEIGHT_UUID                          0x2A8E
#define UDS_CHARACTERISTIC_V02MAX                               "VO2 Max"
#define UDS_CHARACTERISTIC_V02MAX_UUID                          0x2A96
#define UDS_CHARACTERISTIC_HEART_RATE_MAX                       "Heart Rate Max"
#define UDS_CHARACTERISTIC_HEART_RATE_MAX_UUID                  0x2A8D
#define UDS_CHARACTERISTIC_RESETTING_HEART_RATE                 "Reseting Heart Rate"
#define UDS_CHARACTERISTIC_RESETTING_HEART_RATE_UUID            0x2A92
#define UDS_CHARACTERISTIC_MAX_RECOMMENDED_HEART_RATE           "Maximum Recommended Heart Rate"
#define UDS_CHARACTERISTIC_MAX_RECOMMENDED_HEART_RATE_UUID      0x2A91
#define UDS_CHARACTERISTIC_AEROBIC_THRESHOLD                    "Aerobic Threshold"
#define UDS_CHARACTERISTIC_AEROBIC_THRESHOLD_UUID               0x2A7F
#define UDS_CHARACTERISTIC_ANAEROBIC_THRESHOLD                  "Anaerobic Threshold"
#define UDS_CHARACTERISTIC_ANAEROBIC_THRESHOLD_UUID             0x2A83
#define UDS_CHARACTERISTIC_SPORT_TYPE                           "Sport type for Aerobic and Anaerobic Thresholds"
#define UDS_CHARACTERISTIC_SPORT_TYPE_UUID                      0x2A93
#define UDS_CHARACTERISTIC_THRESHOLD_ASSESSMENT_DATE             "Date of Threshold Assessment"
#define UDS_CHARACTERISTIC_THRESHOLD_ASSESSMENT_DATE_UUID        0x2A86
#define UDS_CHARACTERISTIC_WEIGHT_CIRCUMFERENCE                 "Weight Circumference"
#define UDS_CHARACTERISTIC_WEIGHT_CIRCUMFERENCE_UUID            0x2A97
#define UDS_CHARACTERISTIC_HIP_CIRCUMFERENCE                    "Hip Circumference"
#define UDS_CHARACTERISTIC_HIP_CIRCUMFERENCE_UUID               0x2A8F
#define UDS_CHARACTERISTIC_FAT_BURN_HR_LOWER_LIMIT              "Fat Burn Heart Rate Lower Limit"
#define UDS_CHARACTERISTIC_FAT_BURN_HR_LOWER_LIMIT_UUID         0x2A88
#define UDS_CHARACTERISTIC_FAT_BURN_HR_UPPER_LIMIT              "Fat Burn Heart Rate Upper Limit"
#define UDS_CHARACTERISTIC_FAT_BURN_HR_UPPER_LIMIT_UUID         0x2A89
#define UDS_CHARACTERISTIC_AEROBIC_HR_LOWER_LIMIT               "Aerobic Heart Rate Lower Limit"
#define UDS_CHARACTERISTIC_AEROBIC_HR_LOWER_LIMIT_UUID          0x2A7E
#define UDS_CHARACTERISTIC_AEROBIC_HR_UPPER_LIMIT               "Aerobic Heart Rate Upper Limit"
#define UDS_CHARACTERISTIC_AEROBIC_HR_UPPER_LIMIT_UUID          0x2A84
#define UDS_CHARACTERISTIC_ANAEROBIC_HR_LOWER_LIMIT             "Anaerobic Heart Rate Lower Limit"
#define UDS_CHARACTERISTIC_ANAEROBIC_HR_LOWER_LIMIT_UUID        0x2A81
#define UDS_CHARACTERISTIC_ANAEROBIC_HR_UPPER_LIMIT             "Anaerobic Heart Rate Upper Limit"
#define UDS_CHARACTERISTIC_ANAEROBIC_HR_UPPER_LIMIT_UUID        0x2A82
#define UDS_CHARACTERISTIC_FIVE_ZONE_HR_LIMITS                  "Five Zone Heart Rate Limits"
#define UDS_CHARACTERISTIC_FIVE_ZONE_HR_LIMITS_UUID             0x2A8B
#define UDS_CHARACTERISTIC_THREE_ZONE_HR_LIMITS                 "Three Zone Heart Rate Limits"
#define UDS_CHARACTERISTIC_THREE_ZONE_HR_LIMITS_UUID            0x2A94
#define UDS_CHARACTERISTIC_TWO_ZONE_HR_LIMITS                   "Two Zone Heart Rate Limits"
#define UDS_CHARACTERISTIC_TWO_ZONE_HR_LIMITS_UUID              0x2A95
#define UDS_CHARACTERISTIC_DATABASE_CHANGE_INCREMENT            "Database Change Increment"
#define UDS_CHARACTERISTIC_DATABASE_CHANGE_INCREMENT_UUID       0x2A99
#define UDS_CHARACTERISTIC_USER_INDEX                           "User Index"
#define UDS_CHARACTERISTIC_USER_INDEX_UUID                      0x2A9A
#define UDS_CHARACTERISTIC_USER_CONTROL_POINT                   "User Control Point"
#define UDS_CHARACTERISTIC_USER_CONTROL_POINT_UUID              0x2A9F
#define UDS_CHARACTERISTIC_LANGUAGE                             "Language"
#define UDS_CHARACTERISTIC_LANGUAGE_UUID                        0x2AA2

/* Weight scale service */
#define WIGHT_SCALE_SERVICE_NAME                                "Weight Scale Service"
#define WIGHT_SCALE_SERVICE_UUID                                0x181D
#define WIGHT_SCALE_SERVICE_INDEX                               38

#define WSS_CHARACTERISTIC_COUNT                                2
#define WSS_CHARACTERISTIC_FEATURE                              "WSS Feature"
#define WSS_CHARACTERISTIC_FEATURE_UUID                         0x2A9E
#define WSS_CHARACTERISTIC_MEASUREMENT                          "WSS Measurement"
#define WSS_CHARACTERISTIC_MEASUREMENT_UUID                     0x2A9D

#define EXTENDED_PROPERTIES_DESCRIPTOR_NAME                     "Extended Properties Descriptor"
#define USER_DESCRIPTION_DESCRIPTOR_NAME                        "User Description Descriptor"
#define CLIENT_CONFIG_DESCRIPTOR_NAME                           "Client Configuration Descriptor"
#define SERVER_CONFIG_DESCRIPTOR_NAME                           "Server Configuration Descriptor"
#define PRESENTATION_FORMAT_DESCRIPTOR_NAME                     "Presentation Format Descriptor"
#define AGGREGATE_FORMAT_DESCRIPTOR_NAME                        "Aggregate Format Descriptor"
#define VALID_RANGE_DESCRIPTOR_NAME                             "Valid Range Descriptor"
#define ER_REFERENCE_DESCRIPTOR_NAME                            "Environmental Sensing Reference Descriptor"
#define REPORT_REFERENCE_DESCRIPTOR_NAME                        "Report Reference Descriptor"
#define NUMBER_OF_DIGITALS_DESCRIPTOR_NAME                      "Number of Digitals Descriptor"
#define VALUE_TRIGGER_SETTING_DESCRIPTOR_NAME                   "Value Trigger Setting Descriptor"
#define ES_CONFIGURATION_DESCRIPTOR_NAME                        "Environmental Sensing Configuration Descriptor"
#define ES_MEASUREMENT_DESCRIPTOR_NAME                          "Environmental Sensing Measurement Descriptor"
#define ES_TRIGGER_SETTING_DESCRIPTOR_NAME                      "Environmental Sensing Trigger Setting DEscriptor"
#define TIME_TRIGGER_SETTING_DESCRIPTOR_NAME                    "Time Trigger Setting Descriptor"
#define DESCRIPTOR_LIST_SIZE                                    15

/* Please note that this value needs to be changed based on adding new service */
#define SERVICE_LIST_SIZE                                      (COMMON_AUDIO_SERVICE_INDEX)
#define UNKNOWN_SERVICE_NAME                                    "Unknown Service"
#define UNKNOWN_CHARACTERISTIC_NAME                             "Unknown Characteristic"
#define UNKNOWN_DESCRIPTOR_NAME                                 "Unknown Descriptor"

/* Broadcast Audio Scan Service - BASS */
#define BROADCAST_AUDIO_SCAN_SERVICE_NAME                               "Broadcast Audio Scan"
#define BROADCAST_AUDIO_SCAN_SERVICE_UUID                               0x184F
#define BROADCAST_AUDIO_SCAN_SERVICE_INDEX                              39
/* Characteristics Info */
#define BASS_CHARACTERISTIC_COUNT                                       2
#define BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT          "Broadcast Audio Scan Control Point"
#define BASS_CHARACTERISTIC_BROADCAST_AUDIO_SCAN_CONTROL_POINT_UUID     0x2BC7
#define BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE                     "Broadcast Receive State"
#define BASS_CHARACTERISTIC_BROADCAST_RECEIVE_STATE_UUID                0x2BC8

/* Audio Stream Control service - ASCS */
#define AUDIO_STRAM_CONTROL_SERVICE_NAME                                "Audio Stream Control"
#define AUDIO_STRAM_CONTROL_SERVICE_UUID                                0x184E
#define AUDIO_STRAM_CONTROL_SERVICE_INDEX                               40
/* Characteristics Info */
#define ASCS_CHARACTERISTIC_COUNT                                       3
#define ASCS_CHARACTERISTIC_AUDIO_STRAM_CONTROL_POINT                   "ASE Control Point"
#define ASCS_CHARACTERISTIC_AUDIO_STRAM_CONTROL_POINT_UUID              0x2BC6
#define ASCS_CHARACTERISTIC_SINK_AUDIO_STRAM_CONTROL                    "Sink ASE"
#define ASCS_CHARACTERISTIC_SINK_AUDIO_STRAM_CONTROL_UUID               0x2BC4
#define ASCS_CHARACTERISTIC_SOURCE_AUDIO_STRAM_CONTROL                  "Source ASE"
#define ASCS_CHARACTERISTIC_SOURCE_AUDIO_STRAM_CONTROL_UUID             0x2BC5

/* Published Audio Capabilities service - PACS */
#define PUBLISHED_AUDIO_CAPABILITIES_SERVICE_NAME                       "Published Audio Capabilities"
#define PUBLISHED_AUDIO_CAPABILITIES_SERVICE_UUID                       0x1850
#define PUBLISHED_AUDIO_CAPABILITIES_SERVICE_INDEX                      41
/* Characteristics Info */
#define PACS_CHARACTERISTIC_COUNT                                       6
#define PACS_CHARACTERISTIC_SINK_PUBLISHED_AUDIO_CAPABILITIES           "Sink PAC"
#define PACS_CHARACTERISTIC_SINK_PUBLISHED_AUDIO_CAPABILITIES_UUID      0x2BC9
#define PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION                         "Sink Audio Location"
#define PACS_CHARACTERISTIC_SINK_AUDIO_LOCATION_UUID                    0x2BCA
#define PACS_CHARACTERISTIC_SOURCE_PUBLISHED_AUDIO_CAPABILITIES         "Source PAC"
#define PACS_CHARACTERISTIC_SOURCE_PUBLISHED_AUDIO_CAPABILITIES_UUID    0x2BCB
#define PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION                       "Source Audio Location"
#define PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATION_UUID                  0x2BCC
#define PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS                    "Available Audio Contexts"
#define PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS_UUID               0x2BCD
#define PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS                    "Supported Audio Contexts"
#define PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS_UUID               0x2BCE

/* Volume Control service - VCS */
#define VOLUME_CONTROL_SERVICE_NAME                                     "Volume Control"
#define VOLUME_CONTROL_SERVICE_UUID                                     0x1844
#define VOLUME_CONTROL_SERVICE_INDEX                                    42
/* Characteristics Info */
#define VCS_CHARACTERISTIC_COUNT                                        3
#define VCS_CHARACTERISTIC_VOLUME_STATE                                 "Volume State"
#define VCS_CHARACTERISTIC_VOLUME_STATE_UUID                            0x2B7D
#define VCS_CHARACTERISTIC_VOLUME__CONTROL_POINT                        "Volume Control Point"
#define VCS_CHARACTERISTIC_VOLUME__CONTROL_POINT_UUID                   0x2B7E
#define VCS_CHARACTERISTIC_VOLUME_FLAGS                                 "Volume Flags"
#define VCS_CHARACTERISTIC_VOLUME_FLAGS_UUID                            0x2B7F

/* Coordinated Set Identification service - CSIS */
#define COORDINATED_SET_IDENTIFICATION_SERVICE_NAME                     "Coordinated Set Identification"
#define COORDINATED_SET_IDENTIFICATION_SERVICE_UUID                     0x1846
#define COORDINATED_SET_IDENTIFICATION_SERVICE_INDEX                    43
/* Characteristics Info */
#define CSIS_CHARACTERISTIC_COUNT                                       4
#define CSIS_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY                  "Set Identity Resolving Key"
#define CSIS_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_UUID             0x2B84
#define CSIS_CHARACTERISTIC_COORDINATED_SET_SIZE                        "Coordinated Set Size"
#define CSIS_CHARACTERISTIC_COORDINATED_SET_SIZE_UUID                   0x2B85
#define CSIS_CHARACTERISTIC_SET_MEMBER_LOCK                             "Set Member Lock"
#define CSIS_CHARACTERISTIC_SET_MEMBER_LOCK_UUID                        0x2B86
#define CSIS_CHARACTERISTIC_SET_MEMBER_RANK                             "Set Member Rank"
#define CSIS_CHARACTERISTIC_SET_MEMBER_RANK_UUID                        0x2B87

/* Common Audio service - CAS */
#define COMMON_AUDIO_SERVICE_NAME                                       "Common AudiO"
#define COMMON_AUDIO_SERVICE_UUID                                       0x1853
#define COMMON_AUDIO_SERVICE_INDEX                                      44

#endif /* defined(CLX_BLE_GATT_SERVICE_VERBOSE) */

#endif /* __ServiceVerbose_h__ */

