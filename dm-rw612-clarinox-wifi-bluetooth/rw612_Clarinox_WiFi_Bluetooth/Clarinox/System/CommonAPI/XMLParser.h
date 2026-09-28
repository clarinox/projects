#ifndef XMLParser_h
#define XMLParser_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                XMLParser.h
* Description         Declares a light-weight class to parse XML documents
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/

#include "ClxDOM.h"

/**
If this modifier appears in front of a parameter decleration, it means that the content of
that parameter will be changed by the function.
*/
#define CLX_CHANGABLE

#define GET_QNAME(name, qname)                    \
{                                                 \
    s1* q_end = clxStrChr ((s1*)name, ':');       \
    qname = q_end ? (q_end + 1) : (s1*)name;      \
}

/**
XMLParser is a lightweight XML parser class which provides most (but not all) of functionality of powerful XML parsers
which are targeted on PC environments. XMLParser is mainly targeted at limited-resource embedded systems. XMLParser only
handles XML documents encoded in ASCII/UTF-8 encoding systems. XML documents encoded in a different Unicode encoding system (e.g UTF-16, UTF-32)
must be converted to UTF-8 (by using ClxUnicode class) first before fed to XMLParser class. XMLParser works in two different modes:

1. DOM mode : The result of XML parsing and analysis will be stored in a Document-Object-Model-like structure called ClxDOMDocument.
In this mode, everything is a string. The user should decide if a piece of data should be
treated as a number or string or a complex structure.

2. DataBinding mode : While the XML document is being processed, methods of another class (inherited from XMLDataBinder class) will
be invoked to analyze the data on-the-fly. The second class will simply map XML data to C/C++ data structures (structs, arrays, linked lists, ...).
In this mode, no DOM-like data structure will be created.

The second mode is the preferred mode in embedded environments, since it avoids using resource-consuming and hard-to-use DOM structures. XML data will
be directly mapped to C/C++ data structures, and will be ready to be used immediately. For more information on DataBinding mode, refer to
XMLDataBinder class documentation.

Note that, in either mode, XMLParser may alter the original XML document. If you need the original XML document after parsing, you need
to take a copy of it before feeding it to XMLParser class.
*/
class XMLParser
{
private:
    s1*               XMLDoc;
    u4                size;
    u4                currentIndex;
    u2                errNo;
    boolean           notifyComments_;

    // These are for namespace handling:
    typedef struct nameSpaceURIStruct
    {
        s1* prefix;
        s1* nameSpaceURI;
    }nameSpaceURIStruct;
    ClxExpandanleDataStack*            nameSpaceURIList;
    ClxExpandanleDataStackBrowser*     nameSpaceURIListBrowser;    

private:
    s1        isNextCharFromCharList (const s1* charList);
    s1*       nextEntity (u4& wordLength, boolean lookForEqualSign);
    u4        parseXMLAttributes (ClxDOMAttributeList* attrList, boolean* hasBody, boolean xmlStartingTag = FALSE);
    boolean   parseXMLElement ();
    s1*       nextValueTerminatingByCharList (const s1* charList, u4& valueLength);
    boolean   parseXMLDocument ();

public:
/**
Constructs an XMLParser object, and starts the parsing process.

\param[ in ] XMLDocBuffer Memory buffer containing the XML document to be processed (ASCII/UTF-8 encoded). CLX_CHANGABLE refers to the fact
that the buffer will be altered by the class during the parsing process.
\param[ in ] XMLDocSize Size of the memory buffer, in bytes. 
\param[ in ] notifyComments If TRUE, it makes the parser add \b comment elements to DOM structure as well. If FALSE, all comment elements in XML document will be ignored.

\remarks
This constructor initializes the parser, and automatically starts the parsing process. When this constructor returns, the parsing process
is already finished (successfully, or in error). The user must call getErrorIndex() function to make sure if the parsing process has been successful.
XMLDocBuffer MUST NOT be destroyed or changed during the parsing process. if \p copyStrings is FALSE, it must NOT be destroyed even after the process has been finished.
In this case, XMLDocBuffer may be destroyed after the result DOM structure has been destroyed. In embedded environments, It is preffered to set copyStrings to FALSE.
*/
    XMLParser (s1* CLX_CHANGABLE XMLDocBuffer, u4 XMLDocSize, boolean notifyComments);

/**
Retrieves the XML buffer, fed to XMLParser through XMLDocBuffer parameter of constructors.

\param[ in ] XMLDocSize Pointer to a variable of type u4 which in return will hold the size of XML buffer (as XMLDocSize parameter of constructors).
This parameter can be NULL if the user does not need this information.

\return Pointer to XML buffer (the same as XMLDocBuffer parameter of constructors).
*/
    s1* getXMLDocBuffer(u4* XMLDocSize = NULL)
    {
        if (XMLDocSize) *XMLDocSize = size;
        return XMLDoc;
    }

/**
Returns the error number if any error has happened during the parsing process.

\return the error number.

\remarks
If no error has happened during the parsing process, this function will return zero. Otherwise, 
It will return a non-zero error number. Two different types of errors might happen:

- Parsing errors : The structure of XML document does not fully comply with XML standard (errors 1 to 19 - up to 47 is reserved for this kind of errors).
- User-defined errors: Errors defined by the user who has implemented XMLParser (errors 48 or bigger). The user MUST avoid using error numbers 1 to 47 for user-defined erros.

List of Parsing Errors returned by XMLParser::getErrorNo() is as follows:

    - 0    no error occurred
    - 1    unexpected end of document
    - 2    encountered an illegal <
    - 3    expected an = after the attribute's name
    - 4    expected an " or ' after = when parsing an attribute
    - 5    expected an " or ' at the end of attributes's value
    - 6    attribute's name contains an & which is not an entity reference
    - 7    attribute's value contains an & which is not an entity reference
    - 8    element does not have a valid name
    - 9    CDATA section does not end with ]]>
    - 10   comment section does not end with -->
    - 11   closing tag does not match opening tag
    - 12   xml tag has a body
    - 13   no root element defined
    - 14   entity contains an & which is not an entity reference
    - 15   XMLDocBuffer argument of the constructor is NULL, or XMLDocSize argument is zero
    - 16   DOCTYPE does not have a root element name
    - 17   DOCTYPE section does not end with >
    - 18   closing tag does not end with >

Other errors will be caused by the implementation of XMLParser. You have to refer to the documentation related to that class to find out about the user-defined errors and their meanings.    
*/
    u4 getErrorNo()
    {
        return errNo;
    }

/** Specifies where (in the XML buffer) the parsing error has happened. 
The index is zero-based (e.g the first byte of XMLDocBuffer is index 0).

\return The index of the error in XML buffer.
*/
    u4 getErrorIndex()
    {
        return currentIndex;
    }

    u2 parse();

protected:

    virtual u2 startDocument (const s1* version, const s1* encoding) = 0;
    virtual u2 endDocument (u2 errorNo) = 0;

    virtual u2 startElement (const s1* nameSpaceURI, const s1* name, const s1* qName, ClxDOMAttributeList* attrList) = 0;
    virtual u2 endElement (const s1* nameSpaceURI, const s1* name, const s1* qName) = 0;
    virtual u2 text (const s1* data, u1 type) = 0;

    virtual u2 processingInstruction(const s1* target, const s1* data)
    {
        (void) target;
        (void) data;

        return 0; 
    }
};


#endif //XMLParser_h

