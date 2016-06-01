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
	, respawnPos(rect.getPosition())
{
}

Player::~Player()
{
	delete scroll;
	scroll = NULL;
}
void Player::initialize()
{
	speed = SPEED::GROUND;
	GameObject::initialize();
	jumpTimer.initialize();
	isJump = false;
}
void Player::updata()
{
	moving();
	if (respawn())
	{
		return;
	}
	//scroll->moving(rect.getPosition()-GSvector2(100,0));
	//
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
	if (!isGround)
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
bool Player::respawn()
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
	collisionStar(obj);
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
		return;
	}
	isGround = false;
}
void Player::collisionStar(const GameObject* obj)
{
	if (!obj->isSameType(STAR))
	{
		return;
	}
	Star* s = (Star*)&obj;
	s->ride(&rect);
	s->pickUp(&velocity);
	scroll->start();
}
void Player::collisionRespawn(const GameObject* obj)
{
	if (!obj->isSameType(RESPAWN))
	{
		return;
	}
	Respawn* respawn = (Respawn*)obj;
	respawn->setRespawn(&respawnPos);
}