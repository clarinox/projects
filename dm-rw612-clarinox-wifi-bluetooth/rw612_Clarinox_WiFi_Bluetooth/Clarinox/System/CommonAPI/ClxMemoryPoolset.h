#ifndef ClxMemoryPoolset_h
#define ClxMemoryPoolset_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxMemoryPoolset.h
* Description         Clarinox memory poolset definitions
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

/**
Define USER_SUPPLIED_MEMORY_POOL at the beginning of your application's main file (or BSP) to define
own set of memory poolset for the application. The following is an example of how to define a poolset:

\code

#include "ClxMemoryPoolset.h"

//   Below we will define a poolset with 21 pools of sized 4 bytes to 1.2 MB
//   At each row, the first number is the size of memory blocks in the corresponding memory pool
//   The second number is the number of memory blocks in the corresponding memory pool.
//   Note that the size of buffers in all pools are divisible by 4 (4, 8, 12, ... 12000000).

USER_SUPPLIED_MEMORY_POOL(
    { 4, 1200    }, 
    { 8, 400     }, 
    { 12, 1200   },
    { 16, 1200   }, 
    { 20, 200    }, 
    { 24, 400    },
    { 28, 400    }, 
    { 36, 600    }, 
    { 40, 50     },
    { 52, 20     }, 
    { 60, 40     }, 
    { 108, 60    },
    { 116, 15    }, 
    { 160, 20    }, 
    { 200, 20    },
    { 520, 8     },
    { 1068, 8    }, 
    { 1424, 20   }, 
    { 12000, 8   }, 
    { 2800000, 1 }, 
    { 12000000, 1}, );
\endcode
*/

// BufferDetails userSuppliedMemoryPool_[]

#ifdef __cplusplus

#define USER_SUPPLIED_MEMORY_POOL(memoryPool)											 \
	extern "C"																			 \
	{																				     \
		u4 userSuppliedMemoryPoolSize = sizeof( memoryPool ) / sizeof( BufferDetails );  \
		const BufferDetails* userSuppliedMemoryPool = (memoryPool);						 \
	}

#else

#define USER_SUPPLIED_MEMORY_POOL(memoryPool)										 \
	u4 userSuppliedMemoryPoolSize = sizeof( memoryPool ) / sizeof( BufferDetails );  \
	const BufferDetails* userSuppliedMemoryPool = (memoryPool);

#endif




#ifdef __cplusplus
extern "C" {
#endif


typedef struct 
{
    u4 size;
    u4 count;
} BufferDetails;


// _____________________________________________________________________________
//
// Function prototypes for memory allocating, re-allocating and de-allocating functions 
// _____________________________________________________________________________
//

typedef void* (*ClxAllocMemFunc) (const ClxPackage* package, u2 moduleID, u4 line, u4 size );
typedef void* (*ClxReallocMemFunc) (const ClxPackage* package, u2 moduleID, u4 line, void* mem, u4 size );
typedef void (*ClxFreeMemFunc) (void* ptr);



// _____________________________________________________________________________
//
// ClarinoxSoftFrame Memory PoolSet Access Functions 
// _____________________________________________________________________________
//



/**
Allocates a block of memory in the poolset. If the allocation fails for any reason, a BLACKBOX exception will be raised.

\param[ in ] package The package which has requested for the allocation. If NULL, the default package will be assumed.
\param[ in ] moduleID The identifier of the module (file) which is calling this function
\param[ in ] line The line number of the code which is calling this function
\param[ in ] size The size of the memory block to be allocated

\return Pointer to the allocated buffer. This value CANNOT be NULL.
*/
extern void* clxPoolsetAlloc (const ClxPackage* package, u2 moduleID, u4 line, u4 size);


/**
Allocates a block of memory in the poolset and sets its bytes to zero. If the allocation fails for any reason, a BLACKBOX exception will be raised.

\param[ in ] package The package which has requested for the allocation. If NULL, the default package will be assumed.
\param[ in ] moduleID The identifier of the module (file) which is calling this function
\param[ in ] line The line number of the code which is calling this function
\param[ in ] size The size of the memory block to be allocated

\return Pointer to the allocated buffer. This value CANNOT be NULL.
*/
extern void* clxPoolsetAllocZero (const ClxPackage* package, u2 moduleID, u4 line, u4 size);


/**
Reallocates a block of memory in the poolset. If the re-allocation fails for any reason, a BLACKBOX exception will be raised.

clxPoolsetRealloc() is used when a larger block of memory is needed for a buffer. 
This function allocates a larger block, copies the content of the buffer to the new block, and frees the old block.

\param[ in ] package The package which has requested for a re-allocation. 
                     This could be different from the package which initially allocated the buffer. If NULL, the default package will be assumed.
\param[ in ] moduleID The identifier of the module (file) which is calling this function
\param[ in ] line The line number of the code which is calling this function
\param[ in ] mem A pointer to a block of memory which is already allocated in the poolset
\param[ in ] size The size of the new memory block to be allocated

\return Pointer to the reallocated buffer. This value CANNOT be NULL.
*/
extern void* clxPoolsetRealloc (const ClxPackage* package, u2 moduleID, u4 line, void* mem, u4 size);


/**
Tries to allocate a block of memory in the poolset. As opposed to #clxPoolsetAlloc() API, if for any reason the allocation attempt fails, this function does NOT raise a BLACKBOX exception.
Instead, it will simply return a NULL pointer. 

The caller MUST always verify whether or not the returned pointer is NULL.

Allocation attempt may fail in one of the following scenarios:

- If the memory pool from which the buffer is to be allocated does not currently have any free buffers. In this case, this function will NOT try to expand the pool, or choose a pool with larger buffers.
- If the size of buffer requested to be allocated is larger than the largest buffers in SoftFrame poolset. 
- The SoftFrame poolset is not yet initialized.

In the scenarios above, this function will return a NULL pointer.

If a buffer is successfully allocated, it may be freed using clxPoolsetFree() function.

NOTE : If memory corruption is detected, this function will still raise a BLACKBOX exception.

\param[ in ] package The package which has requested for the allocation. If NULL, the default package will be assumed.
\param[ in ] moduleID The identifier of the module (file) which is calling this function
\param[ in ] line The line number of the code which is calling this function
\param[ in ] size The size of the memory block to be allocated

\return Pointer to the allocated buffer. NULL if allocation attempt fails.
*/
extern void* clxPoolsetTryAlloc (const ClxPackage* package, u2 moduleID, u4 line, u4 size);


/**
Frees a block of memory previously allocated by #clxPoolsetAlloc(), #clxPoolsetAllocZero(), #clxPoolsetRealloc(), or #clxPoolsetTryAlloc().

NOTE: This function MUST not be used to free a memory block allocated by \b new operator, or \b NEW macro.

\param[ in ] ptr a pointer to the memory block which is to be freed
*/
extern void clxPoolsetFree (void* ptr);

/**
Confirms the integrity of the memory pool elements. The check is done
against memory overruns, underruns and link list integrity. The function
generates an exception if encounters an integrity failure.
*/
extern void clxCheckMemoryCorruption (void);


/**
Allocates a block of memory in the poolset for APPLICATION package. If the allocation attempt fails, a BLACKBOX exception will be raised.

Refer to the documentation of #clxPoolsetAlloc() for more information.

\param[ in ] moduleID The identifier of the module (file) which is calling this function
\param[ in ] line The line number of the code which is calling this function
\param[ in ] size The size of the memory block to be allocated
*/
#define clxAppPoolsetAlloc(moduleID, line, size)            clxPoolsetAlloc(CLX_PACKAGE(APPLICATION), (moduleID), (line), (size))


/**
Allocates a block of memory in the poolset for APPLICATION package and sets its bytes to zero. If the allocation attempt fails, a BLACKBOX exception will be raised.

Refer to the documentation of #clxPoolsetAllocZero() for more information.

\param[ in ] moduleID The identifier of the module (file) which is calling this function
\param[ in ] line The line number of the code which is calling this function
\param[ in ] size The size of the memory block to be allocated

\return Pointer to the allocated buffer. This value CANNOT be NULL.
*/
#define clxAppPoolsetAllocZero(moduleID, line, size)        clxPoolsetAllocZero(CLX_PACKAGE(APPLICATION), (moduleID), (line), (size))


/**
Reallocates a block of memory in the poolset for APPLICATION package. If the reallocation attempt fails, a BLACKBOX exception will be raised.

Refer to the documentation of #clxPoolsetRealloc() for more information.

\param[ in ] moduleID The identifier of the module (file) which is calling this function
\param[ in ] line The line number of the code which is calling this function
\param[ in ] mem A pointer to a block of memory which is already allocated in the poolset
\param[ in ] size The size of the new memory block to be allocated

\return Pointer to the reallocated buffer. This value CANNOT be NULL.
*/
#define clxAppPoolsetRealloc(moduleID, line, mem, size )    clxPoolsetRealloc(CLX_PACKAGE(APPLICATION), (moduleID), (line), (mem), (size))


/**
Tries to allocates a block of memory in the poolset for APPLICATION package. 
This macro uses #clxPoolsetTryAlloc(). Therefore, the returned value may be NULL. Refer to the documentation of #clxPoolsetTryAlloc() for more information.

\param[ in ] moduleID The identifier of the module (file) which is calling this function
\param[ in ] line The line number of the code which is calling this function
\param[ in ] size The size of the memory block to be allocated

\return Pointer to the allocated buffer. NULL if allocation attempt fails.
*/
#define clxAppPoolsetTryAlloc(moduleID, line, size)         clxPoolsetTryAlloc(CLX_PACKAGE(APPLICATION), (moduleID), (line), (size))


/**
Allocates a block of memory in the poolset for APPLICATION package. Refer to documentation of #clxAppPoolsetAlloc() for more information.

\param[ in ] size The size of the memory block to be allocated
*/
#define clxAppAlloc(size)                                   clxAppPoolsetAlloc(CLX_MODULE_ID, __LINE__, size)


/**
Allocates a block of memory in the poolset for APPLICATION package, and sets all its bytes to zero.  Refer to documentation of #clxAppPoolsetAlloc() for more information.
\param[ in ] size The size of the memory block to be allocated
*/
#define clxAppAllocZero(size)                               clxAppPoolsetAllocZero(CLX_MODULE_ID, __LINE__, size)


/**
Tries to allocates a block of memory in the poolset for APPLICATION package. 

This macro may return NULL. Refer to documentation of #clxAppPoolsetAlloc() for more information.

\param[ in ] size The size of the memory block to be allocated
*/
#define clxAppTryAlloc(size)                                clxAppPoolsetTryAlloc(CLX_MODULE_ID, __LINE__, size)



// _____________________________________________________________________________
//
// Private heap support for memory poolset
// All the following functions SHALL be defined in the BSP
// _____________________________________________________________________________
//

/**
Initializes the private heap. When this function returns, Clarinox SoftFrame assumes the complete
ownership of the heap. No information about the heap is supposed to be reported to SoftFrame.
This function must be implemented, even if there is no need for initializing the heap.
*/
extern void clxMemoryInitPrivateHeap (void);

/**
Destroys the private heap. When this function is called, Clarinox SoftFrame has already given up the ownership
of the heap.

This function must be implemented, even if there is no need for destroying the heap.
*/
extern void clxMemoryDestroyPrivateHeap (void);

/**
Allocates a contiguous memory block in the private heap. If no memory block with the size requested is available,
this function must return NULL.

\param[ in ] allocationSize size of the contiguous memory block requested.

\return A pointer to the allocated memory block of size \p allocationSize.
*/
extern void* clxMemoryAllocateFromPrivateHeap (unsigned int allocationSize);

/**
Frees a block of memory in the private heap. The memory block must have been allocated by clxMemoryAllocateFromPrivateHeap function.

\param[ in ] buff A pointer to the buffer which is to be freed. This pointer must have been returned by clxMemoryAllocateFromPrivateHeap.
*/
extern void clxMemoryFreeFromPrivateHeap (void* buff);

/**
To be implemented in application side when application side is not overriding the delete operator 
Also need to define macro CLX_DELETE_IN_SYSTEM if application side is not overriding the delete operator.

\param[ in ] ptr A pointer to the object which will be deleted.
*/
extern void clxBspDeleteOperator ( void* ptr );

/**
To be implemented in application side when application side is not overriding the detele[] operator 
Also need to define macro CLX_DELETE_IN_SYSTEM if application side is not overriding the delete[] operator.

\param[ in ] ptr A pointer to the object which will be deleted.

*/
extern void clxBspDeleteOperatorArray ( void* ptr );



/************************
ClxMemoryPoolBufferList
************************/
struct ClxMemoryPoolBufferList;

/**
An object of type ClxMemoryPoolBufferListHandle manages a list of buffers of a fixed size in SoftFrame Poolset. 
A ClxMemoryPoolBufferListHandle object provides a safe alternative to standard clxPoolsetAlloc() API in the sense that, as opposed to the API mentioned, 
the ClxMemoryPoolBufferListHandle object does NOT treat an out-of-memory condition as a fatal error. Instead, the allocation attempt will simply return a NULL pointer. Therefore,
a ClxMemoryPoolBufferListHandle object may be used in situations where a best-effort allocation attempt is sufficient.

ClxMemoryPoolBufferListHandle provides the following two mechanisms to simplify the memory management in platforms with memory constraint:

- Maximum number of buffer allocations may be limited. When the maximum number of buffers are allocated, subsequent allocation attempts will simply fail by retuning a NULL pointer.
- Optionally, one or more buffers may be reserved. The ClxMemoryPoolBufferListHandle object attempts to pre-allocate and maintain a list of reserved buffers. When an allocation request
  is received by the user, a reserved buffer (if any available) will be returned. If there is no reserved buffer is available at the time of allocation request, then a new buffer will be allocated
  from the SoftFrame poolset. When the allocated buffers are freed, the ClxMemoryPoolBufferListHandle object will store the buffers internally (without handing them back the SoftFrame poolset) until
  enough buffers (as determined by the current number of reserved buffers) are stored. Then, the rest of the buffers will be directly freed back to the SoftFrame poolset.
  Buffer reservation may be used by the user in order to maintain a minimum number of buffers.

  NOTE : the number of reserved buffers may be updated (increased or decreased) at any time.

NOTE : A ClxMemoryPoolBufferListHandle NEVER expands the SoftFrame memory poolset.   
*/
typedef struct ClxMemoryPoolBufferList* ClxMemoryPoolBufferListHandle;


/**
Creates and returns a memory pool buffer list of type ClxMemoryPoolBufferListHandle. This function may be called only when the SoftFrame poolset is already initialized.

NOTE : If you wish to use a memory pool buffer list object for C++ object allocation, DO NOT use this function directly. Instead, create an object of type ClxMemoryPoolBufferListAllocator (which calls this function internally).

\param[ in ] name                The name of the memory pool buffer list. Used for debugging purposes. May be set to NULL.
\param[ in ] bufferSize          The size of each buffer which will be allocated by this object.
\param[ in ] maxNumberOfBuffers  The maximum number of buffer which may be allocated via this object. Any allocation attempt beyond this limit will result in a NULL pointer 
                                 (even if there are more buffers available in the SoftFrame pool).
\param[ in ] package             The package to which this object belongs. This package will be used for all buffer allocations.
                                
\return A pointer to a ClxMemoryPoolBufferList object. NULL if SoftFrame poolset is not yet initialized, or the SoftFrame poolset does not have a pool of buffers large enough for the requested buffer size.
*/
extern ClxMemoryPoolBufferListHandle clxMemoryPoolBufferListCreate(const s1* name, u4 bufferSize, u2 maxNumberOfBuffers, const ClxPackage* package);

/**
Reserves zero or more buffers for the ClxMemoryPoolBufferListHandle object. The API will try to adjust the internal reserved buffer list immediately (e.g. by allocating more buffers or freeing some or all of the
buffers currently in the free reserved list). This API may be called at any time.

NOTE : When a ClxMemoryPoolBufferListHandle object is initially created, it will have zero reserved buffers.

\param[ in ] handle       The ClxMemoryPoolBufferListHandle object.
\param[ in ] numOfBuffers Number of buffers to reserve. This value may be equal, less, or greater than the current number of reserved buffers. A value of zero is allowed. 
                          NOTE : If the provided value is larger than the maximum number of buffers allowed for the ClxMemoryPoolBufferListHandle object (as passed to #clxMemoryPoolBufferListCreate() API), this
                                 value will also be set the maximum value.
\param[ in ] moduleID     The ModuleID of the module calling this function. This will be used only if this function requires one or more new buffers from the SoftFrame poolset (for debugging purposes).
\param[ in ] line         The line of code calling this function. This will be used only if this function requires one or more new buffers from the SoftFrame poolset (for debugging purposes).

\return Current number of allocated buffers for this object. This includes both the free reserved buffers, and any allocated buffers which have not been freed yet.
*/
extern u2 clxMemoryPoolBufferListReserve(ClxMemoryPoolBufferListHandle handle, u2 numOfBuffers, u2 moduleID, u4 line);


/**
Allocates a buffer via the ClxMemoryPoolBufferListHandle object. If there is any free reserved buffer currently stored internally in the object, it will be returned. Otherwise, a new buffer will be allocated from SoftFrame
poolset and returned.

NOTE : Any buffer allocated via this function MUST be freed using clxPoolsetFree() or clxFree().

\param[ in ] handle   The ClxMemoryPoolBufferListHandle object.
\param[ in ] moduleID The ModuleID of the module calling this function. This will be used only if this function requires to allocate a new object from the SoftFrame poolset (for debugging purposes).
\param[ in ] line     The line of code calling this function. This will be used only if this function requires to allocate a new object from the SoftFrame poolset (for debugging purposes).
\param[ in ] size     The size of the buffer to be allocated. If this value is larger than the buffer size passed to #clxMemoryPoolBufferListCreate(), the function will fail and return NULL.

\return Pointer to allocated buffer. 
        NULL if the current number of allocations has already reached the maximum number of allocations (as passed to #clxMemoryPoolBufferListCreate() function), 
        there is no more buffer to allocate, or the provided size is larger than the maximum allocation size provided to the #clxMemoryPoolBufferListCreate() function. 
*/
extern void* clxMemoryPoolBufferListAllocate(ClxMemoryPoolBufferListHandle handle, u2 moduleID, u4 line, u4 size);


/**
Destroys a ClxMemoryPoolBufferListHandle object. If there is any free reserved buffers currently in the internal buffer list, it will be freed by this function.
NOTE : When this function is called, if there is any buffer which has been allocated using #clxMemoryPoolBufferListAllocate() but has not been freed yet, a BLACKBOX will occur.

\param[ in ] handle The ClxMemoryPoolBufferListHandle object. After this function returns, the object handle MUST not be accessed any longer.
*/
extern void clxMemoryPoolBufferListDestroy(ClxMemoryPoolBufferListHandle handle);



#ifdef __cplusplus
}
#endif



#ifdef __cplusplus


/**
Used by template classes which require an "Allocator" class. When used, the memory
will be allocated from ClarinoxSoftFrame memory poolset.
*/
class ClxSoftframePoolsetAllocator
{
public:
    void* alloc(size_t size) const
    {
        return clxPoolsetAlloc(NULL, 0U, 0U, (u4)size);
    }

    void free(void* buf) const
    {
        clxPoolsetFree(buf);
    }

    void* realloc(void* buf, size_t size) const
    {
        return clxPoolsetRealloc(NULL, 0U, 0U, buf, (u4)size);
    }

    void* alloc(size_t size, const ClxPackage* package, u2 moduleID, u4 line) const
    {
        return clxPoolsetAlloc(package, moduleID, line, (u4)size);
    }

    void* realloc(void* buf, size_t size, const ClxPackage* package, u2 moduleID, u4 line) const
    {
        return clxPoolsetRealloc(package, moduleID, line, buf, (u4)size);
    }   
};


/**
Used by template classes which require an "Allocator" class. When used, a static memory with
fixed size will be used. Cannot be used when a dynamic allocation of memory buffer is required.
*/
template<size_t MAX_SIZE>
class ClxStaticMemoryAllocator
{
private:
    CLX_PLATFORM_ALIGNED_BUFFER(buf_, MAX_SIZE);

public:
    void* alloc(size_t size) const
    {
        if (size == MAX_SIZE)
        {
            return (void*)buf_;
        }
        else
        {
            return NULL;
        }
    }

    void free(void* buf) const
    {}

    void* realloc(void* buf, size_t size) const
    {
        return NULL;
    }

    void* alloc(size_t size, const ClxPackage* package, u2 moduleID, u4 line) const
    {
        return alloc(size);
    }

    void* realloc(void* buf, size_t size, const ClxPackage* package, u2 moduleID, u4 line) const
    {
        return realloc(buf, size);
    }  
};

#endif // __cplusplus


#endif    // ClxMemoryPoolset_h

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
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused type declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.3                                      */ 
/* Justification : Unused type declarations are to be used in user 		      */
/* 				   applications.      										  */
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
