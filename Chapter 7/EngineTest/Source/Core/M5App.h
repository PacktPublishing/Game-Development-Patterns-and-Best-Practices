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

// For book
#include <string>
#include <iostream>

//Forward Declarations
struct M5GameData;

// Singleton.h
//class Singleton
//{
//	public:
//		Singleton & GetInstance()
//		{
//			if (!instance)
//			{
//				if (destroyed)
//				{
//					M5DEBUG_ASSERT(destroyed, "Singleton Destroyed");
//				}
//				else
//				{
//					CreateInstance();
//				}
//			}
//
//			return *instance;
//		}
//
//	private:
//		Singleton * instance;
//		bool destroyed;
//
//		static void CreateInstance()
//		{
//			static Singleton originalInstance;
//			instance = &originalInstance;
//		}
//
//		// Disable usability of silently generated functions
//		Singleton();
//		~Singleton()
//		{
//			instance = NULL;
//			destroyed = true;
//		}
//		Singleton(const Singleton &);
//		Singleton& operator=(const Singleton&);
//	
//};

class StaticExamples
{
public:
	static float classVariable;

	static void StaticFunction()
	{
		// Note, can only use static variables and functions within static function
		std::string toDisplay = "\n I can be called anywhere! classVariable value: " + 
								std::to_string(classVariable);

		printf(toDisplay.c_str());
	}

	void InFunction()
	{
		static int enemyCount = 0;

		// Increase the value of enemyCount
		enemyCount += 10;

		std::string toDisplay = "\n Value of enemyCount:  " + 
								std::to_string(enemyCount);

		printf(toDisplay.c_str());
	}
};

template <class T>
class TemplateExample
{
public:
	// Constructor
	TemplateExample();
	// Destructor
	~TemplateExample();
	// Function
	T TemplatedFunction(T);
};

template <class T> TemplateExample<T>::TemplateExample()
{
	printf("\nConstructor!");
}

template <class T> TemplateExample<T>::~TemplateExample()
{
	printf("\nDeconstructor!");
}

template <class T> T TemplateExample<T>::TemplatedFunction(T obj)
{
	std::cout << "\nValue: " << obj;
	return obj;
}


template <typename T>
class Singleton
{
public:
	Singleton()
	{
		// Set our instance variable when we are created
		if (instance == nullptr)
		{
			instance = static_cast<T*>(this);
		}
		else
		{
			// If instance already exists, we have a problem
			printf("\nError: Trying to create more than one Singleton");
		}
	}

	// Once destroyed, remove access to instance
	virtual ~Singleton()
	{
		instance = nullptr;
	}

	// Get a reference to our instance
	static T & GetInstance()
	{
		return *instance;
	}

	// Deletes the instance, needs to be called or resource leak
	static void RemoveInstance()
	{
		delete instance;
	}

private:
	// Note, needs to be a declaration
	static T * instance;

};

template <typename T> T * Singleton<T>::instance = nullptr;

class HighScoreManager : public Singleton<HighScoreManager>
{
public:
	void CheckHighScore(int score);

private:
	int highScore;
};





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

private:
  static LRESULT CALLBACK M5WinProc(HWND win, UINT msg, WPARAM wp, LPARAM lp);
  static void ProcessMessages(void);

};//end M5APP




#endif