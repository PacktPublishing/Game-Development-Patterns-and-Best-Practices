/******************************************************************************/
/*!
\file   ClampComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Component to Clamp an object in the screen
*/
/******************************************************************************/
#ifndef CLAMP_COMPONENT_H
#define CLAMP_COMPONENT_H
#include "M5Component.h"

//! Component to Clamp an object in the screen
class ClampComponent : public M5Component
{
public:
	ClampComponent();
	virtual void Update(float dt);
	virtual ClampComponent* Clone(void) const;
};

#endif //CLAMP_COMPONENT_H

