/***********************************************************************************
*
* Project             Clarinox Reference Application
* File                GapBle.cpp
* Description         This application file contains sub menu section for
*                     common GAP procedures
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

#include "ClxBsp.h"
#include "ClarinoxBlue.h"

#include "Gap.Api.h"
#include "Gatt.Ble.Common.Api.h"
#include "Gap.Ble.Api.h"
#include "Gap.Ble.Bonding.Api.h"
#include "Gatt.Ble.Service.h"
#include "Gatt.Ble.Server.Api.h"
#include "Gap.Ble.ChannelSounding.Api.h"
#include "GapBleApp.h"

#include <stdio.h>

#if defined(CLX_BLE_CS_REFLECTOR)
#include "Gap.Ble.ChannelSounding.Api.h"

#include "BleChannelSounding.h"
#endif /* defined(CLX_BLE_CS_REFLECTOR) */

#if defined(CLX_OOB_PAIRING_SUPPORT)
#include "mainBluetooth.h"
#include <stdlib.h>

/* oobData contains and stores all the information asociated with OOB pairing */
AppOobData oobData = {};
#endif

/***************************************************************************************************************************************
*                                                     getBondingProperty
*
* Enable or disable the MITM protection as local device input/output capabilities.
* If secure flag is true enable secure bonding procedure in stack.
*
* \param secureFlag       -     Indicates if LE secure pairing is enabled or disabled
* \param securityRequest  -     TRUE  - Invoke security request procedure in stack.
*                         -     FALSE - Does not invoke security request procedure in stack.
* \param crossTransportFlag  -  Indicates if CrossTransport flag supports legacy or secure
*
* \return u1              - Type of authentication method for bonding procedure.
*
*****************************************************************************************************************************************/
u1 getBondingProperty ( boolean secureFlag, boolean securityRequest, boolean crossTransportFlag )
{
    u1 bondingProperty = ClxBleSmpSecureBondingProperty_MitmNotRequired;

    switch (getIoCapability())
    {
        case IO_DISPLAY_YES_NO:
        case IO_KEYBOARD_DISPLAY:
        {
            if (secureFlag)
            {
                bondingProperty = ClxBleSmpSecureBondingProperty_MitmRequired;
            }
            break;
        }

        case IO_KEYBOARD_ONLY:
        {
            bondingProperty = ClxBleSmpSecureBondingProperty_MitmRequired;
            break;
        }

        case IO_DISPLAY_ONLY:
        case IO_NONE:
        default:
        {
            break;
        }
    }

    if (secureFlag)
    {
        bondingProperty = (u1)(bondingProperty | ClxBleSmpSecureBondingProperty_SecureBonding);
    }

    if (securityRequest)
    {
        bondingProperty = (u1)(bondingProperty | ClxBleSmpSecureBondingProperty_SecurityRequest);
    }

    if (crossTransportFlag)
    {
        bondingProperty = (u1)(bondingProperty | ClxBleSmpSecureBondingProperty_CrossTransport);
    }

    return bondingProperty;
}

/*******************************************************************************************************************************
*                                                bleStackMessageHandler
*
* This call-back function is registered for the GAP and GATT profiles, 
* any events raised by GAP profile causes this call-back function executed with
* the associated event and parameters
*
* \param stack          - Local device stack handle.
* \param serviceHandle  - Profile/service handle.
* \param messageID      - Indication id.
* \param params         - Void pointer to the indication parameters.
* \param errorCode      - Contains the error code.
*
* \return boolean       - TRUE If the call-back function handles indication or indication with *_COMPLETE.
*                         Otherwise, return FALSE
* \note                 - The API should be called in non blocking mode.
*
*******************************************************************************************************************************/
boolean bleStackMessageHandler(ClxStack stack, ClxHandle serviceHandle, u4 messageID, const void* params, ClxError errorCode)
{
    (void)serviceHandle;

    ClxError ret = CLX_ERROR;

    /**
    These (below indications with *_COMPLETE) are command complete indications received when the execution of corresponding API commands
    are completed. The command complete indications are received only when the API has been called in non-blocking mode. 
    The output parameters can be accessed from argument "params".
    */
    if (messageID == CLX_GAP_BLE_MANAGE_WHITE_LIST_COMPLETE)
    {
        clxConsoleUIEngineText("\nManage White List command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_START_BONDING_PROCEDURE_COMPLETE)
    {
        clxConsoleUIEngineText("\nBonding procedure completed with the result: %s\n", clxGetErrorCodeText(errorCode));

#if defined(CLX_BLE_CS_REFLECTOR)
        csInitialize(stack);
#endif /* defined(CLX_BLE_CS_REFLECTOR) */

    }
    else if (messageID == CLX_GAP_BLE_DISCONNECT_PHYSICAL_LINK_COMPLETE)
    {
        clxConsoleUIEngineText("\nDisconnecting completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_SET_BONDABLE_COMPLETE)
    {
        clxConsoleUIEngineText("\nSet Bondable command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_SET_PAIRED_DEVICE_NAME_COMPLETE)
    {
        clxConsoleUIEngineText("\nSet paired device name completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_GET_PAIRED_DEVICE_NAME_COMPLETE)
    {
        ClxGapBleGetPairedDeviceNameComplete *arg = (ClxGapBleGetPairedDeviceNameComplete*)params;

        clxConsoleUIEngineText("\nGet Paired Device name completed with the result: %s\n", clxGetErrorCodeText(errorCode));

        if (errorCode == CLX_SUCCESS && (arg->deviceDetail->name) != NULL)
        {
            clxConsoleUIEngineText("\nPaired device name: %s\n", arg->deviceDetail->name);
        }
    }
    else if (messageID == CLX_GAP_BLE_GET_LIST_OF_PAIRED_DEVICES_COMPLETE)
    {
        ClxGapBleGetListOfPairedDevicesComplete *arg = (ClxGapBleGetListOfPairedDevicesComplete*)params;

        clxConsoleUIEngineText("\nList of Paired Devices command completed with the result: %s\n", clxGetErrorCodeText(errorCode));

        if (errorCode == CLX_SUCCESS)
        {
            clxConsoleUIEngineText("\nTotal number of paired device list: %u\n", (*arg->numberOfPairedDevices));

            /**
            Prints the list of paired device details.
            */
            if ((*arg->numberOfPairedDevices) != 0)
            {
                for (u4 deviceCount = 0; deviceCount < (*arg->numberOfPairedDevices); deviceCount++)
                {
                    clxConsoleUIEngineText("\n(Address = %02X%02X%02X%02X%02X%02X)\n",arg->deviceAddrList[deviceCount].value[0],
                                                                        arg->deviceAddrList[deviceCount].value[1],
                                                                        arg->deviceAddrList[deviceCount].value[2],
                                                                        arg->deviceAddrList[deviceCount].value[3],
                                                                        arg->deviceAddrList[deviceCount].value[4],
                                                                        arg->deviceAddrList[deviceCount].value[5]);

                    clxConsoleUIEngineText("\n(Address type = %x)\n", arg->deviceAddrList[deviceCount].addressType);
                }
            }    
        }
    }
    else if (messageID == CLX_GAP_BLE_USER_PASSKEY_REQUEST_REPLY_COMPLETE)
    {
        clxConsoleUIEngineText("\nUser Passkey Request Reply command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_USER_CONFIRMATION_REQUEST_REPLY_COMPLETE)
    {
        clxConsoleUIEngineText("\nUser Confirmation Request Reply command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_DELETE_PAIRED_DEVICE_INFO_COMPLETE)
    {
        clxConsoleUIEngineText("\nDelete Paired Device Info command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_DELETE_ALL_PAIRED_DEVICES_INFO_COMPLETE)
    {
        clxConsoleUIEngineText("\nDelete All Paired Devices Info command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_ENCRYPT_COMPLETE)
    {
        clxConsoleUIEngineText("\nEncrypt command completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_GET_CONNECTION_PARAMETERS_COMPLETE)
    {
        ClxGapBleGetConnectionParametersComplete *arg = (ClxGapBleGetConnectionParametersComplete*)params;

        /**
        Object to store the active connection details.
        */
        ClxConfigList* argParams = arg->parameters;

        /**
        Prints the active connection details
        */
        if (argParams)
        {
            ClxConfigParam* item = argParams->first;
            ClxConfigBleBdAddress* bdAddress = NULL;
            s1 temp[CLX_BLUETOOTH_ADDRESS_ASCII_MIN_BUFFER_SIZE];

            clxConsoleUIEngineText("\n");

            while (item != NULL)
            {
                if (strcmp("LocalCurrentAddress", item->paramName) == 0 && item->processed)
                {
                    bdAddress = (ClxConfigBleBdAddress*) item;
                    clxConsoleUIEngineText("\nLocal Current Address    %s\n", clxConvertBluetoothAddressToAscii(bdAddress->addr.value, temp));
                }
                else if (strcmp("RemoteCurrentAddress", item->paramName) == 0 && item->processed)
                {
                    bdAddress = (ClxConfigBleBdAddress*) item;
                    clxConsoleUIEngineText("Remote Current Address   %s\n", clxConvertBluetoothAddressToAscii(bdAddress->addr.value, temp));
                }
                else if (strcmp("RemoteIdentityAddress", item->paramName) == 0 && item->processed)
                {
                    bdAddress = (ClxConfigBleBdAddress*) item;
                    clxConsoleUIEngineText("Remote Identity Address  %s\n", clxConvertBluetoothAddressToAscii(bdAddress->addr.value, temp));
                }

                item = item->next;
            }
        }
        else
        {
            clxConsoleUIEngineText("\nGet Connection Parameter command failed with the result: %s\n", clxGetErrorCodeText(errorCode));
        }
    }
    else if (messageID == CLX_GAP_BLE_REJECT_BONDING_PROCEDURE_COMPLETE)
    {
        clxConsoleUIEngineText("\nRejecting the bonding procedure completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_CONNECTION_PARAMETER_CHANGE_RESPONSE_COMPLETE)
    {
        clxConsoleUIEngineText("\nConnection parameter change response completed with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    /**
    Security request received from server to initiate bonding procedure by client 
    */
    else if (messageID == CLX_GAP_BLE_SECURITY_REQUEST_INDICATION)
    {
        ClxGapBleSecurityRequestIndication* params_ = (ClxGapBleSecurityRequestIndication*)params;
        boolean ctFlag = FALSE;

        clxConsoleUIEngineText ("\nSecurity request received from peripheral");
        clxConsoleUIEngineText ("\n(Bonding Type = %d), (Mitm = %d), (Secure = %d), (Cross Transport = %d)", params_->bondingType, params_->mitmProtectionRequired, params_->securityFlag, params_->crossTransportFlag);

#if defined(CLX_BLE_CONFIRMATION_AUTO_ACCEPT)
        s1 ch = 'y';
#else
        clxConsoleUIEngineText ("\nDo you want to process the security request?");
        s1 ch = clxConsoleUIEngineMessageBox("", "yYnN", 4);
#endif

        if ((ch == 'y') || (ch == 'Y'))
        {
#if defined(CLX_OOB_PAIRING_SUPPORT)
            /* 
            If OOB pairing has to be enabled, 
            do it here after we get the connection handle and before initiating bonding procedure
            */
            if (TRUE == oobData.enableOobPairing)
            {
                enableDisableOob(stack, params_->connectionHandle, TRUE);
            }
#endif

            u1 localRemoteKeys = (u1)ClxBleSmpKeyDistribution_EncryptionKey | (u1)ClxBleSmpKeyDistribution_IdentityKey;

#if defined(CLX_BT_CLASSIC)
            ctFlag = TRUE;
            localRemoteKeys = localRemoteKeys | (u1)ClxBleSmpKeyDistribution_LinkKey;
#endif
            /*
            Initiate bonding procedure where the security manager uses a key distribution approach to perform identity and encryption functionalities.
            */
            ret = clxGapBleStartBondingProcedure(stack,
                                                 params_->connectionHandle,
                                                 ClxBleSmpBondingType_Bonding,
                                                 getBondingProperty(params_->securityFlag, FALSE, ctFlag),
                                                 16,
                                                 localRemoteKeys,
                                                 localRemoteKeys,
                                                 FALSE);
            if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
            {
                clxConsoleUIEngineText("\nclxGapBleStartBondingProcedure command failed with the result: %s\n", clxGetErrorCodeText(ret));
            }
        }
        else
        {
            /**
            Rejects the security request received from server.
            */
            ret = clxGapBleRejectBondingProcedure(stack, params_->connectionHandle, FALSE);
            if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
            {
                clxConsoleUIEngineText("\nclxGapBleRejectBondingProcedure command failed with the result: %s\n", clxGetErrorCodeText(ret));
            }
        }
    }
    /**
    User passkey request event received from stack when the local device enables authentication procedure with man-in-the-middle 
    protection using passkey method during bonding process.
    */
    else if (messageID == CLX_GAP_BLE_USER_PASSKEY_REQUEST_INDICATION)
    {
        s1 message[128] = {0};
        u4 passKey      = 0;
        
        ClxGapBleUserPasskeyRequestIndication* arg = (ClxGapBleUserPasskeyRequestIndication*)params;

        clxConsoleUIEngineInputBox ("Please enter the 6 digit passkey (000000 - 999999) to connect the remote device: ", message, 7);
        (void)sscanf(message, "%u", &passKey);

        /**
        Respond to the received authentication request with passkey
        */
        ret = clxGapBleUserPasskeyRequestReply(stack, arg->connectionHandle, TRUE, passKey, FALSE);
        if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
        {
            clxConsoleUIEngineText("\nclxGapBleUserPasskeyRequestReply command failed with the result: %s\n", clxGetErrorCodeText(ret));
        }
    }
    /**
    User passkey notification event received from stack when the local device enables authentication procedure with No man-in-the-middle 
    protection during bonding procedure.
    */
    else if (messageID == CLX_GAP_BLE_USER_PASSKEY_NOTIFICATION_INDICATION)
    {
        ClxGapBleUserPasskeyNotificationIndication* arg = (ClxGapBleUserPasskeyNotificationIndication*)params;
        clxConsoleUIEngineText ("\nThe passkey \"%u\" to connect the remote device", arg->value);
    }
    /**
    User confirmation request event received from stack when the local device enables authentication procedure with man-in-the-middle and 
    secure bonding using numeric comparison method during bonding procedure.
    */
    else if (messageID == CLX_GAP_BLE_USER_CONFIRMATION_REQUEST_INDICATION)
    {
        ClxGapBleUserConfirmationRequestIndication* arg = (ClxGapBleUserConfirmationRequestIndication*)params;

#if defined(CLX_BLE_CONFIRMATION_AUTO_ACCEPT)
        s1 ch = 'y';
#else
        clxConsoleUIEngineText ("\nPlease confirm the passkey \"%u\" to connect?", arg->value);
        const s1* y = "yYnN";
        s1 ch = clxConsoleUIEngineMessageBox("", (s1*)y, 4);
#endif

        if ((ch == 'y') || (ch == 'Y'))
        {
            /**
            Accept the received authentication request.
            */
            ret = clxGapBleUserConfirmationRequestReply(stack, arg->connectionHandle, TRUE, FALSE);
            if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
            {
                clxConsoleUIEngineText("\nclxGapBleUserConfirmationRequestReply command failed with the result: %s\n", clxGetErrorCodeText(ret));
            }
        }
        else
        {
            /**
            Reject the received authentication request.
            */
            ret = clxGapBleUserConfirmationRequestReply(stack, arg->connectionHandle, FALSE, FALSE);
            if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
            {
                clxConsoleUIEngineText("\nclxGapBleUserConfirmationRequestReply command failed with the result: %s\n", clxGetErrorCodeText(ret));
            }
        }
    }
    /**
    Receives the pairing request from remote device and invokes the pairing process using clxGapBleStartBondingProcedure(..) API.
    */
    else if (messageID == CLX_GAP_BLE_PAIRING_REQUEST_INDICATION)
    {
        ClxGapBlePairingRequestIndication* arg = (ClxGapBlePairingRequestIndication*)params;
        boolean ctFlag = FALSE;

        clxConsoleUIEngineText ("\nBonding request received from central");
        clxConsoleUIEngineText ("\n(Bonding Type = %d), (Mitm = %d), (Secure = %d), (Cross Transport = %d)", arg->bondingType, arg->mitmProtection, arg->secureConnection, arg->crossTransport);

#if defined(CLX_BLE_CONFIRMATION_AUTO_ACCEPT)
        s1 ch = 'y';
#else
        clxConsoleUIEngineText ("\nDo you want to process the bonding request?");
        const s1* y = "yYnN";
        s1 ch = clxConsoleUIEngineMessageBox("", (s1*)y, 4);
#endif

        if ((ch == 'y') || (ch == 'Y'))
        {
#if defined(CLX_OOB_PAIRING_SUPPORT)
            /* 
            If OOB pairing has to be enabled, 
            do it here after we get the connection handle and before initiating bonding procedure
            */
            if (TRUE == oobData.enableOobPairing)
            {
                enableDisableOob(stack, arg->connectionHandle, TRUE);
            }
#endif
            u1 localRemoteKeys = (u1)ClxBleSmpKeyDistribution_EncryptionKey | (u1)ClxBleSmpKeyDistribution_IdentityKey;

#if defined(CLX_BT_CLASSIC)
            ctFlag = TRUE;

            if (arg->distributedKeys & ClxBleSmpKeyDistribution_LinkKey)
            {
                localRemoteKeys = localRemoteKeys | (u1)ClxBleSmpKeyDistribution_LinkKey;
            }
#endif

            /*
            Initiate bonding procedure where the security manager uses a key distribution approach to perform identity and encryption functionalities.
            */
            ret = clxGapBleStartBondingProcedure(stack,
                                                 arg->connectionHandle,
                                                 ClxBleSmpBondingType_Bonding,
                                                 getBondingProperty(arg->secureConnection, FALSE, ctFlag),
                                                 16,
                                                 localRemoteKeys,
                                                 localRemoteKeys,
                                                 FALSE);
            if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
            {
                clxConsoleUIEngineText("\nclxGapBleStartBondingProcedure command failed with the result: %s\n", clxGetErrorCodeText(ret));
            }
        }
        else
        {
            ret = clxGapBleRejectBondingProcedure(stack, arg->connectionHandle, FALSE);
            if ((CLX_SUCCESS != ret) && (CLX_ERROR_COMPLETION_PENDING != ret))
            {
                clxConsoleUIEngineText("\nclxGapBleRejectBondingProcedure command failed with the result: %s\n", clxGetErrorCodeText(ret));
            }
        }
    }
    else if (CLX_GAP_BLE_CONNECTION_PARAMETER_CHANGE_REQUEST_INDICATION == messageID)
    {
        ClxGapBleConnectionParameterChangeRequestIndication* arg = (ClxGapBleConnectionParameterChangeRequestIndication*)params;

        clxConsoleUIEngineText ("\nConnection parameter change request: Con.Handle %u, Min.Interval %u, Max.Interval %u, Latency %u, Supervision Timeout %u\n",
            arg->connectionHandle, arg->minimumInterval, arg->maximumInterval, arg->latency, arg->supervisionTimeout);

#if defined(CLX_BLE_CONFIRMATION_AUTO_ACCEPT)
        s1 ch = 'y';
#else
        clxConsoleUIEngineText ("\nDo you want to accept the connection parameter change?");
        const s1* y = "yYnN";
        s1 ch = clxConsoleUIEngineMessageBox("", (s1*)y, 4);
#endif

        boolean accept = FALSE;
        if ((ch == 'y') || (ch == 'Y'))
        {
            accept = TRUE;
        }
        
        ret = clxGapBleConnectionParameterChangeResponse(stack,
                                                         arg->connectionHandle,
                                                         accept,
                                                         arg->minimumInterval,
                                                         arg->maximumInterval,
                                                         arg->latency,
                                                         arg->supervisionTimeout,
                                                         1,
                                                         0x0c00,
                                                         FALSE);

        if (CLX_ERROR_COMPLETION_PENDING != ret)
        {
            clxConsoleUIEngineText("\nclxGapBleConnectionParameterChangeResponse command failed with the result: %s\n", clxGetErrorCodeText(ret));
        }
    }
    /**
    Indication received when the encryption procedure is completed successfully
    */
    else if (messageID == CLX_GAP_BLE_ENCRYPTION_COMPLETED_INDICATION)
    {
        ClxGapBleEncryptionCompletedIndication* arg = (ClxGapBleEncryptionCompletedIndication*)params;
        clxConsoleUIEngineText("\nRemote device encrypted the connection with the result: %s\n", clxGetErrorCodeText(arg->reason));
        clxConsoleUIEngineText ("\nConnectionHandle : %x \n", arg->connectionHandle);
    }
    else if (messageID == CLX_GAP_BLE_CONNECTION_PARAMETER_UPDATED_INDICATION)
    {
        ClxGapBleConnectionParameterUpdatedIndication* arg = (ClxGapBleConnectionParameterUpdatedIndication*)params;
        clxConsoleUIEngineText("\nConnection parameters updated: Con.Handle %u, Con.Interval %u, Con.Latency %u, Supervision timeout %u\n",
                arg->connectionHandle, arg->connectionInterval, arg->connectionLatency, arg->supervisionTimeout);
    }
    else if (messageID == CLX_GAP_BLE_DATA_LENGTH_CHANGED_INDICATION)
    {
        ClxGapBleDataLengthChangedIndication* arg = (ClxGapBleDataLengthChangedIndication*)params;
        clxConsoleUIEngineText ("\nData length changed: Con.Handle %u, Tx length %u, Rx length %u\n", arg->connectionHandle, arg->txPacketLength, arg->rxPacketLength);
    }
    else if (messageID == CLX_GAP_BLE_PHY_UPDATED_INDICATION)
    {
        ClxGapBlePhyUpdatedIndication* arg = (ClxGapBlePhyUpdatedIndication*)params;
        clxConsoleUIEngineText ("\nPHY updated: Con.Handle %u, Tx PHY %u, Rx PHY %u\n", arg->connectionHandle, arg->txPhy, arg->rxPhy);
    }
#if defined (CLX_BLE_CS_INITIATOR) || defined(CLX_BLE_CS_REFLECTOR)
    else if (messageID == CLX_GAP_BLE_CS_INITIALIZE_COMPLETE)
    {
        clxConsoleUIEngineText("\nCLX_GAP_BLE_CS_INITIALIZE_COMPLETE with the result: %s\n", clxGetErrorCodeText(errorCode));
    }
    else if (messageID == CLX_GAP_BLE_CS_CONFIG_COMPLETED_INDICATION)
    {
        ClxGapBleCsConfigCompletedIndication* arg = (ClxGapBleCsConfigCompletedIndication*)params;
        clxConsoleUIEngineText("\nCLX_GAP_BLE_CS_CONFIG_COMPLETED_INDICATION with the result: %s\n", clxGetErrorCodeText(arg->status));
    }    
    else if (messageID == CLX_GAP_BLE_CS_SUB_EVENT_RESULT_INDICATION)
    {
        ClxGapBleCsSubEventResultIndication* arg = (ClxGapBleCsSubEventResultIndication*)params;

        if(arg->subEventResult.subEventDoneStatus == CLX_BLE_CS_PARTIAL)
        {
            ClxCsProcedureSubEventResult(arg);
        }
        else
        {
            ClxCsProcedureSubEventResult(arg);

            ClxRasBuildAndNotify();
        }

        clxConsoleUIEngineText("---- SubEvent Result ----\n");

        clxConsoleUIEngineText("configId                 : %u\n", arg->configId);
        clxConsoleUIEngineText("startingAclEventCounter  : %u\n", arg->startingAclEventCounter);
        clxConsoleUIEngineText("procedureCounter         : %u\n", arg->procedureCounter);
        clxConsoleUIEngineText("frequencyCompensation    : 0x%04x\n", arg->frequencyCompensation);
        clxConsoleUIEngineText("referencePowerLevel      : 0x%02x\n", arg->referencePowerLevel);

        clxConsoleUIEngineText("procedureDoneStatus      : %u\n", arg->subEventResult.procedureDoneStatus);
        clxConsoleUIEngineText("subEventDoneStatus       : %u\n", arg->subEventResult.subEventDoneStatus);
        clxConsoleUIEngineText("abortReason              : %u\n", arg->subEventResult.abortReason);
        clxConsoleUIEngineText("numberOfAntennaPaths     : %u\n", arg->subEventResult.numberOfAntennaPaths);
        clxConsoleUIEngineText("numberOfStepsReported    : %u\n", arg->subEventResult.numberOfStepsReported);

        ClxBleCsSubEventStepDataDetails* stepDataDetails = arg->stepDataDetails;

        for (u2 index = 0; index < arg->subEventResult.numberOfStepsReported; index++)
        {
            clxConsoleUIEngineText("Step Data: %u, Mode: %u, Channel: %u, DataLength: %u, Data: ", 
                                    index, stepDataDetails->mode, stepDataDetails->channel, stepDataDetails->dataLength);
            for(u2 count = 0; count < stepDataDetails->dataLength; count++)
            {
                clxConsoleUIEngineText("%02x ", *(&stepDataDetails->data + count));
            }
            clxConsoleUIEngineText("\n");

            stepDataDetails = (ClxBleCsSubEventStepDataDetails*)(((u1*)stepDataDetails) + 3 + stepDataDetails->dataLength);
        }

        clxConsoleUIEngineText("\n");
    }
    else if (messageID == CLX_GAP_BLE_CS_SUB_EVENT_CONTINUE_RESULT_INDICATION)
    {
        ClxGapBleCsSubEventContinueResultIndication* arg = (ClxGapBleCsSubEventContinueResultIndication*)params;

        ClxCsProcedureSubEventContinueResult(arg);

        if(arg->subEventResult.subEventDoneStatus != CLX_BLE_CS_PARTIAL)
        {
            ClxRasBuildAndNotify();
        }

        clxConsoleUIEngineText("---- SubEvent Continue Result ----\n");

        clxConsoleUIEngineText("configId                 : %u\n", arg->configId);
        clxConsoleUIEngineText("procedureDoneStatus      : %u\n", arg->subEventResult.procedureDoneStatus);
        clxConsoleUIEngineText("subEventDoneStatus       : %u\n", arg->subEventResult.subEventDoneStatus);
        clxConsoleUIEngineText("abortReason              : %u\n", arg->subEventResult.abortReason);
        clxConsoleUIEngineText("numberOfAntennaPaths     : %u\n", arg->subEventResult.numberOfAntennaPaths);
        clxConsoleUIEngineText("numberOfStepsReported    : %u\n", arg->subEventResult.numberOfStepsReported);

        ClxBleCsSubEventStepDataDetails* stepDataDetails = arg->stepDataDetails;

        for (u2 index = 0; index < arg->subEventResult.numberOfStepsReported; index++)
        {
            clxConsoleUIEngineText("Step Data: %u, Mode: %u, Channel: %u, DataLength: %u, Data: ", 
                                    index, stepDataDetails->mode, stepDataDetails->channel, stepDataDetails->dataLength);
            for(u2 count = 0; count < stepDataDetails->dataLength; count++)
            {
                clxConsoleUIEngineText("%02x ", *(&stepDataDetails->data + count));
            }
            clxConsoleUIEngineText("\n");

            stepDataDetails = (ClxBleCsSubEventStepDataDetails*)(((u1*)stepDataDetails) + 3 + stepDataDetails->dataLength);
        }

        clxConsoleUIEngineText("\n");
    }
#endif /* defined (CLX_BLE_CS_INITIATOR) || defined(CLX_BLE_CS_REFLECTOR) */
    else
    {
        return FALSE;
    }

    return TRUE;
}

/***************************************************************************************************************************************
*                                                initiateBlePairing
*
* Initiates BLE pairing procedure with the given remote device whose connection handle is passed as parameter
*
* \param stack              - Local device stack handle.
* \param connectionHandle   - Handle of connection with remote device.
* \param secureFlag         - Secure connection or Legacy.
* \param blocking           - Blocking or Non-Blocking mode of API execution
* 
* \return ClxResult
*
****************************************************************************************************************************************/
ClxResult initiateBlePairing(ClxStack stack, ClxBleConnectionHandle connectionHandle, boolean secureFlag, boolean blocking)
{
    boolean ctFlag = FALSE;
    u1      localRemoteKeys = (u1)ClxBleSmpKeyDistribution_EncryptionKey | (u1)ClxBleSmpKeyDistribution_IdentityKey;
    
#if defined(CLX_OOB_PAIRING_SUPPORT)
    u1 bondingProperty;
    if (FALSE == secureFlag)
    {
        bondingProperty = ClxBleSmpSecureBondingProperty_MitmRequired | ClxBleSmpSecureBondingProperty_SecurityRequest;
    }
    else
    {
        bondingProperty = ClxBleSmpSecureBondingProperty_SecureBonding | ClxBleSmpSecureBondingProperty_MitmNotRequired | ClxBleSmpSecureBondingProperty_SecurityRequest;
    }
#endif

#if defined(CLX_BT_CLASSIC)
    ctFlag = TRUE;
    localRemoteKeys = localRemoteKeys | (u1)ClxBleSmpKeyDistribution_LinkKey;
#endif

    /**
    Initiate bonding procedure where the security manager uses a key distribution approach to perform identity and encryption functionalities.
    */
    ClxResult ret = clxGapBleStartBondingProcedure(stack,
                                                   connectionHandle,
                                                   ClxBleSmpBondingType_Bonding,
#if defined(CLX_OOB_PAIRING_SUPPORT)
                                                   bondingProperty,
#else
                                                   getBondingProperty(secureFlag, TRUE, ctFlag),
#endif
                                                   16,
                                                   localRemoteKeys,
                                                   localRemoteKeys,
                                                   blocking);

    clxConsoleUIEngineText("\nclxGapBleStartBondingProcedure: status - %s\n", clxGetErrorCodeText(ret));

    return ret;
}

/***************************************************************************************************************************************
*                                                startEncryption
*
* Initiate Encryption procedure with the given remote device whose connection handle is passed as parameter
*
* \param stack              - Local device stack handle.
* \param connectionHandle   - Handle of connection with remote device.
* \param secureFlag         - Secure connection or Legacy.
* \param securityRequest    - Type of Security or Bonding property
* \param blocking           - Blocking or Non-Blocking mode of API execution
* 
* \return void
*
****************************************************************************************************************************************/
void startEncryption(ClxStack stack, ClxBleConnectionHandle connectionHandle, boolean secureFlag, boolean securityRequest, boolean blocking)
{
    /* 
    We set mitmProtectionRequired to FALSE to make sure the encryption will happen regardless of the strength of the key we have: 
    */
    ClxResult ret = clxGapBleEncrypt(stack, connectionHandle, getBondingProperty(secureFlag, securityRequest, FALSE), blocking);
    clxConsoleUIEngineText("\nclxGapBleEncrypt: status - %s\n", clxGetErrorCodeText(ret));
}

/***************************************************************************************************************************************
*                                                disconnectFromConnectedDevice
*
* Disconnect connection with the connected remote device which is represented by the given connection handle
*
* \param stack              - Local device stack handle.
* \param connectionHandle   - Handle of connection with remote device.
* \param blocking           - Blocking or Non-Blocking mode of API execution
* 
* \return void
*
****************************************************************************************************************************************/
void disconnectFromConnectedDevice(ClxStack stack, ClxBleConnectionHandle connectionHandle, boolean blocking)
{
    ClxResult ret = clxGapBleDisconnectPhysicalLink(stack, connectionHandle, DISCONNECTION_TIMEOUT, blocking);
    clxConsoleUIEngineText("\nclxGapBleDisconnectPhysicalLink: status - %s\n", clxGetErrorCodeText(ret));
}

/***************************************************************************************************************************************
*                                                getCurrentConnectionDetails
*
* Returns the connection details of the connection whose handle is passed
*
* \param stack              - Local device stack handle.
* \param connectionHandle   - Handle of connection with remote device.
* \param blocking           - Blocking or Non-Blocking mode of API execution
* 
* \return void
*
****************************************************************************************************************************************/
void getCurrentConnectionDetails(ClxStack stack, ClxBleConnectionHandle connectionHandle, boolean blocking)
{
    /**
    Object to store active connection parameters values.
    */
    struct Params
    {
        ClxConfigList           parentList;

        ClxConfigBleBdAddress   localAddress;
        ClxConfigBleBdAddress   remoteCurrentAddress;
        ClxConfigBleBdAddress   remoteIdentityAddress;
    } params;

    clxConfigInitParamsList(&params.parentList, NULL, NULL);
    clxConfigInitBleBdAddressParam(&params.localAddress, "LocalCurrentAddress", NULL, &params.parentList);
    clxConfigInitBleBdAddressParam(&params.remoteCurrentAddress, "RemoteCurrentAddress", NULL, &params.parentList);
    clxConfigInitBleBdAddressParam(&params.remoteIdentityAddress, "RemoteIdentityAddress", NULL, &params.parentList);

    /**
    Retrieves the active connection details.
    */
    ClxResult err = clxGapBleGetConnectionParameters(stack, connectionHandle, &params.parentList, blocking);

    if (err == CLX_SUCCESS)
    {
        s1 temp[CLX_BLUETOOTH_ADDRESS_ASCII_MIN_BUFFER_SIZE];
        clxConsoleUIEngineText("\nConnection Handle : %u\n", connectionHandle);

        if (params.localAddress.paramInfo.processed == TRUE)
        {
            clxConsoleUIEngineText("Local Current Address : %s\n", clxConvertBluetoothAddressToAscii(params.localAddress.addr.value, temp));
        }
        
        if (params.remoteCurrentAddress.paramInfo.processed == TRUE)
        {
            clxConsoleUIEngineText("Remote Current Address : %s\n", clxConvertBluetoothAddressToAscii(params.remoteCurrentAddress.addr.value, temp));
        }
        
        if (params.remoteIdentityAddress.paramInfo.processed == TRUE)
        {
            clxConsoleUIEngineText("Remote Identity Address : %s\n", clxConvertBluetoothAddressToAscii(params.remoteIdentityAddress.addr.value, temp));
        }
        
        clxConsoleUIEngineText("\n");
    }
    else
    {
        clxConsoleUIEngineText("clxGapBleGetConnectionParameters failed with the error %s\n", clxGetErrorCodeText(err));
    }
}

/***************************************************************************************************************************************
*                                                deleteBlePairedDeviceInfo
*
* Delete paired devide details that is stored
*
* \param stack                  - Local device stack handle.
* \param remoteDeviceAddress    - BD address of the remote device that has to be deleted.
* \param isOldestInfo           - Delete oldest pairing info or not.
* \param blocking               - Blocking or Non-Blocking mode of API execution
* 
* \return void
*
****************************************************************************************************************************************/
void deleteBlePairedDeviceInfo(ClxStack stack, ClxBleBdAddress* remoteDeviceAddress, boolean isOldestInfo, boolean blocking)
{
    ClxError err = CLX_ERROR;

    if (isOldestInfo)
    {
        err = clxGapBleDeletePairedDeviceInfo(stack, remoteDeviceAddress, blocking);
        clxConsoleUIEngineText("\nDeleting Paired info completed with %s\n", clxGetErrorCodeText(err));
    }
    else
    {
        err = clxGapBleDeleteAllPairedDevicesInfo(stack, blocking);
        clxConsoleUIEngineText("\nDeleting All Paired info completed with %s\n", clxGetErrorCodeText(err));
    }
}

/***************************************************************************************************************************************
*                                                changeConnectionParameters
*
* Updates the connection parameter, tx/rx PHY and extending the packet length.
*
* \param stack                  - Local device stack handle
* \param conHandle              - Active connection handle
* \param filter                 - Filter to update connection parameters, set phy and data length extension
* \param minConInterval         - Minimum connection interval
* \param maxConInterval         - Maximum connection interval
* \param conLatency             - Connection latency
* \param supTimeout             - Supervision timeout
* \param minConEventLen         - Minimum connection event length
* \param maxConEventLen         - Maximum connection event length
* \param singlePackLen          - Single packet length
* \param singlePacTransTime     - Single packet transmit time
* \param phyPreference          - Preferred PHY such as controller or host preference
* \param txPhy                  - Preferred Tx PHY
* \param rxPhy                  - Preferred Rx PHY
* \param leCodedOptions         - Preferred coded PHY
* \param blocking               - Blocking or Non-Blocking mode of API execution
* 
* \return void
*
****************************************************************************************************************************************/
void changeConnectionParameters(ClxStack              stack,
                                u2                    conHandle,
                                u1                    filter,
                                u2                    minConInterval,
                                u2                    maxConInterval,
                                u2                    conLatency,
                                u2                    supTimeout,
                                u2                    minConEventLen,
                                u2                    maxConEventLen,
                                u2                    singlePackLen,
                                u2                    singlePacTransTime,
                                u1                    phyPreference,
                                ClxBlePhyType         txPhy,
                                ClxBlePhyType         rxPhy,
                                ClxBleLECodedPhy      leCodedOptions,
                                boolean               blocking)
{
    ClxResult ret = clxGapBleChangeConnectionParameter(stack,
                                                       conHandle,
                                                       filter,
                                                       minConInterval,
                                                       maxConInterval,
                                                       conLatency,
                                                       supTimeout,
                                                       minConEventLen,
                                                       maxConEventLen,
                                                       singlePackLen,
                                                       singlePacTransTime,
                                                       phyPreference,
                                                       txPhy,
                                                       rxPhy,
                                                       leCodedOptions,
                                                       blocking);

    clxConsoleUIEngineText("\nChanging connection parameters completed with %s\n", clxGetErrorCodeText(ret));
}

void startExtendedScan(ClxStack stack, boolean bNameFilter)
{
    ClxResult ret = CLX_ERROR;
    ClxGapBleExtendedScanParameters scanParameter_Le1M_PHY;

    scanParameter_Le1M_PHY.scanInterval = 120;
    scanParameter_Le1M_PHY.scanType     = BleScanType_Passive;
    scanParameter_Le1M_PHY.scanWindow   = 100;

    if (bNameFilter)
    {
        clxSetDeviceNameFilteringOption ();
    }

    ret = clxGapBleEnableExtendedScan( stack,                                       /* stack                     */
                                       ClxBleOwnAddressMode_Identity,               /* localAddressType          */
                                       ClxExtendedScanFilterPolicy_All,             /* filterPolicy              */
                                       &scanParameter_Le1M_PHY,                     /* scanParameter_Le1M_PHY    */
                                       NULL,                                        /* scanParameter_LeCoded_PHY */
                                       ClxExtendedScanFilterDuplicate_Enabled,      /* filterDuplicates          */
                                       0,                                           /* duration                  */
                                       0,                                           /* period                    */
                                       TRUE );                                      /* block                     */

    clxConsoleUIEngineText("\nclxGapBleEnableExtendedScan: status - %s\n", clxGetErrorCodeText(ret));
}


#if defined(CLX_OOB_PAIRING_SUPPORT)
/***************************************************************************************************************************************
*                                                generateOobData
*
* Present the user menu and generate the OOB keys based on the user selection option and by calling the appropriate 
* stack APIs. Print the keys.
*
* \param stack                  - Local device stack handle.
* 
* \return void
*
****************************************************************************************************************************************/
void generateOobData(ClxStack stack)
{
    u4 option = 1;
    size_t inputByteCount = 0;
    ClxResult ret = CLX_SUCCESS;

    do
    {
        clxConsoleUIEngineInputBox("Enter the pairing method: 1 - Legacy pairing, 2 - Secure pairing : ", oobData.input_buffer, MAX_INPUT_SIZE);
        (void)sscanf(oobData.input_buffer, "%u", &option);

        if ((option != 1) && (option != 2))
        {
            clxConsoleUIEngineText("\nPlease enter the valid option as either 1 or 2.\n");
            break;
        }

        /**
        Set the local device in bondable mode.
        */
        ret = clxGapBleSetBondable(stack, TRUE, TRUE);
        if (CLX_SUCCESS != ret)
        {
            clxConsoleUIEngineText("\nclxGapBleSetBondable failed: status - %s\n", clxGetErrorCodeText(ret));
            break;
        }

        (option == 1) ? oobData.pairingMode = ClxBlePairMode_Legacy : oobData.pairingMode = ClxBlePairMode_Secure;

        memset(&oobData.ptrStackOobKeys, 0, sizeof(oobData.ptrStackOobKeys));

        /* We set the memory for the keys, so the stack can set the non-null with valid values */
        oobData.ptrStackOobKeys.localPublicKeyX = oobData.publicKeyX;
        oobData.ptrStackOobKeys.localPublicKeyY = oobData.publicKeyY;
        oobData.ptrStackOobKeys.localPrivateKey = oobData.privateKey;

        clxConsoleUIEngineText("\nChoose applicable:-\n");
        clxConsoleUIEngineText("1. Only Local OOB data available (No Remote OOB)\n");
        clxConsoleUIEngineText("2. Only Remote OOB data available (No Local OOB)\n");
        clxConsoleUIEngineText("3. Both OOB data available\n");
        clxConsoleUIEngineText("4. No OOB data available\n");
        clxConsoleUIEngineInputBox("5. Exit : ", oobData.input_buffer, MAX_INPUT_SIZE);
        (void)sscanf(oobData.input_buffer, "%u", &option);
        if ((option >= 5) || (option < 1))
        {
            if (option != 5)
            {
                clxConsoleUIEngineText("\nPlease enter valid option.\n");
            }
            break;
        }

        if ((1 == option) || (3 == option))
        {
            /* Assign valid memory so that stack generates local device random value using clxGapBleGenerateOobData() */
            oobData.ptrStackOobKeys.randomLocal = oobData.randomLocal;
            oobData.ptrStackOobKeys.confirmLocal = oobData.confirmLocal;
        }

        ret = clxGapBleGenerateOobData(stack, 
                                       (oobData.pairingMode == ClxBlePairMode_Secure) ? TRUE : FALSE,
                                       &oobData.ptrStackOobKeys,
                                       TRUE);
        clxConsoleUIEngineText("\nclxGapBleGenerateOobData: status - %s\n", clxGetErrorCodeText(ret));

        clxConsoleUIEngineText("\nLocal device OOB keys (generated) are as below;");

        clxConsoleUIEngineText("\nPublic Key X: ");
        for (u4 index = 0; index < LE_PUBLIC_PRIVATE_KEY_LENGTH; index++) 
        {
            clxConsoleUIEngineText("%02X", oobData.ptrStackOobKeys.localPublicKeyX[index]);
        }

        clxConsoleUIEngineText("\nPublic Key Y: ");
        for (u4 index = 0; index < LE_PUBLIC_PRIVATE_KEY_LENGTH; index++) 
        {
            clxConsoleUIEngineText("%02X", oobData.ptrStackOobKeys.localPublicKeyY[index]);
        }

        clxConsoleUIEngineText("\nPrivate Key: ");
        for (u4 index = 0; index < LE_PUBLIC_PRIVATE_KEY_LENGTH; index++) 
        {
            clxConsoleUIEngineText("%02X", oobData.ptrStackOobKeys.localPrivateKey[index]);
        }

        if ((1 == option) || (3 == option))
        {
            clxConsoleUIEngineText("\nRandom Local: ");
            for (u4 index = 0; index < LE_RANDOM_CONFIRM_VALUE_LENGTH; index++) 
            {
                clxConsoleUIEngineText("%02X", oobData.ptrStackOobKeys.randomLocal[index]);
            }

            clxConsoleUIEngineText("\nRandom Confirm: ");
            for (u4 index = 0; index < LE_RANDOM_CONFIRM_VALUE_LENGTH; index++) 
            {
                clxConsoleUIEngineText("%02X", oobData.ptrStackOobKeys.confirmLocal[index]);
            }
        }

        clxConsoleUIEngineText("\n");

        if ((2 == option) || (3 == option)) 
        {
            /* Enter the confirm and random values of remote device that are obtained using NFC communication */
            clxConsoleUIEngineInputBox("Enter the remote device’s random value (hexadecimal, without the “0x” prefix): ", oobData.input_buffer, MAX_INPUT_SIZE);
            inputByteCount = strlen(oobData.input_buffer) / 2;
            for (u4 index = 0; index < inputByteCount; index++) 
            {
                char byteStr[3] = { oobData.input_buffer[2 * index], oobData.input_buffer[2 * index + 1], '\0' };
                oobData.randomRemote[index] = (u1)strtol(byteStr, NULL, LE_RANDOM_CONFIRM_VALUE_LENGTH);
            }

            clxConsoleUIEngineInputBox("Enter the remote device’s confirm value (hexadecimal, without the “0x” prefix):", oobData.input_buffer, MAX_INPUT_SIZE);
            inputByteCount = strlen(oobData.input_buffer) / 2;
            for (u4 index = 0; index < inputByteCount; index++) 
            {
                char byteStr[3] = { oobData.input_buffer[2 * index], oobData.input_buffer[2 * index + 1], '\0' };
                oobData.confirmRemote[index] = (u1)strtol(byteStr, NULL, LE_RANDOM_CONFIRM_VALUE_LENGTH);
            }

            oobData.ptrStackOobKeys.randomRemote = oobData.randomRemote;
            oobData.ptrStackOobKeys.confirmRemote = oobData.confirmRemote;
        }
    }while(0);
}

/***************************************************************************************************************************************
*                                                enableDisableOob
*
* Enable or disable OOB authentication in the stack by calling the appropriate APIs based on user input.
*
* \param stack                  - Local device stack handle.
* \param bleConnectionHandle    - BLE Connection Handle of the connection remote device
* \param enable                 - boolean indicating whether to enable or disable OOB authentication
* 
* \return void
*
****************************************************************************************************************************************/
void enableDisableOob(ClxStack stack, ClxBleConnectionHandle bleConnectionHandle, boolean enable)
{
    /*
    Now, we have generated the local device OOB data and set the remote OOB data also to be passed to stack for pairing, if enabled */
    ClxResult ret = clxGapBleEnableDisableOobPairing(stack, 
                                                     bleConnectionHandle,
                                                     enable,
                                                     (oobData.pairingMode == ClxBlePairMode_Secure) ? TRUE : FALSE,
                                                     &oobData.ptrStackOobKeys,
                                                     TRUE);

    clxConsoleUIEngineText("\nclxGapBleEnableDisableOobPairing: %s status - %s\n",
                                                enable ? "Enable" : "Disable",
                                                clxGetErrorCodeText(ret));
}
#endif /* CLX_OOB_PAIRING_SUPPORT */

