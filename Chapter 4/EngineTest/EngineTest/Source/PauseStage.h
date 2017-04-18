/******************************************************************************/
/*!
\file   PauseStage.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/26

Stage for a Pause Menu
*/
/******************************************************************************/
#ifndef PAUSE_STAGE_H
#define PAUSE_STAGE_H

#include "Core\M5Stage.h"

class PauseStage : public M5Stage
{
public:
	PauseStage(void);
	~PauseStage(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
private:
};

#endif //PAUSE_STAGE_H