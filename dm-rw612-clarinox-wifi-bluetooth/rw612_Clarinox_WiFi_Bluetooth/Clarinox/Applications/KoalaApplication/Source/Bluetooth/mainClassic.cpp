/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                mainClassic.cpp
* Description         This file provides a main menu of the application with
*                     the options of initialization and termination of the Classic
*                     Bluetooth stack and Bluetooth connectivity options.
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

// _____________________________________________________________________________
//
#undef  CLX_MODULE_ID
#define CLX_MODULE_ID  20123
// _____________________________________________________________________________
//

#if defined(CLX_BT_CLASSIC)
#include "ClxBsp.h"
#include "ClarinoxBlueConst.h"
#include "ClarinoxBlue.h"
#include "ClxList.h"

#include "Gap.Api.h"
#include "mainBluetooth.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
extern void clxPrintMemoryStatistics();
#ifdef __cplusplus
}
#endif

/* Maximum number of remote devices to pair and store details of them */
#define MAX_NUMBER_OF_PAIRED_DEVICES                20

/* Enable fixed pin code during pairing authentication */
#define FIXED_PIN_CODE

/* Macro to accept the GAP connection without user Intervention */
#define AUTO_ACCEPT_CONNECTION_REQUEST

/* Description of ClxMajorDeviceClass which is used to display the supported device class of remote device */
const s1* deviceClassList[] = {"Miscellaneous Equipment",
                               "Computer",
                               "Phone",
                               "LAN Device",
                               "AudioVideo",
                               "Peripheral",
                               "Imaging Device",
                               "Wearable Device",
                               "Toy",
                               "Health Equipment"};

/* Menu options used to invoke SPP main Menu */
typedef enum ClxAppClassicMenuOptions_Enum
{
    ClxAppClassicMenuOptions_SearchForDevices           = 1,
    ClxAppClassicMenuOptions_WaitForIncomingConnection,
    ClxAppClassicMenuOptions_ConnectPairedDevice,
    ClxAppClassicMenuOptions_ConnectedDeviceMenu,
    ClxAppClassicMenuOptions_DeletePairedDeviceInfo,
    ClxAppClassicMenuOptions_DeleteAllPairedDevices,
    ClxAppClassicMenuOptions_Disconnect,
#if defined(CLX_SCO_BRIDGE)
    ClxAppClassicMenuOptions_ScoBridgeMenu,
#endif
    ClxAppClassicMenuOptions_ReturnToPreviousMenu,
    ClxAppClassicMenuOptions_TotalOptions
}ClxAppClassicMenuOptions;

/* 
Variables associated with Classic object 
*/
typedef struct ClxClassicInstanceInfoStruct
{
    ClxDeviceId     connectedDeviceId;      /* Current connected remote device id                                   */
    ClxSemaphore    connectionSemaphore;    /* Synchronization for connection and termination                       */
    boolean         isClassicInitialized;   /* Indicate if the classic part of stack init are initialized or not    */
    ClxDeviceDetail lastPairedDeviceDetail; /* Details of the last successfully paired remote device */
}ClxClassicInstanceInfo;

/* Structure with variables required for Classic instance */
ClxClassicInstanceInfo classicInfo = {};

/* Initialize BSP and UI interface, and provide the main UI menu. */
void classicMenu(ClxStack stack, const s1* deviceName);

/* Vendor Specific command implementation */
void clxVendorSpecific(const u1* x, u4 y);

/*******************************************************************************************************************************
*                                                classicStackMessageHandler
*
* This call-back function is registered for the Classic GAP profile, 
* any events raised by GAP profile causes this call-back function executed with
* the associated event and parameters 
*
* \param stack         - Local device stack handle
* \param serviceHandle - Profile/service handle
* \param messageID     - Indication id
* \param params        - Void pointer to the indication parameters
* \param errorCode     - Contains the error code
*
* \return boolean      - TRUE If the call-back function handles indication or indication with *_COMPLETE.
*                        Otherwise, it will return FALSE
* \note                - The API should be called in non blocking mode.
*
*******************************************************************************************************************************/
boolean classicStackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    (void)serviceHandle;

    ClxError err = CLX_FAIL;

    /* Indication of each inquiry cycle completion in the periodic inquiry mode */
    if (messageID == CLX_GAP_START_INQUIRY_COMPLETE)
    {
        return true;
    }
    /* Indication of each inquiry cycle completion in the limited inquiry mode */
    else if(messageID == CLX_GAP_START_LIMITED_INQUIRY_COMPLETE)
    {
        return true;
    }
    /* Indication of stop inquiry completed from the local device */
    else if((messageID == CLX_GAP_STOP_INQUIRY_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
        ClxConsoleUIEngine::text("\nStop inquiry failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    /* Indication of a new device being found */
    else if (messageID == CLX_GAP_DEVICE_DISCOVERED_INDICATION)
    {
        ClxGapDeviceDiscoveredIndication* arg = (ClxGapDeviceDiscoveredIndication*)params;
        const s1* deviceClass = "Uncategorized Device";
        
        if (arg->deviceDetail.majorClassOfDevice != MJ_UNCATEGORIZED)
        {
            deviceClass = (s1*)deviceClassList[arg->deviceDetail.majorClassOfDevice];
        }
        
        ClxConsoleUIEngine::text("\nDevice Discovered : %s (%s)",
            arg->deviceDetail.deviceName,
            deviceClass);
    }
    /* Indication of a legacy pin code request during pairing operation */
    else if (messageID == CLX_GAP_PIN_CODE_REQUEST_INDICATION)
    {
        ClxGapPinCodeRequestIndication* arg = (ClxGapPinCodeRequestIndication*)params;
#if defined(FIXED_PIN_CODE)
        s1 pincode[5] = "0000";
#else
        s1 pincode[16];
        ClxConsoleUIEngine::inputBox ("\nEnter PIN code : ", pincode, sizeof(pincode));
#endif

        /* Sends pin code response for pairing operation */
        err = clxGapPinCodeRequestReply(stack, arg->deviceDetail.deviceId, (const u1*)pincode, strlen(pincode), FALSE);
        if ((CLX_SUCCESS != err) && (CLX_ERROR_COMPLETION_PENDING != err))
        {
            ClxConsoleUIEngine::text("\nPincode request reply failed with error: %s\n", clxGetErrorCodeText(err));
        }
    }
    /* Indication of a Simple Secure Pairing pass key request during pairing operation */
    else if (messageID == CLX_GAP_USER_PASSKEY_REQUEST_INDICATION)
    {
        ClxGapUserPasskeyRequestIndication* arg = (ClxGapUserPasskeyRequestIndication*)params;

         /* Variables to store the passkey details */
        u4 passkey;
        s1 passkeyStr[10];
        ClxConsoleUIEngine::inputBox ("\nEnter User Passkey (numeric) : ", passkeyStr, sizeof(passkeyStr));
        (void)sscanf(passkeyStr, "%u", &passkey);

        /* Sends user provided passkey to the remote device */
        err = clxGapUserPasskeyRequestReply(stack, arg->deviceDetail.deviceId, TRUE, passkey, FALSE);        
        if ((CLX_SUCCESS != err) && (CLX_ERROR_COMPLETION_PENDING != err))
        {
            ClxConsoleUIEngine::text("\nPasskey request reply failed with error: %s\n", clxGetErrorCodeText(err));
        }
    }
    /* Indication of a Simple Secure Pairing pass key notification during pairing operation */
    else if (messageID == CLX_GAP_USER_PASSKEY_NOTIFICATION_INDICATION)
    {
        ClxGapUserPasskeyNotificationIndication* arg = (ClxGapUserPasskeyNotificationIndication*)params;
        
        ClxConsoleUIEngine::text ("\nPasskey for the device \"%08X%04X\" %s is \"%u\"\n",
                                  arg->deviceDetail.deviceId.msb,arg->deviceDetail.deviceId.lsb, 
                                  arg->deviceDetail.deviceName, arg->value);
    }
    /* Indication of a Simple Secure Pairing pass key confirmation request during pairing operation */
    else if (messageID == CLX_GAP_USER_CONFIRMATION_REQUEST_INDICATION)
    {
        ClxGapUserConfirmationRequestIndication* arg = (ClxGapUserConfirmationRequestIndication*)params;
        ClxConsoleUIEngine::text ("\n Please confirm the passkey \"%u\" to connect to \"%08X%04X\" %s?",
                                  arg->value,
                                  arg->deviceDetail.deviceId.msb,arg->deviceDetail.deviceId.lsb,
                                  arg->deviceDetail.deviceName);
        s1 ch = ClxConsoleUIEngine::messageBox("", "yYnN", 4);
        if ((ch == 'y') || (ch == 'Y'))
        {
            /* Local device confirms the authentication request */
            err = clxGapUserConfirmationRequestReply(stack, arg->deviceDetail.deviceId, TRUE, FALSE);
            if ((CLX_SUCCESS != err) && (CLX_ERROR_COMPLETION_PENDING != err))
            {
                ClxConsoleUIEngine::text("\nUser confirmation request reply failed with error: %s\n", clxGetErrorCodeText(err));
            }
        }
        else
        {
            /* Local device rejects the authentication request */
            err = clxGapUserConfirmationRequestReply(stack, arg->deviceDetail.deviceId, FALSE, FALSE);
            if ((CLX_SUCCESS != err) && (CLX_ERROR_COMPLETION_PENDING != err))
            {
                ClxConsoleUIEngine::text("\nUser confirmation request reply failed with error: %s\n", clxGetErrorCodeText(err));
            }
        }
    }
    /* Indication of a remote connection authorization */
    else if (messageID == CLX_GAP_INCOMING_CONNECTION_REQUEST_INDICATION)
    {
        ClxGapIncomingConnectionRequestIndication* arg = (ClxGapIncomingConnectionRequestIndication*)params;

#if defined(AUTO_ACCEPT_CONNECTION_REQUEST)
        s1 ch = 'Y';
#else
#if 1
        ClxConsoleUIEngine::text("\nA connection request received from device (%08X%04X) %s. Accept?",
                                 arg->deviceDetail.deviceId.msb, arg->deviceDetail.deviceId.lsb, 
                                 arg->deviceDetail.deviceName);
#else
        ClxConsoleUIEngine::text("\nA connection request received from %s.Accept(y), Reject(n) or don't respond(x)", 
            arg->deviceDetail.deviceName);
#endif

        s1 ch = ClxConsoleUIEngine::messageBox("", "yYnNxX", 6);
#endif
        if ((ch == 'y') || (ch == 'Y'))
        {
            /* Local device accepts the remote ACL connection request */
            classicInfo.connectedDeviceId = arg->deviceDetail.deviceId;
            err = clxGapAcceptConnectionRequest(stack, arg->deviceDetail.deviceId, FALSE);
            if ((CLX_SUCCESS != err) && (CLX_ERROR_COMPLETION_PENDING != err))
            {
                ClxConsoleUIEngine::text("\nAccept connection request failed with error: %s\n", clxGetErrorCodeText(err));
            }
        }
        else if((ch == 'n') || (ch == 'N'))
        {
            /* Local device rejects the remote ACL connection request */
            err = clxGapRejectConnectionRequest(stack, arg->deviceDetail.deviceId, ClxUnspecified, FALSE);
            if ((CLX_SUCCESS != err) && (CLX_ERROR_COMPLETION_PENDING != err))
            {
                ClxConsoleUIEngine::text("\nReject connection request failed with error: %s\n", clxGetErrorCodeText(err));
            }
            else
            {
                ClxConsoleUIEngine::text("\nA connection request rejected from %08X%04X %s",
                    arg->deviceDetail.deviceId.msb, arg->deviceDetail.deviceId.lsb,
                    arg->deviceDetail.deviceName);
            }
        }
        else if((ch == 'x') || (ch == 'X'))
        {
            ClxConsoleUIEngine::text("\nConnection request not responded %08X%04X %s",
                                     arg->deviceDetail.deviceId.msb, arg->deviceDetail.deviceId.lsb,
                                     arg->deviceDetail.deviceName);
        }
    }
    /* Indicated completion of pairing procedure */
    else if (messageID == CLX_GAP_PAIRING_COMPLETE_INDICATION)
    {
        ClxGapPairingCompleteIndication* arg = (ClxGapPairingCompleteIndication*)params;
        if (arg->status == 0)
        {
            ClxConsoleUIEngine::text("Pairing completed\n");
            ClxConsoleUIEngine::text("Remote Device Name    : %s\n", arg->deviceDetail.deviceName);
            ClxConsoleUIEngine::text("Remote Device ID      : %08X%04X\n",
                arg->deviceDetail.deviceId.msb, arg->deviceDetail.deviceId.lsb);
            
            if (FALSE == arg->isBonded)
            {
                ClxConsoleUIEngine::text("Bonding details stored: ");
                ClxConsoleUIEngine::text("No\n", arg->isBonded);

                /*
                If isBonded is FALSE, this means the remote device doesn't support storing pairing information.
                Use option 0 in paired device menu to connect to this newly paired device.
                */

                ClxConsoleUIEngine::text("\nNote: Remote device doesn't accept storing the pairing information.\n");
                ClxConsoleUIEngine::text("In paired device menu, use option 0 to connect to this newly paired device!\n");
            }      
        }
        else
        {
            ClxConsoleUIEngine::text("Pairing failed with status : %s\n", clxGetErrorCodeText(arg->status));
        }
       
        /* 
        We store the pairing device details temporarily as the last paired device, to list while connecting. 
        If isBonded is FALSE, then the details are temporarily available and not available in non-volatile memory 
        */
        if (CLX_SUCCESS == arg->status)
        {
            memcpy(&classicInfo.lastPairedDeviceDetail, &arg->deviceDetail, sizeof(ClxDeviceDetail));
        }
        else
        {
            /* Reset the already stored last paired device detail and the current pairing has failed */
            memset(&classicInfo.lastPairedDeviceDetail, 0, sizeof(ClxDeviceDetail));
        }
    }
    /* This indication is received when the physical (ACL) link to a remote device has failed/disconnected */
    else if(messageID == CLX_GAP_LINK_DISCONNECTION_INDICATION)
    {
        ClxGapLinkDisconnectionIndication* arg = (ClxGapLinkDisconnectionIndication*)params;
        ClxConsoleUIEngine::text("\nPhysical link disconnected with disconnection reason : %s\n", clxGetErrorCodeText(0x2700 + arg->disconnectionReason));   
    }
    /* Indication of accepting an incoming connection */
    else if (messageID == CLX_GAP_ACCEPT_CONNECTION_REQUEST_COMPLETE)         
    {
        if (errorCode != CLX_SUCCESS)
        {
            classicInfo.connectedDeviceId = CLX_INVALID_DEVICE_ID;
            ClxConsoleUIEngine::text("\nFailed to accept incoming ACL connection\n");
        }
        else
        {
            clxReleaseSemaphore(classicInfo.connectionSemaphore);
            ClxConsoleUIEngine::text("\nRequest accepted\n");
        }
    }
    /* Indication of confirming or rejecting the authentication request */
    else if ((messageID == CLX_GAP_USER_CONFIRMATION_REQUEST_REPLY_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
        ClxConsoleUIEngine::text("\nUser confirmation request reply failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    /* Indication of pin code response during a pairing operation */
    else if ((messageID == CLX_GAP_PIN_CODE_REQUEST_REPLY_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
        ClxConsoleUIEngine::text("\nPincode request reply failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    /* Indication of rejecting an incoming connection */
    else if ((messageID == CLX_GAP_REJECT_CONNECTION_REQUEST_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
        ClxConsoleUIEngine::text("\nReject connection request failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    /* Indication of passkey response during a pairing operation */
    else if ((messageID == CLX_GAP_USER_PASSKEY_REQUEST_REPLY_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
        ClxConsoleUIEngine::text("\nPasskey request reply failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    /**  
    These (below indications with *_COMPLETE) are command complete indications received when the corresponding API commands are called 
    in non-blocking mode. The output parameters can be accessed from argument "params".
    */
    else if ((messageID == CLX_GAP_INITIATE_BONDING_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
         ClxConsoleUIEngine::text("\nInitiate bonding failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if ((messageID == CLX_GAP_SET_DISCOVERABILITY_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
        ClxConsoleUIEngine::text("\nSet discoverability failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if ((messageID == CLX_GAP_SET_CONNECTABILITY_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
        ClxConsoleUIEngine::text("\nSet connectability failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if(messageID == CLX_GAP_DELETE_PAIRED_DEVICE_INFO_COMPLETE)
    {
        if (CLX_SUCCESS == errorCode)
        {
            ClxConsoleUIEngine::text("\nPairing information deleted!\n");
        }
        else
        {
            ClxConsoleUIEngine::text("\nDelete pairing information failed with error: %s\n", clxGetErrorCodeText(errorCode));
        }
    }
    else if(messageID == CLX_GAP_DELETE_ALL_PAIRED_DEVICES_INFO_COMPLETE)
    {
        if (CLX_SUCCESS == errorCode)
        {
            ClxConsoleUIEngine::text("\nAll pairing information deleted!\n");
        }
        else
        {
            ClxConsoleUIEngine::text("\nDelete all pairing information failed with error: %s\n", clxGetErrorCodeText(errorCode));
        }
    }
    else if(messageID == CLX_GAP_DISCONNECT_PHYSICAL_LINK_COMPLETE)
    {
        if (CLX_SUCCESS == errorCode)
        {
            ClxConsoleUIEngine::text("\nACL disconnected\n");
        }
        else
        {
            ClxConsoleUIEngine::text("\nACL disconnection failed with error: %s\n", clxGetErrorCodeText(errorCode));
        }
    }
    else if ((messageID == CLX_GAP_GET_DISCOVERED_DEVICE_BY_INDEX_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
        ClxConsoleUIEngine::text("\nGet discovered device by index failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if ((messageID == CLX_GAP_GET_PAIRED_DEVICE_BY_INDEX_COMPLETE) && (CLX_SUCCESS != errorCode))
    {
        ClxConsoleUIEngine::text("\nGet paired device by index failed with error: %s\n", clxGetErrorCodeText(errorCode));
    }
    else
    {
        /* This indication is not known for any of the profiles */
        return FALSE;
    }

    return TRUE;
}

/*******************************************************************************************************************************
*                                                discoverDevices
*
* Perform inquiry, discover BT devices in range, display them by name on the screen, continue searching
* till user presses C or c to cancel the search. Present a menu the user to select the device to pair with, 
* and then initiate bonding procedure with the selected device.
*
* \param stack      - ClarinoxBlue stack
* \param liacMode   - Inquiry Mode
*******************************************************************************************************************************/
void discoverDevices(ClxStack stack, boolean liacMode)
{
    s1              ch      = 0;
    u4              index   = 0;
    ClxError        err     = CLX_FAIL;

    /* Object to store the details of the discovered device */
    ClxDeviceDetail device;

    /* Buffer to store the discovered device IDs after completion of inquiry */
    static ClxDeviceId deviceList[MAX_NUMBER_OF_PAIRED_DEVICES];

    if(!stack)
    {
        ClxConsoleUIEngine::text ("\nStack hasn't been created!\n");
        return;
    }

    /* Variable to configure the filtering type for Inquiry function */
    struct ClxGapInquiryFilter filter;
    
    /* Set the inquiry filter */
    filter.filterMask = ClxNoInquiryFilter;
    filter.serviceClass = ClxDeviceServiceClass(ST_AUDIO | ST_RENDERING);
    filter.majorClass = ClxMajorDeviceClass(0);
    filter.minorClass = 0;

    /* 
    Start inquiry in the mode required by the user, most devices use General Inquiry Mode
    */
    if (liacMode)
    {
        err = clxGapStartLimitedInquiry(stack, &filter, gBlock);
        if (CLX_SUCCESS != err && CLX_ERROR_COMPLETION_PENDING != err)
        {
            ClxConsoleUIEngine::text("\nStart limited inquiry failed with error: %s\n", clxGetErrorCodeText(err));
        }
    }
    else 
    {
        err = clxGapStartInquiry(stack, &filter, FALSE, 10, 9, 8, gBlock);
        if (CLX_SUCCESS != err && CLX_ERROR_COMPLETION_PENDING != err)
        {
            ClxConsoleUIEngine::text("\nStart inquiry failed with error: %s\n", clxGetErrorCodeText(err));
        }
    }

    ClxConsoleUIEngine::text("\nAt any time, press C to stop searching.\n");

    do
    {
        ch = ClxConsoleUIEngine::messageBox("Enter c to stop searching", "cC", 2);
    }while ((ch != 'c') && (ch != 'C'));
    
    /* Stop inquiry, so that free the radio from inquiry */
    err = clxGapStopInquiry(stack, gBlock);
    if (CLX_SUCCESS != err && CLX_ERROR_COMPLETION_PENDING != err)
    {
        ClxConsoleUIEngine::text("\nStop inquiry failed with error: %s\n", clxGetErrorCodeText(err));
    }
   
    while (TRUE)
    {
        /*
        Present the list of devices discovered during the inquiry operation to the user
        */
        err = clxGapGetDiscoveredDeviceByIndex(stack, &device, index, gBlock);

        if (err == CLX_SUCCESS)
        {
            ClxConsoleUIEngine::text ("%u. %s(RSSI: %ddBm)\n", index + 1, device.deviceName, device.rssi);

            deviceList[index] = device.deviceId;
            ++index;
        }
        else if (err == CLX_ERROR_INVALID_COMMAND_ARGUMENT)
        {
            break;
        }
        else
        {
            ClxConsoleUIEngine::text("\nFailed to retrieve the discovered device. Error: %s\n", clxGetErrorCodeText(err));
            break;
        }
    }

    if (index)
    {
        /* Variables to select a device for pairing process */
        s1 input[5];
        u4 selection = 0;
        ClxConsoleUIEngine::text("%u. Return\n", index + 1);

        while ((selection < 1) || (selection > index + 1))
        {
            ClxConsoleUIEngine::inputBox ("\nSelect a device to pair : ", input, sizeof(input));

            selection = (u4)atoi(input);
        }
        
        if (selection < index + 1)
        {
            /*
            Pair with the selected device; this will potentially cause some callback functions
            depending on the authentication mode (i.e. pincode entry or passcode verification etc)
            */
            /* Security level for bonding process */

            ClxConsoleUIEngine::text("\nPairing with the remote device . . .\n");
            ClxSecurityRequirement securityRequirement = ClxMediumSecurity;
            err = clxGapInitiateBonding(stack, deviceList[selection - 1], securityRequirement, gBlock);
            if (CLX_SUCCESS != err && CLX_ERROR_COMPLETION_PENDING != err)
            {
                /* Reset the already stored last paired device detail and the current pairing has failed */
                memset(&classicInfo.lastPairedDeviceDetail, 0, sizeof(ClxDeviceDetail));
                ClxConsoleUIEngine::text("\nPairing failed with error: %s\n", clxGetErrorCodeText(err));
            }
        }
    }
}

/*******************************************************************************************************************************
*                                                       selectPairedDevice
*
* Retrieve the list of paired devices, and display it to the user.
*
* \param stack          - ClarinoxBlue stack
*
* \return ClxDeviceId   - Remote Bluetooth device ID
*
*******************************************************************************************************************************/
ClxDeviceId selectPairedDevice(ClxStack stack)
{
    /* Buffer to store the number of paired devices */
    static ClxDeviceId deviceList[MAX_NUMBER_OF_PAIRED_DEVICES];

    /* Variable to store the device ID which is retrieved from paired devices list based on user selection */
    ClxDeviceId selectedDeviceID = CLX_INVALID_DEVICE_ID;

    ClxError err    = CLX_FAIL;
    u4       index  = 0;

    /* If the last pair device available, make it TRUE, so can be used in future menu operations */
    boolean  isLastPairedDeviceAvailable = FALSE;


    /* Object to store the details of the paired devices */
    ClxDeviceDetail device;

    /* 
    If last paired device details are stored (valid) then list it as 0th device. 
    We do this as some remote device don't with to store bonding details after pairing. In such case, 
    the details are temporarily available during the lifetime of this instance/connection and not retained beyond that.
    */
    if (CLX_IS_DEVICE_ID_VALID(classicInfo.lastPairedDeviceDetail.deviceId) == TRUE)
    {
        ClxConsoleUIEngine::text ("0. Connect to last paired remote device\n");
        isLastPairedDeviceAvailable = TRUE;
    }

    while (index < MAX_NUMBER_OF_PAIRED_DEVICES)
    {
        /*
        Present the list of devices discovered during the inquiry operation to the user
        */
        err = clxGapGetPairedDeviceByIndex(stack, &device, index, gBlock);

        if (err == CLX_SUCCESS)
        {
            deviceList[index] = device.deviceId;

            ClxConsoleUIEngine::text ("%u. %s\n", index + 1, device.deviceName);

            ++index;
        }
        else if (err == CLX_ERROR_DATABASE_RECORD_NOT_FOUND)
        {
            if ((index) || (isLastPairedDeviceAvailable))
            {
                ClxConsoleUIEngine::text ("%u. %s\n", index + 1, "Return to Previous Menu");
            }
            break;
        }
        else
        {
            if ((index) || (isLastPairedDeviceAvailable))
            {
                ClxConsoleUIEngine::text ("%u. %s\n", index + 1, "Return to Previous Menu");
            }

            ClxConsoleUIEngine::text("\nFailed to retrieve the paired device. Error: %s\n", clxGetErrorCodeText(err));          
            break;
        }
    }

    if ((index) || (isLastPairedDeviceAvailable))
    {
        s1 s_str[5];

        u4 selection = 0;
        
        do
        {
            selection = 0;

            if (selection <= index)
            {
                ClxConsoleUIEngine::inputBox ("\nSelect a device : ", s_str, sizeof(s_str));
                selection = (u4)atoi(s_str);
            }
            else if (selection == (index + 1))
            {
                break;
            }
        }while ((selection > (index + 1)));

        if (selection != (index + 1))
        {
            if (0 == selection)
            {
                /* If this is a selection of last paired device and is valid */
                if (isLastPairedDeviceAvailable)
                {
                    selectedDeviceID = classicInfo.lastPairedDeviceDetail.deviceId;
                }
                else
                {
                    ClxConsoleUIEngine::text("\nInvalid selection\n");
                }
            }
            else
            {
                /* Retrieves the required paired device details from stack, based on user selection */
                err = clxGapGetPairedDeviceByIndex(stack, &device, selection-1, gBlock);
                if (CLX_SUCCESS != err && CLX_ERROR_COMPLETION_PENDING != err)
                {
                    ClxConsoleUIEngine::text("\nFailed to retrieve the paired device. Error: %s\n", clxGetErrorCodeText(err));
                }
                selectedDeviceID = deviceList[selection-1];
            }
        }
    }
    else
    {
        ClxConsoleUIEngine::text("There are no paired devices!");
    }

    return selectedDeviceID;
}

/******************************************************************************************************************************************
*                                                       initializeClassic
*
* Initializes ClarinoxBlue classic profiles with configuration parameters for Bluetooth stack.
*
* \param stack    - ClarinoxBlue stack.
*
* \return void
*
******************************************************************************************************************************************/
void initializeClassic(ClxStack stack)
{
    if (FALSE == classicInfo.isClassicInitialized)
    {
        /*
        Initialize the Bluetooth stack with the parameters; params, event call-back function; stackMessageHandler
        and the exception handler; userExceptionHandler 
        */
        if(NULL == classicInfo.connectionSemaphore)
        {
            classicInfo.connectionSemaphore  = clxCreateSemaphore(0);
        }

        /*
        Create handles for all the supported profiles for this application
        */
        initializeClassicProfiles(stack);

        classicInfo.isClassicInitialized    = TRUE;
        classicInfo.connectedDeviceId       = CLX_INVALID_DEVICE_ID;
        memset(&classicInfo.lastPairedDeviceDetail, 0, sizeof(ClxDeviceDetail));
    }
    else
    {
        ClxConsoleUIEngine::text("\nClassic is already initialized\n");
    }
}

/******************************************************************************************************************************************
*                                                       terminateClassic
*
* De-Initializes ClarinoxBlue classic profiles and resources.
*
******************************************************************************************************************************************/
void terminateClassic()
{
    if (classicInfo.isClassicInitialized)
    {
        /*
        Close the created profile handles before terminating
        */
        terminateClassicProfiles();

        /* 
        Terminate the stack and all the components and resources. 
        The host is disconnected from the stack at this point
        */
        clxDeleteSemaphore(classicInfo.connectionSemaphore);
        classicInfo.connectionSemaphore = NULL;
        classicInfo.isClassicInitialized = FALSE;
    }
}

/*******************************************************************************************************************************
*                                                       Main
*
* Initialize BSP and UI interface, and provide the main UI menu.
*
* \param stack      - ClarinoxBlue stack
* \param deviceName - Name string of the remote device
*
*******************************************************************************************************************************/
void classicMenu(ClxStack stack, const s1* deviceName)
{
    if (stack == NULL)
    {
        ClxConsoleUIEngine::text("\nClarinox Stack has to be initialized first\n");
        return;
    }

    while(TRUE)
    {
        const s1* menu = "Search for devices in proximity\0"
                         "Wait for an incoming connection request\0"
                         "Connect to a paired device\0"
                         "Go to connected device menu\0"
                         "Delete paired device information\0"
                         "Delete all paired devices\0"
                         "Disconnect from remote device\0"
#if defined(CLX_SCO_BRIDGE)
                         "SCO Bridge Menu\0"
#endif
                         "Return to previous menu\0";

        u4 index = ClxConsoleUIEngine::showMenu("Enter your selection:", menu, ClxAppClassicMenuOptions_TotalOptions - 1);

        if ((FALSE == classicInfo.isClassicInitialized) && (index < ClxAppClassicMenuOptions_ReturnToPreviousMenu))
        {
            ClxConsoleUIEngine::text("\nPlease make sure to initialize the Bluetooth Classic first\n");
            continue;
        }

        /*
        Handle menu selection
        */
        switch (index)
        {
            case ClxAppClassicMenuOptions_SearchForDevices:
            {
                /* Discover devices with SPP server instance, to connect to */
                discoverDevices(stack, FALSE);
                break;
            }
            
            case ClxAppClassicMenuOptions_WaitForIncomingConnection:
            {
              /* Variable to configure the filtering type for Inquiry function */
                struct ClxGapInquiryFilter filter;

                /* Set the inquiry filter */
                filter.filterMask = ClxNoInquiryFilter;
                filter.serviceClass = ClxDeviceServiceClass(ST_AUDIO | ST_RENDERING);
                filter.majorClass = ClxMajorDeviceClass(0);
                filter.minorClass = 0;

                ClxResult ret = clxGapStartInquiry(stack, &filter, FALSE, 10, 9, 8, gBlock);
                if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                {
                    ClxConsoleUIEngine::text("Start inquiry failed with error: %s\n", clxGetErrorCodeText(ret));
                }
                /* 
                Makes the local device discoverable. 
                The purpose is to respond to a device that makes a general inquiry 
                */
                ClxResult err = clxGapSetDiscoverability(stack, TRUE, 2048, 1800, gBlock);
                if (!err)
                {
                    /* Makes the local device connectable mode for the remote device to send connection request */
                    err = clxGapSetConnectability(stack, TRUE, 2048, 400, gBlock);
                    if (!err)
                    {
                        ClxConsoleUIEngine::text("\nWaiting for an incoming connection for 60 seconds. . .");
                        if (clxAcquireSemaphoreTimed(classicInfo.connectionSemaphore, 60000) == CLX_SUCCESS)
                        {

                        }

                        /* Disable the Connectability and Discoverability for a better performance */
                        err = clxGapSetConnectability(stack, FALSE, 2048, 400, gBlock);
                        if ((CLX_SUCCESS != err) && (CLX_ERROR_COMPLETION_PENDING != err))
                        {
                            ClxConsoleUIEngine::text("Set connectability failed with error: %s\n", clxGetErrorCodeText(err));
                        }

                        err = clxGapSetDiscoverability(stack, FALSE, 2048, 1800, gBlock);
                        if ((CLX_SUCCESS != err) && (CLX_ERROR_COMPLETION_PENDING != err))
                        {
                            ClxConsoleUIEngine::text("Set discoverability failed with error: %s\n", clxGetErrorCodeText(err));
                        }
                    }
                    else
                    {
                        ClxConsoleUIEngine::text("\nSet connectability failed with error %s\n", clxGetErrorCodeText(err));
                    }
                }
                else
                {
                    ClxConsoleUIEngine::text("\nSet discoverability failed with error %s\n", clxGetErrorCodeText(err));
                }

                ret = clxGapStopInquiry(stack, gBlock);
                if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
                {
                    ClxConsoleUIEngine::text("Stop inquiry failed with error: %s\n", clxGetErrorCodeText(ret));
                }
                break;
            }

            case ClxAppClassicMenuOptions_ConnectPairedDevice:
            {
                /* Get the list of already paired device and select the desired one. */
                ClxDeviceId id = selectPairedDevice(stack);
                
                /* If a valid device is selected, proceed with menu options for further functions */
                if ( CLX_IS_DEVICE_ID_VALID(id) == TRUE )
                {
                    classicInfo.connectedDeviceId = id;
                    allProfilesMenuFunction(stack, id, deviceName);
                }

                break;
            }
            
            case ClxAppClassicMenuOptions_ConnectedDeviceMenu:
            {
                if (CLX_IS_DEVICE_ID_VALID(classicInfo.connectedDeviceId) == TRUE)
                {
                    allProfilesMenuFunction(stack, classicInfo.connectedDeviceId, deviceName);
                }
                else
                {
                    ClxConsoleUIEngine::text("No device is connected\n");
                }
                
                break;
            }
            case ClxAppClassicMenuOptions_DeletePairedDeviceInfo:
            {
                /* Get the list of already paired device and select the desired one. */
                ClxDeviceId id = selectPairedDevice(stack);
                
                /* If a valid device is selected, proceed with menu options for further functions */
                if (CLX_IS_DEVICE_ID_VALID(id) == TRUE)
                {
                    ClxResult err = clxGapDeletePairedDeviceInfo(stack, id, gBlock);
                    if (CLX_SUCCESS == err)
                    {
                        ClxConsoleUIEngine::text("Pairing information deleted!\n");
                    }
                    else
                    {
                        if (CLX_ERROR_COMPLETION_PENDING != err)
                        {
                            ClxConsoleUIEngine::text("Delete pairing information failed with error %s\n", clxGetErrorCodeText(err));
                        }
                    }
                }
                
                break;
            }
            
            case ClxAppClassicMenuOptions_DeleteAllPairedDevices:
            {
                /* API function to delete all of the paired device information from the configuration file */
                ClxError err = clxGapDeleteAllPairedDevicesInfo(stack, gBlock);
                if (err == CLX_SUCCESS)
                {
                    ClxConsoleUIEngine::text("\nAll paired device information deleted!\n");
                }
                else
                {
                    if (CLX_ERROR_COMPLETION_PENDING != err)
                    {
                        ClxConsoleUIEngine::text("\nDelete all pairing information failed with error %s\n", clxGetErrorCodeText(err));
                    }
                }

                break;
            }

            case ClxAppClassicMenuOptions_Disconnect:
            {
                /* API function to disconnect from the connected remote device */
                ClxError err = clxGapDisconnectPhysicalLink(stack, classicInfo.connectedDeviceId, gBlock);
                if (err == CLX_SUCCESS)
                {
                    classicInfo.connectedDeviceId = CLX_INVALID_DEVICE_ID;
                }
                else
                {
                    if (CLX_ERROR_COMPLETION_PENDING != err)
                    {
                        ClxConsoleUIEngine::text("ACL disconnection failed with error % s\n", clxGetErrorCodeText(err));
                    }
                }

                break;
            }

#if defined(CLX_SCO_BRIDGE)
            case ClxAppClassicMenuOptions_ScoBridgeMenu:
            {
                scoBridgeMenu(stack, deviceName);
                break;
            }
#endif

            case ClxAppClassicMenuOptions_ReturnToPreviousMenu:
            {
                return;
            }

            default:
            {
                break;
            }
        } // switch
    } //while
}

void clxVendorSpecific(const u1* x, u4 y)
{
    (void)x;
    (void)y;
}
#endif /* defined(CLX_BT_CLASSIC) */


