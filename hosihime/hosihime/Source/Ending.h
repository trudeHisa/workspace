#ifndef _ENDING_H_
#define _ENDING_H_
#include "IScene.h"
#include "TimeScore.h"
class Device;
class Ending :public IScene
{
public:
	Ending(Device& device, TimeScore& score);
	~Ending();
 	 void Init();
	 void Update();
	 void Draw(const Renderer& renderer);
	 void Finish();
	 Scene Next();
	 bool IsEnd();
private:
	bool isEnd;
	Device& device;
	TimeScore& score;
};
#endif