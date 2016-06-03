#ifndef _LOAD_H_
#define _LOAD_H_
#include "IScene.h"
class Device;
class Load :public IScene
{
public:
	Load(Device& device);
	~Load();
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
	void loadTextrue();
	void loadSound();
private:
	bool isEnd;
	Device& device;
};
#endif