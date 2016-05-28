#include "Player.h"
#include "Star.h"
#include "Rock.h"
Player::Player(const std::string& textrue, const MyRectangle& rect, Scroll* scroll)
	:GameObject(textrue, rect, PLAYER),
	star(NULL), scroll(scroll), rock(NULL), jflag(false)
{
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
void Player::initialize()
{	
	GameObject::initialize();
	jflag = false;
	star = NULL;
	rock = NULL;
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
	//starDestroy();
	moving();
	respawn();
	if (!isGround)
	{
		scroll->moving(velocity);
	}
	//*gsFrameTimerGetTime()
	rect.translate(velocity);
}
void Player::respawn()
{
	if (WINDOW_HEIGHT + rect.getHeight() >= rect.getPosition().y)
	{
		return;
	}
	jflag = false;
	if (rock != NULL)
	{
		rock->respawn(rect.getPosition(), &velocity);
		return;
	}
	velocity.x = 64 - rect.getPosition().x;
	velocity.y = 50 - rect.getPosition().y;
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
	y_prev = rect.getPosition().y;
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
	y_temp = rect.getPosition().y;
	velocity.y = (rect.getPosition().y - y_prev) + 1;
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
		rock = NULL;
		rock = (Rock*)obj;		
	}

	if (obj->isSameType(ROCK))
	{
		isGround = true;
		jflag = false;
	}
	else if (obj->isSameType(START))
	{
		isGround = true;
		jflag = false;
	}
	else if (obj->isSameType(GOAL))
	{
		isGround = true;
		jflag = false;
	}
	else
	{
		isGround = false;
	}

	if (obj->isSameType(GOAL))
	{
		isDead = true;
	}
}
//bool Player::setStar(GameObject* _star)
//{
//	return false;
//}
