#include"GamePlay.h"
#include "Stage.h"
#include "Input.h"
#include "Device.h"
GamePlay::GamePlay(Device& device, TimeScore& score)
	: device(device), stage(NULL), stageName(""),
	stageSelect(device, stageName), score(score)
	//, animTimer(5), anim(&animTimer)
{

}
GamePlay::~GamePlay()
{
}
void GamePlay::Init()
{
	//device.getSound().StopSE("Opening.wav");
	mode = SELECT;
	isEnd = false;
	stageSelect.initialize();
	stage = NULL;
	stageName = "";
	/*anim.addCell("D", 1, 3, 64, 64);
	anim.addCell("A", 2, 3, 64, 64);*/
}
void GamePlay::Update()
{
	/*std::string n = "D";
	if (gsGetKeyState(GKEY_S))
	{
	n = "A";
	}
	animTimer.updata();
	anim.updata(n);*/
	switch (mode)
	{
	case SELECT:
		stageSelect.updata();
		if (stageSelect.isEnd())
		{
			createStage();
		}
		break;
	case PLAY:
		if (device.getInput().getDebugResetTrigger())
		{
			createStage();
		}
		stage->updata();
		isEnd = stage->getIsEnd();
		break;
	}
}
void GamePlay::createStage()
{
	device.getSound().PlaySE("decision.wav");
	stage = std::shared_ptr<Stage>(new Stage(stageName, device));
	stage->initialize();
	stageSelect.finish();
	mode = PLAY;
}
void GamePlay::Draw(const Renderer& renderer)
{
	switch (mode)
	{
	case SELECT:
		stageSelect.draw(renderer);
		break;
	case PLAY:
		stage->draw(renderer);
		break;
	}
	//anim.draw(renderer, "anim.bmp", &GSvector2(50, 50));
}
void GamePlay::Finish()
{
	stage->finish();
}
Scene GamePlay::Next()
{
	return MODE_ENDING;
}
bool GamePlay::IsEnd()
{
	return isEnd;
}