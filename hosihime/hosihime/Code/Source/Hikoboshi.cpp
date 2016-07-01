#include "Hikoboshi.h"

Hikoboshi::Hikoboshi(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect)
	:GameObject(textrue, position, viewSize, rect, GAMEOBJ_TYPE::HIKOBOSHI)
{
}

Hikoboshi::~Hikoboshi()
{
}

void Hikoboshi::updata()
{

}

void Hikoboshi::collision(const GameObject* obj)
{
	if (obj->getType() == GAMEOBJ_TYPE::PLAYER)
	{
		isDead = true;
	}
}

GameObject* Hikoboshi::clone(const GSvector2& position)
{
	return new Hikoboshi(textrue, position, viewSize, rect);
}