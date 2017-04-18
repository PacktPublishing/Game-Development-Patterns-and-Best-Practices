/******************************************************************************/
/*!
\file   ShrinkComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/05

Shrink Debuff Component
*/
/******************************************************************************/
#ifndef SHRINK_COMPONENT_H
#define SHRINK_COMPONENT_H

#include "Core/M5Component.h"
#include "Core/M5Vec2.h"

//!< Shrink Debuff for AstroShot
class ShrinkComponent : public M5Component
{
public:
	ShrinkComponent(void);
	~ShrinkComponent(void);
	virtual void Update(float dt);
	virtual ShrinkComponent* Clone(void) const;
private:
	M5Vec2 m_oldScale;
	bool m_hasStarted;
	float m_timer;
	float m_maxTime;

};

#endif //SHRINK_COMPONENT_H
