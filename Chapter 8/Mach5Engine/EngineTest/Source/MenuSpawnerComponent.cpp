/******************************************************************************/
/*!
\file   MenuSpawnerComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/18

Base graphics component.  For now it just contains a texture.
*/
/******************************************************************************/
#include "MenuSpawnerComponent.h"
#include "Core\M5ArcheTypes.h"
#include "Core\M5IniFile.h"
#include "Core\M5Random.h"
#include "Core\M5Math.h"
#include "Core\M5ObjectManager.h"
#include "Core\M5Object.h"

#include <cmath>
#include <string>

MenuSpawnerComponent::MenuSpawnerComponent(void):
	M5Component(CT_MenuSpawnerComponent),
	m_type(AT_INVALID),
	m_velMin(1),
	m_velMax(1),
	m_timer(0),
	m_maxTime(1)
{
}

void MenuSpawnerComponent::Update(float dt)
{
	m_timer += dt;
	if (m_timer > m_maxTime)
	{
		M5Object* pObj = M5ObjectManager::CreateObject(m_type);
		pObj->pos.Set(m_pObj->pos.x, m_pObj->pos.y);

		float rot = M5Random::GetFloat(0, M5Math::TWO_PI);
		pObj->rotation = rot;
		pObj->vel.Set(std::cos(rot), std::sin(rot));
		M5Vec2::Scale(pObj->vel, pObj->vel, M5Random::GetFloat(m_velMin, m_velMax));


		//make sure to reset the timer
		m_timer = 0;
	}
}
void MenuSpawnerComponent::FromFile(M5IniFile& iniFile)
{
	std::string type;
	iniFile.SetToSection("MenuSpawnerComponent");
	iniFile.GetValue("velMin", m_velMin);
	iniFile.GetValue("velMax", m_velMax);
	iniFile.GetValue("maxTime", m_maxTime);
	iniFile.GetValue("type", type);
	m_type = StringToArcheType(type);
	
	//Create an object right at the start
	m_timer = m_maxTime;

}
 MenuSpawnerComponent* MenuSpawnerComponent::Clone(void) const
{
	 MenuSpawnerComponent* pClone = new MenuSpawnerComponent();
	 pClone->m_type    = m_type;
	 pClone->m_velMin  = m_velMin;
	 pClone->m_velMax  = m_velMax;
	 pClone->m_timer   = 0;
	 pClone->m_maxTime = m_maxTime;
	 pClone->m_pObj = m_pObj;

	 return pClone;
}