#include "Star.h"

Star::Star(const std::string& textrue, const GSvector2* position)
	:GameObject(textrue, &Point(1,1), STAR, position)
{
	
}

Star::~Star()
{
}

void Star::initialize()
{
	isDead = false;
	castLocation(&position, &location);
}
void Star::updata(MapData* mapdata)
{
	if (!isNextMove(mapdata))
	{
		(*mapdata)(location.y, location.x) = SPACE;
		isDead = true;
		return;
	}
	Point oldLocation = location;//�ʒu�t���[���O��location
	nextPosition(&position);
	castLocation(&position,&location);
	mapUpdata(mapdata, &oldLocation, SPACE);
}
void Star::nextPosition(GSvector2* pos)
{
	pos->x++;
}