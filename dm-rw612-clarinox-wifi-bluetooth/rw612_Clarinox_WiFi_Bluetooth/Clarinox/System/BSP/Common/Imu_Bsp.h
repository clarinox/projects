#ifndef __RW612_BSP_IMU_BSP_H__
#define __RW612_BSP_IMU_BSP_H__

/******************************************************************************
*
* Project             ClarinoxBSP
* File                Imu_Bsp.h
* Description         This file includes IMU_Bsp related declarations.
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

#include "ClarinoxErrorCodes.h"
#include "ClxTypes.h"


typedef ClxResult (*clxImuIrqHandler)(void* userData, u1 irqType, boolean isrContext);
typedef ClxResult (*clxImuMsgHandler)(void* userData, u1 irqType);

ClxResult clxImuInit(clxImuIrqHandler irq_handler, clxImuMsgHandler msg_handler, void* irqHandlerUserData);
ClxResult clxImuFwDownload(void);

void      clxImuMsgReceive(void);

u4        clxImuGetCmdLength(void);
void      clxImuGetCmdBuf(u1* payloadPtr, u4 dataLength);

u1        clxImuGetDataBufNum(void);
u4        clxImuGetDataBufLength(u1 bufNum);
void      clxImuGetDataBuf(u1* payloadPtr, u4 dataLength, u1 bufNum);

ClxResult clxImuSendCmdData(u1 *cmd_payload, u4 length);
ClxResult clxImuSendTxData(u1 *data, u4 length);

boolean   clxImuIsBuffFull(void);
void      clxImuEnableInterrupts(void);

#ifdef __cplusplus
}
#endif

#endif /* __RW612_BSP_IMU_BSP_H__ */
