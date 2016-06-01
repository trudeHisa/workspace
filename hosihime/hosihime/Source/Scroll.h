#ifndef _SCROLL_H_
#define _SCROLL_H_

#include "Point.h"
#include "Renderer.h"
enum SCROLLMODE
{
	VERTICAL,// x
	HORIZONTAL,//y
	OMNIDIRECTIONAL//xy
};
class Scroll
{
public:
	Scroll(const Point* windowSize);
	void initialize();
	void updata();
	void draw(Renderer& renderer);
	void reSetMoveing(const GSvector2& position);
	//Scroll処理
	void moving(const GSvector2& velocity);
	//ウィンドウの中にあるか
	const bool isInsideWindow(const GSvector2& pos, const GSvector2& size)const;
	const GSvector2& getMovingAmount()const;

	void setMode(SCROLLMODE _mode);
	const SCROLLMODE getMode()const;

	void stop();
	void start();
	bool isStop();
private:
	void warp(GSvector2* pos,const GSvector2& velocity);
private:
	SCROLLMODE mode;
	bool isStart;
	GSvector2 position1;
	GSvector2 position2;
	Point windowSize;
	GSvector2 movingAmount;//どれだけScrollしたか
};
#endif