#include "Planet.h"
Planet::Planet(const std::string& textrue, const GSvector2& position)
	:GameObject(textrue, MyRectangle(position, position + GSvector2(64, 64)), PLANET)
{
}

Planet::~Planet()
{
}
void Planet::updata()
{
}
void Planet::collision(const GameObject* obj)
{
}