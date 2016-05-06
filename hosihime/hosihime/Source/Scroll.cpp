#include "Scroll.h"

Scroll::Scroll(const Point* windowSize)
	:windowSize(*windowSize)
{
}
void Scroll::initialize()
{
	movingAmount = 0;
}
//�E�B���h�E�̒��ɂ��邩
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
//Scroll����
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