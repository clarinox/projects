#ifndef ClarinoxWlan_h
#define ClarinoxWlan_h

/*******************************************************************************
*
* Project             ClarinoxWLAN
* File                ClarinoxWlan.h
* Description         ClarinoxWlan Protocol Stack
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#include "ClarinoxWlanConst.h"
#include "WlanStackPacketCaptureInterface.h"
#include "Wlan.Config.h"
#include "Wlan.Api.h"
#if defined(CLX_WIFI_OVER_LAN)
#   include "WiFiOverLAN.Api.h"
#endif
#include "WlanAuthManagementInterface.h"


#ifdef __cplusplus
extern "C" {
#endif


struct ClxWlanPhysicalInterface;

typedef struct ClxWlanDriverEntryStruct
{
    struct ClxWlanPhysicalInterface* (*create) (_in_ void* context);
    void                             (*destroy) (struct ClxWlanPhysicalInterface* entry);
} ClxWlanDriverEntry;


/**
Data Structure for the indication #CLX_INIT_CLARINOX_WLAN_COMPLETE
*/
typedef struct ClxInitClarinoxWlanCompleteStruct
{
    _user_out_ ClxStack*    stack;			   /*!< pointer to a variable which, on successful completion, will point to the WLAN stack object. */
} ClxInitClarinoxWlanComplete;


/**
Initiates WLAN stack. When this function is used in non-blocking mode returns immediately. Upon initialization of the stack is complete,
an indication of type #CLX_INIT_CLARINOX_WLAN_COMPLETE will be sent to the call-back function. Due to the internal architecture, 
we always need a service handle to perform a non-blocking API call. However, when calling clxInitClarinoxWlan() and clxTerminateClarinoxWlan(), 
there is no service handle available (e.g. there is no virtual interface created). Therefore, we use an internal service to perform the non-blocking call. 
This internal service is passed to the event handler call-back function (#CLX_INIT_CLARINOX_WLAN_COMPLETE indication), 
but it is NOT used for any other API calls and must be ignored.
The errorCode parameter of the call-back function must be checked, to
see if the stack has been initialized successfully. Refer \ref sec_wlan_architecture_initStack for more information on usage.
\code
if (clxInitClarinoxWlan(&params, FALSE, stackMessageHandler, NULL, NULL, &stack, FALSE) != CLX_ERROR_COMPLETION_PENDING)
{
ClxConsoleUIEngine::text ("Initialization of ClarinoxWlan failed\n");
return 0;
}
\endcode

If this function is used in blocking mode, then it returns upon successful completion of the WLAN stack.
\code
if (clxInitClarinoxWlan(&params, FALSE, stackMessageHandler, NULL, NULL, &stack, TRUE) != CLX_SUCCESS)
{
ClxConsoleUIEngine::text ("Initialization of ClarinoxWlan failed\n");
return 0;
}
\endcode

\param[ in  ] driverEntry             The entry to the WLAN hardware driver code. This object is provided by Clarinox. This argument CANNOT be NULL.
\param[ in  ] indicationScheduler     An optional scheduler object to be used for scheduling ClarinoxBlue application indications. If NULL, a new thread with its own dedicated scheduler 
                                        will be internally started for the application indications.
\param[ in  ] indicationCallbackFunc  A pointer to the call-back functions which will receive the indications. This parameter CANNOT be NULL.
\param[ inout ] configList              The list of parameters to be configured, as a set of name/value pairs.
                                        The list object, and all its child objects, must not be modified or deleted until this command is complete.
                                        These objects are all allocated by the caller. See \ref page_wlan_configParams for the list of configuration items.  
\param[ out ] stack                   A pointer to a variable which, on successful completion, will point to the WLAN stack object.
\param[ in  ] block                   Indicates mode of operation:
                                        TRUE: Blocking mode
                                        FALSE: Non-blocking mode

\return In blocking mode, #CLX_SUCCESS if successful.
        In non-blocking mode, result of the actual operation will be passed to the callback function. 
        
        Other possible return values are:

        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT: The argument indicationCallbackFunc is NULL.
        - #CLX_WLAN_FAILED: The initialization of ClarinoxWLAN stack has failed.
*/
ClxError clxInitClarinoxWlan(_in_ const ClxWlanDriverEntry*   driverEntry,
                             _in_ ClxScheduler                indicationScheduler,
                             _in_ ClxApplicationCallbackFunc  indicationCallbackFunc,
                             _inout_ ClxConfigList*			  configList,
                             _user_out_ ClxStack*             stack,
                             _in_ boolean                     block);

/**
Initiates the first phase of the stack termination. The first phase includes cleaning up the stack by disconnecting from the remote services.
If the function is called in non-blocking mode, it returns immediately. When the termination is complete, an indication of type #CLX_TERMINATE_CLARINOX_WLAN_COMPLETE
will be received by the indication call-back function. At that moment, the second phase of WLAN termination must be performed by calling #clxDestroyClarinoxWlan. 
Due to the internal architecture, we always need a service handle to perform a non-blocking API call. However, after calling clxTerminateClarinoxWlan(), 
there is no service handle available. Therefore, we use an internal service to perform the non-blocking call hence this internal service must be ignored.
This internal service handle is passed to the event handler call-back function with the #CLX_TERMINATE_CLARINOX_WLAN_COMPLETE indication. 

IMPORTANT : All open handles belonging to this instance of stack MUST BE CLOSED before this function is called. Otherwise, the behaviour will be undefined, and the stack
may even crash.

\param[ in  ] stack  Wi-Fi stack handle. A stack object must be created before any other operation.
\param[ in  ] block                   Indicates mode of operation:
                                        TRUE: Blocking mode
                                        FALSE: Non-blocking mode

\return #CLX_SUCCESS if successful.

        Other possible return values are:

        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT:
*/
ClxResult clxTerminateClarinoxWlan(_in_ ClxStack  stack,
                                   _in_ boolean block);

/**
Performs the second (last) phase of WLAN termination by deleting the objects, threads, and timers. It also releases all the memory used by the stack.
This function MUST ONLY be called when the first phase of stack termination is complete. When this function returns, the stack is completely terminated.

IMPORTANT : If an user-defined indication scheduler has not been passed to #clxInitClarinoxWlan, that this function CANNOT be called within the context of the call-back function (or any other service call-back functions) thread.
This is due to the fact that the call-back thread must also be terminated and cleaned up by this function. The developer must devise a mechanism in order to
call this function outside of the call-back function.

\param[ in  ] stack  Wi-Fi stack handle. A stack object must be created before any other operation.

\return #CLX_SUCCESS if successful.

        Other possible return values are:

        - #CLX_ERROR_INVALID_COMMAND_ARGUMENT:
*/
ClxResult clxDestroyClarinoxWlan(_in_ ClxStack  stack);

/**
Returns a text string containing the name of the error code. This function only returns the string in debug mode.
In release mode, the return string is always an empty string.

\param[ in ] errorCode The error code for which a string representation must be returned.

\return A stack-allocated string containing the string representation of the error code. This string MUST not be modified or deleted.
*/

const s1* clxGetWlanErrorCodeText(ClxError errorCode);



/* Useful Tools: */
/**
Parses the string containing a MAC address in the format XX:XX:XX:XX:XX:XX (Null terminated),
and returns the MAC address in binary format (6 bytes, no null termination).

\param[ in ] str The Null-terminated string buffer containing the MAC address in HEX format.
\param[ out ] macAddrBuf A caller-allocated buffer which on return will carry the MAC address in binary format (only if the return
value of the function is TRUE). The size of this buffer MUST BE at least 6 bytes.

\return TRUE The conversion has been successful.
FALSE The string is not in the correct HEX format.
*/
#define clxWlanParseMacAddressString    clxParseMacAddressString



/**
ClxWlanStationListHandle represents a list of WLAN stations.
Each station in the list is identified by its unique MAC address, and is of the type struct ClxWlanStationListItem, or an application-defined type derived from struct ClxWlanStationListItem.

An object of type ClxWlanStationListHandle is created by a call to #clxWlanStationListCreate, and destroyed by a call to #clxWlanStationListDestroy.
*/
struct ClxWlanStationList;
typedef struct ClxWlanStationList* ClxWlanStationListHandle;


/**
The BASE type of items in a ClxWlanStationList object.

The application may define its own type in the following format:

struct ClxWlanAppStationMapItem
{
    struct ClxWlanStationListItem base;  // MUST be the every first member of the derived type

    // Rest of the members
};

In this case, the size of the application-defined structure must be passed as the second argument to clxWlanStationListCreate().
*/
struct ClxWlanStationListItem
{
    u1 macAddress[CLX_MAC_ADDRESS_LENGTH];              /*!< MUST NOT be modified by the application */
};


/**
Contains information on a newly-allocated or currently-existing station object in an object of type #ClxWlanStationListHandle.
Returned by clxWlanStationListAdd() function.
*/
struct ClxWlanStationListItemInfo
{
    struct ClxWlanStationListItem* station;            /*!< The #ClxWlanStationListItem object associated with the station */
    boolean                         stationExists;      /*!< TRUE if the station (with the specific MAC address) has already existed on the list. FALSE, otherwise */
};



/**
Creates an object of type #ClxWlanStationListHandle, which is used to store the list of WLAN stations.

\param[ in ] maxNumberOfStations             The maximum number of stations that can be stored in the list object.
\param[ in ] sizeof_ClxWlanStationListItem   The size of struct ClxWlanStationListItem structure or the application-defined structure which has derived from struct ClxWlanStationListItem.
                                             NOTE : The value of this argument CANNOT be less than sizeof(struct ClxWlanStationListItem).

\return A pointer to the created list object.
*/
ClxWlanStationListHandle clxWlanStationListCreate(u4 maxNumberOfStations, u4 sizeof_ClxWlanStationListItem);


/**
Destroys a ClxWlanStationList object created by a previous call to #clxWlanStationListCreate.

\param[ in ] list Pointer to the ClxWlanStationList object.
*/
void clxWlanStationListDestroy(ClxWlanStationListHandle list);

/**
Adds a new WLAN station to the ClxWlanStationList object. If a station with the provided MAC address already exits on the list,
Information on the current station existing on the list will be returned.

\param[ in ] list             Pointer to the ClxWlanStationList object.
\param[ in ] macAddress       The unique MAC address of the station, as an array of type u1 and size #CLX_MAC_ADDRESS_LENGTH.

\return An object of type ClxWlanStationListItemInfo which contains information on the station added to the list.
        If the station already existed on the list, the object will contain information on the existing item on the list. Otherwise, it will contain information on the newly allocated item.
        If the list has been full, the member ClxWlanStationListItemInfo.station will be set to NULL. In this, the other members of the returned object must be ignored.
*/
struct ClxWlanStationListItemInfo clxWlanStationListAdd(ClxWlanStationListHandle list, const u1* macAddress);

/**
Finds a WLAN station in the ClxWlanStationList object and returns its ClxWlanStationListItem object.

NOTE : The returned object MUST NOT be deleted by the caller.

\param[ in ] list       Pointer to the ClxWlanStationList object.
\param[ in ] macAddress The unique MAC address of the station, as an array of type u1 and size #CLX_MAC_ADDRESS_LENGTH.

\return The ClxWlanStationListItem object associated with the found station, or NULL if the station was not found.
*/
struct ClxWlanStationListItem* clxWlanStationListFindByMacAddress(ClxWlanStationListHandle list, const u1* macAddress);

/**
Removes a WLAN station, identified by its MAC address, from the ClxWlanStationList object and deletes its associated ClxWlanStationListItem object.
If the WLAN station does not exist, this function will return FALSE.

\param[ in ] list       Pointer to the ClxWlanStationList object.
\param[ in ] macAddress The unique MAC address of the station, as an array of type u1 and size #CLX_MAC_ADDRESS_LENGTH.

\return TRUE if an entry with the provided MAC address was found and removed. FALSE if no entry with the provided MAC address was found.
*/
boolean clxWlanStationListRemove(ClxWlanStationListHandle list, const u1* macAddress);

/**
Deletes all WLAN stations from a ClxWlanStationList object.

\param[ in ] list Pointer to the ClxWlanStationList object.
*/
void clxWlanStationListClear(ClxWlanStationListHandle list);


/**
Returns the number of WLAN stations in the ClxWlanStationList object.

\param[ in ] list Pointer to the ClxWlanStationList object.

\return Number of stations stored on the list.
*/
u4 clxWlanStationListGetNumber(ClxWlanStationListHandle list);

/**
Returns a WLAN station stored in the ClxWlanStationList object by its zero-based index.

\param[ in ] list  Pointer to the ClxWlanStationList object.
\param[ in ] index Zero-based index of the item on the list.

\return A pointer to the ClxWlanStationListItem object associated to the item, or NULL if an item with the provided index does not exist.
*/
struct ClxWlanStationListItem* clxWlanStationListGetByIndex(ClxWlanStationListHandle list, u4 index);





#ifdef __cplusplus
}
#endif

#endif // ClarinoxWlan_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused type declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.3                                      */ 
/* Justification : Unused type declarations are to be used in user 		      */
/* 				   applications.      										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/
