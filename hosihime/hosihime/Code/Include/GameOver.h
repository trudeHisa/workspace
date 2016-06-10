#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_
#include "IScene.h"
class Device;
class GameOver :public IScene
{
public:
	GameOver(Device& device);
	~GameOver();
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	bool isEnd;
	Device& device;
};
#endif