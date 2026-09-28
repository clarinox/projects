#ifndef ClxMailBox_h
#define ClxMailBox_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxMailBox.h
* Description         OS-independent implementation of Thread MailBox
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


typedef void* ClxMailBox;


extern ClxMailBox clxCreateMailBox( u1 queueSizeInBits );

extern  ClxResult       clxTerminateMailBox  ( ClxMailBox mailBox );

extern  void            clxDeleteMailBox     ( ClxMailBox mailBox );

extern  ClxResult       clxPostToMailBox     ( ClxMailBox mailBox, void* msg );

extern  ClxResult       clxTryPostToMailBox  ( ClxMailBox mailBox, void* msg );

extern  ClxResult       clxFetchFromMailBox  ( ClxMailBox mailBox, void** msg , u4 timeout );

extern  ClxResult       clxTryFetchFromMailBox  ( ClxMailBox mailBox, void** msg );

#ifdef __cplusplus
}
#endif

#endif    // ClxMailBox_h

