#include"GamePlay.h"
GamePlay::GamePlay(Sound* sound)
	:sound(*sound)
{
}
GamePlay::~GamePlay()
{
}
void GamePlay::Init()
{
	isEnd = false;
}
void GamePlay::Update()
{
	star.LinePattern6();
	isEnd = gsGetKeyTrigger(GKEY_SPACE);
}
void GamePlay::Draw(Renderer& renderer)
{	
	renderer.DrawTextrue("gameplay.bmp", &GSvector2(0, 0));
	//renderer.DrawTextrue("space.bmp", &GSvector2(0, 0));
	star.Draw(renderer);
	renderer.DrawString("aBÇÉCÇ¶", &GSvector2(50, 50),30);
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