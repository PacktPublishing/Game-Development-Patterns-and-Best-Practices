/******************************************************************************/
/*!
file    M5Debug.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/6

This file contains the definition for the Debug functions and Macros.
*/
/******************************************************************************/
#include "M5Debug.h"

#define WIN32_LEAN_AND_MEAN 
#include <windows.h> /*DebugBreak*/

#include <sstream>
#include <cstring>
#include <cstdio>


namespace
{
//!< Flag to know if a debug console has been created or not
bool s_hasConsole = false;
}

namespace M5Debug
{
/******************************************************************************/
/*!
This function is used to force a crash if a certain condition isn't met.  This
should be used by programmers to make sure a condition is true.  This will
only work in DEBUG mode.  In Release mode the code is removed.  This function
should not be called.  Call the macro defined in the h file instead.

\attention
Dont call this function.  Use M5ASSERT(expression, outputMessage);!!!

\param expression
The expression to test.  If it is false the program will crash.

\param outputMessage
The message to tell the user.

\param functionName
The name of the function that the Assert was located in.

\param fileName
The name of the file that the Assert was located in.

\param lineNumber
The line number the of the Assert.

\return
TRUE if the expression was false and the user clicks yes.  False if the
expression is true.
*/
/******************************************************************************/
bool Assert(bool expression, const char* outputMessage,
	const char* functionName,
	const char* fileName,
	unsigned lineNumber)
{
#if defined(DEBUG) | defined(_DEBUG)
	if (!expression)
	{
		std::stringstream ss;

		/*Set output message*/
		ss << "ASSERTION FAILURE:";
		ss << "\nFile: ";
		ss << fileName;
		ss << "\nLine: ";
		ss << lineNumber;
		ss << "\nFunction: ";
		ss << functionName;
		ss << "\n\n Description: ";
		ss << outputMessage;
		ss << "\n\nYES: Break into the Debugger.";
		ss << "\nNO: Exit immediately";

		/*display a message to the user*/
		int result = MessageBox(NULL, ss.str().c_str(), "ASSERT!",
			MB_TASKMODAL | MB_SETFOREGROUND | MB_YESNO | MB_ICONERROR);

		if (result == IDYES)
			return true;

		ExitProcess((unsigned)(-1));

	}
	return false;
#else
	//In release mode do nothing
	expression;
	outputMessage;
	functionName;
	fileName;
	lineNumber;

#endif
}
/******************************************************************************/
/*!
This will create a Yes No message box with the given output message.  This
should only be used for critical reasons, such as explaining to the user why
the game must exit.

\attention
This function will be called in Debug and Release mode.

\param outputMessage
The message to say in the message box

\return
True if the user clicks yes, false otherwise.

*/
/******************************************************************************/
int MessagePopup(const char* outputMessage)
{
#if defined(DEBUG) | defined(_DEBUG)
	int result = MessageBoxA(0, outputMessage, "Important Message!",
		MB_SYSTEMMODAL | MB_SETFOREGROUND | MB_YESNO | MB_ICONERROR | MB_DEFAULT_DESKTOP_ONLY);

	return (result == IDYES);
#else
	//In release mode do nothing
	outputMessage = 0;
	return 0;
#endif
}
/******************************************************************************/
/*!
This will create a console window for debug printing.  Do NOT call this
function, use the macro instead.

\attention
Do NOT Call this function.  M5DEBUG_CREATE_CONSOLE();

*/
/******************************************************************************/
void CreateConsole(void)
{
#if defined(DEBUG) | defined(_DEBUG)
	if (s_hasConsole == false)
	{
		FILE* pFile;
		AllocConsole();

		freopen_s(&pFile, "CONOUT$", "wt", stdout);
		freopen_s(&pFile, "CONOUT$", "wt", stderr);
		SetConsoleTitle("Debug Console");
		s_hasConsole = true;
	}

#else
	//In release mode do nothing
#endif
}
/******************************************************************************/
/*!
This will destroy the console window for debug printing.  Do NOT call this
function, use the macro instead.

\attention
Do NOT Call this function.  M5DEBUG_DESTROY_CONSOLE();

*/
/******************************************************************************/
void DestroyConsole(void)
{
#if defined(DEBUG) | defined(_DEBUG)
	if (s_hasConsole == true)
	{
		FreeConsole();
		s_hasConsole = false;
	}
	
#else
	//In release mode do nothing
#endif
}
/******************************************************************************/
/*!
This function clears the console screen.

\attention
Do NOT Call this function.  M5DEBUG_CLEAR();

*/
/******************************************************************************/
void ClearScreen(void)
{
#if defined(DEBUG) | defined(_DEBUG)
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hStdout;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// Fill the entire screen with blanks.
	if (!FillConsoleOutputCharacter(hStdout,       // Handle to console screen buffer 
		' ',                                         // Character to write to the buffer
		dwConSize,                                   // Number of cells to write 
		coordScreen,                                 // Coordinates of first cell 
		&cCharsWritten))                             // Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;

	// Set the buffer's attributes accordingly.
	if (!FillConsoleOutputAttribute(hStdout,    // Handle to console screen buffer 
		csbi.wAttributes,                         // Character attributes to use
		dwConSize,                                // Number of cells to set attribute 
		coordScreen,                              // Coordinates of first cell 
		&cCharsWritten))                          // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.
	SetConsoleCursorPosition(hStdout, coordScreen);
#else
	//in release mode do nothing
#endif
}
/******************************************************************************/
/*!
This function can be used to easily test your code in debug or release mode.

\attention
If you want this to run in only Debug, use M5DEBUG_TEST macro

\param expression
The expression to test.

\param testName
The name of the test that will print.

*/
/******************************************************************************/
void TestResult(bool expression, const char* testName)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	printf("%-20s:", testName);
	if (expression)
	{
		SetConsoleTextAttribute(hstdout, 0x0A);
		printf("Passed\n");
	}
	else
	{
		SetConsoleTextAttribute(hstdout, 0x0C);
		printf("FAILED\n");
	}

	/*Reset console*/
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
}
}//end namespace M5Debug

