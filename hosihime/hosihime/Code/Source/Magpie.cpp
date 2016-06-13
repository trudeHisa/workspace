#include "Magpie.h"


Magpie::Magpie(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect, IMediator* objMediator)
	:GameObject(textrue, position, viewSize, rect, MAGPIE),
	objMediator(objMediator),
	isMove(false)
{
}

Magpie::~Magpie()
{
}

void Magpie::initialize()
{
	GameObject::initialize();
	isMove = false;
}

void Magpie::updata()
{
	GSvector2 point(0, 0);
	if (!isMove)
	{
		return;
	}
	position += velocity;
	if (position.distance(point) > 0.5f)
	{
		return;
	}
	isMove = false;
}
void Magpie::collision(const GameObject* obj)
{
	if (obj->getType() != PLAYER)
	{
		return;
	}
	isMove = true;
}

void Magpie::ride(GSvector2* position, const GSvector2* size)const
{
	if (!isMove)
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
