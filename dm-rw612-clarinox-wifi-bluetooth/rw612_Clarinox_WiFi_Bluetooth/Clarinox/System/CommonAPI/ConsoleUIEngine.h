#ifndef UIEngine_h
#define UIEngine_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ConsoleUIEngine.h
* Description         ConsoleUIEngine.h file
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
Console UIEngine provides a very simple console-based thread-safe user interface, including inputs, prompts, and menus. 
*/


/**
Initializes the UI engine. The engine starts a thread to capture key strokes. Key strokes are
emitted to other threads based on the priority of the UI activity being performed on each thread.
The UI activity priorities are as follows (the highest priority first):

    - Text : Has the higher priority. It will print the text right away, regardless of the status
                of other threads.
    - InputBox and MessageBox : If two or more threads start a InputBox or MessageBox at the same time,
                                the keyboard control is passed to the most recent InputBox or MessageBox.
    - Menu : A menu cannot be shown when an activity of higher priority is active. When active, a
                menu can be interrupted by an inputbox, messagebox or text. The menu items cannot be selected
                until the higher priority activity finishes. Afterwards, the menu will automatically become
                active again.
    - Background Text : An attempt to send a text to the console will block if there is any higher priority
                activity running at the moment. The text will be shown only after the higher priority
                activity has finished.
    
NOTE : This module calls the BSP function userPrintfFunction() when any character needs to be written to the output. If this
function is not implemented by the application, the default "printf" function of the underlying platform will be called.
Similarly, this module calls the BSP function userGetInputFunction() when any character needs to be read from the input. If this
function is not implemented by the application, the default "scanf" function of the underlying platform will be called.

\param[ in ] maxInputSize The maximum size of the input which can be entered by the user. This is the size
of the internal buffer which is used to store the user's input. This size excludes the null-termination character.
*/
void clxConsoleUIEngineInit(ClxSize maxInputSize);

/**
Destroys the UI engine.  
*/
void clxConsoleUIEngineDestroy(void);

/**
Sends a text message, formatted in printf style, to the console output. This function has the highest
priority and prints the text immediately, regardless of the status of other threads.
*/
void clxConsoleUIEngineText (const s1 * format, ... );


/**
Shows a message in the console output, and waits for the user's input.

\param[ in ] message The message to be shown to the user.
\param[ out ] inputBuffer The caller-allocated buffer which will contain the user's entered text when
this function returns. The returned text will be null-terminated.
\param[ in ] inputBufferLen the size of the caller-provided buffer. The maximum length of the string
the user can enter is inputBufferLen - 1 (one byte is reserved for null-termination).
*/
void clxConsoleUIEngineInputBox (const s1* message, s1* inputBuffer, u4 inputBufferLen);

/**
Shows a prompt to the user, and waits for the user to press a key. The user needs to press ENTER after entering
the key. The function will not return until one of the characters (keys) provided in the list of accepted characters
is entered by the user.

\param[ in ] message The prompt message to be shown to the user.
\param[ in ] acceptedCharsList The list of characters which can be entered by the
user as the selection.
\param[ in ] numOfAcceptedChars Number of characters in acceptedCharsList.
    
\return The character which has entered by the user. 
*/
s1 clxConsoleUIEngineMessageBox (const s1* message, const s1* acceptedCharsList, u4 numOfAcceptedChars);

/**
Shows a simple console-based menu to the user, and waits until one of the menu items is selected.

\param[ in ] menuTitle The title of the input, as a null-terminated string. Can be NULL.
\param[ in ] menuItemsList The list of all menu items, concatenated together in a single buffer.
Each item in the buffer MUST be terminated by the null character (ASCII character 0). NOTE THAT
THIS IS NOT AN ARRAY OF MENU ITEMS AS SEPARATE BUFFERS, BUT A SINGLE BUFFER CONTAINING THE MENU ITEMS, EACH
TERMINATED BY NULL CHARACATER (INCLUDING THE LAST ITEM).
\param[ in ] numberOfMenuItems The number of items stored in menuItemsList.
    
\return the selected item, as an one-based index (the first item has index 1, and so on).
*/
u4 clxConsoleUIEngineShowMenu(const s1* menuTitle, const s1* menuItemsList, u4 numberOfMenuItems);


#ifdef __cplusplus
}
#endif



#ifdef __cplusplus

/**
DEPRECATED: For Backward compatibility with old code only:
*/
namespace ClxConsoleUIEngine
{
    /* Same as clxConsoleUIEngineInit */
    void init(ClxSize maxInputSize);

    /* Same as clxConsoleUIEngineDestroy */
    void destroy();

    /* Same as clxConsoleUIEngineText */
    void text (const s1 * format, ... );

    /* Same as clxConsoleUIEngineInputBox */
    void inputBox (const s1* message, s1* inputBuffer, u4 inputBufferLen);

    /* Same as clxConsoleUIEngineMessageBox */
    s1 messageBox (const s1* message, const s1* acceptedCharsList, u4 numOfAcceptedChars);

    /* Same as clxConsoleUIEngineShowMenu */
    u4 showMenu(const s1* menuTitle, const s1* menuItemsList, u4 numberOfMenuItems);
}

#endif // __cplusplus



#endif // UIEngine_h

