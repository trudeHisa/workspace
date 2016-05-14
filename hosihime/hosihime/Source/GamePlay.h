#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "IScene.h"
#include "Sound.h"
#include "Stage.h"
#include "StageSelect.h"
#include "Animation.h"
enum PLAY_MODE
{
	SELECT, PLAY
};
class GamePlay :public IScene
{
public:
	GamePlay(Sound* sound);
	~GamePlay();
	void Init();
	void Update();
	void Draw(Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	Animation anim;
	AnimationTimer animTimer;
	bool isEnd;
	Sound sound;
	Stage* stage;
	PLAY_MODE mode;
	StageSelect stageSelect;
};
#endif