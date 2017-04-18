/******************************************************************************/
/*!
\file   M5ObjectPool.cpp
\author John P. Doran
\par    email: john\@johnpdoran.com
\par    Mach5 Game Engine
\date   2016/11/19

Globally accessible static class for object caching to avoid creating new objects
if we already have one not being used.

*/
/******************************************************************************/
#include "M5ObjectPool.h"
#include "Source\Core\M5ObjectManager.h"

template class M5ObjectPool<AT_Bullet>;// explicit instantiation     

/******************************************************************************/
/*!
Returns the first available object if it exists. If not, it will create a new 
one for us
*/
/******************************************************************************/

template <M5ArcheTypes T>
M5Object * M5ObjectPool<T>::AcquireObject()
{
	// Check if we have any available
	if (!available.empty())
	{
		// Get reference to an available object
		M5Object * object = available.back();

		// Since we are going to use it, it's no longer available, so
		// we need to remove the last element from our list
		available.pop_back();

		// Finally, return the reference
		return object;
	}
	else
	{
		// If none are avaliable, create a new one
		M5Object * object = M5ObjectManager::CreateObject(T);

		pool.push_back(object);

		return object;
	}
}

/******************************************************************************/
/*!
Marks an object as being available again

\param
The object to be made available again
*/
/******************************************************************************/
template <M5ArcheTypes T>
void M5ObjectPool<T>::ReleaseObject(M5Object * object)
{
	// If it's valid, move this object into our available list
	if ((object->GetType() == T) && 
		(std::find(pool.begin(), pool.end(), object) != pool.end()))
	{
		//Make sure we haven't already been added already
		if(std::find(available.begin(), available.end(), object) == available.end())
		{
			available.push_back(object);
		}
	}

}

/******************************************************************************/
/*!
Takes care of removing all of the objects from the pool whenever we're finished
working with it.
*/
/******************************************************************************/
template<M5ArcheTypes T>
void M5ObjectPool<T>::ClearPool()
{
	//  Go through each of our objects and destroy them
	for (int i = pool.size() - 1; i >= 0; --i)
	{
		M5ObjectManager::DestroyObject(pool[i]);
		pool.pop_back();
	}

	// Now clear out the available queue
	available.clear();
}

template<M5ArcheTypes T>
std::vector<M5Object*>  M5ObjectPool<T>::pool;

template<M5ArcheTypes T>
std::deque<M5Object*>  M5ObjectPool<T>::available;

