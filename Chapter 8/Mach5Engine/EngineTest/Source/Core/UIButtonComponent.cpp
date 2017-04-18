/******************************************************************************/
/*!
\file   UIButtonComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Component to test if a HUD button is clicked
*/
/******************************************************************************/
#include "UIButtonComponent.h"
#include "M5Command.h"
#include "M5CommandTypes.h"

#include "M5Intersect.h"
#include "M5Input.h"
#include "M5Debug.h"
#include "M5Object.h"
#include "M5IniFile.h"
#include "M5ObjectManager.h"

#include <string>

/******************************************************************************/
/*!
Constructor to Set the type
*/
/******************************************************************************/
UIButtonComponent::UIButtonComponent(void) :
	M5Component(CT_UIButtonComponent), m_pOnClick(nullptr)
{
}
/******************************************************************************/
/*!
Destructor for the UIButton Component
*/
/******************************************************************************/
UIButtonComponent::~UIButtonComponent(void)
{
	delete m_pOnClick;
	m_pOnClick = 0;
}
/******************************************************************************/
/*!
Checks if the button has been clicked in screen space
*/
/******************************************************************************/
void UIButtonComponent::Update(float)
{
	if (M5Input::IsTriggered(M5_MOUSE_LEFT))
	{
		M5Vec2 clickPoint;
		M5Input::GetMouse(clickPoint);
		if (M5Intersect::PointRect(clickPoint, m_pObj->pos, m_pObj->scale.x, m_pObj->scale.y))
		{
			M5DEBUG_ASSERT(m_pOnClick != 0, "The UIButton command is null");
			m_pOnClick->Execute();
		}
	}
}
/******************************************************************************/
/*!
Reads the command for the button from an inifile

\param iniFile
The ini file to read from
*/
/******************************************************************************/
void UIButtonComponent::FromFile(M5IniFile& iniFile)
{
	std::string commandType;
	iniFile.SetToSection("UIButtonComponent");
	iniFile.GetValue("command", commandType);
	m_pOnClick = M5ObjectManager::CreateCommand(StringToCommand(commandType));
	m_pOnClick->FromFile(iniFile);
}
/******************************************************************************/
/*!
virtual contructor for the UIButtonComponent
*/
/******************************************************************************/
UIButtonComponent* UIButtonComponent::Clone(void) const
{
	UIButtonComponent* pClone = new UIButtonComponent();
	pClone->m_pObj = m_pObj;
	if(m_pOnClick != nullptr)
	  pClone->m_pOnClick = m_pOnClick->Clone();
	return pClone;
}
/******************************************************************************/
/*!
Sets the command of the given UIButton onClick action, and deletes the old one

\param [in] pCommand
The new command to set
*/
/******************************************************************************/
void UIButtonComponent::SetOnClick(M5Command* pCommand)
{
	//Make sure to delete the old one
	delete m_pOnClick;
	m_pOnClick = pCommand;
}

