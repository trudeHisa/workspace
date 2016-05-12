#ifndef _ROCK_H_
#define _ROCK_H_

#include "GamaObject.h"

class Rock:public GameObject
{
public:
	Rock(const std::string& textrue, const GSvector2& position);
	~Rock();
	void updata();
	void collision(const GameObject* obj);
	void respawn(const GSvector2& pos,GSvector2* vel);
private:
};
#endif