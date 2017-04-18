/******************************************************************************/ 
/*! 
\file   RegisterStages.h 
\author UserPreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the Stages in the 
current project.  UserPreBuild.bat looks for files named *Stage.h 
and registers those stages with the StageManager. 
*/ 
/******************************************************************************/ 
#ifndef REGISTER_STAGES_H 
#define REGISTER_STAGES_H 
 
#include "Core\M5StageManager.h" 
#include "Core\M5StageTypes.h" 
#include "Core\M5StageBuilder.h" 
#include "GamePlayStage.h" 
#include "PauseStage.h" 
#include "SplashStage.h" 
 
 
inline void RegisterStages(void) {  
 M5StageManager::AddStage(ST_GamePlayStage, new M5StageTBuilder< GamePlayStage >() ); 
 M5StageManager::AddStage(ST_PauseStage, new M5StageTBuilder< PauseStage >() ); 
 M5StageManager::AddStage(ST_SplashStage, new M5StageTBuilder< SplashStage >() ); 
} 
#endif //REGISTER_STAGES_H 
