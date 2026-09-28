#ifndef __Org_Bluetooth_Service_Coordinated_Set_Identification_Service_h__
#define __Org_Bluetooth_Service_Coordinated_Set_Identification_Service_h__

/*******************************************************************************
*
* Project             Clarinox Reference Application
* File                org.bluetooth.service.coordinated_set_identification_service.h
* Description         Declares definitions for the GATT service Coordinated Set Identification Service
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2024 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

/**
Coordinated Set Identification Service GATT Service:
To discover a Coordinated Set and its members, a device discovers at least one member of the
Coordinated Set (e.g., via friendly name), connects to it, and obtains the SIRK
*/
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_NAME    "Coordinated Set Identification Service"
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_UUID    0x1846

/**
Set Identity Resolving Key Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY                 "Set Identity Resolving Key"
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_HANDLE_INDEX    2
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_STRUCT          struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_VALUE_TYPE      ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields_Type
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_SIZE            ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields_Size
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_IDENTITY_RESOLVING_KEY_UUID            0x2B84


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicSetIdentityResolvingKey.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicSetIdentityResolvingKey.
*/
struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields
{
    /**
    Field : type
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 type;
    
    /**
    Field : value
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 value[16];
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields
*/
#define ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields
*/
#define ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields_Size    (1 + 16)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSetIdentityResolvingKey(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSetIdentityResolvingKeyFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSetIdentityResolvingKey(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Coordinated Set Size Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE                 "Coordinated Set Size"
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_HANDLE_INDEX    4
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_STRUCT          struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_VALUE_TYPE      ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields_Type
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_SIZE            ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields_Size
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_COORDINATED_SET_SIZE_UUID            0x2B85


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicCoordinatedSetSize.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicCoordinatedSetSize.
*/
struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields
{
    /**
    Field : coordinated_Set_Size
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 coordinatedSetSize;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields
*/
#define ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields
*/
#define ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicCoordinatedSetSize(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicCoordinatedSetSizeFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicCoordinatedSetSize(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Set Member Lock Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSetMemberLockFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK                 "Set Member Lock"
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_HANDLE_INDEX    6
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_WRITABLE | CLX_GATT_ATTRIBUTE_PERMISSION_NOTIFIABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_STRUCT          struct ClxOrgBluetoothCharacteristicSetMemberLockFields
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_VALUE_TYPE      ClxOrgBluetoothCharacteristicSetMemberLockFields_Type
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_SIZE            ClxOrgBluetoothCharacteristicSetMemberLockFields_Size
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_LOCK_UUID            0x2B86


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicSetMemberLock.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicSetMemberLock.
*/
struct ClxOrgBluetoothCharacteristicSetMemberLockFields
{
    /**
    Field : set_Member_Lock
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 setMemberLock;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSetMemberLockFields
*/
#define ClxOrgBluetoothCharacteristicSetMemberLockFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicSetMemberLockFields
*/
#define ClxOrgBluetoothCharacteristicSetMemberLockFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSetMemberLockFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicSetMemberLockFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSetMemberLockFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSetMemberLock(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSetMemberLockFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicSetMemberLockFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSetMemberLockFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSetMemberLock(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



/**
Set Member Rank Characteristic:

The UUID of this characteristic is defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_UUID.

The value of this characteristic is of type #ClxOrgBluetoothCharacteristicSetMemberRankFields.

Local GATT Service:
The handle index of this characteristic in the local service is defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_HANDLE_INDEX.
The remote access permissions for this characteristic are defined by #CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_PERMISSIONS.
*/
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK                 "Set Member Rank"
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_HANDLE_INDEX    9
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_PERMISSIONS     (CLX_GATT_ATTRIBUTE_PERMISSION_READABLE | CLX_GATT_ATTRIBUTE_PERMISSION_ENCRYPTION_REQUIRED)
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_STRUCT          struct ClxOrgBluetoothCharacteristicSetMemberRankFields
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_VALUE_TYPE      ClxOrgBluetoothCharacteristicSetMemberRankFields_Type
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_SIZE            ClxOrgBluetoothCharacteristicSetMemberRankFields_Size
#define CLX_GATT_SERVICE_COORDINATED_SET_IDENTIFICATION_SERVICE_CHARACTERISTIC_SET_MEMBER_RANK_UUID            0x2B87


/**
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicSetMemberRank.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicSetMemberRank.
*/
struct ClxOrgBluetoothCharacteristicSetMemberRankFields
{
    /**
    Field : set_Member_Rank
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 setMemberRank;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicSetMemberRankFields
*/
#define ClxOrgBluetoothCharacteristicSetMemberRankFields_Type    ClxBleAttributeValueType_FixedLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicSetMemberRankFields
*/
#define ClxOrgBluetoothCharacteristicSetMemberRankFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicSetMemberRankFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicSetMemberRankFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSetMemberRankFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicSetMemberRank(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicSetMemberRankFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicSetMemberRankFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicSetMemberRankFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicSetMemberRank(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);





/**
Returns the interface to Coordinated Set Identification Service GATT service.
The interface may be used to register one or more instances of this service in the local GATT server

\return The interface to Coordinated Set Identification Service GATT service. The interface SHALL NOT be modified or removed
*/
extern const ClxBleGattServiceInterface* clxGetCoordinatedSetIdentificationServiceGattServiceInterface();


#ifdef __cplusplus
}
#endif

#endif /* __Org_Bluetooth_Service_Coordinated_Set_Identification_Service_h__ */

