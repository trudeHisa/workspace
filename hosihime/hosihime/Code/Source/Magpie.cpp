#include "Magpie.h"

#include "Calculate.h"
Magpie::Magpie(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect, IMediator* objMediator)
	:GameObject(textrue, position, viewSize, rect, MAGPIE),
	objMediator(objMediator), state(STANDBY), timer(1, 1),
	angle(0), speed(5)
{
}

Magpie::~Magpie()
{
}

void Magpie::initialize()
{
	GameObject::initialize();
	state=STANDBY;
	angle = 0;
	speed = 5;
}

void Magpie::updata()
{
	Calculate<float> calc;	
	switch (state)
	{
	case Magpie::STANDBY:
		angle += -0.07f;
		angle = calc.wrap(angle, 0, 360);
		velocity.y = std::sin(angle)*1.5f*gsFrameTimerGetTime();
		break;
	case Magpie::TAKEIN:
		timer.update();
		if (!timer.isEnd())
		{
			return;
		}
		if (position.distance(targetPoint) <=velocity.length()*speed)
		{
			state = SENDON;
			targetPoint = targetPoint + GSvector2(1500,-800);
			float alpha = gsFrameTimerGetTime() * 10 / targetPoint.length();
			velocity = position.lerp(targetPoint, alpha) - position;
			velocity.normalize();
		}
		break;
	case Magpie::SENDON:
		speed = 8;
		break;
	default:
		break;
	}
	position += velocity*gsFrameTimerGetTime()*speed;
}
void Magpie::collision(const GameObject* obj)
{
	if (obj->getType() != PLAYER)
	{
		return;
	}
	if (state == STANDBY)
	{
		state = TAKEIN;
		targetPoint = objMediator->get(MAGPIE_ENDSPOT)->getPosition();
		targetPoint.y -= viewSize.y;
		float alpha= gsFrameTimerGetTime() * 30 / targetPoint.length();
		velocity = position.lerp(targetPoint, alpha) - position;
		velocity.normalize();
	}
}
GameObject* Magpie::clone(const GSvector2& position)
{
	return new Magpie(textrue, position, viewSize, rect,objMediator);
}
const bool Magpie::isRide()const
{
	return state == TAKEIN;
}