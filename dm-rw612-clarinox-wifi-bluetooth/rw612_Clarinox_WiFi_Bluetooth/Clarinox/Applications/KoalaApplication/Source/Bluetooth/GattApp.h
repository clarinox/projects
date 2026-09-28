#ifndef __GattApp_h__
#define __GattApp_h__

/********************************************************************************
*
* Project             Clarinox Reference Application
* File                GattApp.h
* Description         This file provides GATT Application functions declarations.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "Gatt.Ble.Common.Api.h"
#include "Gap.Ble.Api.h"

#if defined(CLX_BLE_ISOCHRONOUS)
#include "Ble.Bap.Api.h"
#endif /* CLX_BLE_ISOCHRONOUS */

#if defined(CLX_WINDOWS)
#include <direct.h>
#endif /* defined(CLX_WINDOWS) */

#if defined(CLX_WINDOWS)
#define MAX_NUMBER_OF_HANDLES       4
#else
#define MAX_NUMBER_OF_HANDLES       1
#endif /* defined(CLX_WINDOWS) */

#if defined(CLX_WINDOWS)
#define MAX_NUM_SERVICES                100
#define MAX_NUM_CHARACTERISTIC_LIST     100
#define MAX_NUM_DESCRIPTORS_LIST        100
#else
#define MAX_NUM_SERVICES                5
#define MAX_NUM_CHARACTERISTIC_LIST     10
#define MAX_NUM_DESCRIPTORS_LIST        3
#endif /* defined(CLX_WINDOWS) */

#define CLX_BLE_GAP_AD_TYPE_FLAG                                       0x01
#define CLX_BLE_GAP_AD_TYPE_INCOMPLETE_LIST_OF_16_BIT_SERVICE_UUID     0x02
#define CLX_BLE_GAP_AD_TYPE_SHORTED_LOCAL_DEVICE_NAME                  0x08
#define CLX_BLE_GAP_AD_TYPE_COMPLETE_LOCAL_DEVICE_NAME                 0x09
#define CLX_BLE_GAP_AD_TYPE_APPEARANCE                                 0x19
#define CLX_BLE_GAP_AD_TYPE_TX_POWER_LEVEL                             0x0a

#define MAX_REMOTE_DEVICE_NAME_SIZE  31

/*
Maximum number of remote device whose details can be stored
*/
#if defined(CLX_WINDOWS)
#define REMOTE_DEVICE_LIST_SIZE      32
#else
#define REMOTE_DEVICE_LIST_SIZE      8
#endif

#define NO_DEVICE_NAME               "<null>"

/**
Max length for the name of a service when it turns up as a menu item in the list of services
*/
#define MAX_SERVICE_NAME_LENGTH_VERBOSE         64

/**
Object to store the discovered remote device details.
*/
typedef struct RemoteDeviceInfoStruct
{
    ClxBleBdAddress address;
    s1              name[MAX_REMOTE_DEVICE_NAME_SIZE + 1];
    s1              rssi;
    u1              advSID;
    u2              audioRole;
}RemoteDeviceInfo;

RemoteDeviceInfo* showRemoteDeviceList();
void resetRemoteDeviceList();
extern ClxHandle createGattHandle(ClxStack stack);
extern void deleteGattHandle(ClxHandle handle);
extern boolean stackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode);
extern ClxBleBdAddress* showPairedDeviceList(ClxStack stack);

u1 getBondingProperty ( boolean secureFlag, boolean securityRequest, boolean crossTransportFlag );

extern const s1* getServiceName(u2 uuid);
extern const s1* getCharacteristicName(u2 serviceUuid, u2 characteristicUuid);
extern const s1* getDescriptorName(u2 uuid);

/** 
Implementation to store remote device details 
*/
class RemoteDeviceList
{
private:
    RemoteDeviceInfo list_[REMOTE_DEVICE_LIST_SIZE];
    u4               currentSize_;

public:
    RemoteDeviceList()
    :
    currentSize_(0)
    {}

    void reset()
    {
        currentSize_ = 0;
    }

    RemoteDeviceInfo* addDevice(ClxBleBdAddress& address, const u1* name, u4 nameLength, u1 advSID, s1 rssi, u2 audioRole)
    {
        RemoteDeviceInfo* ret = NULL;

        if (currentSize_ < REMOTE_DEVICE_LIST_SIZE)
        {
            ret = &list_[currentSize_];
            ret->address.addressType = address.addressType;
            memcpy(ret->address.value, address.value, sizeof(address.value));

            if (name)
            {
                u4 len2Copy = MIN(nameLength, MAX_REMOTE_DEVICE_NAME_SIZE);

                memcpy(ret->name, name, len2Copy);
                ret->name[len2Copy] = '\0';
            }
            else
            {
                strcpy(ret->name, NO_DEVICE_NAME);
            }
            
            ret->rssi = rssi;
            ret->advSID = advSID;
            ret->audioRole = audioRole;

            ++currentSize_;
        }

        return ret;
    }

    RemoteDeviceInfo* findAudioSource(void)
    {
        RemoteDeviceInfo* deviceInfo = NULL;

#define RSSI_THRESHOLD      ((s1) -80)        // -80 dBm

        if (currentSize_ == 0)
        {
            return NULL;
        }

        s1 bestRssi = (s1)-128;        // start at -128 (lowest RSSI)

        for (u4 loop = 0; loop < currentSize_; loop++)
        {
            if (list_[loop].audioRole & ClxBleAudioRole_BroadcastMediaSender)
            {
                if (list_[loop].rssi >= RSSI_THRESHOLD && list_[loop].rssi > bestRssi)
                {
                    bestRssi = list_[loop].rssi;
                    deviceInfo = &list_[loop];
                }
            }
        }

        return deviceInfo;
    }

    RemoteDeviceInfo* findDevice(ClxBleBdAddress& address)
    {
        RemoteDeviceInfo* deviceInfo = NULL;

        if (currentSize_ < REMOTE_DEVICE_LIST_SIZE)
        {
            for (u4 i = 0; i < currentSize_; i++)
            {
                if ((memcmp(list_[i].address.value, address.value, sizeof(address.value)) == 0) &&
                    (list_[i].address.addressType == address.addressType))
                {
                    deviceInfo = &list_[i];
                }
            }
        }
        else
        {
            deviceInfo = &list_[REMOTE_DEVICE_LIST_SIZE];
        }

        return deviceInfo;
    }

    RemoteDeviceInfo* findDeviceByAdressAndSID(ClxBleBdAddress& address, u1 advSID)
    {
        RemoteDeviceInfo* deviceInfo = NULL;

        for (u4 i = 0; i < currentSize_; i++)
        {
            if ((memcmp(list_[i].address.value, address.value, sizeof(address.value)) == 0) &&
                (list_[i].address.addressType == address.addressType) &&
                (list_[i].advSID == advSID))
            {
                deviceInfo = &list_[i];
            }
        }

        return deviceInfo;
    }

    u4 currentSize() const
    {
        return currentSize_;
    }

    RemoteDeviceInfo& operator[] (u4 index)
    {
        CLX_ASSERT(index < currentSize_);
        return list_[index];
    }
};

#ifdef __cplusplus
extern "C"
{
#endif

extern  void clxInitBsp(void);

#ifdef __cplusplus
}
#endif

ClxResult clxBLECheckCharacteristicHandleByCharName( u2     characteristicHandle, s1*    charName );

void initAdvertisingData(const s1* deviceName);

#endif /* __GattApp_h__ */

