/******************************************************************************/
/*!
\file   M5Stage.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    2D Game Engine
\date   2016/08/08

Base class for M5Stage

*/
/******************************************************************************/
#ifndef M5_STAGE_H
#define M5_STAGE_H


/*! A struct to hold the function pointers for a stage.*/
class M5Stage
{
public:
	//!Used to Load big resource such as textures in an M5Stage.  This is only called once.
	M5Stage(void) {};
	//!Used to Unload textures or Save data to file.  This is only called when we are not restarting.
	virtual ~M5Stage(void) {}//emtpy virtual destructor
	//!Used to Set/Reset data when the M5Stage starts or restarts
	virtual void Init(void) = 0;
	//!Called once per frame to update M5Stage Logic
	virtual void Update(float dt) = 0;
	//!Called after a Stage Change or request to restart
	virtual void Shutdown(void) = 0;

};

#endif