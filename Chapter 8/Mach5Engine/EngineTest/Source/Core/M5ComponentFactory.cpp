/******************************************************************************/
/*!
\file   M5ComponentFactory.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/22

Class for instantiating components based on a regiestered name/type.

*/
/******************************************************************************/
#include "M5ComponentFactory.h"
#include "M5Debug.h"
#include "M5Component.h"
#include "M5ComponentBuilder.h"

/******************************************************************************/
/*!
Destructor makes sure to delete all builders from the factory
*/
/******************************************************************************/
M5ComponentFactory::~M5ComponentFactory(void)
{
	ClearBuilders();
}
/******************************************************************************/
/*!
Adds a ComponentBuilder to the Factory if it doesn't already exist.

\param [in] name
The name to associate with the given builder.

\param [in] pBuilder
A pointer to a ComponentBuilder that will be owned and deleted by the factory.
*/
/******************************************************************************/
void M5ComponentFactory::AddBuilder(M5ComponentTypes name, M5ComponentBuilder* pBuilder)
{
	std::pair<ArcheTypeItor, bool> itor = m_builderMap.insert(std::make_pair(name, pBuilder));
	M5DEBUG_ASSERT(itor.second == true, "Trying to add a builder that already exists");
}
/******************************************************************************/
/*!
Removes a builder from the factory if it exists.

\param [in] name
The name of the Component/Builder to remove.
*/
/******************************************************************************/
void M5ComponentFactory::RemoveBuilder(M5ComponentTypes name)
{
	BuilderMap::iterator itor = m_builderMap.find(name);
	M5DEBUG_ASSERT(itor != m_builderMap.end(),
		"Trying to Remove a Builder that doesn't exist");

	//First delete the builder
	delete itor->second;
	itor->second = 0;
	//then erase the element
	m_builderMap.erase(itor);
}
/******************************************************************************/
/*!
Returns a new M5Component based on the type of the builder.

\param [in] name
The name of the M5Component to build

\return
A Derived class in the M5Component inheritance chain.

*/
/******************************************************************************/
M5Component* M5ComponentFactory::Build(M5ComponentTypes name)
{
	ArcheTypeItor itor = m_builderMap.find(name);
	M5DEBUG_ASSERT(itor != m_builderMap.end(), "Trying to use a Builder that doesn't exist");
	return itor->second->Build();
}
/******************************************************************************/
/*!
Removes all elements from the factory and deletes the associated builders.
*/
/******************************************************************************/
void M5ComponentFactory::ClearBuilders(void)
{
	ArcheTypeItor itor = m_builderMap.begin();
	ArcheTypeItor end = m_builderMap.end();

	//Make sure to delete all builder pointers first
	while (itor != end)
	{
		delete itor->second;
		itor->second = 0;
		++itor;
	}

	//Then clear the hash table
	m_builderMap.clear();
}