#ifndef _TIMESCORE_H_
#define _TIMESCORE_H_
#include "Timer.h"

class TimeScore
{
public:
	TimeScore();
	~TimeScore();
	void init();
	void setScore(Timer& timer);
	const int getScore()const;
private:
	int score;
};

#endif