#ifndef ClxPrivateMemoryPool_h
#define ClxPrivateMemoryPool_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxPrivateMemoryPoolHandle.h
* Description         Private Single-sized Memory Pool
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#if defined(CLX_GNU)
#   define CLX_NEW_THROW   throw()
#else
#   define CLX_NEW_THROW     
#endif


#ifdef __cplusplus
extern "C" {
#endif


/**
A Private Memory Pool is a single contiguous chunk of memory which is divided into one or buffers of fixed size. Each fixed-size buffer in the pool may
be allocated and freed individually. After initialization of a private pool, the size of each buffer can not be modified. However, the total number of buffers
in the pool may be increased by expanding the pool object.

IMPORTANT : Access to a private memory pool is NOT thread safe. If the private pool is to be accessed by two or more threads, a multi-thread access
protection mechanism (e.g. such as a Mutex) shall be applied externally by the application.
*/
typedef size_t ClxPrivateMemoryPoolHandle;

/**
Creates a private memory pool object of fixed-sized buffers and returns a handle to it.
The pool object is initialized with 0 or more buffers. The number of buffers may be increased later on by a call to #clxExpandPrivateMemoryHeap.

\param[ in ] numberOfBuffers    Number of fixed-size buffers which the private pool will contain. This value may be set to 0.
\param[ in ] maxAllocationSize  The maximum size which can be allocated using the function clxAllocatePrivateMemoryPoolBuffer(). This is the size of each fixed-sized buffer in the pool.
\param[ in ] package            The package object which is to be passed to the allocation function. 
\param[ in ] allocMemFunc       The function which is called to allocate the entire private memory pool, as a single contiguous chunk of memory. This argument can be NULL. if set to NULL,
                                the memory for the private pool will be allocated from the ClarinoxSoftFrame poolset (In this case, ClarinoxSoftframe shall already have been initialized).

\return A handle to the private memory pool.
*/
ClxPrivateMemoryPoolHandle clxCreatePrivateMemoryPool(u4 numberOfBuffers, 
													  u4 maxAllocationSize,
                                                      const ClxPackage* package,
													  ClxAllocMemFunc allocMemFunc);

/**
Allocates memory from a private pool set, and returns a pointer to the allocated buffer in the memory. 
If there is no free buffer in the pool, or if the requested size is more than the size of each buffer (as passed to #clxCreatePrivateMemoryPool),
this function will return NULL.

NOTE : If the requested size is less than the size of each fixed-size buffer, the entire buffer will be allocated and returned.

\param[ in ] pool The handle to the private pool as returned by #clxCreatePrivateMemoryPool.
\param[ in ] size The size of the buffer required to be allocated. This size cannot be more than the maxBufferSize argument passed to #clxCreatePrivateMemoryPool.
\return A pointer to the allocated buffer in the private pool. Will be NULL if there is no free buffer available, or the size argument is invalid.
*/
void* clxAllocatePrivateMemoryPoolBuffer(ClxPrivateMemoryPoolHandle poolHandle, u4 size);

/**
Frees a buffer previously allocated in the private pool by a call to clxAllocatePrivateMemoryPoolBuffer. If the function detects memory corruption, BLACKBOX will occur.

\param[ in ] buf A pointer to the buffer to be freed. This shall be the same the value returned by clxAllocatePrivateMemoryPoolBuffer.
*/
void clxFreePrivateMemoryPoolBuffer(void* buf);

/**
Determines if there is a free buffer available in the private memory pool.

\param[ in ] pool The handle to the private pool as returned by #clxCreatePrivateMemoryPool.
\param[ in ] size The size of the buffer required.

\return TRUE if there is a free buffer available.
FALSE if there is no free buffer, or the argument 'size' exceeds the maximum allocation size (as passed to #clxCreatePrivateMemoryPool).
*/
boolean clxIsPrivateMemoryPoolBufferAvailable(ClxPrivateMemoryPoolHandle poolHandle, u4 size);

/**
Returns the number of free (non-allocated) fixed-sized buffers available in the private memory pool.

\param[ in ] pool The handle to the private pool as returned by #clxCreatePrivateMemoryPool.

\return The number of free (non-allocated) fixed-sized buffers available in the private memory pool.
*/
u4 clxGetNumberOfPrivateMemoryFreeBuffers(ClxPrivateMemoryPoolHandle poolHandle);


/**
Returns the total number of fixed-sized buffers (free or allocated) available in the private memory pool.

\param[ in ] pool The handle to the private pool as returned by #clxCreatePrivateMemoryPool.

\return The total number of fixed-sized buffers (free or allocated) available in the private memory pool.
*/
u4 clxGetTotalNumberOfPrivateMemoryBuffers(ClxPrivateMemoryPoolHandle poolHandle);


/**
Expands the private memory pool with one or more extra buffers. The new buffers will have the same maximum buffer size as the value passed to #clxCreatePrivateMemoryPool.
The new block of memory for the new buffer will be allocated by calling the same allocation function passed to #clxCreatePrivateMemoryPool.

\param[ in ] pool The handle to the private pool as returned by #clxCreatePrivateMemoryPool.
\param[ in ] numberOfExtraBuffers The number of extra buffers to be allocated and attached to the private memory pool.
\param[ in ] package The package object which is to be passed to the allocation function. This value may be different from the package value passed to #clxCreatePrivateMemoryPool.
*/
void clxExpandPrivateMemoryHeap(ClxPrivateMemoryPoolHandle poolHandle, 
                                u4 numberOfExtraBuffers,
                                const ClxPackage* package);

/**
Destroys the private memory pool by freeing any memory allocated for it. The freeMemFunc function passed to #clxCreatePrivateMemoryPool will be used to free the memory.
After this function returns, the handle to the private memory will be invalid and SHALL not be used any longer.

\param[ in ] pool The handle to the private pool as returned by #clxCreatePrivateMemoryPool.
\param[ in ] freeMemFunc The function which is called by #clxDestroyPrivateMemoryPool() to free the memory allocated for the private memory pool. This argument may be NULL only if
             allocMemFunc (as passed to clxCreatePrivateMemoryPool) was also NULL. Otherwise, it shall match allocMemFunc.
*/
void clxDestroyPrivateMemoryPool(ClxPrivateMemoryPoolHandle poolHandle, ClxFreeMemFunc freeMemFunc);

/**
Checks the entire private memory pool for corruption. If corruption is detected, BLACKBOX(s) will occur.

\param[ in ] pool The handle to the private pool as returned by #clxCreatePrivateMemoryPool.

\return If no BLACKBOX occurs, the function will return the number of buffers which are currently free (not allocated). This value can be used, for instance right before
destroying the private pool by a call to #clxDestroyPrivateMemoryPool, in oder to make sure all buffers are freed 
(in this case, return value shall be equal to numberOfBuffers as passed to #clxCreatePrivateMemoryPool).  
*/
void clxCheckPrivateMemoryPoolForCorruption(ClxPrivateMemoryPoolHandle poolHandle);


#ifdef __cplusplus
}
#endif



#ifdef __cplusplus

/**
Base class for a C++ object which is to be allocated in a private memory pool.
NOTE : It might not be safe to allocate a C++ object which does not derive from ClxPrivatePoolAllocator
in a private memory pool (e.g. for instance by using placement new operator). Always use this base class.

An instance of a class which derives from ClxPrivatePoolAllocator CANNOT be allocated anywhere other than a private memory pool.
Therefore, in order to allocate an object of the arbitrary type T (which does not derive from ClxPrivatePoolAllocator) in a private memory pool,
a new class can be defined which multiply derives from both T and ClxPrivatePoolAllocator, as follows:

T is an arbitrary C++ class which has a VIRTUAL DESTRUCTOR. 
Define any required constructor if T has non-default constuctors.

class T_PrivatePoolAllocator : public T, public ClxPrivatePoolAllocator
{
public:

};

In order to allocate an instance of T in a private pool called 'privatePool' :

T* obj = new(privatePool) T_PrivatePoolAllocator (constructor_args);

In order to destruct and de-allocate obj from the private pool:

delete obj;

However, T SHALL have a virtual destructor. Otherwise, the behaviour will be undefined.
*/
class ClxPrivatePoolAllocator
{
private:
	/* Cannot be used to allocate an object of this class (or a derived class): */
    void* operator new (size_t size) CLX_NEW_THROW
    {
    	(void)size;
		CLX_ASSERT(0);
        return NULL;
    }
    
	/* Cannot be used to allocate an object of this class (or a derived class): */
    void* operator new[] (size_t size) CLX_NEW_THROW
    {
    	(void)size;
		CLX_ASSERT(0);
        return NULL;
    }

	/* Cannot be used to allocate an object of this class (or a derived class): */
	void* operator new (size_t size, const ClxPackage* package, u2 moduleID, u4 line) CLX_NEW_THROW
	{
		(void)size;
		(void)package;
		(void)moduleID;
		(void)line;
		CLX_ASSERT(0);
		return NULL;
	}

	/* Cannot be used to allocate an object of this class (or a derived class): */
	void* operator new[] (size_t size, const ClxPackage* package, u2 moduleID, u4 line) CLX_NEW_THROW
	{
		(void)size;
		(void)package;
		(void)moduleID;
		(void)line;
		CLX_ASSERT(0);
		return NULL;
	}

public:
    void* operator new (size_t size, ClxPrivateMemoryPoolHandle poolHandle)
    {
		return clxAllocatePrivateMemoryPoolBuffer(poolHandle, (u4)size);
    }

	void* operator new[](size_t size, ClxPrivateMemoryPoolHandle poolHandle)
    {
		return clxAllocatePrivateMemoryPoolBuffer(poolHandle, (u4)size);
    }

	void operator delete(void* buf, ClxPrivateMemoryPoolHandle poolHandle)
    {
		 (void)poolHandle;
        clxFreePrivateMemoryPoolBuffer(buf);
    }

	void operator delete[](void* buf, ClxPrivateMemoryPoolHandle poolHandle)
    {
		(void)poolHandle;
        clxFreePrivateMemoryPoolBuffer(buf);
    }

    void operator delete(void* buf)
    {
        clxFreePrivateMemoryPoolBuffer(buf);
    }

    void operator delete[](void* buf)
    {
        clxFreePrivateMemoryPoolBuffer(buf);
    }
};


#endif

#endif // ClxPrivateMemoryPool_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/
