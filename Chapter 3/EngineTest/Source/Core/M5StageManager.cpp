/******************************************************************************/
/*!
file    M5StageManager.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/7

This provides Support for switching stages in your game, such as switching
between levels and menus.
*/
/******************************************************************************/
#include "M5StageManager.h"
#include "M5App.h"
#include "M5Gfx.h"
#include "M5Input.h"
#include "M5Timer.h"
#include "M5Debug.h"
#include "M5ObjectManager.h"
#include "..\RegisterStages.h"

#include "M5Stage.h"
#include "M5StageBuilder.h"
#include "M5Factory.h"

#include <vector>


namespace
{
//"Private" class data
static M5Factory<M5StageTypes, M5StageBuilder, M5Stage> 
                             s_stageFactory; /*!< Factory for creating Stages based off of the */
static M5Timer               s_timer;        /*!< Timer used to keep track of frame time.*/
static M5GameData*           s_pGameData;    /*!< Pointer to user defined shared data from main*/
static M5StageTypes          s_currStage;    /*!< This is the current stage we are in*/
static M5StageTypes          s_prevStage;    /*!< This is the last stage we were in*/
static M5StageTypes          s_nextStage;    /*!< This is the stage we are going into*/
static bool                  s_isQuitting;   /*!< TRUE if we are quitting, FALSE otherwise*/
static bool                  s_isRestarting; /*!< TRUE if we are restarting, FALSE otherwise*/

}//end unnamed namespace

/******************************************************************************/
/*!
Allocates recourses related to the Stage Manager.  This should NOT be called
by the user.  It will be called automatically by the system.

\param [in] pGData
A pointer to M5GameData struct to copy initial data.

\param [in] gameDataSize
The size of the M5GameData struct so we know how much memory to allocate.

\param [in] framePerSecond
The desired number of times per second that the game should update.
*/
/******************************************************************************/
void M5StageManager::Init(const M5GameData* pGData, int gameDataSize, int framesPerSecond)
{
  M5DEBUG_CALL_CHECK(1);

  /*Initialize stage data*/
  s_prevStage    = ST_INVALID;
  s_currStage    = ST_INVALID;
  s_nextStage    = ST_INVALID;
  s_isQuitting   = false;
  s_isRestarting = false;
  s_timer.Init(framesPerSecond);

  M5DEBUG_ASSERT(gameDataSize >= 1, "M5GameData must have at least size of 1");

  /*Allocate space for game data, I don't know the details so just copy bytes*/
  s_pGameData = reinterpret_cast<M5GameData*>(new char[gameDataSize]);
  /*Copy all data*/
  std::memcpy(s_pGameData, pGData, (size_t)gameDataSize);
  RegisterStages();
}
/******************************************************************************/
/*!
Deallocates resourses related to the Stage Manager.  This should NOT be called
by the user.  It will be called automatically by the system.

*/
/******************************************************************************/
void M5StageManager::Shutdown(void)
{
  //This was allocated as an array of bytes
  char* toDelete = reinterpret_cast<char*>(s_pGameData);
  delete[] toDelete;
  s_pGameData = 0;
}
/******************************************************************************/
/*!
Adds the type/M5StageBuilder pair to the stage factory.  Users should not need 
to call this function.  A batch file will automatically register all stages 
if they are named correctly: eg *Stage

\param [in] type
The stage type to assocaite the M5StageBuilder with  

\param [in] builder
A pointer to a new M5StageBuilder type for this stage
*/
/******************************************************************************/
void M5StageManager::AddStage(M5StageTypes type, M5StageBuilder* builder)
{
  s_stageFactory.AddBuilder(type, builder);
}
/******************************************************************************/
/*!
Removes a M5StageBuilder from the stage factory.

\param [in] type
The M5StageBuilder to remove based on the association when added.

*/
/******************************************************************************/
void M5StageManager::RemoveStage(M5StageTypes type)
{
	s_stageFactory.RemoveBuilder(type);
}
/******************************************************************************/
/*!
Clears all M5StageBuilders from the StageFactory
*/
/******************************************************************************/
void M5StageManager::ClearStages(void)
{
	s_stageFactory.ClearBuilders();
}
/******************************************************************************/
/*!
Returns if the Game stage manager has been set to quit or not.

\return
TRUE if the manager has been set to quit, FALSE otherwise.

*/
/******************************************************************************/
bool M5StageManager::IsQuitting(void)
{
  return s_isQuitting;
}
/******************************************************************************/
/*!
Returns if the game stage manager is going to restart the stage or not.

\return
TRUE if the manager is going to restart the stage, FALSE otherwise.

*/
/******************************************************************************/
bool M5StageManager::IsRestarting(void)
{
  return s_isRestarting;
}
/******************************************************************************/
/*!
Returns the unique id of the previous stage.

\return
The unique id of the previous stage.
*/
/******************************************************************************/
int M5StageManager::GetPreviousStage(void)
{
  return s_prevStage;
}
/******************************************************************************/
/*!
Returns the unique id of the current stage.

\return
The unique id of the current stage.
*/
/******************************************************************************/
int M5StageManager::GetCurrentStage(void)
{
  return s_currStage;
}
/******************************************************************************/
/*!
Returns the unique id of the next stage.

\return
The unique id of the next stage.
*/
/******************************************************************************/
int M5StageManager::GetNextStage(void)
{
  return s_nextStage;
}
/******************************************************************************/
/*!
Returns an Instance of the Shared GameData.

\return
A pointer to the shared GameData
*/
/******************************************************************************/
M5GameData& M5StageManager::GetGameData(void)
{
  return *s_pGameData;
}
/******************************************************************************/
/*!
This function controls the main game loop.  It will update the application,
initialize, update and shutdown all stages.  This must be called Every
GameLoop.

*/
/******************************************************************************/
void M5StageManager::Update(void)
{
  float frameTime = 0.0f;
  /*Get the Current stage*/
  M5Stage* pCurrentStage = s_stageFactory.Build(s_currStage);

  if (s_isRestarting == true)
    s_isRestarting = false;/*We need to reset our restart flag*/
  else
    pCurrentStage->Load();/*Only load if we are not restarting*/
    

  /*Call the initialize function*/
  pCurrentStage->Init();

  /*Keep going until the stage has changed or we are quitting.*/
  while ((s_currStage == s_nextStage) && !s_isQuitting && !s_isRestarting)
  {
    /*Our main game loop*/
    s_timer.StartFrame();/*Save the start time of the frame*/
    M5Input::Reset(frameTime);
    M5App::ProcessMessages();
    pCurrentStage->Update(frameTime);
	M5ObjectManager::Update(frameTime);
	M5Gfx::Update();
    frameTime = s_timer.EndFrame();/*Get the total frame time*/
  }

  /*Make sure to shutdown the stage*/
  pCurrentStage->Shutdown();

  /*Only unload if we are not restarting*/
  if (!s_isRestarting) {
    pCurrentStage->Unload();
    delete pCurrentStage;
	pCurrentStage = 0;
  }

  /*Change Stage*/
  ChangeStage();
}
/******************************************************************************/
/*!
Sets the stage that the game should start in.  This should only be called once
at the beginning of the game.

\attention
THIS SHOULD ONLY BE CALLED ONCE AT THE BEGINNING OF THE GAME.

\param [in] startStage
A unique id of the stage that the game should start in.
*/
/******************************************************************************/
void M5StageManager::SetStartStage(M5StageTypes startStage)
{
  s_prevStage = startStage;
  s_currStage = startStage;
  s_nextStage = startStage;
}
/******************************************************************************/
/*!
Sets the stage id of the next stage.  Use this to request a change from one
stage to another.

\param [in] nextStage
A unique id of the next that the game should start in.
*/
/******************************************************************************/
void M5StageManager::SetNextStage(M5StageTypes nextStage)
{
  s_nextStage = nextStage;
}
/******************************************************************************/
/*!
Sets if the game stage manager should quit.  Use this to exit the game from
inside a stage.
*/
/******************************************************************************/
void M5StageManager::Quit(void)
{
  s_isQuitting = true;
}
/******************************************************************************/
/*!
Sets if the game stage manager should restart the current stage.  Use this to
restart the current from inside a stage.

\attention
This does not restart the game.  It calls Shutdown, then Init on the current
stage, and continues updating.
*/
/******************************************************************************/
void M5StageManager::Restart(void)
{
  s_isRestarting = true;
}
/******************************************************************************/
/*!
Used to change the stage ids after the stage has shutdown.
*/
/******************************************************************************/
void M5StageManager::ChangeStage(void)
{
  s_prevStage = s_currStage;
  s_currStage = s_nextStage;
}
