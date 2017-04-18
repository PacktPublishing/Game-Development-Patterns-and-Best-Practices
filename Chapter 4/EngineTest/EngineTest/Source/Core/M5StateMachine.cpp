/******************************************************************************/
/*!
\file   M5StateMachine.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/08

Finite Statemachine base class component
*/
/******************************************************************************/
#include "M5StateMachine.h"

M5StateMachine::M5StateMachine(M5ComponentTypes type):
	M5Component(type),
	m_pCurr(0),
	m_pNext(0)
{
}
M5StateMachine::~M5StateMachine(void)
{
	//Empty Base class
}
void M5StateMachine::Update(float dt)
{
	if (m_pCurr == 0)
	{
		m_pCurr = m_pNext;
		m_pCurr->Enter(dt);
	}
	else if (m_pCurr == m_pNext)
		m_pCurr->Update(dt);
	else
	{
		m_pCurr->Exit(dt);
		m_pCurr = m_pNext;
		m_pCurr->Enter(dt);
	}
}
void M5StateMachine::SetNextState(M5State* pNext)
{
	m_pNext = pNext;
}