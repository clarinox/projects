/*********************************************************************************
*
* Project             Wlan Sample Application
* File                mainWiFi.cpp
* Description         Wlan Sample application main file
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
********************************************************************************/

#include <stdio.h>
#include "ClxBsp.h"
#include "ClxBspConfig.h"
#include "ClxSocketWrapper.h"
#include "ConsoleUIEngine.h"
#include "ClarinoxWlan.h"
#include "ClarinoxWlanConst.h"
#include "Wlan.Api.h"
#include "Wlan.Config.h"
#include "string.h"
#include "WiFiApp.h"
#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
#include "Wlan.ClxMesh.Api.h"
#endif
#ifdef CLX_WIFI_MESH_AUTO
#include "WlanMeshAuto.h"
#endif

#ifdef CLX_WPA_SUPPLICANT
#   include "Wlan.WpaSupplicant.Api.h"
#endif


//#if !defined(CLX_WIFI_OVER_LAN) && !defined(WLAN_FW_FILE_NAME)
//#    error "Define WLAN_FW_FILE_NAME in ClxBspConfig.h"
//#endif
//
//#if !defined(CLX_WIFI_OVER_LAN)
//const s1* firmwareFileName = WLAN_FW_FILE_NAME;
//#endif

#if defined (CLX_MLAN_LABTOOL_SUPPORTED) || defined (CLX_BT_LABTOOL_SUPPORTED)
	const s1* firmwareFileName   = "sdio8987_sdio_combo.bin";
#else
	const s1* firmwareFileName   = "MarvellWlanFirmware.bin";
#endif

#if defined(CLX_WILINK)
const s1* wl1xxSdioCaptureMask = "WL18XX_SdioCaptureMask";
static u1 wifiPowerLevel = MIN(DEFAULT_STA_MAX_TX_POWER, DEFAULT_AP_MAX_TX_POWER);
#endif

#if defined(CLX_BANDWIDTH_LIMIT_SUPPORTED)
#define MAX_BW_LIMIT_EXCEPT_PORTS_NUM	10	/* DON'T CHANGE THIS! IT MUST BE SYNCHRONOUS WITH THE STACK. */
#endif

s1 clxUiInputBuffer[MAX_UI_INPUT_SIZE + 1];

volatile boolean rootInitFlag = FALSE;
volatile boolean nonrootInitFlag = FALSE;

#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
extern boolean clxWlanMeshIndicationHandler(ClxStack wlanStack, ClxHandle wlanHandle, u4 indicationID, const void* params, ClxError errorCode);
#endif

/*******************************************************************************************************************************
*                                                       Main
*
* Initialize BSP and UI interface, and provide the main UI menu.
*
*******************************************************************************************************************************/

static boolean wlanIndicationHandler(ClxStack stack, ClxHandle handle, u4 messageID, const void* params, ClxError errorCode);

static ClxStack wlanStack = NULL;                                        /* A stack object must be created before any other        */

void clxProcessSoftFrameConfigParamsForWlan(ClxGetSoftFrameIntegerParam getIntParam, ClxGetSoftFrameStringParam getStrParam)
{
#ifdef CLX_WIFI_MESH_AUTO
    meshAutoProcessSoftFrameConfigParams(getIntParam, getStrParam);
#endif
}

void clxWlanInitRates(ClxWlanConfigRate rates[MAX_NUMBER_OF_RATES], ClxConfigArray* ratesArray, ClxConfigList* parentList)
{
    u4 numberOfRates = 0;

    /*
    List of data rates which are available and can be used for both sending and receiving of frames.
    The list also determines what standards (e.g. IEEE802.11b, IEEE802.11g, IEEE802.11n) are enabled for the local station.
    NOTE : When a particular standard is to be used, ALL MANDATORY rates for that standard SHALL be included in the list.
    NOTE : In AP role, the 'Basic Rate' flag (second last argument of the function clxConfigInitRateParam) defines the rates which must be
    supported by all stations in the BSS as they are used by the AP to send broadcast and multicast frames.
    NOTE : ClxWlanConfigRate objects are not directly owned by the parent list. They are owned by an array object of type ClxConfigArray.
    Therefore, we pass NULL as the last argument of clxConfigInitRateParam.
    NOTE : If a rate in the list is not supported by the WLAN hardware, it will be silently ignored.

    Non-HT (IEEE802.11abg) rates.
    */
    clxConfigInitRateParam(&rates[0], NULL, ClxWlanNonHTRate_1Mbps, 0, TRUE, NULL);
    clxConfigInitRateParam(&rates[1], NULL, ClxWlanNonHTRate_2Mbps, 0, TRUE, NULL);
    clxConfigInitRateParam(&rates[2], NULL, ClxWlanNonHTRate_5_5Mbps, 0, TRUE, NULL);
    clxConfigInitRateParam(&rates[3], NULL, ClxWlanNonHTRate_11Mbps, 0, TRUE, NULL);
    clxConfigInitRateParam(&rates[4], NULL, ClxWlanNonHTRate_6Mbps, 0, TRUE, NULL);
    clxConfigInitRateParam(&rates[5], NULL, ClxWlanNonHTRate_9Mbps, 0, FALSE, NULL);
    clxConfigInitRateParam(&rates[6], NULL, ClxWlanNonHTRate_12Mbps, 0, TRUE, NULL);
    clxConfigInitRateParam(&rates[7], NULL, ClxWlanNonHTRate_18Mbps, 0, FALSE, NULL);
    clxConfigInitRateParam(&rates[8], NULL, ClxWlanNonHTRate_24Mbps, 0, FALSE, NULL);
    clxConfigInitRateParam(&rates[9], NULL, ClxWlanNonHTRate_33Mbps, 0, FALSE, NULL);
    clxConfigInitRateParam(&rates[10], NULL, ClxWlanNonHTRate_36Mbps, 0, FALSE, NULL);
    clxConfigInitRateParam(&rates[11], NULL, ClxWlanNonHTRate_48Mbps, 0, FALSE, NULL);
    clxConfigInitRateParam(&rates[12], NULL, ClxWlanNonHTRate_54Mbps, 0, FALSE, NULL);

    numberOfRates = 13;

#if defined(CLX_IEEE802_11_N_SUPPORTED)
    /* HT (IEEE802.11n) rates: */
    clxConfigInitRateParam(&rates[13], NULL, ClxWlanNonHTRate_NULL, 0, FALSE, NULL);
    clxConfigInitRateParam(&rates[14], NULL, ClxWlanNonHTRate_NULL, 1, FALSE, NULL);
    clxConfigInitRateParam(&rates[15], NULL, ClxWlanNonHTRate_NULL, 2, FALSE, NULL);
    clxConfigInitRateParam(&rates[16], NULL, ClxWlanNonHTRate_NULL, 3, FALSE, NULL);
    clxConfigInitRateParam(&rates[17], NULL, ClxWlanNonHTRate_NULL, 4, FALSE, NULL);
    clxConfigInitRateParam(&rates[18], NULL, ClxWlanNonHTRate_NULL, 5, FALSE, NULL);
    clxConfigInitRateParam(&rates[19], NULL, ClxWlanNonHTRate_NULL, 6, FALSE, NULL);
    clxConfigInitRateParam(&rates[20], NULL, ClxWlanNonHTRate_NULL, 7, FALSE, NULL);

    numberOfRates = 21;

#	if defined (SUPPORT_TWO_SPATIAL_STREAMS)
    /* MIMO rates */
    clxConfigInitRateParam(&rates[21], NULL, ClxWlanNonHTRate_NULL, 8, FALSE, NULL);
    clxConfigInitRateParam(&rates[22], NULL, ClxWlanNonHTRate_NULL, 9, FALSE, NULL);
    clxConfigInitRateParam(&rates[23], NULL, ClxWlanNonHTRate_NULL, 10, FALSE, NULL);
    clxConfigInitRateParam(&rates[24], NULL, ClxWlanNonHTRate_NULL, 11, FALSE, NULL);
    clxConfigInitRateParam(&rates[25], NULL, ClxWlanNonHTRate_NULL, 12, FALSE, NULL);
    clxConfigInitRateParam(&rates[26], NULL, ClxWlanNonHTRate_NULL, 13, FALSE, NULL);
    clxConfigInitRateParam(&rates[27], NULL, ClxWlanNonHTRate_NULL, 14, FALSE, NULL);
    clxConfigInitRateParam(&rates[28], NULL, ClxWlanNonHTRate_NULL, 15, FALSE, NULL);

    numberOfRates = 29;
#	endif
#endif

    /*
    Initialize the configuration array object (stationConfig.supportedRates) to hold the list of supported data rates:
    */
    clxConfigInitParamsArray(ratesArray,
        "SupportedRates",
        (ClxConfigParam*)rates,
        NULL,
        numberOfRates,
        parentList);
}

ClxError mainWiFiInit()
{
    ClxError error = CLX_SUCCESS;
    if (wlanStack == NULL)
    {
        clxTcpIpModule_Init();      /* Initialize the LwIP stack */

        struct WlanConfig
        {
            ClxConfigList    parentList;

            /*
            Driver specific parameters:
            */
            ClxConfigString  sdioDriverName;
            ClxConfigString  firmwareFileName;
            ClxConfigData    masterKey;
            ClxConfigInteger frameCaptureMask;
#if defined(CLX_WILINK)
            ClxConfigInteger rxHeapSize;
            ClxConfigInteger rxBaWinSize;
            ClxConfigInteger sdioFrameCaptureMask;

#if defined(CLX_WL12XX)
            ClxConfigString  nvsFileName;
            ClxConfigInteger refClock;
#elif defined(CLX_WL18XX)
            ClxConfigData    wl18xxTxPowerList;
#endif

#if defined(ENABLE_WILINK_FW_LOG)
            ClxConfigInteger wilink8LogAccess;
#endif

#elif defined(CLX_MARVELL)
            ClxConfigInteger  scanTableSize;
            ClxConfigInteger  mlanHeapSize;
#endif

#if defined(CLX_WIFI_OVER_LAN)
            ClxConfigInteger  localIP;
            ClxConfigInteger  localNetmask;
#endif
            ClxConfigInteger  stackDescriptorHeapSize;
        } wlanConfig;

        clxConfigInitParamsList(&wlanConfig.parentList, NULL, NULL);

        /*
        Name of the SDIO driver. This value is passed to the SDIO interface implementation in the BSP (ClxSdioBspInterface),
        and its meaning depends on the BSP interface implementation and/or the underlying platform.
        Refer to the SDIO interface implementation in the BSP
        */
        clxConfigInitStringParam(&wlanConfig.sdioDriverName, "SdioDriverName", "SDCardDev0", &wlanConfig.parentList);

#if !defined(CLX_WIFI_OVER_LAN)
        /*
        The file containing WL1xx firmware binary. Can be a real file in the underlying file system, or a virtual file
        through an implementation of ClxFileBspInterface BSP interface:
        */
        clxConfigInitStringParam(&wlanConfig.firmwareFileName, "FirmwareFileName", firmwareFileName, &wlanConfig.parentList);
#endif

        /* Frames to be captured by ClarinoxDebugger. 0xFFFFFFFF & (~CLX_WLAN_FRAME_TYPE_BEACON) means capture all frames except for beacons.  */
        clxConfigInitIntegerParam(&wlanConfig.frameCaptureMask, "FrameCaptureMask", 0xFFFFFFFF, &wlanConfig.parentList);

#if defined(CLX_WILINK)
#if defined(CLX_WL12XX)
        clxConfigInitStringParam(&wlanConfig.nvsFileName, "NvsFileName", "wl127x-nvs.bin", &wlanConfig.parentList);
        clxConfigInitIntegerParam(&wlanConfig.refClock, "WL12XX_ReferenceClock", (u4)Wl12xxReferenceClock_Clock_38_4Mhz_TCXO, &wlanConfig.parentList);
#endif
        clxConfigInitIntegerParam(&wlanConfig.sdioFrameCaptureMask, wl1xxSdioCaptureMask, CLX_WL18XX_SDIO_CAPTURE_ALL, &wlanConfig.parentList);

        clxConfigInitIntegerParam(&wlanConfig.rxHeapSize, "WL18XX_RxHeapSize", 16 * 1024, &wlanConfig.parentList);
        clxConfigInitIntegerParam(&wlanConfig.rxBaWinSize, "WL18XX_RxBaWinSize", 4, &wlanConfig.parentList);

#if defined(CLX_WL18XX)
        const u1 powerLevels[3] =
        {
            wifiPowerLevel,   /* Max Power Level (0xff : automatic mode power setting - 0 to 0x30 :  manual mode power settings in dBm) */
            wifiPowerLevel,   /* Medium Power Level (0xff : automatic mode power setting - 0 to 0x30 :  manual mode power settings in dBm) */
            wifiPowerLevel,   /* Lowe Power Level (0xff : automatic mode power setting - 0 to 0x30 :  manual mode power settings in dBm) */
        };

        clxConfigInitDataParam(&wlanConfig.wl18xxTxPowerList, "WL18XX-TxPowerList", powerLevels, sizeof(powerLevels), &wlanConfig.parentList);
#endif

#if defined(ENABLE_WILINK_FW_LOG)
        /* Set the WiLink 8 log access mechanism: */
        clxConfigInitIntegerParam(&wlanConfig.wilink8LogAccess, "WL18XX-FirmwareLogAccess", ClxWl18xxFirmwareLogAccess_Continuous_DebugPin, &wlanConfig.parentList);
#endif
#elif defined(CLX_MARVELL)
        clxConfigInitIntegerParam(&wlanConfig.scanTableSize, "Marvell-ScanTableSize", 30, &wlanConfig.parentList);
        clxConfigInitIntegerParam(&wlanConfig.mlanHeapSize, "Marvell-TotalHeapSize", MLAN_HEAP_SIZE, &wlanConfig.parentList);;
#endif

#if defined(CLX_WIFI_OVER_LAN)
        clxConfigInitIntegerParam(&wlanConfig.localIP, "WiFiOverLAN_LocalIP", WIFI_OVER_LAN_LOCAL_IP, &wlanConfig.parentList);
        clxConfigInitIntegerParam(&wlanConfig.localNetmask, "WiFiOverLAN_LocalNetmask", WIFI_OVER_LAN_LOCAL_NETMASK, &wlanConfig.parentList);
#endif
        clxConfigInitIntegerParam(&wlanConfig.stackDescriptorHeapSize, "StackDescriptorHeapSize", WLAN_STACK_DESCRIPTOR_SIZE, &wlanConfig.parentList);

        /*
        Initialize the ClarinoxWLAN stack and bind it to a physical WLAN interface. If successful, one or more
        Virtual Interfaces can be started on top of this physical interface:
        */
        error = clxInitClarinoxWlan(&Wlan_DriverEntry,        	            /* Driver Entry for Wlan                                                                                            */
            NULL,
            wlanIndicationHandler,                                  /* Indication handler function which is called when there is any indication from WLAN stack                 */
            &wlanConfig.parentList,                                 /* Configuration parameters */
            &wlanStack,                                                 /* On a successful return, will contain the stack object                                                */
            TRUE);                                                  /* Do not return until the initialization of ClarinoxWLAN is complete either in error or with success       */
        if (error != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("Initializing ClarinoxWlan failed with error %s\n", clxGetWlanErrorCodeText(error));
            wlanStack = NULL;
            return error;
        }

        clxConsoleUIEngineText("ClarinoxWLAN version      %s\n", clxGetClarinoxWlanVersion());
        clxConsoleUIEngineText("ClarinoxSoftFrame version %s\n", clxGetClarinoxSoftFrameVersion());


#ifdef CLX_WPA_SUPPLICANT
        if (clxInitWpaSupplicant(clxA2lGetStackIndicationScheduler(wlanStack),
            wlanIndicationHandler,
            TRUE) != CLX_SUCCESS)
        {
            clxConsoleUIEngineText("Initialization of WPA Supplicant failed\n");
            return error;
        }
#endif
    }
    else
    {
        clxConsoleUIEngineText("Wifi Stack is already enabled\n");
    }

    return error;
}

int mainWiFi()
{
    //clxInitBsp();                                             /* Board support package initialization                   */
    //clxConsoleUIEngineInit(128);                    		  /* Initializing the UI interface with 128 character input max from console */

#if defined(CLX_DEBUG)
    ClxError error = CLX_SUCCESS;
#endif

#define CLX_BOOTLOADER_IMAGE_TAG
#if defined (CLX_BOOTLOADER_IMAGE_TAG)
    const char time[] = __TIME__;
    const char date[] = __DATE__;
    clxConsoleUIEngineText("\n\n\n\n\n****************************************\n");
    clxConsoleUIEngineText("         Firmware image details\n"                   );
    clxConsoleUIEngineText("           Built time: %s\n",time                    );
    clxConsoleUIEngineText("           Built date: %s\n",date                    );
    clxConsoleUIEngineText("********************************************\n\n\n\n");
#endif

    while(1)
    {
        const s1* menu = "Enable Wifi Stack\0"
                         "Wlan Station(STA) Test\0"
                         "Wlan AccessPoint(AP) Test\0"
                         "Wlan Mesh Test\0"
                         "Disable Wifi Stack\0"
                         "Change WiFi Power level\0"
                         "Issue LWIP command\0"
                         "Iperf\0"
        				 "Debug Control\0"
                         "Wlan Mesh Auto Test\0"
                         "Return to previous menu";

#if defined(CLARINOX_MESH_DEMO_ROOT_MENU) || defined(CLARINOX_MESH_DEMO_NONROOT_MENU)
        u4 s =1;
#else
        u4 s = clxConsoleUIEngineShowMenu("Please select how to proceed:", menu, 11);
#endif

        if (s == 1)
        {
            mainWiFiInit();

#if defined(CLARINOX_MESH_DEMO_ROOT_MENU) || defined(CLARINOX_MESH_DEMO_NONROOT_MENU)
            while(1)
            {
                if(rootInitFlag == TRUE)
                {
                    CLX_PRINTF("\n\rMESH NODE STARTING AS A ROOT\n\r");
                    showMeshMenu(wlanStack);
                }
                else if(nonrootInitFlag == TRUE)
                {
                    CLX_PRINTF("\n\rMESH NODE STARTING AS A NONROOT\n\r");
                    meshAutoInit(wlanStack);
                }
            }
#endif
        }
        else if (s == 2)
        {
	        if (wlanStack)
            {
                showStationMenu(wlanStack);
            }
            else
            {
                clxConsoleUIEngineText("Wifi Stack does not exist!\n");
            }
        }
        else if (s == 3)
        {
            if (wlanStack)
            {
                showAccessPointMenu(wlanStack);
            }
            else
            {
                clxConsoleUIEngineText("Wifi Stack does not exist!\n");
            }
        }
        else if (s == 4)
        {
#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
            if (wlanStack)
            {
                showMeshMenu(wlanStack);
            }
            else
            {
                clxConsoleUIEngineText("Wifi Stack does not exist!\n");
            }
#else
            clxConsoleUIEngineText("ClarinoxMesh not supported!\n");
#endif
        }
        else if (s == 5)
        {
            if (wlanStack)
            {

#ifdef CLX_WPA_SUPPLICANT
                if (clxTerminateWpaSupplicant(TRUE) != CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("termination of WPA Supplicant failed\n");
                }

                clxDestroyWpaSupplicant();
#endif

                /*
                Disabling the WLAN stack consists of two phases: Termination of the stack internal tasks and state machines, and then
                Destroying the stack object and all memory and resources associated to it. We call clxTerminateClarinoxWlan() first
                to terminate the WLAN stack. the call is always asynchronous (it returns immediately). When the termination procedure
                is complete, the indication CLX_WLAN_STACK_TERMINATION_COMPLETE_INDICATION is received. Upon reception of this indication,
                we can destroy the stack object by calling clxDestroyClarinoxWlan(). But, we cannot call this function in the context of the
                indication thread. So, we use a semaphore to wake up and destroy the stack in the context of the main thread:
                */
                clxTerminateClarinoxWlan(wlanStack, TRUE);

                /* Wait for the CLX_WLAN_STACK_TERMINATION_COMPLETE_INDICATION */
                clxConsoleUIEngineText("\nWaiting for stack termination, to complete . . .");


                /* CLX_WLAN_STACK_TERMINATION_COMPLETE_INDICATION received */
                clxDestroyClarinoxWlan(wlanStack);

                /* If clxDestroyClarinoxWlan returns it means that stack has been destroyed */
                clxConsoleUIEngineText("\nStack destroyed completely");

                clxTcpIpModule_Deinit();

                wlanStack = NULL;
            }
            else
            {
                clxConsoleUIEngineText("Wifi Stack does not exist!\n");
            }
        }
        else if (s == 6)
        {
#if defined(CLX_WILINK)
        	if(wlanStack)
        	{
        		clxConsoleUIEngineText("Please stop any active wifi interfaces and disable the WiFi stack first!\n");
        	}
        	else
        	{
                clxConsoleUIEngineInputBox("Enter WiFi power level ", clxUiInputBuffer, sizeof(clxUiInputBuffer));

                wifiPowerLevel = atoi(clxUiInputBuffer);

                if(wifiPowerLevel > MAX_TX_POWER_SUPPORTED_BY_WLAN)
                {
                	wifiPowerLevel = MIN(DEFAULT_STA_MAX_TX_POWER, DEFAULT_AP_MAX_TX_POWER);;
                }

                clxConsoleUIEngineText("Power level chosen is %u dBm\n", wifiPowerLevel);
                clxConsoleUIEngineText("Please re-enable the WiFi stack for new power level to take effect.\n");
        	}
#else
            clxConsoleUIEngineText("Feature not supported!\n");
#endif
        }
        else if (s == 7)
        {
#if defined(CLX_NETWORK_INTERFACE_LWIP)
            clxConsoleUIEngineInputBox("<lwip> ", clxUiInputBuffer, sizeof(clxUiInputBuffer));
            issueLwipCommand(clxUiInputBuffer);
#else
            clxConsoleUIEngineText("Feature not supported!\n");
#endif
        }
        else if (s == 8)
        {
#if defined(CLX_SOCKETS_SUPPORT)
        	clxConsoleUIEngineInputBox("<iperf> ", clxUiInputBuffer, sizeof(clxUiInputBuffer));
            clxStartIPerf(clxUiInputBuffer);
#else
            clxConsoleUIEngineText("Feature not supported!\n");
#endif
        }
        else if (s == 9)
        {
#if defined(CLX_DEBUG)
            const s1* debugMenu = "Enable debug message generation\0"
                "Disable debug message generation\0"
                "Flush debug FIFO to ClariFi (FIFO mode only)\0"
                "Disable debug FIFO mode (FIFO mode only)\0"
                "Throw a BLACKBOX\0"
                "Return to previous menu";

            u4 s = clxConsoleUIEngineShowMenu("Please select how to proceed:", debugMenu, 6);

            switch (s)
            {
            case 1:
                {
                    clxConsoleUIEngineInputBox("Debug bit to enable (Bit 0 is the right most bit): ", clxUiInputBuffer, sizeof(clxUiInputBuffer));
                    s4 value = clxAsciiToInteger(clxUiInputBuffer);
                    if ((value >= 0) && (value < sizeof(u4) * 8))
                    {
                        clxSetDebugFlagBits(1 << (u4)value);
                    }
                    else
                    {
                        clxConsoleUIEngineText("Invalid debug bit (%d)\n", value);
                    }
                }
                break;

            case 2:
                {
                    clxConsoleUIEngineInputBox("Debug bit to disable (Bit 0 is the right most bit): ", clxUiInputBuffer, sizeof(clxUiInputBuffer));
                    s4 value = clxAsciiToInteger(clxUiInputBuffer);
                    if ((value >= 0) && (value < sizeof(u4) * 8))
                    {
                        clxResetDebugFlagBits(1 << (u4)value);
                    }
                    else
                    {
                        clxConsoleUIEngineText("Invalid debug bit (%d)\n", value);
                    }
                }
                break;

            case 3:
                error = clxFlushDebugFifoToClariFi();
                if (error != CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("clxFlushDebugFifoToClariFi() failed with error %s\n", clxGetWlanErrorCodeText(error));
                }
                break;

            case 4:
                error = clxDisableDebugFifoMode();
                if (error != CLX_SUCCESS)
                {
                    clxConsoleUIEngineText("clxFlushDebugFifoToClariFi() failed with error %s\n", clxGetWlanErrorCodeText(error));
                }
                break;

            case 5:
                BLACKBOX;
                break;

            default:
                break;
            }
#else
            clxConsoleUIEngineText("Feature supported in Debug version only\n");
#endif
        }
        else if (s == 10)
        {
#if defined(CLX_WIFI_MESH_AUTO)
            if (wlanStack)
            {
                meshAutoInit(wlanStack);
            }
            else
            {
                clxConsoleUIEngineText("Wifi Stack does not exist!\n");
            }
#else
            clxConsoleUIEngineText("ClarinoxMeshAuto not supported!\n");
#endif
        }
        else if (s == 11)
        {
            return 0;
        }
    }
}

/*******************************************************************************************************************************
*                                                     wlanIndicationHandler
*
* This call-back function is registered for wlan stack, any events raised inside stack, causes this
* call-back function executed with the associated event and parameters. Executed from the stack thread context
*
* \param stack Local device stack handle
* \param serviceHandle profile/service handle
* \param messageID indication id
* \param params void pointer to the indication parameters
* \param errorCode contains the error code
*
*******************************************************************************************************************************/
static boolean wlanIndicationHandler(ClxStack stack, ClxHandle handle, u4 messageID, const void* params, ClxError errorCode)
{
    switch (messageID)
    {
    case CLX_WLAN_HARDWARE_ERROR_INDICATION:
        clxConsoleUIEngineText("\nWlan Fatal hardware error received\n");
        break;

    case CLX_INIT_CLARINOX_WLAN_COMPLETE:
        clxConsoleUIEngineText("\nWlan stack has been initialized successfully\n");
        break;

    case CLX_TERMINATE_CLARINOX_WLAN_COMPLETE:
        clxConsoleUIEngineText("\nWlan stack has been terminated successfully\n");
        break;

    case CLX_WLAN_SCAN_COMPLETE:
    case CLX_WLAN_BSS_DISCOVERED_INDICATION:
    case CLX_WLAN_LINK_LOST_INDICATION:
    case CLX_WLAN_AP_DISCONNECTED_INDICATION:
        return clxWlanStationIndicationHandler(stack, handle, messageID, params, errorCode);

    case CLX_WLAN_DRIVER_SPECIFIC_INDICATION:
        if (clxWlanStationIndicationHandler(stack, handle, messageID, params, errorCode) == FALSE)
        {
            return clxWlanAccessPointIndicationHandler(stack, handle, messageID, params, errorCode);
        }
        break;

    case CLX_WLAN_STATION_JOINED_INDICATION:
    case CLX_WLAN_STATION_DISCONNECTED_INDICATION:
    case CLX_WLAN_STATION_AUTHENTICATION_INITIATED_INDICATION:
    case CLX_WLAN_STATION_ASSOCIATION_INITIATED_INDICATION:
    case CLX_WLAN_STATION_AUTHENTICATION_COMPLETED_INDICATION:
    case CLX_WLAN_STATION_ASSOCIATION_COMPLETED_INDICATION:
        return clxWlanAccessPointIndicationHandler(stack, handle, messageID, params, errorCode);

#if defined(CLARINOX_WLAN_MESH_SUPPORTED)
    case CLX_WLAN_MESH_UPLINK_CONNECTION_EXCEPTION_INDICATION:
    case CLX_WLAN_MESH_NODE_DISCOVERED_INDICATION:
    case CLX_WLAN_MESH_NODE_REMOVED_INDICATION:
    case CLX_WLAN_MESH_NODE_UPDATED_INDICATION:
    case CLX_WLAN_MESH_NEW_ROOT_DETECTED_INDICATION:
    case CLX_WLAN_MESH_TOPOLOGY_QUERY_RESPONSE_INDICATION:
    case CLX_WLAN_MESH_PACKET_PROCESSED_INDICATION:
        return clxWlanMeshIndicationHandler(stack, handle, messageID, params, errorCode);
#endif
        
    default:
        return FALSE;
    }

    return TRUE;
}


/*******************************************************************************************************************************
*                                                     printCapabilities
*******************************************************************************************************************************/
void clxWlanPrintCapabilities(u4 capabilities)
{
    /*
    General capabilities of a WLAN station. Can be bit-wise-combined into a single variable:
    */
    clxConsoleUIEngineText("\nGeneral Capabilities:\n");

    if (capabilities & CLX_WLAN_CAPABILITY_SHORT_PREAMBLE_SUPPORTED)
    {
        clxConsoleUIEngineText("CLX_WLAN_CAPABILITY_SHORT_PREAMBLE_SUPPORTED\n");
    }
    if (capabilities & CLX_WLAN_CAPABILITY_QOS_SUPPORTED)
    {
        clxConsoleUIEngineText("CLX_WLAN_CAPABILITY_QOS_SUPPORTED\n");
    }
    if (capabilities & CLX_WLAN_CAPABILITY_SHORT_SLOT_TIME_SUPPORTED)
    {
        clxConsoleUIEngineText("CLX_WLAN_CAPABILITY_SHORT_SLOT_TIME_SUPPORTED\n");
    }
    if (capabilities & CLX_WLAN_CAPABILITY_RADIO_MEASUREMENT_SUPPORTED)
    {
        clxConsoleUIEngineText("CLX_WLAN_CAPABILITY_RADIO_MEASUREMENT_SUPPORTED\n");
    }
    if (capabilities & CLX_WLAN_CAPABILITY_APSD_SUPPORTED)
    {
        clxConsoleUIEngineText("CLX_WLAN_CAPABILITY_APSD_SUPPORTED\n");
    }
    if (capabilities & CLX_WLAN_CAPABILITY_BTM_SUPPORTED)
    {
    	clxConsoleUIEngineText("CLX_WLAN_CAPABILITY_BTM_SUPPORTED\n");
    }
}

#if defined CLX_BANDWIDTH_LIMIT_SUPPORTED
extern void clxWlanSetBwLimit(ClxHandle handle)
{
	ClxResult ret;

	while (1)
	{
		const s1 *menu1 = "Set Tx Bandwitdh Limit\0"
				"Set Rx Bandwidth Limit\0"
				"Set Both Bandwidth Limits\0"
				"Return to main menu";

		u4 numOfItems = 4;

		u4 bwLimitType = clxConsoleUIEngineShowMenu(
				"Select bandwidth limit direction", menu1, numOfItems);

		if (bwLimitType >= 4)
			return;

		const s1 *menu2 = "10Mbps\0"
				"5Mbps\0"
				"2Mbps\0"
				"1Mbps\0"
				"500Kbps\0"
				"200Kbps\0"
				"100Kbps\0"
				"No Limit\0"
				"Return to main menu";

		numOfItems = 9;

		u4 bwLimit = clxConsoleUIEngineShowMenu("Select bandwidth limit", menu2,
				numOfItems);
		u4 bwLimitBps = 0;

		switch (bwLimit)
		{
		case 1:
			bwLimitBps = 10000000;
			break;
		case 2:
			bwLimitBps = 5000000;
			break;
		case 3:
			bwLimitBps = 2000000;
			break;
		case 4:
			bwLimitBps = 1000000;
			break;
		case 5:
			bwLimitBps = 500000;
			break;
		case 6:
			bwLimitBps = 200000;
			break;
		case 7:
			bwLimitBps = 100000;
			break;
		case 8:
			bwLimitBps = 0;
			break;
		default:
			return;
		}

		struct BwLimitSet
		{
			ClxConfigList parentList;
			ClxConfigUnsigned setTxBwLimitBps;
			ClxConfigUnsigned setRxBwLimitBps;
			ClxConfigArray    ratesArray;
		};

		struct BwLimitSet bwLimitSet;

		/* The parent list to be passed to clxConfigInitParamsList. SHALL be initialized first: */
		clxConfigInitParamsList(&bwLimitSet.parentList, NULL, NULL);

		if (bwLimitType & 1)
		{
			clxConfigInitUnsignedParam(&bwLimitSet.setTxBwLimitBps,
					"SetTxBwLimit", bwLimitBps, &bwLimitSet.parentList);
		}

		if (bwLimitType & 2)
		{
			clxConfigInitUnsignedParam(&bwLimitSet.setRxBwLimitBps,
					"SetRxBwLimit", bwLimitBps, &bwLimitSet.parentList);
		}

		ret = clxWlanSetParametersValue(handle, /* Handle to the virtual interface as returned by clxWlanCreateInterface */
		&bwLimitSet.parentList, /* A pointer to parent list object containing the parameter */
		TRUE); /* Blocking mode. Do no return until the parameter is read from the driver */

		if (ret == CLX_SUCCESS)
		{
			clxConsoleUIEngineText("BW Limit set successfully\n");
		}
	}
}

extern void clxWlanSetBwLimitExceptPors(ClxHandle handle)
{
	ClxResult ret;

	u2 ports[MAX_BW_LIMIT_EXCEPT_PORTS_NUM];
	u1 size = 0;

	struct
	{
		ClxConfigList parentList;
		ClxConfigArray portsArray;
	} exceptPorts;

	/* The parent list to be passed to clxConfigInitParamsList. SHALL be initialized first: */
	clxConfigInitParamsList(&exceptPorts.parentList, NULL, NULL);

	/* Add except ports to array (shown below as an example!)*/
	/*
	 ports[size++] = 100;
	 ports[size++] = 200;
	 ports[size++] = 5353;
	 */

	clxConfigInitParamsArray(&exceptPorts.portsArray, "BwLimitExcepPorts",
			(u2*) ports, NULL, size, &exceptPorts.parentList);

	ret = clxWlanSetParametersValue(handle, /* Handle to the virtual interface as returned by clxWlanCreateInterface */
	&exceptPorts.parentList, /* A pointer to parent list object containing the parameter */
	TRUE); /* Blocking mode. Do no return until the parameter is read from the driver */

	if (ret == CLX_SUCCESS)
	{
		clxConsoleUIEngineText("Exception ports set successfully.\n");
	}
}

extern void clxWlanGetBwUsage(ClxHandle handle)
{
	ClxResult ret;

	while (1)
	{
		const s1 *menu = "Get Tx Bandwitdh Usage\0"
				"Get Rx Bandwidth Usage\0"
				"Get Both Bandwidth Usages\0"
				"Return to main menu";

		u4 numOfItems = 4;

		u4 bwLimitType = clxConsoleUIEngineShowMenu(
				"Select bandwidth limit direction", menu, numOfItems);

		if (bwLimitType >= 4)
			return;

		struct BwLimitGet
		{
			ClxConfigList parentList;
			ClxConfigUnsigned getTxBwUsageBps;
			ClxConfigUnsigned getRxBwUsageBps;
		};

		struct BwLimitGet bwLimitGet;

		/* The parent list to be passed to clxConfigInitParamsList. SHALL be initialized first: */
		clxConfigInitParamsList(&bwLimitGet.parentList, NULL, NULL);

		if (bwLimitType & 1)
		{
			clxConfigInitUnsignedParam(&bwLimitGet.getTxBwUsageBps,
					"GetTxBwUsage", 0, &bwLimitGet.parentList);
		}

		if (bwLimitType & 2)
		{
			clxConfigInitUnsignedParam(&bwLimitGet.getRxBwUsageBps,
					"GetRxBwUsage", 0, &bwLimitGet.parentList);
		}

		ret = clxWlanGetParametersValue(handle, /* Handle to the virtual interface as returned by clxWlanCreateInterface */
		&bwLimitGet.parentList, /* A pointer to parent list object containing the parameter */
		TRUE); /* Blocking mode. Do no return until the parameter is read from the driver */

		if (ret == CLX_SUCCESS)
		{
			if (bwLimitType & 1)
			{
				clxConsoleUIEngineText("Tx bandwidth usage = %dKbps\n",
						(bwLimitGet.getTxBwUsageBps.paramValue / 1000));
			}

			if (bwLimitType & 2)
			{
				clxConsoleUIEngineText("Rx bandwidth usage = %dKbps\n",
						(bwLimitGet.getRxBwUsageBps.paramValue / 1000));
			}
		}
	}
}
#endif /* CLX_BANDWIDTH_LIMIT_SUPPORTED */


int clarinoxMainWifi(void)
{
#if defined(CLX_TRACE)
	CLX_ENABLE_ALL_TRACE_EVENT_CATEGORIES;
    clxTraceInit();
#endif

    mainWiFi();
    return 0;
}

