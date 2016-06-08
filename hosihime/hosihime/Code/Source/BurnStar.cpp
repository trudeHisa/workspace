#include "BurnStar.h"

BurnStar::BurnStar(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect, StarMove_Ptr move)
	:GameObject(textrue, position, viewSize, rect, BURNSTAR),
	Star(textrue, position, viewSize, rect, move)
{
}

BurnStar::~BurnStar()
{
}

void BurnStar::initialize()
{
	Star::initialize();
}
void BurnStar::updata()
{
	Star::updata();
}
void BurnStar::collision(const GameObject* obj)
{
	Star::collision(obj);
}
void BurnStar::draw(const Renderer& renderer, const Scroll& scroll)
{
	Star::draw(renderer,scroll);
}

Star* BurnStar::clone()
{
	return new BurnStar(textrue, startPosi, viewSize, rect, StarMove_Ptr(move->clone()));
}
GameObject* BurnStar::clone(const GSvector2& position)
{
	return new BurnStar(textrue, position, viewSize, rect, StarMove_Ptr(move->clone()));
}