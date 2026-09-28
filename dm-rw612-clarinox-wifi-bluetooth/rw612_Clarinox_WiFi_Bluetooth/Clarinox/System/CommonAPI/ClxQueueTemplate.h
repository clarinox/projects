#ifndef ClxQueueTemplate_h
#define ClxQueueTemplate_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxQueueTemplate.h
* Description         ClxQueueTemplate header file
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#ifdef __cplusplus

/**
Generic template for a container object which is able to queue objects as a circular doubly-linked list.

The queued objects will be of type QueueableBase which could be either a C++ class or C structure. QueueableBase must at least have
the following two members:

struct (or class) QueueableBase
{
    QueueableBase* prev_;
    QueueableBase* next_;

    // Optionally other members
};

Since this is a circular linked list, both prev_ and next_ SHALL initially be set to a pointer to their parent object (of type QueueableBase).

The actual objects which are queued into the linked list could be directly of type QueueableBase (in case QueueableBase has more members than just prev_ and next_),
a class deriving from QueueableBase (in C++ code only), a structure or class which has a member of type QueueableBase, or any other approach, as long as the following
can be met:

- It should be possible to extract a pointer to the actual queued object from the pointer to its corresponding QueueableBase object. This is due to the fact, only a pointer
to QueueableBase object is stored in the container and not to its corresponding actual parent object. 
*/
template<typename QueueableBase>
class ClxQueueTemplate : public QueueableBase
{
public:
    class Iterator
    {
    private:
        QueueableBase* current_;

    public:
        Iterator(const Iterator& c)
        :
        current_(c.current_)
        {}

    public:
        Iterator(QueueableBase& current)
        :
        current_(&current)
        {}

        QueueableBase& operator* ()
        {
            return *current_;
        }

        const QueueableBase& operator* () const
        {
            return *current_;
        }

        Iterator& operator++ () /* Prefix */
        {
            current_ = current_->next_;

            return *this;
        }

        Iterator operator++ (int) /* Postfix */
        {
            Iterator ret(*this);
            current_ = current_->next_;

            return ret;
        }

        Iterator& operator-- () /* Prefix */
        {
            current_ = current_->prev_;

            return *this;
        }

        Iterator operator-- (int) /* Postfix */
        {
            Iterator ret(*this);
            current_ = current_->prev_;

            return ret;
        }

        boolean operator== (const Iterator& c) const
        {
            return (current_ == c.current_) ? TRUE : FALSE;
        }

        boolean operator!= (const Iterator& c) const
        {
            return (current_ == c.current_) ? FALSE : TRUE;
        }
    };

private:
    /**
    A queue cannot be copied via its copy constructor.
    */
    ClxQueueTemplate(const ClxQueueTemplate& c) {}

protected:
    ClxQueueTemplate() : QueueableBase()
    {
        QueueableBase::prev_ = this;
        QueueableBase::next_ = this;    
    }

    virtual ~ClxQueueTemplate()
    {
        QueueableBase::next_->prev_ = QueueableBase::prev_;
        QueueableBase::prev_->next_ = QueueableBase::next_;
        QueueableBase::prev_ = this;
        QueueableBase::next_ = this;    
    }

public:
    /**
    Return an iterator to the first element in the queue. If the queue is not empty, the iterator will be valid.
    Otherwise, it will be nullIterator iterator (as returned by nullIterator() method).
    */
    Iterator first()
    {
        return *QueueableBase::next_;   
    }


    /**
    Return an iterator to the last element in the queue. If the queue is not empty, the iterator will be valid.
    Otherwise, it will be nullIterator iterator (as returned by nullIterator() method).
    */
    Iterator last()
    {
        return *QueueableBase::prev_;   
    }

    /**
    Returns an invalid iterator. This iterator shall never be de-referenced.

    In order to iterate the queue in the forward direction:

    Iterator it = queue.first();
    for (; it != queue.nullIterator(); ++it)
    {}

    In order to iterate the queue in the reverse direction:

    Iterator it = queue.last();
    for (;it != queue.nullIterator(); --it)
    {}
    */
    Iterator nullIterator()
    {
        return *static_cast<QueueableBase*>(this);   
    }

protected:
    /**
    queues a new item to this container by appending it AFTER a given existing item in the container.
    If the container is used as a FIFO (Item1 first, ItemN last), the existing item will be extracted first.


    Example:
    This container before the operation:
        
      |--> ItemN --> RootItem (This container) --> Item1 --> Item2 ---|
      |-------------------------- ... --- Item3 <---------------------|

    After calling appendAfter(NewItem, Item2) :

      |--> ItemN --> RootItem (This container) --> Item1 --> Item2 --> NewItem ---|
      |-------------------------- ... --- Item3 <---------------------------------|


    \param[ in ] newItem The new item to be queued into the container. This item cannot have already
    been queued in the same or different container.

    \param[ in ] prevItem The existing item, after which the new item will be added. This item must already have been
    queued in this container object.
    */
    void appendAfter( QueueableBase* newItem, QueueableBase* prevItem )
    {
        if (newItem->prev_ == newItem)
        {
            CLX_ASSERT( newItem->next_ == newItem );
            newItem->prev_ = prevItem;
            newItem->next_ = prevItem->next_;
            prevItem->next_->prev_ = newItem;
            prevItem->next_ = newItem;
        }
    }

    /**
    queues a new item to this container by appending it BEFORE a given existing item in the container.
    If the container is used as a FIFO (Item1 first, ItemN last), the new item will be extracted first.

    Example:
    This container before the operation:

        
      |--> ItemN --> RootItem (This container) --> Item1 --> Item2 ---|
      |-------------------------- ... --- Item3 <---------------------|

    After calling appendBefore(NewItem, Item2) :

      |--> ItemN --> RootItem (This container) --> Item1 --> NewItem -> Item2 -----|
      |-------------------------- ... --- Item3 <----------------------------------|


    \param[ in ] newItem The new item to be queued into the container. This item cannot have already
    been queued in the same or different container.

    \param[ in ] nextItem The existing item, before which the new item will be added. This item must already have been
    queued in this container object.
    */
    void appendBefore( QueueableBase* newItem, QueueableBase* nextItem )
    {
        if (newItem->prev_ == newItem)
        {
            CLX_ASSERT( newItem->next_ == newItem );
            newItem->next_ = nextItem;
            newItem->prev_ = nextItem->prev_;
            nextItem->prev_->next_ = newItem;
            nextItem->prev_ = newItem;
        }
    }

    /**
    adds zero or more new items to this container by appending all of them AFTER a given existing
    item in the container. The new items are transferred from another container object to this object. The order of the new items
    will be reserved. 
    After the appending operation, the passed queue will be empty (since all its items have been transferred to this container 
    and an item cannot be queued into two containers at the same time).


    Example:
    This containers before the operation:
        
      |--> Item1N --> RootItem10 (queue1) --> Item11 --> Item12 -------|
      |-------------------------- ... --- Item13 <---------------------|


      |--> Item2M --> RootItem20 (queue2) --> Item21 --> Item22 -------|
      |-------------------------- ... --- Item23 <---------------------|


    After calling queue1.appendAfter(queue2, Item12) :


      |--> Item1N --> RootItem10 (queue1) --> Item11 --> Item12 --> Item21 --> Item22 ---|
      |----------------- ... --- Item13 <-- Item2M <---- .... --- Item23 <---------------|


      |----> RootItem20 (queue2) ---|
      |-----------------------------|


    \param[ in ] queue The queue, all items of which will be transferred to this container. This queue will be empty
    when this function returns. If this queue is already empty, calling of this function will have no effect.

    \param[ in ] prevItem The existing item, after which the new items will be added. This item must already have been
    queued in this container object.
    */
    void appendQueueAfter( ClxQueueTemplate& queue, QueueableBase* prevItem )
    {
        if (!queue.isEmpty())
        {
            queue.next_->prev_ = prevItem;
            queue.prev_->next_ = prevItem->next_;
            prevItem->next_->prev_ = queue.prev_;
            prevItem->next_ = queue.next_;

            /* We clear queue so it will not have any items any more: */
            queue.prev_ = &queue;
            queue.next_ = &queue;        
        }
    }

    /**
    adds zero or more new items to this container by appending all of them BEFORE a given existing
    item in the container. The new items are transferred from another container object to this object. The order of the new items
    will be reserved. 
    After the appending operation, the passed queue will be empty (since all its items have been transferred to this container 
    and an item cannot be queued into two containers at the same time).


    Example:
    This containers before the operation:
        
      |--> Item1N --> RootItem10 (queue1) --> Item11 --> Item12 -------|
      |-------------------------- ... --- Item13 <---------------------|


      |--> Item2M --> RootItem20 (queue2) --> Item21 --> Item22 -------|
      |-------------------------- ... --- Item23 <---------------------|


    After calling queue1.appendBefore(queue2, Item12) :


      |--> Item1N --> RootItem10 (queue1) --> Item11 --> Item21 --> Item22 ------------------|
      |---------------- .... --- Item13 <-- Item12 <-- Item2M <-- .... --- Item23 <----------|


      |----> RootItem20 (queue2) ---|
      |-----------------------------|

    \param[ in ] queue The queue, all items of which will be transferred to this container. This queue will be empty
    when this function returns. If this queue is already empty, calling of this function will have no effect.

    \param[ in ] nextItem The existing item, before which the new items will be added. This item must already have been
    queued in this container object.
    */
    void appendQueueBefore( ClxQueueTemplate& queue, QueueableBase* nextItem )
    {
        if (!queue.isEmpty())
        {
            queue.prev_->next_ = nextItem;
            queue.next_->prev_ = nextItem->prev_;
            nextItem->prev_->next_ = queue.next_;
            nextItem->prev_ = queue.prev_;

            /* We clear queue so it will not have any items any more: */
            queue.prev_ = &queue;
            queue.next_ = &queue;
        }
    }

    /*
    detach() does not check whether "item" has been queued into
    this queue. The user must assure that.
    */
    void detach( QueueableBase* item )
    {
        item->next_->prev_ = item->prev_;
        item->prev_->next_ = item->next_;
        item->prev_ = item;
        item->next_ = item;
    }

    /**
    Checks if a given item is a valid item. A valid item is an item which is not this container itself.
    The function is used when traversing the container object. The traversal can be in forward direction (starting from ClxQueueTemplate.first())
    or in backward direction (starting from ClxQueueTemplate.last()). Since the container is a circular linked list, the traversal will never result
    in a NULL pointer. But, the traversal will eventually result in getting back to the root of the linked list, which is this container itself (as
    an object deriving from QueueableBase). This function can be called to check if the traversal attempt has ended.

    Example:
        ClxQueueTemplate<SomeType> queue;

        SomeType* current = queue.firstItem();

        while(queue.checkValidity(current))
        {
            // Process current
            current = current->next_;
        }
    */
    boolean checkValidity(const QueueableBase* item) const
    {
        return (item != this);
    }

public:
    /**
    Returns the first item in the container. If the container is empty, the return value will be a pointer to this container, itself.
    */
    QueueableBase* firstItem() const
    {
        return QueueableBase::next_;
    }

    /**
    Returns the last item in the container. If the container is empty, the return value will be a pointer to this container, itself.
    */
    QueueableBase* lastItem() const
    {
        return QueueableBase::prev_;
    }

    /**
    Returns TRUE if this container is currently empty (there is item queued inside the this container at this moment),
    or FALSE otherwise.
    */
    boolean isEmpty() const
    {
        if (QueueableBase::next_ == this)
        {
            CLX_ASSERT (QueueableBase::prev_ == this);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
};


#if !defined(CLARINOX_DEBUGGER)

/**
A C++-style queue for objects which are pure C structures.
Refer to ClxCQueueable.h for more information about the structure of C queueable objects (objects which can be queued in a queue of type ClxCQueue).
*/
template<typename CStruct>
class ClxCQueueTemplate : public ClxQueueTemplate<ClxCQueueable>
{
public:
    class Iterator
    {
    private:
        ClxCQueueTemplate<CStruct>&   queue_;
        CStruct*                      current_;

    public:
        Iterator(ClxCQueueTemplate<CStruct>& queue)
        :
        queue_(queue),
        current_(reinterpret_cast<CStruct*>(queue.firstItem()))
        {}

        CStruct* operator* ()
        {
            if (queue_.isValid(current_))
            {
                return current_;
            }
            else
            {
                return NULL;
            }
        }

        Iterator(const Iterator& c)
        :
        queue_(c.queue_),
        current_(c.current_)
        {}

        Iterator& operator++ ()
        {
            current_ = ClxCQueueTemplate<CStruct>::next(*current_);
	        return *this;
        }

        Iterator& operator-- ()
        {
            current_ = ClxCQueueTemplate<CStruct>::prev(*current_);
	        return *this;
        }

        Iterator operator++ (int)
        {
            Iterator ret(*this);
            current_ = ClxCQueueTemplate<CStruct>::next(*current_);
	        return ret;
        }

        Iterator operator-- (int)
        {
            Iterator ret(*this);
            current_ = ClxCQueueTemplate<CStruct>::prev(*current_);
	        return ret;
        }
    };

    class ConstIterator
    {
    private:
        const ClxCQueueTemplate<CStruct>&   queue_;
        const CStruct*                      current_;

    public:
        ConstIterator(const ClxCQueueTemplate<CStruct>& queue)
        :
        queue_(queue),
        current_(reinterpret_cast<CStruct*>(queue.firstItem()))
        {}

        const CStruct* operator* () const
        {
            if (queue_.isValid(current_))
            {
                return current_;
            }
            else
            {
                return NULL;
            }
        }

        ConstIterator(const ConstIterator& c)
        :
        queue_(c.queue_),
        current_(c.current_)
        {}

        ConstIterator& operator++ ()
        {
            current_ = ClxCQueueTemplate<CStruct>::next(*current_);
	        return *this;
        }

        ConstIterator& operator-- ()
        {
            current_ = ClxCQueueTemplate<CStruct>::prev(*current_);
	        return *this;
        }

        ConstIterator operator++ (int)
        {
            ConstIterator ret(*this);
            current_ = ClxCQueueTemplate<CStruct>::next(*current_);
	        return ret;
        }

        ConstIterator operator-- (int)
        {
            ConstIterator ret(*this);
            current_ = ClxCQueueTemplate<CStruct>::prev(*current_);
	        return ret;
        }
    };

public:
    static void initItem(CStruct& item)
    {
        item.queueable.prev_ = &item.queueable;
        item.queueable.next_ = &item.queueable;
    }

    static boolean isItemQueued(CStruct& item)
    {
        return (item.queueable.next_ != &item.queueable);
    }

    static CStruct* next(CStruct& item)
    {
        return reinterpret_cast<CStruct*>(item.queueable.next_);
    }

    static CStruct* prev(CStruct& item)
    {
        return reinterpret_cast<CStruct*>(item.queueable.prev_);
    }

    void pushBack(CStruct* item)
    {
        appendBefore (&item->queueable, this);
    }

    void pushFront(CStruct* item)
    {
        appendAfter (&item->queueable, this);
    }

    CStruct* popFromFront()
    {
        if (isEmpty()) 
        {
            return NULL;
        }

        ClxCQueueable* ret = next_;
        detach(ret);
        return reinterpret_cast<CStruct*>(ret);
    }

    CStruct* popFromBack()
    {
        if (isEmpty()) 
        {
            return NULL;
        }

        ClxCQueueable* ret = prev_;
        detach(ret);
        return reinterpret_cast<CStruct*>(ret);
    }

    void detachItem(CStruct* item)
    {
        detach(&item->queueable);
    }

    void appendQueueBack(ClxCQueueTemplate& queue)
    {
        ClxQueueTemplate<ClxCQueueable>::appendQueueBefore(queue, this);
    }

    void appendQueueFront(ClxCQueueTemplate& queue)
    {
        ClxQueueTemplate<ClxCQueueable>::appendQueueAfter(queue, this);
    }

    boolean isValid(CStruct* item) const
    {
        return checkValidity(&item->queueable);
    }
};


#endif     /* #if !defined(CLARINOX_DEBUGGER) */

#endif     // __cplusplus



#if !defined(CLARINOX_DEBUGGER)

#ifdef __cplusplus
extern "C" {
#endif


/* ClxCQueue is the Pure-C Version of ClxCQueueTemplate: */

typedef struct ClxCQueueStruct
{
    struct ClxCQueueable queueable;
} ClxCQueue;

typedef struct ClxCQueueIteratorStruct
{
    const ClxCQueue*       parent;
    struct ClxCQueueable*  current;
} ClxCQueueIterator;


extern void clxCQueueInit(ClxCQueue* arg);
extern void clxCQueueInitItem(struct ClxCQueueable* obj);
extern void clxCQueuePushFront(ClxCQueue* queue, struct ClxCQueueable* obj);
extern void clxCQueuePushBack(ClxCQueue* queue, struct ClxCQueueable* obj);
extern struct ClxCQueueable* clxCQueuePopBack(ClxCQueue* queue);
extern struct ClxCQueueable* clxCQueuePopFront(ClxCQueue* queue);
extern void clxCQueueDetachItem(ClxCQueue* queue, struct ClxCQueueable* obj);
extern boolean clxCQueueIsEmpty(const ClxCQueue* queue);

extern void clxCQueueFront(const ClxCQueue* queue, ClxCQueueIterator* out);
extern void clxCQueueBack(const ClxCQueue* queue, ClxCQueueIterator* out);

extern boolean clxCQueueIteratorIsValid(const ClxCQueueIterator* iter);

extern void clxCQueueIteratorNext(ClxCQueueIterator* iter);
extern void clxCQueueIteratorPrev(ClxCQueueIterator* iter);

#ifdef __cplusplus
}
#endif

#endif     /* #if !defined(CLARINOX_DEBUGGER) */

#endif    // ClxQueueTemplate_h

/******************************************************************************/ 
/* 1. MISRA C 2004 RULE VIOLATION:                                            */ 
/* Message       : Sections of code should not be “commented out”.            */ 
/* Rule          : MISRA-C:2004 Rule 2.4                                      */ 
/* Justification : Inside comment section, example of code is given for       */
/*				   clarity.											          */
/*                 Only used for example code to clarify the use.             */
/*                 As we generate API documentation from header files         */
/*				   (using Doxygen), this is necessary.                        */
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
/* Message       : The character sequences Slash'/' Star'*' and Slash'/'      */
/*				   Slash'/'  shall not be used within a comment. 	  		  */
/* Rule          : MISRA-C:2012 Rule 3.1                                      */ 
/* Justification : Only used for example code to clarify the use. As we		  */	
/*				   generate API documentation from header files (using 		  */
/*				   Doxygen), this is necessary.							  	  */
/******************************************************************************/
