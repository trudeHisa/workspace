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
const bool GameObject::isSameLocation(const Point& _location)const
{
	return _location == location;
}
const bool GameObject::isSameType(GAMEOBJ_TYPE _type)const
{
	return type == _type;
}
void GameObject::castLocation(const GSvector2* pos, Point* loc)
{
	loc->x = pos->x / BLOCKSIZE;
	loc->y = pos->y / BLOCKSIZE;
}
void GameObject::mapdataAssignment(MapData* mapdata, const Point* point, GAMEOBJ_TYPE _type)
{
	for (int sy = 0; sy < size.y; sy++)
	{
		for (int sx = 0; sx < size.x; sx++)
		{
			(*mapdata)(point->y + sy, point->x + sx) = _type;
		}
	}
}
void GameObject::mapUpdata(MapData* mapdata, const Point* oldLocation, GAMEOBJ_TYPE oldPostype)
{
	mapdataAssignment(mapdata,&location,type);
	for (int sy = 0; sy < size.y; sy++)
	{
		for (int sx = 0; sx < size.x; sx++)
		{
			Point sp(sx,sy);
			Point spl = location + sp;
			Point spol = (*oldLocation) + sp;
			if (spl== spol)
			{
				return;
			}
			if ((*mapdata)(oldLocation->y, oldLocation->x) != type)
			{
				return;
			}
		}
	}
	mapdataAssignment(mapdata,oldLocation, oldPostype);
}
const bool GameObject::isInSideMap(const MapData* mapdata, const Point* point)const
{
	if (mapdata->getSize1() <= point->x)
	{
		return false;
	}
	if (mapdata->getSize0() <= point->y)
	{
		return false;
	}
	return true;
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
	for (int sy = 0; sy < size.y; sy++)
	{
		for (int sx = 0; sx < size.x; sx++)
		{
			if (!nextAction((*mapdata)(nextLoc.y + sy, nextLoc.x + sx)))
			{
				return false;
			}
			Point point = nextLoc + Point(sx,sy);
			if (!isInSideMap(mapdata, &point))
			{
				return false;
			}
		}
	}
	return true;
}
