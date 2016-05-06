#ifndef _SCROLL_H_
#define _SCROLL_H_

#include "Point.h"
#include "Renderer.h"
class Scroll
{
public:
	Scroll(const Point* windowSize);
	void initialize();
	//�E�B���h�E�̒��ɂ��邩
	const bool isInsideWindow(float posx,float width)const;
	//Scroll����
	void moving(float velocity);
	const float getMovingAmount()const;
	void draw(Renderer& renderer);
private:
	Point windowSize;
	float movingAmount;//�ǂꂾ��Scroll������
};
#endif