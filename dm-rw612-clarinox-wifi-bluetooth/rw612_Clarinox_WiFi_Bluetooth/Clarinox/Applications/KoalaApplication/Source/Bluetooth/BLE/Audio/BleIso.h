#ifndef __BLE_ISO_Tx_h__
#define __BLE_ISO_Tx_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                BleIso.h
* Description         Declares ClarinoxBlue LE Audio Send.
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#include "ClxBsp.h"
#include "ClarinoxBlue.h"

/**
 * "BLE Audio Send Thread Context Count. Its equal to count of BIS or CIS
 */
#define CLX_BLE_AUDIO_SEND_THREAD_CONTEXT_COUNT             CLX_GATT_MAX_BIS_SUPPORTED

#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX

#ifdef CLX_WINDOWS
#define CLX_BLE_AUDIO_LC3_SEND_OFFSET                       10   /* In Windows, Audio send as Periodic shot based timer */
#else
#define CLX_BLE_AUDIO_LC3_SEND_OFFSET                       7
#endif /* CLX_WINDOWS */

#else /* !CLX_BLE_ISO_TIMER_BASED_AUDIO_TX*/

#if defined (CLX_WINDOWS) || defined (CLX_FLOATINGPOINT_LC3)
/* High Resolution Time based trigger */
#define CLX_BLE_AUDIO_LC3_SEND_OFFSET                       9500
#else
#define CLX_BLE_AUDIO_LC3_SEND_OFFSET                       7200
#endif /* defined (CLX_WINDOWS) || defined (CLX_FLOATINGPOINT_LC3) */

#endif /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */

/*
BLE Audio Play State enum
*/
typedef enum ClxBleAudioPlayStateEnum
{
    ClxBleAudioPlayState_IDLE      = 0,                     /* BLE audio send state is Idle */
    ClxBleAudioPlayState_PLAY,                              /* BLE audio send state is Active or play */
    ClxBleAudioPlayState_PAUSE,                             /* BLE audio send state is Pause */
    ClxBleAudioPlayState_STOP,                              /* BLE audio send state is Stop the Audio send process */
    ClxBleAudioPlayState_GoNext,                            /* BLE audio send state is Go and Play the next audio file */
    ClxBleAudioPlayState_GoPrevious,                        /* BLE audio send state is Go and Play the previous audio file */
    ClxBleAudioPlayState_TERMINATE                          /* BLE audio send state is Terminate the Audio Send thread */
}ClxBleAudioPlayState;

/* BLE Audio Send Thread Context Struture */
typedef struct ClxBLEAudioSendThrdContextStruct
{
    ClxThreadHandle             bleAudioSendThreadHandle;                       /*!< BLE audio send thread handle */
    ClxSemaphore                bleAudioSendSemaphore;                          /*!< BLE audio send Semaphore */
    ClxBleAudioPlayState        bleCurrentPlayState;                            /*!< BLE Audio Play State enum */
    u2                          bleISOStreamHandle;                             /*!< ISO stream handle */
    s1                          bleThreadName [ 30 ] ;                          /*!< Thread Name "CLX_BLE_AUDIO_SEND_THREAD_NAME" concatenate with index */
    u1                          bleSupportedAudioFileCount;                     /*!< Overall Audio file supported count */
    u1                          bleCurrentFileIndex;                            /*!< BLE Audio send thready playing current file index */
    u1                          bleThreadContextIndex;                          /*!< BLE Audio send thready playing current file index */
    ClxSemaphore                bleAudioSendThreadKillSemaphore;                /*!< Audio Send Thread Kill Semaphore */

#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX
    ClxSemaphore                bleISOTxSemaphore;                              /*!< Audio Send ISO data controller Semaphore */
    ClxTimer                    isoTxTimer;                                     /*!< Audio Send ISO data Tx Timer Handle */
#endif /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */

    BleLc3Encode             lc3Encode;

}ClxBLEAudioSendThrdContext;

#ifdef CLX_BLE_ISO_TIMER_BASED_AUDIO_TX
ClxResult bleCreateIsoSendTimer ( u1 index );

ClxResult bleDestroyIsoSendTimer ( ClxBLEAudioSendThrdContext* clxAudioSendThreadCxtInfo );
#endif /* CLX_BLE_ISO_TIMER_BASED_AUDIO_TX */

/**
Get the Audio send thread Context structure

\return      Base address of the context structure
*/
ClxBLEAudioSendThrdContext* bleGetAudioSendThrdCxtInfo ( u1 index );

/**
Initialize the Audio send context structure fields and call the create the Audio Send Thread function.
*/
void bleInitAudioSendThread ( u1 index );

/**
Reset the Audio send context structure fields and destroy the Audio Send Thread resources.
*/
void bleDestroyAudioSendThread ( u1 index );

/**
BLE Audio send Thread handler function.

\param data  Thread input data.
*/
ClxResult bleAudioSendThreadHandler ( void* data );

/**
Function to create the BLE Audio send Thread 
*/
void bleCreateAudioSendThread  ( u1 index );

/**
Set the play status as PLAY and signal to semaphore for start the Audio send process
*/
void bleStartAudioSendProcess ( u1 index );

/**
User to set the Audio send thread play status into the Context structure

\param  newState    User BLE Audio Play State enum
*/
void bleSetAudioSendThreadState ( ClxBleAudioPlayState  newState, u1 index );

/**
Get the Audio send thread play status from the Context structure

\return      BLE Audio Play State enum from the context structure
*/
ClxBleAudioPlayState bleGetAudioSendThreadState ( u1 index );

/**
Fill ISO Stream Handle into the Audio Send Thread context structure.

\param  isoStreamHandle      ISO Stream Handle
*/
void bleFillIsoStreamHandleIntoAudioSendThrdCxt ( u2 isoStreamHandle );

/**
Reset ISO Stream Handle into the Audio Send Thread context structure.
*/
void bleResetIsoStreamHandleIntoAudioSendThrdCxt ( void );

#endif /* CLX_BLE_ISOCHRONOUS */

#endif /* __BLE_ISO_Tx_h__ */
