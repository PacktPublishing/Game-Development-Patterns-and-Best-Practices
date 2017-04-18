/******************************************************************************/
/*!
\file   ChangeStageCommand.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to change stages
*/
/******************************************************************************/
#include "ChangeStageCommand.h"
#include "M5StageManager.h"
#include "M5GameData.h"
#include "M5IniFile.h"


ChangeStageCommand::ChangeStageCommand(M5StageTypes nextStage):m_stage(nextStage)
{
}
ChangeStageCommand::ChangeStageCommand(void) :m_stage(ST_INVALID)
{
}
void ChangeStageCommand::Execute(void)
{
	M5StageManager::SetNextStage(m_stage);
	M5StageManager::GetGameData().menuFile = m_menuFile;
}
ChangeStageCommand* ChangeStageCommand::Clone(void) const
{
	ChangeStageCommand* pClone = new ChangeStageCommand(*this);
	return pClone;
}
void ChangeStageCommand::SetNextStage(M5StageTypes nextStage)
{
	m_stage = nextStage;
}
void ChangeStageCommand::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("ChangeStageCommand");
	std::string nextStage;
	iniFile.GetValue("next", nextStage);
	iniFile.GetValue("menuFile", m_menuFile);
	
	m_stage = StringToStage(nextStage);

}