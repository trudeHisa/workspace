#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <gslib.h>
#include "GameObject.h"
#include "Timer.h"
#include "Animation.h"
#include "Star.h"
class Device;
#define GSfloat gravity 3;
class Player :public GameObject
{
public:
	Player(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect,
		Scroll* scroll, Device& device);
	virtual ~Player();
	void updata();
    void initialize();
	void collision(const GameObject* obj);
	void draw(const Renderer& renderer, const Scroll& scroll);
	GameObject* clone(const GSvector2& position);
	void endMove();
	bool getIsClear();
	void nonCollision();
private:
	void moving();
	void gravity();
	//Œü‚«‚ð•Ô‚·
	const float moveHorizontal();
	void rideUpDown();	
	//jump
	void jumpStart();
	void jump();
	void jumpEnd();

	const bool respawn();

	const bool isRide()const;
	void statRide(const GameObject* obj);
	//collision
	void collisionGround(const GameObject* obj);
	void collisionStar(const GameObject* obj);
	void collisionRespawn(const GameObject* obj);

	//anim
	void changeAnimation(int dir);
	const std::string getDirKey(int dir);
private:
	bool isGround;
	float jumpPower;

	bool isJump;
	float speed;
	bool isClear;

	GSvector2 respawnPos;
	Scroll* scroll;
	Device& device;

	//
	unsigned int rideStarPointerNum;

	const float GRAVITY;
	const float JUMPMAXPOW;
	const float JUMPSPEED;
	const float VERTICAL;
	const float JUMPVERTICAL;
	const GSvector2 SCROLLOFFSET;

	//int direction;
	std::string currentDirAnimeKey;
	//float lr;
	Animation animation;
	AnimationTimer animeTimer;
};
#endif