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
#include <string>

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
  /*This should appear at the top of winmain to have windows find memory leaks*/
  M5DEBUG_LEAK_CHECKS(-1);

  M5InitData initData;  /*Declare my InitStruct*/
  M5GameData gameData;  /*Create my game data initial values*/
  M5IniFile iniFile;    /*To load my init data from file*/
  std::string title;
  std::string startStage;

  iniFile.ReadFile("GameData/InitData.ini");
  iniFile.SetToSection("InitData");

  /*Set up my InitStruct*/
  iniFile.GetValue("width", initData.width);
  iniFile.GetValue("height", initData.height);
  iniFile.GetValue("framesPerSecond", initData.fps);
  iniFile.GetValue("fullScreen", initData.fullScreen);
  iniFile.GetValue("title", title);
  iniFile.GetValue("startStage", startStage);

  gameData.menuFile = startStage + ".ini";

  iniFile.SetToSection("GameData");
  /*Set up Starting Game data*/
  iniFile.GetValue("startLevel", gameData.level);
  iniFile.GetValue("maxLevel", gameData.maxLevels);
  

  //Other init data 
  initData.title        = title.c_str();
  initData.instance     = instance;
  initData.pGData       = &gameData;

  /*Pass InitStruct to Function.  This function must be called first!!!*/
  M5App::Init(initData);
  
  /*Make sure to add what stage we will start in*/
  M5StageManager::SetStartStage(StringToStage(startStage));
  /*Start running the game*/
  M5App::Update();
  /*This function must be called after the window has closed!!!*/
  M5App::Shutdown();
  
  //Save the new state to the initfile
  int width         = static_cast<int>(M5App::GetResolution().x);
  int height        = static_cast<int>(M5App::GetResolution().y);
  bool isFullScreen = M5App::GetFullScreen();

  iniFile.SetToSection("InitData");
  iniFile.AddKeyValue("width", width);
  iniFile.AddKeyValue("height", height);
  iniFile.AddKeyValue("fullScreen", isFullScreen);
  iniFile.WriteFile("GameData/InitData.ini");


  return 0;
}

