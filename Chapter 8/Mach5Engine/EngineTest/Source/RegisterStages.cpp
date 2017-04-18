/******************************************************************************/ 
/*! 
\file   RegisterStages.cpp 
\author PreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the Stages in the 
current project.  PreBuild.bat looks for files named *Stage.h 
and registers those stages with the StageManager. 
*/ 
/******************************************************************************/ 
#include "RegisterStages.h" 
#include "Core\M5StageManager.h" 
#include "Core\M5StageTypes.h" 
#include "Core\M5StageBuilder.h" 
#include "GamePlayStage.h" 
#include "MenuStage.h" 
#include "SplashStage.h" 
 
 
void RegisterStages(void) {  
  M5StageManager::AddStage(ST_GamePlayStage, new M5StageTBuilder< GamePlayStage >() ); 
  M5StageManager::AddStage(ST_MenuStage, new M5StageTBuilder< MenuStage >() ); 
  M5StageManager::AddStage(ST_SplashStage, new M5StageTBuilder< SplashStage >() ); 
} 
