/******************************************************************************/
/*!
\file   M5GameData.h
\author Matt Casanova 
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/8

This is a struct that you can define your own game specific game data in. This
is data that needs to be shared across stages, such as player lives or game
score.  You should initilize the values in main before calling 
M5App::Init.
*/
/******************************************************************************/
#ifndef M5GAMEDATA_H
#define M5GAMEDATA_H

/*! This struct holds game data that is shared between stages. This struct must
have at least one data member in it.*/
struct M5GameData
{
  /*!< This should be removed and used for your game specific data */
  int yourGameDataHere;
};

#endif /* GameData_H */