#ifndef ClxBsp_h
#define ClxBsp_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxBsp.h
* Description         Board Support Package common
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#include "ClxCommon.h"
#include "ClxUnalignedAccess.h"
#include "ClxBsp.Errors.h"
#include "Console.Bsp.h"
#include "ClxFile.Bsp.h"
#include "Uart.Bsp.h"
#include "Interrupt.Bsp.h"
#include "NetworkAccessInterface.Bsp.h"
#include "NetworkStackServiceInterface.Bsp.h"
#include "ClxDatabaseInterface.Bsp.h"
#include "Thread.Bsp.h"
#include "ClxSoftTrace.Bsp.h"
#include "ClxTaskScheduler.Bsp.h"
#include "NetworkBufferManager.Bsp.h"
#include "ClarinoxBlue.Driver.Bsp.h"

#define CLX_NUMBER_OF_THREAD_PRIORITY_LEVELS		    5
#define CLX_NUMBER_OF_SF_THREAD_STACK_LEVELS			6
#define CLX_NUMBER_OF_BT_THREAD_STACK_LEVELS			3
#define CLX_NUMBER_OF_WLAN_THREAD_STACK_LEVELS			2

/*
Definition of supported ABIs. If support for ClariFi control channels is enabled, 
One of the following ABI values shall be returned by the implementation of the function clxBsp_GetAbiID() in the BSP.
*/
#define CLX_ABI_ARM_IAR_LE                                          1
#define CLX_ABI_ARM_IAR_BE                                          2
#define CLX_ABI_X86_VC2015_LE                                       3
#define CLX_ABI_ARM_GCC_LE                                          4
#define CLX_ABI_ARM_GCC_BE                                          5
#define CLX_ABI_ARM_KEIL_LE                                         6
#define CLX_ABI_ARM_KEIL_BE                                         7
#define CLX_ABI_ARM_MULTI_LE                                        8
#define CLX_ABI_ARM_MULTI_BE                                        9
#define CLX_ABI_ARM_QCC_LE                                          10
#define CLX_ABI_ARM_QCC_BE                                          11
#define CLX_ABI_TRICORE_32BIT_TASKING6_32BIT_ENUM_LE                12          /* Enums are 32 bits long (Tasking compiler option --integer-enumeration is set) */
#define CLX_ABI_TRICORE_32BIT_TASKING6_VARIABLE_LENGTH_ENUM_LE      13          /* Enums are 8, 16, or 32 bits long (Tasking compiler option --integer-enumeration is NOT set) */
#define CLX_ABI_TRICORE_32BIT_TASKING6_32BIT_ENUM_BE                14          /* Enums are 32 bits long (Tasking compiler option --integer-enumeration is set) */
#define CLX_ABI_TRICORE_32BIT_TASKING6_VARIABLE_LENGTH_ENUM_BE      15          /* Enums are 8, 16, or 32 bits long (Tasking compiler option --integer-enumeration is NOT set) */


#if defined( CLX_LINUX ) || defined( CLX_WINDOWS )
/*
 * WINDOWS or LINUX based OSes will use the standard file system support within the System libraries. 
 * Applications using other RTOSes will need to use the template file system support given in the BSP/Source folder
 * this template allows use of a standard file system, flash file (user-defined) or a test version read-only file system
 */
#   if !defined(CLX_FILE_SYSTEM)
#		if !defined(CLX_QNX) && !defined(CLX_VXWORKS_7)
#       	define CLX_FILE_SYSTEM
#		endif
#   endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef struct ClxCapturedPacketDataStruct
{
    u1* data;
    u4 length;
}ClxCapturedPacketData;


/**
This BSP variable is only used in Multi-Processor platforms only, and should not be used in Single-Processor platforms.

This is a pointer which may point to a BSP-defined variable. If set, the value of the assigned variable will hold the index of the
processor core on which all the stack threads are to be bound. If bound successfully, all stack thread will be scheduled and executed only on
the specified core. If this is pointer points to NULL (the default value), no binding will take place and the stack threads may run on any
core available based on the scheduling algorithm used by the operating system.
*/
extern const u4* clxThreadMultiProcessorBindingCoreIndex;

/**
An array of 5 priority levels that is used internally for the ClarinoxBlue implementation. 
These values map the ClarinoxBlue platform-independent thread priorities to underlying platform priorities. 
Each priority level has a 2 byte priority level, the first index (index 0) of the array represents the highest priority,
while the last index (index 4) of the array represents the lowest priority.
If the table is not defined in the BSP, the default priority of the underlying platform will be used for all
threads. 
*/
extern u2* clarinoxBluePlatformTaskPriorityTable;

/**
An array of size 5, and type u2, which maps the ClarinoxWlan platform-independent thread priorities
to underlying platform priorities. The first index (index 0) of the array represents the highest priority,
while the last index (index 4) of the array represents the lowest priority.
If the table is not defined in BSP, the default priority of the underlying platform will be used for all
threads. 

ALL priorities MUST be defined.

ClarinoxWlan threads:

- Driver thread                        : Uses Highest priority (index 0).
- Stack thread                         : Uses Medium priority  (index 2).
- Application Callback thread          : Uses Low priority     (index 3).
*/
extern u2* clarinoxWlanPlatformTaskPriorityTable;

/**
A total of 4 thread stack sizes are got as input from the BSP and used for thread creation.
The Soft Frame thread stack sizes can be passed in the following order 
0.  SoftFrame Timer Thread stack size 
1.	SoftFrame Debug Thread stack size
2.	SoftFrame Console UI Thread stack size
3.	SoftFrame Terminal Emulator Thread stack size
4.  SoftFrame RPC Application Thread stack size
5.  SoftFrame RPC Stack Thread stack size 
*/
extern u2* clarinoxPlatformSoftFrameTaskStackSizeTable;

/*
The Bluetooth thread stack sizes can be passed in the following order 
0.	Bluetooth Application Thread stack size
1.	Bluetooth Stack Thread stack size
2.	Bluetooth Uart Rx Thread stack size
*/
extern u2* clarinoxPlatformBluetoothTaskStackSizeTable;

/*
The WLAN thread stack sizes can be passed in the following order 
0.	WLAN Stack Thread stack size
1.	WLAN Application Thread stack size
*/
extern u2* clarinoxPlatformWlanTaskStackSizeTable;

/**
Clarinox SoftFrame configuration file name
*/
extern const s1* clxSoftFrameConfigFileName;

/**
Implemented to provide a file name for the debug log to be stored locally. Only used when (in SoftFrame.cfg) the parameter DEBUG_MEDIUM is set to FILE.
If not implemented, the default name "default.cdd" will be used.

The returned value is a implementation-allocated buffer. It shall NOT be modified or deleted for the entire debug session.

NOTE : If a file with the provided name already exists, it will be overwritten. In order to avoid this, an implementation shall provide unique names every time it is called.
NOTE : This function is called only once for each debug session.
*/
extern const s1* (*clxBspGetDebugLogFileName) (void);


/* 
Returns the ABI of the current platform, as a value defined by one of CLX_ABI_ definitions above. 
If support for ClariFi control channels is enabled, this function shall be implemented in the BSP layer.
*/
extern u1 clxBsp_GetAbiID(void);



/* target processor dependent definitions */
#if defined( CLX_INTEL_X86 ) 
#   if defined(CLX_BIG_ENDIAN)
#       error "CLX_BIG_ENDIAN macro is not consistent with the platform type (Intel x86)"
#   elif !defined(CLX_LITTLE_ENDIAN)
#       define CLX_LITTLE_ENDIAN
#   endif
#   define CLX_UNALIGNED_ACCESS_ALLOWED
#endif


#if defined ( CLX_LITTLE_ENDIAN )
#   define CONVERT_TO_LITTLEENDIAN_2( x )                   ( ( u2 ) ( x ) )
#   define CONVERT_TO_LITTLEENDIAN_4( x )                   ( ( u4 ) ( x ) )
#   define CONVERT_TO_BIGENDIAN_2( x )                      ( ( u2 )( ( ( ( u2 ) ( x ) ) << 8 ) | ( ( ( u2 ) ( x ) ) >> 8 ) ) )
#   define CONVERT_TO_BIGENDIAN_4( x )                      ( ( u4 )( ( ( ( u4 ) ( x ) & 0xff000000 ) >> 24 ) | ( ( ( ( u4 ) ( x ) & 0xff0000 ) >> 8 ) ) | ( ( ( ( u4 ) ( x ) & 0xff00 ) << 8 ) ) | ( ( ( u4 ) ( x ) & 0xff ) << 24 ) ) )
#if defined(CLX_64BIT_SUPPORT)
#   define CONVERT_TO_LITTLEENDIAN_8( x )                   ( ( ull ) ( x ) )
#   define CONVERT_TO_BIGENDIAN_8( x )                      ( ( ull )( ( ( ( ull ) ( x ) & 0xff00000000000000ULL ) >> 56 ) | ( ( ( ( ull ) ( x ) & 0xff000000000000ULL ) >> 40 ) ) | ( ( ( ( ull ) ( x ) & 0xff0000000000ULL ) >> 24 ) ) | ( ( ( ull ) ( x ) & 0xff00000000ULL ) >> 8 ) | ( ( ( ull ) ( x ) & 0xff000000ULL ) << 8) | ( ( ( ( ull ) ( x ) & 0xff0000ULL ) << 24 ) ) | ( ( ( ( ull ) ( x ) & 0xff00ULL ) << 40 ) ) | ( ( ( ull ) ( x ) & 0xffULL ) << 56 ) ) )
#endif
#elif defined ( CLX_BIG_ENDIAN )
#   define CONVERT_TO_LITTLEENDIAN_2( x )                   ( ( u2 )( ( ( ( u2 ) ( x ) ) << 8 ) | ( ( ( u2 ) ( x ) ) >> 8 ) ) )
#   define CONVERT_TO_LITTLEENDIAN_4( x )                   ( ( u4 )( ( ( ( ( u4 ) ( x ) ) >> 24 ) & 0xff ) | ( ( ( ( ( u4 ) ( x ) ) >> 8 ) & 0xff00 ) ) | ( ( ( ( ( u4 ) ( x ) ) << 8 ) & 0xff0000 ) ) | ( ( ( ( u4 ) ( x ) ) << 24 ) & 0xff000000 ) ) )
#   define CONVERT_TO_BIGENDIAN_2( x )                      ( ( u2 ) ( x ) )
#   define CONVERT_TO_BIGENDIAN_4( x )                      ( ( u4 ) ( x ) )
#if defined(CLX_64BIT_SUPPORT)
#   define CONVERT_TO_LITTLEENDIAN_8( x )                   ( ( ull )( ( ( ( ( ull ) ( x ) ) >> 56 ) & 0xffULL ) | ( ( ( ( ( ull ) ( x ) ) >> 40 ) & 0xff00ULL ) ) | ( ( ( ( ( ull ) ( x ) ) >> 24 ) & 0xff0000ULL ) ) | ( ( ( ( ull ) ( x ) ) >> 8 ) & 0xff000000ULL ) | ( ( ( ( ull ) ( x ) ) << 8 ) & 0xff00000000ULL ) | ( ( ( ( ull ) ( x ) ) << 24 ) & 0xff0000000000ULL ) | ( ( ( ( ull ) ( x ) ) << 40 ) & 0xff000000000000ULL ) | ( ( ( ( ull ) ( x ) ) << 56 ) & 0xff00000000000000ULL ) ) )
#   define CONVERT_TO_BIGENDIAN_8( x )                      ( ( ull ) ( x ) )
#endif
#else
#   error "Select the platform byte order"
#endif

#if defined CLX_UNALIGNED_ACCESS_ALLOWED

#ifdef __cplusplus ////////////////////////////////////////

#	define WRITE_TO_LITTLEENDIAN_2( value, buffer )             (  *( static_cast<u2*> ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_2( value ) )
#	define WRITE_TO_LITTLEENDIAN_4( value, buffer )             (  *( static_cast<u4*> ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_4( value ) )
#	define WRITE_TO_BIGENDIAN_2( value, buffer )                (  *( static_cast<u2*> ( buffer ) ) = CONVERT_TO_BIGENDIAN_2( value ) )
#	define WRITE_TO_BIGENDIAN_4( value, buffer )                (  *( static_cast<u4*> ( buffer ) ) = CONVERT_TO_BIGENDIAN_4( value ) )
#	define READ_FROM_LITTLEENDIAN_2( buffer )                   (  CONVERT_TO_LITTLEENDIAN_2( *( static_cast<u2*> ( buffer ) ) ) )
#	define READ_FROM_LITTLEENDIAN_4( buffer )                   (  CONVERT_TO_LITTLEENDIAN_4( *( static_cast<u4*> ( buffer ) ) ) )
#	define READ_FROM_BIGENDIAN_2( buffer )                      (  CONVERT_TO_BIGENDIAN_2( *( static_cast<u2*> ( buffer ) ) ) )
#	define READ_FROM_BIGENDIAN_4( buffer )                      (  CONVERT_TO_BIGENDIAN_4( *( static_cast<u4*> ( buffer ) ) ) )
	
#	if defined(CLX_64BIT_SUPPORT)
#	   define WRITE_TO_BIGENDIAN_8( value, buffer )                (  *( static_cast<ull*> ( buffer ) ) = CONVERT_TO_BIGENDIAN_8( value ) )
#	   define WRITE_TO_LITTLEENDIAN_8( value, buffer )             (  *( static_cast<ull*> ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_8( value ) )
#	   define READ_FROM_LITTLEENDIAN_8( buffer )                   (  CONVERT_TO_LITTLEENDIAN_8( *( static_cast<ull*> ( buffer ) ) ) )
#	   define READ_FROM_BIGENDIAN_8( buffer )                      (  CONVERT_TO_BIGENDIAN_8( *( static_cast<ull*> ( buffer ) ) ) )
#	endif // CLX_64BIT_SUPPORT

#else // ifdef __cplusplus ////////////////////////////////////////
	
#	   define WRITE_TO_LITTLEENDIAN_2( value, buffer )             (  *( (u2*) ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_2( value ) )
#	   define WRITE_TO_LITTLEENDIAN_4( value, buffer )             (  *( (u4*) ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_4( value ) )
#	   define WRITE_TO_BIGENDIAN_2( value, buffer )                (  *( (u2*) ( buffer ) ) = CONVERT_TO_BIGENDIAN_2( value ) )
#	   define WRITE_TO_BIGENDIAN_4( value, buffer )                (  *( (u4*) ( buffer ) ) = CONVERT_TO_BIGENDIAN_4( value ) )
#	   define READ_FROM_LITTLEENDIAN_2( buffer )                   (  CONVERT_TO_LITTLEENDIAN_2( *( (u2*) ( buffer ) ) ) )
#	   define READ_FROM_LITTLEENDIAN_4( buffer )                   (  CONVERT_TO_LITTLEENDIAN_4( *( (u4*) ( buffer ) ) ) )
#	   define READ_FROM_BIGENDIAN_2( buffer )                      (  CONVERT_TO_BIGENDIAN_2( *( (u2*) ( buffer ) ) ) )
#	   define READ_FROM_BIGENDIAN_4( buffer )                      (  CONVERT_TO_BIGENDIAN_4( *( (u4*) ( buffer ) ) ) )
	
#	if defined(CLX_64BIT_SUPPORT)
#	   define WRITE_TO_BIGENDIAN_8( value, buffer )                (  *( (ull*) ( buffer ) ) = CONVERT_TO_BIGENDIAN_8( value ) )
#	   define WRITE_TO_LITTLEENDIAN_8( value, buffer )             (  *( (ull*) ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_8( value ) )
#	   define READ_FROM_LITTLEENDIAN_8( buffer )                   (  CONVERT_TO_LITTLEENDIAN_8( *( (ull*) ( buffer ) ) ) )
#	   define READ_FROM_BIGENDIAN_8( buffer )                      (  CONVERT_TO_BIGENDIAN_8( *( (ull*) ( buffer ) ) ) )
#	endif // CLX_64BIT_SUPPORT

#endif // __cplusplus ////////////////////////////////////////

#   define WRITE_TO_LITTLEENDIAN_2_ALIGNED( value, buffer )		WRITE_TO_LITTLEENDIAN_2( ( value ), ( buffer ) )
#   define WRITE_TO_LITTLEENDIAN_4_ALIGNED( value, buffer )     WRITE_TO_LITTLEENDIAN_4( ( value ), ( buffer ) )
#   define WRITE_TO_BIGENDIAN_2_ALIGNED( value, buffer )		WRITE_TO_BIGENDIAN_2( ( value ), ( buffer ) )
#   define WRITE_TO_BIGENDIAN_4_ALIGNED( value, buffer )		WRITE_TO_BIGENDIAN_4( ( value ), ( buffer ) )
#   define READ_FROM_LITTLEENDIAN_2_ALIGNED( buffer )			READ_FROM_LITTLEENDIAN_2( buffer )
#   define READ_FROM_LITTLEENDIAN_4_ALIGNED( buffer )			READ_FROM_LITTLEENDIAN_4( buffer )
#   define READ_FROM_BIGENDIAN_2_ALIGNED( buffer )				READ_FROM_BIGENDIAN_2( buffer )
#   define READ_FROM_BIGENDIAN_4_ALIGNED( buffer )				READ_FROM_BIGENDIAN_4( buffer )

#if defined(CLX_64BIT_SUPPORT)
#   define WRITE_TO_BIGENDIAN_8_ALIGNED( value, buffer )        WRITE_TO_BIGENDIAN_8( ( value ), ( buffer ) )
#   define WRITE_TO_LITTLEENDIAN_8_ALIGNED( value, buffer )     WRITE_TO_LITTLEENDIAN_8( ( value ), ( buffer ) )
#   define READ_FROM_LITTLEENDIAN_8_ALIGNED( buffer )           READ_FROM_LITTLEENDIAN_8( buffer )
#   define READ_FROM_BIGENDIAN_8_ALIGNED( buffer )              READ_FROM_BIGENDIAN_8( buffer ) 
#endif

#else // #if defined CLX_UNALIGNED_ACCESS_ALLOWED

#   define WRITE_TO_LITTLEENDIAN_2( value, buffer )             (  writeToUnaligned16( CONVERT_TO_LITTLEENDIAN_2( value ), ( buffer ) ) )
#   define WRITE_TO_LITTLEENDIAN_4( value, buffer )             (  writeToUnaligned( CONVERT_TO_LITTLEENDIAN_4( value ), ( buffer ) ) )
#   define WRITE_TO_BIGENDIAN_2( value, buffer )                (  writeToUnaligned16( CONVERT_TO_BIGENDIAN_2( value ), ( buffer ) ) )
#   define WRITE_TO_BIGENDIAN_4( value, buffer )                (  writeToUnaligned( CONVERT_TO_BIGENDIAN_4( value ), ( buffer ) ) )
#   define READ_FROM_LITTLEENDIAN_2( buffer )                   (  CONVERT_TO_LITTLEENDIAN_2( readFromUnaligned16( buffer ) ) )
#   define READ_FROM_LITTLEENDIAN_4( buffer )                   (  CONVERT_TO_LITTLEENDIAN_4( readFromUnaligned( buffer ) ) )
#   define READ_FROM_BIGENDIAN_2( buffer )                      (  CONVERT_TO_BIGENDIAN_2( readFromUnaligned16( buffer ) ) )
#   define READ_FROM_BIGENDIAN_4( buffer )                      (  CONVERT_TO_BIGENDIAN_4( readFromUnaligned( buffer ) ) )

#if defined(CLX_64BIT_SUPPORT)
#   define WRITE_TO_LITTLEENDIAN_8( value, buffer )             (  writeToUnaligned64( CONVERT_TO_LITTLEENDIAN_8( value ), ( buffer ) ) )
#   define WRITE_TO_BIGENDIAN_8( value, buffer )                (  writeToUnaligned64( CONVERT_TO_BIGENDIAN_8( value ), ( buffer ) ) )
#   define READ_FROM_LITTLEENDIAN_8( buffer )                   (  CONVERT_TO_LITTLEENDIAN_8( readFromUnaligned64( buffer ) ) )
#   define READ_FROM_BIGENDIAN_8( buffer )                      (  CONVERT_TO_BIGENDIAN_8( readFromUnaligned64( buffer ) ) )
#endif

#ifdef __cplusplus ////////////////////////////////////////

#   define WRITE_TO_LITTLEENDIAN_2_ALIGNED( value, buffer )     (  *( static_cast<u2*> ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_2( value ) )
#   define WRITE_TO_LITTLEENDIAN_4_ALIGNED( value, buffer )     (  *( static_cast<u4*> ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_4( value ) )
#   define WRITE_TO_BIGENDIAN_2_ALIGNED( value, buffer )        (  *( static_cast<u2*> ( buffer ) ) = CONVERT_TO_BIGENDIAN_2( value ) )
#   define WRITE_TO_BIGENDIAN_4_ALIGNED( value, buffer )        (  *( static_cast<u4*> ( buffer ) ) = CONVERT_TO_BIGENDIAN_4( value ) )
#   define READ_FROM_LITTLEENDIAN_2_ALIGNED( buffer )           (  CONVERT_TO_LITTLEENDIAN_2( *( static_cast<u2*> ( buffer ) ) ) )
#   define READ_FROM_LITTLEENDIAN_4_ALIGNED( buffer )           (  CONVERT_TO_LITTLEENDIAN_4( *( static_cast<u4*> ( buffer ) ) ) )
#   define READ_FROM_BIGENDIAN_2_ALIGNED( buffer )              (  CONVERT_TO_BIGENDIAN_2( *( static_cast<u2*> ( buffer ) ) ) )
#   define READ_FROM_BIGENDIAN_4_ALIGNED( buffer )              (  CONVERT_TO_BIGENDIAN_4( *( static_cast<u4*> ( buffer ) ) ) )

#if defined(CLX_64BIT_SUPPORT)
#   define WRITE_TO_BIGENDIAN_8_ALIGNED( value, buffer )        (  *( static_cast<ull*> ( buffer ) ) = CONVERT_TO_BIGENDIAN_8( value ) )
#   define WRITE_TO_LITTLEENDIAN_8_ALIGNED( value, buffer )     (  *( static_cast<ull*> ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_8( value ) )
#   define READ_FROM_LITTLEENDIAN_8_ALIGNED( buffer )           (  CONVERT_TO_LITTLEENDIAN_8( *( static_cast<ull*> ( buffer ) ) ) )
#   define READ_FROM_BIGENDIAN_8_ALIGNED( buffer )              (  CONVERT_TO_BIGENDIAN_8( *( static_cast<ull*> ( buffer ) ) ) )
#endif

#else // ifdef __cplusplus ////////////////////////////////////////

#   define WRITE_TO_LITTLEENDIAN_2_ALIGNED( value, buffer )     (  *( (u2*) ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_2( value ) )
#   define WRITE_TO_LITTLEENDIAN_4_ALIGNED( value, buffer )     (  *( (u4*) ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_4( value ) )
#   define WRITE_TO_BIGENDIAN_2_ALIGNED( value, buffer )        (  *( (u2*) ( buffer ) ) = CONVERT_TO_BIGENDIAN_2( value ) )
#   define WRITE_TO_BIGENDIAN_4_ALIGNED( value, buffer )        (  *( (u4*) ( buffer ) ) = CONVERT_TO_BIGENDIAN_4( value ) )
#   define READ_FROM_LITTLEENDIAN_2_ALIGNED( buffer )           (  CONVERT_TO_LITTLEENDIAN_2( *( (u2*) ( buffer ) ) ) )
#   define READ_FROM_LITTLEENDIAN_4_ALIGNED( buffer )           (  CONVERT_TO_LITTLEENDIAN_4( *( (u4*) ( buffer ) ) ) )
#   define READ_FROM_BIGENDIAN_2_ALIGNED( buffer )              (  CONVERT_TO_BIGENDIAN_2( *( (u2*) ( buffer ) ) ) )
#   define READ_FROM_BIGENDIAN_4_ALIGNED( buffer )              (  CONVERT_TO_BIGENDIAN_4( *( (u4*) ( buffer ) ) ) )

#if defined(CLX_64BIT_SUPPORT)
#   define WRITE_TO_BIGENDIAN_8_ALIGNED( value, buffer )        (  *( (ull*) ( buffer ) ) = CONVERT_TO_BIGENDIAN_8( value ) )
#   define WRITE_TO_LITTLEENDIAN_8_ALIGNED( value, buffer )     (  *( (ull*) ( buffer ) ) = CONVERT_TO_LITTLEENDIAN_8( value ) )
#   define READ_FROM_LITTLEENDIAN_8_ALIGNED( buffer )           (  CONVERT_TO_LITTLEENDIAN_8( *( (ull*) ( buffer ) ) ) )
#   define READ_FROM_BIGENDIAN_8_ALIGNED( buffer )              (  CONVERT_TO_BIGENDIAN_8( *( (ull*) ( buffer ) ) ) )
#endif

#endif // __cplusplus ////////////////////////////////////////

#endif // #if defined CLX_UNALIGNED_ACCESS_ALLOWED


#if defined(CLX_FLOATING_POINT_SUPPORTED)
extern void writeFloatToLittleEndianUnaligned(r4 value, u4* buffer);
extern void writeDoubleToLittleEndianUnaligned(r8 value, u4* buffer);
extern void writeFloatToLittleEndianAligned(r4 value, u4* buffer);
extern void writeDoubleToLittleEndianAligned(r8 value, u4* buffer);

extern void writeFloatToBigEndianUnaligned(r4 value, u4* buffer);
extern void writeDoubleToBigEndianUnaligned(r8 value, u4* buffer);
extern void writeFloatToBigEndianAligned(r4 value, u4* buffer);
extern void writeDoubleToBigEndianAligned(r8 value, u4* buffer);

extern r4 readFloatFromLittleEndianUnaligned(const u4* buffer);
extern r8 readDoubleFromLittleEndianUnaligned(const u4* buffer);
extern r4 readFloatFromLittleEndianAligned(const u4* buffer);
extern r8 readDoubleFromLittleEndianAligned(const u4* buffer);

extern r4 readFloatFromBigEndianUnaligned(const u4* buffer);
extern r8 readDoubleFromBigEndianUnaligned(const u4* buffer);
extern r4 readFloatFromBigEndianAligned(const u4* buffer);
extern r8 readDoubleFromBigEndianAligned(const u4* buffer);
#endif


#   define WRITE_TO_LITTLEENDIAN_3( value, buffer )                 \
    ((buffer)[0]) = (u1)((u4)(value) & 0x000000FF);                   \
    ((buffer)[1]) = (u1)(((u4)(value) & 0x0000FF00) >> 8);            \
    ((buffer)[2]) = (u1)(((u4)(value) & 0x00FF0000) >> 16)


#   define WRITE_TO_BIGENDIAN_3( value, buffer )                    \
    ((buffer)[2]) = (u1)((u4)(value) & 0x000000FF);                   \
    ((buffer)[1]) = (u1)(((u4)(value) & 0x0000FF00) >> 8);            \
    ((buffer)[0]) = (u1)(((u4)(value) & 0x00FF0000) >> 16)
    
#   define READ_FROM_LITTLEENDIAN_3( buffer )                       ( (u4)((u1*)((buffer)[0])) | ((u4)((u1*)((buffer)[1])) << 8) | ((u4)((u1*)((buffer)[2])) << 16) ) 
#   define READ_FROM_BIGENDIAN_3( buffer )                          ( (u4)((u1*)((buffer)[2])) | ((u4)((u1*)((buffer)[1])) << 8) | ((u4)((u1*)((buffer)[0])) << 16) ) 

/*  value shall be of type ClxUInteger64 or ClxSInteger64 */
#   define WRITE_TO_LITTLEENDIAN_5( value, buffer )                 \
    ((buffer)[0]) = (u1)((u4)((value).lsb) & 0x000000FF);               \
    ((buffer)[1]) = (u1)(((u4)((value).lsb) & 0x0000FF00) >> 8);        \
    ((buffer)[2]) = (u1)(((u4)((value).lsb) & 0x00FF0000) >> 16);       \
    ((buffer)[3]) = (u1)(((u4)((value).lsb) & 0xFF000000) >> 24);       \
    ((buffer)[4]) = (u1)((u4)((value).msb) & 0x000000FF)

/*  value shall be of type ClxUInteger64 or ClxSInteger64 */
#   define WRITE_TO_BIGENDIAN_5( value, buffer )                    \
    ((buffer)[4]) = (u1)((u4)((value).lsb) & 0x000000FF);                   \
    ((buffer)[3]) = (u1)(((u4)((value).lsb) & 0x0000FF00) >> 8);            \
    ((buffer)[2]) = (u1)(((u4)((value).lsb) & 0x00FF0000) >> 16);           \
    ((buffer)[1]) = (u1)(((u4)((value).lsb) & 0xFF000000) >> 24);           \
    ((buffer)[0]) = (u1)((u4)((value).msb) & 0x000000FF)

/*  
    value shall be of one of the following types :
    ClxUInteger64 : type shall be set to u4
    ClxSInteger64 : type shall be set to s4 
*/
#   define READ_FROM_LITTLEENDIAN_5( value, type, buffer )                                                                                            \
    ((value).lsb) = (type)( (u4)((u1*)((buffer)[0])) | ((u4)((u1*)((buffer)[1])) << 8) | ((u4)((u1*)((buffer)[2])) << 16) | ((u4)((u1*)((buffer)[3])) << 24) ); \
    ((value).msb) = (type)((u1*)((buffer)[4]))

/*  
    value shall be of one of the following types :
    ClxUInteger64 : type shall be set to u4
    ClxSInteger64 : type shall be set to s4 
*/
#   define READ_FROM_BIGENDIAN_5( value, type, buffer )                                                                                               \
    ((value).lsb) = (type)( (u4)((u1*)((buffer)[4])) | ((u4)((u1*)((buffer)[3])) << 8) | ((u4)((u1*)((buffer)[2])) << 16) | ((u4)((u1*)((buffer)[1])) << 24) ); \
    ((value).msb) = (type)((u1*)((buffer)[0]))


/*  value shall be of type ClxUInteger64 or ClxSInteger64 */
#   define WRITE_TO_LITTLEENDIAN_6( value, buffer )                     \
    ((buffer)[0]) = (u1)((u4)((value).lsb) & 0x000000FF);                   \
    ((buffer)[1]) = (u1)(((u4)((value).lsb) & 0x0000FF00) >> 8);            \
    ((buffer)[2]) = (u1)(((u4)((value).lsb) & 0x00FF0000) >> 16);           \
    ((buffer)[3]) = (u1)(((u4)((value).lsb) & 0xFF000000) >> 24);           \
    ((buffer)[4]) = (u1)((u4)((value).msb) & 0x000000FF);                   \
    ((buffer)[5]) = (u1)(((u4)((value).msb) & 0x0000FF00) >> 8)


/*  value shall be of type ClxUInteger64 or ClxSInteger64 */
#   define WRITE_TO_BIGENDIAN_6( value, buffer )                        \
    ((buffer)[5]) = (u1)((u4)((value).lsb) & 0x000000FF);                   \
    ((buffer)[4]) = (u1)(((u4)((value).lsb) & 0x0000FF00) >> 8);            \
    ((buffer)[3]) = (u1)(((u4)((value).lsb) & 0x00FF0000) >> 16);           \
    ((buffer)[2]) = (u1)(((u4)((value).lsb) & 0xFF000000) >> 24);           \
    ((buffer)[1]) = (u1)((u4)((value).msb) & 0x000000FF);                   \
    ((buffer)[0]) = (u1)(((u4)((value).msb) & 0x0000FF00) >> 8)

/*  
    value shall be of one of the following types :
    ClxUInteger64 : type shall be set to u4
    ClxSInteger64 : type shall be set to s4 
*/
#   define READ_FROM_LITTLEENDIAN_6( value, type, buffer )                                                                                            \
    ((value).lsb) = (type)( (u4)((u1*)((buffer)[0])) | ((u4)((u1*)((buffer)[1])) << 8) | ((u4)((u1*)((buffer)[2])) << 16) | ((u4)((u1*)((buffer)[3])) << 24) ); \
    ((value).msb) = (type)( (u4)((u1*)((buffer)[4])) | ((u4)((u1*)((buffer)[5])) << 8) )

/*  
    value shall be of one of the following types :
    ClxUInteger64 : type shall be set to u4
    ClxSInteger64 : type shall be set to s4 
*/
#   define READ_FROM_BIGENDIAN_6( value, type, buffer )                                                                                               \
    ((value).lsb) = (type)( (u4)((u1*)((buffer)[5])) | ((u4)((u1*)((buffer)[4])) << 8) | ((u4)((u1*)((buffer)[3])) << 16) | ((u4)((u1*)((buffer)[2])) << 24) ); \
    ((value).msb) = (type)( (u4)((u1*)((buffer)[1])) | ((u4)((u1*)((buffer)[0])) << 8) )


#if !defined(CLX_64BIT_SUPPORT)
/*  value shall be of type ClxUInteger64 or ClxSInteger64 */
#   define WRITE_TO_LITTLEENDIAN_8( value, buffer )                     \
    do{                                                                 \
    WRITE_TO_LITTLEENDIAN_4(((value).lsb), (u4*)(buffer));              \
    WRITE_TO_LITTLEENDIAN_4(((value).msb), ((u4*)(buffer) + 1));        \
    }while(0)


/*  value shall be of type ClxUInteger64 or ClxSInteger64 */
#   define WRITE_TO_BIGENDIAN_8( value, buffer )                        \
    do{                                                                 \
    WRITE_TO_BIGENDIAN_4(((value).msb), (u4*)(buffer));                 \
    WRITE_TO_BIGENDIAN_4(((value).lsb), ((u4*)(buffer) + 1));           \
    }while(0)

/*  
    value shall be of one of the following types :
    ClxUInteger64 : type shall be set to u4
    ClxSInteger64 : type shall be set to s4 
*/
#   define READ_FROM_LITTLEENDIAN_8( value, type, buffer )				\
    ((value).lsb) = (type)READ_FROM_LITTLEENDIAN_4(((u4*)(buffer)));		\
    ((value).msb) = (type)READ_FROM_LITTLEENDIAN_4(((u4*)(buffer) + 1))

/*  
    value shall be of one of the following types :
    ClxUInteger64 : type shall be set to u4
    ClxSInteger64 : type shall be set to s4 
*/
#   define READ_FROM_BIGENDIAN_8( value, type, buffer )					\
    ((value).msb) = (type)READ_FROM_BIGENDIAN_4(((u4*)(buffer)));			\
    ((value).lsb) = (type)READ_FROM_BIGENDIAN_4(((u4*)(buffer) + 1))

#endif // #if !defined(CLX_64BIT_SUPPORT)


/*  value shall be of type ClxUInteger128 or ClxSInteger128 */
#   define WRITE_TO_LITTLEENDIAN_16( value, buffer )					 \
    do{                                                                  \
    WRITE_TO_LITTLEENDIAN_4(((value).lsb.lsb), ((u4*)(buffer)));         \
    WRITE_TO_LITTLEENDIAN_4(((value).lsb.msb), ((u4*)(buffer) + 1));     \
    WRITE_TO_LITTLEENDIAN_4(((value).msb.lsb), ((u4*)(buffer) + 2));     \
    WRITE_TO_LITTLEENDIAN_4(((value).msb.msb), ((u4*)(buffer) + 3));     \
    }while (0)


/*  value shall be of type ClxUInteger128 or ClxSInteger128 */
#   define WRITE_TO_BIGENDIAN_16( value, buffer )						\
    do{                                                                 \
    WRITE_TO_BIGENDIAN_4(((value).msb.msb), ((u4*)(buffer)));			\
    WRITE_TO_BIGENDIAN_4(((value).msb.lsb), ((u4*)(buffer) + 1));		\
    WRITE_TO_BIGENDIAN_4(((value).lsb.msb), ((u4*)(buffer) + 2));		\
    WRITE_TO_BIGENDIAN_4(((value).lsb.lsb), ((u4*)(buffer) + 3));       \
    }while (0)


/*  
    value shall be of one of the following types :
    ClxUInteger128 : type shall be set to u4
    ClxSInteger128 : type shall be set to s4 
*/
#   define READ_FROM_LITTLEENDIAN_16( value, type, buffer )					\
    ((value).lsb.lsb) = (type)READ_FROM_LITTLEENDIAN_4(((u4*)(buffer)));		\
    ((value).lsb.msb) = (type)READ_FROM_LITTLEENDIAN_4(((u4*)(buffer) + 1));	\
    ((value).msb.lsb) = (type)READ_FROM_LITTLEENDIAN_4(((u4*)(buffer) + 2));	\
    ((value).msb.msb) = (type)READ_FROM_LITTLEENDIAN_4(((u4*)(buffer) + 3))


/*  
    value shall be of one of the following types :
    ClxUInteger128 : type shall be set to u4
    ClxSInteger128 : type shall be set to s4 
*/
#   define READ_FROM_BIGENDIAN_16( value, type, buffer )					\
    ((value).msb.msb) = (type)READ_FROM_BIGENDIAN_4(((u4*)(buffer)));			\
    ((value).msb.lsb) = (type)READ_FROM_BIGENDIAN_4(((u4*)(buffer) + 1));		\
    ((value).lsb.msb) = (type)READ_FROM_BIGENDIAN_4(((u4*)(buffer) + 2));		\
    ((value).lsb.lsb) = (type)READ_FROM_BIGENDIAN_4(((u4*)(buffer) + 3))


#ifdef __cplusplus
}
#endif


#endif // ClxBsp_h

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : A function should be used in preference to a function-like */
/*                 macro.                                                     */ 
/* Rule          : MISRA-C:2004 Rule 19.7                                     */ 
/* Justification : No risk identified. Used to provide better performance in  */
/*                 embedded system environments that do not support efficient */
/*				   functions inlining.                                        */
/******************************************************************************/

/******************************************************************************/
/* 1. MISRA C 2004 RULE VIOLATION:                                            */
/* Message       : Identifiers (internal and external) shall not rely on the  */
/*                 significance of more than 31 characters.                   */
/* Rule          : MISRA-C:2004 Rule 5.1                                      */
/* Justification : Improves clarity of macro definitions. The compiler used   */
/*                 supports symbols longer than 31 characters, hence no risks.*/
/******************************************************************************/


/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused type declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.3                                      */ 
/* Justification : Unused type declarations are to be used in user 		      */
/* 				   applications.      										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/
