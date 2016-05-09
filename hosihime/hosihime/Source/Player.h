#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GamaObject.h"

class Star;
class Player :public GameObject
{
public:
	Player(const std::string& textrue, const GSvector2* position,Scroll* scroll);
	~Player();
	void updata(MapData* mapdata);
	//star�ɏ�ꂽ���H
	bool setStar(GameObject* _star);
private:
	void moving();
	void starDestroy();
	bool collision(int nextPosType);
	void nextVelocity(GSvector2* _velocity);
	Star* star;
	Scroll* scroll;

	bool jflag = false;
	int y_temp = 0;
	int y_prev = 0;
};
#endif