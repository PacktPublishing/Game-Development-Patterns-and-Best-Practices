/******************************************************************************/
/*!
\file   M5Debug.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/6


This file contains the prototyes for the Debug functions and Macros.

*/
/******************************************************************************/
#ifndef M5_DEBUGTOOLS_H
#define M5_DEBUGTOOLS_H

#include "M5Gfx.h"

//! Tools used to help debug the game
namespace M5Debug
{
/*These functions should NOT be called!!!! USE THE MACROS!!!! */
bool Assert(bool expression, const char* outputMessage,
  const char* fucntionName, const char* fileName,
  unsigned lineNumber);
void CreateConsole(void);
void DestroyConsole(bool finalDestroy = false);
void ClearScreen(void);
void TestResult(bool expression, const char* testName);

/*This should only be called for IMPORTANT MESSAGES to the user
Really STUDENTS probably don't need it!!! */
int MessagePopup(const char* outputMessage);
}




/*Macros for debug only!!!*/
#if defined(DEBUG) | defined(_DEBUG)
/*! Used to exclude rarely-used stuff from Windows */
#define WIN32_LEAN_AND_MEAN 
#include <windows.h> /*DebugBreak*/
#include <cstdio>
#include <cstdlib>
/*! Use this macro instead of the function to print to the console in debug
only*/
#define M5DEBUG_PRINT(...) printf(__VA_ARGS__)
/*! Use this macro instead of the function to clear the console in debug only*/
#define M5DEBUG_CLEAR() M5Debug::ClearScreen()
/*! Use this macro instead of the function to ASSERT in debug only*/
#define M5DEBUG_ASSERT(exp, str) if(M5Debug::Assert((exp),(str),      \
  __FUNCTION__,__FILE__, __LINE__)) {DebugBreak();}         
/*!Use this macro instead of the function to create a console in debug only*/
#define M5DEBUG_CREATE_CONSOLE() M5Debug::CreateConsole();
/*!Use this macro instead of the function to destroy a console in debug only*/
#define M5DEBUG_DESTROY_CONSOLE() M5Debug::DestroyConsole();
/*! Use this macro to draw debug text on the screen*/
#define M5DEBUG_WRITETEXT(text, x, y) M5Gfx::WriteText((text),(x), (y))
/*!Use this to test your code in debug only*/
#define M5DEBUG_TEST(exp, str) M5Debug::TestResult((exp), (str))
/*! If you have a leak, there is a number in curly braces next to the error.
Put that number in this function and check the call stack to see when and
where the allocation happened. Set it to -1 to have it not break.*/
#define M5DEBUG_LEAK_CHECKS(x) \
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);\
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);\
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);\
  _CrtSetBreakAlloc((x));

/*!Use this to make sure a function is only called one time*/
#define M5DEBUG_CALL_CHECK(x)\
  static int functionCounter = 0;\
  ++functionCounter;\
  M5DEBUG_ASSERT(functionCounter==(x),"This function should be called only once.");
#else
/*! Use this macro instead of the function to print to the console in debug
only*/
#define M5DEBUG_PRINT(...)
/*! Use this macro instead of the function to clear the console in debug only*/
#define M5DEBUG_CLEAR()
/*! Use this macro instead of the function to ASSERT in debug only*/
#define M5DEBUG_ASSERT(expression, outputMessage)
/*!Use this macro instead of the function to create a console in debug only*/
#define M5DEBUG_CREATE_CONSOLE()
/*!Use this macro instead of the function to destroy a console in debug only*/
#define M5DEBUG_DESTROY_CONSOLE()
/*! Use this macro to draw debug text on the screen*/
#define M5DEBUG_WRITETEXT(text, x, y)
/*!Use this to test your code in debug only*/
#define M5DEBUG_TEST(exp, str) 
/*! If you have a leak, there is a number in curly braces next to the error.
Put that number in this function and check the call stack to see when and
where the allocation happened. Set it to -1 to have it not break.*/
#define M5DEBUG_LEAK_CHECKS(x)
/*!Use this to make sure a function is only called one time*/
#define M5DEBUG_CALL_CHECK(x)
#endif


#endif