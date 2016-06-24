#include "Player.h"
#include "Device.h"

#include "Calculate.h"
#include "Respawn.h"
#include "Magpie.h"
#include "StarParticleController.h"


Player::Player(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	Scroll* scroll, Device& device, IEffectMediator* effectMediator)
	:GameObject(textrue, position, viewSize, rect, PLAYER),

	GRAVITY(10), VERTICAL(5),
	JUMPMAXPOW(-11), JUMPSPEED(0.03),
	JUMPVERTICAL(6),
	SCROLLOFFSET(GSvector2(-WINDOW_WIDTH / 2 + viewSize.x, -(WINDOW_HEIGHT / 2) - viewSize.y)),

	device(device), scroll(scroll),
	respawnPos(position),
	rideStarPointerNum(0), jumpPower(0),
	speed(VERTICAL),
	isJump(false), isRespawn(true),
	isGround(false), isClear(false),
	isMagpieRide(false),

	animation(animeTimer),
	animeTimer(60.f),
	currentDirAnimeKey("R"),
	effectMediator(effectMediator),
	positionsRight(position+GSvector2(10,64)),
	positionsLeft(position+GSvector2(80,64))

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
	isMagpieRide = false;

	currentDirAnimeKey = "R";
	animeTimer.initialize();
	animeTimer.setStarTimer(60.f);
	animation.addCell("L", 1, 1, 64, 64);//�ړ���
	animation.addCell("R", 2, 1, 64, 64);//�ړ��E
	animation.addCell("JL", 3, 1, 64, 64);//�W�����v��
	animation.addCell("JR", 4, 1, 64, 64);//�W�����v�E
	animation.addCell("SR", 5, 1, 64, 64);//�����E
	animation.addCell("SL", 6, 1, 64, 64);//����荶

	//animation.addCell("SL", 6, 1, 74,112);//����荶

	isRespawn = true;
	scroll->initialize(position + SCROLLOFFSET);
	ishold = false;

	positionsRight = position + GSvector2(10, 64);
	positionsLeft = position + GSvector2(80, 64);
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
	positionsRight = position + GSvector2(10, 64);
	positionsLeft = position + GSvector2(80, 64);

	gravity();
	jumpStart();
	rideUpDown();
	jump();
	float movedir = moveHorizontal();
	changeAnimation(movedir);
	if (!isGround)
	{
		return;
	}
	const Sound& sound = device.getSound();
	if (!sound.IsPlaySE("landing.wav") && movedir != 0)
	{
		sound.PlaySE("landing.wav");
	}
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
	device.getSound().PlaySE("jump.wav");

	if (currentDirAnimeKey == "R")
	{
		
		effectMediator->add("StarEffect", positionsRight);
	}
	if (currentDirAnimeKey == "L")
	{
		effectMediator->add("StarEffect", positionsLeft);
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
	float direction = device.getInput().getVelocity().x;
	velocity.x = direction* speed;
	return direction;
}

void Player::endMove()
{
	if (!isClear) return;
	//velocity.x = 2.0f;
	if (isGround == false)
		isDead = true;
}

bool Player::getIsClear()
{
	return isClear;
}

//��ʂȂ��ɉf���Ă��Ȃ������烊�X�|��
const bool Player::respawn()
{
	//��ʓ����H
	if (scroll->isInsideWindow(scroll->transformViewPosition(position), viewSize))
	{
		/*
		��肠����
		*/
		if (isGround)
		{
			isRespawn = false;
		}
		
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
	if (obj->getType() == HIKOBOSHI)
	{
		ishold = true;
	}

	if (obj->getType() == MAGPIE)
	{
		const Magpie* mag = dynamic_cast<const Magpie*>(obj);
		if (mag->isRide())
		{
			ride(obj);
			isMagpieRide = true;
			jumpEnd();
		}
		else
		{
			isMagpieRide = false;
		}
	}
	if (isMagpieRide)
	{
		return;
	}
	collisionStar(obj);
	collisionRespawn(obj);
	collisionGround(obj);
	if (obj->getType() == GOAL) isClear = true;
	if (obj->getType() == BURNSTAR || obj->getType() == PLANET)
	{
		//effectMediator->add("FireworkEffect", position);
		position = respawnPos;
		velocity = GSvector2(0, 0);
		jumpPower = 0;
		isRespawn = true;
	}
}
void Player::collisionGround(const GameObject* obj)
{
	GAMEOBJ_TYPE type = obj->getType();
	if (type == RESPAWN ||
		type == START ||
		type == GOAL ||
		type == MAGPIE_ENDSPOT)
	{
		isGround = true;
		jumpEnd();
	}
}

void Player::ride(const GameObject* obj)
{
	if (obj->getType() == MAGPIE)
	{
		position.x = obj->getPosition().x + 32;
		position.y = obj->getPosition().y - 2;
		return;
	}
	position = obj->getPosition();
	position.y -= viewSize.y;
}

void Player::collisionStar(const GameObject* obj)
{
	if (isRespawn)
	{
		return;
	}
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
		ride(obj);
		jumpEnd();
		return;
	}
	if (rideStarPointerNum != pointerNum)
	{
		return;
	}
	ride(obj);
	jumpEnd();
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
	isMagpieRide = false;
}

GameObject* Player::clone(const GSvector2& position)
{
	return new Player(textrue, position, viewSize, rect, scroll, device, effectMediator);
}

void Player::draw(const Renderer& renderer, const Scroll& scroll)
{
	if (!isInScreen(scroll))
	{
		return;
	}
	if (ishold)
	{
		renderer.DrawTextrue("hold.bmp", &scroll.transformViewPosition(position));
		return;
	}
	animation.draw(renderer, textrue, &scroll.transformViewPosition(position));
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
