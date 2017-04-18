/******************************************************************************/
/*!
\file   M5App.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/6

A globably accessable Static class for Creating and controlling the window in 
the Mach 5 Engine.
*/
/******************************************************************************/
#ifndef M5_APP_H
#define M5_APP_H

#include "M5Vec2.h"

/*! Used to exclude rarely-used stuff from Windows */
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

//Forward Declarations
struct M5GameData;

/*! A Struct used to initialize the system.*/
struct M5InitData
{
  HINSTANCE   instance;    /*!< The Instance from WinMain*/
  const char* title;       /*!< The title of the window in windoM5d mode*/
  M5GameData* pGData;      /*!< A pointer that contains the intial game values*/
  int         gameDataSize;/*!< The size of the M5GameData struct*/
  int         height;      /*!< The height of the client area of the screen*/
  int         width;       /*!< The width of the client area of the screen*/
  int         fps;         /*!<*The target frames per second for the game, usually 30 or 60*/
  bool        fullScreen;  /*!< If the game should begin in fullscreen or not*/
};

//! Singleton class to Control the Window
class M5App
{
public:
  friend class M5StageManager;

  /*Call These in Main*/

  /*This must be called first, before the game is started*/
  static void Init(const M5InitData& initStruct);
  /*Call this after you add your stages to start the game*/
  static void Update(void);
  /*Call this after Update is finished*/
  static void Shutdown(void);

  /*Call these to control or get info about The application*/

  /*Use this to change to fullscreen and back*/
  static void SetFullScreen(bool fullScreen);
  /*Use this to show and hide the window*/
  static void ShowWindow(bool show);
  /*Use this to show and hide the default window cursor*/
  static void ShowCursor(bool showCursor);
  /*Use this to change the resolution of the game*/
  static void SetResolution(int width, int height);
  /*Returns the width and height of the window (client area)*/
  static M5Vec2 GetResolution(void);
  /*Gets the fullscreen value of the App*/
  static bool GetFullScreen(void);

private:
  static LRESULT CALLBACK M5WinProc(HWND win, UINT msg, WPARAM wp, LPARAM lp);
  static void ProcessMessages(void);

};//end M5APP




#endif