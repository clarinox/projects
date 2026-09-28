#ifndef __Gap_Ble_ChannelSounding_Api_h__
#define __Gap_Ble_ChannelSounding_Api_h__

/********************************************************************************
*
* Project             ClarinoxBlue
* File                Gap.Ble.ChannelSounding.Api.h
* Description         Declares API Functions and Definitions For Gap Ble Channel Sounding
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/**
80 bit variable with each bit representing the channels used for CS.
*/
#define CLX_GAP_CS_CHANNEL_MAP_BITS_SIZE                                                    10

/**
Length of the parameter representing subevent
*/
#define CLX_GAP_CS_SUB_EVENT_VALUE_LENGTH                                                   3

/**
Refer to #clxGapBleCsInitialize function.
*/
#define CLX_GAP_BLE_CS_INITIALIZE_COMPLETE                                                  0x7500

/**
Refer to #clxGapBleCsCreateUpdateConfig function.
*/
#define CLX_GAP_BLE_CS_CREATE_UPDATE_CONFIG_COMPLETE                                        0x7501

/**
Refer to #clxGapBleCsScheduleProcedure function.
*/
#define CLX_GAP_BLE_CS_SCHEDULE_PROCEDURE_COMPLETE                                          0x7502

/**
Refer to #clxGapBleCsRemoveConfig function.
*/
#define CLX_GAP_BLE_CS_REMOVE_CONFIG_COMPLETE                                               0x7503

/**
Refer to #clxGapBleCsSetChannelClassification function.
*/
#define CLX_GAP_BLE_CS_SET_CHANNEL_CLASSIFICATION_COMPLETE                                  0x7504

/**
This event shall be generated when the local Controller has results to the creation or updation of CS Config
The parameter of this indication is of type #clxGapBleCsConfigCompletedIndication.
*/
#define CLX_GAP_BLE_CS_CONFIG_COMPLETED_INDICATION                                          0xb500

/**
This event shall be generated when the local Controller has results to report for a CS subevent during the CS procedure.
The parameter of this indication is of type #clxGapBleCsSubEventResultIndication.
*/
#define CLX_GAP_BLE_CS_SUB_EVENT_RESULT_INDICATION                                          0xb501

/**
This event shall be generated when the local Controller has results to report for a CS subevent Continue packet during the CS procedure.
The parameter of this indication is of type #clxGapBleCsSubEventContinueResultIndication.
*/
#define CLX_GAP_BLE_CS_SUB_EVENT_CONTINUE_RESULT_INDICATION                                 0xb502

/**
Specifies the role of the local CS controller.
*/
typedef enum ClxBleCsRoleEnum
{
    ClxBleCsRole_Initiator   = 0x00,    /*!< Initiator role of CS which initiates the CS procudeure */
    ClxBleCsRole_Reflector   = 0x01     /*!< Reflector role of CS which responds to the CS procudeure */
} ClxBleCsRole;

/**
Indicates the RTT variant to be used during the CS procedure
*/
typedef enum ClxBleCsRttTypeEnum
{
    ClxBleCsRttType_AaOnly          = 0x00,    /*!< RTT AA-only */
    ClxBleCsRttType_32bitSounding   = 0x01,    /*!< RTT with 32-bit sounding sequence */
    ClxBleCsRttType_96bitSounding   = 0x02,    /*!< RTT with 96-bit sounding sequence */
    ClxBleCsRttType_32bitRandom     = 0x03,    /*!< RTT with 32-bit random sequence */
    ClxBleCsRttType_64bitRandom     = 0x04,    /*!< RTT with 64-bit random sequence */
    ClxBleCsRttType_96bitRandom     = 0x05,    /*!< RTT with 96-bit random sequence */
    ClxBleCsRttType_128bitRandom    = 0x06     /*!< RTT with 128-bit random sequence */
} ClxBleCsRttType;

/**
Specifies the PHY of the local CS controller.
*/
typedef enum ClxBleCsPhyEnum
{
    ClxBleCsPhy_Le1MPhy      = 0x01,    /*!< LE 1M PHY */
    ClxBleCsPhy_Le2MPhy      = 0x02,    /*!< LE 2M PHY */
    ClxBleCsPhy_Le2M2BtPhy   = 0x03     /*!< LE 2M 2BT PHY */
} ClxBleCsPhy;

/**
Specifies the different SNR control adjustments for Sync transmission
*/
typedef enum ClxBleCsSnrControlEnum
{
    ClxBleCsSnrControl_18dBAdjustment   = 0x00,    /*!< SNR control adjustment of 18 dB. */
    ClxBleCsSnrControl_21dBAdjustment   = 0x01,    /*!< SNR control adjustment of 21 dB. */
    ClxBleCsSnrControl_24dBAdjustment   = 0x02,    /*!< SNR control adjustment of 24 dB. */
    ClxBleCsSnrControl_27dBAdjustment   = 0x03,    /*!< SNR control adjustment of 27 dB. */
    ClxBleCsSnrControl_30dBAdjustment   = 0x04,    /*!< SNR control adjustment of 30 dB. */
    ClxBleCsSnrControl_NotApplied       = 0xFF     /*!< SNR control is not to be applied. */
} ClxBleCsSnrControl;

/**
CS modes related details
*/
typedef struct ClxBleCsModeDetailsStruct
{
    u1  mainModeType;            /*!< CS modes used during the CS procedure */
    u1  subModeType;             /*!< CS modes used during the CS procedure */
    u1  minimumMainModeSteps;    /*!< Indicate the range of main mode CS steps to be executed before a submode CS step is executed during the CS procedure */
    u1  maximumMainModeSteps;    /*!< Indicate the range of main mode CS steps to be executed before a submode CS step is executed during the CS procedure */
    u1  mainModeRepetition;      /*!< Indicates the number of main mode CS steps repeated from the last CS subevent at the beginning of the current CS subevent */
    u1  mode0Steps;              /*!< Indicates the number of mode-0 CS steps to be included at the beginning of each CS subevent. */
} ClxBleCsModeDetails;

/**
Information about the channels used in the CS procedure.
*/
typedef struct ClxBleCsChannelDetailsStruct
{
    u1  channelMap[CLX_GAP_CS_CHANNEL_MAP_BITS_SIZE];    /*!< 80 bit variable. Set 1 to enable nth channel and 0 to disable. Channels n = 0, 23, 24, 25, 77 and 78 shall be set to 0 and nit n = 79 to be set as 0xff. */
    u1  channelMapRepetition;                            /*!< Number of times the channels specified by Channel_Map are to be repeated for non-mode-0 steps */
    u1  channelSelectionType;                            /*!< The Channel Selection Algorithm to be used during the CS procedure */
    u1  ch3cShape;                                       /*!< Indicates the shape for user-specified channel sequence. Applicable only when channelSelectionType is set to 1 */
    u1  ch3cJump;                                        /*!< Indicates the number of channels skipped in each rising and falling sequence. Applicable only when channelSelectionType is set to 1 */
} ClxBleCsChannelDetails;

/**
Information about the parameters related to the CS procedure duration and interval
*/
typedef struct ClxBleCsProcedureDetailsStruct
{
    u2  maxProcedureLength;      /*!< Maximum duration for each procedure. Range: 0x0001 to 0xFFFF. Time = N x 0.625 ms */
    u2  minProcedureInterval;    /*!< Minimum number of connection events between consecutive procedures. Range: 0x0001 to 0xFFFF. */
    u2  maxProcedureInterval;    /*!< Maximum number of connection events between consecutive procedures. Range: 0x0001 to 0xFFFF. */
    u2  maxProcedureCount;       /*!< Number of procedures to be scheduled. 0x0000 to continue until disabled. */
} ClxBleCsProcedureDetails;

/**
Specifies the parameters related to the duration of each CS subevent
*/
typedef struct ClxBleCsSubEventDetailsStruct
{
    u1  minSubEventLength[CLX_GAP_CS_SUB_EVENT_VALUE_LENGTH];    /*!< Minimum suggested duration for each subevent in microseconds. Range: 1250 us to 4 s */
    u1  maxSubEventLength[CLX_GAP_CS_SUB_EVENT_VALUE_LENGTH];    /*!< Maximum suggested duration for each subevent in microseconds. Range: 1250 us to 4 s */
} ClxBleCsSubEventDetails;

/**
Information about the SNR control adjustment for Sync transmission
*/
typedef struct ClxBleCsSnrControlDetailsStruct
{
    ClxBleCsSnrControlEnum  snrControlInitiator;    /*!< SNR control adjustment for the CS_SYNC transmissions of the initiator */
    ClxBleCsSnrControlEnum  snrControlReflector;    /*!< SNR control adjustment for the CS_SYNC transmissions of the reflector */
} ClxBleCsSnrControlDetails;

/**
Information about the Step Data of Sub Event and Continue Result status
*/
typedef struct ClxBleCsSubEventStepDataDetailsStruct
{
    u1  mode;          /*!< Mode type */
    u1  channel;       /*!< Channel index */
    u1  dataLength;    /*!< Length of mode- and role-specific information being reported */
    u1  data;          /*!< Mode- and role-specific data of variable length #dataLength, starting from value present in address of #data */
} ClxBleCsSubEventStepDataDetails;

/**
Information about the Sub Event Result status
*/
typedef struct ClxBleCsSubEventResultDetailsStruct
{
    u1   procedureDoneStatus;      /*!< Status of CS done procedure */
    u1   subEventDoneStatus;       /*!< Status of CS subevent */
    u1   abortReason;              /*!< Indicates the abort reason */
    u1   numberOfAntennaPaths;     /*!< Number of antenna paths used during the phase measurement stage of the CS step */
    u1   numberOfStepsReported;    /*!< Number of steps in the CS subevent for which results are reported */
} ClxBleCsSubEventResultDetails;

/**
Data Structure for the indication #CLX_GAP_BLE_CS_CONFIG_COMPLETED_INDICATION
*/
typedef struct ClxGapBleCsConfigCompletedIndicationStruct
{
    u1                      status;                  /*!< Result of the Channel Sounding procedure completion */
    ClxBleConnectionHandle  connectionHandle;        /*!< GAP BLE ACL Connection Handle */
    u1                      configId;                /*!< Channel Sounding Configuration ID. Can be new or existing. Range: 0 to 3 */
    boolean                 created;                 /*!< TRUE if config is created, FALSE if removed */
    ClxBleCsModeDetails     modeDetails;             /*!< Mode related details. */
    ClxBleCsRoleEnum        role;                    /*!< Channel Sounding role of local controller. */
    ClxBleCsRttTypeEnum     rttType;                 /*!< Specifies the RTT variant to be used during the CS procedure */
    ClxBleCsPhyEnum         csSyncPhy;               /*!< PHY used for CS Sync */
    ClxBleCsChannelDetails  channelDetails;          /*!< Information about the channels used in the procedure. */
    u1                      interlude1Time;          /*!< Interlude time in microseconds between the CS_SYNC packets used in mode-0 and mode-1 steps */
    u1                      interlude2Time;          /*!< Interlude time in microseconds between the CS tones */
    u1                      fcsTime;                 /*!< Time in microseconds for frequency changes */
    u1                      phaseMeasurementTime;    /*!< Time in microseconds for the phase measurement period of the CS tones */
} ClxGapBleCsConfigCompletedIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_CS_SUB_EVENT_RESULT_INDICATION
*/
typedef struct ClxGapBleCsSubEventResultIndicationStruct
{
    ClxBleConnectionHandle            connectionHandle;           /*!< GAP BLE ACL Connection Handle */
    u1                                configId;                   /*!< Channel Sounding Configuration ID. Can be new or existing. Range: 0 to 3 */
    u2                                startingAclEventCounter;    /*!< Indicates the starting ACL connection event count from which the CS event results reported in this HCI event are anchored. */
    u2                                procedureCounter;           /*!< CS procedure count since completion of the Channel Sounding Security Start procedure */
    u2                                frequencyCompensation;      /*!< Frequency compensation value in units of 0.01 ppm. Range: -100 ppm (0x58F0) to +100 ppm (0x2710). Units: 0.01 ppm */
    u1                                referencePowerLevel;        /*!< Reference Power Level. Range: -127 to 20 */
    ClxBleCsSubEventResultDetails     subEventResult;             /*!< Result of the CS procedure */
    u2                                stepDataDetailsLength;      /*!< Total length of the Step Data */
    ClxBleCsSubEventStepDataDetails*  stepDataDetails;            /*!< Array of Step Data of count #subEventResult.numberOfStepsReported */
} ClxGapBleCsSubEventResultIndication;

/**
Data Structure for the indication #CLX_GAP_BLE_CS_SUB_EVENT_CONTINUE_RESULT_INDICATION
*/
typedef struct ClxGapBleCsSubEventContinueResultIndicationStruct
{
    ClxBleConnectionHandle            connectionHandle;         /*!< GAP BLE ACL Connection Handle */
    u1                                configId;                 /*!< Channel Sounding Configuration ID. Can be new or existing. Range: 0 to 3 */
    ClxBleCsSubEventResultDetails     subEventResult;           /*!< Result of the CS procedure */
    u2                                stepDataDetailsLength;    /*!< Total length of the Step Data */
    ClxBleCsSubEventStepDataDetails*  stepDataDetails;          /*!< Array of Step Data of count #subEventResult.numberOfStepsReported */
} ClxGapBleCsSubEventContinueResultIndication;

/**
This command initializes Channel Sounding (CS) for the remote device specified by the input connection handle.
During this process, the CS capabilities of both the local and remote devices are queried, and default parameters are configured with the controller

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_CS_INITIALIZE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                   Stack
\param[  in   ] connectionHandle        GAP BLE ACL Connection Handle
\param[  in   ] role                    Channel Sounding role of local controller.
\param[  in   ] csSyncAntennaSelection  The antenna identifier to be used for transmitting and receiving CS_SYNC packets. Range: 0x01 to 0x04, 0xFE - Antennas to be used, in repetitive order. 0xFF - Random
\param[  in   ] maxTxPower              The maximum transmit power level to be used for all CS transmissions. Range: -127 to 20dbm.
\param[  in   ] block                   Indicates mode of operation:TRUE : Blocking mode FALSE : Non-blocking mode

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

*/
ClxResult clxGapBleCsInitialize(_in_ ClxStack                stack,
                                _in_ ClxBleConnectionHandle  connectionHandle,
                                _in_ ClxBleCsRoleEnum        role,
                                _in_ u1                      csSyncAntennaSelection,
                                _in_ u1                      maxTxPower,
                                _in_ boolean                 block);

/**
Creates a new CS configuration or updates an existing CS configuration with the identifier Config ID on the connection identified by the Connection Handle in the local and/or the remote Controller

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_CS_CREATE_UPDATE_CONFIG_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack             Stack
\param[  in   ] connectionHandle  GAP BLE ACL Connection Handle
\param[  in   ] configId          Channel Sounding Configuration ID. Can be new or existing. Range: 0 to 3
\param[  in   ] writeContext      1 for write in local controller only, 2 for local and remote controller.
\param[  in   ] modeDetails       Mode related details.
\param[  in   ] role              Channel Sounding role of local controller.
\param[  in   ] channelDetails    Information about the channels used in the procedure.
\param[  in   ] rttType           Specifies the RTT variant to be used during the CS procedure
\param[  in   ] csSyncPhy         PHY used for CS Sync
\param[  in   ] block             Indicates mode of operation:TRUE : Blocking mode FALSE : Non-blocking mode

\return #CLX_SUCCESS if successful.
    In blocking mode, result will be returned by this function.
    In non-blocking mode, result of the actual operation will be passed to the callback function.

    Other possible return values are:

    - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
    - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
    - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
    - #CLX_ERROR_INVALID_HANDLE: Invalid handle

*/
ClxResult clxGapBleCsCreateUpdateConfig(_in_ ClxStack                            stack,
                                        _in_ ClxBleConnectionHandle              connectionHandle,
                                        _in_ u1                                  configId,
                                        _in_ u1                                  writeContext,
                                        _user_in_ const ClxBleCsModeDetails*     modeDetails,
                                        _in_ ClxBleCsRoleEnum                    role,
                                        _user_in_ const ClxBleCsChannelDetails*  channelDetails,
                                        _in_ ClxBleCsRttTypeEnum                 rttType,
                                        _in_ ClxBleCsPhyEnum                     csSyncPhy,
                                        _in_ boolean                             block);

/**
Enables or disables the local Controller's scheduling of Channel Sounding (CS) procedures with the remote device associated with the specified Connection Handle.
During this process, the local Controller configures parameters for scheduling one or more CS procedures and enables security.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_CS_SCHEDULE_PROCEDURE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack                       Stack
\param[  in   ] connectionHandle            GAP BLE ACL Connection Handle
\param[  in   ] configId                    Channel Sounding Configuration ID. Can be new or existing. Range: 0 to 3
\param[  in   ] procedureDetails            Specifies the parameters related to the CS procedure duration and interval
\param[  in   ] subeventDetails             Specifies the parameters related to the duration of each CS subevent
\param[  in   ] toneAntennaConfigSelection  Antenna configuration index, range: 0x00 to 0x07.
\param[  in   ] phy                         PHY used for CS procedure
\param[  in   ] txPowerDelta                Recommended difference between remote power level for CS tones and RTT packets and existing power level for the PHY
\param[  in   ] preferredPeerAntenna        0, 1, 2 and 3 for first, second, third and forth order antenna element.
\param[  in   ] snrDetails                  Information about the SNR control adjustment for Sync transmission.
\param[  in   ] enable                      TRUE - CS procedures are to be enabled. FALSE - CS procedures are to be disabled.
\param[  in   ] block                       Indicates mode of operation:TRUE : Blocking mode FALSE : Non-blocking mode

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

*/
ClxResult clxGapBleCsScheduleProcedure(_in_ ClxStack                               stack,
                                       _in_ ClxBleConnectionHandle                 connectionHandle,
                                       _in_ u1                                     configId,
                                       _user_in_ const ClxBleCsProcedureDetails*   procedureDetails,
                                       _user_in_ const ClxBleCsSubEventDetails*    subeventDetails,
                                       _in_ u1                                     toneAntennaConfigSelection,
                                       _in_ ClxBleCsPhyEnum                        phy,
                                       _in_ u1                                     txPowerDelta,
                                       _in_ u1                                     preferredPeerAntenna,
                                       _user_in_ const ClxBleCsSnrControlDetails*  snrDetails,
                                       _in_ boolean                                enable,
                                       _in_ boolean                                block);

/**
Removes a CS configuration identified by Config ID from the local Controller for the connection identified by the Connection Handle parameter.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                    When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_CS_REMOVE_CONFIG_COMPLETE.
                    This indication does not have any parameters.

\param[  in   ] stack             Stack
\param[  in   ] connectionHandle  GAP BLE ACL Connection Handle
\param[  in   ] configId          Channel Sounding Configuration ID
\param[  in   ] block             Indicates mode of operation:TRUE : Blocking mode FALSE : Non-blocking mode

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

*/
ClxResult clxGapBleCsRemoveConfig(_in_ ClxStack                stack,
                                  _in_ ClxBleConnectionHandle  connectionHandle,
                                  _in_ u1                      configId,
                                  _in_ boolean                 block);

/**
This command is used to update the channel classification based on its local information.

Blocking mode    : This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GAP_BLE_CS_SET_CHANNEL_CLASSIFICATION_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] stack       Stack
\param[  in   ] channelMap  80 bit variable. Set 1 to enable nth channel and 0 to disable. Channels n = 0, 23, 24, 25, 77 and 78 shall be set to 0 and nit n = 79 to be set as 0xff.
\param[  in   ] block       Indicates mode of operation:TRUE : Blocking mode FALSE : Non-blocking mode

\return #CLX_SUCCESS if successful.
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

*/
ClxResult clxGapBleCsSetChannelClassification(_in_ ClxStack        stack,
                                              _user_in_ const u1*  channelMap,
                                              _in_ boolean         block);


#ifdef __cplusplus
}
#endif



#endif // __Gap_Ble_ChannelSounding_Api_h__
