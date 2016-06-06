#ifndef _ROCK_H_
#define _ROCK_H_

#include "GameObject.h"

class Respawn:public GameObject
{
public:
	Respawn(const std::string& textrue, const GSvector2& position, const MyRectangle& rect);
	~Respawn();
	void updata();
	void collision(const GameObject* obj);
	void setRespawn(float* posx);
	GameObject* clone(const GSvector2& position);
};
#endif