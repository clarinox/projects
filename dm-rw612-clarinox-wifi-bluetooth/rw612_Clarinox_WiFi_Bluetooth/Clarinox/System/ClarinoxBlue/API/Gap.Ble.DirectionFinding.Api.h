#ifndef __GAP_BLE_DIRECTIONFINDING_API_h__
#define __GAP_BLE_DIRECTIONFINDING_API_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                Gap.Ble.DirectionFinding.Api.h
* Description         Declares API Functions and Definitions For Gap Ble DirectionFinding
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#include "Gap.Ble.Api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
Refer to #clxGapBleEnableDisableConnectionlessCteTransmission function.
*/
#define CLX_GAP_BLE_ENABLE_DISABLE_CONNECTIONLESS_CTE_TRANSMISSION_COMPLETE                 0x7400

/**
Refer to #clxGapBleEnableCapturingConnectionlessIqSamples function.
*/
#define CLX_GAP_BLE_ENABLE_CAPTURING_CONNECTIONLESS_IQ_SAMPLES_COMPLETE                     0x7401

/**
Refer to #clxGapBleDisableCapturingConnectionlessIqSamples function.
*/
#define CLX_GAP_BLE_DISABLE_CAPTURING_CONNECTIONLESS_IQ_SAMPLES_COMPLETE                    0x7402

/**
Refer to #clxGapBleSetConnectionCteParameters function.
*/
#define CLX_GAP_BLE_SET_CONNECTION_CTE_PARAMETERS_COMPLETE                                  0x7403

/**
Refer to #clxGapBleConnectionCteRequestEnableDisable function.
*/
#define CLX_GAP_BLE_CONNECTION_CTE_REQUEST_ENABLE_DISABLE_COMPLETE                          0x7404

/**
Refer to #clxGapBleConnectionCteResponseEnableDisable function.
*/
#define CLX_GAP_BLE_CONNECTION_CTE_RESPONSE_ENABLE_DISABLE_COMPLETE                         0x7405

/**
Refer to #clxGapBleReadAntennaInformation function.
*/
#define CLX_GAP_BLE_READ_ANTENNA_INFORMATION_COMPLETE                                       0x7406

/**
This indication is received when controller reports IQ information from the Constant Tone Extension which is part of the periodic advertising packet is received from the advertiser identified by provided sync handle.
Connectionless IQ report reception shall be enabled using API #clxGapBleEnableCapturingConnectionlessIqSamples in order to receive the reports via this indication.
The parameter of this indication is of type #ClxGapBleConnectionlessIqReportIndication.
*/
#define CLX_GAP_BLE_CONNECTIONLESS_IQ_REPORT_INDICATION                                     0xb400

/**
This indication is received when controller reports IQ information from the Constant Tone Extension of a received packet from the advertiser identified by provided connection handle.
Connection IQ report reception shall be enabled using API #clxGapBleConnectionCteRequestEnableDisable in order to receive the reports via this indication.
A Controller is not required to generate this event for packets that have a bad CRC.
The parameter of this indication is of type #ClxGapBleConnectionIqReportIndication.
*/
#define CLX_GAP_BLE_CONNECTION_IQ_REPORT_INDICATION                                         0xb401

/**
This indication is received if the peer rejects the request to enable CTE request.
CTE request is initiated by the controller to the peer device using API #clxGapBleConnectionCteRequestEnableDisable.
The parameter of this indication is of type #ClxGapBleCteRequestFailedIndication.
*/
#define CLX_GAP_BLE_CTE_REQUEST_FAILED_INDICATION                                           0xb402

/**
Specifies the type of CTE (Constant Tone Extension)
*/
typedef enum ClxBleCteTypeEnum
{
    ClxBleCteType_AoAConstantToneExtension           = 0x00,              /*!< AoA Constant Tone Extension */
    ClxBleCteType_AoDConstantToneExtension_1uS_Slots = 0x01,              /*!< AoD Constant Tone Extension with 1 s slots */
    ClxBleCteType_AoDConstantToneExtension_2uS_Slots = 0x02,              /*!< AoD Constant Tone Extension with 2 s slots */
    ClxBleCteType_UnknownAoAConstantToneExtension    = 0xFF               /*!< No Constant Tone Extension */
} ClxBleCteType;

/**
Specifies the switching and sampling slots of CTE in a periodic advertising train
*/
typedef enum ClxBleCteSamplingSlotsEnum
{
    ClxBleCteSamplingSlots_1us_Each = 0x01,    /*!< Switching and sampling slots are 1 s each */
    ClxBleCteSamplingSlots_2us_Each = 0x02     /*!< Switching and sampling slots are 2 s each */
} ClxBleCteSamplingSlots;

/**
Specifies the switching sampling rates of CTE
*/
typedef enum ClxBleSwitchingSamplingRatesEnum
{
    ClxBleSwitchingSamplingRates_1us_AodSwitching         = 0x01,            /*!< 1 s switching supported for AoD transmission */
    ClxBleSwitchingSamplingRates_1us_AodSampling          = 0x02,            /*!< 1 s sampling supported for AoD reception */
    ClxBleSwitchingSamplingRates_1us_AoaSwitchingSampling = 0x04             /*!< 1 s switching and sampling supported for AoA reception */
} ClxBleSwitchingSamplingRates;

/**
Specifies the sync type of CTE in periodic advertising to synchronize to
*/
typedef enum ClxBleSyncCteTypeEnum
{
    ClxBleSyncCteType_DontSyncWithAoA                 = 0x01,    /*!< Do not sync to packets with an AoA Constant Tone Extension. Ignore given Advertising SID and other parameters and continue. */
    ClxBleSyncCteType_DontSyncWithAoDSlot1Microsecond = 0x02,    /*!< Do not sync to packets with an AoD Constant Tone Extension with 1 s slots */
    ClxBleSyncCteType_DontSyncWithAoDSlot2Microsecond = 0x04,    /*!< Do not sync to packets with an AoD Constant Tone Extension with 2 s slots */
    ClxBleSyncCteType_DontSyncWithType3Cte            = 0x08     /*!< Do not sync to packets with a type 3 Constant Tone Extension (currently reserved for future use) */
} ClxBleSyncCteType;

/**
Specifies the status of the packet that was received from controller during periodic advertising
*/
typedef enum ClxBleCtePacketStatusEnum
{
    ClxBleCtePacketStatus_CorrectCrc                    = 0x00,        /*!< CRC of the packet is correct */
    ClxBleCtePacketStatus_IncorrectCrcCteTimeUsed       = 0x01,        /*!< Incorrect CRC, controller determines sampling points using length and CTE time field */
    ClxBleCtePacketStatus_IncorrectCrcCtePositionUsed   = 0x02,        /*!< Incorrect CRC, controller determines length and position of CTE in some other way */
    ClxBleCtePacketStatus_InsufficientResources         = 0xFF         /*!< Sampling not taken due to insufficient resources */
} ClxBleCtePacketStatus;

/**
Details required to set connection CTE receive parameters.
*/
typedef struct ClxBleConnectionCteReceiveParametersStruct
{
    ClxBleCteSamplingSlots  switchingSamplingSlots;    /*!< Slots for switching and sampling duration. */
    boolean                 isEnableSampling;          /*!< TRUE to enable controller to sample CTE, FALSE to disable sampling. */
} ClxBleConnectionCteReceiveParameters;

/**
Details required to set connection CTE transmit parameters.
*/
typedef struct ClxBleConnectionCteTransmitParametersStruct
{
    ClxBleCteType  cteType;    /*!< Type of CTE to set */
} ClxBleConnectionCteTransmitParameters;

/**
Details required to request connection CTE on the controller.
*/
typedef struct ClxBleConnectionCteRequestParametersStruct
{
    u2             cteConnectionInterval;    /*!< Requested connection interval for initiating CTE. 0 to initiate once at the earliest, 0x0001 to 0xFFFF interval to initiate periodically */
    u1             cteLength;                /*!< Constant Tone Extension length in 8 s units. Range:- 0x02 to 0x14. */
    ClxBleCteType  cteType;                  /*!< Type of CTE to enable. */
} ClxBleConnectionCteRequestParameters;

/**
Data Structure for the indication #CLX_GAP_BLE_READ_ANTENNA_INFORMATION_COMPLETE
*/
typedef struct ClxGapBleReadAntennaInformationCompleteStruct
{
    _user_out_ ClxBleSwitchingSamplingRates* switchingSamplingRates;       /*!< Switching sampling rates supported by Controller. */
    _user_out_ u1*                           numberOfAntennae;             /*!< Number of Antennae supported by controller. Range: 0x01 to 0x4B. */
    _user_out_ u1*                           maxSwitchingPatternLength;    /*!< Maximum length of antenna switching pattern supported by the Controller. Range: 0x02 to 0x4B. */
    _user_out_ u1*                           cteLength;                    /*!< Constant Tone Extension length in 8 s units. Range:- 0x02 to 0x14. */
} ClxGapBleReadAntennaInformationComplete;

/**
Data Structure for the indication #CLX_GAP_BLE_CONNECTIONLESS_IQ_REPORT_INDICATION
*/
typedef struct ClxGapBleConnectionlessIqReportIndicationStruct
{
    u2                      syncHandle;              /*!< Handle identifying the periodic advertising train */
    u1                      channelIndex;            /*!< Index of channel in which the packet was received */
    s2                      rssi;                    /*!< RSSI value for the packet. Range: -1270 to +200, Units: 0.1 dBm. */
    u1                      rssiAntennaId;           /*!< ID of the antenna. */
    ClxBleCteType           cteType;                 /*!< Specifies the type CTE (Constant Tone Extension) */
    ClxBleCteSamplingSlots  slotDurations;           /*!< Sampling rate used by the controller. */
    ClxBleCtePacketStatus   packetStatus;            /*!< Indicates if packet has a valid CRC or controller computed the position and size of CTE */
    u2                      periodicEventCounter;    /*!< Event counter, controller increments this counter by one for every periodic advertising interval */
    u1                      sampleCount;             /*!< Number of I and Q samples captured within the packet. 0 if no samples provided, otherwise 0x09 - 0x52 */
    u1*                     iSample;                 /*!< List of I samples (signed 1 byte values) for the reported packet in the order of sampling points within the packet */
    u1*                     qSample;                 /*!< List of Q samples (signed 1 byte values) for the reported packet in the order of sampling points within the packet */
} ClxGapBleConnectionlessIqReportIndication;


/**
Data Structure for the indication #CLX_GAP_BLE_CONNECTION_IQ_REPORT_INDICATION
*/
typedef struct ClxGapBleConnectionIqReportIndicationStruct
{
    u2                      connectionHandle;          /*!< Connection Handle that corresponds to the reported information */
    ClxBlePhyType           receiverPhy;               /*!< PHY in which the packet is received */
    u1                      dataChannelIndex;          /*!< Index of data channel in which the data physical channel PDU was received. Range:- 0x00 to 0x24 */
    s2                      rssi;                      /*!< RSSI value for the packet. Range: -1270 to +200, Units: 0.1 dBm */
    u1                      rssiAntennaId;             /*!< ID of the antenna in which the RSSI was measured */
    ClxBleCteType           cteType;                   /*!< Specifies the type CTE (Constant Tone Extension) */
    ClxBleCteSamplingSlots  slotDurations;             /*!< Sampling rate used by the controller. */
    ClxBleCtePacketStatus   packetStatus;              /*!< Indicates if packet has a valid CRC or controller computed the position and size of CTE */
    u2                      connectionEventCounter;    /*!< Event counter, controller increments this counter by one for every periodic advertising interval */
    u1                      sampleCount;               /*!< Number of I and Q samples captured within the packet. 0 if no samples provided, otherwise 0x09 - 0x52 */
    u1*                     iSample;                   /*!< List of I samples (signed 1 byte values) for the reported packet in the order of sampling points within the packet */
    u1*                     qSample;                   /*!< List of Q samples (signed 1 byte values) for the reported packet in the order of sampling points within the packet */
} ClxGapBleConnectionIqReportIndication;


/**
Data Structure for the indication #CLX_GAP_BLE_CTE_REQUEST_FAILED_INDICATION
*/
typedef struct ClxGapBleCteRequestFailedIndicationStruct
{
    u1  status;              /*!< 0x00 if response is received for the request otherwise, the appropriate error code */
    u2  connectionHandle;    /*!< Connection Handle that corresponds to the reported information */
} ClxGapBleCteRequestFailedIndication;

/**
Set Connection CTE receive or transmit parameters on the connection identified by the given connection handle.
Setting connection CTE receive parameters enables/disables sampling received constant tone extension.

NOTE: Any one of the receive or transmit parameters shall be set at any time and not both.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_SET_CONNECTION_CTE_PARAMETERS_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack               Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle    Handle identifying the connection. Range: 0x0000 to 0x0EFF.
\param[  in   ] numberOfAntennae    Number of Antennae in the switching pattern. Range: 0x02 to 0x4B.
\param[  in   ] antennaIds          IDs of the list of antennae.
\param[  in   ] receiveParameters   Receive parameters. NULL if transmit parameters are set.
\param[  in   ] transmitParameters  Transmit parameters. NULL if receive parameters are set.
\param[  in   ] block               Type of the operation.
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

        - #CLX_ERROR_HCI_COMMAND_DISALLOWED: When the CTE responses have already been enabled.
        - #CLX_ERROR_HCI_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE: When numberOfAntenne is greater than those supported or when given switching slot duration is not supported by Controller
                                                    or if any of the antennaIds doesn't identify an antenna or if cteType is not supported by Controller
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleSetConnectionCteParameters(_in_ ClxStack   stack,
                                              _in_ u2                                                 connectionHandle,
                                              _in_ u1                                                 numberOfAntennae,
                                              _user_in_ const u1*                                     antennaIds,
                                              _user_in_ const ClxBleConnectionCteReceiveParameters*   receiveParameters,
                                              _user_in_ const ClxBleConnectionCteTransmitParameters*  transmitParameters,
                                              _in_ boolean                                            block);


/**
Start or stop Connection CTE request procedure on the connection identified by the given connection handle.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_CONNECTION_CTE_REQUEST_ENABLE_DISABLE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                    Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle         Handle identifying the connection. Range: 0x0000 to 0x0EFF.
\param[  in   ] enableRequestParameters  Parameters to enable CTE request procedure. NULL to disable or stop the request procedure.
\param[  in   ] block                    Type of the operation.
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

        - #CLX_ERROR_HCI_COMMAND_DISALLOWED: When the CTE responses have already been enabled.
        - #CLX_ERROR_HCI_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE: When numberOfAntenne is greater than those supported or when given switching slot duration is not supported by Controller
                                                    or if any of the antennaIds doesn't identify an antenna or if cteType is not supported by Controller
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleConnectionCteRequestEnableDisable(_in_ ClxStack                                          stack,
                                                     _in_ u2                                                connectionHandle,
                                                     _user_in_ const ClxBleConnectionCteRequestParameters*  enableRequestParameters,
                                                     _in_ boolean                                           block);

/**
Request controller to respond/stop responding to Connection CTE requests on the connection identified by the given connection handle.

NOTE: API #clxGapBleSetConnectionCteParameters (for transmit parameters) shall be called atleast once before calling this API.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_CONNECTION_CTE_RESPONSE_ENABLE_DISABLE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack             Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] connectionHandle  Handle identifying the connection. Range: 0x0000 to 0x0EFF.
\param[  in   ] isEnable          TRUE to enable response, FALSE to disable responding to CTE requests.
\param[  in   ] block             Type of the operation.
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

        - #CLX_ERROR_HCI_COMMAND_DISALLOWED: When the CTE transmit parameters are not set prior or if the PHY doesn't allow CTE.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleConnectionCteResponseEnableDisable(_in_ ClxStack  stack,
                                                      _in_ u2        connectionHandle,
                                                      _in_ boolean   isEnable,
                                                      _in_ boolean   block);

/**
Read details about antenna supported by the controller.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_READ_ANTENNA_INFORMATION_COMPLETE.
                   The parameter of this indication is of type #ClxGapBleReadAntennaInformationComplete.

\param[  in   ] stack                      Local device stack handle. A stack object must be created before a GAP API used.
\param[  out  ] switchingSamplingRates     Switching sampling rates supported by Controller.
\param[  out  ] numberOfAntennae           Number of Antennae supported by controller. Range: 0x01 to 0x4B.
\param[  out  ] maxSwitchingPatternLength  Maximum length of antenna switching pattern supported by the Controller. Range: 0x02 to 0x4B.
\param[  out  ] cteLength                  Constant Tone Extension length in 8 s units. Range:- 0x02 to 0x14.
\param[  in   ] block                      Type of the operation.
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

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleReadAntennaInformation(_in_ ClxStack                             stack,
                                          _user_out_ ClxBleSwitchingSamplingRates*  switchingSamplingRates,
                                          _user_out_ u1*                            numberOfAntennae,
                                          _user_out_ u1*                            maxSwitchingPatternLength,
                                          _user_out_ u1*                            cteLength,
                                          _in_ boolean                              block);



/**
Sets connectionless CTE transmit parameters and enable/disable transmission of Constant Tone Extension (CTE).
A valid advertising set handle has to be passed to the API.

NOTE: Before calling this API, Extended advertising and Periodic advertising parameters has to set successfully.

NOTE: numberOfAntennae and antennaIds are applicable only for CTE type AoD.

NOTE: The sequence of events to enable controller to advertise with Constant Tone Extension are;.
- Set extended advertising parameters
- Set periodic advertising parameters
- Set connectionless CTE transmit parameters
- Enable CTE transmission
- Enable periodic advertising
- Enable extended advertising
- Set periodic advertising data

Once enabled, the Controller shall continue advertising with Constant Tone Extensions under following conditions;.
- CTE transmission is disabled but periodic advertising is allowed to continue..
- If periodic advertising is disabled and re-enabled.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_ENABLE_DISABLE_CONNECTIONLESS_CTE_TRANSMISSION_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                      Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] existingAdvertisingHandle  The handle to an existing extended advertising set.
\param[  in   ] cteLength                  Constant Tone Extension length in 8 s units. Range:- 0x02 to 0x14.
\param[  in   ] cteType                    Type of CTE to enable or disable.
\param[  in   ] numberOfCtePerInterval     The number of Constant Tone Extensions to transmit in each periodic advertising interval. Range: 0x01 to 0x10.
\param[  in   ] numberOfAntennae           Number of Antennae in the switching pattern. Range: 0x02 to 0x4B.
\param[  in   ] antennaIds                 IDs of the list of antennae.
\param[  in   ] isEnable                   TRUE to enable advertising CTE. FALSE to disable advertising CTE.
\param[  in   ] block                      Type of the operation.
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

        - #CLX_ERROR_HCI_COMMAND_DISALLOWED: When CTE is already enabled or if periodic advertising parameters are not set prior to this command or if PHY doesn't support CTE.
        - #CLX_ERROR_HCI_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE: When cteLength or numberOfAntenne is greater than those supported or when given CTE type is not supported by Controller or Controller is unable to schedule CTE_Count packets in each event or if any of the antennaIds doesn't identify an antenna.
        - #CLX_ERROR_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE: Advertising set corresponding to the Advertising_Handle parameter does not exist/invalid.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleEnableDisableConnectionlessCteTransmission(_in_ ClxStack                         stack,
                                                              _in_ ClxBleExtendedAdvertisingHandle  existingAdvertisingHandle,
                                                              _in_ u1                               cteLength,
                                                              _in_ ClxBleCteType                    cteType,
                                                              _in_ u1                               numberOfCtePerInterval,
                                                              _in_ u1                               numberOfAntennae,
                                                              _user_in_ const u1*                   antennaIds,
                                                              _in_ boolean                          isEnable,
                                                              _in_ boolean                          block);

/**
Enables connectionless IQ sample capturing from the periodic advertising train specified by the given sync handle.
The Controller starts to capture IQ samples from the periodic advertising train.

NOTE: switchingSamplingSlots, numberOfAntennae and antennaIds are only applicable while receiving CTE type AoA.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_ENABLE_CAPTURING_CONNECTIONLESS_IQ_SAMPLES_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                   Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] syncHandle              Handle identifying the periodic advertising train.
\param[  in   ] switchingSamplingSlots  Slots for switching and sampling duration.
\param[  in   ] maxNumberOfCteToSample  0 to sample and report all available CTE. Otherwise, the given number of samples to be captured at the maximum. Range: 0x00 to 0x10.
\param[  in   ] numberOfAntennae        Number of Antennae in the switching pattern. Range: 0x02 to 0x4B.
\param[  in   ] antennaIds              IDs of the list of antennae.
\param[  in   ] block                   Type of the operation. 
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

        - #CLX_ERROR_HCI_COMMAND_DISALLOWED: If periodic advertising is on a PHY that doesn't allow CTE .
        - #CLX_ERROR_HCI_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE: When numberOfAntenne is greater than those supported or when given switching slot duration is not supported by Controller or if any of the antennaIds doesn't identify an antenna.
        - #CLX_ERROR_BLE_INVALID_EXTENDED_ADVERTISING_HANDLE: Advertising set corresponding to the Advertising_Handle parameter does not exist/invalid.
        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleEnableCapturingConnectionlessIqSamples(_in_ ClxStack                stack,
                                                          _in_ u2                      syncHandle,
                                                          _in_ ClxBleCteSamplingSlots  switchingSamplingSlots,
                                                          _in_ u1                      maxNumberOfCteToSample,
                                                          _in_ u1                      numberOfAntennae,
                                                          _user_in_ const u1*          antennaIds,
                                                          _in_ boolean                 block);

/**
Disables connectionless IQ sample capturing from the periodic advertising train specified by the given sync handle.
The Controller stops to capture IQ samples from the periodic advertising train.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_DISABLE_CAPTURING_CONNECTIONLESS_IQ_SAMPLES_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack       Local device stack handle. A stack object must be created before a GAP API used.
\param[  in   ] syncHandle  Handle identifying the periodic advertising train.
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

        - #CLX_CLARINOX_BLUE_HCI_ERROR_CODE_BASE+n: HCI error 'n' was received from the Bluetooth controller. For detailed list of
                                                    any HCI errors (CLX_ERROR_HCI_*) please refer to 'ClarinoxBlue Error codes' page of API documentation.
*/
ClxResult clxGapBleDisableCapturingConnectionlessIqSamples(_in_ ClxStack  stack,
                                                           _in_ u2        syncHandle,
                                                           _in_ boolean   block);

#ifdef __cplusplus
}
#endif

#endif // __GAP_BLE_DIRECTIONFINDING_API_h__
