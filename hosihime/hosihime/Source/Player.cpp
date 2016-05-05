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

void Player::nextPosition(GSvector2* pos)
{
	if (star)
	{
		star->playerPickUp(pos);
		return;
	}
	pos->x++;
}
bool Player::nextAction(int nextPosType)
{
	return true;
}
bool Player::setStar(GameObject* _star)
{
	if (!_star->isSameLocation(location))
	{
		return false;
	}
	star =(Star*)_star;
	return true;
}
