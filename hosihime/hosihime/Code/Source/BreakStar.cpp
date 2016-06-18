#include "BreakStar.h"

BreakStar::BreakStar(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	float helth, StarMove_Ptr move, float max_Durability, IEffectMediator* effectMediator)
	:GameObject(textrue, position, viewSize, rect, BREAKSTAR),
	Star(textrue, position, viewSize, rect, helth, move,effectMediator),
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
		//êØÇì_ñ≈Ç≥ÇπÇÈ
		blinkerTime += gsFrameTimerGetTime();
		if (blinkerTime > 0.1f)
		{
			blinker = !blinker;//boolílÇÃêÿÇËë÷Ç¶
		}
	}
	/* */
	if (durability < max_Durability / 5)
	{
		textrue = "star_break1.bmp";
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
	//êØÇÃï\é¶
	if (blinker)
	{
		Star::draw(renderer, scroll);
	}
	//Star::draw(renderer, scroll);
}
Star* BreakStar::clone()
{
	return new BreakStar(textrue, startPosi, viewSize, rect, helth,StarMove_Ptr(move->clone()), max_Durability,effectMediator);
}
GameObject* BreakStar::clone(const GSvector2& position)
{
	return new BreakStar(textrue, position, viewSize, rect, helth, StarMove_Ptr(move->clone()), max_Durability, effectMediator);
}