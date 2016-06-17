#include "FireworkParticle.h"

FireworkParticle::FireworkParticle(const std::string& textrue,
	float angle/*deg*/, float speed, const GSvector2& position)
	:textrue(textrue), position(position), GRAVITY(0.1f),
	rotate(0), velocity(0, 0), isDead(false), alpha(1.0f)
{
	Calculate<float> calc;
	angle = calc.degTorad(angle);
	velocity.x = -std::cos(angle);
	velocity.y = -std::sin(angle);
	velocity *= speed;
}

FireworkParticle::~FireworkParticle()
{
}

void FireworkParticle::initialize()
{
	isDead = false;
	alpha=1.0f;
}
void FireworkParticle::update()
{
	rotate += gsFrameTimerGetTime()*velocity.x*3.0f;
	position += velocity*gsFrameTimerGetTime();
	velocity.y += GRAVITY;
	alpha -= gsFrameTimerGetTime()*0.02f;
	isDead = alpha <= 0;
}
void FireworkParticle::draw(const Renderer& renderer, const Scroll& scroll)
{
	renderer.DrawTextrue(textrue, &scroll.transformViewPosition(position),
		NULL, &GSvector2(8, 8), NULL, rotate, &GScolor(1, 1, 1, alpha));
}
const bool FireworkParticle::getIsDead()const
{
	return isDead;
}