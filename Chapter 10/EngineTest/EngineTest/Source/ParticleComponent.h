/******************************************************************************/
/*!
\file   ParticleComponent.h
\author John Doran
\par    email: john@johnpdoran.com
\par    Mach5 Game Engine
\date   2016/12/06

Particle system component. Allows you to draw many particles on the screen.
*/
/******************************************************************************/
#ifndef PARTICLE_COMPONENT_H
#define PARTICLE_COMPONENT_H

#include "Core\M5Component.h"
#include "Core\M5Vec2.h"
#include "Core\M5Random.h"
#include "Core\M5Object.h"
#include <map>

enum ParticleType
{
	PS_Static,
	PS_Moving
};


// Abstract class for us to derive from
class ParticleSystem
{
public:
	float lifeTime;
	M5Vec2 startScale;
	float endScale;

	// Pure virtual functions
	virtual void Init(M5Object * object) = 0;
	virtual void Update(M5Object * object, float dt, float lifeLeft) = 0;

	float Lerp(float start, float end, float fraction);

};

class StaticParticleSystem : public ParticleSystem
{
	void Init(M5Object * obj);	

	void Update(M5Object *, float, float);

};

class MovingParticleSystem : public ParticleSystem
{
	void Init(M5Object * obj);

	void Update(M5Object *, float, float);

};

class ParticleFactory
{
public:
	static int objectCount;
	static std::map<ParticleType, ParticleSystem *> particleSystems;

	// Getting our Flyweight
	static ParticleSystem & GetParticleSystem(ParticleType type);
	~ParticleFactory();
};



class ParticleComponent : public M5Component
{
public:
	ParticleComponent();
	virtual void Update(float dt);
	virtual M5Component* Clone(void);
	virtual void FromFile(M5IniFile& iniFile);
	bool activated;
	float lifeLeft;

private:
	ParticleType particleType;
};

#endif // !PARTICLE_COMPONENT_H

