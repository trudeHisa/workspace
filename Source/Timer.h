#ifndef _TIMER_H_
#define _TIMER_H_

#define FRAMETIME 60
class Timer
{
public:
	Timer(float _timer,float _setting);
	void initialize();
	void update();
	bool isEnd();
	float getTime();
	void stop();
	void start();
	float getDefTime();
private:
	float time;
	float defTime;
	bool isStop;
};
#endif