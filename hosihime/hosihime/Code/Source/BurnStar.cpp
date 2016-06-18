#include "BurnStar.h"

BurnStar::BurnStar(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	float helth, StarMove_Ptr move,IEffectMediator* effectMediator)
	:GameObject(textrue, position, viewSize, rect, BURNSTAR),
	Star(textrue, position, viewSize, rect, helth, move,effectMediator),
	animTimer(60), anim(anim)
{
}

BurnStar::~BurnStar()
{
}

void BurnStar::initialize()
{
	Star::initialize();
	animTimer.initialize();
	animTimer.setStarTimer(60.f);
	anim.addCell("F", 1,2, 64, 64);//�ړ���
}
void BurnStar::updata()
{
	Star::updata();
	anim.updata("F");
	animTimer.updata();
}
void BurnStar::collision(const GameObject* obj)
{
	Star::collision(obj);
}
void BurnStar::draw(const Renderer& renderer, const Scroll& scroll)
{
	Star::draw(renderer,scroll);
	anim.draw(renderer, "fire.bmp", &scroll.transformViewPosition(position));
}

Star* BurnStar::clone()
{
	return new BurnStar(textrue, startPosi, viewSize, rect, helth, StarMove_Ptr(move->clone()), effectMediator);
}
GameObject* BurnStar::clone(const GSvector2& position)
{
	return new BurnStar(textrue, position, viewSize, rect, helth, StarMove_Ptr(move->clone()), effectMediator);
}