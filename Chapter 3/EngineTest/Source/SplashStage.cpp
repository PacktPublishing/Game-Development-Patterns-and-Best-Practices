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
#include "Core\M5Vec2.h"
#include "Core\M5StageManager.h"
#include "Core\M5Object.h"
#include "Core\M5ObjectManager.h"
#include "Core\GfxComponent.h"
#include "Core\M5ArcheTypes.h"
#include "Core\M5Input.h"
#include "Core\M5Random.h"
#include <ctime>


namespace
{
  /*The max time to be in this stage*/
const float MAX_SPLASH_TIME = 6.0f;

}

/******************************************************************************/
/*!
The load stage will only be called once, when the stage is first entered.
You should load resources that won't need to be changed if the stage is 
restarted.

*/
/******************************************************************************/
void SplashStage::Load(void)
{
  /*Create a debug console*/
  M5DEBUG_CREATE_CONSOLE();
  M5Random::Seed(static_cast<unsigned>(std::time(0)));
}
/******************************************************************************/
/*!
The Init function will be called once when the stage is entered, then again
every time the stage is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the stage.  Here I am also 
using this stage to test my vectors and matricies.

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

  M5Gfx::SetBackgroundColor(0.0f, 0.f, 0.f);

  /*Reset the timer for this stage*/
  m_changeTimer = 0.f;

  M5Vec2 windowSize = M5App::GetResolution(); 
  M5Object* pObj = M5ObjectManager::CreateObject(AT_Splash);
  pObj->scale.x = windowSize.y;
  pObj->scale.y = windowSize.y;
  pObj->pos.x = windowSize.x / 2;
  pObj->pos.y = windowSize.y / 2;
  
  GfxComponent* pGfxComp = 0;
  pObj->GetComponent(CT_GfxComponent, pGfxComp);
  M5Gfx::RegisterHudComponent(pGfxComp);

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
  m_changeTimer += dt;

  /*Check for time, only be in this stage for the set time*/
  if (m_changeTimer > MAX_SPLASH_TIME)
	  M5StageManager::SetNextStage(ST_GamePlayStage);
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
/******************************************************************************/
/*!
This is the unload stage.  Use this stage to clean up any resources from the 
load stage.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void SplashStage::Unload(void)
{
}
