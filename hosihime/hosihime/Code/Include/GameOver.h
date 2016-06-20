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
	GSvector2 iconPosi[2];
	float time;
	float currentTime;
	float alpha;
	bool isSelectMode;
	GSuint nowSelect;
	Device& device;
	Fade fadeIn;
	Fade fadeOut;
};
#endif