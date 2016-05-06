#include "Star.h"

Star::Star(const std::string& textrue, const GSvector2* position)
	:GameObject(textrue, &Point(1, 1), STAR, position)
{

}

Star::~Star()
{
}

void Star::updata(MapData* mapdata)
{
	if (!isNextMove(mapdata))
	{
		if ((*mapdata)(location.y,location.x) == type)
		{
			mapdataAssignment(mapdata, &location, SPACE);
		}
		isDead = true;
		return;
	}
	Point oldLocation = location;//位置フレーム前のlocation
	nextVelocity(&velocity);
	position += velocity;
	castLocation(&position, &location);
	mapUpdata(mapdata, &oldLocation, SPACE);
}
void Star::nextVelocity(GSvector2* _velocity)
{
	_velocity->x = 1;
	_velocity->y = 1;
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