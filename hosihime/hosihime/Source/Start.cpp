#include "Start.h"
Start::Start(const std::string& textrue, const GSvector2& position)
	:GameObject(textrue, MyRectangle(position, position + GSvector2(64*5, 64*3)), START)
{
}

Start::~Start()
{}

void Start::updata()
{}

void Start::collision(const GameObject* obj)
{}
