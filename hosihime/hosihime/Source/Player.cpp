#include "Player.h"
#include "Input.h"
#include "Star.h"
#include "Calculate.h"
#include "Respawn.h"
#define GRAVITY 8
#define JUMPSPEED 0.3

enum SPEED
{
	GROUND = 6, NONGROUND = 3
};

Player::Player(const std::string& textrue, const MyRectangle& rect, Scroll* scroll, const Input& input)
	:GameObject(textrue, rect, PLAYER),
	scroll(scroll), isJump(false),
	input(input), jumpTimer(37, 37), speed(3),
	respawnPos(rect.getPosition()),
	scrollOffset(-rect.getPosition())
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
	speed = SPEED::GROUND;
}
void Player::jumpEnd()
	{
	isJump = false;
	jumpTimer.initialize();
	}
void Player::updata()
	{
	moving();
	if (respawn())
	{
		return;
	}
	scroll->moving(rect.getPosition(),scrollOffset);
	rect.translate(velocity*gsFrameTimerGetTime());
	}
//ˆÚ“®
void Player::fallHorizontal()
	{
	//speed = SPEED::NONGROUND;
	Calculate<float> calc;
	/*velocity.x = calc.clamp(velocity.x, -SPEED::NONGROUND, SPEED::NONGROUND);
	velocity.x = LERP(gsFrameTimerGetTime()*0.01f, velocity.x, 0);*/
}
void Player::gravity()
{
	if (isGround)
	{
		isres = false;
		//speed = SPEED::GROUND;
		velocity.y = 0;
		return;
	}
	fallHorizontal();
	velocity.y = GRAVITY;
}
void Player::moving()
{
	Anyfall();
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
	if (!input.getActionTrigger())
	{
		return;
	}
	isJump = true;
}
void Player::jump()
{
	if (!isJump)
	{
		return;
	}
	velocity.y = -jumpTimer.getTime()*JUMPSPEED;
	jumpTimer.update();
	if (!jumpTimer.isEnd())
	{
		return;
	}
	jumpEnd();
}
void  Player::Anyfall()
{
	if (isAnyfall)
	{
		velocity.y = 5;
	}
}
void Player::moveHorizontal()
{
	if (isRide||isres)
	{
		return;
	}
	velocity.x = input.getVelocity().x * speed;
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
	isres = true;
	return true;
}
//Õ“Ë
void Player::collision(const GameObject* obj)
{
	isRide=collisionStar(obj);
	collisionRespawn(obj);
	collisionGround(obj);
}
void Player::collisionGround(const GameObject* obj)
{
	if (obj->isSameType(RESPAWN) ||
		obj->isSameType(START) ||
		obj->isSameType(GOAL))
{
		isGround = true;
		isJump = false;
		isAnyfall = false;
		scroll->stop();
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