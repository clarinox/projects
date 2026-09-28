#ifndef ClxTime_h
#define ClxTime_h

/******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxTime.h
* Description         Declares ClxTime related
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
A structure to hold time of day details
*/
struct ClxFullTime {
    u1 sec;
    u1 min;
    u1 hour;
    u1 day;
    u1 month;
    u2 year;
    u1 dayOfWeekSinceSun;
};

/**
A structure to provide the Time value in seconds and microseconds
*/
struct ClxTimeval {
    u4 tv_sec;    // time value seconds
     u4 tv_usec;    // time value micro seconds
};

typedef struct ClxTimeoutStruct
{
    u4 startTime;
    u4 value;
} ClxTimeout;

/**
Sleeps for the given amount of time.
\param[ in ] milliseconds is the amount of time to sleep in milliseconds.
*/
extern  void         clxSleep                    ( u4 milliseconds );


/**
Sleeps for the given amount of time.
\param[ in ] microseconds is the amount of time to sleep in microseconds.
*/
extern void          clxUSleep					 ( u4 microseconds );

/**
Reads the tick time in milliseconds
\return the number of seconds since the OS was started.
*/
extern  u4           clxTickTime                 ( void );

/**
Reads the tick time in milliseconds.
Clarinox stack does not utilize this function, hence it is provided for application portability.
\param[ in ] previousTick if set to 0 then the internal difference counter is used, if set to a non-zero value, then user supplied difference counter will be used.
\return the number of seconds since the OS was started (or previousTick value) in ASCII format.
*/
extern  const char*  clxTickTimeFormatted        ( u4* previousTick );

/**
Reads the high resolution tick time in microseconds (some platforms do not provide the high resolution time).
This function is mandatory for ClarinoxWLAN stack and must return tick time in microseconds precision. 
\return the high resolution tick time in microseconds
*/
extern  u4           clxHighResolutionTime       ( void );

/**
Reads the current time into an ASCII string
Clarinox stack does not utilize this function, hence it is provided for application portability.
\param[ out ] t[ 18 ] is a buffer for the date-time as string
(yyyymmdd hh:mm:ss) to be written into.
*/
extern  void         clxGetCurrentTimeFormatted  ( s1 t[ 18 ] );

/**
Reads the current time into the ClxTimeval structure.
Clarinox stack does not utilize this function, hence it is provided for application portability.
\param[ out ] currentTime is a ClxTimeval structure to read the current time. \sa ClxTimeval
*/
extern  void         clxGetCurrentTime           ( struct ClxTimeval* currentTime );

/**
Reads the current date of time from the Operating System.
Clarinox stack does not utilize this function, hence it is provided for application portability.
\return the current date as an unsigned 4 byte value (yyyymmdd)
*/
extern  u4           clxGetCurrentDate           ( void );

/**
Returns a ClxTimeout object which represents a timeout value starting from the time this function is called.
The ClxTimeout may be passed to any API functions which take ClxTimeout objects as an argument.
*/
extern ClxTimeout    clxStartTimeout(u4 timeoutValue);

// _____________________________________________________________________________
//
// ClxTime
// _____________________________________________________________________________
//

/**
    Time functionality. Tick time is used in various time stamp and time measurement functions within the Clarinox libraries.
    Tick time is in millisecond resolution and targeting soft real-time systems.
    There is a high resolution (nanoseconds) tick time function prototype is provided for convenience,
    but this function is never used in Clarinox libraries.
    In fact only clxTickTime and clxSleep functions are used by Clarinox libraries.
*/

#ifdef __cplusplus
}
#endif


#endif    // ClxTime_h

/******************************************************************************/ 
/* 1. MISRA C 2012 RULE VIOLATION:                                            */ 
/* Message       : A project should not contain unused tag declarations. 	  */
/* Rule          : MISRA-C:2012 Rule 2.4                                      */ 
/* Justification : Tag declarations are available to be used in user		  */ 
/*				   applications.    										  */
/******************************************************************************/
