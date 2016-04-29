#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	Timer(int _timer, int _setting);
	void initialize();
	void update();
	bool isEnd();
private:
	int timer;
	int setting;
};
#endif