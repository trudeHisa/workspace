#ifndef _ANIMATIONTIMER_H_
#define _ANIMATIONTIMER_H_
class AnimationTimer
{
public:
	AnimationTimer(float time);
	~AnimationTimer();
	void setStarTimer(float time);
	void initialize();
	void updata();
	void reset();
	bool isStop();
	bool isZero();
	void stop();
	void start();
private:
	int startTime;
	int time;
	bool isStar;
};
#endif