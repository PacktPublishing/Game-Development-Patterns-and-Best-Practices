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


class RandomGoComponent : public M5StateMachine
{
public:
	RandomGoComponent(void);
	virtual void FromFile(M5IniFile&);
	virtual RandomGoComponent* Clone(void) const;
private:
	class FindState : public M5State
	{
	public:
		FindState(RandomGoComponent* parent);
		void Enter(float dt);
		void Update(float dt);
		void Exit(float dt);
	private:
		RandomGoComponent* m_parent;
	};
	class RotateState : public M5State
	{
	public:
		RotateState(RandomGoComponent* parent);
		void Enter(float dt);
		void Update(float dt);
		void Exit(float dt);
	private:
		float m_targetRot;
		M5Vec2 m_dir;
		RandomGoComponent* m_parent;
	};
	class GoState : public M5State
	{
	public:
		GoState(RandomGoComponent* parent);
		void Enter(float dt);
		void Update(float dt);
		void Exit(float dt);
	private:
		RandomGoComponent* m_parent;
	};

	friend FindState;
	friend GoState;
	friend RotateState;

	float       m_speed;
	float       m_rotateSpeed;
	M5Vec2      m_target;
	FindState   m_findState;
	RotateState m_rotateState;
	GoState     m_goState;
};


#endif // !RANDOM_GO_COMPONENT_H
