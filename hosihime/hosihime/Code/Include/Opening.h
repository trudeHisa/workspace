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
	GSvector2 textPos_D;//�e�L�X�g�̏����ʒu
	GSvector2 vel;
};

#endif
