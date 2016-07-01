#include "Respawn.h"
Respawn::Respawn(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize,const MyRectangle& rect)
	:GameObject(textrue, position, viewSize, rect, GAMEOBJ_TYPE::RESPAWN)
{
}
Respawn::~Respawn()
{
}
void Respawn::updata()
{
}
void Respawn::collision(const GameObject* obj)
{
}
void Respawn::setRespawn(GSvector2* pos)const
{
	pos->x = position.x;
	pos->y = position.y - 5 * 64;
}
GameObject* Respawn::clone(const GSvector2& position)
{
	return new Respawn(textrue, position,viewSize, rect);
}