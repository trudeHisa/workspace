#ifndef _STAR_H_
#define _STAR_H_
#include "GamaObject.h"
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
	//îgê¸
	void LinePattern7(GSvector2* _velocity, float* rot);
	float ang, spd, sindw, rot = 0;
};
#endif