/************************************************************************************
*
* Project             ClarinoxMesh Application
* File                NetworkBufferManager.Bsp.cpp
* Description         Implementation of ClxNetworkBufferPool interface for RW612
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*************************************************************************************/


#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MESH_BUFFER_POOL_NAME	"clarinox.wlan.mesh"

#define MAX_NETWORK_INPUT_SIZE                       (25*1024) //100kB


struct ClxNetworkBufferPool
{
	u4 numberOfAllocatedBuffer;
};


typedef struct ClxNetworkBufferWithRefCountStruct
{
	struct ClxNetworkBuffer base;
	u4						refCount;
} ClxNetworkBufferWithRefCount;


struct ClxNetworkBufferPool meshBufferPool = { 0 };

u4 clxNetworkInputBuffer[MAX_NETWORK_INPUT_SIZE];
ClxPriorityQueueHeapHandle  queueHeapHandle;


struct ClxNetworkBufferPool* clxBspNetworkBufferPoolOpen(const s1* poolName)
{
	if (strcmp(poolName, MESH_BUFFER_POOL_NAME) == 0)
	{
		BLACKBOX_IF(meshBufferPool.numberOfAllocatedBuffer > 0);

		queueHeapHandle =  clxPriorityQueueHeapCreateStatic(clxNetworkInputBuffer, (4*MAX_NETWORK_INPUT_SIZE));

		return &meshBufferPool;
	}

	return NULL;
}

void clxBspNetworkBufferPoolClose(_in_ struct ClxNetworkBufferPool* pool)
{
	if (pool->numberOfAllocatedBuffer > 0)
	{
		BLACKBOX;
	}
}

ClxNetworkBufferHandle clxBspNetworkBufferPoolAlloc(_in_ struct ClxNetworkBufferPool* pool,
													_in_ u2 bufferSize,
													_in_ u2 flags)
{
	//ClxNetworkBufferWithRefCount* buffer = (ClxNetworkBufferWithRefCount*)malloc(GET_PLATFORM_ALIGNED_SIZE(sizeof(ClxNetworkBufferWithRefCount)) + bufferSize);
	ClxNetworkBufferWithRefCount* buffer = clxPriorityQueueHeapMalloc(queueHeapHandle, GET_PLATFORM_ALIGNED_SIZE(sizeof(ClxNetworkBufferWithRefCount)) + bufferSize);

	if (buffer == NULL)
	{
		return NULL;
	}

	buffer->base.address = (u1*)buffer + GET_PLATFORM_ALIGNED_SIZE(sizeof(ClxNetworkBufferWithRefCount));
	buffer->base.size = bufferSize;
	buffer->base.flags = flags;

	buffer->refCount = 1;

	return &buffer->base;
}

boolean clxBspNetworkBufferPoolRelease(_in_ ClxNetworkBufferHandle handle,
                                       _in_ ClxBspNetworkBufferPoolCleanup cleanupFunc,
                                       _in_ void* cleanupFuncContext)
{
	ClxNetworkBufferWithRefCount* buffer = (ClxNetworkBufferWithRefCount*)handle;

	BLACKBOX_IF(buffer->refCount == 0);

	if (--buffer->refCount == 0)
	{
        if (cleanupFunc)
        {
            cleanupFunc(cleanupFuncContext, handle);
        }

		//free(buffer);
		clxPriorityQueueHeapFree(queueHeapHandle, buffer);
		return TRUE;
	}

	return FALSE;
}

void clxBspNetworkBufferPoolDuplicate(_in_ ClxNetworkBufferHandle handle)
{
	ClxNetworkBufferWithRefCount* buffer = (ClxNetworkBufferWithRefCount*)handle;

	++buffer->refCount;
}


