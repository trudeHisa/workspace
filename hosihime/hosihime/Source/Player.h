#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <gslib.h>
#include "GameObject.h"
#include "Timer.h"
class Device;
#define GSfloat gravity 3;

class Player :public GameObject
{
public:
	Player(const std::string& textrue, const MyRectangle& rect, Scroll* scroll, Device& device);
	~Player();
	void updata();
	void initialize();
	void collision(const GameObject* obj);
private:
	void moving();
	void gravity();
	void jumpStart();
	void jump();
	void jumpEnd();
	void rideUpDown();
	void moveHorizontal();
	const bool respawn();

	void collisionGround(const GameObject* obj);
	const bool collisionStar(const GameObject* obj);
	void collisionRespawn(const GameObject* obj);
private:
	bool isGround;
	float jumpPower;

	bool isJump;
	bool isRide;
	float speed;
	GSvector2 respawnPos;

	Scroll* scroll;
	Device& device;
};
#endif