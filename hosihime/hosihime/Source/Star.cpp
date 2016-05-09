#include "Star.h"
#define PAI 3.141f

Star::Star()
	:ang(0), pos(640, 300)
{
}
Star::~Star()
{
}

void Star::Init()
{
	//sound.PlaySE("testSE.wav");
}

//右斜め下に落ちていく
void Star::LinePattern1()
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
//左斜め下に落ちていく
void Star::LinePattern2()
{
	ang -= 2;
	pos.x -= 3;
	pos.y += 1;
	if (pos.x <= 0)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 1280;
		pos.y = 100;
	}
}

//右下に落ちていく放物線
void Star::LinePattern3()
{
	rot -= 0.2;	//角度
	spd = 6;	    //スピード
	ang += 2;

	//移動量
	movx = cos(rot * PAI / 180) * spd;
	movy = sin(rot * PAI / 180) * spd;

	pos.x += movx;
	pos.y -= movy;

	//徐々に90度にする
	if ((rot -= 0.001) < -90) rot = -90;
	if (pos.x >= 1280 || pos.y >= 720)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 0;
		pos.y = 100;
		rot = 0;
	}
}
//左下に落ちていく放物線
void Star::LinePattern4()
{
	rot -= 0.2;	//角度
	spd = 6;	    //スピード
	ang -= 2;

	//移動量
	movx = cos(rot * PAI / 180) * spd;
	movy = sin(rot * PAI / 180) * spd;

	pos.x -= movx;
	pos.y -= movy;

	//徐々に90度にする
	if ((rot -= 0.001) < -90) rot = -90;
	if (pos.x <= 0 || pos.y >= 720)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 1280;
		pos.y = 100;
		rot = 0;
	}
}

//円運動
void Star::LinePattern5()
{
	rot -= 2;	//角度
	spd = 8;	    //スピード
	ang += 2;

	//移動量
	movx = cos(rot * PAI / 180) * spd;
	movy = sin(rot * PAI / 180) * spd;

	pos.x += movx;
	pos.y -= movy;

	//徐々に90度にする
	//if ((rot -= 0.001) < -90) rot = -90;
	if (pos.x >= 1280 || pos.y >= 720)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 640;
		pos.y = 360;
		rot = 0;
	}
}
//ブランコみたいな動き
void Star::LinePattern6()
{
	rot += 2;	//角度
	spd = 10;	    //スピード
	sindw = 150;		//振れ幅
	ang += 2;

	//移動量
	movx = cos(rot * PAI / 360) * spd;
	movy = cos(rot* PAI / 180) * sindw;
									//↑ここの数字を60ぐらいにすると波線になる

	pos.x += movx;
	pos.y = movy + 300;

	if (pos.x >= 1280 || pos.y >= 720)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 640;
		pos.y = 300;
		rot = 0;
	}
}
//波線/後で角度をつける
void Star::LinePattern7()
{
	rot += 2;	//角度
	spd = 10;	    //スピード
	sindw = 120;		//振れ幅
	ang += 2;

	//移動量
	movx = cos(rot * PAI / 360) * spd;
	movy = cos(rot* PAI / 120) * sindw;

	pos.x += movx;
	pos.y = movy + 300;

	if (pos.x >= 1280 || pos.y >= 720)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 640;
		pos.y = 300;
		rot = 0;
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
