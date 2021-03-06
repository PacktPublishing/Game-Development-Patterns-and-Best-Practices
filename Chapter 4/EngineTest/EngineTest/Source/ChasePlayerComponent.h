/******************************************************************************/
/*!
\file   ChasePlayerComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/09

Simple AI to Chase the Player
*/
/******************************************************************************/
#ifndef CHASE_PLAYER_COMPONENT_H
#define CHASE_PLAYER_COMPONENT_H

#include "Core/M5Component.h"

enum State
{
	Idle,
	Follow,
	Death
};

//!< Simple AI to Chase the Player
class ChasePlayerComponent : public M5Component
{
public:
	ChasePlayerComponent(void);
	virtual void Update(float dt);
	virtual void FromFile(M5IniFile& iniFile);
	virtual M5Component* Clone(void);
	virtual void EnterState(State state);
	virtual void UpdateState(State state, float dt);
	virtual void ExitState(State state);
	virtual void SetNewState(State state, bool initialState = false);
private:
	float m_speed;
	float m_followDistance;
	float m_loseDistance;

	void FollowPlayer();
	float GetDistanceFromPlayer();
	State currentState;

};



/*
class ChasePlayerStates
{
public:
	void OnStart();
	void OnUpdate();
	void OnExit();
};
*/

#endif //CHASE_PLAYER_COMPONENT_H
