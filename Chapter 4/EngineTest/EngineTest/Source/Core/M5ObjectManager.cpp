/******************************************************************************/
/*!
\file   M5ObjectManager.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/22

Globally accessible static class for easy creation and destruction of
game objects.

*/
/******************************************************************************/
#include "M5ObjectManager.h"
#include "M5Object.h"
#include "M5Debug.h"
#include "M5IniFile.h"
#include "../RegisterComponents.h"
#include "../RegisterArcheTypes.h"

#include "M5Component.h"
#include "M5ComponentBuilder.h"
#include "M5Factory.h"

#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <sstream>

namespace
{
typedef std::vector<M5Object*>                      ObjectVec;   //!< typedef Container to hold all game objects
typedef ObjectVec::iterator                         VecItor;     //!< typdef Iterator for object container
typedef std::unordered_map<M5ArcheTypes, M5Object*> PrototypeMap;//!< typedef Container to hold prototypes
typedef PrototypeMap::iterator                      MapItor;     //!< typedef Iterator for prototypes

const int START_SIZE = 100;                                      //!< Starting alloc count of object pointers

static M5Factory<M5ComponentTypes, M5ComponentBuilder, M5Component>
                          s_componentFactory;                    //!< Factory of all registered components
static PrototypeMap       s_prototypes;                          //!< Map of active prototypes in game
static ObjectVec          s_objects;                             //!< Vector of active objects in game    
static int                s_objectStart;                         //!< The value to start updating the object list from.
static std::stack<int>    s_pauseStack;
}//end unnamed namespace

 /******************************************************************************/
 /*!
   Init function for the M5ObjectMangager.  This function reserves space for
   objects as well as Registers all M5Components.
 */
 /******************************************************************************/
void M5ObjectManager::Init(void)
{
	M5DEBUG_CALL_CHECK(1);
	s_objects.reserve(START_SIZE);
	s_objectStart = 0;

	//We must register components before we can create our prototypes
	RegisterComponents();
	RegisterArcheTypes();
}
/******************************************************************************/
/*!
Shutdown function clears all game objects and destroys prototypes.
*/
/******************************************************************************/
void M5ObjectManager::Shutdown(void)
{
	M5DEBUG_CALL_CHECK(1);
	s_objectStart = 0;
	DestroyAllObjects();

	//Delete prototypes
	MapItor itor = s_prototypes.begin();
	MapItor end = s_prototypes.end();

	while (itor != end)
	{
		delete itor->second;
		itor->second = 0;
		++itor;
	}
}
/******************************************************************************/
/*!
Updates all game objects

\param [in] dt
The time in seconds since the last frame.
*/
/******************************************************************************/
void M5ObjectManager::Update(float dt)
{
	for (size_t i = s_objectStart; i < s_objects.size(); ++i)
	{
		if (s_objects[i]->isDead)
		{
			delete s_objects[i];
			s_objects[i] = s_objects[s_objects.size() - 1];
			s_objects.pop_back();
			--i;//so that we can update the shifted object 
		}
		else
		{
			s_objects[i]->Update(dt);
		}
	}
}
/******************************************************************************/
/*!
Function to delete all currently active game objects.
*/
/******************************************************************************/
void M5ObjectManager::DestroyAllObjects(void)
{
	size_t size = s_objects.size();
	for (size_t i = s_objectStart; i < size; ++i)
	{
		delete s_objects[i];
		s_objects[i] = 0;
	}

	s_objects.clear();
}
/******************************************************************************/
/*!
Function to delete all currently active game objects of the given type.

\param [in] type
The Archetype to delete
*/
/******************************************************************************/
void M5ObjectManager::DestroyAllObjects(M5ArcheTypes type)
{
	for (size_t i = s_objectStart; i < s_objects.size(); ++i)
	{
		if (s_objects[i]->GetType() == type)
		{
			delete s_objects[i];
			s_objects[i] = s_objects[s_objects.size() - 1];
			s_objects.pop_back();
		}
	}
}
/******************************************************************************/
/*!
Function to create a game object from a previsuoly loaded ArchType ini file.

\param [in] type
The M5ArcheType to create

\return
A new object of the given M5ArcheTypes type.
*/
/******************************************************************************/
M5Object* M5ObjectManager::CreateObject(M5ArcheTypes type)
{
	MapItor found = s_prototypes.find(type);
	M5DEBUG_ASSERT(found != s_prototypes.end(), "Trying to create and Archetype that doesn't exist");

	M5Object* pClone = found->second->Clone();
	s_objects.push_back(pClone);
	return pClone;

}
/******************************************************************************/
/*!
Adds the given M5Object to the ObjectManager to be updated.

\param [in] pToAdd
The M5Object To Add
*/
/******************************************************************************/
void M5ObjectManager::AddObject(M5Object* pToAdd)
{
	VecItor found = std::find(s_objects.begin(), s_objects.end(), pToAdd);
	M5DEBUG_ASSERT(found == s_objects.end(), "Trying to Add an Object that already exists");

	s_objects.push_back(pToAdd);
}
/******************************************************************************/
/*!
Finds a specific instance of a game object and deletes it.

\attention
This will delete the parameter object.  It can no longer be used after this
function.

\param [in,out] pToDestroy
An instance of an M5Object to remove and delete.

*/
/******************************************************************************/
void M5ObjectManager::DestroyObject(M5Object* pToDestroy)
{
	VecItor itor = std::find(s_objects.begin() + s_objectStart, s_objects.end(), pToDestroy);
	M5DEBUG_ASSERT(itor != s_objects.end(), "Trying to destroy an object that doesn't exist");

	delete *itor;
	std::iter_swap(itor, --s_objects.end());
	s_objects.pop_back();
}
/******************************************************************************/
/*!
Finds a specific instance of a game object based on ID and deletes it.

\param [in] objectID
An instance of an M5Object to remove and delete.
*/
/******************************************************************************/
void M5ObjectManager::DestroyObject(int objectID)
{
	for (size_t i = s_objectStart; i < s_objects.size(); ++i)
	{
		if (s_objects[i]->GetID() == objectID)
		{
			delete s_objects[i];
			s_objects[i] = s_objects[s_objects.size() - 1];
			s_objects.pop_back();
		}
	}
}
/******************************************************************************/
/*!
Finds the first object of the specifed type returns it via the parameter

\param [in] type
The type to find

\param [out] pObj
A pointer to an M5Object to be filled in.

\attention If the type isn't found, the parameter is not set at all.
*/
/******************************************************************************/
void M5ObjectManager::GetFirstObjectByType(M5ArcheTypes type, M5Object*& pObj)
{
	for (size_t i = s_objectStart; i < s_objects.size(); ++i)
	{
		if (s_objects[i]->GetType() == type)
		{
			pObj = s_objects[i];
			return;
		}	
	}
}
/******************************************************************************/
/*!
Finds the first object of the specifed by the objectID and returns it via 
the parameter

\param [in] objectID
The id to find

\param [out] pObj
A pointer to an M5Object to be filled in.

\attention If the type isn't found, the parameter is not set at all.
*/
/******************************************************************************/
void M5ObjectManager::GetObjectByID(int objectID, M5Object*& pObj)
{
	for (size_t i = s_objectStart; i < s_objects.size(); ++i)
	{
		if (s_objects[i]->GetID() == objectID)
		{
			pObj = s_objects[i];
			return;
		}
	}
}
/******************************************************************************/
/*!
Finds all instances of the specifed object type and returns the collection

\param [in] type
The type to find

\param [out] returnVec 
A vector that will be filled with objects of the correct type.

\attention
The pointers in the container are only valid this frame.  They could be destroyed
at any time.
*/
/******************************************************************************/
void M5ObjectManager::GetAllObjectsByType(M5ArcheTypes type, std::vector<M5Object*>& returnVec)
{
	for (size_t i = s_objectStart; i < s_objects.size(); ++i)
	{
		if (s_objects[i]->GetType() == type)
			returnVec.push_back(s_objects[i]);
	}
}
/******************************************************************************/
/*!
  Adds a component to the M5ObjectManager component factory.

  \param [in] type
  The component type to associate with the pBuilder.

  \param [in] pBuilder
  The M5ComponentBuilder to use when creating new component of the given type.
*/
/******************************************************************************/
void M5ObjectManager::AddComponent(M5ComponentTypes type, M5ComponentBuilder* pBuilder)
{
	s_componentFactory.AddBuilder(type, pBuilder);
}
/******************************************************************************/
/*!
Removes a component and deletes the builder associated with the component type.

\param [in] type
The component type to remove
*/
/******************************************************************************/
void M5ObjectManager::RemoveComponent(M5ComponentTypes type)
{
	s_componentFactory.RemoveBuilder(type);
}
/******************************************************************************/
/*!
Adds and Archetype from an ini file.

\param [in] type
The type archetype to associate with the given file.

\param [in] fileName
The of an ini file that will load data bout the archetype
*/
/******************************************************************************/
void M5ObjectManager::AddArcheType(M5ArcheTypes type, const char* fileName)
{
	MapItor found = s_prototypes.find(type);
	M5DEBUG_ASSERT(found == s_prototypes.end(), "Trying to add a prototype that already exists");

	M5IniFile file;//My inifile to open	
	file.ReadFile(fileName);


	M5Object* pObj = new M5Object(type);
	pObj->FromFile(file);

	std::string components;//A string of all my components
	file.GetValue("components", components);

	//parse the component string and create each component
	std::stringstream ss(components);
	std::string name;
	//Loop through the stream and get each component name
	while (ss >> name)
	{
		M5Component* pComp = s_componentFactory.Build(StringToComponent(name));
		pComp->FromFile(file);
		pObj->AddComponent(pComp);
	}

	//Add the prototype to the prototype map
	s_prototypes.insert(std::make_pair(type, pObj));
}
/******************************************************************************/
/*!
Removes and deletes the associated Archetype from the prototype map.

\param [in] type
The archetype to remove and delete
*/
/******************************************************************************/
void M5ObjectManager::RemoveArcheType(M5ArcheTypes type)
{
	MapItor found = s_prototypes.find(type);
	M5DEBUG_ASSERT(found != s_prototypes.end(), "Trying to Remove a prototype that doesn't exist");
	delete found->second;
	found->second = 0;
	s_prototypes.erase(found);
}
void M5ObjectManager::Pause(void)
{
	s_pauseStack.push(s_objectStart);
	s_objectStart = s_objects.size();
}
void M5ObjectManager::Resume(void)
{
	s_objectStart = s_pauseStack.top();
	s_pauseStack.pop();
}