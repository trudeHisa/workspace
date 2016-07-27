#include"GamePlay.h"
#include "Input.h"
#include "Device.h"
#include "PlayMode_Play.h"
#include "PlayMode_Select.h"

GamePlay::GamePlay(Device& device, TimeScore& score, StarFade& starFade)
	: device(device), stageNo(0),
	mode(0),
	score(score), isContinue(false), pause(device),
	starFade(starFade), isend(false)
{
}
GamePlay::~GamePlay()
{
}
void GamePlay::init()
{
	isend = false;
	mode = Mode(new PlayMode_Select(device, stageNo));
	mode->initialize();
	if (isContinue)
	{
		createStage();
	}
	pause.initializse();
}
void GamePlay::update()
{
	pause.update();
	if(pause.isPausing())
	{
		pause.pauseMenu();
		isend = pause.isEnd();

		return;
	}
	mode->updata();
	if (device.getInput().getDebugResetTrigger())
	{
		createStage();
	}
	modeEnd();
}
void GamePlay::createStage()
{
	mode = Mode(new PlayMode_Play(device, stageNo, score,starFade));
	mode->initialize();
}
void GamePlay::modeEnd()
{
	if (!mode->isEnd())
	{
		return;
	}
	mode->finish();

	//mode内でセレクトしたい
	if (mode->getMode() == SELECT)
	{
		isLastStage = mode->isLastStage();//最終ステージかどうか判別
		createStage();
		return;
	}

	isend = true;
}
void GamePlay::draw(const Renderer& renderer)
{
	mode->draw(renderer);
	if (pause.isPausing())pause.draw(renderer);
}
void GamePlay::finish()
{
	isContinue = false;
}
Scene GamePlay::next()
{
	if (pause.isEnd()) return pause.next();
	if (mode->getFlag() == CLEARFLAG::CLEAR)
	{
		return isLastStage ? Scene::MODE_ENDING : Scene::MODE_RESULT;
	}
	return Scene::MODE_GAMEOVER;
}
bool GamePlay::isEnd()
{
	return isend;
}

void GamePlay::Continue()
{
	isContinue = true;
}
int GamePlay::getStageNo()
{
	return stageNo;
}