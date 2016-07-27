#ifndef _TITLE_H_
#define _TITLE_H_
#include "IScene.h"
#include "Timer.h"
#include "Background_Star.h"

class Device;
class Title :public IScene
{
public:
	Title(Device& device, Background_Star& bStar);
	~Title();
	void init();
	void update();
	void draw(const Renderer& renderer);
	void finish();
	Scene next();
	bool isEnd();
private:
	Timer timer;
	float alpha;
	float rogoAlpha;
	
	Device& device;
	bool isend;
	int index;//‘I‘ğˆŠÇ—
	bool boolSpace;//

	Background_Star& bStar;
};
#endif