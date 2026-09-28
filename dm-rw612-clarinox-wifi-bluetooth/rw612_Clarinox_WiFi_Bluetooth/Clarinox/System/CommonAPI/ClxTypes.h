#ifndef ClxTypes_h
#define ClxTypes_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxTypes.h
* Description         Clarinox Type definitions
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/



/* 
CLX_REQUIRED_ALIGNMENT is the required alignment for dynamically allocated memory buffers in the system. 
This value SHALL be a power of 2.
*/
#if !defined(CLX_REQUIRED_ALIGNMENT)
#   define CLX_REQUIRED_ALIGNMENT       4   /* SHALL be an integer literal since the actual value of CLX_REQUIRED_ALIGNMENT shall be known at pre-processing time.
                                               DO NOT USE non-literal values such as "sizeof(void*)" or alike */
#endif


/* Sanity check for CLX_REQUIRED_ALIGNMENT: */
#if CLX_REQUIRED_ALIGNMENT >= 8 
#   if !defined(CLX_64BIT_SUPPORT)
#       error "Define CLX_64BIT_SUPPORT when CLX_REQUIRED_ALIGNMENT >= 8"
#   endif
#elif CLX_REQUIRED_ALIGNMENT == 4
#else
#   error "CLX_REQUIRED_ALIGNMENT must be either 4 or a value equal or higher than 8"
#endif



#ifdef __cplusplus
extern "C" {
#endif


// _____________________________________________________________________________
//
// ClxTypes
// _____________________________________________________________________________
//

#if defined( CLX_CLANG )        ||      \
    defined( CLX_GNU )          ||      \
    defined( CLX_MICROSOFT )    ||      \
    defined( CLX_MULTI )        ||      \
    defined( CLX_IAR )          ||      \
    defined( CLX_KEIL )         ||      \
    defined( CLX_CGT_C6000 )    ||      \
    defined( CLX_SHC)           ||      \
    defined(CLX_ARM_DS5)        ||      \
    defined(CLX_ARM_RVDS)       ||      \
    defined(CLX_CCS)            ||      \
    defined(CLX_DIAB)           ||      \
    defined (CLX_TASKING)

/**
One byte signed:                        s1
*/
typedef          char                   s1;

/**
One byte unsigned:                      u1
*/
typedef unsigned char                   u1;

/**
Two bytes signed:                       s2
*/
typedef          short                  s2;

/**
Two bytes unsigned:                     u2
*/
typedef unsigned short                  u2;

/**
Four bytes signed:                      s4
*/
typedef          int                    s4;

/**
Four bytes unsigned:                    u4
*/
typedef unsigned int                    u4;

#   if defined(CLX_64BIT_SUPPORT)
#       if defined( CLX_MICROSOFT )
        typedef unsigned __int64        ull;
        typedef          __int64        sll;
#       else
        typedef unsigned long long      ull;
        typedef          long long      sll;
#       endif
#   endif // CLX_64BIT_SUPPORT

#   if defined(CLX_FLOATING_POINT_SUPPORTED)
    typedef          float              r4;
    typedef          double             r8;
#   endif


#   if defined (CLX_MICROSAR)
    /**
    With Vector MICROSAR OS, typedef boolean defined in "Platform_Types.h" header 
    file causes a redeclaration error with the boolean typedef defined here when 
    pure C compilation is used. If Vector MICROSAR OS header file is used do not 
    type define boolean.
    */
#       if !defined (PLATFORM_TYPES_H)
        typedef unsigned char           boolean;
#       endif

#   else

    typedef unsigned char               boolean;

#   endif /* #if defined (CLX_MICROSAR) */

/**
Size (of buffers, data structures . . .)
*/
typedef unsigned int                    ClxSize;

/**
Result of an operation (API call, ...)
*/
typedef int                             ClxResult;

/** 
Represents an API error - obsolete 
*/
typedef ClxResult                       ClxError;

#elif defined( CLX_CODE_COMPOSER )

typedef          char                   s1; // There is no single byte type support for TI 55x processors
typedef unsigned char                   u1;
typedef          short                  s2;
typedef unsigned short                  u2;
typedef          long                   s4;
typedef unsigned long                   u4;

#   if defined(CLX_64BIT_SUPPORT)
    typedef          long long          sll;
    typedef unsigned long long          ull;
#   endif

#   if defined(CLX_FLOATING_POINT_SUPPORTED)
    typedef float                       r4;
    typedef double                      r8;
#   endif

typedef unsigned char                   boolean;

#else

#   error "Define your compiler specific types here"

#endif /* Compiler definition */


/* 
The following macro is used for unused parameter warning in functions;
    myFunc(aParam)
    {
        UNUSED(aParam);
    }
*/

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif


#if defined( CLX_MICROSOFT ) || defined(CLX_CLANG)
#   define ATTRIBUTE_ALIGNED
    typedef void*           HANDLE;
    typedef HANDLE      CLX_HANDLE;
#elif defined( CLX_GNU )
#   if !defined( CLX_UNALIGNED_ACCESS_ALLOWED )
#       define ATTRIBUTE_ALIGNED __attribute__ ((aligned (4)))
#   else
#       define ATTRIBUTE_ALIGNED
#   endif
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE;
#elif defined( CLX_TASKING )
typedef void* LPVOID;           
typedef u4  UINT;             
typedef void*  CLX_HANDLE;       
#elif defined( CLX_MULTI )
#   define ATTRIBUTE_ALIGNED __attribute__ ((aligned (4)))
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE;
#elif defined( CLX_CODE_COMPOSER ) || defined( CLX_CGT_C6000 )
#   define ATTRIBUTE_ALIGNED
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE;
#   elif defined ( CLX_IAR )
typedef void* CLX_HANDLE;
#   elif defined ( CLX_KEIL )
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE;
#   elif defined ( CLX_SHC )
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE;  
#   elif defined ( CLX_DIAB )
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE; 
#   elif defined ( CLX_CCS )
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE;
#   elif defined ( CLX_ARM_DS5 )
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE;
#   elif defined ( CLX_ARM_RVDS )
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE;
#elif defined ( CLX_QNX )
typedef void* LPVOID;
typedef u4 UINT;
typedef void* CLX_HANDLE;
#else
#   error "Define your OS/Compiler specific definitions here"
#endif // defined( CLX_WINDOWS )

#ifndef TRUE
#    define TRUE 1
#endif
#ifndef FALSE
#    define FALSE 0
#endif
#ifndef NULL
#    define NULL 0
#endif

/*
Simple parametric alignment macro.
If building for Linux/GNU, apply alignment with the given parameter.
On other platforms, expand to nothing.
Usage: struct MyStruct { ... } CLX_ALIGNED(8);
*/
#if defined(CLX_LINUX) || defined(CLX_GNU)
#   define CLX_ALIGNED(n) __attribute__((aligned(n)))
#else
#   define CLX_ALIGNED(n)
#endif


/* 
The type definition ClxMaxAlignType defines a scalar type whose alignment requirement is at least as large as that of every scalar type.
This type is used to define a placement buffer (a buffer which holds an allocated C++ object). 
If not defined in the project/make file, the default value of u4 (for 32-bit systems) will be used.
*/
#if !defined(ClxMaxAlignType)
#   if CLX_REQUIRED_ALIGNMENT == 8
        typedef ull ClxMaxAlignType;
#   elif CLX_REQUIRED_ALIGNMENT == 4
        typedef u4 ClxMaxAlignType;
#   else
#       error "Define ClxMaxAlignType for your platform"
#   endif
#endif


typedef struct ClxUInteger64Struct
{
    u4 msb;
    u4 lsb;
} ClxUInteger64;

typedef struct ClxUInteger128Struct
{
    ClxUInteger64 msb;
    ClxUInteger64 lsb;
} ClxUInteger128;

typedef struct ClxSInteger64Struct
{
    u4 msb;
    u4 lsb;
} ClxSInteger64;

typedef struct ClxSInteger128Struct
{
    ClxSInteger64 msb;
    ClxSInteger64 lsb;
} ClxSInteger128;



#if !defined( CHECK_IF_ARG_NULL_IN_CREATE )
#define CHECK_IF_ARG_NULL_IN_CREATE(value)                                      \
do{                                                                             \
	if((value) == 0)                                                            \
    {                                                                           \
        return 0;                                                               \
    }                                                                           \
}while (0)
#endif

#if !defined( CHECK_IF_ARG_NULL )
#define CHECK_IF_ARG_NULL(value)                                                \
do{                                                                             \
	if((value) == 0)                                                            \
    {                                                                           \
        return CLX_ERROR_INVALID_COMMAND_PARAMETER;                             \
    }                                                                           \
}while(0)
#endif

#if !defined( CLX_UNKNOWN_ITEM )
#define CLX_UNKNOWN_ITEM (-1)
#endif


#ifdef __cplusplus
}
#endif


/** \file ClxTypes.h
    \brief ClxTypes.h contains the Clarinox type information
*/

#endif    // ClxTypes_h

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : Sections of code should not be commented out.              */ 
/* Rule          : MISRA-C:2004 Rule 2.4                                      */ 
/* Justification : Inside comment section, example of code is given for       */
/*				   clarity.											          */
/*                 Only used for example code to clarify the use.             */
/*                 As we generate API documentation from header files         */
/*				   (using Doxygen), this is necessary.                        */
/******************************************************************************/

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

