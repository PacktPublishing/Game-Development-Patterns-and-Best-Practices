/******************************************************************************/
/*!
\file   PlayerInputComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Player input for AstroShot
*/
/******************************************************************************/
#ifndef PLAYER_INPUT_COMPONENT
#define PLAYER_INPUT_COMPONENT

#include "Core/M5Component.h"

//!< Player input component for AstroShot
class PlayerInputComponent : public M5Component
{
public:
	PlayerInputComponent(void);
	~PlayerInputComponent(void);
	virtual void Update(float dt);
	virtual M5Component* Clone(void);
	virtual void FromFile(M5IniFile& iniFile);
private:
	float m_forwardSpeed;
	float m_speedDamp;
	float m_bulletSpeed;
	float m_rotationSpeed;

};

#endif // !PLAYER_INPUT_COMPONENT

