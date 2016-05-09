#include"GamePlay.h"
#include"Player.h"

GamePlay::GamePlay(Sound* sound)
	:ang(0), pos(0, 100),sound(*sound)
{
	
}
GamePlay::~GamePlay()
{
	
}
void GamePlay::Init()
{
	//sound.PlaySE("testSE.wav");
	isEnd = false;
}
void GamePlay::Update()
{
	p.Update();
	star.LinePattern7();
	isEnd = gsGetKeyTrigger(GKEY_SPACE);
}
void GamePlay::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("gameplay.bmp", &GSvector2(0, 0));
	p.Draw(renderer);
	star.Draw(renderer);
}
void GamePlay::Finish()
{
}
Scene GamePlay::Next()
{
	return MODE_ENDING;
}
bool GamePlay::IsEnd()
{
	return isEnd;
}