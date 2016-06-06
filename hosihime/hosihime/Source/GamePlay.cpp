#include"GamePlay.h"
#include "Stage.h"
#include "Input.h"
#include "Device.h"
GamePlay::GamePlay(Device& device, TimeScore& score)
: device(device),stage(NULL),stageSelect(device),score(score)
//, animTimer(5), anim(&animTimer)
{

}
GamePlay::~GamePlay()
{
	delete stage;
	stage = NULL;
}
void GamePlay::Init()
{
	//device.getSound().StopSE("Opening.wav");
	mode = SELECT;
	isEnd = false;
	stageSelect.initialize();
	stage = NULL;
	//anim.addCell("D", 1, 3, 64, 64);
	//anim.addCell("A", 2, 3, 64, 64);
}
void GamePlay::Update()
{
	/*std::string n = "D";
	if (gsGetKeyState(GKEY_S)!=0)
	{
		n = "A";
	}
	animTimer.updata();
	anim.updata(n);*/
	switch (mode)
	{
	case SELECT:
		stageSelect.updata();
		if (device.getInput().getActionTrigger())
		{
			device.getSound().PlaySE("decision.wav");
			stage = stageSelect.createStage();
			stage->initialize();
			stageSelect.finish();
			mode = PLAY;
		}
		break;
	case PLAY:
		if (device.getInput().getDebugResetTrigger())
		{
			device.getSound().PlaySE("decision.wav");
			stage = NULL;
			stage = stageSelect.createStage();
			stage->initialize();
		}
		stage->updata();

		isEnd=stage->getIsEnd();
		stage->saveScore(score);
		break;
	}
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