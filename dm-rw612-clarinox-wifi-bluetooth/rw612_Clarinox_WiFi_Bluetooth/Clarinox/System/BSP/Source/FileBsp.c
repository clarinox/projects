/*******************************************************************************
*
* Project             Clarinox Softframe
* File                FileBsp.c
* Description         BSP Support for File Operations
*
* This file contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved (C) Copyright Clarinox Technologies Pty Ltd 2001-2026
*
*******************************************************************************/

#include <stdlib.h>
#include "ClxBsp.h"
#include "ClxUserFile.h"
#include <string.h>

/* Must define only one of the below MACROs. MUST BE COMING FROM the PROJECT

 #define RAM_FILE_SUPPORTED
 #define FLASH_FILE_SUPPORTED 

*/                                      

/**
File header information for flash files (file length)
 */
#define FILE_HEADER_LENGTH 	4U

 #if defined( FLASH_FILE_SUPPORTED )
/**
Used for maintaining the currently opened file's file length
 */
static u4 fileLength = 0U;
#endif

/**
Print console debug traces for file interface
*/
//#define FILE_INTERFACE_DBG_TRACE

/* IMPORTANT
 *   TODO -
 * FILE RECORDS NEED TO BE WRAPPED IN PROPER HEADER AND CHECKSUM FORMAT
 * TO DETECT AND HANDLE CORRUPTION PROPERLY.  
 */

/* User application must provide the file list. An example is provided below */
extern VirtualFile fileList[];

/**
Pointer to the constant virtual file list of the device.
 */
const VirtualFile* clxVirtualFileSystemMap = NULL;

/**
    This function called when open file request is received from the system.
    \param[ in ] name NULL terminated string to indicate name of the file.
    \param[ in ] flags different file access modes such as 'read', 'write', 'append' etc...
                 One or more combination of access flags can be used for file operations. For e.g. read operation can be (CLX_FILE_MUST_EXIST & CLX_FILE_FLAG_READ).
                 The implementation is NOT required to support any combination of flags.
    \param[ in ] file pointer to the file identifier. The identifier is a value of type void*. Its actual content is implementation-specific. If the file is opened
                 successfully, this value CANNOT be NULL. Otherwise, it will be ignored by the system.
    \param[ in ] currentSize size of the file.

    \return ClxResult. Function must return one of the following result codes:
    - CLX_SUCCESS: if operation is successful.
    - CLX_FILE_NOT_EXIST: if file does not exist in file system.
*/
static ClxResult open (const s1* name, u2 flags, void** file, u4* currentSize)
{
    ClxResult ret = CLX_FILE_NOT_EXIST;
    u4 i = 0;

    while(clxVirtualFileSystemMap[i].fileName != NULL)
    {
	    if (strcmp(name, clxVirtualFileSystemMap[i].fileName) == 0)
	    {
            *file = (void*)&clxVirtualFileSystemMap[i];
            switch(clxVirtualFileSystemMap[i].type)
            {
#if defined( READ_ONLY_FILE_SUPPORTED )
                case StorageType_RAM:
					{
						*currentSize = clxVirtualFileSystemMap[i].ram.fileLen;
#if defined (FILE_INTERFACE_DBG_TRACE)
					    CLX_PRINTF("\nRead only file %s opened", name);
						CLX_PRINTF("file size %u\n", *currentSize);
#endif /* FILE_INTERFACE_DBG_TRACE */
						ret = CLX_SUCCESS;
						break;
					}
#endif /* READ_ONLY_FILE_SUPPORTED */


#if defined (FLASH_FILE_SUPPORTED)
                case StorageType_Flash:
                    {
                        if(flags & CLX_FILE_FLAG_WRITE)
                        {
                        	/* erase the file if opened with write flag. */
                            memset((void*)(clxVirtualFileSystemMap[i].ram.fileBuffer), 0x00, clxVirtualFileSystemMap[i].ram.fileLen);
                            *currentSize = 0;
                            ret =  CLX_SUCCESS;
                        }
                        else if(flags & CLX_FILE_FLAG_READ)
                        {
                        	/* Retrieve the file length using the file header information */
                        	*currentSize = (u4)clxVirtualFileSystemMap[i].ram.fileBuffer[0];
                            ret = CLX_SUCCESS;
                        }
#if defined (FILE_INTERFACE_DBG_TRACE)
                        CLX_PRINTF("\nRead write file %s opened", name);
                        CLX_PRINTF("file size %u\n", *currentSize);
#endif
                        break;
                    }
#endif /* FLASH_FILE_SUPPORTED */
                
                default:
                    {
                        BLACKBOX;
                        break;
                    }
            }
        }
        i++;
    }

	return ret;
}

/**
This Callback function called when close file request is received from Client.
\param[ in ] file handle to the file to be closed.
\return This function does not return any parameters. After function returns the stack considers closing of the file regardless.
*/
static void close (void* file)
{
    VirtualFile* vf = (VirtualFile*)file;
#if defined( FLASH_FILE_SUPPORTED )
    u4* ramBuffer = NULL;
#endif /* FLASH_FILE_SUPPORTED */

#if defined (FILE_INTERFACE_DBG_TRACE)
    CLX_PRINTF("closing file %s\n", vf->fileName);
#endif /* FILE_INTERFACE_DBG_TRACE */

    switch(vf->type)
    {
      
#if defined( READ_ONLY_FILE_SUPPORTED )
    case StorageType_RAM:
		{
			/*Do nothing */
			break;
		}
#endif /* defined( READ_ONLY_FILE_SUPPORTED ) */

#if defined( FLASH_FILE_SUPPORTED )
    case StorageType_Flash:
		{
			/* Update the file header with the latest file length */
			ramBuffer = (u4*)(&(vf->ram.fileBuffer[0]));

			*ramBuffer = fileLength;

#if defined (FILE_INTERFACE_DBG_TRACE)
		    CLX_PRINTF("file length %u bytes\n", *((u4*)(&vf->ram.fileBuffer[0])));
#endif /* FILE_INTERFACE_DBG_TRACE */

		    fileLength = 0U;
			break;
		}
#endif /* FLASH_FILE_SUPPORTED */
                
    default:
      
        break;
    }    
}

/**
This Callback function called when a file WRITE request is received in Clarinox code. Note that the write function call does not dictate the complete writing of the dataLength
\param[ in ] file handle to the file to be written.
\param[ in ] indexMsb The MSB value of the file index to which the data is to be written.
\param[ in ] indexLsb The LSB value of the file index to which the data is to be written.
\param[ in ] data pointer to the data buffer which contains the data to be written into the file.
\param[ in ] dataLength length of the dataBuffer to be written.
\param[ in ] written if the function returns then this variable indicates the length of the data written so far....
                            In case function returns ClxResult which is other than CLX_SUCCESS, lengthRead must be ignored.
\return ClxResult. Function must return one of the following result codes:
- CLX_SUCCESS: if operation is successful.
- CLX_FILE_ERROR_WRITING: if there is problem with write operation.
*/
static ClxResult write (void* file, u4 indexMsb, u4 indexLsb, const void* data, size_t len, size_t* written)
{
    VirtualFile* vf = (VirtualFile*)file;
    ClxResult ret = CLX_FILE_ERROR_WRITING;
    
    switch(vf->type)
    {
#if defined( READ_ONLY_FILE_SUPPORTED )
	    case StorageType_RAM:
			{
				/* No write support for volatile file implementation, it is read only */
				*written = len;
				/* CLX_PRINTF("file write %u bytes\n", *written); */
				ret = CLX_SUCCESS;
				break;
			}
#endif /* defined( READ_ONLY_FILE_SUPPORTED ) */

#if defined (FLASH_FILE_SUPPORTED)
		case StorageType_Flash:
			{
				memcpy((void*)(vf->ram.fileBuffer + indexLsb), data, len);
				*written = len;
#if defined (FILE_INTERFACE_DBG_TRACE)
				CLX_PRINTF("file write %u bytes\n", *written);
#endif /* FILE_INTERFACE_DBG_TRACE */
				fileLength = fileLength + len;
				ret = CLX_SUCCESS;
				break;
			}
#endif /* FLASH_FILE_SUPPORTED */

		default:
			{
				BLACKBOX;
				break;
			}
    }

    return ret;
}

/**
This Callback function called when a READ request is received from the Clarinox code. Note that the READ function call does not dictate the complete reading of the dataLength.

NOTE : If the index is right at the end of the file or beyond that, CLX_FILE_END_OF_FILE shall be returned. However, if the index is within the file and at least one byte can be read, the implementation
shall not return CLX_FILE_END_OF_FILE.

\param[ in ] file handle to the file to be read.
\param[ in ] indexMsb The MSB value of the file index from which the data is to be read.
\param[ in ] indexLsb The LSB value of the file index from which the data is to be read.
\param[ in ] data pointer to the buffer allocated by user, for the data.
\param[ in ] dataLength length of the dataBuffer to be read.
\param[ in ] read if the function returns then this variable indicates the length of the data read so far....
             In case function returns ClxResult which is other than CLX_SUCCESS, lengthRead MUST BE set to zero.

\return ClxResult.
- CLX_SUCCESS: if operation is successful.
- CLX_FILE_END_OF_FILE : The provided index is at the end of the file or beyond.
*/
static ClxResult read (void* file, u4 indexMsb, u4 indexLsb, void* buf, size_t len, size_t* read)
{
    ClxResult ret = CLX_FILE_ERROR_READING;
    VirtualFile* vf = (VirtualFile*)file;

    switch(vf->type)
    {
#if defined( READ_ONLY_FILE_SUPPORTED )
    case StorageType_RAM:
        {
            *read = 0;

            if (indexMsb)
            {
#if defined (FILE_INTERFACE_DBG_TRACE)
                CLX_PRINTF("file read error LEN_OVER_4GB_NOT_SUPPORTED\n");
#endif /* FILE_INTERFACE_DBG_TRACE */
                ret = CLX_FILE_LEN_OVER_4GB_NOT_SUPPORTED;
            }
            else if (!file)
            {
#if defined (FILE_INTERFACE_DBG_TRACE)
                CLX_PRINTF("file read error INVALID_HANDLE\n");
#endif /* FILE_INTERFACE_DBG_TRACE */
                ret = CLX_FILE_INVALID_HANDLE;
            }
            else
            {

                u4 fileLen = vf->ram.fileLen;
                const s1* fileBuffer = vf->ram.fileBuffer;

                if (fileLen <= indexLsb)
                {
#if defined (FILE_INTERFACE_DBG_TRACE)
                    CLX_PRINTF("file read END_OF_FILE\n");
#endif /* FILE_INTERFACE_DBG_TRACE */
                    ret = CLX_FILE_END_OF_FILE;
                }
                else
                {
                    if ((fileLen - indexLsb) < len)
                    {
                        *read = fileLen - indexLsb;
                    }
                    else
                    {
                        *read = len;
                    }

                    memcpy(buf, fileBuffer + indexLsb, *read);
                    ret = CLX_SUCCESS;
                }
            }
            
            break;
        }
#endif /* READ_ONLY_FILE_SUPPORTED */

#if defined (FLASH_FILE_SUPPORTED)
    case StorageType_Flash:
        {
            *read = 0;

            if (indexMsb)
            {
#if defined (FILE_INTERFACE_DBG_TRACE)
               CLX_PRINTF("file read error LEN_OVER_4GB_NOT_SUPPORTED\n");
#endif /* FILE_INTERFACE_DBG_TRACE */
                ret = CLX_FILE_LEN_OVER_4GB_NOT_SUPPORTED;
            }
            else if (!file)
            {
#if defined (FILE_INTERFACE_DBG_TRACE)
                CLX_PRINTF("file read error INVALID_HANDLE\n");
#endif /* FILE_INTERFACE_DBG_TRACE */
                ret = CLX_FILE_INVALID_HANDLE;
            }
            else
            {
                u4 fileLen = (u4)(vf->ram.fileBuffer[0]);

                /* The data area start after the file header */
                const s1* fileBuffer = vf->ram.fileBuffer + FILE_HEADER_LENGTH;

                if (fileLen <= indexLsb)
                {
#if defined (FILE_INTERFACE_DBG_TRACE)
                    CLX_PRINTF("file read END_OF_FILE\n");
#endif /* FILE_INTERFACE_DBG_TRACE */
                    ret = CLX_FILE_END_OF_FILE;
                }
                else
                {
                    if ((fileLen - indexLsb) < len)
                    {
                        *read = fileLen - indexLsb;
                    }
                    else
                    {
                        *read = len;
                    }

                    memcpy(buf, fileBuffer + indexLsb, *read);
                    ret = CLX_SUCCESS;
                }
            }

            break;
        }
#endif /* FLASH_FILE_SUPPORTED */

    default:
        {
            BLACKBOX;
            break;
        }
    }

    return ret;
}

/**
This Callback function called by the system to question if the given position in the file exists (is not beyond the end of the file).
Indexes are zero-based.
\param[ in ] file handle to the file to be read.
\param[ in ] indexMsb The MSB value of the position index which is to be checked for existence in the file.
\param[ in ] indexLsb The LSB value of the position index which is to be checked for existence in the file.

\return boolean. Function must return either TRUE or FALSE.
- TRUE: if index exists in the file.
- FALSE: if index is beyond the end of the file.
*/
static boolean isFilePositionValid (void* file, u4 indexMsb, u4 indexLsb)
{
    VirtualFile* vf = (VirtualFile*)file;

#if defined (FILE_INTERFACE_DBG_TRACE)
    CLX_PRINTF("file isIndexSupported %s\n", vf->fileName);
#endif /* FILE_INTERFACE_DBG_TRACE */

	if (indexMsb)
	{
		return FALSE;
	}
	else if (!file)
	{
		return FALSE;
	}

    switch(vf->type)
    {
#if defined( READ_ONLY_FILE_SUPPORTED )
    case StorageType_RAM:
        {
	    u4 fileLen = vf->ram.fileLen;
	    return (indexLsb < fileLen) ? TRUE : FALSE;	
        }
#endif /* defined( READ_ONLY_FILE_SUPPORTED ) */

    default:
        BLACKBOX;
    }

    return FALSE;
}


/**
This Callback function called by the system to force the implementation to flush any data, previously written into the file, to be written to the permanent storage.
This needs to be properly implemented if caching is internally used by the implementation.
\param[ in ] file handle to the file to be read.
\return ClxResult.
*/
static ClxResult flush (void* file)
{
    return CLX_SUCCESS;
}


/**
Callback function prototypes used by BSP to handle file system related function calls.
*/
ClxFileBspInterface clxMemoryFileInterface = {&open,
											  &close,
											  &write,
											  &read,
											  &isFilePositionValid,
                                              &flush};
                                             
