#include "Scroll.h"

Scroll::Scroll(const Point* windowSize)
	:windowSize(*windowSize)
{
}
void Scroll::initialize()
{
	movingAmount = 0;
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
}
const float Scroll::getMovingAmount()const
{
	return movingAmount;
}
void Scroll::draw(Renderer& renderer)
{

}