/******************************************************************************/
/*!
\file   Main.cpp
\author Matt Casanova 
\par    email: lazersquad@gmail.com
\par    Simple 2D Game Engine
\date   2012/11/26

This is file contains the main function to make a basic window. 
*/
/******************************************************************************/
/* These are necessary includes to do any memory leak detection ***************/
/*This should always  be the first code in your file*/
#if defined(DEBUG) | defined(_DEBUG) 
#define CRTDBG_MAP_ALLOC 
#include <cstdlib>
#include <crtdbg.h>
#endif 
/******************************************************************************/

#include <windows.h> /*WinMain*/ 

/*Include the engine functions*/
#include "Core\M5App.h"
#include "Core\M5StageManager.h"
#include "Core\M5Stage.h"
#include "Core\M5GameData.h"
#include "RegisterStages.h"
#include "RegisterComponents.h"
#include "Core\M5IniFile.h"

#include "Core\M5Debug.h"

/******************************************************************************/
/*!

\brief
The main function for a windowed program.

\param instance 
An identifier for the process.  This is used for various windows things.

\param prev
This is not used anymore, we can ignore it.

\param comamndLine
A string that is comes from the typed command line.  In games we usually don't
care.

\param show 
A variable stating if the window is visible, we always want it visible.

\return
An Error code.  Just return 0;
*/
/******************************************************************************/
#pragma warning(suppress: 28251)
int WINAPI WinMain(HINSTANCE instance,
                   HINSTANCE /*prev*/, 
                   LPSTR /*commandLine*/, 
                   int /*show*/)
{
  /*This should appear at the top of winmain to have windws find memory leaks*/
  M5DEBUG_LEAK_CHECKS(-1);

  M5InitData initData;          /*Declare my InitStruct*/
  M5GameData gameData = { 0 };  /*Create my game data initial values*/
  M5IniFile iniFile;            /*To load my init data from file*/

  iniFile.ReadFile("GameData/InitData.ini");
  iniFile.SetToSection("InitData");

  /*Set up my InitStruct*/
  iniFile.GetValue("width", initData.width);
  iniFile.GetValue("height", initData.height);
  iniFile.GetValue("framesPerSecond", initData.fps);
  iniFile.GetValue("fullScreen", initData.fullScreen);
  
  initData.title        = "AstroShot";
  initData.instance     = instance;
  /*Information about your specific gamedata */
  initData.pGData       = &gameData;
  initData.gameDataSize = sizeof(M5GameData);

  /*Pass InitStruct to Function.  This function must be called first!!!*/
  M5App::Init(initData);
  
  /*Make sure to add what stage we will start in*/
  M5StageManager::SetStartStage(ST_SplashStage);

  /*Start running the game*/
  M5App::Update();
  /*This function must be called after the window has closed!!!*/
  M5App::Shutdown();
  
  return 0;
}

