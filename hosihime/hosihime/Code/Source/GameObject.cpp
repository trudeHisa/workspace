/*
GameObject.cpp
*/
#include "GameObject.h"
GameObject::GameObject(
	const std::string& textrue,
	const GSvector2& position,
	const GSvector2& viewSize,
	const MyRectangle& rect,
	const GAMEOBJ_TYPE type)
	:textrue(textrue),position(position),
	viewSize(viewSize),rect(rect), type(type)
{
}
GameObject::~GameObject()
{
}
void GameObject::draw(const Renderer& renderer, const Scroll& scroll)
{
	GSvector2 pos = position;
	pos-= scroll.getMovingAmount();
	if (!scroll.isInsideWindow(pos, viewSize))
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
	MyRectangle myrect(position+rect.getPosition(),rect.getSize());
	MyRectangle otrect(obj->position + obj->rect.getPosition(), obj->rect.getSize());
	return myrect.intersects(&otrect);
}