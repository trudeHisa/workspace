#include "Rock.h"
Rock::Rock(const std::string& textrue,const MyRectangle& rect)
	:GameObject(textrue,rect, ROCK)
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
	vel->x =rect.getPosition().x-pos.x;
	vel->y = 50- pos.y;
}