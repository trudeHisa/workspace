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

void Star::Draw(Renderer& renderer)
{
	renderer.AdditionBlend();
	renderer.DrawTextrue("star.bmp", &pos, NULL, &GSvector2(32, 32), NULL, ang, NULL);
	renderer.InitBlendFunc();
}

void Star::Finish()
{
}
