/******************************************************************************/ 
/*! 
\file   RegisterArcheTypes.h 
\author PreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the ArcheTypes in the 
ArcheTypes Folder  UserPreBuild.bat looks for files named *.ini 
and registers those with the ObjectManager. 
*/ 
/******************************************************************************/ 
#ifndef REGISTER_ARCHETYPES_H 
#define REGISTER_ARCHETYPES_H 
 
#include "Core\M5ArcheTypes.h" 
#include "Core\M5ObjectManager.h" 
 
 
inline void RegisterArcheTypes(void) {  
M5ObjectManager::AddArcheType(AT_Bullet, "ArcheTypes\\Bullet.ini"); 
M5ObjectManager::AddArcheType(AT_Player, "ArcheTypes\\Player.ini"); 
M5ObjectManager::AddArcheType(AT_Raider, "ArcheTypes\\Raider.ini"); 
M5ObjectManager::AddArcheType(AT_Splash, "ArcheTypes\\Splash.ini"); 
} 
#endif //REGISTER_ARCHETYPES_H 
