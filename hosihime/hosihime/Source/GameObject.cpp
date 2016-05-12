/*
GameObject.cpp
*/
#include "GamaObject.h"
GameObject::GameObject(const std::string& textrue, const MyRectangle& rect,
	const GAMEOBJ_TYPE type)
	:textrue(textrue),rect(rect), type(type)
{

}
GameObject::~GameObject()
{
}
void GameObject::draw(Renderer& renderer, const Scroll* scroll)
{
	GSvector2 pos = rect.getMin();
	pos.x -= scroll->getMovingAmount();
	if (!scroll->isInsideWindow(pos.x, rect.getWidth()))
	{
		return ;
	}
	renderer.DrawTextrue(textrue, &pos);
}
void GameObject::initialize()
{
	velocity = GSvector2(0, 0);
	isDead = false;
}
void GameObject::finish()
{
}
const bool GameObject::getIsDead()const
{
	return isDead;
}
const bool GameObject::isSameType(GAMEOBJ_TYPE _type)const
{
	return type == _type;
}
const bool GameObject::isCollision(const GameObject* obj)const
{
	return rect.intersects(obj->rect);
}