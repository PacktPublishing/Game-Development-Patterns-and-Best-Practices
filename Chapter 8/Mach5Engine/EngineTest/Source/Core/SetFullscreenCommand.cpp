/******************************************************************************/
/*!
\file   SetFullscreenCommand.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to change the resolution
*/
/******************************************************************************/
#include "SetFullscreenCommand.h"
#include "M5App.h"
#include "M5IniFile.h"


SetFullscreenCommand::SetFullscreenCommand(void) :m_isFullscreen(false)
{
}
void SetFullscreenCommand::Execute(void)
{
	M5App::SetFullScreen(m_isFullscreen);
}
SetFullscreenCommand* SetFullscreenCommand::Clone(void) const
{
	SetFullscreenCommand* pClone = new SetFullscreenCommand();
	pClone->m_isFullscreen = m_isFullscreen;
	return pClone;
}
void SetFullscreenCommand::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("SetFullscreenCommand");
	iniFile.GetValue("isFullscreen", m_isFullscreen);


}