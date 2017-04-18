/******************************************************************************/
/*!
\file   SpaceShooterHelp.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/24

This is a helper function to load objects from an ini.  It may be used in
a lot of stages so It is better to create this function.
*/
/******************************************************************************/
#include "SpaceShooterHelp.h"

#include "Core\M5ObjectManager.h"
#include "Core\M5IniFile.h"
#include "Core\M5ArcheTypes.h"
#include "Core\M5Object.h"
#include <sstream>
#include <iomanip>

/******************************************************************************/
/*!
Loads stage objects from a pre opened ini file.

\param [in] iniFile
A pre-opened Stage iniFile to load object from

*/
/******************************************************************************/
void LoadObjects(M5IniFile& iniFile)
{
	//Get my list of ArcheTypes from the file
	std::string archeTypesList;
	iniFile.GetValue("ArcheTypes", archeTypesList);
	//Load list into stream
	std::stringstream ss(archeTypesList);
	//Variables to read from file
	int count;
	std::string posList;

	std::string typeAsString;
	while (ss >> typeAsString)
	{
		//Start reading current section of ini
		iniFile.SetToSection(typeAsString);
		//Get nessisary vars from file
		iniFile.GetValue("count", count);
		iniFile.GetValue("pos", posList);
		//Load position list into stream
		std::stringstream posStream(posList);

		//Create my objects and set postions
		for (int i = 0; i < count; ++i)
		{
			M5ArcheTypes typeAsEnum = StringToArcheType(typeAsString);
			M5Object* pObj = M5ObjectManager::CreateObject(typeAsEnum);
			posStream >> pObj->pos;
		}
	}
}