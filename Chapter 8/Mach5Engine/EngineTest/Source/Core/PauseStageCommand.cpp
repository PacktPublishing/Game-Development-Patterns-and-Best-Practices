/******************************************************************************/
/*!
\file   PauseStageCommand.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to pause a stage
*/
/******************************************************************************/
#include "PauseStageCommand.h"
#include "M5StageManager.h"
#include "M5GameData.h"
#include "M5IniFile.h"


PauseStageCommand::PauseStageCommand(M5StageTypes nextStage) :
	m_stage(nextStage),m_drawPaused(false)
{
}
PauseStageCommand::PauseStageCommand(void) : m_stage(ST_INVALID)
{
}
void PauseStageCommand::Execute(void)
{
	M5StageManager::PauseAndSetNextStage(m_stage, m_drawPaused);
	M5StageManager::GetGameData().menuFile = m_menuFile;
}
PauseStageCommand* PauseStageCommand::Clone(void) const
{
	PauseStageCommand* pClone = new PauseStageCommand();
	pClone->m_stage = m_stage;
	pClone->m_menuFile = m_menuFile;
	pClone->m_drawPaused = m_drawPaused;
	return pClone;
}
void PauseStageCommand::SetNextStage(M5StageTypes nextStage)
{
	m_stage = nextStage;
}
void PauseStageCommand::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("PauseStageCommand");
	std::string nextStage;
	iniFile.GetValue("next", nextStage);
	iniFile.GetValue("menuFile", m_menuFile);
	iniFile.GetValue("drawPaused", m_drawPaused);

	m_stage = StringToStage(nextStage);

}