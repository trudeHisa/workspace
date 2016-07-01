#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "IScene.h"
#include "TimeScore.h"
#include "IPlayMode.h"
#include <memory>
#include "Pause.h"
class Device;
typedef std::shared_ptr<IPlayMode> Mode;

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
	void Continue();
	bool IsEnd();
	int getStageNo();
private:
	void modeEnd();
	void createStage();
private:
	int stageNo;
	bool isEnd;
	bool isLastStage;
	bool isContinue;
	Mode mode;
	TimeScore& score;
	Device& device;
	Pause pause;
	
};
#endif