#include "BulletComponent.h"
#include "Core\M5Gfx.h"
#include "Core\M5Math.h"
#include "Core\M5Object.h"
#include "EngineTest\M5ObjectPool.h"    
#include "Core\GfxComponent.h"


BulletComponent::BulletComponent():
M5Component(CT_BulletComponent)
{
}

void BulletComponent::Update(float /*dt*/)
{
	M5Vec2 pos = m_pObj->pos;
	M5Vec2 scale = m_pObj->scale;
	scale *= .5f;
	M5Vec2 botLeft;
	M5Vec2 topRight;
	M5Gfx::GetWorldBotLeft(botLeft);
	M5Gfx::GetWorldTopRight(topRight);

	if (pos.x + scale.x > topRight.x || pos.x - scale.x < botLeft.x ||
		pos.y + scale.y > topRight.y || pos.y - scale.y < botLeft.y)
	{

		m_pObj->scale = M5Vec2(1.5f, 1.5f);
		M5ObjectPool<AT_Bullet>::ReleaseObject(m_pObj);
	}

}

M5Component * BulletComponent::Clone(void)
{
	BulletComponent * pNew = new BulletComponent;
	pNew->m_pObj = m_pObj;
	return pNew;
}
