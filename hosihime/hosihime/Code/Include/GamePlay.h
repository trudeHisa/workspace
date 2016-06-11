#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "IScene.h"
#include "TimeScore.h"
#include "IPlayMode.h"
#include <memory>
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
	bool IsEnd();
private:
	void modeEnd();
	void createStage();
private:
	std::string stageName;
	int stageNo;
	bool isEnd;
	bool isLastStage;
	Mode mode;
	TimeScore& score;
	Device& device;
};
#endif