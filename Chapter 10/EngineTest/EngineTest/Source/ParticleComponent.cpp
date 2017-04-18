/******************************************************************************/
/*!
\file   ParticleComponent.cpp
\author John Doran
\par    email: john@johnpdoran.com
\par    Mach5 Game Engine
\date   2016/12/06

Particle system component. Allows you to draw many particles on the screen.
*/
/******************************************************************************/
#include "ParticleComponent.h"
#include "Core\M5Gfx.h"
#include "Core\M5Math.h"
#include "Core\M5Object.h"
#include "EngineTest\M5ObjectPool.h"    
#include "Core\GfxComponent.h"
#include "Core\M5IniFile.h"
#include <map>

// Define our static variables
int ParticleFactory::objectCount = 0;
std::map<ParticleType, ParticleSystem *> ParticleFactory::particleSystems;


/******************************************************************************/
/*!
Will give you the percentage of the fraction from start to end

\param start
What value to start from

\param end
What value to end from

\param fraction
What percentage of the way are we are from start to finish

*/
/******************************************************************************/
float ParticleSystem::Lerp(float start, float end, float fraction)
{
	return start + fraction * (end - start);
}


/******************************************************************************/
/*!
Used to initalize the particle system and set any parameters needed

\param obj
A reference to the object

*/
/******************************************************************************/
void StaticParticleSystem::Init(M5Object * obj)
{
	obj->vel = M5Vec2(0, 0);
}

/******************************************************************************/
/*!
Used to update the particle system. Called once per frame

\param m_pObj
A reference to the object

\param dt
Amount of time that has passed since the previous frame

\param lifeLeft
The amount of lifetime the object has left

*/
/******************************************************************************/
void StaticParticleSystem::Update(M5Object * m_pObj, float /*dt*/, float lifeLeft)
{
	// Change our size based on where we want it to be
	float currentPercentage = 1 - (lifeLeft / lifeTime);
	m_pObj->scale.x = Lerp(startScale.x, startScale.x * endScale, currentPercentage);
	m_pObj->scale.y = Lerp(startScale.y, startScale.y * endScale, currentPercentage);
}

/******************************************************************************/
/*!
Used to initalize the particle system and set any parameters needed

\param obj
A reference to the object

*/
/******************************************************************************/
void MovingParticleSystem::Init(M5Object * obj)
{
	obj->vel = M5Vec2(M5Random::GetFloat(-1, 1), M5Random::GetFloat(-1, 1)) * 10;
}

/******************************************************************************/
/*!
Used to update the particle system. Called once per frame

\param m_pObj
A reference to the object

\param dt
Amount of time that has passed since the previous frame

\param lifeLeft
The amount of lifetime the object has left

*/
/******************************************************************************/
void MovingParticleSystem::Update(M5Object * m_pObj, float /*dt*/, float lifeLeft)
{
	// Change our size based on where we want it to be
	float currentPercentage = 1 - (lifeLeft / lifeTime);
	m_pObj->scale.x = Lerp(startScale.x, startScale.x * endScale, currentPercentage);
	m_pObj->scale.y = Lerp(startScale.y, startScale.y * endScale, currentPercentage);
}

/******************************************************************************/
/*!
Used to get our Flyweight object and access the shared properties of the 
particles.

\param type
What kind of particle we want to get access to

*/
/******************************************************************************/
ParticleSystem & ParticleFactory::GetParticleSystem(ParticleType type)
{
	// If our object exists, return it
	if (particleSystems.find(type) != particleSystems.end())
	{
		return  *particleSystems[type];
	}

	ParticleSystem * newSystem = nullptr;

	// Otherwise, let's create one
	switch (type)
	{
	case PS_Static:
		newSystem = new StaticParticleSystem();
		newSystem->endScale = 0;
		newSystem->lifeTime = 1.5;
		newSystem->startScale = M5Vec2(2.5, 2.5);

		particleSystems[PS_Static] = newSystem;

		objectCount++;
		break;

	case PS_Moving:
		newSystem = new MovingParticleSystem();
		newSystem->endScale = 0;
		newSystem->lifeTime = 1.5;
		newSystem->startScale = M5Vec2(2.5, 2.5);
		particleSystems[PS_Moving] = newSystem;
		objectCount++;
		break;

	}

	return *newSystem;

}

/******************************************************************************/
/*!
Deconstructor for the ParticleFactory. Removes all of the elements in our
particleSystems map

*/
/******************************************************************************/
ParticleFactory::~ParticleFactory()
{
	for (auto iterator = particleSystems.begin(); 
		 iterator != particleSystems.end(); 
		 iterator++) 
	{
		// iterator->first = key
		// iterator->second = value
		delete iterator->second;
	}

}


/******************************************************************************/
/*!
Construtor for ParticleSystem component.  Sets default values
*/
/******************************************************************************/
ParticleComponent::ParticleComponent() :
	M5Component(CT_ParticleComponent)
{
}

/******************************************************************************/
/*!
Takes care of the particle system, decrease lifetime and adjust scaling.
Will mark for destruction if needed.

\param [in] dt
The time in seconds since the last frame.
*/
/******************************************************************************/
void ParticleComponent::Update(float dt)
{
	// Decrease our life by the change in time this frame (delta time, dt)
	lifeLeft -= dt;

	ParticleFactory::GetParticleSystem(particleType).Update(m_pObj, dt, lifeLeft);

	// If there is no life left, destroy our object
	if (lifeLeft <= 0)
	{
		m_pObj->isDead = true;
	}

}


/******************************************************************************/
/*!
Clones the current component and updates it with the correct information.

\return
A new component that is a clone of this one
*/
/******************************************************************************/
M5Component * ParticleComponent::Clone(void)
{
	ParticleComponent * pNew = new ParticleComponent;
	pNew->m_pObj = m_pObj;
	pNew->particleType = particleType;

	ParticleSystem & system = ParticleFactory::GetParticleSystem(particleType);
	system.Init(pNew->m_pObj);
	pNew->lifeLeft = system.lifeTime;
	return pNew;
}

/******************************************************************************/
/*!
Reads in data from a preloaded ini file.

\param [in] iniFile
The preloaded inifile to read from.
*/
/******************************************************************************/
void ParticleComponent::FromFile(M5IniFile& iniFile)
{
	// Get our initial particle type
	std::string particleTypeText;
	iniFile.SetToSection("ParticleComponent");
	iniFile.GetValue("type", particleTypeText);
	
	if (particleTypeText == "Static")
	{
		particleType = PS_Static;
	}
	else if(particleTypeText == "Moving")
	{
		particleType = PS_Moving;

	}
	
}