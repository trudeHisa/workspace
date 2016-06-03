#include "Timer.h"
#include <GSframetimer.h>
/*
timer 変更
updataで60(フレーム数)で割っていたがフレーム上限が設定されて
なかったため変更

gslibで用意されていた[gsFrameTimerGetTime()]使用
デルタタイムを取得

60カウントが1秒になっている
*/
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
	timer -= 1.f * gsFrameTimerGetTime();
}
float Timer::getTime()
{
	return timer;
}
bool Timer::isEnd()
{
	return timer <= 0;
}