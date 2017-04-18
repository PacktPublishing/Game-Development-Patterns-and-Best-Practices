/******************************************************************************/
/*!
\file   RandomGoComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/08

Finite Statemachine base class component
*/
/******************************************************************************/
#include "RandomGoComponent.h"
#include "Core\M5Gfx.h"
#include "Core\M5Random.h"
#include "Core\M5Object.h"
#include "Core\M5Intersect.h"
#include "Core\M5IniFile.h"
#include "Core\M5Math.h"
#include <cmath>

RLCFindState::RLCFindState(RandomGoComponent* parent):
	m_parent(parent)
{
}
void RLCFindState::Enter(float)
{
	M5Vec2 botLeft;
	M5Vec2 topRight;
	M5Gfx::GetWorldBotLeft(botLeft);
	M5Gfx::GetWorldTopRight(topRight);

	m_parent->m_target.x = M5Random::GetFloat(botLeft.x, topRight.x);
	m_parent->m_target.y = M5Random::GetFloat(botLeft.y, topRight.y);

}
void RLCFindState::Update(float)
{
	m_parent->SetNextState(&m_parent->m_rotateState);
}
void RLCFindState::Exit(float)
{
}
RLCRotateState::RLCRotateState(RandomGoComponent* parent) :
	m_parent(parent)
{
}

void RLCRotateState::Enter(float )
{
	M5Vec2::Sub(m_dir, m_parent->m_target, m_parent->m_pObj->pos);
	m_targetRot = std::atan2f(m_dir.y, m_dir.x);
	m_targetRot = M5Math::Wrap(m_targetRot, 0.f, M5Math::TWO_PI);
	m_parent->m_pObj->rotationVel = m_parent->m_rotateSpeed;
}
void RLCRotateState::Update(float )
{
	m_parent->m_pObj->rotation = M5Math::Wrap(m_parent->m_pObj->rotation, 0.f, M5Math::TWO_PI);
	if(M5Math::IsInRange(m_parent->m_pObj->rotation, m_targetRot - .1f, m_targetRot + .1f))
		m_parent->SetNextState(&m_parent->m_goState);
}
void RLCRotateState::Exit(float )
{
	m_parent->m_pObj->rotationVel = 0;
	m_dir.Normalize();
	M5Vec2::Scale(m_dir, m_dir, m_parent->m_speed);
	m_parent->m_pObj->vel = m_dir;
}

RLCGoState::RLCGoState(RandomGoComponent* parent) :
	m_parent(parent)
{
}
void RLCGoState::Enter(float )
{

}
void RLCGoState::Update(float )
{
	if (M5Intersect::PointCircle(m_parent->m_target,
		m_parent->m_pObj->pos,
		m_parent->m_pObj->scale.x))
	{
		m_parent->SetNextState(&m_parent->m_findState);
	}
}
void RLCGoState::Exit(float )
{
	m_parent->m_pObj->vel.Set(0, 0);
}

RandomGoComponent::RandomGoComponent():
	M5StateMachine(CT_RandomGoComponent),
	m_speed(1),
	m_rotateSpeed(1),
	m_findState(this),
	m_rotateState(this),
	m_goState(this)
{
	SetNextState(&m_findState);
}
void RandomGoComponent::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("RandomGoComponent");
	iniFile.GetValue("speed", m_speed);
	iniFile.GetValue("rotationSpeed", m_speed);
}
M5Component* RandomGoComponent::Clone(void)
{
	RandomGoComponent* pNew = new RandomGoComponent;
	pNew->m_speed = m_speed;
	pNew->m_rotateSpeed = m_rotateSpeed;
	return pNew;
}