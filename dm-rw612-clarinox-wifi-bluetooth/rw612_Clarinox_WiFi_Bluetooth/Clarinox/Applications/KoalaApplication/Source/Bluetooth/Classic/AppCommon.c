/**********************************************************************************
*
* Project             Clarinox Reference Application
* File                AppCommon.cpp
* Description         Application common definitions
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2021 by Clarinox Technologies Pty. Ltd.
*
**********************************************************************************/

#include "AppCommon.h"
#include "ClxStandard.h"
#include "ClxMemoryPoolset.h"

/*******************************************************************************************************************************
* Indicates if the characters printed are not complete and to be followed in the data buffer from next indication
*******************************************************************************************************************************/
boolean pendingData = FALSE;

/*******************************************************************************************************************************
*                                                    isDelimiterOccurred
*
* This function is used to parse and finds out the occurence of atleast one of the delimiter in the list which matches the value.
*
* \param list the source buffer to be parsed
* \param delimiter the list of string until which the characters to be printed
* \param count the number of delimiter strings
* \return boolean TRUE if matches the delimiter, else FALSE
*
*******************************************************************************************************************************/
boolean isDelimiterOccurred(s1* list, delimiter* delimList, u4 count)
{
    u4 index = 0;
    for (;index < count; index++)
    {
        if (!clxStrNCmp(list, delimList[index].delim, delimList[index].delimLength))
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*******************************************************************************************************************************
*                                                    printEachDataList
*
* This function is used to parse and print one element of the list until it encounters the delimiter value. 
*
* \param list the source buffer to be parsed
* \param delimiter the list of string until which the characters to be printed
* \param count the number of delimiter strings
* \return s1 buffer pointer till the characters printed
*
*******************************************************************************************************************************/
s1 *printEachDataList(s1 *list, delimiter* delimList, u4 count)
{
    while (TRUE != isDelimiterOccurred(list, delimList, count))
    {
        if(*list == '\0')
        {
            pendingData = TRUE;
            return list;
        }

        clxConsoleUIEngineText("%c", *list);
        list++;
    }
    
    clxConsoleUIEngineText(" ", *list);
    return list;
}

/*******************************************************************************************************************************
*                                                    displayDataList
*
* This function is used to parse and print all the element of the list which corresponds to the key and until it encounters 
* the delimiter value. 
*
* \param pData the source buffer to be parsed
* \param dataLen length of the source buffer
* \param delimiter the list of string until which the characters to be printed
* \param count the number of delimiter strings
* \param key the key whose corresponding/following characters to be printed
* \return boolean which tells whether any character values are printed or not
*
*******************************************************************************************************************************/
boolean displayDataList(u1 *pData, u4 dataLen, delimiter* delimList, u4 count, const s1 *key)
{
    u1 isDataPrinted = FALSE;
    if (NULL == pData)
    {
        return isDataPrinted;
    }

    char* list = (char*)clxMemDup((void*)pData, dataLen+1);
    
    /* To be used during deletion */
    s1* pList = list;

    if (NULL == list)
    {
        return isDataPrinted;
    }

    list[dataLen] = '\0';
    if (TRUE == pendingData)
    {
        list = printEachDataList(list, delimList, count);
        isDataPrinted = TRUE;
    }

    pendingData = FALSE;
    list = (char*) clxStrStr(list, key);
    while (list != NULL)
    {
        list = (char*) clxStrStr(list, "\"");
        if (NULL == list)
        {      
            break;
        }

        ++list;
        clxConsoleUIEngineText("\n");
        list = printEachDataList(list, delimList, count);
        isDataPrinted = TRUE;
        list = (char*) clxStrStr(list, key);
    }
    
    /*
    list is created using clxMemDup, hence once it is processed we must delete the duplicate memory
    */
    clxBspDeleteOperatorArray(pList);
    return isDataPrinted;
}

