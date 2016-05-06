#include "Player.h"
#include "Star.h"
Player::Player(const std::string& textrue, const GSvector2* position)
	:GameObject(textrue, &Point(1, 1), PLAYER, position),star(NULL)
{

}
Player::~Player()
{
	delete star;
	star = NULL;
}
void Player::updata(MapData* mapdata)
{
	if (star != NULL)
	{
		if (star->getIsDead())
		{
			velocity = GSvector2(0,0);
			star = NULL;
		}
	}
	if (!isNextMove(mapdata))
	{
		return;
	}
	Point oldLocation = location;//位置フレーム前のlocation
	nextVelocity(&velocity);
	position += velocity;
	castLocation(&position, &location);
	mapUpdata(mapdata, &oldLocation, SPACE);
}
void Player::initialize()
{
	isDead = false;
	castLocation(&position, &location);
}
void Player::nextVelocity(GSvector2* _velocity)
{
	if (star != NULL)
	{		
		star->playerPickUp(&velocity);
		return;
	}
	_velocity->x=1;
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
