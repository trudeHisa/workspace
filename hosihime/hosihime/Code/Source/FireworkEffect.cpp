#include "FireworkEffect.h"
FireworkEffect::FireworkEffect()
	:firework(GSvector2(0, 0))
{
}
FireworkEffect::FireworkEffect(const GSvector2& position)
	: firework(position)
{

}
FireworkEffect::~FireworkEffect()
{
}
void FireworkEffect::initialize()
{
	firework.initialize();
}
void FireworkEffect::update()
{
	firework.update();
}
void FireworkEffect::draw(const Renderer& renderer, const Scroll& scroll)
{
	firework.draw(renderer, scroll);
}
void FireworkEffect::finish()
{
	firework.finish();
}
const bool FireworkEffect::getIsEnd()const
{
	return firework.getIsEnd();
}
IEffect* FireworkEffect::clone(const GSvector2& position)
{
	return new FireworkEffect(position);
}