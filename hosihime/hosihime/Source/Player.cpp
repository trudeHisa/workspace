#include "Player.h"
#include "Star.h"

Player::Player(const std::string& textrue, const GSvector2* velocityition, Scroll* scroll)
	:GameObject(textrue, &Point(1, 1), PLAYER, velocityition), star(NULL), scroll(scroll)
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
	moving();
	GSvector2 nextVel(0, 0);
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
bool Player::collision(int nextvelocityType)
{
	return nextvelocityType != ROCK;
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

void Player::moving()
{
	if (jflag == true){
		y_temp = velocity.y;
		velocity.y = (velocity.y - y_prev) + 1;
		y_prev = y_temp;
		if (position.y == 600)
			jflag = false;
	}
	if (GetAsyncKeyState(VK_UP) && jflag == false)
	{
		jflag = true;
		y_prev = velocity.y;
		velocity.y = velocity.y - 20;
	}
}
