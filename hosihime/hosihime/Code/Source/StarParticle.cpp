#include "StarParticle.h"


StarParticle::StarParticle(const std::string& textrue,
	float angle/*deg*/, float speed, const GSvector2& position)
	: textrue(textrue), position(position), GRAVITY(0.1f),
	rotate(0), velocity(0, 0), isDead(false), alpha(1.0f)
{
	Calculate<float> calc;
	angle = calc.degTorad(angle);
	velocity.x = -std::cos(angle);
	velocity.y = -std::sin(angle);
	velocity *= speed;
}


StarParticle::~StarParticle()
{
}
void StarParticle::initialize()
{
	position = center;
	isDead = false;
}
void StarParticle::update()
{
	rotate += gsFrameTimerGetTime()*velocity.x*3.0f;
	position += velocity*gsFrameTimerGetTime();
	velocity.y += GRAVITY;
	alpha -= gsFrameTimerGetTime()*0.02f;
	isDead = alpha <= 0;
}
void StarParticle::draw(const Renderer& renderer)
{
	renderer.DrawTextrue(textrue, &position, NULL, &GSvector2(4, 4), NULL, alpha * 180, &GScolor(1, 1, 1, alpha));
}
const bool StarParticle::getIsDead()const
{
	return isDead;
}