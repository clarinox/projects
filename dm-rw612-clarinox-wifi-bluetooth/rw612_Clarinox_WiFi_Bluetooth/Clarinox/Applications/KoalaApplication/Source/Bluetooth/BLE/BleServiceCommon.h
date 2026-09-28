#ifndef __Ble_Service_Common_h__
#define __Ble_Service_Common_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                BleServiceCommon.h
* Description         Declares ClarinoxBlue LE Audio Common service and 
                      characteristics declarations.
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#if defined( CLX_BLE_SERVICE_EXTENDED_API )

void clxBleServicesMenu( ClxStack stack, ClxHandle gattHandle );

/*
BLE Services Menu APIs
*/
void clxBleBatteryLevelServiceMenu     ( ClxStack stack, ClxHandle gattHandle );
void clxBleDeviceInformationServiceMenu( ClxStack stack, ClxHandle gattHandle );
void clxBleMediaControlServiceMenu     ( ClxStack stack, ClxHandle gattHandle );
void clxBleVolumeControlServiceMenu    ( ClxStack stack, ClxHandle gattHandle );
void clxBleAlertNotificationServiceMenu( ClxStack stack, ClxHandle gattHandle );

ClxBleGattRoleType clxBleGetCurrentGattRoleByGattHandle( ClxHandle gatt );

const s1* clxBleGetCurrentGattRoleName( ClxBleGattRoleType gattRole );

u2 clxBleGetServerCharacteristicsHandleByUUIDs( ClxHandle gatt,
                                                u1        ServiceListIndex,
                                                u1        characteristicHandleIndex );

u2 clxBleGetClientCharacteristicsHandleByUUIDs( ClxHandle gatt,
                                                u4        serviceUuid,
                                                u4        characteristicUuid );

#endif /* defined( CLX_BLE_SERVICE_EXTENDED_API ) */

#endif /* __Ble_Service_Common_h__ */

