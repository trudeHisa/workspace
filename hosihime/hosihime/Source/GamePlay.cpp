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
}
void GamePlay::Init()
{
	isEnd = false;
	stage = new Stage("mapdata\\testmap.csv");
	stage->initialize();
}
void GamePlay::Update()
{
	stage->updata();
	isEnd = gsGetKeyTrigger(GKEY_SPACE);
}
void GamePlay::Draw(Renderer& renderer)
{
	stage->draw(renderer);
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