#ifndef __ClxSoftTrace__
#define __ClxSoftTrace__

/*******************************************************************************
* 
* Project           :   Clarinox SoftFrame
* File              :   ClxSoftTrace.h
* Description       :   ClariFi Insight (ClarinoxTrace)
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#if defined(CLX_TRACE)


#include "ClxTypes.h"
#include "ClxSoftTrace.Bsp.h"



/**
ClariFi Insight Event Categories: 

Events in each category may be enabled and disabled independently. Currently, up to 112 categories may be defined.

NOTE : All event categories are enabled by default when the application starts up. Each category may be enabled or disabled
by CLX_ENABLE_TRACE_EVENT_CATEGORY() and CLX_DISABLE_TRACE_EVENT_CATEGORY() macros respectively.

The definition for each category must follow the following format:

#define CLX_TRACE_EVENT_CATEGORY_<CategoryName>     <CategoryValue>

Where <CategoryName> is the name of the category, as passed to CLX_TRACE_EVENTn() and CLX_TRACE_ISR_EVENTn() macros.
For the sake of consistency, the category names should be in upper case.

The 4 MSB bits of <CategoryValue> determines the zero-based index of the category in clxTraceEnabledCategories[] array. 
The 28 LSB bits determines the category flag bit in clxTraceEnabledCategories[index]. 
*/

#define CLX_TRACE_EVENT_CATEGORY_GENERIC                	0x0000001U     /*  CategoryName = GENERIC 		*/
#define CLX_TRACE_EVENT_CATEGORY_OS                     	0x0000002U     /*  CategoryName = OS      		*/
#define CLX_TRACE_EVENT_CATEGORY_TASKS                  	0x0000004U     /*  CategoryName = TASKS   		*/
#define CLX_TRACE_EVENT_CATEGORY_NET                    	0x0000008U     /*  CategoryName = NET   		*/
#define CLX_TRACE_EVENT_CATEGORY_IPV4                   	0x0000010U     /*  CategoryName = IPV4    		*/
#define CLX_TRACE_EVENT_CATEGORY_WLAN                   	0x0000020U     /*  CategoryName = WLAN    		*/
#define CLX_TRACE_EVENT_CATEGORY_MESH                   	0x0000040U     /*  CategoryName = MESH    		*/
#define CLX_TRACE_EVENT_CATEGORY_MLAN_PCIE              	0x0000080U     /*  CategoryName = MLAN_PCIE     */
#define CLX_TRACE_EVENT_CATEGORY_MLAN_MEM               	0x0000100U     /*  CategoryName = MLAN_MEM      */
#define CLX_TRACE_EVENT_CATEGORY_MLAN_TASK              	0x0000200U     /*  CategoryName = MLAN_TASK     */
#define CLX_TRACE_EVENT_CATEGORY_IPERF             			0x0000400U     /*  CategoryName = IPERF     	*/
#define CLX_TRACE_EVENT_CATEGORY_REFERENCEABLE              0x0000800U     /*  CategoryName = REFERENCEABLE */
#define CLX_TRACE_EVENT_CATEGORY_WILINK8                    0x0001000U     /*  CategoryName = WILINK8       */


#define CLX_TRACE_NUMBER_OF_EVENT_CATEGORY_INDEXES      	4 /* DO NOT MODIFY */

#define CLX_TRACE_EVENT_CATEGORY_ID(CategoryName)       	CLX_TRACE_EVENT_CATEGORY_##CategoryName
#define CLX_TRACE_EVENT_ID(CategoryName, EventName) 		CLX_TRACE_EVENT_##CategoryName##_##EventName

/**
Enables a ClxTrace event category at runtime. When an event category is enabled, any event belonging to the category may be generated. 

\param[ in ] CategoryName Name of the category.
*/
#define CLX_ENABLE_TRACE_EVENT_CATEGORY(CategoryName)                                                            \
    clxTraceEnabledCategories[(CLX_TRACE_EVENT_CATEGORY_ID(CategoryName) & 0xF0000000U) >> 28] |=                \
        (CLX_TRACE_EVENT_CATEGORY_ID(CategoryName) & 0x0FFFFFFFU)

/**
Disables a ClxTrace event category at runtime. When an event category is disable, no event belonging to the category may be generated. 

\param[ in ] CategoryName Name of the category.
*/
#define CLX_DISABLE_TRACE_EVENT_CATEGORY(CategoryName)                                                           \
    clxTraceEnabledCategories[(CLX_TRACE_EVENT_CATEGORY_ID(CategoryName) & 0xF0000000U) >> 28] &=                \
        ~(CLX_TRACE_EVENT_CATEGORY_ID(CategoryName) & 0x0FFFFFFFU)


/**
Enables all ClxTrace event categories at runtime.
*/
#define CLX_ENABLE_ALL_TRACE_EVENT_CATEGORIES                                                                    \
    for (u4 i = 0; i < CLX_TRACE_NUMBER_OF_EVENT_CATEGORY_INDEXES; i++)                                          \
    {                                                                                                            \
        clxTraceEnabledCategories[i] = 0x0FFFFFFF;                                                               \
    }


/**
Disables all ClxTrace event categories at runtime.					
*/					
#define CLX_DISABLE_ALL_TRACE_EVENT_CATEGORIES                                                                   \
    for (u4 i = 0; i < CLX_TRACE_NUMBER_OF_EVENT_CATEGORY_INDEXES; i++)                                          \
    {                                                                                                            \
        clxTraceEnabledCategories[i] = 0;                                                                        \
    }


/**
Definition of a word in the platform:
*/
#if CLX_REQUIRED_ALIGNMENT > 4
#   define TRACE_BUFFER_WORD_SIZE                       8       /* Bytes */
#   define TRACE_BUFFER_TYPE                            ull
#elif CLX_REQUIRED_ALIGNMENT == 4
#   define TRACE_BUFFER_WORD_SIZE                       4       /* Bytes */
#   define TRACE_BUFFER_TYPE                            u4
#endif


/* 
Event Generation Macros:
*/

#define CLX_TRACE_GENERATE_EVENT1(eventID, isrContext, arg1)                                                    \
    clxTraceGlobalLockStatus = clxTraceBsp_Lock();                                                              \
    clxTraceEvent1((eventID), (isrContext));                                                                    \
    clxTraceArguments[0] = (TRACE_BUFFER_TYPE)(arg1);                                                           \
    clxTraceBsp_Unlock(clxTraceGlobalLockStatus);


#define CLX_TRACE_GENERATE_EVENT4(eventID, isrContext, arg1, arg2, arg3, arg4)                                  \
    clxTraceGlobalLockStatus = clxTraceBsp_Lock();                                                              \
    clxTraceEvent4((eventID), (isrContext));                                                                    \
    clxTraceArguments[0] = (TRACE_BUFFER_TYPE)(arg1);                                                           \
    clxTraceArguments[1] = (TRACE_BUFFER_TYPE)(arg2);                                                           \
    clxTraceArguments[2] = (TRACE_BUFFER_TYPE)(arg3);                                                           \
    clxTraceArguments[3] = (TRACE_BUFFER_TYPE)(arg4);                                                           \
    clxTraceBsp_Unlock(clxTraceGlobalLockStatus);


#define CLX_TRACE_GENERATE_EVENT7(eventID, isrContext, arg1, arg2, arg3, arg4, arg5, arg6, arg7)                \
    clxTraceGlobalLockStatus = clxTraceBsp_Lock();                                                              \
    clxTraceEvent7((eventID), (isrContext));                                                                    \
    clxTraceArguments[0] = (TRACE_BUFFER_TYPE)(arg1);                                                           \
    clxTraceArguments[1] = (TRACE_BUFFER_TYPE)(arg2);                                                           \
    clxTraceArguments[2] = (TRACE_BUFFER_TYPE)(arg3);                                                           \
    clxTraceArguments[3] = (TRACE_BUFFER_TYPE)(arg4);                                                           \
    clxTraceArguments[4] = (TRACE_BUFFER_TYPE)(arg5);                                                           \
    clxTraceArguments[5] = (TRACE_BUFFER_TYPE)(arg6);                                                           \
    clxTraceArguments[6] = (TRACE_BUFFER_TYPE)(arg7);                                                           \
    clxTraceBsp_Unlock(clxTraceGlobalLockStatus);


/*
ClarinoxTrace Events:

    A trace event is composed of an Event ID, Time stamp and argument(s) 
    An event may be short (containing one argument), long (containing 4 arguments) or very long (containing 7 arguments).

    The size of each argument is one word. A word is equal to 4 bytes (in 32-bit platforms) or 8 bytes (in 64-bit platforms).
*/
     

/**
Determines whether or not a ClarinoxTrace event category is enabled. If an event category is enabled, 
any event belonging to the category may be generated (e.g. stored in the trace FIFO). 
Otherwise, no event belonging to the category may be generated.

\param[ in ] CategoryName Name of the category.
\return true if the event category is enabled. false otherwise.
*/
#define CLX_TRACE_EVENT_CATEGORY_ENABLED(CategoryName)                                                          \
    (clxTraceEnabledCategories[(CLX_TRACE_EVENT_CATEGORY_ID(CategoryName) & 0xF0000000U) >> 28] &               \
    (CLX_TRACE_EVENT_CATEGORY_ID(CategoryName) & 0x0FFFFFFFU))      


/**
Generates a short ClarinoxTrace event and stores it in the trace FIFO. 

NOTE : This macro CANNOT be called in the context of an ISR.

\param[ in ] CategoryName Name of the category to which the event belongs. If the event category is currently disabled, this event will NOT be generated.
\param[ in ] eventID      The event ID
\param[ in ] arg1         The argument value for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
*/
#define CLX_TRACE_EVENT1(CategoryName, eventID, arg1)                                                           \
    if (CLX_TRACE_EVENT_CATEGORY_ENABLED(CategoryName))                                                         \
    {                                                                                                           \
        CLX_TRACE_GENERATE_EVENT1(eventID, FALSE, arg1);                                                        \
    }


/**
Generates a long ClarinoxTrace event and stores it in the trace FIFO. 

NOTE : This macro CANNOT be called in the context of an ISR.

\param[ in ] CategoryName Name of the category to which the event belongs. If the event category is currently disabled, this event will NOT be generated.
\param[ in ] eventID      The event ID.
\param[ in ] arg1         The value of argument 1 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg2         The value of argument 2 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg3         The value of argument 3 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg4         The value of argument 4 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
*/
#define CLX_TRACE_EVENT4(CategoryName, eventID, arg1, arg2, arg3, arg4)                                         \
    if (CLX_TRACE_EVENT_CATEGORY_ENABLED(CategoryName))                                                         \
    {                                                                                                           \
        CLX_TRACE_GENERATE_EVENT4(eventID, FALSE, arg1, arg2, arg3, arg4);                                      \
    }


/**
Generates a very long ClarinoxTrace event and stores it in the trace FIFO. 

NOTE : This macro CANNOT be called in the context of an ISR.

\param[ in ] CategoryName Name of the category to which the event belongs. If the event category is currently disabled, this event will NOT be generated.
\param[ in ] eventID      The event ID.
\param[ in ] arg1         The value of argument 1 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg2         The value of argument 2 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg3         The value of argument 3 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg4         The value of argument 4 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg5         The value of argument 5 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg6         The value of argument 6 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg7         The value of argument 7 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
*/
#define CLX_TRACE_EVENT7(CategoryName, eventID, arg1, arg2, arg3, arg4, arg5, arg6, arg7)                       \
    if (CLX_TRACE_EVENT_CATEGORY_ENABLED(CategoryName))                                                         \
    {                                                                                                           \
        CLX_TRACE_GENERATE_EVENT7(eventID, FALSE, arg1, arg2, arg3, arg4, arg5, arg6, arg7);                    \
    }


/**
Generates a short ClarinoxTrace event and stores it in the trace FIFO. 

NOTE : This macro may ONLY be called in the context of an ISR.

\param[ in ] CategoryName Name of the category to which the event belongs. If the event category is currently disabled, this event will NOT be generated.
\param[ in ] eventID      The event ID
\param[ in ] arg1         The argument value for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
*/
#define CLX_TRACE_ISR_EVENT1(CategoryName, eventID, arg1)                                                       \
    if (CLX_TRACE_EVENT_CATEGORY_ENABLED(CategoryName))                                                         \
    {                                                                                                           \
        CLX_TRACE_GENERATE_EVENT1(eventID, TRUE, arg1);                                                         \
    }


/**
Generates a long ClarinoxTrace event and stores it in the trace FIFO. 

NOTE : This macro may ONLY be called in the context of an ISR.

\param[ in ] CategoryName Name of the category to which the event belongs. If the event category is currently disabled, this event will NOT be generated.
\param[ in ] eventID      The event ID.
\param[ in ] arg1         The value of argument 1 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg2         The value of argument 2 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg3         The value of argument 3 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg4         The value of argument 4 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
*/
#define CLX_TRACE_ISR_EVENT4(CategoryName, eventID, arg1, arg2, arg3, arg4)                                     \
    if (CLX_TRACE_EVENT_CATEGORY_ENABLED(CategoryName))                                                         \
    {                                                                                                           \
        CLX_TRACE_GENERATE_EVENT4(eventID, TRUE, arg1, arg2, arg3, arg4);                                       \
    }


/**
Generates a very long ClarinoxTrace event and stores it in the trace FIFO. 

NOTE : This macro may ONLY be called in the context of an ISR.

\param[ in ] CategoryName Name of the category to which the event belongs. If the event category is currently disabled, this event will NOT be generated.
\param[ in ] eventID      The event ID.
\param[ in ] arg1         The value of argument 1 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg2         The value of argument 2 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg3         The value of argument 3 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg4         The value of argument 4 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg5         The value of argument 5 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg6         The value of argument 6 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
\param[ in ] arg7         The value of argument 7 for this event. This value will be case to a 4-byte integer (in 32bit systems),
                          or a 8-byte integer (in 64bit systems).
*/
#define CLX_TRACE_ISR_EVENT7(CategoryName, eventID, arg1, arg2, arg3, arg4, arg5, arg6, arg7)                   \
    if (CLX_TRACE_EVENT_CATEGORY_ENABLED(CategoryName))                                                         \
    {                                                                                                           \
        CLX_TRACE_GENERATE_EVENT7(eventID, TRUE, arg1, arg2, arg3, arg4, arg5, arg6, arg7);                     \
    }



#ifdef __cplusplus
extern "C" {
#endif

/**
Initializes The ClariFi Insight (ClarinoxTrace) internal buffers and objects. 
This function MUST be called before any ClarinoxTrace-related macros and functions may be used.

This function calls ClarinoxTrace BSP implementations (defined in ClxSoftTrace.Bsp.h) to initialize the internal structures.

NOTE : This function may be called before SoftFrame is initialized.
*/
extern void clxTraceInit();


/* 
Internal Definitions (MUST NOT BE MODIFIED OR ACCESSED):
*/

extern u4                 clxTraceEnabledCategories[CLX_TRACE_NUMBER_OF_EVENT_CATEGORY_INDEXES];
extern TRACE_BUFFER_TYPE* clxTraceArguments;
extern void*              clxTraceGlobalLockStatus;

extern void clxTraceEvent1(u2 eventID, boolean isrContext);     /* NOT TO BE CALLED DIRECTLY */
extern void clxTraceEvent4(u2 eventID, boolean isrContext);     /* NOT TO BE CALLED DIRECTLY */
extern void clxTraceEvent7(u2 eventID, boolean isrContext);     /* NOT TO BE CALLED DIRECTLY */


#ifdef __cplusplus
}
#endif


#else

#define CLX_TRACE_GENERATE_EVENT1(eventID, isrContext, arg1)
#define CLX_TRACE_GENERATE_EVENT4(eventID, isrContext, arg1, arg2, arg3, arg4)
#define CLX_TRACE_GENERATE_EVENT7(eventID, isrContext, arg1, arg2, arg3, arg4, arg5, arg6, arg7)

#define CLX_TRACE_EVENT1(CategoryName, eventID, arg1)
#define CLX_TRACE_EVENT4(CategoryName, eventID, arg1, arg2, arg3, arg4)
#define CLX_TRACE_EVENT7(CategoryName, eventID, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
#define CLX_TRACE_ISR_EVENT1(CategoryName, eventID, arg1)
#define CLX_TRACE_ISR_EVENT4(CategoryName, eventID, arg1, arg2, arg3, arg4)
#define CLX_TRACE_ISR_EVENT7(CategoryName, eventID, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)


#endif // #if defined(CLX_TRACE)

/* Do NOT change the location of the following line: */
#include "ClxTraceEvents.h"

#endif  // __ClxSoftTrace__
