#include "StarParticle.h"


StarParticle::StarParticle(const std::string& textrue,
	float angle/*deg*/, float speed, const GSvector2& position)
	: textrue(textrue), GRAVITY(0.2f),
	rotate(0), velocity(0, 0), isDead(false), alpha(1.0f),
	mt(rnd()), rand(0, 1), position(position)
{
	Calculate<float> calc;
	angle = calc.degTorad(angle);
	velocity.x = std::cos(angle);
	//velocity.x = speed;
	velocity.y = -std::sin(angle);
	//velocity.y = speed;
	velocity *= speed;
}
StarParticle::~StarParticle()
{
}
void StarParticle::initialize()
{
	isDead = false;
	alpha = 1.0f;
}
void StarParticle::update()
{
	rotate += gsFrameTimerGetTime()*velocity.x*8.0f;
	position += velocity*gsFrameTimerGetTime();
	//velocity.y += GRAVITY;
	alpha -= gsFrameTimerGetTime()*0.01f;
	isDead = alpha <= 0;
}
void StarParticle::draw(const Renderer& renderer, const Scroll& scroll)
{
	renderer.DrawTextrue(textrue, &scroll.transformViewPosition(position/* + GSvector2(60, 70+rand(mt)*15)*/),
		NULL, &GSvector2(4, 4), NULL, alpha * 180, &GScolor(rand(mt), rand(mt), rand(mt), alpha));
}
const bool StarParticle::getIsDead()const
{
	return isDead;
}