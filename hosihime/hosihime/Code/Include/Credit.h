#ifndef _CREDIT_H_
#define _CREDIT_H_
#include "IScene.h"
#include "Fade.h"
class Device;
class Credit :public IScene
{
public:
	Credit(Device& device);
	~Credit();
	void init();
	void update();
	void draw(const Renderer& renderer);
	void finish();
	Scene next();
	bool isEnd();
private:
	bool isend;
	Device& device;
	Fade fadeIn;
	Fade fadeOut;
};


#endif