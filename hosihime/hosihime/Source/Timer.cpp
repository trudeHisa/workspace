#include "Timer.h"

Timer::Timer(int _timer, int _setting)
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
	timer--;
}
bool Timer::isEnd()
{
	return timer <= 0;
}