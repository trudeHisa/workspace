#include "Star_cricle.h"
#define PAI 3.14f
//‰~
Star_circle::Star_circle(float speed)
	:spd(speed)
{
	rot = 0;
}

Star_circle::~Star_circle()
{

}

GSvector2 Star_circle::moving()
{
	rot -= 2;

	GSvector2 velocity(0, 0);
	velocity.x = cos(rot * PAI / 90) * spd;
	velocity.y = -sin(rot * PAI / 90) * spd;

	return velocity;
}