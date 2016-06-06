#include "Player.h"
#include "Device.h"
#include "Star.h"
#include "Calculate.h"
#include "Respawn.h"

Player::Player(const std::string& textrue,const GSvector2& position,
	const GSvector2& viewSize,const MyRectangle& rect,
	Scroll* scroll, Device& device)
	:GameObject(textrue,position,viewSize,rect, PLAYER),
	GRAVITY(10), VERTICAL(5),
	JUMPMAXPOW(-15),JUMPSPEED(0.1),
	JUMPVERTICAL(10),
	SCROLLOFFSET(GSvector2(-150, -450)),
	scroll(scroll), isJump(false),
	jumpPower(0),
	speed(VERTICAL),
	respawnPos(position),
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
	speed = VERTICAL;
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
	scroll->moving(position,SCROLLOFFSET);
	position += velocity*gsFrameTimerGetTime();
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
		position = GSvector2(0,viewSize.y + 64);
		//rect.translate(GSvector2(0, rect.getHeight() + 64));
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
		speed = VERTICAL;
		return;
	}
	speed = JUMPVERTICAL;
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
const bool Player::respawn()
{
	if (position.y <= WINDOW_HEIGHT +viewSize.y)
	{
		return false;
	}
	position=respawnPos;
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
		/*const Sound& sound = device.getSound();
		if (!sound.IsPlaySE("Landing.wav")&&velocity.x!=0)
		{
		   sound.PlaySE("Landing.wav");
		}*/
		return;
	}
	isGround = false;
}
const bool Player::collisionStar(const GameObject* obj)
{
	if (!obj->isSameType(STAR))
	{
		return false;
	}
	Star* s = (Star*)obj;
	s->ride(&position,&viewSize);
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
GameObject* Player::clone(const GSvector2& position)
{
	return new Player(textrue,position,viewSize,rect,scroll,device);
}