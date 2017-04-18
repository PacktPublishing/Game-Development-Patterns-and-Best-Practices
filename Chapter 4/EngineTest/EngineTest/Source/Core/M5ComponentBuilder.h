/******************************************************************************/
/*!
\file   M5ComponentBuilder.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/22

Base class Builder for easily instantiating M5Components

*/
/******************************************************************************/
#ifndef M5COMPONENT_BUILDER_H
#define M5COMPONENT_BUILDER_H

//Forward declaration
class M5Component;

//! Base Builder class to create M5Components via a M5ComonentFactory
class M5ComponentBuilder
{
public:
	~M5ComponentBuilder() {} //empty virtual destructor
	//! Virtual Build call that must be overloaded by all Derived Builders
	virtual M5Component* Build(void) = 0;
private:
};

/*! Templated builder derived class so I don't need to create a Builder for each
M5Component type*/
template <typename T>
class M5ComponentTBuilder : public M5ComponentBuilder
{
public:
	virtual M5Component* Build(void);
private:
};


//! Creates a new M5Component of type T
template <typename T>
M5Component* M5ComponentTBuilder<T>::Build(void)
{
	return new T();
}



#endif // M5COMPONENT_BUILDER_H
