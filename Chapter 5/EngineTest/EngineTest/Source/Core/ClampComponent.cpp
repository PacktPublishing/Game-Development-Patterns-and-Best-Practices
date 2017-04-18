/******************************************************************************/
/*!
\file   ClampComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Component to clamp an object in the screen
*/
/******************************************************************************/
#include "ClampComponent.h"
#include "M5Gfx.h"
#include "M5Math.h"
#include "M5Object.h"

/******************************************************************************/
/*!
Constructor to set the Type of the component.
*/
/******************************************************************************/
ClampComponent::ClampComponent(void) :
	M5Component(CT_ClampComponent)
{
}
/******************************************************************************/
/*!
Returns a new Stage based on the type of the builder.

\param [in] dt
The time in seconds since the last frame
*/
/******************************************************************************/
void ClampComponent::Update(float /*dt*/)
{
	M5Vec2 botLeft;
	M5Vec2 topRight;
	M5Gfx::GetWorldBotLeft(botLeft);
	M5Gfx::GetWorldTopRight(topRight);
	m_pObj->pos.x = M5Math::Clamp(m_pObj->pos.x, botLeft.x, topRight.x);
	m_pObj->pos.y = M5Math::Clamp(m_pObj->pos.y, botLeft.y, topRight.y);
}
/******************************************************************************/
/*!
Virtual constructor the class.

\return
A new clamp component that is a copy of this one.

*/
/******************************************************************************/
M5Component* ClampComponent::Clone(void)
{
	ClampComponent* pNew = new ClampComponent;
	pNew->m_pObj = m_pObj;
	return pNew;
}