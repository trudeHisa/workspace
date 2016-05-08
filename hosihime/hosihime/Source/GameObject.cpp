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
void GameObject::draw(Renderer& renderer, const Scroll* scroll)
{
	GSvector2 pos = position - GSvector2(BLOCKSIZE, BLOCKSIZE);
	if (!scroll->isInsideWindow(pos.x,size.x*BLOCKSIZE))
	{
		return;
	}	
	pos.x -= scroll->getMovingAmount();
	renderer.DrawTextrue(textrue, &pos);
}
void GameObject::initialize()
{
	velocity = GSvector2(0, 0);
	castLocation(&position,&location);
	isDead = false;
}
void GameObject::finish(MapData* mapdata)
{
	mapdataAssignment(mapdata, &location, SPACE);
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
	Point sp(0, 0);
	for (sp.y = 0; sp.y < size.y; sp.y++)
	{
		for (sp.x = 0; sp.x < size.x; sp.x++)
		{
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
void GameObject::move(MapData* mapdata,GAMEOBJ_TYPE oldPostype)
{
	Point oldLocation = location;//位置フレーム前のlocation
	position += velocity;	
	castLocation(&position, &location);
	mapUpdata(mapdata, &oldLocation, oldPostype);
}
const bool GameObject::isCollision(const MapData* mapdata, const Point* nextLocation)
{
	if (*nextLocation == location)
	{
		return true;
	}
	Point _size(0, 0);
	for (_size.y = 0; _size.y < size.y; _size.y++)
	{
		for (_size.x = 0; _size.x < size.x; _size.x++)
		{
			Point point = (*nextLocation) + _size;
			if (!collision((*mapdata)(point.y, point.x)))
			{
				return false;
			}			
			if (!isInSideMap(mapdata, &point))
			{
				isDead = true;
				return false;
			}
		}
	}
	return true;
}
const bool GameObject::isNextMove(const MapData* mapdata,const GSvector2* nextVelcity)
{
	GSvector2 npos = position + *nextVelcity;
	GSvector2 nposs = position + *nextVelcity + GSvector2(size.x*BLOCKSIZE, size.y*BLOCKSIZE);

	Point nextLoc;
	Point nextLocs;
	castLocation(&npos, &nextLoc);
	castLocation(&nposs, &nextLocs);

	if (!isCollision(mapdata, &nextLoc) || !isCollision(mapdata, &nextLocs))
	{
		return false;
	}
	return true;
}
