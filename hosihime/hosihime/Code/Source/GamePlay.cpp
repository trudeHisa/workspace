#include"GamePlay.h"
#include "Input.h"
#include "Device.h"
#include "PlayMode_Play.h"
#include "PlayMode_Select.h"

GamePlay::GamePlay(Device& device, TimeScore& score)
	: device(device), stageNo(0),
	mode(0),
	score(score), isContinue(false)
{
}
GamePlay::~GamePlay()
{
}
void GamePlay::Init()
{
	isEnd = false;
	mode = Mode(new PlayMode_Select(device, stageNo));
	mode->initialize();
	if (isContinue)
	{
		createStage();
	}
}
void GamePlay::Update()
{
	mode->updata();
	if (device.getInput().getDebugResetTrigger())
	{
		createStage();
	}
	modeEnd();
}
void GamePlay::createStage()
{
	mode = Mode(new PlayMode_Play(device, stageNo, score));
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

	isEnd = true;
}
void GamePlay::Draw(const Renderer& renderer)
{
	mode->draw(renderer);
}
void GamePlay::Finish()
{
	isContinue = false;
}
Scene GamePlay::Next()
{
	if (mode->getFlag() == CLEARFLAG::CLEAR)
	{
		return isLastStage ? Scene::MODE_ENDING : Scene::MODE_RESULT;
	}
	return Scene::MODE_GAMEOVER;
}
bool GamePlay::IsEnd()
{
	return isEnd;
}

void GamePlay::Continue()
{
	isContinue = true;
}
int GamePlay::getStageNo()
{
	return stageNo;
}