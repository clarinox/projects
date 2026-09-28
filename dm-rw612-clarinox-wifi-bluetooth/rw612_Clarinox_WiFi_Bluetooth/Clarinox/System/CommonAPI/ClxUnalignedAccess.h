#ifndef ClxUnalignedAccess_h
#define ClxUnalignedAccess_h

/*******************************************************************************
*
* Project           Clarinox SoftFrame
* File              ClxUnalignedAccess.h
* Description       Unaligned Memory Write and Read functions
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


#if defined(CLX_64BIT_SUPPORT)
/**
reads a 64bit value from an unaligned memory address.

\param[ in ] buffer a pointer to a buffer which contains a 64bit number. The address of the buffer may
not be 8-byte aligned.

\return The 64bit value as an u4 variable.
*/
extern  ull               readFromUnaligned64       ( const void* buffer );
#endif

/**
reads a 32bit value from an unaligned memory address.

\param[ in ] buffer a pointer to a buffer which contains a 32bit number. The address of the buffer may
not be 4-byte aligned.

\return The 32bit value as an u4 variable.
*/
extern  u4               readFromUnaligned       ( const void* buffer );

/**
reads a 16bit value from an unaligned memory address.

\param[ in ] buffer a pointer to a buffer which contains a 16bit number. The address of the buffer may
not be 4-byte aligned.

\return The 16bit value as an u2 variable.
*/
extern  u2               readFromUnaligned16     ( const void* buffer );

#if defined(CLX_64BIT_SUPPORT)
/**
writes a 64bit value to an unaligned memory address.

\param[ in ] value a 64bit value which will be written in \e buffer.
\param[ out ] buffer a pointer to a buffer which on return will contain \e value. The address of the buffer may
not be 8-byte aligned.
*/
extern  void             writeToUnaligned64        ( ull value, void* buffer );

#endif

/**
writes a 32bit value to an unaligned memory address.

\param[ in ] value a 32bit value which will be written in \e buffer.
\param[ out ] buffer a pointer to a buffer which on return will contain \e value. The address of the buffer may
not be 4-byte aligned.
*/
extern  void             writeToUnaligned        ( u4 value, void* buffer );

/**
writes a 16bit value to an unaligned memory address.

\param[ in ] value a 16bit value which will be written in \e buffer.
\param[ out ] buffer a pointer to a buffer which on return will contain \e value. The address of the buffer may not be
4-byte aligned.
*/
extern  void             writeToUnaligned16      ( u2 value, void* buffer );


#ifdef __cplusplus
}
#endif


#endif // ClxUnalignedAccess_h
