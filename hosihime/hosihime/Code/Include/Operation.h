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
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	void TexChange();
	Scene Next();
	bool IsEnd();
private:
	int index;
	bool isEnd;
	Device& device;
	Fade fadeIn;
	Fade fadeOut;
};
#endif


