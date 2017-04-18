/******************************************************************************/
/*!
\file   M5ObjectPool.h
\author John P. Doran
\par    email: john\@johnpdoran.com
\par    Mach5 Game Engine
\date   2016/11/19

Globally accessible static class for object caching to avoid creating new objects
if we already have one not being used.

*/
/******************************************************************************/
#ifndef M5OBJECT_POOL_H
#define M5OBJECT_POOL_H

#include <vector>
#include <queue>

#include "EngineTest\Source\Core\M5Object.h"

template <M5ArcheTypes T>
class M5ObjectPool
{
public:
	// Gives to us the first available object, creating a new one if none is available
	static M5Object * AcquireObject();
	
	// Returns the object to the pool making it available for reuse
	static void ReleaseObject(M5Object* object);

	// Removes all of the objects in the pool and removes references as needed
	static void ClearPool();

private:
	// All of the objects in the object pool
	static std::vector<M5Object*>  pool;

	// All of the objects that are currently available
	static std::deque<M5Object*> available;
};


#endif //M5OBJECT_POOL_H

