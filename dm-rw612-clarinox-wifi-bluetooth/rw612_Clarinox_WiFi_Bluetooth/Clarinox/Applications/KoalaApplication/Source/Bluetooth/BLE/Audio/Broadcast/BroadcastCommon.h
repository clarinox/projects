#ifndef __BroadcastCommon_h__
#define __BroadcastCommon_h__

/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                BroadcastCommon.h
* Description         This file provides Broadcast Application functions declarations.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

/* Broadcast Audio Scan Control point opcode */
typedef enum ClxBleBassOpcodeEnum
{
    ClxBleBassOpcode_RemoteScanStopped      = 0x00,
    ClxBleBassOpcode_RemoteScanStarted      = 0x01,
    ClxBleBassOpcode_AddSource              = 0x02,
    ClxBleBassOpcode_ModifySource           = 0x03,
    ClxBleBassOpcode_SetBroadcastCode       = 0x04,
    ClxBleBassOpcode_RemoveSource           = 0x05
    /* RFU: 0x06 - 0xFF*/
} ClxBleBassOpcode;

/* Broadcast Selector */
typedef struct ClxBleBroadcastSelectorInfoStruct
{
    u1 addrType;                                    /* Advertiser address type */
    u1 address[6];                                  /* Advertiser address */
    u1 advSID;                                      /* Advertiser SID */
    u1 broadcastId[3];                              /* Broadcast Id available in extended adv report */
    u1 paSync;                                      /* Periofic advertising sync state */
    u2 paInterval;                                  /* Periodic advertising interval */
    u1 bigEngryption;                               /* Encrypton flag */
    u1 sourceId;                                    /* Source Id which is assigned by scan delegator */
    u1 numSubGroup;                                 /* Number of sub group */
    u4 bisSync;                                     /* BIS bitmap */
    u1 metaDataLength;                              /* Meta data length available in Basic Audio Announcement */
    u2 receiveStateValueHandle;                     /* BASS receive state attribute handle */
    ClxBleConnectionHandle connectionHandle;        /* ACL connection handle */
} ClxBleBroadcastSelectorInfo;

void bluetoothLowEnergyBroadcastSenderMenu   ( ClxStack stack );
void bluetoothLowEnergyBroadcastReceiverMenu ( ClxStack stack );
void bluetoothLowEnergyBroadcastSelectorMenu ( ClxStack stack );

ClxResult clxBleBroadcastSenderStartBIG ( ClxStack stack );

ClxResult clxBleBroadcastSenderStopBIG ( ClxStack stack );

void clxBleBroadcastSenderAddBIGInfo ( ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement );

void clxBleBroadcastSoureAddCodecAndMetadataInfo ( ClxBleAudioBISBasicAudioAnnouncement* basicAnnouncement );

void clxBleBassClientRemoteScanStopped(void);

void clxBleBAupdateAdvInfo(u4 broadcastId, u1 advSid, ClxBleBdAddress addr);
void clxBleBAupdateSyncInfo(u2 PaInterval);
u2 clxBleBAgetReceiveStateAttributeHandle(void);
void clxBleBAprocessReceiveStateNotification(u1* data, u4 dataLength);

#if FIX_TIMER
ClxResult clxBleBAcreateConnectionMonitoringTimer(void);
ClxResult clxBleBAdestroyConnectionMonitoringTimer(void);
#endif

#endif /* defined(CLX_BLE_ISOCHRONOUS) */

#endif /* __BroadcastCommon_h__ */

