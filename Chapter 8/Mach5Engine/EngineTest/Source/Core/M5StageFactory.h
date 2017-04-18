/******************************************************************************/
/*!
\file   M5StageFactory.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/10

Class for instantiating stages based on a regiestered name/type.

*/
/******************************************************************************/
#ifndef M5STAGE_FACTORY_H
#define M5STAGE_FACTORY_h

#include <unordered_map>
#include "M5StageTypes.h"

//Forward declarations
class M5Stage;
class M5StageBuilder;

/*! Class for Easily Creating Stages at runtime.*/
class M5StageFactory
{
public:
	~M5StageFactory(void);
	void AddBuilder(M5StageTypes type, M5StageBuilder* builder);
	void RemoveBuilder(M5StageTypes type);
	M5Stage* Build(M5StageTypes type);
	void ClearBuilders(void);

private:
	//! Typedef for my Hash Table of M5GameStages and M5StageBuilder's
	typedef std::unordered_map<M5StageTypes, M5StageBuilder*> BuilderMap;
	//! Easy Typedef for the itorator to my BuilderMap.
	typedef BuilderMap::iterator ArcheTypeItor;
	//! Container to map M5StageTypes to M5StageBuilder 
	BuilderMap m_builderMap; 
};



#endif // M5STAGE_FACTORY_H
