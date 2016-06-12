#ifndef _LOAD_H_
#define _LOAD_H_
#include "IScene.h"
class Device;
class Renderer;
class Load :public IScene
{
public:
	Load(Device& device, Renderer& renderer);
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
	Renderer& renderer;
	Device& device;
};
#endif