/*
Player�N���X
5/13�@�v�H�F���R�������\�b�h�ǉ��AUpdete�ύX

*/




#include "Player.h"
#include "Star.h"
#include "Rock.h"


Player::Player(const std::string& textrue, const GSvector2& position, Scroll* scroll)
	:GameObject(textrue, MyRectangle(position, position + GSvector2(64, 64)), PLAYER),
	star(NULL), scroll(scroll), rock(NULL)
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
void Player::updata()
{
	FreeFall();
	if (star != NULL)
	{
		if (star->getIsDead())
		{
			star = NULL;
			velocity = GSvector2(0, 1);
			return;
		}
		star->pickUp(&velocity);
	}	
	if (gsGetKeyTrigger(GKEY_SPACE))
	{
		if (rock != NULL)
		{
			rock->respawn(rect.getMin(), &velocity);
		}
	}
	scroll->moving(velocity.x);
	rect = rect.translate(velocity);
}
//���R��������
void Player::FreeFall()
{
	if (isGround)
	{
		velocity = GSvector2(0,0);
	}
	else
	{
		velocity =GSvector2(0,3);
	}
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
void Player::collision(const GameObject* obj)
{
	if (obj->isSameType(STAR))
	{
		if (star == NULL)
		{
			star = (Star*)obj;
		}
	}
	if (obj->isSameType(ROCK))
	{
		if (rock == NULL)
		{
			rock = (Rock*)obj;
		}
		isGround = true;
	}
	else
	{
		isGround = false;
	}
}
bool Player::setStar(GameObject* _star)
{
	return false;
}
