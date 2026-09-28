#ifndef ClxBspOsTimer_h
#define ClxBspOsTimer_h

/******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxBspOsTimer.h
* Description         Declares ClxOsTimer related
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
A type for holding the timer handle for the current operating system.
Clarinox Timer APIs use this timer handle for most of the timer operations.
*/
typedef void* ClxOsTimer;


/**
Clx Timer reload options
*/
typedef enum ClxOsTimerType_Enum
{
    ClxOsTimerType_OneShot,           /*!< Create one shot timer. Timer will be in the dormant state after it expires. */
    ClxOsTimerType_Periodic           /*!< Create a periodic timer. Timer will auto-reload after it expires. */
} ClxOsTimerType;


typedef void (*ClxOsTimerCallbackFunc)(void* data);


/**
Creates a new timer. The timer handle is returned with the timer parameter.

\param[ out ] *timer An internal Clarinox-specific handle to the timer. With this value, the timer can be controlled via other APIs.

\param[ in ] name Name of the new timer as a null-terminated UTF-8 string.

\param[ in ] period The period value of the new timer is in milliseconds.

\param[ in ] callbackFunc The callback function to be called when the timer expires.

\param[ in ] callbackData The value of void* passed as the only argument to the callback function. This value may be NULL.

\param[ in ] type Determines whether the timer will work periodically or as a one-shot.

\return CLX_SUCCESS if the timer creation has been successful.
*/
extern ClxResult clxBspOsTimerCreate(ClxOsTimer*            timer,
                                     const char*            name,
					                 u4                     period,
					                 ClxOsTimerCallbackFunc callbackFunc,
                                     void*                  callbackData,
                                     ClxOsTimerType         type);


/**
This function starts a created timer.
\param[ in ] timer is the handle for the timer
\return status
\retval CLX_SUCCESS Operation completed successfully.
*/
extern ClxResult clxBspOsTimerStart(ClxOsTimer timer);



/**
This function checks if timer is running.
\param[ in ] timer is the handle for the timer
\return status
\retval TRUE timer is running.
*/
extern boolean clxBspOsTimerIsRunning(ClxOsTimer timer);


/**
Re-starts a timer that was previously created. If the timer had already been started and was already in the active state,
then clxTimerReset() will cause the timer to re-evaluate its expiry time so that it is relative to when clxTimerReset() was called.
If the timer was in the dormant state then clxTimerReset() has equivalent functionality to the clxTimerActivate() API function.
\param[ in ] timer is the handle for the timer
\param[ in ] newPeriod The new period for the timer. If set to 0, the last period value will be used.
\return status
\retval CLX_SUCCESS Operation completed successfully.
*/
extern ClxResult clxBspOsTimerRestart(ClxOsTimer timer, u4 newPeriod);


/**
This function stops a timer that was previously started.
\param[ in ] timer is the handle for the timer
\return status
\retval TRUE timer is running.
*/
extern ClxResult clxBspOsTimerStop(ClxOsTimer timer);


/**
This function deletes a timer that was previously created.
\param[ in ] timer is the handle for the timer
\return status
\retval TRUE timer is running.
*/
extern ClxResult clxBspOsTimerDelete(ClxOsTimer timer);

#ifdef __cplusplus
}
#endif


#endif    // ClxBspOsTimer_h
