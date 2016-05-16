#ifndef _PLANET_H_
#define _PLANET_H_
#include "GameObject.h"
class Planet :public GameObject
{
public:
	Planet(const std::string& textrue, const GSvector2& position);
	~Planet();
	void updata();
	void collision(const GameObject* obj);
};
#endif