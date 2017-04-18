/******************************************************************************/
/*!
\file   ChangeStageCommand.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to change stages
*/
/******************************************************************************/
#ifndef CHANGE_STAGE_COMMAND_H
#define CHANGE_STAGE_COMMAND_H

#include "M5Command.h"
#include "M5StageTypes.h"
#include <string>
//Forward Declaration
class M5IniFile;

class ChangeStageCommand : public M5Command
{
public:
	ChangeStageCommand(M5StageTypes nextStage);
	ChangeStageCommand(void);
	virtual void Execute(void);
	void SetNextStage(M5StageTypes nextStage);
	virtual ChangeStageCommand* Clone(void) const;
	virtual void FromFile(M5IniFile&);
private:
	M5StageTypes m_stage;
	std::string  m_menuFile;


};


#endif //CHANGE_STAGE_COMMAND_H
