#include"GamePlay.h"
#include "Stage.h"
#include "Star.h"
GamePlay::GamePlay(Sound* sound)
	:sound(*sound), stage(0)
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
}
void GamePlay::Update()
{
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
		stage->updata();
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