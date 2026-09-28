/******************************************************************************
*
* Project             ClarinoxBSP
* File                Imu_Bsp.c
* Description         NXP (mlan) IMU BSP Implementation for RW612
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2022
*
*******************************************************************************/


/*******************************************************************************
								Includes
*******************************************************************************/

#include "fsl_power.h"
#include "Imu_Bsp.h"
#include "fsl_common.h"
#include "fsl_adapter_imu.h"
#include "fsl_imu.h"
#include "fsl_loader.h"

#include "ClxMutex.h"
#include "ClxTime.h"

#include "ClxCommonDefines.h"

/*******************************************************************************
							 Define and Macros
*******************************************************************************/

#if defined(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)
#ifndef MCI_WAKEUP_DONE_PRIORITY
#define MCI_WAKEUP_DONE_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1)
#endif
#else
#ifndef MCI_WAKEUP_DONE_PRIORITY
#define MCI_WAKEUP_DONE_PRIORITY (3U)
#endif
#endif

typedef struct
{
	IMU_Msg_t *msg;
	uint32_t length;
} imu_msg_t;

typedef struct
{
	imu_msg_t       imu_msg;
	clxImuIrqHandler irqHandler;
	clxImuMsgHandler msgHandler;
	void*           irqHandlerUserData;
}imu_bus_handle_t;

/* Remove me: This structure is not present in mlan and can be removed later */
typedef  struct
{
    u2 size;
    u2 pkttype;
    //HostCmd_DS_COMMAND hostcmd;	//data
} __attribute__((packed)) IMUPkt;

/*******************************************************************************
							 Private Variables
*******************************************************************************/

static ClxMutex txrx_mutex;
static imu_bus_handle_t  imuHandle;


/*******************************************************************************
							Public Variables
*******************************************************************************/


/*******************************************************************************
						Private Function Prototypes
*******************************************************************************/
static int imu_init_locks(void);
static int imu_get_mutex(void);
static int imu_put_mutex(void);

static int imu_create_task_lock(void);
void       imu_delete_task_lock(void);

static void imu_init_imulink(void);
static void mlan_init_wakeup_irq(void);

static hal_imumc_status_t rpmsg_irq_handler(IMU_Msg_t *pImuMsg, uint32_t length);
static hal_imumc_status_t rpmsg_msg_handler(IMU_Msg_t *pImuMsg, uint32_t length);
static void set_msg_content(IMU_Msg_t *pImuMsg, uint32_t length);


/*******************************************************************************
							Private Functions
*******************************************************************************/

/* Sets message content to local message structure */
static void set_msg_content(IMU_Msg_t *pImuMsg, uint32_t length)
{
	imuHandle.imu_msg.msg = pImuMsg;
	imuHandle.imu_msg.length = length;
}

/* Initializes the driver struct */
static int imu_init_locks(void)
{
    int status = CLX_SUCCESS;
    if (txrx_mutex == NULL)
    {
    	txrx_mutex = clxCreateMutex_(NULL, 0);
        if (txrx_mutex == NULL)
            return CLX_ERROR;
    }

    status = imu_create_task_lock();
    return status;
}


static int imu_get_mutex(void)
{
	clxAcquireMutex(txrx_mutex);
	return CLX_SUCCESS;
}

static int imu_put_mutex(void)
{
	clxReleaseMutex(txrx_mutex);
	return CLX_SUCCESS;
}

static void imu_init_imulink(void)
{
    /* Assign IMU channel for CPU1-CPU3 communication */
    HAL_ImuInit(kIMU_LinkCpu1Cpu3);
}

static hal_imumc_status_t rpmsg_irq_handler(IMU_Msg_t *pImuMsg, uint32_t length)
{
	hal_imumc_status_t status = kStatus_HAL_ImumcError;

	if (NULL != imuHandle.irqHandler)
	{
		if (CLX_SUCCESS
				!= imuHandle.irqHandler(imuHandle.irqHandlerUserData, 0, TRUE))
		{
			return status;
		}
		status = kStatus_HAL_ImumcSuccess;
	}

	return status;
}

static hal_imumc_status_t rpmsg_msg_handler(IMU_Msg_t *pImuMsg, uint32_t length)
{
	//hal_imumc_status_t status = kStatus_HAL_ImumcError;

	/* save interrupt message content to local message structure*/
	set_msg_content(pImuMsg, length);
	clxDebugLog("IMU: IRQ came: %d \n", pImuMsg->Hdr.type);

	if (CLX_SUCCESS
			!= imuHandle.msgHandler(imuHandle.irqHandlerUserData,
					pImuMsg->Hdr.type))
	{
		/* clear local message structure */
		set_msg_content(NULL, 0);
		return kStatus_HAL_ImumcError;
	}
	return kStatus_HAL_ImumcSuccess;
}

static void mlan_init_wakeup_irq(void)
{
#ifndef __ZEPHYR__
	/* Enable WLAN wakeup done interrupt */
	NVIC_SetPriority(WL_MCI_WAKEUP_DONE0_IRQn, MCI_WAKEUP_DONE_PRIORITY);
	NVIC_EnableIRQ(WL_MCI_WAKEUP_DONE0_IRQn);
#endif
}


/*******************************************************************************
							Public Functions
*******************************************************************************/

ClxResult clxImuInit(clxImuIrqHandler irq_handler, clxImuMsgHandler msg_handler, void* irqHandlerUserData)
{
	int ret                = 0;

	ret = imu_init_locks();

	/* save interrupt handle info */
	imuHandle.irqHandler 			= irq_handler;
	imuHandle.msgHandler			= msg_handler;
	imuHandle.irqHandlerUserData 	= irqHandlerUserData;

	/* clear message structure */
	set_msg_content(NULL, 0);

	return (ClxResult)ret;
}

ClxResult clxImuFwDownload(void)
{
	int ret                = 0;
	int retry_cnt          = 3;

	retry:
	/* Comment out this line if CPU1 image is downloaded through J-Link.
	 * This is for load service case only.
	 */
	power_off_device(LOAD_WIFI_FIRMWARE);
	//wifi_io_d("%u IMU download WLAN FW.\n", os_ticks_get());
	/* Download firmware */
	ret = sb3_fw_download(LOAD_WIFI_FIRMWARE, 1, (uint32_t) 0);
	/* If fw download is failed, retry downloading for 3 times. */
	if (ret) {
		if (retry_cnt != 0) {
			retry_cnt--;
			goto retry;
		} else {
			//wifi_io_e("Download firmware failed");
			return CLX_FAIL;
		}
	}
	//wifi_io_d("%u WLAN FW is active.\n", os_ticks_get());

	imu_init_imulink();

    HAL_ImuInstallCallback(kIMU_LinkCpu1Cpu3, rpmsg_msg_handler, IMU_MSG_COMMAND_RESPONSE);

    HAL_ImuInstallCallback(kIMU_LinkCpu1Cpu3, rpmsg_msg_handler, IMU_MSG_EVENT);

    HAL_ImuInstallCallback(kIMU_LinkCpu1Cpu3, rpmsg_msg_handler, IMU_MSG_RX_DATA);

    HAL_ImuInstallCallback(kIMU_LinkCpu1Cpu3, rpmsg_irq_handler, IMU_MSG_CONTROL);

    mlan_init_wakeup_irq();

    return CLX_SUCCESS;
}

void clxImuMsgReceive(void)
{
	clxDebugLog("IMU: IRQ handled! \n");
	(void)HAL_ImuReceive(kIMU_LinkCpu1Cpu3);
}

u4 clxImuGetCmdLength(void)
{
	u4 cmdLength = 0;
	IMUPkt *cmdPkt;

	cmdPkt = (IMUPkt*) imuHandle.imu_msg.msg->PayloadPtr[0];
	cmdLength = cmdPkt->size;

	return cmdLength;
}

void clxImuGetCmdBuf(u1 *payloadPtr, u4 dataLength)
{
	u4 i;
	u1 *buf;

	buf = (u1*) imuHandle.imu_msg.msg->PayloadPtr[0];
	for (i = 0; i < dataLength; i++)
	{
		payloadPtr[i] = buf[i];
	}
}

u1 clxImuGetDataBufNum(void)
{
	u1 bufNum = 0;

	bufNum = imuHandle.imu_msg.msg->Hdr.length;

	return bufNum;
}

u4 clxImuGetDataBufLength(u1 bufNum)
{
	u4 dataLength = 0;
	IMUPkt *dataPkt;

	dataPkt = (IMUPkt*) imuHandle.imu_msg.msg->PayloadPtr[bufNum];
	dataLength = dataPkt->size;

	return dataLength;
}

void  clxImuGetDataBuf(u1* payloadPtr, u4 dataLength, u1 bufNum)
{
	u4 i;
	u1 *buf;

	buf = (u1*) imuHandle.imu_msg.msg->PayloadPtr[bufNum];
	for (i = 0; i < dataLength; i++)
	{
		payloadPtr[i] = buf[i];
	}
}

ClxResult clxImuSendCmdData(u1 *cmd_payload, u4 length)
{
	ClxResult ret = CLX_SUCCESS;

	imu_get_mutex();

	uint32_t failCnt = 0;

	while(kStatus_HAL_ImumcSuccess != HAL_ImuSendCommand(kIMU_LinkCpu1Cpu3, cmd_payload, length))
	{
		//ret = CLX_ERROR;
		failCnt++;
		clxDebugLog("IMU: BSP: cmd fail try num: %d \n", failCnt);
		clxSleep(1);
	}
		clxDebugLog("IMU: BSP: cmd sent");
	imu_put_mutex();

	return ret;
}

ClxResult clxImuSendTxData(u1 *data, u4 length)
{
	ClxResult ret = CLX_SUCCESS;

	imu_get_mutex();

	if(kStatus_HAL_ImumcSuccess != HAL_ImuSendTxData(kIMU_LinkCpu1Cpu3, data, length))
		ret = CLX_ERROR;

	/* IMU multi data send APIs usage */
//	if(kStatus_HAL_ImumcSuccess != HAL_ImuAddWlanTxPacket(kIMU_LinkCpu1Cpu3, data, length))
//		ret = CLX_ERROR;
//
//	if(kStatus_HAL_ImumcSuccess != HAL_ImuSendMultiTxData(kIMU_LinkCpu1Cpu3))
//		ret = CLX_ERROR;

	imu_put_mutex();

	return ret;
}


static int imu_create_task_lock(void)
{
    int ret = 0;

    ret = HAL_ImuCreateTaskLock();
    if (ret != CLX_SUCCESS)
    {
        //wifi_e("Create imu task lock failed.");
        return CLX_FAIL;
    }

    return CLX_SUCCESS;
}

void imu_delete_task_lock(void)
{
    HAL_ImuDeleteTaskLock();
}

void WL_MCI_WAKEUP_DONE0_DriverIRQHandler(void)
{
    IRQn_Type irq_num = WL_MCI_WAKEUP_DONE0_IRQn;

    /* Mask IMU ICU interrupt */
    DisableIRQ(irq_num);
    /* Clear CPU1 wakeup register */
    PMU_DisableWlanWakeup(1);
    EnableIRQ(irq_num);
}

boolean clxImuIsBuffFull(void)
{
	return (boolean)clxIsTxBuffFull(kIMU_LinkCpu1Cpu3);
}

void clxImuEnableInterrupts(void)
{
	/* clear local message structure */
	set_msg_content(NULL, 0);
}
