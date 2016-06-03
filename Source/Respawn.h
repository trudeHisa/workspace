#ifndef _ROCK_H_
#define _ROCK_H_

#include "GameObject.h"

class Respawn:public GameObject
{
public:
	Respawn(const std::string& textrue, const MyRectangle& rect);
	~Respawn();
	void updata();
	void collision(const GameObject* obj);
	void setRespawn(float* posx);
private:
};
#endif