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
#ifndef CHANGE_RESOLUTION_COMMAND_H
#define CHANGE_RESOLUTION_COMMAND_H

#include "M5Command.h"

//Forward Declaration
class M5IniFile;

class ChangeResolutionCommand : public M5Command
{
public:
	ChangeResolutionCommand(void);
	virtual void Execute(void);
	virtual ChangeResolutionCommand* Clone(void) const;
	virtual void FromFile(M5IniFile&);
private:
	int m_width;
	int m_height;


};


#endif //PAUSE_STAGE_COMMAND_H
