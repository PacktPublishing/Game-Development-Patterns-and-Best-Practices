/******************************************************************************/
/*!
\file   M5ObjectManager.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/22

Globally accessible static class for easy creation and destruction of
game objects.
*/
/******************************************************************************/
#ifndef M5OBJECT_MANAGER_H
#define M5OBJECT_MANAGER_H

#include "M5ComponentFactory.h"
#include "M5ComponentTypes.h"
#include "M5CommandTypes.h"
#include "M5ArcheTypes.h"
#include <vector>


//Forward declarations
class M5Object;
class M5ComponentBuilder;
class M5Command;

//! Globally accessible static class for easy creation and destruction of game objects.
class M5ObjectManager
{
public:
	friend class M5App;
	friend class M5StageManager;

	// Adds an user created object to the M5ObjectManager
	static void AddObject(M5Object* toAdd);
	// Creates an object of the Specifed ArcheType if it has been loaded
	static M5Object* CreateObject(M5ArcheTypes type);
	// Removes and deletes the given object from The M5ObjectManager
	static void DestroyObject(M5Object* pToDestroy);
	// Removes and deletes the object with the given object id
	static void DestroyObject(int objectID);
	//Removes and deletes all objects from the object manager
	static void DestroyAllObjects(bool destroyPaused = false);
	//Destroys and deletes all objects of the given M5ArcheType from the M5ObjectManager
	static void DestroyAllObjects(M5ArcheTypes type);
	// Finds the first occurace of the given Archetype
	static void GetFirstObjectByType(M5ArcheTypes type, M5Object*& pObj);
	// Finds the object specifed by the given objectID 
	static void GetObjectByID(int objectID, M5Object*& pObj);
	// Finds all objects of the given Archetype
	static void GetAllObjectsByType(M5ArcheTypes type, std::vector<M5Object*>& returnVec);
	//Creates a component of the given type
	static M5Component* CreateComponent(M5ComponentTypes type);
	// Creates an assocaitation between the given type and a builder 
	static void AddComponent(M5ComponentTypes type, M5ComponentBuilder* pBuilder);
	// Removes the builder assocaited with the given type
	static void RemoveComponent(M5ComponentTypes type);
	// Creates an association between the given type and the contents of the given file
	static void AddArcheType(M5ArcheTypes type, const char* fileName);
	// Removes the Archetype from the object factory
	static void RemoveArcheType(M5ArcheTypes type);
	//Creates a Command of the given type
	static M5Command* CreateCommand(M5CommandTypes type);
	//Adds a cloneable command to the M5ObjectManager
	static void AddCommand(M5CommandTypes type, M5Command* pCommand);
	//Removes the clonable command from the M5ObjectManager
	static void RemoveCommand(M5CommandTypes type);


private:
	static void Init(void);
	static void Shutdown(void);
	static void Update(float dt);
	static void Pause(void);
	static void Resume(void);
};


#endif //M5OBJECT_MANAGER