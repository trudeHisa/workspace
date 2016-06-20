#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_
#include "IScene.h"
#include "Fade.h"
class Device;
class GamePlay;
class GameOver :public IScene
{
public:
	GameOver(Device& device, GamePlay* _play);
	~GameOver();
	void Init();
	void Update();
	void FadeOut();
	void Draw(const Renderer& renderer);
	void selectDraw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	bool isEnd;
	GamePlay* play;
	GSvector2 textPosi;
	GSvector2 scales[2];
	GSvector4 colors[2];
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