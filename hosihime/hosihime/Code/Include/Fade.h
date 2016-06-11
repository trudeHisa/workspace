#ifndef _FADE_H_
#define _FADE_H_

#include <game.h>
#include "Renderer.h"
class Fade
{
public:
	Fade();
	~Fade();
	void initialize();
	void updata();
	void start(const GScolor& startColor, const GScolor& endColor, float time/*second*/);

	void stop();
	const bool isEnd()const;
	//void setMode(FadeMode mode)
	void draw(const Renderer& renderer);
private:
	bool isend;
	bool isStart;
	float time; 
	float currentTime;
	GScolor startColor;
	GScolor endColor;
	GScolor currentColor;
};
#endif
