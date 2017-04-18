/******************************************************************************/
/*!
\file   GrowToSizeComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/18

Grows the object to a give size the removes it self.

*/
/******************************************************************************/
#include "GrowToSizeComponent.h"
#include "Core\M5Object.h"
#include "Core\M5IniFile.h"

GrowToSizeComponent::GrowToSizeComponent(void):
	M5Component(CT_GrowToSizeComponent),
	m_rate(1, 1),
	m_maxSize(1, 1)
{

}
void GrowToSizeComponent::Update(float dt)
{
	bool lessThanX = m_pObj->scale.x < m_maxSize.x;
	bool lessThanY = m_pObj->scale.y < m_maxSize.y;
	if(lessThanX)
		m_pObj->scale.x += m_rate.x * dt;

	if (lessThanY)
		m_pObj->scale.y += m_rate.y * dt;

	if (!lessThanX && !lessThanY)
		isDead = true;
}
void GrowToSizeComponent::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("GrowToSizeComponent");
	iniFile.GetValue("rateX", m_rate.x);
	iniFile.GetValue("rateY", m_rate.y);
	iniFile.GetValue("maxX", m_maxSize.x);
	iniFile.GetValue("maxY", m_maxSize.y);

}
GrowToSizeComponent* GrowToSizeComponent::Clone(void) const
{
	GrowToSizeComponent* pClone = new GrowToSizeComponent();
	pClone->m_rate = m_rate;
	pClone->m_maxSize = m_maxSize;
	pClone->m_pObj = m_pObj;

	return pClone;

}