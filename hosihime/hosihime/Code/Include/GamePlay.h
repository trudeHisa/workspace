#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "IScene.h"
#include "TimeScore.h"
#include "IPlayMode.h"
#include <memory>
#include "Pause.h"
#include "StarFade.h"
class Device;
typedef std::shared_ptr<IPlayMode> Mode;

class GamePlay :public IScene
{
public:
	GamePlay(Device& device, TimeScore& score, StarFade& starFade);
	~GamePlay();
	void init();
	void update();
	void draw(const Renderer& renderer);
	void finish();
	Scene next();
	void Continue();
	bool isEnd();
	int getStageNo();
private:
	void modeEnd();
	void createStage();
private:
	int stageNo;
	bool isend;
	bool isLastStage;
	bool isContinue;
	Mode mode;
	TimeScore& score;
	Device& device;
	Pause pause;
	StarFade& starFade;
};
#endif