#include "Timer.h"

Timer::Timer(float _timer, float _setting)
:timer(_timer), setting(_setting)
{
}
void Timer::initialize()
{
	timer = setting;
}
void Timer::update()
{
	if (timer <= 0)
	{
		return;
	}
	timer -= (1.f / 60);
}
float Timer::getTime()
{
	return timer;
}
bool Timer::isEnd()
{
	return timer <= 0;
}