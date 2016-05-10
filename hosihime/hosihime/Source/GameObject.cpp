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
	if (!scroll->isInsideWindow(pos.x, size.x*BLOCKSIZE))
	{
		return;
	}
	pos.x -= scroll->getMovingAmount();
	renderer.DrawTextrue(textrue, &pos);
}
void GameObject::initialize()
{
	velocity = GSvector2(0, 0);
	castLocation(&position, &location);
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
	mapdataAssignment(mapdata, oldLocation, oldPostype);
	mapdataAssignment(mapdata, &location, type);	
}
const bool GameObject::isInDataMap(const MapData* mapdata, const Point* point)const
{
	if (point->x < 0)
	{
		return false;
	}
	if (point->y < 0)
	{
		return false;
	}
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
void GameObject::move(MapData* mapdata, GAMEOBJ_TYPE oldPostype)
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
	if (!isInDataMap(mapdata, nextLocation))
	{
		isDead = true;
		return false;
	}
	if (!collision((*mapdata)(nextLocation->y, nextLocation->x)))
	{
		return false;
	}	
	return true;
}
const bool GameObject::isNextMove(const MapData* mapdata, const GSvector2* nextVelcity)
{
	//x,x+width,y,y+height
	int dirx[2] ={0, size.x};
	int diry[2] ={0, size.y};
	//(0,0)(w,0)(0,h)(w,h)
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			GSvector2 npos = position + *nextVelcity;
			npos += GSvector2(dirx[x] * BLOCKSIZE, diry[y]* BLOCKSIZE);
			Point nextLoc;
			castLocation(&npos, &nextLoc);
			if (!isCollision(mapdata, &nextLoc))
			{
				return false;
			}
		}
	}
	return true;
}
