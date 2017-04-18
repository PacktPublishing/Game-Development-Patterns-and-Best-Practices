#include <iostream>

class Shape
{
public:
	virtual ~Shape(void) {}//empty base class constructor
	virtual void Draw(void) const = 0;
	virtual Shape* Clone(void) const = 0;
};

class Circle : public Shape
{
public:
	virtual void Draw(void) const
	{
		std::cout << "I'm a Circle" << std::endl;
	}
	virtual Circle* Clone(void) const
	{
		return new Circle(*this);
	}
};

int main(void)
{
	Circle* pCircle = new Circle();
	//No need to cast
	Circle* pClone = pCircle->Clone();
	
	//... Do sopmething Circle specific with pClone

	delete pClone;
	delete pCircle;
	return 0;
}