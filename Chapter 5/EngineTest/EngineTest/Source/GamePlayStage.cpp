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

float maxTime = 1;
float timer = 0;

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
	

	timer = 0;

}
void GamePlayStage::Update(float dt)
{
	M5Object* pPlayer;
	M5ObjectManager::GetFirstObjectByType(AT_Player, pPlayer);

	if (M5Input::IsPressed(M5_ESCAPE))
		M5StageManager::Quit();
	else if(pPlayer == nullptr)
		M5StageManager::Quit();
	else if (M5Input::IsTriggered(M5_Z))//Dynamically Shrink
	{
		pPlayer->AddComponent(new ShrinkComponent);
	}
	else if (M5Input::IsTriggered(M5_N))
	{
		M5StageManager::GetGameData().level++;
		M5StageManager::SetNextStage(ST_GamePlayStage);
	}
	else if (M5Input::IsTriggered(M5_R))
	{
		M5StageManager::Restart();
	}
	else if (M5Input::IsTriggered(M5_P))
	{
		M5StageManager::PauseAndSetNextStage(ST_PauseStage);
	}

	timer += dt;
	if (timer > maxTime)
	{
		timer = 0;
		M5Object* pRaider = M5ObjectManager::CreateObject(AT_Raider);
		M5Object* pUfo = M5ObjectManager::CreateObject(AT_Ufo);
		pUfo->pos.x = M5Random::GetFloat(-100, 100);
		pUfo->pos.y = M5Random::GetFloat(-60, 60);
		pRaider->pos.x = M5Random::GetFloat(-100, 100);
		pRaider->pos.y = M5Random::GetFloat(-60, 60);
	}


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
			pFirst->pos  -= dir * dt;
			pSecond->pos  += dir *  dt;
		}
		else
		{
			M5ObjectManager::DestroyObject(pairs[i].first);
			M5ObjectManager::DestroyObject(pairs[i].second);
		}

	}
}
void GamePlayStage::Shutdown(void)
{
	M5ObjectManager::DestroyAllObjects();
}
