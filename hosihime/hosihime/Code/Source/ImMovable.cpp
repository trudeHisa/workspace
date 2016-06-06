#include "ImMovable.h"

ImMovable::ImMovable(const std::string& textrue, const GSvector2& position, const MyRectangle& rect, GAMEOBJ_TYPE type)
	:GameObject(textrue,position,rect, type)
{
}
ImMovable::~ImMovable()
{
}
void ImMovable::updata()
{

}
void ImMovable::collision(const GameObject* obj)
{

}
GameObject* ImMovable::clone(const GSvector2& position)
{
	return new ImMovable(textrue,position, rect,type);
}