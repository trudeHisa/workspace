#include "LightParticle.h"

LightParticle::LightParticle(
	const std::string& textrue, const GSvector2& center,
	float speed, float angle, float alphaSpeed)
	:textrue(textrue), center(center), speed(speed), angle(angle),
	position(center), alpha(1), isDead(false), alphaSpeed(alphaSpeed)
{
	initialize();
}

LightParticle::~LightParticle()
{

}

void LightParticle::initialize()
{
	position = center;
	isDead = false;
}

void LightParticle::update()
{
	//“®‚«
	GSvector2 v;
	gsVector2FromDirection(&v, angle);
	position += v*speed*gsFrameTimerGetTime();

	isDead = alpha <= 0;

	alpha -= alphaSpeed*gsFrameTimerGetTime();
}

void LightParticle::draw(const Renderer& renderer)
{
	renderer.DrawTextrue(textrue, &position, NULL, &GSvector2(4, 4), NULL, alpha * 180, &GScolor(1, 1, 1, alpha));
}

const bool LightParticle::getIsDead()const
{
	return isDead;
}