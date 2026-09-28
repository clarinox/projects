#ifndef _AppCommon_h_
#define _AppCommon_h_

/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                AppCommon.h
* Description         Application common definitions used in PBAP and MAP
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2021 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#include "ClxCommon.h"

/* Structure to hold the delimiter details while parsing the buffer */
typedef struct delimiterStruct
{
    s1* delim;
    u4 delimLength;
}delimiter;

/*******************************************************************************************************************************
*                                                    displayDataList
*
* This function is used to parse and print all the element of the list which corresponds to the key and until it encounters 
* the delimiter value. 
*
*******************************************************************************************************************************/
boolean displayDataList(u1 *pData, u4 dataLen, delimiter* delimList, u4 count, const s1 *key);

#endif //_AppCommon_h_

