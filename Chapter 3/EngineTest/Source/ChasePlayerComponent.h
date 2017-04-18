/******************************************************************************/
/*!
\file   ChasePlayerComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/09

Simple AI to Chase the Player
*/
/******************************************************************************/
#ifndef CHASE_PLAYER_COMPONENT_H
#define CHASE_PLAYER_COMPONENT_H

#include "Core/M5Component.h"

//!< Simple AI to Chase the Player
class ChasePlayerComponent : public M5Component
{
public:
	ChasePlayerComponent(void);
	virtual void Update(float dt);
	virtual void FromFile(M5IniFile& iniFile);
	virtual M5Component* Clone(void);
private:
	float m_speed;

};

#endif //CHASE_PLAYER_COMPONENT_H
