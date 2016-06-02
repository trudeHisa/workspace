#include "Player.h"
#include "Input.h"
#include "Star.h"
#include "Calculate.h"
#include "Respawn.h"
#define GRAVITY 10
#define JUMPSPEED 0.3

enum SPEED
{
	GROUND = 10, JUMP = 3
};

Player::Player(const std::string& textrue, const MyRectangle& rect, Scroll* scroll, const Input& input)
	:GameObject(textrue, rect, PLAYER),
	scroll(scroll), isJump(false),
	input(input), jumpTimer(40, 40), speed(3)
	, respawnPos(rect.getPosition()), scrollOffset(-rect.getPosition())
{

}
Player::~Player()
{
	delete scroll;
	scroll = NULL;
}
void Player::initialize()
{
	GameObject::initialize();
	jumpEnd();
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
void Player::gravity()
{
	if (isGround)
	{
		velocity.y = 0;
		return;
	}
	Calculate<float> calc;
	velocity.x = calc.clamp(velocity.x - 0.05f, 0, 3);
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
	if (!input.getActionTrigger())
	{
		return;
	}
	isJump = true;
	speed = SPEED::JUMP;
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
void Player::jumpEnd()
{
	isJump = false;
	speed = SPEED::GROUND;
	jumpTimer.initialize();
}
void Player::moveHorizontal()
{
	if (!isGround && !isJump)
	{
		return;
	}
	velocity.x = input.getVelocity().x * speed;
}
const  bool Player::respawn()
{
	if (rect.getPosition().y <= WINDOW_HEIGHT + rect.getHeight())
	{
		return false;
	}
	rect.resetPosition(respawnPos);
	return true;
}
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
	Star* s = (Star*)obj;
	s->ride(&rect);
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