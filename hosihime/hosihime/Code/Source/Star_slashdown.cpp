#include "Star_slashdown.h"
//éŒê¸
Star_slashdown::Star_slashdown(const GSvector2 &velocity)
	:velocity(velocity)
{

}
Star_slashdown::Star_slashdown(const Star_slashdown& other)
	: velocity(other.velocity)
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

int Star_slashdown::length()
{
	return 2;
}

IStarMove* Star_slashdown::clone()
{
	return new Star_slashdown(*this);
}