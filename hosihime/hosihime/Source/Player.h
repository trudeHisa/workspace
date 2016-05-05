#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GamaObject.h"

class Player :public GameObject
{
public:
	Player(const std::string& textrue, const GSvector2* position);
	~Player();
	void updata(MapData* mapdata);
	void initialize();
	//starÇ…èÊÇÍÇΩÇ©ÅH
	bool SetStar(GameObject* _star);
private:
	bool nextAction(int nextPosType);
	void nextPosition(GSvector2* pos);
	GameObject* star;
};
#endif