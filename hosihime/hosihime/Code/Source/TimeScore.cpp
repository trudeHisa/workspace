#include "TimeScore.h"
#include "../Include/CSVStream.h"
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
void TimeScore::setScore(Timer& timer,int stageNo)
{
	score =(timer.getDefTime()*FRAMETIME)-timer.getTime();
	
}
const int  TimeScore::getScore() const 
{
	return score/FRAMETIME;
}