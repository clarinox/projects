#ifndef ClxDataConversion_h
#define ClxDataConversion_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxDataConversion.h
* Description         Clarinox Type conversion
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
ClxUnicodeToChar - Simple Unicode to char function.
\param c Destination (char)
\param uc Source (Unicode)
\param size Length of destination buffer, at least half the size of source
\return buffers may not overlap and -1 on error.
*/
extern int ClxUnicodeToChar(s1 *c, const s1 *uc, int size);

/**
ClxCharToUnicode - Simple char to Unicode function.
\param uc Destination (Unicode)
\param c Source (char)
\param size Length of destination buffer, at least twice the size of source
\return buffers may not overlap and -1 on error.
 */
extern int ClxCharToUnicode(s1 *uc, const s1 *c, int size);

#ifdef __cplusplus
}
#endif


#endif    // ClxDataConversion_h
