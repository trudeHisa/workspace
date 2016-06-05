#include "Scroll.h"
#include "Calculate.h"

Scroll::Scroll(float widht, float height)
	:windowSize(0, 0, widht, height)
{
}
void Scroll::initialize()
{
	position1 = GSvector2(0, 0);
	position2 = GSvector2(windowSize.getWidth(), 0);
	movingAmount = GSvector2(0, 0);
	isStart = true;
	mode = MODE_VERTICAL;
}
void Scroll::updata()
{
}
void Scroll::draw(const Renderer& renderer)
{
	renderer.DrawTextrue("space.bmp", &position1);
	renderer.DrawTextrue("space.bmp", &position2);
}
//ウィンドウの中にあるか
const bool Scroll::isInsideWindow(const GSvector2& pos, const GSvector2& size)const
{
	MyRectangle rect(pos,size);
	return rect.intersects(&windowSize);
}
void Scroll::warp(GSvector2* pos,const GSvector2& velocity)
{
	Calculate<float>calc;
	float width = windowSize.getWidth();
	float height = windowSize.getHeight();
	pos->x = calc.wrap(pos->x - velocity.x, -width, width);
	pos->y = calc.wrap(pos->y - velocity.y, -height, height);
}
//Scroll処理
void Scroll::moving(const GSvector2&  position, const GSvector2& offset)
{
	if (isStop()){ return; }	

	float alpha = gsFrameTimerGetTime()*0.1f;
	GSvector2 lerp = movingAmount.lerp(position+offset, alpha);
	lerp *=mode;
	//差分確保
	GSvector2 margin = movingAmount - lerp;
	movingAmount = lerp;
	
	//背景スクロール
	warp(&position1, -margin);
	warp(&position2, -margin);
}
const GSvector2& Scroll::getMovingAmount()const
{
	return movingAmount;
}
void Scroll::setMode(SCROLL_MODE _mode)
{
	mode = _mode;
}
const SCROLL_MODE& Scroll::getMode()const
{
	return mode;
}

void Scroll::stop()
{
	isStart = false;
}
void Scroll::start()
{
	isStart = true;
}
bool Scroll::isStop()
{
	return !isStart;
}