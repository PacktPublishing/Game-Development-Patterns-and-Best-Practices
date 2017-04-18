/******************************************************************************/ 
/*! 
\file   RegisterCommands.cpp 
\author PreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the Commands in the 
Include folder and current project.  PreBuild.bat looks for files named *Command.h 
and registers those with the ObjectManager. 
*/ 
/******************************************************************************/ 
#include "Core\M5ObjectManager.h" 
#include "Core\M5CommandTypes.h" 
#include "Core\M5TBuilder.h" 
#include "Core\ChangeResolutionCommand.h" 
#include "Core\ChangeStageCommand.h" 
#include "Core\M5Command.h" 
#include "Core\PauseStageCommand.h" 
#include "Core\QuitCommand.h" 
#include "Core\ResumeStageCommand.h" 
#include "Core\SetFullscreenCommand.h" 
 
 
void RegisterCommands(void) {  
 M5ObjectManager::AddCommand(CMD_ChangeResolutionCommand, new ChangeResolutionCommand() ); 
 M5ObjectManager::AddCommand(CMD_ChangeStageCommand, new ChangeStageCommand() ); 
 M5ObjectManager::AddCommand(CMD_PauseStageCommand, new PauseStageCommand() ); 
 M5ObjectManager::AddCommand(CMD_QuitCommand, new QuitCommand() ); 
 M5ObjectManager::AddCommand(CMD_ResumeStageCommand, new ResumeStageCommand() ); 
 M5ObjectManager::AddCommand(CMD_SetFullscreenCommand, new SetFullscreenCommand() ); 
} 
