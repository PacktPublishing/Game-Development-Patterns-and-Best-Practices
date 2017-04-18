/******************************************************************************/
/*!
file    GamePlayStage.cpp
\author Matt Casanova
\\par   email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

This is a stage for the Mach5 Engine Demo project. This would be a
good place to load game data and initialize object you need for your game.
*/
/******************************************************************************/
#include "GamePlayStage.h"
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

GamePlayStage::GamePlayStage(void)
{
}
GamePlayStage::~GamePlayStage(void)
{
}
void GamePlayStage::Init(void)
{

	//Construct file to read
	std::stringstream file;
	file << "Stages\\Level";
	file << std::setw(2) << std::setfill('0') << 
		M5StageManager::GetGameData().level << ".ini";

	//Open IniFIle
	M5IniFile iniFile;
	iniFile.ReadFile(file.str());
	LoadObjects(iniFile);

}
void GamePlayStage::Update(float dt)
{
	M5Object* pPlayer;
	M5ObjectManager::GetFirstObjectByType(AT_Player, pPlayer);

	if (M5Input::IsPressed(M5_ESCAPE))
		M5StageManager::Quit();
	else if (pPlayer == nullptr)
	{
		M5StageManager::Quit();
	}
	else if (M5Input::IsTriggered(M5_R))
	{
		M5StageManager::Restart();
	}
	else if (M5Input::IsTriggered(M5_P))
	{
		M5StageManager::PauseAndSetNextStage(ST_PauseStage);
	}

	CheckCollision(dt);
}

void GamePlayStage::Shutdown(void)
{
	M5ObjectManager::DestroyAllObjects();
}

void GamePlayStage::CheckCollision(float dt)
{
	CollisionPairs pairs;
	M5Phy::GetCollisionPairs(pairs);
	size_t size = pairs.size();
	for (size_t i = 0; i < size; ++i)
	{
		M5Object* pFirst = nullptr;
		M5Object* pSecond = nullptr;
		M5ObjectManager::GetObjectByID(pairs[i].first, pFirst);
		M5ObjectManager::GetObjectByID(pairs[i].second, pSecond);

		if (pFirst == nullptr || pSecond == nullptr)
			continue;

		if (pFirst->GetType() == pSecond->GetType())
		{
			M5Vec2 dir;
			M5Vec2::Sub(dir, pSecond->pos, pFirst->pos);
			pFirst->pos -= dir * dt;
			pSecond->pos += dir *  dt;
		}
		else
		{
			M5ObjectManager::DestroyObject(pairs[i].first);
			M5ObjectManager::DestroyObject(pairs[i].second);
		}

	}
}