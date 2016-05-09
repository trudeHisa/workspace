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

//�E�΂߉��ɗ����Ă���
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
//���΂߉��ɗ����Ă���
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

//�E���ɗ����Ă���������
void Star::LinePattern3()
{
	rot -= 0.2;	//�p�x
	spd = 6;	    //�X�s�[�h
	ang += 2;

	//�ړ���
	movx = cos(rot * PAI / 180) * spd;
	movy = sin(rot * PAI / 180) * spd;

	pos.x += movx;
	pos.y -= movy;

	//���X��90�x�ɂ���
	if ((rot -= 0.001) < -90) rot = -90;
	if (pos.x >= 1280 || pos.y >= 720)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 0;
		pos.y = 100;
		rot = 0;
	}
}
//�����ɗ����Ă���������
void Star::LinePattern4()
{
	rot -= 0.2;	//�p�x
	spd = 6;	    //�X�s�[�h
	ang -= 2;

	//�ړ���
	movx = cos(rot * PAI / 180) * spd;
	movy = sin(rot * PAI / 180) * spd;

	pos.x -= movx;
	pos.y -= movy;

	//���X��90�x�ɂ���
	if ((rot -= 0.001) < -90) rot = -90;
	if (pos.x <= 0 || pos.y >= 720)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 1280;
		pos.y = 100;
		rot = 0;
	}
}

//�~�^��
void Star::LinePattern5()
{
	rot -= 2;	//�p�x
	spd = 8;	    //�X�s�[�h
	ang += 2;

	//�ړ���
	movx = cos(rot * PAI / 180) * spd;
	movy = sin(rot * PAI / 180) * spd;

	pos.x += movx;
	pos.y -= movy;

	//���X��90�x�ɂ���
	//if ((rot -= 0.001) < -90) rot = -90;
	if (pos.x >= 1280 || pos.y >= 720)
	{
		sound.PlaySE("testSE2.wav");
		pos.x = 640;
		pos.y = 360;
		rot = 0;
	}
}
//�u�����R�݂����ȓ���
void Star::LinePattern6()
{
	rot += 2;	//�p�x
	spd = 10;	    //�X�s�[�h
	sindw = 150;		//�U�ꕝ
	ang += 2;

	//�ړ���
	movx = cos(rot * PAI / 360) * spd;
	movy = cos(rot* PAI / 180) * sindw;
	//�������̐�����60���炢�ɂ���Ɣg���ɂȂ�

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
//�g��/��Ŋp�x������
void Star::LinePattern7()
{
	rot += 2;	//�p�x
	spd = 10;	    //�X�s�[�h
	sindw = 120;		//�U�ꕝ
	ang += 2;

	//�ړ���
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
