/*
GameObject.cpp
*/
#include "GamaObject.h"
GameObject::GameObject(const std::string& textrue, const Point* size,
	const GAMEOBJ_TYPE type, const GSvector2* position)
	:textrue(textrue), size(*size), type(type), position(*position)
{

}
GameObject::~GameObject()
{
}
void GameObject::draw(Renderer& renderer)
{
	renderer.DrawTextrue(textrue, &position);
}
void GameObject::initialize()
{
	isDead = false;
}
void GameObject::finish()
{

}
const bool GameObject::getIsDead()const
{
	return isDead;
}
const Point GameObject::getSize()const
{
	return size;
}
void GameObject::castLocation(const GSvector2* pos, Point* loc)
{
	loc->x = pos->x / BLOCKSIZE;
	loc->y = pos->y / BLOCKSIZE;
}
void GameObject::mapUpdata(MapData* mapdata, const Point* oldLocation, GAMEOBJ_TYPE oldPostype)
{
	(*mapdata)(location.y, location.x) = type;
	if (location == (*oldLocation))
	{
		return;
	}
	if ((*mapdata)(oldLocation->y, oldLocation->x) != type)
	{	
		return;
	}
	(*mapdata)(oldLocation->y, oldLocation->x) = oldPostype;
}
const bool GameObject::isNextMove(const MapData* mapdata)
{
	GSvector2 nextPos = position;
	nextPosition(&nextPos);
	Point nextLoc;
	castLocation(&nextPos, &nextLoc);
	if (nextLoc == location)
	{
		return true;
	}
	if ((*mapdata)(nextLoc.y, nextLoc.x) != SPACE)
	{
		return false;
	}
	if (mapdata->getSize1() <= nextLoc.x)
	{
		return false;
	}
	if (mapdata->getSize0() <= nextLoc.y)
	{
		return false;
	}
	return true;
}
