#ifndef _OPENING_H_
#define _OPENING_H_
#include "IScene.h"

class Device;
class Opening : public IScene
{
public:
	Opening(Device& device);
	~Opening();
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	bool isEnd;
	Device& device;
	GSvector2 textPos;
	GSvector2 textPos_D;//テキストの初期位置
	GSvector2 vel;
};

#endif
