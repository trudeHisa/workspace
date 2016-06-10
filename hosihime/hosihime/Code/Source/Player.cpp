#include "Player.h"
#include "Device.h"

#include "Calculate.h"
#include "Respawn.h"

Player::Player(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	Scroll* scroll, Device& device)
	:GameObject(textrue,position,viewSize,rect,PLAYER),
	rideStarPointerNum(0),
	GRAVITY(10), VERTICAL(5),
	JUMPMAXPOW(-15),JUMPSPEED(0.1),
	JUMPVERTICAL(10),
	SCROLLOFFSET(GSvector2(-WINDOW_WIDTH/2+viewSize.x, -(WINDOW_HEIGHT/2)-viewSize.y)),
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
	rideStarPointerNum = 0;
}
void Player::jumpEnd()
{
	isJump = false;
	jumpPower = 0;
}
void Player::updata()
{
	moving();
	/*if (respawn())
	{
		return;
	}*/
	scroll->moving(position, SCROLLOFFSET);
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
		/*
		*64は星のサイズ
		*要リファクタリング
		*/
		position.y +=viewSize.y + 64;
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
	Calculate<float>calc;
	jumpPower = calc.clamp(jumpPower, JUMPMAXPOW, -JUMPMAXPOW);
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
	position = respawnPos;
	velocity = GSvector2(0, 0);
	jumpPower = 0;
	return true;
	return false;
}
//衝突
void Player::collision(const GameObject* obj)
{
	//collisionStar(obj);
	//collisionRespawn(obj);
	collisionGround(obj);
	if (obj->getType() == BURNSTAR)
	{
		isDead = true;
	}
}
void Player::collisionGround(const GameObject* obj)
{
	GAMEOBJ_TYPE type = obj->getType();
	if (type==RESPAWN||
		type==START ||
		type==GOAL)
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
	GAMEOBJ_TYPE type = obj->getType();
	if (type != STAR&& type!=BREAKSTAR)
	{
		return false;
	}
	//当たって
	if (rideStarPointerNum != 0)
	{

	}
	//unsigned int pointerNum =(unsigned int)obj;
	//if (rideStarPointerNum == 0 || rideStarPointerNum == pointerNum)
	//{
	//	rideStarPointerNum = pointerNum;

		const Star* s = dynamic_cast<const Star*>(obj);	
		s->ride(&position, &viewSize);
		s->pickUp(&velocity);
		jumpEnd();
		return true;
	//}
	//return false;
}
void Player::collisionRespawn(const GameObject* obj)
{
	if (obj->getType()!=RESPAWN)
	{
		return;
	}
	const Respawn* respawn =dynamic_cast<const Respawn*>(obj);
	respawn->setRespawn(&respawnPos.x);
}
GameObject* Player::clone(const GSvector2& position)
{
	return new Player(textrue,position,viewSize,rect,scroll,device);
}