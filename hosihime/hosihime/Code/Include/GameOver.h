#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_
#include "IScene.h"
#include "Fade.h"
class Device;
class GameOver :public IScene
{
public:
	GameOver(Device& device);
	~GameOver();
	void Init();
	void Update();
	void FadeOut();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	bool isEnd;
	GSvector2 textPosi;
	float time;
	float currentTime;
	float alpha;
	Device& device;
	Fade fadeIn;
	Fade fadeOut;
};
#endif