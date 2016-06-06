#include "ImMovable.h"

ImMovable::ImMovable(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize,const MyRectangle& rect, GAMEOBJ_TYPE type)
	:GameObject(textrue,position,viewSize,rect, type)
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
	return new ImMovable(textrue,position,viewSize, rect,type);
}