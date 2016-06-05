#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "IScene.h"
#include "Stage.h"
#include "TimeScore.h"
#include "StageSelect.h"

class Device;
enum PLAY_MODE
{
	SELECT, PLAY
};
class GamePlay :public IScene
{
public:
	GamePlay(Device& device, TimeScore& score);
	~GamePlay();
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	void createStage();
private:
	std::string stageName;
	bool isEnd;
	std::shared_ptr<Stage>stage;
	PLAY_MODE mode;
	StageSelect stageSelect;
	TimeScore& score;
	Device& device;
};
#endif