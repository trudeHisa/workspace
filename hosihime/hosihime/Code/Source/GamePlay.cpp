#include"GamePlay.h"
#include "Input.h"
#include "Device.h"
#include "PlayMode_Play.h"
#include "PlayMode_Select.h"

GamePlay::GamePlay(Device& device, TimeScore& score)
: device(device), stageName(""), stageNo(0),
mode(0),
score(score)
{
}
GamePlay::~GamePlay()
{
}
void GamePlay::Init()
{
	//device.getSound().StopSE("Opening.wav");
	isEnd = false;
	stageName = "";
	mode = Mode(new PlayMode_Select(device, stageNo));
	mode->initialize();
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
	device.getSound().PlaySE("decision.wav");
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
}
Scene GamePlay::Next()
{
	if (mode->getFlag() == CLEARFLAG::CLEAR)
	{
		return isLastStage ? MODE_ENDING : MODE_RESULT;
	}
	return MODE_GAMEOVER;
}
bool GamePlay::IsEnd()
{
	return isEnd;
}