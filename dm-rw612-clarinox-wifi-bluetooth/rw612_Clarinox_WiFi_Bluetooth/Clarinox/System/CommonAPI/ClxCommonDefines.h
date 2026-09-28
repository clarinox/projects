#ifndef ClxCommonDefines_h
#define ClxCommonDefines_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxCommonDefines.h
* Description         ClarinoxSoftFrame Common header file
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


 
#define CD_API


/* Identifies a function which may return CLX_ERROR_COMPLETION_PENDING and the function will be complete asynchronously */
#define CLX_ASYNC

/*
Represents a static method function in a C structure. The behaviour of the function is defined to be equivalent to a static method of a C++ class. 

Example:

struct SomeStruct
{
	CLX_STATIC_METHOD void (*staticMethod) (...);
	void (*nonStaticMethod) (struct SomeStruct* this_, ...); 
};
*/
#define CLX_STATIC_METHOD

/*
Calculates a/b. If the result is not an integer, the result is rounded up to next integer value.
*/
#define CLX_DIVIDE_AND_ROUND(a, b)        (((a) + (b) - 1) / (b))

/* 
Defines a data buffer of the given size (in byes), which is guaranteed to be 16bit aligned in the memory.
*/
#define CLX_ALIGNED_BUFFER_2(name, size)  u2 (name)[((size) + 1)/2] 

/* 
Defines a data buffer of the given size (in byes), which is guaranteed to be 32bit aligned in the memory.
*/
#define CLX_ALIGNED_BUFFER_4(name, size)  u4 (name)[((size) + 3)/4] 

/* 
Defines a data buffer of the given size (in byes), which is guaranteed to be aligned in the memory at the maximum alignment required in the current platform (as defined by ClxMaxAlignType).
*/
#define CLX_PLATFORM_ALIGNED_BUFFER(name, size)  ClxMaxAlignType (name)[((size) + (sizeof(ClxMaxAlignType) - 1))/sizeof(ClxMaxAlignType)] 


/*
Returns the number of elements in a variable of fixed-sized C array type. e.g. VarType varName[N]; CLX_NUM_OF_ELEMENTS_IN_ARRAY(varName) == N
*/
#define CLX_NUM_OF_ELEMENTS_IN_ARRAY(varName)       (sizeof((varName)) / sizeof((varName)[0]))


#ifdef __cplusplus
#define CLX_OFFSET_OF(Type, member) ((size_t)reinterpret_cast<const s1*>(&(((Type*)0)->member)))
#else
#define CLX_OFFSET_OF(Type, member) ((size_t)&(((Type*)0)->member))
#endif


/* 
The qualifier Clx16bitAligned_ is added to a buffer pointer definition to specify that the variable points to
a buffer in the memory which is at least 16bit aligned:
*/
#define Clx16bitAligned_

/* 
The qualifier Clx32bitAligned_ is added to a buffer pointer definition to specify that the variable points to
a buffer in the memory which is at least 32bit aligned:
*/
#define Clx32bitAligned_

/* 
The qualifier ClxPlatformAligned_ is added to a buffer pointer definition to specify that the variable points to
a buffer in the memory which is aligned according to the value of CLX_REQUIRED_ALIGNMENT:
*/
#define ClxPlatformAligned_

/*
Returns a value with only the specified bit set, and all other bits are reset. The total number
of bits in the return value depends on the type casting used:
*/
#define CLX_SET_BIT(bit)  ((size_t)(1 << (bit)))


#define CLX_INFINITE    0xFFFFFFFF


/**
Returns a value of equal to or larger than originalSize which is aligned with (divisible by) requiredAlignment.
IMPORTANT : requiredAlignment MUST be a power of 2 (e.g. 2, 4, 16, 256, 2048, ...).
*/
#define CLX_ALIGNED_SIZE(originalSize, requiredAlignment)   ((originalSize) + (((requiredAlignment) - ((originalSize) & ((requiredAlignment)-1))) & ((requiredAlignment)-1)))

#define GET_16BIT_ALIGNED_SIZE(size)  CLX_ALIGNED_SIZE((size), 2)
#define GET_32BIT_ALIGNED_SIZE(size)  CLX_ALIGNED_SIZE((size), 4)

#define GET_PLATFORM_ALIGNED_SIZE(size)  CLX_ALIGNED_SIZE((size), CLX_REQUIRED_ALIGNMENT)


#define CLX_MAC_ADDRESS_LENGTH				                                 6
#define CLX_IPV4_ADDRESS_LENGTH				                                 4


#ifndef MAX
#   define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#endif
#ifndef MIN
#   define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#endif


/** 
clxDoNothing is used when a variadic macro needs to be mapped to nothing. 
*/
#if defined(CLX_VARIADIC_MACROS_SUPPORTED)
#   define clxDoNothing(...);
#endif


#if defined(CLX_DEBUG)
#   define CLX_DEBUG_STR(str)	str
#else
#   define CLX_DEBUG_STR(str)	NULL
#endif



/*
Returns a value which uniquely identifies the type of a C structure at run time.
*/
#define CLX_C_STRUCTURE_TYPE(StructureName)                     (void*)&_ClxCObjectType_##StructureName

/*
Defines RunTime Type Information (RTTI) for a C structure and associates it to the structure. 
RTTI is a unique number across the application which is used to identify the type of a C object at run time.
The macro CLX_C_STRUCTURE_TYPE returns the type for a structure which has been associated RTTI.
*/
#define CLX_DECLARE_C_OBJECT_RTTI(StructureName)                 extern const u1 _ClxCObjectType_##StructureName

/*
Instantiates RunTime Type Information for a C structure which is associated RTTI using the macro CLX_DECLARE_C_OBJECT_RTTI.
This macro must be called in a C or C++ file in order to assign a unique number to the C structure at link time. The
number can then be used to identify the type of a C object at run time.

Example:

Define a base structure which RTTI capability as follows:

struct BaseStruct
{
    void* rtti;
};

Now, you can define different structures of different types which all derive from BaseStruct as follows:

struct Struct1
{
    struct BaseStruct;      // Simulation of C++ inheritance in C. SHALL be the very first member in the derived structure
};

struct Struct2
{
    struct BaseStruct;      // Simulation of C++ inheritance in C. SHALL be the very first member in the derived structure
};

...

struct StructN
{
    struct BaseStruct;      // Simulation of C++ inheritance in C. SHALL be the very first member in the derived structure
};

Now, define RTTI for each structure:

CLX_DECLARE_C_OBJECT_RTTI(Struct1);
CLX_DECLARE_C_OBJECT_RTTI(Struct2);
...
CLX_DECLARE_C_OBJECT_RTTI(StructN);

Now, in a C or C++ file instantiate RTTI for these structures:
CLX_INSTANTIATE_C_OBJECT_RTTI(Struct1);
CLX_INSTANTIATE_C_OBJECT_RTTI(Struct2);
...
CLX_INSTANTIATE_C_OBJECT_RTTI(StructN);

Now, you can identify the type of an object at run time as long as you know the object derives from BaseStruct:

void getObjectType(BaseStruct* object)
{
    if (object->rtti == CLX_C_STRUCTURE_TYPE(Struct1))
    {
        printf ("object is of type Struct1\n");
    }
    else if (object->rtti == CLX_C_STRUCTURE_TYPE(Struct2))
    {
        printf ("object is of type Struct2\n");
    }
    ...
    else if (object->rtti == CLX_C_STRUCTURE_TYPE(StructN))
    {
        printf ("object is of type StructN\n");
    }
}
*/

#ifdef __cplusplus
#   define CLX_INSTANTIATE_C_OBJECT_RTTI(StructureName)     extern const u1 _ClxCObjectType_##StructureName = 0
#else
#   define CLX_INSTANTIATE_C_OBJECT_RTTI(StructureName)     const u1 _ClxCObjectType_##StructureName = 0
#endif


#if !defined( CLX_MODULE_ID)
#define CLX_MODULE_ID 0
#endif

#ifdef __cplusplus
#	define MISRA_FALSE	false
#else
#	define MISRA_FALSE	0
#endif

#if defined( BLACKBOX )
#   undef BLACKBOX
#endif


#if defined(CLX_DEBUG_INTERNAL)

#   define BLACKBOX                     clxBspExceptionHandler (CLX_MODULE_ID, __LINE__, FALSE)   																    
#   define CLX_ASSERT(condition)	    if (!(condition)) clxBspExceptionHandler (CLX_MODULE_ID, __LINE__, FALSE)   

#else   

#   define BLACKBOX																                            \
     do																				                        \
     {																			                            \
         CLX_PRINTF ("BLACKBOX at %s:%d", __FILE__, __LINE__);				                                \
         handleBlackBox( CLX_MODULE_ID, __LINE__ );    /* report and terminate */                           \
     } while( 0 )

    /**
    This macro asserts that condition is TRUE. Otherwise, it will cause a BLACKBOX.
    NOTE : This macro MUST NOT be called in the context of an ISR. Instead, the macro CLX_ASSERT_ISR must be used.
    */
#define CLX_ASSERT(condition)                                                                               \
     if (!(condition))                                                                                      \
     {																			                            \
         CLX_PRINTF ("Assert Failed (%s:%d) : %s", __FILE__, __LINE__, #condition);				            \
         handleBlackBox( CLX_MODULE_ID, __LINE__ );    /* report and terminate */                           \
     }

#endif // #if defined(CLX_DEBUG_INTERNAL)


#define BLACKBOX_IF( X )                                                                                \
do{                                                                                                     \
    if( X )                                                                                             \
    {                                                                                                   \
        BLACKBOX;                                                                                       \
    }                                                                                                   \
}while(0);


/**
Same as BLACKBOX but should be called in the context of an ISR (Interrupt Service Routine).
*/
#define BLACKBOX_ISR                                                                                    \
    clxBspExceptionHandler(CLX_MODULE_ID, __LINE__, TRUE)


#define BLACKBOX_ISR_SAFE(isrContext)                                                                   \
    if (isrContext)                                                                                     \
    {                                                                                                   \
        BLACKBOX_ISR;                                                                                   \
    }                                                                                                   \
    else                                                                                                \
    {                                                                                                   \
        BLACKBOX;                                                                                       \
    }


#if defined(CLX_DEBUG)
#   define CLX_DEBUG_ASSERT(condition)  CLX_ASSERT(condition)
#else
#   define CLX_DEBUG_ASSERT(condition)
#endif


/**
Same as CLX_ASSERT but should be called in the context of an ISR (Interrupt Service Routine).
*/
#define CLX_ASSERT_ISR(condition)                                                                       \
 if (!(condition))                                                                                      \
 {																			                            \
     clxBspExceptionHandler(CLX_MODULE_ID, __LINE__, TRUE);    /* report and terminate */               \
 }


#if defined(CLX_DEBUG)
#	if !defined(CLX_ENABLE_FAST_PATH_SANITY_CHECK)
#		define CLX_ENABLE_FAST_PATH_SANITY_CHECK
#	endif
#endif

#if defined(CLX_ENABLE_FAST_PATH_SANITY_CHECK)
#	define FAST_PATH_ASSERT(condition)		CLX_ASSERT(condition)
#else
#	define FAST_PATH_ASSERT(condition)
#endif


#ifndef CLX_MODULE_ID
#     define CLX_MODULE_ID 0
#endif


#ifdef __cplusplus
extern "C" {
#endif


typedef void (*ClxStdOutput) (const s1* format, ...);


#if !defined(CLX_VARIADIC_MACROS_SUPPORTED)
extern void clxDoNothing(const s1* format, ...);
#endif


/** A platform-specific descriptor of a memory region which is aligned based on the alignment requirements of the code */
typedef struct ClxAlignedMemoryRegionStruct
{
	void* address;			/*!< The address of the beginning of the memory region */
	
	void* id;				/*!< An opaque pointer which may be set and used by the BSP implementation */
} ClxAlignedMemoryRegion;


/**
Represents a single contiguous segment of multi-segmented data. A linked list of ClxDataSegment objects make up the entire data.
*/
typedef struct ClxDataSegmentStruct
{
	const u1*	                    data;       /*!< Pointer to contiguous data segment */
	u4		                        length;     /*!< Length of the data segment */

    struct ClxDataSegmentStruct*    next;       /*!< Pointer to the next segment, or NULL if this is the last segment */
} ClxDataSegment;

  
/** 
Exception function prototype is used by an application to handle stack exceptions. The handler provides moduleId and lineNumber to the call-back function 
and the application must log the moduleId and lineNumber for informing Clarinox to determine a possible stack issue. 
Then the application must restart the stack and application upon an exception for proper device operation. 
*/
typedef void (*ClxExceptionCallback) ( s4 moduleId, s4 lineNumber );

/**
userExceptionFunction points to the Exception Handler function in the application. By default, no Exception Handler has been defined.
An application may set this variable to an application-defined function inside clxInitBsp() implementation.

NOTE : Normally, an implementation SHALL NOT return. After processing the exception details (e.g. moduleId and lineNumber), it may throw a CPU exception, or call
exit() standard function, or call assert() function (only in debug version).

NOTE : This function is called in the context of the thread in which the exception has occurred.
*/
extern ClxExceptionCallback userExceptionFunction;

/**
Used Internally.
*/
extern void handleBlackBox ( s4 moduleID, s4 line );

/**
Used Internally.
*/
extern void clxBspExceptionHandler ( s4 moduleId, s4 lineNumber, boolean isrContext );

/**
Returns the ClarinoxSoftFrame version.
\return A function-allocated buffer containing the version as a null-terminated string. 
        The buffer must NOT be modified by the caller.
        Version is in the form of "[major_version].[minor_version].[revision].p[patch_no]"
*/
extern const s1* clxGetClarinoxSoftFrameVersion(void);

/**
Prototype of the function pointer passed as the first argument to clxProcessSoftFrameConfigParams().
The function will read the integral value of a configuration parameter from Clarinox SoftFrame configuration file (SoftFrame.cfg).

\param[ in ] defaultValue         The default value for the parameter. If a parameter with the provided name does not exist, this value will be returned instead.
                                  NOTE : If the parameter exists but the value is not an integer, 0 will be returned.
\param[ in ] parameterNameFormat  printf-style format string which is used to generate the parameter name. This MUST be a NULL-terminated string. This value CANNOT be NULL.
\param[ in ] ...                  Variadic arguments used as the arguments to the parameterNameFormat.

\return The value of the found parameter converted to a signed integer, of the default value if the parameter was not found.
*/
typedef s4 (*ClxGetSoftFrameIntegerParam) (s4 defaultValue, const s1* parameterNameFormat, ...);

/**
Prototype of the function pointer passed as the second argument to clxProcessSoftFrameConfigParams().
The function will read the string value of a configuration parameter from Clarinox SoftFrame configuration file (SoftFrame.cfg).

\param[ in ] parameterNameFormat  printf-style format string which is used to generate the parameter name. This MUST be a NULL-terminated string. This value CANNOT be NULL.
\param[ in ] ...                  Variadic arguments used as the arguments to the parameterNameFormat.

\return The value of the found parameter as a NULL-terminated string, or NULL if the parameter was not found.

NOTE : The returned string buffer (of type "const s1*") MUST NOT be modified or deleted. 
       The returned buffer remains valid until the implementation of clxProcessSoftFrameConfigParams() is returned.
*/
typedef const s1* (*ClxGetSoftFrameStringParam)  (const s1* parameterNameFormat, ...);


/**
Prototype of the function pointer clxProcessSoftFrameConfigParams.
*/
typedef void (*ClxProcessSoftFrameConfigParams) (ClxGetSoftFrameIntegerParam getIntParam,
                                                 ClxGetSoftFrameStringParam  getStrParam);


/**
Pointer to an application-defined function which will be called during the initialization of Clarinox SoftFrame. An implementation is optional. 
The implementation can obtain the values of application-specific configuration parameters which are stored in the Clarinox SoftFrame configuration file. 
If an implementation is available, its pointer needs to be set to this variable before SoftFrame is initialized. This is typically done in clxInitBsp() function.  
The configuration file is typically named "SoftFrame.cfg"

IMPORTANT : The implementation function is called after the debug sub-system has been initialized. So, it is safe to use debug-related API functions (e.g. clxDebugLog, clxDebugError, ...)
            In the implementation. It is also safe to call CLX_ASSERT, BLACKBOX and related macros.

NOTE : The implementation function is called in the context of the thread initializing Clarinox SoftFrame.

\param[ in ] getIntParam The function which can be called by the implementation to obtain the integral value of a configuration parameter.
\param[ in ] getStrParam The function which can be called by the implementation to obtain the string value of a configuration parameter.
*/
extern ClxProcessSoftFrameConfigParams clxProcessSoftFrameConfigParams;



#if defined(CLX_DEBUG)

    /**
    Dynamically enables one or more bits in the SoftFrame debug flag. This will change the initial value of the debug flag defined as the parameter DEBUG_FLAG defined in SoftFrame.cfg
    
    \param[ in ] bitsToSet Bits to enable in the debug flag. The new value of the debug flag will be set to (CurrentDebugFlag | bitsToSet).
    */
    extern void clxSetDebugFlagBits(u4 bitsToSet);

    /**
    Dynamically disables one or more bits in the SoftFrame debug flag. This will change the initial value of the debug flag defined as the parameter DEBUG_FLAG defined in SoftFrame.cfg

    \param[ in ] bitsToReset Bits to disable in the debug flag. The new value of the debug flag will be set to (CurrentDebugFlag & ~(bitsToReset)).
    */
    extern void clxResetDebugFlagBits(u4 bitsToReset);

    /**
    Flushes the current contents of the SoftFrame debug FIFO buffer to the debug medium (as specified by the parameter DEBUG_MEDIUM defined in SoftFrame.cfg) and erases the FIFO contents.

    This function succeeds only if:

      - The debug subsystem is currently in FIFO mode (e.g. the parameter DEBUG_FIFO_MODE is set to 1 in SoftFrame.cfg and clxDisableDebugFifoMode() has not been called).
      - The debug subsystem is active (e.g. has not failed).

    \return CLX_SUCCESS The current contents of the debug FIFO have been flushed to the debug medium and the debug FIFO is now empty.
            CLX_ERROR_BAD_STATE The debug subsystem is not currently in FIFO mode.
            CLX_ERROR_CONNECTION_NOT_EXIST A debug connection does not exist.
            CLX_ERROR_CONNECTION_FAILED The debug connection failed during the operation.
    */
    extern ClxResult clxFlushDebugFifoToClariFi(void);

    /**
    Disables the SoftFrame debug FIFO mode. If successful, the current contents of the debug FIFO is flushed into the debug medium (as specified by the parameter DEBUG_MEDIUM defined in SoftFrame.cfg) 
    and the FIFO contents are erased. Then, the debug subsystem will continue in the normal (stream) mode.

    This function succeeds only if:

      - The debug subsystem is currently in FIFO mode (e.g. the parameter DEBUG_FIFO_MODE is set to 1 in SoftFrame.cfg and clxDisableDebugFifoMode() has not been called).
      - The debug subsystem is active (e.g. has not failed).

    \return CLX_SUCCESS The debug FIFO mode has been successfully disabled.
            CLX_ERROR_BAD_STATE The debug subsystem is not currently in FIFO mode.
            CLX_ERROR_CONNECTION_NOT_EXIST A debug connection does not exist.
            CLX_ERROR_CONNECTION_FAILED The debug connection failed during the operation.
    */
    extern ClxResult clxDisableDebugFifoMode(void);

    /**
    Sends a debug log message to ClariFi.
    */
    extern void clxDebugLog(const s1* format, ...);


    /**
    Sends a debug warning message to ClariFi.
    */
    extern void clxDebugWarning(const s1* format, ...);


    /**
    Sends a debug error message to ClariFi.
    */
    extern void clxDebugError(const s1* format, ...);

    /**
    Sends contents of a memory buffer to ClariFi.
    Optionally, a description (as a NULL-terminated string) may be provided.
    */
    extern void clxDebugMemory(const s1* description, const void* data, u4 dataLen);

#else // defined(CLX_DEBUG)

#   define clxDebugLog                 clxDoNothing
#   define clxDebugWarning             clxDoNothing
#   define clxDebugError               clxPrintfTimestamped
#   define clxDebugMemory              clxDoNothing

#endif // defined(CLX_DEBUG)


/* Returns a 32bit random number: */
extern u4 clxGetRandomNumber(void);


#ifdef __cplusplus
}
#endif



/** \file ClxCommonDefines.h
    \brief ClxCommonDefines.h contains the ClarinoxSoftFrame common macro defines
*/


#endif    // ClxCommonDefines_h

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : Sections of code should not be “commented out”.            */ 
/* Rule          : MISRA-C:2004 Rule 2.4                                      */ 
/* Justification : Inside comment section, example of code is given for       */
/*				   clarity.											          */
/*                 Only used for example code to clarify the use.             */
/*                 As we generate API documentation from header files         */
/*				   (using Doxygen), this is necessary.                        */
/******************************************************************************/ 

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : C macros shall only expand to a braced initialiser,        */
/*                 a constant, a string literal, a parenthesised expression,  */ 
/*				   a type qualifier, a storage class specifier,               */
/*				   or a do-whilezero construct.                               */ 
/* Rule          : MISRA-C:2004 Rule 19.4                                     */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */ 
/*                 platforms. Used to provide better flexibility for templated*/ 
/*				   code to eliminate programmer errors.                       */
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
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : The # and ## operators should not be used.                 */
/* Rule          : MISRA-C:2004 Rule 19.13                                    */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */
/*                 platforms. Used to provide better flexibility.	          */
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

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : The character sequences Slash'/' Star'*' and Slash'/'      */
/*				   Slash'/'  shall not be used within a comment. 	  		  */
/* Rule          : MISRA-C:2012 Rule 3.1                                      */ 
/* Justification : Only used for example code to clarify the use. As we		  */	
/*				   generate API documentation from header files (using 		  */
/*				   Doxygen), this is necessary.							  	  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : The # and ## preprocessor operators should not be used.    */
/* Rule          : MISRA-C:2012 Rule 20.10                                    */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */
/*                 platforms. Used to provide better flexibility.	          */
/******************************************************************************/
