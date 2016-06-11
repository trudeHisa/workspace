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
	if (!isInScreen(scroll))
	{
		return;
	}
	GSvector2 pos = position - scroll.getMovingAmount();
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
const bool GameObject::isInScreen(const Scroll& scroll)const
{
	GSvector2 viewPos = position -scroll.getMovingAmount();
	return scroll.isInsideWindow(viewPos, viewSize);
}

const GSvector2& GameObject::getViewSize()const
{
	return viewSize;
}
const bool GameObject::getIsDead()const
{
	return isDead;
}
const GAMEOBJ_TYPE GameObject::getType()const
{
	return type;
}
const GSvector2& GameObject::getPosition()const
{
	return position;
}
const MyRectangle& GameObject::getRect()const
{
	return rect;
}
const bool GameObject::isCollision(const GameObject* obj)const
{
	MyRectangle myrect(position+rect.getPosition(),rect.getSize());
	MyRectangle otrect(obj->position + obj->rect.getPosition(), obj->rect.getSize());
	return myrect.intersects(&otrect);
}
void GameObject::nonCollision()
{

}
