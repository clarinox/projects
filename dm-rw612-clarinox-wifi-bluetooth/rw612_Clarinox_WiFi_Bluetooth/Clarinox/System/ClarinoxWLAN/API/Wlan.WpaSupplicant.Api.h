#ifndef wlan_wpa_supplicant_api_h
#define wlan_wpa_supplicant_api_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                Wlan.WpaSupplicant.Api.h
* Description         API to use WPA Supplicant with ClarinoxWLAN
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#if defined(CLX_WPA_SUPPLICANT)

/**
Indicates of an invalid WPA Supplicant network ID value (of type ClxWpaSupplicantNetworkID). 
*/
#define CLX_INVALID_WPA_SUPPLICANT_NETWORK_ID                       -1

/**
Refer to #clxInitWpaSupplicant or #clxInitWpaSupplicantRpcClient function.
*/
#define CLX_INIT_WPA_SUPPLICANT_COMPLETE                            0x7900

/**
Refer to #clxTerminateWpaSupplicant or #clxTerminateWpaSupplicantRpcClient function.
*/
#define CLX_TERMINATE_WPA_SUPPLICANT_COMPLETE                       0x7901

/**
Refer to #clxDestroyWpaSupplicantRpcClient function.
*/
#define CLX_DESTROY_WPA_SUPPLICANT_COMPLETE                   	    0x7902

/**
Refer to #clxWpaSupplicant_AddInterface function.
*/
#define CLX_WPA_SUPPLICANT_ADD_INTERFACE_COMPLETE                   0x7903

/**
Refer to #clxWpaSupplicant_RemoveInterface function.
*/
#define CLX_WPA_SUPPLICANT_REMOVE_INTERFACE_COMPLETE                0x7904

/**
Refer to #clxWpaSupplicant_AddWirelessNetwork function.
*/
#define CLX_WPA_SUPPLICANT_ADD_WIRELESS_NETWORK_COMPLETE            0x7905

/**
Refer to #clxWpaSupplicant_RemoveWirelessNetwork function.
*/
#define CLX_WPA_SUPPLICANT_REMOVE_WIRELESS_NETWORK_COMPLETE         0x7906

/**
Used Internally.
*/
#define CLX_WPA_SUPPLICANT_DOES_WIRELESS_NETWORK_EXIST_COMPLETE     0x7907

/**
Refer to #clxWpaSupplicant_AddHostApInterface function.
*/
#define CLX_WPA_SUPPLICANT_ADD_HOST_AP_INTERFACE_COMPLETE           0x7908

/**
Refer to #clxWpaSupplicant_AddWirelessNetworkEx function.
*/
#define CLX_WPA_SUPPLICANT_ADD_WIRELESS_NETWORK_EX_COMPLETE         0x7909

/**
Refer to #clxWpaSupplicant_RemoveWirelessNetworkEx function.
*/
#define CLX_WPA_SUPPLICANT_REMOVE_WIRELESS_NETWORK_EX_COMPLETE      0x790A

/**
Refer to #clxWpaSupplicant_GetWirelessNetworkByIndex function.
*/
#define CLX_WPA_SUPPLICANT_GET_WIRELESS_NETWORK_BY_INDEX_COMPLETE   0x790B

/**
Refer to #clxWpaSupplicant_SendBssTranstionReq function.
*/
#define CLX_WPA_SUPPLICANT_SEND_BSS_TRANSITION_REQ_COMPLETE         0x790C

#ifdef __cplusplus
extern "C" {
#endif


typedef ClxConfigValue ClxConfigWsSymbol;

CLX_DEFINE_CONFIG_TYPE(ClxConfigWsSymbol);

typedef s4 ClxWpaSupplicantNetworkID;


/**
Initializes WPA Supplicant stack. This function must be called before any other API may be used.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_INIT_WPA_SUPPLICANT_COMPLETE. This indication does not have any parameters.
				   
\param[ in ] indicationScheduler The scheduler object which will be used to schedule indications. This argument CANNOT be NULL.
\param[ in ] indCallbackFunc The indication call-back function. 
\param[ in ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode
                                       
\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
    
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: indicationScheduler or indCallbackFunc is NULL.
        - #CLX_ERROR_BAD_STATE: Bad state
*/
extern ClxResult clxInitWpaSupplicant(_in_ ClxScheduler indicationScheduler, 
                                      _in_ ClxApplicationCallbackFunc indCallbackFunc,
                                      _in_ boolean block);
/**
Initializes WPA Supplicant stack RPC client.

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_INIT_CLARINOX_WLAN_COMPLETE.
                   The parameter of this indication is of type #ClxInitClarinoxWlanComplete.

\param[ in  ] contextID   The ID of the command context in which this command will be executed
\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode
                                       
\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
    
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: indicationScheduler or indCallbackFunc is NULL.
        - #CLX_ERROR_BAD_STATE: Bad state

*/
extern ClxResult clxInitWpaSupplicantRpcClient(_in_ u1            contextID,
                                               _in_ boolean       block);


/**
Terminates WPA Supplicant stack. This command will not complete until WPA Supplicant has been terminated
(successfully or with an error).

NOTE : WPA Supplicant stack must already have been initialized by a previous call to #clxInitWpaSupplicant().
NOTE : When termination of the WPA Supplicant stack is complete with success, #clxDestroyWpaSupplicant() must be called
       to destroy the stack object.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_TERMINATE_WPA_SUPPLICANT_COMPLETE. This indication does not have any parameters.
\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode
                                
\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
    
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_BAD_STATE: Bad state
*/
extern ClxResult clxTerminateWpaSupplicant(_in_ boolean block);

/**
Terminates WPA Supplicant stack. This command will not complete until WPA Supplicant has been terminated
(successfully or with an error).

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_INIT_CLARINOX_WLAN_COMPLETE.
                   The parameter of this indication is of type #ClxInitClarinoxWlanComplete.

\param[ in  ] contextID   The ID of the command context in which this command will be executed
\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode
                                       
\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
    
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_BAD_STATE: Bad state
*/
extern ClxResult clxTerminateWpaSupplicantRpcClient(_in_ u1            contextID,
                                                    _in_ boolean       block);

/**
Destroys WPA Supplicant stack. This command must be called when the stack has been successfully terminated by a previous call to #clxTerminateWpaSupplicant.
*/
extern void clxDestroyWpaSupplicant(void);

/**
Destroys WPA Supplicant RPC client. This command must be called when the stack has been successfully terminated by a previous call to #clxTerminateWpaSupplicantRpcClient.
Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command

Non-blocking mode: This function will return immediately with the error code CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_INIT_CLARINOX_WLAN_COMPLETE.
                   The parameter of this indication is of type #ClxInitClarinoxWlanComplete.

\param[ in  ] contextID   The ID of the command context in which this command will be executed
\param[ in  ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode
                                       
\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
    
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_BAD_STATE: Bad state
*/
extern ClxResult clxDestroyWpaSupplicantRpcClient(_in_ u1            contextID,
                                                  _in_ boolean       block);


/**
Adds a non-AP virtual interface to WPA Supplicant.
The virtual interface must have been created by a previous call to #clxWlanCreateInterface(), and must have successfully
started by a call to #clxWlanStartInterface().

NOTE : WPA Supplicant must already have been initialized by a previous call to #clxInitWpaSupplicant().

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WPA_SUPPLICANT_ADD_INTERFACE_COMPLETE. This indication does not have any parameters.

wpa_supplicant.conf :

As the third parameter, name of the WPA Supplicant configuration file is passed. The file name is normally called 
wpa_supplicant.conf and contains general configuration parameters, along with wireless networks' information. The file 
could be read from ROM or the underlying file system (via Clarinox File BSP interface implementation).
A sample wpa_supplicant.conf file is as follows:

\code
# Makes sure WPA Supplicant will not try to connect to any network on its own. THIS PARAMETER IS MANDATORY.
ap_scan=0

# WPA-Personal(PSK) with TKIP and enforcement for frequent PTK rekeying
network={
	ssid="example"
	proto=WPA
	key_mgmt=WPA-PSK
	pairwise=TKIP
	group=TKIP
	psk="not so secure passphrase"
	wpa_ptk_rekey=600
}
\endcode

The structure of wpa_supplicant.conf, and the list of parameters which may be used are defined at
https://w1.fi/cgit/hostap/plain/wpa_supplicant/wpa_supplicant.conf.
Please refer to the documentation of #clxWpaSupplicant_AddWirelessNetwork() for more information about wireless network
configuration.

\param[ in ] service Service reference of type #ClxService for the virtual interface, as obtained by a previous call to #clxWlanCreateInterface().
                   
\param[ in ] ifName The unique name of the interface. The interface may be assigned any arbitrary name as long as it is 
                      unique among all registered interfaces.
                    This argument CANNOT be NULL.

\param[ in ] type Type of the virtual interface. This MUSt be exactly the same value passed to #clxWlanCreateInterface().

\param[ in ] configFileName Name of the file from which the configuration parameters for this interface will be obtained. 
                            The file must already exist and must have READ permission. This argument CANNOT be NULL. 
\param[ in ] block          Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
    
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicant_AddInterface(_in_ ClxService* service, 
                                               _user_in_ const s1* ifName,
                                               _in_ ClxInterfaceType type,
                                               _user_in_ const s1* configFileName, 
                                               _in_ boolean block);


/**
Adds an AP virtual interface to WPA Supplicant (hostsp).
The virtual interface must have been created by a previous call to #clxWlanCreateInterface(), and must have successfully
started by a call to #clxWlanStartInterface().

NOTE : WPA Supplicant must already have been initialized by a previous call to #clxInitWpaSupplicant().

Blocking mode: This function will not return until the command is complete. The function return value indicates the
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WPA_SUPPLICANT_ADD_HOST_AP_INTERFACE_COMPLETE. This indication does not have any parameters.

\param[ in ] service Service reference of type #ClxService for the virtual interface, as obtained by a previous call to #clxWlanCreateInterface().

\param[ in ] type Type of the virtual interface. This MUSt be exactly the same value passed to #clxWlanCreateInterface().

\param[ in ] ifName The unique name of the interface. The interface may be assigned any arbitrary name as long as it is
                    unique among all registered interfaces. This argument CANNOT be NULL.

\param[ in ] ssid SSID of the AccessPoint which is identified by this service. This argument CANNOT be NULL.
                            
\param[ in ] parameters List of configuration parameters. These are the same parameters passed to hostapd.conf
                        Refer to https://web.mit.edu/freebsd/head/contrib/wpa/hostapd/hostapd.conf for more details.
                        NOTE : Please refer to the documents for #clxWpaSupplicant_AddWirelessNetwork() for details on how to prepare the list.
                        This argument may be NULL.

\param[ in ] block Indicates mode of operation:
                   TRUE: Blocking mode
                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicant_AddHostApInterface(_in_ ClxService* service,
                                                     _user_in_ const s1* ifName,
                                                     _in_ ClxInterfaceType type,
                                                     _user_in_ const ClxSSID* ssid,
                                                     _inout_ ClxConfigList* parameters,
                                                     _in_ boolean block);


/**
Removes a virtual interface from WPA Supplicant list. The interface must already have been added to WPA Supplicant by a 
previous call to #clxWpaSupplicant_AddInterface().

IMPORTANT : Before a virtual interface may be stopped (by a call to #clxWlanStopInterface), it MUST be removed from WPA 
            Supplicant list. Otherwise, the behaviour will be undefined, and the application may crash.

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WPA_SUPPLICANT_REMOVE_INTERFACE_COMPLETE. This indication does not have any parameters.

\param[ in ] service Service reference of type #ClxService for the virtual interface, as obtained by a previous call to #clxWlanCreateInterface().
\param[ in ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
    
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicant_RemoveInterface(_in_ ClxService* service, 
                                                  _in_ boolean block);



/**
Adds a wireless network to the list of known wireless networks of a virtual interface. The virtual interface should be
in Station role. Information about a wireless network is generally obtained from scan results
(please refer to #clxWlanScan() for more information about scan results).

NOTE : Before #clxWlanConnect() is called to establish a connection to a wireless network, the network MUST be added to
       the list of wireless network by a call to this function. Otherwise, WPA Supplicant will not be able to carry out
       authentication measures during the connection establishment procedure, as it does not have the security
       credentials of the network.

NOTE : Modifying the configuration parameters of the selected network entry, to which a connection is currently being established, may result in undefined behaviour.  

Blocking mode: This function will not return until the command is complete. The function return value indicates the
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WPA_SUPPLICANT_ADD_WIRELESS_NETWORK_EX_COMPLETE. This indication does not have any parameters.

A wireless network is uniquely identified by its NetworkID (of type ClxWpaSupplicantNetworkID). Only one entry for each wireless network may exist in the
list of known networks of a virtual interface. If this function is called to add an existing wireless network, then the
provided parameters will be replaced in the current entry. In this case, the existing parameters which are not being re-configured
(e.g. they are not in the list of parameters passed to this function), will NOT be modified.

There are two ways to add a wireless network to the list of known networks of a virtual interface:

Static : The wireless networks, along with their security credentials, may be passed to WPA Supplicant in the
         configuration file (wpa_supplicant.conf). The details of the wireless networks are read from the configuration
         files and automatically added to the list of known wireless networks of the virtual interface. Afterwards, any
         modification of the file by the application will not have any effect.

Dynamic: Wireless networks may be added at run time by a call to this function. The function may be used to add
         new wireless networks, or modify the details of the networks already added to the list (either statically via
         the configuration file, or dynamically by a previous call to this function).

The parameters and values, which are passed as the forth argument to this function, are exactly the same as those passed
in the configuration file. 

The following configuration objects types may be used:

ClxConfigInteger : If the value of a parameter is an integer, this object must be used to pass the parameter to this
                   function.

Example :

    wpa_ptk_rekey=600

can be passed as follows:

    \code
    ClxConfigInteger wpaPtkRekey;
    clxConfigInitIntegerParam(&wpaPtkRekey, "wpa_ptk_rekey", 600, &list);
    \endcode

ClxConfigString : If the value of a parameter is a string, this object must be used to pass the parameter to this
                  function.
                  Please note that the value of a parameter is a string ONLY if it is enclosed in double quotes.
                  For instance identity="user@example.com" is a string but key_mgmt=WPA-PSK is NOT a string.

Example :

    password="foobar"

can be passed as follows:

    \code
    ClxConfigString password;
    clxConfigInitStringParam(&password, "password", "foobar", &list);
    \endcode

ClxConfigData : If the value of a parameter is binary data, this object must be used to pass the parameter to this
                function.
                The value of binary configuration parameter is encoded in HEX in the configuration file.
                Please note that the binary data (non-encoded) must be passed to this function.
                Also, ClxConfigString CANNOT be used to pass the value of a binary data parameter in HEX format.


Example :

    psk=06b4be19da289f475aa46a33cb793029d4ab3db7a23ee92382eb0106c72ac7bb

can be passed as follows:

    \code
    ClxConfigData psk;

    u1 pskValue[] = {0x06, 0xb4, 0xbe, 0x19, 0xda, 0x28, 0x9f, 0x47,
                     0x5a, 0xa4, 0x6a, 0x33, 0xcb, 0x79, 0x30, 0x29,
                     0xd4, 0xab, 0x3d, 0xb7, 0xa2, 0x3e, 0xe9, 0x23,
                     0x82, 0xeb, 0x01, 0x06, 0xc7, 0x2a, 0xc7, 0xbb};

    clxConfigInitDataParam(&psk, "psk", pskValue, sizeof(pskValue), &list);
    \endcode

ClxConfigWsSymbol : If the value of a parameter does not fall into any of the categories mentioned above, ClxConfigWsSymbol
                    must be used.
                    This includes the parameters which have a string value but the value is NOT enclosed in double quotes.

                    As an example, all of the following parameters must be passed as ClxConfigWsSymbol objects:
                    proto
                    key_mgmt
                    pairwise
                    group
                    eap

Example:

    key_mgmt=WPA-EAP

can be passed as follows:

    \code
    ClxConfigWsSymbol keyMgmt;
    clxConfigInitWsSymbolParam(&keyMgmt, "key_mgmt", "WPA-EAP", &list);
    \endcode

A full network example:

Passed statically in the configuration file:

\code
# Only WPA-PSK is used. Any valid cipher combination is accepted.
network={
    ssid="example"
    proto=WPA
    key_mgmt=WPA-PSK
    pairwise=CCMP TKIP
    group=CCMP TKIP WEP104 WEP40
    psk="very secret passphrase"
    priority=2
}
\endcode

Passed dynamically:

\code
struct WirelessNetwork
{
    ClxConfigList       parent;

    ClxConfigString     ssid;

    ClxConfigWsSymbol   protocol;
    ClxConfigWsSymbol   keyMgmt;
    ClxConfigWsSymbol   pairwise;
    ClxConfigWsSymbol   groupwise;

    ClxConfigString    psk;
    ClxConfigInteger priority;
};

struct WirelessNetwork network;

clxConfigInitParamsList(&network.parent, NULL, NULL);
clxConfigInitStringParam(&network.ssid, "ssid", "example", &network.parent);
clxConfigInitWsSymbolParam(&network.protocol, "proto", "WPA", &network.parent);
clxConfigInitWsSymbolParam(&network.keyMgmt, "key_mgmt", "WPA-PSK", &network.parent);
clxConfigInitWsSymbolParam(&network.pairwise, "pairwise", "CCMP TKIP", &network.parent);
clxConfigInitWsSymbolParam(&network.groupwise, "group", "CCMP TKIP WEP104 WEP40", &network.parent);
clxConfigInitStringParam(&network.psk, "psk", "very secret passphrase", &network.parent);
clxConfigInitIntegerParam(&network.priority, "priority", 2, &network.parent);

ClxWpaSupplicantNetworkID networkID = CLX_INVALID_WPA_SUPPLICANT_NETWORK_ID;

clxWpaSupplicant_AddWirelessNetwork(service, &networkID, &network.parent);
\endcode

\param[ in ] service Service reference of type #ClxService for the virtual interface, as obtained by a previous call to #clxWlanCreateInterface().
\param[ in ] networkID As an input, this value indicates the network ID of the entry to be modified. If set to CLX_INVALID_WPA_SUPPLICANT_NETWORK_ID, a new entry
                       will be created and its networkID will be returned by this argument. If set to a valid network ID which does not exist, this command will complete with the error #CLX_SYSTEM_ENOENT.
                       This argument cannot be NULL.
\param[ in ] parameters List of configuration parameters. This argument may be NULL.
\param[ in ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_SYSTEM_ENOENT: An entry with the provided valid networkID was not found
        - Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicant_AddWirelessNetworkEx(_in_ ClxService* service,
                                                       _inout_ ClxWpaSupplicantNetworkID* networkID,
                                                       _inout_ ClxConfigList* parameters,
                                                       _in_ boolean block);


/**
This command works like #clxWpaSupplicant_AddWirelessNetworkEx, with the exception that it identifies network entries by the SSID only.
If there is no network entry with the provided SSID, a new entry will be created. Otherwise, the existing entry will be modified.
NOTE : If there is more than one entry with the same SSID, this command will modify the very first entry it finds.

NOTE : The configuration parameters passed are the same as those passed to #clxWpaSupplicant_AddWirelessNetworkEx. The only exception is the 'ssid' parameter 
       which is passed directly to this function as second argument. it must NEVER be passed as a configuration parameter.

NOTE : Use this command only if the application guarantees that there is only one entry per SSID. Otherwise, the behaviour may be undefined.

\param[ in ] service Service reference of type #ClxService for the virtual interface, as obtained by a previous call to #clxWlanCreateInterface().
\param[ in ] ssid SSID of the network to be added. This argument CANNOT be NULL.
\param[ in ] parameters List of configuration parameters. This argument may be NULL.
\param[ in ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicant_AddWirelessNetwork(_in_ ClxService* service,
                                                     _user_in_ const ClxSSID* ssid,
                                                     _inout_ ClxConfigList* parameters,
                                                     _in_ boolean block);


/**
Removes a wireless network entry from the list of known wireless networks of a virtual interface.

The entry must have been added statically (via the configuration file),
or dynamically (by a previous call to #clxWpaSupplicant_AddWirelessNetworkEx).

Blocking mode: This function will not return until the command is complete. The function return value indicates the 
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WPA_SUPPLICANT_REMOVE_WIRELESS_NETWORK_EX_COMPLETE. This indication does not have any parameters.

\param[ in ] service Service reference of type #ClxService for the virtual interface, as obtained by a previous call to #clxWlanCreateInterface().
\param[ in ] networkID The ID of the network to remove. If a network entry with the provided ID does not exist, the command will be complete with the error #CLX_SYSTEM_ENOENT. 
\param[ in ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
    
        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_SYSTEM_ENOENT: An entry with the provided networkID was not found
        - Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicant_RemoveWirelessNetworkEx(_in_ ClxService* service, 
                                                          _in_ ClxWpaSupplicantNetworkID networkID,
                                                          _in_ boolean block);


/**
Removes a wireless network entry from the list of known wireless networks of a virtual interface.

The entry must have been added statically (via the configuration file),
or dynamically (by a previous call to #clxWpaSupplicant_AddWirelessNetwork or #clxWpaSupplicant_AddWirelessNetworkEx).

NOTE : Use this command only if the application guarantees that there is only one entry per SSID. Otherwise, the behaviour may be undefined.

Blocking mode: This function will not return until the command is complete. The function return value indicates the
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WPA_SUPPLICANT_REMOVE_WIRELESS_NETWORK_COMPLETE. This indication does not have any parameters.

\param[ in ] service Service reference of type #ClxService for the virtual interface, as obtained by a previous call to #clxWlanCreateInterface().
\param[ in ] ssid SSID of the network to be removed. If a network entry with the provided SSID does not exist, the command will be complete with the error #CLX_SYSTEM_ENOENT. 
                  If more than one network entry with the provided SSID exists, the very first entry on the list will be removed.
                  This argument CANNOT be NULL.
\param[ in ] block            Indicates mode of operation:
                                   TRUE: Blocking mode
                                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_SYSTEM_ENOENT: An entry with the provided SSID was not found
        - Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicant_RemoveWirelessNetwork(_in_ ClxService* service,
                                                        _user_in_ const ClxSSID* ssid,
                                                        _in_ boolean block);



/**
Retrieves a network entry by its zero-based index on the list. Please note that the index is different from the network ID.

If the network entry with the provided index exists, its network ID and (optionally) a caller-defined set of its parameters will be returned.

Blocking mode: This function will not return until the command is complete. The function return value indicates the
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WPA_SUPPLICANT_GET_WIRELESS_NETWORK_BY_INDEX_COMPLETE. This indication does not have any parameters.

\param[ in ] service        Service reference of type #ClxService for the virtual interface, as obtained by a previous call to #clxWlanCreateInterface().
\param[ in ] index          The zero-based index of the network entry on the list. If a network entry with the provided index does not exist, the command will be complete with the error #CLX_SYSTEM_ENOENT.
                            This argument CANNOT be NULL.
\param[ out ] networkID     Upon successful completion of the command, this argument will hold the network ID of the network entry with the provided index.
\param[ inout ] parameters  An optional list of parameters which, upon successful completion of the command, will contain the requested parameters of the network entry. 
\param[ in ] block          Indicates mode of operation:
                            TRUE: Blocking mode
                            FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_SYSTEM_ENOENT: An entry with the provided index does not exist
        - Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicant_GetWirelessNetworkByIndex(_in_ ClxService* service,
                                                            _in_ u4 index,
                                                            _user_out_ ClxWpaSupplicantNetworkID* networkID,
                                                            _inout_ ClxConfigList* parameters,
                                                            _in_ boolean block);

/**
Sends a transition request from the AP to the station connected to it.
This function is defined for the 802.11v standard implementation. For it to work, CONFIG_WNM_AP must be defined.

Blocking mode: This function will not return until the command is complete. The function return value indicates the
               result of the command.

Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type
                   #CLX_WPA_SUPPLICANT_SEND_BSS_TRANSITION_REQ_COMPLETE. This indication does not have any parameters.

\param[ in ] service Service reference of type #ClxService for the virtual interface, as obtained by a previous call to #clxWlanCreateInterface().

\param[ in ] ifName The unique name of the interface. The interface may be assigned any arbitrary name as long as it is
                    unique among all registered interfaces. This argument CANNOT be NULL.

\param[ in ] type Type of the virtual interface. This MUSt be exactly the same value passed to #clxWlanCreateInterface().

\param[ in ] cmdBTM A formatting template string used to construct an 802.11v BSS Transition Management (BTM) Request command.
                    This template is dynamically populated with runtime parameters (such as the client MAC, target BSSID,
                    channel, and capability bitmask) before being sent to the hostapd control interface to steer the client.

\param[ in ] block Indicates mode of operation:
                   TRUE: Blocking mode
                   FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicant_SendBssTransitionReq(_in_ ClxService* service,
    _user_in_ const s1* ifName,
    _in_ ClxInterfaceType type,
	_user_in_ const s1* cmdBTM,
    _in_ boolean block);


/**
 Initializes the subsequent member of parentList with the given object of type #ClxConfigWsSymbol (Wpa_Supplicant Symbol).
 
 A configuration parameter of type #ClxConfigWsSymbol is used when the value of a wpa_supplicant (or hostap) parameter is a string but it is NOT to be enclosed in double quotes.
 NOTE : If the value of a wpa_supplicant (or hostap) parameter which is to be a string but it is to be enclosed in double quotes, the type #ClxConfigString must be used.

 \param[ in ] object a pointer to the an object of type ClxConfigWsSymbol
 \param[ in ] paramName string pointer to name of the parameter.
 \param[ in ] paramValue string pointer to the value of this object.
 \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
extern void clxConfigInitWsSymbolParam(ClxConfigWsSymbol* object, const s1* paramName, const s1* paramValue, ClxConfigList* parentList);


#ifdef __cplusplus
}
#endif


#endif // #if defined(CLX_WPA_SUPPLICANT)

#endif // wlan_wpa_supplicant_api_h




