#include "Star_eight.h"
#define PAI 3.14f
Star_eight::Star_eight(float speed,float sdwidth)
	:spd(speed), sindw(sdwidth)
{
	rot = 0;
}

Star_eight::~Star_eight()
{

}

GSvector2 Star_eight::moving()
{
	rot += 2;

	GSvector2 velocity(0, 0);
	velocity.x = cos(rot * PAI / 360) * spd;
	velocity.y = -cos(rot * PAI / 180) * sindw;

	return velocity;
}