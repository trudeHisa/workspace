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
	void draw(Renderer& renderer, const Scroll* scroll);
public:
	void ride(MyRectangle* rect);
	void pickUp(GSvector2* velocity);
	Star* clone();
private:
	void rotate();
private:
	IStarMove* move;
	float angle;//rad
	GSvector2 startPosi;
};
#endif