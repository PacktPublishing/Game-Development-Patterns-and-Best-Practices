/******************************************************************************/
/*!
file    ColliderComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/26

Component to be used with the Physics enigne.  This contains collion info
about it's game object.  For now, it only containts a radius.
*/
/******************************************************************************/
#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "M5Component.h"

class ColliderComponent : public M5Component
{
public:
	ColliderComponent(void);
	~ColliderComponent(void);
	virtual void Update(float dt);
	virtual void FromFile(M5IniFile& iniFile);
	virtual M5Component* Clone(void);
	void TestCollision(const ColliderComponent* pOther);


private:
	float m_radius;
	bool  m_isResizeable;
};

#endif //COLLIDER_COMPONENT_H