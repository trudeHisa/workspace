#include "Timer.h"
#include <GSframetimer.h>

/*
timer 変更
updataで60(フレーム数)で割っていたがフレーム上限が設定されて
なかったため変更

gslibで用意されていた[gsFrameTimerGetTime()]使用
デルタタイムを取得

60カウントが1秒になっている
06/03久秋：引数を実時間の秒数で指すように変更
				_timer・・・初期値
				_setting・・・設定値
*/
Timer::Timer(float _timer,float _setting)
:time(_timer*FRAMETIME), defTime(_setting),isStop(false)
{
}
void Timer::initialize()
{
	isStop = false;
	time = defTime*FRAMETIME;
}
void Timer::reset(float time)
{
	this->time = time;
	defTime = time;
}
void Timer::update()
{
	if (time <= 0)
	{
		return;
	}
	if (isStop==true)return;

	time -= 1.f * gsFrameTimerGetTime();
}
float Timer::getTime()
{
	return time;
}
bool Timer::isEnd()
{
	return time <= 0;
}

float Timer::getDefTime()
{
	return defTime;
}


void Timer::stop()
{
	isStop = true;
}
void Timer::start()
{
	isStop = false;
}