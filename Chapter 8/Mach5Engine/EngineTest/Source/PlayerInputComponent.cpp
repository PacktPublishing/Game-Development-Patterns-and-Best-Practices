/******************************************************************************/
/*!
\file   PlayerInputComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Player input for AstroShot. This component hard codes the type of gun the 
player shoots
*/
/******************************************************************************/
#include "PlayerInputComponent.h"
#include "Core\M5IniFile.h"
#include "Core\M5Input.h"
#include "Core\M5Vec2.h"
#include "Core\M5Object.h"
#include "Core\M5ObjectManager.h"
#include <cmath>

/******************************************************************************/
/*!
Sets component type and starting values for player
*/
/******************************************************************************/
PlayerInputComponent::PlayerInputComponent(void) :
	M5Component(CT_PlayerInputComponent),
	m_forwardSpeed(0),
	m_speedDamp(0),
	m_rotationSpeed(0),
	m_rotationalDamp(0)
{
}
/******************************************************************************/
/*!
PlayerInputDestructor, does nothing
*/
/******************************************************************************/
PlayerInputComponent::~PlayerInputComponent(void)
{
}
/******************************************************************************/
/*!
Updates the player based on input
*/
/******************************************************************************/
void PlayerInputComponent::Update(float dt)
{
	//first check for rotation
	if (M5Input::IsPressed(M5_A)) 
	{
		m_pObj->rotationVel += m_rotationSpeed * dt;
		m_pObj->rotationVel *= m_rotationalDamp;
	}
	else if (M5Input::IsPressed(M5_D))
	{
		m_pObj->rotationVel -= m_rotationSpeed * dt; 
		m_pObj->rotationVel *= m_rotationalDamp;
	}
	else
		m_pObj->rotationVel = 0;

	//Then check for forward movement
	if (M5Input::IsPressed(M5_W))
	{
		//Get vector from rotation
		M5Vec2 dir(std::cos(m_pObj->rotation), std::sin(m_pObj->rotation));
		M5Vec2::Scale(dir, dir, m_forwardSpeed * dt);
		m_pObj->vel += dir;
		M5Vec2::Scale(m_pObj->vel, m_pObj->vel, m_speedDamp);
	}

	//then check for bullets 
	if (M5Input::IsTriggered(M5_SPACE))
	{
	
		M5Object* bullet1 = M5ObjectManager::CreateObject(AT_Bullet);
		M5Object* bullet2 = M5ObjectManager::CreateObject(AT_Bullet);
		bullet2->rotation = bullet1->rotation = m_pObj->rotation;

		M5Vec2 bulletDir(std::cos(bullet1->rotation), std::sin(bullet1->rotation));
		M5Vec2 perp(bulletDir.y, -bulletDir.x);
		bullet1->pos = m_pObj->pos + perp * .5f * m_pObj->scale.y;
		bullet2->pos = m_pObj->pos - perp * .5f * m_pObj->scale.y;

		M5Vec2::Scale(bulletDir, bulletDir, m_bulletSpeed * dt);

		bullet1->vel = m_pObj->vel + bulletDir;
		bullet2->vel = m_pObj->vel + bulletDir;

	}
}
/******************************************************************************/
/*!
Virtual constructor for PlayerInputComponent
*/
/******************************************************************************/
PlayerInputComponent* PlayerInputComponent::Clone(void) const
{
	PlayerInputComponent* pNew = new PlayerInputComponent;
	pNew->m_forwardSpeed   = m_forwardSpeed;
	pNew->m_bulletSpeed    = m_bulletSpeed;
	pNew->m_rotationSpeed  = m_rotationSpeed;
	pNew->m_speedDamp      = m_speedDamp;
	pNew->m_rotationalDamp = m_rotationalDamp;
	return pNew;
}
/******************************************************************************/
/*!
Loads PlayerInput data from an iniFile

\param
The preloaded iniFile to read.
*/
/******************************************************************************/
void PlayerInputComponent::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("PlayerInputComponent");
	iniFile.GetValue("forwardSpeed", m_forwardSpeed);
	iniFile.GetValue("bulletSpeed", m_bulletSpeed);
	iniFile.GetValue("rotationSpeed", m_rotationSpeed);
	iniFile.GetValue("speedDamp", m_speedDamp);
	iniFile.GetValue("rotationalDamp", m_rotationalDamp);
}