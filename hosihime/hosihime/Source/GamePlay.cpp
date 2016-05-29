#include"GamePlay.h"
#include "Stage.h"


GamePlay::GamePlay(Sound* sound)
:sound(*sound), stage(0), animTimer(5), anim(&animTimer)
{

}
GamePlay::~GamePlay()
{
	delete stage;
	stage = 0;
}
void GamePlay::Init()
{
	mode = SELECT;
	isEnd = false;
	stageSelect.initialize();
	anim.addCell("D", 1, 3, 64, 64);
	anim.addCell("A", 2, 3, 64, 64);
}
void GamePlay::Update()
{
	std::string n = "D";
	if (gsGetKeyState(GKEY_S))
	{
		n = "A";
	}
	animTimer.updata();
	anim.updata(n);
	switch (mode)
	{
	case SELECT:
		if (stageSelect.updata(&stage))
		{
			stage->initialize();
			stageSelect.finish();
			mode = PLAY;
		}
		break;
	case PLAY:
		if (gsGetKeyTrigger(GKEY_R))
		{
			stageSelect.debugMapCreate(&stage);
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