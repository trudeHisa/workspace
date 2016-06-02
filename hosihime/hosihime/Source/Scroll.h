#ifndef _SCROLL_H_
#define _SCROLL_H_

#include "Point.h"
#include "Renderer.h"
#include "MyRectangle.h"
enum SCROLLMODE
{
	VERTICAL=0,// x
	HORIZONTAL,//y
	OMNIDIRECTIONAL//xy
};
class Scroll
{
public:
	Scroll(float widht,float height);
	void initialize();
	void updata();
	void draw(Renderer& renderer);
	//Scroll処理
	void moving(const GSvector2& position, const GSvector2& offset=GSvector2(0,0));
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
	MyRectangle windowSize;
	GSvector2 movingAmount;//どれだけScrollしたか
};
#endif