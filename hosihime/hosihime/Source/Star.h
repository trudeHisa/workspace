#ifndef _STAR_H_
#define _STAR_H_
#include "GamaObject.h"
#include "StarMediator.h"
#include "IStarMove.h"
class Star :public GameObject
{
	Star(const std::string& textrue, const GSvector2& position,IStarMove* move);
	~Star();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
	void pickUp(GSvector2* vel);
	void ride(MyRectangle* rect);
	Star* clone();
	void finish();
private:
	IStarMove* move;
	float ang;
};
#endif