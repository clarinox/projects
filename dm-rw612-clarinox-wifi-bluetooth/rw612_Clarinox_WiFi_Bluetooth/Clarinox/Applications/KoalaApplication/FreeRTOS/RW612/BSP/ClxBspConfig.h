/*******************************************************************************
*
* Project             BSP configuration file
* File                ClxBspConfig.h
* Description         Bsp related functions and variables are defined here.
*
* This file contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#ifndef __ClxBspConfig_H__
#define __ClxBspConfig_H__


#ifdef __cplusplus
extern "C" {
#endif

#if defined (CLARINOX_WLAN_MESH_SUPPORTED)

#if defined(USER_DEFINED_STATION_MAC_ADDRESS)
#   define CLX_WLAN_STATION_MAC_ADDRESS      {0x00, 0x12, 0x32, 0x56, 0x78, 0xB5}
#endif

#if defined(CLX_WIFI_MESH_AUTO)
#define WLAN_MESHAUTO_SCHED_THREAD_SIZE         512*2
#endif

#endif /* defined(CLARINOX_WLAN_MESH_SUPPORTED) */

#define WLAN_STACK_DESCRIPTOR_SIZE              (64*1024)

#if defined(CLX_WPA_SUPPLICANT)
#define WPA_SUPPLICANT_CONFIG_FILE      "wpa_supplicant.conf"
#endif /* defined(CLX_WPA_SUPPLICANT) */

#define MAX_UI_INPUT_SIZE                       64
#define NO_OF_SCAN_REPETITION                   5
#define MAX_NO_OF_AP_IN_VICINITY                20

/*Network configuration macros*/
#if defined (CLX_NETWORK_INTERFACE_LWIP)
#   define LWIP_THREAD_STACK_SIZE                                              (4*768)
//#   define USE_IPERF
//#   define CLX_WLAN_PREFER_SPEED_OVER_LATENCY
//#   define CLX_NET_IF_STATS
//#	define USE_DHCP_CLIENT
//#	define USE_DHCP_SERVER
//#	define USE_IPERF_SERVER
//#   ifndef USE_DHCP_CLIENT
//    // from netif.h
//#endif

//#	define CLX_SOCKETS_SUPPORT
#	define USE_DHCP_CLIENT
#	define USE_DHCP_SERVER
#define CLX_ASYNC_SOCKET_RX_DATAGRAM_QUEUE_SIZE_IN_BITS         4
#endif	//defined (CLX_NETWORK_INTERFACE_LWIP)


#if defined (CLX_MLAN_LABTOOL_SUPPORTED) || defined (CLX_BT_LABTOOL_SUPPORTED)
#define MLAN_HEAP_SIZE						  (4096*5) /* Bytes */
#else
#define MLAN_HEAP_SIZE						  (8192*30)		/* Bytes */
#endif


/* select either UART or JLINK for debugging */
#   define CLX_USE_CONTINUOUS_MEM_SEGMENT
#ifdef CLX_USE_UART_FOR_CLARIFI_CONNECTION
#	define CLX_UART_DEBUG
#else
#   define CLX_JLINK_RTT_DEBUG_INTERFACE
#endif


    #	define CLX_BSP_THREAD_INTERFACE
    #	define CLX_BSP_MUTEX_INTERFACE
    #	define CLX_BSP_SEMAPHORE_INTERFACE
    #	define CLX_BSP_TIME_INTERFACE


/**
Clarinox Thread configuration

Main thread						-	Thread which starts the Clarinox application
Timer thread					-	This thread is present only in the debug version of libraries
Debug thread					-	Sends debug messages to the Clarinox debugger (Not present in release version)
ConsoleUI thread				-	Sends/Receives text messages from the console
Terminal Emulator thread		-	Replaces debug thread in the release version of libraries
WLAN stack thread				-	WLAN stack thread
Call-back(Application) thread	-	WLAN call-back thread
*/
/*Clarinox thread priority levels*/
#	define DEFAULT_WLAN_DRIVER_HIGH_TASK_PRIORITY                          9
#	define DEFAULT_WLAN_DRIVER_MEDIUM_HIGH_TASK_PRIORITY                   7
#	define DEFAULT_WLAN_DRIVER_MEDIUM_TASK_PRIORITY                        5
#	define DEFAULT_WLAN_DRIVER_MEDIUM_LOW_TASK_PRIORITY                    3
#	define DEFAULT_WLAN_DRIVER_LOW_TASK_PRIORITY                           1

#	define DEFAULT_BLUETOOTH_DRIVER_HIGH_TASK_PRIORITY                     9
#	define DEFAULT_BLUETOOTH_DRIVER_MEDIUM_HIGH_TASK_PRIORITY              7
#	define DEFAULT_BLUETOOTH_DRIVER_MEDIUM_TASK_PRIORITY                   5
#	define DEFAULT_BLUETOOTH_DRIVER_MEDIUM_LOW_TASK_PRIORITY               3
#	define DEFAULT_BLUETOOTH_DRIVER_LOW_TASK_PRIORITY                      1

/*Clarinox Thread stack sizes*/
#  define MAIN_THREAD_STACK_SIZE                                                6*512u
#  define CLARINOX_SOFTFRAME_TIMER_THREAD_STACK_SIZE                            4*256u
#  define CLARINOX_SOFTFRAME_DEBUG_THREAD_STACK_SIZE                            4*256u
#  define CLARINOX_SOFTFRAME_UI_THREAD_STACK_SIZE                               4*256u
#  define CLARINOX_SOFTFRAME_TERMINAL_EMULATOR_THREAD_STACK_SIZE                4*256u
#  define CLARINOX_WLAN_STACK_THREAD_STACK_SIZE	                                4*2048u
#  define CLARINOX_WLAN_APPLICATION_THREAD_STACK_SIZE          				    4*2048u
#  define CLARINOX_BLUETOOTH_APPLICATION_THREAD_STACK_SIZE                      4*800u
#  define CLARINOX_BLUETOOTH_STACK_THREAD_STACK_SIZE                            4*1536u
#  define CLARINOX_BLUETOOTH_UARTRX_THREAD_STACK_SIZE                           4*400u

/*Wireless chip firmware selection*/
#if defined (CLX_88W8887) || defined (CLX_88W8897) || defined (CLX_88W8797) || defined (CLX_88W8977) || defined (CLX_88W8997)	|| defined (CLX_88W8987) || defined (CLX_IW416)
#	define CLX_NXP_WIRELESS_SOC
#else
#	error "PLEASE DEFINE THE CHIP SPECIFIC FIRMWARE MACRO"	
#endif

#ifdef __cplusplus
}
#endif


#endif /* __ClxBspConfig_H__ */

