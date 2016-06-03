#include "AnimationTimer.h"
#include <algorithm>
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
	startTime = (int)(60 * time);
}
void AnimationTimer::initialize()
{
	time = startTime;
	isStart = true;
}
void AnimationTimer::updata()
{
	if (isStop()){ return; }
	time = std::max(time - 1, 0);
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