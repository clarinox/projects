/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                ServicesMenu.cpp
* Description         This file provides the selectService function, which
*                     includes the UI menu with the supported services options.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2021 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

// _____________________________________________________________________________
//
#undef  CLX_MODULE_ID
#define CLX_MODULE_ID  20014
// _____________________________________________________________________________
//

#define CLX_ONLY_SPP

#include "ClxCommon.h"
#include "ClarinoxBlue.h"

#include "../mainBluetooth.h"

#include "SPP/Spp.h"
#ifndef CLX_ONLY_SPP
#include "A2dpSource.h"
#include "A2dpSink.h"
#include "Avrcp.h"
#include "HfpHandsfree.h"
#include "HfpAudioGateway.h"
#include "HspHeadset.h"
#include "HspAudioGateway.h"
#include "Pbap.h"
#include "Map.h"
#ifdef HID_HOST
#include "HidHost.h"
#else
#include "HidDevice.h"
#endif
#endif

/*****************************************************************************************************************************************
TODO NOTES TO ADD OR REMOVE A PROFILE

1. Add an/Remove the profile's respective header in #include
2. Add an/Remove the profile's menu enum value entry to ServiceMenuOption
3. Add/Remove the profile's respective create handle function to initializeClassicProfiles(..)
4. Add/Remove the profile's respective delete handle function to terminateClassicProfiles(..)
5. Add/Remove the profile's suitable menu display name to the 'menu' string in function allProfilesMenuFunction(..)
6. Add/Remove the profile's respective switch case entry with menu display function call to/from the function allProfilesMenuFunction(..)
*****************************************************************************************************************************************/


/* Menu options used to invoke service Menu */
typedef enum ServiceMenuOptionEnum
{
    ServiceMenuOption_ServiceDiscovery = 1,
#ifndef CLX_ONLY_SPP
    ServiceMenuOption_A2dpSourceRole,
    ServiceMenuOption_A2dpSinkRole,
    ServiceMenuOption_Avrcp,
#endif
    ServiceMenuOption_Spp,
#ifndef CLX_ONLY_SPP
	ServiceMenuOption_Map,
    ServiceMenuOption_Pbap,
    ServiceMenuOption_HfpHf,
    ServiceMenuOption_HfpAg,
    ServiceMenuOption_HspHs,
    ServiceMenuOption_HspAg,
#ifdef HID_HOST
    ServiceMenuOption_HidHost,
#else
    ServiceMenuOption_HidDevice,
#endif
#endif
	ServiceMenuOption_ReturnToPrevious,
    ServiceMenuOption_Total
}ServiceMenuOption;

#if defined(CLX_SCO_BRIDGE)
/* 
Variables associated with SCO Menu object 
*/
typedef struct ClxScoMenuInfoStruct
{
    ClxDeviceId hfDeviceId;      /* Device ID of the remote HF role device */
    ClxDeviceId agDeviceId;      /* Device ID of the remote AG role device */
}ClxScoMenuInfo;

/* Structure with variables required for SCO Menu operations */
ClxScoMenuInfo scoMenuInfo = {};
#endif

/******************************************************************************************************************************************
*                                                       initializeClassicProfiles
*
* Initializes individual classic profiles with configuration parameters for Bluetooth stack.
*
* \param stack    - ClarinoxBlue stack.
*
* \return void
*
******************************************************************************************************************************************/
void initializeClassicProfiles(ClxStack stack)
{
    clxConsoleUIEngineText("\n");

    /*
    Create handles for all the supported profiles for this application
    */
//    createA2dpSourceHandle(stack);
//    createA2dpSinkHandle(stack);
//    createAvrcpHandle(stack);
//    createHfpHfHandle(stack);
//    createHfpAgHandle(stack);
//    createHspHsHandle(stack);
//    createHspAgHandle(stack);
//    createMapHandle(stack);
//    createPbapHandle(stack);
//#ifdef HID_HOST
//    createHidHostHandle(stack);
//#else
//    createHidDeviceHandle(stack);
//#endif
    clxConsoleUIEngineText("\n");
}

/******************************************************************************************************************************************
*                                                       terminateClassicProfiles
*
* De-Initializes individual classic profiles and resources.
*
******************************************************************************************************************************************/
void terminateClassicProfiles()
{
    /*
    Close the created profile handles before terminating
    */
    deleteSppHandle();
#ifndef CLX_ONLY_SPP
#ifdef HID_HOST
    deleteHidHostHandle();
#else
    deleteHidDeviceHandle();
#endif
    deletePbapHandle();
    deleteMapHandle();
    deleteHspAgHandle();
    deleteHspHsHandle();
    deleteHfpAgHandle();
    deleteHfpHfHandle();
    deleteAvrcpHandle();
    deleteA2dpSinkHandle();
    deleteA2dpSourceHandle();
#endif
}

/*******************************************************************************************************************************
*                                                       allProfilesMenuFunction
*
* Provide the service selection UI menu and show the selected service's menu
*
* \param stack      - ClarinoxBlue stack
* \param deviceId   - Device ID of the remote device that is to be connected
* \param deviceName - Name string of the remote device
*
*******************************************************************************************************************************/
void allProfilesMenuFunction(ClxStack stack, ClxDeviceId deviceId, const s1* deviceName)
{
    while (1)
    {
        const s1* menu = "(SDP)   Service Discovery Protocol\0"
#ifndef CLX_ONLY_SPP
                         "(A2DP)  Advanced Audio Distribution Profile - Source role\0"
                         "(A2DP)  Advanced Audio Distribution Profile - Sink role\0"
                         "(AVRCP) Audio Video Remote Control Profile - Controller role\0"
#endif
                         "(SPP)   Serial Port Profile\0"
#ifndef CLX_ONLY_SPP
                         "(MAP)   Message Access Profile - (MCE) MAP Client Equipment role\0"
                         "(PBAP)  Phonebook Access Profile - (PCE) PBAP Client Equipment role\0"
                         "(HFP)   Hands-Free Profile - (HF) Hands-Free role\0"
                         "(HFP)   Hands-Free Profile - (AG) Audio Gateway role\0"
                         "(HSP)   HeadSet Profile - (HS) HeadSet role\0"
                         "(HSP)   HeadSet Profile - (AG) Audio Gateway role\0"
#ifdef HID_HOST
                         "(HID)   Human Interface - Host or Server role\0"
#else
                         "(HID)   Human Interface - Device or Client role\0"
#endif
#endif
                         "<- Return to previous menu\0";

        clxConsoleUIEngineText("\n %s", deviceName);

        u4 ch = clxConsoleUIEngineShowMenu("\nPlease select a service", menu, ServiceMenuOption_Total - 1);
        switch (ch)
        {
            case ServiceMenuOption_ServiceDiscovery:
            {
                sdapMenuFunction(stack, deviceId);
                break;
            }

#ifndef CLX_ONLY_SPP
            case ServiceMenuOption_A2dpSourceRole:
            {
                showA2dpSourceMenu(deviceId, deviceName);
                break;
            }

            case ServiceMenuOption_A2dpSinkRole:
            {
                showA2dpSinkMenu(deviceId, deviceName);
                break;
            }
            
            case ServiceMenuOption_Avrcp:
            {
                showAvrcpMenu(stack, deviceId, deviceName);
                break;
            }
#endif

            case ServiceMenuOption_Spp:
            {
                sppMenuFunction(stack, deviceId);
                break;
            }

#ifndef CLX_ONLY_SPP
            case ServiceMenuOption_Map:
            {
                showMapMenu(stack, deviceId, deviceName);
                break;
            }

            case ServiceMenuOption_Pbap:
            {
                showPbapMenu(stack, deviceId, deviceName);
                break;
            }

            case ServiceMenuOption_HfpHf:
            {
                showHfpHfMenu(stack, deviceId, deviceName);
                break;
            }

            case ServiceMenuOption_HfpAg:
            {
                showHfpAgMenu(stack, deviceId, deviceName);
                break;
            }

            case ServiceMenuOption_HspHs:
            {
                showHspHsMenu(stack, deviceId, deviceName);
                break;
            }

            case ServiceMenuOption_HspAg:
            {
                showHspAgMenu(stack, deviceId, deviceName);
                break;
            }

#ifdef HID_HOST
            case ServiceMenuOption_HidHost:
            {
                showHidHostMenu(stack, deviceId);
                break;
            }
#else
            case ServiceMenuOption_HidDevice:
            {
                showHidDeviceMenu(stack, deviceId);
                break;
            }
#endif
#endif

            case ServiceMenuOption_ReturnToPrevious:
            {
                return;
            }

            default:
            {
                clxConsoleUIEngineText("\nInvalid menu option\n");
                break;
            }
        }
    }
}

#if defined(CLX_SCO_BRIDGE)
/*******************************************************************************************************************************
*                                                       scoBridgeMenu
*
* Provide the SCO device selection and UI menu
*
* \param stack      - ClarinoxBlue stack
* \param deviceName - Name string of the remote device
*
*******************************************************************************************************************************/
void scoBridgeMenu(ClxStack stack, const s1* deviceName)
{
    while (1)
    {
        const s1* menu = "Select Hands-Free (HF) device\0"
                         "Select Audio Gateway (AG) device\0"
                         "HF Menu (Remote AG device)\0"
                         "AG Menu (Remote HF device)\0"
                         "<- Return to previous menu\0";

        clxConsoleUIEngineText("\n %s", deviceName);

        u4 ch = clxConsoleUIEngineShowMenu("\nPlease select the desired option", menu, 5);
        switch (ch)
        {
            case 1:
            {
                ClxDeviceId id = selectPairedDevice(stack);
                if ( CLX_IS_DEVICE_ID_VALID(id) == TRUE )
                {
                    scoMenuInfo.hfDeviceId = id;
                }
                else
                {
                    clxConsoleUIEngineText("There are no paired devices!");
                }

                break;
            }

            case 2:
            {
                ClxDeviceId id = selectPairedDevice(stack);
                if ( CLX_IS_DEVICE_ID_VALID(id) == TRUE )
                {
                    scoMenuInfo.agDeviceId = id;
                }
                else
                {
                    clxConsoleUIEngineText("There are no paired devices!");
                }

                break;
            }

            case 3:
            {
                showHfpHfMenu(stack, scoMenuInfo.agDeviceId, deviceName);
                break;
            }

            case 4:
            {
                showHfpAgMenu(stack, scoMenuInfo.hfDeviceId, deviceName);
                break;
            }

            case 5:
            {
                return;
            }
    
            default:
            {
                clxConsoleUIEngineText("\nInvalid menu option\n");
                break;
            }
        }
    }
}
#endif /* #if defined(CLX_SCO_BRIDGE) */


