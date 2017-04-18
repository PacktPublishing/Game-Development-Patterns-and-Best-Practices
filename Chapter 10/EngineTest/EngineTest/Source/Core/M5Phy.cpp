/******************************************************************************/
/*!
file    M5Phy.cpp
\author Matt Casanova
\\par   email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/26

Basis Physics engine for Mach 5.  This is a work in progress.
*/
/******************************************************************************/
#include "M5Phy.h"
#include "M5Object.h"
#include "ColliderComponent.h"

#include <stack>

namespace
{
//Class Private variables

static std::vector<ColliderComponent*> s_colliders;      //!< Vector of regiestered colliders
static CollisionPairs                  s_collisionPairs; //!< This frames collision pairs. 
static int                             s_colliderStart = 0;  //!< The index to start updating on
static std::stack<int>                 s_pauseStack;
}


void M5Phy::RegisterCollider(ColliderComponent* pCollider)
{
	s_colliders.push_back(pCollider);
}
void M5Phy::UnregisterCollider(ColliderComponent* pCollider)
{
	for (size_t i = s_colliderStart; i < s_colliders.size(); ++i)
	{
		if (s_colliders[i] == pCollider)
		{
			s_colliders[i] = s_colliders[s_colliders.size() - 1];
			s_colliders.pop_back();
		}
	}
}
void M5Phy::GetCollisionPairs(CollisionPairs& pairs)
{
	pairs = s_collisionPairs;
}
void M5Phy::AddCollisionPair(int firstID, int secondID)
{
	s_collisionPairs.push_back(std::make_pair(firstID, secondID));
}
void M5Phy::Update(void)
{
	s_collisionPairs.clear();
	size_t size = s_colliders.size();
	for (size_t i = s_colliderStart; i < size; ++i)
	{
		ColliderComponent* pFirst = s_colliders[i];
		for (size_t j = i + 1; j < size; ++j)
		{
			pFirst->TestCollision(s_colliders[j]);
		}
	}
}
void M5Phy::Pause(void)
{
	s_pauseStack.push(s_colliderStart);
	s_colliderStart = s_colliders.size();
}
void M5Phy::Resume(void)
{
	s_colliderStart = s_pauseStack.top();
	s_pauseStack.pop();
}