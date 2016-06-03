#include"GamePlay.h"
#include "Stage.h"
#include "Input.h"
GamePlay::GamePlay( Sound& sound, const Input& input)
:sound(sound), stage(NULL),input(input),stageSelect(sound,input)//, animTimer(5), anim(&animTimer)
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
		if (input.getActionTrigger())
		{
			sound.PlaySE("decision.wav");
			stage = stageSelect.createStage();
			stage->initialize();
			stageSelect.finish();
			mode = PLAY;
		}
		break;
	case PLAY:
		if (input.getDebugResetTrigger())
		{
			sound.PlaySE("decision.wav");
			stage = NULL;
			stage = stageSelect.createStage();
			stage->initialize();
		}
		stage->updata();
		isEnd=stage->getIsEnd();
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