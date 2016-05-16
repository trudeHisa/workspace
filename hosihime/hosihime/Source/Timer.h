#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	Timer(float _timer, float _setting);
	void initialize();
	void update();
	bool isEnd();
	float getTime();
private:
	float timer;
	float setting;
};
#endif