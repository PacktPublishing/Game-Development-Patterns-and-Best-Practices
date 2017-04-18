#include <string>
#include <iostream>
#include <list>

class GameObject;

class ObjectPool
{
private:
	std::list<GameObject*> pool;
	static ObjectPool* instance;

	// Private constructor so users are unable to create without GetInstance
	ObjectPool() {}

public:

	static ObjectPool* GetInstance();
	GameObject* AquireObject();
	void ReleaseObject(GameObject* object);
	void ClearPool();

};

class GameObject
{
private:
	// Character's health
	int currentHealth;
	int maxHealth;

	// Character's name
	std::string name;

public:
	GameObject();
	void Initialize(std::string _name = "Unnamed", int _maxHealth = -1);
	std::string GetInfo();

	void* operator new(size_t);
	void operator delete(void* obj);

};

/******************************************************************************/
/*!
Constructor that initializes the class' data
*/
/******************************************************************************/
GameObject::GameObject()
{
	Initialize();
}
	
/******************************************************************************/
/*!
Initalizes or resets the values of the class
*/
/******************************************************************************/
void GameObject::Initialize(std::string _name, int _maxHealth)
{
	name = _name;
	maxHealth = _maxHealth;
	currentHealth = maxHealth;
}

/******************************************************************************/
/*!
Prints out information about the class 
*/
/******************************************************************************/
std::string GameObject::GetInfo()
{
	return name + ": " + std::to_string(currentHealth) + "/" + std::to_string(maxHealth);
}

void* GameObject::operator new(size_t)
{
	return ObjectPool::GetInstance()->AquireObject();
}

void GameObject::operator delete(void* obj)
{
	ObjectPool::GetInstance()->ReleaseObject(static_cast<GameObject*>(obj));
}




ObjectPool* ObjectPool::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ObjectPool();
	}
	return instance;
}

/******************************************************************************/
/*!
Returns the first available object if it exists. If not, it will create a new
one for us
*/
/******************************************************************************/

GameObject* ObjectPool::AquireObject()
{
	// Check if we have any objects available
	if (!pool.empty())
	{
		// Get reference to an avaliable object
		GameObject* object = pool.back();

		// Since we are going to use it, it's no longer available, so
		// we need to remove the last element from our list
		pool.pop_back();

		// Finally, return the reference
		return object;
	}
	else
	{
		// If none are avaliable, create a new one
		return static_cast<GameObject*>(malloc(sizeof(GameObject)));
	}
}


/******************************************************************************/
/*!
Marks an object as being available again

\param
The object to be made available again
*/
/******************************************************************************/
void ObjectPool::ReleaseObject(GameObject* object)
{
	// Reset the object 
	object->Initialize();

	// Add it to our avaliable list
	pool.push_back(object);
}

/******************************************************************************/
/*!
Takes care of removing all of the objects from the pool whenever we're finished
working with it.
*/
/******************************************************************************/
void ObjectPool::ClearPool()
{
	while (!pool.empty())
	{
		GameObject * object = pool.back();
		pool.pop_back();
		free(object);
	}
}


ObjectPool* ObjectPool::instance = 0;


int main()
{
	ObjectPool* pool = ObjectPool::GetInstance();
	GameObject * slime = new GameObject();

	std::cout << "Initial: " << slime->GetInfo() << std::endl;

	slime->Initialize("Slime", 10);

	std::cout << "After Assignment: " << slime->GetInfo() << std::endl;

	delete slime;

	slime = new GameObject();

	std::cout << "Reused: " << slime->GetInfo() << std::endl;

	pool->ClearPool();
	delete pool;

	return 0;
}