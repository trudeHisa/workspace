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
	movingAmount = 0;
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
const bool Scroll::isInsideWindow(float posx, float width)const
{
	if (posx > windowSize.x)
	{
		return false;
	}
	if (posx + width < 0)
	{
		return false;
	}
	return true;
}
//Scroll処理
void Scroll::moving(float velocity)
{
	movingAmount += velocity;
	Calculate<float>calc;
	position1.x = calc.wrap(position1.x - velocity, -windowSize.x, windowSize.x);
	position2.x = calc.wrap(position2.x - velocity, -windowSize.x, windowSize.x);
}
const float Scroll::getMovingAmount()const
{
	return movingAmount;
}
