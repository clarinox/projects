/*******************************************************************************
*
* Project             ClarinoxSoftFrame
* File                ClxBspFileList.c
* Description         BSP Support for File contents
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

// _____________________________________________________________________________
//

#undef  CLX_MODULE_ID
#define CLX_MODULE_ID  1028
// _____________________________________________________________________________
//
#include "ClxBsp.h"
#include "ClxUserFile.h"
#include "ClxStandard.h"
#include "ClxBspConfig.h"


#if defined (CLX_WPA_SUPPLICANT)
#include "wpa_supplicant.conf.h"
#include "Certificates/ca.pem.h"
#include "Certificates/client.key.h"
#include "Certificates/client.pem.h"
#endif

void initROMFileSystemMap       (void);

 /*
These below tables are used as the fixed values if RAM_FILE_SUPPORTED, and CANNOT be changed
If FLASH_FILE_SUPPORTED, then these values are used as the default values,
and they will be changed through out the execution
*/

/**
* DEBUG_FLAG sets the masking flag (32 bits) for debugging
* Choose the debugging features you need from the following list. A 1 means the feature is on, and a 0 means the feature is off.
* DEBUG_FLAG is written in binary format. If the number of bits is less than 32, available bits
* are assumed to be the right-most bits. The not-mentioned bits are assumed to be 0.
* The right-most bit is bit number 0, and the left-most bit is the bit number 31 (regardless of the endianness of the machine).
*
* The following list specifies the system-defined features:
* Bit 0   : Stack Tracing (function calls)
* Bit 1   : Warning messages
* Bit 2   : Logging messages
* Bit 3   : Fatal error messages
* Bit 4   : Memory analysis messages
* Bit 5   : Bluetooth Protocol Monitor messages
* Bit 6   : IEEE802.11 Frame View
* Bit 7   : Not Used
* Bit 8   : Not Used
* Bit 9   : Not Used
* Bit 10  : Co-operative Tasking Monitoring
* Bit 11  : Wi-Fi Host Controller Interface messages
* Bit 12  : Logger messages
* Bit 13  : RPC Protocol Monitor messages
* Bit 14  : IOT Monitor
*
* Other bits are user-defined
*/

static const s1 debugConfig[] =
#ifdef CLX_DEBUG
"DEBUG_MEDIUM = UART\n"
#else
"DEBUG_MEDIUM = NONE\n"
#endif
"DEBUG_PORT_NAME = DEBUG_PORT\n"
"DEBUG_BAUD_RATE = 460800\n"
"DEBUG_DATA_BITS = 8\n"
"DEBUG_STOP_BITS = 0\n"
"TE_MEDIUM = UART\n"
"TE_PORT_NAME = DEBUG_PORT\n"
"TE_BAUD_RATE = 921600\n"
"TE_DATA_BITS = 8\n"
"TE_STOP_BITS = 0\n"
"DEBUG_TIMEOUT = 2000\n"
"DEBUG_BUFFER_SIZE = 3588\n"

/* Mesh Auto Credentials */
"WLAN_MESH_ID = clx\n"
"WLAN_MESH_SSID = clxmesh\n"
"WLAN_MESH_PASSWORD = clarinox\n"
//"WLAN_MESH_CHANNEL=36\n"
//"WLAN_MESH_BAND=2\n"

#ifdef CLX_DEBUG
//"DEBUG_FLAG =   00000000001000\n\n"; // Fatal Error ON
//"DEBUG_FLAG =   00100001000000\n\n"; // WiFi logging on
//"DEBUG_FLAG =   00000000100000\n\n"; // BT logging on
//"DEBUG_FLAG =   00100001111111\n\n"; // BT/WiFi & logging on
//"DEBUG_FLAG =   00100001111100\n\n"; // BT/WiFi & logging on (except stack trace/warning)
//"DEBUG_FLAG =   00000000001110\n\n"; // logging on (except stack trace)
//"DEBUG_FLAG =   00110001111111\n\n"; // BT/WiFi & cooperative tasking & logging on
//"DEBUG_FLAG =   00100001011111\n\n"; // WiFi + other logging on
//"DEBUG_FLAG =   00100001011110\n\n"; // WiFi + other logging on (except stack trace/warning)
//"DEBUG_FLAG =   00000000111110\n\n"; // BT + other logging on (except stack trace/warning)

//"DEBUG_FLAG =   00100001101110\n\n"; // WiFi + other logging on (except stack trace/warning and memory)
"DEBUG_FLAG =   00000000000000\n\n"; // all flags off
#else
"DEBUG_FLAG =   00000000000000\n\n"; // all flags off
#endif

static const s1 licence[] = "";

/*
    Size of the data region used for storing pairing information
    Each device paired will take up about 200 bytes of data
*/
#define BLUETOOTH_PAIRING_DATA_REGION_SIZE           4*1024
#define BLE_PAIRING_DATA_REGION_SIZE                 2*1024


/*      Example Bluetooth Classic Pairing information file for a Samsung Galaxy S4
 *
 *      First four bytes are used for file header information
 *      (file length saved in little endian format) e.g. 163 -> 0xa3, 0x00, 0x00, 0x00
 *
 *      The rest of the file contains the Pairing information
 *      Each entry/line of the file ends with a 0x0a
 *      Last byte of the file is 0x0a.
 */
static s1 bluetoothConfig[BLUETOOTH_PAIRING_DATA_REGION_SIZE] ="";

static s1 bleConfig[BLE_PAIRING_DATA_REGION_SIZE] = "";

VirtualFile fileList[] =
{
    /* SoftFrame Configuration file */
    { StorageType_RAM,   "SoftFrame.cfg",             {sizeof(debugConfig),      (s1*)debugConfig            }},

    /* Licence file for operation without time limit */
    { StorageType_RAM,   "licence.txt",   	          {sizeof(licence),          (s1*)licence                }},

#if defined (CLX_WPA_SUPPLICANT)
	{ StorageType_RAM,  "wpa_supplicant.conf",  	  {sizeof(wpa_supplicant_conf), wpa_supplicant_conf     }},
	/* Certificate file issued by Certificate Authority for WLAN Enterprise connection */
	{ StorageType_RAM, "ca.pem",  		 			  {sizeof(ca_pem),           ca_pem                  }},
	/* Client Private Key file WLAN Enterprise connection */
	{ StorageType_RAM, "client.key",  		 		  {sizeof(client_prv_key),   client_prv_key          }},
	/* Client Certificate file used for WLAN Enterprise connection */
	{ StorageType_RAM, "client.pem",  		 		  {sizeof(client_pem),       client_pem              }},
#endif

    /* ClarinoxBlue Configuration file, keeps BT pairing information */
    { StorageType_RAM,   "ClarinoxBlue.cfg",          {sizeof(bluetoothConfig),  bluetoothConfig             }},

    /* ClarinoxBlueLowEnergy Configuration file, keeps BLE pairing information */
    { StorageType_RAM,   "ClarinoxBlueLowEnergy.cfg", {sizeof(bleConfig),        bleConfig                   }},

    /* final file - identifies the end of virtual file list - DO NOT REMOVE */
    { StorageType_RAM,   NULL,                        {0,                        NULL                        }}
};

extern const VirtualFile* clxVirtualFileSystemMap;

void initROMFileSystemMap(void)
{
    clxVirtualFileSystemMap = fileList;
}
