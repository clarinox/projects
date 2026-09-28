#ifndef ClxPackages_h
#define ClxPackages_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxPackages.def
* Description         Clarinox Packages
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

typedef struct ClxPackageStruct
{
    const s1* name;
} ClxPackage;  
  
#define CLX_DEFINE_PACKAGE(name)                \
    extern const ClxPackage _clxPackage_##name;  
    
#define CLX_PACKAGE(name)   &_clxPackage_##name

#define CLX_PACKAGE_(name) CLX_PACKAGE(name)
#define CLX_THIS_PACKAGE    CLX_PACKAGE_(CLX_STATIC_PACKAGE_NAME)


#ifdef __cplusplus
#   define CLX_BEGIN_PACKAGE_LIST                                                                                                       \
        extern "C"                                                                                                                      \
        {                                                                                                                               \
            const ClxPackage* _clxMemoryStatisticsPackageList_[] = {

#define CLX_END_PACKAGE_LIST                                                                                                            \
            };                                                                                                                          \
            ClxSize _clxMemoryStatisticsPackageListSize_ = sizeof(_clxMemoryStatisticsPackageList_)/(sizeof(ClxPackage*));        \
        }


#else
#   define CLX_BEGIN_PACKAGE_LIST  const ClxPackage* _clxMemoryStatisticsPackageList_[] = {

#define CLX_END_PACKAGE_LIST                                                                                                            \
    };                                                                                                                                  \
    ClxSize _clxMemoryStatisticsPackageListSize_ = sizeof(_clxMemoryStatisticsPackageList_)/(sizeof(ClxPackage*));
#endif


#if !defined(CLX_STATIC_PACKAGE_NAME)
#   define CLX_STATIC_PACKAGE_NAME     DEFAULT
#endif

  
  
CLX_DEFINE_PACKAGE(APPLICATION)

CLX_DEFINE_PACKAGE(DEFAULT)
CLX_DEFINE_PACKAGE(SOFTFRAME_GLOBAL)
CLX_DEFINE_PACKAGE(SOFTFRAME_CRYPTO)
CLX_DEFINE_PACKAGE(SOFTFRAME_AT_COMMAND)

CLX_DEFINE_PACKAGE(DEBUG_PKG)
CLX_DEFINE_PACKAGE(TASKING)
CLX_DEFINE_PACKAGE(OS_ADAPTER)
CLX_DEFINE_PACKAGE(CONSOLE_UI)
CLX_DEFINE_PACKAGE(MEMORY_STATISTICS)
CLX_DEFINE_PACKAGE(TERMINAL_EMULATOR)

CLX_DEFINE_PACKAGE(XML_PKG)
CLX_DEFINE_PACKAGE(IPERF_PKG)
CLX_DEFINE_PACKAGE(DHCP_PKG)
CLX_DEFINE_PACKAGE(NETWORK_PING_PKG)
CLX_DEFINE_PACKAGE(HTTP_PKG)
CLX_DEFINE_PACKAGE(MINI_HTTP_SERVER)
CLX_DEFINE_PACKAGE(A2L_RPC)

CLX_DEFINE_PACKAGE(CLARINOXBLUE_GLOBAL)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_TRANSPORT)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_ACL)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_COMMON)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_L2CAP_COMMON)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_L2CAP_CLASSIC)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_NETWORKING)

CLX_DEFINE_PACKAGE(CLARINOXBLUE_HCI)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_SCO_OVER_HCI)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_SCO)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_RFCOMM)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_OBEX)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_OBEX_OVER_L2CAP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BNEP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_AVCTP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_AVDTP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_SDP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_MCAP)

CLX_DEFINE_PACKAGE(CLARINOXBLUE_SDAP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_SPP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_A2DP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_AVRCP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_HIDP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_PAN)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_HDP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_PBAP_CLIENT)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_MAP_CLIENT)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_HFP_HF)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_HFP_AG)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_HSP_HS)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_HSP_AG)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BPP_PRINTER)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BIP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_HRCP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_FTP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_OPP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_CTN_CLIENT)

CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_GLOBAL)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_ACL)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_L2CAP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_ATT_CLIENT)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_ATT_SERVER)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_IPSP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_SMP)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_ATT)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_MESH)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_ISOCHRONOUS)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_CENTRAL)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_PERIPHERAL)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_DIRECTIONFINDING)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_CHANNELSOUNDING)
CLX_DEFINE_PACKAGE(CLARINOXBLUE_BLE_BONDING)


CLX_DEFINE_PACKAGE(CLARINOXWIFI_STACK)
CLX_DEFINE_PACKAGE(CLARINOXWIFI_CHIP_DRIVER)
CLX_DEFINE_PACKAGE(WPA_SUPPLICANT_PKG)

#ifdef __cplusplus
}
#endif

#endif // ClxPackages_h

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
/* Message       : The # and ## operators should not be used.                 */
/* Rule          : MISRA-C:2004 Rule 19.13                                    */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */
/*                 platforms. Used to provide better flexibility.	          */
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
