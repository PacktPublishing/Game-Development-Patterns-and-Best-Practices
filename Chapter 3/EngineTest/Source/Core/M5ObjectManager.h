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
#include "M5ArcheTypes.h"
#include <vector>

class M5Object;
class M5ComponentBuilder;

//! Globally accessible static class for easy creation and destruction of game objects.
class M5ObjectManager
{
public:
	friend class M5App;
	friend class M5StageManager;

	static M5Object* CreateObject(M5ArcheTypes type);
	static void AddObject(M5Object* toAdd);
	static void DestroyObject(M5Object* pToDestroy);
	static void DestroyObject(int objectID);
	static void DestroyAllObjects(void);
	static void DestroyAllObjects(M5ArcheTypes type);
	static void GetAllObjects(M5ArcheTypes type, std::vector<M5Object*>& returnVec);
	static void AddComponent(M5ComponentTypes type, M5ComponentBuilder* pBuilder);
	static void RemoveComponent(M5ComponentTypes type);
	static void AddArcheType(M5ArcheTypes type, const char* fileName);
	static void RemoveArcheType(M5ArcheTypes type);
private:
	static void Init(void);
	static void Shutdown(void);
	static void Update(float dt);
};


#endif //M5OBJECT_MANAGER