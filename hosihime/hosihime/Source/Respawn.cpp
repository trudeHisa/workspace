#include "Respawn.h"
Respawn::Respawn(const std::string& textrue, const MyRectangle& rect)
	:GameObject(textrue, rect, RESPAWN)
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
void Respawn::setRespawn(GSvector2* pos)
{
	pos->x = rect.getPosition().x;
	pos->y = rect.getPosition().y;
}