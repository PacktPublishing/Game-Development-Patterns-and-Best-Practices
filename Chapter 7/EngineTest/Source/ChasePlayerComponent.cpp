/******************************************************************************/
/*!
\file   ChasePlayerComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/09

Simple AI to Chase the Player
*/
/******************************************************************************/
#include "ChasePlayerComponent.h"

#include "Core\M5ObjectManager.h"
#include "Core\M5IniFile.h"
#include "Core\M5Object.h"
#include <vector>
#include <cmath>


/******************************************************************************/
/*!
Sets component type and starting values for player
*/
/******************************************************************************/
ChasePlayerComponent::ChasePlayerComponent(void):
	M5Component(CT_ChasePlayerComponent),
	m_speed(1)
{
	SetNewState(Idle, true);
}
/******************************************************************************/
/*!
Sets component type and starting values for player
*/
/******************************************************************************/
void ChasePlayerComponent::Update(float dt)
{
	UpdateState(currentState, dt);
}

/******************************************************************************/
/*!
Sets component type and starting values for player
*/
/******************************************************************************/
M5Component* ChasePlayerComponent::Clone(void)
{
	ChasePlayerComponent* pNew = new ChasePlayerComponent;
	pNew->m_speed = m_speed;
	pNew->m_followDistance = m_followDistance;
	pNew->m_loseDistance = m_loseDistance;
	return pNew;
}
void ChasePlayerComponent::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("ChasePlayerComponent");
	iniFile.GetValue("speed", m_speed);
	iniFile.GetValue("followDistance", m_followDistance);
	iniFile.GetValue("loseDistance", m_loseDistance);

}

/******************************************************************************/
/*!
Makes it so the enemy will move in the direction of the player
*/
/******************************************************************************/
void ChasePlayerComponent::FollowPlayer()
{
	std::vector<M5Object*> players;
	M5ObjectManager::GetAllObjectsByType(AT_Player, players);
	M5Vec2 dir;
	M5Vec2::Sub(dir, players[0]->pos, m_pObj->pos);
	m_pObj->rotation = std::atan2f(dir.y, dir.x);
	dir.Normalize();
	dir *= m_speed;
	m_pObj->vel = dir;
}

/******************************************************************************/
/*!
Returns the distance of the object this is attached to the player
*/
/******************************************************************************/
float ChasePlayerComponent::GetDistanceFromPlayer()
{
	std::vector<M5Object*> players;
	M5ObjectManager::GetAllObjectsByType(AT_Player, players);

	return M5Vec2::Distance(m_pObj->pos, players[0]->pos);
}

void ChasePlayerComponent::EnterState(State state)
{
	// Depending on  what state we are in, do different things
	switch (state)
	{
	case Idle:
		// No longer move if we were
		if (m_pObj)
		{
			m_pObj->vel = M5Vec2(0, 0);
		}
		
		M5DEBUG_PRINT("\nIdle: Enter");
		break;

	case Follow:
		M5DEBUG_PRINT("\nFollow: Enter");
		break;

	case Death:
		m_pObj->isDead = true;
		M5DEBUG_PRINT("\nDeath: Enter");
		break;
	}
}

void ChasePlayerComponent::UpdateState(State state, float)
{
	// Depending on  what state we are in, do different things
	switch (state)
	{
	case Idle:
		//M5DEBUG_PRINT("\nIdle: Update");
		// If the player gets too close, the enemy notices them
		if (GetDistanceFromPlayer() < m_followDistance)
		{
			// And will begin to give chase
			SetNewState(Follow);
		}
		
		break;

	case Follow:
		//M5DEBUG_PRINT("\nFollow: Update");

		// Follow the player
		FollowPlayer();

		// If the player manages to get away from the enemy
		if (GetDistanceFromPlayer() > m_loseDistance)
		{
			// Stop in your tracks
			SetNewState(Idle);
		}
		break;
	}
}

void ChasePlayerComponent::ExitState(State state)
{
	// Depending on  what state we are in, do different things
	switch (state)
	{
	case Idle:
		M5DEBUG_PRINT("\nIdle: Exit");
		break;

	case Follow:
		M5DEBUG_PRINT("\nFollow: Exit");
		break;
	}
}

void ChasePlayerComponent::SetNewState(State state, bool initialState)
{
	if (!initialState)
	{
		// Exit of our old state
		ExitState(currentState);
	}

	// Then start up our new one
	currentState = state;
	EnterState(currentState);
}