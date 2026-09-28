#ifndef ClxConfigParams_h
#define ClxConfigParams_h

/**************************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxConfigParams.h
* Description         ClarinoxSoftFrame Configuration parameters common structure
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


/**
Returns the unique Type ID of a configuration parameter structure.

Example:
    ClxConfigInteger configInteger;

    clxConfigInitIntegerParam(&configInteger, "ConfigName", 0, NULL);

    assert(configInteger.paramInfo.paramTypeID == CLX_CONFIG_TYPE(ClxConfigInteger));

\param[ in ] ParamStruct The name of the configuration parameter structure.

\return The unique type ID of the passed configuration parameter structure, as an opaque pointer value.
*/
#define CLX_CONFIG_TYPE(ParamStruct)                &C_clx_ConfigType_##ParamStruct

#define CLX_DEFINE_CONFIG_TYPE(ParamStruct)         extern const struct ClxConfigParamType C_clx_ConfigType_##ParamStruct


/**
Checks whether or not a configuration parameter object is of a specific type.

Example:
\code
    ClxConfigInteger configInteger;

    clxConfigInitIntegerParam(&configInteger, "ConfigName", 0, NULL);

    assert(CLX_IS_CONFIG_TYPE(configInteger.paramInfo, ClxConfigInteger));
    assert(!CLX_IS_CONFIG_TYPE(configInteger.paramInfo, ClxConfigString));
\endcode
 paramVar is the configuration parameter variable of type #ClxConfigParam.
 ParamStruct is the name of the configuration parameter structure.

\return TRUE if paramVar is of type ParamStruct. FALSE otherwise.
*/
#define CLX_IS_CONFIG_TYPE(paramVar, ParamStruct)   ((paramVar).paramTypeID == &C_clx_ConfigType_##ParamStruct)




#ifdef __cplusplus
extern "C" {
#endif


struct ClxConfigParamTypePrivate;


/**
ClxConfigParamType uniquely defines a Configuration Parameter type. Only one instance of ClxConfigParamType must exist for each defined
type. The address of the instance is used as the unique type ID for the configuration parameters of that type.
*/
struct ClxConfigParamType
{
    const struct ClxConfigParamTypePrivate* private_;  /* Used internally. SHALL not be modified by the user. */
};


typedef const struct ClxConfigParamType* ClxConfigParamTypeID;


/**
 * ClxConfigParamStruct which contains parameter name, parameter Type ID and boolean flag called 'processed'.
 */
typedef struct ClxConfigParamStruct
{
    const s1*                       paramName;      /*!< Case-sensitive name of the parameter as a NULL-terminated string */
    ClxConfigParamTypeID            paramTypeID;    /*!< The unique Type ID of the parameter, which can be obtained using the macro #CLX_CONFIG_TYPE */
    struct ClxConfigParamStruct*    next;           /*!< Pointer to the next configuration parameter object in the parent list */
    boolean                         processed;      /*!< Set by the Clarinox stack to TRUE if the configuration parameter object has been processed (e.g. value is applied or obtained).
                                                         Set to FALSE if the parameter object has been ignored by the Clarinox stack */
} ClxConfigParam;

/**
 * ClxConfigInteger which stores the parameters of type integer type.
 */
typedef struct ClxConfigIntegerStruct
{
    ClxConfigParam    paramInfo;                    /*!< The base object */
    s4                paramValue;                   /*!< The value of the parameter to be set or obtained */
} ClxConfigInteger;

/**
 * ClxConfigUnsignedStruct which stores the parameters of type unsigned integer type. 
 */
typedef struct ClxConfigUnsignedStruct
{
    ClxConfigParam    paramInfo;                    /*!< The base object */
    u4                paramValue;                   /*!< The value of the parameter to be set or obtained */
} ClxConfigUnsigned;

/**
 * ClxConfigReal which stores the parameters of type real/double. 
 */

#if defined(CLX_FLOATING_POINT_SUPPORTED)
typedef struct ClxConfigRealStruct
{
    ClxConfigParam    paramInfo;                    /*!< The base object */
    r8                paramValue;                   /*!< The value of the parameter to be set or obtained */
} ClxConfigReal;
#endif


/**
 * ClxConfigString which stores the parameters of type string. 
 */
typedef struct ClxConfigStringStruct
{
    ClxConfigParam   paramInfo;                     /*!< The base object */
    union ClxConfigStringContent
    {
        const s1*    paramValue;                    /*!< The value of the object as a NULL-terminated string. This value is used ONLY if this object is being used to set the value of a configuration parameter */
        struct
        {
            s1*          address;                   /*!< Address of a user-defined buffer to which the obtained value of the configuration parameter will be stored. The stored value will contain the NULL termination character */
            ClxSize      Size;                      /*!< The size of the user-defined buffer */
        } paramValueBuffer;                         /*!< The value of the object as a structure. This value is used ONLY if this object is being used to obtain the value of a configuration parameter */
    } content;                                      /*!< Content of the object as a union. The actual value used depends on whether this object is being used to 
                                                        set the value of a configuration parameter or obtain the value of a configuration parameter. */
} ClxConfigString;



/**
 ClxConfigValue which points to a value of an arbitrary type. Optionally, valueTypeID may be set to indicate the type of the object/data pointed to by the ClxConfigValue object.
*/
typedef struct ClxConfigValueStruct
{
    ClxConfigParam          paramInfo;                     /*!< The base object */
   
    ClxConfigParamTypeID    valueTypeID;                   /*!< The type ID of object pointed to by the value parameter. May be set to NULL. */
    void*                   value;                         /*!< The void pointer object containing the value (if the value is being set), or a pointer to the object where the value is to be stored (when the value is being obtained). */
    u4                      valueSize;                     /*!< The size of the value object */
} ClxConfigValue;


/**
 * ClxConfigData which contains a pointer to the parameter data (of type unsigned char) and size of the data (of type integer). 
 */
typedef struct ClxConfigDataStruct
{
    ClxConfigParam    paramInfo;                    /*!< The base object */
    union ClxConfigDataContent
    {
        const u1*         paramData;                /*!< The value of the object as a buffer. This value is used ONLY if this object is being used to set the value of a configuration parameter */
        struct  
        {
            u1*     address;                        /*!< Address of a user-defined buffer to which the obtained value of the configuration parameter will be stored */
            ClxSize size;                           /*!< The size of the user-defined buffer */
        } paramDataBuffer;                          /*!< The value of the object as a structure. This value is used ONLY if this object is being used to obtain the value of a configuration parameter */
    } content;                                      /*!< Content of the object as a union. The actual value used depends on whether this object is being used to 
                                                        set the value of a configuration parameter or obtain the value of a configuration parameter. */
    ClxSize           paramDataLength;              /*!< The length of the value which is either being set or obtained */
} ClxConfigData;

/**
 * Array of configurations, array members shall be of the same type.
 * IMPORTANT : The parameter array shall be cast to the correct type (type of the members) before being browsed for members.
 */
typedef struct ClxConfigArrayStruct
{
    ClxConfigParam        paramInfo;                /*!< The base object */
    void*                 array;                    /*!< Pointer to the configuration parameter array containing one or more configuration parameter objects which are either being set or obtained. 
                                                         The actual type of the elements of the array is given by 'elementTypeID' member */ 
	ClxConfigParamTypeID  elementTypeID;            /*!< The unique Type ID of the elements of the array. Based on this value, the array must be cast to the correct type before being accessed */          
    ClxSize               numOfParams;              /*!< Number of valid elements in the configuration parameter array */ 
} ClxConfigArray;

/**
 * ClxConfigList which contains a pointer(of type ClxConfigParam) to the list of  objects which are of different types 
 * and size(of type integer) of the parameters in the list.
 */
typedef struct ClxConfigListStruct
{
    ClxConfigParam        paramInfo;                /*!< The base object */
    ClxConfigParam*       first;                    /*!< Pointer to the first configuration parameter object in the list */
    ClxConfigParam*       last;                     /*!< Pointer to the last configuration parameter object in the list */
} ClxConfigList;

/**
 * Initializes the subsequent member of parentList with the given object of type #ClxConfigInteger.
 * 
 * \param[ in ] object a pointer to the an object of type ClxConfigInteger  
 * \param[ in ] paramName string pointer to name of the parameter.
 * \param[ in ] paramValue a pointer to value of the parameter of type unsigned integer
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
extern void clxConfigInitIntegerParam   (ClxConfigInteger* object, const s1* paramName, s4 paramValue, ClxConfigList* parentList);

/**
 * Initializes the paramList with the given parameter of type ClxConfigUnsigned.
 * 
 * \param[ in ] object pointer to ClxConfigUnsigned
 * \param[ in ] paramName pointer to parameter name
 * \param[ in ] paramValue parameter value 
 * \param[ in ] parentList pointer to ClxConfigList which we are willing to fill
 */
extern void clxConfigInitUnsignedParam   (ClxConfigUnsigned* object, const s1* paramName, u4 paramValue, ClxConfigList* parentList);

/**
 * Initializes the subsequent member of parentList with the given object of type #ClxConfigReal.
 *
 * \param[ in ] object a pointer to an object of type ClxConfigReal  
 * \param[ in ] paramName a string pointer to name of the parameter.
 * \param[ in ] paramValue a pointer to value of the parameter of type double
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
#if defined(CLX_FLOATING_POINT_SUPPORTED)
extern void clxConfigInitRealParam      (ClxConfigReal* object, const s1* paramName, r8 paramValue, ClxConfigList* parentList);
#endif

/**
 * Initializes the subsequent member of parentList with the given object of type #ClxConfigValue.
 * This function is the same as clxConfigInitValueParamEx() except that it sets object->valueTypeID to NULL.
 * 
 * \param[ in ] object a pointer to the an object of type ClxConfigInteger  
 * \param[ in ] paramName string pointer to name of the parameter.
 * \param[ in ] value pointer to the value of this object.
 * \param[ in ] valueSize Size of the value of this object.
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
extern void clxConfigInitValueParam   (ClxConfigValue* object, const s1* paramName, void* value, u4 valueSize, ClxConfigList* parentList);


/**
 * Initializes the subsequent member of parentList with the given object of type #ClxConfigValue.
 *
 * \param[ in ] object a pointer to the an object of type ClxConfigInteger
 * \param[ in ] paramName string pointer to name of the parameter.
 * \param[ in ] paramTypeID The typeID of the object to which object.value is pointing. This value may be NULL.
 * \param[ in ] value pointer to the value of this object.
 * \param[ in ] valueSize Size of the value of this object.
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
extern void clxConfigInitValueParamEx(ClxConfigValue* object, const s1* paramName, ClxConfigParamTypeID paramTypeID, void* value, u4 valueSize, ClxConfigList* parentList);


/**
 * Initializes the subsequent member of parentList with the given object of type #ClxConfigString.
 *
 * \param[ in ] object a pointer to an object of type ClxConfigString  
 * \param[ in ] paramName a string pointer to name of the parameter.
 * \param[ in ] paramValue a string pointer to value of the parameter 
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
extern void clxConfigInitStringParam    (ClxConfigString* object, const s1* paramName, const s1* paramValue, ClxConfigList* parentList);

/**
 * Initializes the subsequent member of parentList with the given object of type #ClxConfigString. The object will contain an empty buffer to which a string value will be stored.
 *
 * \param[ in ] object a pointer to an object of type ClxConfigString  
 * \param[ in ] paramName a string pointer to name of the parameter.
 * \param[ in ] paramValueBuffer a string pointer to the buffer into which the value will be stored. 
 * \param[ in ] paramValueBufferSize Size of paramValueBuffer, in bytes.
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
extern void clxConfigInitStringBufferParam    (ClxConfigString* object, const s1* paramName, s1* paramValueBuffer, ClxSize paramValueBufferSize, ClxConfigList* parentList);

/**
 * Initializes the subsequent member of parentList with the given object of type #ClxConfigData.
 *
 * \param[ in ] object a pointer to an object of type ClxConfigData  
 * \param[ in ] paramName a string pointer to name of the parameter.
 * \param[ in ] paramData a pointer to data of the parameter of type unsigned char
 * \param[ in ] paramDataLength size of the parameter data of type unsigned integer
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
extern void clxConfigInitDataParam      (ClxConfigData* object, const s1* paramName, const u1* paramData, ClxSize paramDataLength, ClxConfigList* parentList);

/**
 * Initializes the subsequent member of parentList with the given object of type #ClxConfigData. The object will contain an empty buffer to which binary data value will be stored.
 *
 * \param[ in ] object a pointer to an object of type ClxConfigData  
 * \param[ in ] paramName a string pointer to name of the parameter.
 * \param[ in ] paramDataBuffer a pointer to the buffer into which the value will be stored in binary format. 
 * \param[ in ] paramDataBufferSize Size of paramDataBuffer, in bytes.
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
extern void clxConfigInitDataBufferParam      (ClxConfigData* object, const s1* paramName, u1* paramDataBuffer, ClxSize paramDataBufferSize, ClxConfigList* parentList);

/**
 * Initializes the subsequent member of parentList with the given object of type #ClxConfigArray.
 *
 * \param[ in ] object a pointer to an object of type ClxConfigArray  
 * \param[ in ] paramName pointer to paramName of type string
 * \param[ in ] array a pointer to a list of type a specific type.
 * \param[ in ] elementTypeID Type of each element in the array. Use #CLX_CONFIG_TYPE to get the type (e.g. CLX_CONFIG_TYPE(ClxConfigInteger))
 * \param[ in ] numOfParams number of parameters of size and type of unsigned integer
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add
 */
extern void clxConfigInitParamsArray    (ClxConfigArray* object, const s1* paramName, void* array, ClxConfigParamTypeID elementTypeID, ClxSize numOfParams, ClxConfigList* parentList);

/**
 * Initializes the first member of the List with the given object of type #ClxConfigList.
 *
 * \param[ in ] object a pointer to an object of type ClxConfigList  
 * \param[ in ] paramName a string pointer to parameter name.
 * \param[ in ] parentList pointer to parent List of type #ClxConfigList which we are willing to add.
 */
extern void clxConfigInitParamsList     (ClxConfigList* object, const s1* paramName, ClxConfigList* parentList);

/**
 * Searches in a configuration list for a specific configuration parameter.
 *
 * \param[ in ] list The list in which the specific parameter is to be searched for. 
 * \param[ in ] paramName The name of the parameter to be searched for. This argument cannot be NULL.
 * \param[ in ] paramType (Optional) Type of the parameter to be searched for. If NULL, it will be ignored.
 * return A pointer to the found parameter object. If no parameter with the specified name and type is found, the 
 return value will be NULL.
 */
extern ClxConfigParam* clxFindConfigParam(const ClxConfigList* list, const s1* paramName, ClxConfigParamTypeID paramType);


/**
 * Searches in a configuration chain for a specific configuration parameter.
 *
 * \param[ in ] begin The beginning of the chain. This parameter will be searched first. If this argument is NULL, the return value will also be NULL.
 * \param[ in ] paramName The name of the parameter to search for. This argument cannot be NULL.
 * \param[ in ] valueTypeID Type of the value pointed to by the ClxConfigValue object (ClxConfigValue.valueTypeID). May be set to NULL.
 * return A pointer to the found parameter object. If no parameter with the specified name and type is found, the 
 return value will be NULL.
 */
extern ClxConfigParam* clxFindConfigParamInChain(ClxConfigParam* begin, const s1* paramName, ClxConfigParamTypeID valueTypeID);


/**
 * Searches in a configuration list for a configuration parameter of type ClxConfigValue and a specific value type ID.
 *
 * \param[ in ] list The list in which the specific parameter is to be searched for.
 * \param[ in ] paramName The name of the parameter to be searched for. This argument cannot be NULL.
 * \param[ in ] valueTypeID Type of the value pointed to by the ClxConfigValue object (ClxConfigValue.valueTypeID). May be set to NULL.
 * return A pointer to the found parameter object. If no parameter with the specified name and type is found, the
 return value will be NULL.
 */
extern ClxConfigValue* clxFindValueTypeConfigParam(const ClxConfigList* list, const s1* paramName, ClxConfigParamTypeID valueTypeID);


/**
 * Searches in a configuration chain for a configuration parameter of type ClxConfigValue and a specific value type ID.
 *
 * \param[ in ] begin The beginning of the chain. This parameter will be searched first. If this argument is NULL, the return value will also be NULL.
 * \param[ in ] paramName The name of the parameter to search for. This argument cannot be NULL.
 * \param[ in ] valueTypeID Type of the value pointed to by the ClxConfigValue object (ClxConfigValue.valueTypeID). May be set to NULL.
 * return A pointer to the found parameter object. If no parameter with the specified name and type is found, the
 return value will be NULL.
 */
extern ClxConfigValue* clxFindValueTypeConfigParamInChain(ClxConfigParam* begin, const s1* paramName, ClxConfigParamTypeID valueTypeID);


/*
Definitions of the configuration parameters. Used internally. 
*/
CLX_DEFINE_CONFIG_TYPE(ClxConfigInteger);
CLX_DEFINE_CONFIG_TYPE(ClxConfigUnsigned);

#if defined (CLX_FLOATING_POINT_SUPPORTED)
CLX_DEFINE_CONFIG_TYPE(ClxConfigReal);
#endif

CLX_DEFINE_CONFIG_TYPE(ClxConfigValue);
CLX_DEFINE_CONFIG_TYPE(ClxConfigString);
CLX_DEFINE_CONFIG_TYPE(ClxConfigData);
CLX_DEFINE_CONFIG_TYPE(ClxConfigArray);
CLX_DEFINE_CONFIG_TYPE(ClxConfigList);

#ifdef __cplusplus
}
#endif



#define CLX_ITERATE_CONFIG_PARAMS(configList)							                                                \
	ClxConfigList* list = (configList);																	                \
    if (list->first)                                                                                                    \
    {                                                                                                                   \
        ClxConfigParam* item = list->first;                                                                             \
	    do																                                                \
	    {																									            \
		    if (0)																							            \
		    {


#define CLX_PROCESS_CONFIG_PARAM(ParameterName, Type)										                            \
			    continue;																					            \
		    }																								            \
            if ((strcmp((ParameterName), item->paramName) == 0) &&			                                            \
              (item->paramTypeID == &C_clx_ConfigType_##Type))                                                          \
		    {                                                                                                           \
                Type* param = (Type*)item;


#define CLX_END_ITERATE_CONFIG_PARAMS														                            \
			    continue;																					            \
		    }																								            \
	    }                                                                                                               \
        while((item = item->next) != NULL);                                                                             \
    }




#ifdef __cplusplus

class CppClxConfigList : public ClxConfigList
{
public:
    CppClxConfigList(const s1* name, ClxConfigList* parentList)
    {
        clxConfigInitParamsList(this, name, parentList);
    }
};

class CppClxConfigInteger : public ClxConfigInteger
{
public:
    CppClxConfigInteger(const s1* name, ClxConfigList* parentList)
    {
        clxConfigInitIntegerParam(this, name, 0, parentList);
    }
};

class CppClxConfigString : public ClxConfigString
{
public:
    CppClxConfigString(const s1* name, ClxConfigList* parentList)
    {
        clxConfigInitStringParam(this, name, 0, parentList);
    }
};


#endif // #ifdef __cplusplus


#endif    // ClxConfigParams_h

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : Unions shall not be used.                                  */ 
/* Rule          : MISRA-C:2004 Rule 18.4                                     */ 
/* Justification : No risk identified. Unions are used in this instance for   */
/*                 packing and unpacking data / sending and receiving data    */ 
/*				   back and forth between the application side and the WLAN   */
/*				   stack side of the code. Depending on the direction the data*/ 
/*				   is sent the type of the data used will differ.             */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : C macros shall only expand to a braced initialiser,        */
/*                 a constant, a string literal, a parenthesised expression,  */ 
/*				   a type qualifier, a storage class specifier,               */
/*				   or a do-whilezero construct.                               */ 
/* Rule          : MISRA-C:2004 Rule 19.4                                     */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */ 
/*                 platforms. Used to provide better flexibility for templated*/ 
/*				   code to eliminate programmer errors.                       */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : A function should be used in preference to a function-like */
/*                 macro.                                                     */ 
/* Rule          : MISRA-C:2004 Rule 19.7                                     */ 
/* Justification : No risk identified. Used to provide better performance in  */
/*                 embedded system environments that do not support efficient */
/*				   functions inlining.                                        */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : In the definition of a function-like macro each instance of*/
/*                 a parameter shall be enclosed in parentheses unless it is  */ 
/*				   used as the operand of # or ## .                           */
/* Rule          : MISRA-C:2004 Rule 19.10                                    */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */
/*                 platforms. Parameter used both as type for data declaration*/
/* 				   and as the operand of ## (Misra compliant).                */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : The # and ## operators should not be used.                 */
/* Rule          : MISRA-C:2004 Rule 19.13                                    */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */
/*                 platforms. Used to provide better flexibility.	          */
/******************************************************************************/


/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : The union keyword should not be used.					  */
/* Rule          : MISRA-C:2012 Rule 19.2                                     */ 
/* Justification : No risk identified. Unions are used in this instance for   */
/*                 packing and unpacking data / sending and receiving data    */ 
/*				   back and forth between the application side and the WLAN   */
/*				   stack side of the code. Depending on the direction the data*/ 
/*				   is sent the type of the data used will differ.             */
/******************************************************************************/

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : The # and ## preprocessor operators should not be used.    */
/* Rule          : MISRA-C:2012 Rule 20.10                                    */ 
/* Justification : No risk identified. Tested extensively in muliple embedded */
/*                 platforms. Used to provide better flexibility.	          */
/******************************************************************************/
