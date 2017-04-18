/******************************************************************************/
/*!
\file   M5Component.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/18

Base class component for M5Objects

*/
/******************************************************************************/
#include "M5Component.h"

int M5Component::s_componentID = 0;

/******************************************************************************/
/*!
Constructor to set the type of component as well as defaults.

\param [in] type
The type of this component.
*/
/******************************************************************************/
M5Component::M5Component(M5ComponentTypes type):
	isDead(false),
	m_pObj(0), 
	m_type(type),
	m_id(++s_componentID)
{
}
/******************************************************************************/
/*!
  Virtual destructor because this is used as a base class.
*/
/******************************************************************************/
M5Component::~M5Component(void) 
{
	 //Empty Base Class virtual destructor 
}
/******************************************************************************/
/*!
  Function to allow derived classes to read data from an ini file.
*/
/******************************************************************************/
void M5Component::FromFile(M5IniFile&)
{
	//empty for the base class
}
/******************************************************************************/
/*!
Allows the parent pointer to be be set by the user

\param [in] pObject
The object that this component belongs to
*/
/******************************************************************************/
void M5Component::SetParent(M5Object* pObject)
{ 
	m_pObj = pObject;
}
/******************************************************************************/
/*!
Returns the type of this component.

\return
The type of this component
*/
/******************************************************************************/
M5ComponentTypes M5Component::GetType(void) const 
{ 
	return m_type; 
}
/******************************************************************************/
/*!
Returns the unique id of this component.

\return 
The unique id of this component
*/
/******************************************************************************/
int M5Component::GetID(void)const 
{ 
	return m_id; 
}