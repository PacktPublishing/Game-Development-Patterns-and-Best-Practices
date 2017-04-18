#include <iostream>

//To make using functions pointers easier
typedef int (*OneArgFunc)(int);
typedef int (*TwoArgsFunc)(int, int);

//The different actions to do
int Square(int x)
{
	return x * x;
}

int Cube(int x)
{
	return x*x*x;
}
int Add(int x, int y)
{
	return x + y;
}

//Base Command Class
class Command
{
public:
	virtual ~Command(void) {}
	virtual void Execute(void) = 0;
};

//Derived command classes
class Square5Command : public Command
{
public:
	virtual void Execute(void)
	{
		std::cout << "5 squared is " << Square(5) << std::endl;
	}
};

class OneArgCommand : public Command
{
public:
	OneArgCommand(OneArgFunc action, int* pValue):
		m_action(action), m_pValue(pValue)
	{
	}
	virtual void Execute(void)
	{
		*m_pValue = m_action(*m_pValue);
	}
private:
	OneArgFunc m_action;
	int* m_pValue;
};
class TwoArgCommand : public Command
{
public:
	TwoArgCommand(TwoArgsFunc action, int x, int y) :
		m_action(action), m_first(x), m_second(y)
	{
	}
	virtual void Execute(void)
	{
		std::cout << "The Result is " << m_action(m_first, m_second) << std::endl;
	}
private:
	TwoArgsFunc m_action;
	int     m_first;
	int     m_second;
};

class SomeObject
{
public:
	SomeObject(int x):m_x(x)
	{
	}

	void Display(void)
	{
		std::cout << "x is " << m_x << std::endl;
	}
	void Change(void)
	{
		m_x += m_x;
	}

private:
	int m_x;
};
typedef void (SomeObject::*SomeObjectMember)(void);
class SomeObjectCommand : public Command
{
public:
	SomeObjectCommand(SomeObject* pObj, SomeObjectMember member) :
		m_pObj(pObj), m_member(member)
	{
	}
	virtual void Execute(void)
	{
		(m_pObj->*m_member)();
	}
private:
	SomeObject* m_pObj;
	SomeObjectMember m_member;
};
template<typename Type, typename Method>
class TMethodCommand: public Command
{
public:
	TMethodCommand(Type* pObj, Method method) :m_pObj(pObj), m_method(method)
	{
	}
	virtual void Execute(void)
	{
		(m_pObj->*m_method)();
	}
private:
	Type*  m_pObj;
	Method m_method;
};

int main(void)
{
	const int SIZE = 6;
	int value = 2;
	SomeObject object(10);
	Command* commands[SIZE] = {
		new Square5Command,
		new OneArgCommand(Square, &value),
		new OneArgCommand(Cube, &value),
		new TwoArgCommand(Add, 5, 6),
		new SomeObjectCommand(&object, &SomeObject::Display),
		new TMethodCommand<SomeObject, SomeObjectMember>(&object, &SomeObject::Change)
	};


	//The Client Code
	commands[0]->Execute();//Square5
	std::cout << "value is " << value << std::endl;
	commands[1]->Execute();//OneArg Square
	std::cout << "value is " << value << std::endl;
	commands[2]->Execute();//OneArg Cube
	std::cout << "value is " << value << std::endl;
	commands[3]->Execute();//TwoArg

	//Member function pointers
	commands[4]->Execute();//Display
	commands[5]->Execute();//Change 
	commands[4]->Execute();//Display

	for (int i = 0; i < SIZE; ++i)
		delete commands[i];

	return 0;
}