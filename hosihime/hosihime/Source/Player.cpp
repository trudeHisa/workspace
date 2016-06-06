#include "Player.h"
#include "Device.h"
#include "Star.h"
#include "Calculate.h"
#include "Respawn.h"
#define GRAVITY 10
#define JUMPMAXPOW -20
#define JUMPSPEED 0.1

Player::Player(const std::string& textrue, const MyRectangle& rect, Scroll* scroll, Device& device)
	:GameObject(textrue, rect, PLAYER),
	scroll(scroll), isJump(false),
	jumpPower(0),
	speed(6),
	respawnPos(rect.getPosition()),
	device(device)
{
}
Player::~Player()
{
	scroll = NULL;
}
void Player::initialize()
{
	isAnyfall = false;
	isres = false;
	GameObject::initialize();
	jumpEnd();
	speed = 6;
	jumpPower = 0;
}
void Player::jumpEnd()
	{
	isJump = false;
	jumpPower = 0;
	}
void Player::updata()
	{
	moving();
	if (respawn())
	{
		return;
	}
	scroll->moving(rect.getPosition(), -respawnPos);
	rect.translate(velocity*gsFrameTimerGetTime());
	}
void Player::gravity()
{
	if (isGround)
	{
		velocity.y = 0;
		return;
	}
	velocity.y = GRAVITY;
}
void Player::moving()
{
	Anyfall();
	gravity();
	jumpStart();
	rideUpDown();
	moveHorizontal();
	jump();
}
void Player::rideUpDown()
{
	if (!isRide)
	{
		return;
	}
	if (device.getInput().getDownTrigger())
	{
		velocity = GSvector2(0, 0);
		rect.translate(GSvector2(0, rect.getHeight() + 64));
	}
	if (device.getInput().getUpTrigger())
	{
		isJump = true;
		jumpPower = JUMPMAXPOW;
	}
}
void Player::jumpStart()
{
	if (!isGround&&!isRide)
	{
		return;
	}
	if (isJump)
	{
		return;
	}
	if (!device.getInput().getActionTrigger())
	{
		return;
	}
	isJump = true;
	jumpPower = JUMPMAXPOW;
}
void Player::jump()
{
	if (!isJump)
{
		return;
	}
	velocity.y = jumpPower;
	jumpPower += GRAVITY*gsFrameTimerGetTime()*JUMPSPEED;
	}
void Player::moveHorizontal()
{
	//if (!isGround && !isJump)
	//{
	//	return;
	//}
	velocity.x = device.getInput().getVelocity().x * speed;
}
//
const  bool Player::respawn()
{
	if (rect.getPosition().y <= WINDOW_HEIGHT + rect.getHeight())
	{
		return false;
	}
	rect.resetPosition(respawnPos);
	velocity = GSvector2(0, 0);
	jumpPower = 0;
	return true;
}
//Õ“Ë
void Player::collision(const GameObject* obj)
{
	isRide = collisionStar(obj);
	collisionRespawn(obj);
	collisionGround(obj);
	if (obj->isSameType(GOAL)) isDead = true;
}
void Player::collisionGround(const GameObject* obj)
{
	if (obj->isSameType(RESPAWN) ||
		obj->isSameType(START) ||
		obj->isSameType(GOAL))
{
		isGround = true;
		jumpEnd();
		scroll->stop();
		/*	const Sound& sound = device.getSound();
			if (!sound.IsPlaySE("Landing.wav")&&velocity.x!=0)
			{
			sound.PlaySE("Landing.wav");
			}	*/
		return;
	}
	scroll->start();
	isGround = false;
}
const bool Player::collisionStar(const GameObject* obj)
{
	if (!obj->isSameType(STAR))
	{
		return false;
	}
	if (gsGetKeyTrigger(GKEY_DOWN))
	{
		isAnyfall = true;
		rect.translate(GSvector2(0,58));
		return false;
	}
	Star* s = (Star*)obj;
	s->ride(&rect);
	s->pickUp(&velocity);
	jumpEnd();
	isAnyfall = false;
	return true;
}
void Player::collisionRespawn(const GameObject* obj)
{
	if (!obj->isSameType(RESPAWN))
	{
		return;
	}
	Respawn* respawn = (Respawn*)obj;
	respawn->setRespawn(&respawnPos.x);
}
GameObject* Player::clone(const GSvector2& position)
{
	return new Player(textrue, MyRectangle(position, rect.getSize()),scroll,device);
}