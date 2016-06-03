#include"GamePlay.h"
#include "Stage.h"
#include "Input.h"
GamePlay::GamePlay(Sound* sound, const Input& input,TimeScore& score)
:sound(*sound), stage(NULL),input(input),stageSelect(input),score(score)//, animTimer(5), anim(&animTimer)
{

}
GamePlay::~GamePlay()
{
	delete stage;
	stage = NULL;
}
void GamePlay::Init()
{
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
		if (input.getActionTrigger())
		{
			stage = stageSelect.createStage();
			stage->initialize();
			stageSelect.finish();
			mode = PLAY;
		}
		break;
	case PLAY:
		if (input.getDebugResetTrigger())
		{
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
void GamePlay::Draw(Renderer& renderer)
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