#include "Star_wave.h"
#define PAI 3.14f
//”g
Star_wave::Star_wave(GSvector2 vel, float shwidth)
:rot(0), velocity(vel), sindw(shwidth)
{
	rot = 0;
}
Star_wave::Star_wave(const Star_wave& other)
{
	velocity = other.velocity;
	sindw = other.sindw;
	rot = 0;
}
Star_wave::~Star_wave()
{

}

GSvector2 Star_wave::moving()
{
	rot += 2;
	velocity.y = cos(rot * PAI / 120) * sindw;

	return velocity;
}

IStarMove* Star_wave::clone()
{
	return new Star_wave(*this);
}