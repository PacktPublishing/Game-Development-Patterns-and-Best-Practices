/******************************************************************************/
/*!
\file   PlayerInputComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Player input for AstroShot
*/
/******************************************************************************/
#include "PlayerInputComponent.h"
#include "Core\M5IniFile.h"
#include "Core\M5Input.h"
#include "Core\M5Vec2.h"
#include "Core\M5Object.h"
#include "Core\M5ObjectManager.h"
#include "Core\M5Gfx.h"
#include "Core\GfxComponent.h"
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
	m_rotationSpeed(0)
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
	//Do forward motion


	//If gamepad is working just face the direction of left thumbstick
	if (M5Input::GamePadIsConnected())
	{
		M5Vec2 leftThumb;
		M5Vec2 dir;
		M5Input::GetLeftThumb(leftThumb);
		if(M5Vec2::LengthSquared(leftThumb) > 0)
		  m_pObj->rotation = std::atan2(leftThumb.y, leftThumb.x);

		M5Vec2::Scale(dir, leftThumb, m_forwardSpeed * dt);
		m_pObj->vel += dir;
		M5Vec2::Scale(m_pObj->vel, m_pObj->vel, m_speedDamp);

		if (M5Input::IsTriggered(M5_GAMEPAD_A) || M5Input::IsTriggered(M5_SPACE))
		{
			M5Vec2 perp;
			M5Object* bullet1 = M5ObjectManager::CreateObject(AT_Bullet);
			M5Object* bullet2 = M5ObjectManager::CreateObject(AT_Bullet);
			bullet2->rotation = bullet1->rotation = m_pObj->rotation;

			dir.Set(std::cos(bullet1->rotation), std::sin(bullet1->rotation));
			perp.Set(dir.y, -dir.x);
			bullet1->pos = m_pObj->pos + perp * .5f * m_pObj->scale.y;
			bullet2->pos = m_pObj->pos - perp * .5f * m_pObj->scale.y;

			M5Vec2::Scale(dir, dir, m_bulletSpeed * dt);

			bullet1->vel = m_pObj->vel + dir;
			bullet2->vel = m_pObj->vel + dir;

		}
	}
	
	//Back up controls to rotate and shoot if there is no game pad.

	if (M5Input::IsPressed(M5_W))
	{
		M5Vec2 dir(std::cos(m_pObj->rotation), std::sin(m_pObj->rotation));
		M5Vec2::Scale(dir, dir, m_forwardSpeed * dt);
		m_pObj->vel += dir;
		M5Vec2::Scale(m_pObj->vel, m_pObj->vel, m_speedDamp);
	}

	if (M5Input::IsPressed(M5_A))
		m_pObj->rotationVel += m_rotationSpeed * dt;
	else if (M5Input::IsPressed(M5_D))
		m_pObj->rotationVel -= m_rotationSpeed * dt;
	else
		m_pObj->rotationVel = 0;


}
/******************************************************************************/
/*!
Virtual constructor for PlayerInputComponent
*/
/******************************************************************************/
M5Component* PlayerInputComponent::Clone(void)
{
	PlayerInputComponent* pNew = new PlayerInputComponent;
	pNew->m_forwardSpeed  = m_forwardSpeed;
	pNew->m_bulletSpeed   = m_bulletSpeed;
	pNew->m_rotationSpeed = m_rotationSpeed;
	pNew->m_speedDamp     = m_speedDamp;
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
}