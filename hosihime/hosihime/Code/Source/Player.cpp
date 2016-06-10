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
	device(device),
	anim(&animetimer),
	animetimer(60.f)
{
}
Player::~Player()
{
	scroll = NULL;
	animetimer = NULL;
}
void Player::initialize()
{
	GameObject::initialize();
	jumpEnd();
	speed = 6;
	jumpPower = 0;

	animetimer.initialize();
	animetimer.setStarTimer(60.f);
	anim.addCell("L", 1, 3, 64, 64);//移動左
	anim.addCell("R", 2, 3, 64, 64);//移動右
	anim.addCell("JL", 3, 3, 64, 64);//ジャンプ左
	anim.addCell("JR", 4, 3, 64, 64);//ジャンプ右
	/*anim.addCell("D", 5, 3, 64, 64);
	anim.addCell("A", 6, 3, 64, 64);*/
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
	gravity();
	jumpStart();
	rideUpDown();
	moveHorizontal();
	jump();
	animation();
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
	changedir = device.getInput().getVelocity().x;
	velocity.x = changedir* speed;
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
//衝突
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
GameObject* Player::clone(const GSvector2& position)
{
	return new Player(textrue, MyRectangle(position, rect.getSize()),scroll,device);
}

void Player::draw(const Renderer& renderer, const Scroll& scroll)
{
	GSvector2 pos = rect.getPosition();
	pos -= scroll.getMovingAmount();
	if (!scroll.isInsideWindow(pos, rect.getSize()))
	{
		return;
	}
	//renderer.DrawTextrue("orihime.bmp", &pos);
	anim.draw(renderer, "orihime.bmp", &pos);
}

void Player::animation()
{
	
	//migi
	if (changedir > 0)
	{
		lr = 2;
		anim.updata("R");
		if (!isGround)
		{
			anim.updata("JR");
			lr = 1;
		}
	}
	else if (changedir >= 0 && isGround && lr == 1)
	{
		anim.updata("R");
		lr = 0;
	}
	
	//hidari
	if (changedir < 0)
	{
		lr = -2;
		anim.updata("L");
		if (!isGround)
		{
			anim.updata("JL");
			lr = -1;
		}
	}
	else if (changedir <= 0 && isGround && lr == -1)
	{
		anim.updata("L");
		lr = 0;
	}

	//changedir が　0 のとき
	if (!isGround && lr == 2)
	{
		anim.updata("JR");
	}
	else if (!isGround && lr == -2)
	{
		anim.updata("JL");
	}
	else if (isGround && lr > 0)
	{
		anim.updata("R");
	}
	else if (isGround && lr < 0)
	{
		anim.updata("L");
	}
}