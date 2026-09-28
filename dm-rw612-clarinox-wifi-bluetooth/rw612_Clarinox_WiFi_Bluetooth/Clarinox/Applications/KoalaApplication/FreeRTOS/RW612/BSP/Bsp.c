/*******************************************************************************
*
* Project             Board Support Package
* File                Bsp.c
* Description         Bsp related functions and variables are defined here.
*
* This file contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/          
// _____________________________________________________________________________
//
#undef  CLX_MODULE_ID
#define CLX_MODULE_ID  1022
// _____________________________________________________________________________
//


#include <stdlib.h>
#include <assert.h>

#include "ClxBsp.h"
#include "Bsp.h"
#include "ClxMemoryPoolset.h"
#include "ClxCommonDefines.h"
#include "ClxBspConfig.h"
#include "ClarinoxErrorCodes.h"

extern boolean clxTerminalEmulatorEnabled  (void);
extern void    __cxa_pure_virtual          (void);
extern void    vPortEnterCritical          (void);
extern void    vPortExitCritical           (void);
#ifdef CLX_BSP_TEST
extern int     bspTest                     (void);
#endif
#if defined (CLX_MLAN_LABTOOL_SUPPORTED) || defined (CLX_BT_LABTOOL_SUPPORTED)
extern void    labtoolMain                 (void);
#endif

void __cxa_pure_virtual()
{
	BLACKBOX;
    while (1);
}

void clxOsAbstrationLayeExceptionCallback(s4 moduleId, s4 lineNumber)
{
    (void)moduleId;
    (void)lineNumber;

    /* A resource/event assigned to Clx Tasks has been accessed/updated by a non-Clx Task */
    while(1);
}

u1 clxBsp_GetAbiID()
{
    return CLX_ABI_ARM_IAR_LE;
}


#if defined (CLX_WPA_SUPPLICANT)

int isblank (int __c)
{
	return ((__c == 0x09) || (__c == 0x20)) ? 1 : 0;
}

static u4 wpaSupplicantMemoryUsage          = 0U;
static u4 wpaSupplicantHighestEverMemUsage  = 0U;

/**
Returns the current memory consumed by the WPA supplicant during WLAN enterprise processes.
*/
u4 clxWpaSupplicantBsp_CurrentMemUsage (void)
{
    return wpaSupplicantMemoryUsage;
}

/**
Returns the highest ever memory consumed by the WPA supplicant during WLAN enterprise processes.
*/
u4 clxWpaSupplicantBsp_HighestEverMemUsage (void)
{
    return wpaSupplicantHighestEverMemUsage;
}


ClxResult clxWpaSupplicantBsp_Init(void)
{
    wpaSupplicantMemoryUsage            = 0U;
    wpaSupplicantHighestEverMemUsage    = 0U;

    return CLX_SUCCESS;
}

void clxWpaSupplicantBsp_Destroy(void)
{
    wpaSupplicantMemoryUsage            = 0;
    wpaSupplicantHighestEverMemUsage    = 0U;
}


#define WPA_SUPPLICANT_BSP_HEAP_BUFFER_SIGNATURE		0xDEADDEAD
#define WPA_SUPPLICANT_BSP_POOLSET_BUFFER_SIGNATURE		0xCAFECAFE

#define WPA_SUPPLICANT_BSP_HEAP_BUFFER_THRESHOLD		3000 /* Bytes */

typedef struct ClxWpaSupplicant_BufferHeaderStruct
{
	u4 signature;
	u4 size;
} ClxWpaSupplicant_BufferHeader;


void* clxWpaSupplicantBsp_Alloc(size_t size)
{
	boolean allocatedInPoolset = FALSE;

    u1* ret = NULL;

    wpaSupplicantMemoryUsage = wpaSupplicantMemoryUsage + size;

    if(wpaSupplicantMemoryUsage > wpaSupplicantHighestEverMemUsage)
    {
        wpaSupplicantHighestEverMemUsage = wpaSupplicantMemoryUsage;
    }

    if (size < WPA_SUPPLICANT_BSP_HEAP_BUFFER_THRESHOLD)
    {
    	ret = (u1*)malloc(size + sizeof(ClxWpaSupplicant_BufferHeader));
    }

    if (!ret)
    {
    	ret = (u1*)clxPoolsetAlloc(CLX_PACKAGE(WPA_SUPPLICANT_PKG), 0, 0, size + sizeof(ClxWpaSupplicant_BufferHeader));
        allocatedInPoolset = TRUE;
    }

    if (ret)
    {
    	ClxWpaSupplicant_BufferHeader* hdr = (ClxWpaSupplicant_BufferHeader*)ret;

		/* store the signature  */
    	hdr->signature = (allocatedInPoolset ? WPA_SUPPLICANT_BSP_POOLSET_BUFFER_SIGNATURE : WPA_SUPPLICANT_BSP_HEAP_BUFFER_SIGNATURE);
    	hdr->size = size;

        return (void*)(hdr + 1);
    }
    else
    {
        return NULL;
    }
}

void clxWpaSupplicantBsp_Free(void *ptr)
{
    if (ptr)
    {
        /* extract the size information fo the memory being freed using the first memory location */
        wpaSupplicantMemoryUsage = wpaSupplicantMemoryUsage - *((u4*)ptr - 1);

    	ClxWpaSupplicant_BufferHeader* hdr = (ClxWpaSupplicant_BufferHeader*)ptr - 1;

    	if (hdr->signature == WPA_SUPPLICANT_BSP_POOLSET_BUFFER_SIGNATURE)
        {
            clxPoolsetFree((void*)hdr);
        }
        else if (hdr->signature == WPA_SUPPLICANT_BSP_HEAP_BUFFER_SIGNATURE)
        {
            free((void*)hdr);
        }
    	else
    	{
    		BLACKBOX;
    	}
    }
}

void* clxWpaSupplicantBsp_Realloc(void *ptr, size_t size)
{
    void* newBuf = NULL;

    if (ptr)
    {
    	ClxWpaSupplicant_BufferHeader* hdr = (ClxWpaSupplicant_BufferHeader*)ptr - 1;

        newBuf = clxWpaSupplicantBsp_Alloc(size);

        if (newBuf)
        {
            memcpy(newBuf, ptr, hdr->size);

            clxWpaSupplicantBsp_Free(ptr);

        }

        return newBuf;
    }
    else
    {
        return clxWpaSupplicantBsp_Alloc(size);
    }
}

#endif

/*
*********************************************************************************************************
*                                          MAIN THREAD
*
* Description : This is a main thread entry function; initializes the Clarinox wireless stacks
*
* Arguments   : notUsed 
*
*********************************************************************************************************
*/
int clarinoxMain(void)
{
    clxInitBsp();

    /*
    Initialize user interface engine and start a menu for possible operations
    */
   clxConsoleUIEngineInit(MAX_TEXT_SIZE);

    while(1)
    {
		const s1* menu = "WiFi\0"
				 "Bluetooth\0";

#if defined(CLARINOX_MESH_DEMO_ROOT_MENU) || defined(CLARINOX_MESH_DEMO_NONROOT_MENU)
		u4 index = 1;
#else
        u4 index = clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, 2);
#endif

        if (index == 1)
        {
        	clarinoxMainWifi();

        }
        else if (index == 2)
        {
        	mainBluetooth();

        }
    }
}


void clxBspEnableSystemInterrupt(void* irqStatus)
{
	vPortExitCritical();
	return;
}

void* clxBspDisableSystemInterrupt()
{
	vPortEnterCritical();
	return NULL;
}


/*******************************************************************************************************************************
*                                                     userExceptionHandler
*
* Traps the stack exceptions.
* This function must not return back to the caller.
* This function is called by the stack when an unrecoverable error has happened in Clarinox code;
* It could be a device driver issue or a stack issue.
* After this point, the stack behavior is undefined.
*
* The parameters moduleId and lineNumber would provide Clarinox with more information about the exception.
*
* \param moduleId         - Module ID from where the exception is thrown
* \param lineNumber     - Line number from the module from where the exception is thrown
*
* \return void
*
*******************************************************************************************************************************/
void userExceptionHandler( s4 moduleId, s4 lineNumber )
{
    /*
    Handle the exception here in the way the application wants to;

    i.e.,
    Notify the rest of the system, like, an error message could be displayed to the user via console, etc
    Restart the system and restore the communications to the remote devices.
    Do not return from this function without initiating the appropriate restart procedures.
    */
    CLX_PRINTF("Clarinox raised an exception in module: %u, line: %u\n", moduleId, lineNumber);
    assert(0);
    exit(0);
}

