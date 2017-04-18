/******************************************************************************/
/*!
\file   GrowToSizeComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/18

Grows the object to a give size the removes it self.

*/
/******************************************************************************/
#ifndef GROW_TO_SIZE_COMPONENT_H
#define GROW_TO_SIZE_COMPONENT_H

#include "Core\M5Component.h"
#include "Core\M5Vec2.h"

class GrowToSizeComponent : public M5Component
{
public:
	GrowToSizeComponent(void);
	virtual void Update(float dt);
	virtual void FromFile(M5IniFile& iniFile);
	virtual GrowToSizeComponent* Clone(void) const;

private:
	M5Vec2 m_rate;
	M5Vec2 m_maxSize;
};

#endif // !GROW_TO_SIZE_COMPONENT_H
