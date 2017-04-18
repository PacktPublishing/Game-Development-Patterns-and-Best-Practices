/******************************************************************************/
/*!
\file   MenuStage.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/17

The MenuStage in AstroShot
*/
/******************************************************************************/
#ifndef MENU_STAGE_H
#define MENU_STAGE_H

#include "Core\M5Stage.h"

class MenuStage : public M5Stage
{
public:
	MenuStage(void);
	~MenuStage(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
private:
};

#endif //MENU_STAGE_H