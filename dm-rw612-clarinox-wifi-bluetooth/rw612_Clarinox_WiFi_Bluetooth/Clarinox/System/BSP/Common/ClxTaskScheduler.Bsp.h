#ifndef ClxTaskScheduler_Bsp_h
#define ClxTaskScheduler_Bsp_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxTaskScheduler.Bsp.h
* Description         Tasking Scheduler BSP for external Sync
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
  

struct ClxSchedulerExtSync
{
	void* rtti;
};


struct ClxSchedulerExtSync* clxSchedulerExtSync_Init(const s1* schedulerName, ClxScheduler scheduler);
void clxSchedulerExtSync_Destroy(struct ClxSchedulerExtSync* sync);

void clxSchedulerExtSync_Lock(struct ClxSchedulerExtSync* sync);
void clxSchedulerExtSync_Unlock(struct ClxSchedulerExtSync* sync);

boolean clxSchedulerExtSync_Sleep(struct ClxSchedulerExtSync* sync, u4 timeout);

void clxSchedulerExtSync_Wakeup(struct ClxSchedulerExtSync* sync);

void clxSchedulerExtSync_IrqWakeup(struct ClxSchedulerExtSync* sync, boolean isrContext);



#ifdef __cplusplus
}
#endif 


#endif // ClxTaskScheduler_Bsp_h
