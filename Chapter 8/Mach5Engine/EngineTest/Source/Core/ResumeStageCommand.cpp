/******************************************************************************/
/*!
\file   ResumeStageCommand.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to change stages
*/
/******************************************************************************/
#include "ResumeStageCommand.h"
#include "M5StageManager.h"

void ResumeStageCommand::Execute(void)
{
	M5StageManager::Resume();
}
ResumeStageCommand* ResumeStageCommand::Clone(void) const
{
	ResumeStageCommand* pClone = new ResumeStageCommand();
	return pClone;
}