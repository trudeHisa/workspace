/*
*@file BreakStar.h
*@brief Starクラスを継承したクラス
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
		float helth, StarMove_Ptr move, float max_Durability,
		IEffectMediator* effectMediator);
	~BreakStar();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
	void draw(const Renderer& renderer, const Scroll& scroll);

	Star* clone();
	GameObject* clone(const GSvector2& position);
private:
	bool isBreakStart;
	float durability;//耐久性
	const float max_Durability;
};
#endif
