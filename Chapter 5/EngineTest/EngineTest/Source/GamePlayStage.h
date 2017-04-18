/******************************************************************************/
/*!
\file   GamePlayStage.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

This is the stage for game play in AstroShot
*/
/******************************************************************************/
#ifndef GAMEPLAY_STAGE_H
#define GAMEPLAY_STAGE_H

#include "Core\M5Stage.h"

class GamePlayStage : public M5Stage
{
public:
	GamePlayStage(void);
	~GamePlayStage(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
private:
};


#endif /* GAMEPLAY_STAGE_H */