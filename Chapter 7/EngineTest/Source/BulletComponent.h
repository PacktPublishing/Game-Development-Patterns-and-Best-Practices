#ifndef BULLET_COMPONENT_H
#define BULLET_COMPONENT_H

#include "Core\M5Component.h"

//!< Removes The parent Game Object if it is outside the view port
class BulletComponent : public M5Component
{
public:
	BulletComponent();
	virtual void Update(float dt);
	virtual M5Component* Clone(void);
	bool activated;
};

#endif // !BULLET_COMPONENT_H

