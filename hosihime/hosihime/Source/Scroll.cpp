#include "Scroll.h"

Scroll::Scroll(const Point* windowSize)
	:windowSize(*windowSize)
{
}
void Scroll::initialize()
{
	position1 = GSvector2(0, 0);
	position1 = GSvector2(windowSize.x, 0);
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
const bool Scroll::isInsideWindow(float posx,float width)const
{
	float rPos = posx - movingAmount;
	if (rPos > windowSize.x)
	{
		return false;
	}
	if (rPos+width <0)
	{
		return false;
	}
	return true;
}
//Scroll処理
void Scroll::moving(float velocity)
{
	movingAmount += velocity;
	position1.x -= velocity;
	position2.x -= velocity;
	if (position1.x <= -windowSize.x)
	{
		position1.x = windowSize.x;
	}
	if (position2.x <= -windowSize.x)
	{
		position2.x = windowSize.x;
	}
}
const float Scroll::getMovingAmount()const
{
	return movingAmount;
}
