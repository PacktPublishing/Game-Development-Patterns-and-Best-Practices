/******************************************************************************/
/*!
\file   ChangeResolutionCommand.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to change the resolution
*/
/******************************************************************************/
#include "ChangeResolutionCommand.h"
#include "M5App.h"
#include "M5IniFile.h"


ChangeResolutionCommand::ChangeResolutionCommand(void) :m_height(100), m_width(100)
{
}
void ChangeResolutionCommand::Execute(void)
{
	M5App::SetResolution(m_width, m_height);
}
ChangeResolutionCommand* ChangeResolutionCommand::Clone(void) const
{
	ChangeResolutionCommand* pClone = new ChangeResolutionCommand();
	pClone->m_width = m_width;
	pClone->m_height = m_height;
	return pClone;
}
void ChangeResolutionCommand::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("ChangeResolutionCommand");
	iniFile.GetValue("height", m_height);
	iniFile.GetValue("width", m_width);


}