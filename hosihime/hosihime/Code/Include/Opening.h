#ifndef _OPENING_H_
#define _OPENING_H_
#include "IScene.h"

class Device;
class Opening : public IScene
{
public:
	Opening(Device& device);
	~Opening();
	void init();
	void update();
	void draw(const Renderer& renderer);
	void finish();
	Scene next();
	bool isEnd();
private:
	bool isend;
	Device& device;
	GSvector2 textPos;
	GSvector2 textPos_D;//テキストの初期位置
	GSvector2 vel;
};

#endif
