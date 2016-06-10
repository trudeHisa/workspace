#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <gslib.h>
#include "GameObject.h"
#include "Timer.h"
#include "Animation.h"
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
	void draw(const Renderer& renderer, const Scroll& scroll);
	GameObject* clone(const GSvector2& position);
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
 	const bool collisionStar(const GameObject* obj);
	void collisionRespawn(const GameObject* obj);

	//anim
	void animation();
private:
	bool isGround;
	float jumpPower;

	bool isJump;
	bool isRide;
	float speed;
	GSvector2 respawnPos;

	Scroll* scroll;

	Device& device;

	float changedir;
	float lr;
	Animation anim;
	AnimationTimer animetimer;
};
#endif