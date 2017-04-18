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
#ifndef M5COMPONENT_H
#define M5COMPONENT_H
#include "M5ComponentTypes.h"

//Forward declarations
class M5Object;
class M5IniFile;

//! Base class component for M5Objects
class M5Component
{
public:
	M5Component(M5ComponentTypes type);
	virtual ~M5Component(void);
	//! virtual constructor for M5Component, must override
	virtual M5Component* Clone(void) = 0;
	//! the per frame behavoir of component,must override
	virtual void     Update(float dt)= 0;
	virtual void     FromFile(M5IniFile&);
	void             SetParent(M5Object* pParent);
	M5ComponentTypes GetType(void) const;
	int              GetID(void) const;
	//Public data
	bool             isDead;        //!< flag to mark for deletion
protected:
	M5Object*        m_pObj;        //!< Pointer to parent object
private:
	int              m_id;          //!< Unique Id for all componnents
	M5ComponentTypes m_type;        //!< To of Component used for searching
	static int       s_componentID; //!< Static id counter shared by all components.
};


#endif // M5COMPONENT_H