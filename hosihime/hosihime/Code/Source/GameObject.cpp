/*
GameObject.cpp
*/
#include "GameObject.h"
GameObject::GameObject(const std::string& textrue,
	const MyRectangle& rect,const GAMEOBJ_TYPE type)
	:textrue(textrue),rect(rect), type(type)
{
}
GameObject::~GameObject()
{
}
void GameObject::draw(const Renderer& renderer, const Scroll& scroll)
{
	GSvector2 pos = rect.getPosition();
	pos-= scroll.getMovingAmount();
	if (!scroll.isInsideWindow(pos, rect.getSize()))
	{
		return;
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