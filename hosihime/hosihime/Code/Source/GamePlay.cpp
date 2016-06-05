#include"GamePlay.h"
#include "Input.h"
#include "Device.h"
#include "PlayMode_Play.h"
#include "PlayMode_Select.h"

GamePlay::GamePlay(Device& device, TimeScore& score)
	: device(device), stageName(""),
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
	mode = Mode(new PlayMode_Select(device, stageName));
	mode->initialize();
	/*anim.addCell("D", 1, 3, 64, 64);
	anim.addCell("A", 2, 3, 64, 64);*/
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
	mode = Mode(new PlayMode_Play(device, stageName));
	mode->initialize();
}
void GamePlay::modeEnd()
{
	if (!mode->isEnd())
	{
		return;
	}
	mode->finish();
	if (mode->getMode() == SELECT)
	{
		createStage();
		return;
	}
	isEnd = true;
}
void GamePlay::Draw(const Renderer& renderer)
{
	mode->draw(renderer);
	//anim.draw(renderer, "anim.bmp", &GSvector2(50, 50));
}
void GamePlay::Finish()
{
	mode->finish();
}
Scene GamePlay::Next()
{
	return MODE_ENDING;
}
bool GamePlay::IsEnd()
{
	return isEnd;
}