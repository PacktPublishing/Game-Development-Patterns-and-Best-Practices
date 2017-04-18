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
#include "Core\M5Input.h"
#include "Core\M5StageManager.h"
#include "Core\M5Object.h"
#include "Core\M5ObjectManager.h"
#include "Core\M5Gfx.h"
#include "Core\GfxComponent.h"
#include "ShrinkComponent.h"

#include <vector>

std::vector<M5Object*> player;

void GamePlayStage::Load(void)
{
}
void GamePlayStage::Init(void)
{
	M5Object* pObj = M5ObjectManager::CreateObject(AT_Player);
	GfxComponent* pGfxComp = 0;
	pObj->GetComponent(CT_GfxComponent, pGfxComp);
	M5Gfx::RegisterWorldComponent(pGfxComp);

	pObj = M5ObjectManager::CreateObject(AT_Raider);
	pGfxComp = 0;
	pObj->GetComponent(CT_GfxComponent, pGfxComp);
	M5Gfx::RegisterWorldComponent(pGfxComp);

	for (int i = 0; i < 4; ++i)
	{
		pObj = M5ObjectManager::CreateObject(AT_Ufo);
		pGfxComp = 0;
		pObj->GetComponent(CT_GfxComponent, pGfxComp);
		M5Gfx::RegisterWorldComponent(pGfxComp);
	}

}
void GamePlayStage::Update(float /*dt*/)
{
	player.clear();
	M5ObjectManager::GetAllObjects(AT_Player, player);

	if (M5Input::IsPressed(M5_ESCAPE))
		M5StageManager::Quit();
	else if(player.size() == 0)
		M5StageManager::Quit();
	else if (M5Input::IsTriggered(M5_Z))//Dynamically Shrink
	{
		player[0]->AddComponent(new ShrinkComponent);

	}
}
void GamePlayStage::Shutdown(void)
{
	M5ObjectManager::DestroyAllObjects();
}
void GamePlayStage::Unload(void)
{

}