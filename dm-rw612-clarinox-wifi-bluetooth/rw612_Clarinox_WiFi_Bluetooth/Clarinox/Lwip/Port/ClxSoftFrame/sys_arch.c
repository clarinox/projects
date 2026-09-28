/*******************************************************************************
*
* Project             Bluetooth Application
* File                sys_arch.cpp
* Description         LWIP Port to ClarinoxSoftFrame
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
#define CLX_STATIC_PACKAGE_NAME    NETWORK_STACK
// _____________________________________________________________________________
//

#include "ClxBsp.h"
#include "Thread.Bsp.h"

/* lwIP includes. */
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/stats.h"

#include <stdarg.h>


#if defined(CLX_DEBUG)
extern void clxDebugLogWithArguments(const s1* format, va_list args);

void clxLwipDebugMsg(const s1* format, ...)
{
    va_list args;

    va_start(args, format);
    clxDebugLogWithArguments(format, args);
    va_end(args);
}
#endif


#if SYS_LIGHTWEIGHT_PROT

#if !defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
static ClxMutex protection = NULL;
#endif

void sys_init(void)
{
#if !defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
    protection = clxCreateMutex();
#endif
}

void sys_deinit(void)
{
#if !defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
    clxDeleteMutex(protection);
#endif
}

sys_prot_t sys_arch_protect(void)
{
#if defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
	clxBspDisableOsScheduler();
#else
	clxAcquireMutex(protection);
#endif
	return 1;
}

/*
  This optional function does a "fast" set of critical region protection to the
  value specified by pval. See the documentation for sys_arch_protect() for
  more information. This function is only required if your port is supporting
  an operating system.
*/
void sys_arch_unprotect(sys_prot_t pval)
{
#if defined(CLX_OS_SCHEDULER_DISABLE_SUPPORTED)
	clxBspEnableOsScheduler();
#else
	clxReleaseMutex(protection);
#endif
}

#endif // #if SYS_LIGHTWEIGHT_PROT




#if !defined(NO_SYS) || (NO_SYS == 0)


err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    sys_mbox_t obj = ((sys_mbox_t)clxCreateMailBox( CLX_MAIL_BOX_SIZE_IN_BITS ));

    if(obj != NULL)
    {
        *mbox = obj;
        return ERR_OK;
    }
    else
    {
        return ERR_MEM;
    }
}

void sys_mbox_free(sys_mbox_t* mbox)
{  
    clxTerminateMailBox((ClxMailBox)(*mbox));
    clxDeleteMailBox((ClxMailBox)(*mbox));
}

void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
  *mbox = NULL;
}

int sys_mbox_valid(sys_mbox_t *mbox)
{
    return (*mbox != NULL) ? 1 : 0;
}


void sys_mbox_post(sys_mbox_t *mbox, void *data)
{
	clxPostToMailBox((ClxMailBox)(*mbox), data);
}

err_t sys_mbox_trypost(sys_mbox_t* mbox, void *msg)
{
    err_t result;

   if (clxTryPostToMailBox((ClxMailBox)(*mbox), msg) == CLX_SUCCESS )
   {
      result = ERR_OK;
   }
   else 
   {
      // could not post, queue must be full
      result = ERR_MEM;			
   }

   return result;
}

err_t sys_mbox_trypost_fromisr(sys_mbox_t *mbox, void *msg)
{
    err_t result;

   if (clxTryPostToMailBox((ClxMailBox)(*mbox), msg) == CLX_SUCCESS )
   {
      result = ERR_OK;
   }
   else 
   {
      // could not post, queue must be full
      result = ERR_MEM;			
   }

   return result;	
}

u32_t sys_arch_mbox_fetch(sys_mbox_t* mbox, void **msg, u32_t timeout)
{
	u4 startTime = clxTickTime();
    
	/* KW-UNINIT.STACK.MUST: Uninitialized variable */
    void *dummyptr = (void *) 0;
    
	if ( *msg == NULL )
	{
		*msg = dummyptr;
	}
		
    if (timeout == 0)
    {
        timeout = 0xFFFFFFFF;
    }
    
    ClxResult result = clxFetchFromMailBox((ClxMailBox)(*mbox), msg, timeout);
    
    if ( result == CLX_SUCCESS )
    {		
        return clxTickTime() - startTime;
    }
    else // timed out blocking for message
    {
        *msg = NULL;
        
        return SYS_ARCH_TIMEOUT;
    }
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t* mbox, void **msg)
{
    /* KW-UNINIT.STACK.MUST: Uninitialized variable */
    void *dummyptr = (void *) 0;

	if ( *msg == NULL )
	{
		*msg = dummyptr;
	}

    ClxResult result = clxTryFetchFromMailBox((ClxMailBox)(*mbox), msg);
    
    if ( result == CLX_SUCCESS )
    {		
        return ERR_OK;
    }
    else // timed out blocking for message
    {
        *msg = NULL;
        
        return SYS_MBOX_EMPTY;
    }
}


err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    sys_sem_t obj = (sys_sem_t)clxCreateSemaphore(count);

    if(obj != NULL)
    {
        *sem = obj;
        return ERR_OK;
    }
    else
    {
        return ERR_MEM;
    }
}

u32_t sys_arch_sem_wait(sys_sem_t* sem, u32_t timeout)
{
	u4 startTime = clxTickTime();

	if(	timeout != 0)
	{
		if( clxAcquireSemaphoreTimed((ClxSemaphore)(*sem), timeout) == CLX_SUCCESS )
		{		
			return clxTickTime() - startTime;
		}
		else
		{
			return SYS_ARCH_TIMEOUT;
		}
	}
	else
	{
		clxAcquireSemaphore((ClxSemaphore)(*sem));

		return clxTickTime() - startTime;	
	}
}

void sys_sem_signal(sys_sem_t* sem)
{
	clxReleaseSemaphore((ClxSemaphore)(*sem));
}

void sys_sem_free(sys_sem_t* sem)
{		
	clxDeleteSemaphore((ClxSemaphore)(*sem));
}

void sys_sem_set_invalid(sys_sem_t *sem)
{
   *sem = NULL;
}

int sys_sem_valid(sys_sem_t *sem)
{
    if(*sem != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


#if LWIP_COMPAT_MUTEX == 0

err_t sys_mutex_new(sys_mutex_t *mutex)
{
    sys_mutex_t obj = (sys_mutex_t)clxCreateMutex();
    
    if (obj)
    {
        *mutex = obj;
        return ERR_OK;
    }
    else
    {
        return ERR_MEM;
    }
}

void sys_mutex_lock(sys_mutex_t *mutex)
{
    clxAcquireMutex((ClxMutex)*mutex);
}

void sys_mutex_unlock(sys_mutex_t *mutex)
{
    clxReleaseMutex((ClxMutex)*mutex);  
}

void sys_mutex_free(sys_mutex_t *mutex)
{
    clxDeleteMutex((ClxMutex)*mutex);
}

#ifndef sys_mutex_valid
int sys_mutex_valid(sys_mutex_t *mutex)
{
    return (*mutex != NULL) ? 1 : 0;
}
#endif
#ifndef sys_mutex_set_invalid
void sys_mutex_set_invalid(sys_mutex_t *mutex)
{
    *mutex = NULL;
}
#endif

#endif /* #if LWIP_COMPAT_MUTEX == 0 */


typedef void (*LwipThreadProc)(void *arg);

struct Thread
{
    LwipThreadProc proc;
    void* arg;
};

static ClxResult threadProc(void* data)
{
    struct Thread* thread = (struct Thread*)data;
    thread->proc(thread->arg);
    
    clxPoolsetFree ((void*)thread);
    return CLX_SUCCESS;
}

static u4 numberOfThreads = 0;

sys_thread_t sys_thread_new(
   const char* name,
   void (* threadproc)(void *arg),
   void *arg,
   int stacksize,
   int prio)
{
   if (numberOfThreads == 0)
   {
       struct Thread* thread = (struct Thread*)clxAppPoolsetAlloc(0, __LINE__, sizeof(struct Thread));
       
       thread->proc = threadproc;
       thread->arg = arg;
       

       sys_thread_t ret = clxBeginThread(threadProc,
                    (void*)thread, 
                    "LwipThread", 
                    stacksize, 
                    clarinoxWlanPlatformTaskPriorityTable,
					ClxThreadPriority_Low);

       numberOfThreads++;
       
       return ret;
   }
   else
   {
       return NULL;
   }
}

/*
 * Prints an assertion messages and aborts execution.
 */
void sys_assert( const char * msg )
{	
	CLX_ASSERT(0);
}


/*
 * Current time in msec.
 */
u32_t sys_now( void  )
{
   return (u32_t) clxTickTime();
}

u32_t LWIP_RAND()
{
	return rand();
}

#endif // #if !defined(NO_SYS) || (NO_SYS == 0)

