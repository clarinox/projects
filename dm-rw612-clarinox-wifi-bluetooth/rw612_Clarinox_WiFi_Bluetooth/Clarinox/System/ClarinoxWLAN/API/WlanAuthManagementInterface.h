#ifndef WlanAuthManagementInterface_h
#define WlanAuthManagementInterface_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                WlanAuthManagementInterface.h
* Description         Clarinox WLAN stack Authentication Management Interface
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#define CLX_IEEE80211_MIN_HEADER_LENGTH                                                             24
#define CLX_IEEE80211_MAX_HEADER_LENGTH                                                             30

#define CLX_WLAN_MANAGEMENT_INDICATION_BSS_DISCOVERED                                               0x0A01
#define CLX_WLAN_MANAGEMENT_INDICATION_BSS_ASSOCIATION_COMPLETE                                     0x0A02
#define CLX_WLAN_MANAGEMENT_INDICATION_BSS_DEAUTHENTICATED                                          0x0A03
#define CLX_WLAN_MANAGEMENT_INDICATION_SCAN_COMPLETE                                                0x0A04
#define CLX_WLAN_MANAGEMENT_INDICATION_RX_DATA_FRAME_RECV_RECEIVED                                  0x0A05
#define CLX_WLAN_MANAGEMENT_INDICATION_RX_MANAGEMENT_FRAME_RECEIVED                                 0x0A06
#define CLX_WLAN_MANAGEMENT_INDICATION_START_PRE_ASSOC_AUTHENTICATION                               0x0A07
#define CLX_WLAN_MANAGEMENT_INDICATION_CANCEL_PRE_ASSOC_AUTHENTICATION                              0x0A08
#define CLX_WLAN_MANAGEMENT_INDICATION_INTERNAL_SCAN_STARTED                                        0x0A09
#define CLX_WLAN_MANAGEMENT_INDICATION_BSS_SELECTED                                                 0x0A0A      /* A BSS is selected for connection (only in STA role) */
#define CLX_WLAN_MANAGEMENT_INDICATION_RX_AUTH_FRAME_RECEIVED                                       0x0A0B


#define CLX_WLAN_CONFIG_SUPPORTED_NON_HT_RATE_SET                                                   1          /* Config Param is of type ClxConfigData (Value will include the IEEE802.11 IEs back to back including headers) */
#define CLX_WLAN_CONFIG_DTIM_PERIOD                                                                 2          /* In number of beacons (and NOT time units) */
#define CLX_WLAN_CONFIG_CAPABILITY_INFORMATION                                                      3          /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_BEACON_INTERVAL                                                             4          /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_ASSOCIATION_ID                                                              5          /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_OPERATIONAL_CHANNELS_LIST                                                   6          /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_BSSID                                                                       7          /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_INTERFACE_MAC_ADDRESS                                                       8          /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_DEVICE_MAC_ADDRESS                                                          9          /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_OPERATING_CHANNEL                                                           10         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_OPERATING_ERP_INFORMATION                                                   11         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_SSID                                                                        12         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_ROBUST_SECURITY_NETWORK                                                     13         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header)  */
#define CLX_WLAN_CONFIG_WPA                                                                         14         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header)  */
#define CLX_WLAN_CONFIG_HT_CAPABILITIES                                                             15         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_HT_OPERATION                                                                16         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_AP_CLIENT_INACTIVITY_TIMEOUT                                                17         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_HIDDEN_SSID                                                                 18         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_RTS_THRESHOLD                                                               19         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_MAC_LAYER_MTU                                                               20         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_MAX_NUM_OF_CLIENTS                                                          21         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_TX_POWER                                                                    22         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_LISTEN_INTERVAL                                                             23         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_SECURITY_PASSKEY                                                            25         /* Config Param is of type ClxConfigData (Value will be the Clarinox-specific config IE including the header) */
#define CLX_WLAN_CONFIG_VHT_CAPABILITIES                                                            26         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_VHT_OPERATION                                                               27         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_WMM_WME_INFORMATION_ELEMENT                                                 30         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_WMM_WME_PARAMETER_ELEMENT                                                   31         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_WPS_ENABLED                                                                 32         /* Config Param is of type ClxConfigUnsigned */
#define CLX_WLAN_CONFIG_SECURITY_CONFIGURATION_ELEMENT                                              33         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header). 
                                                                                                                  Accessible via clxWlanManagementCommand_GetRemoteConfigParam() for both Local and Remote stations in STA role */
#define CLX_WLAN_CONFIG_EXTENDED_CAPABILITIES                                                       34         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_HE_CAPABILITIES                                                             35         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */
#define CLX_WLAN_CONFIG_HE_OPERATION                                                                36         /* Config Param is of type ClxConfigData (Value will be the IEEE802.11 IE including the header) */

#ifdef __cplusplus
extern "C" {
#endif


    /********************************************
    ClxWlanManagement_IndicationHandler
    *********************************************/
    struct ClxWlanManagement_IndicationHandlerStruct;
    typedef struct ClxWlanManagement_IndicationHandlerStruct ClxWlanManagement_IndicationHandler;


    /********************************************
    ClxWlanMacHeader
    *********************************************/
    typedef struct ClxWlanMacHeaderStruct
    {
        u2 frameCtrl;
        u1 destAddr[CLX_MAC_ADDRESS_LENGTH];
        u1 srcAddr[CLX_MAC_ADDRESS_LENGTH];
        u1 bssid[CLX_MAC_ADDRESS_LENGTH];
    } ClxWlanMacHeader;



    /********************************************
    ClxWlanStackBufferDescriptor
    *********************************************/
    typedef struct ClxWlanStackBufferDescriptorStruct
    {
        ClxNetworkBufferDescriptor obj;
    } ClxWlanStackBufferDescriptor;



    /********************************************
    ClxWlanManagementIndication
    *********************************************/
    typedef struct ClxWlanManagementIndicationStruct
    {
        u2 indicationID;
    } ClxWlanManagementIndication;



    /********************************************
    ClxWlanManagement_IndicationHandlerFunction
    *********************************************/
    typedef boolean (*ClxWlanManagement_IndicationHandlerFunction) (ClxWlanManagement_IndicationHandler* this_,
                                                                    const ClxWlanManagementIndication* indication);


    /************************************************
    struct ClxWlanManagement_IndicationHandlerStruct
    *************************************************/
    struct ClxWlanManagement_IndicationHandlerStruct
    {
        ClxWlanManagement_IndicationHandlerFunction handle;
    };



    /********************************************
    ClxWlanManagementIndication_BssDiscovered
    *********************************************/
    typedef struct ClxWlanManagementIndication_BssDiscoveredStruct
    {
        ClxWlanManagementIndication     base;

        ClxWlanMacHeader                macHeader;

        u2                              beaconInterval;
        u2                              capabilityInfo;
        u4                              tsf_MSB;
        u4                              tsf_LSB;
        const u1*                       ies;
        u4                              iesLength;
        u1                              channel;
        ClxWlanFrequencyBand            band;
        s1                              rssi;
        s1                              noise;
    } ClxWlanManagementIndication_BssDiscovered;



    /*****************************************************
    ClxWlanManagementIndication_AssociationComplete
    *****************************************************/
    typedef struct ClxWlanManagementIndication_AssociationCompleteStruct
    {
        ClxWlanManagementIndication                 base;

        u1                                          linkMacAddress[CLX_MAC_ADDRESS_LENGTH];
        
        ClxResult                                   result;

        boolean                                     reassociation;

        u2                                          channelNumber;
        ClxWlanFrequencyBand                        frequencyBand;

        const ClxWlanStackBufferDescriptor*         beaconPayloadDescr;
        const ClxWlanStackBufferDescriptor*         assocReqPayloadDescr;
        const ClxWlanStackBufferDescriptor*         assocRspPayloadDescr;
    } ClxWlanManagementIndication_AssociationComplete;


    /********************************************
    ClxWlanManagementIndication_Deauthenticated
    *********************************************/
    typedef struct ClxWlanManagementIndication_DeauthenticatedStruct
    {
        ClxWlanManagementIndication     base;

        u1                              linkMacAddress[CLX_MAC_ADDRESS_LENGTH];
    } ClxWlanManagementIndication_Deauthenticated;


    /********************************************
    ClxWlanManagementIndication_ScanComplete
    *********************************************/
    typedef struct ClxWlanManagementIndication_ScanCompleteStruct
    {
        ClxWlanManagementIndication     base;

        boolean                         internalScan;   /* TRUE if the scan session has been initiated by the WLAN stack and not the external management interface */
        s4                              result;
    } ClxWlanManagementIndication_ScanComplete;


    /********************************************************
    ClxWlanManagementIndication_PreAssocAuthenticationStruct
    ********************************************************/
    typedef struct ClxWlanManagementIndication_PreAssocAuthenticationStruct
    {
        ClxWlanManagementIndication                 base;

        ClxSSID                                     ssid;
        ClxWlanManagementIndication_BssDiscovered   bss;
    } ClxWlanManagementIndication_PreAssocAuthentication;



    /********************************************************
    ClxWlanManagementIndication_BssSelected
    ********************************************************/
    typedef struct ClxWlanManagementIndication_BssSelectedStruct
    {
        ClxWlanManagementIndication                 base;

		ClxSSID										ssid;
        ClxWlanManagementIndication_BssDiscovered   bss;
    } ClxWlanManagementIndication_BssSelected;



    /********************************************************
    ClxWlanManagementIndication_FrameReceived
    ********************************************************/
    typedef struct ClxWlanManagementIndication_FrameReceivedStruct
    {
        ClxWlanManagementIndication                 base;

        ClxWlanStackBufferDescriptor*               desc;
        ClxWlanMacHeader                            macHeader;

        u2                                          etherType;      /* Valid for Data frames only */

        u1                                          channel;
        u1                                          band;
        s4                                          rssi;
    } ClxWlanManagementIndication_FrameReceived;



    /********************************************
    Network Interface Commands:
    *********************************************/
    extern ClxResult clxWlanManagementCommand_SendManagementFrame(_in_ ClxA2lDispCommandModuleID      moduleID,
                                                                  _in_ ClxWlanStackBufferDescriptor*  desc,
                                                                  _in_ u2                             subtype,
                                                                  _in_ const u1*                      destAddr,
                                                                  _in_ const u1*                      srcAddr,
                                                                  _in_ const u1*                      bssid,
                                                                  _in_ boolean                        block);

    extern ClxResult clxWlanManagementCommand_SendDataFrame(_in_ ClxA2lDispCommandModuleID      moduleID,
                                                            _in_ ClxWlanStackBufferDescriptor*  desc,
                                                            _in_ const u1*                      destAddr,
                                                            _in_ const u1*                      srcAddr,
                                                            _in_ u2                             etherType,
                                                            _in_ boolean                        block);


    extern ClxResult clxWlanManagementCommand_ApplyEncryptionKey (_in_ ClxA2lDispCommandModuleID  moduleID,
                                                                  _in_ const u1*                  linkMacAddress,
                                                                  _in_ u4                         cipher,
                                                                  _in_ ClxWlanKeyType             keyType,
                                                                  _in_ const u1*                  key,
                                                                  _in_ u4                         keyLength,
                                                                  _in_ u4                         keyIndex,
                                                                  _in_ const u1*                  txSequence,
                                                                  _in_ boolean                    setAsCurrentKey);


    extern ClxResult clxWlanManagementCommand_GetLocalConfigParam(_in_ ClxA2lDispCommandModuleID  moduleID,
                                                                  _in_ u4                         parameterID,
                                                                  _out_ ClxConfigParam*           parameter);

    extern ClxResult clxWlanManagementCommand_GetRemoteConfigParam(_in_ ClxA2lDispCommandModuleID  moduleID,
                                                                   _in_ const u1*                  address,
                                                                   _in_ u4                         parameterID,
                                                                   _out_ ClxConfigParam*           parameter);
 


    extern ClxResult clxWlanManagementCommand_Scan (_in_ ClxA2lDispCommandModuleID  moduleID,
                                                    _in_ const u1*                  ssid,
                                                    _in_ u4                         ssidLen);


    extern ClxResult clxWlanManagementCommand_Authenticate(_in_ ClxA2lDispCommandModuleID   moduleID,
                                                           _in_ const u1*                   bssid,
                                                           _in_ u2                          algorithm,
                                                           _in_ u2                          authTransactionSeqNo,
                                                           _in_ u2                          statusCode,
                                                           _in_ const u1*                   extraAuthFields,
                                                           _in_ u4                          extraAuthFieldsLength,
                                                           _in_ const u1*                   authIEs,
                                                           _in_ u4                          authIEsLength);


    extern ClxResult clxWlanManagementCommand_Associate (_in_ ClxA2lDispCommandModuleID  moduleID,
                                                         _in_ const ClxSSID*             ssid,
                                                         _in_ const u1*                  bssid,
                                                         _in_ const u1*                  assocReqIEs,
                                                         _in_ u4                         assocReqIEsLength);

    extern ClxResult clxWlanManagementCommand_Deauthenticate (_in_ ClxA2lDispCommandModuleID  moduleID,
                                                              _in_ const u1*                  linkMacAddress,
                                                              _in_ u1                         ieee802_11_Reason);


    extern ClxResult clxWlanManagementCommand_PreAssocAuthenticationComplete (_in_ ClxA2lDispCommandModuleID  moduleID,
                                                                              _in_ const u1*                  ssid,
                                                                              _in_ u4                         ssidLen,
                                                                              _in_ const u1*                  macAddress,
                                                                              _in_ u2                         status);

    extern ClxResult clxWlanManagementCommand_ApConfigComplete(_in_ ClxA2lDispCommandModuleID  moduleID,
                                                               _in_ ClxResult                  result);

    extern ClxResult clxWlanManagementCommand_SetLocalIEs(_in_ ClxA2lDispCommandModuleID  moduleID,
                                                          _in_ const u1*                  ies,
                                                          _in_ u4                         iesLength);

    extern ClxWlanStackBufferDescriptor* clxWlanManagementCommand_AllocateTxDescriptor(_in_ ClxA2lDispCommandModuleID  moduleID,
                                                                                       _in_ u2                         maxPayloadSize);

    extern ClxWlanManagement_IndicationHandler* clxWlanManagementCommand_RegisterIndicationHandler(_in_ ClxA2lDispCommandModuleID                    moduleID,
                                                                                                   _in_ ClxScheduler                                 scheduler,
                                                                                                   _in_ ClxWlanManagement_IndicationHandlerFunction  handlerFunction,
                                                                                                   _in_ size_t                                       objectSize,
                                                                                                   _in_ u1                                           priority);

    extern void clxWlanManagementCommand_UnregisterIndicationHandler(_in_ ClxA2lDispCommandModuleID              moduleID,
                                                                     _in_ ClxWlanManagement_IndicationHandler*   arg);

    extern u2 clxWlanManagementCommand_EncodeMacHeader(_in_ const ClxWlanMacHeader*  hdr,
                                                       _in_ u2                       dataLength,
                                                       _out_ u1*                     data);

    extern u2 clxWlanManagementCommand_DecodeMacHeader(_in_ const u1*           data,
                                                       _in_ u2                  dataLength,
                                                       _out_ ClxWlanMacHeader*  hdr);

#ifdef __cplusplus
}
#endif



#endif    // WlanAuthManagementInterface_h

/******************************************************************************/
/* 1. MISRA C 2004 RULE VIOLATION:                                            */
/* Message       : Identifiers (internal and external) shall not rely on the  */
/*                 significance of more than 31 characters.                   */
/* Rule          : MISRA-C:2004 Rule 5.1                                      */
/* Justification : Improves clarity of macro definitions. The compiler used   */
/*                 supports symbols longer than 31 characters, hence no risks.*/
/******************************************************************************/


/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused type declarations.     */
/* Rule          : MISRA-C:2012 Rule 2.3                                      */ 
/* Justification : Unused type declarations are to be used in user            */
/*                 applications.                                              */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations.      */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user          */ 
/*                 applications.                                              */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations.    */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user        */ 
/*                 applications.                                              */
/******************************************************************************/

