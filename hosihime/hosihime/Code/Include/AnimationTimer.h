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
	const bool isStop()const;
	const bool isZero()const;
	void stop();
	void start();
private:
	float startTime;
	float time;
	bool isStart;
};
#endif