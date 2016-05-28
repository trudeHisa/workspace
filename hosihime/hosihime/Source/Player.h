#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <gslib.h>
#include "GameObject.h"
class Rock;
class Star;
#define GSfloat gravity 3;
class Player :public GameObject
{
public:
	Player(const std::string& textrue, const MyRectangle& rect, Scroll* scroll);
	~Player();
	void updata();
    void initialize();
	//starÇ…èÊÇÍÇΩÇ©ÅH
	//bool setStar(GameObject* _star);
	void collision(const GameObject* obj);
private:
	void respawn();
	void starDestroy();
	void freeFall();
	void moving();
	bool jump();
	void jumpstart();
	void moveLR();

private:
	Star* star;
	Scroll* scroll;
	Rock* rock;

	bool isGround=false;
	bool jflag = false;
	int y_temp = 0;
	int y_prev = 0;
	int count = 0;
};
#endif