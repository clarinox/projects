/*******************************************************************************
*
* Project             ClarinoxBlue
* File                ClarinoxBlueDriver.Bsp.cpp
* Description         ClarinoxBlue Driver Interface to UART Driver
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

// _____________________________________________________________________________
//
#undef  CLX_MODULE_ID
#define CLX_MODULE_ID 30115
// _____________________________________________________________________________
//

#if defined(CLX_ENABLE_BLUETOOTH)

/*******************************************************************************
								Includes
*******************************************************************************/

#include "stdio.h"
#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include "ClarinoxBlueErrorCodes.h"
#include "ClarinoxBlueConst.h"
#include "ClarinoxBlueScoInterface.h"
#include "ClarinoxBlue.Driver.Bsp.h"

#include "fwk_platform_ble.h"

/*******************************************************************************
							 Define and Macros
*******************************************************************************/

//#define CLARINOXBLUE_SCO_OVER_HCI

#define IMU_BLE_PACKET_TYPE_FIELD_LENGTH                            1 /* Bytes */
#define MAX_HCI_EVENT_SIZE                                       (CLX_EVENT_HDR_LEN + 255)   /* Bytes */

#define GET_BITS( data, startBit, totalBits ) ( ( (data) >> (startBit) ) & ( ( 1UL << (totalBits) ) - 1 ) )

typedef enum StateEnum
{
    State_Idle,
    State_WaitingForPacketHeader,
    State_WaitingForPacketPayload
} State;

/*******************************************************************************
							 Private Variables
*******************************************************************************/

static ClxBluetoothPacketType   rxPktType;
static u4                       rxRequiredLen;
static State                    rxState;

#if defined(CLARINOXBLUE_SCO_OVER_HCI)
static u4                       rxScoPacketsDropped = 0;
#endif

/*******************************************************************************
							Public Variables
*******************************************************************************/


/*******************************************************************************
						Private Function Prototypes
*******************************************************************************/

static void clxBlueInit(void);
static ClxResult clxBlueStart(_in_ const ClxConfigList* configList);
static void clxBlueStop(void);
static void clxBlueTerminate(void);
static void clxBlueSendData(_in_ const u1* data, _in_ ClxSize dataLength);
static ClxResult clxBlueLockUsbSetTotalScoBandwidth (_in_ u4 bandwidth);
static void clxBlueLockUsbSftIrqHandler (void);
static void clxBlueLock(void);
static void clxBlueUnlock(void);
static void* clxBlueAllocatMemory (const ClxPackage* package, u2 moduleID, u4 line, u4 size);
static void clxBlueFreeMemory(void* ptr);

static void submitHciEvent( const u1* data, u4 totalLength );
static void submitAclPacket( const u1* data, u4 totalLength );
#if defined(CLARINOXBLUE_SCO_OVER_HCI)
static void submitScoPacket( const u1* data, u4 totalLength );
#endif
static void clxImuBleDataReceived(uint8_t packetType, u1* buffer, u2 length);

/*******************************************************************************
							Private Functions
*******************************************************************************/

static void clxBlueInit(void)
{
    rxPktType           = (ClxBluetoothPacketType)0xFF;
    rxRequiredLen       = 0;
    rxState             = State_Idle;

#if defined(CLARINOXBLUE_SCO_OVER_HCI)
    rxScoPacketsDropped = 0;
#endif

    PLATFORM_SetHciRxCallback(clxImuBleDataReceived);
    PLATFORM_InitBle();
}

static ClxResult clxBlueStart(_in_ const ClxConfigList* configList)
{
	PLATFORM_StartHci();
        return CLX_SUCCESS;
}

static void clxBlueStop(void)
{
	/* nothing to do */
}

static void clxBlueTerminate(void)
{
	PLATFORM_TerminateBle(); // TODO: check it if it works correctly.
}

static void clxBlueSendData(_in_ const u1* data, _in_ ClxSize dataLength)
{
    ClxResult ret = PLATFORM_SendHciMessage((uint8_t*)data, dataLength);
    BLACKBOX_IF(ret != CLX_SUCCESS);
}

static ClxResult clxBlueLockUsbSetTotalScoBandwidth (_in_ u4 bandwidth)
{
    return CLX_SUCCESS;
}

static void clxBlueLockUsbSftIrqHandler (void)
{
	/* nothing to do */
}

static void clxBlueLock(void)
{
	/* nothing to do */
}

static void clxBlueUnlock(void)
{
	/* nothing to do */
}

/* All outgoing and incoming packet buffers are allocated via this function */
static void* clxBlueAllocatMemory (const ClxPackage* package, u2 moduleID, u4 line, u4 size)
{
	return clxPoolsetAlloc(package, moduleID, line, size);
}

static void clxBlueFreeMemory(void* ptr)
{
	clxPoolsetFree(ptr);
}

/* Called by the UART driver RX IRQ handler: */
static void clxImuBleDataReceived(uint8_t packetType, u1* buffer, u2 length)
{
    const u1* data = buffer;
    u4 dataLength = length;

    while(1)
    {
        switch (rxState)
        {
        case State_Idle:
            rxRequiredLen = IMU_BLE_PACKET_TYPE_FIELD_LENGTH;

            if (dataLength >= IMU_BLE_PACKET_TYPE_FIELD_LENGTH)
            {
                rxPktType = (ClxBluetoothPacketType)data[0];

                switch (rxPktType)
                {
                case ClxBluetoothPacketType_hciCommand:
                    rxRequiredLen += CLX_CMD_HDR_LEN;
                    break;

                case ClxBluetoothPacketType_hciSCO:
                    rxRequiredLen += CLX_SCO_HDR_LEN;
                    break;

                case ClxBluetoothPacketType_hciACL:
                    rxRequiredLen += CLX_ACL_HDR_LEN;
                    break;

                case ClxBluetoothPacketType_hciEvent:
                    rxRequiredLen += CLX_EVENT_HDR_LEN;
                    break;

                default:
                    BLACKBOX_ISR;
                    break;
                }
            }
            else
            {
                /* Wait for the packet type: */
                return /*rxRequiredLen*/;
            }

            rxState = State_WaitingForPacketHeader;
            break;

        case State_WaitingForPacketHeader:
            if (dataLength >= rxRequiredLen)
            {
                switch (rxPktType)
                {
                case ClxBluetoothPacketType_hciACL:
                    rxRequiredLen += READ_FROM_LITTLEENDIAN_2((u2*) &data[IMU_BLE_PACKET_TYPE_FIELD_LENGTH + 2]);
                    break;
#if defined(CLARINOXBLUE_SCO_OVER_HCI)
                case ClxBluetoothPacketType_hciSCO:
                    rxRequiredLen += data[IMU_BLE_PACKET_TYPE_FIELD_LENGTH + 2];
                    break;
#endif
                case ClxBluetoothPacketType_hciEvent:
                    rxRequiredLen += data[IMU_BLE_PACKET_TYPE_FIELD_LENGTH + 1];
                    break;

                default:
                    BLACKBOX_ISR;
                }
            }
            else
            {
                /* Wait for the packet header: */
                return /*rxRequiredLen*/;
            }

            rxState = State_WaitingForPacketPayload;
            break;

        case State_WaitingForPacketPayload:
            if (dataLength >= rxRequiredLen)
            {
                switch (rxPktType)
                {
                case ClxBluetoothPacketType_hciACL:
                    submitAclPacket(data + IMU_BLE_PACKET_TYPE_FIELD_LENGTH, rxRequiredLen - IMU_BLE_PACKET_TYPE_FIELD_LENGTH);
                    break;
#if defined(CLARINOXBLUE_SCO_OVER_HCI)
                case ClxBluetoothPacketType_hciSCO:
                    submitScoPacket(data + IMU_BLE_PACKET_TYPE_FIELD_LENGTH, rxRequiredLen - IMU_BLE_PACKET_TYPE_FIELD_LENGTH);
                    break;
#endif
                case ClxBluetoothPacketType_hciEvent:
                    submitHciEvent(data + IMU_BLE_PACKET_TYPE_FIELD_LENGTH, rxRequiredLen - IMU_BLE_PACKET_TYPE_FIELD_LENGTH);
                    break;

                default:
                    BLACKBOX_ISR;
                }
            }
            else
            {
                /* Wait for the entire payload: */
                return /*rxRequiredLen*/;
            }

            /* We look for the next packet: */
            dataLength -= rxRequiredLen;
            //*length = dataLength; // TODO: check it why we need that.

            if (dataLength)
            {
                /* We have to move whatever we have to the beginning of the buffer: */
                memmove(buffer, buffer + rxRequiredLen, dataLength);
            }

            rxState = State_Idle;
            break;

        default:
            BLACKBOX_ISR;
        }
    }
}

static void submitHciEvent( const u1* data, u4 totalLength )
{
    CLX_DEBUG_ASSERT((totalLength >= CLX_EVENT_HDR_LEN) && (totalLength <= MAX_HCI_EVENT_SIZE));

    u1* hciEventBuf = clxBlueDriverGetRxHciEventBuffer(data[0], totalLength);

    memcpy(hciEventBuf, data, totalLength);

    clxBlueDriverSubmitRxHciEvent(hciEventBuf, TRUE);
}

static void submitAclPacket( const u1* data, u4 totalLength )
{
    CLX_DEBUG_ASSERT(totalLength >= CLX_ACL_HDR_LEN);

    u2 connectionHandle =  READ_FROM_LITTLEENDIAN_2((u2*) &data[ 0 ] );
    connectionHandle &=  0x0FFF ;
    u1 aclPbFlag = GET_BITS( data[ 1 ], 4, 2);
    u1 aclBcFlag = GET_BITS( data[ 1 ], 6, 2);

    u4 index = CLX_ACL_HDR_LEN;

    while (index < totalLength)
    {
        struct ClxRxAclBuffer* buffer = clxBlueDriverGetFreeRxAclBuffer();

        if (!buffer)
        {
            BLACKBOX_ISR;
            return;
        }

        buffer->bcFlag = aclBcFlag;
        buffer->pbFlag = aclPbFlag;
        buffer->length = MIN((totalLength - index), buffer->bufferSize);
        buffer->connectionHandle = connectionHandle;

        memcpy(buffer->address, data + index, buffer->length);

        clxBlueDriverQueueRxAclBuffer(buffer);

        index += buffer->length;
        aclPbFlag = CLX_ACL_FRAME_CONT;
    }

	clxBlueDriverFlushRxAclBuffers(TRUE);
}

#if defined(CLARINOXBLUE_SCO_OVER_HCI)
static void submitScoPacket( const u1* data, u4 totalLength )
{
    CLX_DEBUG_ASSERT(totalLength >= CLX_SCO_HDR_LEN);

    u2 connectionHandle =  READ_FROM_LITTLEENDIAN_2((u2*) &data[ 0 ] );
    connectionHandle &=  0x0FFF ;

    u4 payloadLength = totalLength - CLX_SCO_HDR_LEN;

    struct ClxRxScoBuffer* scoBufferDescriptor = clxBlueDriverGetFreeRxScoBuffer(payloadLength);

    if (!scoBufferDescriptor)
    {
        ++rxScoPacketsDropped;
        return;
    }

    memcpy(scoBufferDescriptor->buffer, data + CLX_SCO_HDR_LEN, payloadLength);

    scoBufferDescriptor->scoHandle = connectionHandle;
    scoBufferDescriptor->dataLength = payloadLength;

    clxBlueDriverSubmitRxScoBuffer(scoBufferDescriptor, FALSE);
}
#endif /* CLX_PACKAGE_CLARINOXBLUE_SCO_OVER_HCI */

/*******************************************************************************
							Public Functions
*******************************************************************************/

/*
In the beginning of the file Bsp.cpp, add the following C extern:
extern "C" ClarinoxBlueDriverInterface clxBlueDriverInterface;

In the function clxInitBsp() add the following line:
clarinoxBlueDriverInterface = &clxBlueDriverInterface;
*/
struct ClarinoxBlueDriverInterface clxBlueDriverInterface = {clxBlueInit,
                                                             clxBlueStart,
                                                             clxBlueStop,
                                                             clxBlueTerminate,
                                                             clxBlueSendData,
                                                             clxBlueLockUsbSetTotalScoBandwidth,
                                                             clxBlueLockUsbSftIrqHandler,
                                                             clxBlueLock,
                                                             clxBlueUnlock,
                                                             clxBlueAllocatMemory,
                                                             clxBlueFreeMemory};

#endif // #if defined(CLX_ENABLE_BLUETOOTH)
