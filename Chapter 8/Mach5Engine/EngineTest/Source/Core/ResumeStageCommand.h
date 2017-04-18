/******************************************************************************/
/*!
\file   ResumeStageCommand.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to Resume a stage
*/
/******************************************************************************/
#ifndef RESUME_STAGE_COMMAND_H
#define RESUME_STAGE_COMMAND_H

#include "M5Command.h"
//Forward Declaration
class M5IniFile;

class ResumeStageCommand : public M5Command
{
public:
	virtual void Execute(void);
	virtual ResumeStageCommand* Clone(void) const;
private:



};


#endif //RESUME_STAGE_COMMAND_H
#pragma once
