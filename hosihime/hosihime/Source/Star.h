#ifndef _STAR_H_
#define _STAR_H_
#include "GameObject.h"
#include "IStarMove.h"
class Star :public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2& position,IStarMove* move);
	~Star();
	void inisialize();
	void updata();
	void collision(const GameObject* obj);
	void pickUp(GSvector2* vel);
	void ride(MyRectangle* rect);
private:
	IStarMove* move;
	float ang;
};
#endif