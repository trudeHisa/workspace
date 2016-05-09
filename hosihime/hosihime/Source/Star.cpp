#include "Star.h"

Star::Star()
	:ang(0), pos(0, 100)
{
}
Star::~Star()
{
}

void Star::Init()
{
	//sound.PlaySE("testSE.wav");
}

void Star::StarSlush()
{
	ang += 2;
	pos.x += 3;
	pos.y += 1;
	if (pos.x >= 1280)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 0;
		pos.y = 100;
	}
}

void Star::Draw(Renderer& renderer)
{
	renderer.AdditionBlend();
	renderer.DrawTextrue("star.bmp", &pos, NULL, &GSvector2(32, 32), NULL, ang, NULL);
	renderer.InitBlendFunc();
}

void Star::Finish()
{
}