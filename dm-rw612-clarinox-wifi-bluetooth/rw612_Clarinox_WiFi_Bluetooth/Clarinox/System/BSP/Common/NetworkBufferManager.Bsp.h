#ifndef NetworkBufferManager_Bsp_h
#define NetworkBufferManager_Bsp_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                NetworkBufferManager.Bsp.h
* Description         Defines Network Buffer Manager Interface
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#define CLX_NETWORK_BUFFER_FLAG_TX		            CLX_SET_BIT(1)
#define CLX_NETWORK_BUFFER_FLAG_RX		            CLX_SET_BIT(2)
#define CLX_NETWORK_BUFFER_FLAG_ALLOCATE_RESERVED   CLX_SET_BIT(3)      /* Allocate from reserved area. Generally, an allocation from reserved are shouldn't fail. 
                                                                           if it does, the buffer pool owner should notify all the interested modules when some buffer space becomes available (e.g. when some space is freed) */
#define CLX_NETWORK_BUFFER_FLAG_TX_COMPLETE_EVENT	CLX_SET_BIT(4)      /* When the TX frame transmission is complete (with success or in error), the buffer pool owner should indicate it to the sending module */


#ifdef __cplusplus
extern "C" {
#endif


struct ClxNetworkBuffer
{
	u1* address;
	u2  size;
	u2  flags;
};

typedef const struct ClxNetworkBuffer* ClxNetworkBufferHandle;

struct ClxNetworkBufferPool;

typedef void (*ClxBspNetworkBufferPoolCleanup) (void* ctx, ClxNetworkBufferHandle handle);


extern struct ClxNetworkBufferPool* clxBspNetworkBufferPoolOpen(const s1* poolName);

extern void clxBspNetworkBufferPoolClose(_in_ struct ClxNetworkBufferPool* pool);

extern ClxNetworkBufferHandle clxBspNetworkBufferPoolAlloc(_in_ struct ClxNetworkBufferPool* pool, 
														   _in_ u2 bufferSize, 
														   _in_ u2 flags);

extern boolean clxBspNetworkBufferPoolRelease (_in_ ClxNetworkBufferHandle handle, 
                                               _in_ ClxBspNetworkBufferPoolCleanup cleanupFunc,
                                               _in_ void* cleanupFuncContext);

extern void clxBspNetworkBufferPoolDuplicate (_in_ ClxNetworkBufferHandle handle);


#ifdef __cplusplus
}
#endif

#endif  // NetworkBufferManager_Bsp_h
