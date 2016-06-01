#include "Timer.h"
#include <GSframetimer.h>
/*
timer �ύX
updata��60(�t���[����)�Ŋ����Ă������t���[��������ݒ肳���
�Ȃ��������ߕύX

gslib�ŗp�ӂ���Ă���[gsFrameTimerGetTime()]�g�p
�f���^�^�C�����擾

60�J�E���g��1�b�ɂȂ��Ă���
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