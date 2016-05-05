#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "IScene.h"
#include "Sound.h"
#include "Star.h"
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
	bool isEnd;
	float ang;
	GSvector2 pos;
	Sound sound;
	Star slush;
};
#endif