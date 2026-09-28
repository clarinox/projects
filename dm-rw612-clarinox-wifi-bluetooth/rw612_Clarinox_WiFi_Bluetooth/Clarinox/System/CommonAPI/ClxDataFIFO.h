#ifndef ClxDataFIFO_h
#define ClxDataFIFO_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxDataFIFO.h
* Description         ClxDataFIFO
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/



#define CLX_DATA_FIFO_MIN_BUFFER_SIZE          16       /*!< The minimum size of the buffer associated to a ClxDataFIFO object */



#ifdef __cplusplus
extern "C" {
#endif


struct ClxDataFIFOStruct;
typedef struct ClxDataFIFOStruct ClxDataFIFO;

/**
Creates a general purpose FIFO to store data bytes. The FIFO buffer is allocated in the SoftFrame poolset. The total size of the buffer is always a power of 2 (e.g. 16, 32, ..., 1024, ...).
The minimum supported buffer size is defined as #CLX_DATA_FIFO_MIN_BUFFER_SIZE.

NOTE : The actual size of the buffer which can be used to store data is one less than the total size (e.g. 15, 31, ..., 1023, ...). 
       This is due to the fact that the FIFO object reserves one byte to distinguish between empty and full buffer.

Example: If the value 730 is passed to this function, it will be rounded up to 1024. 
         The actual buffer available for storing data will then be 1023 bytes.

\param[ in ] totalBufferSize The total size of the FIFO buffer in bytes. If the value provided is not a power of 2, it will be rounded up to the next power-of-2 value.
                             The buffer size available for storing data is one less than this value.   

\return Pointer to the data FIFO object of type ClxDataFIFO. When the object is not need any longer, it must be destroyed by a call to #clxDataFIFO_Destroy. 
*/
extern ClxDataFIFO* clxDataFIFO_Create(u4 totalBufferSize);

/**
Destroys ab object of type ClxDataFIFO.

\param[ in ] obj The data FIFO object to be destroyed.
*/
extern void clxDataFIFO_Destroy(ClxDataFIFO* obj);

/**
Pushes one or more bytes of data to the data FIFO. This function does not allow overwriting the data currently stored in the FIFO.

\param[ in ] obj The data FIFO object.
\param[ in ] data The data to be pushed into the FIFO. This argument CANNOT be NULL.
\param[ in ] length the length of the data. 

\return TRUE if the provided data has been successfully pushed into the FIFO.
        FALSE if there is not enough space to push the provided data into the FIFO. In this case, no data will be pushed at all.
*/
extern boolean clxDataFIFO_Push(ClxDataFIFO* obj, const u1* data, u4 length);

/**
Pushes one or more bytes of data to the data FIFO. If there is not enough space in the FIFO buffer, part or all of the data currently stored in the FIFO buffer will be overwritten by the new data.
NOTE : The provided data CANNOT be larger than the maximum size of the FIFO buffer (as returned by a call to #clxDataFIFO_GetMaximumLength).

\param[ in ] obj The data FIFO object.
\param[ in ] data The data to be pushed into the FIFO. This argument CANNOT be NULL.
\param[ in ] length the length of the data. 

\return Number of bytes overwritten in the FIFO buffer. 
*/
extern u4 clxDataFIFO_PushOverwrite(ClxDataFIFO* obj, const u1* data, u4 length);

/**
Removes one or more bytes of currently stored data from the FIFO and copies them to a caller-provided buffer.

NOTE : If some data needs to be removed from the FIFO without being copied to an external buffer, use the clxDataFIFO_Release() API instead.

\param[ in ] obj The data FIFO object.
\param[ in ] output The caller-provided buffer to which the data will be copied.
\param[ in ] maxLength The maximum number of bytes to be removed from the FIFO and copied into the caller-provided buffer. 
                       The actual number of bytes copied may be less than this value if not enough data is currently available in the FIFO.
\return The actual number of bytes removed from the FIFO and copied into the output buffer. This value cannot be more than the maximum length argument passed to the function.
*/
extern u4 clxDataFIFO_Pop(ClxDataFIFO* obj, u1* output, u4 maxLength);


/**
Removes one or more bytes of currently stored data from the FIFO.

\param[ in ] obj The data FIFO object.
\param[ in ] length The number of bytes to be removed from the FIFO. 

\return TRUE if the data has been successfully removed from the FIFO.
        FALSE if the provided length is lager than the number of bytes currently stored in the FIFO. In this case, no data will be removed from the FIFO.
*/
extern boolean clxDataFIFO_Release(ClxDataFIFO* obj, u4 length);


/**
Returns the current number of bytes stored in the data FIFO. 

\param[ in ] obj The data FIFO object.
\return The number of bytes currently available in the FIFO.
*/
extern u4 clxDataFIFO_GetCurrentLength(ClxDataFIFO* obj);


/**
Returns the size of the free buffer currently available in the FIFO. The user may push data of up this length to the FIFO buffer without overwritting any data currently stored in the FIFO. 

\param[ in ] obj The data FIFO object.
\return The number of free bytes available in the FIFO for new data.  
*/
extern u4 clxDataFIFO_GetFreeLength(ClxDataFIFO* obj);

/**
Removes all currently stored data from the data FIFO object. When this function returns, the FIFO will be completely empty (e.g. A subsequenct call to #clxDataFIFO_GetCurrentLength will return 0).

NOTE : This function DOES NOT destroy the FIFO object.

\param[ in ] obj The data FIFO object.
*/
extern void clxDataFIFO_Clear(ClxDataFIFO* obj);



#ifdef __cplusplus
}
#endif


#endif // ClxDataFIFO_h



