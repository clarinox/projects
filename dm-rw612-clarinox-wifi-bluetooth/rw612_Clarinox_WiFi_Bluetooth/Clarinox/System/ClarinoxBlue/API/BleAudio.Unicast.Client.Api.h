#ifndef __BleAudio_Unicast_Client_Api_h__
#define __BleAudio_Unicast_Client_Api_h__

/*******************************************************************************
*
* Project             ClarinoxBlue
* File                BleAudio.Unicast.Client.Api.h
* Description         Declares API Functions and Definitions For BleAudioUnicastClient
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/**
Refer to #clxBleAudioGetAudioCapabilities function.
*/
#define CLX_BLE_AUDIO_GET_AUDIO_CAPABILITIES_COMPLETE                                       0x5f10

/**
Refer to #clxBleAudioGetAseId function.
*/
#define CLX_BLE_AUDIO_GET_ASE_ID_COMPLETE                                                   0x5f11

/**
Refer to #clxBleAudioGetSupportedAudioContexts function.
*/
#define CLX_BLE_AUDIO_GET_SUPPORTED_AUDIO_CONTEXTS_COMPLETE                                 0x5f12

/**
Refer to #clxBleAudioGetAvailableAudioContexts function.
*/
#define CLX_BLE_AUDIO_GET_AVAILABLE_AUDIO_CONTEXTS_COMPLETE                                 0x5f13

/**
Refer to #clxBleAudioSetLocation function.
*/
#define CLX_BLE_AUDIO_SET_LOCATION_COMPLETE                                                 0x5f14

/**
Refer to #clxBleAudioConfigureAse function.
*/
#define CLX_BLE_AUDIO_CONFIGURE_ASE_COMPLETE                                                0x5f15

/* Unicast audio meta data */
typedef struct ClxBleAudioUnicastMetadataStruct
{
    _user_out_ u1*  buffer;                         /* User allocated buffer */
    _in_ u2         bufferSize;                     /* Buffer size */
    _in_ u2         actualLength;                   /* Actual data length */
    _in_ u2         offset;                         /* Buffer offset */
} ClxBleAudioUnicastMetadata;

/**
Data Structure for the indications #CLX_BLE_AUDIO_GET_AUDIO_CAPABILITIES_COMPLETE, #CLX_BLE_AUDIO_GET_ASE_ID_COMPLETE, #CLX_BLE_AUDIO_GET_SUPPORTED_AUDIO_CONTEXTS_COMPLETE and
#CLX_BLE_AUDIO_GET_AVAILABLE_AUDIO_CONTEXTS_COMPLETE
*/
typedef struct ClxBleAudioUnicastMetadataCompleteStruct
{
    _user_out_ ClxBleAudioUnicastMetadata*  metadata;    /*!< Unicast audio meta data */
} ClxBleAudioUnicastMetadataComplete;

/**
Requests to get the audio capabilities from remote device.Unicast Client reads the value of Sink/Source PAC characteristics to discover audio capability settings.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BLE_AUDIO_GET_AUDIO_CAPABILITIES_COMPLETE.
                   The parameter of this indication is of type #ClxBleAudioUnicastMetadataComplete.

\param[  in   ] gatt               GATT client handle. which is retrieved through the API #clxGattCreateClient
\param[  in   ] handle             Attribute handle to read
\param[  out  ] metadata           Application allocated pointer to retrieve the audio capabilities.
\param[  in   ] block              Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

*/
ClxResult clxBleAudioGetAudioCapabilities(_in_ ClxHandle                          gatt,
                                          _in_ u2                                 handle,
                                          _user_out_ ClxBleAudioUnicastMetadata*  metadata,
                                          _in_ boolean                            block);

/**
Requests to get the audio streaming endpint ID. Unicast Client reads the value of ASE characteristics to discover ASE ID.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BLE_AUDIO_GET_ASE_ID_COMPLETE.
                   The parameter of this indication is of type #ClxBleAudioUnicastMetadataComplete.

\param[  in   ] gatt        GATT client handle. which is retrieved through the API #clxGattCreateClient
\param[  in   ] handle      Attribute handle to read
\param[  out  ] metadata    Application allocated pointer to retrieve ASE
\param[  in   ] block       Type of the operation.
                                TRUE:  API will be blocked until this command is completed (successfully or failed).
                                FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

*/
ClxResult clxBleAudioGetAseId(_in_ ClxHandle                            gatt,
                              _in_ u2                                   handle,
                              _user_out_ ClxBleAudioUnicastMetadata*    metadata,
                              _in_ boolean                              block);

/**
Reads the value of supported audio contexts characteristic to determine the context type values.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BLE_AUDIO_GET_SUPPORTED_AUDIO_CONTEXTS_COMPLETE.
                   The parameter of this indication is of type #ClxBleAudioUnicastMetadataComplete.

\param[  in   ] gatt                   GATT client handle. which is retrieved through the API #clxGattCreateClient
\param[  in   ] handle                 Attribute handle to read
\param[  out  ] metadata               Application allocated pointer to retrieve the supported audio contexts
\param[  in   ] block                  Type of the operation.
                                       TRUE:  API will be blocked until this command is completed (successfully or failed).
                                       FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

*/
ClxResult clxBleAudioGetSupportedAudioContexts(_in_ ClxHandle                        gatt,
                                               _in_ u2                                  handle,
                                               _user_out_ ClxBleAudioUnicastMetadata*   metadata,
                                               _in_ boolean                             block);

/**
Reads the value of available audio contexts characteristic to determine the context type values.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BLE_AUDIO_GET_AVAILABLE_AUDIO_CONTEXTS_COMPLETE.
                   The parameter of this indication is of type #ClxBleAudioUnicastMetadataComplete.

\param[  in   ] gatt                  GATT client handle. which is retrieved through the API #clxGattCreateClient
\param[  in   ] handle                Attribute handle to read
\param[  out  ] metadata              Application allocated pointer to retrieve the avilable audio contexts
\param[  in   ] block                 Type of the operation.
                                      TRUE:  API will be blocked until this command is completed (successfully or failed).
                                      FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return ClxError Error code for the operation.

        - CLX_ERROR_COMPLETION_PENDING: operation will be completed asynchronously (only in non-blocking mode)
        - CLX_ERROR_COMMAND_CANCELLED: the handle was closed before the command has completed (only in blocking mode)
        - CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - CLX_ERROR_INVALID_HANDLE: invalid handle

*/
ClxResult clxBleAudioGetAvailableAudioContexts(_in_ ClxHandle                           gatt,
                                               _in_ u2                                  handle,
                                               _user_out_ ClxBleAudioUnicastMetadata*   metadata,
                                               _in_ boolean                             block);

/**
Configures the preferred audio location.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BLE_AUDIO_SET_LOCATION_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt           GATT client handle. which is retrieved through the API #clxGattCreateClient
\param[  in   ] handle         Attribute handle to write
\param[  in   ] dataBuffer     Application allocated buffer to set an audio location
\param[  in   ] length         Allocated buffer length
\param[  in   ] block          Type of the operation.
                                      TRUE:  API will be blocked until this command is completed (successfully or failed).
                                      FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
*/
ClxResult clxBleAudioSetLocation(_in_ ClxHandle         gatt,
                                 _in_ u2                handle,
                                 _user_in_ u1*          dataBuffer,
                                 _in_ u2                length,
                                 _in_ boolean           block);

/**
Configures Audio Stream Endpoint's(ASE) control operation.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_BLE_AUDIO_CONFIGURE_ASE_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt          GATT client handle. which is retrieved through the API #clxGattCreateClient
\param[  in   ] handle        Attribute handle to write
\param[  in   ] dataBuffer    Application allocated pointer to configure ASE operations
\param[  in   ] length        Allocated buffer length
\param[  in   ] block         Type of the operation.
                                      TRUE:  API will be blocked until this command is completed (successfully or failed).
                                      FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle
*/
ClxResult clxBleAudioConfigureAse(_in_ ClxHandle                       gatt,
                                  _in_ u2                           handle,
                                  _user_in_ u1*                     dataBuffer,
                                  _in_ u2                           length,
                                  _in_ boolean                      block);


#ifdef __cplusplus
}
#endif



#endif // __BleAudio_Unicast_Client_Api_h__
