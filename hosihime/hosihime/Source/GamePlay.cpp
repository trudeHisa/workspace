#include"GamePlay.h"
#include"Player.h"

GamePlay::GamePlay(Sound& sound)
	:ang(0), pos(0, 100),sound(sound)
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
	ang+= 2;
	pos.x+=3;
	pos.y += 1;
	if (pos.x >= 1280)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 0;
		pos.y = 100;
	}
	isEnd = gsGetKeyTrigger(GKEY_SPACE);
}
void GamePlay::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("gameplay.bmp", &GSvector2(0, 0));
	//renderer.DrawTextrue("space.bmp", &GSvector2(0, 0));
	renderer.AdditionBlend();
	renderer.DrawTextrue("star.bmp", &pos,NULL,&GSvector2(32,32),NULL,ang,NULL);
	renderer.InitBlendFunc();	
	p.Draw(renderer);
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