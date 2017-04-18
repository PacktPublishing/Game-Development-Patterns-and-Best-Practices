/******************************************************************************/
/*!
\file   MenuSpawnerComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/18

Component to spawn objects from outward from the center
*/
/******************************************************************************/
#ifndef MENU_SPAWNER_COMPONENT_H
#define MENU_SPAWNER_COMPONENT_H

#include "Core\M5Component.h"
#include "Core\M5ArcheTypes.h"

class MenuSpawnerComponent : public M5Component
{
public:
	MenuSpawnerComponent(void);

	virtual void Update(float dt);
	virtual void FromFile(M5IniFile& iniFIle);
	virtual MenuSpawnerComponent* Clone(void) const;
private:
	M5ArcheTypes m_type;
	float m_velMin;
	float m_velMax;
	float m_timer;
	float m_maxTime;

};


#endif //MENU_SPAWNER_COMPONENT_H