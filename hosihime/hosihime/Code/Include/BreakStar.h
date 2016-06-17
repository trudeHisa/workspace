/*
*@file BreakStar.h
*@brief StarNXπp³΅½NX
*@author matuo
*@data 2016/6/7
*/
#ifndef _BREAKSTAR_H_
#define _BREAKSTAR_H_

#include "Star.h"
class BreakStar :public Star
{
public:
	BreakStar(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect,
		StarMove_Ptr move, float max_Durability);
	~BreakStar();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
	void draw(const Renderer& renderer, const Scroll& scroll);

	Star* clone();
	GameObject* clone(const GSvector2& position);
private:
	bool isBreakStart;
	float durability;//Οv«
	const float max_Durability;
	float blinkerTime;//_ΕΤupΟ
	bool blinker;//_ΕpΟ
};
#endif
