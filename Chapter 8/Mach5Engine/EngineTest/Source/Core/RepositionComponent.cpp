/******************************************************************************/
/*!
\file   RepositionComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/11/03

Repositions the object every frame so it stays reletive to the window
*/
/******************************************************************************/
#include "RepositionComponent.h"
#include "M5App.h"
#include "M5Math.h"
#include "M5Object.h"
#include "M5IniFile.h"

/******************************************************************************/
/*!
Contructor to set type.
*/
/******************************************************************************/
RepositionComponent::RepositionComponent(void) :
	M5Component(CT_RepositionComponent),m_xScale(0.0f), m_yScale(0.0f)
{
}
/******************************************************************************/
/*!
Destructor
*/
/******************************************************************************/
RepositionComponent::~RepositionComponent(void)
{
}
/******************************************************************************/
/*!
Sets object to dead if it is outside of the view port.  Right now this only
works if the viewport isn't rotated.
*/
/******************************************************************************/
void RepositionComponent::Update(float /*dt*/)
{
	M5Vec2 windowSize = M5App::GetResolution();
	m_pObj->pos.x = windowSize.x * m_xScale;
	m_pObj->pos.y = windowSize.y * m_yScale;
}
/******************************************************************************/
/*!
Virtual constructor for this component
*/
/******************************************************************************/
RepositionComponent* RepositionComponent::Clone(void) const
{
	RepositionComponent* pNew = new RepositionComponent;
	pNew->m_pObj = m_pObj;
	pNew->m_xScale = m_xScale;
	pNew->m_yScale = m_yScale;
	return pNew;
}
void RepositionComponent::FromFile(M5IniFile& iniFile) 
{
	iniFile.SetToSection("RepositionComponent");
	iniFile.GetValue("xScale", m_xScale);
	iniFile.GetValue("yScale", m_yScale);
}