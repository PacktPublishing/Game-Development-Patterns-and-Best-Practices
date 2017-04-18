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
#ifndef REPOSITION_COMPONENT_H
#define REPOSITION_COMPONENT_H

#include "M5Component.h"


//Foward Declarations
class M5IniFile;

//!< Removes The parent Game Object if it is outside the view port
class RepositionComponent : public M5Component
{
public:
	RepositionComponent(void);
	~RepositionComponent(void);
	virtual void Update(float dt);
	virtual RepositionComponent* Clone(void) const;
	virtual void FromFile(M5IniFile&);
private:
	float m_xScale;
	float m_yScale;
};

#endif // !REPOSITION_COMPONENT_H

