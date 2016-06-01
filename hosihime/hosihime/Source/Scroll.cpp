#include "Scroll.h"
#include "Calculate.h"
Scroll::Scroll(const Point* windowSize)
	:windowSize(*windowSize)
{
}
void Scroll::initialize()
{
	position1 = GSvector2(0, 0);
	position2 = GSvector2(windowSize.x, 0);
	movingAmount = GSvector2(0, 0);
	isStart = true;
	mode = VERTICAL;
}
void Scroll::updata()
{

}
void Scroll::draw(Renderer& renderer)
{
	renderer.DrawTextrue("space.bmp", &position1);
	renderer.DrawTextrue("space.bmp", &position2);
}
//ウィンドウの中にあるか
const bool Scroll::isInsideWindow(const GSvector2& pos, const GSvector2& size)const
{
	if (pos.x > windowSize.x)
	{
		return false;
	}
	if (pos.x + size.x < 0)
	{
		return false;
	}

	if (pos.y > windowSize.y)
	{
		return false;
	}
	if (pos.y + size.y < 0)
	{
		return false;
	}
	return true;
}
void Scroll::warp(GSvector2* pos,const GSvector2& velocity)
{
	Calculate<float>calc;
	pos->x = calc.wrap(pos->x - velocity.x, -windowSize.x, windowSize.x);
	
	pos->y = calc.wrap(pos->y - velocity.y, -windowSize.y, windowSize.y);
}

void Scroll::verticalMoving(float x,float alpha)
{
	Calculate<float>calc;
	float lerpx = LERP(alpha, movingAmount.x, x);
	movingAmount.x = lerpx;
	//position1.x = calc.wrap(position1.x - movingAmount.x, -windowSize.x, windowSize.x);
	//position2.x = calc.wrap(position2.x - movingAmount.x, -windowSize.x, windowSize.x);
}
void Scroll::horizontalMoving(float y, float alpha)
{
	Calculate<float>calc;
	float lerpy = LERP(alpha, movingAmount.y,y);
	movingAmount.y = lerpy;
	/*position1.y = calc.wrap(position1.y - movingAmount.y, -windowSize.y, windowSize.y);
	position2.y = calc.wrap(position2.y -movingAmount.y, -windowSize.y, windowSize.y);*/
}
void Scroll::omnidirectionalMoving(const GSvector2& pos, float alpha)
{
	GSvector2 lerp = movingAmount.lerp(pos, alpha);
	movingAmount = lerp;
	/*warp(&position1, lerp);
	warp(&position2, lerp);*/
}

//Scroll処理
void Scroll::moving(const GSvector2&  position, const GSvector2& offset)
{
	if (isStop()){ return; }
	
	float alpha = gsFrameTimerGetTime()*0.2f;
	switch (mode)
	{
	case VERTICAL:
		verticalMoving(position.x+offset.x,alpha);
		break;
	case HORIZONTAL:
		horizontalMoving(position.y + offset.y, alpha);
		break;
	case OMNIDIRECTIONAL:
		omnidirectionalMoving(position + offset, alpha);
		break;
	}
}
const GSvector2& Scroll::getMovingAmount()const
{
	return movingAmount;
}
void Scroll::setMode(SCROLLMODE _mode)
{
	mode = _mode;
}
const SCROLLMODE Scroll::getMode()const
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