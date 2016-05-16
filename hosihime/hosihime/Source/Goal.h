#ifndef _GOAL_H_
#define _GOAL_H_

#include "GameObject.h"

class Goal : public GameObject
{
public:
	Goal(const std::string& textrue, const GSvector2& position);
	~Goal();
	void updata();
	void collision(const GameObject* obj);
	
private:
};

#endif