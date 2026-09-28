#ifndef ClxPriorityQueueHeap_h
#define ClxPriorityQueueHeap_h

 /*******************************************************************************
*
* Project           Clarinox SoftFrame
* File              ClxPriorityQueueHeap.h
* Description       The ClxPriorityQueueHea pmodule is based on the FreeRTOS 10.2 
*                   heap5 implementation. Heap 5 allows the heap to be defined 
*                   across multiple non-contiguous blocks and combines 
*                   (coalescences) adjacent memory blocks as they are freed.
*
*******************************************************************************/


/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


#ifdef __cplusplus
extern "C" {
#endif


#define CLX_HEAP5_MAX_NUM_OF_HEAP_AREAS				10U

struct ClxPriorityQueueHeap;
typedef struct ClxPriorityQueueHeap* ClxPriorityQueueHeapHandle;


/**
Creates a binary tree heap object. Up to 10 non-contiguous buffers may be allocated for the heap.
*/
ClxPriorityQueueHeapHandle clxPriorityQueueHeapCreate(u4 memBlockSize, u1 numBlocks);	

/**
Creates a binary tree heap object. A single static buffer (allocated and owned by the caller) will be used as the heap.
The caller must NOT modifiy or deleted the provided buffer until the heap object is destroyed by a call to clxHeap5_destroy.
*/
ClxPriorityQueueHeapHandle clxPriorityQueueHeapCreateStatic(ClxMaxAlignType* staticBuffer, size_t bufferSizeInBytes);

/**
Destroys the heap object. If the heap internal buffers are owned (e.g. internally allocated) by the heap object, they will be
removed as well.
*/
void clxPriorityQueueHeapDestroy(ClxPriorityQueueHeapHandle handle);

/**
Allocates memory of requested size.
*/
void* clxPriorityQueueHeapMalloc(ClxPriorityQueueHeapHandle handle, size_t xWantedSize);

/**
Frees allocated memory.
*/
void clxPriorityQueueHeapFree(ClxPriorityQueueHeapHandle handle, void *pv);

/**
Get free heap size.
*/
size_t clxPriorityQueueHeapGetFreeHeapSize(ClxPriorityQueueHeapHandle handle);

/**
Get minimum ever free heap size.
*/
size_t clxPriorityQueueHeapGetMinEverFreeHeapSize(ClxPriorityQueueHeapHandle handle);

/**
 Checks whether particular memory address belongs to this heap.
 */
boolean clxPriorityQueueHeapBelongsToHeap(ClxPriorityQueueHeapHandle handle, void *pv);


#ifdef __cplusplus
}
#endif


#endif // ClxPriorityQueueHeap_h
