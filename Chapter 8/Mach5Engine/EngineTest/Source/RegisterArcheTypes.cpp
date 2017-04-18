/******************************************************************************/ 
/*! 
\file   RegisterArcheTypes.cpp 
\author PreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the ArcheTypes in the 
ArcheTypes Folder  UserPreBuild.bat looks for files named *.ini 
and registers those with the ObjectManager. 
*/ 
/******************************************************************************/ 
#include "Core\M5ArcheTypes.h" 
#include "Core\M5ObjectManager.h" 
 
 
void RegisterArcheTypes(void) {  
M5ObjectManager::AddArcheType(AT_1024x768Button, "ArcheTypes\\1024x768Button.ini"); 
M5ObjectManager::AddArcheType(AT_1280x768Button, "ArcheTypes\\1280x768Button.ini"); 
M5ObjectManager::AddArcheType(AT_800x600Button, "ArcheTypes\\800x600Button.ini"); 
M5ObjectManager::AddArcheType(AT_BackButton, "ArcheTypes\\BackButton.ini"); 
M5ObjectManager::AddArcheType(AT_Bullet, "ArcheTypes\\Bullet.ini"); 
M5ObjectManager::AddArcheType(AT_FullscreenButton, "ArcheTypes\\FullscreenButton.ini"); 
M5ObjectManager::AddArcheType(AT_GameOverTitle, "ArcheTypes\\GameOverTitle.ini"); 
M5ObjectManager::AddArcheType(AT_MenuAsteroid, "ArcheTypes\\MenuAsteroid.ini"); 
M5ObjectManager::AddArcheType(AT_MenuButton, "ArcheTypes\\MenuButton.ini"); 
M5ObjectManager::AddArcheType(AT_MenuSpawner, "ArcheTypes\\MenuSpawner.ini"); 
M5ObjectManager::AddArcheType(AT_MenuTitle, "ArcheTypes\\MenuTitle.ini"); 
M5ObjectManager::AddArcheType(AT_OptionsButton, "ArcheTypes\\OptionsButton.ini"); 
M5ObjectManager::AddArcheType(AT_OptionsTitle, "ArcheTypes\\OptionsTitle.ini"); 
M5ObjectManager::AddArcheType(AT_PauseTitle, "ArcheTypes\\PauseTitle.ini"); 
M5ObjectManager::AddArcheType(AT_PlayButton, "ArcheTypes\\PlayButton.ini"); 
M5ObjectManager::AddArcheType(AT_Player, "ArcheTypes\\Player.ini"); 
M5ObjectManager::AddArcheType(AT_QuitButton, "ArcheTypes\\QuitButton.ini"); 
M5ObjectManager::AddArcheType(AT_Raider, "ArcheTypes\\Raider.ini"); 
M5ObjectManager::AddArcheType(AT_Splash, "ArcheTypes\\Splash.ini"); 
M5ObjectManager::AddArcheType(AT_Ufo, "ArcheTypes\\Ufo.ini"); 
M5ObjectManager::AddArcheType(AT_WindowedButton, "ArcheTypes\\WindowedButton.ini"); 
} 
