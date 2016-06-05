#include "ImMovable.h"

ImMovable::ImMovable(const std::string& textrue, const MyRectangle& rect, GAMEOBJ_TYPE type)
	:GameObject(textrue,rect, type)
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
	return new ImMovable(textrue, MyRectangle(position, rect.getSize()),type);
}