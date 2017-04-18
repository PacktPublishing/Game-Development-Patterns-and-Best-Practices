/******************************************************************************/
/*!
file    M5Phy.h
\author Matt Casanova
\\par   email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/26

Basis Physics engine for Mach 5.  This is a work in progress.
*/
/******************************************************************************/
#ifndef M5PHY_H
#define M5PHY_H

#include <vector>


//Forward Declarations
class ColliderComponent;

//! Typedef name for my pairs of collided objectIDs
typedef std::vector < std::pair<int, int> > CollisionPairs;

//! Singleton class to test collision between pairs of M5Objects
class M5Phy
{
public:
	friend class M5StageManager;

	//Registers a collider with the physics engine
	static void RegisterCollider(ColliderComponent* pCollider);
	//Unregisters a collider with the physics engine
	static void UnregisterCollider(ColliderComponent* pCollider);
	//Gets all pairs of objects that collided this frame.
	static void GetCollisionPairs(CollisionPairs& pairs);
	//Marks a pair of M5Objects as having collided.
	static void AddCollisionPair(int firstID, int secondID);

private:
	static void Update(void);
	static void Pause(void);
	static void Resume(void);
};


#endif //M5PHY_H