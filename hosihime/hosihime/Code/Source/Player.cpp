#include "Player.h"
#include "Device.h"

#include "Calculate.h"
#include "Respawn.h"

//state�p�^�[��
Player::Player(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	Scroll* scroll, Device& device)

	:GameObject(textrue, position, viewSize, rect, PLAYER),

	GRAVITY(10), VERTICAL(5),
	JUMPMAXPOW(-15), JUMPSPEED(0.1),
	JUMPVERTICAL(10),
	SCROLLOFFSET(GSvector2(-WINDOW_WIDTH / 2 + viewSize.x, -(WINDOW_HEIGHT / 2) - viewSize.y)),

	device(device), scroll(scroll),
	respawnPos(position),
	rideStarPointerNum(0), jumpPower(0),
	speed(VERTICAL), 
	isJump(false), isRespawn(true),
	isGround(false), isClear(false), 

	animation(animeTimer),
	animeTimer(60.f),
	currentDirAnimeKey("R")
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

	isGround = false;
	isClear = false;

	currentDirAnimeKey = "R";
	animeTimer.initialize();
	animeTimer.setStarTimer(60.f);
	animation.addCell("L", 1, 1, 64, 64);//�ړ���
	animation.addCell("R", 2, 1, 64, 64);//�ړ��E
	animation.addCell("JL", 3, 1, 64, 64);//�W�����v��
	animation.addCell("JR", 4, 1, 64, 64);//�W�����v�E

	animation.addCell("SR", 5, 1, 74, 112);//�����E
	animation.addCell("SL", 6, 1, 74,112);//����荶

	isRespawn = true;

	scroll->initialize(position+SCROLLOFFSET);
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
	scroll->moving(position, SCROLLOFFSET);
	endMove();
	position += velocity*gsFrameTimerGetTime();
	if (isRide())
	{
		textrue = "starride.bmp";
	}
	else
	{
		textrue = "orihime.bmp";
	}
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
	jump();

	changeAnimation(moveHorizontal());
}
void Player::rideUpDown()
{
	if (rideStarPointerNum == 0)
	{
		return;
	}
	if (device.getInput().getDownTrigger())
	{
		
		velocity = GSvector2(0, 0);
		/*
		*64�͐��̃T�C�Y
		*�v���t�@�N�^�����O
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
const float Player::moveHorizontal()
{
	//if (!isGround && !isJump)
	//{
	//	return;
	//}
	float direction = device.getInput().getVelocity().x;
	velocity.x = direction* speed;
	return direction;
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

//��ʂȂ��ɉf���Ă��Ȃ������烊�X�|��
const bool Player::respawn()
{
	//view���W�ɕϊ�
	GSvector2 pos = position - scroll->getMovingAmount();
	//��ʓ����H
	if (scroll->isInsideWindow(pos, viewSize))
	{
		/*
		��肠����
		*/
		isRespawn = false;
		return false;
	}

	if (isRespawn)
	{
		return false;
	}

	position = respawnPos;
	velocity = GSvector2(0, 0);
	jumpPower = 0;

	isRespawn = true;
	return true;
}

/**
*����Ă�����true
*0�̎��͏���Ă��Ȃ�
*/
const bool Player::isRide()const
{
	return rideStarPointerNum != 0;
}
//�Փ�
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
	if (rideStarPointerNum == 0)
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
	respawn->setRespawn(&respawnPos);
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
	if (!isInScreen(scroll))
	{
		return;
	}
	GSvector2 pos = position - scroll.getMovingAmount();
	
	animation.draw(renderer, textrue, &pos);
	
}

const std::string Player::getDirKey(int dir)
{
	if (dir > 0)
	{
		return "R";
	}
	if (dir < 0)
	{
		return "L";
	}
	return currentDirAnimeKey;
}

void Player::changeAnimation(int dir)
{
	currentDirAnimeKey = getDirKey(dir);
	std::string stateKey = "";
	if (isJump)
	{
		stateKey = "J";
	}
	if (isRide())
	{
		stateKey = "S";
	}
	animation.updata(stateKey + currentDirAnimeKey);
}
//void Player::animation()
//{	
//	//migi
//	if (changedir > 0)
//	{
//		lr = 2;
//		animation.updata("R");
//		if (!isGround)
//		{
//			animation.updata("JR");
//			lr = 1;
//		}
//	}
//	else if (changedir >= 0 && isGround && lr == 1)
//	{
//		animation.updata("R");
//		lr = 0;
//	}
//	
//	//hidari
//	if (changedir < 0)
//	{
//		lr = -2;
//		animation.updata("L");
//		if (!isGround)
//		{
//			animation.updata("JL");
//			lr = -1;
//		}
//	}
//	else if (changedir <= 0 && isGround && lr == -1)
//	{
//		animation.updata("L");
//		lr = 0;
//	}
//
//	//changedir ���@0 �̂Ƃ�
//	if (!isGround && lr == 2)
//	{
//		animation.updata("JR");
//	}
//	else if (!isGround && lr == -2)
//	{
//		animation.updata("JL");
//	}
//	else if (isGround && lr > 0)
//	{
//		animation.updata("R");
//	}
//	else if (isGround && lr < 0)
//	{
//		animation.updata("L");
//	}
//}