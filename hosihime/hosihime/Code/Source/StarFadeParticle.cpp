#include "StarFadeParticle.h"

StarFadeParticle::StarFadeParticle(const GSvector2& position)
:position(position), vel(GSvector2(-1, 1)), speed(4.0f), isDead(false)
{
}

StarFadeParticle::~StarFadeParticle()
{
}
void StarFadeParticle::initialize()
{
	isDead = false;
}
void StarFadeParticle::update()
{
	position += vel*speed*gsFrameTimerGetTime();
}
void StarFadeParticle::draw(const Renderer& renderer)
{
	isDead = position.y > 720;
	renderer.drawTextrue("teil.bmp", &position);
}
const bool StarFadeParticle::getIsDead()const
{
	return isDead;
}

