#include "Rock.h"
Rock::Rock(const std::string& textrue, const GSvector2& position)
	:GameObject(textrue, MyRectangle(position, position+GSvector2(64*4, 64*2)), ROCK)
{
}

Rock::~Rock()
{
}
void Rock::updata()
{
}
void Rock::collision(const GameObject* obj)
{

}
void Rock::respawn(const GSvector2& pos,GSvector2* vel)
{
	vel->x =rect.getMin().x-pos.x;
	vel->y = 50- pos.y;
}