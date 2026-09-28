#ifndef __C_Bleservicegenerator_Xml_Custom_OrgBluetoothCharacteristicGapResolvablePrivateAddressOnly__
#define __C_Bleservicegenerator_Xml_Custom_OrgBluetoothCharacteristicGapResolvablePrivateAddressOnly__

/*******************************************************************************
*
* Project             ClarinoxBlue Low Energy
* File                org.bluetooth.characteristic.gap.resolvable_private_address_only.h
* Description         Declares definitions for the Reference Characteristic ""
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
Encoder function for this structure is #clxEncodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly.
Decoder function for this structure is #clxDecodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly.
*/
struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields
{
    /**
    Field : resolvablePrivateAddress
    Format : uint8
    Unit : Not Available
    Description : Not Available
    Requirement : Mandatory
    */
    u1 resolvableprivateaddress;
};

/**
Defines the value type of the structure #ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields
*/
#define ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields_Type    ClxBleAttributeValueType_VariableLength
/**
Defines the maximum encoded size of the structure #ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields
*/
#define ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields_Size    (1)

/**
Encodes the fields of an object of type #ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields into a characteristic value.

\param[ in ] buffer A caller-provided buffer into which the fields of the input are to be encoded.
\param[ in ] bufferSize Size of the caller-provided buffer
\param[ in ] input A pointer to an object of type ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields which contains the data to be encoded into buffer.
\param[ in ] inputSize Size of input. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields).

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the encoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the encoded data in buffer. If the procedure has failed, the return value shall be 0
*/
extern u4 clxEncodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly(_out_ u1* buffer, _in_ ClxSize bufferSize, _in_ const void* input, _in_ ClxSize inputSize, _out_ ClxResult* result);

/**
Decodes a characteristic value into the fields of an object of type #ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields.

\param[ in ] data A caller-provided buffer containing the data in encoded format.
\param[ in ] dataLength Length of encoded data
\param[ out ] output A pointer to an object of type ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields which, on a successful return, will contain the data in decoded format.
\param[ in ] outputSize Size of output. SHALL be set to sizeof(struct ClxOrgBluetoothCharacteristicGapResolvablePrivateAddressOnlyFields). 

\param[ in ] result A pointer to a variable of type ClxResult which on return will contain the result of the decoding procedure. CLX_SUCCESS indicates success while any other value indicates failure

\return The length of the ENCODED data in the data argument which was decoded into the output fields. If the procedure has failed, the return value shall be 0
*/
extern u4 clxDecodeOrgBluetoothCharacteristicGapResolvablePrivateAddressOnly(_in_ const u1* data,  _in_ ClxSize dataLength, _out_ void* output, _in_ ClxSize outputSize, _out_ ClxResult* result);



#ifdef __cplusplus
}
#endif

#endif // __C_Bleservicegenerator_Xml_Custom_OrgBluetoothCharacteristicGapResolvablePrivateAddressOnly__

