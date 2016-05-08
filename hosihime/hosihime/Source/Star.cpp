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
	GSvector2 nextVel = velocity;
	float nang = angle;

	nang += 0.03f;
	nextVel.y = sin(nang) * 4;
	nextVel.x = 2;

	if (!isNextMove(mapdata, &nextVel))
	{
		mapdataAssignment(mapdata, &location, SPACE);
		return;
	}

	angle += 0.03f;
	velocity.y = sin(angle) * 4;
	velocity.x = 2;

	move(mapdata, SPACE);
}
void Star::nextVelocity(GSvector2* _velocity, float* angle)
{
	*angle += 0.03f;
	_velocity->y = sin(*angle) * 4;
	_velocity->x = 2;
}
bool Star::collision(int nextPosType)
{
	if (nextPosType == SPACE || nextPosType == PLAYER)
	{
		return true;
	}
	isDead = true;
	return false;
}
void Star::playerPickUp(GSvector2* _velocity)
{
	_velocity->x = velocity.x;
	_velocity->y = velocity.y;
}