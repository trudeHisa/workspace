#ifndef _TITLE_H_
#define _TITLE_H_
#include "IScene.h"
#include "Timer.h"
class Device;
class Title :public IScene
{
public:
	Title(Device& device);
	~Title();
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	Timer timer;
	float alpha;
	Device& device;
	bool isEnd;
	int index;//‘I‘ğˆŠÇ—
	bool boolSpace;//
};
#endif