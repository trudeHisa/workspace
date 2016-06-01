#ifndef _STAR_H_
#define _STAR_H_
#include <string>
#include "GameObject.h"

class IStarMove;

class Star :public GameObject
{
public:
	Star(const std::string& textrue, const MyRectangle& rect, IStarMove* move);
	~Star();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
	void ride(MyRectangle* rect);
	Star* clone();
	void finish();
private:
	IStarMove* move;
	float ang;
	GSvector2 startPosi;
};
#endif