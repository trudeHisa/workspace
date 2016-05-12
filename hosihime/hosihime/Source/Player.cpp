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
	GSvector2 nextVel(0, 0);
	if (star != NULL)
	{
		star->playerPickUp(&nextVel);
	}
	if (GetAsyncKeyState(VK_UP) && jflag == false)
	{
		jflag = true;
		y_prev = position.y;
		nextVel.y = -20;
	}
	if (jflag == true){
		y_temp = position.y;
		nextVel.y = (position.y - y_prev) + 5;
		y_prev = y_temp;

	}
	if (!isNextMove(mapdata, &nextVel))
	{
		return;
	}
	if (jflag == true){
		y_temp = position.y;
		velocity.y = (position.y - y_prev) + 5;
		y_prev = y_temp;

	}
	if (GetAsyncKeyState(VK_UP)&&jflag == true)
	{
		velocity.y = -20;
	}

	if (star != NULL)
	{
		star->playerPickUp(&velocity);
	}
	scroll->moving(velocity.x);
	move(mapdata);
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
