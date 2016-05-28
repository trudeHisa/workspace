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
//Scroll処理
void Scroll::moving(const GSvector2& velocity)
{
	if (isStop()){ return; }
	Calculate<float>calc;
	switch (mode)
	{
	case VERTICAL:
		movingAmount.x += velocity.x;

		position1.x = calc.wrap(position1.x - velocity.x, -windowSize.x, windowSize.x);
		position2.x = calc.wrap(position2.x - velocity.x, -windowSize.x, windowSize.x);
		break;
	case HORIZONTAL:
		movingAmount.y += velocity.y;

		position1.y = calc.wrap(position1.y - velocity.y, -windowSize.y, windowSize.y);
		position2.y = calc.wrap(position2.y - velocity.y, -windowSize.y, windowSize.y);
		break;
	case OMNIDIRECTIONAL:
		movingAmount += velocity;
		warp(&position1, velocity);
		warp(&position2, velocity);
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