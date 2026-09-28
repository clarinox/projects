/*******************************************************************************
*
* Project             Bluetooth Application
* File                ClxBspHeap.cpp
* Description         Clarinox heap functions and variables are defined here.
*
* This file contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include <stdlib.h>
//#include <cr_section_macros.h>
#include "pin_mux.h"

/* 
 * Use a custom memory pool set: as follows 
 * The first element is the user buffer size and the second one is the no of buffers required
 * Buffer size must be in ascending order
 * Buffer size must be a multiple of 4
 * Use Clarinox Debugger to tune the buffer size and numbers
 */

BufferDetails userMemoryPool[] = {
    { 8     ,   25 },     //0
    { 12    ,   10 },     //1
    { 16    ,   25 },     //2
    { 20    ,   5  },     //3
    { 24    ,   10 },     //4
    { 32    ,   10 },     //5
    { 40    ,   5  },     //6
    { 44    ,   5  },     //7
    { 48    ,   5  },     //8
    { 60    ,   5  },     //9
    { 80    ,   10 },     //10
    { 88    ,   10 },     //11
    { 92    ,   25 },     //12
    { 108   ,   10 },     //13
    { 128   ,   10 },     //14
    { 144   ,   5  },     //15
    { 164   ,   5  },     //16
    { 172   ,   10 },     //17
    { 202   ,   8  },     //18
    { 240   ,   8  },     //19
    { 260   ,   8  },     //20
    { 296   ,   5  },     //21
    { 384   ,   8  },     //22
    { 428   ,   1  },     //23
    { 496   ,   6  },     //24
    { 552   ,   5  },     //25
    { 656   ,   4  },     //26
    { 764   ,   3  },     //27
    { 860   ,   4  },     //28
    { 920   ,   3  },     //29
    { 1088  ,   1  },     //30
    { 1296  ,   1  },     //31
    { 1400  ,   1  },     //32
    { 1860  ,   1  },     //33
    { 2740  ,   1  },     //34
    { 3600  ,   1  },     //35
    { 4648  ,   1  },     //36
    { 6200  ,   1  },     //37
    { 8456  ,   1  },     //38
    { 10880 ,   1  },     //39
    { 11664 ,   1  },     //40
    { 14880 ,   1  },     //41
    { 56000 ,   1  },     //42
    { 65740 ,   1  },     //43

    {MLAN_HEAP_SIZE, 1}
};

USER_SUPPLIED_MEMORY_POOL(userMemoryPool)


/*  
Allocates a private heap of size CLARINOX_PRIVATE_HEAP_SIZE used for Clarinox stack and SoftFrame allocations. Clarinox SoftFrame 
infrastructure uses the function clxMemoryAllocateFromPrivateHeap to allocate memory for Clarinox poolset table and for any 
further memory expansion if required (confined to the heap size). The memory allocation could be either static or dynamic. 
The size of this heap depends on the protocol/profile requested which allocates a pre-determined buffer size that is controlled 
by user settings in the BSP. Hence the maximum heap size required is limited for a given application.

Clarinox Debugger tools (Memory Monitor, Memory Poolset, Memory Statistics) can be used to analyze the Clarinox heap usage. 

Memory Monitor - Provides information (Module ID, Line number, Buffer address, size, allocation time and status) about memory allocation 
and de-allocation by Clarinox stack and SoftFrame modules

Memory Poolset - Provides information (number of buffers defined and number of buffers used) about Clarinox poolset table usage.

Memory Statistics - Provides statistical information (Total allocations, de-allocations, Max Buffers used, Average buffers used and Memory leak) 
about Clarinox memory pool usage
*/

#if defined (CLX_USE_CONTINUOUS_MEM_SEGMENT)

#define CLX_PRIVATE_HEAP_SIZE                     ( (512U+200U)*1024U )
static s1 clxPrivateHeap[CLX_PRIVATE_HEAP_SIZE] = { 0x00 };

#define PRIVATE_HEAP_START_ADDRESS (clxPrivateHeap)
#define PRIVATE_HEAP_END_ADDRESS   (clxPrivateHeap + CLX_PRIVATE_HEAP_SIZE)

static s1* privateHeapPtr = (s1*)PRIVATE_HEAP_START_ADDRESS;


/**
Assigns the starting address of the heap to privateHeapPtr
*/
void clxMemoryInitPrivateHeap (void)
{
	for (u4 i = 0; i < CLX_PRIVATE_HEAP_SIZE; i ++)
	{
		clxPrivateHeap[i] = 0;
	}
   privateHeapPtr = PRIVATE_HEAP_START_ADDRESS;

}

/**
Destroys the private heap. If a heap is allocated using a dynamic memory scheme then it should be freed here.
*/
void clxMemoryDestroyPrivateHeap (void)
{
   privateHeapPtr = PRIVATE_HEAP_START_ADDRESS;
}

/**
Allocates the memory of "size" and returns the address.
*/
void* clxMemoryAllocateFromPrivateHeap(u4 size)
{
    void* ret = privateHeapPtr;
    privateHeapPtr += size;
    u4 length = (u4) (privateHeapPtr - PRIVATE_HEAP_START_ADDRESS);
    if(length > CLX_PRIVATE_HEAP_SIZE)
    {
    	//clxDebugMsg(ClxDebugLogLevel_Error, "clxMemoryAllocateFromPrivateHeap size %u is too big for the heap", size);
        BLACKBOX;
        //TODO Clarinox code has run out of memory, reset the device.
        while(1)
        {
            clxSleep(100);
        }
    }
    return ret;
}

boolean clxMemoryBelongToPrivateHeap( void* ptr )
{
    if (((s1*)ptr >= PRIVATE_HEAP_START_ADDRESS) &&
        ((s1*)ptr <= PRIVATE_HEAP_END_ADDRESS ) )
    {
        /* This is a buffer in ClarinoxSoftFrame private heap: */
        return TRUE;
    }
    else
    {
        /* This is a buffer from an external heap: */
        return FALSE;
    }
}


#else

#define CLX_PRIVATE_HEAP_SIZE2                     ( 256U*1024U )
#define CLX_PRIVATE_HEAP_SIZE1                     ( 128U*1024U )

__BSS(SRAM_ITC) static s1 clxPrivateHeap1[CLX_PRIVATE_HEAP_SIZE1] = { 0x00 };
__BSS(SRAM_OC) static s1 clxPrivateHeap2[CLX_PRIVATE_HEAP_SIZE2] = { 0x00 };

#define PRIVATE_HEAP_1_START_ADDRESS (clxPrivateHeap1)
#define PRIVATE_HEAP_1_END_ADDRESS   (clxPrivateHeap1 + CLX_PRIVATE_HEAP_SIZE1)

#define PRIVATE_HEAP_2_START_ADDRESS (clxPrivateHeap2)
#define PRIVATE_HEAP_2_END_ADDRESS   (clxPrivateHeap2 + CLX_PRIVATE_HEAP_SIZE2)


static u1 segment_no = 0;
static s1* privateHeapPtr = (s1*)PRIVATE_HEAP_1_START_ADDRESS;

void clxMemoryInitPrivateHeap  (void)
{
    privateHeapPtr = (s1*)PRIVATE_HEAP_1_START_ADDRESS;
}

void clxMemoryDestroyPrivateHeap  (void)
{
    privateHeapPtr = (s1*)PRIVATE_HEAP_1_START_ADDRESS;
}

static int clxMemoryBelongToPrivateHeap(void* ptr)
{
  s4 temp = (s4)ptr;

  if((temp >= PRIVATE_HEAP_1_START_ADDRESS) &&  (temp <= PRIVATE_HEAP_1_END_ADDRESS))
  {
    return 1;
  }
  else if((temp >= PRIVATE_HEAP_2_START_ADDRESS) && (temp <= PRIVATE_HEAP_2_END_ADDRESS))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void* clxMemoryAllocateFromPrivateHeap(u4 size)
{
    s4 temp = (s4)privateHeapPtr;
    s4 x = temp + size;
    void* ret;

    if(segment_no == 0)
    {
        if((temp + size) <= PRIVATE_HEAP_1_END_ADDRESS)
        {
          // allocate memory in the first block
          void* ret = privateHeapPtr;
          privateHeapPtr += size;

          return ret;

        }
        else if(((temp + size) > PRIVATE_HEAP_1_END_ADDRESS))  //transistion from first to second area
        {

          privateHeapPtr = (char*)PRIVATE_HEAP_2_START_ADDRESS;

          segment_no = 1;

          void* ret = privateHeapPtr;
          privateHeapPtr += size;

          return ret;

        }
    }
    else if(segment_no == 1)
    {

       if((temp + size) <= PRIVATE_HEAP_2_END_ADDRESS)
        {
          void* ret = privateHeapPtr;
          privateHeapPtr += size;

          return ret;

        }
        else if(((temp + size) > PRIVATE_HEAP_2_END_ADDRESS))
        {
            //Over flow no memory left.
          	privateHeapPtr = 0;
  			BLACKBOX;
  			exit(0);
        }

    }

}



#endif

/**
Frees a block of memory in the private heap. The memory block must have been allocated by
clxMemoryAllocateFromPrivateHeap function.
*/
void clxMemoryFreeFromPrivateHeap(void* buff)
{}

/**
Overloading delete operators. Memory that belongs to Clarinox heap will be freed using the API #clxPoolsetFree. 
The user can call their implementation if the memory to be freed is outside Clarinox heap.
*/ 
void clxBspDeleteOperator ( void* ptr )
{
    if (clxMemoryBelongToPrivateHeap(ptr) == TRUE)
    {
        /* This is a buffer in ClarinoxSoftFrame private heap: */
        clxPoolsetFree(ptr);
    }
    else
    {
        /* This is a buffer from an external heap: */
        free (ptr);
    }
}


/**
Overloading delete operators (array version). 
*/ 
void clxBspDeleteOperatorArray ( void* ptr )
{

    if (clxMemoryBelongToPrivateHeap(ptr) == TRUE)
    {
        /* This is a buffer in ClarinoxSoftFrame private heap: */
        clxPoolsetFree(ptr);
    }
    else
    {
        /* This is a buffer from an external heap: */
        free (ptr);
    }

}

