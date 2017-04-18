#include <iostream>
#include <cstdlib>
#include <ctime>

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
	virtual Shape* Clone(void) const
	{
		return new Circle(*this);
	}
};

class Square : public Shape
{
public:
	virtual void Draw(void) const
	{
		std::cout << "I'm a Square" << std::endl;
	}
	virtual Shape* Clone(void) const
	{
		return new Square(*this);
	}
};

class Triangle : public Shape
{
public:
	virtual void Draw(void) const
	{
		std::cout << "I'm a Triangle" << std::endl;
	}
	virtual Shape* Clone(void) const
	{
		return new Triangle(*this);
	}
};
class CircleSpawner
{
public:
	CircleSpawner(Circle* pCircle, float maxTime) :
		m_pToSpawn(pCircle),
		m_spawnTime(0.f),
		m_maxSpawnTime(maxTime)
	{
	}
	void Update(float dt)
	{
		m_spawnTime += dt;
		if (m_spawnTime > m_maxSpawnTime)
		{
			//Use copy constructor
			Circle* pClone = new Circle(*m_pToSpawn);

			//…Register the clone somehow 
			//Right now this will leak

			//Reset timer  
			m_spawnTime = 0;
		}
	}
private:
	Circle* m_pToSpawn;
	float   m_spawnTime;
	float   m_maxSpawnTime;
};

int main(void)
{
	//init srand
	std::srand(static_cast<unsigned>(time(0)));
	//Create my shapes
	const int MAX = 3;
	Shape* shapes[MAX] = { new Circle(), new Square(), new Triangle() };

	//
	for (int i = 0; i < MAX * 2; ++i)
	{
		Shape* copy = shapes[std::rand() % MAX]->Clone();
		copy->Draw();
		delete copy;
	}

	//make sure to delete my original shapes
	for (int i = 0; i < MAX; ++i)
		delete shapes[i];

	return 0;
}