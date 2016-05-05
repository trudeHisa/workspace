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
		mapdataAssignment(mapdata,&location,SPACE);
		isDead = true;
		return;
	}
	Point oldLocation = location;//位置フレーム前のlocation
	nextPosition(&position);
	castLocation(&position,&location);
	mapUpdata(mapdata, &oldLocation, SPACE);
}
void Star::draw(Renderer& renderer)
{
	GSvector2 pos = position - GSvector2(BLOCKSIZE*2, BLOCKSIZE);
	renderer.DrawTextrue(textrue, &pos);
}
void Star::nextPosition(GSvector2* pos)
{
	pos->x++;
	pos->y++;
}
bool Star::nextAction(int nextPosType)
{
	return nextPosType == SPACE || nextPosType == PLAYER;
}
void Star::playerPickUp(GSvector2* pos)
{
	pos->x=position.x;
	pos->y = position.y;
}