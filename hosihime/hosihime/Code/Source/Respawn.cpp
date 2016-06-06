#include "Respawn.h"
Respawn::Respawn(const std::string& textrue, const GSvector2& position, const MyRectangle& rect)
	:GameObject(textrue,position,rect, RESPAWN)
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
void Respawn::setRespawn(float* posx)
{
	*posx= position.x;
}
GameObject* Respawn::clone(const GSvector2& position)
{
	return new Respawn(textrue, position, MyRectangle(GSvector2(0, 0), rect.getSize()));
}