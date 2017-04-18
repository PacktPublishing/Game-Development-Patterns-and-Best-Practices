/******************************************************************************/
/*!
\file   SetFullscreenCommand.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command set full screen to true or false
*/
/******************************************************************************/
#ifndef SET_FULLSCREEN_COMMAND_H
#define SET_FULLSCREEN_COMMAND_H

#include "M5Command.h"

//Forward Declaration
class M5IniFile;

class SetFullscreenCommand : public M5Command
{
public:
	SetFullscreenCommand(void);
	virtual void Execute(void);
	virtual SetFullscreenCommand* Clone(void) const;
	virtual void FromFile(M5IniFile&);
private:
	bool m_isFullscreen;


};


#endif //SET_FULLSCREEN_COMMAND_H
