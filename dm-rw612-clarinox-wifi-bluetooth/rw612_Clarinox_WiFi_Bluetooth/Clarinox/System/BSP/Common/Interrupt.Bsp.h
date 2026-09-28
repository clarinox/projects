#ifndef INTERRUPT_BSP_h
#define INTERRUPT_BSP_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                Interrupt.Bsp.h
* Description         Declares Interrupt interface for BSP
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
A variable of type ClxInterruptID which represents the Interrupt ID.
*/
	typedef void* ClxInterruptID;
 /**Callback function prototypes used by BSP to handle stack function calls. */   
    typedef struct ClxInterruptBspInterfaceStruct
    {
  /**This callback function called when configuring an interrupt. The function returns an InterruptID.
    \param[ in ] interruptName A string containing the name of the interrupt to be handled.
    \param[ in ] isr  Interrupt handler function pointer, taking void* context as a parameter and returning void
    \param[ in ] isrContext defines the isr context
*/  
        ClxInterruptID (*configure) (const s1* interruptName, 
									 void (*isr) (void* context),
									 void* isrContext);       
    /**
    This function called for enabling interrupt.
    */
		void (*enable)	(ClxInterruptID intID);
    /**
    This function called for disabling interrupt.
    */
		void (*disable)	(ClxInterruptID intID);
    
    } ClxInterruptBspInterface;
    
     /**
    Clarinox stacks internally use the clxInterruptBspInterface. 
    These implementations need to implement all of the functions defined as part of the #ClxInterruptBspInterface structure.
*/
	
    
    extern ClxInterruptBspInterface clxInterruptBspInterface;


    extern void* clxBspDisableSystemInterrupt();
    
    extern void clxBspEnableSystemInterrupt(void* irqStatus);

#ifdef __cplusplus
}
#endif

#endif // INTERRUPT_BSP_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/
