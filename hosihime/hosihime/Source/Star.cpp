#include "Star.h"

Star::Star(const std::string& textrue, const GSvector2* position)
	:GameObject(textrue, &Point(1, 1), STAR, position)
{
	angle = 0;
}

Star::~Star()
{
}

void Star::updata(MapData* mapdata)
{
	GSvector2 nextVel = velocity;
	float nang = angle;

	nang += 0.03f;
	nextVel.y = sin(nang) * 4;
	nextVel.x = 2;

	if (!isNextMove(mapdata, &nextVel))
	{
		return;
	}
	angle += 0.03f;
	velocity.y = sin(angle) * 4;
	velocity.x = 2;

	move(mapdata, SPACE);
}
void Star::nextVelocity(GSvector2* _velocity, float* angle)
{
	*angle += 0.03f;
	_velocity->y = sin(*angle) * 4;
	_velocity->x = 2;
}
bool Star::collision(int nextPosType)
{
	if (nextPosType == SPACE || nextPosType == PLAYER)
	{
		return true;
	}
	isDead = true;
	return false;
}
void Star::playerPickUp(GSvector2* _velocity)
{
	_velocity->x = velocity.x;
	_velocity->y = velocity.y;
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
