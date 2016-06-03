#ifndef _MAGPIE_H_
#define _MAGPIE_H_
#include "GameObject.h"
#include <vector>
class Magpie:public GameObject
{
public:
	Magpie(const std::string& textrue, const GSvector2& position);
	~Magpie();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
private:
	void sort();
	void setDestination();
private:
	GSvector2 destination;
};
#endif
