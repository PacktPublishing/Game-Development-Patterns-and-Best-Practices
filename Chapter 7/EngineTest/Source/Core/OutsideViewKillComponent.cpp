/******************************************************************************/
/*!
\file   OutsideViewKillComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Removes The parent Game Object if it is outside the view port.  Right now
this only works if the viewport isn't rotated.

TODO: Remove Object from rotated viewport
*/
/******************************************************************************/
#include "OutsideViewKillComponent.h"
#include "M5Gfx.h"
#include "M5Math.h"
#include "M5Object.h"
#include "EngineTest\M5ObjectPool.h"    


/******************************************************************************/
/*!
Contructor to set type.
*/
/******************************************************************************/
OutsideViewKillComponent::OutsideViewKillComponent(void) :
	M5Component(CT_OutsideViewKillComponent)
{
}
/******************************************************************************/
/*!
Destructor
*/
/******************************************************************************/
OutsideViewKillComponent::~OutsideViewKillComponent(void)
{
}
/******************************************************************************/
/*!
Sets object to dead if it is outside of the view port.  Right now this only 
works if the viewport isn't rotated.
*/
/******************************************************************************/
void OutsideViewKillComponent::Update(float /*dt*/)
{
	M5Vec2 pos = m_pObj->pos;
	M5Vec2 scale = m_pObj->scale;
	scale *= .5f;
	M5Vec2 botLeft;
	M5Vec2 topRight;
	M5Gfx::GetWorldBotLeft(botLeft);
	M5Gfx::GetWorldTopRight(topRight);
	
	if (pos.x + scale.x > topRight.x || pos.x - scale.x < botLeft.x ||
		pos.y + scale.y > topRight.y || pos.y - scale.y < botLeft.y)
	{
		//M5ObjectPool<AT_Bullet>::ReleaseObject(m_pObj);
		m_pObj->isDead = true;
	}

}
/******************************************************************************/
/*!
Virtual constructor for this component
*/
/******************************************************************************/
M5Component* OutsideViewKillComponent::Clone(void)
{
	OutsideViewKillComponent* pNew = new OutsideViewKillComponent;
	pNew->m_pObj = m_pObj;
	return pNew;
}