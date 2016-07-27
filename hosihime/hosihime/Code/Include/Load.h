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
	void init();
	void update();
	void draw(const Renderer& renderer);
	void finish();
	Scene next();
	bool isEnd();
private:
	void loadTextrue();
	void loadSound();
private:
	bool isend;
	Renderer& renderer;
	Device& device;
};
#endif