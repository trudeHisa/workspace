#include "Player.h"
#include "Device.h"

#include "Calculate.h"
#include "Respawn.h"

//stateパターン
Player::Player(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	Scroll* scroll, Device& device)
	:GameObject(textrue, position, viewSize, rect, PLAYER),
	rideStarPointerNum(0),
	GRAVITY(10), VERTICAL(5),
	JUMPMAXPOW(-15), JUMPSPEED(0.1),
	JUMPVERTICAL(10),
	SCROLLOFFSET(GSvector2(-WINDOW_WIDTH / 2 + viewSize.x, -(WINDOW_HEIGHT / 2) - viewSize.y)),
	scroll(scroll), isJump(false),
	jumpPower(0),
	speed(VERTICAL),
	respawnPos(position),
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
	speed = VERTICAL;
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
	/*if (respawn())
	{
		return;
	}*/
	scroll->moving(position, SCROLLOFFSET);
	endMove();
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
	animation();
}
void Player::rideUpDown()
{
	if (!isRide())
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
		position.y += viewSize.y + 64;
	}
	if (device.getInput().getUpTrigger())
	{
		isJump = true;
		jumpPower = JUMPMAXPOW;
	}
}
void Player::jumpStart()
{
	if (!isGround&&rideStarPointerNum == 0)
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
	changedir = device.getInput().getVelocity().x;
	velocity.x = changedir* speed;
}

void Player::endMove()
{
	if (!isClear) return;
	velocity.x = 2.0f;
	if (isGround == false) isDead = true;
}

bool Player::getIsClear()
{
	return isClear;
}

//
const bool Player::respawn()
{
	if (position.y <= WINDOW_HEIGHT + viewSize.y)
	{
		return false;
	}
	position = respawnPos;
	velocity = GSvector2(0, 0);
	jumpPower = 0;
	return true;
}

/**
*乗っていたらtrue
*0の時は乗っていない
*/
const bool Player::isRide()const
{
	return rideStarPointerNum != 0;
}
//衝突
void Player::collision(const GameObject* obj)
{
	collisionStar(obj);
	collisionRespawn(obj);
	collisionGround(obj);
	if (obj->getType() == GOAL) isClear = true;
	if (obj->getType() == BURNSTAR)
	{
		isDead = true;
}
}
void Player::collisionGround(const GameObject* obj)
{
	GAMEOBJ_TYPE type = obj->getType();
	if (type == RESPAWN ||
		type == START ||
		type == GOAL)
	{
		isGround = true;
		jumpEnd();
		/*const Sound& sound = device.getSound();
			if (!sound.IsPlaySE("Landing.wav")&&velocity.x!=0)
			{
			sound.PlaySE("Landing.wav");
			}*/
	}
}
void Player::statRide(const GameObject* obj)
{
	const Star* star = dynamic_cast<const Star*>(obj);
	star->ride(&position, &viewSize);
	star->pickUp(&velocity);
	jumpEnd();
}
void Player::collisionStar(const GameObject* obj)
{
	GAMEOBJ_TYPE type = obj->getType();
	if (type != STAR&& type != BREAKSTAR)
	{
		return;
	}
	//
	unsigned int pointerNum = (unsigned int)obj;
	if (!isRide())
{
		rideStarPointerNum = pointerNum;		
		statRide(obj);
		return;
	}
	if (rideStarPointerNum != pointerNum)
	{
		return;	
	}
	statRide(obj);
}
void Player::collisionRespawn(const GameObject* obj)
{
	if (obj->getType() != RESPAWN)
	{
		return;
	}
	const Respawn* respawn = dynamic_cast<const Respawn*>(obj);
	respawn->setRespawn(&respawnPos.x);
}
void Player::nonCollision()
{
	rideStarPointerNum = 0;
	isGround = false;
}

GameObject* Player::clone(const GSvector2& position)
{
	return new Player(textrue, position, viewSize, rect, scroll, device);
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