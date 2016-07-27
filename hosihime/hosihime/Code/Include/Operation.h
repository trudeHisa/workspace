#ifndef _OPERATION_H_
#define _OPERATION_H_
#include "IScene.h"
#include "Background_Star.h"
#include "Fade.h"
class Device;
class Operation :public IScene
{
public:
	Operation(Device& device);
	~Operation();
	void init();
	void update();
	void draw(const Renderer& renderer);
	void finish();
	void Texchange();
	Scene next();
	bool isEnd();
private:
	int index;
	bool isend;
	Device& device;
	Fade fadeIn;
	Fade fadeOut;
};
#endif


