#ifndef ClxUserFile_h
#define ClxUserFile_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxUserFile.h
* Description         File System interface for BSP
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/
#include "ClxTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
StorageType is used for defining the user file storage type. Either Flash or RAM file is used, the RAM file is a read-only storage.
This is only valid if a file system is not found on the target platform (CLX_FILE_SYSTEM is not defined).
*/
typedef enum StorageType_
{
    StorageType_RAM = 0,
    StorageType_Flash
}StorageType;

/**
VirtualFileStruct defines a structure where user can declare all the files used in the application. 
This is only valid if a file system is not found on the target platform (CLX_FILE_SYSTEM is not defined). Below is an example use of the structure;
\code
 const VirtualFile fileList[] = { { StorageType_Flash, "SoftFrame.cfg",    {sizeof(debugConfig),     debugConfig}     },
                                  { StorageType_Flash, "ClarinoxBlue.cfg", {sizeof(bluetoothConfig), bluetoothConfig} },
                                  { StorageType_Flash, "licence.txt",      {sizeof(licence),         licence}         } };
\endcode

*/
typedef struct VirtualFileStruct
{
    StorageType type;
    const s1*   fileName;
#if defined( READ_ONLY_FILE_SUPPORTED )
    struct
    {
        u4            fileLen;
        const s1*    fileBuffer;
    } ram;
#endif
    
#if defined( FLASH_FILE_SUPPORTED )
    struct
    {
        u4          blockIndex;
    } flash;
#endif
} VirtualFile;

#ifdef __cplusplus
}
#endif


#endif // ClxUserFile_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/
