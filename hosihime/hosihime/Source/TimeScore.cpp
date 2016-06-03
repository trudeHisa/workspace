#include "TimeScore.h"

TimeScore::TimeScore() :score(0)
{
}
TimeScore::~TimeScore()
{
}
void TimeScore::init()
{
	score = 0;
}
void TimeScore::setScore(Timer& timer)
{
	score=(timer.getDefTime()*FRAMETIME)-timer.getTime();
}
const int TimeScore::getScore() const 
{
	return score;
}