#ifndef ClxStandard_h
#define ClxStandard_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxStandard.h
* Description         Clarinox standard functions
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

 
#if defined(CLX_USE_STD_STRING_H)

#define CLX_STRLEN      return (((const s1*)str != NULL) ? (ClxSize)strlen(str) : 0);
#define CLX_STRCPY      return ((((const s1*)source != NULL) && ((const s1*)destination != NULL)) ? strcpy(destination, source) : 0);
#define CLX_STRCMP      return ((((const s1*)str1 != NULL) && ((const s1*)str2 != NULL)) ? strcmp(str1, str2) : -1);     
#define CLX_MEMCPY      return ((((const u1*)source != NULL) && ((const u1*)destination != NULL)) ? memcpy(destination, source, n) : 0);
#define CLX_MEMCMP      return ((((const u1*)buf1 != NULL) && ((const u1*)buf2 != NULL)) ? memcmp(buf1, buf2, n) : -1);    
#define CLX_MEMSET      return (((const u1*)destination != NULL) ? memset(destination, c, count) : 0);  
#define CLX_MEMMOVE     return ((((const u1*)source != NULL) && ((const u1*)destination != NULL)) ? memmove(destination, source, n) : 0);     
#define CLX_STRCHR      return (((const s1*)source != NULL) ? strchr(source, character) : 0);     
#define CLX_STRRCHR     return (((const s1*)source != NULL) ? strrchr(source, character) : 0);  
#define CLX_STRSTR      return ((((const s1*)source != NULL) && ((const s1*)sub != NULL)) ? strstr(source, sub) : 0);     
#define CLX_STRNCPY     return ((((const s1*)source != NULL) && ((const s1*)destination != NULL)) ? strncpy(destination, source, num) : 0);    
#define CLX_STRCAT      return ((((const s1*)source != NULL) && ((const s1*)destination != NULL)) ? strcat(destination, source) : 0);       
#define CLX_STRNCAT     return ((((const s1*)source != NULL) && ((const s1*)destination != NULL)) ? strncat(destination, source, num) : 0);
#define CLX_STRNCMP     return ((((const s1*)src1 != NULL) && ((const s1*)src2 != NULL)) ? strncmp(src1, src2, num) : -1);
#define CLX_MEMCHR      return (((const u1*)buf != NULL) ? memchr(buf, c, len) : 0);  

#endif // #if defined(CLX_USE_STD_STRING_H)



#if defined(CLX_USE_STD_STRING_H) && defined(CLX_INLINE)

    CLX_INLINE ClxSize      clxStrLen   (const s1* str)                                { CLX_STRLEN  }
    CLX_INLINE s1*          clxStrCpy   (s1* destination, const s1* source)            { CLX_STRCPY  }
    CLX_INLINE s4           clxStrCmp   (const s1* str1, const s1* str2)               { CLX_STRCMP  }
    CLX_INLINE void*        clxMemCpy   (void* destination, const void* source, u4 n)  { CLX_MEMCPY  }
    CLX_INLINE s4           clxMemCmp   (const void* buf1, const void* buf2, u4 n)     { CLX_MEMCMP  }
    CLX_INLINE void*        clxMemSet   (void* destination, s4 c, u4 count)            { CLX_MEMSET  }
    CLX_INLINE void*        clxMemMove  (void* destination, const void* source, u4 n)  { CLX_MEMMOVE }
    CLX_INLINE const s1*    clxStrChr   (const s1* source, s4 character)               { CLX_STRCHR  }
    CLX_INLINE const s1*    clxStrRChr  (const s1* source, s4 character)               { CLX_STRRCHR } 
    CLX_INLINE const s1*    clxStrStr   (const s1* source, const s1* sub)              { CLX_STRSTR  }
    CLX_INLINE s1*          clxStrNCpy  (s1* destination, const s1* source, s4 num)    { CLX_STRNCPY }
    CLX_INLINE s1*          clxStrCat   (s1* destination, const s1* source)            { CLX_STRCAT  }
    CLX_INLINE s1*          clxStrNCat  (s1* destination, const s1* source, u4 num)    { CLX_STRNCAT }
    CLX_INLINE s4           clxStrNCmp  (const s1* src1, const s1* src2, s4 num)       { CLX_STRNCMP }
    CLX_INLINE const void*  clxMemChr   (const void* buf, s4 c, u4 len)                { CLX_MEMCHR  }

#else

/**
Evaluate the length of a NULL terminated string.
\param str the string to be evaluated.
\return length of the string.
\note The evaluated length does not include the NULL character itself.
*/
extern  u4 clxStrLen( const s1* str );

/**
Copy a string.
\param source source string.
\param destination destination string.
\return \p destination if success, 0 otherwise.
*/
extern  s1* clxStrCpy( s1* destination, const s1* source );

/**
Compare two strings.
\param source source string.
\param destination destination string.
\return 0 if same, the first encountered difference if not the same.
*/
extern  s4 clxStrCmp( const s1* source, const s1* destination );

/**
Copy memory content from one buffer to another.
\param destination destination buffer
\param source source buffer
\param n number of bytes that must be copied.
\return \p destination if success, 0 otherwise.
*/
extern  void* clxMemCpy( void* destination, const void* source, u4 n );

/**
Compare memory contents between two buffers.
\param source source buffer.
\param destination destination buffer.
\param n Number of bytes that must be compared.
\return 0 if same, the first encountered difference if not the same.
*/
extern  s4 clxMemCmp( const void* source, const void* destination, u4 n );

/**
Set memory with a specific byte value.
\param destination memory start address to be set.
\param c byte value to be used to set the memory.
\param count size of the area to be set in bytes.
\return \p destination if success, 0 otherwise.
*/
extern  void* clxMemSet( void* destination, s4 c, u4 count );

/**
Move memory content from one buffer to another.
\param destination destination buffer
\param source source buffer
\param n number of bytes that must be moved.
\return \p destination if success, 0 otherwise.
*/
extern  void* clxMemMove( void* destination, const void* source, u4 n );

/**
Find first occurrence of \p character in \p source string.
\param source Null terminated source string.
\param character character to be searched.
\return Pointer to the found character, 0 if not found.
*/
extern  const s1* clxStrChr( const s1* source, s4 character );

/**
Find last occurrence of \p character in \p source string.
\param source Null terminated source string.
\param character character to be searched.
\return Pointer to the found character, 0 if not found.
*/
extern  const s1* clxStrRChr(const s1* source, s4 character);

/**
Find first occurrence of \p sub string in \p source string.
\param source Null terminated source string.
\param sub Null terminated sub string.
\return Pointer to the first occurrence of the sub string, 0 if not found.
*/
extern  const s1* clxStrStr( const s1* source, const s1* sub );

/**
Copies the first \p num characters of \p source to \p destination.
If the end of the \p source string (which is signalled by a null-character) is
found before num characters have been copied, \p destination is padded with
zeros until a total of \p num characters have been written to it.

No null-character is implicitly appended to the end of \p destination, so
\p destination will only be null-terminated if the length of the string in
\p source is less than num.

\param source string to be copied.
\param destination destination array where the content is to be copied.
\param num maximum number of characters to be copied from source
\return \p destination if success, 0 otherwise.
*/
extern  s1* clxStrNCpy( s1* destination, const s1* source, s4 num );

/**
Concatenate strings.
Appends a copy of the \p source string to the \p destination string.
The terminating null character in \p destination is overwritten by the first
character of \p source, and a new null-character is appended at the end of the
new string formed by the concatenation of both in \p destination.
\param source String to be appended. This should not overlap \p destination.
\param destination String to append to. Shall be large enough to contain the
       concatenated resulting string.
\return \p destination if success, 0 otherwise.
*/
extern  s1* clxStrCat( s1* destination, const s1* source );

/**
Compare two strings.
\param source source string.
\param destination destination string.
\param n number of characters to be compared.
\return 0 if same, the first encountered difference if not the same.
*/
extern  s4 clxStrNCmp( const s1* source, const s1* destination, s4 n );

/**
Append characters from string.
Appends the first \p num characters of \p source to \p destination,
plus a terminating null-character.
If the length of the string in \p source is less than \p num,
only the content up to the terminating null-character is copied.
\param[ in ] destination Destination array, which should contain a string,
             and be large enough to contain the concatenated resulting string,
             including the additional null-character.
\param[ in ] source string to be appended.
\param[ in ] num Maximum number of characters to be appended.
\return \p destination if success, 0 otherwise.
*/
extern  s1* clxStrNCat( s1* destination, const s1* source, u4 num );

/**
Find first occurrence of \p c in \p buffer.
\param buf memory buffer to search in. It doesn't need to be null-terminated. 
\param c character to be searched.
\param len size of buf in bytes.
\return Pointer to the found character, 0 if not found.
*/
extern  const void* clxMemChr(const void* buf, s4 c, u4 len);

#endif // #if defined(CLX_USE_STD_STRING_H) && defined(CLX_INLINE)


/**
Duplicate memory.
\param[ in ] data buffer to be duplicated.
\param[ in ] length size of \p data.
\return A new buffer whose content and size are same those of \p data.
*/
extern  void* clxMemDup( void* data, u4 length );

/**
Compare memory contents between two buffers. Comparison is case insensitive.
\param source source buffer.
\param destination destination buffer.
\param n Number of bytes that must be compared.
\return 0 if same, the first encountered difference if not the same.
*/
extern  s4 clxMemCmpCaseInsensitive ( const void* source, const void* destination, u4 n );

/**
Copies input buffer into output in the reverse order (e.g. The last byte of the input is stored as the first byte of the output, and so on).
*/
extern void clxReverseMemCpy(u1* ret, const u1* input, u4 length);

/**
Duplicate a string.
\param str Null terminated string to be duplicated.
\return A new string with the same content as that in \p str.
*/
extern  s1* clxStrDup( const s1* str );

/**
Find first occurrence of \p str string in \p buf memory buffer of size \p len. The search is case insensitive.
\param buf buffer to search str in.
\param str Null terminated sub string.
\param len size of buf in bytes.
\return Pointer to the first character of the found string inside the buffer, 0 if not found.
*/
extern  const void* clxMemStrCaseInsensitive( const void* buf, const s1* str, u4 len);

/**
Compares two strings. The comparison is case insensitive.

\param[ in ] arg1 First string
\param[ in ] arg2 Second string

\return 0 if strings are same. Otherwise, a non-zero value is returned. 
*/
extern int clxStrCmpCaseInsensitive (const s1* arg1, const s1* arg2);

/**
Compares two strings up to len bytes. The comparison is case insensitive.

\param[ in ] arg1 First string
\param[ in ] arg2 Second string

\return 0 if strings are same. Otherwise, a non-zero value is returned. 
*/
extern int clxNStrCmpCaseInsensitive (const s1* arg1, const s1* arg2, size_t len);

/**
Find last occurrence of \p character in \p source string.
\param source Null terminated source string.
\param character character to be searched.
\return Pointer to the found character, 0 if not found.
*/
extern const s1* clxRStrChr( const s1* source, s4 character );

/**
Find first occurrence of \p sub string in \p source memory buffer.
\param source Memory in which to look for substring.
\param destination Null terminated sub string.
\param sourceLen length of the memory buffer
\return Pointer to the first occurrence of the sub string, 0 if not found.
*/
extern const void* clxMemStr( const void* source, const s1* destination,  u4 sourceLen);

/**
Converts a memory block from hex string (0 to 9, A to F, a to f) to unsigned integer. 

The conversion starts from the left-most character and continues until on the following events occurs:

    - 8 valid hex characters are decoded (e.g. two HEX characters per byte). 
    - An invalid (non-hex) character is encountered
    - End of the buffer is reached.

NOTE : This function will NOT ignore the space characters at the beginning of the string. the string MUST start with the hex characters.
       Optionally, the input may immediately start with a '0x' or '0X' prefix, followed by the hex characters.

This function is the Hex counterpart of atoi() standard function.

\param[ in ] str The NULL-terminated string to parse. This argument CANNOT be NULL.

\return an unsigned integer containing the converted Hex number.
*/
extern u4 clxHexToInteger(const s1* str);

/**
Converts a string to a signed integer. This function behaves the same as the standard atoi() function with the exception that it will NOT ignore the space characters at the beginning of the string.
The valid characters in the string are the minus sign (only as the very first character in the string), and '0' through '9'.
Parsing of the string stops as soon as an invalid character is encountered and the value generated up to that point is returned.

NOTE : If the value in the string does not fit in a s4 variable, the behaviour is undefined.

\param[ in ] str The NULL-terminated string to parse. This argument CANNOT be NULL.

\return the converted value as a signed integer.
*/
extern s4 clxAsciiToInteger(const s1* str);

/**
Converts a string, containing either an unsigned value in hex format or signed value in ASCII format, into a 4-byte unsigned integer value.

    - If the string immediately starts with a "0x" or "0X" prefix, it will assumed to be in hex format. In this case, this function is equivalent to clxHexToInteger().

    - If the string does not start with the "0x" or "0X" prefix, it will assumed to be in ASCII format. In this case, this function is equivalent to clxAsciiToInteger().
      NOTE : If the ASCII value is a negative number, it will be decoded as a singed value but will be cast to an unsigned value and returned.

\param[ in ] str The NULL-terminated string to parse. This argument CANNOT be NULL.

\return the converted value as an unsigned integer.
*/
extern u4 clxAsciiOrHexToUInt(const s1* str);


#if defined(CLX_64BIT_SUPPORT)
/**
Converts a string, containing either an unsigned value in hex format or a signed value in ASCII format, into a 4-byte integer value.

    - If the string immediately starts with a "0x" or "0X" prefix, it will assumed to be in hex format. In this case, this function is equivalent to clxHexToInteger().
      The return value will be a signed 8-byte value in the range [0, 4,294,967,295].

    - If the string does not start with the "0x" or "0X" prefix, it will assumed to be in ASCII format. In this case, this function is equivalent to clxAsciiToInteger().
      The return value will be a signed 8-byte value in the range [-2,147,483,648, 2,147,483,647].

\param[ in ] str The NULL-terminated string to parse. This argument CANNOT be NULL.

\return the converted value as a signed 8-byte integer. 
*/
extern sll clxAsciiOrHexToInt(const s1* str);
#endif

/**
Converts a string to a signed integer. Returns a pointer to the character right after the last numeric character in the input string.
The valid characters in the string are the minus sign (only as the very first character in the string), and '0' through '9'.
Parsing of the string stops as soon as an invalid character is encountered and the value generated up to that point is returned as the second argument.
If there is no invalid character in the string, the return value will point to the NULL character at the end of the string.

\param[ in ] str The NULL-terminated input string to parse. This argument CANNOT be NULL.
\param[ in ] value Pointer to a value of type s4 which will contain the converted signed integer. This argument CANNOT be NULL.

\return Pointer to the character (in the input string) right after the last valid (numeric) character which was converted.
        This pointer will never be NULL (since the input string cannot be NULL).
*/
extern const s1* clxAsciiToIntegerEx(const s1* str, s4* value);


/**
Convert a memory block from binary to ASCII. The result will have a "0x" prefix before the value.

The size of destination must be at least (3 + twice "length")

\param[ out ] destination The destination address which holds the converted ASCII value. The return value on a successful return will be NULL terminated.
\param[ in ] source The source address which contains data in hex format
\param[ in ] length The number of bytes that have to be converted to ASCII.
\return ClxResult code.
\retval CLX_SUCCESS Operation completed successfully.
\return CLX_FAIL clxBinaryToAscii failed.
*/
extern  ClxResult clxBinaryToAscii( s1* destination, const u1* source, u4 length );

/**
This function is exactly the same as clxBinaryToAscii, but the "0x" prefix will not be added to the destination.

The size of destination must be at least (1 + twice "length")
*/
ClxResult clxBinaryToAsciiNoPrefix( s1* destination, const u1* source, u4 length );

/**
Convert a memory block from ASCII to binary.
\param[ in ] destination The destination address which holds the converted hex
             value.
\param[ in ] source The source address which contains data in ASCII format.
\param[ in ] length The source length, in bytes.
\return ClxResult code.
\retval CLX_SUCCESS Operation completed successfully.
\retval CLX_FAIL clxAsciiToBinary failed.
*/
extern  ClxResult clxAsciiToBinary( u1* destination, const u1* source, s4 length );

/**
Converts an english alphabet character (a..z, A..Z) to uppercase. Non-english alphabet characters will be returned as is. 

\param[ in ] c the english alphabet character to be converted to uppercase.
\return The uppercase character (in case an of english alphabet). Same as c, otherwise.
*/
extern s1 clxToUpper(s1 c);

/**
Converts an english alphabet character (a..z, A..Z) to lowercase. Non-english alphabet characters will be returned as is. 

\param[ in ] c the english alphabet character to be converted to lowercase.
\return The lowercase character (in case an of english alphabet). Same as c, otherwise.
*/
extern s1 clxToLower(s1 c);

/**
Converts all characters in a string to uppercase characters.

\param[ in ] s the string to be converted to uppercase.
\return The same as s. This function changes the characters in the original buffer.
No new buffer will be created.
*/
extern  s1* clxStrUpr (s1* s);

/**
Converts all characters in a string to lowercase characters.

\param[ in ] s the string to be converted to lowercase.
\return The same as s. This function changes the characters in the original buffer.
No new buffer will be created.
*/
extern  s1* clxStrLwr (s1* s);

/**
Determines if the argument is a valid numeric character (0..9

\param[ in ] c The character
\return TRUE if this is a valid numeric character. FALSE otherwise.
*/
extern boolean clxIsDigit(s1 c);


/**
Determines if the argument is a valid HEX character (0..9, a..f, A..F)

\param[ in ] c The character
\return TRUE if this is a valid HEX character. FALSE otherwise.
*/
extern boolean clxIsXDigit(s1 c);


/**
Splits a string into sub-strings by a delimiter string.
Refer to https://linux.die.net/man/3/strtok_r for details.
*/
extern s1* clxStrtok_r(s1* str, const s1* delimiters, s1** ctx);


/**
Strips a string of leading and trailing space and tab characters. The string must be modifiable (e.g. non-constant), as the string will be directly modified.

\param [ in ] str The buffer containing the string. The string will be modified in the same buffer.

\return point to the stripped string. This will be NULL only if the provided string has been NULL.
*/
extern s1* clxStripString(s1* str);


/**
Converts a big endian UCS2-formatted (two-bytes-per-character) ASCII string into normal single-byte-per-character representation.

\param[ in ] ucs2String A string of characters in UCS2 big endian format. The string is not null terminated.
\param[ in ] ucs2StringLength The length of ucs2String in bytes (NOT characters).
\param[ out ] asciiString A caller provided buffer into which to store the ASCII string. The size of this buffer
must be at least half of ucs2StringLength plus one byte for null character (ucs2StringLength/2 + 1). The result will be
null-terminated.

ret If TRUE the conversion was done successfully.
     If FALSE, the string stored in ucs2String is in big endian UCS2 format. 
*/
boolean convertUCS2BEToASCII( const u1* ucs2String, u4 ucs2StringLength, u1* asciiString);

/**
Converts a little endian UCS2-formatted (two-bytes-per-character) ASCII string into normal single-byte-per-character representation.

\param[ in ] ucs2String A string of characters in UCS2 little endian format. The string is not null terminated.
\param[ in ] ucs2StringLength The length of ucs2String in bytes (NOT characters).
\param[ out ] asciiString A caller provided buffer into which to store the ASCII string. The size of this buffer
must be at least half of ucs2StringLength plus one byte for null character (ucs2StringLength/2 + 1). The result will be
null-terminated.

ret If TRUE the conversion was done successfully.
     If FALSE, the string stored in ucs2String is in little endian UCS2 format. 
*/
boolean convertUCS2LEToASCII( const u1* ucs2String, u4 ucs2StringLength, u1* asciiString);

/** \file ClxStandard.h
    \brief Provides the standard function support for consistent execution.
*/

/**
Specifies the command line arguments which need to be parsed.
The arguments are separated by spaces. An argument CANNOT contain a space character unless it is enclosed in a pair of double quotes.

NOTE : A tab character cannot be used to separate the arguments.

Example:

arg1 some_arg "this is all one argument" last-arg

The arguments are:

- arg1

- some_arg

- this is all one argument

- last-arg
*/
struct ClxCommandLineArguments
{
	s1* str;
};

/**
Returns the next argument in the command line. This function adds a NULL termination character (\0) at the end of the argument.

\param[ in ] input The command line argument. This function will change input->str if required.

\return Pointer to the next NULL-terminated argument in the input, or NULL if no other argument exists in the input.
*/
extern const s1* clxCommandLineArguments_parseNext(struct ClxCommandLineArguments* input);


#ifdef __cplusplus
}
#endif


#endif    // ClxStandard_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused type declarations 	  */
/* Rule          : MISRA-C:2012 Rule 2.3                                      */ 
/* Justification : Unused type declarations are to be used in user 		      */
/* 				   applications.      										  */
/******************************************************************************/
