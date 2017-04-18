/******************************************************************************/
/*!
\file   M5StageFactory.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/10

Class for instantiating stages based on a regiestered name/type.

*/
/******************************************************************************/
#include "M5StageFactory.h"
#include "M5Debug.h"
#include "M5Stage.h"
#include "M5StageBuilder.h"

/******************************************************************************/
/*!
Destructor makes sure to delete all builders from the factory
*/
/******************************************************************************/
M5StageFactory::~M5StageFactory(void)
{
  ClearBuilders();
}
/******************************************************************************/
/*!
Adds a StageBuilder to the Factory if it doesn't already exist.

\param [in] name
The name to associate with the given builder.

\param [in] pBuilder
A pointer to a StageBuilder that will be owned and deleted by the factory.
*/
/******************************************************************************/
void M5StageFactory::AddBuilder(M5StageTypes name, M5StageBuilder* pBuilder)
{
  std::pair<ArcheTypeItor, bool> itor = m_builderMap.insert(std::make_pair(name, pBuilder));
  M5DEBUG_ASSERT(itor.second == true, "Trying to add a builder that already exists");
}
/******************************************************************************/
/*!
Removes a builder from the factory if it exists.

\param [in] name
The name of the Stage/Builder to remove.
*/
/******************************************************************************/
void M5StageFactory::RemoveBuilder(M5StageTypes name)
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
Returns a new Stage based on the type of the builder.

\param [in] name
The name of the Stage to build

\return 
A Derived class in the M5Stage inheritance chain.  

*/
/******************************************************************************/
M5Stage* M5StageFactory::Build(M5StageTypes name)
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
void M5StageFactory::ClearBuilders(void)
{
  ArcheTypeItor itor = m_builderMap.begin();
  ArcheTypeItor end  = m_builderMap.end();

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