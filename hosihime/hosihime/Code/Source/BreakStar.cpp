#include "BreakStar.h"

BreakStar::BreakStar(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	StarMove_Ptr move, float max_Durability)
	:GameObject(textrue, position, viewSize, rect, BREAKSTAR),
	Star(textrue, position, viewSize, rect, move,max_Durability),
	durability(max_Durability), max_Durability(max_Durability),
	isBreakStart(false)
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
	isBreakStart = false;
	blinkerTime = 0;
	blinker = false;
}
void BreakStar::updata()
{
	Star::updata();
	if (!isBreakStart)
	{
		return;
	}
	durability -= gsFrameTimerGetTime();
	if (durability <= 0)
	{
		isDead = true;
	}
	if (durability < max_Durability / 2)
	{
		//¯‚ð“_–Å‚³‚¹‚é
		blinkerTime += gsFrameTimerGetTime();
		if (blinkerTime > 0.1f)
		{
			blinker = !blinker;//bool’l‚ÌØ‚è‘Ö‚¦
		}
	}
}
void BreakStar::collision(const GameObject* obj)
{
	Star::collision(obj);
	if (obj->getType() == PLAYER)
	{
		isBreakStart = true;
	}
}
void BreakStar::draw(const Renderer& renderer, const Scroll& scroll)
{
	//¯‚Ì•\Ž¦
	if (blinker)
	{
		Star::draw(renderer, scroll);
	}
	//Star::draw(renderer, scroll);
}
Star* BreakStar::clone()
{
	return new BreakStar(textrue, startPosi, viewSize, rect, StarMove_Ptr(move->clone()), max_Durability);
}
GameObject* BreakStar::clone(const GSvector2& position)
{
	return new BreakStar(textrue, position, viewSize, rect, StarMove_Ptr(move->clone()), max_Durability);
}