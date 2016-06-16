#include "CircleParticle.h"

CircleParticle::CircleParticle(
	const std::string& textrue,const GSvector2& center,
	float speed, float angle, float alphaSpeed)
	:textrue(textrue),center(center), speed(speed), angle(angle),
	position(center), alpha(1), isDead(false), alphaSpeed(alphaSpeed)
{
	initialize();
}

CircleParticle::~CircleParticle()
{
}

void CircleParticle::initialize()
{
	position = center;
	isDead = false;
}
void CircleParticle::update()
{
	GSvector2 v;
	gsVector2FromDirection(&v, angle);
	position += v*speed*gsFrameTimerGetTime();

	isDead= alpha<=0;

	alpha -= alphaSpeed*gsFrameTimerGetTime();
}

void CircleParticle::draw(const Renderer& renderer, const Scroll& scroll)
{

	renderer.DrawTextrue(textrue, &scroll.transformViewPosition(position), NULL, &GSvector2(4, 4), NULL, alpha * 180, &GScolor(1, 1, 1, alpha));
}

const bool CircleParticle::getIsDead()const
{
	return isDead;
}
