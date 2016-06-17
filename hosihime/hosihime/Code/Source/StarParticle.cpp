#include "StarParticle.h"


StarParticle::StarParticle(
	const std::string& textrue, const GSvector2& center,
	float speed, float angle, float alphaSpeed)
	:textrue(textrue), center(center), speed(speed), angle(angle),
	position(center), alpha(1), isDead(false), alphaSpeed(alphaSpeed),
	GRAVITY(0.1), rotate(rotate), veloctiy(veloctiy)
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
	GSvector2 v;
	gsVector2FromDirection(&v,angle);
	position += v*speed*gsFrameTimerGetTime();
	

	isDead = alpha <= 0;

	alpha -= alphaSpeed*gsFrameTimerGetTime();
}
void StarParticle::draw(const Renderer& renderer)
{
	renderer.DrawTextrue(textrue, &position, NULL, &GSvector2(4, 4), NULL, alpha * 180, &GScolor(1, 1, 1, alpha));
}
const bool StarParticle::getIsDead()const
{
	return isDead;
}