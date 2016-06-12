#include "CircleParticle.h"

CircleParticle::CircleParticle(
	const std::string& textrue,const GSvector2& center,
	float speed, float angle, float maxDistance)
	:textrue(textrue),center(center), speed(speed), angle(angle),
	maxDistance(maxDistance), position(center), alpha(1), isDead(false)
{
}

CircleParticle::~CircleParticle()
{
}

void CircleParticle::initialize()
{
	position = center;
	isDead = false;
}
void CircleParticle::updata()
{
	GSvector2 v;
	gsVector2FromDirection(&v, angle);
	position += v*speed*gsFrameTimerGetTime();

	isDead=center.distance(position) >= maxDistance;

	alpha -=0.01f*gsFrameTimerGetTime();
}

void CircleParticle::draw(const Renderer& renderer)
{
	renderer.DrawTextrue(textrue, &position,&GScolor(1,1,1,alpha));
}

const bool CircleParticle::getIsDead()const
{
	return isDead;
}
