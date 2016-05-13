#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <gslib.h>
#include "GamaObject.h"
class Rock;
class Star;
#define GSfloat gravity 3;
class Player :public GameObject
{
public:
	Player(const std::string& textrue, const GSvector2& position,Scroll* scroll);
	~Player();
	void updata();
	//starÇ…èÊÇÍÇΩÇ©ÅH
	bool setStar(GameObject* _star);
	void collision(const GameObject* obj);
private:
	void starDestroy();
	void FreeFall();
	Star* star;
	Scroll* scroll;
	Rock* rock;

	bool isGround=false;
	bool jflag = false;
	int y_temp = 0;
	int y_prev = 0;
};
#endif