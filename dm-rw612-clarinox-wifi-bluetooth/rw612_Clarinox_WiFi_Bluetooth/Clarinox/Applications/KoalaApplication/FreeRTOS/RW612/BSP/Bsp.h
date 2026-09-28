#ifndef __Bsp_H__
#define __Bsp_H__

/******************************************************************************
*
* Project             ClarinoxSoftFrame
* File                Bsp.h
* Description         This file includes Bsp related declarations.
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern const s1*                clxSoftFrameConfigFileName;
extern ClxExceptionCallback     clxOsAbstractionLayerExceptionFunction;

extern void                     clxInitBsp                     (void);
extern int                      mainClarinoxBlue               (void);
extern int                      clarinoxMainWifi               (void);
extern void                     initROMFileSystemMap           (void);
extern int                      clarinoxMain                   (void);
extern ClxResult                mainThreadEntry                (void*);
extern int                      mainBluetooth                  (void);

extern void clxProcessSoftFrameConfigParamsForWlan(ClxGetSoftFrameIntegerParam getIntParam, ClxGetSoftFrameStringParam getStrParam);


#define MAX_TEXT_SIZE                   128
extern ClxFileBspInterface      clxMemoryFileInterface;

                                                                                      
#ifdef __cplusplus
}
#endif

#endif // __Bsp_H__
