#include "Rock.h"
Rock::Rock(const std::string& textrue, const GSvector2* position)
	:GameObject(textrue, &Point(2,1), ROCK, position)
{
}

Rock::~Rock()
{
}
void Rock::updata(MapData* mapdata)
{
	castLocation(&position, &location);
	mapUpdata(mapdata, &location, SPACE);
}
void Rock::nextVelocity(GSvector2* _velocity)
{
}
bool Rock::nextAction(int nextPosType)
{
	return false;
}