/******************************************************************************/
/*!
file    SplashStage.cpp
\author Matt Casanova 
\\par   email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/10

This is a stage for the Mach5 Engine Demo project. This would be a 
good place to load game data and initialize object you need for your game.
*/
/******************************************************************************/
#include "SplashStage.h"

#include "Core\M5App.h"
#include "Core\M5Debug.h"
#include "Core\M5StageManager.h"
#include "Core\M5ObjectManager.h"
#include "Core\M5Object.h"
#include "Core\M5Random.h"
#include "Core\M5IniFile.h"
#include "Core\M5GameData.h"
#include "Core\M5StageTypes.h"
#include "SpaceShooterHelp.h"
#include <ctime>
#include <string>


/******************************************************************************/
/*!
The Constructor will only be called once, when the stage is first entered.
You should load resources that won't need to be changed if the stage is 
restarted.
*/
/******************************************************************************/
SplashStage::SplashStage(void)
{
  /*Create a debug console*/
  M5DEBUG_CREATE_CONSOLE();
  M5Random::Seed(static_cast<unsigned>(std::time(0)));
}
/******************************************************************************/
/*!
Use the desctuctor of the stage to clean up any resources from the
load stage.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
SplashStage::~SplashStage(void)
{
	//We are done this with ArcheType so lets get rid of it.
	M5ObjectManager::RemoveArcheType(AT_Splash);
	M5DEBUG_DESTROY_CONSOLE();
}
/******************************************************************************/
/*!
The Init function will be called once when the stage is entered, then again
every time the stage is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the stage.

*/
/******************************************************************************/
void SplashStage::Init(void)
{
  //This code will only show in the console if it is active and you 
  //are in debug mode.
  M5DEBUG_PRINT("This is a demo of the different things you can do\n");
  M5DEBUG_PRINT("in the Mach 5 Engine.  Play with the demo but you must\n");
  M5DEBUG_PRINT("also inspect the code and comments.\n\n");
  M5DEBUG_PRINT("If you find errors, report to lazersquad@gmail.com");

  //Create ini reader and starting vars
  M5IniFile iniFile;
  std::string loadDir = "Stages\\";
  std::string nextStage;
  //Load file
  iniFile.ReadFile(loadDir + M5StageManager::GetGameData().menuFile);

  //Read global ini file values
  iniFile.GetValue("maxSplashTime", m_maxSplashTime);
  iniFile.GetValue("nextStage", nextStage);
  iniFile.GetValue("nextFile", m_nextFile);
  m_nextStage = StringToStage(nextStage);
  M5StageManager::GetGameData().menuFile = nextStage + ".ini";
  //Read Objects From IniFile
  LoadObjects(iniFile);

  //Set background color.  
  M5Gfx::SetBackgroundColor(0, 0, 0);
  /*Reset the timer for this stage*/
  m_splashTime = 0.f;
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the 
action, behavoir, drawing and stage changes should happen.
*/
/******************************************************************************/
void SplashStage::Update(float dt)
{
  /*increment timer*/
  m_splashTime += dt;

  /*Check for time, only be in this stage for the set time*/
  if (m_splashTime > m_maxSplashTime)
  {
	  M5StageManager::SetNextStage(m_nextStage);
	  M5StageManager::GetGameData().menuFile = m_nextFile;
  }
}
/******************************************************************************/
/*!
This is the shutdown stage.  Use this stage to clean up any resources from 
the init stage.  Since this stage is simple, there is nothing to clean up 
here.

*/
/******************************************************************************/
void SplashStage::Shutdown(void)
{
	M5ObjectManager::DestroyAllObjects();
}


