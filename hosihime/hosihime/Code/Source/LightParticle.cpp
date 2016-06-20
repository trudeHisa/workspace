#include "LightParticle.h"

LightParticle::LightParticle(const std::string& textrue,
	float angle/*deg*/, float speed, const GSvector2& position)
	: textrue(textrue), position(position), GRAVITY(0.1f),
	rotate(0), velocity(0, 0), isDead(false), alpha(1.0f)
{
	Calculate<float> calc;
	angle = calc.degTorad(angle);
	velocity.x = -std::cos(rand());
	//velocity.x = speed;
	velocity.y = -std::sin(rand());
	//velocity.y = speed;
	velocity *= speed;
}

LightParticle::~LightParticle()
{

}

void LightParticle::initialize()
{
	isDead = false;
	alpha = 1.0f;
}

void LightParticle::update()
{
	//動き
	rotate += gsFrameTimerGetTime()*velocity.x*8.0f;
	position += velocity*gsFrameTimerGetTime()*0.25f;
	//velocity.y += GRAVITY;
	alpha -= gsFrameTimerGetTime()*0.014f;
	isDead = alpha <= 0;
}

void LightParticle::draw(const Renderer& renderer, const Scroll& scroll)
{
	//ポジションを星の生成位置
	renderer.DrawTextrue(textrue, &scroll.transformViewPosition(position), NULL, &GSvector2(4, 4), NULL, alpha * 180, &GScolor(1, 1, 1, alpha));
}

const bool LightParticle::getIsDead()const
{
	return isDead;
}