#ifndef ClxCQueueable_h
#define ClxCQueueable_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxCQueueable.h
* Description         ClxCQueueable header file
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


/**
In some occasions in C++ code, it is desirable to queue a list of objects which have pure C structure type (e.g. structures defined in APIs are generally pure C structures). Since C++ inheritance
cannot be used to derive the C structure from a queueable base class, we need to simulate C++ inheritance in C code using membership.

A C structure which is a queueable type (e.g. an instance of which can be queued in a queue of type ClxCQueue) SHALL have the following structure:

struct SampleQueueableStruct
{
    struct ClxCQueueable queueable;
};

Where 'queueable' SHALL always be the very first member in its parent structure - the rest of the structure may be placed after 'queueable'. In other words, a C queueable type is a C structure with its very first member being of type
'struct ClxCQueueable' and having the name 'queueable' (neither the type nor the name of the first member may be different).

When an instance of a queueable structure is created, it SHALL be initialized before it can be queued in a queue of type ClxCQueue. In order to initialize the newly-created object,
use the static method ClxCQueue::initItem(). Example:

SampleQueueableStruct obj;

ClxCQueue<SampleQueueableStruct>::initItem(obj);

NOTE : Initialization of an object needs to be performed only once. Afterwards, the object can be freely queued into and de-queued out of same or different queues of type ClxCQueue.

IMPORTANT : If the contents of C queueable object is copied to a new queueable object of the same type, the new object still SHALL be initialized using ClxCQueue::initItem(). During the copy
procedure, the contents of the member 'queueable' of the current object SHALL NOT be copied to the member 'queueable' of the new object.
*/

struct ClxCQueueable
{
    struct ClxCQueueable* prev_;   /* USED INTERNALLY. NOT TO BE MODIFIED */
    struct ClxCQueueable* next_;   /* USED INTERNALLY. NOT TO BE MODIFIED */
};


#ifdef __cplusplus
}
#endif


#endif    // ClxCQueueable_h
