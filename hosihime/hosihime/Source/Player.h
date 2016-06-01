#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <gslib.h>
#include "GameObject.h"
#include "Timer.h"
class Input;
#define GSfloat gravity 3;

class Player :public GameObject
{
public:
	Player(const std::string& textrue, const MyRectangle& rect, Scroll* scroll, const Input& input);
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
	void moveHorizontal();
	const bool respawn();

	void collisionGround(const GameObject* obj);
 	const bool collisionStar(const GameObject* obj);
	void collisionRespawn(const GameObject* obj);
private:
	const Input& input;
	Scroll* scroll;
	
	Timer jumpTimer;
	float speed;
	GSvector2 respawnPos;
	bool isGround;
	bool isJump;
	bool isRide;
};
#endif