#include "Star_pendulum.h"
#define PAI 3.14f
//êUÇËéq
Star_pendulum::Star_pendulum(float speed, float shwidth)
	:spd(speed), sindw(shwidth)
{
	rot = 0;
}
Star_pendulum::Star_pendulum(const Star_pendulum& other)
	: spd(other.spd), sindw(other.sindw), rot(0)
{

}
Star_pendulum::~Star_pendulum()
{

}

GSvector2 Star_pendulum::moving()
{
	rot += 2;
	
	GSvector2 velocity(0, 0);
	velocity.x = cos(rot * PAI / 360) * spd;
	velocity.y = -sin(rot * PAI / 180) * sindw;

	return velocity;
}

IStarMove* Star_pendulum::clone()
{
	return new Star_pendulum(*this);
}