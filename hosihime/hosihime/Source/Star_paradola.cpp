#include "Star_parabola.h"
#define PAI 3.14f
//����
Star_paradola::Star_paradola(float speed)
	:spd(speed)
{
	rot = 0;
}

Star_paradola::~Star_paradola()
{

}

GSvector2 Star_paradola::moving()
{
	rot -= 0.2;
	
	GSvector2 velocity(0,0);
	velocity.x = cos(rot * PAI / 180) * spd;
	velocity.y = -sin(rot * PAI / 180) * spd;

	//���X��90�x�ɂ���
	if ((rot -= 0.1) < -90) rot = -90;

	return velocity;
}
IStarMove* Star_paradola::clone()
{
	return new Star_paradola(*this);
}