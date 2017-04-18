/******************************************************************************/
/*!
\file   M5StageManager.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/7

Singleton to control quitting, restarting and switching stages.

*/
/******************************************************************************/
#ifndef M5_STAGEMGR_H
#define M5_STAGEMGR_H

//Forward Declarations
class M5Stage;
struct M5GameData;
class M5StageBuilder;

#include "M5StageTypes.h"


//! Singleton to control quitting, restarting and switching stages.
class M5StageManager
{
public:
  friend class M5App;

  //Registers a GameStage and a builder with the the StageManger
  static void AddStage(M5StageTypes type, M5StageBuilder* builder);
  //Removes a Stage Builder from the Manager
  static void RemoveStage(M5StageTypes type);
  //Clears all stages from the StageManager
  static void ClearStages(void);
  //Sets the given stage ID to the starting stage of the game
  static void SetStartStage(M5StageTypes startStage);
  //Test if the game is quitting
  static bool IsQuitting(void);
  //Test stage is restarting
  static bool IsRestarting(void);
  //Gets the previous stage of the game
  static int  GetPreviousStage(void);
  //Gets the Current Stage of the game
  static int  GetCurrentStage(void);
  //Gets the Next stage of the game
  static int  GetNextStage(void);
  //Gets the pointer to the users game specific data
  static M5GameData& GetGameData(void);
  //Sets the next stage for the game
  static void SetNextStage(M5StageTypes nextStage);
  //Tells the game to quit
  static void Quit(void);
  //Tells the stage to restart
  static void Restart(void);

private:
  static void Init(const M5GameData* gameData, int gameDataSize, int framesPerSecond);
  static void Update(void);
  static void Shutdown(void);
  static void ChangeStage(void);

};//end M5StageManager



#endif //M5_STAGEMGR_H