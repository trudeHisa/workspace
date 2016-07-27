#include "Player.h"
#include "Device.h"

#include "Calculate.h"
#include "Respawn.h"
#include "Magpie.h"
#include "StarParticleController.h"


Player::Player(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	Scroll* scroll, Device& device, IEffectMediator* effectMediator)
	:GameObject(textrue, position, viewSize, rect, GAMEOBJ_TYPE::PLAYER),

	GRAVITY(10), VERTICAL(5),
	JUMPMAXPOW(-10), JUMPSPEED(0.03),
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
	positionsRight(position + GSvector2(10, 64)),
	positionsLeft(position + GSvector2(80, 64)),
	respawnCount(0, 4)
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
	respawnCount.initialize();

	currentDirAnimeKey = "R";
	animeTimer.initialize();
	animeTimer.setStarTimer(60.f);
	animation.addCell("L", 1, 1, 64, 64);//移動左
	animation.addCell("R", 2, 1, 64, 64);//移動右
	animation.addCell("JL", 3, 1, 64, 64);//ジャンプ左
	animation.addCell("JR", 4, 1, 64, 64);//ジャンプ右
	animation.addCell("SR", 5, 1, 64, 64);//星乗り右
	animation.addCell("SL", 6, 1, 64, 64);//星乗り左

	//animation.addCell("SL", 6, 1, 74,112);//星乗り左

	isRespawn = true;
	scroll->initialize(position + SCROLLOFFSET);
	ishold = false;

	positionsRight = position + GSvector2(10,70);
	positionsLeft = position + GSvector2(80, 70);
}
void Player::jumpEnd()
{
	if (isJump == true)
	{
		device.getSound().playSE("着地.wav");
	}
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

	if (respawnCount.isEnd())
	{
		position = respawnPos;
		velocity = GSvector2(0, 0);
		jumpPower = 0;
		isRespawn = true;
		respawnCount.initialize();
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
	positionsRight = position + GSvector2(10, 70);
	positionsLeft = position + GSvector2(80, 70);

	gravity();
	jumpStart();
	
	jump();
	float movedir = moveHorizontal();
	changeAnimation(movedir);
	if (!isGround)
	{
		return;
	}
	const Sound& sound = device.getSound();
	if (!sound.isPlaySE("landing.wav") && movedir != 0)
	{
		sound.playSE("landing.wav");
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
	device.getSound().playSE("jump.wav");

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
		respawnCount.initialize();
		return;
	}
	
	respawnCount.update();

	speed = JUMPVERTICAL;
	velocity.y = jumpPower;
	jumpPower += GRAVITY*gsFrameTimerGetTime()*JUMPSPEED;
	Calculate<float>calc;
	jumpPower = calc.clamp(jumpPower, JUMPMAXPOW, -JUMPMAXPOW);
}
const float Player::moveHorizontal()
{
	if (isRespawn)
	{
		return 0.0f;
	}
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

//画面ないに映っていなかったらリスポン
const bool Player::respawn()
{
	//画面内か？
	if (isInScreen(*scroll))
	{
		/*
		取りあえず
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

	device.getSound().playSE("リスポーン.wav");
	position = respawnPos;
	velocity = GSvector2(0, 0);
	jumpPower = 0;
	isRespawn = true;
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
	if (obj->getType() == GAMEOBJ_TYPE::HIKOBOSHI)
	{
		ishold = true;
	}

	if (obj->getType() == GAMEOBJ_TYPE::MAGPIE)
	{
		const Magpie* mag = dynamic_cast<const Magpie*>(obj);
		if (mag->isRide())
		{
			if (!device.getSound().isPlaySE("kasasagi_fly.wav"))
			{
				device.getSound().playSE("kasasagi_fly.wav");
			}
			//device.getSound().playSE("kasasagi_fly.wav");
			if (currentDirAnimeKey == "R")
			{

				effectMediator->add("LightEffect", positionsRight);
			}
			if (currentDirAnimeKey == "L")
			{
				effectMediator->add("LightEffect", positionsLeft - GSvector2(68, 0));
			}
			ride(obj);
			isMagpieRide = true;
			jumpEnd();
		}
		else
		{
			isMagpieRide = false;
			device.getSound().stopSE("kasasagi_fly.wav");
		}
	}
	if (isMagpieRide)
	{
		return;
	}
	collisionStar(obj);
	collisionRespawn(obj);
	collisionGround(obj);
	if (obj->getType() == GAMEOBJ_TYPE::GOAL) isClear = true;
	if (obj->getType() == GAMEOBJ_TYPE::BURNSTAR || obj->getType() == GAMEOBJ_TYPE::PLANET)
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
	if (type == GAMEOBJ_TYPE::RESPAWN ||
		type == GAMEOBJ_TYPE::START ||
		type == GAMEOBJ_TYPE::GOAL ||
		type == GAMEOBJ_TYPE::MAGPIE_ENDSPOT)
	{
		isGround = true;
		jumpEnd();
	}
}

void Player::ride(const GameObject* obj)
{
	if (obj->getType() == GAMEOBJ_TYPE::MAGPIE)
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
	if (!isInScreen(*scroll))
	{
		return;
	}
	if (isRespawn)
	{
		return;
	}
	GAMEOBJ_TYPE type = obj->getType();
	if (type != GAMEOBJ_TYPE::STAR&& type != GAMEOBJ_TYPE::BREAKSTAR)
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
		rideUpDown();
		return;
	}
	if (rideStarPointerNum != pointerNum)
	{
		return;
	}
	ride(obj);
	jumpEnd();
	rideUpDown();
}
void Player::collisionRespawn(const GameObject* obj)
{
	if (obj->getType() != GAMEOBJ_TYPE::RESPAWN)
	{
		return;
	}
	GSvector2 respawn = obj->getPosition();
	respawn.y -=5 * 64;
	respawnPos = respawn;
	//const Respawn* respawn = dynamic_cast<const Respawn*>(obj);
	//respawn->setRespawn(&respawnPos);
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
		renderer.drawTextrue("hold.bmp", &scroll.transformViewPosition(position));
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
