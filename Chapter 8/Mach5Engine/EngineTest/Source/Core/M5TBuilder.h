/******************************************************************************/
/*!
\file   M5TBuilder.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/11/03

Base class Builder for easily instantiating M5Components

*/
/******************************************************************************/
#ifndef M5T_BUILDER_H
#define M5T_BUILDER_H

//! Base Builder class to create templated builders via a templated factory
template <typename Return>
class M5BaseTBuilder
{
public:
	~M5BaseTBuilder() {} //empty virtual destructor
		             //Virtual Build call that must be overloaded by all Derived Builders
	virtual Return* Build(void) = 0;
private:
};

/*! Templated builder derived class so I don't need to create a Builder for each
M5Component type*/
template <typename Return, typename T>
class M5TBuilder : public M5BaseTBuilder<Return>
{
public:
	virtual Return* Build(void);
private:
};


//! Creates a new M5Component of type T
template <typename Return, typename T>
Return* M5TBuilder<Return, T>::Build(void)
{
	return new T();
}



#endif // M5T_BUILDER_H
