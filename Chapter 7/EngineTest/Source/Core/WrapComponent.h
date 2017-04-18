/******************************************************************************/
/*!
\file   WrapComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Component to wrap an object in the screen
*/
/******************************************************************************/
#ifndef WRAP_COMPONENT_H
#define WRAP_COMPONENT_H

#include "M5Component.h"

//!< Component to wrap an object in the screen
class WrapComponent : public M5Component
{
public:
	WrapComponent(void);
	~WrapComponent(void);
	virtual void Update(float dt);
	virtual M5Component* Clone(void);
private:

};

#endif // !WRAP_COMPONENT_H

