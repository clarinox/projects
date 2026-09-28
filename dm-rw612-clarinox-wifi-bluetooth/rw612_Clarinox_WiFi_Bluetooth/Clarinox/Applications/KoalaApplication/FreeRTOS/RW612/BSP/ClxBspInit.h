#ifndef __ClxBspInit_H__
#define __ClxBspInit_H__

/******************************************************************************
*
* Project             ClarinoxSoftFrame
* File                ClxBspInit.h
* Description         This file includes Bsp Initialization related declarations.
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


extern void         userExceptionHandler      ( s4 moduleId, s4 lineNumber );
extern void         printfFunction            ( char* formattedOutput );
extern int          getInputFunction          ( char* buffer, unsigned int bufferSize );
extern ClxError     clxInitBluetoothController( ClxStack stack );
extern int          clarinoxMain              (void);
extern boolean      clxWlanPowerOnChip        (void);
extern boolean      clxWlanPowerOffChip       (void);
extern void         EXTILine0_Config          (void);
extern void         initROMFileSystemMap      (void);


//extern boolean clxEnableWlanHardware();
extern boolean clxDisableWlanHardware();
//extern void clxWlanLowLevelInit(void);
extern void clxWlanIrqPinConfig(void);
extern void clxWlanPinConfig(void);
void clxExternalSdioIrqHandler(void);

extern struct ClxWl18xxConfigData            clxWl18xxStaticConfigData;
extern        ClxFileBspInterface            clxMemoryFileInterface;
//extern        ClxSdioBspInterface            clxSdioTargetSpecificBspInterface;
extern        ClxUartBspInterface  	         clxUartGenericBspInterface;
extern struct ClarinoxBlueDriverInterface    clxBlueDriverInterface;


extern void*                               (*clxHardwareMemCpy) (void* dest, void* scr, size_t num);
//extern boolean                             (*clxPowerOnChip)  ();
//extern boolean                             (*clxPowerOffChip) ();

extern const u2 wlanPlatformTaskPriorityTable[5];
extern const u2 bluetoothPlatformTaskPriorityTable[5];
extern const u2 clarinoxFreeRTOSSoftFrameTaskStackSizeTable[4];
extern const u2 clarinoxFreeRTOSWlanTaskStackSizeTable[2];
extern const u2 clarinoxFreeRTOSBluetoothTaskStackSizeTable[3];

#ifdef CLX_KOALA_LCD
    extern void initializeLcd ( const u1* lcdAppName );
#endif

extern int                  clarinoxMain(void);

#ifdef __cplusplus
}
#endif

#endif // __ClxBspInit_H__
