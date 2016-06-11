#include "Fade.h"

Fade::Fade()
	:isStart(false), isend(false),
	time(0), currentTime(0),
	startColor(0, 0, 0, 0),
	endColor(0, 0, 0, 0)
{
}

Fade::~Fade()
{
}

void Fade::initialize()
{
	isStart = false;
	isend = false;
	time = 0; //delta
	currentTime = 0;
	startColor = GScolor(0, 0, 0, 0);
	endColor = GScolor(0, 0, 0, 0);
}
void Fade::updata()
{
	if (!isStart)
	{
		return;
	}
	if (0 < time&&currentTime < time)
	{
		currentTime += gsFrameTimerGetTime();
		gsVector4Lerp(&currentColor, &startColor, &endColor, currentTime / time);
		return;
	}
	currentColor = endColor;
	isend = true;
}
void Fade::start(const GScolor& startColor, const GScolor& endColor, float time/*second*/)
{
	isStart = true;
	this->startColor = startColor;
	this->endColor = endColor;
	this->time = time*60.0f;
	currentTime = 0;
	isend =false;
}

void Fade::stop()
{
	isStart = false;
}
const bool Fade::isEnd()const
{
	return isend;
}
/*void setMode(FadeMode mode)
{

}*/
void Fade::draw(const Renderer& renderer)
{
	renderer.DrawFillRect(&GSvector2(0, 0), &GSrect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT), &currentColor);
}