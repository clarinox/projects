/*******************************************************************************
*
* Project
* File                HardwareWlan.c
* Description         WLAN module specific GPIO functions.
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
#include "fsl_gpio.h"
#include "fsl_common.h"
//#include "fsl_iomuxc.h"
#include "fsl_io_mux.h"
#include "pin_mux.h"
#include "FreeRTOSConfig.h"

#define WL_IRQ_PRIORITY		5U
#define  CLX_WLAN_ISR_Handler	GPIO4_Combined_0_15_IRQHandler
/*!
void enableHostSideModuleInterrupts(void);
void disableHostSideModuleInterrupts(void);
void clxWlanEnPinConfig(void);
extern void sdioCardInterruptHandler();
Whether the SW is turned on */
volatile bool g_InputSignal = false;

extern void        enableSdioIrq  			 (void);
extern void 	   disableSdioIrq			 (void);

/* Interrupt Vector for WLAN IRQ pin interrupt */
extern void clxSdioIrqHandler(void);
void CLX_WLAN_ISR_Handler(void)
{

	    /* Change state of switch. */
//	    g_InputSignal = true;
//	    SDK_ISR_EXIT_BARRIER;
//		if(EXTI_GetITStatus(WLAN_EXTERNAL_INTERRUPT_LINE) != RESET)

// Is this needed at Actronika?
#if 0
		if (GPIO_PortGetInterruptFlags(WL_INT_PORT) & (1U << WL_INT_PIN))
		{
			disableHostSideModuleInterrupts();

//			EXTI_ClearITPendingBit(WLAN_EXTERNAL_INTERRUPT_LINE);

			clxSdioIrqHandler();

    	}

	/* clear the interrupt status */
	GPIO_PortClearInterruptFlags(WL_INT_PORT, ~0);
#endif
}
/**
Configures WLAN_EN GPIO pin to be in output push-pull mode
*/

void clxWlanLowLevelInit(void)
{
	// Is this needed at Actronika? Pin configurations are arranged by Actronika at board initialization AFAIK
#if 0
	/*Configure WL_EN pin */
	/* GPIO configuration of WL_EN on GPIO_SD_B2_04 (pin F14) */
		gpio_pin_config_t WL_EN_config = {
			.direction = kGPIO_DigitalOutput,
			.outputLogic = 0U,
			.interruptMode = kGPIO_NoIntmode
		};
		/* Initialize GPIO functionality on GPIO_SD_B2_04 (pin F14) */
		GPIO_PinInit(WL_EN_PORT, WL_EN_PIN, &WL_EN_config);
		/* GPIO configuration of WL_IRQ on GPIO_SD_B2_03 (pin E15) */
		gpio_pin_config_t WL_IRQ_config = {
			.direction = kGPIO_DigitalInput,
			.outputLogic = 0U,
			.interruptMode = kGPIO_IntRisingEdge
		};
		/* Initialize GPIO functionality on GPIO_SD_B2_03 (pin E15) */

		GPIO_PinInit(WL_INT_PORT, WL_INT_PIN , &WL_IRQ_config);
		GPIO_PortEnableInterrupts(WL_INT_PORT, 1U << WL_INT_PIN);
		/* set IRQ priority */
		NVIC_SetPriority(WL_IRQ, WL_IRQ_PRIORITY);

		GPIO_PortClearInterruptFlags(WL_INT_PORT, ~0);
		EnableIRQ(WL_IRQ);
#endif
}

/**
Sets the WLAN_EN GPIO pin high.
*/
bool clxWlanPowerOnChip(void)
{
// It is informed that reset pin of wireless module is not connected at Actronika Hardware.
#if 0
	GPIO_PinWrite(WL_EN_PORT,WL_EN_PIN,1U);
//	SDK_DelayAtLeastUs(10000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
#endif
    return true ;
}

/**
Sets the WLAN_EN GPIO pin low.
*/
bool clxWlanPowerOffChip(void)
{
// It is informed that reset pin of wireless module is not connected at Actronika Hardware.
#if 0
	GPIO_PinWrite(WL_EN_PORT,WL_EN_PIN,0U);
//	SDK_DelayAtLeastUs(10000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
#endif
    return true ;
}

/**
Enables the WiFi chip by toggling the WLAN_EN pin. 
This function calls clxWlanPowerOnChip() and clxWlanPowerOffChip() to toggle the WLAN_EN pin.
*/
boolean clxEnableWlanHardware(void)
{
    boolean ret = true;        
    /* Enable WLAN hardware by toggling WLAN_EN pin*/    
    ret = clxWlanPowerOffChip();
    clxSleep(200);
    ret = clxWlanPowerOnChip();
    clxSleep(200);
  
    return ret;
}

/**
Disables the WiFi chip by resetting the WLAN_EN pin. 
This function calls clxWlanPowerOffChip() to reset the WLAN_EN pin.
*/
void clxDisableWlanHardware(void)
{
    /*Power off WLAN hardware*/
    clxWlanPowerOffChip();
}

/*
 *
 * Enable Wireless module interrupts
 * Can be WLAN interrupt, BT interrupt or both, comming via SDIO or via Pin
 */
void enableHostSideModuleInterrupts(void)
{
	//enableSdioIrq();
}

/*
 *
 * Disable Wireless module interrupts
 * Can be WLAN interrupt, BT interrupt or both, coming via SDIO or via Pin
 */
void disableHostSideModuleInterrupts(void)
{
	//disableSdioIrq();
}


