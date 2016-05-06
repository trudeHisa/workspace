#ifndef _SCROLL_H_
#define _SCROLL_H_

#include "Point.h"
#include "Renderer.h"
class Scroll
{
public:
	Scroll(const Point* windowSize);
	void initialize();
	//ウィンドウの中にあるか
	const bool isInsideWindow(float posx,float width)const;
	//Scroll処理
	void moving(float velocity);
	const float getMovingAmount()const;
	void draw(Renderer& renderer);
private:
	Point windowSize;
	float movingAmount;//どれだけScrollしたか
};
#endif