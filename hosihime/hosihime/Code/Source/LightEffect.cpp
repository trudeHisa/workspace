#include "LightEffect.h"
LightEffect::LightEffect()
	:light(GSvector2(0, 0))
{

}

LightEffect::LightEffect(const GSvector2& position)
	: light(position)
{

}

LightEffect::~LightEffect()
{
}

void LightEffect::initialize()
{
	light.initialize();
}

void LightEffect::update()
{
	light.update();
}

void LightEffect::draw(const Renderer& renderer, const Scroll& scroll)
{
	light.draw(renderer,scroll);
}

void LightEffect::finish()
{

}

const bool LightEffect::getisEnd()const
{
	return light.getisEnd();
}

IEffect* LightEffect::clone(const GSvector2& position)
{
	return new LightEffect(position);
}