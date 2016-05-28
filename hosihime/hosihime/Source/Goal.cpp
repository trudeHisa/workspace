#include "Goal.h"
Goal::Goal(const std::string& textrue, const GSvector2& position)
	:GameObject(textrue, MyRectangle(position, position + GSvector2(64 * 5, 64 * 3)), GOAL)
{
}

Goal::~Goal()
{}

void Goal::updata()
{}

void Goal::collision(const GameObject* obj)
{}
