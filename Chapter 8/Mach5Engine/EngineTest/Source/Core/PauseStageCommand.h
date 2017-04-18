/******************************************************************************/
/*!
\file   PauseStageCommand.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to Pause a stage
*/
/******************************************************************************/
#ifndef PAUSE_STAGE_COMMAND_H
#define PAUSE_STAGE_COMMAND_H

#include "M5Command.h"
#include "M5StageTypes.h"
#include <string>
//Forward Declaration
class M5IniFile;

class PauseStageCommand : public M5Command
{
public:
	PauseStageCommand(M5StageTypes nextStage);
	PauseStageCommand(void);
	virtual void Execute(void);
	void SetNextStage(M5StageTypes nextStage);
	virtual PauseStageCommand* Clone(void) const;
	virtual void FromFile(M5IniFile&);
private:
	M5StageTypes m_stage;
	std::string  m_menuFile;
	bool         m_drawPaused;


};


#endif //PAUSE_STAGE_COMMAND_H
