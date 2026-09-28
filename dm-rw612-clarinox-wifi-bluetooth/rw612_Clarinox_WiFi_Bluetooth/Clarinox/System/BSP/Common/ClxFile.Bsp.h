#ifndef ClxFile_Bsp_h
#define ClxFile_Bsp_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxFile.Bsp.h
* Description         File System interface for BSP
*
* This software is copyrighted and contains proprietary information of
* Clarinox Technologies Proprietary Limited.
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

/**
Flags representing file access modes.
*/

/**
Flag used for read operation. File must exist (even if the flag CLX_FILE_MUST_EXIST is not added).
*/
#define CLX_FILE_FLAG_READ        0x0001
/**
Flag used for write operation.
*/
#define CLX_FILE_FLAG_WRITE       0x0002
/**
Flag used to indicate binary file. If not used, the implementation must assume a text file.
*/
#define CLX_FILE_FLAG_BINARY      0x0004
/**
Flag used to append/modify at the end of the file.
*/
#define CLX_FILE_FLAG_APPEND      0x0008
/**
Flag used to indicate that file must already exist before the commencement of a certain file operation. If this flag is not
used, and the file does not exist, it may be created, or the operation may fail (depending on the other flags used, and on the specific implementation). 
*/
#define CLX_FILE_MUST_EXIST       0x0010
/**
Flag used to indicate that the file is being opened in the Stream mode. In the Stream mode, the file can be read or written as a stream. No random access is supported. In this mode,
the indexMsb and indexLsb arguments passed to the write() and read() functions are guaranteed to be sequential (the implementation of this interface does not require to maintain a current index value). 
This is the default mode. If neither CLX_FILE_STREAM_MODE nor CLX_FILE_RANDOM_ACCESS_MODE is provided, the Stream mode should be assumed by the implementation of open() function. 
If both CLX_FILE_STREAM_MODE and CLX_FILE_RANDOM_ACCESS_MODE are passed, and the implementation does not support both at the same time, the implementation of open() function must return CLX_FILE_OPEN_FLAG_NOT_CONSISTENT.
*/
#define CLX_FILE_STREAM_MODE      0x0020
/**
Flag used to indicate that the file is being opened in the Random Access mode. The Access Mode supports access to a file (for read or write or both) in an arbitrary index.
However, this mode cannot be used to read from or write to an index which does not exist yet. Like Stream mode, the file can be expanded by writing to the end of the file (the last index).
If both CLX_FILE_STREAM_MODE and CLX_FILE_RANDOM_ACCESS_MODE are passed, and the implementation does not support both at the same time, the implementation of open() function must return CLX_FILE_OPEN_FLAG_NOT_CONSISTENT.
*/
#define CLX_FILE_RANDOM_ACCESS_MODE      0x0040


#ifdef __cplusplus
extern "C" {
#endif

/**
Callback function prototypes used by BSP to handle file system related function calls.
*/
typedef struct ClxFileBspInterfaceStruct
{
    /**
    This Callback function called when open file request is received from the system.
    \param[ in ] name NULL terminated string to indicate name of the file.
    \param[ in ] flags different file access modes such as 'read', 'write', 'append' etc... 
                 One or more combination of access flags can be used for file operations. For e.g. read operation can be (CLX_FILE_MUST_EXIST & CLX_FILE_FLAG_READ).
                 The implementation is NOT required to support any combination of flags.
    \param[ in ] file pointer to the file identifier. The identifier is a value of type void*. Its actual content is implementation-specific. If the file is opened
                 successfully, this value CANNOT be NULL. Otherwise, it will be ignored by the system.
    \param[ in ] currentSize size of the file.
    
    \return ClxResult. Function must return one of the following result codes: 
    - #CLX_SUCCESS: if operation is successful.
    - CLX_FILE_NOT_EXIST: if file does not exist in file system
    - CLX_FILE_CREATE_FAILED: If file creation fails for any reason.
    - CLX_FILE_OPEN_FAILED: if file cannot be opened or file open is forbidden.
    - CLX_FILE_IS_OPEN: if file is already in use/opened.
    - CLX_FILE_NOT_WRITABLE: if file cannot be opened for writing.
    - CLX_FILE_NOT_READABLE: if file cannot be opened for reading.
    - CLX_FILE_NOT_APPENDABLE: if file cannot be opened for appending.
    - CLX_FILE_OPEN_FLAG_NOT_CONSISTENT: if the combination of the flags provided is not supported by the implementation.
    - CLX_FILE_UNSPECIFIED_ERROR: if file cannot be opened for unknown reasons.
    */
    ClxResult (*open) (const s1* name, u2 flags, void** file, u4* currentSize);

    /**
    This Callback function called when close file request is received from Client.
    \param[ in ] file handle to the file to be closed.
   
    \return This function does not return any parameters. After function returns the stack considers closing of the file regardless.
    */
    void (*close) (void* file);

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
    - #CLX_SUCCESS: if operation is successful.
    - CLX_FILE_INVALID_HANDLE: if handle is invalid
    - CLX_FILE_NOT_WRITABLE: if write operation is forbidden for this file.
    - CLX_FILE_ERROR_WRITING: if there is problem with write operation.
    - CLX_FILE_ACCESS_DENIED: if the file cannot be written due to for e.g. file permissions are set to Read-only, file already open etc...
    */
    ClxResult (*write) (void* file, u4 indexMsb, u4 indexLsb, const void* data, size_t dataLength, size_t* written);
    
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

    \return ClxResult. Function must return one of the following result codes:
    - CLX_SUCCESS: if operation is successful.
    - CLX_FILE_END_OF_FILE : The provided index is at the end of the file or beyond.
    - CLX_FILE_INVALID_HANDLE: if handle is invalid
    - CLX_FILE_ERROR_READING: if there is problem with read operation.
    - CLX_FILE_NOT_READABLE: if the file read is forbidden.
    - CLX_FILE_ERROR_READING: An error occurred while reading the file.
    - CLX_FILE_ACCESS_DENIED: if the file cannot be written due to for e.g. file permissions are set such that READ is forbidden, file already open, file cannot be opened etc...
    */
    ClxResult (*read) (void* file, u4 indexMsb, u4 indexLsb, void* buf, size_t dataLength, size_t* read);

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
    boolean (*isFilePositionValid) (void* file, u4 indexMsb, u4 indexLsb);

    /**
    This Callback function called by the system to force the implementation to flush any data, previously written into the file, to be written to the permanent storage.
    This needs to be properly implemented if caching is internally used by the implementation.
    \param[ in ] file handle to the file to be read.
   
    \return ClxResult. Function must return one of the following result codes:
    - CLX_SUCCESS: if operation is successful.
    - CLX_FILE_INVALID_HANDLE: if handle is invalid
    - CLX_FILE_NOT_WRITABLE: if write operation is forbidden for this file.
    - CLX_FILE_ERROR_WRITING: if there is problem with write operation.
    - CLX_FILE_ACCESS_DENIED: if the file cannot be written due to for e.g. file permissions are set such that READ is forbidden, file already open, file cannot be opened etc...
    */
    ClxResult (*flush) (void* file);

} ClxFileBspInterface;

/**
clxFileBspInterface must be assigned to a user filled structure instance that defines user implementations for the non-volatile storage system implementation. 
#ClxFileBspInterface structure (of type #ClxFileBspInterfaceStruct) provides the elements of the non-volatile storage functions. If a file system is available, 
then these functions must be associated to their corresponding standard file system calls.
*/
extern ClxFileBspInterface* clxFileBspInterface;

#ifdef __cplusplus
}
#endif


#endif // ClxFile_Bsp_h

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
