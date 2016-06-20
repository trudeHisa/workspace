#include "Timer.h"
#include <GSframetimer.h>

/*
timer �ύX
updata��60(�t���[����)�Ŋ����Ă������t���[��������ݒ肳���
�Ȃ��������ߕύX

gslib�ŗp�ӂ���Ă���[gsFrameTimerGetTime()]�g�p
�f���^�^�C�����擾

60�J�E���g��1�b�ɂȂ��Ă���
06/03�v�H�F�����������Ԃ̕b���Ŏw���悤�ɕύX
				_timer�E�E�E�����l
				_setting�E�E�E�ݒ�l
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