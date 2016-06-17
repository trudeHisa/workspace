#include "StarEffect.h"


StarEffect::StarEffect()
:star(GSvector2(0,0))

{
}

StarEffect::StarEffect(const GSvector2& postion)
: star(postion)
{
}

StarEffect::~StarEffect()
{
}
void StarEffect::initialize()
{
	star.initialize();
}
void  StarEffect::update()
{
	star.update();
}
void StarEffect::draw(const Renderer& renderer)
{
	star.draw(renderer);
}
void StarEffect::finish()
{

}
const bool StarEffect::getIsEnd()const
{
	return star.getIsEnd();
}
IEffect* StarEffect::clone(const GSvector2& position)
{
	return new StarEffect(position);
}
