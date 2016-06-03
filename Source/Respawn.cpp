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
void Respawn::setRespawn(float* posx)
{
	*posx= rect.getPosition().x;
}