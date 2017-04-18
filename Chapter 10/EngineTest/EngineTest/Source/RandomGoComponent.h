/******************************************************************************/
/*!
\file   RandomGoComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/08

Component to find, rotate to and move toward a random location
*/
/******************************************************************************/
#ifndef RANDOM_LOCATION_COMPONENT_H
#define RANDOM_LOCATION_COMPONENT_H

#include "Core\M5Component.h"
#include "Core\M5StateMachine.h"
#include "Core\M5Vec2.h"

//Forward declation
class RandomGoComponent;

class RLCFindState : public M5State
{
public:
	RLCFindState(RandomGoComponent* parent);
	void Enter(float dt);
	void Update(float dt);
	void Exit(float dt);
private:
	RandomGoComponent* m_parent;
};
class RLCRotateState : public M5State
{
public:
	RLCRotateState(RandomGoComponent* parent);
	void Enter(float dt);
	void Update(float dt);
	void Exit(float dt);
private:
	float m_targetRot;
	M5Vec2 m_dir;
	RandomGoComponent* m_parent;
};
class RLCGoState : public M5State
{
public:
	RLCGoState(RandomGoComponent* parent);
	void Enter(float dt);
	void Update(float dt);
	void Exit(float dt);
private:
	RandomGoComponent* m_parent;
};


class RandomGoComponent : public M5StateMachine
{
public:
	RandomGoComponent(void);
	virtual void FromFile(M5IniFile&);
	virtual M5Component* Clone(void);
private:
	friend RLCFindState;
	friend RLCGoState;
	friend RLCRotateState;

	float          m_speed;
	float          m_rotateSpeed;
	M5Vec2         m_target;
	RLCFindState   m_findState;
	RLCRotateState m_rotateState;
	RLCGoState     m_goState;
};


#endif // !RANDOM_LOCATION_COMPONENT_H
