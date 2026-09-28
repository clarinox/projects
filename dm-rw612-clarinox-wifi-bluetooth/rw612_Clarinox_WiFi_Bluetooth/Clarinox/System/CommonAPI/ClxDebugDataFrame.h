#ifndef CLX_DEBUG_DATA_FRAME_h
#define CLX_DEBUG_DATA_FRAME_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxDebugDataFrame.h
* Description         Declares a network data packets debug interface based on ClxCommInterface
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

typedef enum ClxWlanDataPacketDirection
{
    ClxWlanDataPacketDirection_Tx,
    ClxWlanDataPacketDirection_Rx
} ClxWlanDataPacketDirection;

#ifdef __cplusplus
extern "C" {
#endif

void sendDataFrameToDebug(u1* buf, u4 bufLen, ClxWlanDataPacketDirection direction);

#ifdef __cplusplus
}
#endif

#endif // CLX_DEBUG_DATA_FRAME_h
