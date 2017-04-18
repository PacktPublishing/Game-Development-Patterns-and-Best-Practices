#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

class Observer
{
public:
	virtual ~Observer(void) {}
	virtual void Update(float currentHealth, float maxHealth) = 0;
};
class Subject
{
public:
	virtual ~Subject(void) {}
	virtual void RegisterObserver(Observer* pToAdd)      = 0;
	virtual void UnregisterObserver(Observer* pToRemove) = 0;
	virtual void Notify(void)                            = 0;
};



class Player : public Subject
{
public:
	Player(float maxHealth);
	void AdjustHealth(float adjustValue);
	virtual void RegisterObserver(Observer* pToAdd);
	virtual void UnregisterObserver(Observer* pToRemove);
	virtual void Notify(void);
private:
	typedef std::vector<Observer*> ObserverVec;

	float       m_maxHealth;
	float       m_health;
	ObserverVec m_observers;
};
Player::Player(float maxHealth):
	m_maxHealth(maxHealth),
	m_health(maxHealth)
{
}
void Player::AdjustHealth(float adjustValue)
{
	m_health += adjustValue;
	Notify();
}
void Player::RegisterObserver(Observer* pToAdd)
{
	ObserverVec::iterator itor; 
	itor = std::find(m_observers.begin(), m_observers.end(), pToAdd);
	assert(itor == m_observers.end());
	m_observers.push_back(pToAdd);
}
void Player::UnregisterObserver(Observer* pToRemove)
{
	ObserverVec::iterator itor;
	itor = std::find(m_observers.begin(), m_observers.end(), pToRemove);
	
	if (itor != m_observers.end())
	{
		std::swap(*itor, *(--m_observers.end()));
		m_observers.pop_back();
	}
}
void Player::Notify(void)
{
	size_t size = m_observers.size();
	for (size_t i = 0; i < size; ++i)
		m_observers[i]->Update(m_health, m_maxHealth);
}



class PlayerDisplay : public Observer
{
public:
	PlayerDisplay(Subject* subject);
	~PlayerDisplay(void);
	void Display(void) const;
	virtual void Update(float currentHealth, float maxHealth);
private:
	float    m_health;
	Subject* m_subject;
};
PlayerDisplay::PlayerDisplay(Subject* subject):
	m_health(0.0f),
	m_subject(subject)
{
	m_subject->RegisterObserver(this);
}
PlayerDisplay::~PlayerDisplay(void)
{
	m_subject->UnregisterObserver(this);
}
void PlayerDisplay::Display(void) const
{
	printf("Health: %6.0f\n", m_health);
}
void PlayerDisplay::Update(float currentHealth, float /*maxHealth*/)
{
	m_health = currentHealth;
}



class PlayerHealthBar : public Observer
{
public:
	PlayerHealthBar(Subject* subject);
	~PlayerHealthBar(void);
	void Display(void) const;
	virtual void Update(float currentHealth, float maxHealth);
private:
	float       m_percent;
	std::string m_color;
	Subject*    m_subject;
};
PlayerHealthBar::PlayerHealthBar(Subject* subject):
	m_percent(0.0f),
	m_color(),
	m_subject(subject)
{
	m_subject->RegisterObserver(this);
}
PlayerHealthBar::~PlayerHealthBar(void)
{
	m_subject->UnregisterObserver(this);
}
void PlayerHealthBar::Display(void) const
{
	printf("Status: %6s %4.0f%%\n", m_color.c_str(), m_percent);
}
void PlayerHealthBar::Update(float currentHealth, float maxHealth)
{
	m_percent = (currentHealth / maxHealth) * 100.f;

	if (m_percent >= 75.0f)
		m_color = "Green";
	else if (m_percent < 75.0f && m_percent > 35.0f)
		m_color = "Yellow";
	else
		m_color = "Red";

}


class StageLogic : public Observer
{
public:
	StageLogic(Subject* subject);
	bool IsQuitting(void) const;
	~StageLogic(void);
	virtual void Update(float currentHealth, float maxHealth);
private:
	bool     m_isQuitting;
	Subject* m_subject;
};
StageLogic::StageLogic(Subject* subject):
	m_isQuitting(false),
	m_subject(subject)
{
	m_subject->RegisterObserver(this);
}
bool StageLogic::IsQuitting(void) const
{
	return m_isQuitting;
}
StageLogic::~StageLogic(void)
{
	m_subject->UnregisterObserver(this);
}
void StageLogic::Update(float currentHealth, float /*maxHealth*/)
{
	if (currentHealth <= 0)
		m_isQuitting = true;
}




int main(void)
{
	//Our value to decrement by
	const float DECREMENT = -1.0f;
	const float STARTING_HEALTH = 5.0f;

	//creating our objects
	Player player(STARTING_HEALTH);
	PlayerDisplay display(&player);
	PlayerHealthBar bar(&player);
	StageLogic quitLogic(&player);

	//Set the inital values to print
	player.Notify();

	//loop until player is dead
	while (!quitLogic.IsQuitting())
	{
		display.Display();
		bar.Display();
		player.AdjustHealth(DECREMENT);
	}

	return 0;
}