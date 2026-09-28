#ifndef __UnicastCommon_h__
#define __UnicastCommon_h__

/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                UnicastCommon.h
* Description         This file provides Unicast Application functions declarations.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2025 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#if defined(CLX_BLE_ISOCHRONOUS)

#include "BleAudioCommon.h"

void bluetoothLowEnergyUnicastSenderMenu   ( ClxStack stack );
void bluetoothLowEnergyUnicastReceiverMenu ( ClxStack stack );

ClxBleRoleType getRoleByAseUuid (u2 uuid);

ClxResult clxBleUnicastSetAudioStreamEndPoint (u1 aseID, ClxBapAudioStreamEndpoint* inputAseInfo );

void clxBleUnicastFillASEInfo ( u1 opCode, ClxBapAudioStreamEndpoint* aseRecord );

#endif /* CLX_BLE_ISOCHRONOUS */

#endif /* __UnicastCommon_h__ */

