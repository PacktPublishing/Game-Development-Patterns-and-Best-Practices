/******************************************************************************/
/*!
\file   M5Factory.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/17

Templated class for creating  generic factory
*/
/******************************************************************************/
#ifndef M5FACTORY_H
#define M5FACTORY_H

#include "M5Debug.h"
#include <unordered_map>

template<typename EnumType, typename BuilderType, typename ReturnType>
class M5Factory
{
public:
	~M5Factory(void);
	void AddBuilder(EnumType type, BuilderType* builder);
	void RemoveBuilder(EnumType type);
	ReturnType* Build(EnumType type);
	void ClearBuilders(void);
private:
	//! Typedef for my Hash Table of M5GameStages and M5StageBuilder's
	typedef std::unordered_map<EnumType, BuilderType*> BuilderMap;
	//! Easy Typedef for the itorator to my BuilderMap.
	typedef typename BuilderMap::iterator MapItor;
	//! Container to map M5GameStages to M5Builders 
	BuilderMap m_builderMap;
};

/******************************************************************************/
/*!
Destructor makes sure to delete all builders from the factory
*/
/******************************************************************************/
template<typename EnumType, typename BuilderType, typename ReturnType>
M5Factory<EnumType, BuilderType, ReturnType>::~M5Factory(void)
{
	ClearBuilders();
}
/******************************************************************************/
/*!
Adds a Builder to the Factory if it doesn't already exist.

\param [in] type
The type to associate with the given builder.

\param [in] pBuilder
A pointer to a Builder that will be owned and deleted by the factory.
*/
/******************************************************************************/
template<typename EnumType, typename BuilderType, typename ReturnType>
void M5Factory<EnumType, BuilderType, ReturnType>::AddBuilder(EnumType type,
	BuilderType* pBuilder)
{
	std::pair<MapItor, bool> itor = m_builderMap.insert(std::make_pair(type, pBuilder));
	M5DEBUG_ASSERT(itor.second == true, "Trying to add a builder that already exists");
}
/******************************************************************************/
/*!
Removes a builder from the factory if it exists.

\param [in] type
The Type of the Enum/Builder to remove.
*/
/******************************************************************************/
template<typename EnumType, typename BuilderType, typename ReturnType>
void M5Factory<EnumType, BuilderType, ReturnType>::RemoveBuilder(EnumType type)
{
	BuilderMap::iterator itor = m_builderMap.find(type);
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
Returns a new ReturnType pointer based on the type of the builder.

\param [in] type
The type of object to build

\return
A Derived class in the ReturnType inheritance chain.
*/
/******************************************************************************/
template<typename EnumType, typename BuilderType, typename ReturnType>
ReturnType* M5Factory<EnumType, BuilderType, ReturnType>::Build(EnumType type)
{
	MapItor itor = m_builderMap.find(type);
	M5DEBUG_ASSERT(itor != m_builderMap.end(), "Trying to use a Builder that doesn't exist");
	return itor->second->Build();
}
/******************************************************************************/
/*!
Removes all elements from the factory and deletes the associated builders.
*/
/******************************************************************************/
template<typename EnumType, typename BuilderType, typename ReturnType>
void M5Factory<EnumType, BuilderType, ReturnType>::ClearBuilders(void)
{
	MapItor itor = m_builderMap.begin();
	MapItor end = m_builderMap.end();

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

#endif M5FACTORY_H
