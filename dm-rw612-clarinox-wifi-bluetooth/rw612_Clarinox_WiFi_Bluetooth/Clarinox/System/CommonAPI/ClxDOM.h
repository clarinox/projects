#ifndef ClxDOM_h
#define ClxDOM_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxDOM.h
* Description         Declares a simple Document-Object-Model-like interface 
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

class ClxDOMAttribute;
class ClxDOMDocument;
class ClxDOMElement;

/**
ClxDOMAttributeList class holds a list of all attributes associated to an element. Therefore, instead of the element directly handling its attributes, all
attribute-related functionality has been transferred to this class. Elements which have at least one attribute hold a pointer to an object of type ClxDOMAttributeList. 
It is impossible for the user to directly create an object of type ClxDOMAttributeList. An object of this class will be implicitly created when one or more attribute are
attached to an element. Refer to ClxDOMDocument documentation for more information on how to DOM objects.
*/
class ClxDOMAttributeList
{
private:
    friend class ClxDOMElement;
    friend class XMLParser;

private:
    ClxDOMAttribute* first;
    ClxDOMAttribute* last;
    ClxDOMElement*     parentElement;

private:
    ClxDOMAttributeList(ClxDOMElement* parentNode) : first(NULL), last(NULL), parentElement(parentNode) {}

public:
/**
Adds an attribute to this object. An attribute (of type ClxDOMAttribute) can be created using "ClxDOMDocument::createAttribute" function.

\param[ in ] attr A pointer to an attribute object of type ClxDOMAttribute. Use "createAttribute" function of the owner document to create an attribute.

\remarks
There is no need for the user to directly call this method. Users, instead, can use "setAttribute" or "setAttributeNode" method of the parent element
to create an attribute and add it to the corresponding element. 
*/
    void                add (ClxDOMAttribute* attr);

/**
Removes an attribute from this object. Note that the corresponding attribute will be only removed from the list. The attribute object, itself, WILL NOT BE DESTROYED.   

\param[ in ] attr A pointer to an attribute which must be removed from this object.

\return FALSE if the attribute does not exist in this list (or if attr parameter is NULL). TRUE if the attributed was removed from the list successfully.

\remarks
There is no need for the user to directly call this method. Users, instead, can use "removeAttributeNode" method of the parent element
to remove an attribute from the corresponding element. DO NOT FORGET that this method (as well as "removeAttributeNode") WILL NOT FREE THE MEMORY OF THE ATTRIBUTE OBJECT. It is
user's responsibility to do so (by using c++ "delete" operator). Since the attribute object is not attached to any element any more, it will not be destroyed automatically when the owner document is destroyed. 
*/
    boolean             remove (ClxDOMAttribute* attr);

/**
Searches for the next attribute in the list, which name matches a given value.  

\param[ in ] name A null-terminated string which holds the attribute name the function should look for. This parameter is case sensitive.
\param[ in ] lastAttr A pointer to the last attribute found and returned by "getFirstAttributeByName", or "getNextAttributeByName" which has been previously called. Only attributes following
this attribute in the list will be searched.

\return If search is successful, the return value is a pointer to the found attribute with the same name as "name" parameter. If no such attribute exists (or if
"lastAttr" parameter is NULL, or does not even exist in this list), the return value will be NULL.

\remarks
A good programming practice, when using DOM documents, is to avoid using an attribute, as "lastAttr" parameter, which has not been returned by "getFirstAttributeByName"
or "getNextAttributeByName". Use the very same "name" parameter on each call to these functions. Otherwise, the result will not even make any sense.

Instead of this method, the user can directly use "getNextAttributeByName" method of the parent element object (ClxDOMElement::getNextAttributeByName).

Unlike standard DOM interface, "*" is not acceptable as "name" parameter. If "name" parameter has a prefix (e.g "clx:name"), prefixes will be considered in the search procedure.
If it does not have a prefix (e.g. "name"), prefixes in the name of all attributes will be ignored during the search procedure.
*/
    ClxDOMAttribute*    getNextAttributeByName(const s1* name, ClxDOMAttribute* lastAttr);

/**
Searches for the next attribute in the list, which name and namespace URI match given values.  

\param[ in ] name A null-terminated string which holds the attribute name the function should look for. This parameter is case sensitive.
\param[ in ] nameSpaceURI A null-terminated string which holds the namespace URI to which the result attribute must belong. If this parameter is set to NULL, it means the
returned attribute must not belong to any namespace (not even the default namespace). DO NOT USE AN EMPTY STRING FOR THIS PURPOSE. This parameter is case sensitive.
\param[ in ] lastAttr A pointer to the last attribute found and returned by "getFirstAttributeByNameNS", or "getNextAttributeByNameNS" which has been previously called. Only attaributes following
this attribute in the list will be searched.

\return If search is successful, the return value is a pointer to the found attribute which has the same name as "name" parameter, and belongs to the namespace specified by "nameSpaceURI" parameter . 
If no such attribute exists (or if "lastAttr" parameter is NULL, or does not even exist in this list), the return value will be NULL.

\remarks
A good programming practice, when using DOM documents, is to avoid using an attribute, as "lastAttr" parameter, which has not been returned by "getFirstAttributeByNameNS"
or "getNextAttributeByNameNS". Use the very same "name" and "nameSpaceURI" parameters on each call to these functions. Otherwise, the result will not even make any sense.

Instead of this method, the user can directly use "getNextAttributeByNameNS" method of the parent element object (ClxDOMElement::getNextAttributeByNameNS).

Unlike standard DOM interface, "*" is not acceptable as "name" or "nameSpaceURI" parameters. If "name" parameter has a prefix (e.g "clx:name"), prefixes will be considered in the search procedure.
If it does not have a prefix (e.g. "name"), prefixes in the name of all attributes will be ignored during the search procedure.
*/
    ClxDOMAttribute*    getNextAttributeByNameNS(const s1* name, const s1* nameSpaceURI, ClxDOMAttribute* lastAttr);

/**
Searches for an attribute in the list, which name matches a given value. The search procedure will start from the beginning of the list.  

\param[ in ] name A null-terminated string which holds the attribute name the function should look for. This parameter is case sensitive.

\return If search is successful, the return value is a pointer to the found attribute with the same name as "name" parameter. If no such attribute exists, the return value will be NULL.

\remarks
The return attribute object can be fed to "getNextAttributeByName" method, as "lastAttr" parameter, to continue the search procedure.

Instead of this method, the user can directly use "getFirstAttributeByName" method of the parent element object (ClxDOMElement::getFirstAttributeByName).

Unlike standard DOM interface, "*" is not acceptable as "name" parameter. If "name" parameter has a prefix (e.g "clx:name"), prefixes will be considered in the search procedure.
If it does not have a prefix (e.g. "name"), prefixes in the name of all attributes will be ignored during the search procedure.
*/
    ClxDOMAttribute*    getFirstAttributeByName(const s1* name)
    {
        return getNextAttributeByName (name, first);
    }

/**
Searches for an attribute in the list, which name and namespace URI match given values. The search procedure will start from the beginning of the list.  

\param[ in ] name A null-terminated string which holds the attribute name the function should look for. This parameter is case sensitive.
\param[ in ] nameSpaceURI A null-terminated string which holds the namespace URI to which the result attribute must belong. If this parameter is set to NULL, it means the
returned attribute must not belong to any namespace (not even the default namespace). DO NOT USE AN EMPTY STRING FOR THIS PURPOSE. This parameter is case sensitive.

\return If search is successful, the return value is a pointer to the found attribute which has the same name as "name" parameter, and belongs to the namespace specified by "nameSpaceURI" parameter . 
If no such attribute exists, the return value will be NULL.

\remarks
The return attribute object can be fed to "getFirstAttributeByNameNS" method, as "lastAttr" parameter, to continue the search procedure.

Instead of this method, the user can directly use "getFirstAttributeByNameNS" method of the parent element object (ClxDOMElement::getFirstAttributeByNameNS).

Unlike standard DOM interface, "*" is not acceptable as "name" or "nameSpaceURI" parameters. If "name" parameter has a prefix (e.g "clx:name"), prefixes will be considered in the search procedure.
If it does not have a prefix (e.g. "name"), prefixes in the name of all attributes will be ignored during the search procedure.
*/
    ClxDOMAttribute*    getFirstAttributeByNameNS(const s1* name, const s1* nameSpaceURI)
    {
        return getNextAttributeByNameNS (name, nameSpaceURI, first);
    }

/**
Returns a pointer to parent element object (the element which owns the attributes stored in this list).

\return A pointer to parent element object. The return value should never be NULL.
*/
    ClxDOMElement*  getParentNode()
    {
        return parentElement;
    }

/**
Returns a pointer to the first attribute object stored in this list.

\return A pointer to the first attribute object stored in this list. if no attribute is stored in the list, the returned value is NULL.
*/
    ClxDOMAttribute* getFirstAttribute()
    {
        return first;
    }

/**
Returns a pointer to the last attribute object stored in this list.

\return A pointer to the last attribute object stored in this list. if no attribute is stored in the list, the returned value is NULL.
*/
    ClxDOMAttribute* getLastAttribute()
    {
        return last;
    }

/**
Destroys all the attributes in the list, and frees the memory associated to them. The destructor is automatically called when the owner element is being destroyed.
*/
    ~ClxDOMAttributeList();
};


/**
There are 4 type of elements:

CLXDOM_REGULAR  : a regular element which can have attributes, body, and child elements.

CLXDOM_TEXT        : an element which only holds a text. It serves as a body element for its parent element. It cannot have attributes, or child elements.

CLXDOM_CDATA    : an element which only holds non-decodable data. It is the same as text elements. Refer to XML documentation for more information on CDATA sections.

CLXDOM_COMMENT    : an element which only holds a comment. It cannot have attributes, or child elements.
*/
#define CLXDOM_REGULAR        1
#define CLXDOM_TEXT           3
#define CLXDOM_CDATA          4
#define CLXDOM_COMMENT        8

/**
ClxDOMElement holds all data about an element node in DOM documents. Each ClxDOMElement object has a parent element (except for the root element which does not have any parent).
Each element can have siblings (it holds pointers to previous and next elements, in the list of their parent's children). Also, each element can have children (it holds pointers to its first
and last child). 

Each element can also have attributes (it holds a pointer to a ClxDOMAttributeList object which, on behalf of the parent element, holds a list of attributes).
Elements can be of type CLXDOM_REGULAR, CLXDOM_TEXT, CLXDOM_CDATA, and CLXDOM_COMMENT. Only elements of type CLXDOM_REGULAR can have children, and attributes. The user can define their own
element types (by using any type ID except 1, 3, 4, and 8), but the standard ClxDOMElement does not come with any support (e.g search) for user-defined elements. The user should write their own
version of element class (inherited from ClxDOMElement).

Each element has a name (called "Tag Name" in XML terminology), and can belong to a namespace. A namespace serves like namespaces in C++, in order to eliminate the possibility of similar "Tag Name" confusion in DOM documents.
A namespace can be any null-terminated string, but in XML standard, they take the form of an URI (web address). The namespace URI does not necessarily refer to a real website. It is just a unique name.
If an element does not belong to any namespace, its nameSpaceURI parameter must be NULL. Avoid using an empty string ("") for this purpose. Following this rule will prevent the user from getting confused by namespaces.

ClxDOMElement object cannot be created directly by the user. They must be created with "ClxDOMDocument::createElement" method. Refer to "ClxDOMDocument" for more information on how to use DOM objects.
*/
class ClxDOMElement
{
private:
    friend class ClxDOMDocument;

private:
    s1*        tagName;
    s1*        nsURI;

    ClxDOMElement* prevSibling;
    ClxDOMElement* nextSibling;
    ClxDOMElement* firstChild;
    ClxDOMElement* lastChild;
    ClxDOMElement* parentNode;
    
    ClxDOMAttributeList* attributes;

    u1        nodeType;
    boolean copyTagName;

private:
    ClxDOMElement (ClxDOMElement* parentNode_, s1* tagName_, s1* nameSpaceURI, boolean copyTagName_ = TRUE, u1 elementType = CLXDOM_REGULAR);
    void            initialize(ClxDOMElement* rightBefore, ClxDOMElement* rightAfter, ClxDOMElement* parent);
    ClxDOMElement*    getElement (const s1* elementName, const s1* nameSpaceURI, boolean NS);     

public:
/**
Searches for the next child element, which tag name matches a given value. Only elements of type CLXDOM_REGULAR will be included in the search procedure.  

\param[ in ] name A null-terminated string which holds the tag name the method should look for. This parameter is case sensitive.
\param[ in ] lastElement A pointer to the last element found and returned by "getFirstElementByTagName", or "getNextElementByTagName" which has been previously called. Only elements in a lower position to this
element will be searched (lower position means either a child or a sibling element attached after the element).

\return If search is successful, the return value is a pointer to the found element with the same tag name as "name" parameter. If no such attribute exists (or if
"lastElement" parameter is NULL), the return value will be NULL.

\remarks
A good programming practice, when using DOM documents, is to avoid using an element, as "lastElement" parameter, which has not been returned by "getFirstElementByTagName"
or "getNextElementByTagName". Use the very same "name" parameter on each call to these functions. Otherwise, the result will not even make any sense.

Unlike standard DOM interface, "*" is not acceptable as "name" parameter. If "name" parameter has a prefix (e.g "clx:name"), prefixes will be considered in the search procedure.
If it does not have a prefix (e.g. "name"), prefixes in the name of all attributes will be ignored during the search procedure.

This function only searches this element's children. The element's siblings (or the element itself) will not be included in the search procedure. In DOM terminology, an element's children includes the direct children
(elements directly attached to that element), and indirect children (the children of children, and the children of the children of the children, and so on).
*/
    ClxDOMElement*    getNextElementByTagName (const s1* name, ClxDOMElement* lastElement);

/**
Searches for the next child element, which tag name and namespace URI match given values. Only elements of type CLXDOM_REGULAR will be included in the search procedure.  

\param[ in ] name A null-terminated string which holds the tag name the method should look for. This parameter is case sensitive.
\param[ in ] nameSpaceURI A null-terminated string which holds the namespace URI to which the result element must belong. If this parameter is set to NULL, it means the
returned element must not belong to any namespace (not even the default namespace). DO NOT USE AN EMPTY STRING FOR THIS PURPOSE. This parameter is case sensitive.
\param[ in ] lastElement A pointer to the last element found and returned by "getFirstElementByTagNameNS", or "getNextElementByTagNameNS" which has been previously called. Only elements in a lower position to this
element will be searched (lower position means either a child or a sibling element attached after the element).

\return If search is successful, the return value is a pointer to the found element with the same tag name as "name" parameter and belongs to the namespace specified by "nameSpaceURI" parameter. 
If no such attribute exists (or if "lastElement" parameter is NULL), the return value will be NULL.

\remarks
A good programming practice, when using DOM documents, is to avoid using an element, as "lastElement" parameter, which has not been returned by "getFirstElementByTagName"
or "getNextElementByTagName". Use the very same "name" and "nameSpaceURI" parameters on each call to these functions. Otherwise, the result will not even make any sense.

Unlike standard DOM interface, "*" is not acceptable as "name" and "nameSpaceURI" parameters. If "name" parameter has a prefix (e.g "clx:name"), prefixes will be considered in the search procedure.
If it does not have a prefix (e.g. "name"), prefixes in the name of all attributes will be ignored during the search procedure.

This function only searches this element's children. The element's siblings (or the element itself) will not be included in the search procedure. In DOM terminology, an element's children includes the direct children
(elements directly attached to that element), and indirect children (the children of children, and the children of the children of the children, and so on).
*/
    ClxDOMElement*    getNextElementByTagNameNS (const s1* name, const s1* nameSpaceURI, ClxDOMElement* lastElement);

/**
Finds the next text node child (a child element of type CLXDOM_TEXT). This function only searches direct children of this element. 

\param[ in ] lastElement the last text child found and returned by "getFirstTextNode" or "getNextTextNode".

\return A pointer to the found text node. If no text node is found, the return value will be NULL.

\remarks
A good programming practice, when using DOM documents, is to avoid using an element, as "lastElement" parameter, which has not been returned by "getFirstTextNode"
or "getNextTextNode". Using a "lastElement" object which is not a text node, or even is not a direct child, will not make any sense.

This function searches for direct children. In DOM terminology, an element's children includes the direct children
(elements directly attached to that element), and indirect children (the children of children, and the children of the children of the children, and so on).
*/
    ClxDOMElement*    getNextTextNode (ClxDOMElement* lastElement);

/**
Removes (detaches) a child element from the DOM document tree.

\param[ in ] child A pointer to the child element which must be removed.

\remarks
"child" parameter can be a direct or indirect child, or it can even be not a child of this element. To prevent any confusion from happening, we recommend that this method only be used
for direct children.

This method WILL NOT destroy "child" object. It is the user's responsibility to delete the element (by using c++ "delete" operator). 
*/
    void            removeChild (ClxDOMElement* child);

/**
Replaces a child element with another element.

\param[ in ] newChild A pointer to the new element.
\param[ in ] oldChild A pointer to the child element which must be replaced.

\remarks
"oldChild" parameter can be a direct or indirect child, or it can even be not a child of this element. To prevent any confusion from happening, we recommend that this method only be used
for direct children.

This method WILL NOT destroy "oldChild" object. It is the user's responsibility to delete the element (by using c++ "delete" operator).

"newChild" MUST NO BE ATTACHED to the any DOM document. If so, remove it first (by calling "removeChild" method). If you do not do so, using this method will result in the parent DOM document
being broken.
*/
    void            replaceChild (ClxDOMElement* newChild, ClxDOMElement* oldChild);

/**
Creates a new attribute, and attaches it to this element.

\param[ in ] name The name of the attribute as a null-terminated string. This parameter CANNOT be NULL.
\param[ in ] nameSpaceURI The namespace URI to which this attribute belongs, as a null-terminated string. This parameter can be NULL.
\param[ in ] value The value associated to this parameter, as a null-terminated string. This parameter CANNOT be NULL.
\param[ in ] copyAttribute_ If TRUE, all the three strings mentioned above will be copied to new function-allocated buffers, and then attached to the created attribute node.
If FALSE, the very same strings will be attached to the created attribute. Default value is TRUE.
*/
    void            setAttribute (s1* name, s1* nameSpaceURI, s1* value, boolean copyAttribute_ = TRUE);

/**
Attaches an already-created attribute, to this element. The same as "ClxDOMAttributeList::add" function.
*/
    void            setAttributeNode (ClxDOMAttribute* attr);

/**
Changes Tag name of this element.

\param[ in ] tagName_ the new tag name, as a null-terminated string.

\remarks
If this element has been created with "copyTagName_" parameter of "ClxDOMDocument::Createelement" or "ClxDOMDocument::creareText" method set to TRUE, the new tag name will be
first copied to a function-allocated buffer and then will be inserted to the element. Otherwise, the very same string pointer will be added to the element.
*/
    void            setTagName (s1* tagName_);

/**
Changes the namespace URI this element belongs to.

\param[ in ] nameSpaceURI The new namespace URI, as a null-terminated string. This parameter can be NULL (which means this element does not belong to any namespace).

\remarks
If this element has been created with "copyTagName_" parameter of "ClxDOMDocument::Createelement" or "ClxDOMDocument::creareText" method set to TRUE, the new namespace URI string will be
first copied to a function-allocated buffer and then will be inserted to the element. Otherwise, the very same string pointer will be added to the element.
*/
    void            setNameSpaceURI (s1* nameSpaceURI);

/**
Creates an exact copy of this element, with the same name, namespace URI, attributes, and children. The result element will not be attached to any DOM document.

\param[ in ] copyChildsAndAttributes if TRUE, states that all children and attributes of this element must be copied to the new element. If FALSE, the result element will not have any children or
attributes.
\param [ in ] copyStrings if TRUE, states that all strings (this element's and children elements' name and namespaceURI, and attributes' name and value and namspaceURI) must be copied to new function-allocated buffers.
if FALSE, the very same pointers to those strings will be used.

\return A pointer to the new element.

\remarks
This function initializes a new ClxDOMElement object and copies the contents of this element into the new object. If "copyChildsAndAttributes" is set to TRUE, and this element has any
children or attributes, a new object will be created for each of them, and the contents of those elements and attributes will be copied to new objects as well.
Setting "copyStrings" to FALSE is troublesome. The user has to be very careful. In this case, If the original element gets destroyed, all these buffers might become invalid, leaving the cloned element broken.
*/
    ClxDOMElement*    cloneElement (boolean copyChildsAndAttributes, boolean copyStrings);

/*
Retrieves the position of this element in the DOM document tree.

\return A zero-based index as the position of the element in the tree.

\remarks
The root element has position 0. Its direct children have position 1. Its children's direct children has position 2, and so on.
*/
    u4                getTreePosition();

public:

/**
Searches for a child element, which tag name matches a given value. The search procedure starts from the first child of this element. 
Only elements of type CLXDOM_REGULAR will be included in the search procedure.  

\param[ in ] name A null-terminated string which holds the tag name the method should look for. This parameter is case sensitive.

\return If search is successful, the return value is a pointer to the found element with the same tag name as "name" parameter. If no such attribute exists (or if
"lastElement" parameter is NULL), the return value will be NULL.

\remarks
Unlike standard DOM interface, "*" is not acceptable as "name" parameter. If "name" parameter has a prefix (e.g "clx:name"), prefixes will be considered in the search procedure.
If it does not have a prefix (e.g. "name"), prefixes in the name of all attributes will be ignored during the search procedure.

This function only searches this element's children. The element's siblings (or the element itself) will not be included in the search procedure. In DOM terminology, an element's children includes the direct children
(elements directly attached to that element), and indirect children (the children of children, and the children of the children of the children, and so on).
*/
    ClxDOMElement* getFirstElementByTagName (const s1* name)
    {
        return getNextElementByTagName (name, this);
    }

/**
Searches for the next child element, which tag name and namespace URI match given values. The search procedure starts from the first child of this element. 
Only elements of type CLXDOM_REGULAR will be included in the search procedure.  

\param[ in ] name A null-terminated string which holds the tag name the method should look for. This parameter is case sensitive.
\param[ in ] nameSpaceURI A null-terminated string which holds the namespace URI to which the result element must belong. If this parameter is set to NULL, it means the
returned element must not belong to any namespace (not even the default namespace). DO NOT USE AN EMPTY STRING FOR THIS PURPOSE. This parameter is case sensitive.

\return If search is successful, the return value is a pointer to the found element with the same tag name as "name" parameter and belongs to the namespace specified by "nameSpaceURI" parameter. 
If no such attribute exists (or if "lastElement" parameter is NULL), the return value will be NULL.

\remarks
Unlike standard DOM interface, "*" is not acceptable as "name" and "nameSpaceURI" parameters. If "name" parameter has a prefix (e.g "clx:name"), prefixes will be considered in the search procedure.
If it does not have a prefix (e.g. "name"), prefixes in the name of all attributes will be ignored during the search procedure.

This function only searches this element's children. The element's siblings (or the element itself) will not be included in the search procedure. In DOM terminology, an element's children includes the direct children
(elements directly attached to that element), and indirect children (the children of children, and the children of the children of the children, and so on).
*/
    ClxDOMElement* getFirstElementByTagNameNS (const s1* name, const s1* nameSpaceURI)
    {
        return getNextElementByTagNameNS (name, nameSpaceURI, this);
    }

/**
Retrieves namespace to which this element belongs.

\return A pointer to a null-terminated string containing namespace URI to which element belongs.
*/
    s1*    getNameSpaceURI()
    {
        return nsURI;
    }

/**
Finds a text node child (a child element of type CLXDOM_TEXT). The search procedure starts from the first child of this element.
This function only searches direct children of this element. 

\return A pointer to the found text node. If no text node is found, the return value will be NULL.

\remarks
This function searches diret children. In DOM terminology, an element's children includes the direct children
(elements directly attached to that element), and indirect children (the children of children, and the children of the children of the children, and so on).
*/
    ClxDOMElement* getFirstTextNode ()
    {
        return getNextTextNode (firstChild);
    }
    
/**
Searches for the next attribute in the list, which name matches a given value. The same as "ClxDOMAttributeList::getNextAttributeByName" method.
*/
    ClxDOMAttribute* getNextAttributeByName(const s1* name, ClxDOMAttribute* lastAttr)
    {
        if (attributes) return attributes->getNextAttributeByName (name, lastAttr);
        else return NULL;
    }

/**
Searches for an attribute in the list, which name matches a given value. The search procedure will start from the beginning of the list. 
The same as "ClxDOMAttributeList::getFirstAttributeByName" method.
*/
    ClxDOMAttribute* getFirstAttributeByName(const s1* name)
    {
        if (attributes) return attributes->getFirstAttributeByName (name);
        else return NULL;
    }
    
/**
Searches for the next attribute in the list, which name and namespace URI match given values.
The same as "ClxDOMAttributeList::getNextAttributeByNameNS" method.
*/
    ClxDOMAttribute* getNextAttributeByNameNS(const s1* name, const s1* nameSpaceURI, ClxDOMAttribute* lastAttr)
    {
        if (attributes) return attributes->getNextAttributeByNameNS (name, nameSpaceURI, lastAttr);
        else return NULL;
    }

/**
Searches for an attribute in the list, which name and namespace URI match given values. The search procedure will start from the beginning of the list.
The same as "ClxDOMAttributeList::getFirstAttributeByNameNS" method.
*/
    ClxDOMAttribute* getFirstAttributeByNameNS(const s1* name, const s1* nameSpaceURI)
    {
        if (attributes) return attributes->getFirstAttributeByNameNS (name, nameSpaceURI);
        else return NULL;
    }

/**
Adds a child element to this element. If this element already has children elements, the new child will be attached at the end of children list.

\param[ in ] newElement A pointer to the new element to be attached to the end of this element's children list.

\remarks
"newElement" MUST NO BE ATTACHED to the any DOM document. If so, remove it first (by calling "removeChild" method). If you do not do so, using this method will result in the parent DOM document
being broken.
*/
    void appendChild (ClxDOMElement* newElement)
    {
        if (nodeType == CLXDOM_REGULAR)
        {
            newElement->initialize (NULL, lastChild, this);
        }
    }

/**
Adds a child element to this element. The new child will be attached right before a specified child.

\param[ in ] newElement A pointer to the new element.
\param[ in ] currentElement A pointer to a current child of this element. "currentElement" MUST be a direct child of this element. "newElement" will be inserted right before "currentElement" in their parent's children list.

\remarks
"newElement" MUST NO BE ATTACHED to the any DOM document. If so, remove it first (by calling "removeChild" method). If you do not do so, using this method will result in the parent DOM document
being broken.

If "currentElement" is not a direct child of this element, this function will do nothing.
*/
    void insertBefore (ClxDOMElement* newElement, ClxDOMElement* currentElement)
    {
        if (currentElement->parentNode == this)
        {
            newElement->initialize (currentElement, NULL, NULL);
        }
    }
    
/**
Removes an attribute from this object. The same as "ClxDOMAttributeList::remove" method.
*/
    boolean removeAttributeNode (ClxDOMAttribute* attr)
    {
        if (attributes) return attributes->remove (attr);
        else return FALSE;
    }
    
/**
Specifies if this element has any child nodes.

\return TRUE if this element has any child elements. FALSE otherwise.
*/
    boolean hasChildNodes()
    {
        return firstChild ? TRUE : FALSE;
    }
    
/**
Specifies if this element has any attributes.

\return TRUE if this element has any attributes. FALSE otherwise.
*/
    boolean hasAttributes()
    {
        return attributes ? (attributes->getFirstAttribute() ? TRUE : FALSE) : FALSE;
    }
    
/**
Retrieves the previous sibling of this element.

\return A pointer to the previous sibling element. NULL if this element is the first element in the list of its parent's elements.
*/
    ClxDOMElement* getPrevSibling()
    {
        return prevSibling;
    }

/**
Retrieves the next sibling of this element.

\return A pointer to the next sibling element. NULL if this element is the last element in the list of its parent's elements.
*/
    ClxDOMElement* getNextSibling()
    {
        return nextSibling;
    }

/**
Retrieves the parent element of this element.

\return A pointer to the parent element. NULL if this is the root element.
*/
    ClxDOMElement* getParentNode()
    {
        return parentNode;
    }

/**
Retrieves the first child element of this element.

\return A pointer to the first child element. NULL if this element does not have any child.
*/
    ClxDOMElement* getFirstChild()
    {
        return firstChild;
    }

/**
Retrieves the last child element of this element.

\return A pointer to the last child element. NULL if this element does not have any child.
*/
    ClxDOMElement* getLastChild()
    {
        return lastChild;
    }

/**
Changes the element type of this element.

\param[ in ] elementType The ID of new type. It can be CLXDOM_REGULAR, CLXDOM_TEXT, CLXDOM_CDATA, or CLXDOM_COMMENT. It can also be a user-defined type (ID can be any one-byte number except for 1, 3, 4, and 8).
*/
    void setElementType (u1 elementType)
    {
        nodeType = elementType;
    }

/**
Gets the attribute list of this element.

\return A pointer to an object of type ClxDOMAttributeList, which holds the attribute list of this element. NULL if this element does not have any attribute.
*/
    ClxDOMAttributeList* getAttributes()
    {
        return attributes;
    }

/**
Retrieves the tag name of this element.

\return A null-terminated string, containing the tag name.
*/
    s1* getTagName()
    {
        return tagName;
    }

/**
Retrieves the type of this element.

\return The ID of the element's type. Standard IDs are: 1 (CLXDOM_REGULAR), 3 (CLXDOM_TEXT), 4 (CLXDOM_CDATA), and 8 (CLXDOM_COMMENT). All other IDs are user-defined.
*/
    u1 getElementType ()
    {
        return nodeType;
    }

/**
Destroys all children and attributes of this element. Also, cleans up all memory blockes allocated directly by DOM objects. 
*/
    ~ClxDOMElement();
};



/**
ClxDOMDocument class is the base class for creating DOM documents.

A DOM (Document Object Model) document is a tree data structure which consists of a root node, and one or many sub-nodes. In DOM, each node is called an element.
The root element can have multiple sub-elements (called children), and each of these elements can have multiple sub-elements. All elements under an element are called that element's children.
The elements which come right under an element (directly attached to that element) are called the element's direct children. All other elements (e.g the children of these elements) are called the first element's
indirect children. Note that attributes are NOT considered children of their parent element.

Each element has a name (called tag name). Tag name may belong to a namespace, therefore two tag names which are the same but from different namespaces are considered two different names in DOM. Two different elements with the same name and namespace
may exist in a DOM document. Although namespaces can be any string, but they usually take the form of an URI (e.g http://www.mycompany.com/mynamespace). The URI does not need to point to a real webpage. Since URIs are unique names in the world of web, they can
be used as namespaces.

Each element may have one or more attributes. Each attribute has a name (which may belong to a namespace), and a value (which is always a null-terminated string). Attributes CANNOT have children (sub-elements, or sub-attributes).
Furthermore, elements can be of different types. The four standard element types are:

CLXDOM_REGULAR  : a regular element which can have attributes, and child elements.

CLXDOM_TEXT        : an element which only holds a text (as its tag name). It cannot have attributes, or child elements.

CLXDOM_CDATA    : an element which only holds non-decodable data (as its tag name). It is the same as text elements. Refer to XML documentation for more information on CDATA sections.

CLXDOM_COMMENT    : an element which only holds a comment (as its tag name). It cannot have attributes, or child elements.

Although DOM documents have been invented to represent XML documents in the form of a tree data structure in applications, but they can be used for any tree-like data architecture.
XMLParser class (defined in XMLParser.h file) can parse an XML document, and convert it to a DOM document. The result of the parsing process is a pointer to ClxDOMDocument object.

There is a standard DOM document API, implemented in some programming languages such as Java, JavaScript, .NET framework languages, and others. Although, Clarinox DOM document model is similar to
the standard DOM model, but there are some differences. Therefore, it is necessary to users to read this documentation before starting to use Clarinox DOM documents.

Clarinox DOM model consists of 4 classes:

ClxDOMDocument : the base class which holds a pointer to the root element.

ClxDOMElement : the class representing elements in DOM documents. Each instance of this class holds pointers to the parent element, children, sibling elements, and a pointer to an object of type
ClxDOMAttributeList, which holds the list of element's attributes.

ClxDOMAttribute : the base class for each attribute of an element. Each instance of this class holds a pointer to its parent list (of type ClxDOMAttributeList).

ClxDOMAttributeList : the container class for all attributes of an element.

The important note is none of the classes mentioned above (except for ClxDOMDocument) can be instantiated directly by their constructors. The following describes how to create a DOM document:

1. Create an instance of ClxDOMDocument class by directly calling its constructor. This will be your DOM document base object.

2. Call "CreateElement" method of your document object to create an element node.

3. Attach this element to the document as a root element, by calling "setRootElement" of your document object.

4. Any other elements which are to be attached to this document must be created by "createElement" or "createTextNode" methods of your document object first. Then, the
result elements can be attached to wherever in your document tree. Use "appendChild" or "insertBefore" methods of any of element objects to add a child element to it.

5. Attributes can be created and added to an element by calling "setAttribute" of an element object. Alternatively, an attribute node can be created first, by calling
"createAttribute" method your document object. Then the result attribute object can be attached to an element by calling "setAttributeNode" method of that element.

6. To remove (detach) an element or attribute from the document, use their parent element's "removeChild" or "removeAttributeNode" methods, respectively. The detached element or attribute
can now be attached to another place in the same document, or be attached to a different document. Or, they can be simply destroyed by using c++ "delete" operator. When you destroy an element,
All its child elements and attributes will be automatically destroyed as well.

7. To destroy the whole document, simply destroy the document base object. This will automatically destroy all the elements and attributes attached to the document.
*/
class ClxDOMDocument
{
private:
    s1* xmlVersion;
    s1* xmlEncoding;
    s1* DOCTYPEName;
    s1* DOCTYPEValue;
    ClxDOMElement* root;

public:
/**
Creates a new DOM document.

\param[ in ] version The version of this document (applicable to XML documents), as a null-terminated string. The default value is 1.0 (XML version). This is a just an informative parameter to the user.
The document will simply ignore this parameter.
\param[ in ] encoding The encoding system of all stored strings in the document, as a null-terminated string. The default value is UTF-8. This is a just an informative parameter to the user.
The document will simply ignore this parameter.
*/
    ClxDOMDocument (const s1* version = "1.0", const s1* encoding = "UTF-8");

/**
Sets the root element of this document.

\param[ in ] rootElement A pointer to an element object (created by "createElement" method), which is to be set as the root element of the document.

\remarks
If the document already has a root element, it will be destroyed first (along with all its children nodes and attributes). If you do not want the current root element to be destroyed,
try creating a new document, instead of changing the root element of this document.
*/
    void setRootElement (ClxDOMElement* rootElement);

/**
Retrieves the root element of this document.

\return A pointer to an object of type ClxDOMElement, which is the root element of this document.
*/
    ClxDOMElement* getRootElement()
    {
        return root;
    }

/**
Retrieves the version of this document.

\return A null-terminated string, holding the version.
*/
    s1* getVersion()
    {
        return xmlVersion;
    }

/**
Retrieves the encoding system used for strings stored in this document.

\return A null-terminated string, holding the name of encoding system used.
*/
    s1* getEncoding ()
    {
        return xmlEncoding;
    }

/**
Changes the version of this document.

\param[ in ] version New version of this document, as null-terminated string.
*/
    void                setVersion(s1* version);

/**
Changes the name of the encoding system used for strings stored in this document.

\param[ in ] encoding New encoding system of strings in this document, as null-terminated string.
*/
    void                setEncoding(s1* encoding);

/**
Sets DOCTYPE information of this document. This is only applicable to XML documents. Refer to XML documents for more information on DOCTYPE.

\param[ in ] name The name of DOCTYPE, as null-terminated string. This is simply the tag name of the root element.
\param[ in ] value Other information about DOCTYPE (it can be a reference to a DOCTYPE document, or definitions, or ...). Refer to XML documents.

\remarks
A DOCTYPE definition in an HTML document can be something like this:

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">

In the example above, "name" parameter is HTML, and "value" parameter is the rest, meaning PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd".
*/
    void                setDOCTYPE (s1* name, s1* value);

/**
Creates a new attribute, without attaching it to the document.

\param[ in ] attrName The name of the attribute as a null-terminated string. This parameter CANNOT be NULL.
\param[ in ] nameSpaceURI The namespace URI to which this attribute belongs, as a null-terminated string. This parameter can be NULL.
\param[ in ] attrValue The value associated to this parameter, as a null-terminated string. This parameter CANNOT be NULL.
\param[ in ] copyAttribute_ If TRUE, all the three strings mentioned above will be copied to new function-allocated buffers, and then attached to the created attribute node.
If FALSE, the very same strings will be attached to the created attribute. Default value is TRUE. Refer to "createElement" documentation for more details.
*/
    ClxDOMAttribute*    createAttribute (s1* attrName, s1* nameSpaceURI, s1* attrValue, boolean copyAttribute_ = TRUE);

/**
Creates a new element object, without attaching it to the document.

\param[ in ] tagName_ The tag name of the element, as a null-terminated string. This parameter CANNOT be null.
\param[ in ] nameSpaceURI The namespace URI to which the new will belong. This parameter can be NULL, which means the new element will not belong to any namespace. DO NOT USE EMPTY STRING FOR THIS PURPOSE.  
\param[ in ] copyTagName_ If TRUE, starts that "tagName_", and "nameSpaceURI" parameters must be copied to new function-allocated buffers, and then attached to the object. If FALSE, states that the pointers to these strings
will be directly added to the element.
\param[ in ] elementType The type of the new element. Refer to ClxDOMElement documentation for more information.

\return A pointer to a new element object. It is not attached to the document.

\remarks
When "copyTagName_" parameter is TRUE, this function will create new buffers for string, and copy the strings into them. In this case, the caller is given back the ownership of
"tagName_", and "nameSpaceURI" strings, as soon as the function returns. When the element object is being destroyed, The function-allocated buffers will be deleted automatically.

When "copyTagName_" parameter is FALSE, this function will set the internal pointers to directly point to these two strings. Therefore, The caller WILL NOT BE GIVEN BACK THE OWNERSHIP, until
the element object is destroyed.
*/
    ClxDOMElement*        createElement (s1* tagName_, s1* nameSpaceURI = NULL, boolean copyTagName_ = TRUE, u1 elementType = CLXDOM_REGULAR);

/**
Creates a new text element node.

\param[ in ] text The text, as a null-terminated string.
\param[ in ] copyText Specifies the ownership of "text" buffer. Refer to "createElement" documentation for more details.

\return A pointer to a new text node object. It is not attached to the document.

\remarks
A call to this function is equivalent to a call to "createElement" as follows:

createElement (text, NULL, copyText, CLXDOM_TEXT);
*/
    ClxDOMElement*        createTextNode (s1* text, boolean copyText = TRUE);

/**
Destroys this DOM document, along with all children and attributes, and document-allocated buffers.
*/
    ~ClxDOMDocument()
    {
        if (DOCTYPEName) delete[] DOCTYPEName;
        if (DOCTYPEValue) delete[] DOCTYPEValue;
        if (xmlVersion) delete[] xmlVersion;
        if (xmlEncoding) delete[] xmlEncoding;
        if (root) delete root;
    }
};


/**
ClxDOMAttribute class represents an attribute in an DOM document. It cannot be instantiated directly. Use "ClxDOMDocument::createAttribute" to create an attribute object.
Alternatively, use "ClxDOMElement::setAttribute" to create an attribute object, and attach it to an element. 
*/
class ClxDOMAttribute
{
private:
    friend class ClxDOMAttributeList;
    friend class ClxDOMDocument;
    friend class ClxDOMElement;
    friend class XMLParser;

private:
    s1*                     name;
    s1*                     value;
    s1*                     nsURI;
    ClxDOMAttribute*        prevSibling;
    ClxDOMAttribute*        nextSibling;
    ClxDOMAttributeList*    parentList;
    boolean                 copyAttribute;

private:
    ClxDOMAttribute (s1* attrName, s1* nameSpaceURI, s1* attrValue, boolean copyAttribute_ = TRUE);

public:
    void setName (s1* newName);
    void setValue (s1* newValue);
    void setNameSpaceURI (s1* nameSpaceURI);

public:
/**
Creates a new attribute object, and copies all the current attribute's data into the new attribute. The new attribute will be not be attached to the document.

\param[ in ] copyAttribute_ If TRUE, this function allocates new buffers in the memory, and copies this attribute's data (name, value, and namespace URI) into these new buffers, and then attach these new buffers to the new attribute object.
If FALSE, this function directly attaches the very same buffers of this attribute, to the new attribute.

\remarks
Setting "copyAttribute_" to FALSE is troublesome. The user has to be very careful. In this case, If the original attribute gets destroyed, all these buffers might become invalid, leaving the cloned attribute broken.
*/
    ClxDOMAttribute* cloneAttribute (boolean copyAttribute_);

/**
Retrieves the previous sibling of this attribute in the attributes list of the parent element.

\return A pointer to an object of type ClxDOMAttribute, which is the previous sibling attribute.
*/
    ClxDOMAttribute* getPrevSibling()
    {
        return prevSibling;
    }

/**
Retrieves the next sibling of this attribute in the attributes list of the parent element.

\return A pointer to an object of type ClxDOMAttribute, which is the next sibling attribute.
*/
    ClxDOMAttribute* getNextSibling()
    {
        return nextSibling;
    }

/**
Retrieves the name of this attribute.

\return A null-terminated string, holding the name of this attribute.
*/
    s1* getName()
    {
        return name;
    }

/**
Retrieves the value of this attribute.

\return A null-terminated string, holding the value of this attribute.
*/
    s1* getValue()
    {
        return value;
    }

/**
Retrieves the namespace URI to which this attribute belongs.

\return A null-terminated string, holding the namespace URI to which this attribute belongs. The return value can be NULL.
*/
    s1* getNameSpaceURI()
    {
        return nsURI;
    }

/**
Retrieves ths attribute's parent list object.

\return A pointer to an object of type ClxDOMAttributeList, which is the parent list object.
*/
    ClxDOMAttributeList* getParentList()
    {
        return parentList;
    }

/**
Destroys the attribute object, and any object-allocated string buffers.
*/
    ~ClxDOMAttribute();
};


#endif // ClxDOM_h
