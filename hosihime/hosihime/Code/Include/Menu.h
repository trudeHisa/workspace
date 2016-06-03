#ifndef _MENU_H_
#define _MENU_H_
#include "IScene.h"
class Device;
class Menu :public IScene
{
public:
	Menu(Device& device);
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	Device& device;
	int index;//‘I‘ğˆŠÇ—
	bool isEnd;
};

#endif