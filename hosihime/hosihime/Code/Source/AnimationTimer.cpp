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
	startTime =time;
}
void AnimationTimer::initialize()
{
	time = startTime;
	isStart = true;
}
void AnimationTimer::updata()
{
	if (isStop()){ return; }
	float add = 1.0f * gsFrameTimerGetTime();
	time = std::fmax(time -add, 0);
}
void AnimationTimer::reset()
{
	time = startTime;
}
const bool AnimationTimer::isStop()const
{
	return !isStart;
}
const bool AnimationTimer::isZero()const
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