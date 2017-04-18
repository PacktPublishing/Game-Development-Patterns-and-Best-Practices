/******************************************************************************/
/*!
\file   SpaceShooterHelp.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/24

This is a helper function to load objects from an ini.  It may be used in 
a lot of stages so It is better to create this function.
*/
/******************************************************************************/
#ifndef SPACE_SHOOTER_HELP_H
#define SPACE_SHOOTER_HELP_H

//Forward declare inifile
class M5IniFile;

void LoadObjects(M5IniFile& iniFile);

#endif //SPACE_SHOOTER_HELP_H
