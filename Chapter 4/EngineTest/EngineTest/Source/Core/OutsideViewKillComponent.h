/******************************************************************************/
/*!
\file   OutsideViewKillComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Removes The parent Game Object if it is outside the view port.  Right now 
this only works if the viewport isn't rotated.

TODO: Remove Object from rotated viewport
*/
/******************************************************************************/
#ifndef OUTSIDE_VIEWPORT_KILL_COMPONENT_H
#define OUTSIDE_VIEWPORT_KILL_COMPONENT_H

#include "M5Component.h"

//!< Removes The parent Game Object if it is outside the view port
class OutsideViewKillComponent : public M5Component
{
public:
	OutsideViewKillComponent(void);
	~OutsideViewKillComponent(void);
	virtual void Update(float dt);
	virtual M5Component* Clone(void);
private:

};

#endif // !OUTSIDE_VIEWPORT_KILL_COMPONENT_H

