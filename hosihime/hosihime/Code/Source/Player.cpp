#include "Player.h"
#include "Device.h"

#include "Calculate.h"
#include "Respawn.h"
#include "Magpie.h"
//stateパターン
Player::Player(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	Scroll* scroll, Device& device, IEffectMediator* effectMediator)

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
	isMagpieRide(false),

	animation(animeTimer),
	animeTimer(60.f),
	currentDirAnimeKey("R"),
	effectMediator(effectMediator)
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
	animation.addCell("L", 1, 3, 64, 64);//移動左
	animation.addCell("R", 2, 3, 64, 64);//移動右
	animation.addCell("JL", 3, 3, 64, 64);//ジャンプ左
	animation.addCell("JR", 4, 3, 64, 64);//ジャンプ右
	animation.addCell("SR", 5, 3, 64, 64);//星乗り右
	animation.addCell("SL", 6, 3, 64, 64);//星乗り左

	isRespawn = true;

	scroll->initialize(position + SCROLLOFFSET);
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
	//effectMediator->add( "",position-scroll->getMovingAmount());
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
	velocity.x = 2.0f;
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
	if (scroll->isInsideWindow(scroll->transformViewPosition(position), viewSize))
	{
		/*
		取りあえず
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

		/*const Sound& sound = device.getSound();
			if (!sound.IsPlaySE("Landing.wav")&&velocity.x!=0)
			{
			sound.PlaySE("Landing.wav");
			}*/
	}
}

void Player::ride(const GameObject* obj)
{
	if (obj->getType() == MAGPIE)
	{
		position.x = obj->getPosition().x+32;
		position.y = obj->getPosition().y -2;
		return;
	}

	position = obj->getPosition();
	position.y -= (viewSize.y + 1);
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
	animation.draw(renderer, "orihime.bmp", &scroll.transformViewPosition(position));
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
