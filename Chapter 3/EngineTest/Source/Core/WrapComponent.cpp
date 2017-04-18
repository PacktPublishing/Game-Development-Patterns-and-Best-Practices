/******************************************************************************/
/*!
\file   WrapComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Component to wrap an object in the screen
*/
/******************************************************************************/
#include "WrapComponent.h"
#include "M5Gfx.h"
#include "M5Math.h"
#include "M5Object.h"


WrapComponent::WrapComponent(void) :
	M5Component(CT_WrapComponent)
{
}
WrapComponent::~WrapComponent(void)
{
}
void WrapComponent::Update(float /*dt*/)
{
	M5Vec2 botLeft;
	M5Vec2 topRight;
	M5Gfx::GetWorldBotLeft(botLeft);
	M5Gfx::GetWorldTopRight(topRight);
	m_pObj->pos.x = M5Math::Wrap(m_pObj->pos.x, botLeft.x, topRight.x);
	m_pObj->pos.y = M5Math::Wrap(m_pObj->pos.y, botLeft.y, topRight.y);
}
M5Component* WrapComponent::Clone(void)
{
	WrapComponent* pNew = new WrapComponent;
	pNew->m_pObj = m_pObj;
	return pNew;
}