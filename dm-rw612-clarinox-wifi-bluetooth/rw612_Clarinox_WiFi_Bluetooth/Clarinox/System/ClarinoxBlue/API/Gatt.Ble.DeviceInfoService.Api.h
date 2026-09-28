#ifndef __Gatt_Ble_DeviceInfoService_Api_h__
#define __Gatt_Ble_DeviceInfoService_Api_h__

/*******************************************************************************
*
* Project             GattDeviceInformationService
* File                Gatt.Ble.DeviceInfoService.Api.h
* Description         Declares API Functions and Definitions For 
*                     GattDeviceInformationService
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/**
Refer to #clxGattDevInfoGetManufacturerName function.
*/
#define CLX_GATT_DEV_INFO_GET_MANUFACTURER_NAME_COMPLETE                                    0x2f00

/**
Refer to #clxGattDevInfoGetModelNumber function.
*/
#define CLX_GATT_DEV_INFO_GET_MODEL_NUMBER_COMPLETE                                         0x2f01

/**
Refer to #clxGattDevInfoGetSerialNumber function.
*/
#define CLX_GATT_DEV_INFO_GET_SERIAL_NUMBER_COMPLETE                                        0x2f02

/**
Refer to #clxGattDevInfoGetHardwareRevision function.
*/
#define CLX_GATT_DEV_INFO_GET_HARDWARE_REVISION_COMPLETE                                    0x2f03

/**
Refer to #clxGattDevInfoGetFirmwareRevision function.
*/
#define CLX_GATT_DEV_INFO_GET_FIRMWARE_REVISION_COMPLETE                                    0x2f04

/**
Refer to #clxGattDevInfoGetSoftwareRevision function.
*/
#define CLX_GATT_DEV_INFO_GET_SOFTWARE_REVISION_COMPLETE                                    0x2f05

/**
Refer to #clxGattDevInfoGetSystemId function.
*/
#define CLX_GATT_DEV_INFO_GET_SYSTEM_ID_COMPLETE                                            0x2f06

/**
Refer to #clxGattDevInfoGetIeeeRegulatoryCertificationDataList function.
*/
#define CLX_GATT_DEV_INFO_GET_IEEE_REGULATORY_CERTIFICATION_DATA_LIST_COMPLETE              0x2f07

/**
Refer to #clxGattDevInfoGetPnpId function.
*/
#define CLX_GATT_DEV_INFO_GET_PNP_ID_COMPLETE                                               0x2f08

/**
Refer to #clxGattDevInfoGetUdiForMedicalDevices function.
*/
#define CLX_GATT_DEV_INFO_GET_UDI_FOR_MEDICAL_DEVICES_COMPLETE                              0x2f09

/**
Refer to #clxGattConfigureDeviceInfo function.
*/
#define CLX_GATT_CONFIGURE_DEVICE_INFO_COMPLETE                                             0x2f0a


typedef struct ClxGattDevInfoSystemIdStruct
{
    ClxUInteger64  manufacturerId;
    u4             organizationId;
} ClxGattDevInfoSystemId;

typedef struct ClxGattDevInfoPnpIdStruct
{
    u1  vendorIdSource;
    u2  vendorId;
    u2  productId;
    u2  productVersion;
} ClxGattDevInfoPnpId;

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_MANUFACTURER_NAME_COMPLETE
*/
typedef struct ClxGattDevInfoGetManufacturerNameCompleteStruct
{
    _user_out_ u1*  buffer;          /*!< A caller provided buffer to store the manufacturer name */
    _inout_ u4*     bufferLength;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the manufacturer name */
} ClxGattDevInfoGetManufacturerNameComplete;

/**
This API returns the manufacturer name

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_MANUFACTURER_NAME_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetManufacturerNameComplete.

\param[  in   ] gatt          The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle        The handle of the attribute to be read
\param[  out  ] buffer        A caller provided buffer to store the manufacturer name
\param[ inout ] bufferLength  A caller provided variable which, on a successful completion, will contain the actual length of the manufacturer name
\param[  in   ] block         Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetManufacturerName(_in_ ClxHandle  gatt,
                                            _in_ u2         handle,
                                            _user_out_ u1*  buffer,
                                            _inout_ u4*     bufferLength,
                                            _in_ boolean    block);

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_MODEL_NUMBER_COMPLETE
*/
typedef struct ClxGattDevInfoGetModelNumberCompleteStruct
{
    _user_out_ u1*  buffer;          /*!< A caller provided buffer to store the model number */
    _inout_ u4*     bufferLength;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the model number string */
} ClxGattDevInfoGetModelNumberComplete;

/**
This API returns the model number

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_MODEL_NUMBER_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetModelNumberComplete.

\param[  in   ] gatt          The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle        The handle of the attribute to be read
\param[  out  ] buffer        A caller provided buffer to store the model number
\param[ inout ] bufferLength  A caller provided variable which, on a successful completion, will contain the actual length of the model number string
\param[  in   ] block         Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetModelNumber(_in_ ClxHandle  gatt,
                                       _in_ u2         handle,
                                       _user_out_ u1*  buffer,
                                       _inout_ u4*     bufferLength,
                                       _in_ boolean    block);

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_SERIAL_NUMBER_COMPLETE
*/
typedef struct ClxGattDevInfoGetSerialNumberCompleteStruct
{
    _user_out_ u1*  buffer;          /*!< A caller provided buffer to store the serial number */
    _inout_ u4*     bufferLength;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the serial number string */
} ClxGattDevInfoGetSerialNumberComplete;

/**
This API returns the serial number

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_SERIAL_NUMBER_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetSerialNumberComplete.

\param[  in   ] gatt          The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle        The handle of the attribute to be read
\param[  out  ] buffer        A caller provided buffer to store the serial number
\param[ inout ] bufferLength  A caller provided variable which, on a successful completion, will contain the actual length of the serial number string
\param[  in   ] block         Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetSerialNumber(_in_ ClxHandle  gatt,
                                        _in_ u2         handle,
                                        _user_out_ u1*  buffer,
                                        _inout_ u4*     bufferLength,
                                        _in_ boolean    block);

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_HARDWARE_REVISION_COMPLETE
*/
typedef struct ClxGattDevInfoGetHardwareRevisionCompleteStruct
{
    _user_out_ u1*  buffer;          /*!< A caller provided buffer to store the hardware revision */
    _inout_ u4*     bufferLength;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the hardware revision string */
} ClxGattDevInfoGetHardwareRevisionComplete;

/**
This API returns the hardware revision number

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_HARDWARE_REVISION_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetHardwareRevisionComplete.

\param[  in   ] gatt          The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle        The handle of the attribute to be read
\param[  out  ] buffer        A caller provided buffer to store the hardware revision
\param[ inout ] bufferLength  A caller provided variable which, on a successful completion, will contain the actual length of the hardware revision string
\param[  in   ] block         Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetHardwareRevision(_in_ ClxHandle  gatt,
                                            _in_ u2         handle,
                                            _user_out_ u1*  buffer,
                                            _inout_ u4*     bufferLength,
                                            _in_ boolean    block);

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_FIRMWARE_REVISION_COMPLETE
*/
typedef struct ClxGattDevInfoGetFirmwareRevisionCompleteStruct
{
    _user_out_ u1*  buffer;          /*!< A caller provided buffer to store the firmware revision */
    _inout_ u4*     bufferLength;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the firmware revision string */
} ClxGattDevInfoGetFirmwareRevisionComplete;

/**
This API returns the firmware revision number

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_FIRMWARE_REVISION_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetFirmwareRevisionComplete.

\param[  in   ] gatt          The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle        The handle of the attribute to be read
\param[  out  ] buffer        A caller provided buffer to store the firmware revision
\param[ inout ] bufferLength  A caller provided variable which, on a successful completion, will contain the actual length of the firmware revision string
\param[  in   ] block         Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetFirmwareRevision(_in_ ClxHandle  gatt,
                                            _in_ u2         handle,
                                            _user_out_ u1*  buffer,
                                            _inout_ u4*     bufferLength,
                                            _in_ boolean    block);

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_SOFTWARE_REVISION_COMPLETE
*/
typedef struct ClxGattDevInfoGetSoftwareRevisionCompleteStruct
{
    _user_out_ u1*  buffer;          /*!< A caller provided buffer to store the software revision */
    _inout_ u4*     bufferLength;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the software revision string */
} ClxGattDevInfoGetSoftwareRevisionComplete;

/**
This API returns the software revision number

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_SOFTWARE_REVISION_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetSoftwareRevisionComplete.

\param[  in   ] gatt          The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle        The handle of the attribute to be read
\param[  out  ] buffer        A caller provided buffer to store the software revision
\param[ inout ] bufferLength  A caller provided variable which, on a successful completion, will contain the actual length of the software revision string
\param[  in   ] block         Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetSoftwareRevision(_in_ ClxHandle  gatt,
                                            _in_ u2         handle,
                                            _user_out_ u1*  buffer,
                                            _inout_ u4*     bufferLength,
                                            _in_ boolean    block);

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_SYSTEM_ID_COMPLETE
*/
typedef struct ClxGattDevInfoGetSystemIdCompleteStruct
{
    _user_out_ ClxGattDevInfoSystemId*  systemId;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the system id */
} ClxGattDevInfoGetSystemIdComplete;

/**
This API returns the system identification

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_SYSTEM_ID_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetSystemIdComplete.

\param[  in   ] gatt      The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle    The handle of the attribute to be read
\param[  in   ] buffer    A caller provided buffer to store the system id
\param[  out  ] systemId  A caller provided variable which, on a successful completion, will contain the actual length of the system id
\param[  in   ] block     Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetSystemId(_in_ ClxHandle                      gatt,
                                    _in_ u2                             handle,
                                    _user_in_ u1*                       buffer,
                                    _user_out_ ClxGattDevInfoSystemId*  systemId,
                                    _in_ boolean                        block);

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_IEEE_REGULATORY_CERTIFICATION_DATA_LIST_COMPLETE
*/
typedef struct ClxGattDevInfoGetIeeeRegulatoryCertificationDataListCompleteStruct
{
    _user_out_ u1*  buffer;          /*!< A caller provided buffer to store the IEEE regulatory certification datalist */
    _inout_ u4*     bufferLength;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the IEEE regulatory certification datalist */
} ClxGattDevInfoGetIeeeRegulatoryCertificationDataListComplete;

/**
This API returns the IEE regulatory certificatiion details

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_IEEE_REGULATORY_CERTIFICATION_DATA_LIST_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetIeeeRegulatoryCertificationDataListComplete.

\param[  in   ] gatt          The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle        The handle of the attribute to be read
\param[  out  ] buffer        A caller provided buffer to store the IEEE regulatory certification datalist
\param[ inout ] bufferLength  A caller provided variable which, on a successful completion, will contain the actual length of the IEEE regulatory certification datalist
\param[  in   ] block         Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetIeeeRegulatoryCertificationDataList(_in_ ClxHandle  gatt,
                                                               _in_ u2         handle,
                                                               _user_out_ u1*  buffer,
                                                               _inout_ u4*     bufferLength,
                                                               _in_ boolean    block);

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_PNP_ID_COMPLETE
*/
typedef struct ClxGattDevInfoGetPnpIdCompleteStruct
{
    _user_out_ ClxGattDevInfoPnpId*  pnpId;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the pnp id */
} ClxGattDevInfoGetPnpIdComplete;

/**
This API returns the PNP identification

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_PNP_ID_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetPnpIdComplete.

\param[  in   ] gatt    The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle  The handle of the attribute to be read
\param[  in   ] buffer  A caller provided buffer to store the pnp id
\param[  out  ] pnpId   A caller provided variable which, on a successful completion, will contain the actual length of the pnp id
\param[  in   ] block   Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetPnpId(_in_ ClxHandle                   gatt,
                                 _in_ u2                          handle,
                                 _user_in_ u1*                    buffer,
                                 _user_out_ ClxGattDevInfoPnpId*  pnpId,
                                 _in_ boolean                     block);

/**
Data Structure for the indication #CLX_GATT_DEV_INFO_GET_UDI_FOR_MEDICAL_DEVICES_COMPLETE
*/
typedef struct ClxGattDevInfoGetUdiForMedicalDevicesCompleteStruct
{
    _user_out_ u1*  buffer;          /*!< A caller provided buffer to store the udi medical device details */
    _inout_ u4*     bufferLength;    /*!< A caller provided variable which, on a successful completion, will contain the actual length of the udi medical device */
} ClxGattDevInfoGetUdiForMedicalDevicesComplete;

/**
This API return the Unique Device Identifier for medical devices

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_DEV_INFO_GET_UDI_FOR_MEDICAL_DEVICES_COMPLETE.
                   The parameter of this indication is of type #ClxGattDevInfoGetUdiForMedicalDevicesComplete.

\param[  in   ] gatt          The GATT profile handle which is either GATT server or GATT client
\param[  in   ] handle        The handle of the attribute to be read
\param[  out  ] buffer        A caller provided buffer to store the udi medical device details
\param[ inout ] bufferLength  A caller provided variable which, on a successful completion, will contain the actual length of the udi medical device
\param[  in   ] block         Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattDevInfoGetUdiForMedicalDevices(_in_ ClxHandle  gatt,
                                                _in_ u2         handle,
                                                _user_out_ u1*  buffer,
                                                _inout_ u4*     bufferLength,
                                                _in_ boolean    block);

/**
This API used to configure the following device information charcteristics 1.Manufacturer name 2.Model number 3.Serial number 4.Hardware revision 5.Firmware revision 6.Software revision

Blocking mode: This function will not return until the command is complete. The function return value indicates the result of the command
Non-blocking mode: This function will return immediately with the error code #CLX_ERROR_COMPLETION_PENDING.
                   When the command is complete, the call-back function will be called with an indication of type #CLX_GATT_CONFIGURE_DEVICE_INFO_COMPLETE.
                   This indication does not have any parameters.

\param[  in   ] gatt         GATT server handle
\param[  in   ] handle       The characteristic handle index. Ex, 1.Manufacturer name, model number, serial number, hardware revision.
\param[  in   ] writeBuffer  User input data which is write into the selected GATT service attribute like Manufacturer name, model number, serial number.
\param[  in   ] dataLength   Length of the characteristic value.
\param[  in   ] block        Type of the operation.
                                   TRUE:  API will be blocked until this command is completed (successfully or failed).
                                   FALSE: API will return immediately and then a corresponding API completion event will be raised upon command completion.

\return #CLX_SUCCESS if successful. 
        In blocking mode, result will be returned by this function.
        In non-blocking mode, result of the actual operation will be passed to the callback function.

        Other possible return values are:

        - #CLX_ERROR_COMPLETION_PENDING: Operation will be completed asynchronously (only in non-blocking mode)
        - #CLX_ERROR_COMMAND_CANCELLED: The handle was closed before the command has completed (only in blocking mode)
        - #CLX_ERROR_COMMAND_NOT_COMPLETE: A previous same command has been issued which has not completed yet
        - #CLX_ERROR_INVALID_HANDLE: Invalid handle

        - CLX_SUCCESS: The operation has been successful
*/
ClxResult clxGattConfigureDeviceInfo(_in_ ClxHandle       gatt,
                                     _in_ u2              handle,
                                     _user_in_ const u1*  writeBuffer,
                                     _in_ u4              dataLength,
                                     _in_ boolean         block);



#ifdef __cplusplus
}
#endif

#endif // __Gatt_Ble_DeviceInfoService_Api_h__
