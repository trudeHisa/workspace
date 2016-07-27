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
	/*startÇµÇƒÇÈÇ©ÅH*/
	const bool getIsStart()const;
	const bool getisEnd()const;
	//void setMode(FadeMode mode)
	void draw(const Renderer& renderer);
private:
	bool isEnd;
	bool isStart;
	float time; /*delta*/
	float currentTime;
	GScolor startColor;
	GScolor endColor;
	GScolor currentColor;
};
#endif
