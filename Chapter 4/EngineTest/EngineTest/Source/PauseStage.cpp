/******************************************************************************/
/*!
file    PauseStage.cpp
\author Matt Casanova
\\par   email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Stage for a Pause Menu
*/
/******************************************************************************/
#include "PauseStage.h"
#include "Core\M5GameData.h"
#include "Core\M5Input.h"
#include "Core\M5StageManager.h"
#include "Core\M5Object.h"
#include "Core\M5ObjectManager.h"
#include "Core\M5IniFile.h"
#include "Core\M5Phy.h"
#include "ShrinkComponent.h"
#include "SpaceShooterHelp.h"

#include "Core\M5Random.h"

#include <sstream>
#include <iomanip>


PauseStage::PauseStage(void)
{
}
PauseStage::~PauseStage(void)
{
}
void PauseStage::Init(void)
{
	M5Gfx::SetBackgroundColor(1, 1, 1);
}
void PauseStage::Update(float /*dt*/)
{
	if (M5Input::IsPressed(M5_R))
		M5StageManager::Resume();

}
void PauseStage::Shutdown(void)
{
	//M5ObjectManager::DestroyAllObjects();
}
