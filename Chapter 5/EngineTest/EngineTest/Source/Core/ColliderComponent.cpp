/******************************************************************************/
/*!
file    ColliderComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/26

Component to be used with the Physics enigne.  This contains collion info
about it's game object.  For now, it only containts a radius.
*/
/******************************************************************************/
#include "ColliderComponent.h"

#include "M5Phy.h"
#include "M5IniFile.h"
#include "M5Object.h"
#include "M5Intersect.h"
#include "M5ComponentTypes.h"

ColliderComponent::ColliderComponent(void) :
	M5Component(CT_ColliderComponent),
	m_radius(0),
	m_isResizeable(false)
{
}
ColliderComponent::~ColliderComponent(void)
{
	M5Phy::UnregisterCollider(this);
}
void ColliderComponent::Update(float /*dt*/)
{
	//If (m_isResizeable) resize raduis based on scale

}
void ColliderComponent::FromFile(M5IniFile& iniFile)
{
	int resizeableValue = 0;
	iniFile.SetToSection("ColliderComponent");
	iniFile.GetValue("radius", m_radius);
	iniFile.GetValue("isResizeable", resizeableValue);
	m_isResizeable = resizeableValue == 1;
}
M5Component* ColliderComponent::Clone(void)
{
	ColliderComponent* pNew = new ColliderComponent;
	pNew->m_isResizeable = m_isResizeable;
	pNew->m_radius = m_radius;
	pNew->m_pObj = m_pObj;

	M5Phy::RegisterCollider(pNew);

	return pNew;

}
void ColliderComponent::TestCollision(const ColliderComponent* pOther)
{
	if (M5Intersect::CircleCircle(m_pObj->pos, m_radius,
		pOther->m_pObj->pos, pOther->m_radius))
	{
		M5Phy::AddCollisionPair(m_pObj->GetID(), pOther->m_pObj->GetID());
	}
}