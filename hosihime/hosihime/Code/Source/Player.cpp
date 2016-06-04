#include "Player.h"
#include "Device.h"
#include "Star.h"
#include "Calculate.h"
#include "Respawn.h"
#define GRAVITY 10
#define JUMPMAXPOW -20
#define JUMPSPEED 0.1

enum SPEED
{
	GROUND = 6, NONGROUND = 3
};

Player::Player(const std::string& textrue, const MyRectangle& rect, Scroll* scroll, Device& device)
	:GameObject(textrue, rect, PLAYER),
	scroll(scroll), isJump(false),
	jumpPower(0),
	speed(3),
	respawnPos(rect.getPosition()),
	scrollOffset(-rect.getPosition()),
	device(device)
{
}
Player::~Player()
{
	scroll = NULL;
}
void Player::initialize()
{
	GameObject::initialize();
	jumpEnd();
	speed = SPEED::GROUND;
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
	scroll->moving(rect.getPosition(), scrollOffset);
	rect.translate(velocity*gsFrameTimerGetTime());
}
//ˆÚ“®
void Player::fallHorizontal()
{
	//speed = SPEED::NONGROUND;
	Calculate<float> calc;
	velocity.x = calc.clamp(velocity.x, -SPEED::NONGROUND, SPEED::NONGROUND);
	velocity.x = LERP(gsFrameTimerGetTime()*0.01f, velocity.x, 0);
}
void Player::gravity()
{
	if (isGround)
	{
		//speed = SPEED::GROUND;
		velocity.y = 0;
		return;
	}
	fallHorizontal();
	velocity.y = GRAVITY;
}
void Player::moving()
{
	gravity();
	jumpStart();
	moveHorizontal();
	jump();
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
	jumpPower =JUMPMAXPOW;
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
	if (!isGround && !isJump)
	{
		return;
	}
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
		//device.getSound().PlaySE("Landing.wav");		
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
	Star* s = (Star*)obj;
	s->ride(&rect);
	s->pickUp(&velocity);
	jumpEnd();
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