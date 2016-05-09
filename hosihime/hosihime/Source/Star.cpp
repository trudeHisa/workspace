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

//�E�΂߉��ɗ����Ă���
void Star::LinePattern1(GSvector2* _velocity)
{
	_velocity->x = 3;
	_velocity->y = 1;
}
//���΂߉��ɗ����Ă���
void Star::LinePattern2(GSvector2* _velocity)
{
	_velocity->x = -3;
	_velocity->y = 1;
}

//�E���ɗ����Ă���������
void Star::LinePattern3(GSvector2* _velocity,float* rot)
{
	*rot -= 0.2;	//�p�x
	spd = 6;	    //�X�s�[�h

	_velocity->x = cos(*rot * PAI / 180) * spd;
	_velocity->y = -sin(*rot * PAI / 180) * spd;

	//���X��90�x�ɂ���
	if ((*rot -= 0.001) < -90) *rot = -90;
}
//�����ɗ����Ă���������
void Star::LinePattern4(GSvector2* _velocity, float* rot)
{
	*rot -= 0.2;	//�p�x
	spd = 6;	    //�X�s�[�h

	_velocity->x = -cos(*rot * PAI / 180) * spd;
	_velocity->y = -sin(*rot * PAI / 180) * spd;

	//���X��90�x�ɂ���
	if ((*rot -= 0.001) < -90) *rot = -90;
}

//�~�^��
void Star::LinePattern5(GSvector2* _velocity, float* rot)
{
	*rot -= 2;	//�p�x
	spd = 8;	    //�X�s�[�h

	_velocity->x = cos(*rot * PAI / 180) * spd;
	_velocity->y = -sin(*rot * PAI / 180) * spd;

}
//�u�����R�݂����ȓ���
void Star::LinePattern6(GSvector2* _velocity, float* rot)
{
	*rot += 2;	//�p�x
	spd = 10;	    //�X�s�[�h
	sindw = 150;		//�U�ꕝ

	_velocity->x = cos(*rot * PAI / 360) * spd;
	_velocity->y = cos(*rot* PAI / 180) * sindw; +300;

}
//�g��/��Ŋp�x������
void Star::LinePattern7(GSvector2* _velocity, float* rot)
{
	*rot += 2;	//�p�x
	spd = 10;	    //�X�s�[�h
	sindw = 120;		//�U�ꕝ

	_velocity->x = cos(*rot * PAI / 360) * spd;
	_velocity->y = cos(*rot* PAI / 120) * sindw +300;

}
