#ifndef _SCROLL_H_
#define _SCROLL_H_

#include "Point.h"
#include "Renderer.h"
class Scroll
{
public:
	Scroll(const Point* windowSize);
	void initialize();
	void updata();
	void draw(Renderer& renderer);
	//Scroll����
	void moving(float velocity);
	//�E�B���h�E�̒��ɂ��邩
	const bool isInsideWindow(float posx,float width)const;
	const float getMovingAmount()const;	
private:
	GSvector2 position1;
	GSvector2 position2;
	Point windowSize;
	float movingAmount;//�ǂꂾ��Scroll������
};
#endif