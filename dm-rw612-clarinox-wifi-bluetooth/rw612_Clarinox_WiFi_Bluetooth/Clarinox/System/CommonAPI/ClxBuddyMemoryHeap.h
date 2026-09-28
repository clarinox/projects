#ifndef ClxBuddyMemoryHeap_h
#define ClxBuddyMemoryHeap_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxBuddyMemoryHeap.h
* Description         Private Buddy Memory Heap
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif


/**
A memory heap which uses Buddy Memory Allocation algorithm to allocate buffers of different sizes.

IMPORTANT : Access to a buddy memory heap is NOT thread safe. If the memory heap is to be accessed by two or more threads, a multi-thread access
protection mechanism (e.g. such as a mutex) shall be applied externally by the application.
*/
typedef void* ClxBuddyMemoryHeapHandle;

/**
Creates a memory heap object and returns a handle to it. The heap is based on Buddy Memory Allocation algorithm: The heap is made up of one or more base blocks.
The size of an allocated buffer will always be ((2^n) * BaseBlockSize) where n may be zero and more.

NOTE : Base block size is always a power of 2. The first argument passed to this function (minAllocationSize) is used to calculate the base block size. The base block size
is always larger than minAllocationSize.

Example : If BaseBlockSize is 32, allocated buffers can be 32, 64, 128, 256, 512, ... bytes long. 

\param[ in ] minAllocationSize The minimum allocation size. Lower values for this argument result in less memory waste, but more allocation/de-allocation overhead.
Higher values result in less allocation/de-allocation overhead but more memory waste. 
\param[ in ] totalHeapSize Total size of the heap, in bytes. If not a power-of-2 value, it will be rounded up to the next power-of-2 value. 
\param[ in ] allocMemFunc The function which is called to allocate the entire memory heap, as a single contiguous chunk of memory. This argument can be NULL. if set to NULL,
the memory for the private heap will be allocated from the ClarinoxSoftFrame poolset (In this case, ClarinoxSoftframe shall already have been initialized).

\return A handle to the private Buddy memory heap.
*/
ClxBuddyMemoryHeapHandle clxCreateMemoryHeap(u4 minAllocationSize, u4 totalHeapSize, const ClxPackage* package, ClxAllocMemFunc allocMemFunc);

/**
Allocates memory from a memory heap, and returns a pointer to the allocated buffer in the memory. This function may be called in the context of a CPU Interrupt Service Routine (ISR).
If there is no free buffer in the heap with the requested size, this function will return NULL.

If successful, the allocated buffer is guaranteed to be aligned for the underlying platform (e.g. according to the value of CLX_REQUIRED_ALIGNMENT).

\param[ in ] heapHandle The handle to the memory heap as returned by #clxCreateMemoryHeap.
\param[ in ] size The size of the buffer required to be allocated.
\return A pointer to the allocated buffer in the memory heap. Will be NULL if there is no free buffer available, or the size argument is invalid.
*/
void* ClxPlatformAligned_ clxAllocateHeapMemoryBlock(ClxBuddyMemoryHeapHandle heapHandle, u4 size);

/**
Frees a buffer previously allocated in the memory heap by a call to clxAllocateHeapMemoryBlock. If the function detects memory corruption, BLACKBOX will occur.
This function may be called in the context of a CPU Interrupt Service Routine (ISR).

\param[ in ] heapHandle The handle to the memory heap as returned by #clxCreateMemoryHeap.
\param[ in ] buf A pointer to the buffer to be freed. This shall be the same the value returned by clxAllocateHeapMemoryBlock.
*/
void clxFreeHeapMemoryBlock(ClxBuddyMemoryHeapHandle heapHandle, void* buf);


/**
Destroys the memory heap by freeing any memory allocated for it.
After this function returns, the handle to the memory heap will be invalid and SHALL not be used any longer.

NOTE : Before this function is called, ALL previously-allocated buffers shall already have been freed. Otherwise,
a BLACKBOX will occur.

\param[ in ] heapHandle The handle to the memory heap as returned by #clxCreateMemoryHeap.
\param[ in ] freeMemFunc The function which is called by #clxDestroyMemoryHeap() to free the memory allocated for the memory heap. This argument may be NULL only if
allocMemFunc (as passed to clxCreateMemoryHeap) was also NULL. Otherwise, it shall match allocMemFunc.
*/
void clxDestroyMemoryHeap(ClxBuddyMemoryHeapHandle heapHandle, ClxFreeMemFunc freeMemFunc);


/**
Checks for corruption in a memory heap. If corruption is detected, a BLACKBOX will occur.

\param[ in ] heapHandle The handle to the memory heap as returned by #clxCreateMemoryHeap.
*/
void clxCheckMemoryHeapForCorruption(ClxBuddyMemoryHeapHandle heapHandle);


#ifdef __cplusplus
}
#endif


#endif // ClxBuddyMemoryHeap_h
