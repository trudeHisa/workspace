#include "Start.h"
Start::Start(const std::string& textrue, const GSvector2& position)
	:GameObject(textrue, MyRectangle(position, position + GSvector2(128, 64)), START)
{
}

Start::~Start()
{}
void Start::update()
{}
void Start::collision(const GameObject* obj)
{}
void Start::respawn(const GSvector2& pos, GSvector2* vel)
{}