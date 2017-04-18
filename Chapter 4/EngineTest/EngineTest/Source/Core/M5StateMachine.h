/******************************************************************************/
/*!
\file   M5StateMachine.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/08

Finite Statemachine base class component
*/
/******************************************************************************/
#ifndef M5STATEMACNINE_H
#define M5STATEMACNINE_H

#include "M5Component.h"
#include "M5Vec2.h"

//! Base State for M5StateMachines
class M5State
{
public:
	//! Empty virtual destructor
	virtual ~M5State(void) {}
	//! Called when we first enter a state
	virtual void Enter(float dt)  = 0;
	//! called once per frame
	virtual void Update(float dt) = 0;
	//! called before we exit a state
	virtual void Exit(float dt)   = 0;
};

//! Base class for Finite statemanchine component for AstroShot
class M5StateMachine : public M5Component
{
public:
	M5StateMachine(M5ComponentTypes type);
	virtual ~M5StateMachine(void);
	virtual void Update(float dt);
	void SetNextState(M5State* pNext);
private:
	M5State* m_pCurr; //!< a pointer to our current state to be updated
	M5State* m_pNext; //!< a pointer to the next state to be updated
};

#endif //M5STATEMACNINE_H
