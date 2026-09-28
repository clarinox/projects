#ifndef Clarinox_Test_h_
#define Clarinox_Test_h_

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                A2L.TestPort.h
* Description         Declares Clarinox Test Framework definitions
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#define CLARIFI_NUMBER_OF_CONTROL_CHANNELS              8  
#define CLARIFI_TEST_CONTROL_CHANNEL                    0  

#define ClxTestCallback ClxCCHCallback


#ifdef __cplusplus
extern "C" {
#endif

struct ClxControlChannelBase;
typedef struct ClxControlChannelBase* ClxControlChannel;


#if !defined(CLX_CABI)
/* Represents the 32bit ID of an Control Channel call-back function (also called an event handler). */
typedef s4 ClxCCHCallback;
#endif


typedef ClxResult (*ClxTestControlChannelExecuteFunction) (_in_ const s1* name, 
    _in_ const void* in, 
    _out_ void** out, 
    _in_ ClxControlChannel channel);


typedef u4 (*ClxTestControlChannelActionHandler) (_in_ void* context,
    _in_ u1 type, 
    _in_ const u1* request, 
    _in_ u4 requestLen, 
    _out_ u1* responseBuf, 
    _in_ u4 responseBufLen);


ClxResult clxTestRunControlChannelServer(_in_ u1 channelNo, 
                                         _in_ ClxTestControlChannelExecuteFunction functionList,                                                 
                                         _in_ u4 callStackSize);


ClxResult clxTestRunControlChannelServerEx(_in_ u1 channelNo, 
                                           _in_ ClxTestControlChannelExecuteFunction functionList,                                                 
                                           _in_ u4 callStackSize,
                                           _in_ ClxTestControlChannelActionHandler actionHandler,
                                           _in_ void* actionHandlerContext);

ClxResult clxTestInvokeCallbackFunction(_in_ ClxControlChannel channel,
                                        _in_ ClxCCHCallback callbackFuncID,
                                        _in_ const void* input,
                                        _out_ void* output);


#if defined(CLX_CABI)	
#	define CLX_CTYPE __attribute__(ClxCType)
#else
#	define CLX_CTYPE	
#endif
	
	
#define CLX_CCH_FUNCTION_LIST_BEGIN(list_name)                                                                                                           \
    ClxResult list_name(const s1* name, const void* in, void** out, ClxControlChannel channel)                                                           \
    {


#define CLX_CCH_FUNCTION(func_name)                                                                                                                     \
        if (strcmp(#func_name, name) == 0)                                                                                                              \
        {                                                                                                                                               \
            *out = (void*)((u1*)in + GET_PLATFORM_ALIGNED_SIZE(sizeof(Clx_CCH_Input_##func_name)));                                                     \
            memset(*out, 0, sizeof(Clx_CCH_Output_##func_name));                                                                                        \
            return func_name((Clx_CCH_Input_##func_name*)in, (Clx_CCH_Output_##func_name*)(*out), channel);                                             \
        }


#define CLX_CCH_FUNCTION_LIST_END                                                                                                                       \
        *out = NULL;                                                                                                                                    \
        return CLX_ERROR_FUNCTION_NOT_EXIST_ON_CONTROL_CHANNEL;                                                                                         \
    }


#define CLX_DECLARE_CCH_FUNCTION__(func_name, Input_list, Output_list)                                                		                            \
    typedef struct Clx_CCH_Input_##func_name                                                                                                            \
    {                                                                                                                                                   \
        Input_list;                                                                                                                                     \
    } Clx_CCH_Input_##func_name;                                                                                                                        \
                                                                                                                                                        \
    typedef struct Clx_CCH_Output_##func_name                                                                                                           \
    {                                                                                                                                                   \
        Output_list;                                                                                                                                    \
    } Clx_CCH_Output_##func_name;                                                                                                                       \
                                                                                                                                                        \
    ClxResult func_name (Clx_CCH_Input_##func_name* in, Clx_CCH_Output_##func_name* out, ClxControlChannel channel)

        
#if defined(CLX_CABI)		
#define CLX_DECLARE_CCH_FUNCTION(func_name, Input_list, Output_list) CLX_DECLARE_CCH_FUNCTION__(func_name, Input_list, Output_list) __attribute__(ClxCType)
#else
#define CLX_DECLARE_CCH_FUNCTION(func_name, Input_list, Output_list) CLX_DECLARE_CCH_FUNCTION__(func_name, Input_list, Output_list)	
#endif
				
#define CLX_IMP_CCH_FUNCTION(func_name)   ClxResult func_name (Clx_CCH_Input_##func_name* in, Clx_CCH_Output_##func_name* out, ClxControlChannel channel)
                
#define CLX_NA                                                                  void* _na_     
                                 
#define CLX_DECLARE_TEST_FUNCTION(func_name, Input_list, Output_list)           CLX_DECLARE_CCH_FUNCTION(func_name, Input_list, Output_list) 
        
#define CLX_IMP_TEST_FUNCTION(func_name)                                        CLX_IMP_CCH_FUNCTION(func_name)        

#define CLX_TEST_FUNCTION_LIST_BEGIN(list_name)                                 CLX_CCH_FUNCTION_LIST_BEGIN(list_name)       
#define CLX_TEST_FUNCTION(func_name)                                            CLX_CCH_FUNCTION(func_name)
#define CLX_TEST_FUNCTION_LIST_END                                              CLX_CCH_FUNCTION_LIST_END  
      


typedef struct ClxTestSynchronousIndicationStruct
{
    ClxHandle   serviceHandle;

    u4          messageID;
    const void* params;
    ClxError    errorCode;

    void*       prv;   /* NOT TO BE ACCESSED OR MODIFIED BY THE USER */
} ClxTestSynchronousIndication;


extern ClxTestSynchronousIndication clxTestWaitForSynchronousIndication(ClxScheduler indicationScheduler, ClxHandle serviceHandle, const ClxTimeout* timeout);

extern void clxTestDeleteSynchronousIndication(ClxTestSynchronousIndication* obj);

extern boolean clxTestRunServiceDefaultIndicationHandler(ClxHandle serviceHandle, const ClxTestSynchronousIndication* obj);


typedef struct clxTestGetPendingServiceIndication_InputStruct
{
    ClxHandle   serviceHandle;

    u4          messageID;
    const void* params;
    ClxError    errorCode;

    void*       prv;   /* NOT TO BE ACCESSED OR MODIFIED BY THE USER */
} clxTestGetPendingServiceIndication_Input;


extern ClxResult clxTestGetPendingServiceIndication(void);


#ifdef __cplusplus
    class ClxTestSynchronousIndicationScope
    {
    private:
        ClxTestSynchronousIndication indication_;
    public:
        ClxTestSynchronousIndicationScope(const ClxTestSynchronousIndication& indication)
        :
        indication_(indication)
        {}
        
        ~ClxTestSynchronousIndicationScope()
        {
            clxTestDeleteSynchronousIndication(&indication_);
        }

        ClxTestSynchronousIndication* operator->()
        {
            return &indication_;
        }

        const ClxTestSynchronousIndication* operator->() const
        {
            return &indication_;
        }
    };
#endif



extern ClxTestSynchronousIndication clxTestWaitForGapSynchronousIndication(ClxScheduler indicationScheduler, ClxStack stack, const ClxTimeout* timeout);

extern ClxTestSynchronousIndication clxTestWaitForGapBleSynchronousIndication(ClxScheduler indicationScheduler, ClxStack stack, const ClxTimeout* timeout);

#ifdef __cplusplus
}
#endif



#endif // Clarinox_Test_h_

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : C macros shall only expand to a braced initialiser,        */
/*                 a constant, a string literal, a parenthesised expression,  */ 
/*				   a type qualifier, a storage class specifier,               */
/*				   or a do-whilezero construct.                               */ 
/* Rule          : MISRA-C:2004 Rule 19.4                                     */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */ 
/*                 platforms. Used to provide better flexibility for templated*/ 
/*				   code to eliminate programmer errors.                       */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : A function should be used in preference to a function-like */
/*                 macro.                                                     */
/* Rule          : MISRA-C:2004 Rule 19.7                                     */ 
/* Justification : No risk identified. Used to provide better performance in  */
/*                 embedded system environments that do not support efficient */
/*				   functions inlining.                                        */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : In the definition of a function-like macro each instance of*/
/*                 a parameter shall be enclosed in parentheses unless it is  */ 
/*				   used as the operand of # or ## .                           */
/* Rule          : MISRA-C:2004 Rule 19.10                                    */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */
/*                 platforms. Parameter used both as type for data declaration*/
/* 				   and as the operand of ## (Misra compliant).                */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : The # and ## operators should not be used.                 */
/* Rule          : MISRA-C:2004 Rule 19.13                                    */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */
/*                 platforms. Used to provide better flexibility.	          */
/******************************************************************************/


/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused type declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.3                                      */ 
/* Justification : Unused type declarations are to be used in user 		      */
/* 				   applications.      										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : The # and ## preprocessor operators should not be used.    */
/* Rule          : MISRA-C:2012 Rule 20.10                                    */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */
/*                 platforms. Used to provide better flexibility.	          */
/******************************************************************************/
