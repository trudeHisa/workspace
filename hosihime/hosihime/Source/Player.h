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
	//starÇ…èÊÇÍÇΩÇ©ÅH
	bool setStar(GameObject* _star);
private:
	void starDestroy();
	bool collision(int nextPosType);
	Star* star;
	Scroll* scroll;

	bool jflag = false;
	int y_temp = 0;
	int y_prev = 0;
};
#endif