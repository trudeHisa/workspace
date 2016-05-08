#include "Player.h"
#include "Star.h"

Player::Player(const std::string& textrue, const GSvector2* position, Scroll* scroll)
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
	starDestroy();

	GSvector2 nextVel= velocity;
	if (star != NULL)
	{
		star->playerPickUp(&nextVel);
	}

	if (!isNextMove(mapdata, &nextVel))
	{
		return;
	}
	
	if (star != NULL)
	{
		star->playerPickUp(&velocity);
	}
	scroll->moving(velocity.x);
	move(mapdata,SPACE);
}
void Player::nextVelocity(GSvector2* _velocity)
{

}
void Player::starDestroy()
{
	if (star == NULL)
	{
		return;
	}
	if (!star->getIsDead())
	{
		return;
	}
	velocity = GSvector2(0, 0);
	star = NULL;
}
bool Player::collision(int nextPosType)
{
	return nextPosType != ROCK;
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
