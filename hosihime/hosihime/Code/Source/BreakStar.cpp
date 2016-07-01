#include "BreakStar.h"

BreakStar::BreakStar(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	float helth, StarMove_Ptr move, float max_Durability, 
	IEffectMediator* effectMediator, Device& device)
	:GameObject(textrue, position, viewSize, rect, GAMEOBJ_TYPE::BREAKSTAR),
	Star(textrue, position, viewSize, rect, helth,
	move,effectMediator,device),
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
		//星を点滅させる
		blinkerTime += gsFrameTimerGetTime();
		if (blinkerTime > 0.1f)
		{
			blinker = !blinker;//bool値の切り替え
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
	if (obj->getType() == GAMEOBJ_TYPE::PLAYER)
	{
		isBreakStart = true;
	}
}
void BreakStar::draw(const Renderer& renderer, const Scroll& scroll)
{
	//星の表示
	//if (blinker)
	//{
	//	Star::draw(renderer, scroll);
	//}
	Star::draw(renderer, scroll);
}
Star* BreakStar::clone()
{
	return new BreakStar(textrue, startPosi, viewSize, rect, helth,
		StarMove_Ptr(move->clone()), max_Durability, effectMediator, device);
}
GameObject* BreakStar::clone(const GSvector2& position)
{
	return new BreakStar(textrue, position, viewSize, rect, helth,
		StarMove_Ptr(move->clone()), max_Durability, effectMediator, device);
}