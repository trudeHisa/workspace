#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <gslib.h>
#include "GameObject.h"
#include "Timer.h"
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
	GameObject* clone(const GSvector2& position);
	void endMove();
	bool getIsClear();
	void nonCollision();
private:
	void moving();
	void gravity();
	void moveHorizontal();
	void rideUpDown();	
	//jump
	void jumpStart();
	void jump();
	void jumpEnd();

	const bool respawn();
	//collision
	void collisionGround(const GameObject* obj);
	void collisionStar(const GameObject* obj);
	void collisionRespawn(const GameObject* obj);
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
};
#endif