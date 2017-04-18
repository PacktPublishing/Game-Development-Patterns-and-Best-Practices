/******************************************************************************/
/*!
\file   ChasePlayerComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/09

Simple AI to Chase the Player
*/
/******************************************************************************/
#include "ChasePlayerComponent.h"

#include "Core\M5ObjectManager.h"
#include "Core\M5IniFile.h"
#include "Core\M5Object.h"
#include <vector>
#include <cmath>


/******************************************************************************/
/*!
Sets component type and starting values for player
*/
/******************************************************************************/
ChasePlayerComponent::ChasePlayerComponent(void):
	M5Component(CT_ChasePlayerComponent),
	m_speed(1)
{

}
/******************************************************************************/
/*!
Sets component type and starting values for player
*/
/******************************************************************************/
void ChasePlayerComponent::Update(float)
{
	std::vector<M5Object*> players;
	M5ObjectManager::GetAllObjectsByType(AT_Player, players);
	M5Vec2 dir;
	M5Vec2::Sub(dir, players[0]->pos, m_pObj->pos);
	m_pObj->rotation = std::atan2f(dir.y, dir.x);
	dir.Normalize();
	dir *= m_speed;
	m_pObj->vel = dir;
}
/******************************************************************************/
/*!
Sets component type and starting values for player
*/
/******************************************************************************/
ChasePlayerComponent* ChasePlayerComponent::Clone(void) const
{
	ChasePlayerComponent* pNew = new ChasePlayerComponent;
	pNew->m_speed = m_speed;
	return pNew;
}
void ChasePlayerComponent::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("ChasePlayerComponent");
	iniFile.GetValue("speed", m_speed);
}

