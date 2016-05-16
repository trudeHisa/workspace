#ifndef START_H_
#define START_H_

#include "GameObject.h"

class Start : public GameObject
{
public:
	Start(const std::string& textrue, const GSvector2& position);
	~Start();
	void updata();
	void collision(const GameObject* obj);

private:

};

#endif