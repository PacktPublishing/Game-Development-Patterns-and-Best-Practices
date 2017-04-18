/******************************************************************************/
/*!
\file   M5ComponentFactory.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/18

Class for instantiating components based on a regiestered name/type.

*/
/******************************************************************************/
#ifndef M5COMPONENT_FACTORY_H
#define M5COMPONENT_FACTORY_H

#include <unordered_map>
#include "M5ComponentTypes.h"

//Forward declarations
class M5Component;
class M5ComponentBuilder;

/*! Class for Easily Creating Components at runtime.*/
class M5ComponentFactory
{
public:
	~M5ComponentFactory(void);
	void AddBuilder(M5ComponentTypes name, M5ComponentBuilder* builder);
	void RemoveBuilder(M5ComponentTypes name);
	M5Component* Build(M5ComponentTypes name);
	void ClearBuilders(void);
private:
	//! Typedef for my Hash Table of M5ComponentTypes and M5ComponentBuilders
	typedef std::unordered_map<M5ComponentTypes, M5ComponentBuilder*> BuilderMap;
	//! Easy Typedef for the itorator to my BuilderMap.
	typedef BuilderMap::iterator MapItor;
	//! Container to map M5ComponentTypes to M5Builders 
	BuilderMap m_builderMap; 
};



#endif // M5COMPONENT_FACTORY_H
