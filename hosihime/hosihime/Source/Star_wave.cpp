#include "Star_wave.h"
#define PAI 3.14f
Star_wave::Star_wave(GSvector2 vel, float shwidth)
	:velocity(vel), sindw(shwidth)
{
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