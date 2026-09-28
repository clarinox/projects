#ifndef ClxCircularDataContainer_h
#define ClxCircularDataContainer_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxCircularDataContainer.h
* Description         ClxCircularDataContainer class
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#ifdef __cplusplus


#define Clx_CircularDataContainer_BuffersSizeMask                                (size - 1)
#define Clx_CircularDataContainer_BuffersSize                                    (size - 1)    // one byte is always kept free to be able to distinguish between an empty container and completely full container.

/**
ClxCircularDataIterator is an object which points to a specific location in a data container object.
ClxCircularDataIterator objects can be increased and decreased as normal numeric variables. But, they cannot
be compared by usual C/C++ operators ( e.g. > < == != <= >= ). ClxCircularDataContainer::isEuqal(), ClxCircularDataContainer::isBigger(),
and ClxCircularDataContainer::isSmaller() methods have to be used to compare two iterator objects which belong to a certain data container object.
Also, in order to find the distance between two iterators, the subtraction operator (-) cannot be used.
ClxCircularDataContainer::distance() method has to be used, instead. Two iterators can be added by the addition operator (+). 
The result is meant to be a third iterator with its distance from the beginning point being the sum of distances of the 
two original iterators from the beginning point. Remember that iterators point to locations on a circle, not an infinitely long line.
*/
typedef u4 ClxCircularDataIterator;

/**
Size MUST be a power of 2 (2, 4, 8, ..., 128, ..., 4096, ...). If size is not a power of 2, the behaviour of
this class will be undefined. The actual size of the circular data container will be one byte less than size. This is due to the fact
that one byte is always left empty in order to be able to differentiate between completely empty container and completely full container. 
*/

/**
ClxCircularDataContainer implements a circular data container. Circular data containers suit situations when raw data need to be buffered
temporarily for analysis/parsing. The unit of elements stored in a data container is always "a byte".

The data container is made up of a static buffer of the length fixed as "size - 1". The data container implements its own concept of allocation.
Only allocated region of the container can be used (read and written). Reading from and writing to non-allocated region is illegal and MUST NOT
be carried out. The container has two integrated values, the beginning point and the end point, which simply identify the boundary of the
allocated region. The begin iterator points to the beginning point, while the end iterator points to a location which is one byte after the end point.
Before writing to or reading from any location, the location has to be checked to make sure it is between the beginning point and the end point.
Locations in the container are represented by iterators (objects of type ClxCircularDataIterator). iterators ARE NOT simply the index of the location
in the container buffer, since the container is circular. An iterator is only valid (points to a valid location) if it is smaller than (and NOT equal to)
the end iterator. Use isValid() to make sure an iterator is smaller than end iterator. Also, you can
use isBigger() or isSmaller() methods to compare an iterator with the end iterator or other iterators. 
*/
class ClxCircularDataContainer
{
protected:
    u1* const      baseAddr;
    u4             beginIndex;
    u4             endIndex;
    const u4       size;
    const boolean  bufferOwned;

public:
    ClxCircularDataContainer(u4 bufSize)
    : 
    baseAddr((u1*)clxAppAlloc (bufSize)),
    beginIndex (0),
    endIndex(0), 
    size(bufSize),
    bufferOwned(TRUE)
    {
        BLACKBOX_IF((bufSize & (bufSize - 1)) != 0);
    }

    ClxCircularDataContainer(u1* buffer, u4 bufSize)
    : 
    baseAddr (buffer), 
    beginIndex (0), 
    endIndex(0), 
    size(bufSize),
    bufferOwned(FALSE)
    {
        BLACKBOX_IF((bufSize & (bufSize - 1)) != 0);
    }

    ~ClxCircularDataContainer()
    {
        if ((bufferOwned) && (baseAddr))
        {
            clxPoolsetFree(baseAddr);
        }
    }
 
    /**
    Allocates a region in the data container. The returned buffer is guaranteed to be contiguous in the memory. This function
    does NOT move the end iterator. The caller has to call updateLength() method afterwards to inform the container of the amount
    of data written in the container. If updateLength() is not called afterwards, the new written data will be considered invalid,
    and a further call of this function will overwrite the written data.
    \param[ in ] length As input, it is the length of the returned value as wished by the caller. On output, it is
    the actual length of the buffer allocated and returned. The returned value of length could be smaller than the original
    value if:
    - there is no contiguous buffer of size \p length in the container.
    - Allocating a buffer of size \p length in the container would exceed the maximum size of the container.
    \return A pointer to a buffer of size /p length, allocated in the container which is guaranteed to be contiguous
    in the memory. It will be NULL if the container is already completely full (length will be set to zero).
    */
    u1* allocate (u4& length)
    {
        u4 currentLength = getCurrentLength();
        beginIndex &= Clx_CircularDataContainer_BuffersSizeMask;
        endIndex &= Clx_CircularDataContainer_BuffersSizeMask;
        if (currentLength == Clx_CircularDataContainer_BuffersSize)
        {
            length = 0;
            return 0;
        }
        else if (length + currentLength > Clx_CircularDataContainer_BuffersSize)
        {
            length = Clx_CircularDataContainer_BuffersSize - currentLength;
        }

        if (endIndex >= beginIndex)
        {
            length = (size - endIndex < length) ? (size - endIndex) : length;     
            if((length + currentLength > Clx_CircularDataContainer_BuffersSize) || (length == 0))
            {
                return 0;
            }
        }
        else
        {
            length = (Clx_CircularDataContainer_BuffersSize - currentLength < length) ? (Clx_CircularDataContainer_BuffersSize - currentLength) : length; 
            if(length == 0)
            {
                return 0;
            }
        }
        return (baseAddr + endIndex);
    }

    /**
    Expands the allocated region of the container by moving the end iterator forward by \p lengthOfNewDataAdded bytes.
    This function must only be called after allocate() has been called, to inform the container of the amount of new data
    written in the container. Data written in the buffer returned by allocate() will not be considered valid until this function
    is called to inform the container of the amount of data written.
    */
    u4 updateLength (u4 lengthOfNewDataAdded)
    {
        if(getCurrentLength() + lengthOfNewDataAdded > Clx_CircularDataContainer_BuffersSize)
        {
            return 0;
        }
        endIndex = (endIndex + lengthOfNewDataAdded) & Clx_CircularDataContainer_BuffersSize;
        return lengthOfNewDataAdded;
    }

    /**
    Releases some parts or the entire allocated region in the container by moving the begin iterator forward to a given
    location. If the given location (newBeginIterator) is bigger than the end iterator, then both the begin iterator and the
    end iterator will be moved to the new location, resulting in a completely empty container.
    */
    void release (ClxCircularDataIterator newBeginIterator)
    {
        if (((newBeginIterator - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask) < 
            ((endIndex - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask))
        {
            beginIndex = newBeginIterator;
        }
        else
        {
            beginIndex = endIndex = newBeginIterator;
        }
    }

    boolean copyTo(ClxCircularDataIterator iter, u1* output, u4 length)
    {
        iter &= Clx_CircularDataContainer_BuffersSizeMask;

        if ((isValid(iter)) && (distance(endIndex, iter) >= length))
        {
            if ((iter + length) > size)
            {
                u4 lenToCopy = size - iter;

                CLX_ASSERT(lenToCopy < length);
                memcpy(output, baseAddr + iter, lenToCopy);
                memcpy(output + lenToCopy, baseAddr, (length - lenToCopy));
            }
            else
            {
                memcpy(output, baseAddr + iter, length);
            }

            return TRUE;
        }

        return FALSE;
    }

public:
    /**
    Returns an iterator to the beginning point of the data container. Returned iterator is valid
    if it is smaller than (and NOT equal to) the end iterator. The begin iterator can never be bigger than
    the end iterator, but it can be equal to the end iterator (when the container is completely empty). 
    */
    ClxCircularDataIterator begin() const
    {
        return beginIndex;
    }

    /**
    Returns an iterator to the location which is one byte after the end point of the data container.
    The returned iterator does not point to a valid location itself. But, it can be used to check the validity of
    other iterators. Only iterators which are smaller than end iterator point to a valid iterator. Iterators do not need to be checked against the begin iterator as all iterators
    are automatically bigger than the begin iterator (since the comparison is carried out with the begin iterator as the base).
    */
    ClxCircularDataIterator end() const
    {
        return endIndex;
    }

    /**
    Gets the length of the currently allocated region of the container. The allocated region of the container
    is the region between the beginning point and the end point, and is the only valid region of the data container
    to read from and write to.
    */
    u4 getCurrentLength() const
    {
        return ((endIndex - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask);
    }

    /**
    Gets the maximum length of the container.
    */
    u4 getMaximumLength() const
    {
        return Clx_CircularDataContainer_BuffersSize;
    }

    /**
    Specifies if the given iterator is valid (is pointing to a valid location in the container).
    The return value is the same as the return value of the function calls isSmaller(Iter, end()), and isBigger(end(), Iter).
    */
    boolean isValid(ClxCircularDataIterator Iter) const
    {
        return (((endIndex - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask) > 
                ((Iter - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask));
    }

    /**
    Gets a reference to the location in the data container to which \p Iter points. The returned reference
    can be read or written.
    */
    u1& operator[] (ClxCircularDataIterator Iter)
    {
        return baseAddr[Iter & Clx_CircularDataContainer_BuffersSizeMask];
    }

    /**
    Gets the value stored in the location in the data container to which \p Iter points.
    */
    u1 operator[] (ClxCircularDataIterator Iter) const
    {
        return baseAddr[Iter & Clx_CircularDataContainer_BuffersSizeMask];
    }

    /**
    Compares the location of Iter1 and Iter2, based on the location of the beginning point.
    Returns TRUE if Iter1 is bigger than Iter2 (if Iter1 is more far away from the beginning point than Iter2 is).
    */
    boolean isBigger (ClxCircularDataIterator Iter1, ClxCircularDataIterator Iter2) const
    {
        return ((Iter1 - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask) > ((Iter2 - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask);
    }

    /**
    Compares the location of Iter1 and Iter2, based on the location of the beginning point.
    Returns TRUE if Iter1 is smaller than Iter2 (if Iter1 is closer to the beginning point than Iter2 is).
    */
    boolean isSmaller (ClxCircularDataIterator Iter1, ClxCircularDataIterator Iter2) const
    {
        return ((Iter1 - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask) < ((Iter2 - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask);
    }

    /**
    Compares the location of Iter1 and Iter2, based on the location of the beginning point.
    Returns TRUE if Iter1 is equal to Iter2 (if Iter1 points to the same location as Iter2 does).
    */
    boolean isEqual (ClxCircularDataIterator Iter1, ClxCircularDataIterator Iter2) const
    {
        return ((Iter1 - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask) == ((Iter2 - beginIndex) & Clx_CircularDataContainer_BuffersSizeMask);
    }

    /**
    Gets the circular distance of Iter1 from Iter2 (equal to Iter2 - Iter1 in circular math). In order to have the shortest
    distance between Iter1 and Iter2, Iter2 must be bigger than or equal to Iter1 (either isSmaller (Iter1, Iter2) or isEqual (Iter1, Iter2) must return TRUE). 
    If Iter1 is bigger than Iter2 (isBigger (Iter1, Iter2) returns TRUE), the return value of this function will
    be the longest distance between the iterators (remember that on a circle, two points have a shorter and a longer distance).
    */
    u4 distance (ClxCircularDataIterator Iter1, ClxCircularDataIterator Iter2) const
    {
        return ((Iter2 - Iter1) & Clx_CircularDataContainer_BuffersSizeMask);        
    }
};


#endif // #ifdef __cplusplus

#endif // ClxCircularDataContainer_h



