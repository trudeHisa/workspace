#include "Star.h"

Star::Star(const std::string& textrue, const GSvector2* position)
	:GameObject(textrue, &Point(1, 1), STAR, position)
{
	angle = 0;
}

Star::~Star()
{
}

void Star::updata(MapData* mapdata)
{
	float nang = angle;
	GSvector2 nextVel = velocity;
	nextVelocity(&nextVel,&nang);
	Point nextLoc;
	nextLocation(&nextLoc,&nextVel);
	if (!isNextMove(mapdata,&nextLoc))
	{
		if ((*mapdata)(location.y,location.x) == type)
		{
			mapdataAssignment(mapdata, &location, SPACE);
		}
		isDead = true;
		return;
	}
	nextVelocity(&velocity,&angle);
	move(mapdata, SPACE);
}
void Star::nextVelocity(GSvector2* _velocity,float* angle)
{
	*angle+=0.03f;
	_velocity->y = sin(*angle) *4;
	_velocity->x =2;
}
bool Star::nextAction(int nextPosType)
{
	return nextPosType == SPACE || nextPosType == PLAYER;
}
void Star::playerPickUp(GSvector2* _velocity)
{
	_velocity->x = velocity.x;
	_velocity->y = velocity.y;
}