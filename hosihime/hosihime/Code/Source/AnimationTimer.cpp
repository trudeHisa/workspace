#include "AnimationTimer.h"
#include <algorithm>
#include <gslib.h>
AnimationTimer::AnimationTimer(float time)
{
	setStarTimer(time);
	initialize();
}

AnimationTimer::~AnimationTimer()
{
}

void AnimationTimer::setStarTimer(float time)
{
	startTime = time;
}
void AnimationTimer::initialize()
{
	time = startTime;
	isStart = true;
}
void AnimationTimer::updata()
{
	if (isStop()){ return; }
	time = std::fmaxf(time - 1.f * gsFrameTimerGetTime() , 0);
}
void AnimationTimer::reset()
{
	time = startTime;
}
bool AnimationTimer::isStop()
{
	return !isStart;
}
bool AnimationTimer::isZero()
{
	return time <= 0;
}
void AnimationTimer::stop()
{
	isStart = false;
}
void AnimationTimer::start()
{
	isStart = true;
}