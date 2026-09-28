#ifndef ClxFifoList_h
#define ClxFifoList_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxFifoList.h
* Description         ClxFifoList
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
A simple list of opaque object pointers, with FIFO structure.
Items in the list are void pointers which may point to any type of objects.
*/
struct ClxFifoList;

/**
Creates and returns a FIFO list. The list capacity (number of items which can be pushed into the list) is fixed and provided as the first argument.

\param[ in ] listCapacity The list capacity, as the maximum number of items which can be pushed into the list. The capacity is always a power-of-2 value.
                          If the provided value is not a power of 2, it will be rounded up to the next power-of-2 value (For example, if the provided value is 17, the line capacity will be 32).
                          The capacity of a FIFO list is fixed. The FIFO list will NOT be expanded, or shrunk.

\param[ in ] allocMemFunc An optional function pointer which will be called to allocate any required space in the memory. If set to NULL, the required space will be allocated in the ClarinoxSoftFrame poolset.

\return Pointer to the FIFO list.
*/
struct ClxFifoList* clxCreateFifoList(ClxSize listCapacity, ClxAllocMemFunc allocMemFunc);

/**
Pushes a new item to the end of a FIFO list.

\param[ in ] list The FIFO list.
\param[ in ] item The item to push into the list. The item is a void pointer which may point to any object. The pointer itself will be stored in the list.

\return TRUE if the new item was successfully pushed into the end of the FIFO list.
        FALSE if the item cannot be pushed into the list since the list is full.
*/
boolean clxPushToFifoList(struct ClxFifoList* list, void* item);

/**
Pops an item from the beginning of a FIFO list, and returns it.

\param[ in ] list The FIFO list.

\return Pointer to the popped item. This will be NULL if no item was popped out since the list is empty.
*/
void* clxPopFromFifoList(struct ClxFifoList* list);

/**
Gets the number of items in a FIFO list.

\param[ in ] list The FIFO list.

\return Number of items currently stored in the list.
*/
ClxSize clxGetNumberOfItemsInFifoList(struct ClxFifoList* list);

/**
Destroys a FIFO list by releasing its memory. Any item in the list will be ignored.

\param[ in ] list The FIFO list.
\param[ in ] freeMemFunc An optional function pointer which will be called to release the list memory. If set to NULL, the memory will be released to the ClarinoxSoftFrame poolset.
*/
void clxDestroyFifoList(struct ClxFifoList* list, ClxFreeMemFunc freeMemFunc);


#ifdef __cplusplus
}
#endif



#endif    // ClxFifoList_h
