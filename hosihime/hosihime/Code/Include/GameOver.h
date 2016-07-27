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
	void init();
	void update();
	void draw(const Renderer& renderer);
	void selectdraw(const Renderer& renderer);
	void finish();
	Scene next();
	bool isEnd();
private:
	void blackOut();
	void menuSelect();
	void logoMove();
private:
	bool isend;
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