#include "CircleEffect.h"
CircleEffect::CircleEffect()
	:circle(GSvector2(0,0))
{

}

CircleEffect::CircleEffect(const GSvector2& position)
	: circle(position)
{
}

CircleEffect::~CircleEffect()
{
}

void CircleEffect::initialize()
{
	circle.initialize();
}
void CircleEffect::update()
{
	circle.update();
}
void CircleEffect::draw(const Renderer& renderer, const Scroll& scroll)
{
	circle.draw(renderer,scroll);
}
void CircleEffect::finish()
{
}
const bool CircleEffect::getisEnd()const
{
	return circle.getisEnd();
}
IEffect* CircleEffect::clone(const GSvector2& position)
{
	return new CircleEffect(position);
}