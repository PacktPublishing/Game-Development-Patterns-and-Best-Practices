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
#include "M5Phy.h"
#include "M5Input.h"
#include "M5Timer.h"
#include "M5Debug.h"
#include "M5ObjectManager.h"
#include "..\RegisterStages.h"

#include "M5Stage.h"
#include "M5StageBuilder.h"
#include "M5Factory.h"

#include <vector>
#include <stack>


namespace
{
//! Struct to help save pause info
struct PauseInfo
{
	PauseInfo(M5Stage* p, M5StageTypes t):
	pStage(p), type(t){}
	M5Stage* pStage;
	M5StageTypes type;
};

//"Private" class data
static M5Factory<M5StageTypes, M5StageBuilder, M5Stage>
s_stageFactory; /*!< Factory for creating Stages based off of the */
std::stack<PauseInfo>        s_pauseStack;
static M5Stage*              s_pStage;       /*!< Pointer to base class stage */
static M5Timer               s_timer;        /*!< Timer used to keep track of frame time.*/
static M5GameData*           s_pGameData;    /*!< Pointer to user defined shared data from main*/
static M5StageTypes          s_currStage;    /*! Enum to know what stage to load from factory*/
static M5StageTypes          s_nextStage;    /*! Enum to know what stage to load next*/
static bool                  s_isChanging;   /*!< TRUE is we are changing states, false otherwise*/
static bool                  s_isQuitting;   /*!< TRUE if we are quitting, FALSE otherwise*/
static bool                  s_isRestarting; /*!< TRUE if we are restarting, FALSE otherwise*/
static bool                  s_isPausing;
static bool                  s_isResuming;


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
	s_pStage       = nullptr;
	s_currStage    = ST_INVALID;
	s_nextStage    = ST_INVALID;
	s_isQuitting   = false;
	s_isRestarting = false;
	s_isPausing    = false;
	s_isResuming   = false;
	s_isChanging   = true; //make sure we load the first stage
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
	
	InitStage();

	/*Keep going until the stage has changed or we are quitting.*/
	while (!s_isChanging && !s_isQuitting && !s_isRestarting)
	{
		/*Our main game loop*/
		s_timer.StartFrame();/*Save the start time of the frame*/
		M5Input::Reset(frameTime);
		M5App::ProcessMessages();
		M5ObjectManager::Update(frameTime);
		M5Phy::Update();
		s_pStage->Update(frameTime);
		M5Gfx::Update();
		frameTime = s_timer.EndFrame();/*Get the total frame time*/
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
	s_isChanging = true;
	s_nextStage = nextStage;
}
/******************************************************************************/
/*!
Pauses the current stage and changes to a the next one.

\param [in] nextStage
A unique id of the next that the game should start in.
*/
/******************************************************************************/
void M5StageManager::PauseAndSetNextStage(M5StageTypes nextStage)
{
	s_isPausing  = true;
	s_isChanging = true;
	s_nextStage  = nextStage;

}
/******************************************************************************/
/*!
Resumes the previous stages
*/
/******************************************************************************/
void M5StageManager::Resume(void)
{
	M5DEBUG_ASSERT(!s_pauseStack.empty(), "Trying to Resume an e")
	s_isChanging = true;
	s_isResuming = true;

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
Initilizes the current stage based on status.
*/
/******************************************************************************/
void M5StageManager::InitStage(void)
{
	if (s_isRestarting)
	{
		s_pStage->Init();/*Call the initialize function*/
		s_isRestarting = false;/*We need to reset our restart flag*/
	}
	else if (s_isResuming)
	{
		M5ObjectManager::Resume();
		M5Phy::Resume();
		M5Gfx::Resume();
		s_isResuming = s_isChanging = false;
		PauseInfo pi = s_pauseStack.top();
		s_pauseStack.pop();
		s_currStage = s_nextStage = pi.type;
		s_pStage = pi.pStage;
	}
	else if (s_isChanging)
	{
		s_pStage = s_stageFactory.Build(s_currStage);
		s_pStage->Init();/*Call the initialize function*/
		s_isChanging = false;
	}
}
/******************************************************************************/
/*!
Used to change the stage ids after the stage has shutdown.
*/
/******************************************************************************/
void M5StageManager::ChangeStage(void)
{
	/*Only unload if we are not restarting*/
	if (s_isPausing)
	{
		M5ObjectManager::Pause();
		M5Phy::Pause();
		M5Gfx::Pause();
		PauseInfo pi(s_pStage, s_currStage);
		s_pauseStack.push(pi);
		s_isPausing = false;
	}
	else if (!s_isRestarting) {
		/*Make sure to shutdown the stage*/
		s_pStage->Shutdown();
		delete s_pStage;
		s_pStage = nullptr;
	}
	else if (s_isRestarting)
	{
		/*Make sure to shutdown the stage*/
		s_pStage->Shutdown();
	}

	s_currStage = s_nextStage;
}
