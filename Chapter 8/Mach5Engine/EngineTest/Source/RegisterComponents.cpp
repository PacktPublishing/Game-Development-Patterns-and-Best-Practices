/******************************************************************************/ 
/*! 
\file   RegisterComponents.cpp 
\author UserPreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the Components in the 
Include folder and current project.  UserPreBuild.bat looks for files named *Component.h 
and registers those with the ObjectManager. 
*/ 
/******************************************************************************/ 
#include "Core\M5ObjectManager.h" 
#include "Core\M5ComponentTypes.h" 
#include "Core\M5ComponentBuilder.h" 
#include "Core\ClampComponent.h" 
#include "Core\ColliderComponent.h" 
#include "Core\GfxComponent.h" 
#include "Core\OutsideViewKillComponent.h" 
#include "Core\RepositionComponent.h" 
#include "Core\UIButtonComponent.h" 
#include "Core\WrapComponent.h" 
#include "ChasePlayerComponent.h" 
#include "GrowToSizeComponent.h" 
#include "MenuSpawnerComponent.h" 
#include "PlayerInputComponent.h" 
#include "RandomGoComponent.h" 
#include "ShrinkComponent.h" 
 
 
void RegisterComponents(void) {  
 M5ObjectManager::AddComponent(CT_ClampComponent, new M5ComponentTBuilder< ClampComponent >() ); 
 M5ObjectManager::AddComponent(CT_ColliderComponent, new M5ComponentTBuilder< ColliderComponent >() ); 
 M5ObjectManager::AddComponent(CT_GfxComponent, new M5ComponentTBuilder< GfxComponent >() ); 
 M5ObjectManager::AddComponent(CT_OutsideViewKillComponent, new M5ComponentTBuilder< OutsideViewKillComponent >() ); 
 M5ObjectManager::AddComponent(CT_RepositionComponent, new M5ComponentTBuilder< RepositionComponent >() ); 
 M5ObjectManager::AddComponent(CT_UIButtonComponent, new M5ComponentTBuilder< UIButtonComponent >() ); 
 M5ObjectManager::AddComponent(CT_WrapComponent, new M5ComponentTBuilder< WrapComponent >() ); 
 M5ObjectManager::AddComponent(CT_ChasePlayerComponent, new M5ComponentTBuilder< ChasePlayerComponent >() ); 
 M5ObjectManager::AddComponent(CT_GrowToSizeComponent, new M5ComponentTBuilder< GrowToSizeComponent >() ); 
 M5ObjectManager::AddComponent(CT_MenuSpawnerComponent, new M5ComponentTBuilder< MenuSpawnerComponent >() ); 
 M5ObjectManager::AddComponent(CT_PlayerInputComponent, new M5ComponentTBuilder< PlayerInputComponent >() ); 
 M5ObjectManager::AddComponent(CT_RandomGoComponent, new M5ComponentTBuilder< RandomGoComponent >() ); 
 M5ObjectManager::AddComponent(CT_ShrinkComponent, new M5ComponentTBuilder< ShrinkComponent >() ); 
} 
