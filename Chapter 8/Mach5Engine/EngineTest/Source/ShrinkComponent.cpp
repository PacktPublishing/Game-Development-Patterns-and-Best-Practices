/******************************************************************************/
/*!
\file   ShrinkComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/05

Shrink Debuff Component
*/
/******************************************************************************/
#include "ShrinkComponent.h"

#include "Core\M5Object.h"
#include "Core\M5Math.h"


/******************************************************************************/
/*!
Sets component type and starting values for player
*/
/******************************************************************************/
ShrinkComponent::ShrinkComponent(void) :
	M5Component(CT_ShrinkComponent),
	m_oldScale(),
	m_hasStarted(false),
	m_timer(0),
	m_maxTime(5)
{
}
/******************************************************************************/
/*!
PlayerInputDestructor, does nothing
*/
/******************************************************************************/
ShrinkComponent::~ShrinkComponent(void)
{
}
/******************************************************************************/
/*!
Updates the player based on input
*/
/******************************************************************************/
void ShrinkComponent::Update(float dt)
{
	if (m_hasStarted == false)
	{
		//If there is already a shrink component, just add to that timer.
		ShrinkComponent* pShrink = 0;
		m_pObj->GetComponent(CT_ShrinkComponent, pShrink);
		if (pShrink != 0 && pShrink != this)
		{
			pShrink->m_timer -= 5;
			isDead = true;
		}
		else
		{
			m_oldScale = m_pObj->scale;
			m_pObj->scale.Set(2, 2);
			m_hasStarted = true;
		}
	}

	m_timer += dt;

	if (m_timer > m_maxTime)
	{
		m_pObj->scale = m_oldScale;
		isDead = true;
	}
}
/******************************************************************************/
/*!
Virtual constructor for PlayerInputComponent
*/
/******************************************************************************/
ShrinkComponent* ShrinkComponent::Clone(void) const
{
	ShrinkComponent* pNew = new ShrinkComponent();
	return pNew;
}