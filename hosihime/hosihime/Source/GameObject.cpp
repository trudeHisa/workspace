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
bool GameObject::forDrawPosition(GSvector2* _position, const Scroll* scroll)
{
	*_position=position-GSvector2(BLOCKSIZE, BLOCKSIZE);
	if (!scroll->isInsideWindow(_position->x, size.x*BLOCKSIZE))
	{
		return false;
	}
	_position->x -= scroll->getMovingAmount();
	return true;
}
void GameObject::draw(Renderer& renderer, const Scroll* scroll)
{
	GSvector2 pos;
	if (!forDrawPosition(&pos,scroll))
	{
		return;
	}
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
void GameObject::mapUpdata(MapData* mapdata, const Point* oldLocation)
{
	mapdataAssignment(mapdata, oldLocation, SPACE);
	mapdataAssignment(mapdata, &location, type);	
}
void GameObject::move(MapData* mapdata)
{
	Point oldLocation = location;//位置フレーム前のlocation
	position += velocity;
	castLocation(&position, &location);
	mapUpdata(mapdata, &oldLocation);
}
const bool GameObject::isCollision(const MapData* mapdata, const Point* nextLocation)
{
	if (*nextLocation == location)
	{
		return true;
	}
	if (!mapdata->isInArray(nextLocation->y,nextLocation->x))
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
