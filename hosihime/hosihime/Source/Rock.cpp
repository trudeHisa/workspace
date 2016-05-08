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
	//castLocation(&position, &location);
	//mapUpdata(mapdata, &location, SPACE);
}
bool Rock::collision(int nextPosType)
{
	return false;
}