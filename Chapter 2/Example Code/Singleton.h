template <typename T>
class Singleton
{
public:
	Singleton()
	{
		// Set our instance variable when we are created
		if (instance == nullptr)
		{
			instance = static_cast<T*>(this);
		}
		else
		{
			// If instance already exists, we have a problem
			printf("\nError: Trying to create more than one Singleton");
		}
	}

	// Once destroyed, remove access to instance
	virtual ~Singleton()
	{
		instance = nullptr;
	}

	// Get a reference to our instance
	static T & GetInstance()
	{
		return *instance;
	}

	// Creates an instance of our instance
	static void CreateInstance()
	{
		new T();
	}

	// Deletes the instance, needs to be called or resource leak
	static void RemoveInstance()
	{
		delete instance;
	}

private:
	// Note, needs to be a declaration
	static T * instance;

};

template <typename T> T * Singleton<T>::instance = nullptr;

class HighScoreManager : public Singleton<HighScoreManager>
{
public:
	void CheckHighScore(int score);

private:
	int highScore;
};