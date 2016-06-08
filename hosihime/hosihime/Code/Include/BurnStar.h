/*
*@file BurnStar.h
*@brief Starクラスを継承したクラス
*@author matuo
*@data 2016/6/7
*/
#ifndef _BURNSTAR_H_
#define _BURNSTAR_H_

#include "Star.h"
class BurnStar :public Star
{
public:
	BurnStar(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect, StarMove_Ptr move);
	~BurnStar();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
	void draw(const Renderer& renderer, const Scroll& scroll);

	Star* clone();
	GameObject* clone(const GSvector2& position);
private:

};
#endif