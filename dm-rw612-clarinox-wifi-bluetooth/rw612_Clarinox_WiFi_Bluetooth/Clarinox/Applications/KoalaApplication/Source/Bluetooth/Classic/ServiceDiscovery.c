/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                ServiceDiscovery.cpp
* Description         This file provides SDAP profile handle creation / deletion,
*                     SDAP UI menu, and indication call back functions.
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
#define CLX_MODULE_ID  20024
// _____________________________________________________________________________
//

#include "ClxCommon.h"
#include "ClarinoxBlue.h"

//#include "../mainBluetooth.h"

#include "Sdap.Api.h"
#include "Gap.Api.h"

/* 
Device ID specific parameters as config items
*/
typedef struct SdpDeviceIdDetailsEnum
{
    ClxConfigUnsigned sdpDiSpecificationId;
    ClxConfigUnsigned sdpDiVendorId;
    ClxConfigUnsigned sdpDiProductId;
    ClxConfigUnsigned sdpDiVersion;
    ClxConfigUnsigned sdpDiPrimaryRecord;
    ClxConfigUnsigned sdpDiVendorIdSource;
}SdpDeviceIdDetails;

/* 
Enum for menu items
*/
typedef enum ClxSdapMenuEnum
{
    ClxSdapMenu_DiscoverDevices             = 1,
    ClxSdapMenu_GetDeviceDetails,
    ClxSdapMenu_AllowDeviceToDiscover,
    ClxSdapMenu_ReturnToPreviousMenu,
    ClxSdapMenu_Total
}ClxSdapMenu;

/* 
Description of ClxBlueServiceType which is used to display the supported services received from remote device
*/
const s1* servicesList[] = {"Headset Profile (HSP) Headset role",
                            "Headset Profile (HSP) AudioGateway role",
                            "Hands-Free Profile (HFP) Hands-Free role",
                            "Hands-Free Profile (HFP) AudioGateway role",
                            "Serial Port Profile (SPP)",
                            "PhoneBook Access Profile (PBAP) Client role",
                            "PhoneBook Access Profile (PBAP) Server role",
                            "Object Push Profile (OPP)",
                            "Message Notification Server (MNS) of Message Access Profile (MAP)",
                            "Message Access Server (MAS) of Message Access Profile (MAP)",
                            "SIM Access Profile (SAP) Server role",
                            "File Transfer Profile (FTP) Server Role",
                            "Audio-Video Remote Control Profile (AVRCP) Target role",
                            "Audio-Video Remote Control Profile (AVRCP) Controller role",
                            "Audio Advanced Distribution Profile (A2DP) Sink role",
                            "Audio Advanced Distribution Profile (A2DP) Source role",
                            "Dial-up Networking Profile (DUN)",
                            "Personal Area Networking Profile(PAN USER)",
                            "Personal Area Networking Profile(PAN NAP)",
                            "Personal Area Networking Profile(PAN GN)",
                            "Human Interface Device Profile (HID)",
                            "Video Distribution Profile (VDP) Sink role",
                            "Video Distribution Profile (VDP) Source role",
                            "Health Device Profile (HDP) Sink role",
                            "Health Device Profile (HDP) Source role",
                            "Synchronization Profile (SYNC)",
                            "Device ID Profile (DI)"};


/* 
Variables associated with Service Menu 
*/
typedef struct ClxServiceMenuInfoStruct
{
    ClxConfigList       serviceInfo;    /* Config list to fetch and store the details of the service information from remote device */
    SdpDeviceIdDetails  sdpDidDetails;  /* Object to store the SDP device ID profile related informations                           */
}ClxServiceMenuInfo;

/* Structure with variables required for Service Menu */
ClxServiceMenuInfo serviceMenuInfo = {};

/*******************************************************************************************************************************
*                                                       SdapIndicationHandler
*
* This call-back function is registered for the SDP protocol, any events raised by SDP protocol causes this call-back function
* executed with the associated event and parameters.
*
* \param stack         - Local device stack handle
* \param serviceHandle - Profile/service handle  
* \param messageID     - Indication ID
* \param params        - Void pointer to the indication parameters
* \param errorCode     - Error code returned by stack
*
* \return boolean      - TRUE If the call-back function handles indication or indication with *_COMPLETE.
*                        Otherwise, return FALSE
*
*******************************************************************************************************************************/
boolean SdapIndicationHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    (void*)stack;
    (void*)serviceHandle;
    (void)errorCode;
    
    if (CLX_SDAP_DISCOVER_REMOTE_SERVICES_COMPLETE == messageID)
    {
        struct ClxSdapDiscoverRemoteServicesComplete*  arg             = (struct ClxSdapDiscoverRemoteServicesComplete*)params;
        ClxSize                                 serviceCount    = *(arg->numberOfDiscoveredServices);
        
        for (u4 i = 0; i < serviceCount; i++)
        {
            clxConsoleUIEngineText ("%u. %s\n", i+1, servicesList[(u1)arg->serviceInfoList[i].type]);
        }

        clxConsoleUIEngineText ("\n");

        return TRUE;
    }

    return FALSE;
}

/*******************************************************************************************************************************
*                                                       discoverServices
*
* Create the SDP handle, and send a SDP request to the remote device, and inform the user of the available services
* in the remote device and close the SDP handled.
*
* \param stack      - ClarinoxBlue stack
* \param deviceId   - Device ID of the remote device that is to be connected
* \param sdap       - Profile handle
*
*******************************************************************************************************************************/
void discoverServices(ClxStack stack, ClxDeviceId deviceId, ClxHandle sdap)
{
    (void*)stack;
    u4 read = 0;
    ClxError ret = CLX_FAIL;

    /* Object to store the discovered services details */
    struct ClxBlueServiceInfo services[30];

    clxConsoleUIEngineText ("\nDiscovering Services . . .\n");

    /* Discovers available services from remote device by using device ID */
    ret = clxSdapDiscoverRemoteServices(sdap, deviceId, services, 20, &read, CLX_SDAP_FILTER_ALL, TRUE);

    if (ret != CLX_SUCCESS)
    {
        clxConsoleUIEngineText ("\nError : %s\n", clxGetErrorCodeText(ret));
    }
    else if (read == 0)
    {
        clxConsoleUIEngineText ("\nNo service discovered\n", clxGetErrorCodeText(ret));
    }
    else
    {
        clxConsoleUIEngineText ("\nThe following services are supported:\n\n", clxGetErrorCodeText(ret));

        for (u4 i = 0; i < read; i++)
        {
            /* Prints the received services name on console */
            clxConsoleUIEngineText ("%u. %s\n", i+1, servicesList[(u1)services[i].type]);
        }
    }
    clxConsoleUIEngineText ("\n");
}

/*******************************************************************************************************************************
*                                                    displayDIServiceInfo
*
* Function to display the Device ID profile specific parameter values
*
*******************************************************************************************************************************/
void displayDIServiceInfo()
{
    clxConsoleUIEngineText ("DID Specification ID     : 0x%.4x\n", serviceMenuInfo.sdpDidDetails.sdpDiSpecificationId.paramValue);
    clxConsoleUIEngineText ("DID Vendor ID            : 0x%.4x\n", serviceMenuInfo.sdpDidDetails.sdpDiVendorId.paramValue);
    clxConsoleUIEngineText ("DID Product ID           : 0x%.4x\n", serviceMenuInfo.sdpDidDetails.sdpDiProductId.paramValue);
    clxConsoleUIEngineText ("DID Version              : 0x%.4x\n", serviceMenuInfo.sdpDidDetails.sdpDiVersion.paramValue);
    clxConsoleUIEngineText ("DID Primary Record       : 0x%.2x\n", serviceMenuInfo.sdpDidDetails.sdpDiPrimaryRecord.paramValue);
    clxConsoleUIEngineText ("DID Vendor ID Source     : 0x%.4x\n", serviceMenuInfo.sdpDidDetails.sdpDiVendorIdSource.paramValue);
}

/*******************************************************************************************************************************
*                                                    sdapMenuFunction
*
* Provide the SDAP UI menu.
*
* \param stack      - ClarinoxBlue stack
* \param deviceId   - Device ID of the remote device that is to be connected
*
*******************************************************************************************************************************/
void sdapMenuFunction(ClxStack stack, ClxDeviceId deviceId)
{
    ClxError ret    = CLX_FAIL;
    
    /* In case of a single context allocated for all profiles, block must be TRUE always */
    boolean block   = TRUE;
    ClxHandle sdap  = NULL;

    /* Create SDAP profile handle, This handle to be passed for other SDAP API commands */
    sdap = clxSdapCreate(stack, SdapIndicationHandler);
    if (sdap == NULL)
    {
        clxConsoleUIEngineText ("\nSDAP creation failed\n");
        return;
    }
    
    while (TRUE)
    {
        const s1* menu = "Discover services in remote device\0"
                         "Get Device ID details from remote device\0"
                         "Allow the remote device to discover services\0"
                         "Return to previous menu\0"; 
     
        u4 ch = clxConsoleUIEngineShowMenu("SDAP Menu", menu, ClxSdapMenu_Total - 1);
        
        switch (ch)
        {
            case ClxSdapMenu_DiscoverDevices:
            {
                discoverServices(stack, deviceId, sdap);
            }
            break;

            case ClxSdapMenu_GetDeviceDetails:
            {
                /**
                Initialize the configuration items for which you want the details. 
                The stack discovers these items from remote device and fills in the values which can be accessed 
                after the command execution is success.
                */
                clxConfigInitParamsList(&serviceMenuInfo.serviceInfo, NULL, NULL);
                clxConfigInitUnsignedParam(&serviceMenuInfo.sdpDidDetails.sdpDiSpecificationId, "DiSpecificationId", 0, &serviceMenuInfo.serviceInfo);
                clxConfigInitUnsignedParam(&serviceMenuInfo.sdpDidDetails.sdpDiVendorId,        "DiVendorId",        0, &serviceMenuInfo.serviceInfo);
                clxConfigInitUnsignedParam(&serviceMenuInfo.sdpDidDetails.sdpDiProductId,       "DiProductId",       0, &serviceMenuInfo.serviceInfo);
                clxConfigInitUnsignedParam(&serviceMenuInfo.sdpDidDetails.sdpDiVersion,         "DiVersion",         0, &serviceMenuInfo.serviceInfo);
                clxConfigInitUnsignedParam(&serviceMenuInfo.sdpDidDetails.sdpDiPrimaryRecord,   "DiPrimaryRecord",   0, &serviceMenuInfo.serviceInfo);
                clxConfigInitUnsignedParam(&serviceMenuInfo.sdpDidDetails.sdpDiVendorIdSource,  "DiVendorIdSource",  0, &serviceMenuInfo.serviceInfo);

                /* Discover information about Device ID profile */
                ret = clxSdapGetRemoteServiceInformation(sdap, deviceId, ClxSdapServiceClassID_ClxDeviceID, &serviceMenuInfo.serviceInfo, block);
                if (CLX_SUCCESS == ret)
                {
                    clxConsoleUIEngineText ("\nSDAP get remote service details success..\n");
                    displayDIServiceInfo();
                }
                else
                {
                    clxConsoleUIEngineText ("\nSDAP get remote service details returned with error code: %s\n", clxGetErrorCodeText(ret));
                }
            }
            break;

            case ClxSdapMenu_AllowDeviceToDiscover:
            {
                ret = clxGapSetConnectability(stack, TRUE, 2048, 400, TRUE);
                if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                {
                    clxConsoleUIEngineText("\nclxGapSetConnectability command failed with the result: %s\n", clxGetErrorCodeText(ret));
                }

                ret = clxGapSetDiscoverability(stack, TRUE, 2048, 1800, TRUE);
                if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                {
                    clxConsoleUIEngineText("\nclxGapSetDiscoverability command failed with the result: %s\n", clxGetErrorCodeText(ret));
                }

            }
            break;

            case ClxSdapMenu_ReturnToPreviousMenu:
            {
                /* Disable the Connectability and Discoverability for a better performance */
                ret = clxGapSetConnectability(stack, FALSE, 2048, 400, TRUE);
                if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                {
                    clxConsoleUIEngineText("\nclxGapSetConnectability command failed with the result: %s\n", clxGetErrorCodeText(ret));
                }

                ret = clxGapSetDiscoverability(stack, FALSE, 2048, 1800, TRUE);
                if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                {
                    clxConsoleUIEngineText("\nclxGapSetDiscoverability command failed with the result: %s\n", clxGetErrorCodeText(ret));
                }

                ret = clxCloseHandle(sdap);
                if (CLX_SUCCESS != ret)
                {
                    clxConsoleUIEngineText ("SDAP close service failed: %s\n", clxGetErrorCodeText(ret));
                }

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

/*******************************************************************************************************************************
*                                                     sdapMessageHandler
*
* This callback function is registered for the PAN profile, any events raised by PAN profile, causes this 
* callback function executed with the associated event and parameters. Executed from the stack thread context
*
* \param stack         - Local device stack handle
* \param serviceHandle - Profile/service handle  
* \param messageID     - Indication ID
* \param params        - Void pointer to the indication parameters
* \param errorCode     - Error code returned by stack
*
* \return boolean      - TRUE If the call-back function handles indication or indication with *_COMPLETE.
*                        Otherwise, return FALSE
*
*******************************************************************************************************************************/
boolean sdapMessageHandler(ClxServiceID serviceID, u2 indicationID, const void* params, ClxError errorCode)
{
    (void)serviceID;

    switch (indicationID)
    {
        /**
        These (below indications with *_COMPLETE) are command complete indications received when the corresponding API commands are called 
        in non-blocking mode. The output parameters can be accessed from argument "params".
        */
        case CLX_SDAP_GET_REMOTE_SERVICE_INFORMATION_COMPLETE:
        {
            clxConsoleUIEngineText ("CLX_SDAP_GET_REMOTE_SERVICE_INFORMATION_COMPLETE: %s\n", clxGetErrorCodeText(errorCode));
            if (CLX_SUCCESS == errorCode)
            {
                displayDIServiceInfo();
            }
        }
        break;

        case CLX_SDAP_DISCOVER_REMOTE_SERVICES_COMPLETE:
        {
            struct ClxSdapDiscoverRemoteServicesComplete*  arg             = (struct ClxSdapDiscoverRemoteServicesComplete*)params;
            ClxSize                                 serviceCount    = *(arg->numberOfDiscoveredServices);
            
            for (u4 i = 0; i < serviceCount; i++)
            {
                /* Prints the received services name on console */
                clxConsoleUIEngineText ("%u. %s\n", i+1, servicesList[(u1)arg->serviceInfoList[i].type]);
            }
        
            clxConsoleUIEngineText ("\n");
        }
        break;

        default:
        {
            return FALSE;
        }
        break;
    }

    return TRUE;
}

