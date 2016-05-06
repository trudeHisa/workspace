#include "Player.h"
#include "Star.h"
Player::Player(const std::string& textrue, const GSvector2* position,Scroll* scroll)
	:GameObject(textrue, &Point(1, 1), PLAYER, position), star(NULL), scroll(scroll)
{

}
Player::~Player()
{
	delete star;
	star = NULL;
	delete scroll;
	scroll = NULL;
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
	scroll->moving(velocity.x);
	castLocation(&position, &location);
	mapUpdata(mapdata, &oldLocation, SPACE);
}
void Player::nextVelocity(GSvector2* _velocity)
{
	if (star != NULL)
	{		
		star->playerPickUp(&velocity);
	}
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
