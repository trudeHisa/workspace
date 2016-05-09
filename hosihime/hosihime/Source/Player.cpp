#include "Player.h"
#include "Star.h"

bool jflag = false;
int y_temp = 0;
int y_prev = 0;

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
	move();
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

void Player::move()
{
	if (jflag == true){
		y_temp = pos.y;
		pos.y += (pos.y - y_prev) + 1;
		y_prev = y_temp;
		if (pos.y == 600)
			jflag = false;
	}
	if (GetAsyncKeyState(VK_UP) && jflag == false)
	{
		jflag = true;
		y_prev = pos.y;
		pos.y = pos.y - 20;
	}
}
