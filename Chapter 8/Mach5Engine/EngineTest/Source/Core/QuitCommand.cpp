/******************************************************************************/
/*!
\file   QuitCommand.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/18

Creates a command to Quit the game
*/
/******************************************************************************/
#include "QuitCommand.h"
#include "M5StageManager.h"
#include "M5ObjectManager.h"

void QuitCommand::Execute(void)
{
	M5StageManager::Quit();
}
QuitCommand* QuitCommand::Clone(void) const
{
	return new QuitCommand();
}