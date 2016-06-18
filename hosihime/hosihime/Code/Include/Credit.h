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
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	bool isEnd;
	Device& device;
	Fade fadeIn;
	Fade fadeOut;
};


#endif