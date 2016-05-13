#include "Star_slashdown.h"

Star_slashdown::Star_slashdown(const GSvector2 &velocity)
	:velocity(velocity)
{

}

Star_slashdown::~Star_slashdown()
{

}

GSvector2 Star_slashdown::moving()
{
	//GSvector2 velocity;
	return velocity;
}