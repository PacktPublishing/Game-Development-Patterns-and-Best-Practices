/******************************************************************************/
/*!
\file   MenuStage.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/17

The MainMenu in AstroShot
*/
/******************************************************************************/
#include "MenuStage.h"
#include "Core\M5ObjectManager.h"
#include "Core\M5App.h"
#include "Core\M5IniFile.h"
#include "Core\M5StageManager.h"
#include "Core\M5GameData.h"
#include "SpaceShooterHelp.h"
#include <string>

MenuStage::MenuStage(void)
{
}
MenuStage::~MenuStage(void)
{
}
void MenuStage::Init(void)
{
	std::string loadDir = "Stages\\";
	//Create ini reader and starting vars
	M5IniFile iniFile;
	//Load file
	iniFile.ReadFile(loadDir + M5StageManager::GetGameData().menuFile);
	//Read Objects From IniFile
	LoadObjects(iniFile);
}
void MenuStage::Update(float /*dt*/)
{
}
void MenuStage::Shutdown(void)
{
	M5ObjectManager::DestroyAllObjects();
}
