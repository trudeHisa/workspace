#include "BreakStar.h"

BreakStar::BreakStar(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize,const MyRectangle& rect,
	float max_Durability, StarMode_Ptr move)
	:GameObject(textrue, position, viewSize, rect, BREAKSTAR),
	Star(textrue, position, viewSize, rect,move),
	durability(max_Durability), max_Durability(max_Durability)
{
}

BreakStar::~BreakStar()
{
}

void BreakStar::initialize()
{
	GameObject::initialize();
	Star::initialize();
	durability = max_Durability;
}
void BreakStar::updata()
{
	Star::updata();
}
void BreakStar::collision(const GameObject* obj)
{
	Star::collision(obj);
	if (obj->getType()==PLAYER)
	{
		durability -= gsFrameTimerGetTime();
		if (durability <= 0)
		{
			isDead = true;
		}
	}
}
void BreakStar::draw(const Renderer& renderer, const Scroll& scroll)
{
	Star::draw(renderer,scroll);
}
Star* BreakStar::clone()
{
	return new BreakStar(textrue, startPosi, viewSize, rect, max_Durability, StarMode_Ptr(move->clone()));
}
GameObject* BreakStar::clone(const GSvector2& position)
{
	return new BreakStar(textrue, position, viewSize, rect, max_Durability, StarMode_Ptr(move->clone()));
}