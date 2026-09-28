#ifndef ClxExpandableBuffer_h
#define ClxExpandableBuffer_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxExpandableBuffer.h
* Description         Defines ClxExpandableBuffer class
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


/**
An instance of the class ClxExpandableBuffer represents a buffer which size is dynamic and may grow if required.
The pool (heap) from which the buffer is allocated is determined by the Allocator class passed as the template argument.
An instance holds an initial buffer with an initial size (which could be 0). As new data is added to the buffer,
the buffer grows automatically based on a expansion factor, which is given as the second argument of the constructor.

NOTE : An instance is used to hold some data with a certain length. Please note that the current size of the internal buffer
is NOT the same as the length of the data stored in the object. In other words, at any given time, there might be some empty space at the end of internal
buffer.
*/
template<class Allocator>
class ClxExpandableBuffer
{
private:
    u1*         buf_;
    ClxSize     dataLength_;
    ClxSize     bufSize_;
    u1          expansionFactor_;

    Allocator   allocator_;

public:
    /**
    Constructs an instance of ClxExpandableBuffer.

    \param[ in ] initialSize The initial size of the buffer in the memory. If set to 0, no buffer will be allocated initially.
    \param[ in ] expansionFactor The expansion factor which is used when the buffer needs to be expanded. Please refer to documentation
    of the method #addData() for more information. This value can be set to 0.
    */
    ClxExpandableBuffer(ClxSize initialSize = 0, u1 expansionFactor = 2)
    :
    buf_(NULL), dataLength_(0), bufSize_(initialSize), expansionFactor_(MAX(expansionFactor, 1))
    {
        if (initialSize)
        {
            buf_ = (u1*)allocator_.alloc(initialSize);
        }
    }    

    /**
    Deconstructs the instance. If the instance currently holds any buffer in the memory, it will be deleted as well.
    */
    ~ClxExpandableBuffer()
    {
        if (buf_) 
        {
            allocator_.free(buf_);
        }
    }


    /**
    Adds new data to the end of the buffer. Based on the current size of the internal buffer, one of the following will take place:
    
    - If there is no buffer allocated (e.g. initialSize was set to zero when the constructer was called), it will be allocated
    with the length of the data.
    - If there is already a buffer allocated, and there is enough empty space at the end of the buffer to hold the new data, no size expansion will
    take place and the new data will be simply copied to the end of the buffer.
    - If there is already a buffer allocated, but there is not enough empty space at the end of the buffer to hold the new data, it buffer will be expanded first.
    Assume the current size of the buffer is "bufSize", and the current size of data stored in the buffer is "dataLength". Then the new size of the buffer will be:

    bufSize = MAX(bufSize*expansionFactor, dataLength+len);

    where MAX returns the argument which is greater than the other, and expansionFactor is the value passed to the constructor. If expansionFactor is set to 0,
    then the new size of the buffer will always be dataLength+len.
    
    \param[ in ] data A pointer to the new data to be added to the end of the buffer. This CANNOT be NULL.
     \param[ in ] len The length of the data to be added to the end of the buffer. This CANNOT be 0.
    */
    void addData(const u1* data, u4 len)
    {
        expand(len);

        memcpy((buf_ + dataLength_), data, len);
        dataLength_ += len;
    }

    /**
    Expands the buffer so an empty space of at least lengthToAdd will be in the end of the buffer. The rules of how the buffer is expanded is exactly the same as
    #addData(). The only difference between this method and addData() is that after expansion (if required), #addData will copy the passed data to the end of the buffer,
    but this method will not copy anything to the buffer.

    \param[ in ] lengthToAdd The minimum amount of empty space (in bytes) which is required at the end of the buffer. When this function returns, the caller can make sure
    that at least lengthToAdd bytes of empty space exists at the end of the buffer.
    */
    void expand(u4 lengthToAdd)
    {
        u4 newLength = dataLength_ + lengthToAdd;
        if (bufSize_ < newLength)
        {
            bufSize_ = MAX((bufSize_ * expansionFactor_), newLength);

            buf_ = (u1*)allocator_.realloc(buf_, bufSize_);
        }
    }

public:
    /**
    Resets the contents of the buffer by setting the length of the stored data to 0. The current size of the buffer will not change. 
    */
    void reset()
    {
        dataLength_ = 0;
    }

    /**
    Returns a pointer to the beginning of the internal buffer in the memory. The pointer can be used to read from the buffer or write into it.
    */
    u1* operator*()
    {
        return buf_;
    }

    /**
    Returns a constant pointer to the beginning of the internal buffer in the memory. The pointer can only be used to read from the buffer.
    */
    const u1* operator*() const
    {
        return buf_;
    }

    /**
    Returns the length of the data currently stored in the internal buffer. This value is NOT the same as the current size of the internal buffer. 
    */
    ClxSize dataLength() const
    {
        return dataLength_;
    }
};


#endif // ClxExpandableBuffer_h

