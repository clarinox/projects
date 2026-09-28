#ifndef ClxStack_h
#define ClxStack_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxExpandanleDataStack.h
* Description         Declares a simple size-expandable stack structure class
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

class ClxExpandanleDataStackBrowser;

/**
ClxStack is a simple stack structure which is size-expandable. The stack is created with an initial size. 
If, when pushing data into the stack, the stack runs out of space, new buffers (of the same size as initial buffer) 
will be allocated and attached at the end of the current buffer. During stack unwinding process 
(When popping data out of the stack), the extra buffers will be automatically deleted. 
The initial buffer will never be deleted during the unwinding process.
The whole process is performed seamlessly, without the user knowing anything about it.

All buffers will be allocated in the heap memory.
*/
class CD_API ClxExpandanleDataStack
{
private:
    friend class ClxExpandanleDataStackBrowser;

private:
    void*        current;
    void*        index;
    u4           lenLeft;
    u4           bufSize;
    boolean      align;

public:
/**
Creates and initializes a stack structure, with an initial size.

\param[ in ] stackBuffersSize the initial size of the stack in the heap memory. 
This is the minimum amount of memory space occupied by the stack.
When necessary, new buffers of the same size will be allocated and attached to the end of the stack.
\param[ in ] alignBuffers If TRUE, the stack 4-byte aligns data into the stack. 
This will guarantee that pointers returned by pop function will be 4-byte aligned 
(as long as the data is popped in the same order as they have been pushed into the stack). 
If FALSE, the stack will store the data in the stack as they are. 
In this case, pointers returned by pop function may not be 4-byte aligned.

\remarks
The stack memory-aligns the data in the stack by changing the size of data 
(attaching unused bytes at the end of data) so the size of data will be divisible by 4. 
This will guarantee that the address of each piece of data, which has been pushed in the stack,
will be 4-byte aligned. This means that ClxStack may attach 1 to 3 bytes to the end of each piece of data. 
This will be negligible if the typical size of data pushed into the stack is much more than 3 bytes 
(e.g. 10 bytes or more). Otherwise, memory aligning will result in a substantial waste of memory space.
*/
    ClxExpandanleDataStack (u4 stackBuffersSize, boolean alignBuffers = TRUE);

/**
pushes a piece of data into the stack. If not enough space is available in the stack, 
a new buffer will allocated, and attached to the end of the stack.

\param[ in ] buf A pointer to data which is to be pushed into the stack. 
The content of \p buf will be copied in the stack. Therefore, the caller takes back the ownership
of \p buf as soon as the function returns.
\param[ in ] len The length of data (stored in \p buf) to be pushed into the stack. 
\p len MUST NOT be larger than \p stackBuffersSize parameter of the constructor. 
\p len must typically be considerably less than \p stackBuffersSize in order to ensure 
reasonable use of memory space.
*/
    void  push (void* buf, u4 len);

/**
pops the last-pushed item out of the stack. All items must be popped out of the stack in the 
very same order as they were pushed. Failure to obey this rule will result in
ALL DATA IN THE STACK BECOMING CORRUPTED AND INACCESSIBLE. 

\param[ in ] len The length of the last-pushed item which is to be popped out of the stack. 
This parameter must be exactly the same as the length of data pushed into the stack
by calling push function.
\return A pointer to the popped data. If \p alignBuffers parameter of the constructor has been set to TRUE, 
this pointer will be guaranteed to be 4-byte memory aligned (as long as the "pop in the same order as push" 
rule has been complied with. If \p alignBuffers parameter of the constructor has been set to FALSE, 
this pointer may not be aligned. Therefore, the caller has to copy the content of the returned pointer to 
a new aligned buffer, by calling \b clxMemCpy function.

\remarks
IMPORTANT NOTE : note that pop does not automatically copy the popped data from the stack buffer 
into a caller-provided buffer. Rather, it returns a pointer to the data in the stack buffer. 
Since the data has been already popped out of the stack, the space it has occupied in the stack 
can be reused. Therefore, if new data is pushed into the stack, it will be copied over the last-popped data. 
Even a next pop function call to pop the next item might result in the current buffer getting deleted, 
and the pointer returned by the last pop function call becoming expired. In order to avoid any problem, 
the caller may copy the content of returned buffer to a new buffer. 
If more than one thread is using the stack at the same time, the user has to use a mutex to 
synchronize the access of multiple threads to the stack.

Automatic memory alignment is only necessary when the user wishes to directly use the returned buffer. 
In this case, the user must be careful not to push new items into the stack, or pop next items out of 
the stack, before they are done with the currently popped item. Alternatively, the user may use an instance 
of the class ClxStackBrowser which enables the user to get access to pushed items in the stack without 
having to pop them out of the stack.

This function may throw an exception of type ClxStack::error when no item of size \p len can be popped
out of the stack. This only happens when the "pop in the same order as push" rule has been violated.
*/
    void* pop (u4 len);

/**
An exception class which may be throw by pop function. Refer to pop function for more information.
*/
    class error {};

/**
Deletes all the buffers created. ALL DATA WILL BE LOST.
*/
    ~ClxExpandanleDataStack();
};

/**
ClxStackBrowser is a tool which can be attached to a instance of the class \b ClxStack, and enable the user to
browse the contents of the stack, without causing the stack to unwind (without popping data out of the stack).
This class browses items in the stack from the end (last pushed item) towards the beginning (first pushed item).

IMPORTANT : using this class could be dangerous if its use is not synchronized by the original ClxStack class. 
For instance, if a thread tries to pop one or more items out of the stack, and another thread tries to 
browse the items in the stack at the same time, this may result in severe difficulties. 
The user must be very careful when using ClxStack and ClxStackBrowser at the same time. 
*/
class ClxExpandanleDataStackBrowser
{
private:
    ClxExpandanleDataStack* stack;
    void*                    currentBuffer;
    void*                    browseIndex;

public:
/**
Initializes an instance of this class, by attaching it to a ClxStack object.

\param[ in ] stackToBrowse A pointer to a ClxStack object which is to be browsed by this class.
*/
    ClxExpandanleDataStackBrowser(ClxExpandanleDataStack* stackToBrowse) : stack (stackToBrowse), currentBuffer (NULL), browseIndex (0) {}

/**
Prepares the class for browsing, by adjusting the internal pointers to point to the last item in the stack. 
The user must call this function every time They need to restart browsing the stack. This function must be 
called at least once before starting browsing the stack.
*/
    void  start();

/**
Returns a pointer to the next item in the stack. If the function has been called first, it returns the first item 
(the last-pushed item) in the stack. This function moves from the last-pushed item, towards the first-pushed item. 

\remarks
This function acts exactly like ClxStack::pop, without popping the items out of the stack. The return value will 
be NULL, when the class reaches the beginning of the stack.
*/
    void* next(u4 len);

/**
Returns a pointer to the previous item in the stack.
This function moves towards the last-pushed item. 

\remarks
This function acts exactly like ClxStack::pop (in reverse order), without popping the items out of the stack. 
The return value will be NULL, when the class reaches the end of the stack.
*/
    void* prev(u4 len);
};


#endif // ClxStack_h

