#include "Star.h"
#define PAI 3.14f
Star::Star(const std::string& textrue, const GSvector2* velocityition)
	:GameObject(textrue, &Point(1, 1), STAR, velocityition)
{
}

Star::~Star()
{
}

void Star::inisialize()
{
	velocity = GSvector2(0, 0);
	castLocation(&position, &location);
	isDead = false;
	rot = 0;
	ang = 0;
}

void Star::updata(MapData* mapdata)
{
	GSvector2 nextVel(0, 0);
	float nrot = rot;

	LinePattern1(&nextVel);
	//LinePattern3(&nextVel, &nrot);

	if (!isNextMove(mapdata, &nextVel))
	{
		return;
	}
	
	LinePattern1(&velocity);
	//LinePattern3(&velocity, &rot);
	ang += 2;

	move(mapdata, SPACE);
}

bool Star::collision(int nextvelocityType)
{
	if (nextvelocityType == SPACE || nextvelocityType == PLAYER)
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
void Star::LinePattern1(GSvector2* _velocity)
{
	_velocity->x = 3;
	_velocity->y = 1;
}
//左斜め下に落ちていく
void Star::LinePattern2(GSvector2* _velocity)
{
	_velocity->x = -3;
	_velocity->y = 1;
}

//右下に落ちていく放物線
void Star::LinePattern3(GSvector2* _velocity,float* rot)
{
	*rot -= 0.2;	//角度
	spd = 6;	    //スピード

	_velocity->x = cos(*rot * PAI / 180) * spd;
	_velocity->y = -sin(*rot * PAI / 180) * spd;

	//徐々に90度にする
	if ((*rot -= 0.001) < -90) *rot = -90;
}
//左下に落ちていく放物線
void Star::LinePattern4(GSvector2* _velocity, float* rot)
{
	*rot -= 0.2;	//角度
	spd = 6;	    //スピード

	_velocity->x = -cos(*rot * PAI / 180) * spd;
	_velocity->y = -sin(*rot * PAI / 180) * spd;

	//徐々に90度にする
	if ((*rot -= 0.001) < -90) *rot = -90;
}

//円運動
void Star::LinePattern5(GSvector2* _velocity, float* rot)
{
	*rot -= 2;	//角度
	spd = 8;	    //スピード

	_velocity->x = cos(*rot * PAI / 180) * spd;
	_velocity->y = -sin(*rot * PAI / 180) * spd;

}
//ブランコみたいな動き
void Star::LinePattern6(GSvector2* _velocity, float* rot)
{
	*rot += 2;	//角度
	spd = 10;	    //スピード
	sindw = 150;		//振れ幅

	_velocity->x = cos(*rot * PAI / 360) * spd;
	_velocity->y = cos(*rot* PAI / 180) * sindw; +300;

}
//波線/後で角度をつける
void Star::LinePattern7(GSvector2* _velocity, float* rot)
{
	*rot += 2;	//角度
	spd = 10;	    //スピード
	sindw = 120;		//振れ幅

	_velocity->x = cos(*rot * PAI / 360) * spd;
	_velocity->y = cos(*rot* PAI / 120) * sindw +300;

}
