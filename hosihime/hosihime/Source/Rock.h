#ifndef _ROCK_H_
#define _ROCK_H_

#include "GamaObject.h"

class Rock:public GameObject
{
public:
	Rock(const std::string& textrue, const GSvector2* position);
	~Rock();
	void updata(MapData* mapdata);
	void initialize();
private:
	bool nextAction(int nextPosType);
	void nextPosition(GSvector2* pos);
};
#endif