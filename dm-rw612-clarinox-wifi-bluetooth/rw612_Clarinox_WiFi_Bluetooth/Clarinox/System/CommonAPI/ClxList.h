#ifndef ClxList_h
#define ClxList_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxList.h
* Description         Declares list related classes, types and macros
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


template<class Type, class Allocator>
class ClxListIteratorBase;

/**
ClxListBase container class.
\tparam Type class of the objects to be contained.
\tparam u4 a datatype from the family of unsigned integers big enough
        to address every object in an array of object pointers.
*/
template<class Type, class Allocator>
class ClxListBase
{
public:
    Type**      objects_;
    u4          count_;
    u4          capacity_;
    boolean     owner_;

private:
    Type**      objectsBase_;
    u4          capacityRear_;
    Allocator   allocator_;

public:
    ClxListBase(){ initialize( TRUE  ); }
    /**
    \param[ in ] owner ownership flag.
                 - 1 to make the list owns the objects.
                     So that when list is destructed all objects in the list are
                     also destructed.
                 - 0 otherwise.
    */
    ClxListBase( boolean owner ){ initialize( owner ); }
    virtual ~ClxListBase(){ empty(); allocator_.free( ( void* ) objectsBase_ ); }
    /**
    Assign list's preferred capacity.
    \param[ in ] idealCapacity preferred capacity.
    */
    boolean capacity( u4 idealCapacity );
    /**
    Append an object into the list.
    \param[ in ] type object to be appended.
    */
    void add( Type* type );
    /**
    \copydoc add(Type*)
    */
    void append( Type* type ){ add( type ); }
    /**
    Insert an object at a specific location.
    \param[ in ] obj object to be inserted.
    \param[ in ] index location desired.
    */
    void insert( Type* obj, u4 index );
    /**
    Prepend an object.
    \param[ in ] obj object to be prepended.
    */
    void prepend( Type* obj );

    /**
    Access a list item at a specific location.
    \param[ in ] index the location index of the item desired.
    \return Pointer to the object at the specified location.
    */
    Type* operator []( u4 index ){ return locateIndex( index ); }
    /**
    Acess the first member in the list.
    */
    Type* first(){ return locateIndex( 0 ); }
    /**
    Acess the second member in the list.
    */
    Type* second(){ return locateIndex( 1 ); }
    /**
    Access the second last member in the list.
    */
    Type* secondLast(){ return ( ( count_ >= 2 ) ? locateIndex( count_ - 2 ) : NULL); }
    /**
    Access the last member in the list.
    */
    Type* last(){ return ( ( count_ >= 1 ) ? locateIndex( count_ - 1 ) : NULL); }

    /**
    Detach the object at a specific location.
    \param[ in ] index location index.
    \return The detached object.
    */
    Type* detachIndex( u4 index );

    /**
    Delete the object at a specific location.
    \param[ in ] index location index.
    */
    void destroyIndex( u4 index ){ delete( detachIndex( index ) ); }

    /**
    Detach an object.
    \param[ in ] the object to be detached.
    \return the object detached.
    */
    Type* detachType( Type* type ){ return detachIndex( locateType( type ) ); }
    /**
    Delete an object.
    \param[ in ] the object to be deleted.
    */
    void destroyType( Type* type ){ delete( detachType( type ) ); }
    /**
    Detach the first object.
    \return the object detached.
    */
    Type* detachFirst(){ return detachIndex( 0 ); }
    ///Delete the first object.
    void destroyFirst(){ delete( detachFirst() ); }

    /**
    Detach the last object.
    \return the object detached.
    */
    Type* detachLast(){ return count_ ? detachIndex( count_ - 1 ) : NULL; }
    ///Delete the last object.
    void destroyLast(){ delete( detachLast() ); }

    /**
    Returns a boolean indicating the list status.
    \return 
    \retval TRUE if the list is empty
    \retval FALSE if the list has at least one element in it
    */
    boolean                 isEmpty                 ()                          { return ( count_ == 0 ); }
 
    /**
    Deletes all elements of the list and sets the count to 0.
    */
     void                    empty                   ();

    /**
    Returns a new ClxListIteratorBase object for the current list.
    \return ClxListIteratorBase object
    */
    ClxListIteratorBase<Type, Allocator> iterator  ();

protected:
    void                    initialize              ( boolean owner );
    void                    increaseCapacity        ();
    Type*                   locateIndex             ( u4 index )      { return ( index < count_ ) ? objects_[ index ] : NULL; }
    u4                      locateType              ( Type* );
};

/**
ClxListIteratorBase iterator class.
\tparam Type class of the objects to be contained.
\tparam u4 a datatype from the family of unsigned integers big enough
        to address every object in an array of object pointers.
Iterator class for ClxListBase<class Type, class u4> provides a mechanism 
to iterate the objects in a list.
*/
template<class Type, class Allocator>
class ClxListIteratorBase
{
public:
    ClxListBase<Type, Allocator>*       list_;
    u4                               current_;

public:
                            ClxListIteratorBase        ( ClxListBase<Type, Allocator>* list )     : list_( list ) { restart(); }
                            // constructor

    /**
    This function restarts iteration from the first object.
    */
    void                    restart                 ()                          { current_ = 0; }

    /**
    This function restarts iteration from the last object.
    */
    void                    restartBackward         ()                          { current_ = u4( list_->count_ - 1 ); }

    /**
    This function starts iteration from the given object.
    \param[ in ] index is the position of the object for iteration to start from.
    */
    void                    startFrom               ( u4 index )      { current_ = index; }

    /**
    This operator returns the current object
    \return Pointer to the current object.
    */
    Type*                   operator *              ();

    /**
    This operator returns the current object after pre-increment
    \return Pointer to the next object.
    */
    Type*                   operator ++             ();

    /**
    This operator returns the current object and points to the next object
    \return Pointer to the current object.
    */
    Type*                   operator ++             ( int );

    /**
    This operator returns the previous object and points to the that object
    \return Pointer to the previous object.
    */
    Type*                   operator --             ();
 
    /**
    This operator returns the current object and points to the previous object
    \return Pointer to the current object.
    */
    Type*                   operator --             ( int );
};

// _____________________________________________________________________________
//
// List Class Utility Macros
// _____________________________________________________________________________
//

/**
This macro is checking the IF_EQUAL condition to be used in LIST_FIND, LIST_DESTROY and LIST_DETACH macros.
*/
#define IF_EQUAL( v1, v2 )                      ( ( v1 ) == ( v2 ) )
/**
This macro is used for checking the IF_NOT_EQUAL condition to be used in LIST_FIND, LIST_DESTROY and LIST_DETACH macros.
*/
#define IF_NOT_EQUAL( v1, v2 )                  ( ( v1 ) != ( v2 ) )
/**
This macro is used for  the IF_LESS_THAN condition to be used in LIST_FIND, LIST_DESTROY and LIST_DETACH macros.
*/
#define IF_LESS_THAN( v1, v2 )                  ( ( v1 ) <  ( v2 ) )
/**
This macro is used for checking the IF_GREATER_THAN condition to be used in LIST_FIND, LIST_DESTROY and LIST_DETACH macros.
*/
#define IF_GREATER_THAN( v1, v2 )               ( ( v1 ) >  ( v2 ) )
/**
This macro is used for checking the IF_LESS_THAN_AND_EQUAL_TO condition to be used in LIST_FIND, LIST_DESTROY and LIST_DETACH macros.
*/
#define IF_LESS_THAN_AND_EQUAL_TO( v1, v2 )     ( ( v1 ) <= ( v2 ) )
/**
This macro is used for checking the IF_GREATER_THAN_AND_EQUAL_TO condition to be used in LIST_FIND, LIST_DESTROY and LIST_DETACH macros.
*/
#define IF_GREATER_THAN_AND_EQUAL_TO( v1, v2 )  ( ( v1 ) >= ( v2 ) )

/**
\cond 1
*/
#define LIST_FIND_INDEX( index, list, compareFunction, member, value )                        \
    {                                                                                         \
        for ( index = 0 ; index < ( list->count_ ) ; index++ )                                \
        {                                                                                     \
            if ( compareFunction( ( list->objects_[ index ]->member ), value ) )              \
            {                                                                                 \
                break;    /* found */                                                         \
            }                                                                                 \
        }                                                                                     \
    }                                                                                         \
    
/**
\endcond
*/

/**
Macro for searching an object_member_to_compare_against the_value_to_compare 
of all items in a list_of_objects to find a "CONDITION". The first item
found satisfying this condition from the list is returned in the object.
  LIST_FIND( object, list_of_objects, CONDITION, object_member_to_compare_against, the_value_to_compare );
*/
#define LIST_FIND( item, list, compareFunction, member, value )                               \
    {                                                                                         \
        u4 index;                                                                             \
        LIST_FIND_INDEX( index, list, compareFunction, member, value );                       \
                                                                                              \
        /* This is the only way to set subclass pointers to superclass ones */                \
        *( void** )&item = ( *list )[ index ];                                                \
    }                                                                                         \

/**
Macro for searching an object_member_to_compare_against the_value_to_compare 
of all items in a list_of_objects to find a "CONDITION". The first item
found satisfying this condition from the list is removed from the list and
the item is deleted.
  LIST_DESTROY( object, list_of_objects, CONDITION, object_member_to_compare_against, the_value_to_compare );
*/
#define LIST_DESTROY( result, list, compareFunction, member, value )                          \
    {                                                                                         \
        u4 index;                                                                             \
        LIST_FIND_INDEX( index, list, compareFunction, member, value );                       \
        boolean* returnValue = result;                                                        \
        if ( ( *list )[ index ] )                                                             \
        {                                                                                     \
            list->destroyIndex( index );                                                      \
            if ( returnValue )                                                                \
            {                                                                                 \
                *returnValue = TRUE;                                                          \
            }                                                                                 \
        }                                                                                     \
        else if ( returnValue )                                                               \
        {                                                                                     \
            *returnValue = FALSE;                                                             \
        }                                                                                     \
    }                                                                                         \

/**
Macro for searching an object_member_to_compare_against the_value_to_compare 
of all items in a list_of_objects to find a "CONDITION". The first item
found satisfying this condition from the list is removed from the list and
the item pointer is returned in the object.
  LIST_DETACH( object, list_of_objects, CONDITION, object_member_to_compare_against, the_value_to_compare );
*/
#define LIST_DETACH( item, list, compareFunction, member, value )                             \
    {                                                                                         \
        u4 index;                                                                             \
        LIST_FIND_INDEX( index, list, compareFunction, member, value );                       \
        if ( ( *list )[ index ] )                                                             \
        {                                                                                     \
            item = list->detachIndex( index );                                                \
        }                                                                                     \
        else                                                                                  \
        {                                                                                     \
            item = NULL;                                                                      \
        }                                                                                     \
    }

/**
Macro for iterating in a list_of_objects of class to execute the expression_to_perform
for each item of the list.
  LIST_PERFORM_ON_ALL_ITEMS( class, list_of_objects, expression_to_perform );
*/
#define LIST_PERFORM_ON_ALL_ITEMS( Type, list, function )                                     \
    {                                                                                         \
        ClxListIterator< Type > li( list );                                                   \
        Type* item = li++;                                                                    \
        while ( item != NULL )                                                                \
        {                                                                                     \
            function;																		  \
			item = li++;																	  \
        }                                                                                     \
    }                                                                                         \

/* Default List and ClxListIterator classes use ClarinoxSoftframe Pool Set for allocation of elements in the list */

template<class Type>
class ClxList : public ClxListBase<Type, ClxSoftframePoolsetAllocator>
{
public:
    ClxList()
    :
    ClxListBase<Type, ClxSoftframePoolsetAllocator>() 
    {}

    ClxList( boolean owner )
    :
    ClxListBase<Type, ClxSoftframePoolsetAllocator>( owner ) 
    {}

    ClxListIteratorBase<Type, ClxSoftframePoolsetAllocator>* iterator()
    { 
        return ( ClxListIteratorBase<Type, ClxSoftframePoolsetAllocator>* ) ClxListBase<Type, ClxSoftframePoolsetAllocator>::iterator(); 
    }
};

template<class Type>
class ClxListIterator : public ClxListIteratorBase<Type, ClxSoftframePoolsetAllocator>
{
public:
    ClxListIterator( ClxListBase<Type, ClxSoftframePoolsetAllocator>* list )
    :
    ClxListIteratorBase<Type, ClxSoftframePoolsetAllocator>( list ) 
    {}   
};

// reserved space for possible 'quick' prepend operations
#define PREPEND_RESERVE 1


template<class Type, class Allocator>
inline void ClxListBase<Type, Allocator>::initialize( boolean owner )
{
    owner_       = owner;
    capacity_    = count_   = 0;
    objectsBase_ = objects_ = NULL;
}

template<class Type, class Allocator>
inline void ClxListBase<Type, Allocator>::empty()
{
    if ( owner_ )
    {
#if 1 
        Type** object = objects_;
        Type** last = objects_ + count_;

        while ( object < last )
        {
            delete( ( Type* )( *object++ ) );
        }
#else   
        for (u4 i = 0; i < count_; i++)
        {
           delete( ( Type* )( objects_[i] ));        
        }
#endif
    }
    count_ = 0;
}

template<class Type, class Allocator>
inline void ClxListBase<Type, Allocator>::increaseCapacity()
{
    if ( capacity_ == 0 )
    {
        capacity_ = 7;                      // initial capacity
    }
    else
    {
        capacity_ += ( capacity_ >> 1 );    // 50% increase always
    }

    // allocate a larger array of object pointers
    Type** objects = ( Type** ) allocator_.alloc( (capacity_ * sizeof( Type* )) );
 
    // copy all the object pointers to the NEW buffer.
    memcpy( ( void* ) ( objects + PREPEND_RESERVE ), ( void* ) objects_, count_ * sizeof( Type* ) );

    // delete the old buffer
    allocator_.free( ( void* ) objectsBase_ );

    // start using the NEW one
    objectsBase_  = objects;
    objects_      = objects   + PREPEND_RESERVE;
    capacityRear_ = capacity_ - PREPEND_RESERVE;
}

template<class Type, class Allocator>
inline boolean ClxListBase<Type, Allocator>::capacity( u4 idealCapacity )
{
    if ( count_ <= idealCapacity )
    {
        capacity_ = idealCapacity - ( idealCapacity >> 1 ) + 1;    // GT's trick for less arithmetic intensive
        increaseCapacity();
        return TRUE;    // success
    }

    return FALSE;   // failed
}

template<class Type, class Allocator>
inline void ClxListBase<Type, Allocator>::add( Type* type )
{
    if ( count_ == capacity_ )
    // 100% capacity is being used, need some more
    {
        increaseCapacity();
    }
    else if ( count_ == capacityRear_ )
    // no space left at the back
    {
        // this list is an append (add) type.
        // therefore bring all of them forward
        // without providing PREPEND_RESERVE
        memmove( ( void* ) ( objectsBase_ /* + PREPEND_RESERVE*/ ), ( void* ) objects_, count_ * sizeof( Type* ) );
        objects_ = objectsBase_ /* + PREPEND_RESERVE */;
        capacityRear_ = capacity_ /* - PREPEND_RESERVE */;
    }
    
    // insert ( or append ) the NEW object
    // increment the population of the list by 1 
    objects_[ count_++ ] = type;
}

template<class Type, class Allocator>
inline void ClxListBase<Type, Allocator>::insert( Type* type, u4 index )
{

    if ( objectsBase_ == objects_ ) // also capacity_ == capacityRear_
    // no space at front (we have to do it the slower way)
    {
        if ( count_ == capacity_ )
        // 100% capacity is being used, need some more
        {
            increaseCapacity();
        }

        // make space for the newcomer shifting
        // the ones after the index
        if( ( index != count_ ) && ( count_ != 0 ) )
        {

            Type** mark = &( objects_[ index + 1 ] );
            Type** p    = &( objects_[ count_ ] );
            do
            {
                *p = *( p - 1 );
            } while ( ( p-- ) != mark );
        }
    }
    else
    // there is space at front (this should work much faster)
    {
        // bring enough of them forward to make a space for the NEW one
        memmove( ( void* ) ( objects_ - 1 ), ( void* ) objects_, index * sizeof( Type* ) );
        objects_--;
        capacityRear_++;
    }

    // insert the NEW object
    objects_[ index ] = type;

    // increment the population of the list by 1
    count_++;
}

template<class Type, class Allocator>
inline void ClxListBase<Type, Allocator>::prepend( Type* type )
{
    if ( objectsBase_ == objects_ ) // also capacity_ == capacityRear_
    // no space at front
    {
        if ( count_ == capacity_ )
        // 100% capacity is being used, need some more
        {
            increaseCapacity();
        }
        else if( count_ != 0 )
        // we have to do it the slower way
        {
            // make space for the newcomer shifting
            // the ones after the first one
            Type** mark = &( objects_[ 1 ] );
            Type** p    = &( objects_[ count_ ] );
            do
            {
                *p = *( p - 1 );
            } while ( ( p-- ) != mark );

            // insert the NEW object
            objects_[ 0 ] = type;

            // increment the population of the list by 1
            count_++;
            return;     // done
        }
    }

    objects_--;
    capacityRear_++;

    // insert the NEW object
    objects_[ 0 ] = type;

    // increment the population of the list by 1
    count_++;
}

template<class Type, class Allocator>
inline Type* ClxListBase<Type, Allocator>::detachIndex( u4 index )
{
    Type* type = NULL;
    if ( index < count_ )
    {
        type = objects_[ index ];

        // decrement population
        count_--;

        if ( index == 0 )
        {
            objects_++;
            capacityRear_--;
        }
        else
        {
            // shrink the objects array removing the
            // one pointed by the index
            memmove(
                &( objects_[ index ] ),
                &( objects_[ index + 1 ] ),
                ( count_ - index ) * sizeof( Type* ) );
        }
    }
    return type;
}

template<class Type, class Allocator>
inline u4 ClxListBase<Type, Allocator>::locateType( Type* type )
{
    for ( u4 i = 0; i < count_; i++ )
    {
        if ( objects_[ i ] == type )
        {
            return i;    // found
        }
    }
    
    return count_;    // not found
}

template<class Type, class Allocator>
inline ClxListIteratorBase<Type, Allocator> ClxListBase<Type, Allocator>::iterator()
{
    return ClxListIteratorBase<Type, Allocator>( this );
}


#define TListIteratorBase   ClxListIteratorBase<Type, Allocator>

template<class Type, class Allocator>
inline Type* TListIteratorBase::operator *()
{
    Type* type = NULL;

    if ( current_ < list_->count_ )
    {
        type = list_->objects_[ current_ ];
    }
    
    return type;
}

template<class Type, class Allocator>
inline Type* TListIteratorBase::operator ++( int )
{
    Type* type = NULL;

    if ( current_ < list_->count_ )
    {
        type = list_->objects_[ current_++ ];
        // NOTE: incrementing the current beyond
        //       list_->count_, next time all of
        //       the operator functions will return
        //       NULL.
    }
    
    return type;
}
 
template<class Type, class Allocator>
inline Type* TListIteratorBase::operator ++()
{
    Type* type = NULL;

    if ( ( current_ + 1 ) < list_->count_ )
    {
        type = list_->objects_[ ++current_ ];
    }
    else
    {
        CLX_ASSERT(0); // this should not happen
    }
    
    return type;
}

template<class Type, class Allocator>
inline Type* TListIteratorBase::operator --( int )
{
    Type* type = NULL;
    u4 listCount = list_->count_;

    if ( current_ <= listCount )
    {
        type = list_->objects_[ current_-- ];
        // NOTE: decrementing the current beyond 0
        //       results in 0xffff which is still a
        //       positive number. Next time all of
        //       the operator functions will return
        //       NULL.
    }
    else
    {
        CLX_ASSERT(0); // this should not happen
    }
    
    return type;
}

template<class Type, class Allocator>
inline Type* TListIteratorBase::operator --()
{
    Type* type = NULL;

    if ( current_ > 0 )
    {
        type = list_->objects_[ --current_ ];
    }
    
    return type;
}


#endif  // ClxList_h
