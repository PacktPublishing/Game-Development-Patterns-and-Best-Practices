/******************************************************************************/
/*!
\file   QuitCommand.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/18

Creates a command to Quit the game
*/
/******************************************************************************/
#ifndef QUIT_COMMAND_H
#define QUIT_COMMAND_H

#include "M5Command.h"

class QuitCommand : public M5Command
{
public:
	virtual void Execute(void);
	virtual QuitCommand* Clone(void) const;
private:
};

#endif //QUIT_COMMAND_H