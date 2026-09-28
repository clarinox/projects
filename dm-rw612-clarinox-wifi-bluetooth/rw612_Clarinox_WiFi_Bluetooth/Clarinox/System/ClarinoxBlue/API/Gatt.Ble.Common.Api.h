#ifndef __Gatt_Ble_Common_Api_h__
#define __Gatt_Ble_Common_Api_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gatt.Ble.Common.Api.h
* Description         Declares Common API Functions and Definitions For GattBle
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#define CLX_GATT_HANDLE_SIZE                                  2                 /*!< Bytes */
#define CLX_GATT_16BIT_UUID_SIZE                              2                 /*!< Bytes */
#define CLX_GATT_128BIT_UUID_SIZE                             16                /*!< Bytes */

#define CLX_GATT_MINIMUM_MTU                                  23                /*!< Bytes */

#define CLX_GATT_MAX_DEVICE_NAME                              248               /*!< max name reserved for remote device, user cannot change this value */ 

#define CLX_GATT_CHARACTERISTICS_MAX_BUFFER_SIZE              512               /*!< max size for Characteristics value, user cannot change this value */ 

#define CLX_GATT_MAX_UUID_LENGTH                              16                /*!< max UUID is used for generic UUID definition */  


/**
Characteristic Properties:
*/
#define CLX_GATT_CHARACTERISTIC_PROPERTY_BROADCAST                      0x01
#define CLX_GATT_CHARACTERISTIC_PROPERTY_READ                           0x02
#define CLX_GATT_CHARACTERISTIC_PROPERTY_WRITE_WITHOUT_RESPONSE         0x04
#define CLX_GATT_CHARACTERISTIC_PROPERTY_WRITE                          0x08
#define CLX_GATT_CHARACTERISTIC_PROPERTY_NOTIFY                         0x10
#define CLX_GATT_CHARACTERISTIC_PROPERTY_INDICATE                       0x20
#define CLX_GATT_CHARACTERISTIC_PROPERTY_AUTHENTICATED_SIGNED_WRITES    0x40
#define CLX_GATT_CHARACTERISTIC_PROPERTY_EXTENDED                       0x80


/**
Defines UUID type
*/
typedef enum ClxGattUuidTypeEnum
{
    ClxGattUuidType_Uuid2                                   = 2,                    /*!< 2 byte Bluetooth SIG defined UUID */   
    ClxGattUuidType_Uuid4                                   = 4,                    /*!< 4 byte Bluetooth SIG defined UUID */   
    ClxGattUuidType_Uuid16                                  = 16                    /*!< 16 byte generic defined UUID */   
} ClxGattUuidType;

/**
Determines service type for related operation
*/
typedef enum ClxGattServiceTypeEnum
{
    ClxGattServiceType_Primary                              = 0x2800,               /*!< Select an operation only for primary services */
    ClxGattServiceType_Secondary                            = 0x2801,               /*!< Select an operation only for secondary services */
    ClxGattServiceType_Include                              = 0x2802,               /*!< Select an operation only for include services */
    ClxGattServiceType_Characteristics                      = 0x2803                /*!< Select an operation only for characteristics */
} ClxGattServiceType;

/**
Defines characteristics description declarations
*/
typedef enum ClxGattCharacteristicsDescriptorsEnum
{
    ClxGattCharacteristicsDescriptors_ExtendedProperties    = 0x2900,               /*!< Characteristic Extended Properties  */
    ClxGattCharacteristicsDescriptors_UserDescription       = 0x2901,               /*!< Characteristic User Description     */
    ClxGattCharacteristicsDescriptors_ClientConfiguration   = 0x2902,               /*!< Client Characteristic Configuration */
    ClxGattCharacteristicsDescriptors_ServerConfiguration   = 0x2903,               /*!< Server Characteristic Configuration */
    ClxGattCharacteristicsDescriptors_Format                = 0x2904,               /*!< Characteristic Presentation Format  */
    ClxGattCharacteristicsDescriptors_AggregateFormat       = 0x2905                /*!< Characteristic Aggregate Format     */
} ClxGattCharacteristicsDescriptors;

/**
Defines UUID structure 
NOTE : the UUID is stored in the platform's natural byte order. Use the functions clxInitGattUuid2(), clxInitGattUuid16FromBinary(), or
clxInitGattUuid16FromAscii() to store an UUID in an instance of ClxGattUuid.
*/
typedef struct ClxGattUuidStruct
{
    u4                  value[CLX_GATT_MAX_UUID_LENGTH/4];
    ClxGattUuidType     type;
} ClxGattUuid;


/**
FLOAT type as defined by the ISO/IEEE Std. 11073-20601-2008 standard.
*/
typedef struct ClxFloatStruct
{
    s1 exponent;                /*!< 8-bit signed exponent (-128 through +127) to base 10 */
    s4 mantissa;                /*!< 32-bit signed integer (-2,147,483,648 through +2,147,483,647) */
} ClxFloat;

#define CLX_FLOAT_VALUE_PLUS_INFINITY               0x007FFFFE          /*!< exponent 0, mantissa +(2^23 -2) */
#define CLX_FLOAT_VALUE_MINUS_INFINITY              0x00800002          /*!< exponent 0, mantissa -(2^23 -2) */
#define CLX_FLOAT_VALUE_NOT_A_NUMBER                0x007FFFFF          /*!< exponent 0, mantissa +(2^23 -1) */
#define CLX_FLOAT_VALUE_NOT_AT_THIS_RESOLUTION      0x00800000          /*!< exponent 0, mantissa -(2^23) */

/**
Encodes a FLOAT value of type ClxFloat to a u4 integer.

\param[ in ] input The FLOAT value to be encoded

\return the FLOAT value in the encoded format, as a u4 integer.
*/
extern u4 clxEncodeFloat(const ClxFloat* input);

/**
Extracts the exponent and mantissa components of a FLOAT value from a FLOAT-encoded u4 integer.

\param[ in ] encodedValue The FLOAT value in the encoded format.
\param[ out ] output The output structure which on return will contain the exponent and mantissa of the FLOAT value.
*/
extern void clxDecodeFloat(u4 encodedValue, ClxFloat* output);


/**
SFLOAT type as defined by the ISO/IEEE Std. 11073-20601-2008 standard.
*/
typedef struct ClxSFloatStruct
{
    s1 exponent;            /*!< 4-bit signed exponent (-8 through +7) to base 10  */
    s2 mantissa;            /*!< 12-bit signed integer (-2,048 through +2,047) */
} ClxSFloat;


#define CLX_SFLOAT_VALUE_PLUS_INFINITY               0x07FE          /*!< exponent 0, mantissa +(2^11 -2) */
#define CLX_SFLOAT_VALUE_MINUS_INFINITY              0x0802          /*!< exponent 0, mantissa -(2^11 -2) */
#define CLX_SFLOAT_VALUE_NOT_A_NUMBER                0x07FF          /*!< exponent 0, mantissa +(2^11 -1) */
#define CLX_SFLOAT_VALUE_NOT_AT_THIS_RESOLUTION      0x0800          /*!< exponent 0, mantissa -(2^11) */

/**
Encodes a SFLOAT value of type ClxFloat to a u4 integer.

\param[ in ] input The SFLOAT value to be encoded

\return the SFLOAT value in the encoded format, as a u4 integer.
*/
extern u2 clxEncodeSFloat(const ClxSFloat* input);

/**
Extracts the exponent and mantissa components of a SFLOAT value from a SFLOAT-encoded u4 integer.

\param[ in ] encodedValue The SFLOAT value in the encoded format.
\param[ out ] output The output structure which on return will contain the exponent and mantissa of the SFLOAT value.
*/
extern void clxDecodeSFloat(u2 encodedValue, ClxSFloat* output);



/**
Defines appearance UUID values
*/
typedef enum ClxGattGapAppearanceEnum
{
    ClxGattGapAppearance_Unknown                                     = 0,                   /*!< None                            */
    ClxGattGapAppearance_GenericPhone                                = 64,                  /*!< Generic category                */
    ClxGattGapAppearance_GenericComputer                             = 128,                 /*!< Generic category                */
    ClxGattGapAppearance_GenericWatch                                = 192,                 /*!< Generic category                */
    ClxGattGapAppearance_SportsWatch                                 = 193,                 /*!< Watch subtype                   */
    ClxGattGapAppearance_GenericClock                                = 256,                 /*!< Generic category                */
    ClxGattGapAppearance_GenericDisplay                              = 320,                 /*!< Generic category                */
    ClxGattGapAppearance_GenericRemoteControl                        = 384,                 /*!< Generic category                */
    ClxGattGapAppearance_GenericEyeGlasses                           = 448,                 /*!< Generic category                */
    ClxGattGapAppearance_GenericTag                                  = 512,                 /*!< Generic category                */
    ClxGattGapAppearance_GenericKeyring                              = 576,                 /*!< Generic category                */
    ClxGattGapAppearance_GenericMediaPlayer                          = 640,                 /*!< Generic category                */
    ClxGattGapAppearance_GenericBarcodeScanner                       = 704,                 /*!< Generic category                */
    ClxGattGapAppearance_GenericThermometer                          = 768,                 /*!< Generic category                */
    ClxGattGapAppearance_ThermometerEar                              = 769,                 /*!< Thermometer subtype             */
    ClxGattGapAppearance_GenericHeartRateSensor                      = 832,                 /*!< Generic category                */
    ClxGattGapAppearance_HeartRateSensorHeartRateBelt                = 833,                 /*!< Heart Rate Sensor subtype       */
    ClxGattGapAppearance_GenericBloodPressure                        = 896,                 /*!< Generic category                */
    ClxGattGapAppearance_BloodPressureArm                            = 897,                 /*!< Blood Pressure subtype          */
    ClxGattGapAppearance_BloodPressureWrist                          = 898,                 /*!< Blood Pressure subtype          */
    ClxGattGapAppearance_HumanInterfaceDevice                        = 960,                 /*!< HID Generic                     */
    ClxGattGapAppearance_Keyboard                                    = 961,                 /*!< HID subtype                     */
    ClxGattGapAppearance_Mouse                                       = 962,                 /*!< HID subtype                     */
    ClxGattGapAppearance_Joystick                                    = 963,                 /*!< HID subtype                     */
    ClxGattGapAppearance_Gamepad                                     = 964,                 /*!< HID subtype                     */
    ClxGattGapAppearance_DigitizerTablet                             = 965,                 /*!< HID subtype                     */
    ClxGattGapAppearance_CardReader                                  = 966,                 /*!< HID subtype                     */
    ClxGattGapAppearance_DigitalPen                                  = 967,                 /*!< HID subtype                     */
    ClxGattGapAppearance_BarcodeScanner                              = 968,                 /*!< HID subtype                     */
    ClxGattGapAppearance_GenericGlucoseMeter                         = 1024,                /*!< Generic category                */
    ClxGattGapAppearance_GenericRunningWalkingSensor                 = 1088,                /*!< Generic category                */
    ClxGattGapAppearance_RunningWalkingSensorInShoe                  = 1089,                /*!< Running Walking Sensor subtype  */
    ClxGattGapAppearance_RunningWalkingSensorOnShoe                  = 1090,                /*!< Running Walking Sensor subtype  */
    ClxGattGapAppearance_RunningWalkingSensorOnHip                   = 1091,                /*!< Running Walking Sensor subtype  */
    ClxGattGapAppearance_CyclingGeneric                              = 1152,                /*!< Generic category                */
    ClxGattGapAppearance_CyclingComputer                             = 1153,                /*!< Cycling subtype                 */
    ClxGattGapAppearance_CyclingSpeedSensor                          = 1154,                /*!< Cycling subtype                 */
    ClxGattGapAppearance_CyclingCadenceSensor                        = 1155,                /*!< Cycling subtype                 */
    ClxGattGapAppearance_CyclingPowerSensor                          = 1156,                /*!< Cycling subtype                 */
    ClxGattGapAppearance_CyclingSpeedCadenceSensor                   = 1157,                /*!< Cycling subtype                 */
    ClxGattGapAppearance_PulsOximeterGeneric                         = 3136,                /*!< Pulse Oximeter subtype          */
    ClxGattGapAppearance_Fingertip                                   = 3137,                /*!< Pulse Oximeter subtype          */
    ClxGattGapAppearance_WristWorn                                   = 3138,                /*!< Pulse Oximeter subtype          */
    ClxGattGapAppearance_OutdoorSportsGeneric                        = 5184,                /*!< Outdoor Sports Activity subtype */
    ClxGattGapAppearance_LocationDisplayDevice                       = 5185,                /*!< Outdoor Sports Activity subtype */
    ClxGattGapAppearance_LocationNavigationDisplayDevice             = 5186,                /*!< Outdoor Sports Activity subtype */
    ClxGattGapAppearance_LocationPod                                 = 5187,                /*!< Outdoor Sports Activity subtype */
    ClxGattGapAppearance_LocationNavigationPod                       = 5188                 /*!< Outdoor Sports Activity subtype */
} ClxGattGapAppearance;

/**
Defines BLE Service UUID Codes
*/
enum BleServiceUuidEnum
{
    BLE_SERVICE_ALERT_NOTIFICATION                                   =  0x1811,             /*!< Alert Notification Service      */
    BLE_SERVICE_BATTERY                                              =  0x180F,             /*!< Battery Service                 */
    BLE_SERVICE_BLOOD_PRESSURE                                       =  0x1810,               /*!< Blood Pressure                  */ 
    BLE_SERVICE_CURRENT_TIME                                         =  0x1805,             /*!< Current Time Service            */
    BLE_SERVICE_CYCLING_POWER                                        =  0x1818,             /*!< Cycling Power                   */ 
    BLE_SERVICE_CYCLING_SPEED_AND_CADENCE                            =  0x1816,             /*!< Cycling Speed and Cadence       */
    BLE_SERVICE_DEVICE_INFORMATION                                   =  0x180A,             /*!< Device Information              */ 
    BLE_SERVICE_GENERIC_ACCESS                                       =  0x1800,             /*!< Generic Access                  */ 
    BLE_SERVICE_GENERIC_ATTRIBUTE                                    =  0x1801,             /*!< Generic Attribute               */ 
    BLE_SERVICE_GLUCOSE                                              =  0x1808,             /*!< Glucose                         */        
    BLE_SERVICE_HEALTH_THERMOMETER                                   =  0x1809,             /*!< Health Thermometer              */ 
    BLE_SERVICE_HEART_RATE                                           =  0x180D,             /*!< Heart Rate                      */      
    BLE_SERVICE_HUMAN_INTERFACE_DEVICE                               =  0x1812,             /*!< Human Interface Device          */ 
    BLE_SERVICE_IMMEDIATE_ALERT                                      =  0x1802,             /*!< Immediate Alert                 */ 
    BLE_SERVICE_LINK_LOSS                                            =  0x1803,             /*!< Link Loss                       */      
    BLE_SERVICE_LOCATION_AND_NAVIGATION                              =  0x1819,             /*!< Location and Navigation         */ 
    BLE_SERVICE_NEXT_DST_CHANGE                                      =  0x1807,             /*!< Next DST Change Service         */
    BLE_SERVICE_PHONE_ALERT_STATUS                                   =  0x180E,             /*!< Phone Alert Status Service      */
    BLE_SERVICE_REFERENCE_TIME_UPDATE                                =  0x1806,             /*!< Reference Time Update Service   */
    BLE_SERVICE_RUNNING_SPEED_AND_CADENCE                            =  0x1814,             /*!< Running Speed and Cadence       */
    BLE_SERVICE_SCAN_PARAMETERS                                      =  0x1813,             /*!< Scan Parameters                 */ 
    BLE_SERVICE_TX_POWER                                             =  0x1804,             /*!< Tx Power                        */        
    BLE_SERVICE_USER_DATA                                            =  0x181C              /*!< User Data                       */
};                                                                                                                                 

#ifdef __cplusplus
}
#endif

#endif  // __Gatt_Ble_Common_Api_h__

