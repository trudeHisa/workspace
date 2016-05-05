#include "Player.h"
#include "Star.h"
Player::Player(const std::string& textrue, const GSvector2* position)
	:GameObject(textrue, &Point(1, 1), PLAYER, position),
	star(0)
{

}
Player::~Player()
{
	delete star;
	star = 0;
}
void Player::updata(MapData* mapdata)
{
	if (star != 0)
	{
		if (star->getIsDead())
		{
			position.x = location.x*BLOCKSIZE;
			position.y = location.y*BLOCKSIZE;
			star = 0;
		}
	}
	if (!isNextMove(mapdata))
	{
		return;
	}
	Point oldLocation = location;//位置フレーム前のlocation
	nextPosition(&position);
	castLocation(&position, &location);
	mapUpdata(mapdata, &oldLocation, SPACE);
}
void Player::initialize()
{
	isDead = false;
	castLocation(&position, &location);
}
void Player::draw(Renderer& renderer)
{
	GSvector2 pos = position - GSvector2(BLOCKSIZE*2, BLOCKSIZE);
	renderer.DrawTextrue(textrue, &pos);
}
void Player::nextPosition(GSvector2* pos)
{
	if (star != 0)
	{		
		star->playerPickUp(&position);
		return;
	}
	pos->x++;
}
bool Player::nextAction(int nextPosType)
{
	return nextPosType!=ROCK;
}
bool Player::setStar(GameObject* _star)
{
	if (!_star->isSameLocation(location))
	{
		return false;
	}	
	star = (Star*)_star;
	return true;
}
