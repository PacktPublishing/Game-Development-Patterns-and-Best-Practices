/******************************************************************************/
/*!
\file   M5Timer.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/8

Class to help control frames per second of the game.

*/
/******************************************************************************/
#ifndef M5GAME_TIMER_H
#define M5GAME_TIMER_H

/*! Used to exclude rarely-used stuff from Windows */
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>


/*! Class to calculate time seconds for the game.  Used to get frame time for game */
class M5Timer
{
public:
	//Initilzes Game Timer data
	void  Init(int fps);
	//Sets the internal data to the start time of the frame
	void  StartFrame(void);
	//Calcualates and returns the total frame time in milliseconds
	float EndFrame(void);
private:
	void SetTargetFPS(int fps);
	LARGE_INTEGER s_frequency;       /*!< The frequency of the high performance clock*/
	LARGE_INTEGER s_startTime;       /*!< The start time of the frame*/
	LARGE_INTEGER s_endTime;         /*!< The end time of the frame*/
	float         s_targetFPS;       /*!< The number of frame you want per second*/
	float         s_targetFrameTime; /*!< The time each frame should take*/


};


#endif // !M5GAME_TIMER_H
