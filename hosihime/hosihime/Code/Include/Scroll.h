#ifndef _SCROLL_H_
#define _SCROLL_H_

#include "Point.h"
#include "Renderer.h"
#include "MyRectangle.h"

typedef GSvector2 SCROLL_MODE;
#define MODE_VERTICAL SCROLL_MODE(1,0)
#define MODE_HORIZONTAL SCROLL_MODE(0,1)
#define MODE_OMNIDIRECTIONAL SCROLL_MODE(1,1)
class Scroll
{
public:
	Scroll(float widht,float height);
	void initialize();
	void updata();
	void draw(const Renderer& renderer);
	//Scroll処理
	void moving(const GSvector2& position, const GSvector2& offset=GSvector2(0,0));
	//ウィンドウの中にあるか
	const bool isInsideWindow(const GSvector2& pos, const GSvector2& size)const;
	const GSvector2& getMovingAmount()const;

	void setMode(SCROLL_MODE _mode);
	const SCROLL_MODE& getMode()const;

	void stop();
	void start();
	bool isStop();
private:
	void warp(GSvector2* pos,const GSvector2& velocity);
private:
	SCROLL_MODE mode;
	bool isStart;
	GSvector2 position1;
	GSvector2 position2;
	MyRectangle windowSize;
	GSvector2 movingAmount;//どれだけScrollしたか
};
#endif