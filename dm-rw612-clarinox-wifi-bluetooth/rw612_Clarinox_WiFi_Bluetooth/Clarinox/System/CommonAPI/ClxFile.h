#ifndef ClxFile_h
#define ClxFile_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxFile.h
* Description         Declares File related declarations
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/



#define CLX_FILE_SEEK_SET               0
#define CLX_FILE_SEEK_CUR               1



#ifdef __cplusplus
extern "C" {
#endif


/* 
The following names are reserved for stdout, stdin, and stderr virtual file handles.
An BSP implementation may handle these (if required by the application):

The following names SHALL NOT be used for any physical or other virtual files:
*/
#define CLX_STDIN_FILE_NAME              "__clxstdin"       /* May be opened with the mode "r" or "rb" */
#define CLX_STDOUT_FILE_NAME             "__clxstdout"      /* May be opened with the mode "w" or "wb" */
#define CLX_STDERR_FILE_NAME             "__clxstderr"      /* May be opened with the mode "w" or "wb" */



struct ClxFileStruct;
typedef struct ClxFileStruct ClxFILE;


/**
Open file.
Opens the file whose name is specified in the parameter \p filename and
associates it with a stream that can be identified in future operations by the
ClxFILE object whose pointer is returned. The operations that are allowed on the
stream and how these are performed are defined by the \p mode parameter.
\param[ in ] filename C string containing the name of the file to be opened.
             This parameter must follow the file name specifications of the
             running environment and can include a path if the system supports
             it.
\param[ in ] mode C string containing a file access modes. It can be:
             - "r" Open a file for reading. The file must exist.
             - "w" Create an empty file for writing. If a file with the same
               name already exists its content is erased and the file is treated
               as a new empty file.
             - "a" Append to a file. Writing operations append data at the end
               of the file. The file is created if it does not exist.
             - "r+" Open a file for update both reading and writing. The file
               must exist.
             - "w+" Create an empty file for both reading and writing. If a file
               with the same name already exists its content is erased and the
               file is treated as a new empty file.
             - "a+" Open a file for reading and appending. All writing
               operations are performed at the end of the file, protecting the
               previous content to be overwritten. You can reposition
               the internal pointer to anywhere in the file for reading,
               but writing operations will move it back to the end of file. The
               file is created if it does not exist.

             With the mode specifiers above the file is open as a text file. In
             order to open a file as a binary file, a "b" character has to be
             included in the mode string. This additional "b" character can
             either be appended at the end of the string (thus making the
             following compound modes: "rb", "wb", "ab", "r+b", "w+b", "a+b")
             or be inserted between the letter and the "+" sign for the mixed
             modes ("rb+", "wb+", "ab+").

             For the modes where both read and writing (or appending) are
             allowed (those which include a "+" sign), the stream should be
             flushed (clxFFlush) or repositioned (clxFSeek) between
             either a reading operation followed by a writing operation or a
             writing operation followed by a reading operation.

\param[ in ] stream A pointer, which on a successful return will hold the address of the stream object of type ClxFILE.
                    If the return value is not CLX_SUCCESS, this argument will be set to NULL.

\return CLX_SUCCESS if the file was opened successfully. Any other value indicates an error. In this case, stream argument will be NULL.
*/
ClxResult clxFOpen(const char *path, const char *mode, ClxFILE** stream);


/**
Close file.
Closes the file associated with the stream and disassociates it.
All internal buffers associated with the stream are flushed: the content of any
unwritten buffer is written and the content of any unread buffer is discarded.
Even if the call fails, the stream passed as parameter will no longer be
associated with the file.
\param[ in ] stream Pointer to a ClxFILE object that specifies the stream to be closed.
\return Zero on success. EOF otherwise.
*/
int          clxFClose(ClxFILE *stream);

/**
Read block of data from \p stream.
Reads an array of \p count elements, each one with a size of \p size bytes,
from the \p stream and stores them in the block of memory specified by \p ptr.
\param[ in ] ptr Pointer to a block of memory with a minimum size of (size*count) bytes.
\param[ in ] size Size in bytes of each element to be read.
\param[ in ] count Number of elements, each one with a size of size bytes.
\param[ in ] stream Pointer to a ClxFILE object that specifies an input stream.
\return The total amount of bytes read if successful is (size * count).
\post The position indicator of the stream is advanced by the total amount of bytes read.
*/
size_t      clxFRead(void *ptr, size_t size, size_t count, ClxFILE *stream);

/**
Write block of data to stream.
Writes an array of \p count elements, each one with a size of \p size bytes,
from the block of memory pointed by \p ptr to the current position in the
stream.
\param[ in ] ptr Pointer to the array of elements to be written.
\param[ in ] size Size in bytes of each element to be written.
\param[ in ] count Number of elements, each one with a size of size bytes.
\param[ in ] stream Pointer to a ClxFILE object that specifies an output stream.
\return The total amount of bytes written is (size * count).
\post The position indicator of the stream is advanced by the total number of bytes written.
*/
size_t      clxFWrite(const void *ptr, size_t size, size_t count, ClxFILE *stream);

/**
Flush stream.
If the given \p stream was open for writing and the last i/o operation was an
output operation, any unwritten data in the output buffer is written to the
file. If it was open for reading and the last operation was an input operation,
the behavior depends on the specific library implementation. In some
implementations this causes the input buffer to be cleared, but this is not
standard behavior. If the argument is a null pointer, all open files are
flushed. The \p stream remains open after this call. When a file is closed,
either because of a call to clxFClose or because the program terminates, all the
buffers associated with it are automatically flushed.
\param[ in ] stream Pointer to a ClxFILE object that specifies a buffered stream.
\return A zero value on success, EOF otherwise.
*/
int          clxFFlush ( ClxFILE * stream );

/**
Read block of data from \p stream up to n-1 bytes (excluding the NULL termination character) or until a new line character is reached, or end of file is reached (whichever happens first).
If successful, the return string is always NULL terminated.

\param[ in ] ptr Pointer to a block of memory with a minimum size of n bytes.
\param[ in ] n size of the memory block.
\param[ in ] stream Pointer to a ClxFILE object that specifies an input stream.

\return If successful, the same str, otherwise NULL.
*/
char*         clxFGets(char *str, int n, ClxFILE *stream);

/**
writes a one-byte unsigned character specified by the argument ch to the specified stream and advances the position indicator for the stream.

\return The same character that has been written. If an error occurs, EOF is returned and the error indicator is set.
*/
int           clxFPutc(int ch, ClxFILE* stream);

/**
gets the next one-byte unsigned character from the specified stream and advances the position indicator for the stream.

\return The same character that has been written. If an error occurs, EOF is returned and the error indicator is set.
*/
int           clxFGetc(ClxFILE* stream);

/**
Write string to stream.
Writes the string pointed by \p str to the \p stream.
The function begins copying from the address specified (\p str) until it reaches
the terminating null character ('\0'). This final null-character is not copied
to the \p stream.
\param[ in ] str An array containing the null-terminated sequence of characters
             to be written.
\param[ in ] stream Pointer to a ClxFILE object that identifies the stream where
             the string is to be written.
\return non-negative value on success, EOF otherwise.
*/
int          clxFPuts ( const char * str, ClxFILE * stream );

/**
Reposition stream position indicator.
Sets the position indicator associated with the stream to a new position defined
by adding \p offset to a reference position specified by \p origin. The
End-of-File internal indicator of the stream is cleared after a call to this
function, and all effects from previous calls are dropped. When using clxFSeek
on text files with offset values other than zero or values retrieved with
clxFTell, bear in mind that on some platforms some format transformations occur
with text files which can lead to unexpected repositioning. On streams open for
update (read+write), a call to clxFSeek allows to switch between reading and
writing.
\param[ in ] stream Pointer to a ClxFILE object that identifies the stream.
\param[ in ] offset Number of bytes to offset from origin.
\param[ in ] origin Position from where offset is added. It is specified by one
             of the following constants.
             - CLX_FILE_SEEK_SET Beginning of file
             - CLX_FILE_SEEK_CUR Current position of the file pointer

NOTE : Repositioning from end of the file is not supported.

\return zero on success, non-zero values otherwise.
*/
int          clxFSeek ( ClxFILE * stream, long int offset, int origin );


/**
Return the value of the error indicator of a stream.

\param[ in ] stream Pointer to a ClxFILE object.

\return non-zero if the error indicator has been set. zero otherwise.
*/
int          clxFError ( ClxFILE * stream );


/**
Return the value of the EOF (End Of File) indicator of a stream.

\param[ in ] stream Pointer to a ClxFILE object.

\return non-zero if the EOF indicator has been set. zero otherwise.
*/
int          clxFEof ( ClxFILE * stream );

/**
Clear the error and EOF indicators of a stream, and the last error number (as returned by clxFErrorNo) to CLX_SUCCESS.

\param[ in ] stream Pointer to a ClxFILE object.
*/
void        clxClearErr ( ClxFILE * stream );


/**
Returns the total file size. The maximum file size is limited to the size of "long int" in the platform.

\param[ in ] stream Pointer to a ClxFILE object.
\param[ out ] fileSize Will be set to the file size.
*/
void        clxGetFileSize (ClxFILE * stream, long int* fileSize);



#ifdef __cplusplus
}
#endif


#endif    // ClxFile_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused macro declarations 	  */
/* Rule          : MISRA-C:2012 Rule 2.5                                      */ 
/* Justification : Macro declarations are available to be used in user		  */ 
/*				   applications.											  */
/******************************************************************************/

