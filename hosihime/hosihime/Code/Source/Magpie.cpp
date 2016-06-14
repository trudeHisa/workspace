#include "Magpie.h"

#include "Calculate.h"
Magpie::Magpie(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect, IMediator* objMediator)
	:GameObject(textrue, position, viewSize, rect, MAGPIE),
	objMediator(objMediator), state(STANDBY), timer(1, 1),
	angle(0)
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
}

void Magpie::updata()
{
	GSvector2 point(0, 0);
	Calculate<float> calc;
	float alpha;
	switch (state)
	{
	case Magpie::STANDBY:
		angle+=0.1f;
		calc.wrap(angle,0,360);
		position.y += std::sin(angle) *5;
		break;
	case Magpie::TAKEIN:
		timer.update();
		if (!timer.isEnd())
		{
			return;
		}
		point= objMediator->get(MAGPIE_ENDSPOT)->getPosition();
		alpha = gsFrameTimerGetTime()*30 / point.length();
		position = position.lerp(point,alpha );
		if (position.distance(point) < 1)
		{
			state = SENDON;
		}
		break;
	case Magpie::SENDON:
		position += GSvector2(1, 1);
		break;
	default:
		break;
	}
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
	}
}

void Magpie::ride(GSvector2* position, const GSvector2* size)const
{
	if (state != TAKEIN)
	{
		return;
	}
	GSvector2 pos(this->position);
	pos.y -= size->y;
	*position = pos;
}

GameObject* Magpie::clone(const GSvector2& position)
{
	return new Magpie(textrue, position, viewSize, rect,objMediator);
}
