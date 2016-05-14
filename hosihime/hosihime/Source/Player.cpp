#include "Player.h"
#include "Star.h"
#include "Rock.h"
Player::Player(const std::string& textrue, const GSvector2& position, Scroll* scroll)
	:GameObject(textrue, MyRectangle(position, position + GSvector2(64, 64)), PLAYER),
	star(NULL), scroll(scroll), rock(NULL)
{
	jflag = false;
}

Player::~Player()
{
	delete rock;
	rock = NULL;
	delete star;
	star = NULL;
	delete scroll;
	scroll = NULL;
}

void Player::moving()
{
	if (jump() == true)
	{
		return;
	}
	if (!isGround)
	{
		velocity = GSvector2(0, 3);
		if (star != NULL)
		{
			star->pickUp(&velocity);
		}
		starDestroy();
		jumpstart();
		return;
	}
	velocity = GSvector2(0, 0);
	jumpstart();
	moveLR();
}
void Player::updata()
{
	moving();
	respawn();
	if (!isGround)
	{
		scroll->moving(velocity.x);
	}
	//*gsFrameTimerGetTime()
	rect = rect.translate(velocity);
}
void Player::respawn()
{
	if (WINDOW_HEIGHT + rect.getHeight() >= rect.getMin().y)
	{
		return;
	}
	jflag = false;
	if (rock != NULL)
	{
		rock->respawn(rect.getMin(), &velocity);
		return;
	}
	velocity.x = 574 - rect.getMin().x;
	velocity.y = 50 - rect.getMin().y;
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
	velocity = GSvector2(0, 1);
	star = NULL;
}void Player::jumpstart()
{
	if (!gsGetKeyTrigger(GKEY_SPACE))
	{
		return;
	}
	jflag = true;
	y_prev = rect.getMin().y;
	velocity = GSvector2(0, -25);
	star = NULL;
}
bool Player::jump()
{
	if (jflag == false)
	{
		return false;
	}
	if (gsGetKeyState(GKEY_RIGHT))
	{
		velocity.x = 3;
	}
	if (gsGetKeyState(GKEY_LEFT))
	{
		velocity.x = -3;
	}
	y_temp = rect.getMin().y;
	velocity.y = (rect.getMin().y - y_prev) + 1;
	y_prev = y_temp;
	return true;
}
void Player::moveLR()
{
	if (gsGetKeyState(GKEY_RIGHT))
	{
		velocity = GSvector2(3, 0);
	}
	if (gsGetKeyState(GKEY_LEFT))
	{
		velocity = GSvector2(-3, 0);
	}
}
void Player::collision(const GameObject* obj)
{
	if (obj->isSameType(STAR))
	{
		if (star == NULL)
		{
			star = (Star*)obj;
			star->ride(&rect);
		}
		else
		{
			jflag = false;
		}
	}
	if (obj->isSameType(ROCK))
	{
		if (rock == NULL)
		{
			rock = (Rock*)obj;
		}
		isGround = true;
		jflag = false;
	}
	else
	{
		isGround = false;
	}
	if (obj->isSameType(PLANET))
	{
		//isDead = true;
	}
}
//bool Player::setStar(GameObject* _star)
//{
//	return false;
//}
