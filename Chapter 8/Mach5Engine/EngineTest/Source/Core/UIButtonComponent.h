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
#ifndef BUTTON_COMPONENT_H
#define BUTTON_COMPONENT_H

#include "M5Component.h"
#include "M5Vec2.h"

//forward declare
class M5Command;


//!< Component to give a clickable command to an object
class UIButtonComponent : public M5Component
{
public:
	UIButtonComponent(void);
	~UIButtonComponent(void);
	virtual void     Update(float dt);
	virtual void     FromFile(M5IniFile&);
	virtual UIButtonComponent* Clone(void) const;
	void SetOnClick(M5Command* pCommand);
private:
	M5Command* m_pOnClick;
};


#endif //UIBUTTON_COMPONENT_H