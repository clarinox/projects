#ifndef wlan_wpa_supplicant_bsp_h
#define wlan_wpa_supplicant_bsp_h

/*******************************************************************************
*
* Project             WPA Supplicant Port
* File                Wlan.WpaSupplicant.Bsp.h
* Description         BSP layer for port of WPA Supplicant to ClarinoxWLAN
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#if defined(CLX_WPA_SUPPLICANT)

#ifdef __cplusplus
extern "C" {
#endif
  


/**
Called during the initialization of WPA Supplicant. Any BSP-related initialization can be placed in the implementation of this function.
If the implementation returns an error, the initialization WPA Supplicant will fail with the same error code.

\return CLX_SUCCESS If successful.
        Any other value indicates an error.
*/
extern ClxResult clxWpaSupplicantBsp_Init(void);


/**
Called when WPA Supplicant is being terminated.
*/
extern void clxWpaSupplicantBsp_Destroy(void);


/** 
Allocates a buffer and returns a pointer to it.

\param[ in ] size Size, in bytes, of the buffer to be allocated.

\return Pointer to the allocated buffer, or NULL if the buffer could not be allocated.
*/
extern void* clxWpaSupplicantBsp_Alloc(size_t size);


/**
Frees a buffer previously allocated by a call to #clxWpaSupplicantBsp_Alloc().

\param[ in ] ptr Pointer to the buffer to be freed.
*/
extern void clxWpaSupplicantBsp_Free(void *ptr);


/**
Resizes a buffer which has previously been allocated by a call to #clxWpaSupplicantBsp_Alloc().

\param[ in ] ptr Pointer to the buffer to be resized.
\param[ in ] size The new size of the buffer.

\return The pointer to the re-sized buffer. Could be the same as ptr. 
NULL if the buffer could not be resized. In this case, the original buffer will NOT be freed.
*/
extern void* clxWpaSupplicantBsp_Realloc(void *ptr, size_t size);



#ifdef __cplusplus
}
#endif

#endif // CLX_WPA_SUPPLICANT

#endif // wlan_wpa_supplicant_bsp_h




