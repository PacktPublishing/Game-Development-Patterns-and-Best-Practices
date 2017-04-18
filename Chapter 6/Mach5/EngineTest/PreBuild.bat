::******************************************************************************
::Filename: PreBuild.bat
::author:   Matt Casanova 
::e-mail:   lazersquad@gmail.com
::Project:  Mach5 
::date:     2016/8/10
::
::Brief:
::The batch file recreate the enums and register files for a Mach 5 engine Game.
::******************************************************************************
@echo off

::Change to source directory
cd Source

echo CreateStageEnum
call:CreateStageEnum

echo CreateComponentEnum
call:CreateComponentEnum

echo CreateCommandEnum
call:CreateCommandEnum

echo CreateRegisterStages
call:CreateRegisterStages

echo CreateRegisterComponent
call:CreateRegisterComponent

echo CreateArcheTypeEnum
call:CreateArcheTypesEnum

echo CreateRegisterArcheType
call:CreateRegisterArcheTypes

goto:eof

::******************************************************************************
::Auto generates the RegisterStages.h files which registers all user 
::created stages with the StageManger
::******************************************************************************
:CreateRegisterStages
::Create output file
set HEADER=RegisterStages.h
set SOURCE=RegisterStages.cpp
::Add file header
echo /******************************************************************************/ > %HEADER%
echo /*! >> %HEADER%
echo \file   RegisterStages.h >> %HEADER%
echo \author PreBuild.bat >> %HEADER%
echo \par    email: lazersquad\@gmail.com >>%HEADER%
echo \par    Mach5 Game Engine >> %HEADER%
echo. >> %HEADER%
echo This file gets auto generated based on the names of the Stages in the >> %HEADER%
echo current project.  PreBuild.bat looks for files named *Stage.h >> %HEADER%
echo and registers those stages with the StageManager. >> %HEADER%
echo */ >> %HEADER%
echo /******************************************************************************/ >> %HEADER%

::Add Code Guards
echo #ifndef REGISTER_STAGES_H >> %HEADER%
echo #define REGISTER_STAGES_H >> %HEADER%
echo. >> %HEADER%

echo void RegisterStages(void);  >> %HEADER%
echo #endif //REGISTER_STAGES_H >> %HEADER%

::Do Source Files
echo /******************************************************************************/ > %SOURCE%
echo /*! >> %SOURCE%
echo \file   RegisterStages.cpp >> %SOURCE%
echo \author PreBuild.bat >> %SOURCE%
echo \par    email: lazersquad\@gmail.com >>%SOURCE%
echo \par    Mach5 Game Engine >> %SOURCE%
echo. >> %SOURCE%
echo This file gets auto generated based on the names of the Stages in the >> %SOURCE%
echo current project.  PreBuild.bat looks for files named *Stage.h >> %SOURCE%
echo and registers those stages with the StageManager. >> %SOURCE%
echo */ >> %SOURCE%
echo /******************************************************************************/ >> %SOURCE%
::Add includes
echo #include "RegisterStages.h" >> %SOURCE%
echo #include "Core\M5StageManager.h" >> %SOURCE%
echo #include "Core\M5StageTypes.h" >> %SOURCE%
echo #include "Core\M5StageBuilder.h" >> %SOURCE%

::Include all Stage header files
for %%f in ( *Stage.h ) do (
  echo #include "%%f" >> %SOURCE%
)
echo. >> %SOURCE%
echo. >> %SOURCE%

echo void RegisterStages(void) {  >> %SOURCE%
::Get all files with the name *Stage in it and output just the file name
for %%f in ( *Stage.h ) do (
  echo   M5StageManager::AddStage^(ST_%%~nf, new M5StageTBuilder^< %%~nf ^>^(^) ^); >> %SOURCE%
)
echo } >> %SOURCE%
goto:eof
::******************************************************************************
::Auto generates the RegisterComponents.h files which registers all user 
::created components with the ObjectManager
::******************************************************************************
:CreateRegisterComponent
::Create output file
set HEADER=RegisterComponents.h
set SOURCE=RegisterComponents.cpp
::Add file header
echo /******************************************************************************/ > %HEADER%
echo /*! >> %HEADER%
echo \file   %HEADER% >> %HEADER%
echo \author PreBuild.bat >> %HEADER%
echo \par    email: lazersquad\@gmail.com >>%HEADER%
echo \par    Mach5 Game Engine >> %HEADER%
echo. >> %HEADER%
echo This file gets auto generated based on the names of the Components in the >> %HEADER%
echo Include folder and current project.  PreBuild.bat looks for files named *Component.h >> %HEADER%
echo and registers those with the ObjectManager. >> %HEADER%
echo */ >> %HEADER%
echo /******************************************************************************/ >> %HEADER%
::Add Code Guards
echo #ifndef REGISTER_COMPONENTS_H >> %HEADER%
echo #define REGISTER_COMPONENTS_H >> %HEADER%
echo. >> %HEADER%
echo void RegisterComponents(void); >> %HEADER%
echo #endif //REGISTER_COMPONENTS_H >> %HEADER%



echo /******************************************************************************/ > %SOURCE%
echo /*! >> %SOURCE%
echo \file   %SOURCE% >> %SOURCE%
echo \author UserPreBuild.bat >> %SOURCE%
echo \par    email: lazersquad\@gmail.com >>%SOURCE%
echo \par    Mach5 Game Engine >> %SOURCE%
echo. >> %SOURCE%
echo This file gets auto generated based on the names of the Components in the >> %SOURCE%
echo Include folder and current project.  UserPreBuild.bat looks for files named *Component.h >> %SOURCE%
echo and registers those with the ObjectManager. >> %SOURCE%
echo */ >> %SOURCE%
echo /******************************************************************************/ >> %SOURCE%
::Add includes
echo #include "Core\M5ObjectManager.h" >> %SOURCE%
echo #include "Core\M5ComponentTypes.h" >> %SOURCE%
echo #include "Core\M5ComponentBuilder.h" >> %SOURCE%
::All Component header files from the Include folder
for %%f in ( Core\*???Component.h ) do (
  echo #include "Core\%%~nxf" >> %SOURCE%
)
::All Component header files from the current project
for %%f in ( *Component.h ) do (
  echo #include "%%f" >> %SOURCE%
)
echo. >> %SOURCE%
echo. >> %SOURCE%
echo void RegisterComponents(void) {  >> %SOURCE%
::All Component header files from the Include folder
for %%f in ( Core\*???Component.h ) do (
  echo  M5ObjectManager::AddComponent^(CT_%%~nf, new M5ComponentTBuilder^< %%~nf ^>^(^) ^); >> %SOURCE%
)
::All Component header files from the current project
for %%f in ( *Component.h ) do (
  echo  M5ObjectManager::AddComponent^(CT_%%~nf, new M5ComponentTBuilder^< %%~nf ^>^(^) ^); >> %SOURCE%
)
echo } >> %SOURCE%
goto:eof
::******************************************************************************
::Auto generates the RegisterArcheTypes.h file which adds ArcheTypes to the 
::ObjectManager 
::******************************************************************************
:CreateRegisterArcheTypes
::Create output file
set HEADER=RegisterArcheTypes.h
set SOURCE=RegisterArcheTypes.cpp
::Add file header
echo /******************************************************************************/ > %HEADER%
echo /*! >> %HEADER%
echo \file   RegisterArcheTypes.h >> %HEADER%
echo \author PreBuild.bat >> %HEADER%
echo \par    email: lazersquad\@gmail.com >>%HEADER%
echo \par    Mach5 Game Engine >> %HEADER%
echo. >> %HEADER%
echo This file gets auto generated based on the names of the ArcheTypes in the >> %HEADER%
echo ArcheTypes Folder  UserPreBuild.bat looks for files named *.ini >> %HEADER%
echo and registers those with the ObjectManager. >> %HEADER%
echo */ >> %HEADER%
echo /******************************************************************************/ >> %HEADER%
::Add Code Guards
echo #ifndef REGISTER_ARCHETYPES_H >> %HEADER%
echo #define REGISTER_ARCHETYPES_H >> %HEADER%
echo. >> %HEADER%
echo void RegisterArcheTypes(void);  >> %HEADER%
echo #endif //REGISTER_ARCHETYPES_H >> %HEADER%




echo /******************************************************************************/ > %SOURCE%
echo /*! >> %SOURCE%
echo \file   %SOURCE% >> %SOURCE%
echo \author PreBuild.bat >> %SOURCE%
echo \par    email: lazersquad\@gmail.com >>%SOURCE%
echo \par    Mach5 Game Engine >> %SOURCE%
echo. >> %SOURCE%
echo This file gets auto generated based on the names of the ArcheTypes in the >> %SOURCE%
echo ArcheTypes Folder  UserPreBuild.bat looks for files named *.ini >> %SOURCE%
echo and registers those with the ObjectManager. >> %SOURCE%
echo */ >> %SOURCE%
echo /******************************************************************************/ >> %SOURCE%
::Add includes
echo #include "Core\M5ArcheTypes.h" >> %SOURCE%
echo #include "Core\M5ObjectManager.h" >> %SOURCE%
echo. >> %SOURCE%
echo. >> %SOURCE%

echo void RegisterArcheTypes(void) {  >> %SOURCE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( ..\ArcheTypes\*.ini ) do (
  echo M5ObjectManager::AddArcheType^(AT_%%~nf, "ArcheTypes\\%%~nf.ini"^); >> %SOURCE%
)
echo } >> %SOURCE%

goto:eof
::******************************************************************************
::Auto generates the enum for M5StageTypes based on the files that the user created.
::******************************************************************************
:CreateStageEnum
::Create 
set ENUMFILE=Core\M5StageTypes.h
echo /******************************************************************************/ > %ENUMFILE%
echo /*! >> %ENUMFILE%
echo \file   M5StageTypes.h >> %ENUMFILE%
echo \author UserPreBuild.bat >> %ENUMFILE%
echo \par    email: lazersquad\@gmail.com >>%ENUMFILE%
echo \par    Mach5 Game Engine >> %ENUMFILE%
echo. >> %ENUMFILE%
echo This file gets auto generated based on the names of the Stages in the >> %ENUMFILE%
echo current project.  UserPreBuild.bat looks for files of the type *Stage.h >> %ENUMFILE%
echo and creates an enumeration value of ST_*Stage. >> %ENUMFILE%
echo */ >> %ENUMFILE%
echo /******************************************************************************/ >> %ENUMFILE%

echo #ifndef M5STAGE_TYPES_H >> %ENUMFILE%
echo #define M5STAGE_TYPES_H >> %ENUMFILE%
echo #include ^<string^> >> %ENUMFILE%
echo. >> %ENUMFILE%
echo. >> %ENUMFILE%
echo //! AutoGenerated enum based on stage file names  >> %ENUMFILE%
echo enum M5StageTypes {  >> %ENUMFILE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( *Stage.h ) do (
  echo ST_%%~nf, >> %ENUMFILE%
)
::Add one more to the end without the comma
echo ST_INVALID >> %ENUMFILE%
echo }; >> %ENUMFILE%
echo. >> %ENUMFILE%
echo. >> %ENUMFILE%


echo //! AutoGenerated function to convert strings to our M5StageTypes type >> %ENUMFILE%
echo inline M5StageTypes StringToStage^(const std::string^& string^) { >> %ENUMFILE%

)
for %%f in ( *Stage.h ) do (
  echo if^(string ^=^= "%%~nf"^) return ST_%%~nf; >> %ENUMFILE%
)
echo return ST_INVALID; >> %ENUMFILE%
echo } >> %ENUMFILE%

echo #endif //M5STAGE_TYPES_H >> %ENUMFILE%
mv %ENUMFILE% "..\..\Include\%ENUMFILE%" > nul 2> nul
goto:eof
::******************************************************************************
::Auto generates the enum for M5ComponentTypes based on the files that
:: the user created.
::******************************************************************************
:CreateComponentEnum

set ENUMFILE=Core\M5ComponentTypes.h
echo /******************************************************************************/ > %ENUMFILE%
echo /*! >> %ENUMFILE%
echo \file   M5ComponentTypes.h >> %ENUMFILE%
echo \author UserPreBuild.bat >> %ENUMFILE%
echo \par    email: lazersquad\@gmail.com >>%ENUMFILE%
echo \par    Mach5 Game Engine >> %ENUMFILE%
echo. >> %ENUMFILE%
echo This file gets auto generated based on the names of the Components in the >> %ENUMFILE%
echo current project.  UserPreBuild.bat looks for files of the type *Component.h >> %ENUMFILE%
echo and creates an enumeration value of CT_*Component. >> %ENUMFILE%
echo */ >> %ENUMFILE%
echo /******************************************************************************/ >> %ENUMFILE%

echo #ifndef M5COMPONENT_TYPE_H >> %ENUMFILE%
echo #define M5COMPONENT_TYPE_H >> %ENUMFILE%
echo #include ^<string^> >> %ENUMFILE%
echo. >> %ENUMFILE%
echo. >> %ENUMFILE%
echo //! AutoGenerated enum based on component file names  >> %ENUMFILE%
echo enum M5ComponentTypes {  >> %ENUMFILE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( Core\*???Component.h ) do (
  echo CT_%%~nf, >> %ENUMFILE%
)

for %%f in ( *Component.h ) do (
  echo CT_%%~nf, >> %ENUMFILE%
)
::Add one more to the end without the comma
echo CT_INVALID >> %ENUMFILE%


echo }; >> %ENUMFILE%
echo. >> %ENUMFILE%
echo. >> %ENUMFILE%

echo //! AutoGenerated function to convert strings to our M5ComponentTypes type >> %ENUMFILE%
echo inline M5ComponentTypes StringToComponent^(const std::string^& string^) { >> %ENUMFILE%

for %%f in ( Core\*???Component.h ) do (
  echo if^(string ^=^= "%%~nf"^) return CT_%%~nf; >> %ENUMFILE%
)
for %%f in ( *Component.h ) do (
  echo if^(string ^=^= "%%~nf"^) return CT_%%~nf; >> %ENUMFILE%
)
echo return CT_INVALID; >> %ENUMFILE%
echo } >> %ENUMFILE%
echo #endif //M5COMPONENT_TYPE_H >> %ENUMFILE%

goto:eof
::******************************************************************************
::Auto generates the enum for M5ArcheTypes based on the files that
:: the user created.
::******************************************************************************
:CreateArcheTypesEnum
::Create 
set ENUMFILE=Core\M5ArcheTypes.h
echo /******************************************************************************/ > %ENUMFILE%
echo /*! >> %ENUMFILE%
echo \file   M5ArcheTypes.h >> %ENUMFILE%
echo \author UserPreBuild.bat >> %ENUMFILE%
echo \par    email: lazersquad\@gmail.com >>%ENUMFILE%
echo \par    Mach5 Game Engine >> %ENUMFILE%
echo. >> %ENUMFILE%
echo This file gets auto generated based on the names of the ArcheTypes in the >> %ENUMFILE%
echo current project.  UserPreBuild.bat looks for files of the type *.ini in the ArcheTypes folder >> %ENUMFILE%
echo and creates an enumeration value of AT_*. >> %ENUMFILE%
echo */ >> %ENUMFILE%
echo /******************************************************************************/ >> %ENUMFILE%

echo #ifndef M5ARCHE_TYPES_H >> %ENUMFILE%
echo #define M5ARCHE_TYPES_H >> %ENUMFILE%
echo #include ^<string^> >> %ENUMFILE%
echo. >> %ENUMFILE%
echo. >> %ENUMFILE%
echo //! AutoGenerated enum based on archetype ini file names  >> %ENUMFILE%
echo enum M5ArcheTypes {  >> %ENUMFILE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( ..\ArcheTypes\*.ini ) do (
  echo AT_%%~nf, >> %ENUMFILE%
)

::Add one more to the end without the comma
echo AT_INVALID >> %ENUMFILE%
echo }; >> %ENUMFILE%

echo. >> %ENUMFILE%
echo. >> %ENUMFILE%

echo //! AutoGenerated function to convert strings to our M5ArcheTypes type >> %ENUMFILE%
echo inline M5ArcheTypes StringToArcheType^(const std::string^& string^) { >> %ENUMFILE%

for %%f in ( ..\ArcheTypes\*.ini ) do (
  echo if^(string ^=^= "%%~nf"^) return AT_%%~nf; >> %ENUMFILE%
)
echo return AT_INVALID; >> %ENUMFILE%
echo } >> %ENUMFILE%

echo #endif //M5ARCHE_TYPES_H >> %ENUMFILE%

goto:eof

::******************************************************************************
::Auto generates the enum for M5CommandTypes based on the files that
:: the user created.
::******************************************************************************
:CreateCommandEnum
set ENUMFILE=Core\M5CommandTypes.h
echo /******************************************************************************/ > %ENUMFILE%
echo /*! >> %ENUMFILE%
echo \file   M5CommmandTypes.h >> %ENUMFILE%
echo \author PreBuild.bat >> %ENUMFILE%
echo \par    email: lazersquad\@gmail.com >>%ENUMFILE%
echo \par    Mach5 Game Engine >> %ENUMFILE%
echo. >> %ENUMFILE%
echo This file gets auto generated based on the names of the commands in the >> %ENUMFILE%
echo current project.  PreBuild.bat looks for files of the type *Command.h >> %ENUMFILE%
echo and creates an enumeration value of CMD_*Command. >> %ENUMFILE%
echo */ >> %ENUMFILE%
echo /******************************************************************************/ >> %ENUMFILE%

echo #ifndef M5COMMAND_TYPE_H >> %ENUMFILE%
echo #define M5COMMAND_TYPE_H >> %ENUMFILE%
echo #include ^<string^> >> %ENUMFILE%
echo. >> %ENUMFILE%
echo. >> %ENUMFILE%
echo //! AutoGenerated enum based on command file names  >> %ENUMFILE%
echo enum M5CommandTypes {  >> %ENUMFILE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( Core\*???Command.h ) do (
  echo CMD_%%~nf, >> %ENUMFILE%
)

for %%f in ( *Command.h ) do (
  echo CMD_%%~nf, >> %ENUMFILE%
)
::Add one more to the end without the comma
echo CMD_INVALID >> %ENUMFILE%


echo }; >> %ENUMFILE%
echo. >> %ENUMFILE%
echo. >> %ENUMFILE%

echo //! AutoGenerated function to convert strings to our M5CommandTypes type >> %ENUMFILE%
echo inline M5CommandTypes StringToCommand^(const std::string^& string^) { >> %ENUMFILE%

for %%f in ( Core\*???Command.h ) do (
  echo if^(string ^=^= "%%~nf"^) return CMD_%%~nf; >> %ENUMFILE%
)
for %%f in ( *Command.h ) do (
  echo if^(string ^=^= "%%~nf"^) return CMD_%%~nf; >> %ENUMFILE%
)
echo return CMD_INVALID; >> %ENUMFILE%
echo } >> %ENUMFILE%
echo #endif //M5COMMAND_TYPE_H >> %ENUMFILE%





goto:eof




